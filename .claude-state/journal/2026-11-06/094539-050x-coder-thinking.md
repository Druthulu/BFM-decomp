---
ts: 2026-11-06T16:45:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WAtepqJtynXkFpHyOT2m
---
MATCH on the first try with the twin shape. Score 0. The launder is gone, the pins $4/$5 remain (allowed, not the row kind).

Now record:
- results.tsv row: MATCH, best 0, tries 2 (win0 and win), wall '-', evidence "twin func_8017DE00 shape: a0 = s0 << 10 as loop head, trailing copy dropped; launder gone".

Wait, the "tries" count: I scored win0 (score 2) and win.c (score 0) = 2 tries.

- moves.md: `launder | func_8017D8E8 | MATCH: twin func_8017DE00 — a0 = s0 << 10 moved to loop head, trailing copy dropped (no launder) (W47x)`

- notes.md.

Then item 3.

Let me do these appends.
