---
ts: 2026-11-06T16:32:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_m8dLiiBiH6lnz19VQH6u
---
Pass order: cse1 → jump_opt → sched1 → regclass → local_alloc. Where's combine? Combine runs after cse? Let me look earlier (2800ish). Anyway.

Key: local_alloc does the copy combining. Let me read local-alloc's combine_regs to see conditions.
