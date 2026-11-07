---
ts: 2026-11-06T15:32:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fHpYgNRbCQIdVjzyJfJX
---
MATCH for item 3! 

d2:
```c
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            /* lever 3 comment */
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            vol = vol | 0x3000;
            func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
The 2nd set of vol (ori) placed right before the call kills the sched1 birth boost, and the redundant ori folds into the call's expression.

Wait — the 2nd set is `vol = vol | 0x3000;` and the call ORs 0x3000 again — gcc folds them into one ori. And the order of li a0 vs ori now matches the target. 

Let me write win.c = d2 and verify. Then record.

Note: the launder is gone; the pins (a1 $5, and the $4 pin in a scope) remain — not row kinds.

Let me write win.c.
