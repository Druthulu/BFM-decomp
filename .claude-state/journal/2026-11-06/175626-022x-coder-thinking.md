---
ts: 2026-11-07T00:56:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yJ5xxRCd8hQZjILFTUh5
---
Hmm, no allocno_priority in global.c. In gcc 2.7.2, global register allocation was in global.c with `global_alloc` computing `allocno->n_refs` and `allocno->live_length`? Let me grep for n_refs / live_length.
