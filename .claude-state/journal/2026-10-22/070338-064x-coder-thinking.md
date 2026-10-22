---
ts: 2026-10-22T13:03:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_NOy9WVDtGTxoR2qyn0Ut
---
All variants score 4 (or worse). The best is 4 with the base being the "no launder" body.

Interesting: `gen_use2_cmp_other` (the compare with the other symbol) scored 7 — the compare adds instructions but the base stays in a register (as we saw).

So item 2 = WALL cse-const-addr with best 4 (28 scored tries so far, some earlier).

Let me count the tries for item 2: w1 (4), n2 (4), n3 (4), b1-b5 (5), x1 (7), plus the 28 variants = ~40 scored tries ✓ (>30).

Now let me do item 3 (C750): score its variants.
