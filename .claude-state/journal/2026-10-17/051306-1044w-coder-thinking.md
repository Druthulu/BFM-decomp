---
ts: 2026-10-17T11:13:06.450Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
I'm noticing func_80181E90 gets called before its declaration in the tree, meaning it's implicitly declared as an unprototyped int-returning function even though it's defined K&R-style. I should write a generic script that takes a function name and file to check this pattern, and verify whether match_one includes common.h.
