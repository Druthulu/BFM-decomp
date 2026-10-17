---
ts: 2026-10-17T17:11:49.309Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm puzzled why q1 worked but the cast-add variant with a0 via (s32) didn't—likely the cast produces a separate addition pseudo-operation that breaks the pattern match. I should check the allocation code to find evidence of this mechanism.
