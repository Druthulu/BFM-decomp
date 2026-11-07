---
ts: 2026-11-06T20:34:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bi3fBr8ZMEjYlh9T16xH
---
Let me look at the .rtl dump around 16503 to see the initial placement (the RTL dump is the initial RTL after expand). If the const insn is at the call there, then it's expand, not cse.

Let me view around 16480-16520.
