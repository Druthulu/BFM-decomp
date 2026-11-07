---
ts: 2026-11-06T12:02:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i0ameNJdTSvhS0yHBbMU
---
Item 3: WALL best 46, 32 tries.

Wall tag: `cse-const-addr` (cse substitutes the constant D_800AE620 address into each load, 16 extra insns; the launder is what kept it base-relative in a register).

Hmm, wait. Let me reconsider the best: 46 comes from a body missing 16 insns (78 vs 94) — that's the *opposite* of the lever-free v0 (110 vs 94). Both are far. The lowest score is 46.

Hmm, is 46 legitimate? The body compiles and is semantically correct C (struct initializer). Yes.

Let me record: WALL, best 46, tries 32, wall cse-const-addr, evidence "launder keeps D_800AE620 base-relative in $5/$7; without it cse folds the const address into each load (8x lui/addiu, 110 vs 94); struct-copy bodies 46-61".

Now write results row, moves.md, notes.md. Then item 4.

Time: item 3 took ~35 min. Items 4 remaining. Let me move faster.
