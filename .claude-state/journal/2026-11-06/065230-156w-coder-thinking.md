---
ts: 2026-11-06T13:52:30.298Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a9242f8c917e0a5c4
model: claude-opus-5-5
effort: medium
turnId: 88b25866-c9e8-45b1-81c6-d2f63ee67e57
---
The src/config tree is clean, so now I'll do the swap.

I'm swapping the win.c bodies across every shard with bank_swap.py, except func_80177EA4 in G31y, which gets a whole-file copy since its header matches HEAD. After that I'll rewrite the TSV, fix the remaining instruments and barrier wall, then run the doc, strict, cast and gate checks.
