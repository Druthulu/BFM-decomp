---
ts: 2026-10-17T16:49:17.720Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2da07d641273c840
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd2d9a2-f2f0-40d5-a2a4-89410462182c
---
I'm digging into RTL dumps to trace how CSE and the MIPS backend handle the store/load sequence, specifically how cse records memory equivalences after a halfword store and whether the zero-extend from a subsequent lhu load gets folded against that.

I'm considering whether changing the type or access pattern of the pointer could prevent cse from recording the mem equivalence, but same-mode accesses seem to forward regardless. I'm also checking whether volatile stores would evict the mem from cse's equivalence table, though that likely counts as a disallowed "barrier" trick per the constraints.

Then I'm wondering if restructuring the conditionals into a separate guarded block, reached via a jump that gets threaded later, could change the CFG enough to avoid the forwarding — similar to how an earlier attempt handled this. That raises the question of pass ordering: whether jump threading happens before or after cse1 in gcc 2.x, and whether -fcse-follow-jumps would merge the blocks back together anyway, so I want to check the actual compiler dumps rather than keep guessing.
