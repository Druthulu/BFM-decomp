---
ts: 2026-10-17T16:12:51.654Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f42f9bd4d9f47ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 1d9764d9-f745-4839-857f-1b214f31db78
---
I'm noticing the scheduling order differs between the two versions because of how the register is used—in A1 the shifted register is a live-in global variable rather than a newly killed one, which affects how gcc's rank_for_schedule heuristic weighs births versus kills when ordering instructions.

I want to test whether reordering the source so the load happens before the conditional branch, placing it earlier in the basic block, would change its allocation behavior enough to produce a matching schedule.
