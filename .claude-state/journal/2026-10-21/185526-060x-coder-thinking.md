---
ts: 2026-10-22T00:55:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_TRPYLcqsMPu63zdBi81q
---
nopin also gives 41 ins / score 17 (the notes' claim of 9 was for the "nopin" of a different variant maybe, or stale).

OK. So the lever-free compiler folds the constant. Since the game's compiler (same gcc 2.7.2) produced the target from its own source, the difference must be in the source spelling.

Let me think about what spelling makes gcc keep the early set:

What if the source used `v0 = 1;` where v0 is a variable that's ALSO used in the `return` at the end (the final path)? Like:

```
v0 = 1;
v1 = 9; if (arg2 == v1) return v0;
v1 = 0x11; if (arg2 == v1) return v0;
v1 = 0x29; if (arg2 == v1) return v0;
v1 = 0xA; if (arg2 == v1) return v0;
return *(s32*)(arg0+0x178) != arg1;
```
That's the same.

Hmm, what if the game's source had the FOUR comparisons as a single `if` with `||`:
```
v0 = 1;
if (arg2 == v1) ...
```
no.

Let me consider that the game's source might have used a `switch`:
```
switch (arg2) {
case 9: case 0x11: case 0x29: case 0xA: return v0;
}
```
gcc with a switch on 4 sparse values → it would generate a jump table (for a range 9..41 with 4 cases, gcc 2.7.2 uses a jump table if the density is high enough; here the range is 9..41 = 33 entries with 4 cases → density 12% → gcc 2.7.2's default threshold... it might still use a jump table). The ROM has 4 compares → so no switch. ✓ (as I assumed).

OK, radically different approach: maybe the "1" is not from a variable at all, but the ROM's `li v0,1` is the RESULT_DECL set that gcc placed early because the four `return 1`s were merged by JUMP THREADING into the predecessor...

Specifically, gcc's combine "jump threading" (in 2.7.2: `jump threading` was in combine? or in flow?). If the four return blocks are `li $2,1; jr ra` and they're all identical, flow's "tail merging" (crossjumping) merges them into one block. Then the block is `li $2,1; jr ra` and the branches jump to it.

But the ROM has the li BEFORE the branches. That could result from "tail merging" + "reorder" moving the block? Or from the scheduler.

Hmm, what if the merged block was placed BEFORE the branches by the block reordering? The merged block `li $2,1; jr ra` — if the block order placed it before the compares... The `jr ra` epilogue is at the end (ins 37) though.

Hmm, what if the merged "return 1" block was placed right after the branch that reaches it (fall-through) and the delay-slot filler moved `li $2,1` into the delay slot of ins 22? Let's think:

Layout:
```
21: li v1,9
22: beq a2,v1, RET      (branch to the jr ra at ins 37)
23: li v0,1              <- delay slot
24: li v1,17
...
```
For this, the `li v0,1` must be in the fall-through block (ins 23 is the delay slot of ins 22, so ins 23's block is the fall-through of ins 22). So the RTL order was: [set $2=1] then [branch]. And the set is before the branch — i.e. the set was in the block that falls through to the compare chain.

So the set was BEFORE the compares in the RTL. With the four `return 1`s (literals), the sets would be in the return blocks (after the compares). With `v0 = 1` before the compares and `return v0`, the set is before ✓ but it gets folded.

=> The fold is the enemy. What spelling avoids the fold?

Hmm! IDEA: what if the value 1 is set via `v0 = 1;` where v0 is declared as `register`?? Not allowed (register vars without asm are allowed though! "no `register` vars" per constraints — forbidden).

IDEA: What if the copy `move RESULT_DECL, v0` is not generated because the return expression IS the variable and gcc's "return" statement for a variable... no, the copy is always generated.

IDEA: What if the variable is `volatile`? no.

IDEA: What if the four returns are inside a nested function? no.

IDEA: What if the value is set by an expression involving a load that gcc turns into `li`? e.g. `v0 = *(s32*)&some_const` → a load. no.

IDEA (promising!): What if the value 1 is produced by an expression that gcc 2.7.2 implements as a COPY from a pseudo that is set by a comparison of constants? e.g. `v0 = (3 > 2);` → gcc folds to 1.

IDEA: What if the value is set in a way that produces TWO different values that are both 1? e.g. `v0 = 1;` and later `v0 = 1;` again (two sets) → cse merges them (same value, no intervening modification) → back to one set. But does cse merge them? cse's global pass would find the second set redundant and delete it — but only if cse runs before combine? Order in gcc 2.7.2: flow → cse → combine? Actually the pass order in gcc 2.7.2 (rtl pass list): expand, flow, combine, cse, ... hmm: `pass_combine` comes before `pass_cse`? In gcc 2.7.2's pass list: ... "combine", "cse", "jump", "loop", ... Let me recall gcc 2.7.2's pass order in `passes.c`:
```
  NEXT_PASS (function_init);
  NEXT_PASS (split_hard_reg);
  NEXT_PASS (init_regsets);
  NEXT_PASS (integrate);
  NEXT_PASS (combine);
  NEXT_PASS (sched);
  NEXT_PASS (local_alloc);
  NEXT_PASS (global_alloc);
  NEXT_PASS (reload);
  ...
```
Hmm, where's cse? In gcc 2.7.2: after "combine" there's "sched"? Let me recall the actual order:

gcc 2.7.2 passes:
1. ...
2. `pass_expand`
3. `pass_fixup_cfg`?
4. `pass_jump`
5. `pass_loop`
6. `pass_flow`
7. `pass_combine`
8. `pass_regmove`?
9. `pass_expand`
10. `pass_cse`
11. `pass_cse2`
12. `pass_sched`
13. `pass_local_alloc`
14. `pass_global_alloc`
15. `pass_reload`
...

So combine runs BEFORE cse. And combine is where "copy_const" folding happens (within a block, but combine works on the whole function in a "combine_insns" loop over all insns, tracking reg sets across labels via `reg_equivs`? combine's cross-block constant propagation exists as "reg_equivs" — hmm, in 2.7.2 combine has `reg_equivs` for "the same value" tracking.

OK. Regardless: empirically it folds.

NEW IDEA (this one might work!): Make the early set's value NOT a compile-time constant to gcc by making it depend on a value gcc treats as unknown but which is 1 at runtime — using the `(u16)` cast trick on the mask temp!

Look at the target: ins 18 `andi v1,a3,0xffff` — the (u16) cast of arg3. And ins 19 `and v0,v0,v1` — the mask test. And ins 20 `bnez v0,+0x90`.

Hmm, what if the value 1 came from something like `v0 = (u16)(v0 & v1) ? 1 : 0`? no.

NEW IDEA: Use the ROM's own structure: the `move v0,zero` sets (the return-0 paths) — those are RESULT_DECL sets. And the `li v0,1`...

Hmm, hold on! What if the value 1 in the target is NOT a result variable but the RESULT_DECL set by the "return 1" statement, and gcc placed it early via the DELAY SLOT FILLER moving it from the merged return block into ins 23's delay slot? For that, the merged return block must be reachable ONLY by fall-through from ins 22... but it's reached by 4 branches. Unless the delay-slot filler works differently: gcc's MIPS delay-slot filler (mips_delay_slot_filler in config/mips-mac.c or mips.c) can move an instruction from a block into a predecessor's delay slot if the block has only ONE predecessor path...

Hmm, in the target, all four branches go to +0x94 (the jr ra). If the "return 1" block were `li $2,1; jr ra` at +0x94... but the listing shows ins 36 `move v0,zero` at +0x90 and ins 37 `jr ra` at +0x94. So +0x94 is the jr ra, NOT a `li $2,1; jr ra` block. So the `li $2,1` is definitely before the branches.

Therefore the source computed 1 before the compares, and the copy was coalesced.

Hmm, so how did the game's gcc avoid the fold? Maybe because in the game's source, the value was NOT the constant 1 but a variable that gcc couldn't fold, e.g.:

```
v0 = 1;    /* but v0 was maybe assigned in a loop or from a function */
```

OR the game's source had `v0` as a variable that was set to 1 in a way that gcc treats as a copy from a pseudo with multiple sets...

OR (!!) the game's source had the four returns as `return v0;` where v0 was set to 1 BEFORE, and gcc's fold happened but the RESULT_DECL ended up in $2 anyway and the const temp in $3 — wait! Maybe the fold DID happen in the game's compile, and the result was: the const temp gets $2?? But the ROM shows the const temp in $3 and the result in $2.

Hmm, unless the ROM's const temp in $3 is because the const temp was NOT a pseudo but a hard-reg-preferred...

Hmm, hold on! What about this: in the ROM, is the "const temp" $3 maybe a PSEUDO that got allocated $3 because $2 was taken by the RESULT_DECL (which is live from ins 3 onward — the `move v0,zero` at ins 3 is the RESULT_DECL=0 set!). So $2 is occupied by the RESULT_DECL from ins 3 (the first `return 0` path) — wait, no: the RESULT_DECL is a single pseudo; different paths set it to 0 or 1. The pseudo's live range spans the whole function (it's live from the first set to the end). But $2's occupancy is per-path...

In terms of allocation: the RESULT_DECL is a pseudo with 2 sets (0 at ins 3/7/16/36 and 1 at ins 23) — live from ins 3 to the end. If the RESULT_DECL is allocated $2, then $2 is occupied from ins 3 onward → the const temp (live at ins 8-29) can't use $2 → gets $3 ✓✓✓!!!

So the ROM's allocation: RESULT_DECL → $2 (its preference), const temp → $3.

In our lever-free compile: the RESULT_DECL's set is only at the return blocks (ins 32 in mine) → $2 is free during the compares → the const temp takes $2 ✗.

So the difference is again the early `li v0,1` (the RESULT_DECL=1 set before the compares).

So, in the game's compile, the RESULT_DECL had an early set of 1 — meaning the game's source had `return 1` in a way that set the RESULT_DECL early... OR the game's source had a variable whose value was 1 and the copies were coalesced (making the RESULT_DECL set early).

AH WAIT. Here's a thought: if the local `v0` (value 1) is COALESCED with the RESULT_DECL ($2), then the local's set `li $2,1` IS the RESULT_DECL's set ✓ — and the RESULT_DECL's live range starts there → $2 occupied → const temp → $3 ✓✓.

So the fold must be prevented for the coalescing to happen. The game's source must have prevented it. What source spelling prevents gcc 2.7.2 from folding a constant into the return copy?

Possibility: the game's source had `v0` assigned 1 and the four returns as `return v0;` — and gcc's cse "propagate_const" doesn't fold a constant into a copy ACROSS basic blocks when the copy's destination is the RESULT_DECL? But our compiler folds it...

Hmm, maybe our folding is not combine but the "return" statement lowering: in gcc 2.7.2, `expand_end_asm`/`expand_return` generates `move RESULT_DECL, v0`. Then combine's "copy_const"...

Whatever. Since OUR source spelling differs from the game's, maybe a different spelling avoids the fold. Options to test (each cheap):

T1: `v0 = 1;` placed OUTSIDE the inner `if` block (i.e., before the `if ((*(s16*)(arg1+0xAE) & arg3) == 0)` test) — the set would then be even earlier and in a different block. Hmm, but then the value is set on paths that don't use it → gcc might sink it.

T2: Declare v0 with init: `s32 v0 = 1;` at the top of the function.

T3: Use `v0` in the final path too: `return v0 & (*(s32*)(arg0+0x178) != arg1);` — hmm, `1 & x` → gcc folds to x → the value's use disappears. But maybe during combine, the `&` prevents the fold of the set (the set has 2 uses: 4 copies + the AND)? combine substitutes the constant into all uses and deletes the set anyway.

T4: Assign v0 = 1 twice in different blocks: `v0 = 1;` before the compares and `v0 = 1;` in a nested block.

T5: Make v0's set be a copy from a parameter: `v0 = arg3;`?? Not 1.

T6: What if the value 1 is set as `v0 = 1 - 0;`? folded.

T7: What if we return `v0` where `v0` is set via `v0 = 1;` and v0 is ALSO the variable used in the mask test? no.

T8: What if the source uses a `do { } while(0)` wrapper for the four compares? That creates a block scope; the value set inside... Hmm: the notes mention vJ_dowhile (do-while ref boost on v0).

T9: What if the four returns are in a nested block `{ ... }` (scope) — changes nothing.

T10 (interesting!): What if the value is assigned in the block that ALSO contains the const temp assignment, e.g.:
```
v1 = 9;
v0 = 1;
if (arg2 == v1) return v0;
```
Order swap: the set of v0 comes after the set of v1 → then v1 (const) is live from its set to the compare... and v0's set after. Hmm, allocation order might change: with v0's set AFTER v1's set, maybe v0 gets $2 (first come) and v1 gets $3! But the fold would still delete v0's set... unless the fold doesn't happen.

Hmm, but here's the thing: the FOLD is what kills it. Let me verify the fold hypothesis by checking whether the target's early `li v0,1` could be produced by ANY lever-free C. Let me test a promising shape:

```
s32 v0;
...
if (mask == 0) {
    v1 = 9;
    v0 = 1;
    if (arg2 == v1) return v0;
    ...
}
```
Hmm.

Let me think about what makes gcc's cse/combine NOT fold. One known blocker: if the pseudo is set to a constant AND the pseudo is used in a `MEM` context or the pseudo's set is in a different block than the use AND there's a "jump" — cse's propagate_const requires the reg to be "constant at the use point", which requires proving no modification in between — with a single set, it's provable.

Another known blocker: the pseudo is a "user" of a call's clobbered reg? no.

Another: **the set is in a block that is not guaranteed to dominate the use**? Not our case.

Another blocker: the pseudo has MULTIPLE sets. Let's explore T4 (two sets of 1 in different blocks). Then cse can't propagate a constant (two definitions), and combine can't fold → the copies remain `move RESULT_DECL, v0` → then reload1 coalesces v0 with RESULT_DECL ($2) → the copies vanish → and the two sets of v0 remain: `li $2,1` twice → but cse would remove the second one if it's redundant... cse's "global_cse" removes a redundant set when the reg holds the same value ✓ (the value is 1 in both). But the second set's block might not be dominated... e.g.:

```
v0 = 1;          /* block A */
if (cond1) { v0 = 1; return v0; }   /* block B */
```
cse would see the set in B as redundant (v0 already 1) → delete → then we're back to one set → and then combine might fold (if combine runs after cse — no, combine runs BEFORE cse in gcc 2.7.2!). Hmm, so with combine running first, the two sets prevent combine's fold; then cse removes the redundant second set; then the copies `move RESULT_DECL, v0` survive (cse doesn't fold constants into copies... hmm, cse's "propagate_const" might, but it processes the final single set...).

Hmm, actually in gcc 2.7.2 the order is: combine → cse → cse2 → sched → local_alloc → global_alloc → reload. If cse propagates the constant into the copies, we're back to square one.

But hold on: the ROM has the early set and the branches jump to the bare `jr ra` — the copies are gone. If cse propagated the constant into the copies, we'd get `li $2,1` at each return → merged → the li in the return block (not early) ✗.

So the ROM's compile must have had the copies coalesced (never folded). That means cse did NOT propagate the constant. cse's propagate_const in gcc 2.7.2 requires the reg to be set to a constant and NOT set again — with two sets it wouldn't propagate.

But if the two sets are in a dominance relation, cse's "global_cse" would delete the second (redundant) — hmm, but would it? cse deletes a set if the reg's value is already known to be the same constant at that point (that's exactly propagate_const's job) → it would delete the second set and then propagate the constant into the copies ✗.

Ugh.

OK, let me flip to the empirical mode: just try a bunch of spellings and look at the diffs. The compiler is fast (1.2 s per score). Let me write ~8 variants and score them. Even if I don't find a match, I'll have ≥30 tries and a well-evidenced WALL.

But wait — maybe I should reconsider the whole approach: maybe the lever-free body doesn't need the "early set" shape; maybe there's a completely different C that yields the same 39 instructions. The target has:
- `li v1,9` etc. — a const temp in $3 (4 sets)
- `li v0,1` early
- `move v0,zero` in delay slots (3×) and at ins 36

The `move v0,zero` in the delay slots: those are the RESULT_DECL=0 sets for `return 0` paths. In our lever-free compile, mine has `move v0,zero` at ins 21 (hmm) and the target has them at ins 3, 7, 16, 36.

Wait, that's interesting: in the target, the `return 0` sets are in the delay slots of the branches (ins 3, 7, 16) — i.e. the RESULT_DECL=0 is set BEFORE the branch (in the fall-through path) and the branch jumps to the epilogue. That's gcc's standard "return 0" scheduling: the delay slot is filled with the result set.

In mine, the `move v0,zero` appears at ins 21 — after the bnez at ins 20. Hmm, that suggests mine's "return 0" set is placed differently. But whatever, the diff shows only ins 21 differs in that region... Actually the diff shows mine[20:30] vs target[20:30] as one replace block, so mine[21]=`move v0,zero` vs target[21]=`li v1,9` — mine has an EXTRA `move v0,zero` and the rest are shifted.

Hmm, so mine's structure: `bnez v0, epilogue; move v0,zero; li v0,9; ...` — mine sets v0=0 on the fall-through path (which then goes into the compares) — that would be wrong semantically... unless mine's `bnez v0, 6ac4` jumps to the epilogue and the fall-through (v0==0) enters the compares with v0=0 — and later the result is overwritten. So the `move v0,zero` is dead on that path. It's the RESULT_DECL=0 set for the `return 0` at the end (the path where the mask test fails) — but that path is the branch-taken path, not the fall-through. Confusing but it's gcc's scheduling: it hoisted the RESULT_DECL=0 set into the fall-through (since the value is dead there) — no wait, it can't hoist it into a path where it's not the result... unless the result on that path is later overwritten (true: the compares overwrite v0 with the final comparison result). So gcc reused $2 for the "0" result and then reused it again. Clever compiler.

So the target's shape: the `return 0` sets are in the delay slots of the branches that RETURN 0 (ins 3, 7, 16) — i.e. the set is placed on the path where the result IS 0.

OK. Now let me consider the possibility of a fundamentally different source shape that produces the target lever-free. What if the source is:

```
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0 = 0;    /* the result, initialized to 0 */
    ...
    if (...) {
        v0 = 1;
        ...
    }
    return v0;
}
```
That's a single-return shape → the RESULT_DECL is set from v0 at the end → the target has multiple exits though.

Hmm.

Let me now consider that maybe the answer is a `goto`-based shape (the catalog allows "statement order" but goto is a real C construct... "real C moves only" with the catalog listing temps, decl order/scope, widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse. goto isn't listed but "statement order" might cover it. The moves.md shows a MATCH with "for -> goto loop" — so goto IS used by other shards ✓.

So a goto-based rewrite is allowed! E.g.:

```
s32 v0;
...
v0 = 1;
v1 = 9;
if (arg2 == v1) goto RET1;
v1 = 0x11;
if (arg2 == v1) goto RET1;
...
RET1:
return v0;
```
Hmm, that's the same as the ifs.

What about:
```
v0 = 1;
if (arg2 != 9) { v1 = 0x11; if (arg2 == v1) goto RET1; ... }
goto RET1;
RET1: return v0;
```
Same.

Hmm, what if the value 1 is set via a comparison that the compiler folds into `li`? no.

Let me try yet another angle: maybe the fold can be avoided by making the early value's set be a COPY from a pseudo whose set is a constant BUT the copy is in a different block and cse can't propagate...

You know what? Let me just try a batch of variants empirically. Cheap. Let me write 6 variants for item 1:

V1: `v0 = 1;` moved OUTSIDE the mask-test block (before the `if ((*(s16*)(arg1+0xAE) & (u16)arg3) == 0)` test) — i.e. set at the top of the `if (*(u16*)(arg1+0x5E) != arg2)` block.
V2: `s32 v0 = 1;` init at decl, at the top of the function.
V3: two sets: `v0 = 1;` before the compares and `v0 = 1;` inside the first return branch.
V4: `v0` used in the final path too: `return v0 & (*(s32*)(arg0+0x178) != arg1);`
V5: the four compares with `||`: `if (arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA) return v0;`
V6: the value set via `v0 = 1;` where v0 is `u16`? (tried) — skip.
V7: goto-based: set v0 = 1; then `if (arg2 == v1) goto R;` with a single `R: return v0;`.

Let me write V1, V2, V3, V4, V5, V7 and score them.

Note: the body must be the function definition only (the --body flag). Also the signature must stay.

Let me write them.

V1:
```c
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0;
    s32 v1;
    if (*(u16 *)((u8 *)arg1 + 0x0) == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg1 + 0x58) == 0) {
        return 0;
    }
    if (*(u16 *)((u8 *)arg1 + 0x5E) != arg2) {
        if ((*(s32 *)((u8 *)arg1 + 0x5C) & 0xC100) != 0x8000) {
            return 0;
        }
        v0 = 1;
        if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
            v1 = 9;
            if (arg2 == v1) return v0;
            v1 = 0x11;
            if (arg2 == v1) return v0;
            v1 = 0x29;
            if (arg2 == v1) return v0;
            v1 = 0xA;
            if (arg2 == v1) return v0;
            return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
        }
    }
    return 0;
}
```

V2: `s32 v0 = 1;` at decl.

V3: two sets.

V4: final path uses v0.

V5: ||-fold.

V7: goto.

Let me write all 6 in parallel Write calls, then score all 6 in one Bash call.

Actually — to conserve effort, let me think about which are most likely. Honestly, the fold is done by gcc's cse/combine; none of these will prevent it. But cheap to test.

Hmm, let me think about ONE more possibility that might really work: making the value 1 come from a variable whose set is a copy from the RESULT_DECL... impossible.

What about making the function return type `void` and using a different mechanism? no, the signature must stay.

What about the "1" being the return of a comparison that gcc implements as `sltu v0,zero,v0`? no.

Hmm, what about this: what if the early value is not 1 but the result of `!(...)`? no.

What if the source returns `v0` where v0 was set to 1 by an expression like `v0 = (u16)(arg3 - arg3 + 1)`? folded.

Honestly, gcc 2.7.2's cse "propagate_const" only propagates a constant into a use if the reg is set to that constant and there are no other sets — and it works across blocks (that's the "global_cse" pass). So the only way to keep the early set is to have the value NOT be a constant in gcc's view.

The only way to have a value of 1 that gcc doesn't know: a runtime load, or a value derived from a parameter.

!!!! IDEA !!!! What if the value comes from a PARAMETER comparison that's always true but gcc can't fold? Like `v0 = (*(u16*)(arg1+0x5E) == arg2) ? ...` no.

Hmm, what about `v0 = (arg2 == 9) | (arg2 != 9);` → 1 always, but gcc folds `x|!x`? gcc 2.7.2 might not fold that! It would generate: `sltu v0,zero,arg2`? Hmm, `arg2 == 9` is a comparison (2 insns) — the ROM has no such instructions. ✗.

So the value must come from a CONSTANT expression that gcc treats as a constant → fold.

=> The early set CANNOT survive in a lever-free body... unless the copy is coalesced BEFORE the fold. Hmm! What about the ORDER of passes: combine runs before reload. But what about the "expand" pass: the `return v0;` statement is expanded to `move RESULT_DECL, v0` — and gcc 2.7.2's expand pass has a special case: `expand_return` → if the value is a variable... it generates the copy.

Hmm, BUT: gcc 2.7.2's `expand_return` has an optimization: if the returned expression is a simple variable, it does `emit_queue` of a copy. And then there's "tail call" optimization.

OK — What if the source returns a value that IS the RESULT_DECL-like pseudo... i.e. what if the function's return value is assigned by the RETURN of a value that's already in a register the RESULT_DECL prefers? Specifically: `return v0;` where v0 is a LOCAL — gcc's expand_return might do "the returned value is a local; the copy is `move RESULT_DECL, v0`". If RESULT_DECL and v0 get the same register, reload1's coalesce removes the copy. But the FOLD happens earlier (combine/cse), replacing the copy with the constant.

=> The fold is the wall for this shape. The notes' wall tag "const-fold-return" is apt.

Given that, item 1 is likely a WALL. But hold on — maybe there's a spelling where the value is set by a `+=` or a compound expression that yields a copy rather than a constant:
`v0 = 1; v0 += 0;` → folded.

What about `v0 = 1; v0 |= 0;`? folded.

What about `v0 = 1; v0 = v0;`? folded.

What about `v0 = 1; v0 ^= 0;`? folded.

What about `v0 = 1; if (0) v0 = 2;`? the dead branch is removed → one set.

What about `v0 = 1; v0 = cond ? 1 : 1;`? folded.

Hmm, what about making the value's set be a copy from a CONSTANT PARAMETER-default... no.

Let me now consider: maybe the ROM's early `li v0,1` is NOT from a variable but from the SOURCE having `return 1` in a place where the RESULT_DECL is set early — e.g., the source might be:

```
if (mask_test) {
    if (arg2 == 9) return 1;
    ...
}
```
and gcc 2.7.2 generated: the four `return 1` blocks → each `li $2,1; jr ra` → crossjumping (tail merging) merges the four identical blocks into ONE → the merged block `li $2,1; jr ra` → the four branches jump to it. Then the SCHEDULER (final scheduling) might move the `li $2,1` into the delay slot of ins 22? For that, the merged block must have a single predecessor... it has 4. Hmm, but gcc's MIPS delay-slot filler CAN move an instruction into a delay slot if the instruction is the FIRST in the block and the block is reached by a fall-through from that branch... but here the block is reached by 4 branches (not fall-through).

Hmm, wait. Actually the branches jump to +0x94 = the `jr ra` at ins 37, and the `li v0,1` is at ins 23 (delay slot of ins 22). If the merged return block were `li $2,1; jr ra` at +0x94, then ins 37 would be `li $2,1` and ins 38 `jr ra` and there'd be 40 ins. The target has 39.

Alternatively the merged block is just `jr ra` (ins 37) — i.e. the `li $2,1` was REMOVED from it and placed earlier. Who removed it? The delay-slot filler moving it into ins 23's delay slot — but only if legal: moving `li $2,1` from the merged block into ins 23's delay slot is legal only if all paths to the merged block pass through ins 23. Paths: ins 22 (fall-through executes ins 23 ✓), ins 25, 27, 29 (fall through from 23 ✓). And the path from the final compare (ins 30-34) — it does `j 6abc` (ins 34) — that path does NOT pass through ins 23! But that path sets $2 to the comparison result, and if the `li $2,1` were executed on that path it would clobber the result ✗. So the filler can't move it there.

=> So the `li $2,1` at ins 23 is a genuine early set from the source (a variable set before the compares) ✓ — the source computes 1 before the compares, and the copies were coalesced.

So: the game's source has a variable set to 1 before the compares, returned in four places, and gcc did NOT fold the constant.

Why would gcc not fold? Because the variable is ALSO used elsewhere! E.g. if the variable is used after the returns (in the final path) — the final path in the ROM returns the comparison result, so v0 (the 1-valued variable) isn't used there.

Hmm, unless the source's final path was `return v0 & (...)` — the ROM's final path computes `lw v0,376(a0); xor v0,v0,a1; sltu v0,zero,v0` — that's `x != arg1` (no AND with 1). If the source were `return v0 & (x != arg1)`, gcc would fold `1 & x` → x (the AND is gone since 1 is a no-op for AND? `1 & x` = x ✓ gcc folds). But then the AND wouldn't appear ✓ consistent with the ROM! But the fold of `1 & x` requires knowing v0=1 → the constant propagates → the set is deleted ✗.

Hmm, unless gcc's fold of `1 & x` doesn't delete the set but... no, it would.

OK, let me look at this from the "what did the game's source look like" angle. The decompiler (this project) derived orig.c from the ROM. The game's source is unknown. The ROM's shape is: value 1 set early, four early returns of it.

Hmm, here's a thought: what if the game's source had the four returns as `return v0;` where v0 is a variable that gcc 2.7.2 kept in a REGISTER because it's ALSO used in the `if` conditions? No...

Honestly, let me try the empirical route with several variants, including some exotic ones:
- V8: `v0 = 1;` and the four returns `return v0;` BUT with v0 declared as `s32` and the function's return type `s32` — done.
- V9: make the four returns return `v0` where v0 is assigned `v0 = 1;` INSIDE the `if (mask)` block right before the first compare (that's orig.c) — done (nopin).

Let me test the hypothesis that the fold is unavoidable by testing a shape where the value's set is in a DIFFERENT basic block from ALL its uses and see if the fold still happens: e.g. V1 (set before the mask test). If gcc still folds, the "cross-block fold" is confirmed.

Let me also try:
- V10: use a `while`/`do-while` structure? no.

And one more idea:
- V11: `v0 = 1;` where v0 is a `static`? no (would add a store).

- V12: Make the value 1 a function PARAMETER default? The signature can't change (4 args fixed). But hmm — the constraint says "no signature or decl change outside the body". The body's parameters are given.

- V13: What if we make `v0` a local array element? `s32 v0[1]; v0[0] = 1; ... return v0[0];` → memory traffic ✗.

Let me just run the batch of 6 and see. Even if all fail, they count as tries.

Actually, hold on. Let me reconsider the problem completely differently: maybe the lever-free body doesn't need to reproduce the "early set" — maybe the pin isn't needed at all for a DIFFERENT reason: maybe the target's shape can be produced by a source where the RESULT_DECL is set early because of a `goto`-based single-exit structure:

```
s32 v0;
...
v0 = 1;
if (arg2 == v1) goto RET;
v1 = 0x11; if (arg2 == v1) goto RET;
...
goto FIN;
RET:
  return v0;      <- hmm same
FIN:
  return *(s32*)(arg0+0x178) != arg1;
```
With a goto, the four `goto RET` all jump to one block `return v0;` → the copy is ONE copy (not four) → and the block is reached by 4 branches. The copy `move RESULT_DECL, v0` — the fold still applies.

BUT: here's the thing — with a single `return v0`, the copy is one instruction. If it's NOT folded (because the set is in a different block and cse's propagate_const doesn't cross blocks?), then the shape would be: `li v0,1` early + 4 branches to a block with `move $2,$3; jr ra` — an extra `move` ✗ (the ROM has no move).

Unless the coalesce merges them → the copy vanishes ✓.

So the goto version has ONE copy to coalesce (vs 4). Maybe with the goto version, gcc's combine handles it differently! Because with 4 separate `return v0` statements, gcc's "tail merging"/crossjumping might merge the return blocks first, creating the same shape.

Let me try the goto variant. It's cheap.

Actually, even better: maybe the trick is that with a goto, the copy `move RESULT_DECL, v0` is in a block whose predecessor is the goto — and gcc's cse propagate_const might not fold across a "goto" (since cse's propagation requires the use to be reachable without an intervening set — it should handle gotos fine).

Let me just test. Batch:
V1 (set before the mask test), V3 (two sets), V4 (v0 used in the final path), V5 (||-fold), V7 (goto with a single return v0), V8 (goto with four separate return v0? same as V7).

Let me write V1, V3, V4, V5, V7 and also:
V9: `v0 = 1;` where v0 is assigned BEFORE the first `if` in the function (top-level) — then it's set on all paths (including the early returns 0) → the fold might be blocked because the set is in the entry block and the uses are in many blocks? cse's propagate_const would still fold. But cheap to test.

Let me write them.
