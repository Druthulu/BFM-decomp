---
ts: 2026-11-06T09:59:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7o40reMFKfCU141VshSw
---
Item 4 is quite different: it has `register s32 f __asm__("$3")` and a keepalive inside the loop. The kinds row says keepalive,pin. Here `f` is used in real code (`f = 1; ... f != 1`), and the keepalive adds a reference to i1 to change allocation priority. This is a real "greg-ref-count" style wall (like moves line 16, 51, 60).

So item 4 is a keepalive-ref-count wall probably.

Item 2: let me read func_80180AC4 (already read: pin ret $2 + keepalive; returns 0/1 via ret, void). Same structural problem as item 1.

Hmm, so items 1, 2, 3 all have a `$2` pin on a return-value-ish variable in a void function. Item 4 has a $3 pin on a loop flag + keepalive.

Wait, but item 2: `ret = 0; goto out; ... ret = 1; out: keepalive`. In a void function, `ret` is dead → those assignments deleted. Same issue.

Unless... hmm! Wait. Let me check item 2's target: maybe `ret` is actually used. Let me disassemble.

Actually, let me reconsider — maybe there IS a legitimate route: the target's v0 sets might come from a `return` in a function whose *declaration in the TU is void but whose definition is in this file first*. The conflict error... unless we change the *callers'* declarations. Forbidden.

Hmm, wait, is it? "no signature or decl change outside the body (callers stay as they are)". So no.

OK so items 1,2,3 look like `expand-void-return` walls (moves line 19: `keepalive,pin | func_800D2A24 | WALL expand-void-return — void def (caller TU K&R void decl); target li v0,0/1 on exits; expand drops void return values (W03)`).

That's exactly the tag: `expand-void-return`. And item 2 is precisely "target li v0,0/1 on exits". Item 1: target li v0,-1 etc.

So the expected results might be WALL expand-void-return for items 1,2,3 and something else for item 4.

But hold on — the brief says "singleton crack shard G26x" and asks to write lever-free bodies that score 0. Maybe the shard is about trying. The brief explicitly allows WALL with ≥30 tries.

Hmm, but 30 scored tries per item × 4 items = 120 compiles. That's a lot but feasible (each compile ~35ms + overhead; actually delever_search --try takes maybe a few seconds).

Wait, actually, let me reconsider item 1 once more. Is there really no way? Let me think about `void` functions in GCC 2.7.2 and the `return` statement. The parser: for a void function, `return expr;` → warning and it does `expand_null_return` (discards). Confirmed by test.

What about `return (void)rv;`? Still void.

What about declaring the function with `s32` and *also* making the callers' void declaration not conflict by... the callers are after the definition. If the definition is `s32` and the later `extern void` declaration conflicts — error. What if we define the function *without* a return type and with an old-style definition? Still int, conflicts.

What if the definition is `void` but we place the *body* in a way that GCC treats... no.

So WALL expand-void-return for 1,2,3? Let me verify item 2's target and item 3's target to confirm the tag.

Actually wait. Let me reconsider item 3: `rv = 0` only in the else branch, and the function is void. Target probably does `move v0,zero` in the else. That's the same expand-void-return.

But hold on — item 3 also has `obj` pinned to $2 and `chn` pinned to $3. Those are separate pins. The kinds are keepalive,pin (all pins). The task says "MATCH = the kinds in <dir>/kinds gone" — all pins gone. So we need to remove $2 obj, $3 chn, $2 rv pins and the keepalive.

`obj` = call result. In MIPS, a call result naturally comes in v0. `obj = func_801290DC(...)`. Without a pin, local-alloc/global-alloc might still assign obj to v0 if it's used soon... but obj is used across the whole if-block (obj+0x20, obj+0x1C, obj+0x2C), and there's no call in between? There's no call inside the if. So obj lives across the block; global-alloc might put it in a callee-saved reg (s0) since it's live... but it's born from a call and dies at block end; global-alloc gives it v0 possibly. Let's test.

`chn` = w = param_2, used in 3 stores. Pin $3.

So item 3 might crack with real C (drop pins, maybe reorder), except for the `rv = 0` in the else which needs the void-return problem. Hmm, unless the else branch's `rv = 0` can be expressed as a real return... no.

Wait — actually, is `rv = 0` in the else branch really needed? Let's look at the target. If the target has `move v0,zero` (or `li v0,0`) in the else branch, then yes, it's a return value.

Let me disassemble all four targets. Let me get the baseline objects via --try orig.c --keep for each.

First, let me copy orig.c for all items and baseline them.
