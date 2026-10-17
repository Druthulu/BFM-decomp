---
ts: 2026-10-17T06:04:45.309Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm noticing other files reference func_8017D234 with the old void(void) signature, likely in pointer tables, so changing it to void(s32) means I'll need to manually update those extern declarations since the automated fix only touched func_8017D254's decls.
