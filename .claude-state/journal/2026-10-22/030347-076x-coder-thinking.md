---
ts: 2026-10-22T09:03:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EexyzlUWVVdkMvVXkPTU
---
Good — the tag format: `<pass>-<what>`. For item 1, the mechanism: the store's base address needs a hard reg; local_alloc creates the hard-reg copy into the first reg not held by a local qty ($4/a0, because $2 and $3 are held by the call-result and the 0x9000/slt qtys), and that copy becomes the q global's copy preference, so global-alloc puts q in $4. The target needs $3 (which only the pin can hold, since $3 is the 0x9000/slt qty's reg).

Tag: "local-alloc-hardregcopy" — hmm, let me make it descriptive: `lreg-hardregcopy-a0`? Following the style of existing tags (e.g. "global-copy-pref", "greg-lo-reg-count"), I'd use: "local-alloc-hardregcopy" with the explanation.

Let me pick: `local-alloc-hardregcopy` — "the store's base address needs a hard reg; local-alloc's hard-reg copy takes $4 (the first reg no local qty holds) and that copy is the q global's preference".

Now, wait. Before finalizing item 1 as a WALL, let me reconsider ONE more time whether the address copy's reg could be steered...

The key constraint: the address copy takes the first reg not held by a local qty. The local qtys hold: v0 (the call results r77/r80, the consts r84/r85), v1 (the const r78/r81 and the slt r79/r82). The target requires v1 for the const/slt. So $3 is held → the copy takes $4.

Hmm! But hold on: what if the const/slt were NOT local qtys but *hard regs* in the RTL? Then they wouldn't hold v1 as a qty, and the address copy could take v1.

How could the const 0x9000 be a hard reg in the RTL? If the source compared against a variable whose value is a constant in a hard reg... hmm.

OR: what if the comparison were done with the constant in a *different* form: e.g. `func_8012BD14(ptr) - 0x9000 > 0`? That's different code.

Hmm, what about `0x9000 < func_8012BD14(ptr)`? Same.

What if the comparison were `(u32)func_8012BD14(ptr) > 0x9000u`? The unsigned comparison would need `sltu` and the const 0x9000 in a reg — the same shape but `sltu` ✗ (the target has `slt`).

Hmm. So the const is inevitably a qty in v1.

Hmm, unless... the const qty's reg could be something else while the ASM still shows `li v1,0x9000`! Hmm: what if the const qty gets v1 but the *address copy* gets... hmm.

OK, what if the address copy could take v1 in a DIFFERENT block? The address copy is in block 9 (the join). The const qty is in blocks 2/5. If the "not held by any qty" rule is function-wide, we're stuck.

Hmm, let me VERIFY that rule with an experiment! If the rule is function-wide, then making the const qty NOT exist in one of the arms (e.g. by making the case-1 arm's comparison use a different constant spelling that produces a hard-reg const) would free v1.

Hmm, alternatively: let me test whether the address copy's reg changes if I *remove* the slt/const from one arm. E.g. a variant where the case-1 arm's comparison is `func_8012BD14(ptr) > 0x9000` and the case-2 arm's is... they're the same.

Hmm, what if one arm's comparison were spelled with a *variable* const and the other with a literal? Then one const would be a qty (v1) and the other a remat...

Honestly, let me test the simplest version of the hypothesis: does the address copy take v1 if the const/slt qtys are gone? Diagnostic: d3 = replace the comparison with something that doesn't need a const reg, e.g. `if (func_8012BD14(ptr) > 0)` — hmm, that changes the const (0) but the qty still exists (the const 0 → `li v0,0`? hmm, a comparison against 0 needs no const reg: `blez`? the slt would be optimized away → the branch becomes a direct compare). Let me try: `if (func_8012BD14(ptr) > 0)`. Then the const/slt qtys vanish → v0 and v1 are free → the address copy should take v0 (the first free) or v1.

If the address copy takes v0 in that case, then the rule "first reg not held by a local qty" is confirmed (v0 first). And that would suggest the target's v1 could be reached only if v0 is held by a qty and v1 is not.

In the target: v0 is held by the call-result qty ✓ and v1 is held by the const/slt qtys ✗ (that's the blocker).

Hmm! So the ONLY way: the const/slt must not be qtys.

Hmm, hmm. What if the *slt* were eliminated? The target has `slt v1,v1,v0; bnez v1,default` — the slt result is in v1. That's the target's shape: `if (ret > 0x9000) return 0;` compiles to slt+bnez (not a direct branch, since MIPS's `ble` has a 16-bit offset limit... hmm, actually the target's branch is `bnez v1,4030` (a far branch) and `slt v1,v1,v0` — so gcc computed the comparison into a reg because the branch target was too far? Hmm, the branch offset from 3fe8 to 4030 is 0x48 = 72 instructions — beyond the 16-bit branch range? The offset is in instructions: 72 < 32768 ✓ so a direct branch would work. Hmm, but gcc uses slt+beq/bnez when the comparison is "inverted" (the `>` form): `if (ret > 0x9000) goto default;` → the target is far → gcc uses slt + bnez.

Hmm, and the slt result is in v1 (overwriting the const).

So the slt qty (r79) is in v1 too. Hmm.

So both the const and the slt qtys are in v1 → v1 is held.

UNLESS: the const and the slt were the SAME qty! I.e. if the const's value could be computed into the slt's reg — that's what happens (`li v1,0x9000; slt v1,v1,v0` — the slt overwrites the const's reg). But they're still 2 qtys (r78, r79) both in v1.

So v1 is held by qtys. Yeah.

Hmm, so how did the ORIGINAL compiler put the pointer in v1? Because the original compiler (the one that made the game) may have had different reload/local-alloc behavior, OR the original source was different (e.g. the pointer was a hard-reg variable... no).

Hmm! OR: maybe the original source had the pointer used in a way that avoided the address copy: e.g. if the original source's stores were done via a *pointer-typed* variable where the base is loaded...

Hmm, hold on! What if the original source's `q` was a *pointer* (Unkstruct*) and the store was `q->unk2 = val` — the address is the pointer pseudo → the same copy ✗.

Hmm. What if the original source stored via an *array of shorts*: `((u16 *)q)[1] = val;` — same.

OK: what if the original code did the stores through a *different* base: e.g. the stores were `((Unkstruct_801815AC_3 *)arg->unk64)->unk2 = val` — i.e. the source reloaded arg->unk64 in the join! Then the join would have its own load: `lw v1,100(s0); sh v0,2(v1)` — hmm! And the arms' loads (the q loads) would be dead... unless the arms' q loads are needed for something else. Hmm, the target HAS the loads in the arms.

Hmm, hmm. But wait!!! What if the source is:

```c
case 2:
    if (func_8012BD14(ptr) > 0x9000) return 0;
    q = arg->unk64;
    val = 3;
    break;
...
q->unk2 = val;
q->unk34 = 0;
```
and the ORIGINAL compiler produced `lw v1,100(s0)` in the arms and `sh v0,2(v1)` in the join — with the address copy landing in v1 because the original compiler's local-alloc had v1 free (the const in v1 was... hmm).

OK, I need to stop. It's a WALL. Let me be honest about the mechanism and record it.

Actually, hold on, hold on. One more idea!!! What if the *value* (val) and the *pointer* (q) were SWAPPED in their roles — i.e., what if the thing that's global-with-2-defs were the pointer and the thing in the join were... no, that's what we have.

Hmm, what about this: the local qty that holds v0 is the CALL RESULT (r77/r80). What if the call result were NOT a qty but a hard reg? It IS a hard reg (v0) in the RTL: `(set (reg:SI 2 v0) (call ...))` — the call's result is directly in v0! So v0 is a hard-reg use, not a qty!

Hmm! So which qtys hold v0? From the .lreg table: r84 (const 1, block 0), r85 (const 2, block 1) → both → v0 ✓. And r78/r79 (block 2) → v1, r81/r82 (block 5) → v1.

So the qtys holding v0: r84, r85 (the switch constants 1 and 2!). And v1: r78, r79, r81, r82 (the const 36864 and the slt results).

Interesting! So if the switch constants (1 and 2) were NOT qtys, v0 would be free → the address copy would take v0 (not v1) — worse.

And if the const/slt qtys were not qtys, v1 would be free → the address copy takes... v0 first (held by r84/r85) → v0 ✗ (the target needs v1).

Hmm!! So the address copy takes the FIRST reg not held by a qty. To get v1, we need v0 held and v1 free. v0 is held by the switch constants (r84/r85) ✓ and v1 is held by the const/slt (r78/r79/r81/r82) ✗.

So: the const 0x9000 and the slt must NOT be qtys. But they must be materialized in v1 in the asm...

Hmm! What if they were materialized in v1 by RELOAD (remat) rather than by local-alloc? Then at local_alloc time, the const qty would exist but... hmm, it would still be a qty holding some reg.

Hmm, unless the const is rematerialized and local_alloc doesn't allocate a reg to it... In GCC, a qty with reg_equiv_constant still gets a reg in local_alloc (the reg is then deleted by reload's remat).

Hmm, BUT: the §368 technique says the *init insn is deleted* by reload and the constant is rematerialized before each use. The remat reg is chosen by reload (order_regs_for_reload) = the first wholly-unused call-clobbered reg in regno order. Hmm, in the target, the const is in v1 — hmm, at reload time, is v1 "wholly unused"? The switch value (r83) is in v1 (allocated by global_alloc) → v1 is used → hmm, then reload would pick v0? (v0 is used by r84/r85/r76) → a1? ✗.

Hmm, but the target's const IS in v1, so in the pinned version the const was NOT rematerialized (it was a local qty in v1) — or reload picked v1 for the remat.

OK. Enough. WALL for item 1.

Hmm, but hold on. Let me reconsider the whole thing ONE last time from the "what would the original source be" angle, because a MATCH requires reproducing the original's allocation, and the pin is the current project's way. The original PSX compiler (a different gcc?) assigned the pointer to v1.

Hmm, one more idea: what if the original source had the pointer as a `register`-declared variable WITHOUT an asm constraint? "register s32 q;" — that's a "register var" which the brief forbids ("no `register` vars"). Hmm, and it would probably not change anything (gcc 2.7 mostly ignores `register` except for allocation hints... actually gcc 2.7 DOES honor `register` by preferring a register for it, but that doesn't pick a specific one).

OK. Item 1 = WALL. Let me record it and move on. I'll spend the remaining time on items 2 and 3.

For item 2 and 3 (the twins): pins $18 (w) and $0 (zr). The notes say:
- Target (115 ins): w (= w0) in $18/s2, ot in $19/s1; flag in $16/s0, flag2 in $20/s4 (move s4,s0), flag3 in $22/s6 (move s6,s4), flag4 back in $16/s0 (move s0,s4).
- Lever-free body: score 29, 113 ins.
- Blockers: (1) the `+ zr` addends keep the flag→flag2 and flag2→flag4 copies alive; (2) the $18 pin fixes w in s2; without it gcc gives the more-referenced w0 the first callee-saved reg ($19/s1) and ot the second ($20/s2).

So for these items, the lever is: (a) make the flag copies survive (e.g. via s16 widths, per the cookbook "HImode copy escapes cse"), and (b) swap the callee-saved order (w → s2, ot → s1).

Interesting: the notes mention that a variant keeping `w = w0;` as a real copy scores the same 29.

The key insight from the moves.md: "pin | func_8017E1D4 | MATCH — $0 zr pin: s16 flag2/3/4 copies (sign-extend escapes cse, combine nonzero_bits -> move); $18 w pin: ot = inner call split from the return (ot +2 refs > w in greg)". That's a very similar twin! The moves for that item: s16 copies for the zr pins, and splitting the ot from the return for the $18 pin.

So for our twins, the analogous levers:
- zr pin: use s16 (or u16?) copies of the flag so the "sign-extend escapes cse" and the copies survive → the `move s4,s0` etc. survive.
- $18 pin (w in s2): make `ot` have more refs than w so that ot gets the FIRST callee-saved reg ($19/s1) and w gets the second ($20/s2)? Hmm, wait: the target has w in $18 (s2) and ot in $19 (s1). The note says "without it gcc gives the more-referenced w0 the first callee-saved register ($19/s1) and ot the second ($20/s2)". So we need w to have FEWER refs than ot (so ot gets s1 and w gets s2). Like the moves.md entry: "ot = inner call split from the return (ot +2 refs > w in greg)".

So the plan for items 2/3:
1. Read the source of func_801886B8 and func_801889B8.
2. Try: s16 copies for the flags; split the ot from the return; etc.

Let me first look at the source. Let me find the function in the src file.

Time: I'm at ~1h55m. Let me move fast on items 2 and 3 (~25 min each).

Let me first write item 1's results row + notes, then start item 2.

Actually, let me first do the item-1 bookkeeping (results.tsv row, notes.md update, moves.md line), then item 2.

The results.tsv row format: `dir file func kinds result best tries wall evidence` (tabs).
- dir: func_801815AC__ov_SC05_018_jr_8017D604
- file: src/ov_SC05_018/ov_SC05_018_jr_8017D604.c
- func: func_801815AC
- kinds: pin
- result: WALL
- best: 4
- tries: 72
- wall: local-alloc-hardregcopy
- evidence: "gcc pass + mechanism ≤ 140 chars"

Let me count the tries: c0(1) c1(2) c2(3) c3(4) c4(5) v05-v10(11) w1(12) w2(compile error) w3(13) w4(14) x1(15) x2(16) d1(17) d2(18) s01..s10 × t1..t5 = 50 → 68, y1(69) y2(70), orig(71), win(72). Let me say 72.

Let me write the row and update the notes.
