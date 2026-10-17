---
ts: 2026-10-17T10:47:46.627Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
That's much worse at 79+. I notice wx1 still holds onto x1 even though it's unused, which is dead but harmless. I want to figure out why the x1or case with multi/two variants hits 79 — likely because the andi zext instruction sets x1 as a multi-set now, which blocks something. Let me examine one instance closely.
