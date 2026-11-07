---
ts: 2026-11-06T05:51:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q2n9FPNI8ccyUb5dv76S
---
tryinc says 141 includers, but grep found 136 files including the header. The difference: `recs_for` uses `inc.get(tu, [])` mapping header→TUs, which may include TUs that include it transitively (or duplicates). I should check all 141. Let me rerun check_all with 141.
