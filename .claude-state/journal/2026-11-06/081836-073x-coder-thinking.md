---
ts: 2026-11-06T15:18:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_87mV6p8HlK945IIk5vzQ
---
Interesting — it's only 08:17! I thought it was later. So item 2 took ~8 minutes. Good, plenty of budget. 

Hmm, given the time, maybe I should spend a bit more on item 2? The brief says budget 20-30 min per item; past 30 stop. I've used ~10 min on item 2 (08:08-08:17). A WALL needs ≥20 min AND ≥30 tries. I have 34 tries but only ~10 min. The rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I should spend at least 20 min on it. Let me continue exploring for ~10 more minutes.

Let me think harder about item 2.

Key insight: the target compares t (s0) against 3 after knowing t==5. To keep the compare unfolded, cse's jump equivalence must be broken. 

What invalidates cse's recorded jump equivalence? Looking at cse.c: `record_jump_cond` is called for conditional jumps; the equivalence is in the current EBB's equivalence table. A `set` of the register invalidates. Also a LABEL ends the block.

So: a surviving LABEL between the t==5 branch and the t!=3 test would work. The do-while(0) didn't survive jump1.

What survives jump1 as a label with zero instructions? 

Idea: a `switch` with a single case? gcc might generate a compare + label. Hmm.

Idea: a `goto` that jumps forward over nothing? `goto L; L: ...` — jump1 deletes jump-to-next.

Idea: a backward goto creating a loop that runs once? jump1 might not delete a backward branch easily. E.g.:

```
s0_label:
...
if (t == 5) {
    if (some_always_true) goto s0_label;   // no
```

What about a `while (1) { ...; break; }` around the test? g4 tested `while (1) { if (t != 3) goto sel_094; break; }` → 4 (folded). So the loop label didn't break cse? Hmm, that's surprising: a while(1) loop with a break should create a label. But jump1's `delete_unreachable` / the loop with a constant-true condition might be flattened.

Hmm, what about a label that's the target of the *existing* switch jump table? The case labels! The switch on idx has cases; each case block starts with a label. But the t==5 test is inside case 5, far from a label.

What if we restructure the switch so that the t!=3 test is the *first* statement of a new case? E.g., move the t!=3 test into a separate label reachable by a goto from inside the t==5 block:

```
if (t == 5) {
    goto test3;
test3:
    if (t != 3) goto sel_094;
}
```
jump1 removes goto-to-next.

What about:
```
if (t == 5) {
    goto L1;
L2:
    if (t != 3) goto sel_094;
    ...
L1:
    goto L2;
}
```
Silly; jump1 would thread.

Hmm.

What about using the switch's case label as the split? The `case 5:` label is where t is computed. The t==5 branch is after. No.

What about moving the t==5 test to the top of case 5 and the t!=3 test into a *different case*? Semantics change.

Hmm, what about a `for` loop with a variable condition that's always true but opaque? E.g. `for (i = 0; i < 1; i++)` — folds. `for (i = 0; i <= mode; i++)` — mode is runtime; not always true.

What about using the existing `mode` variable: `if (mode != -1) { if (t != 3) goto sel_094; }` — not always true. No.

OK, another angle: the cse jump equivalence is recorded only for the fall-through of a conditional jump comparing a REG with a CONST. If the t==5 test were a `switch` (jump table), no equivalence is recorded! A switch on t with cases 0,3,5 would use a jump table (bad, changes code). But maybe a switch with few cases compiles to compares — same.

What if the t==5 test is written as a comparison of two registers: `if (t == five)` where `five` is a variable? cse's record_jump_cond records "t == five" (reg==reg), not "t == const". Then the `t != 3` fold requires knowing five==3... it's not. But we need five==5 at runtime; if `five` is a local constant 5, cse knows five==5 (constant) and might fold t==five to t==5. Hmm, cse's fold_rtx would substitute five's constant into the compare → `t == 5` → same equivalence? Actually record_jump_cond is called with the *folded* operands? Let me check: in cse.c, `record_jump_cond (code, mode, op0, op1, ...)` is called from `record_jump_equiv` with the operands of the jump insn. If five's constant is substituted by fold_rtx before, then it's const again.

But if `five` is a variable whose value cse can't determine (e.g., set from a function result), then the branch compares two registers. But then `five` must be 5 at runtime — where would it come from? We could set `s32 five = 5;` — cse knows it's 5.

Unless we make `five` a *parameter-derived* value that's 5... no.

Hmm, what about `if (t == (s16)(D_8011514A - ...))`? changes code.

