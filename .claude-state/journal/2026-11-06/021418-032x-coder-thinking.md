---
ts: 2026-11-06T09:14:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EZJNCiPtjzwgmBRXvC8m
---
Let me write a script to print target vs mine insns around a region for a candidate. I can reuse _score_file internals: it computes `mine` and `tgt` and classify. Let me write a small "insns.py" that mirrors _score_file but prints full lists. Copy the relevant portion.

Actually easier: use `--try ... --keep` which prints candidate object path, then objdump it and the baseline. But baseline path per includer. Hmm.

Let me write insns.py under shard dir replicating _score_file up to mine/tgt, then print range.
