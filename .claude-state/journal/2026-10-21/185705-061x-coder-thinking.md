---
ts: 2026-10-22T00:57:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_xWiQm4yCGzqOHR141f09
---
All 16-17. The fold is robust.

Interesting: vN7 (goto) = 16 (slightly better). Let me look at the goto diff to see the shape.

Let me think about what else could work. Key insight needed: get an early `li $2,1` with the const temp in $3.

Alternative approach: what if the ROM's shape can be produced by a DIFFERENT decomposition: e.g. the "1" could be the result of `(s32)(x != 0)` where x is... no.

Let me reconsider: maybe I should attack it from the "which register gets what" angle: the const temp is $3. In the lever-free compile, the const temp is $2. What if we make the const temp a variable that gcc will NOT want to put in $2 — e.g. if the const temp is USED as a call argument or has a high priority?

Hmm, in the target the const temp (v1) is used for 4 compares AND for the (u16)arg3 mask (ins 18 `andi v1,a3,0xffff`). So v1 is a general temp.

In our compile, v1 got... hmm, in mine the const temp got $2 and the mask temp got? Let me look at mine's earlier instructions (ins 0-19) to see. The diff showed only ins 2,6,10,15,20+ differing — so mine[0:20] == target[0:20] except those. So mine's `andi v1,a3,0xffff` (ins 18) matched ✓ — so in mine, v1 = $3 for the mask temp, and the const temp (9/17/41/10) got $2?! That means gcc used TWO different pseudos: the mask temp in $3 and the const temp in $2.

