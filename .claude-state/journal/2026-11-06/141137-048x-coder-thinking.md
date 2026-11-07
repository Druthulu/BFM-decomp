---
ts: 2026-11-06T21:11:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0OsrV7VIoYzD3fChv1LU
---
Not the same pattern. Let me look at the "Family of 10" comment and maybe the shared header `func_8017F0D0`? The TU includes headers at top. Let me search for the family in the TU's @stuck comments.

Actually, let me focus: item 2 needs the dead `move v0,s0`. This is the expand-void-return wall. Let me check the wall tag definition: "expand-void-return | expand | void-return expansion drops a value the target keeps live (G24)". Yes.

But before declaring WALL, I must try ≥30 scored tries and ≥20 min. That's a lot of compiles but they're cheap. Let me brainstorm variants and batch them.

Variants to get `move v0,s0` kept in a void function:
1. `return (s32)a0;` — tried, ignored.
2. Make rv volatile → store, no.
3. Use rv as a store value at the end to a *dummy* global? extra store.
4. `if (rv != 0) {}` — branch, no.
5. `while (0) rv = ...;` — dead.
6. Use rv in the argument of a call that's already there? No call at end.
7. Make the last statement a *conditional* store `*a0 = rv ? sp20 : ...`? no.
8. Return type trick: define the function with `void` but use `__attribute__((...))`? no.
9. K&R definition with implicit int return? `func_8017F0D0(a0,a1,a2) s32 *a0; ...` — the TU has `extern void func_8017F0D0(s32*,s32,s32)`; a K&R def with implicit int would conflict (int vs void). Error.
10. What if the function returns void but we use a *different* local that aliases the return reg? No.

Hmm, what about `*a0 = rv;` where rv is used and then `rv = (s32)a0;` and then `func_8012B77C(...)`? no.

