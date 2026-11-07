---
ts: 2026-11-06T12:46:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vPvvBe3yE9qxSBGvqTPk
---
Existing tags. The best fit: a new tag `sched1-ret-war` (sched1/global). Let me phrase it as `sched1-ret-v0-war`.

Before recording, let me do the last few tries (2-3) to be thorough and also confirm the best. Then record WALL with best=46, tries=~40.

Actually, let me try one more genuinely different idea quickly: what if I reorder the arm so `ret = N` comes BEFORE the unkD8 store, but the value assigned is *not* live across the call... no, it would be.

Alternative: `ret = N;` right after the unkCC store and before the call, then the call, then unkD8 store. ret live across the call → s0. Already implied by c1 (s0).

OK, and one final idea: what if the store to unkD8 is done through a *pointer local* declared before, e.g. `((Unkstruct*)param_1)->unkD8 = ...` vs `*(s32*)((u8*)param_1 + 0xD8) = ...`? Same.

Let me instead try combining v21 with the c5 do-while and with `s16 idx` (v09) to see if the combination gets below 46 — a better "best" for the WALL row. Quick: 2 candidates.

w1 = v21 + v09's s16 idx.
w2 = v21 + do-while around ret in the 0x28 arm only (c5 style).

Let me generate and score.
