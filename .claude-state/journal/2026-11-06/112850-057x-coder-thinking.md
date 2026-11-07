---
ts: 2026-11-06T18:28:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xsmLQqxxXeCm9uq0l4lU
---
Still 3. Time 11:28:46 → 17.7 min. I need ~2.3 more minutes of tries. Let me try a few more:

w20: make the parameter use `(s32)a0` in the load: `v1 = *(s32 *)((s32)a0 + 0xCC);` — same.
w21: use a `u8` local for v0? `u8 v0;` — the load of D_80078EB1 is u8; target uses lbu. If v0 were u8, the compare `v0 < a1` would promote... different insns.
w22: use `s16 v0` — different.
w23: `v1 = ((Unkstruct_80184B70 *)a0)->unkCC; v0 = 1;` order — covered.

Let me also try a *two-variable* split of v1 per arm with a merge via the store duplicated... no.

w20: `if (!(v0 < a1)) { if (v0 < a2) { v1 = load; v0 = 1; } else { v0 = 2; v1 = load; } } else { v0 = 2; v1 = load; }` — covered by sweep (s013?).

Let me try w20 (s32 cast) and w21 (u8 v0) and w22 (swap the two compares: `if (v0 < a2)` outer?). Then write the results.

Actually w22 is interesting: swap the nesting order — outer test `v0 < a2`, inner `v0 < a1`. The target's asm order is: slt a1 (v0<a1) first, bnez, then slt v0 (v0<a2). So the source must have the a1 test first. Swapping would change the asm. Skip.

w20 and w21.