Wait, maybe the move v0,s0 isn't dead-value; maybe it's the return value of a *call* whose result is used as the store? Let me re-read: at 3294 `jal func_8012B77C` (a0=sp+32=sp20). The call returns v0. Then 3298 `sh v0,26(sp)` — the delay slot stores v0 (the call's return) to sp10+0xA! Interesting: the `sh v0,26(sp)` is in the jal delay slot, storing v0. So v0 after the call = the sh value? Then 329c `lw v0,32(sp)` overwrites v0 with sp20.

Actually `sh v0,26(sp)` stores the call's return value (or a previously computed v0). Hmm, the delay slot executes before the call takes effect, so it stores the pre-call v0 (the p[2]+a2[2] sum). Then the call returns into v0.

Then `lw v0,32(sp)` = sp20.

OK so the move v0,s0 is separate.

Let me consider: could the target's `move v0,s0` be `rv = (s32)a0` where rv is used as the *argument* to the call? No, the call is before.

What if we restructure so the call to func_8012B77C comes AFTER the rv assignment? The target order is fixed.

Hmm. Let me look at other void functions in moves.md that MATCHed with a trailing dead move. Search for "move v0" in moves.md.

Actually, let me reconsider: maybe `rv = (s32)a0;` can be kept if `rv` is used by the *next* function? No.

What about making the store `*a0 = rv;` and then using `rv` as the base of a *second* store that flow can't prove dead? Target has no second store.

I think this is a WALL. But the brief says a WALL needs ≥20 min and ≥30 scored tries. Let me spend some time and tries. Let me generate a bunch of candidate variants programmatically and score them in one batch (sc.sh handles multiple files). But each is a separate candidate. Let me write ~15 variants.

Actually, wait. Let me reconsider the problem: perhaps we can avoid the dead move by making the value live through the *store* in a clever way. The target's last ops:
```
lw v0,32(sp)
nop
sw v0,0(s0)
move v0,s0
```
What if the C is:
```
*a0 = sp20;
a0 = a0;   // identity launder - not allowed
```
No.

What if the C's last statement is `return (s32)a0;` but with the function declared with a *cast* to a returning type? Can't change signature.

Hold on — what if we define the function as `void func_8017F0D0(...)` but add a nested block with `return (s32)a0;`? Same.

What if we exploit that GCC 2.7.2 expand_return for void functions might emit the value if the function is declared K&R with no prototype? The TU's extern void decl is a prototype. If we define it before the extern decls? The extern decls are at file scope lines 3603, 3636, and the definition at 3803. Wait, the extern void decls are at 3603/3636 (before 3803). Actually the comment says "The TU declares extern void func_8017F0D0(...) at file scope 3x (:5197 :5285 :5319)" — different line numbers in another file? The grep earlier showed 3454, 3603, 3636. Hmm, three extern decls. And the definition at 3803.

If the definition appears BEFORE the first extern void decl, GCC would still see the conflicting type? The definition's type is established; a later `extern void f(...)` conflicts → error.

What if we use a K&R definition without a return type (implicit int)? Then a later extern void conflicts. Error.

OK. Let me try a different angle: maybe the `move v0,s0` can be produced by making `rv` the *return value* of the void function through a call to a function returning s32 and storing it? No.

Let me look at the exact wall "expand-void-return" cases: func_800D2A24, func_801F0C4C, etc. All WALL. And there are MATCHes where the function returned s32 (signature change allowed in those TUs). Here the signature is locked.

Given the constraint "no signature or decl change outside the body (callers stay as they are)", this is a genuine wall: expand-void-return.

But wait — the PARTIAL option: maybe we can keep the keepalive asm (row kind) and remove only the pin, achieving score 0 → PARTIAL:keepalive. Or keep the pin and remove keepalive → PARTIAL:pin (score 1, not 0). Let me check: w1 (keepalive removed, pin kept) = score 1. So PARTIAL:pin needs score 0 — not achieved. w2 (both removed) = score 1. So no PARTIAL either.

Hmm, so if we can't get score 0 at all, the result is WALL with best = lowest score of a lever-free body. Lever-free = both gone (w2) = 1. So best=1, result WALL, wall=expand-void-return.

But hold on — is the requirement "best = lowest score of a lever-free body"? Yes for WALL. w2 is lever-free (no pin, no keepalive) and scores 1. So best=1.

But before declaring WALL, let me try harder. Maybe there's a real-C way to keep the dead value. Let me think about `flow`'s dead-store elimination: it deletes sets of regs that are dead. A set is kept if the reg is live. In a void function, v0 is not live at exit. BUT if the function has a `return` statement with a value, expand_return sets v0 and marks it as the return value... but for void, expand ignores.

What if the function's return type is void but we use `__builtin_apply`? No.

What about `longjmp`? No.

Hmm, what if the move is not dead but is the *return address* setup? No.

Let me try: maybe the target's `move v0,s0` comes from `rv = (s32)a0;` where rv is used as the *value stored* by a second store that is to the same location as the first, and flow/combine merges them? E.g.:
```
*a0 = sp20;
*a0 = (s32)a0;   // second store, different value
```
No, that would be a different store.

What if `*a0 = rv;` where rv is (s32)a0? Then the store value is a0 (s0), and the target's store value is sp20 (v0). No.

What if the C is `rv = sp20; *a0 = rv; rv = (s32)a0;` and we make the final `rv` used by a store to a *volatile* dummy? extra store.

I'm fairly convinced it's a WALL. But let me try a couple more real-C tricks:

Trick: `return;` after a `switch` where the default sets rv and returns? No.

Trick: Make the function end with a call whose return is stored, e.g., `*a0 = func_8012B77C(...)`? But the target's call result goes to sp10+0xA in the delay slot, not stored to a0.

Trick: `a0 = (s32 *)rv;`? no.

Let me look at the "nop" at 32a0. If we could make the move be the load-delay filler... no, the nop is separate.

Hmm, actually, let me reconsider: what if `move v0,s0` is the delay-slot fill for the preceding `sw`? No, sw has no delay.

Let me try one more idea: use `rv` as the argument to a `printf`-like function? no.

Let me count tries so far: w1, w2, w3 = 3 scored tries. Need 30 for a WALL. Let me generate a systematic batch.

Actually, wait. Let me reconsider the possibility of using `return` in a void function differently. GCC 2.7.2: `expand_return` — for a void function with a value, it calls `expand_null_return` (ignores). But what if the value is a *struct* or the return type is `void` but we return via a `return` in a function declared with an old-style definition? Hmm.

What if we declare the function as returning `s32` inside a *nested scope*? Like define a nested function? GCC supports nested functions. We could define the outer as void and... no.

What if we use an `asm` label to alias? Not allowed.

Another angle: maybe the move v0,s0 can be produced by the *store* `*a0 = rv` if rv is in v0 and the store's base a0 is in s0, and then a *second* use of a0 as a value. The second use could be the return value of the function if the function were s32. Locked.

OK, let me try: what if `func_8012B77C`'s return value is used as the stored value, and rv = a0 is used as the *out* pointer? The call's a0 = sp+32. If instead the C passes `(s32)&rv`... no.

Let me look at the problem from the "what does the target's move accomplish" view: it sets v0 = a0 at function exit. This is the classic "return a0" of a function whose C return type is s32 but whose callers declare void. The src comment confirms the pin+asm is the workaround. Since we can't change the signature, WALL.

Actually, hold on. What about defining the function with an `s32` return type but *without* conflicting with the extern void decls by... the extern decls are in the same TU. Could we make the definition's return type `s32` and the extern decls `void` — GCC 2.7.2 might only *warn* "conflicting types" or *error*? The src comment says HARD cc1 error. Let me verify by testing a variant with s32 return. If it's an error, that's evidence.

Let me test w4: s32 return (no pin/keepalive).

But the brief says no signature change. Testing it is fine for evidence but can't be the win.c.

Let me instead try the remaining real-C ideas and count tries. Actually, let me reconsider the PARTIAL option: maybe removing only the pin (keeping keepalive) gives score 0? Let me test: orig minus pin, keepalive kept. But keepalive is `__asm__("" : : "r"(rv))` where rv is now a plain s32; the asm keeps rv live. The move `rv = (s32)a0` would be kept by the asm, and rv (plain) would be allocated... maybe v0? Without the $2 pin, local-alloc might give rv another reg. Let me test.

If that scores 0, result = PARTIAL:keepalive (pin gone). That's a valid PARTIAL! The brief allows PARTIAL:<kinds still kept>. So even if MATCH is impossible, a PARTIAL:keepalive (score 0, only keepalive remains) is a good outcome. Let me test.

Similarly, maybe removing keepalive but keeping pin gives score 1 (w1) — no.

Let me test orig minus pin.
