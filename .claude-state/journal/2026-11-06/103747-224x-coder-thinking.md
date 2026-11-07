---
ts: 2026-11-06T17:37:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0yiUqK58WJVbCeBHAZal
---
Time 12 min. All 7.

Let me try to directly test the coalescing hypothesis: add a copy `sh16 = x` where x is a variable known to be in v0. The only v0 value is the call result. E.g., in the then arm: `sh16 = angle << 16;` no.

What if we restructure so sh16 is assigned from a v0 value in the join block? Hmm.

Time is limited; let me consider the WALL. But I want to be thorough for 20 min. Let me run a few more batches (8 min = ~15 variants).

Variants:
h1: `p[0x79] = angle;` moved after the if (order change) — check.
h2: the else arm's load via `*(s16*)` (sign-extended load) — different insns.
h3: sh16 as s16 — semantics.
h4: `sh16 = angle << 16;` → `sh16 = angle << 0x10;` same.
h5: `sh16 = angle << 16;` → `sh16 = (angle << 16) & 0xFFFFFFFF;` folds.

Let me also try the "no angle variable" version: `p[0x79] = func_80029D3C(cmp79);` then the shift uses `p[0x79]` — the call result isn't kept in a var; the shift would reload p[0x79] (extra load) or CSE the store value. x1 did this partially.

Let me try h1 and a couple.
