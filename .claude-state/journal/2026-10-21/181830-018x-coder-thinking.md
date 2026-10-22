---
ts: 2026-10-22T00:18:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_noogNE6CmzE0A0qyzljN
---
Hmm, that's data. The functions here (ov_SC06_029 etc.) are "ov" modules — maybe the target asm for those functions is in asm/ov_SC06_029/... Let me check.

Actually the item TU is src/ov_SC06_029/ov_SC06_029_jr_8017C954.c — but the function func_8018656C appears in build/asm/ov_SC01_084/data/tail.data.o? That seems like a data section. Hmm, maybe the ov modules are "overlay" modules, and their asm is in asm/ov_SC06_029/.

Let me check what asm dirs exist for our TUs.
