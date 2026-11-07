---
ts: 2026-11-06T06:21:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bmbvWpwguzk8uK7ebxDa
---
The body is clean: no asm, no register, no volatile.

But there's an unused `s16 v1;` declaration in the middle block (declared but unused now — `v1` is used for `v1 = ((...)a0)->unk100;` — yes, it IS used for the 2nd load and the `if (v1 == 2)` test). Let me check: `s16 v1;` then `v1 = ...->unk100; if (v1 == 2)`. So v1 is used (as s16). Good.

Wait, but there's `s32 v1w;` and `s16 v1;`. Both used. OK.

Hmm, one concern: `s16 v1` for the `unk100` field — the target's `lh v1,256(s0)` loads s16. Fine.

Now, is this body "lever-free"? Yes: no pins, no launders, no asm.

But hold on — the constraint says "levers of other kinds the def already had (pins under other causes) may stay, never added". We removed everything.

Also: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". Our body has `v1 = ((...)a0)->unk100;` — no identity launder. Good.

Let me now copy x1 to win.c and re-score to confirm.

Then write notes/results/moves.

Note: this item's win.c uses `(s32)a0` instead of a local s0 variable — that's a real C change (dropping the copy). Good.

Let me finalize.
