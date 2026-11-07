---
ts: 2026-11-06T05:34:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zaqumKaFcgpz6UfG6pIb
---
h4's remaining diff is almost entirely the a0/a1 register swap (plus one missing insn). The register swap: a0↔a1. This is the same class as the earlier issue — a global-alloc/local-alloc choice.

h4 has 44 ins (one missing). The missing one is at the end (mine[27:28] vs target[25:29]): mine has `sh a0,28` where target has `subu v0,v0,a1; subu a1,a1,v0; sh v0,28` — hmm, mine is missing a `sh v0,28`.

So h4: 1 missing store + register swap.

If I could fix the register swap (a0/a1) and the missing store, it'd be 0. The register swap might be fixable with a declaration-order or dead-reset move.

Hmm, time: 22:34, 16 min. Let me try a couple of variants on h4:
- reorder declarations.
- add a dead-reset.

Actually, the a0/a1 swap: u88 is in a1 instead of a0, u8C in a0 instead of a1. These are local-alloc choices (a0/a1 are caller-saved, used across the calls? no, they die before the calls). The target uses a0 for u88 and a1 for u8C. Mine (h4) uses a1 for u88 and a0 for u8C.

This is a qty priority tie in local-alloc. Moves: declaration order, temp reuse, s16/u8 widths.

Let me try:
j1: h4 with the declarations reordered (u88, u8C, t, t2 → different order).
j2: h4 with u88/u8C as s16 instead of s32.
j3: h4 with the t/t2 declarations moved.

Let me run these quickly. If one cracks it, great; otherwise wall.

Actually, the register swap affects the whole function, and the *value* at position 3 (lhu a1 vs a0) is just the register name. The score 12 counts these.

Let me try j1-j4.
