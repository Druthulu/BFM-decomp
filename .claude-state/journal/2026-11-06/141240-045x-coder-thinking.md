---
ts: 2026-11-06T21:12:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pLQD4Pc1JG1H0wh0KoMP
---
"If function wants no value, give it none": `expand_expr (retval, NULL_RTX, VOIDmode, 0);` — expand the expression for side effects only. `(s32)a0` has no side effects → nothing emitted. So `return (s32)a0;` in a void fn gives nothing. Confirms the comment.

So we need a real side-effecting expression that computes a0 into v0 as the last instruction without adding a store. What about `return *a0 = rv;`? That's the store (already there) and the value of the assignment is rv, which would be... in v0? Hmm: `return (*a0 = rv);` — the expression's value is rv. expand_expr with NULL target: the assignment expands, storing rv to *a0; the value rv is in a register (possibly the same as the store source, i.e. v0). Hmm, but the value would be rv (the loaded sp20), not a0.

The target's move is a0 → v0. Hmm.

What if the last expression is a comma: `(rv = (s32)a0, *a0 = rv);`? Then the value is the assignment rv, and rv=a0 would be computed... but the order: rv=a0 then *a0=rv stores a0 to *a0. Wrong semantics and different code.

Wait, actually, hold on. Let me re-read the target:

```
20b0: lw v0,32(sp)
20b4: nop
20b8: sw v0,0(s0)
20bc: move v0,s0
20c0: lw ra,44(sp)
...
```
`sw v0,0(s0)` stores the loaded value; `move v0,s0` sets v0=a0.

In the original source, `rv = sp20; *a0 = rv; rv = (s32)a0; asm(rv)`. The `rv = (s32)a0` is the move.

Since the value is dead, we need a side-effecting use. Real C side effects: store, call, volatile access.

What if we store rv=a0 to a *dead* stack slot? That adds an sw. Not match.

What if we pass it to a function? A jal.

Hmm. Is there any C construct where GCC emits `addu v0,s0,zero` and nothing else? A return value of a non-void function is the only natural one, but the decls forbid it.

Wait — do they? The extern decls are `extern void func_80181BF0(s32 *a0, s32 a1, s32 a2);`. If my definition is `void func_80181BF0(...)`, fine. What if the definition's return type is written as something that doesn't conflict? No.

Hmm, what about changing the *declaration* inside the body region? The `--body` splice replaces only the definition text; the file-scope extern decls stay. Conflicting types = error.

Unless the candidate body is a *TU text* (not --body): `--try TU FN FILE` without --body lets me supply the whole TU! Then I could change the extern decls too... but the constraint says no decl change outside the body, and callers stay as they are. Changing `extern void` to `extern s32` for the decls *and* the definition is a signature change outside the body → not allowed. Also the diff would show it.

Hmm. But wait: the moves.md W04 match did exactly this ("s32 fn returned nothing"). Different shard though; the constraint here is explicit: "no signature or decl change outside the body (callers stay as they are)".

Let me think about other real-C options for producing a dead `move v0,s0`:

1. `rv = (s32)a0;` where rv is used by a later *store that is itself dead but not deleted*: e.g., store to a local array element that is later... flow deletes dead stores to locals. Volatile → emits store.

2. Make the last use of a0 be an *address computation* feeding something: e.g., `((s32 (*)(s32))...` no.

3. What about `*a0 = rv;` where the store's base is a0 — the store uses s0. Then `move v0,s0` could come from a *second* store using a0 as the base for a different address that folds to zero offset? No, that'd be an extra sw.

4. What about a computed goto / label address? `&&label` puts a code address in a register (lui/addiu), not s0.

5. What if the last statement is `sp20 = (s32)a0;` — a store to the stack slot. The target's frame has sp20 at 32(sp). A store would be `sw s0,32(sp)` — an extra instruction. But wait — would it be deleted? sp20 is a local whose address is taken (passed to func_8012B77C via &sp20), so stores to it can't be deleted... Actually after the call, the value isn't read; flow could delete the store if the address doesn't escape... it does escape (passed to a function), so the store can't be deleted! That would give `sw s0,32(sp)` — but the target has `move v0,s0`, not a store. Different.

