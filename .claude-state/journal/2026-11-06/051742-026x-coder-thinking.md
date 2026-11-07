---
ts: 2026-11-06T12:17:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nYj5lCoqwdKXb9nVuTGr
---
Hmm, same as a1. `a1v = arg1 & 1` got computed into v0 from t4 (the arg1 copy). So gcc still copied arg1 to t4 and computed the andi from it into v0. Because combine? Actually `a1v` was a separate pseudo, and gcc allocated arg1 copy to t4, a1v to v0.

Wait, but a1v is used once in the branch. gcc didn't fold the andi into the test? It did `andi v0,t4,1` then bnez v0. In target `andi a1,a1,1; bnez a1` — computed in a1.

To force a1v into a1... Hmm.

Alternative approach: what makes gcc put a value in a1? A value that's a parameter passed to a call, or... Actually gcc 2.7.2 local-alloc assigns registers by priority; the a1 register is preferred for pseudos that are "used in a move" etc. Hard.

Think about the target's actual mechanism: the launder's asm forced a1v into a1 AND forced the arg1 copy. The copy t3 was emitted BEFORE the asm (because arg1 needed later). So the sequence: copy arg1 out (t3), then asm output in a1.

Lever-free real C equivalent: we need arg1 to be copied out to a temp and a1v computed in a1. If we write `a1v = arg1 & 1;` the compiler keeps arg1 in a1 and uses a1v in v0 — no copy needed, and the andi is non-destructive to a1.

What if we make arg1 "die" in a1 by having a1v take its register? E.g., a real second set: `arg1 = arg1 & 1`? No, that changes later uses of arg1 (which test 0x8000). Unless we save arg1 first:

```
s32 a1v;
s32 a1save = arg1;      // real copy
a1v = arg1 & 1;
...
if (!a1v) ...
...
if (a1save & 0x8000) ...
if (a1save & 1) ...
```
Then arg1 is used twice (a1save init, a1v init). gcc may coalesce a1save = arg1 and then a1v = arg1&1. Register: arg1 in a1, a1save coalesced (same reg), a1v in v0 → `andi v0,a1,1`. Still no copy. Hmm.

But target's copy is of arg1 into t3 and then a1 is reused for a1v. This is exactly "arg1 dies at a1v's birth". For that, the last use of arg1 must be the andi itself, i.e., no later uses of arg1. But target DOES have later uses of arg1 (the 0x8000/0x1 tests at c98/cdc use t3). So the later uses are of a COPY, made explicitly.

So write:
```
s32 a1s = arg1;       // copy used later
s32 a1v = arg1 & 1;   // last use of arg1
...
if (!a1v)
...
if (a1s & 0x8000)
if (a1s & 1)
```
Then arg1's uses: a1s init (move), a1v andi. gcc could coalesce a1s with arg1 → a1s in a1, then andi from a1 into v0. Still no copy needed since arg1 is the same reg as a1s.

Hmm. The fundamental issue: coalescing.

To prevent coalescing of a1s with arg1, we need a real computation: e.g. a1s = arg1 | 0? No, identity.

What if a1s = (s16) arg1? That's a real computation but changes value; however, the uses are `& 0x8000` and `& 1`, both only depend on low 16 bits. So `(s16) arg1` is semantically equivalent for those uses! And `a1v = arg1 & 1` also only low bit.

But (s16) arg1 emits sll/sra (2 insns), which target doesn't have. Hmm, unless gcc optimizes.

Alternatively, a1v = arg1 & 1 and a1s = arg1 - (arg1 & 1) + (arg1 & 1)? No, too many insns.

Let's reconsider. Maybe a different real-C shape gives the same top sequence. The target top is:
```
move t2,a0
move t3,a1
andi a1,a1,1
bnez a1,b48
move t4,a2     (delay)
```
What if the source computes something with arg1 that ends up in a1, e.g. `arg1 & 1` computed in place. gcc 2.7.2 local-alloc has the notion of "the pseudo prefers a register that dies" — for `andi`, gcc emits `andi dst,src,1`; if dst == src allowed, it can allocate a1v to a1 only if arg1 dies there. arg1 doesn't die if used later.

Unless... the later uses are of a different C variable that gcc copies BEFORE. The order in target: move t3,a1 BEFORE andi a1,a1,1. So the copy happens first, and then arg1 dies at the andi. That's exactly what gcc does when it must copy arg1 out: it inserts the copy at the point of the last use, before it.

