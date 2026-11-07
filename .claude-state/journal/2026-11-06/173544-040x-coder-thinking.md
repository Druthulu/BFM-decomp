---
ts: 2026-11-07T00:35:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zP03rNj8If1Z9fArRH4f
---
Only w10-w19 ran (glob w1[0-9]). Let me score w2* too.

Interesting: w18/w19 (real byte store through obj, varying address) score 7 — better but not 0. Let me check whether the pointer reload happened there. Also w16 (do-while around the big statement) is 10 with 67 ins.

Let me score w2* and then look at w18's diff.
