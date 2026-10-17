---
ts: 2026-10-17T11:57:41.194Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm thinking a label between the copy and t3v insns might exist during cse2/local-alloc but get stripped by the time final runs, likely because jump2 deletes unreferenced labels after a jump targeting it gets removed. Labels also mark basic block boundaries, which matters for scheduling since blocks can't be reordered across them, though it shouldn't affect liveness.

I need to figure out how a label could appear here from plain C code without a dead branch -- user labels from goto statements are one possibility, but jump.c's handling of unreferenced labels (LABEL_NUSES, LABEL_PRESERVE_P) would determine whether such a label survives. I want to check jump.c to see exactly how it decides whether to delete a label.
