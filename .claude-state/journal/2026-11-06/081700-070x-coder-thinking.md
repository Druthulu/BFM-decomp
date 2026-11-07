---
ts: 2026-11-06T15:17:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5sVfywIpKyHs3HsWdDgA
---
At 6d4: `sll v0,s1,0x10` then `sra s0,v0,0x10` — that's `t = (s16)a1` (a1 in s1). v0 is a scratch. So t is in s0.

Now, the target's `bne s0,v1,71c` compares t (s0) against v1=3. In g1, `bne s1,v1` compares a1 (s1) against 3 — same register as a1. So the register difference is just the compared operand.

So to match, we need a compare on t's register (s0) that the compiler can't fold. The compiler folds because it knows t==5 via the jump equivalence on t.

Hmm — but what if we compare `t` in a way that cse's jump equivalence doesn't apply: e.g., compare `t` against 3 but through an *opaque* value that cse can't relate... 

Wait, actually: cse's jump equivalence is `t == 5` recorded at the `bne t,v0,740`. It's invalidated by a set of t. We tried no-op sets; they were removed. What about a set that isn't a no-op but is value-preserving for the *specific value 5* and which the compiler can't fold because it doesn't know t=5 at the set point... but it does.

Hmm, unless the set is BEFORE the t==5 branch! If we set t = <something> before the branch, then the branch equivalence is on the new value. Wait:

```
if (t == 3) goto sel_054;
if (t == 5) {
    ...
}
```
What if we insert a set of t before the t==5 test that is value-preserving but opaque, so the branch `t == 5` is on an unknown value? No — then the branch itself would be a real compare (it already is). The jump equivalence would still be recorded on t at that branch.

Hmm.

What if the t!=3 test is moved to a *different* variable that's a copy of t, and the copy is made BEFORE the t==5 test:
```
s16 u;
...
u = t;          // before the t==5 branch
if (t == 5) {
    if (u != 3) goto sel_094;
}
```
cse equates u and t (a copy) and knows both are 5 → folds. Unless the copy is made in a way cse doesn't equate: e.g., `u = (s16)(t << 0);`? folds. `u = t + 0;`? folds.

Hmm.

What about making u come from a different source: `u = (s16)a1;` — same as t. cse equates.

Hmm, what about making u a *different type* so cse's equivalence is via SUBREG and the comparison isn't folded? E.g., `s32 u = (s16)a1;` then `if (u != 3)`. u is a separate pseudo but cse equates u == t (both are sign_extend of a1's low bits) → folds? Let me test.

Actually — wait. f1 was `(s16)a1 != 3` which folded. So cse knows (s16)a1 == 5.

What about `u = (s32)(u16)a1;`? That's zero-extend; for a1 with low 16 bits 5, u = 5 (if a1's high bits are 0) — but a1 could be 0x10005 → u = 5, still 5! Actually (u16)a1 = 5 always when t==5? t = (s16)a1 == 5 means low 16 bits = 5, so (u16)a1 = 5 → u = 5. So `u = (u32)(u16)a1; if (u != 3)` is always true. But would the compiler know? It knows t==5, i.e. sign_extend(low16)==5 → low16 == 5. Deriving (u16)a1 == 5 requires reasoning through the sign extension — cse might not. Let me test `if ((u16)a1 != 3)`. hmm, similar to h1 but on a1.

Wait, h1 was `(u16)t == 5` which added an andi (because t is s16 and (u16)t needs masking). But `(u16)a1` also needs an andi (a1 is s32). So the compare `(u16)a1 != 3` would need `andi` → extra ins.

Unless the andi is folded into the compare? MIPS has no andi-compare.

Hmm.

