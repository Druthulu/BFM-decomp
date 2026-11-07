---
ts: 2026-11-06T06:25:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xazfjFeKtohVZD4VThZN
---
That's loop reversal, not strength reduction. Let me test empirically instead: build w2.c = for loops + only the launder asm restored (pins removed) and see whether hoisting stops.

Actually more efficient: test both variants in one sc.sh call.

Variant A (w2): for loops, pins removed, launder KEPT.
Variant B (w3): for loops, launder removed, pins KEPT (i.e., orig with launder deleted).

orig has both. Let me create:
w2 = orig minus pins (launder kept)
w3 = orig minus launder (pins kept)

Then score both.

Note the pins: `register s32 tmp __asm__("$2")` and `register s32 hh __asm__("$2")`. Note both pinned to the SAME reg $2 — that's legal only if their live ranges don't overlap.

Let me build them.
