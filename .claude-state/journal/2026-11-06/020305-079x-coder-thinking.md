---
ts: 2026-11-06T09:03:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0uaznxFyo2mnSscdGzzW
---
Interesting! v22 (`z = (a[2]-z)*buf[5];`) scores 2 with 512 insns! That's close. Let me see the diff.

v18/v19/v20 score 20 with 513 insns (the product kept + an extra store) — so the product IS kept when used. Good, that confirms the mechanism: a real use keeps it.

v22: `z = (a[2]-z)*buf[5];` — 512 insns, score 2. Let me look at the diff.
