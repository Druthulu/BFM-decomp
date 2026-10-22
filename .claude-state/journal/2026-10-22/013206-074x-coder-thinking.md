---
ts: 2026-10-22T07:32:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_dM63lx1OZVItw7zec7c3
---
This is the SAME function as item 4 (func_80190D70) but in a different TU (ov_SC06_033 vs ov_SC06_032)! The body is nearly identical (the same launder on vol).

So item 5 should crack with the same recipe: `vol = vol | 0x3000;` right before the call.

Let me apply it: orig.c = lines 3539-3623; cand01 = the plain drop; cand02 = the recipe.

Let me do it.
