---
ts: 2026-10-22T16:26:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Og692uEWYET6F3Hh5vzG
---
q14's C is `if (p == it)`: RTL NE(72,73) where p=72, it=73 — so NE(p,it). After jump: EQ(72,73) = (p,it) — no swap. After cse: EQ(72,73) — no swap! So cse did NOT swap q14's comparison. But for q9/r1, cse DID swap.

q9/r1: pre-cse EQ(72,73) where for r1 it=72, p=73 → (it,p); cse swapped to (73,72) = (p,it).
q14: pre-cse EQ(72,73) where p=72, it=73 → (p,it); cse did NOT swap.

So cse's swap depends on the operands' *values*: it swaps to put... In q9/r1 the operands are (it=REG_EQUAL symbol B, p=REG_EQUAL symbol A+K). In q14 they are (p, it) — same values, different order. cse swapped in one case but not the other? That's contradictory unless cse's swap is triggered by a *specific* REG_EQUAL.

Wait, in q9 (p=72, it=73): EQ(72,73) = (p,it) → cse swapped to (73,72) = (it,p)? Let me recheck: earlier for q9 I printed cse2 showing `(eq (72) (73))`. And .rtl for q9 showed NE(73,72) = (it,p). The .jump for q9? I didn't print. For r1 I printed .jump = EQ(72,73) = (it,p) and .cse = EQ(73,72) = (p,it) → swapped. For q14 .jump = EQ(72,73) = (p,it) and .cse = (72,73) = no swap.

So cse swaps when the operands are (it, p) but not when (p, it)? Both are the same pair. Hmm, that suggests cse's swap is *canonical*: it puts the operand with the lower pseudo number... no: r1 swapped (72,73)→(73,72), moving the higher first. q14 kept (72,73). So not by number.

Maybe cse swaps based on the *REG_EQUAL expressions*: it canonicalizes so that the operand whose REG_EQUAL is a *symbol_ref* comes first (it) and the one whose REG_EQUAL is a *plus* comes second (p)? In r1, (it=72 symbol, p=73 plus) → cse wants (it, p) = (72,73) — but it SWAPPED to (73,72) = (p,it)! Contradiction.

Hmm wait, maybe I mislabeled which reg is which in r1's .cse. r1's RTL: insn 9 sets reg 72 = symbol A (it); insn 23 sets reg 73 = plus(72,K) (p); insn 26 sets reg 72 = symbol B (it). So at the compare, it=72, p=73. .jump EQ(72,73) = (it,p). .cse EQ(73,72) = (p,it). So cse swapped to (p,it).

q14: insn 9 sets p? No — q14 is built from q9: `s32 p; s32 it;` with `if (p == it)`. So p=72, it=73. .rtl NE(72,73) = (p,it); .jump EQ(72,73) = (p,it); .cse EQ(72,73) = (p,it) — no swap.

So cse's output is (p,it) in BOTH cases! I.e., cse canonicalizes to (p, it) — p first. And the target has (it, p). So cse's canonicalization puts p first; to match the target, we'd need cse's input to be such that its output is (it,p) — impossible if cse always outputs (p,it).

Unless the target's C made cse's canonicalization land differently. Hmm, what is cse's rule? Maybe it swaps when the *first* operand's REG_EQUAL is a `plus` (more complex) to put the simpler (symbol) first? In r1: (it symbol, p plus) → swap to (p plus, it symbol)? That puts the complex first, not simpler. Hmm.

Let me look at cse.c's fold_rtx comparison handling in GCC 2.7.2. The source may be in tools/bin/gcc-2.7.2-psx? Let me check if the gcc source tree is available. Probably not (only the binary). 

Alternative: maybe cse doesn't swap; rather, the *jump* pass in q14 differs. In q14, .jump is already (p,it) and cse leaves it. In r1, .jump is (it,p) and cse swaps. So cse swaps only when... the *first* operand is the one that was set most recently? In r1, it(72) is set by insn 26 right before the compare (and p(73) by insn 23). cse's fold_rtx may swap so that the operand set *earlier* (p) is first? In q14, p(72) is set earlier and is already first → no swap. In r1, it(72) set later is first → swap to put p(73) first. So cse canonicalizes to (older-set, newer-set) = (p, it). That's consistent!

So cse always produces (p, it) regardless of source order. The target has (it, p). Therefore the target's C must have made cse NOT swap: e.g., if the *second* operand (it) had no REG_EQUAL (so cse couldn't reorder)? Or if p's REG_EQUAL were absent?

In cse.c's fold_rtx, the reordering likely comes from `fold_rtx` calling `simplify_comparison`-like logic on `(eq x y)` where both have REG_EQUAL constants: it substitutes both, getting `(eq (plus symA K) (symbol symB))`, then... maybe it canonicalizes the comparison so that the *more complex* expression is on the right? That would give (it, p) = (symbol, plus) — the target! But our result is (p, it) = (plus, symbol) — the opposite. Hmm.

Wait, maybe cse's REG_EQUAL substitution for `it` (the second set, symbol B) is not used because `it` was set twice (reg 72 set at insn 9 and 26) — cse's equivalence for it is symbol B (the last set). For p, REG_EQUAL plus(symA,K). Substituting both into the EQ gives (eq (plus symA K) (symbol symB)) if the order is (p,it) → cse may then swap to put the symbol first: (eq symB (plus symA K)) = (it, p) = target! But we observe (p,it). So maybe cse's swap is the *other* direction: it puts the more complex first.

Ugh, circular. Let me get the actual cse2 RTL with the substituted expressions. The cse2 dump shows `(eq (reg 72) (reg 73))` — the registers, not substituted. So the RTL keeps regs; the swap is in the register order.

OK, empirical approach: find a C shape where the final .s gives beq v1,a0. Try:
- Make p's value NOT a REG_EQUAL (so cse doesn't touch the compare): e.g. compute p with a real 2nd set. But p is a single set.
- Make it's value not a REG_EQUAL: e.g. `it = (s32)D_801202A0;` — cse gives REG_EQUAL symbol. If instead `it` were loaded from memory... no.
- Compare with an intermediate variable that has no REG_EQUAL: `s32 q = it; if (q == p)` — q's REG_EQUAL is it's value; cse propagates.
- Use `if (it == p)` where the *comparison is not the first use* of these values: e.g., add a use of it before the compare (the lhu is in body, after). 

What if the comparison uses `it` *after* modifying it (it += 0x10C)? Not the same CFG.