Hmm.

6. What about a `?:` expression with side effects? e.g., `rv = a0 ? (s32)a0 : 0;` — dead.

7. What if we make the value live-out via a *global register variable*? That's a pin.

8. What about `__builtin_return_address`? No.

Hmm. Maybe the answer is that this item is a WALL (best 1) — the pin is load-bearing. But wait: the brief says PARTIAL means win.c scores 0 keeping only some levers. Could we keep the keepalive but drop the pin and score 0? That'd be PARTIAL:keepalive. But our w1 (no levers) scores 1; adding back the keepalive (without the pin) might fix the move while the pin is unnecessary? Let's test: keepalive only:

```c
rv = sp20; *a0 = rv; rv = (s32)a0; __asm__ volatile("" : : "r"(rv));
```
Without the pin, rv is an ordinary variable. Would the `lw v0,32(sp)` still be v0? Our w1 showed the rest matched (only the move missing), so yes.

With the keepalive, the move appears. So PARTIAL:keepalive with score 0. But can we do better — crack it?

Let me think again about the real C. The key: we need a0 in v0 at the end as dead code that survives. What survives dead code? Nothing in a void function... unless the value is used by an asm (forbidden).

Wait, wait. What about `rv` being used in a *non-dead* way that produces the move naturally? Consider:

```
rv = sp20;
*a0 = rv;
a0 = (s32 *)rv;   // no
```

Hmm, what if the last statement is `return;` but the function's return type... 

Let me reconsider: is there any chance the residual `move v0,s0` comes from the *store* `*a0 = rv` being done via a0 itself? Like `*(s32 *)a0 = rv` where the compiler computes `v0 = a0 + 0`? No, the store uses s0 as base.

What about `*a0 = rv, a0` as a comma expression in a statement context → dead.

Hmm, what about making the function return *a0* via a tail call... no.

OK, what about this: the target's move could be the return value of the *store expression* if a0 were the stored value... no.

Let me look at the problem from the other side: is the pin actually needed for the `lw v0`? Our w1 matched everything except the move, so no.

So the remaining lever needed is the keepalive. That means PARTIAL:keepalive (score 0) if we can make win.c score 0 with only the keepalive. Let's verify: take w1 and add `rv = (s32)a0; __asm__ volatile("" : : "r"(rv));`. Score should be 0. That's a PARTIAL:keepalive.

But is PARTIAL acceptable? The brief says result can be PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers). Yes, it's an allowed outcome. But MATCH is better. Let me spend a few tries looking for a real-C crack.

Idea: what if `rv` is declared as a *union* or the last statement is a function call to a function returning... no.

Idea: The last statement could be `*a0 = rv;` and then `a0` is passed to... hmm.

Idea: use a `for` loop or `if` that is always taken but the compiler can't prove: `if (a0 != 0) { }` — comparison dead? The branch would be emitted (extra insn) unless folded.

Idea: `switch ((s32)a0) { }` — a jump table, extra.

Idea: `goto *a0;` — computed goto, extra.

Idea: a statement expression? GCC extension `({ ... })` — same dead-value problem.

Idea: `return;` inside a conditional: no.

Idea: `rv = (s32)a0;` where rv is `register`? A `register` declaration without asm is allowed? The constraint says "no `register` vars" — so no.

Idea: Make rv's value observable via a *pointer to rv* that escapes? e.g., `s32 *prv = &rv; ... *prv = (s32)a0;` → a store.

Hmm.

Idea: use `a0` in the *address* of the store: `*(s32 *)((s32)a0) = rv;` — same.

What if the last store's value is a0, and rv=sp20 is stored earlier... Let's look at the target again:
```
lw v0,32(sp)      ; rv = sp20
sw v0,0(s0)       ; *a0 = rv
move v0,s0        ; rv = a0 (dead)
```
What if the C were `*a0 = rv = sp20;`? Same.

