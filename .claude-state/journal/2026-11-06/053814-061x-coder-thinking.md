---
ts: 2026-11-06T12:38:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VBBMKH9jeSo422mPFJ5B
---
"Registers live at start: 29 30 72 73" — pseudo 73 is live at function start! That's the uninitialized use... but I removed the early `return ret`. Hmm, in c2 I replaced them with `return 0`. So why is 73 live at start?

Ah wait — maybe pseudo 73 is not ret. Let me check: "Registers live at start" includes 72 (param_1?) and 73. Hmm, 72 = s1 = param_1 (used 42 times, crosses 19 calls, dies in 2 places). 73 live at start...

Let me look at insn 127 (line 587) and the STORE region. Let me view the context of those lines.
