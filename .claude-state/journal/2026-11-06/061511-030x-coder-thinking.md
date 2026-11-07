---
ts: 2026-11-06T13:15:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iK996mL0dwkBlC4fEsUQ
---
So in mine, the surviving copy is at 0x9a4 (case 3's position), and case 1's tail at 0x940 became `j 9a4` (backward jump). The merge kept the LATER copy. Target keeps both.

Target: case1 copy at 0x940, case3 copy at 0x9c0, and note target case1 at 0x930 has `bnez v0,940` while mine at 0x930 has `bnez v0,9a4`.

Now: what real-C difference between the two source copies would keep both? The RTL for the two copies is identical modulo pseudo numbering, which renumbered_equal tolerates. So we need the source to produce genuinely different insn patterns but identical final code.

Let me look at the actual RTL at jump2. Use cc1 dumps for this TU: tools/cc1_dumps_tu.sh. That's a shared tool (allowed). Dumps go under my item dir and must be deleted after reading.

Actually, before diving deep: think about what differs. The case-1 tail source:
```
((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
if (((Unkstruct_800B5CB8 *)param_1)->unk1C < 0x10) {
    goto TAIL;
}
goto HITSTUN;
```
Case-3:
```
((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
if (((Unkstruct_800B5CB8 *)param_1)->unk1C < 0x10) {
    /* barrier */
    goto TAIL;
}
goto HITSTUN;
```
Identical.

Idea: in case 1, the preceding code is `if ((unk1C & 3) == 0) func_80143B6C(...)`, then the tail. In case 3, the tail is at the start of the block.

What about the structure of the `goto TAIL` inside the if? If instead written `if (unk1C >= 0x10) goto HITSTUN; goto TAIL;` — the branch would be beqz→bnez? Target has `beqz v0,a20` where a20=HITSTUN. So the compare is `slti v0,v0,16` (v0 = 1 if unk1C<16) and `beqz v0, HITSTUN` = if not(<16) goto HITSTUN. So the source is `if (unk1C < 0x10) goto TAIL; goto HITSTUN;`. Written as `if (unk1C >= 0x10) goto HITSTUN; goto TAIL;` gcc might produce slti + beqz too (canonicalizing)! Actually `x >= 16` → `!(x < 16)` → slti v0, x, 16; beqz v0, HITSTUN. Same instructions, same RTL after canonicalization? The RTL would be (set (reg) (lt (reg) (const 16))) then (if_then_else (eq (reg) 0) ...). Hmm, `if (x < 16) goto TAIL; goto HITSTUN;` also produces exactly that. So same.

Different idea: make the two copies use different *hard* registers? No, target both use v0.

Wait — maybe target's copies differ in a subtle way I haven't compared: the nop placement. Both have nop after the branch (delay slot). Identical.

Hmm, so the source difference that keeps them apart must be in the RTL pattern but not the final code. What about the address expression: `((Unkstruct_800B5CB8 *)param_1)->unk1C` vs a different spelling like `*(s32 *)(param_1 + 0x1C)`? Both produce the same MEM. But the MEM's *alias set* could differ! If one copy uses a different struct type or an array access, the MEM alias set differs → rtx_equal_p on MEM compares... rtx_renumbered_equal_p compares the whole pattern including MEM attributes? It compares rtx structure; MEM_ALIAS_SET is not part of the rtx structure, but the address expression is. If the address expression is structurally different (e.g., `(plus (reg) (const 28))` vs `(plus (reg) (const 28))`) same.

But here's a real trick: use a pointer variable in one copy:
```
s32 *c = &p->unk1C;  // or (s32*)((u8*)p + 0x1C)
*c += 1;
if (*c < 0x10) ...
```
Then the MEM address is `(reg c)` in one copy and `(plus (reg p) (28))` in the other. After CSE/combine and register allocation, the final code is the same: lw v0,28(s0) — because the pointer c is computed once and used; the allocator may keep it in a register (extra insn: addiu c = p+0x1C) unless cse folds it. Hmm, cse would fold `(mem (reg c))` where c is known = p+28? cse's constant/copy propagation would substitute reg c with p+28 if c is a "copy" — but c is an address computed by add, so cse records it as equivalent to (plus p 28) and substitutes. Then RTL becomes identical again. Unless we block cse... but a do-while block between the pointer assignment and use? do-while splits cse EBB, so cse won't propagate across. But then the pointer add survives → extra instruction (addiu). Unless local-alloc coalesces the pointer pseudo with p... no, it's an add.

Hmm. What about using a stack temp? No.

Different approach: exploit `rtx_renumbered_equal_p`'s consistency requirement. If in copy A, the value `v` is used in positions (1) and (2), and in copy B, positions (1) and (2) use two *different* pseudos that both end up in v0 (because their live ranges don't overlap). Then renumbering can't be consistent: A's single pseudo would have to map to two different B pseudos → mismatch! And the final code can still be identical if the two B pseudos both get v0 (they're in a chain, not overlapping).

So: in case 3, use two different temporaries for the value, e.g.:
```
s32 a = p->unk1C + 1;
p->unk1C = a;
s32 b = p->unk1C;   // hmm, would be a load unless cse forwards
if (b < 0x10) goto TAIL;
```
If cse forwards, b becomes a → same. But cse runs before jump2? Yes, cse is before jump2. So b would be equated.

Alternatively: the two uses are the store source and the compare source. In copy A, both use pseudo X. In copy B, use pseudo Y for the store and pseudo Z for the compare, where Y and Z both become v0 because Y dies at the store... but then Z must be computed separately (a load or a copy). A copy `z = y;` would be a move insn in the stream — but at jump2 the move might still be there, adding an instruction (move v0,v0 deleted later? At jump2, a (set (reg z) (reg y)) insn exists and breaks the match... but then it's a mismatch, which is what we want — and if local-alloc coalesces z and y into the same reg, the move becomes a no-op that gets deleted → zero bytes!).

Wait, does the move get deleted? At local-alloc, if z and y are tied/coalesced to the same hard reg, the insn becomes `move v0,v0`. gcc's `final`/`recog` emits it? There's a peephole in the MIPS md: `(set (match_operand 0) (match_operand 1))` with `operands[0] == operands[1]`? There is a general cleanup: `delete_noop_moves` in final.c? Actually gcc 2.7.2 has `delete_noop_moves` called from final? Let me check. There's a pass in final.c: `if (GET_CODE(insn)==INSN && GET_CODE(PATTERN)==SET && SET_DEST==SET_SRC) delete_insn`. I recall `delete_noop_moves` exists in final.c since long ago. Let me grep.

Actually, an even better-known zero-cost construct: `if (cond) { }` — empty if generates a branch insn that's later deleted if empty? No, it can generate nothing at -O.

Alternatively, exploit the fact that the two copies might differ in the *condition* test: target has `slti v0,v0,16`. In one copy write `if (p->unk1C < 0x10)` and in the other `if ((u32)p->unk1C < 0x10)`? unsigned compare → sltiu → different opcode. No.

Hmm, but wait: `slti` vs `sltiu` produce different machine code. No.

What about `if (p->unk1C - 0x10 < 0)`? → subu+bltz, different code.

OK here's another angle: cross-jump's `rtx_renumbered_equal_p` is called per-insn (p1 vs p2) with the renumbering state carried across insns? Let me check rtx_renumbered_equal_p in rtl.c: it uses a static array `renumber_map`? Let me look. It's called separately for each insn in the loop, and the map is reset per call? If per call, then consistency is only within an insn. Hmm, let me check.

Let me read rtx_renumbered_equal_p in gcc 2.7.2 rtl.c.
