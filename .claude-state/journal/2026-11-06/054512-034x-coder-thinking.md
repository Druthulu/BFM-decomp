---
ts: 2026-11-06T12:45:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tScDMws6Wwvf77QxjqXS
---
combo.c (b1+b3+b4 cracked, b2 kept) = score 3. Need to crack b2 for MATCH.

combo without b2 = 29. Hmm, higher than the isolated b2 removal (28) — because interactions.

The b2 issue is a pure a0/v1 register swap on the ua/ub block. Let me examine the exact diff for combo_nb2 to understand.

Ideas: the barrier at b2 sits between `prim[7] |= (attr & 0x40) >> 6;` and `ua = ub = ...`. Its removal lets sched1/alloc move things. Maybe the fix is to make the ua/ub expression depend on the prim store, or to reorder.

Since target has `move a0,v1` and mine `move v1,a0`, and both use the same value... it's about which pseudo gets a0.

Let me check the diff for combo_nb2 in detail (top 40 lines).
