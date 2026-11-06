---
ts: 2026-10-22T21:37:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_z0M0Hz0yjLKAweXyUjcj
---
Excellent! With `u8 byteval`, the two moves are both born early (7 and 8) but in swapped order: mine `move a0,v0` (testval=$4) then `move v1,v0` (byteval=$3); target: `move v1,v0` then `move a0,v0`.

So just the order of the two copies. Since source order is byteval then testval, sched1 scheduled them in reverse (a birth-order/priority thing: the one with the longer remaining path first?). testval feeds the beqz (a branch soon) → higher priority → scheduled first.

To get byteval's copy first, I can:
- swap the source order (testval first, byteval second) → then sched1 might put byteval first? Test: swap.c was based on e1 (u32), score 3. Let me make swap+u8.
- Or give byteval an earlier use.

Let me test swap+u8 and also "testval = src" moved after the `param_2 = param_2 << 4;`.

Actually careful: swapping source order in u8 might yield exactly the target. Let me generate a few order variants on the u8 base.
