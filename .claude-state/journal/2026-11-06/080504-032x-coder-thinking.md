---
ts: 2026-11-06T15:05:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GeYZDZmFdLwet45rr756
---
With the launder (orig, matching):
```
53c lui a0,0x6666
540 ori a0,a0,0x6667
544 li v0,160
548 subu v0,v0,a1        <- 0xA0 - av
54c sll v1,v0,0x7
550 subu v1,v1,v0        <- *0x7F
554 mult v1,a0           <- vol / 0xA0 magic
558 mfhi t1
55c addiu v0,a2,160      <- sx + 0xA0
560 nop
564 mult v0,a0           <- pan / 0x14
568 sra v1,v1,0x1f
56c sra a0,t1,0x6
570 subu a1,a0,v1         <- vol
574 sra v0,v0,0x1f
578 mfhi a2
57c sra v1,a2,0x3
580 subu a2,v1,v0         <- pan
```
So with the launder, vol's mult comes first (source order). Without it, pan first. Both mults are "ready" at the same time; sched1 picks by priority.

Now: what pseudo does the launder's 2nd set demote? vol (a1). The vol division insn (mult v1,a0 at 554, plus the following mfhi/sra/subu group?) is the birthing insn: it sets the vol pseudo (a1). Since vol is live at block start? bb_live_regs: vol is live into this block? vol is defined and used within the same block, so it's NOT live at block start. Hmm.

Wait, `bb_live_regs` is computed at the start of scheduling the block: the set of registers live at block entry. vol is not live at entry (defined here). So birthing_insn_p returns 0 for vol's set.

Which reg IS live at block start? `a2`/sx: sx is set earlier in the same block? Let's see: at 52c `sra a2,v0,0x10` → sx = (s16)...; then `bgez a2`, then a1 = |sx|. So sx (a2) is set in this block too. Hmm.

Hmm, but maybe the basic block starts at 53c (after the beqz at 524/528 branch target?). The `beqz v0,5ac` at 524 branches away; the fall-through continues. The block might be 52c-5a8 or split at 53c (branch target of bgez 530). Actually 53c is a branch target (bgez a2,53c). So basic block = 53c..5a4? Then at 53c: live regs at block start: a1 (av, set at 534/538 in the previous block), a2 (sx)... and vol? No.

Hold on — maybe the birthing insn is the `mult v1,a0` for vol because its dest... The vol pseudo (a1) is set by `subu a1,a0,v1` at 570 — that's the real set. mult writes hi/lo.

Alternatively, the boost applies to `a0` (the magic constant) — lui a0 at 53c sets a0, and a0 is live at block start? At 53c, a0 is not yet set; but a0 is the incoming arg? No, a0 was the arg pointer, clobbered... Actually in the block, `lui a0` at 53c sets a0. reg_n_sets[a0] — a0 is used all over. Hmm, but pseudo vs hard reg: pre-reload these are pseudos.

Let me stop theorizing and instead test cheap variants. Key observation: a2's andi is +0 insns only because it displaced the delay-slot sll (reorg stole andi instead of sll). The count matched. The only difference is *which* insn reorg steals. The target steals the sll. So I need the second set of vol to not be stealable, or to be an insn that reorg wouldn't pick.

