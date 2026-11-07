---
ts: 2026-11-06T09:36:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0oHoW1Rs01EJ5nGmOtDr
---
Line 301 (o) = insn 86: `(set (mem:HI (plus (reg/v 74) (392))) ...)`. reg/v 74 is s0. So the store uses reg 74 (s0's pseudo).

In w, the corresponding insn is at line 307 (offset +5 due to the asm insns being present/absent). Let me print both regions around line 301 (o) / 306 (w).
