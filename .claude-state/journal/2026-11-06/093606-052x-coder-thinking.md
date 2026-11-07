---
ts: 2026-11-06T16:36:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3FhhRdWgd2NDnj8BCWTJ
---
The recipe is captured from `make -n` output (RECIPE_RE) — the actual Makefile pipeline. So the pipeline includes maspsx. My cc1 dump .s should still be cc1's raw output; maspsx could transform it. But register allocation (a0 vs a1) happens in cc1. Unless maspsx does something with `addu $4,$4,$0`... maspsx might convert `addu $4,$4,$0`? No.

Hmm wait, maybe the recipe's CC1FLAGS differ from the Makefile default because of a target-specific variable for this TU (the Makefile mentions "Target-specific CC1FLAGS" at line 1061!). Let me read that section.
