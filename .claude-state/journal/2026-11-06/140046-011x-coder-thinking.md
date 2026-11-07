---
ts: 2026-11-06T21:00:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FT8PfZtLipA5L8UMlflX
---
Key: qtys are ordered by decreasing length of life, allocated in that order; the first-allocated gets the first free register in class order. So the longest-lived qty in the block gets v0. But also the "sugg" pass ties copy-related qtys first (qty_phys_copy_sugg from move insns and matching constraints) — this is the tie that could make load and sub share v0.

Let me see qty_compare.
