---
ts: 2026-10-22T15:36:57.789Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
role: loop
---

‹pa› T11 stopped: T11 asks a question:
question

T11 is stopped. The only coder the card allows for cracking functions can no longer run. OpenRouter retired the free MiniMax model (`minimax/minimax-m3.1-flash:free`) on 2026-10-22, partway through the G16 shard. The run failed with API 400 `unrecognized_model` after 113 turns and 12.9M tokens, and it wrote no results rows. G16's scratch files are still in `/home/musashi/bfm-decomp/.run/P40/T11/G16/`.

Where things stand:
- Batch 4 is banked (commit 926e7a64b3): 9 functions matched, 18 wall rows rewritten, the R22 gate passed 218/218 and strict residue-unused is 0. Nothing has matched since then, so nothing is waiting to be banked.
- 47 shards with about 194 functions remain, from G16 to W50x in `.run/P40/T11/mm_queue_a9.txt`. Each one's brief is ready in `.run/P40/ext/`.
- The c…
milestone: `PY tools/plan_edit.py show --section Milestone`
Decide small changes inside the milestone yourself (plan_edit, then release({hold: "question", note})); ask the developer about the milestone or the scope.
