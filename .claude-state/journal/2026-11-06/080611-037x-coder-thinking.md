---
ts: 2026-11-06T15:06:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3cMgJQh1Wme08Ty8mYDW
---
Line 6887 is in `subst`/`try_combine` — it's used when folding operands within combine. The validity: "Entry I in reg_last_set_value is valid if non-zero, and either ... reg_last_set_table_tick[i] == label_tick" — i.e., across blocks only if no label was crossed. Let me read lines 6880-6900 and 7220-7240 to understand.
