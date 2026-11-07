---
ts: 2026-11-06T05:52:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SicTpRY3wVgzutUOUNlf
---
n3 (launder removed, pin kept) = 24 with 89 ins. So the LAUNDER removal loses 6 instructions! Not the pin.

n2 (pin removed, launder kept) = 15, 94 ins (1 missing).

So the launder is load-bearing for 6 instructions. Hmm, interesting: removing the launder makes the code SHORTER by 6 — cse merged the `cc` computation with something.

Let me look at n3's diff.