What if the C is `rv = sp20; *a0 = rv;` then the *return value of the assignment expression* `*a0 = rv` is rv... no.

Honestly, I think a dead `move` requires an asm or a non-void return. Let me check the possibility of an s32 definition with the extern decls *inside the TU* — but the --body splice keeps them. Unless the body can include a declaration that overrides? No, C doesn't allow redeclaration with a different type.

Hmm, BUT: what if the definition is written as `void func_80181BF0(...)` and we add a *second* nested definition? No.

What about making the function's return type `void` but the last statement a call to a *local* function that... no.

Let me check whether PARTIAL is really the right call, or whether WALL is. Actually, the distinction: PARTIAL:<kept> = win.c scores 0 keeping only those levers. WALL = best is the lowest score of a lever-free body (1). Since keeping the keepalive gives 0, it's PARTIAL:keepalive.

But maybe I can find a real-C crack with the same mechanism as C0414 (dead-reset cse-breaker) or C0535 (do-while). Hmm, the move is deleted by *flow* (dead code), not cse. The comment says "flow ($2 is dead at the end of a void fn)". So a dead-reset won't help.

Unless... flow's dead-code deletion can be defeated by a label! A `goto` label creates a potential jump target; flow can't delete a set that might be needed at a label reachable... Hmm, but the set would still be dead unless the value is used at the label.

What about `if (0) { ... }`? deleted.

Hmm, what if we make the move *not dead* by using it in a way that folds into nothing? E.g., `if ((s32)a0) { }` at the very end: the branch `bnez s0` would be an extra instruction. No.

What about `rv = (s32)a0; return rv;` in a void function? expand_return with VOID: expand_expr(rv, NULL_RTX, VOIDmode) — rv is a variable read, no side effect → nothing. And expand_null_return. So no move.

What about `return *a0 = (s32)a0;`? The assignment's value is a0; expand_expr with NULL target in VOID mode: expands the assignment (store), and the value... `expand_expr` for MODIFY_EXPR with a NULL target and VOIDmode: it will expand the RHS to a target register? Let me look at expr.c: for MODIFY_EXPR with target NULL and VOIDmode (ignore), it expands the RHS with `NULL_RTX, VOIDmode, 0` (ignore) after computing the address. So the RHS a0 is not loaded into a register (no side effect). Hmm, a0 is a variable read → no code.

Hmm, but what if the RHS has a side effect that forces a register? e.g., `*a0 = (rv = sp20)`? That's the store.

What about `*a0 = (sp20 = (s32)a0)`? That's storing a0 to *a0 — wrong.

OK here's another thought: the target's move could be the value of `rv = sp20` if... no, that's v0=lw.

What if we reorder: `rv = (s32)a0; *a0 = sp20;`? Then: rv=a0 (move v0,s0), then the store of sp20 (lw v1, sw v1). Target order: lw v0, sw v0, move v0,s0. Different order. But is `rv = a0` dead here? Yes, deleted.

So no.

I'll test a couple of cheap candidates, then fall back to PARTIAL:keepalive.

Wait, actually — one more idea: make `rv` a value that is *returned by the function through a tail call*? no.

Another: make the last statement a `while(0);`? empty.

Another: `sp10[0] = (s32)a0;`? A store to sp10 (whose address escapes to func_8012B77C) → `sw s0,16(sp)` extra instruction. But hold on: could that store be *scheduled* into a delay slot and the move... no, it's a store, not a move.

Hmm, what about storing a0 into the *dead* sp20 slot? `sp20 = (s32)a0;` — sp20's address escapes (passed to the call), so flow can't delete the store. Target would gain `sw s0,32(sp)` — an extra instruction vs `move v0,s0`. Not a match (but maybe the diff would be an insert of 1 and a replace). Score won't be 0.

What if the store is to a stack slot that doesn't exist... no.

