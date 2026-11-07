---
ts: 2026-11-06T18:13:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Fz25DpAqWcXotsiRbYfQ
---
The relevant part is around line 380: `qty_birth[qty] = 2*insn_number - 1` — probably for pseudos born at death of another. Let me read lines 360-400 and the block_alloc allocation ordering (find_free_reg). Let me read local-alloc.c around 340-420 and around 950-1100 (block_alloc).
