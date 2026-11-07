---
ts: 2026-11-06T15:10:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tuJxf37CwW5MJJHS0QeQ
---
c1.c is correct. The tu_c1.c copy was stale because the `--try c1 --keep >/dev/null` in command A... hmm, it must have failed. Whatever — let me redo the copy properly and verify.

Actually, this level of dump analysis may be more than needed. Let me think about the mechanism differently.

Actually — wait. Maybe I misdiagnosed. Let me reconsider c1: score 30, 236 ins, identical to no-launder. Why would a second set of vol at the call not affect the birth boost?

Look at b4's RTL: insn 476 sets reg 196 (vol) = div result; insn 478 sets reg 196 = and(196, 65535). So vol's pseudo is 196 and has 2 sets.

Which insn gets the birth boost? Let me find max_priority insns in the sched1 log of the b4 dump. In b4, the schedule matches the target (except the delay slot), so whatever the boost is, b4 is correct. Fine.

For c1, the second set is `vol = (vol|..)&0xFFFF` at the END. Then insn numbering: vol's div set is 476, the second set is later. reg_n_sets[196]=2 too. So why does c1 behave like no-launder (pan first)?

Unless... the second set being in a *different basic block* matters? No, reg_n_sets is global.

OR: c1's second set caused combine to transform `(vol | X) & 0xFFFF` into something where vol's div is... Hmm.

OR maybe the issue isn't reg_n_sets[vol] but something else entirely, and b4's improvement comes from the *andi insn itself* being a barrier/scheduling element rather than the set count. Recall b4 = mask placed at the launder position (before the sx div). That andi is an insn in the block between the two mult groups. Maybe it's the presence of an insn with a certain resource that changes the schedule, not the set count.

Hmm. Let me test: place a *different* zero-cost insn at the launder position that doesn't touch vol — e.g., mask `av` (already dead?) — `av &= 0x7F` would add an insn. Any added insn costs +1 unless it merges.

Alternatively, the andi at the launder position might be exactly what the target would look like if... no, the target has no andi there.

Let me look at this from the reorg angle instead. In b4, the ONLY mismatch is the delay slot: mine has andi in the slot, target has sll. And the bne target offset differs (mine branches to 594, target to 598) — that's just because mine lacks the duplicated sll.

What if I place the mask in a way that reorg doesn't steal it? E.g., put the mask in a *different basic block* — the launder position is in the same block as the bne. If the mask were in an earlier block, it wouldn't be stolen and the sll would be copied. But the mask at the launder position is in the same block as the bne (all one block from 53c to 5a4). 

Hmm, what about putting the mask BEFORE the `if (sx == 0x10)` but in a way that... it's the same block.

What determines reorg's choice between stealing a pre-branch insn and copying the thread insn? In reorg.c, `fill_simple_delay_slots` is called for the branch; it tries `fill_slots_from_thread` first? Let me read reorg.c around the logic.

Actually the target's delay slot is filled from the *thread* (fall-through) — the sll after `li a2,15`. In b4, reorg filled from a pre-branch insn (the andi). Reorg's `fill_simple_delay_slots` has a loop:
```
/* Fill the delay slots of the branch.  */
...
for (insn = PREV_INSN (insn); insn; insn = PREV_INSN (insn)) ...
```
It tries to move insns from before the branch into the slot, then `fill_slots_from_thread` for the target/fall-through.

The andi is eligible (a simple ALU insn with a dead-on-slot result? Actually `andi a1,a1,0xffff` writes a1 which is live after — moving it into the delay slot is fine, since the delay slot executes before the branch target... wait, no: the delay slot executes BEFORE the branch is taken, so moving an insn that must execute regardless into the slot is fine).

Why is the andi moved but not, say, the `subu a2,v1,v0` (the pan result)? Because that's the branch's operand (dependency). And earlier insns like `sra v1,a2,3` feed it. The andi is independent of the branch, so it's the first eligible scanning backwards from the branch: the insns between the andi and the branch are all part of the sx computation chain feeding the bne. So the andi is chosen.

If the andi were placed BEFORE the sx computation (e.g., right after the vol division, which is exactly the launder position — before `sx = (sx+0xA0)/0x14`)... that's where b4 has it, and it's still chosen.

So to avoid reorg stealing it, the mask must not be in the same basic block as the bne, or must be dependent on the branch operand, or be after the branch.

Option: put the second set of vol in the *fall-through* block after the branch but make it zero-cost by merging with the final andi. Hmm.

Option: put the second set in a completely different block where it costs 0. Is there any place where vol can be assigned with no extra insn? What about making vol the destination of an existing computation elsewhere in the function? E.g., the earlier `if (((Unkstruct_800B5CB8 *)a0)->unkFC == 0x18)` block? Or `t`?

Actually — what about declaring vol as the *same variable* as an existing multi-set variable, e.g. `t`? If `vol` were a reuse of `t` (which is set twice: t = func_8004787C(...), t = func_80047948(...)), then vol's pseudo... no, that changes semantics; t is used before.

Alternative approach: make the second set at the launder position but with an insn that reorg WON'T steal. Reorg won't steal an insn that:
- is a jump/call
- has a REG_DEAD note? Actually insns that kill registers are less preferred.
- sets a register that is used by the branch? 
- is a load? Loads can be stolen.

From reorg.c's `fill_simple_delay_slots`, there's a check: it won't move an insn that `sets_cc0_p`, or that has a `REG_DEAD`... Let me read the actual code for the eligibility conditions.

Actually, there's a simpler lever: make the second set of vol be a *store to memory*? No.

Alternative: keep the mask but make the sll not duplicated... no, target has the duplicate.

Alternative: what if the second set of vol is placed in the block and ALSO the sll is duplicated by reorg because the andi is not eligible? An insn is not eligible for a delay slot if it's `INSN_CODE < 0`? Hmm.

Let me look at reorg.c's fill_simple_delay_slots.