So: if I write
```
s32 a1s;
...
a1s = arg1;      /* somewhere before */
...
s32 a1v = arg1 & 1;  /* last use */
```
gcc's copy `a1s = arg1` would be emitted where? At the assignment point, which is before the if. But then arg1 is dead after that copy... and a1v's andi would use... a1s (since arg1 dead, gcc might copy-propagate a1s into arg1). Ugh, copy propagation merges them.

Key: the launder's asm breaks copy propagation: gcc cannot know a1v == arg1. Real C can't break that except via a genuinely different value.

So the real second set: a1v = f(arg1) where f is real, and a1s = arg1 is used later. Then gcc must keep arg1 live for a1s, so arg1 in a1; a1v = f(arg1) in v0 typically. Unless f is computed destructively.

Hmm, what if f is something that gcc emits in place? E.g., `a1v = arg1 & 1` — the AND with a constant is a natural in-place candidate.

Let me look at the actual allocator behavior. gcc 2.7.2 local-alloc: for an insn `(set (reg a1v) (and (reg arg1) 1))`, if arg1 is not dead after, a1v cannot be a1 unless arg1 is copied. The allocator has `reg_renumber` preferences. Actually the "qty" preference: a1v prefers the register of arg1 (because `andi` allows dst==src? that's a 3-operand insn where the destination can be the same). gcc's local-alloc would give a1v the same reg only if arg1 dies (then it's a tie). Since arg1 doesn't die, it can't.

BUT: if arg1's only remaining use is the andi and the copy `a1s = arg1` is placed AFTER the andi (because the compiler decided to copy late)? No, a1s=arg1 must be before arg1's value is destroyed.

Hmm, what if we structure it so the copy a1s = arg1 is placed after the branch, e.g.:

```
if (!(arg1 & 1)) {
   a1s = arg1;   // first use of arg1 after
   ...
}
```
No — the branch arms use arg1's value, but arg1 is a param and can be used after.

Different idea: use the C variable `a1v` for the later tests instead of arg1, and compute it as a real second set from arg1:

```
s32 a1v = arg1 & 1;   // used in first test
...
if (arg1 & 0x8000) ...
```
This is what a2 does: arg1 used later, so no copy... and the andi went to v0 from t4. Wait — but there IS a copy of arg1 to t4 in a2! So gcc DID copy arg1 (to t4) and used t4 for the later tests, then computed andi v0,t4,1. So gcc chose: copy arg1 to t4 (because arg1 used 2+ times later?), then compute a1v in v0 from t4.

Target: copy arg1 to t3, then compute a1v in a1 from a1. The only difference is which reg a1v gets (a1 vs v0) and hence the order (in target the andi is in-place, so the copy must precede it; in mine the copy precedes too).

So how to make a1v land in a1? a1v's live range is tiny (born at andi, dies at bnez). Registers: a1 is free after the copy of arg1 to t4 (arg1's value no longer needed in a1 — but wait, in a2 gcc kept using t4 for later arg1 uses, so a1 is free after the copy). So a1 IS free at a1v's birth. Why did gcc give a1v v0 and not a1? Because local-alloc's priority order: v0 ($2) is also caller-saved and available; the allocation order among available regs depends on qty priority and the order of pseudos.

In target, a1v got a1 because the asm forced it. In real C, we need to influence local-alloc. One lever: the pseudo's "preference" comes from the insn pattern — `andi` in gcc 2.7.2 MIPS: the pattern `(set (match_operand:SI 0 "general_operand" "=d,d") (and:SI (match_operand:SI 1 "general_operand" "dI,i") ...))`? Let me check the machine description. Actually there's a known pattern where andi with a constant that fits unsigned can use `d` class. The allocator might prefer dst = src for `andi`? In gcc 2.7.2, `reg_preferred_class`/`reg_alternate_class` and the copy preference. 

Alternatively, use a variable born in a1 via a different construct: make a1v used in a context that requires a1, e.g., pass it as the first arg to a call? No calls here.

Alternative: maybe the whole a1v thing can be avoided by making the compiler emit `andi a1,a1,1` naturally: write `if (!(arg1 & 1))` and have arg1 dead after... but arg1 is used later.

Hmm, wait. What if the LATER tests use a copy variable that is computed FIRST, e.g.:

```
s32 a1s = arg1;       // copy, coalesced? 
```
No...

What if the later tests use `(s16) arg1`? They'd recompute from a1 each time, keeping arg1 live in a1 — then andi must be v0.

What if arg1's later uses go through a variable assigned from a REAL function of arg1? E.g., a1s = arg1 (needed). The copy exists in target as `move t3,a1`; the value is identical. Any real C copy of a param gets coalesced unless the compiler is forced to materialize it (e.g., because the source variable is used after arg1's register is needed).

