---
ts: 2026-11-06T02:55:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Na8N4PCjCfB4DpCVlp48
---
In the .combine dump there are only 3 occurrences of "const_int 28" and no load (mem 28) into a register separate from the store? Let me look at the combine dump around 458-480. The combine dump is after the combine pass (which runs after cse1? no: pass order: jump, cse1, loop, cse2, ..., combine runs BEFORE the first jump? Let me recall gcc 2.7.2 pass order: after expand: jump_optimize, cse, loop, cse2, ... then combine? Actually combine runs after cse1 and loop? The toplev order: ... cse (2827-2870), loop (2900), cse2 (2923), then "combine" later? Let me check: -dc dumps after combine. The order in toplev: after cse2 and jump, there's "instruction combining" then sched1? Hmm.

Anyway, the .combine dump shows the sequence at 458: load 220 into a reg, then store to 28, and then? Let me print it.
