---
ts: 2026-11-06T15:39:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jr3BLBtzptysDJ2do9XQ
---
Interesting: with the two-step, the second computation at 96 is missing (mine has `subu s5,v1,v0` then nothing, target has the recompute at 96). Wait, mine[94:96] vs target[94:97]: mine has sll + subu; target has sll + subu + sll. So the recompute is still folded in c1 too. And rem went to s5 instead of s6 (register shift).

Hmm. So cse still folds.

Let me look at the cse dump for the orig to see the actual insns. But maybe a better approach: think about what the launder does at the RTL: `(set n (asm ...))`. The n pseudo becomes opaque. The expression `d - n*128` before and after are different because n is redefined.

So I need a real second set of n. What real C statement redefines n with the same value and emits nothing? 

Idea: assign n from `t` again: `n = t;`? t has been modified (negated) — not the same.

Idea: save n in another variable first: 
```
s32 n2;
n = t;
n2 = n;      // n2 = n
rem = d - n * 128;
n = n2;      // second set of n, same value
if ((d - n * 128) < 0) rem = -rem;
```
At the tree level, `n = n2` where n2 = n: copy propagation would replace n2 with n, giving `n = n` → deleted. Hmm, unless the tree-level copy prop doesn't happen (gcc 2.7.2's tree optimizations are weak; the RTL passes do copy prop). cse would see `(set n2 n)`, `(set n n2)` → `(set n n)` deleted.

Hmm.

What if the second set is conditional, e.g.:
```
if (0) { n = 0; }
```
flow deletes.

What about `n = n & 0x7FFFFFFF;`? Not value-preserving in general.

Hmm, what about `n` being s32 and the assignment `n = (s32)t;`? Same.

Let me think about the "real 2nd set" that emits nothing in the earlier cracks: func_8017D73C "n = (s16)n at both sites (a real 2nd set, value-preserving for n in {16,20})" — the s16 cast was a no-op because the value was known to be small. Here n's value is unknown, so the cast emits code.

Is there any known-value range for n? d = unk102 - unk100. Let me check the struct types. In the TU, Unkstruct_800B5CB8's unk100/unk102 fields — likely s16 or u16. If d is s16-range, then t = d/128 is in [-256, 255], so n fits in s16! Then `n = (s16)n` should be free... but b1 emitted sll/sra. That means gcc doesn't know.

Wait, if unk102/unk100 are s16 fields, d = (s32)unk102 - unk100, range [-65535, 65535], t = d/128 ∈ [-511, 511] — fits s16, but gcc's range analysis in 2.7.2 is limited.

What about using a *value-known* cast: since t = d / 128 and d is bounded... gcc doesn't know.

Hmm, what about the assignment order: `n = t;` — what if we declare n as s16 from the start? Then `rem = d - n * 128` with n s16: the multiply promotes n to int (sll after sign-extend). The target's `sll v0,a0,7` (a0 = n) suggests n is in a register without sign extension at the multiply. If n were s16, gcc would sign-extend first (sll 16/sra 16) then sll 7 → combined sll16/sra9 (as b1 showed). Target has plain sll 7. So n is SImode.

OK so what real 2nd set of an SImode variable emits nothing?

The dead-reset trick: `n = 0;` after the last use of n? But n is used in the test after. What if we *reorder*: compute the test's expression first, then rem?

```
n = t;
if (t < 0) t = -t;
if ((d - n * 128) < 0) { ... }   // test uses n
rem = d - n * 128;               // rem computed after
if (...) rem = -rem;             // needs the test result
```
Hmm, we could restructure:
```
n = t;
if (t < 0) t = -t;
{
    s32 r = d - n * 128;    // compute once
    rem = r;
    if (r < 0) rem = -r;
}
```
That's the plain form; cse folds.

What about making the second computation use a *dead-reset* of the expression: e.g. after `rem = d - n*128`, insert `n = 0;` and then restore `n = t;`? But t has been negated. Save: 
```
n = t;
if (t < 0) t = -t;
{
    s32 nn = n;
    rem = d - n * 128;
    n = 0;
    n = nn;          // second set of n from a saved copy
    if ((d - n * 128) < 0) rem = -rem;
}
```
Hmm, `n = nn` where nn = n: copy prop → `n = n`. But the intervening `n = 0` makes `n = nn` a real set (not `n = n` after propagation? The propagator replaces nn with n only if nn's value is known to be n's current value; after n = 0, nn ≠ n, so nn stays). So `n = nn` is a real 2nd set of n. And it's a `move` instruction (n = nn) — target doesn't have that... unless reg-alloc coalesces nn into the same register as n! If nn is assigned to the same hard reg as n, the move becomes `move a0,a0` → deleted by dbr/peephole? Possibly.

