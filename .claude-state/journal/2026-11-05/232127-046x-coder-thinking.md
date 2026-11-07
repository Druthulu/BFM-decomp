---
ts: 2026-11-06T06:21:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DbTNDp54jSgHO3pjcPCF
---
Item 2: func_801834A4, 41 lines, kinds launder,pin. Two pins both `$2` (tmp and hh), and one launder on tmp.

Lever-free: remove both pins (make them plain s32), remove the launder asm.

Let me copy orig.c and score baseline.
