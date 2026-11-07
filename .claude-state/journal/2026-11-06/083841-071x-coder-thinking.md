---
ts: 2026-11-06T15:38:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XENBpMt8O1RLhB8vsPJN
---
Target:
```
2f08: sll v0,a0,7      <- n*128 (n in a0)
2f0c: subu s6,v1,v0    <- rem = d - n*128
2f10: sll v0,a0,7      <- recompute n*128
2f14: subu v0,v1,v0
2f18: bgez v0, 2f24    <- test
2f1c: nop
2f20: negu s6,s6
```
So yes, two separate computations. The launder makes n opaque so the second expression is recomputed.

The `move a0,s1` at 2f00 is n=t (in the delay slot of the bgez).

So I need a real 2nd set of n that emits nothing. Options that emit nothing: a dead store to n that flow removes *after* cse. E.g. `n = n;`? At the tree level, `n = n` is eliminated before RTL. Hmm. What about `n = n | 0;`? folded at tree level.

What about a 2nd set of n through a dead store that survives to RTL: e.g.
```
s32 n2;
n = t;
rem = d - n * 128;
n2 = n;      // dead copy
n = n2;      // 
```
Tree-level copy propagation removes these.

Hmm, what about the pattern used in item 1: a dead-reset of a *related* variable that breaks cse's knowledge without changing codegen. Here the cse knowledge is: `rem = d - n*128`. The second expression `d - n*128` is folded to rem by fold_rtx (cse's constant folding using the table). To break it, invalidate either `rem` or the expression's operands.

What if we insert `d = d;`? no. `n = 0;` then restore? `n = t; ... n = 0; if (d - n*128 < 0)` — n would be 0. No.

What if the second expression uses a *different* but equal variable: since `n = t` (before t is negated? no: n = t; if (t<0) t=-t; so t != n in general).

Hmm wait: after `if (t < 0) t = -t;`, t = |n|. Then `rem = d - n*128`. The test `(d - n*128) < 0`. 

What if we rewrite the test to use `t`? `d - n*128` where n could be negative... `(d - n*128) < 0`. If n >= 0, n == t, so `d - t*128` works. But if n < 0, t = -n, so d - t*128 = d + n*128 ≠ d - n*128. So not equivalent.

What about `rem = d - n * 128; if ((d - n * 128) < 0)` — could I make the second expression's *multiplication* opaque by using `n * 128` vs `n << 7`? combine would unify.

What about making the second expression use an addition: `(d + -(n * 128)) < 0`? combine folds.

OK, what about the dead-reset on rem: after computing rem, `rem` is used at 2f0c (subu s6). The test uses the expression. If I insert a *dead* set of `rem`... no, rem is live.

What about computing `rem` in a way that cse doesn't record as the expression's value: e.g. `rem = d; rem -= n * 128;` — two statements. cse: `(set rem d)` then `(set rem (minus rem (mult n 128)))`. The final value of rem is `d - n*128`, and cse's fold_rtx can still fold the test expression to rem's value (the table entry for rem is the expression). Hmm, cse's fold_rtx looks up the expression in the hash table; if `(minus d (mult n 128))` is a known expression with value rem, it folds. With the two-step form, the expression `(plus d (minus (mult n 128)))`... the RTL would be `(set rem (plus rem (minus (mult n 128))))` using the old rem. Then the test `d - n*128` is a *different* RTL expression `(minus d (mult n 128))` — not in the table! So cse wouldn't fold it!

Wait, but the target's first computation `subu s6,v1,v0` is a single subu — the two-step form would still compile to `subu s6,v1,v0` (reg-alloc). And the test would recompute. That's promising!

But careful: `rem = d; rem -= n * 128;` — the tree/RTL might still fold to a single set at the tree level (the front end emits `rem = d - n*128` as one set). GCC's tree-level optimizations in 2.7.2 are minimal; the RTL expansion of `rem = d; rem -= n*128;` would be two sets: `(set rem d)` then `(set rem (minus rem (mult n 128)))`. Then cse sees the second set's src as `(minus rem (mult n 128))`. Later the test `(d - n*128)` = `(minus d (mult n 128))`. cse's fold_rtx would try to simplify: the operands d and n*128 are in the table; the whole expression `(minus d (mult n 128))` — was it ever inserted? The set `(set rem (minus rem (mult n128)))` inserts the expression `(minus rem (mult n128))`, not `(minus d ...)`. So the test's expression is new → not folded. 

But combine might fold the two rem sets back into one before/after cse? combine runs after cse1. cse2 might then fold. Hmm, but the test insn was already emitted... cse2 could still fold the test to rem if it sees `rem = d - n*128` after combine merges. Risky, but let's test.

Variant: `rem = d; rem -= n * 128;`

Another idea in the same vein: `rem = d - n * 128;` written as `rem = d - (n << 7);`? The front end produces the same RTL as mult.

Let me test the two-step variant and also `n = t; rem = d; rem -= n*128;`.

Also another approach: make the test's expression use `rem`'s *old* form... no.

Let me also try: `s32 q = n * 128; rem = d - q;` and test `(d - n * 128)` — cse has q = n*128 in the table; fold_rtx substitutes q into `(minus d (mult n 128))` → `(minus d q)`; is `(minus d q)` in the table? Not as an expression (rem's src was `(minus d q)` if written that way). If rem = d - q, then yes it'd fold. Skip.

Test the two-step.
