---
ts: 2026-11-06T20:23:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zhEtXsDd1nGwJpCVIPQ3
---
Wait — splice.py replaces orig.c (which is the body with the levers) in the TU. For the nolau TU, I spliced nolau.c (levers removed). Good.

Now let me look at the .dbr dump for our function in both, and the .sched2. Let me find the function section and the jal region.

Let me grep for "func_801852B0" in the dbr dumps.
