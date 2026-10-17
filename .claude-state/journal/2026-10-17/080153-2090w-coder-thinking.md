---
ts: 2026-10-17T14:01:53.477Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a2ab9a444ea3aa2ca
model: claude-opus-5-5[1m]
effort: medium
turnId: 4fd53509-0294-4563-a878-c510da735377
---
I notice callers pass unk8/unkA as arg2 and (s16)arg1 - I should test treating both as s16 fields with the b6 body logic, where a1v maps to arg1 and pos maps to arg2.