Hmm, what about restructuring so the compare is `if (it == p)` where p is *not* in a register but a constant? If p's REG_EQUAL (plus symA K) were used, cse would fold... no.

Alternative: change the compare to a *subtraction* form `if (it - p == 0)`. Then the RTL is `(eq (minus it p) 0)` → branch_zero on the subtraction result. That adds a sub instruction unless optimized. q16 gave 1 (same beq? maybe combine folded it back).

What about `if ((s32)(it - p) == 0)`? same.

Maybe use `if (it == p)` but with `p` computed as `p = it + 0x658C` where `it` is the *same pseudo* as the test's it? No.

Let me try a different angle: make cse's swap land on (it,p) by making the *first* operand's REG_EQUAL the "later" one. The rule seems to be "put the operand set earlier first". If I make `it` (the compare operand) set *before* p, then cse puts it first! In q9, the order of sets: it=A (entry), p=it+K (test), it=B (test), compare. At the compare, the operands are the *current* values: p (set at test, earlier) and it (set at test, later). So p is set before it → cse puts p first.

If instead the C were: `it = B; p = it + K;` — but p must be from A. What if we compute p from a *different* variable holding A: `s32 a = it;` at entry, then in test: `it = B; p = a + K; if (it == p)`. Then the sets at test: it=B (first), p=a+K (second) → cse would put it first → (it,p) = target! And `a` = A is live from entry to test, so the entry materializes `it = A; a = it;`? Hmm, that would add a copy. Unless we assign `a = (s32)D_80120194;` at entry and `it` is... but the target's entry materializes `it = &A` in v1 and p from it. 

Wait, let's think: the target's entry: it = A (v1); then the delay slot computes p = it + K (a0). So p is computed at entry (in the delay slot of the j to test), and it=B at test. Then the compare: it (set at test) and p (set at entry, *before* it) → cse would put p first (a0) → beq a0,v1. But the target has beq v1,a0 = (it,p)! Contradiction with my "earlier-set first" rule.

Hmm, so the rule isn't that. Let me re-examine: maybe cse's swap has to do with the *delay slot*/scheduling, not cse. The .cse dump shows the swap, but maybe cse's `fold_rtx` swapped because of the REG_EQUAL values: p's REG_EQUAL is (plus symA K), it's is symbol B. cse might order so that the operand with the *larger* value... 

Let me try to find cse.c's logic. Is the gcc source in the repo? `tools/bin/gcc-2.7.2-psx/` contains cc1 (binary). Maybe there's a source tarball. Let me check quickly: ls tools/bin/gcc-2.7.2-psx. Probably only binaries. Skip.

Empirical: the target's final order is (it,p) with it in v1 and p in a0. In our build, cse produces (p,it) in both q9 and q14. So the target's C must produce an RTL where cse's swap yields (it,p). Since cse swaps (it,p)→(p,it) in r1, the target's pre-cse must have been (p,it) and cse... no, q14's pre-cse (p,it) stayed (p,it). So cse is not swapping to a canonical order; it swaps *only in r1/q9*.

Difference between r1 and q14: in r1 the C is `it == p`, in q14 `p == it`. The pre-cse order differs: r1 (it,p), q14 (p,it). cse swapped r1's but not q14's. So cse canonicalizes to (p,it) — the operand whose REG_EQUAL is the *plus* first? In both cases p is the plus. r1 pre-cse (it,p) → swapped to (p,it). q14 pre-cse (p,it) → kept. So yes: **cse canonicalizes to (plus-operand, symbol-operand)**, i.e., p first.

The target has (it,p) = (symbol, plus). So the target's C must have prevented cse from canonicalizing: e.g., if p had NO REG_EQUAL. Then cse couldn't compare/order them, and the order would stay as the pre-cse (it,p). How to make p have no REG_EQUAL? p = it + K always gets REG_EQUAL (plus ...). Unless p is set in a way that cse can't annotate: e.g., p assigned from a memory load, or p is a *parameter*, or p's set is in a different block with a join...

Alternatively, make the *compare operand* not be p itself but a copy: `s32 q = p; if (it == q)`. Then q's REG_EQUAL is p's... cse propagates REG_EQUAL through copies (REG_EQUAL of q = plus). Hmm.

Or compare `it` with a *reloaded* p? no.

What if we make the comparison `if (it == p)` where p is computed as `p = it + K` and *also* p is used in a way that invalidates its REG_EQUAL before the compare? E.g., a store through a pointer that might alias p? p is a local, no aliasing.

Hmm, what if p is declared `volatile`? Then p is in memory (extra insns).

What if the compare uses `it` and `p` but the RTL order is forced by writing the *branch* as `if (it == p)` with a different CFG layout so that the invert happens in the other direction (no swap)? The swap is in cse1's fold_rtx regardless of CFG.

Maybe: make p's REG_EQUAL not a "plus" by making the addend a *non-constant*: e.g. `s32 k = 0x658C; p = it + k;` — k's REG_EQUAL is const 0x658C; cse folds k into the plus → plus(it, 0x658C) → same. The prior gen_bound_var scored 4 (old structure).

What if p = it + K where the addition is `addu` with a *register* k that cse can't fold because k is set from a memory read? Adds a load.

Hmm, this is a deep rabbit hole for one instruction. Time check: it's ~10:35? Let me check. I've been on this item ~30 min. The score-1 candidate is close, but MATCH needs 0 on all 141 includers.

Let me consider the *other* direction: maybe the target's `beq v1,a0` comes from the C `if (p == it)` with the registers it=v1, p=a0 — i.e., cse canonicalized to (p,it) = (a0,v1) = beq a0,v1... no, the target is beq v1,a0.

Wait, maybe I have the target's register mapping wrong. The diff says mine[8] beq a0,v1 vs target beq v1,a0, and "register pairs a0->v1 x1, v1->a0 x1". If the rest of the code matches, then both have p and it in the same registers. Which is which? Let me dump the target fully to see: target insn 3 `addiu a0,v1,25996` → p=a0, it=v1. So the target's beq v1,a0 = beq it,p. Yes.

So target = (it,p). We need cse to keep (it,p). cse canonicalizes to (p,it) when both have REG_EQUALs (it=symbol, p=plus).

Idea: make the compare operands' REG_EQUALs both *symbols* (not plus) — e.g., if p were also a plain symbol? p = it + K is a plus. Unless K=0 (not).

Idea: make p's REG_EQUAL absent by assigning p in a way that cse can't annotate: e.g., `p = (s32)((u8 *)it + 0x658C);` → still plus. 

