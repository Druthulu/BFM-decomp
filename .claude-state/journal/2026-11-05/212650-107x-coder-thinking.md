---
ts: 2026-11-06T04:26:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cbMiAYRG4k7UII4lbNtw
---
The sched dump is large. Let me find the block containing insn 217 (the addiu). The dump shows `insn_list 217`. Let me find the insn 217 definition and its neighbors, and the scheduling info (the .sched dump shows the schedule with ";; ready" lists? GCC 2.7.2 sched dump format: it prints the RTL with priority annotations? Let me look around line 36287.
