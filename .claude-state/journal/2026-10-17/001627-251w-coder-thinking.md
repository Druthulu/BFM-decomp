---
ts: 2026-10-17T06:16:27.847Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm updating the callers to use the renamed function in SC06_018, replacing the raw address calls with func_80187038 for both arg0 and param_1 cases, since the directory uses K&R-style declarations. I expect SC06_020 and SC06_033 follow similar patterns, so I'll check those caller functions next.
