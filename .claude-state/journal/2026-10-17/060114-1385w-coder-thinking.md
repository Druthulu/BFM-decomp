---
ts: 2026-10-17T12:01:14.495Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm noticing the redundant comparison still gets folded away by CSE, likely because jump threading runs before it and already knows the t==3 branch outcome. I need to figure out how to preserve that extra compare so the structure matches the target's branch sequence rather than collapsing into a simpler path.

Thinking through the GCC toplev.c pass ordering, I realize thread_jumps runs after cse1 but before cse2, so after threading the t==3 jump would bypass the inner test entirely, making it no longer a merge point for cse2 to fold — unless the fallthrough block from the t==5 branch isn't recorded by record_jump_equiv because it lies outside the extended basic block path that cse follows.

I'm also considering whether the source might originally test a different but equal-valued variable (like a cast of the same register) that cse can't recognize as equivalent, which would explain why the redundant comparison survives optimization.

I'm wondering if a switch statement with fallthrough on case 3 and case 5 could compile down to this same chain of compares, or if the duplicate check comes from a label that's actually a branch target from some other unrelated path in the original control flow.

Given how much time I've spent, I should just try a handful of plausible source patterns quickly — a few variations swapping the order of the equality checks and which branch nests inside which — rather than keep analyzing the registers further.
