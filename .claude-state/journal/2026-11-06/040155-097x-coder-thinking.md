---
ts: 2026-11-06T11:01:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ENOx213HVuMgAQ1iKrJX
---
Diff:
1. Position 60: mine has a nop, target `li v0,3` (the delay slot copy).
2. Position 83-84: mine lacks `addiu v0,s1,1` (the delay slot copy).
3. Position 128-130 vs 134-136: the D_801151D0 store moved (the memory barrier's job).

So three issues: the RC-12 copies (2 sites) and the memory barrier.

Let me tackle them one at a time.

Issue 1 (position 60): target has `li v0,3` in a delay slot; mine has nop. This is the "outer else arm" copy that survives because of the opaque copy. Real-C alternatives? The comment says: `(plus (reg 0) 3)` is not a plain constant load so it survives noop-move deletion and stays cross-jumpable.

What real C can produce a non-constant 3? E.g., `n = 3;` where the 3 comes from a variable that's known to be 3? Like `s32 k = 3; n = k;`? cse would propagate k=3 and fold to a constant.

What about `n = (s32)(u16)3;`? folds.

What about `n = 3 | 0;`? folds.

Hmm. What about using a `volatile` variable holding 3? That's a memory access → extra insns.

What about `n = D_80115126;`? No.

The RC-12 trick is the "$0-add opaque copy" — the classic lever. Real C can't easily produce it. That's why the wall tags include `cse-opaque-copy`.

But maybe a different C *shape* avoids the need: e.g., the cross-jump structure. The comment says both arms must have the same rtx for cross-jumping. If instead we structure the code differently (e.g., compute n with a ternary or a shared block), the compiler might produce the target's `li v0,3` differently.

Let me look at the target's code around position 55-90 to understand.

Actually, let me try some variants:
a) `n = 3;` (base) = 9.
b) Use a shared label: `if (D_80115126 == 3) { ... } else { n = 3; }` — same.
c) Restructure: 
```
n = 3;
if (D_80115126 == 3) {
    if (D_8011511A == 3) {
        ot = call(ot, &D_801BC8D0, 3);
    } else {
        n = 4;
    }
}
```
That's the same structure with n=3 before the if. Might produce different codegen (the constant 3 materialized once before the branch). Let me try.

d) Use `n = 3;` in both places but with different variable... 

Let me first look at the target assembly for this function to understand what's needed. Let me dump the target object for func_80187EA0.

Actually the diff already tells me: at position 60 the target has `li v0,3` where mine has nop. Position 83-84: the target has `beqz v0, ff8; addiu v0,s1,1` (the delay slot filled with addiu v0,s1,1) where mine has `beqz v0, ff0` and the addiu elsewhere.

Let me try variants quickly. First, the "n = 3 before the if" restructure.

Also, maybe a `?:` for the 3/4:
```
n = (D_8011511A == 3) ? 3 : 4;
if (D_80115126 == 3) { if (D_8011511A == 3) ot = call(...3); } else n = 3;
```
Hmm.

Let me try several structural variants and score.

Given time constraints (2 big items, ~25 min each), let me be efficient: generate ~10 variants and score them.

Variant ideas:
1. base (n=3 plain).
2. n=3 assigned once before the if, and in the else branch too.
3. `n = 3;` with `n` declared volatile? no.
4. `s32 three = 3;` at function scope, `n = three;` both sites — cse may fold but maybe not across the branch.
5. Use `n = D_80115126 == 3 ? ... ` restructure.
6. Use `do { n = 3; } while(0);` at both sites — the do-while split might preserve the constant.
7. `n = 3; n = n;`? cse removes.
8. `n = (s16)3;`? folds.
9. Use `n = 4 - 1;`? folds to 3.
10. `n = 1 + 2;`? folds.

The do-while idea is promising: `do { n = 3; } while(0);` creates a loop note; the constant might not be cross-jumped... but we WANT cross-jumping.

Hmm, the target needs the `li v0,3` to be CROSS-JUMPED (the outer bne targets the shared insn and reorg copies it into the delay slot). With a do-while around each `n = 3`, they'd be in different loops → not cross-jumpable.

What about a single shared `n = 3` block:
```
if (D_80115126 == 3) {
    if (D_8011511A == 3) { ot = call(...); n = 3; }
    else { n = 4; }
} else {
    n = 3;
}
```
The two n=3 sites are the same constant → cross-jumpable naturally.

The problem per the comment: "it survives the noop-move deletion that otherwise eats the outer else arm entirely (its value is already in $v0 from the compare constant)". So the outer else's `n = 3` is a noop move because $v0 already holds 3 (from the comparison with 3). The noop-move deletion removes it, so the cross-jump target vanishes.

Real-C ways to keep it: make the 3 in `n = 3` not be the same rtx as the compare constant. E.g., if the compare is `D_80115126 == 3` and `n = 3` — both are constant 3 in $v0.

What if `n` is assigned from a *different* source that also evaluates to 3 but is not a constant: e.g., `n = i + 3;` with i=0? Hmm.

What if we change the compare to use a variable: `s32 three = 3; if (D_80115126 == three) { ... n = three; }` — then the compare loads 3 from `three` into a reg, and n = three copies it. But that's the same rtx (the pseudo `three`).

Hmm, if `three` is a variable = 3, then `n = three` is a reg copy, not a constant load. The target wants `li v0,3` (a constant load). 

What if `n = 3` is written as `n = (s32)(s16)3`? folds.

OK, this looks like a genuine opaque-copy wall. But let me try a few cheap variants anyway.

Also issue 3: the memory barrier before D_801151D0 = ot. The comment: the OT-link store (MEM_IN_STRUCT_P + varying) vs D_801151D0 (plain SYMBOL_REF) — the scheduler hoists the global store above the read-modify-write. A real-C fix: make D_801151D0 a one-field struct via an asm-label alias (the comment says it works identically but is an asm-label alias = allowed? The comment: "Re-declaring D_801151D0 as a one-field struct via a §37 asm-label alias works identically; the fence is the smaller edit."). An asm-label alias for a *symbol name* is allowed (like aD800B9A02). So: declare `extern struct { s32 v; } aD801151D0 __asm__("D_801151D0");` and store `aD801151D0.v = (s32)ot;`. That makes the store MEM_IN_STRUCT (different alias set) → the scheduler won't hoist it. That's a real-C + symbol-alias fix, allowed!

Great, that could fix issue 3.

Now issues 1-2 (the RC-12 copies). Let me think about what real C could produce the `li v0,3` in the delay slot.

Target positions around 55-90: let me dump the target to see the context.
