---
ts: 2026-11-06T17:05:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EiDUhJemDgxBDsfFIJ2N
---
Item 3: func_801817D0, 215 ins, one pin: `register u32 m24 __asm__("$14")` ($14 = t6).

The comment says: "the 0xFFFFFF mask lands in $t7 and the 0xE100008E constant in $t6 -- the target has them the other way round. Pinning the mask to $14 (cookbook §17) fixes all 20 affected instructions".

So the pin is m24 = $14 = t6. Lever-free we need the mask (0xFFFFFF) in t6 and the 0xE100008E constant in t7.

The list value 134 for this item — maybe the score of a previous nopin attempt.

Let me set up: orig.c lines 6726-6860, score baseline, then nopin.
