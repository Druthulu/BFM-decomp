---
ts: 2026-11-06T12:06:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fASPvicfaHsxwzrejeIf
---
y2's diff: the volatile store uses `lui v0; addiu v0; sb v1,0(v0)` (3 insns) vs target's `lui at; sb v1,0(at)` (2 insns, at). Plus `move s1,v0` moved. So the volatile store materializes the address in v0 instead of `at`.

Hmm. The `at` register is used for symbol addresses via `lui at; ...`. A volatile store forces a real register.

Let me try the volatile *load* instead of the store (y5). The load `((s32*)D_8018DB2C)[idx]` → `*(volatile s32*)&((s32*)D_8018DB2C)[idx]`. A volatile load can't be moved above the store (it's volatile). Let me test.

Also y6: make the whole call argument volatile: `(*(volatile s32*)&((s32 *)D_8018DB2C)[idx], local)`. Hmm, the value passed is the pointer.

Let me try y5.
