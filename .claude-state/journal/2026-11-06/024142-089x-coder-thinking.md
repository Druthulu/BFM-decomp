---
ts: 2026-11-06T09:41:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_d15jmNorbE6roFdsVr1M
---
rank_for_schedule: highest priority first; then class relative to last scheduled insn; then INSN_LUID (original order).

The message "insn 86 has a greater potential hazard" is from schedule_select when the chosen insn differs from the ready[0] by hazard (store). Let me look at schedule_select (2600-2700).

Actually the message at 2686 says `ready[best_insn]` — the *best* is the one with a greater hazard, and then it's moved to the end? Let me read schedule_select.
