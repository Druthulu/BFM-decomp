---
ts: 2026-11-06T11:07:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GiHt1i9BscjcLM57gkEz
---
Item 3 with n=s16 + do-while-after = 4, still missing the delay-slot addiu. So the do-while-after didn't work for item 3, but did for item 4. Why?

Difference: the call spelling (cast vs direct). Let me try item 3 with a direct call (no cast). Declare the extern with the item's panel type.

The orig declares:
```
extern s32 *func_801880E0(s32*, Panel_8017E978_801880E0*, s16);
```
and calls via a cast to `(s32 *(*)(s32 *, Panel_S40_8018B238_80187EA0 *, s16))`.

Let me replace the declaration with `extern s32 *func_801880E0(s32 *, Panel_S40_8018B238_80187EA0 *, s16);` and the calls with `func_801880E0(ot, w, i)` / `func_801880E0(ot, &D_801BC8D0, 3)`.

If the panel types differ in layout, the compile might still work (both are pointers; the call passes the address).

Let me try.