OK so PARTIAL:keepalive it is, unless... hmm, let me reconsider the "keepalive" kind definition. The kind "keepalive" = "keepalive macro or asm". The win.c must not contain it for MATCH. PARTIAL:keepalive means keeping only the keepalive lever.

Let me first verify the PARTIAL candidate scores 0.

Actually hold on. Let me reconsider one thing: the asm keepalive `__asm__ __volatile__("" : : "r" (rv))` — is there a *non-asm* way to keep a value live that GCC 2.7.2 supports? A `volatile` variable read? `volatile s32 rv;` then `rv = (s32)a0;` → a volatile store to a stack slot (extra sw). But what if rv is volatile and the *value* is used... no.

Hmm, what about a `__builtin_...`? no.

What about taking the address: `s32 *p = &rv;` then `rv = (s32)a0;` — the address is taken but never used; the store to rv (a local whose address escapes via &rv) can't be deleted by flow! Because flow doesn't know the address isn't used? Actually flow does know: if the address is only taken but never used in a way that escapes, GCC's alias analysis in 2.7.2 is weak. Taking the address of a local marks it as "address taken" → stores to it are not deleted (flow's dead store elimination only for non-address-taken). Hmm! But rv is a plain local: `s32 *p = &rv;` — if p is unused, the &rv is dead and deleted, but the "address_taken" flag on rv is set at expand time. Then `rv = (s32)a0` becomes a store to a stack slot: `sw s0, X(sp)` — an extra instruction (store) rather than `move v0,s0`. Not matching.

Unless rv is in a register (register allocation promotes it) — but address-taken locals can't be in registers.

Hmm.

What about `union` tricks? no.

Let me look at the sibling matches in moves.md for this exact pattern: grep "move v0" or "dead" in moves.md? Let me grep for "keepalive" matches with "return v0" — line 28 was a return-type change. Line 288 etc. Let me grep moves.md for "void" + "return".

Actually, let me check whether the *current src* has the function matched already (it does — with pins). The comment says the pin is load-bearing. The expert briefed this item expecting maybe a crack. Let me look at the walls.txt for a tag: "expand-void-return" is the classic wall tag for exactly this! From moves.md: "keepalive | func_800D2A24 | WALL expand-void-return — void def (caller TU K&R void decl); target li v0,0/1 on exits; expand drops void return values (W03)". And several others: "WALL expand-void-return".

So the expected wall tag is `expand-void-return`. Our situation: lever-free best 1 (only the dead move missing). But since we can keep the keepalive for a PARTIAL, the row is PARTIAL:keepalive, wall = `expand-void-return`.

Hmm, but wait: is PARTIAL allowed to keep the keepalive while dropping the pin? Yes.

Let me verify PARTIAL scores 0, then decide. Also try 2-3 real-C cracks quickly.

Actually, one more idea for a real-C crack: `*a0 = rv;` — what if we make the store's *value* be the address a0 itself for the dead slot? no.

What about a *second* store to *a0 that's dead? Stores can't be dead.

What about `rv = (s32)a0; if (rv) ;`? An empty if with a comparison: `bnez s0` extra.

What about `while (rv) break;`? same.

What about `switch (rv) { default: ; }`? A jump table.

What about `return (void)(s32)a0;`? no.

What about the function being `void` but using `return` in a *void* expression context... no.

OK, what about this trick: make the *last* statement a call whose argument is a0 and whose result is discarded — that emits jal with a0=s0. Extra insn.

I'm confident: PARTIAL:keepalive with wall expand-void-return.

Hmm, but hold on. Let me reconsider whether the pin is needed *at all* for the lw. In w1, the code matched except the move, meaning `lw v0,32(sp)` came out naturally. Good.

But wait — actually let me double check: with the keepalive (no pin), does the `lw` stay in v0 and everything else match? The keepalive's asm "r"(rv) constrains rv to a register but not a specific one. The move `rv = (s32)a0` and the asm use. Let's test.

Candidate p1: w1 + `rv = (s32)a0; __asm__ __volatile__("" : : "r" (rv));` at the end.

Let me write and score.
