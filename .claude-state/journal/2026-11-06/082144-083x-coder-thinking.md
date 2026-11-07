---
ts: 2026-11-06T15:21:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qyGeqRkib7szMmRML1jq
---
The `ne:SI` count drops from 19 (rtl/jump) to 18 (cse) — so cse folds one `ne` compare: our `t != 3`. Confirmed: cse is the pass.

Let me identify which one exactly to be sure. The dropped one should be the `(ne (reg t) (const_int 3))`. Let me grep the rtl dump for "ne:SI" with const_int 3.

Actually, the count drop 19→18 in cse is good evidence. Let me confirm the specific compare by grepping the rtl dump.