What if the second set is a `vol = vol & 0xFFFF;` placed *after* the sll statement, i.e. right before the call, so it merges with the final mask? The final `(vol | (0x3000 | sx)) & 0xFFFF` already has an andi at 5a8. If I add `vol = vol & 0xFFFF;` right before the call, cse/combine may fold it into the existing andi (since it's the same expression `vol & 0xFFFF` used twice) — cse would replace the second occurrence with the first's value... Actually `vol & 0xFFFF` then `(vol | ...) & 0xFFFF`: the final andi applies to the whole or, not just vol. So `vol & 0xFFFF` isn't a subexpression of it. Hmm.

But here's a thought: what if I write the second set as a *narrow* assignment that folds: `vol = (u16)vol;`? That's `vol & 0xFFFF` in a 32-bit reg, same as andi. Same as a2.

Alternative: give vol a second set with a value that's already needed — e.g., reuse vol's register for something later. Since the birth boost requires reg_n_sets==1, ANY second set works, even one that's later in the function. What if I reuse `vol` as a temp later in the function, e.g. for `sx`'s final value? No — sx must stay in a2.

Hmm: what about making the second set be at the very end where it's dead? A dead set is deleted by flow, so reg_n_sets goes back to 1.

What about using `vol` in a `do {} while(0)` block with an assignment that's zero-cost? C0535: do{}while(0) splits cse1 EBB. Not relevant.

New idea: make the *first* set and second set both real, zero-cost by having the divide be a compound assignment on vol where the multiply is the first set — that's t1/t4, scored 14. Why 14? Because the multiply result now goes into vol's register (a1) instead of a scratch; the `sll v1`/`subu v1` computed into v1 then mult. In target: `sll v1,v0,0x7; subu v1,v1,v0; mult v1,a0` — the multiply operand is v1 (a scratch, not a1). If vol is the destination of the multiply, gcc might compute it into a1 → `sll a1,...` which changes regs. Let me look at t1's diff quickly to confirm.

Actually — alternative: two sets of vol where the first is the *whole* expression and the second is a copy that cse deletes but flow keeps? No.

What about the second set being `vol = vol + 0;`? fold removes.

What about `vol = -(-vol);`? fold removes.

What about `vol = vol & 0xFFFF;` where vol is declared `u16`? Then no andi needed (the type truncates, but a u16 local in a 32-bit register needs masking on store only). If vol is declared u16 and the value is used as u16, gcc may not emit the mask... but the arithmetic `((0xA0-av)*0x7F)/0xA0` with u16 type: the division would be unsigned! That changes the magic. Not good.

What about `s16 vol`? Division signed, same magic. Assignment to s16 → subreg, no explicit andi? Actually gcc 2.7.2 with `s16 vol = ...` where the expression is int: the assignment to a QI/HImode pseudo... vol would be HImode. Then the value is used in `(vol | (0x3000|sx)) & 0xFFFF` — HImode promotes to int with a sign extension (sll/sra pair) — extra insns. Bad.

Let me reconsider: maybe the second set doesn't need to be on vol. What if the *birth boost* culprit is the magic constant pseudo `a0` (lui/ori pair)? In the target, `lui a0,0x6666; ori a0,a0,0x6667` at 53c-540 is a birthing insn (constant pseudo set once, live at block start?). In the no-launder version, mine had `lui a2,0x6666; ori a2,a2,0x6667` (a2 instead of a0) and then `addiu a0,a3,160; mult a0,a2` — so the constant landed in a2 and pan's addiu in a0. So the launder also affects the constant's allocation. Ugh, tangled.

Empirical approach is better. Let me enumerate cheap variants:

1. `vol = vol & 0xFFFF;` (a2) → score 2, andi in delay slot.
2. Move the mask to a different place: `vol = vol & 0xFFFF;` placed right after `sx = (sx + 0xA0) / 0x14;`? Then the andi might not be stealable... reorg steals from the bne (the `if (sx == 0x10)` test). Any insn before the bne that's dead on the fall-through... The sll is stolen because it's dead on fall-through (fall-through sets sx=0xF then sll again). An `andi vol` before the bne is NOT dead on the fall-through (vol is used after). Wait, in a2 the andi WAS stolen into the delay slot and executed conditionally?! That would be a bug unless... the delay slot is always executed (branch delay slots execute regardless). Yes! MIPS delay slots execute unconditionally; "steal" just means move the insn into the slot. Reorg picks an insn from before the branch that can be moved there (not dependent on the branch). Both andi and sll qualify; it picked andi (earlier in the list).

So placing the andi later (after the sll statement) would make reorg pick the sll (it's the insn right before the bne). Then the andi would remain after... but it would add an insn (the sll is already there; andi extra = 238). Unless the andi merges with the final `&0xFFFF` at 5a8. Let's think: if the source is:

```
sx = sx << 8;
vol = vol & 0xFFFF;
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
The compiler computes `vol & 0xFFFF` (andi) then ors, then final andi. combine might fold `(vol & 0xFFFF) | X` then `& 0xFFFF` → `(vol | X) & 0xFFFF` (since and distributes). Actually combine could simplify `((vol & 0xFFFF) | (0x3000|sx)) & 0xFFFF` to `(vol | ((0x3000|sx)&0xFFFF)) & 0xFFFF`... The final andi is still needed for sx<<8. Hmm, so likely two andis.

3. Use a second set that combine folds away entirely, e.g. `vol = vol | 0;` (fold). Let's test — fold might not remove a self-assignment at the tree level? `vol | 0` → fold to `vol`, then `vol = vol` → the tree has a MODIFY_EXPR of a var to itself; gcc's cse/fold may or may not delete. Test it (t3-like).

4. `vol = vol;` directly.

5. `vol = (vol + 0) & 0xFFFF;` etc.

6. Reuse vol later: add `vol = sx;` after the call? Then vol's 2nd set is a real move (+1 insn) unless dead... it's dead after, flow deletes. No.

7. Change the *first* set: make vol's initialization happen at declaration? No.

8. Use a compound assignment that the target's instruction sequence already has: e.g. `vol -= 0;` fold.

9. Perhaps declare `vol` as a `register` var? That's a pin lever, not allowed (new lever of kind pin).

Let me test variants 3/4 (self-assign, |0) — quick.
