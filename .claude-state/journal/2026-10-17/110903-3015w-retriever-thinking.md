---
ts: 2026-10-17T17:09:03.651Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab10beb61b63cf7bf
model: claude-haiku-5-5[1m]
effort: medium
turnId: 4a5fdbcb-7cc9-464c-a16e-ebcb9d720258
---
QTY_CMP_PRI isn't present in local-alloc.c for this version — the macro doesn't actually exist in 2.7.2. I should grep across the tools/reference directory for QTY_CMP_PRI and REG_ALLOC_ORDER in mips.h to confirm, and I can probably skip verifying the global.c:607 citation since that wasn't part of what's being asked.
