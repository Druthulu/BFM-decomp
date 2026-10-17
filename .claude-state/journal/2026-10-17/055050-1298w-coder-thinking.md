---
ts: 2026-10-17T11:50:50.827Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm noticing sched1 reordered things so that setting v0 happened before the store, even though the store should come first — likely because v0 got tied to the hard register through local-alloc or CSE substitution. I need to figure out how to prevent sched1 from hoisting that hard-reg assignment ahead of the store, maybe by avoiding a trivial copy for the return value.

Checking the dependency chain, the store depends on load 93 while the v0 assignment only has an anti-dependence on the call, so sched1 is free to move it earlier. I'm wondering if making the return value depend on something the store also touches would force the right ordering, but struct-return cases with BLKmode might generate different RTL (like movstrsi instead of move_by_pieces) that sched1 doesn't reorder the same way, which could explain why the original compiled code didn't hit this problem.

Given my time budget per class, I want to try a few cheap variations: one with an explicit struct pointer copy, another returning a0 directly, and others probing whether a different struct size or alignment changes which block-move path gcc takes.

I'm also wondering if the scheduling difference stems from how sched1 orders instructions relative to the store through s0 versus v0 — in the target, the store happens before v0 is set, while in mine the list scheduler seems to pick the final use instruction first when working backwards, which could explain the different insn ordering.

Maybe it's not about dependency ordering at all but block structure — perhaps the struct-return copy happens after a return label inserted by expand_null_return, putting it in a separate basic block that the scheduler can't merge with the earlier code, which would explain why the ordering stays fixed regardless of priority heuristics.
