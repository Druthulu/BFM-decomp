---
ts: 2026-10-17T16:37:19.738Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm noticing the same masking pattern applies here as in func_80185944 - masking the high byte of c0 using the same bitwise AND trick, while keeping tv pinned to register $3.
