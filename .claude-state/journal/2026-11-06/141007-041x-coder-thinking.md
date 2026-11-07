---
ts: 2026-11-06T21:10:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Wi757JUezucw8wy4nqET
---
Item 2: kinds keepalive,pin. The pin: `register s32 rv __asm__("$2")`. The keepalive: `rv = (s32)a0; __asm__ volatile("" : : "r"(rv))`.

Target: at the end, `move v0,s0` (rv = a0), then epilogue. So rv must be in v0 and live at the end. The keepalive fakes a use so the `move v0,s0` isn't deleted (it's dead code otherwise). And `rv = sp20; *a0 = rv;` — rv = v0 (the load from sp20 goes into v0), then store.

So the target: `lw v0,32(sp); sw v0,0(s0); move v0,s0`. Two things in v0: the sp20 load, and the final move.

The keepalive forces the last value (a0) into v0 and keeps it live to the end. Lever-free, `rv = (s32)a0;` would be dead code and deleted.

How to make `move v0,s0` appear without a keepalive/asm? The return value! The function is declared `void func_80181BF0(...)`. If the function returned s32, `return (s32)a0;` would put a0 in v0. But the brief says "no signature or decl change outside the body (callers stay as they are)". The function def signature is part of the body? The brief says "write a lever-free body of func in win.c (bare definition)" and "no signature or decl change outside the body (callers stay as they are)". Changing the return type would be a signature change — likely not allowed. Hmm. But the moves.md has matches like "keepalive replaced by return v0; (s32 fn returned nothing...)" — line 28: "keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)". So changing the *definition's* return type to s32 and returning a0 was used as a MATCH. But is that allowed? That would change the signature... The caller declares it extern void? The brief says "no signature or decl change outside the body (callers stay as they are)". Hmm, "outside the body" — the function's signature is the definition header. In W04 they replaced keepalive with return v0.

But careful: this is a *candidate body* passed to delever_search --try --body, which splices the body. The TU's decls for the function (extern decl at the top) might conflict. The `--body` splices my text in place of the def, so the return type comes from my text. Callers are unchanged. If callers call it as `void`, changing to `s32` is ABI-compatible-ish.

Hmm, but the constraint says "no signature or decl change outside the body (callers stay as they are)". I read this as: don't edit callers or decls elsewhere; the body's own definition header may change if needed? Risky. Let's see if there's another way.

Alternative: make the `move v0,s0` arise from real C. What real C computes a0 into v0 at the end? The function is void. If we make the last statement something that returns a value in v0... e.g., a call? No.

Actually, what about `*a0 = rv` where rv = sp20: the store uses v0. Then `move v0,s0` — that's the keepalive's `rv = (s32)a0`.

Since the def is void, GCC drops the value. Hmm.

Wait, maybe there's a subtlety: `sp20` is read and stored; then the function returns. If the function returned s32, the return value would be... the source's last assignment was rv = a0. If we write `return (s32)a0;` in an s32 function, we get move v0,s0. But that changes the signature.

Let me check the src: the function is declared in the TU as `void func_80181BF0(s32 *a0, s32 a1, s32 a2)` and callers? It's a jr (jal target) function. Let me check how it's declared in the TU and whether there's a sibling declaration.

Also, note the moves.md line 288 etc. use real C. Let me look at what `func_80184D28` did: "keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)". So they changed the definition to return s32. That was accepted as MATCH in W04. But the current brief's constraint says no signature change. Hmm, "no signature or decl change outside the body (callers stay as they are)". Changing `void` to `s32` is a signature change of the def... but it's *in* the body text (the bare definition). The parenthetical "callers stay as they are" suggests the concern is ABI/callers. A void→s32 change doesn't affect callers.

Hmm, risky. Let me look at what the actual function looks like in src and whether the pin is the only issue. Let me first score the lever-free baseline (drop both pin and keepalive) to see the residual.

Also the pin `rv __asm__("$2")` affects `rv = sp20` (the load) → target has lw v0,32(sp). Without the pin, the load might go elsewhere. Let's test.
