---
ts: 2026-11-06T16:27:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5ARuCu2S2jOkFuFQLNNQ
---
Target has `li v0,1` at 0x90 early (before D_800EC9F0=1) and at 0x55c near return. So v0r=1 is set at top too? Actually at 0x90 `li v0,1` then sw v0,0(at) for D_800EC9F0=1 — so v0 is reused as the value 1 for the store. Then at 0x55c `li v0,1` again for the return. So the function does return 1 in v0 (the caller reads it? void function though). The pin $2 keeps v0 as the register for v0r=1.

Lever-free: how to get v0=1? Options:
- Make the function return s32 with `return 1;` — but signature change not allowed.
- Assign a volatile? no.
- The "keepalive" was needed to make the dead assignment stay. Without it flow deletes.

Hmm, but wait: is `v0r = 1` dead? v0r is a local that's never read. flow would delete it. Unless... the assignment `v0r = 1` after `func_80010A98()` — gcc might keep it because it's in v0 (return register) and the function returns void... Actually for a void function, the value in v0 is not used by the caller, but gcc's expand might still emit `li v0,1` if v0r is assigned and v0r is a variable assigned... flow dce removes dead stores to local pseudos. It did, hence keepalive was needed.

So the crack needs a real C construct producing v0=1 without a lever. Ideas:
1. `return;`? No.
2. Make v0r used: e.g., use the value in a call argument at the end? That would change code.
3. Maybe the target actually has the caller use the return value. But decl is `extern void func_800D1E9C(void *arg0);` — changing it to `s32` would be a decl change outside the body. Not allowed by constraints ("no signature or decl change outside the body (callers stay as they are)").

Hmm, but the brief says lever-free body of `func` in win.c (bare definition). "no signature or decl change outside the body" — I think the signature of the function itself is part of the def... "bare definition" means a definition without the levers. Changing return type from void to s32 changes the signature; callers stay as they are (they call it as void). In C, declaring `extern void func(...)` then defining `s32 func(...)` is a conflict in the same TU. So no.

Alternative: keep void but make the last statement a call whose return value... no.

What about making v0r `volatile s32 v0r;`? That's a width/qualifier change in the body, not a lever. A volatile local assignment must be kept! But it changes codegen: `sw v0r, offset(sp)` would appear. Unless v0r is volatile and... no, volatile forces a stack store. That would not match.

Alternative: use a global? no.

Hmm. Maybe there's a different real-C construct: `func_80010A98(); v0r = 1;` — if instead we write the tail as a call that returns int and assign: `i = func_80010A98()`? no, it's void.

What if the value 1 is needed as an argument? The target's last call func_80010A98 takes no args, and `li v0,1` follows.

Maybe the trick: `return` value via a helper? Actually, in GCC 2.7.2 for a void function, `return;` at the end just jumps. The `li v0,1` is the function's result register convention? For functions declared returning int, `return 1;` yields li v0,1. Given the shipped def needed a keepalive, the original source likely did `return 1;` and the decomp uses void + keepalive as a fake.

Can I define the function as `s32 func_800D1E9C(void *arg0)` in win.c? The --try harness compiles a body file. How does delever_search --try work? It probably replaces the function body/definition in the TU and compiles. If I provide a full definition with a different signature, does it accept? The constraint says no signature change. Let me check delever_search.py --help and how --body works. Maybe --body is inserted as the function body text only? Let's check.

Actually, let me check delever_search.py to understand --try/--body.
