---
ts: 2026-10-15T16:18:49.397Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a86ec957c38e69a06
model: claude-opus-5-5[1m]
effort: medium
turnId: d2ceb926-9b47-40f5-bac5-5608e57c3046
---
I should add a selftest control case right after the T3.c8 carry test, before the S_PRIOR line, mirroring txt7's pattern of a signed cast at offset 0x18 with the nested prior access, keeping one such case to confirm the sign-extension logic works while checking whether a different offset would fail the test.
