---
ts: 2026-10-22T00:40:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZScqrgkshbFfd0i0Dv5j
---
Good: for header TU, `--try` uses recs[0] (first includer recipe). So dt.sh score is for one includer (the first). For a header MATCH, must score 0 on every includer: tryinc.py k rotates.

Let me now check the number of includers for these headers. Also, an important detail: the header body may be included in TUs where the function is used differently; but the target comparison is only of this function's instructions.

Plan:
1. For each of 5 items, run sc.sh over existing candidates to get scores.
2. Try more moves to attempt MATCH (each item budget 20-30 min).
3. Write results.tsv row per item; notes; moves.md appends; log.

Let me first check includer counts for the 5 headers.

Let me run the scoring of existing candidates. First check dt.sh works and how long a score takes.