OK. What about breaking the equivalence with a *store*: cse invalidates equivalences on memory stores? No, only the register's.

What about a `set` of t that cse sees as a set but which is later removed by flow? The dead-reset C0414: `t = 0;` after use is deleted by flow *after* cse. But a dead set *before* the test changes the value. Unless the dead set is after the test:
```
if (t != 3) goto sel_094;
t = 0;   // dead reset after the test
```
That doesn't help the test.

Hmm, but C0414's insight is that cse's forward scan invalidates the equivalence at a second set. What if we place a *second set* of t between the t==5 branch and the test, where the second set is a *dead* set that flow removes but cse sees? For cse to see it, it must be present at cse time. flow runs AFTER cse (pass order: jump, cse, combine, flow?). Actually from the dump order: rtl, jump, cse, combine, flow — so flow is after cse. If we write `t = 0; t = (s16)a1;`? The first set is dead (overwritten) → flow deletes it, but cse sees it: cse would process `t = 0`, invalidating the equivalence, then `t = (s16)a1` (which cse might know is 5? no — cse doesn't know (s16)a1 is 5 unless... hmm, it might via the equivalence from the earlier `t = (s16)a1`).

Wait, the equivalence "t == 5" comes from the jump, not from the computation. If we insert `t = 0;` then `t = (s16)a1;` between the branch and the test:
- cse processes the branch: records t == 5.
- cse sees `t = 0` → invalidates t's equivalence.
- cse sees `t = (s16)a1` → t's value is (s16)a1, unknown (cse doesn't know a1's low bits).
- cse sees `if (t != 3)` → cannot fold! 
- combine/flow: combine's get_last_value follows LOG_LINKS: the last set of t is `t = (s16)a1`; it would need to know (s16)a1. Hmm, combine might not fold. flow deletes the dead `t = 0` (it's dead since overwritten).
- The extra `t = (s16)a1` generates an `sll/sra` pair — extra instructions! Unless... hmm, wait, `t = (s16)a1` compiles to `sll v0,s1,0x10; sra s0,v0,0x10` (2 insns). That's 2 extra.

Unless the dead set is the *only* extra: `t = 0;` alone (dead, overwritten by nothing). But then t's value after is 0, not 5.

Hmm what about `t = t;` — cse sees a set (self-copy) and invalidates the equivalence! Then flow deletes it. Does cse delete a self-copy? cse's `cse_insn` might remove `(set t t)` as a no-op... Let me test i1 again: i1 = `t = t;` scored 4. So either the front end removed it or cse ignored it.

What about a set that's dead but *not* a self-copy: e.g. `u = t;` where u is a dead variable? That sets u, not t. Doesn't invalidate t.

Hmm. What about `t = t ^ 0;` — removed.

What about a set of t to a *different* value followed by a set back to (s16)a1, where the first is dead: `t = 0; t = (s16)a1;` — 2 extra insns? The `t = 0` is deleted by flow (dead), and `t = (s16)a1` compiles to sll+sra (2 insns) unless gcc reuses the existing t (it's already in s0). Hmm — if t is already in s0 and `t = (s16)a1` recomputes, gcc emits sll+sra again. That's +2 insns.

Unless we use `t = (s16)t;` as the restoring set — that's a no-op, removed.

Hmm, what about `t = t + 0;` as the dead set, then... removed.

What about `t = 0; t = t + 5;`? t = 5 (known) → cse might fold to t=5. And the first set is dead → flow deletes. But cse would see `t = 0` (invalidate), then `t = t + 5` — cse can fold t+5 = 5 (constant) → records t==5 again. Hmm, then the test folds. But wait, is `t + 5` with t=0 folded by cse? cse's fold_rtx would substitute t=0 → 5. Yes.

What about `t = 0; t = t | 5;`? folds to 5.

What about `t = 0; t = t + a1 - a1 + 5`? Hmm.

What if the restoring set is opaque but cheap: `t = (s16)(a1 & 0xFFFF)`? That's sll+sra + andi = 3 insns. No.

Hmm, what about `t = 0; t = t | (a1 & 0xFFFF);`? For a1's low bits = 5 → t = 5. But that's andi + or + ... more insns.

Hmm.

What if we accept 1-2 extra instructions? The score would be higher (COUNT). Not a MATCH.

OK here's another thought: the dead-reset trick could work in the OTHER direction. cse records t==5 at the branch. What if we make the t==5 test *not* a comparison against a constant in cse's view, by making the constant a register: `if (t == five)` where `five` is a variable known to be 5 at compile time? cse substitutes → const.

But what if `five` is a variable that's *not* known constant but equals 5 at runtime, obtained cheaply? E.g., `five = (s16)a1 & 0; five += 5;` folds.

What about deriving five from a value the compiler can't fold but which is 5: e.g., `five = D_8011514A & 0`? folds (x&0=0). `five = D_8011514A - D_8011514A + 5`? The compiler would load D_8011514A twice? No — it would CSE it to one load, then x-x = 0? fold_rtx may fold x-x only for registers? Hmm, gcc's fold_rtx: `(minus (reg) (reg))` with the same reg → 0? Possibly not.

That would add a load instruction. No.

OK, let me think about the problem from the "score 1" state: g1 has `bne s1,v1` vs `bne s0,v1`. What if we could get the compiler to put a1 in s0 and t in s1? The target has idx→s0? Wait: target prologue: `move s0,a0` (idx = a0), `move s1,a1` (a1). Then `t = (s16)a1` → sra s0, v0 — wait, that overwrites s0 which held idx! Hmm: at 6d4 `sll v0,s1,0x10; 6d8: sra s0,v0,0x10` — s0 now holds t. But idx (s0) is dead by then (the switch used it). So s0 is reused for t.

In g1, comparing a1 extends a1's live range past the t==5 branch, so gcc keeps a1 in s1 (it's already there) and the compare uses s1. To match, the compare must use s0. Since t is in s0, we need to compare t.

