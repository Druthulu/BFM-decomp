---
ts: 2026-11-06T21:07:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eyzvnoHw2AvOZR4Ubodu
---
This is getting deep. The key question: why is off allocated before e? Let me check whether e's qty is even considered. Note reg 79 (e) has REG_EQUIV — in local-alloc, there's a step "if (note && reg_live_length[regno] >= 0) ..." at line 1058 and 1064 `reg_live_length[regno] *= 2` and line 1079 `if (reg_n_refs[regno] == 2 && ...)`. Let me read 1040-1120.
