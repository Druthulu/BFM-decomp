---
ts: 2026-11-06T10:52:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HInN8XfNltkdAzSuqg8m
---
The scheduling region is the whole basic block. The asm is an insn in the block.

Let me look at how the asm affects dependences: line 1950 "Traditional and volatile asm instructions must be considered to use ... all registers" and memory. The asm insn gets a dependence on/from everything. But within the block, the asm is *before* the load. sched1 might treat the asm as a barrier: insns before it can't move after, and vice versa. Since all our insns are after it, no effect on their relative order... EXCEPT that the asm has a huge priority and is scheduled first (it's already first). Then the scheduler proceeds.

Hmm, so why the different schedule?

OH WAIT. Maybe the asm *ends the scheduling* because `INSN_REF_COUNT`? Or maybe sched1 processes the block in two halves: insns before the asm and after? Let me look for "can_throw" or a loop over regions. Actually there's `schedule_insns` which iterates over blocks and calls schedule_block once per block. No split.

Hmm, but the asm might cause `sched_n_insns` limits...

Let me test empirically whether the asm is what causes the order: in my candidate, replace the do-while with the actual asm (barrier) but keep everything else lever-free. If the score drops to 0, the barrier is the only remaining difference (i.e., we can't remove it with this shape).

Actually orig = 0 with pins+barrier. nobar (pins kept, barrier removed) = 18. nopin (barrier kept) = 22. Let me test: lever-free except the barrier (i.e., v_param + barrier) — if that scores 0, then the barrier is the only thing needed and the pins are unnecessary; but the task requires the barrier gone too.

Hmm.

Actually, let me reconsider the target's schedule cause. Maybe with the barrier, the insns before the asm (unk2, unkC0, unkBC, unk5C stores) are in a *different scheduling region* because sched1 treats the asm as a barrier and splits the block into two scheduling "regions"? Looking at the code: schedule_block takes head..tail = the whole block. But there's `INSN_REF_COUNT(head)=1` trick... Let me search for how sched1 handles asm: line 1950 region.

Let me read around 1930-1990.
