---
ts: 2026-11-06T16:34:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9SL7OJQowTv50wh5AkQa
---
Both identical in the first jump pass? Wait v1's dump is the TU with our body (no asm) yet it shows asm_input at 1498/1501 — those are from other functions in the TU. Right, the TU has many functions. I need the region of func_80181F80 specifically. The dumps include all functions. My awk over the whole file is useless.

Let me extract the func_80181F80 section from each dump and diff.