Idea: make the copy `a1s = arg1;` be materialized by using a1s as an lvalue that can't coalesce... 

Alternative approach: instead of a1v = arg1 & 1, maybe a1v can be a value that gcc naturally computes in a1. What computations go into a1 by default? Values that are call arguments (a1 is the second arg reg). No calls.

Hmm. Let me look at the original target more carefully: is `andi a1,a1,1` really a1v? Yes since a1v was pinned to $5.

Let me consider: maybe we don't need a1v in a1. Maybe another real-C shape gives score 0 differently. But the top 6 insns must match: move t2,a0; move t3,a1; andi a1,a1,1; bnez a1; move t4,a2.

The andi must be in a1. That requires a value computed in a1 from a1 where the original arg1 value has been copied out. So we need the copy first. The copy of arg1 to t3 exists in the target. In real C, the copy would be of arg1 to a variable that's used later — and gcc must place it before a1 is clobbered.

Wait... what if the copy is not of arg1 but the andi's input is a variable `x` that holds arg1's value and is used later, while `arg1` (the param) is used for the first test? I.e., swap roles: first test uses the param arg1, later tests use a copy `a1s`. Then:

```
s32 a1s = arg1;
if (!(arg1 & 1)) ...
...
if (a1s & 0x8000)
if (a1s & 1)
```
Now arg1's uses: a1s init and the first test. If gcc coalesces a1s into arg1 (a1), then all uses read a1; andi goes to v0. If gcc does NOT coalesce (because...?), then a1s gets t3 and arg1 stays in a1, andi in place into a1. The order: move t3,a1 then andi a1,a1,1 — EXACTLY target!

So the question is whether gcc coalesces a1s with arg1. Since a1s is just a copy of a param used later, gcc's local-alloc might coalesce it (both live ranges overlap? arg1 is live until the first test; a1s is live from its init to the later tests. They overlap, so a1s cannot share a1 with arg1 unless arg1 dies at the copy... arg1 is used after the copy (first test), so they're simultaneously live! Therefore NO coalescing: a1s must get a different register (t3), and arg1 stays in a1. The copy is emitted: move t3,a1. Then andi a1,a1,1 (in place, arg1 dies at that use — last use!). 

That's the key insight: simultaneous liveness prevents coalescing. In a2, I wrote `a1v = arg1 & 1` and used arg1 later — arg1 live through, a1v born later, so a1v could take a1 after the copy... but gcc's allocation chose t4/v0 differently. Here with a1s = arg1 and the first test using arg1 directly, we get the natural shape.

Wait, but in a2 gcc made t4 = copy of arg1 for later uses, and computed andi into v0 — because arg1 was still the input at the andi, so it couldn't overwrite a1... but it could have if it did the copy first (it did: move t4,a1 came first!). Hmm, but that copy was gcc's own insertion, not tied to a C copy.

Let's just try the swap shape. New a3.c:

```
s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
    ...
    s32 a1s = arg1;   /* copy used by the later tests */
    s32 pos = arg2;
    ...
    if (!(arg1 & 1)) { ... }
    ...
    if (a1s & 0x8000) { ... }
    ...
    if (a1s & 1) { ... }
```

Wait, but careful: the original later tests are `arg1 & 0x8000` and `arg1 & 1`. Using a1s = arg1 is identical.

But there's a subtlety: is a1s live across the whole function? Yes, from the init to the last test. That's a long live range — target keeps it in t3 throughout (caller-saved, fine).

Also arg1 is live only until the first test. Good.

Now pos = arg2. Target move t4,a2 in the bnez delay slot. In a2, pos took t3 (because arg1's copy took t4). With a1s taking t3, pos should take t4.

Let me also reconsider `(s16) arg2` uses: `(s16) arg2` appears in the branch. gcc emits sll/sra from a2 (target: sll v0,a2,0x10; sra v0,v0,0x10 at b18/b24). Fine.

Let me write a3.c.
