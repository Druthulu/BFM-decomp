---
ts: 2026-11-06T21:09:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VwgfvYguItKcUH7iJcSw
---
Exactly: only the dead `move v0,s0` is missing. Everything else matches even with both levers removed (w2 score 1!). So if we can get a real use of `rv = a0` that survives flow and emits no extra insn, we'd hit 0 with no levers at all (a full MATCH, no PARTIAL needed).

How to keep a dead value in a void function with a real C construct that emits zero extra insns?

Options:
- Return type: can't change.
- A real use that costs 0 insns: e.g., `*a0 = rv;` is a real use of rv but stores. 
- Use `rv` in a condition that's known true? `if (rv == a0) return;` → flow may fold (known value) and remove. But maybe it emits a compare? Target has none.

Hmm. The value `rv = (s32)a0` is a0 (the pointer). What if we use it in a way that the compiler proves dead but flow keeps? flow deletes dead sets. To keep the set, the value must be live. 

What if we make `rv` a volatile variable? Then it'd be stored to memory (extra insns). No.

What if the last statement is `*a0 = rv;` where rv = a0? That stores a0's address into *a0 — but target stores sp20. Different.

What if we restructure so the final move is not dead: e.g., make the store use `rv` and then the move is the store's base? Target: `sw v0,0(s0)` where s0=a0. The store base is s0 (a0). If the C is `*(s32 *)rv = ...` with rv = a0... but rv is $2, and the store base would be v0. Target's base is s0.

Hmm.

Let me reconsider: maybe the target's `move v0,s0` is not from `rv = (s32)a0` but from a different construct. What if the function is defined to return something but the TU's extern void... no.

What if we declare a local `s32 ret;` and `return ret;` in a void function? C allows `return;` only; `return expr;` in void function is an error (in C89). But GCC may warn. The constraint is the signature (void) fixed.

Wait — actually, can a void function contain `return (void)expr;`? Hmm.

What if we use the value in a `for` loop's condition that's optimized? No, loops emit code.

What about the `&&`/`||` fold lever: `if (x && rv) ...`? The target has no test.

Hmm, this really looks like the classic expand-void-return wall. But w2 already gets 42/43 with NO levers — only the dead move missing. The wall tag would be `flow-unused-result` or `expand-void-return`. Let me check if there's any way.

Think: `move v0,s0` — v0 = a0. In a void function, this is dead. flow's dead-code elimination removes sets of registers that are never used. To keep it, the register v0 must be considered live at that point. v0 is the return-value register; at function exit it's not live in a void function.

What if we add a real use of v0 after the move that flow can't delete but costs 0 insns? For example, the epilogue doesn't use v0.

What if the last statement is a function call whose return is used? That would emit a call.

What if `rv` is used in a way that's part of an expression whose result is used? E.g., `*a0 = rv = (s32)a0;`? That changes the store.

Wait: target is `sw v0,0(s0)` (store sp20 to *a0) then `move v0,s0`. What if the C is:
```
*a0 = sp20;
rv = (s32)a0;
```
and rv is used by... nothing.

What if we make the store use rv as the base and value? No.

Let me look at the walls for similar functions: expand-void-return appears many times. Is there any MATCH with expand-void-return? moves.md line 297 `keepalive,pin | func_801F0C4C | WALL expand-void-return`. No MATCH. Line 28 `keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)`. That one the function returned s32 (signature change allowed there?).

Hmm. Let me check: maybe this function's TU can define it with a different return type via a cast? The TU declares `extern void func_8017F0D0(s32*,s32,s32)` at file scope. If we define `void func_8017F0D0(...)`, ok. If we define `s32 func_8017F0D0(...)`, conflicting types error. Constraint: no signature change.

But what if we keep the void signature but return a value using a GNU extension? In C, `return expr;` in a void function is an error in GCC 2.7.2? It might be a warning ("return with a value, in function returning void") and still generate the return. Let me test! If GCC 2.7.2 accepts `return (s32)a0;` in a void function with a warning, the value would be placed in v0 and kept live. But the constraint says no signature change — the signature stays void. Adding a return statement is a body change. Is `return expr` in a void function a "lever"? It's real C (with a warning). Hmm, but it changes the function's behavior (callers ignore it). The target does have v0 = a0 at exit, which is consistent with returning a0!

Actually wait: target's final `move v0,s0` sets v0 = a0 at exit. That's exactly what a `return a0;` would produce! And the function returns void per the TU's extern decl, so callers ignore v0. The original matched body used the pin+asm to fake it. But the REAL C could be `return (s32)a0;` in a void function? No — C forbids it; but GCC 2.7.2 might allow with a warning. Let me check the compile: delever_search compiles with -Wall? If it's an error, no.

Actually, the src comment says "(3) The TU declares extern void func_8017F0D0(s32 *, s32, s32); at file scope 3x, so an s32 * return is a HARD cc1 conflicting types error." So the definition must be void. But a `return expr;` inside a void function is a separate diagnostic: "warning: `return' with a value, in function returning void". GCC 2.7.2 might allow it (warning, not error) unless -Werror. Let me test.

If `return (s32)a0;` in a void function compiles, it would set v0=a0 and keep it (expand_return). Let me try.

Actually, careful: `return expr;` in a void function — GCC 2.7.2's expand_return: if the function returns void, it may ignore the value or emit it. Let me just test.

Variant w3: w2 (no levers) with the final two lines replaced by `*a0 = sp20; return (s32)a0;`. But `return (s32)a0;` in a void function. Let me test.

Actually the current body:
```
func_8012B77C(...);
rv = sp20;
*a0 = rv;
rv = (s32)a0;
__asm__(...);
```
Replace with:
```
func_8012B77C(...);
*a0 = sp20;
return (s32)a0;
```
But wait, we also need `rv = sp20; *a0 = rv;` to produce `lw v0,32(sp); nop; sw v0,0(s0)`. With `*a0 = sp20;` directly, it'd be `lw v0,32(sp); sw v0,0(s0)` maybe without nop (load delay). The nop in target is a load-delay slot. The current w1 (rv=sp20; *a0=rv) matched everything including the nop. So keep that form:
```
rv = sp20;
*a0 = rv;
return (s32)a0;
```
But rv is a plain s32 now (w2). And `return (s32)a0` in void.

Hmm, but if the function returns void, `return (s32)a0;` — the value's type is s32, function void. GCC might warn "return with a value". Let me test compile.

Let me also consider: maybe `return;` after assigning? No.

Let me try w3.
