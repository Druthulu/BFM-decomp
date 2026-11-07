---
ts: 2026-11-06T04:28:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OAkB46dA1zw4a53W4vrf
---
The combine dump for func_801810A4 starts at 23348, and the insns 204/211/232 I read at 23845 ARE for func_801810A4 (since the function starts at 23348 and the next function after... let me check). Actually the combine dump at 23845 is after 23348, so yes it's our function. Good. The sched dump section for func_801810A4 starts at 35406. Let me find the block trace for the `<0x11` arm in the sched dump (after 35406) and the priorities.
