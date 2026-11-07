---
ts: 2026-11-06T21:11:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TcjP1FniKpNpnogiqZRN
---
The comment says: an s32 return is a HARD cc1 error (extern void decls). And "a cast-return" was tried and rejected (identical DIFF). And the pin is load-bearing twice: (a) keeps `rv = sp20` in v0 (lw v0), (b) stops sched2 hoisting the return copy into the load-delay slot.

But my lever-free w1 scored 1 — only the missing `move v0,s0`. So the pin is NOT needed for the rest in the current codegen? Wait, my w1 gave 42 ins vs 43 target, with everything else matching. The comment says unpinned => `lw v1 / move v0,s0 / sw v1,0($v0)` — but my w1 produced (apparently) `lw v0,32(sp); sw v0,0(s0)` matching, minus the move. Interesting — the difference is the pinned `rv` temp; in my w1 I declared `s32 rv;` and `rv = sp20; *a0 = rv;`.

So the only residual is the final `move v0,s0`. The question: how to produce it in real C without a keepalive?

Options:
- A real use of a0 after the store that puts a0 into v0. E.g., `*a0 = rv; something(a0)` — a call would clobber... no.
- Return via `return;`? void.
- Hmm: `rv = (s32)a0; *a0 = rv;`? That would store a0 into *a0 — wrong semantics.
- What about making the last store use a0? No.

The target has `move v0,s0` right after `sw v0,0(s0)`. That is: after storing the loaded sp20 into *a0, v0 = a0. In real C terms, this could be the function's return value (if it returned a0) or... a *second* store? No.

Since the extern void decls make an s32 definition a compile error, and the comment says the cast-return was tried and rejected (identical DIFF — meaning no change), the only lever is the asm keepalive... which is forbidden.

Hmm, but wait: the comment says "a cast-return" tried and rejected. Maybe they tried `return (s32)a0;` in a void function? That would be a warning/error.

Is there any other real C that leaves a0 in v0 at the end? What about a statement like `a0 = (s32 *)rv;`? No.

Think about what the target's `move v0,s0` is: `addu $v0,$s0,$zero`. It's dead code. To generate dead code in real C without asm... impossible in general — GCC deletes dead code. Unless the value is "used" in a way that's not deleted: e.g., stored to a volatile variable? That would add a store instruction (extra insn). Or passed to a function that... a call would add a jal.

Hmm, what if we make the last statement a `return` in a function whose decl is void? `return (s32)a0;` → GCC warns "return with a value, in function returning void" but still generates the move? Actually in GCC 2.7.2, `return expr;` in a void function: it may emit the expression evaluation and then the return. Let me test: would it emit `move v0,s0`? Since the return is void, expand_null_return... Actually the RTL for `return expr` in void function: the expr is expanded (a0 copy to v0?) then return. Hmm. Let me just test.

The comment says "a cast-return — all identical DIFF" — but maybe they tried a different form.

Let me think about the exact sequence: `rv = sp20; *a0 = rv;` then `move v0,s0`. If the C is:
```
rv = sp20;
*a0 = rv;
return;   // void
```
no.

What about `*(s32 *)&sp20 = ...`? no.

Another idea: the last statement could be a *conditional* that's provably... no.

Wait — maybe we can make the value of a0 be needed in v0 via the *call* to func_8012B77C: its return type is s32 (extern s32 func_8012B77C). The call's return value in v0 is unused. If we used the call's return value in a way that... no, that's before the store.

Hmm, but the target's move is AFTER the store, at the very end.

What real C statement produces `move v0,s0` at the end of a void function? A `return` of a value in a void function. Let me test whether cc1 accepts `return (s32)a0;` with a void def and emits the move. In C, GCC 2.7.2 gives a warning but compiles. delever_search may treat warnings as fine (the TU already has 10 diagnostics).

Let me try. If the def stays `void func_80181BF0(...)` and the body ends with `return (s32)a0;`, the return statement's expression is expanded into v0 then the function returns. That would give `move v0,s0` (or addu). But would flow delete it? The return value in a void function is not used, so flow might delete the set... Actually `return expr` in a void function: expand_return may ignore the value? Let me check GCC 2.7.2's behaviour. In stmt.c `expand_return`: if the function's return type is void, `expand_null_return()` is used regardless? Let me check.

Alternatively `return;` in a void fn is expand_null_return.

Hmm, let me look at the actual C: maybe there's a trick where the last statement is a store to a *volatile*? Adding a volatile store adds an instruction.

Let me consider: maybe the residual move can be produced by making `*a0 = rv` where a0 is also the *source*? No.

