---
ts: 2026-10-22T11:27:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_KNx21j5XdyXwC1BQXNS9
---
fold_binary isn't in the reference set (it's in fold-const.c but maybe named differently in 2.7 — `fold` handles binary ops via `fold_binary` defined in fold-const.c; grep found nothing so maybe it's `fold` itself).

Let me grep fold-const.c for "MINUS_EXPR" in the main `fold` function region and look for a self-minus case.

Actually, a faster approach: just TEST it. Write the variant `func_8001D0E8(t, 0x140 + (t - t), 0xF0);` and see the score. If the front end folds it, score stays 2 (or maybe changes). If it doesn't fold, we'd see extra instructions (score would jump to COUNT). Either way it's informative and cheap.

Let me batch a bunch of "argument expression" variants:
- `0x140 + (t - t)`
- `0x140 ^ (t ^ t)`
- `0x140 + (t & 0)`
- `0x140 | (t & 0)`
- `0x140 + (t * 0)`
- `0x140 - (t - t)`
- `0x140 + (t == t ? 0 : 0)` — hmm ternary with t==t.
- `(0x140 + 0) ` trivial.

Also the third arg similarly.

And a variant where the SECOND arg is `t` and the THIRD is 0xF0... no.

Let me run this batch. It's cheap.

Also let me add variants where the LOAD is the 2nd arg and the constant is the 1st — no.

Let's go.