What about assigning p via `p = it; p += 0x658C;`? Then p's last set is `p = p + K` with REG_EQUAL plus(p_old, K) where p_old has REG_EQUAL symbol → cse folds to plus(symbol,K) → same.

What about making p's set a *real* second set (p set twice)? E.g. `p = 0; p = it + K;` — the first set is dead and removed.

What if p is computed in the *entry* block (as in the target's delay slot) and `it` is set at test? Then at the compare, p is set before it. Does cse still canonicalize to (p,it)? q9 has p set at test (before it=B). Hmm, the target has p set at entry. Let me test a variant where p is computed in the entry block but *after* the goto — impossible in C. But q9's `test: p = it + K; it = B;` puts p in the test block; the scheduler moved it to the delay slot. The target's C might have p computed *before* the goto in the entry block:
```
it = A;
p = it + K;
goto test;
```
That's the *base* candidate (score 4) where cse folded p into a constant and deleted it=A. So no.

Hmm, but what if we keep `it = A` live by having it used *in the test block* before it=B... 

OK here's another thought: what if the first `it` is live because the `copy` block returns `it` and the compiler's flow can't prove that the entry path doesn't reach copy? In q9, the CFG is entry→test; copy is a separate block. The it pseudo at copy is the test value.

What if we restructure so `copy` is the *fallthrough* of entry? E.g.:
```
it = A;
p = it + K;
copy:
    return it;
```
No — the entry must goto test.

Alright. Given time constraints (the developer asked to finish this item and wrap up), and that score 1 is not 0, I need to decide: WALL with best 1? The wall requires ≥20 min and ≥30 scored tries. I've spent ~35 min on this item and scored ~55 tries (40 existing + 15 new). That's satisfied. Best lever-free = 1 (q9/q14/r1 etc.).

But wait — before walling, let me try the "p has no REG_EQUAL" idea properly: compare `it` against a *variable that is p but reloaded*? 

Actually, here's a clean idea: make the comparison use `p` *via a copy that cse can't fold*: `s32 q; q = p; if (it == q)`. q's REG_EQUAL = plus... cse propagates. Unless q is set before p? No.

Another: use a *function-like* comparison on the addresses: `if ((u32)it == (u32)p)` — same regs.

Another: use `if (it == p) goto zero;` but make `p` a *pointer* (u8 *) and `it` an s32 cast — the RTL is the same (both SImode regs) and REG_EQUALs the same.

Hmm, what if p's REG_EQUAL is *not* a plus because the addition is done in a different mode, e.g. `p = (s32)((long)it + 0x658C);` — DImode add then truncate; cse might not fold into a plus REG_EQUAL... but that changes the codegen (extra insns) unless optimized.

What about `p = it + 0x658C;` where `it` is `u8 *` and p is `u8 *` — same.

What if the addend is applied via an array index: `p = (s32)&it[0x658C];` where it is `u8 *` — same plus.

I think the wall is cse-const-addr (the cse pass's REG_EQUAL substitution/reordering of a constant address). Actually the wall tag "cse-const-addr" fits: "cse folds or substitutes a constant/absolute address the target keeps base-relative". Here cse substitutes the constant-address pseudos into the comparison and reorders the operands. Hmm, the mechanism is slightly different: the *operand order* in the beq. Is there a better tag? walls.txt has no "cse-compare-order". I'd use cse-const-addr (cse substitutes the constant/absolute address pseudos into the compare) — the target keeps the base-relative register pair order.

But wait — maybe the *real* fix is to prevent cse from touching the compare by making the compare use values that aren't REG_EQUAL constants. The target's `it` at the compare is set from `D_801202A0` (a symbol → REG_EQUAL). p is a plus. Both are constants. In the target's compile, cse didn't swap. So the target's C must have had *something* different — maybe the target's `it` is NOT a constant at the compare: e.g., `it` was loaded from memory or incremented. Hmm, but the target's test block does `la v1,D_801202A0` (it = symbol). So it IS a symbol at the compare.

Unless cse's swap depends on the *number of sets* of `it`: in our C, `it` has 2 sets (A and B) → cse's equivalence tracking for a multi-set reg... In the target, same.

Hmm, let me test one more idea: reverse the roles of the variables so that the *symbol* operand is p and the *plus* operand is it. I.e., rename: let the variable compared second be the plus one. The compare is `if (it == p)`; if cse canonicalizes to (plus-operand, symbol-operand), it would put the plus first. In our case p is plus → (p,it). To get (it,p), make `it` the plus operand and `p` the symbol: i.e., the test's variable `it` = p_plus? But `it` is set to a symbol at test. The other operand p is a plus. So cse puts the plus (p) first. The target has the symbol (it) first. So in the target's compile, cse did NOT canonicalize by REG_EQUAL complexity.

Maybe cse's swap is actually by *value magnitude* or by the *REG_EQUAL of the second operand*: it swapped (it,p)→(p,it) in r1 but not (p,it) in q14. Both have the same values. So the swap is direction-dependent: cse swaps only if the second operand's REG_EQUAL is... In r1, second = p (plus). In q14, second = it (symbol). So cse swaps when the second operand is the plus. I.e., it canonicalizes to (plus, symbol). That's a consistent rule: put the "more expensive"/plus operand first.

If that's cse's rule, the target's (it,p) = (symbol, plus) can't be produced by any C where both have those REG_EQUALs. So the target's C must have p WITHOUT a plus REG_EQUAL, OR it WITHOUT a symbol REG_EQUAL.

How to give p no REG_EQUAL while still p = it + K in a register? If p's set is `(set p (plus ...))`, cse annotates REG_EQUAL unless the set has a REG_EQUAL already or is in a context... Actually cse records REG_EQUAL for any set of a register to a constant expression. `plus(symbol, const)` is a constant expression → REG_EQUAL. Hmm.

Unless p is set from a *register* whose value cse can't resolve: e.g., `s32 k; k = 0x658C; p = it + k;` → cse folds k to const → plus(symbol,K). Same.

Unless the addition is `plus` of two registers that cse can't fold: `p = it + k` where k is a *volatile* read or from a function param. No.

What if p is set by a *call*? no.

So the target's C must have `it` without a symbol REG_EQUAL at the compare. But the target materializes `la v1,D_801202A0` right before — a constant symbol. Its REG_EQUAL is the symbol. Hmm.

UNLESS the target's comparison is not between `it` and `p` but between `it` and a *different expression* that cse couldn't equate... The target: `beq v1,a0` where v1 = the register just set by `la v1,D_801202A0` and a0 = p. So it IS it vs p.

So in the target's build, cse did not swap. Maybe because the target's C had the compare in a *different basic block* (test) than p's computation (entry), so cse's REG_EQUAL for p was in a different block and cse's local (per-block) equivalence didn't have p's REG_EQUAL available? cse works per basic block; p is set in the entry block, it in the test block. If p's REG_EQUAL is recorded in the entry block and the compare is in the test block, cse's `reg_eqv_table` might not carry p's REG_EQUAL across blocks (cse2 does global?). In q9, p is computed *in the test block*, so both REG_EQUALs are local → cse swaps. In the target, p is computed in the *entry* block (before the goto), so at the compare (test block) cse doesn't know p's REG_EQUAL → no swap → order stays (it,p)!

But in the base candidate (p computed in entry), cse folded `it=A; p=it+K` into a constant and deleted it=A — score 4. The target's entry computes `it=A` (v1) and `p=it+K` (a0) in the delay slot. So the target's C has p in the entry block but it=A is *live* (not folded).

How did the target keep it=A live? Because the launder asm. Lever-free, we need it=A live. Hmm, but q9 (p in the test block) keeps it=A live across the goto (since p uses it there) and gets score 1. The only residual is the cse swap.

So: can we keep p's computation in the *entry* block (before the goto) AND keep it=A live? In C:
```
it = A;
p = it + K;
goto test;
```
The compiler folds it=A into p (constant) because it's dead after p. To keep it live, `it` must be used after the goto before being reassigned — impossible.

BUT: what if we *delay the reassignment* of it to B so that the entry's it is live into the test block? The target reassigns it=B at test. What if we use a *second variable* for B: `s32 j; ... test: j = B; if (j == p)`. Then the compare is (j,p) — cse would canonicalize (p,j) → beq a0,v1 (wrong registers? j would get v1 maybe). Hmm, but the target's compare uses v1 which was it=A's register. If j is a different variable, it might get a different register and the code would differ (extra? no, it=A dies at entry, j gets v1).

Wait, actually this could work: 
```
s32 it, j, p;
it = A;
p = it + K;
goto test;
copy:
    return j;      // ??? 
test:
    j = B;
    if (j == p) goto zero;
body:
    if (*(u16*)j == 0) goto copy;
    j += 0x10C;
    if (j != p) goto body;
zero:
    return 0;
```
But the target's `copy: return it` returns the *current* value (j). If we rename, the code is semantically identical, and the register allocation would put j in v1 (since it=A dies at entry, v1 is free) and p in a0. The entry: it=A (v1); p=it+K (a0); goto test (delay slot addiu). Then test: j=B → la v1; compare (j,p). Since p's REG_EQUAL was recorded in the *entry* block and the compare is in the test block, cse might not swap → (j,p) = (v1,a0) = target! And `it` at entry is live (used by p) so no fold → the entry computes it=A in v1. 

This is promising! But is renaming a variable a "real C move"? Yes — variable naming/declaration is real C (C0505 catalog mentions decl order/scope; a different variable for the loop iterator is legitimate). The body must remain semantically identical.

However, the target's `copy: return it` — with the rename, copy returns j. The decompiled C uses one variable; but the *target's* C could have used two variables. The compiled result is what matters.

Wait, but there's a subtlety: `it = A; p = it + K;` — if `it` is never used after, the compiler still folds `it + K` to a constant (since it = A is a constant) and deletes `it = A`. The liveness of it doesn't matter: `p = it + K` is constant-folded by cse regardless (fold_rtx substitutes the REG_EQUAL). That's the base candidate's behavior: `la a0, A+K` with no it materialization. So renaming alone doesn't stop the fold of `it + K`!

Hmm right: cse substitutes `it`'s REG_EQUAL (symbol A) into p's plus → constant. The fold happens because both are in the same block and cse propagates. To prevent, `p` must not be computed from `it` in a block where cse knows it's a constant... The target has it=A and p=it+K in the SAME entry block, and cse did NOT fold — because the launder broke the equivalence. Lever-free, cse will fold.

Unless we compute p in the entry block but from a *different* variable that is set to A in the *test* block? No.

What if `p = it + K` is in the entry block and `it`'s assignment is in a *different* block (e.g., a branch)? 
```
if (obj...) — no condition available.
```
There's no condition to create a block.

What if we use the `copy:` label to create a block:
```
it = A;
goto test;
copy:
    ...
```
Hmm.

What if we put `it = A` after the goto? unreachable.

OK so lever-free, `it=A; p=it+K` always folds to a constant la. The target's register-held it=A is purely the launder's effect. That's the wall. 

BUT q9 avoids the fold by computing p *in the test block* (it=A is live across the goto because p uses it there). That gives score 1, with the only residual being cse's operand swap. And cse's swap happens because p's REG_EQUAL is local to the test block.

Can we get p's REG_EQUAL out of the compare's block while keeping it=A live? If p is computed in the *entry* block from it=A, it folds. If p is computed in the test block, cse swaps. What if p is computed in a *third* block between them? E.g.:
```
it = A;
goto mid;
mid:
    p = it + K;
    goto test;
test:
    it = B;
    ...
```
Two gotos. The extra `j` might be optimized away (jump to next). Actually `goto mid; mid: p = ...; goto test;` — the first goto is to the next instruction → removed; then it's the same block as test? The blocks would be merged. Hmm.

What if we use the `copy` label as the intermediate block? The CFG target is: entry→test, test→{zero,body}, body→{copy,body}, copy→exit, zero→exit. There's no mid block.

Could we add a block that the compiler removes but that splits cse's per-block analysis? cse is per-block, and blocks are basic blocks after jump optimization; a redundant label with a goto gets merged.

What about putting `p = it + K;` in the *body* block? No — body is a loop; p must be computed before the compare.

Hmm, what if p is computed in the entry block but with `it` set in the *copy* block? No.

OK, so the residual is a cse per-block REG_EQUAL swap. The wall tag could be "cse-const-addr". Best 1.

Hold on, one more idea: make the comparison's operand order immune to cse by making p *not* have a REG_EQUAL in the compare's block: compute p in the test block but *after* a point where cse loses the equivalence — e.g., after a store that might alias p? p is a local; a store to a *pointer* could alias a local? GCC's alias analysis knows locals aren't aliased by arbitrary pointers? With `-fno-strict-aliasing`, a store through `int *q` could alias p if q might point to p — but q is a local pointing elsewhere; GCC's alias analysis (flow-insensitive, type-based) may consider any int store as aliasing any int local. There are no stores in the test block before the compare though.

What if we add a *harmless* store that cse can't see through, with no net instruction? Impossible.

What about making p a *pointer* (`u8 *p`) and the comparison `if ((u8 *)it == p)`? Same regs.

What about making `it` a pointer and comparing pointers? Same.

I'm convinced: WALL. But hmm, "best = lowest score of a lever-free body" = 1. A WALL row with best 1 is plausible and useful (the next coder knows the residual is one branch operand order).

Wait — actually, maybe I should check whether the *second* comparison (`if (it != p) goto body`) has the same issue in reverse: the diff shows only insn 8 differing, so the second compare matched. The second compare is `ne(it,p)` → beq/bne in source order (it,p) = (v1,a0) → target matches. So only the EQ was swapped by cse.

Hmm, so what if we write the first comparison as a NE with the *other* branch direction, avoiding cse's EQ canonicalization? E.g.:
```
if (it != p) goto body; else goto zero;   // NE, then else
```
The .rtl for the current C is already NE(it,p) goto body + goto zero, and cse converted it to EQ(p,it). What if the C is written so the branch to zero is a *conditional* that cse keeps as NE? E.g., put the zero block *before* body in the source so the layout is:
```
test:
    it = B;
    if (it == p) goto zero;
body: ...
zero: ...
```
That's the current C (zero at the end). GCC expanded to NE→body + jmp zero. Then jump/cse inverted it.

What if the zero block is placed *before* body so that `if (it != p) goto body` is a direct conditional and the fallthrough goes to zero? Source order:
```
test:
    it = B;
    if (it != p) goto body;
    return 0;      // zero fallthrough
body:
    ...
```
r3 was similar but with `goto zero` labels; scored 7 (16 ins) — different CFG. Hmm.

Actually the target's layout: test: it=B; beq it,p,zero; move v0,0; body: ... So the zero block is elsewhere (at the end). The branch is `beq` to zero. GCC's expansion of `if (it == p) goto zero` with zero at the end produces exactly this after optimization. The only issue is the operand order from cse.

What if we write `if (it == p) goto zero;` where zero is *before* test in the source? The layout would differ.

Hmm, what if we force the comparison to be a *bne* to body: `if (it != p) goto body; goto zero;` (explicit). Then the .rtl is NE(it,p) to body (no inversion needed if body follows?) — r3 did `if (it != p) goto body; return 0; body:` giving 16 ins (different). Let me try `if (it != p) goto body; goto zero;` with the zero label after body. The jump to zero would be a j, and the CFG might match. Actually that's exactly what GCC generated internally from `if (it == p) goto zero`. Writing it explicitly shouldn't change the RTL (same CFG).

What if we avoid the inversion by making the conditional branch go directly to zero: `if (it == p) goto zero;` — GCC expands EQ as NE+invert because it prefers the fallthrough. To make it emit EQ directly, the zero block should be the fallthrough: 
```
test:
    it = B;
    if (it != p) goto body;
zero:
    return 0;
body:
    ...
```
Then the conditional is NE(it,p) → body (no inversion) and zero is the fallthrough. But the target's layout has `move v0,zero` after the beq (the delay slot of... hmm, target: beq v1,a0,zero; move v0,0 — the move v0,0 is in the delay slot of the beq (setting up the return value for the fallthrough? no, it's before body). Actually `move v0,zero` in the delay slot of beq to zero: if the branch is taken, v0=0 (return 0); if not, v0=0 then body overwrites. That's a scheduling trick.

If zero were the fallthrough, the code would be: bne it,p,body; move v0,0; ... but the target has beq. So the target's zero block is at the end and the branch is beq to zero, with the fallthrough to body. So the target's expansion was EQ→zero directly (not inverted). Why did GCC emit EQ directly in the target but NE+invert in ours? Because of the block layout: in our C, the `zero:` label is at the end, and `body:` follows `test:` — so the fallthrough after the conditional is body. GCC expands `if (it == p) goto zero` as: emit a conditional branch to zero (EQ) — that would be beq it,p,zero, which is what we want! But our .rtl shows NE(it,p)→body + jmp zero. That's GCC's `do_jump` choosing to branch on the *inverse* to the next label (body) and then jump to zero. Hmm, that's a pessimization, unless the jump pass later inverts it back (it did: the final .s has beq to zero with a delay-slot move). The inversion in jump.c swapped... no, cse swapped.

Actually the final code has beq to zero (EQ) — so jump.c inverted the NE(it,p)→body into EQ(it,p)→zero and then cse swapped the operands to EQ(p,it). So the target's final EQ(it,p) means in the target, after jump's inversion the order was (p,it) and cse swapped it back? No...

Ugh. Let me try one concrete thing: make the jump pass's inversion not swap by ensuring the operands' REG_EQUALs are not both constants in the same block. The cse swap only matters if cse runs after the inversion (it does). 

Given time, let me try a small set of final ideas:
- s1: `if (it == p) goto zero;` but with `p` computed via a *helper variable that is compared*: `s32 q = p; if (it == q) goto zero;` — q's REG_EQUAL propagates (probably).
- s2: compute p in the test block *before* the `it = B` but declare p as `u8 *` and it as `u8 *` (pointer compare) — cse's REG_EQUAL handling for pointers is the same.
- s3: `if ((s32)it == (s32)p)`.
- s4: put `p = it + 0x658C;` in the test block but with `it` copied: `s32 a = it; p = a + K;` — a's REG_EQUAL = symbol; cse folds → plus.
- s5: `if (it == p) goto zero;` with `p` assigned via `p = it + 0x658C; it = it;` no.

Honestly, the cse swap seems robust. Let me do a couple of quick tests (s1, s3, and a version where the compare is written with the operands as `p == it` *and* p computed in the test block — q14 already = 1).

Actually, wait! Let me reconsider q14's trace: q14 (p == it) had .jump EQ(p,it) and cse kept (p,it). q9 (it == p) had .jump EQ(it,p) and cse swapped to (p,it). So cse canonicalizes to (p,it) in both. The target is (it,p). The canonicalization rule might be "put the operand with the REG_EQUAL *plus* first" — p. To defeat it, make p's REG_EQUAL not a plus: what if p is computed as `p = it + 0x658C` where the plus is *not* constant-foldable because it's a `PLUS` of two registers, e.g. `p = it + k` where k is a *parameter*? No params.

What if p is a *global*? no.

What if p is computed via `p = (s32)((u8 *)it + 0x658C);` — same plus.

What if p is computed as `p = it | 0x658C`? That's a different value (no).

Hmm, what if the constant K is applied to `it` in a *different* statement: `it += 0x658C; p = it;`? Then p's REG_EQUAL = it's value = plus(symbol,K) → same. But `it` is then modified — the test reassigns it anyway. Wait! This is interesting: `it += 0x658C; p = it;` — then `it` at the compare is B (reassigned), p = A+K. Same values. The REG_EQUALs: p = it_after = plus(symbol,K). Same.

What about `p = it + K; it -= K;`? p = A+K, it = A (but it's reassigned at test). The `it -= K` is dead? it is reassigned at test → dead, removed.

OK, final answer: WALL cse-const-addr with best 1. Actually, let me reconsider the tag: the mechanism is "cse1 canonicalizes the compare operands to (p,it) because p has a REG_EQUAL plus and it a REG_EQUAL symbol; the target keeps (it,p)". Is that "cse-const-addr"? The walls.txt definition: "cse folds or substitutes a constant/absolute address the target keeps base-relative". Our case: cse substitutes the constant-address pseudos into the compare and reorders. It's a cse constant-address effect. I'll tag `cse-const-addr` with a precise mechanism note. Hmm, but maybe a new tag is better: `cse-compare-order` — `<pass>-<what>`: `cse-compare-order`. The brief says: "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". A new tag is allowed. The mechanism is distinct enough: cse canonicalizes the EQ operand order to (plus-REG_EQUAL, symbol-REG_EQUAL). I'll use `cse-compare-order` since it's precise and new, and the next coder benefits.

But hold on — before walling, let me make one more attempt at the real fix: make the target's *entry* computation work lever-free. The target's entry: `it = A` (v1), `p = it + K` (a0). Lever-free, cse folds p to a constant and deletes it=A. What if `it` is *live* at entry because of the `copy` block? The copy block returns `it`. If we make the copy block return the *entry* it... no.

What if we make `it` live by using it in a *comparison in the entry block* that's part of the CFG? No.

What if we make `it` a *volatile*? extra.

What if we make the entry's `it = A` a *store* to a local that's read later? extra.

OK. WALL.

Now, the row format: `dir file func kinds result best tries wall evidence`.
- dir: func_8012C2D0__func_8012C2D0
- file: src/shared/ov/func_8012C2D0.h
- func: func_8012C2D0
- kinds: launder
- result: WALL
- best: 1
- tries: count my scored attempts. Let me count: existing 39 candidates scored + 13 (batch q) + 5 (q14-q18) + 5 (r) = ~62. I'll say 62. Hmm, "tries" should be the number of scored candidate bodies I evaluated. sc.sh ran on: w1,w2,w3,x1,b1-5,n2,n3 = 10, gen_* = 26 → 36; then q1-13 = 13 → 49; q14-18 = 5 → 54; r1-5 = 5 → 59. Plus dt.sh runs (not new candidates). So 59 scored candidate bodies, of which lever-free new ones ~23. I'll put 59.
- wall: `cse-compare-order`
- evidence: gcc pass + mechanism ≤140 chars: "cse1: (eq it,p) -> (eq p,it) because p's REG_EQUAL is plus(sym,K); target keeps (it,p) -> beq v1,a0 (q9 = 1 ins)" — must be ≤140 chars.

Let me count: "cse1 canonicalises (eq it,p) to (eq p,it) (p REG_EQUAL plus(sym,K)); target keeps (it,p) beq v1,a0 (q9=1)" ~110 chars. Good.

Wait, but the wall requires "≥ 20 min and ≥ 30 scored tries". I have 59 tries and ~40 min. Good.

Now, the win.c requirement: "each MATCH/PARTIAL has its win.c scoring 0". For WALL, no win.c needed. But the brief's DONE WHEN: "each MATCH/PARTIAL has its win.c scoring 0". For WALL, best is the lowest score of a lever-free body. Should I write a win.c anyway? The brief says win.c for MATCH/PARTIAL. For WALL, I'll keep the best body as win.c? Hmm, "best = lowest score of a lever-free body". The item dir has many candidate files. To be safe and useful, I'll write `win.c` = the best lever-free body (q9, score 1) and note it's not a MATCH. Actually the brief says "write a lever-free body of func in G16/<dir>/win.c (bare definition) that scores 0" — that's the goal; for a WALL, best is what we have. I'll write win.c = the score-1 body so the next coder has the best starting point, and notes.md explains.

Hmm, but would a win.c scoring 1 confuse the next stage? The brief's INTERFACES says WALL best = lowest score of a lever-free body. I'll write win.c with the best and say in notes.md it scores 1 (WALL).

Now, before finalizing, I must verify the score-1 body is lever-free (no asm/register/pin/launder). q9 has none. Let me double check: q9 = s32 p; s32 it; no asm. Yes.

Also, does the score-1 candidate score 1 on *every* includer? For a WALL, not required, but the "best" should be representative. Let me run sweep.sh on q9 over all 141 includers? That's ~3.5 min. Since it's the WALL evidence, it's worth confirming the score is uniform (or at least report the first-TU score). The brief says best = lowest score of a lever-free body; the score is measured by dt.sh on the header TU (includer 0). Hmm, for headers the MATCH needs all includers; for WALL the "best" is presumably the dt.sh score. I'll run a quick sweep on a subset (e.g., 8 includers) to see whether 1 is stable, and report the first-TU score. Actually sweep.sh with kmax=141 takes ~141 × 1.2s ≈ 3 min. Let me run it in the background? The rules say commands > few minutes run in the background; this is ~3 min, foreground with raised timeout is OK (max 285s per tool call... risky). Let me run sweep.sh with a subset (e.g., kmax=12) to check stability, and if it's uniform, report best=1.

Actually, the score on other includers could differ (different surrounding code). For a WALL row, the "best" is a single number from dt.sh. I'll do a 10-includer sweep for the evidence.

Time: let me check the clock. Also, the developer wants me to wrap up. Let me:
1. Write win.c = q9 body.
2. Run a quick sweep (kmax=10) on q9.
3. Append results.tsv row, moves.md line, notes.md.
4. Write the log phase-ends/current/logs/T11.cG16.md.
5. Clean dumps and scratch under my shard dir (delete dumps dirs, q_* variants can stay? They're small. But the shard dir <200MB — dumps are the big ones. Delete dumps).
6. Report.

Wait — the log file: `phase-ends/current/logs/T11.cG16.md`. I'm allowed to write it? The brief says LOG: phase-ends/current/logs/T11.cG16.md. But the house rules say "Never read phase-ends/*/logs/" — writing my own log is required. The developer's message says "write the log". OK.

But also: "no make, no git, no commit" — so no commit. Good (the general coder instructions mention commit_task.sh, but the brief overrides: no git, no commit).

Also "write only under .run/P40/T11/G16/ plus appends to .run/P40/T11/moves.md" — but the LOG goes to phase-ends/current/logs/T11.cG16.md, which is explicitly required by the brief. The brief's LOG line overrides. I'll write it.

Let me check the time and proceed.

One more consideration: the developer said "finish only the item you are on (func_8012C2D0)". Good.

Let me first run the sweep check and write win.c. Also, I should double-check that q9's score is not a fluke and whether a *slightly* different variant (e.g., q9 with the declarations as in src: p,it) is score 1 too — q9 has p,it. Fine.

Actually, wait. Let me reconsider one more time whether score 0 is achievable by attacking the cse swap with a *real second set of p* to kill its REG_EQUAL. If p had no REG_EQUAL, cse wouldn't canonicalize and the order would stay (it,p) = target!

How to kill p's REG_EQUAL with a real second set that produces the same value? p is set once (p = it + K). A second set of p would need to preserve the value:
```
p = it + K;
...
p = p;   // identity — dead
```
No.

But what about making p's set *not* annotated with REG_EQUAL: cse annotates REG_EQUAL on a set of a register to an expression if the expression is constant (CONST or symbol_ref or plus of those). `plus(symbol,K)` is constant → annotated. What if the expression is `(plus (reg it) (const K))` where `it` is not known constant at that point? In q9, `it` is set in the entry block (symbol) and p in the test block. cse is per-block: in the test block, is `it`'s REG_EQUAL known? cse2 (global cse) might know it. The cse1 dump showed p's REG_EQUAL... Let me check: does the test block have `(set p (plus (reg it) K))` with REG_EQUAL? In the cse2 dump earlier for q9: insn 23 `(set (reg 72) (plus (reg 73) 25996))` — no expr_list REG_EQUAL shown! Wait, the cse2 dump for q9 showed:

```
(insn 23 20 26 (set (reg/v:SI 72)
        (plus:SI (reg/v:SI 73)
            (const_int 25996))) 3 {addsi3_internal} (nil)
    (nil))
```
No REG_EQUAL! So p has NO REG_EQUAL. Then why did cse swap the compare? Hmm! p has no REG_EQUAL, but `it` (reg 73) has REG_EQUAL symbol B at the compare (insn 26). And the compare is `(eq 72 73)` = (p,it) after cse. Before cse it was `(eq 73 72)`? Wait, the .jump for r1 showed EQ(72,73) = (it,p) with it=72. For q9, the .jump wasn't printed; the .rtl showed NE(73,72) = (it,p) with it=73,p=72. After jump (inversion) → EQ(it,p)? Then cse → EQ(p,it). Hmm.

Wait, in q9's cse2, the compare is (eq 72 73) = (p,it) where p=72, it=73. And insn 26 sets reg 73 = symbol B. So the compare is (eq p it) where it has REG_EQUAL symbol B. cse may have swapped to put the REG_EQUAL operand *second* (since it can substitute it into a compare? no).

In q14, p=72, it=73 too (same declarations), C `p == it` → .jump EQ(72,73) = (p,it) → cse kept (p,it). So cse's output is (p,it) in both. 

If p has no REG_EQUAL and it has one, cse's canonicalization puts p (no REG_EQUAL) first. To get (it,p), we'd need it (the REG_EQUAL one) first — i.e., cse must not canonicalize. Maybe if *neither* has a REG_EQUAL. How to remove it's REG_EQUAL at the compare? `it = (s32)D_801202A0;` — cse annotates. If `it` were set from a *memory load*, no REG_EQUAL, but that changes the code.

Hmm, what if the compare uses a *copy* of it that is not annotated: `s32 j = it; if (j == p)`? j's set is `(set j it)` → cse annotates REG_EQUAL = it's equivalence (symbol) via copy propagation? cse records REG_EQUAL only for constant expressions; `(reg it)` is not constant, so no REG_EQUAL on j. But cse might replace j with it (copy propagation) in the compare → same.

What if we compare `it` with `p` where both are *memory* values? no.

What if the comparison is between `it` and a value that is not p but the result of an arithmetic op on p (e.g. `p - 0`)? identity.

I think the wall stands. Let me also consider that maybe the *target's* build simply had a different cse decision due to a *different pseudo layout* (e.g., p computed in the entry block). We can't reproduce it lever-free.

Decision: WALL, best 1, tag `cse-compare-order` (new).

Hmm, actually let me reconsider the tag: the mechanism is cse reordering the comparison operands. But is it cse1 or cse2? The .cse dump (after cse1) already shows the swap. So cse1. Tag `cse-compare-order`. Fine.

Wait, one more idea just came: what if we make the *comparison* `if (it == p)` but swap which variable is the "it" of the entry: i.e., make the *entry* variable and the *test* variable different (so the test's it is a fresh variable with a fresh pseudo), and the compare uses `(j == p)`. The cse canonicalization would put p (no REG_EQUAL) first and j (REG_EQUAL) second → (p,j) → beq a0,v1... still wrong.

What if p is the one with REG_EQUAL and the test var has none? Then cse might put the no-REG_EQUAL first = (j, p) = target! How to make the test's `it` have no REG_EQUAL? If `it` at the test is *not* a constant: e.g., `it = (s32)D_801202A0;` is a symbol → REG_EQUAL. What if we write `it = (s32)D_801202A0 + 0;`? still constant → REG_EQUAL. What if `it = (s32)(D_801202A0 + 0)`? same.

Hmm, but the target DOES materialize `la v1,D_801202A0` → it's a symbol set. So the target's it has REG_EQUAL. And the target's compare is (it,p) with it first. So cse didn't canonicalize in the target.

Maybe cse's canonicalization rule is: put the operand whose REG_EQUAL is *simpler* first? it=symbol (simpler), p=plus (complex) → (it,p) = target. But our cse produced (p,it). Contradiction. Unless p's REG_EQUAL exists in the *target's* build but not ours... 

Hmm, in q9's cse2, p (72) has no REG_EQUAL (the insn 23 dump showed nil). Maybe in the target's build, p DID have a REG_EQUAL (because p was computed in the entry block from it=A with a REG_EQUAL, and cse carried it) → then cse canonicalizes (symbol, plus) → (it,p) = target! That fits! The target's p is computed in the entry block (delay slot) from it=A which has REG_EQUAL symbol A → p's REG_EQUAL = plus(symA,K). Then the compare (it=symbol B, p=plus) → cse canonicalizes to (symbol, plus) = (it,p) = target!

So the target's C has p computed in the ENTRY block (p = it + K before the goto), giving p a REG_EQUAL, and `it` live. And cse's rule is "symbol first, plus second".

But lever-free, computing p in the entry block folds it=A away (base candidate, score 4). UNLESS we can keep it=A live. The target's it=A is live because the launder asm sets it.

Hmm! But wait: in the target, is it=A live? The entry: it=A (v1); p=it+K (a0, delay slot); then test: it=B (v1). So it=A dies at the delay slot. It's live only for the p computation. Lever-free, `p = it + K` folds to a constant and it=A is deleted. 

Unless... the *fold* can be prevented by making it=A's REG_EQUAL unavailable: e.g., if `it = (s32)D_80120194;` is in the entry block and `p = it + K` is ALSO in the entry block, cse has it's REG_EQUAL and folds. What if the assignment `it = A` is in a *different block* from `p = it + K`? Then cse (per-block) wouldn't know it's constant... but cse2 (global) might. In q9, it=A is in the entry block and p in the test block — that's why p had NO REG_EQUAL (cse1 is per-block; cse2 might be global but the dump showed nil). So in q9, p has no REG_EQUAL → cse canonicalizes (p,it). If instead p had a REG_EQUAL (computed in the same block as it=A), the canonicalization would be (it,p) = target — but then it=A gets folded into p as a constant (since it's dead), giving `la a0, A+K` and no it=A register.

Is there a way to have it=A and p in the same block, with it=A *live*, so no fold? it=A live means used after p. The only later use is at the compare (but it's reassigned at test). What if we *don't* reassign it at test, but use a second variable for B? Then the entry's it=A is still dead after p... unless the copy block returns it (A)? Semantically wrong.

Wait — actually, is it? Let's re-read the target: `copy: return it`. The copy block is reached from body where it is the test value. So the returned value is the test value. If we use two variables (a for entry, it for test), then `copy: return it` returns the test value. The entry `a = A` is dead after p. So a=A gets folded into p → constant. Same fold.

So no.

Conclusion: the target's p has a REG_EQUAL because it's computed from it=A in the same block, and that's only possible with it=A being live, which only the launder achieves. Lever-free, the fold removes it. The q9 structure (p in the test block) gives the closest result (1) because it keeps it=A live across the goto, but then p has no REG_EQUAL and cse reorders the compare.

Hmm, so which is the true wall tag? The mechanism: cse folds the constant-address `it + K` into a constant when it=A is dead (cse-const-addr), OR cse reorders the compare when p is in the test block. The fundamental wall: cse's constant-address substitution/folding. I'll use `cse-const-addr` (existing tag) with the mechanism describing both: "cse folds it=&A into p=it+K (dead it) or, with p in the test block, canonicalises (eq it,p)->(eq p,it); target keeps it in v1 and (it,p)". That's >140 chars. Let me write a tight one:

"cse folds it=&A into p (dead it): la a0,A+K, no v1; p in test block instead -> cse1 canonicalises (eq it,p)->(eq p,it) (p has no REG_EQUAL)" — count ~140. Let me count precisely later.

Maybe the new tag `cse-compare-order` is more precise for the residual, but the *primary* mechanism is the const-addr fold. I'll use `cse-const-addr` since the brief says a tag from walls.txt is preferred and it fits the fold; the evidence explains the residual. Hmm, but the residual at best=1 is the compare order, not the fold (the fold is avoided in q9). The wall is really "cse's constant-address handling: fold or reorder". I'll tag `cse-const-addr` and explain.

Hmm, let me reconsider: the walls.txt cse-const-addr: "cse folds or substitutes a constant/absolute address the target keeps base-relative (T10 S09, S11, S16)". Our case: the target keeps &A in v1 and derives p base-relative; cse folds it. Yes, cse-const-addr is exactly it. The compare reorder is a secondary effect. Use `cse-const-addr`.

Now let me proceed to finalize. Steps:
1. Write win.c = q9 body (best, score 1).
2. Quick sweep of q9 on a few includers to confirm.
3. Append results.tsv row.
4. Append moves.md line.
5. Write notes.md.
6. Write log.
7. Clean dumps (delete $d/dumps*, tu_dump, shared) — keep the shard dir small.
8. Report.

Wait, one issue: the item dir has lots of prior candidate files (gen_*, q_*, etc.). That's fine (small). But the dumps are large; delete them.

Also, item 1's dir: I removed the dumps. I left c_*.c files — fine.

Let me check disk usage after cleanup.

Also: "Items that already have a results.tsv row are done: skip them." I'm adding one row for C2D0 only.

The results.tsv header already exists. I'll append with tabs.

Let me also record the start/end times per item in the log: item 1 (8012B4B8) 09:38–10:06 (~28 min, ~40 tries, no row — Handoff: not started per developer); item 2 (8012C2D0) 10:06–now.

Wait, the developer said to list 8012B4B8 under "Handoff: not started" — but I did work on it. I'll list it there with a note that it was explored to best 19 (block-move variant, score 19) but no row was written per the restart instruction. That's honest and useful. Actually, "Handoff: not started" means the *row* wasn't started? Hmm. I'll put it under "Handoff: not started" as instructed and add the observed best in the notes (not a row). The developer's instruction is explicit; I'll follow it.

Hmm, but wait: is it better to write a row for 8012B4B8 anyway since I have 28 min and 40 tries? The developer said "Do not start the remaining items (func_8012C750, func_801372B0, and func_8012B4B8 if it has no row); list them in your log under 'Handoff: not started'." So no row. I'll comply. But I'll preserve my findings in the log so the next coder can use them (best 19 with the struct-copy variant, c_struct.c). Actually, the log is for the phase; I'll include a short "Handoff" section with the item-1 findings.

Let me now do the sweep check on q9. sweep.sh uses tryinc.py which rotates the includer list; with kmax=8 it checks the first 8. Let me run kmax=10.

Actually, for the WALL evidence, the brief says "best = lowest score of a lever-free body" — dt.sh's score on the header TU. I'll report best 1 and note the first-TU score. A sweep would strengthen it; let me do kmax=8 quickly (8 × ~1.5s = 12s).

Let me do it.
