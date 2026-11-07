---
ts: 2026-11-06T05:04:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZIwDifPOUfc88bnvftSV
---
Hmm, no REG_N_REFS in gcc 2.7.2. The alloc_table's "refs" must come from a different field, maybe `allocno_n_refs` computed in global.c. Let me look at how allocno_n_refs is computed. It's in global.c: `reg_n_refs`? Let me grep allocno_n_refs.
