---
ts: 2026-11-06T13:18:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AUTVe7E0kk4YLiqlDPdz
---
noop_moves handling is at the START of jump_optimize (line 308), before cross-jumping. So no-op moves are deleted before cross-jump. Not useful.

Hmm wait, that's the deletion of "no-op move" insns, i.e., `move r,r`. Since they're deleted first, they can't block.

OK. What about jumps to the next insn (jump_to_next_insn) — also early.

Let me look at the full jump_optimize flow to see what happens before the cross-jump loop (line ~1800-2000). Let me read 138-308 and around 1700-1930 to understand.

Actually, maybe a better empirical approach: use the cc1 dumps to see the RTL at the jump2/cross-jump point for the CURRENT source (with barrier) — the barrier is an asm insn. If I remove the barrier, the merge happens. I want to know what real-C construct inserts a non-removable zero-byte insn in the stream. 

Candidates that produce zero-byte RTL insns:
- CODE_LABEL (0 bytes)
- NOTE (skipped by the walker)
- BARRIER (0 bytes) — generated after unconditional jumps, but the walker? BARRIER is not a NOTE/CODE_LABEL; if encountered in i2's stream, `GET_CODE(i1) != GET_CODE(i2)` → break. But barriers are placed after jumps, not between.
- USE/CLOBBER insns (0 bytes) — from `asm` operands (not allowed) or from... `__builtin_va_arg`? no.
- A `(set (reg) (reg))` move that's still needed? 4 bytes.

A CODE_LABEL is the best candidate. How does real C create a used CODE_LABEL that survives jump optimization? Labels are created for goto targets and switch cases. Jump optimization removes unreferenced labels. A label is referenced if a jump targets it. The label must be between the beqz and the j TAIL in one copy.

Idea: use a conditional goto to a label placed just before `goto TAIL`, where the conditional goto is *the same* condition, and the two branches... e.g.:

```
if (p->unk1C < 0x10) {
    L: goto TAIL;
}
goto HITSTUN;
```
with L referenced from... itself? `L: goto TAIL;` — L is not referenced.

What if we write:
```
if (p->unk1C < 0x10) goto TAIL;
L: goto HITSTUN;
```
and elsewhere in the function, a `goto L` replaces `goto HITSTUN`. Then L is referenced. The insn at L is `j HITSTUN` (the same as before, just labeled). Now the cross-jump compares the two `j TAIL`s. In case3's stream, before `j TAIL` we have: beqz, then... the label L is placed AFTER the j TAIL? No wait. Let me lay it out:

case3:
```
if (unk1C < 0x10) goto TAIL;    // beqz to HITSTUN? Actually compiles as: slti; beqz HITSTUN; j TAIL
L: goto HITSTUN;
```
Hmm, the layout is: slti; beqz v0, HITSTUN; (delay) ; j TAIL; (delay); L: j HITSTUN. The label L is after the j TAIL. Cross-jump compares j TAIL (case1) with j TAIL (case3). The insn before j TAIL is beqz. The label L is after, irrelevant.

To place a label BEFORE j TAIL, the source must be:
```
if (unk1C < 0x10) { L: goto TAIL; }
goto HITSTUN;
```
and L referenced from somewhere such that the jump to L is emitted. If L is referenced by a `goto L` from case 0, then case 0's code would have an extra jump to L (which is a jump to a jump → threaded to TAIL, and the label might become unused and deleted).

Threading: jump_optimize's `redirect_jump` handles "jump to jump": if the target is a JUMP_INSN, it redirects to the target's target. This happens in `jump_optimize`'s main loop (line ~1800?). If the goto to L is threaded to TAIL, L loses its reference → deleted. Unless the threading happens AFTER the cross-jump in the same pass? The pass is a loop over insns; it processes in order. Hmm.

Alternatively, reference L with a *conditional* jump that is not threaded: `if (cond) goto L;` — conditional jumps to a jump are also threaded? In jump_optimize there's code for `if_then_else` jumps to jumps. Hmm.

Another way to keep a label referenced: make it the target of a jump table? A switch case label! A `switch` with cases generates CODE_LABELs and possibly a jump table (zero-byte data in .text? jump tables are in .rodata / .text). But a switch changes code shape.

OK, alternative approach entirely: maybe the crack for item1 is not about labels but about *different register allocation* in one copy. Reconsider: the final bytes are identical, so at cross-jump time (post-reload) the RTL must be identical. The ONLY way the original avoided the merge with identical final RTL is if the merge opportunity wasn't presented: i.e., the jump_chain didn't contain both jumps, or the walk hit a CODE_LABEL first.

Unless the original binary was built with different flags? No.

Wait... maybe the merge DID happen in the original, but then a LATER pass duplicated the code again? No.

Hmm, hold on. Let me reconsider the direction: cross-jump replaces the *later* jump's preceding block with a jump to the earlier copy? In mine, the earlier copy (case1 at 0x940) was replaced by `j 9a4` and the later copy (case3) survived. do_cross_jump(insn, newjpos, newlpos): insn is the jump being changed. It deletes the matching insns before `insn` (the earlier or later one?). Let me read do_cross_jump: it deletes insns from newjpos to insn (the stream of `insn`), and redirects insn to newlpos. In our mine, case1's tail (the EARLIER copy) became a jump to case3's copy. So insn = case1's `j TAIL` (earlier in the insn chain?) and newlpos in case3's stream. Hmm, that means the jump processed first was case1's j TAIL and it cross-jumped to code before... no, it deleted case1's own insns and jumped to case3's.