What about `rv = (s32)a0;` where rv is a variable that is then... unused. Deleted.

OK here's another thought: what if the function is declared void but we use a `return` with a value in a *branch*? no.

Let me just try a few candidates and score:
- c1: end with `return (s32)a0;` in the void def.
- c2: `if (a0) return (s32)a0;`? no.
- c3: use `a0` in the store expression: `*(s32 *)a0 = rv, (s32)a0;`? A comma expression's value unused → deleted.

Hmm, what about assigning to a0 itself: `a0 = (s32 *)a0;` → move s0,s0, deleted.

What about a statement that makes a0 live in v0 across a call? No.

Alternatively: exploit the return-value register of the *preceding call*. The call `func_8012B77C` returns s32 in v0. Target: after the call, `lw v0,32(sp)` overwrites it. So no.

Let me reconsider the problem statement: "MATCH = the kinds in <dir>/kinds gone". Kinds = keepalive,pin. PARTIAL:<kept> means win.c scores 0 keeping only those levers. So if we can't crack it, we can report WALL (best = lowest score of a lever-free body) or PARTIAL if we keep some levers and score 0.

Since the lever-free body scores 1 (best 1), it's a WALL unless we crack it.

But wait — maybe there's a real-C trick: the `move v0,s0` could come from the *address* computation for a store that's optimized... Hmm.

Let me look at how similar cases were cracked in moves.md. Line 28: "keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)". So there, the function's return type was changed to s32 and it worked (no conflicting extern decl presumably). Here the extern decls block that.

But hold on — the extern void decls are at file scope *inside the TU*, in other functions (lines 3694, 3843, 3876 are inside other function bodies? "The TU declares extern void func_80181BF0(...) at file scope 3x (:5197 :5285 :5319)" — the line numbers in the comment differ from the current file (3694 etc.), so the file moved. Anyway.

What if the body declares a *local* prototype? No, the def's return type must match the file-scope extern void decls, else cc1 errors (conflicting types). Since `--try --body` splices only the definition, those extern decls remain.

Unless... we can make the *definition* look like a different function name? No.

OK, let me test the `return (s32)a0;` idea empirically — maybe the comment's "cast-return" refers to something else. But the comment explicitly says "a cast-return — all identical DIFF" (i.e., no change) and "an s32 * return is a HARD cc1 conflicting types error".

So: the only way is a real use of a0 in v0 at the end. What statement is guaranteed to produce `addu v0,s0,zero`?

Idea: `rv = (s32)a0;` then use rv in a way that survives but emits no extra instruction. E.g., store rv to a location that... adds a store.

Hmm, what about a `switch` or a conditional using a0 that folds? E.g., `if (a0) { }` → the comparison is dead → deleted.

What about the last statement `*a0 = rv;` followed by `((Unkstruct_800B5CB8 *)a1)->unkE0 = ...`? no.

Wait — maybe the target's move comes from the *return value of a different expression*: `addu $v0,$s0,$zero` = `v0 = s0 + 0`. In C, `a0 + 0`? Hmm, `rv = (s32)a0 + 0;`? Deleted as dead.

What if rv is a *volatile* s32? `volatile s32 rv;` then `rv = (s32)a0;` → a volatile store, but rv is a local, so it'd go to the stack (extra sw). No.

What if the assignment target is a global? Then a store instruction.

Hmm, so it seems genuinely impossible without a keepalive... unless the return trick works.

Wait, actually: what about making the function *implicitly* return a value by declaring the local `rv` as a register variable that's... no, that's a pin.

Hmm, let me reconsider: maybe there's another real-C structure that changes the *flow* so the move isn't deleted. The move is `rv = (s32)a0` — dead. flow deletes dead sets. Unless... the value is live-out? In a void function, nothing is live-out. 

Unless the function is not void! What if the *definition* stays `void` but we add a nested function or use a label... no.

Hold on — what about `return (s32)a0;` where the compiler treats the expression's value as the return value and the return is NOT null? Let's check GCC 2.7.2 stmt.c expand_return:

```c
void expand_return (retval_rhs) ...
```
and in expand_stmt for RETURN_STMT: if (retval_rhs) expand_return(...) else expand_null_return(). And expand_return starts:
```c
  /* Attempt to optimize the computation of a return value ... */
  ...
  if (TREE_CODE (retval_rhs) != ... )
```
Hmm, but the caller (expand_stmt) might check the function's return type. Let me look at the source in tools/reference/gcc-2.7.2/stmt.c for RETURN_STMT handling.

Let me grep.
