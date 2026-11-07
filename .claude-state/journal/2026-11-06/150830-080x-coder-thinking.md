---
ts: 2026-11-06T22:08:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zwGeGVlvpMftwAgrMzQG
---
Now let me verify the full results.tsv has 3 rows, one per item, and check DONE WHEN: "every item of RM3x/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0."

Items:
1. func_8017E050 — MATCH, win.c scores 0 ✓
2. func_8017E6BC — MATCH, win.c scores 0 ✓
3. func_80177EA4 — WALL, win.c scores 4.

Let me re-verify items 1 and 2 win.c scores one more time (after all edits) and check results.tsv.

Also: should I clean up the scratch candidate files? The brief doesn't require it, but the shard dir should stay < 200 MB (252K, fine). Keeping the tried candidates is useful evidence.

Let me do a final verification run of all three items' win.c.
