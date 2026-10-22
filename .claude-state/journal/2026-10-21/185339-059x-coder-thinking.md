---
ts: 2026-10-22T00:53:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_K1RfNN9rIc8SZLRBdTXl
---
Interesting: vH (literal `return 1`) gives the SAME shape as vA: the const temp in v0 ($2) and `li v0,1` at the return block. So gcc 2.7.2 (with -O2) puts the `li v0,1` in the merged return block, and the const temp got $2 because $2 was free during the compares.

Wait, but if the `li v0,1` is in the merged return block, then during the compare chain $2 is free → the const temp takes $2 ✓ consistent.

Hmm interesting: so even with the literal, gcc created the "return 1" block.

Now — the ROM has the li EARLY. What if the source computes the value 1 EARLY and the returns are literals? Then the early set would be dead (folded).

OK, let me try to think about what gcc construct yields "set $2=1 early, then branches to jr ra".

Alternative: what if the ROM's source used a variable that gcc assigned to $2 for a DIFFERENT reason: e.g. the variable is the second parameter... no.

Hmm, hold on! What about this: the target's ins 23 `li v0,1` — what if it's NOT the result but a *loop/branch* artifact? E.g., what if the source is:

```
if (arg2 == 9) return 1;
```
and gcc generated for the FIRST return: `beq a2,v1,+0x94` with `li v0,1` in the delay slot, and the return block at +0x94 is just `jr ra` — i.e., gcc decided the value 1 is already in $2 (from the delay slot) — that's the classic gcc 2.7.2 MIPS pattern for `return 1` inside a conditional! I recall gcc 2.7.2 generates:

```
   li $2,1        <- in the delay slot of the branch
   ...
   jr $ra
```
Hmm, specifically for:
```
if (x) return 1;
```
gcc 2.7.2 -O2 typically generates:
```
   beqz a0, L1
   move v0,zero    (delay slot, for the else path)
L1:
   li v0,1
   jr ra
```
Hmm, that's the standard shape. But if the "return 1" block is merged with other returns...

But here's the thing: in the target, FOUR branches jump to the same `jr ra` and the `li v0,1` is in the delay slot of the FIRST branch. For that to be correct, all four paths must have $2=1. Since ins 23 executes on all paths (it's the delay slot of ins 22 and ins 24-29 are after it), it works ✓. But gcc must know that the value is 1 on all paths reaching the merged return block.

For gcc to place the `li $2,1` in ins 23's delay slot, the set must be in the fall-through block before the branch — i.e. the RTL order was: [set $2 = 1] [beq ...] and the scheduler moved the set into the delay slot. But the set must dominate all four branches → the set is before ins 21 (the first compare). So the source computed 1 before the compares ✓ (as in orig.c with the pinned v0).

So gcc 2.7.2 DID keep the early set — with the pin. Without the pin, gcc folded.

Hmm, so what if the difference is not the fold but the ALLOCATION: maybe without the pin, gcc keeps the early set but allocates the const temp to $2 and the result to $3? No — mine shows `li v0,9` (const in $2) and `li v0,1` at the return block ($2) — the same reg $2 for both, sequentially. So the early set is gone (folded) in mine.

Hmm OK. So how about making the early set survive by preventing the fold? One classic way: make the value's set and use be in the same basic block... no, they're not.

WAIT. What about gcc 2.7.2's handling of `return` inside a block where the RESULT_DECL is set once? Consider this source shape:

```
s32 res;
res = 1;
if (arg2 == 9) return res;
...
```
RTL (gcc 2.7.2):
```
res.2 = 1
if (arg2 == 9) goto L1
...
L1: return res.2
```
where "return res.2" = `move RESULT_DECL, res.2`.

Now combine: it processes the insns. The set `res.2 = 1` is a constant set; the use is in a copy. gcc 2.7.2's combine has a specific optimization: "If we are copying a constant to a pseudo and the pseudo is dead afterwards, ...". Hmm, there's `simplify_const_copy`.

