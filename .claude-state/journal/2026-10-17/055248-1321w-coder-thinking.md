---
ts: 2026-10-17T11:52:48.741Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm working through the priority tiebreak: with both allocnos at 229 it comes down to allocno ordering, but the free-register calculation favors r323 at 230 over r321's 229. Checking the division, I need the live range length to push past 609 or 610 for the ratio to round up to 230 instead of 229, so I'm testing whether bumping both live ranges achieves that threshold.

Alternatively, I could shorten r323's live length by having it born later — if r321's set in the preheader comes before r323's instead, that would reverse which allocno gets the longer live range and thus the winning priority, but that depends on how the loop invariant hoisting orders the two moves in loop.c.

But target output requires the addiu for s8 to come before s7 in emission order, so I can't flip that. I need some other +1 adjustment to live-length counting that doesn't alter final output — maybe checking how flow.c's propagate_block actually increments reg_live_length per insn, since notes might not count toward it.
