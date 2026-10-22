---
ts: 2026-10-22T00:52:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UThhqOOoKFdOmrg21syV
---
OK so vA uses a local v0 with `v0 = 1;` and literal compares (no v1 temp). The const temp in the target is v1 ($3) holding 9/17/41/10 — so the ROM reuses ONE variable for the four constants, which is what orig.c does (v1 = 9; if (arg2 == v1) ...). In vA, the constants are literals → gcc creates a temp per compare (or reuses one). The target has ONE register v1 reused with 4 sets → consistent with either (gcc reuses the same pseudo for the 4 literal constants if their live ranges don't overlap — likely).

Now the score 17 for vA: the diff showed mine[21] `move v0,zero`, mine[22] `li v0,9`, `beq a2,v0,+0x7c` — so mine's const temp is v0 ($2) and the result "1" is materialized at the return block (mine[31:33] `j 6ac4; li v0,1`).

So in mine, the const temp took $2 and the result 1 got $2 at the return block.

Key insight from the target: the result 1 is set at ins 23 (early) and stays live → $2 is occupied → const temp goes to $3.

So I need gcc to NOT fold `v0 = 1` into the return copies.

IDEA: what if the value 1 is stored in a variable that is ALSO used after the returns in a way that keeps it alive? No.

IDEA 2: What if the assignment is `v0 = 1;` where v0 is declared `volatile`? → memory. No.

IDEA 3 (promising): What if the "1" is produced by a comparison that gcc emits as `li`? For example, `v0 = (arg2 == arg2);` — gcc folds x==x → 1? Actually gcc 2.7.2 might NOT fold `x == x` for a non-constant x! It's a valid optimization but gcc 2.7.2 may not do it (it would need to prove no trap — for integers, no trap, so it's valid; but gcc 2.7.2 might not implement it). If not folded, the RTL would be: compare arg2 with arg2 → `xor v0,arg2,arg2; sltu v0,zero,v0` — extra instructions. Not `li v0,1`. So no.

IDEA 4: `v0 = 1;` where the variable is used in a `&&` fold: e.g. `if (v0 && arg2 == 9) return v0;`? changes semantics/structure.

IDEA 5: Maybe the fold can be blocked by making the four returns use DIFFERENT variables? no.

IDEA 6: Use a union/struct? Not in the catalog.

IDEA 7 (interesting): What if the source returns the value via a variable that gcc treats as a "loop variable"? no.

IDEA 8: What if the return value is computed as an expression involving the RESULT_DECL path that gcc 2.7.2 keeps as a pseudo: e.g. `return (v0 = 1);` — the assignment's value. RTL: `v0.1 = 1; move RESULT_DECL, v0.1`. Same as before.

IDEA 9: What if the early value is not 1 but 1 via a 64-bit or wider type? e.g. `long long v0 = 1;` → different instructions.

IDEA 10 (promising!): What if the early set's value is a constant that gcc keeps because the pseudo is used by a copy in a DIFFERENT mode? Hmm.

IDEA 11: What if the four returns are inside a nested block that has its own scope, and the result variable is declared in the INNER scope, so the variable's live range ends... no, that doesn't matter.

IDEA 12 (very promising): What if the value is computed by an expression that gcc implements as a COPY from a pseudo whose value is set by a copy from the constant, and combine's substitution is blocked because the source pseudo is used in more than one place... Let's think: combine's subst replaces the pseudo with the constant everywhere. But combine has a restriction: it won't delete the set if the pseudo is "set in a different block and used across a jump"? Actually, gcc 2.7.2's combine.c has `subst` handling notes: it can propagate a constant across blocks, BUT there's a rule about "the set must not be in a different basic block unless the value is invariant"... Hmm, in gcc 2.7.2, combine's "reg_or_mem" / "subst" handles `set` of a constant into a copy: the function `simplify_const_copy`? Let me recall... Actually, in gcc 2.7.2, combine.c has:

```
/* Simplify a comparison of a memory block with zero.  */
...
static rtx
simplify_const_copy (rtx reg, rtx const_rtx) ...
```
Hmm, I recall `combine` does handle "move pseudo, const" → "pseudo = const" (that's `reg_or_mem`?). The key function is:

```
/* If X is a register and SET_SRC is a constant, ... */
```
In gcc 2.7.2, combine has a step "subst" of a constant into a copy: `case PLUS_EXPR: ...`. The relevant one is in `combine`:
```
	  /* If we are copying a constant to a register, ... */
```
There's a known optimization: "copy_const" — combine turns `move pseudo, const` into `pseudo = const` and then the pseudo's set is deleted, the constant propagated. This is the classic "constant propagation into a copy".

So yes, the fold happens.

BUT: there's an important exception — combine does NOT do this if the copy's source pseudo is "used in a phi" or if the pseudo is live across a call or if the pseudo has multiple sets.

Hmm, what if the pseudo has TWO sets, e.g.:
```
v0 = 1;
... (some path)
v0 = 1;    /* another set of the same value */
```
Two sets → combine can't propagate (it handles the case of multiple sets by... it could still propagate each). Hmm, but the ROM has only ONE `li v0,1`.

What if the pseudo has one set but is used in a non-copy context (e.g. as an operand of an AND)? Then combine propagates the constant into that use too (it's a constant propagation) → the set is deleted → the uses become constants → the AND with 1 → `andi`? no, `x & 1` → `andi x,1` — an extra instruction vs the ROM's `and`. Hmm, but if the constant propagates into the AND, the AND becomes `andi v0,v0,1` — wrong shape.

OK, radical idea: maybe the answer is to make the value 1 be produced by the comparison `(u16)arg3` mask temp? no.

Let me step back and consider: maybe the ROM's `li v0,1` at ins 23 is NOT the result value but something else! Let me re-examine: what if the source is:

```
if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
    v0 = 1;   /* the result */
    ...
}
```
Yes it's the result.

Hmm, alternatively the ROM could be:
```
    if (arg2 == 9) return 1;
```
with the "1" being the RESULT_DECL set merged early by jump threading. Let me test this empirically! vH_lit1 (literal `return 1`) — what score did it get? The notes say "literal `return 1` arms (H, I)" all 17 or 18. Let me look at the diff for vH to see where its `li v0,1` ended up. If the merged return block has `li v0,1` before `jr ra`, then the branches would jump to it (not to the bare jr ra) → shape differs.

Let me actually run vH and look at the diff. And vJ (do-while ref boost). Let me score several and dump diffs. Let me look at vH's diff.

Actually, let me think about the "delay slot" mechanics more: In the target, `li v0,1` at ins 23 is in the delay slot of the branch at ins 22. gcc's final scheduling (delay slot filling) moves an instruction into a delay slot if it's safe: the instruction must not be needed before... The `li v0,1` is needed only on the paths that return 1 — all of which pass through ins 23 ✓. So the scheduler moved it there from the merged return block? That would be a "threading" of the set backward — that's exactly combine's jump-threading: "move the set into the predecessor's delay slot" is done by the MIPS delay-slot filler, which can move an instruction from a block into a predecessor's delay slot only if the block is reached ONLY from that predecessor (fallthrough). Here the merged return block is reached from 4 branches → the filler can't move the set out of it.

Hmm, so the set must have been in the fall-through path before the branches — i.e., the source computed it before the branches ✓ (v0 = 1 before the compares) — and gcc kept it there because the copy was coalesced.

Alright: so we need the coalescing. And the fold blocks it.

Hmm, wait. Maybe the fold doesn't happen in the ORIGINAL because of the PIN: with `register s32 v0 __asm__("$2")`, the variable is a hard reg. Then `return v0` → `move RESULT_DECL, $2`. combine sees the source is a hard reg $2 whose value is 1 (from `li $2,1`) — combine CAN substitute a constant into a copy whose source is a hard reg? For hard regs, combine is more careful: it can't just replace the use with the constant because the hard reg might be set elsewhere... but it can, since it knows the single set. Hmm, but gcc's combine generally avoids substituting constants into copies from hard regs? Actually, combine's `subst` works on pseudos; for hard regs it uses `reg_or_mem`...

In any case, empirically with the pin, the set survives (that's the target). Without the pin, the fold happens.

So the question: how to make gcc 2.7.2 keep a constant-valued pseudo alive across branches and allocate it to $2?

Thought: gcc 2.7.2's global-alloc assigns hard regs to pseudos; the RESULT_DECL is a pseudo with a preference for $2 (the "prefers v0" note). If our res pseudo were ALSO the RESULT_DECL...

What if we return the result of an expression that gcc computes into the RESULT_DECL directly? e.g. `return 1;` — that's the RESULT_DECL = 1 (constant). The four returns → four sets of the RESULT_DECL → jump threading merges them into one set placed... hmm, where? If the four return blocks are each `li $2,1; jr ra` and jump-threading merges them into one block `li $2,1; jr ra`, then the branches jump to the `li`. The target's branches jump to the `jr ra` (skipping the li). So the target's shape requires the li BEFORE the branches.

UNLESS the four `return 1` blocks each have `li $2,1` and gcc's jump threading moved the `li` into the delay slot of the branch leading to it... For the FIRST branch (ins 22), the return block is reached only from that branch (fall-through) — so the delay-slot filler could move the `li $2,1` into ins 23's delay slot ✓!! And the other three branches (25,27,29) jump to the SAME return block — if the li was moved out of the block into ins 23's delay slot, then the other paths would skip the li → wrong. So the other paths must have their own `li` — but the target shows only ONE `li v0,1` in the whole function!

Hmm, unless the other three branches' delay slots contain the li? No, they contain `li v1,17/41/10`.

Wait, let me re-examine: are ins 25/27/29 branches to +0x94 (ins 37, jr ra)? Yes: "beq a2,v1,6abc" for ins 22,25,27,29 — all to 6abc = ins 37 = `jr ra`. So all four jump to the bare `jr ra`, and $2=1 was set at ins 23 which ALL paths execute (since ins 23 is the delay slot of ins 22, and paths through ins 25/27/29 fall through ins 23) ✓✓.

So the value 1 is set once, before all four compares. This is ONLY possible with the "v0 = 1 before the compares" source + a non-folded set.

So the source is:
```
v0 = 1;
if (arg2 == v1) return v0;
v1 = 0x11; if (arg2 == v1) return v0;
...
```
and the ROM's compiler kept the set of v0 early and coalesced the copies.

Now: WHY would combine not fold? Because with the pin, v0 is a hard reg ($2) — combine's constant substitution into a copy whose SOURCE is a hard reg: gcc's combine in 2.7.2 handles "copy of a hard reg" via `reg_or_mem`? Hmm. Actually, I recall that gcc's combine does NOT propagate a constant out of a hard register, because a hard register's value can be changed by calls etc. — but here there are no calls.

Whatever the reason, the pinned version works. Lever-free, the pseudo folds.

So, what C would give gcc a NON-foldable early set of 1?

Possibility: the set is a COPY from another pseudo (not a constant): e.g.
```
s32 t;
t = 1;
v0 = t;      /* copy */
```
combine: t = 1 (const) → the copy v0 = t → substitute → v0 = 1 → fold. Transitive fold.

Possibility: the set is a copy from a PARAMETER: `v0 = arg3;` — then v0's value isn't constant → no fold ✓, but the value isn't 1.

Hmm, BUT: what if the parameter is unused otherwise and gcc... no, the value must be 1.

Possibility: the value 1 comes from an arithmetic expression on a parameter that gcc can't fold but that yields 1 at runtime: e.g. `v0 = (arg3 == arg3);` → if gcc 2.7.2 doesn't fold x==x, the RTL would be a comparison → 2-3 instructions, not `li`. ✗.

Possibility: `v0 = 1 & arg3;`? Not 1 unless arg3&1.

Hmm.

Possibility: use a GLOBAL variable? no.

Possibility: exploit the `(u16)` cast trick: `v0 = (u16)1;` → folded.

Hmm. So maybe the fold can be prevented by using a construct where gcc's copy is not a simple copy: e.g., the return value is the result of a CONDITIONAL expression:
```
return cond ? v0 : 1;
```
Nah.

Let me reconsider: maybe the previous coder's assumption is wrong and there IS a lever-free way. Let me look at the problem from the register-allocation side: the target has $2 = the result value (1) live across the compare chain, $3 = the const/temp. The lever-free version has $2 = the const temp, and the result set at the return block.

What if we change the source so that the const temp is used BEFORE the result value is set, or so the const temp's live range doesn't overlap the result's? E.g. if the result value were set AFTER the compares (which is the folded case), $2 is free during the compares → the const temp takes $2 ✗.

So the ONLY way is the early set surviving.

Hmm, hold on! What about the "0" sets? The target has `move v0,zero` in the delay slots (ins 3, 7, 16) and at ins 36. These are the RESULT_DECL=0 sets for the `return 0` paths — they're in $2 too. Interesting: so $2 is written with 0 in those paths. Since the delay-slot filler put the "move v0,zero" in the delay slots, the RESULT_DECL=0 sets are also threaded early. Fine.

Now here's a thought experiment: what if the source has NO local variable and the four returns are `return 1;`? Then each return block sets the RESULT_DECL=1. The jump-threading merges the four `return 1` blocks. Hmm, but the merged block would be reached from 4 branches.

Let me just TEST it: score vH_lit1 and look at the diff to see where gcc put `li v0,1`. That tells me how gcc 2.7.2 handles the literal case. Let me do that now — it's cheap (1.2 s).

Also test: `return v0` where v0 = 1 assigned before, but with the const temp as a SEPARATE variable per compare (vE_4temps) to see the reg allocation.

Let me run several and inspect diffs. I'll batch: score vH_lit1 and print the full diff.