But crucially, combine 2.7.2 processes instructions in order and the RTL list order matters: the set comes BEFORE the copy in the list, so combine sees the set first, then the copy. When it reaches the copy `move RESULT_DECL, res.2` with res.2 known to be 1 (from the set), combine does "copy_const" → replaces the copy with `move RESULT_DECL, 1` and deletes the set of res.2 (if res.2 is dead). This is standard.

BUT: gcc 2.7.2's combine has a restriction on deleting the set: it won't delete an insn if the reg is used "across a call" or if the set is in a different block and there's a jump in between? Combine in 2.7.2 works within basic blocks for most optimizations? No — combine works on the whole function but many of its transformations require the same basic block.

Hmm! Actually yes: gcc 2.7.2's combine has `if (insn's block != set's block) skip` for many cases. Specifically, in combine.c, `combine` handles a copy `move dst, src` where src is a reg set in ANOTHER block: the "copy_const" optimization is done in `simplify_const_copy` or in the main loop's `case PLUS_EXPR`... Hmm.

Empirically: mine folded it, and the set was in the same block as the compares (the `v0 = 1` is inside the `if ((*(s16*)(arg1+0xAE) & arg3) == 0) {` block, and the first `return v0` is in a nested block inside it). So the set is in the parent block and the copy is in a child block (different basic blocks) — and gcc still folded it (constant propagation across blocks is done by cse, which handles cross-block propagation of constants! cse's "global cse" pass propagates constants across blocks within a function, and it also handles "jump threading").

Hmm, so cse (not combine) does the cross-block constant propagation. gcc 2.7.2's cse.c has "propagate_const" — it propagates a constant into a register's uses across the whole function if the reg is set to a constant and never modified... but cse's global CSE only propagates within "the same basic block" for registers? No: cse.c's `propagate_const` handles constants set in one block and used in another (it's the "global_cse" pass with `cse_class`...). Hmm, in gcc 2.7.2, cse.c does have a "propagate_const" that works across blocks when the reg is not modified in between (it uses the "reg_equivs" and the "cse_basic_block" pass). Actually, the relevant one: cse.c's `cse_basic_block` does per-block; but there's also "propagate_const" in cse.c that handles "EQV" and constants.

And the notes for the previous coder said: "gcc 2.7.2 folds the constant 1 into the return copies (combine), so the v0 pseudo dies".

Hmm. So combine does it. In gcc 2.7.2's combine.c there's:

```
	  /* If this is a copy of a constant into a register, ... */
```
Specifically, combine's `simplify_const_copy (reg, const_rtx)`? Hmm. Also, combine's main loop has:

```
	    case REG:
	      ...
	      /* If this insn is a copy of a constant, ... */
```
There's `reg_or_mem`? I'm not certain.

OK, empirical approach: let me try to construct variants that might avoid the cross-block fold:

Variant A: Put the `v0 = 1` INSIDE the same basic block as the first return? Not possible (the return is in a nested if).

Variant B: Restructure so that the value 1 is set and used in the SAME block: e.g.
```
if (arg2 == 9) { v0 = 1; return v0; }
```
→ then the set is in the return block → `li v0,1` right before the jump — that's the folded shape anyway.

Variant C: Set the value in the block and use it in the SAME block via a fall-through:
```
v0 = 1;
if (arg2 == 9) goto ret1;   /* not expressible in C directly */
```

Variant D: Make the FIRST compare's return path fall through to a block where v0 is used:
```
v0 = 1;
if (arg2 == 9) return v0;   /* the copy is in a different block */
```

Hmm.

Variant E (promising!): What if the value 1 is set via a computation involving the const temp such that gcc keeps it as a copy? e.g.
```
v0 = 1;
```
Hmm.

Variant F: What if the early value is 1 but stored in a variable that ALSO gets modified in a way that keeps two sets? e.g.
```
v0 = 1;
if (cond) v0 = 1;    /* two sets of the same value */
```
Then cse would merge the two sets (same value) → one set. Hmm, but cse merging happens after the fold? The fold (combine) needs a single set. With two sets, combine can't propagate the constant into the copies → the copies remain `move RESULT_DECL, v0` → then the allocation: v0 gets a register (say $2) and the copies are coalesced with RESULT_DECL ($2) → the copies vanish → and the two sets of v0 = 1 → cse merges them into ONE `li $2,1`?? But there'd be two sets at different points: the early one (before the compares) and the one in the `if (cond)` block. The ROM has only ONE `li v0,1`. Hmm, but if the second set is dead (the `if (cond)` block never executes or its value is the same)... cse would eliminate the redundant set if v0's value is provably the same → cse removes the second set (redundant) → one set remains ✓!!

So Variant F could work:
```
v0 = 1;
if (arg2 == v1) { v0 = 1; return v0; }   /* hmm, the extra set is in a different block */
```
Hmm, but then the extra set's block might not be eliminated, adding an instruction.

Hmm, this is getting deep. Let me instead consider the ACTUAL likely source of the ROM. The ROM was compiled from the ORIGINAL PsyQ source (decomp of the game). The original source probably had something like:

```
int func_8014C308(int arg0, int arg1, int arg2, int arg3) {
    int v0;
    int v1;
    ...
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
    ...
}
```
and the game's compiler produced the target. The game's compiler is gcc 2.7.2 (same toolchain as ours!) with the same flags. So a lever-free version of the same source SHOULD produce the same code... but the difference is that the game's source had a LOCAL variable `v0` (no pin), and our source has the pin `register s32 v0 __asm__("$2")`.

Wait — the game's source didn't have a pin! It just had `int v0;`. And the ROM shows v0 in $2. So gcc 2.7.2 with a plain local DID put it in $2 and kept the early set!

So why doesn't OUR compiler do the same? Because... hmm! Maybe because of how the source is spelled differently (the decompiled source uses casts, `*(u16*)((u8*)arg1+0)`, etc.), but that shouldn't matter for allocation.

OR because the pin was needed to reproduce it, and the decompiler added the pin after finding a mismatch. The notes say "pin $2 — NEEDED DIFFERS (P36 rung B headers1)" — so the pin was added because the plain version differed.

Hmm, so with the game's source spelling (which we don't have exactly), gcc put v0 in $2 and kept the early set. Our lever-free spelling differs somewhere.

What differs? Possibly the ORDER of the declarations, or the exact expressions. The key: for gcc to keep the early set, the set must not be folded...

Hmm! What if the game's source was:
```
if (arg2 == v1) return v0;
```
where v0 was assigned `v0 = 1;` — and gcc's cse/combine folded it in OUR spelling but not in the game's, because of the difference in the EXPRESSIONS? E.g. in the game's source, the four compares might have been `if (arg2 == v1)` where v1 is a variable (as in orig.c) — and the four `return v0` — same as ours.

Alternatively, maybe the game's source had the value 1 assigned in a place where it's also USED elsewhere — e.g. the value might be used in the final `return` too.

Let me look at the target's tail again: ins 31 `lw v0,376(a0)`, 33 `xor v0,v0,a1`, 34 `j 6abc`, 35 `sltu v0,zero,v0` — the final path returns (x != arg1). So the final path's value is a comparison, not 1.

Hmm OK.

Let me look at this from yet another angle: maybe the pin is not what makes the difference; maybe our source's OTHER differences (the cast spellings) matter. Let me test the hypothesis: take orig.c and remove ONLY the pin (that's nopin.c) → score? The notes say nopin = 9 with 40 ins. Interesting! nopin gives 40 ins (vs target 39) and score 9, while vA (const temp as separate var, v0 = 1 before compares) gives 41 ins and score 17.

So nopin (which keeps the v1 const temp variable and the `v0 = 1` early) is much closer: 40 ins, score 9! Let me look at nopin's diff — that's the most promising base.

Let me score nopin and see the diff.
