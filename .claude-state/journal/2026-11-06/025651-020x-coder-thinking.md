---
ts: 2026-11-06T09:56:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9OWGdlTgAjOjRs4yEG47
---
All four are void functions with `register s32 rv __asm__("$2")` + keepalive. The pattern: target computes a return value in v0 but the decomp declares void and uses a pin+keepalive.

So the lever-free solution must make the value live in v0 without asm. Options:

1. Return value (s32 return type) — signature change, conflicts with callers' extern void.
2. Some real C construct where the function is void but the compiler still computes v0 as a byproduct — e.g., if the value is used in a *call argument*? no.
3. What if the "done" block stores to a global that is never read? That'd be a store, not v0.

Hmm, wait. Let's reconsider: in a void function, could the value in v0 arise from a *tail call*? No, target ends with jr ra.

Let me look at the target: `jr ra` at the end. v0 holds the result. So it's a return value. In C, that's `return expr;`.

Now: is changing `void` to `s32` on the definition allowed? The brief: "no signature or decl change outside the body (callers stay as they are)". That forbids changing the signature. So no.

Hmm, so is this item a WALL? But the brief implies these should be crackable with real C moves. Let me re-read: "write a lever-free body of `func` in G26x/<dir>/win.c (bare definition) that scores 0". "Lever-free = none of the row kinds in <dir>/kinds remain". Result can be WALL: "WALL (best = lowest score of a lever-free body)".

But wait — maybe there's a legitimate real-C way: declare the local `rv` and have the function end with `return;`... no.

What about using a `register` variable without asm? `register s32 rv;` — the `register` keyword alone is not a lever (lever_census "D register" maybe counts `register` decls?). Line 1238: `("D", "register"): 2`. Let me check what class D register is.
