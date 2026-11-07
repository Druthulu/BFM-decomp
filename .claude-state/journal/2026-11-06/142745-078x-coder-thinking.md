---
ts: 2026-11-06T21:27:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tcNiXOQQQqk6tYVIOWOh
---
Hmm, only one set of v0 in the function's .cse2 RTL? That seems odd — the function has a call (set v0) and the sp20 load. Let me look at the section directly around the end.

Wait, maybe the .cse2 dump section for func_80181BF0 is short because... let me print the section.
