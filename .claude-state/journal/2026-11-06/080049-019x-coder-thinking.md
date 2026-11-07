---
ts: 2026-11-06T15:00:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ssfGxzj287E9sqsVw7N5
---
The "lines" column in list.tsv = 202/101/101/0/101 — close to 203/102/102/?/102. Interesting: 8017DE00 shows 0 but its body is 32 lines. Hmm, maybe lines = the score/line delta? Actually 202 vs 203 lines, 101 vs 102. So maybe list.tsv's `lines` is body line count minus 1? 8017DE00: 0? Not 31. Maybe it's the number of lines the lever occupies? Whatever.

Now let me verify baseline: score the orig.c body (should be 0 since it's the tree's text). Run dt.sh for item 1.

Wait — scoring orig.c with --body should yield score 0 if the tree's own text. Let me check for one item. Also test the clone bodies are identical across the three.
