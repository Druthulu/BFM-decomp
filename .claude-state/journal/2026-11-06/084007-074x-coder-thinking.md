---
ts: 2026-11-06T15:40:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PisQhJpDio1UUgsMzVqC
---
554 ins, score 13 — still folding (the do-while didn't split the EBB for cse, or the tree merged it).

Hmm. Let me look at the cse dump for the orig to see the exact insns and what the asm does. Actually, maybe the mechanism is different: maybe the launder's second set of n is needed for the *scheduling* (the move a0,s1 lands in the delay slot). The target's `move a0,s1` at 2f00 is the delay slot of the bgez at 2efc. That's `n = t` placed there.

Let me look at the cse dump for a1 (no asm) vs orig, in the region. Let me dump a1's cse and compare.

Actually, the key difference from the diff: mine (a1) at insn 92: `move v0,s1; sll v0,v0,7; ... bgez s6` — cse folded the test to rem (s6). Target recomputes.

Let me think about a real 2nd set of n that emits nothing. What if we use a *different variable* for the second expression that is equal but cse can't prove:

```
n = t;
if (t < 0) t = -t;
rem = d - n * 128;
{
    s32 n2 = n;      // copy
    if ((d - n2 * 128) < 0) rem = -rem;
}
```
cse: `(set n2 n)` → n2 ≡ n (first = n). Then `(mult n2 128)` → canon to `(mult n 128)` → folds to rem. No good.

What if n2 is *not* a copy but an equal-valued expression cse can't relate: e.g. `s32 n2 = (s32)(u16)n;`... changes value.

Hmm.

What about making the SECOND expression different in a way that cse's fold_rtx doesn't see as the same expression but combine later simplifies to the same instruction sequence? E.g. `if ((d - n * 128) < 0)` vs the first `rem = d - n * 128`. What if the test is written as `if (d < n * 128)`? The target's assembly: `sll v0,a0,7; subu v0,v1,v0; bgez v0` — so the target computes the subtraction, i.e. `d - n*128 < 0`. If I write `if (n * 128 > d)`, the codegen might be `slt` etc. Not matching.

What if I write the test as `if ((d - n * 128) < 0)` but with `n * 128` spelled `n * 0x80`? Same.

OK here's another idea: the dead-reset of the *multiply's* operand. The cse table entry is `(mult n 128)` → reg (v0 in the first computation? no, the first computation's sll result is folded into subu). Actually the target's first computation: `sll v0,a0,7; subu s6,v1,v0` — the multiply result is not stored in a reg; it's combined. cse's table would have `(mult n 128)` with value = a reg (the sll dest). Then the test's `(minus d (mult n 128))` → fold_rtx substitutes the sll reg → `(minus d sll_reg)`, then looks up that expression → if the subu's dest (rem) is in the table for `(minus d sll_reg)`, it folds to rem. Yes.

To break: make the first computation's multiply not in the table when the test is processed. cse's table entries are removed when the reg is modified. If between rem and the test we modify the sll dest reg... e.g. a dead-reset on a variable that gets allocated to that temp? Not controllable.

Alternatively, make the first computation use a *different expression form*: `rem = d - n * 128` where the multiply is `(mult n 128)`; if instead we compute `rem = d + (n * -128)` — combine might normalize. The tree folder will normalize `d + n*-128` to `d - n*128`.

What about `rem = -(n * 128) + d;`? folds.

Hmm, what about using a *different temp* for the multiply in the first computation so the table doesn't have `(mult n 128)` as the same? E.g. `s32 q = n * 128; rem = d - q;` — then the table has `(mult n 128) → q` and `(minus d q) → rem`. The test `(minus d (mult n 128))` → fold_rtx substitutes q → `(minus d q)` → folds to rem. Still folds.

Unless the multiply's temp q is *reused* for something else before the test (killing its table entry)? Hmm, cse invalidates q's value if q is redefined, but `(mult n 128)` is still known (it's an expression, not just q). Hmm.

OK, what about making n itself redefined with a value that cse can't track, using a real dead store that flow removes later? E.g.:

```
n = t;
if (t < 0) t = -t;
rem = d - n * 128;
{
    s32 keep = n;
    n = 0;         // kills cse's knowledge of n
    n = keep;      // restore (real 2nd set)
}
if ((d - n * 128) < 0) rem = -rem;
```
At the tree level, `keep` and the assignments: gcc's tree-level copy propagation? gcc 2.7.2 has no tree SSA; it has `store_copyprop`? Actually 2.7.2 has no significant tree optimizations (no SSA). The RTL passes do copy propagation (cse1's canon). In cse1: `(set keep n)` → keep ≡ n. `(set n 0)` → invalidates n. `(set n keep)` → n ≡ keep, and keep ≡ old n? After n=0, keep's value is still the old n; the qty for keep... make_regs_eqv(n, keep). Then `(mult n 128)` → canon to the qty's first reg = keep (or n). If canon picks keep, the expression becomes `(mult keep 128)` — not in the table (the table has `(mult n 128)` where n was the old reg... hmm, but keep and n were in the same qty as the old n? Let's see: initially `(set keep n)` makes keep join n's qty (first = n). Then `(set n 0)` invalidates the qty (removes table entries mentioning n; but keep is in the same qty → all entries invalidated!). Then `(set n keep)`: n joins keep's qty (first = keep? or n?). The old `(mult n 128)` table entry was invalidated. So the test's expression is not foldable → recompute! 

And the codegen: `n = 0; n = keep;` — after cse, these become `(set n keep)` (the `n=0` is dead and deleted by flow). And if n and keep are allocated to the same hard reg, the move is a no-op (may be removed by the assembler/peephole/dbr). Target has no extra move. Risky but worth testing.

Actually, simpler: just `n = 0;` before the test and `n = keep;` — but we can avoid `keep` by re-assigning from t? No, t was negated.

Let me test:
```
{
    s32 keep = n;
    rem = d - n * 128;
    n = 0;
    n = keep;
}
if ((d - n * 128) < 0) rem = -rem;
```

Hmm wait, but the first computation `rem = d - n*128` must come before the reset. Order:
```
n = t;
if (t < 0) t = -t;
{
    s32 keep = n;
    rem = d - n * 128;
    n = 0;
    n = keep;
}
if ((d - n * 128) < 0) ...
```

Let me test this (e1) and a variant where keep is declared at function scope (e2) — declaration order may matter.

Actually, the target's `move a0,s1` at the delay slot suggests n=t copy. Adding keep may add a copy. Let's test.
