---
ts: 2026-11-06T07:33:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mGDR7D3OfV8MS0JpiA8P
---
func_800CAF84 is defined at line 88 as K&R `void func_800CAF84(arg0) void *arg0; {`. It takes one argument. Other functions call it with arg0/s0/ent. Our function (line 269) calls it with no args via a local `extern void func_800CAF84(void);` declaration at line 253 — that's the FAKE part of the lever setup? The local decl with (void) lets the call omit the arg. The original probably called `func_800CAF84(arg0)` (or s0). Since the target jal has no move before it, the argument must already be in a0 — meaning arg0 is passed, not s0 (s0 is in $16). 

So the fix: remove the local extern `(void)` declaration (or change it), and call `func_800CAF84(arg0)`. Then arg0 stays live in a0 across the copies → a0 reserved → copy temps take a1-a3! And the call passes arg0 in a0 with no move. This should score 0!

But wait: if we remove the local extern decl, the function at line 88 is defined earlier in the same TU, so it's visible with its K&R prototype `void func_800CAF84(arg0) void *arg0;`. Calling `func_800CAF84(arg0)` works. But the brief says don't change decls outside the body; the local extern decl is inside the body, so removing/changing it is allowed. Actually, is removing the local extern a "decl change outside the body"? No, it's inside the body.

Let me test: base with `func_800CAF84(arg0)` and the extern changed to `extern void func_800CAF84(void *);` or removed.

Also note the local `extern s32 func_80146A6C(...)` stays.

Let me try variant v30: change extern to `extern void func_800CAF84(void *);` and call with arg0. Or just remove the local extern (since the definition is earlier in the file, it's in scope). Careful: the function is defined at line 88 before our function, so it's visible. Removing the local decl is cleanest and most natural.

Let's test both.
