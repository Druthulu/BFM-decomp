---
ts: 2026-11-06T21:24:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5N1mFtsNZ4x8VCOAY81d
---
Interesting: basic block 2 (from 55 to 70) is the then-block. All insns have priority 1. The scheduling order at T-3: "ready list at T-3: 60 (1) 55 (7f000001) 63 (7f000001), now 63 55 60" — hmm.

Let me see the insns 55, 58, 60, 63, 65, 70. Let me print the RTL for them.
