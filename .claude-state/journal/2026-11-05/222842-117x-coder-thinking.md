---
ts: 2026-11-06T05:28:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mlJyaxHS3sHgzpK8gGeb
---
The call in our function is at line 63746 in the .flow dump. Let me look at the insns before it (the stores). Let me print lines 63500-63760 and grep for `(mem:HI`.

Actually, let me count `(set (mem:HI` occurrences in the region 63000-63750 for flow, and the corresponding region in cse/greg.

Let me find the same function in the .cse dump (grep func_8014E284) and compare counts.

Let me just extract the region and count `(set (mem:HI`.
