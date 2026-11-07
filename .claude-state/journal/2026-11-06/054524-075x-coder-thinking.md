---
ts: 2026-11-06T12:45:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_X9SnqDip954z0qlcKvNZ
---
Item 3 is a header with kinds keepalive,launder (the kinds file says keepalive,launder, but the body ALSO has pins: `register s32 *dp __asm__("$4")`, `register u16 *ba __asm__("$5")`, `register u16 *dst __asm__("$4")`). Per the expert's message: "every row kind not in <kept> is gone from win.c... a win.c that keeps all row kinds is a WALL". The row kinds are keepalive,launder. Pins are NOT in the row kinds — but the constraint says "levers of other kinds the def already had (pins under other causes) may stay, never added". So pins may stay for a MATCH! Only keepalive and launder asm must go.

Interesting: the levers to remove are:
- `__asm__ ("" : : "r"(c36), "r"(dcount));` keepalive
- `__asm__ ("" : "=r"(decoy) : "r"(ba));` launder out-only
- `__asm__ ("" : : "r"(decoy));` keepalive

And the pins stay.

This is a big function. The header must score 0 on all includers (120?).

Let me check the background job first.

Also item 4: func_80177EA4.h, keepalive,launder, 62.

Let me check the background output now.
