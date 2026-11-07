---
ts: 2026-11-06T05:04:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HCB50byRszkOSP3QvVWt
---
`reg_n_refs` comes from `regs.h`'s REG_N_REFS macro, which is `reg_n_refs[regno]`, computed in... `flow.c`? Let me grep in all files for `reg_n_refs`.

Actually in gcc 2.7.2, `reg_n_refs` is computed in `local-alloc.c` or `flow.c` via `REG_N_REFS (regno) += loop_depth`. Let me grep for "loop_depth".
