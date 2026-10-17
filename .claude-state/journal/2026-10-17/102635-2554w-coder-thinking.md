---
ts: 2026-10-17T16:26:35.918Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm noticing the scheduler placed the move instruction right after the load, using it to fill the load delay slot rather than leaving it adjacent to the jal call like in my version.

I'm realizing the scheduler is a backwards list scheduler, so it fills the load delay slot with whatever's available — in the target, the asm volatile barrier around the store likely blocks it from moving there, while without that barrier the compiler slots the move in. I'm now trying other orderings, like whether the stored value depends on something computed before or after the call, to see if that forces the right placement without needing the barrier.

I've spent several minutes on this without a clean fix, so I'm going to try a couple approaches quickly: either keep the call before the store so the value is computed post-call, or recompute the argument expression directly into a0 to match the target's `move a0,s0` pattern — though that seems unlikely to match since the target really does show a plain register move. I'm considering reordering the RTL so the move a0 is emitted earlier, hoping the scheduler keeps it there instead of hoisting the load into that slot.

The function pointer cast for the call doesn't change anything since it's still a jal instruction. I'll settle on a WALL score of 6, combining the sched1 argument-copy hoist with the a1/a2 register mismatch as supporting evidence.
