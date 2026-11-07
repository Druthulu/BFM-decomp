---
ts: 2026-11-06T11:07:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9hXVYWgQfiNqWTUK2V2H
---
x_dwafter.c: score 0! MATCH!

`x_dwafter.c` = the if-body call followed by `do { } while (0);` — i.e., the `__asm__("")` fence replaced by an empty do-while AFTER the call:

```
if (D_80115158[i].h != 0) {
    ot = func_8018B478(ot, w, i);
    do { } while (0);  // !FAKE: do-while
}
```

That's a real-C replacement (a do-while with an empty body) for the asm fence — brilliant: the do-while's LOOP notes make reorg's forward scan stop, so the delay slot is filled from the target.

Score 0 = MATCH! And it's lever-free: the kinds are barrier,pin; we removed the pin (n as s16 instead of zr), the barrier (asm) replaced by a do-while, and the memory barrier replaced by the struct alias.

Wait — but I need to verify the win.c has NO levers: 
- `extern u16 aD800B9A02 __asm__("D_800B9A02")` — an asm-label alias (symbol name). The worked example says it's allowed ("not a codegen lever; was in orig body"). But the constraint says "no pin (register-asm/`__asm__` reg steer)". The asm-label alias is not a register steer. The worked example explicitly kept it. OK.
- The struct alias `extern struct { s32 v; } aD801151D0 __asm__("D_801151D0")` — also an asm-label alias for a symbol name. Same class. OK.
- `do { } while (0);  // !FAKE: do-while` — allowed with the !FAKE tag.

So x_dwafter is a MATCH for item 4!

Now, does the same move work for item 3 (func_80187EA0)? Item 3's x_dwafter scored 5, not 0. Hmm! Different because item 3's call is a cast expression and/or the other differences.

Let me retry item 3 with the do-while AFTER the call... I did: x_dwafter for item 3 = 5. Let me check its diff — maybe it needs a different placement (after vs before). For item 3, x_dwbody (before) = 5, x_dwcall (around) = 5, x_dwafter (after) = 5.

Hmm, so item 3 didn't crack. But maybe another variant will. Let me apply the same idea more carefully to item 3: the difference between items 3 and 4 is:
- Item 4 calls func_8018B478(ot, w, i) directly (declared extern s32 *func_8018B478(s32 *ot, Panel *w0, s16 idx);).
- Item 3 calls through a cast: ((s32 *(*)(s32 *, Panel *, s16))func_801880E0)(ot, w, i).

Maybe the cast spelling matters. Let me try item 3 with the direct call (declaring func_801880E0 with the right prototype). In the orig, func_801880E0 is declared `extern s32 *func_801880E0(s32*, Panel_8017E978_801880E0*, s16);` and then called via a cast to a different Panel type. The cast is because the Panel type differs (Panel_8017E978_801880E0 vs Panel_S40_8018B238_80187EA0).

For item 4, func_8018B478 is declared with the matching type.

Hmm, so for item 3 the cast is needed for type compatibility. But maybe I can declare func_801880E0 with the item's Panel type... that's a declaration change outside the body? The extern is INSIDE the body (block-scope), so it's part of the body. I can change it.

Let me try item 3: declare `extern s32 *func_801880E0(s32 *, Panel_S40_8018B238_80187EA0 *, s16);` and call directly (no cast). Then apply the do-while-after move.

But wait, the type Panel_8017E978_801880E0 vs Panel_S40_8018B238_80187EA0 — are they the same layout? Probably different struct names for the same layout. The cast in the original suggests they differ. Let me check whether the direct call compiles and matches.

Actually, the call's codegen depends on the argument types: `w` is `Panel_S40_8018B238_80187EA0 *`, and the function expects `Panel_8017E978_801880E0 *`. Passing w directly would be a type mismatch (gcc 2.7.2 warns but compiles with a cast needed). The emitted code should be the same (both pointers).

Let me try: replace the cast call with a direct call and add the extern declaration with the item's panel type.

Actually, simpler: try the same do-while-after on item 3 but check the diff to see what's still wrong.

Let me diff item 3's x_dwafter.