Hmm, risky. But wait: the target's n is in a0 (move a0,s1 at 92). If nn also lives in a0, `move a0,a0` might be removed by the delayed-branch pass or peephole. Then the RTL set of n remains for cse purposes.

Actually, hmm: n's value after `n = nn` is opaque to cse only if cse can't see nn ≡ n. After `n = 0; n = nn;` cse: `(set n 0)` invalidates n; `(set n nn)` — nn's value is the old n (a different reg), so n ≡ nn, but the expression `d - n*128`... cse's table has nn's value as the old n (a register), not the expression. So `(mult n 128)` after `n = nn` is not known to equal the old `(mult n 128)` — actually cse's fold_rtx could substitute nn for n (they're equivalent) → `(mult nn 128)`; was `(mult nn 128)` in the table? No, the table had `(mult n 128)`. So no fold! Then the recompute happens.

This is getting complicated. Let me consider the simpler route: maybe the C0414 dead-reset directly: the cse table's expression is `(minus d (mult n 128))`. If we invalidate `d` or `n` between, the fold dies. Since we can't change their values, a dead store to a *different* variable doesn't invalidate. 

Wait, actually: `invalidate(d)` happens on any store to memory that might alias d? d is a local (register). No.

Hmm, what about using a different variable for `d` in the test? `if (((unk102 - unk100) - n*128) < 0)` — recomputing d from memory loads! That would change codegen (extra loads).

OK, let me look at the actual C source's intent: the target recomputes `d - n*128`. Perhaps the original source was:

```
rem = d - n * 128;
if ((d - n * 128) < 0) rem = -rem;
```
Yes, that's what we have.

Alternatively the original might have been:
```
rem = d % 128;   // no
```

Hmm. Since the launder exists, the original (pre-delever) code had the asm, and the lever-free body must find real C.

Let me look at the moves list for a similar "dead re-test" crack: "func_8017D9D8 MATCH: the launder (tied output + m(pad)) -> do { } while (0) + v0 = (s16)v0 (a real 2nd set)". Also "func_8017D73C MATCH: n = (s16)n".

What if the *value* of n is known small enough for a u16 cast but gcc emits andi? b2 gave exactly one extra andi. If instead of `n = (u16)n` we could make the andi fold into the multiply: `(n & 0xFFFF) << 7` = `(n << 7) & 0xFFFF80`? No.

What about `n = (u16)n;` where the andi is combined with the sll by combine? b2's diff showed `andi a0,a0,0xffff` extra at 96 and then presumably `sll v0,a0,7`. Combine could turn `(and a0 0xffff)` then `(mult a0 128)` into `(and (mult a0 128) 0x7fff80)`, not fewer insns.

Hmm, what if we use `n = n & 0xFFFF;` but then the *first* use too? The target's first computation `sll v0,a0,7` with a0=n. If n were masked, the first sll would also need the andi... 

Let me step back: maybe the answer is that n's second set can be a *store to a local variable* — no, that adds sw/lw.

What about `n = t;` then `t = t;`... no.

New idea: use the `do{}while(0)` trick differently: put the *rem computation* in its own block and the test in another, so cse's EBB splits and the table is cleared. b3 wrapped the test in a do-while → score 52 (bad, because the do-while creates a loop structure affecting the whole function? or the block split changed register allocation). Hmm, 52 is bad.

What about wrapping just the rem computation: 
```
do { rem = d - n * 128; } while (0);
if ((d - n * 128) < 0) ...
```
Then the test is in the outer block; cse processes the do-while body as a separate block and then continues? cse1 processes EBBs; a do-while's body is a block with a label; the test after is in the outer block. The cse table from the body doesn't propagate to the test's block. So the test would recompute!

But would the do-while add any instructions? `do { rem = ...; } while (0);` — the `while(0)` is constant, gcc removes the branch. It might leave a label/note only. The func_80181F4C win.c used exactly `do { r = p + i; } while (0);` as a legitimate move.

Let me test that: d1 = wrap rem computation in do-while.

Also d2 = `do { rem = d - n*128; } while (0);` with the test outside.

Let me try.