Hmm — what if we compare `t` but assign a1's *full* value to t first? `t = a1;` — but t is s16! If t is declared s32... then later uses of t (D_80183478[t]) would use the full value — changes semantics (e.g., a1=0x10005 → index 0x10005 instead of 5). But would the bytes differ? The target's later code uses t as s16. If t were s32 = a1, the code would differ.

Hmm, but what if we make a *new* s32 variable `w = a1;` and compare `w != 3`, where w is allocated to s0? Unlikely.

OK, let me consider: maybe the target's source for that compare isn't `t != 3` but something like `(s16)a1 != 3` where the compiler keeps a1 in v0... f1 folded.

I think flow-known-value is a genuine wall. But let me try the dead-set trick quickly since it's cheap: 
k1: `t = 0; t = t + 5;` before the test.
k2: `t = 0; t = t | 5;`
k3: `t = 0; t = 5;`
k4: `u = t; t = u;` (dead? no)
k5: `t = 0;` then restore via `t = (s16)a1;`
k6: `t = t ^ (t ^ 5);`? folds.

Hmm k3 `t = 0; t = 5;` — cse: t=0 (invalidate), t=5 (const). Then t==5 known again → folds. But maybe cse's forward scan doesn't re-record constants after a set within the block? It does (that's how the original fold happened: t was set to 5? no, the original fold came from the jump equivalence).

Actually interesting: if we set `t = 5;` explicitly, cse knows t==5 from the set → folds.

What about `t = 0; t = t + 5;`? cse folds t+5 to 5 (t known 0) → folds.

Hmm.

What about `t = 0; t = t | a1;`? no.

Let me try a couple of these anyway (cheap), plus one idea: `if ((t - 5) != -2)`? folds.

Actually — what about using the *other* variable `idx` or `sel`? no.

Let me try the dead-set family and also `t = 0;` followed by using the *original* t via `a1`: k5. And a variant where the restoring set is `t = (s16)(t + 5);` after `t = 0` → folds.

Hmm, what about `t = 0; t = t - -5;` folds.

I'll test k1-k5 quickly. If no luck, finalize the wall (it'll be ~20 min).

Actually — wait. A cleaner idea: what if the test compares t against a *non-constant* that happens to be 3, derived from `idx` or `mode` without extra instructions? The target has `li v1,3` already materializing 3 for the first compare. The second compare uses the same v1. If the source's second compare were against a variable holding 3 that gcc folds to the same constant, the code is the same. But cse would know the variable's value 3 and still fold t!=3? It folds because t==5, regardless of the other operand being 3. Yes, it knows both → folds.

OK so the only route is to make t unknown.

One more idea: make t's value *not* flow-propagated by using a different variable for the t==5 test and the t!=3 test that cse doesn't equate... but both must be in s0. If we have `t` (s0) and `u` where u is a copy of t allocated to the same register... cse equates copies.

What if `u` is t's value obtained through a `s16` variable that's *modified* between: `u = t; u = u;`... no.

Alright, let me test the dead-set family and then finalize.