In the target, BOTH the mask temp and the const temp are in $3 (the same reg $3 reused). So in the target, the const temp and the mask temp are the SAME pseudo (or two pseudos that share $3 because their live ranges don't overlap).

In mine, the const temp is in $2 (allocated early, priority) and the mask temp in $3.

So if I could make the const temp's pseudo be the SAME variable as the mask temp (v1), then... hmm, in orig.c the mask is `(u16)arg3` — an expression, not a variable. And the const temp is the variable v1.

So: the target uses v1 for both the (u16) cast temp and the constants. If I make the (u16) cast use the SAME variable v1:
```
v1 = (u16)arg3;
if ((*(s16*)(arg1+0xAE) & v1) == 0) { ... }
```
then v1 is one pseudo with 5 sets (mask + 4 constants) → it would get one register, and if that register is $3 ✓ then the const temp is in $3 ✓ and $2 is free for the result value... but the result value's set is folded, so $2 would be taken by... hmm, in the target $2 holds the RESULT_DECL (early set). In our compile, if the const temp is in $3, then $2 is free during the compares → the RESULT_DECL would get $2 at the return block, and the code would be 41 ins with the difference being the position of the `li v0,1` and the branch targets.

Wait, that changes the diff! Let me reconsider: the score is the number of differing instructions. Currently 17. If the const temp moves to $3, the diff would show the const loads matching (4 of them) but the `li v0,1` position would still differ.

Hmm, but the real problem is the early `li v0,1`.

Let me think about how to get the RESULT_DECL set early... The RESULT_DECL is set at the return statements. For an early set, the return must be in a block that's reached... hmm, the RESULT_DECL's set is at the return block, which is after the branches. The only way to have it early is if the value 1 is computed early and copied (coalesced).

So the crux remains: prevent the constant fold.

Hmm, let me look at gcc 2.7.2's cse.c propagate_const behavior: it propagates a constant into a use if the reg was set to that constant and the use is in the same "basic block" OR ... In gcc 2.7.2's cse.c, `propagate_const` handles "the reg is set to a constant in this block and used in this block". The GLOBAL cse pass (`cse_basic_block`) works per basic block, but the "global_cse" file-level pass handles cross-block. Hmm, in gcc 2.7.2, cse.c has:

- `cse_basic_block (scan_insn)` — per block.
- `propagate_const (reg, orig_rtx, eqv)` — "Propagate a constant into the uses of a register" — it's called from cse_basic_block when it finds a set of a constant: it walks FORWARD through the RTL (across blocks!) replacing uses with the constant, as long as the reg isn't set again. This is the cross-block propagation ✓. So the fold happens across blocks ✓ (consistent with our observation).

In `propagate_const`, gcc 2.7.2 has a check:
```
  /* If we are in a basic block that is not the same as the one where the
     register was set, ... */
```
Hmm, and importantly: propagate_const STOPS at certain insns (e.g. calls that clobber, or "NOTE" boundaries?). Let me recall gcc 2.7.2's propagate_const:

```
static int
propagate_const (reg, orig_rtx, eqv)
{
  ...
  for (insn = first_insn; insn; insn = next_insn)
    {
      ...
      if (insn == NOTE) continue;
      if (REGNO (SET_SRC (set)) == reg) ... 
```
Hmm, in 2.7.2 propagate_const is:

```
/* If we are propagating a register value, we need to know ... */
static int
propagate_const (reg, orig_rtx, eqv)
{
  rtx copy_rtx;
  rtx insn;
  int sets_p;
  ...
  sets_p = propagate_one (orig_rtx, eqv, reg, REGNO (reg), ...);
```
I'm fuzzy. But importantly, in gcc 2.7.2's `propagate_one`, there's a check:

```
      /* If we find a set of the register, we can't propagate any further.  */
      ...
      /* Don't propagate into a call that clobbers the register.  */
```
and importantly:
```
      if (INSN_P (insn) && GET_CODE (insn) == CALL_INSN && ...)
```
Also:
```
      /* Don't propagate past a branch that might not be taken?? */
```
Hmm! Actually I recall gcc 2.7.2's propagate_one does NOT propagate across a "jump" incorrectly... but it does handle blocks.

OK, empiricism. Since the fold happens, maybe I can DEFEAT it by putting a CALL between the set and the use? A call clobbers registers → propagate stops at the call ✓!! But a call would add instructions (jal + delay slot) ✗ — the ROM has no calls in this function.

What about a VOLATILE access? `volatile` reads/writes would stop propagation but add instructions.

Hmm, what if the set is followed by a use in a different block reached via a branch — propagate_const in gcc 2.7.2 might stop at a branch if the value isn't guaranteed? Hmm, if propagate_const stopped at branches, our fold wouldn't happen (the use is in a different block).

Wait — is the use really in a different block? The set `v0 = 1` is in block B (the mask-test block), and the first use (`return v0` → copy) is in a nested block (a child of B). Different blocks ✓. So propagate_const DOES cross blocks in 2.7.2.

Hmm, so what stops propagate_const? In gcc 2.7.2's cse.c propagate_one:

```
      /* If we find a set of the register, ... */
      ...
      /* If this insn is a call, ... */
      ...
      /* Don't propagate into insns that are jumped over?? */
```

I recall there IS a rule about "sets_p" and "the value is not live on some path". gcc 2.7.2's propagate_const had a bug/limitation with conditional paths — it only propagates if the reg is set on ALL paths to the use? No, it just walks the RTL linearly.

Since the RTL is a linear list with labels, walking linearly from the set to the use covers only ONE path; if the set is in a block and the use is in a nested block, the linear walk passes through the branch → the propagation continues into the target block ✓ (and also into the fall-through path, incorrectly!). gcc 2.7.2's cse handles this by "cse_class" and the "global_cse" file pass.

Anyway. Empirically the fold happens.

NEW ANGLE: What if I make the value's USE be in the SAME basic block as the set? Then propagate_const would fold it even more surely. Opposite.

NEW ANGLE 2: What if the value 1 is set in a block that is NOT on the linear path to the use? E.g. the set is in a block that jumps to the use block, while the linear order goes through other blocks. propagate_const walks linearly from the set's position: if the use is reached via a jump, the linear walk may still find it (the RTL list order is roughly the block order).

Hmm! What if the set is placed in a block that comes LATER in the RTL list than the use? Not possible (dominance).

NEW ANGLE 3: Make the value's set NOT a constant but a copy from a pseudo that is set to a constant IN A DIFFERENT BLOCK that's not on the linear path... no.

NEW ANGLE 4: **Use a `volatile` free trick: the `&` of a variable.** no.

NEW ANGLE 5 (promising!): What if the value is set via an assignment whose RHS is a CONSTANT EXPRESSION INVOLVING A PARAMETER THAT GCC CANNOT FOLD but whose VALUE at runtime is 1 — specifically the (u16) mask trick!

Look: the ROM computes `andi v1,a3,0xffff` then `and v0,v0,v1` then `bnez v0,+0x90`. What if the source's "1" is actually derived from... no, `li v0,1` is a literal 1.

NEW ANGLE 6: What if the source sets the result variable to 1 using an expression like `v0 = (s32)(1u)`? folded.

NEW ANGLE 7: The game's compiler might have been gcc 2.7.2 with DIFFERENT FLAGS (e.g. -O1 or -O2 with different options) — but our build uses -O2.

Hmm, hold on! Maybe the game's source had the value 1 set via a variable that ALSO appears in the FINAL path, e.g.:

```
v0 = 1;
...
return *(s32*)(arg0+0x178) != arg1 ? v0 : 0;   ???
```
no.

Let me try a slightly different tack: maybe the whole function can be written differently to produce the target WITHOUT the early-set shape. E.g. what if the four compares' branches go to a shared block that sets $2=1 and jumps? The target's branches go directly to the `jr ra` — so no.

Honestly, maybe the answer for this item is a WALL, as the previous coder concluded (best 17; my best so far 16 with the goto variant).

But hold on, let me reconsider the "same variable for the const temp and the mask temp" idea, because it changes the register allocation and might yield a much better score. In the target: v1 ($3) holds the (u16) mask temp (ins 18) AND the four constants (ins 21,24,26,28). If in our source the mask temp is a separate pseudo that gets $3 and the const temp gets $2, then making them the same variable would put the const temp in $3 ✓ — but then what would get $2? The RESULT_DECL (at the return block) and the loads.

Hmm, but the target has the RESULT_DECL in $2 with an early set — we can't have that. But even without the early set, matching the const temp's register reduces the diff by ~4-5 instructions (the 3 `li v1,const` + the branch register operands). The `li v0,1` position would still differ, plus the branch targets (all branches' offsets differ because the code layout differs).

The score counts differing instructions, so branch target offsets differ anyway (the "replace" of branches counts as 1 diff each).

Let me estimate: currently 17 diffs. If the const temp moves to $3: the 3 `li v1,const` become equal (the diff region mine[20:30] vs target[20:30] would partially match) → maybe the diff drops to ~8-10. That would be a better "best" score for the WALL row, but not a MATCH.

Hmm, but careful: the "best" for a WALL row = the lowest score of a lever-free body. A better score is better evidence. But it doesn't matter much.

The real goal is MATCH (score 0). Let me think ONE more time about how to get the early `li $2,1`...

AH WAIT. IDEA!!! What if the four `return v0;` statements are replaced by a SINGLE return at the end of a block, using a flag variable? Like:

```
s32 v0;
s32 v1;
...
if (mask_test) {
    v0 = 1;
    v1 = 9; if (arg2 == v1) goto R;
    ...
    return *(s32*)(arg0+0x178) != arg1;
R:
    return v0;
}
```
Same as before.

IDEA: What if the value 1 is set as the RESULT of the comparison `arg2 == v1` itself? Like:

```
v1 = 9;
if (arg2 == v1) { v0 = 1; return v0; }
```
Then the set is in the return block (not early) ✗.

IDEA: The ROM's early `li v0,1` could ALSO be interpreted as: the source had
```
v0 = 1;
```
where v0 is a variable that is ALSO the RESULT of the function...

Hmm, what if the function's return value is assigned via a POINTER to the RESULT_DECL? no.

IDEA (!!): What if we use the *parameter* trick: the ROM's `li v0,1` — what if in the game's source, the "1" was a GLOBAL variable's value? no (a load).

Let me look at the OTHER items first — maybe they're easier (e.g. item 4's "q pin" is a callee-saved pin; item 5 similar). Actually items 4 and 5 are callee-saved-register-order walls (greg-alloc-order) — the callee-saved bank order is decided by global-alloc priorities; lever-free, gcc's order may differ. Those are "wall"-ish too.

Item 2 (func_8014FD54, pin $2 on `result`): the wall tag is sched1-hardreg-sink. The notes say the best lever-free body was 6 (P1/P2 direct returns, 39 ins). Hmm, 39 ins with score 6 — close!

Item 3 (func_801536DC): best 9.

So all five are near-walls with small residuals. Getting from 6 to 0 requires matching a few register assignments.

Let me focus on item 2 (best 6) — maybe crackable. Let me get its target listing and the diff of its best candidate.

Actually, wait. Let me reconsider the overall time budget: 5 items × 20-30 min. I've spent ~25 min on item 1 already. Let me time-box item 1: a few more experiments, then move on.

Let me try the "same variable for the mask temp and const temp" idea for item 1 (it may reduce the diff and possibly produce a match if the fold still happens but the allocation aligns... no, the fold will still differ). Cheap test though.

And another idea for item 1: what if the four compares use v1 (a variable) but the mask uses a DIFFERENT variable, so that gcc allocates the const temp to $3 (because... hmm).

Honestly, let me try a couple of quick variants and then move on to item 2.

Variants for item 1:
X1: mask temp as a variable v2: `v2 = (u16)arg3;` → the const temp might get $2 still.
X2: the const temp declared FIRST (decl order): `s32 v1; s32 v0;` → maybe the const temp gets $2 and v0 $3... The allocation order matters!

Ooh, X2 is interesting: if the const temp is declared FIRST, maybe gcc gives it $3 (or $2?). In the target the const temp is $3 and the result $2. Hmm, gcc's global-alloc allocates by priority, not declaration order... but for equal priority, the allocno order matters (which follows creation order = declaration order?).

Since the result's pseudo dies (folded), the const temp takes $2 regardless. Unless the result's pseudo survives.

So the ONLY lever is preventing the fold. Let me try one thing: what if the value 1 is set via `v0 = 1;` where v0 is declared BEFORE the other locals and the function has ANOTHER use of v0 — e.g. `v0` is used in the final path as `v0 & ...`? Tried (vN4) → 17.

Let me try the `volatile`-free "asm-free" trick of using a `long`/`short` cast to defeat the fold:
X3: `s16 v0; v0 = 1;` → the value is 1 in HImode; the copy to the SImode RESULT_DECL needs a sign-extension → `li $2,1` then `move $2,$2`? Actually a HImode→SIMode conversion in gcc 2.7.2 for a value in a register: the extension is done by the load (lhu) or by an explicit extension insn. If v0 is in a register with a HImode value, the extension to SIMode is a no-op at RTL level?? No — gcc tracks modes per pseudo; the pseudo would be HImode and the copy to the SImode RESULT_DECL would be an extension `(sign_extend (reg:HI) (reg:SI))` → on MIPS that's `move`+`sll`/`sra`? For a HImode value in a register, gcc 2.7.2 would emit `move $2,$3` then `sll $2,$2,16; sra $2,$2,16` — extra instructions ✗. The notes said s16/u16 widths were tried.

OK. Let me do a couple of quick tests (X1: mask temp as a variable; X2: decl order swap) and then move on to item 2. Actually, let me reconsider one more possibility for item 1:

What if the four `return v0;` are replaced by `return v0;` where v0 is a variable whose value is 1 AND the function ALSO has an early `return 1;`...

Hmm, what about this: the source might have been:
```
if (mask_test) {
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
    ...
}
```
with v0 assigned 1 — the fold kills it. BUT what if the game's source had `v0` as a GLOBAL? A global would be a load ✗.

Alright, let me also consider: maybe the ROM's early `li v0,1` comes from a source where the RESULT is set by a conditional expression at the TOP:

```
v0 = (arg2 == 9 || ...) ? 1 : ...
```
no.

Moving on. Let me do a last quick batch for item 1 with 4 variants (X1: mask temp var; X2: decl order; X3: the four compares via a single `||` chain with v1; X4: goto with the value set at the top of the mask block) and then decide the row.

Hmm, wait. Actually — hold on. Let me reconsider the possibility that the fold is prevented if the variable is declared as `volatile`... no. What about `v0` being a `static`? no.

What about the possibility that the game's source had the four returns as `return v0;` where v0 was assigned 1 — AND gcc's propagate_const didn't fold because the SET was in a block whose successor is a CONDITIONAL and the use was in a nested block — and gcc 2.7.2's propagate_one has this check:

```
      /* Don't propagate a value into a block that is not dominated by the set. */
```
If the set dominates the use ✓ it propagates.

OK. Accept the wall for item 1 (probably), but let me try the cheap X-variants to lower the best score.

Actually, hmm, wait. One more important idea for item 1! What about making the value 1 be set via the `(u16)` cast of a variable that is 1 — e.g.:

```
v0 = 1;
```
vs
```
v0 = (s32)(u16)(arg3 & 1) ... 
```
no.

And another: what if the early set is `v0 = 1;` but v0 is ALSO modified in the final path (`v0 = *(s32*)(arg0+0x178) != arg1; return v0;`)? Then v0 has 2 sets → the fold is blocked (the constant can't be propagated into the copies because... hmm, cse's propagate_const stops at the second set — but the four returns occur BEFORE the second set in the linear order... so propagate_const from the first set would still reach the copies ✗).

Hmm, BUT: cse's propagate_const walks the RTL linearly and stops at the next set of the reg. The four copies come before the second set → they'd be folded ✗.

Unless the second set is BEFORE the copies in the linear order?! E.g.:
```
v0 = 1;      /* set 1 */
v0 = 2;      /* set 2 - kills the fold */
... uses of v0 (the four returns) ...
```
Then at the uses, v0 = 2 → the returns would return 2 ✗ (semantics).

Hmm, but what if the second set is in a block that comes first in the RTL order but doesn't dominate? Not possible in C.

OK, what about the copy `move RESULT_DECL, v0` where v0 has 2 sets — combine can't fold → the copy remains → then reload1 coalesces v0 with RESULT_DECL($2) → the copy vanishes → and v0's 2 sets become `li $2,1` and `li $2,2` → 2 instructions where the ROM has 1 ✗. Unless the second set is dead-code-eliminated (cse removes a redundant set if the value is already 1).

So: two sets of the SAME value 1, where the second is in a nested block:
```
v0 = 1;                       /* block A */
if (cond) { v0 = 1; }          /* block B — redundant */
if (arg2 == v1) return v0;     /* uses */
```
Hmm, cse would remove the redundant set in B (the value is already 1) → back to one set → and then... but combine ran BEFORE cse, so combine saw 2 sets → didn't fold ✓, and cse removed the redundant one ✓ leaving one set. But does cse then propagate the constant into the copies? cse's propagate_const is called when it finds a constant set — it would propagate into the copies ✗.

Hmm, unless cse's global pass doesn't propagate constants into copies of the RESULT_DECL. Ugh, too speculative — but it's a cheap test! Let me include it.

Also the "if (cond) { v0 = 1; }" adds a branch (insns) unless cond is a constant → dead code removed early.

Alternative with 2 sets and no extra instructions: the second set could be inside the FIRST return's block:
```
v0 = 1;
v1 = 9;
if (arg2 == v1) { v0 = 1; return v0; }    /* the 2nd set is in the return block */
v1 = 0x11;
if (arg2 == v1) return v0;
...
```
The second set `v0 = 1` is redundant → cse removes it → then the copies... the first copy is in that block: `move RESULT_DECL, v0` where v0 = 1 → hmm, cse's propagate_const would fold the first copy but the others? It stops at the second set? The second set was removed by cse (redundant) — cse processes in order: it sees the set v0=1 (block A), propagates the constant forward: at the first return block, it encounters the set v0=1 (redundant) — hmm, propagate_one stops at a set of the reg; but cse's "global_cse" first removes redundant sets (the reg already holds 1) → removes the second set → then propagate continues to the copies → folds them ✗.

OK, enough theory. Let me run the cheap experiments (X1..X5) and move on.

X1: mask temp as a variable v2 (separate from v1).
X2: decl order: v1 first, then v0.
X3: `||` chain: `if (arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA) return v0;` (with v0 = 1 before).
X4: two sets (the redundant one in the first return block).
X5: goto version with the mask temp as a variable.

Let me write and score.
