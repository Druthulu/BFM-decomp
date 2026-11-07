---
ts: 2026-11-06T02:27:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fjXxx9h98Oy5eHtJTOgd
---
All variants still 8 (the delay-slot fill). b10 (store after the calls) gives 75 ins but score 20 (wrong order).

The dbr steal is stubborn. Let me look at the dbr dump for nopin to understand why reorg steals the addiu and whether a C change can prevent it. Let me dump the dbr pass (correct scratch dir p4).

Actually, maybe the answer is in the reorg source: the delay slot fill for a conditional branch with a *forward* branch. Let me look at reorg.c's `fill_simple_delay_slots` and the "delete_from_delay_slot"/"trial" logic. The key: for a JUMP_INSN, `fill_slots_from_thread` is tried first (from the target thread), then `fill_simple_delay_slots` tries the fall-through insns.

Wait, actually for a conditional branch, the fall-through's first insn is the delay slot's natural position. Let me look at how reorg handles it: in `fill_simple_delay_slots`, for a JUMP_INSN:
```
      if (GET_CODE (insn) == JUMP_INSN)
	{
	  ...
	  /* Try to fill the delay slot with insns from the target thread */
	  ...
	  if (fill_slots_from_thread (insn, condition, fallthrough, ...))
	    continue;
	  ...
	}
      /* Then try the simple fill from the following insns */
```
Hmm, `fill_slots_from_thread (insn, condition, thread, opposite_thread, ...)` with thread=fallthrough, opposite=target: it looks for insns at the *end* of the fallthrough thread? No...

Let me just read the dbr dump of the nopin. The dbr dump prints "Reorg function" and maybe the decisions? The .dbr dump shows the RTL after reorg. Not the decisions. Hmm.

Let me think about reorg's fill from the target: for a conditional branch, reorg can fill the delay slot with an insn from the *target* path (executed when the branch is taken) or from the fall-through (executed when not taken). To fill with a fall-through insn, it moves the insn from after the branch into the slot — that's a "fill from thread" where the thread is the fall-through. It requires the insn to be safe on the opposite path (taken). The addiu is safe (v0 dead at the target).

Why wouldn't it in the target? Maybe because the target's v0 IS live at the branch target: the target b3c is the epilogue, but wait — maybe at the RTL level, the branch target block is NOT the epilogue but a shared return block that uses v0? Hmm.

Actually — hold on. The target's bnez at a7c goes to b3c which is the epilogue. But maybe at RTL time the branch targeted a different block (e.g., the function's return label), and v0 was live there due to a USE? No.

Alternatively, reorg may have failed because the candidate addiu's destination v0 is the branch's condition register and the branch insn is `bnez v0` — moving an insn that sets v0 into the delay slot could confuse the "condition" (the branch reads v0 in the delay slot?). On MIPS, the branch condition is read when the branch executes, which is BEFORE the delay slot. So safe. But reorg might be conservative about the condition register: `fill_slots_from_thread` has a check `! reg_set_p (..., PATTERN (trial))`? Hmm, there's `condition` handling: for a conditional jump, the delay slot can't set the condition register if the branch... Actually reorg has `own_thread`, `condition` and checks `reg_referenced_p (condition, PATTERN (trial))`? Let me look at the source.

Let me grep reorg.c for "condition" and "sets" near fill_slots_from_thread.
