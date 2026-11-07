---
ts: 2026-11-06T17:12:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_67o4zYUYBRdgPiJhUAew
---
b2 (all constants named at the top) gives 21 — same as nopin. b1 (only c2) gives 23.

Let me check b2's diff: maybe the constants moved but the mask still t7.

Hmm, I'm spending a lot. Time: item 3 started 10:05:34, now 10:12:38 → 7 min. Budget 20-30.

Let me think about what C makes the mask priority higher. Actually — wait. What if we simply make the mask's *refs* higher by using the mask for the 0xFF000000 part too? The target's other and is with 0xFF000000 (a different constant). Hmm.

Another angle: the target's mask is in t6 because with the pin the constant is computed "straight into the hard reg". Lever-free, maybe the original source had the mask as a *pointer dereference*: e.g., `m24 = 0xFFFFFF;` is fine.

Let me look at what register the mask gets in a *different context*: maybe the issue is that t6 is taken by the 0x8E constant. What if we prevent the constants from being hoisted by sched1? sched1 hoists single-set constants (birthing boost) to fill slots. If a constant were used twice (2 uses), it might not hoist. But the constants are used once.

What if we write the stores with the constant expressed as a *variable assigned in a different block*? There's only one block.

Hmm, what about making the constants' stores use the mask-affected value... no.

Let me try: reorder the packet blocks so that the 0x8E constant is materialized LAST among the six (i.e., move the p2 block to the end). Then sched1's hoisting order changes: the constants materialize in source order; the 0x8E would be last (after the mask?). The mask's def is at insn 571 in the RTL (after all packet stores). Sched1 hoists it to 16. The constants are hoisted to 5-15. If the 0x8E constant's materialization moves to after the mask's birth... it might take a different reg.

But reordering the packet blocks changes the instruction order → likely won't match the target (the target has the packets in order p0..p5).

What if we reorder only the *constant assignment* lines? The stores `*qN = ...` are inside each packet block.

Alternatively: the diff shows the 0x8E constant is the one that took t6. What if we change the *spelling* of the 0x8E constant so it's not a single movsi but two insns? It's already two (lui+ori).

Hmm, what if the constant is written as `0xE100008E` but with a cast: `(u32)0xE100008E`? Same.

OK, let me try the *opposite*: give the mask a copy preference to t6. Local-alloc's `qty_phys_copy_sugg` comes from copy insns with a hard reg. If we assign the mask via a copy from a hard reg... e.g., `register u32 m24` is forbidden (register var). But a copy from a variable known in t6? no.

What about `m24 = 0xFFFFFF & 0xFFFFFFFF;`? folds.

Let me try: `m24 = 0xFFFFFF; m24 = m24 & 0xFFFFFF;` — the second assignment creates a use of m24 (a 13th ref!) and the and with a constant... gcc folds `m24 & 0xFFFFFF` (since m24 already has that value? no value-range knowledge) → it would emit an extra `and` instruction. Not good.

Hmm.

Let me look at the actual target/mine around insn 76 to understand the constant's use: `sw t6,0(v0)` vs target `sw t7,0(v0)`. The store of the constant. The constant's live range in lreg: let me find pseudo 117's birth/death in the lreg dump: "used 10 times across 12 insns" — hmm, that line was for a different pseudo maybe.

Let me directly extract from the lreg dump the insns involving reg 117 (the constant) and reg 87 (mask) with their insn numbers.