What about `(s16)a1` — no andi needed (it's a shift pair, but t already holds that value). f1 folded because cse knows the expression.

OK, let me think about the dead-reset C0414 again but in reverse: the trick invalidates a cse *equivalence* with a dead set that flow deletes. Here the knowledge is a jump equivalence (t == 5). Does a dead set `t = 0;` delete... it changes the value. But what if we set t = 0 and then set t = 5? Two sets: `t = 0; t = 5;` — the compiler folds to t = 5 and knows t==5.

What if we do `t = 0;` and then use a DIFFERENT variable that the compiler knows is 5 from... no.

Hmm, what about: make the t!=3 test come before the t==5 test in the CFG but after in the source? Like:

```
if (t == 3) goto sel_054;
if (t != 3) {           // this is the test, but it's before the t==5 test
    if (t == 5) { ... }
}
```
No — then `t != 3` is known false when t==3.

Alternatively:
```
if (t == 5) {
    ...
}
```
The compiler knows t==5 only on the fall-through. What if we structure so the t!=3 test is on the *taken* path of the t==5 branch? E.g.:

```
if (t != 5) goto after;
if (t != 3) goto sel_094;
```
Same knowledge.

What if the t==5 test is `if (t != 5) { ... } else { if (t != 3) ... }` — same.

The knowledge is inherent to the branch.

Hmm, so maybe the target is unreachable lever-free: wall `flow-known-value`.

But wait — g1 scored 1! That means the compare `a1 != 3` produced the right branch with only a register difference. Maybe a different *spelling* of the compare on a1 would make gcc use s0... no, s0 holds t.

Hmm, actually — hold on. In g1, the compare is `bne s1,v1` where s1 = a1. Target `bne s0,v1` where s0 = t. Could we make the compiler *copy* t into a1's register? No.

What if we write `if (a1 != 3)` but with a1 in a way that... no.

Let me reconsider: maybe there's a spelling that compares `t` but where cse's jump equivalence is invalidated because the comparison happens in a different basic block. The t==5 branch's fall-through is in the same EBB. To split, we need a LABEL that survives to cse. cse runs after jump1. A label survives jump1 if there's a real jump to it. 

What creates a surviving label with zero runtime cost? A conditional branch whose two paths converge and are identical — the optimizer might merge. Hmm.

What about a `switch` on another variable with all cases identical? The compiler might keep the jump table (bad).

What about a loop that runs exactly once with a runtime condition:
```
while (s1) { ... break; }
```
The condition s1 is runtime → the loop and label survive? g2 (empty do-while) didn't. Let me test a `while (s1) { if (t != 3) goto sel_094; break; }` — hmm, that changes control flow: if s1 is 0, the test is skipped! Not equivalent.

What about `if (s1) { if (t != 3) goto sel_094; } else { if (t != 3) goto sel_094; }` — both arms identical → compiler merges.

What about `if (s1) { if (t != 3) goto sel_094; }` — if s1==0, skips the test. Not equivalent.

Hmm, what about an always-true runtime condition that the compiler can't prove: e.g. `if (mode != -1)`? mode is a runtime value; not always true. No.

What about `if (t == t)`? folds.

What about `if (t >= -0x8000)`? t is s16 → always true; the compiler knows? Maybe not! t is s16, so t >= -32768 is always true. If the compiler doesn't fold it, it emits a branch — extra insn.

Hmm.

Let me consider: maybe the register difference in g1 can be fixed by a different comparison that keeps a1 in s1 but produces the compare on s0... no.

Alternatively: can we make `t`'s register be s1 and a1's be s0? No, the target has t in s0.

OK, let me try one more family: compare `t` against a value loaded from a *variable* that holds 3, where the variable is not known constant to cse. E.g.:

```
s32 three = 3;
...
if (t == three) ...   // first test
...
if (t != three) goto sel_094;
```
cse knows three==3 → folds t!=three. Unless `three` is reassigned somewhere opaque. Hmm, but the target uses `li v1,3` (a constant), so three must be a constant.

Actually! The target has `li v1,3` before the `beq s0,v1` — the constant 3 is materialized because it's used twice. If the source had a variable `three` set to 3, gcc would still fold it to a constant and materialize it once — the same `li v1,3`. And the second test `t != three` would fold (t==5 known). No.

Hmm.

Let me try: compare t against 3 using the `t` value *after a conversion that produces a real SUBREG set*: e.g. declare a `s16 u` and do `u = t;` where u is a different pseudo that gcc might not equate because of the HImode/SImode boundary. Let me test:
j1: `s16 u = t; if (u != 3) goto sel_094;` (u declared before the if? or inside)
j2: `if ((s16)(t + 0) != 3)` — folds.
j3: `if (*(s16*)&t != 3)` — address taken, memory.
j4: `if ((s16)t != 3)` — folds probably.

Hmm.

Actually, wait. Let me reconsider the problem. Maybe instead of keeping the compare, we can produce the same instruction via a different *branch* that the compiler can't fold: the target's `bne s0,v1,71c`. What if we write the source so that the t!=3 test compares t against 3 but the value of t is *not* known because the t==5 test was done on a copy in a different register?

Concretely:
```
if (t == 3) goto sel_054;
{
    s16 v = t;          // v is a copy
    if (v == 5) {       // test the copy; cse equates v and t...
        if (t != 3) ... // cse knows t == v == 5
```
Hmm.

What if the copy is made through a function boundary... no.

What if the t==5 test is done on `a1` (full) and the t!=3 test on `t`?
```
if (a1 == 5) {
    if (t != 3) goto sel_094;
```
Then: cse knows a1==5 on the fall-through, and knows t = (s16)a1, so t = 5? cse might derive that (sign_extend of the low half of a known 5) = 5. Possibly it folds. But the target's branch is `bne s0,v0` (t vs 5), not `bne a1reg,v0`. So the t==5 test must compare t. Hmm.

But wait — what if we write `if (t == 5)` but ensure the *value* of a1 is used... no.

OK. Let me look at the actual wall tag candidates. moves.md has `flow-known-value` (G22): "a redundant test on a known value is folded away; target keeps it". That's exactly this. And the entry says "a (cc&0xFFFF) mask keeps it but costs 1 andi (best 10)". So it's a known wall family.

But our case is slightly different: we got to score 1 with `a1 != 3` — the branch structure matched. The remaining issue is just the register of the compared operand. Hmm, that's tantalizing.

What if we compare `t` against 3 but make t's value come from a fresh `sra` in s0 that cse can't fold? I.e., recompute t from a1 right before the test: `t = (s16)a1;` — f5 scored 4 (folded). Hmm, because cse knows (s16)a1 == 5.

But g1 shows cse does NOT know a1's full value. So: compute t from a1 in a way that's a fresh sra but where cse can't derive 5? Any (s16)a1 computation IS 5 known.

Unless we compute t from a *wider* value that cse can't resolve: e.g., `t = (s16)(a1 & 0xFFFF)` — cse knows a1&0xFFFF == 5? It knows (s16)a1 == 5, which implies low16 == 5. Would cse derive that? Maybe not! Let me test `t = (s16)(a1 & 0xFFFF); if (t != 3)`. But this adds an `andi`... unless gcc simplifies `(s16)(a1 & 0xFFFF)` to `(s16)a1`? Hmm, `a1 & 0xFFFF` then sign-extend — gcc might see the andi is redundant for the s16 conversion? Actually `(s16)(a1 & 0xFFFF)` == `(s16)a1` — gcc's simplify might do it.

What about `t = (s16)((a1 << 16) >> 16);`? gcc simplifies to (s16)a1.

Hmm.

What about computing t from `a1` via a `u16` variable: `u16 w = a1; t = (s16)w;`? gcc may equate.

Let me just test a batch j.

Also, maybe try comparing `t` with a comparison against a variable `three` that is computed from `a1` in a way cse can't fold: e.g. `s32 three = (a1 - a1) + 3;` folds.

Let me test j1-j6 quickly, then decide on a wall.

Time check: item 2 started ~08:12, now ~08:35? That's 23 min. I should wrap up soon. Let me do one more batch (6 candidates) and then decide.

j1: `u16 w = (u16)a1; if ((s16)w != 3)` — hmm, but the test is inside the t==5 block. Let me phrase: insert `t = (s16)(u16)a1;` before the test.
j2: `if ((s16)(a1 & 0xFFFF) != 3) goto sel_094;`
j3: `s16 u = (s16)a1; if (u != 3)` — insert u = (s16)a1 before the test (not t).
j4: `if ((t ^ (a1 & 0)) != 3)` — folds.
j5: compare t against 3 where the t value is reloaded from a `s16` variable `idx`? no.

Hmm, what about: `if ((s16)a1 != 3)` folded (f1). But `if ((s16)(a1 & 0xFFFF) != 3)` might not fold.

Let me test j1: `t = (s16)(a1 & 0xFFFF);` + old; j2: `if ((s16)(a1 & 0xFFFF) != 3) { goto sel_094; }`; j3: `{ s16 u = (s16)a1; if (u != 3) { goto sel_094; } }`; j4: `if ((s16)(a1 + 0) != 3)`.

Actually — another idea! What about comparing `t` to 3 via the *first* test's equivalence: the first test is `if (t == 3) goto sel_054`. What if we make the second test reuse the same comparison by restructuring:

```
if (t == 3) goto sel_054;
if (t == 5) {
    goto sel_094;
sel_054:
    ...
```
The compiler emits `j sel_094` (g6/f?). The target emits `bne t,3,sel_094`. Since `bne t,3,sel_094` is equivalent to "if t != 3 goto sel_094" and t is known 5, it's a `j`. Only a conditional that's not known produces it.

OK let me also consider: what if the t==5 branch is a *switch* case and the t!=3 test is inside? Same.

Let me run j batch.
