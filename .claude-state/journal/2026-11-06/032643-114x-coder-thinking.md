---
ts: 2026-11-06T10:26:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gGa9cxGHnPMD47S6WfPc
---
All ~110+. Best is nopin at 110. The lever removal costs 9 instructions and a big register shift. This is a WALL.

Let me do a few more meaningful tries (need 30). I have nopin + 28 scored = 29. Let me add a few more to exceed 30, then record.

Actually, the real question: can any lever-free body score better? The pins force specific registers; removing them gives a fundamentally different allocation. 110 is far.

Let me check if maybe keeping the barriers but removing pins is "PARTIAL"? No — PARTIAL means win.c scores 0 keeping only some levers. Neither.

Let me add a few tries and record WALL with best 110 (nopin).

Hmm wait, but the "best = lowest score of a lever-free body" — nopin is 110. But maybe a lever-free body that keeps the two `__asm__("")` barriers (no memory clobber) would be a "PARTIAL:barrier"? The barrier kind is one of the two kinds. If removing only the pins (keeping barriers) scores 0, that's PARTIAL:barrier. Let me test that! Remove only the pins, keep the barriers.

Similarly for other items. Let me test CF3E8 with pins removed but barriers kept.

Actually, the brief says PARTIAL = "win.c scores 0 keeping only those levers". So if a body with barriers kept (pins removed) scores 0, that's PARTIAL:barrier. Worth testing — it's informative and might be the best result.

Let me create nopin_barriers.c: only replace register pins, keep the two `__asm__("")` lines.
