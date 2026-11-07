---
ts: 2026-11-06T15:04:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lSuqgKkOVOZt7gEd3MfU
---
reg_known_value is in sched.c (sched1's dependency analysis). Not cse. Let me search for where the folding of `(0 << 10)` occurs. It could be in combine.c's `simplify_shift_const` or in `fold_rtx` in cse.c via `equiv_constant`. Let me grep cse.c for equiv_constant and constant handling.
