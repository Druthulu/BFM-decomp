---
ts: 2026-11-06T15:15:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vkIn2l2akXweXkx3iMdb
---
h1/h4 added an instruction (andi) and changed a lot. h3/h5/h6/h7 still fold (4).

So g1's `a1 != 3` is the closest: only the register differs (s1 vs s0). 

Can we get the compare on s0 (t) but with a value the compiler doesn't know? What if we compare a *different variable* that is known equal to t at the C level but which gcc keeps in s0? E.g., `s16 u = t; ... if (u != 3)`. cse would equate u and t (same register). It would fold.

What if `u` is derived via `(s16)a1` again: `if ((s16)a1 != 3)` — f1 scored 4 (folded). Hmm, f1 folded because (s16)a1 == t and t==5 known.

But g1 with `a1 != 3` (full 32-bit) didn't fold. What if we compare the full `a1` but gcc puts it in s0? No, a1 is the parameter.

Hmm, what if we reassign `t` to a value that is the full a1? `t = a1;` then t's register holds the full a1 (s0), and `if (t != 3)` would compare s0 against 3 — but t's value wouldn't be 5 (it'd be a1's full value), and later uses of t (like `D_80183478[t]`) need the s16 value. Hmm.

Wait, actually let me reconsider: what is in s0 at that point? t = (s16)a1 → `sra s0,v0,0x10` where v0 holds a1? Let me check the prologue. In the target: `6d8: sra s0,v0,0x10` — so v0 holds a1, and s0 = t. So a1 is in v0, and t in s0.

For g1, `a1 != 3` compares s1 vs v1. Hmm, s1 holds a1? The diff said mine `bne s1,v1` — so a1 is in s1 in my build (register allocation differs because comparing a1 extends its live range). Target has a1 in v0.

Hmm. So g1 is structurally right but the register differs.

What if we compare `(s32)a1` but the compiler... same as a1.

Alternatively: keep the `t != 3` test but make t's value unknown by *reassigning t from a1* right before: `t = (s16)a1;` — f5 scored 4 (folded).

What if we assign t from a1 via a *different* expression that gcc can't equate: e.g. `t = (s16)(a1 & 0xFFFF);`? Then t is a fresh computation from a1's low bits; the compiler knows t==5 (from the earlier branch) → folds.

Hmm.

What about making the compare `t != 3` be against a variable, and make cse's equivalence be on the variable... 

Let me think about g1's success differently: g1 compares a1 (32-bit) which is NOT known to be 5. The emitted compare is on a1's register. If I could make a1's register be s0... Actually, what if I compare `t` but write the source as `if (t != 3 && a1 != 3)`? no.

What about `if ((t | (a1 & 0)) != 3)`? folds t.

What about `if ((t + (a1 - a1)) != 3)`? folds.

Hmm.

What if we compare `t` against 3 but ensure the value of t is re-derived from a1 in a way that's in s0 and not known? For instance, `t = (s16)a1;` then `t = (s16)(t | (a1 << 16 >> 16 & 0))`... folds.

OK, different approach: what if the *first* test `if (t == 3) goto sel_054;` is changed so the jump equivalence is on something else, and the second test stays `t != 3`? The compiler knows t==5 from the t==5 test regardless.

What if we invert the order of the two tests in the source? E.g.:
```
if (t == 5) {
    if (t != 3) goto sel_094;
}
else if (t == 3) goto sel_054;
```
Then the t==5 branch is `if (t == 5)`: on the fall-through t==5 known, so t!=3 folds. Same.

What if we test t==5 via a *different* variable that the compiler can't equate to t, but which is in the same register? For instance, a variable `v` that the compiler allocates to s0 too... but if it's equal to t, cse equates.

Hmm, what about using `a1` for the t==5 test (full 32-bit) and `t` for the t!=3 test?
```
if (a1 == 5) { if (t != 3) goto sel_094; ... }
```
But the target's test is `bne s0,v0` where s0=t and v0=5. If we test a1==5, the compare would be on a1's register, and also the semantics change (a1 could be 0x10005 → t=5 but a1!=5). That would break the case where a1 = 0x10005. Hmm, but does that matter for matching bytes? The bytes would differ (different register).

Wait, but what if a1==5 implies t==5, and the code inside uses t... Actually the target's `if (t == 5)` compares t. If I write `if (a1 == 5)`, the compiler would know t == (s16)a1... For a1==5, t==5. But for a1=0x10005, t==5 while a1!=5 — different behavior. Would the bytes differ? The compare would be `bne a1reg,v0` — different register than target. Not matching.

Hmm.

Let me look at this from the angle of: what does the target's register allocation look like, and why does g1 put a1 in s1? Because comparing a1 keeps it live longer. In the target (with the launder), a1 is in v0 and dies early (t = (s16)a1). 

So to match, the compare must use t's register.

OK — what about this trick: make the t!=3 test use a value that cse can't fold but which lives in the same pseudo as t. cse's jump equivalence is on t. If we do `t = t;`... let me just test it. Also `t = t + 0;`, `t = t * 1;`, `t = -(-t);`, `t = t ^ 0;`, `t = t | 0;`, `t = t & -1;`.

Some of these might survive the tree folder in 2.7.2 and create a real set of t that invalidates cse's equivalence. `-(-t)` for t=5: the compiler knows t=5 → folds to 5? Maybe not; unary minus twice might not be folded in 2.7.2's tree simplifier. Let me test a batch.

Also `t = (s16)t;` (f? not tested — d7 was for item 1). Let me test.

Let me generate i1..i8.
