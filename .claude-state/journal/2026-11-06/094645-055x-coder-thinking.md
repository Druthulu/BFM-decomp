---
ts: 2026-11-06T16:46:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DL1e9xQ7e2hy440BI20a
---
PSEUDO_REGNO_SIZE(regno) = mode size in words? For HImode: 2 bytes → PSEUDO_REGNO_SIZE = 1? Let me check regs.h or the macro. PSEUDO_REGNO_SIZE is defined as `(PSEUDO_REGNO_BYTES (REGNO) / UNITS_PER_WORD)` maybe with a max 1. Let me grep.
