---
ts: 2026-11-06T15:26:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GrFl4waqMJ9YalIwng2G
---
All 4. Time 08:25:54. Item 2 ~16 min.

I'm going to conclude this is a wall. But I need 20 min. Let me spend ~4 more minutes on a final set of ideas, then write up.

Final ideas: 
1. What if the whole function's `t` is declared `s32` instead of `s16` and we rely on `(s16)a1` casts? The target has t as s16 (sra). Changing t to s32 with `t = (s16)a1` keeps the value; the type of t affects comparisons: `t == 5` with t s32 is fine. Would the codegen differ? Probably the same. And would `t != 3` fold? Still yes.

2. What if we make `t` a *different variable* for the t!=3 test: `if ((s16)a1 != 3)` — f1 folded.

3. What if we compare `t` against 3 with the operands swapped: `if (3 != t)` — same.

4. What if the t==5 test is `if (t == 5u)`? unsigned constant — same.

5. What if we use a `long long`? no.

Let me try one more structural thing: make the t==5 branch and the test in the *same* basic block but with the test before... no.

OK, let me also try the "dead-reset" on the constant-holding register: in the RTL, the t==5 compare is `(ne (reg t) (reg 116))` where reg 116 = 5. If we could invalidate reg 116's constant... it's a compiler temp from the source constant 5. What if the source's 5 comes from a *variable* `five` that is dead-reset after the branch? Let me try:

```
s32 five = 5;
...
if (t == five) {
    five = 0;         // dead-reset: invalidates five's const equivalence
    if (t != 3) ...
```
Hmm, but `five = 0` after the branch — is it dead? five isn't used later, so flow deletes it. cse sees `five = 0`, which invalidates five's equivalence. But t's equivalence (t == five, merged class with 5) might survive since t's class still contains 5.

Actually, cse's record_jump_cond for `(ne (reg t) (reg five))`: it makes t and five equivalent in the fall-through. Then the equivalence class {t, five} — does it contain the constant 5? five's value is a constant 5 (from the assignment), so cse's qty_const for five's class is 5, and t joins that class → t's class const is 5. Setting five=0 would split five off, but t remains in the class with const 5? When cse processes a set of five, it removes five from the class but the class (containing t and const 5) stays. So t is still known 5. Folds.

What if we dead-reset *t*? changes value.

OK. I'll finalize. Actually, let me try one more idea that might work: the `t = t` self-copy INSIDE the t==5 block *without* the do-while (i1 did that → 4). What about a self-copy through a *different* variable that cse can't fold: `u = t; t = u;` — that's a copy chain; cse merges. 

What about `t = (s16)(u16)t;`? For t=5 → 5. cse folds? The double cast might not be folded in 2.7.2. Let me test:
y1: `t = (s16)(u16)t;` before the test.
y2: `t = (s16)(s8)t;` — changes value for >127 (t=5 → 5, fine) but semantics for other values... t is 5 in this block, so OK. But the code must still be correct for t==5 only (the block is t==5). Hmm, actually the test is inside `if (t == 5)`, so t is 5; any value-preserving-at-5 transform is fine. But the compiler might fold.

y3: `t = (s16)(t * 2 - t);` → t=5 → 5. Might not fold! And it costs instructions (sll/sub) unless combine folds to t.

Let me test y1, y2, y3. Actually y3 would add instructions if not folded. Hmm.

Actually, the key requirement: the *set* must survive to cse (so it invalidates), and then flow must delete it (so zero bytes). A set that computes a value isn't dead (t is used). So it would cost instructions. Unless the compiler folds it back to `t = t` and removes it (then no invalidation).

So the only zero-cost option is a set that cse sees as a set but which is deleted before/after. `t = t` is the only one — and cse/flow remove it.

Unless... `t = (s16)t;` — a narrowing conversion of t to its own type. cse might see a SUBREG set, and flow might delete it as a no-op. Worth a try (i4 tested `t = (s16)t;` → 4).

OK, I'm done. Let me finalize at ~08:27 (17-18 min). Hmm, still short of 20. Let me do a couple more minutes with y1/y2 and one more structural idea, then finalize at 08:30.

Actually, let me reconsider the requirement: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". I have 50+ tries. If I'm at 17 min, I should spend 3 more. Let me do 2 more batches.

Batch y: y1 `t = (s16)(u16)t;`, y2 `t = (s16)(t & 0xFFFF);`, y3 `t = (s16)(t << 0);`.

And a structural z: what if the t==5 branch is tested via `if (t == 5)` but with the *sel_054* label moved before the test so the test is at a join? Hmm.

Let me just run the y batch.
