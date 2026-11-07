---
ts: 2026-11-06T12:53:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7ADPRDlr8vzf0uwNLsfU
---
None better than 2. Item 2 is looking like a wall: sched1 places the 0x64808080 constant pair one slot too early (above the y store).

Time check: item 2 started ~05:51, now maybe ~06:05. I've done ~15 scored tries for item 2 (w0, v1-v5, v6/v7 compile errors count? they're tries but not scored, v8-v11, d_*7). Let me count scored tries: w0, v1,v2,v3,v4,v5, v8,v9,v10,v11, d_Y,d_C400,d_C78,d_C64,d_CE,d_C400C78,d_C64CE = 17. Need ≥30 for a WALL. So I should keep trying more candidates.

Let me think of more real-C levers for this ORDER residual:

1. Change the y store's *width*: it's s16. Target sh. Already tried u16 cast (same).
2. Make y's computation produce a different register: e.g., declare y as u16. Then y = D_801C11CE + 1; lhu v0; addiu v0; sh. Same.
3. Move `eight = 8;` etc. — no.
4. Change the loop to `for (j = 0; j < 2; j++)` — same.
5. Reorder the vsum statement: the comment says "the +8 (vsum) store sits before the 0x10/0x12 stores here even though the scheduler sinks it back". So the source order of the vsum block is already tuned.
6. Try moving the C64 store *before* the CE store but also before C400: i.e., change the source order to sh(Y), C64, C400, C78, CE — matching the target order exactly! Then sched might leave it alone. v10 (swap C78 and C64) gave 2; v8 (swap C400 and C78) gave 5. Let me try v_new: source order Y, C64, C400, C78, CE.
7. Try Y, C400, C64, C78, CE.
8. Try Y, C64, C78, C400, CE.

Also, the m24/mhi/`*(u32*)out = ((*(u32*)out) & mhi) | (...)` later.

Let me try the permutations of the 4 stores after Y: C400, C78, C64, CE. There are 24 permutations; too many. But the target's final order is: Y, C64, C400, C78, CE. So let me just try that source order. Also try Y, C64, C400, CE, C78.

Let me also try: move the CE store earlier (target has CE at 150, after C64's sw at 149).

Let me generate the exact target order and a couple of neighbors.
