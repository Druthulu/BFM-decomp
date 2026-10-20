---
ts: 2026-10-17T18:52:02.051Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm looking at the join block where the delay slot after the branch is filled with "move a0,s1" pulled eagerly from the target, and wondering how to prevent that instruction from being stolen -- maybe by altering what sits at the head of the join block so the reorg pass finds nothing worth hoisting there.

Tracing through fill_eager_delay_slots' safety check: it steals an instruction from the target thread only when that instruction is safe on the fallthrough path too, and here a0 happens to be dead on the fallthrough side since the next call takes no argument, which is exactly why the steal succeeds. I'm considering whether making a0 live on the fallthrough path, or making the join head instruction the lw into v0 instead, would block the steal since v0's liveness on the fallthrough differs.

Actually that explains it: reorg won't steal an instruction that sets a resource the branch itself reads, so an lw into v0 right before a bnez on v0 is protected from being hoisted. That means if I arrange the join block's head to be exactly that load feeding the branch condition, the scheduler can't pull it into the delay slot, which is the behavior I need.

Without the asm barrier, reorg could steal the move a0,s1 instruction into the delay slot since it's eligible from the target thread. The key condition for stealing is whether a0 is live on the fallthrough path — if the fallthrough path doesn't use a0, reorg will hoist it; if a0 is live there (e.g. consumed by the inner function call), reorg must leave it alone.

Calls only mark argument registers as used if actually passed per the function usage data, so the void-cast call matters here. I'm also wondering if the branch's delay-slot filling logic (fill_eager_delay_slots vs fill_simple) and its jump-prediction heuristic for forward branches could be what's steering this steal-and-redirect decision.

I'm checking whether the fallthrough path can fill the delay slot — but since it loads v0 right before the branch tests v0, that's blocked, and the target's slot is just a nop, so neither thread can fill it. I'm also considering whether restructuring the branch condition or flipping which block the bnez jumps to would change this outcome, but the target still converges to the same join point either way.

I'm trying a few variants to see if reordering the decrement operation, swapping argument evaluation order for the function call, or introducing a local copy of a0 shifts which instruction lands in the delay slot.