Whatever. The point stands.

Let me look at this from the "what did the original source look like" angle: maybe the two copies were NOT identical in the original RTL because one of them had a different *instruction* that the assembler/objdump shows identically due to macro expansion? No, the object bytes are the truth.

Unless the two copies differ in a relocation! E.g., in one copy the `sw`'s address uses a different symbol? No, same s0+28.

I'm stuck on theory. Let me try the empirical route with several candidate bodies. Since each score takes ~1-2 s, 30 tries is cheap. Let me generate variants.

Variant A: temp variable for the increment in case 3 (named iVar1, and a fresh iVar2).
Variant B: pointer alias in case 3.
Variant C: do-while around the increment in case 3.
Variant D: do-while around the whole tail in case 3.
Variant E: reorder statements: compute `p->unk1C + 1` into a temp, compare the temp, store after.
Variant F: case 1 written with a temp instead.
Variant G: use `u16`? no.
Variant H: `if (p->unk1C < 0x10) goto TAIL; goto HITSTUN;` → `if (!(p->unk1C >= 0x10)) ...`.

Actually, wait! What about the `goto TAIL` inside the if vs outside? The source has:
```
if (p->unk1C < 0x10) {
    goto TAIL;
}
goto HITSTUN;
```
What if in one copy we write:
```
if (p->unk1C >= 0x10) {
    goto HITSTUN;
}
goto TAIL;
```
This yields: slti v0, 16; beqz v0, TAIL?? Let's see: `x >= 16` → gcc computes x<16 and branches on false: `slti v0,x,16; beqz v0, HITSTUN` — wait no: `if (x >= 16) goto HITSTUN` compiles to `slti v0,x,16; beqz v0, L_fallthrough?` Hmm: if !(x<16) i.e. x>=16 → goto HITSTUN. So: slti v0,x,16; beqz v0, SKIP; j HITSTUN; SKIP: j TAIL. That's 5 insns (slti, beqz, nop, j HITSTUN, nop, j TAIL) — worse.

Gcc canonicalizes `if (x >= 16) goto A; ... goto B;` with the following fallthrough? The C is `if (x>=16) goto HITSTUN; goto TAIL;` — gcc's jump optimization may reverse the branch: `slti; bnez v0, TAIL`? Then fallthrough to j HITSTUN. Different bytes from target.

OK. Let me now just run a batch. I'll write a Python generator that takes orig.c and produces variants by replacing the case-3 tail text. Then sc.sh scores them all.

Let me define the exact case-3 block text to replace:
```
    case 3:
        ((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
        if (((Unkstruct_800B5CB8 *)param_1)->unk1C < 0x10) {
            /* §5a ZERO-BYTE CROSS-JUMP BARRIER — LOAD-BEARING, DO NOT DELETE.
             * This whole arm is byte-identical to case 1's counter tail; without
             * this line find_cross_jump merges the two and the function comes out
             * 7 instructions short.  Emits no machine code.  See the header. */
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t8_tus2)
            goto TAIL;
        }
        goto HITSTUN;
```

And case-1 tail:
```
        ((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
        if (((Unkstruct_800B5CB8 *)param_1)->unk1C < 0x10) {
            goto TAIL;
        }
        goto HITSTUN;
```

Variants (replacing case-3's block, keeping the barrier removed):
1. temp: `{ s32 u3 = ((Unkstruct_800B5CB8 *)param_1)->unk1C + 1; ((Unkstruct_800B5CB8 *)param_1)->unk1C = u3; if (u3 < 0x10) { goto TAIL; } }`
2. same but compare via p->unk1C after the store (same as orig)
3. pointer alias: `{ s32 *cp = &((Unkstruct_800B5CB8 *)param_1)->unk1C; *cp += 1; if (*cp < 0x10) ... }`
4. do-while around increment
5. do-while around the if
6. `++p->unk1C; if (p->unk1C < 0x10)` — hmm, ++ on a struct field: `++((Unkstruct_800B5CB8 *)param_1)->unk1C;`
7. `p->unk1C = p->unk1C + 1;` (explicit)
8. compare with `<= 0xf`
9. compare with `> 0xf` inverted goto
10. use `iVar1` (the function-wide temp): `iVar1 = p->unk1C + 1; p->unk1C = iVar1; if (iVar1 < 0x10)`.
11. Move the `unk1C += 1` after the compare? no.
12. Use a `s32 x3` declared in the switch's case block.

Also variants on case 1 (the other copy).

Also maybe the trick: make case 1's tail use the shared iVar1 which is live from case 0... Let me just run.

Let me write the generator script. It reads orig.c, removes the barrier, and writes variants to w2_*.c. Use exact string replacement.

I'll write gen.py under my item dir.

Note the brief says the final win.c must be a "bare definition" — yes.

Let me write it.
