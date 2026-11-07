---
ts: 2026-11-06T04:22:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ggisqCDbcweY7ZYtgOS8
---
Same: lw a0,32(s1) at 4934 before the sll at 4938. So even with p after add in source, sched hoists it.

Hmm. What determines sched1's choice? Let me look at sched.c's priority computation to understand how to influence it. The key: `priority (insn)` = the maximum over dependent insns of (1 + priority) plus... Let me read sched.c's priority function.
