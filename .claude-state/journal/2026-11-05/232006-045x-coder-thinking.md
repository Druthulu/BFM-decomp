---
ts: 2026-11-06T06:20:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p4uUvI92uYwqxtbEaU9W
---
Good: "the copy wrapped in do { tmp = (s16)v; c = tmp; } while (0)" — the copy is inside the do-while with the source defined outside. So the do-while's loop-shaped live range keeps the copy (combine doesn't fold it because the copy is in a loop block... and the loop is executed once but jump doesn't merge? Hmm).

In our case the copy is a *call argument* setup, not a C assignment. To wrap it, we'd have to wrap the call statement (w4) — too disruptive.

Alternative: introduce an explicit C copy inside a do-while:

```
do {
    t = otz;
} while (0);   /* t = otz copy in a loop block */
otz = func_801823D4(t, -0x1A);
```
Hmm, then RTL: (set otz v0) ... loop { (set t otz) } ... (set a0 t). Combine would fold t into a0? t is in the loop block; the arg copy after. If the loop block isn't merged, combine won't fold t. But then we'd have `move t,otz` + `move a0,t` = 2 moves vs target's `move a0,s1` only 1. Hmm, target has exactly 2 moves total (s1,v0 and a0,s1). So if we have otz=call (move s1,v0), t=otz (move s?,s1), a0=t (move a0,s?) — that's 3 moves. Too many.

Unless t is coalesced with otz... then it's the same.

Hmm.

Let me reconsider. Maybe there's another way to keep `move s1,v0`: make otz's value live across the func_801823D4 call. What if the *second* call's result assignment uses otz in a way... no.

What if we restructure so the first otz value has a second use *after* the second call? E.g.:

```
otz = RotTransPers4(...);
tmp = otz;             /* save */
otz = func_801823D4(otz, -0x1A);
... use tmp somewhere free?
```
The save `tmp = otz` is a copy — if tmp is used later cheaply... but it'd add insns.

Hmm.

What about the **order** of operations: `AddPrim(D_800A651C[...].a + otz * 4, q)` uses otz after. What if the first call's result were used in a *dead* way that combine folds into an existing instruction?

Let's think about `move s1,v0`: it's a copy from v0. Combine folds a copy when the destination pseudo has exactly one use and dies. If otz (the pseudo) had 2 uses, combine's `(set otz v0)` can't be folded into one of them; instead it would be folded into... combine tries i2+i3 where i3 uses otz. With 2 uses, the copy stays. 

So: give otz a second use that costs nothing. The second use must be in an instruction that already exists, e.g. as part of an address computation that folds. otz is used later in `D_800A651C[...].a + otz * 4`. That's the second otz (after func_801823D4).

What if we use the first otz value in a *comparison* that is then discarded... adds insns.

Hmm, what about the loop's `if (i != 11)`? no.

OK, alternative: **change what's copied**. What if the arg to func_801823D4 is not otz directly but something like `otz` read via a pointer? e.g. `pp`-like. No.

Let me look at the problem from the pass angle: is there a way to make combine not fold across an insn that survives? Yes: an insn that *uses* otz. The cheapest use is one that folds into an existing insn later. But combine is the pass that folds...

What if the use is in an insn that combine does not look at, e.g. a `use` in a call's USE list? Hmm.

Alternatively: can we make the first call result stored into otz via an intermediate that combine can't remove — e.g. `otz = RotTransPers4(...) ;` where otz is assigned twice in the same statement? 

Honestly, maybe try a few quick experiments:
1. `do { otz = RotTransPers4(...); } while (0);` + `do { } while (0);` before the second call (w3-like, but w3 had a bug in gen).
2. Put the second call inside a do-while but also adjust to restore the loop-2 registers (maybe score 36 is fixable by other means — but that's a lot).
3. Use `if (otz) { }`? no.

Wait — what about making the *arg copy* itself inside a do-while via a temporary statement:

```
do {
    otz2 = otz;
} while (0);
otz = func_801823D4(otz2, -0x1A);
```
No, adds a move.

Hmm, but actually, if otz2 is in the loop block and dies at the arg copy... combine folds (set otz2 otz) into (set a0 otz2)? If the loop block isn't merged with the successor, combine can't. Then RTL: (set otz v0), (set otz2 otz), (set a0 otz2) → 3 moves... unless cse2 already merged otz2 into otz (copy propagation) — cse does propagate copies across blocks? cse's copy propagation is within EBBs.

Hmm, 3 moves vs 2. Not good.

Let me reconsider the whole thing: maybe there's a different C spelling where the *first* otz assignment naturally materializes. What if the call result is stored to otz via a **conditional** that's cheap? no.

What if `otz` is used in the *loop increment* expression: `i++, otz`? no.

Hmm, hold on. What about making the second call's argument `otz` be evaluated *before* the first call's result is assigned... no.

Different idea: what if the first call's result is passed to func_801823D4 *and* the same value is needed for the `q->xy` pointers? no.

OK, let me look at what other bodies in this project did for "move s1,v0" pairs. Search moves.md for "move s1,v0" or "re-tie". Line 244: "the two pinned copies wrapped in do{}while(0) — the block splits cse1's ebb so sched1 keeps the $3 copy before the $4 copy". Line 219: do-while keeps a copy.

So the do-while around the *copy statement* is the canonical move. In our case, the copy is the call's arg setup. Wrapping the call statement in do-while (w4) changed loop-2 allocation. But maybe I can compensate: the loop-2 registers flipped s1/s2 (otz vs i). Since otz now has extra refs from the second do-while (its use at depth 2 in loop 2? no, the do-while is in loop 1).

Hmm, w4's diff showed the loop-2 `i` and `otz` swapped: target otz=s1, i=s2; w4 otz=s2, i=s1. The second do-while boosted otz's refs (its uses in loop1 at depth 2 now: otz used twice in loop1 at depth 2 → +2 each). That made otz's priority exceed i's.

Could we compensate by boosting `i`? i is the loop counter. Hmm, this is getting deep.

Alternative: maybe wrap only the *argument copy* portion by restructuring the statement so the copy is a separate statement inside a do-while... but the copy is generated by the call.

Hmm, what about calling func_801823D4 through a *function pointer*? That would change the call form (jalr) — no.

What about `otz = func_801823D4(otz, -0x1A);` → `otz = (s32)func_801823D4(otz, -0x1A);` no-op.

OK — radical but simple idea: **make otz's first value used by the second call's second argument**? No.

Let me look at the actual RTL again: insn 151 `(set r80 (reg v0))`, insn 164 `(set a0 (reg r80))`. Combine combines them because r80 is dead after 164 (single use). 

What if r80 had REG_RETVAL/REG_EQUAL... 

What if we could get the *front end* to emit the arg as a separate variable that is used twice? E.g.:

```
otz = RotTransPers4(...);
func_801823D4(otz, -0x1A);
```
The result of func_801823D4 is assigned to otz anyway. No.

What if `otz` is used in the `AddPrim` call's address *for the first value*? no.

OK. Let me try a few cheap experiments in a batch, and if none work within budget, mark WALL with the evidence. But note the target has just this one residual (score 3) — very close. Let me spend a few more tries.

Experiments:
A. w5: wrap the RotTransPers4 call in do-while (as w2) AND add a second statement inside the same do-while that uses otz in a foldable way, e.g. `do { otz = RotTransPers4(...); otz = otz; } while (0);` — self-assign folds.

B. w6: use `do { otz = RotTransPers4(...); } while (0);` and then `do { otz = func_801823D4(otz, -0x1A); } while (0);` (w4) but ALSO boost `i` to compensate. Meh.

C. w7: make otz's first set appear from a *different* expression: `otz = RotTransPers4(...)` then `otz = func_801823D4(otz, -0x1A)`. What if instead: `s32 t = RotTransPers4(...); do { } while (0); otz = t; otz = func_801823D4(otz, -0x1A);` — hmm, t's set then otz's copy then arg copy: 3 moves.

D. What about making the call's arg a *cast* that forces a move: `func_801823D4((s32)otz, -0x1A)` — no-op.

E. What if otz is declared `volatile`? no.

F. What if we use the value twice by making the second call take otz twice in a foldable second arg... e.g. `func_801823D4(otz, -0x1A)` where the second arg is `-0x1A`. What if we write `func_801823D4(otz, (otz & 0) - 0x1A)`? fold → 0.

G. **Use a comma in the loop body**: e.g. `for (; i < 12; )` with `otz = RotTransPers4(...)` then... 

H. What about making the *loop condition* use otz? no.

I. What about the dead-reset trick (C0414): `otz = RotTransPers4(...); otz = 0;` — no, destroys value.

J. What about a **second set that combine can fold**: `otz = RotTransPers4(...); otz = otz | 0;`? tree folds.

K. What about `otz = RotTransPers4(...) + 0x0;`? tree folds.

Hmm, tree-level folding kills most.

L. What about `otz = RotTransPers4(...); if (otz < 0) { otz = -otz; }`? adds branches.

M. What about using a `switch (otz) {}`? adds compare.

N. **What if the value is used in the loop's if-test via a ternary that folds?** no.

O. What if the *second* call is written as `otz = func_801823D4(otz, -0x1A)` but the first call's result is passed through the *second* call's arg via a temporary that has 2 uses: e.g. `func_801823D4(otz, -0x1A)` where we add a second call using otz? adds a call.

Hmm.

P. What about making otz an **array element**: `otz[0] = RotTransPers4(...)`? that's a store — extra.

Q. What about declaring `s32 otz` and using `*(&otz)`? folds.

Let me reconsider the problem: maybe it's not combine but *cse2*? The dump at cse2 shows the copy present. And combine's output folds. So combine.

Combine's try_combine for i2=(set r80 v0), i3=(set a0 r80): the LOG_LINK. If I could break the LOG_LINK — e.g. by having the loop's back edge... 

Hmm, actually wait! What if instead of a do-while(0) around the call, we use a *real* loop structure whose back edge isn't removable, e.g. `for (j = 0; j < 1; j++) { otz = RotTransPers4(...); }`? jump_optimize can still see the trip count? Probably not (it's a variable loop with one iteration) — the back edge stays, so the block is a real loop, and combine won't fold across blocks (combine only works within a block via LOG_LINKs). That would keep the copy! But it adds the loop overhead: init, compare, branch — 3 extra insns. Unless the loop is the *existing* for loop... 

Hmm, what if the RotTransPers4 call is placed in a block whose successor differs? Like inside an `if` that's always true but not provably: e.g. `if (i >= 0)` — the compiler can't prove i>=0? i is s32, `i >= 0` is not provable → emits slt/bnez = 2 extra insns. No.

OK so blocking combine without insns is hard.

Completely different approach: **make otz's first set not a copy from v0**. If the call's result were combined with something else... e.g. `otz = RotTransPers4(...) ; ` — what if we assign it to a different variable `t` and then use `t` in TWO places, one of which is the arg copy and the other is... the second call's result? no.

Hmm, hold on. What about the AddPrim call: `AddPrim(D_800A651C[*(u16 *)&D_800B9A02].a + otz * 4, q);` — the first arg is `... + otz*4`. otz here is the *second* value. 

What if we restructure the loop to use the first otz value in the AddPrim too? no, order.

I think the practical answer: try wrapping the second call (w4) and compensate the loop-2 register swap. Let me look at w4's numbers via alloc_table to see the priorities and find a compensating move. That's a bigger search.

Alternatively, try: wrap the second call in do-while AND remove the do-while around the first call, but then pp loses the boost... unless the second do-while also boosts pp? No, pp isn't used there.

Hmm, what about putting the pp use inside the second do-while? no.

Wait — maybe a different way to boost pp: the first do-while is what gave pp its ref boost. What if instead we boost pp by wrapping the RotTransPers4 call in a do-while that ALSO contains the arg copy... 

Actually here's a thought: what if we put BOTH calls inside ONE do-while(0) block?

```
do {
    otz = RotTransPers4(...);
    otz = func_801823D4(otz, -0x1A);
} while (0);
```
Then combine folds within the same block (both in the loop block) — no good.

What if the do-while contains only the second call, and the pp boost comes from... the loop depth of the first call must be ≥1.

Alternative pp boost: make pp's use *nested* in a loop by using it in the existing for loop (already depth 1). Need +1 ref: use it twice per iteration (2 refs at depth 1 = +2 each = 4 total refs). Could pp be used twice per iteration cheaply? E.g., pass `pp` to RotTransPers4 (already) and also... 

OH WAIT. What about `pf`? pf is used in loop 2 three times. pp only in loop 1. What if loop 2's `&p` argument were `pp` — that gives pp +3 uses at depth 1 (in the loop). Target: `addiu a2,sp,40` at 30b4, 30f4, 3134 — three separate addius. If pp were used, we'd get `move a2,s7` — mismatch. Unless pp is NOT in a register... no.

Hmm.

Alternatively: what if `p` and `flag` are read/written in a way that adds a use of pp? E.g. after loop 1: `*pp = p;`? adds a store.

OK, let me take yet another angle: what if we DON'T need pp at all — i.e., can the *address* be held in s7 by cse naturally without a variable? In w0, pp was a variable with 3 refs. What if we pass `&p` directly (no pp variable)? Then the address pseudo `&p` (a constant address) would be cse-hoisted into a register... with what ref count? The constant address pseudo might have 1 ref (the single use) — but cse creates a pseudo in a register that's live across the loop, giving it more refs? Hmm, the *hoisted* pseudo is the address expression `(high (symbol_ref))` etc.

Actually, in the target the address is in s7 = a register holding `sp+40`. This is the classic "loop-invariant address hoisted by cse/loop". If we write `&p` directly, cse will create a pseudo for the address in the loop preheader, with n_refs = 2 (def + use). Same as pp! So it would behave like pp (3 refs with loop weighting).

Hmm, so no difference.

Let me now consider: what if we give up on pp's natural allocation and instead accept the 8-score w0? No, we want MATCH.

Time check: it's been a while on item 1 (~40 min?). Let me check the clock.

Actually, let me try a small batch of promising variants quickly (cheap scoring), then decide:

w5: w2 + wrap the second call in `if (otz == otz) { ... }`? adds insns. skip.

w6: w2 but the first call's result assigned through a `s16`? adds insns.

w7: w2 + `otz = otz;`? folds.

w8: w2 with the second call's arg spelled `(s32)(u32)otz`? folds.

Hmm.

NEW IDEA: What if we make the *first* otz assignment happen in a separate basic block that is a real block — by putting it inside the existing `if (i != 11)` / else structure? No...

NEW IDEA 2: The `do { } while (0)` around the *first* call created a loop block. What if we place the *second* call inside the SAME loop but as the loop's *exit condition*... no.

NEW IDEA 3: What if the loop becomes `do { ... } while (++i < 12)` — the existing for loop is `for (; i < 12; )`. Changing the loop shape changes lots.

NEW IDEA 4: What about assigning the call result to otz *twice* in the source: 
```
otz = RotTransPers4(...);
otz = otz;     /* self-assign — folded by the front end */
```
no.

NEW IDEA 5: `otz = RotTransPers4(...); if (i == 11) otz = otz;` — folded.

Hmm.

NEW IDEA 6: what if the value passed to func_801823D4 is `otz` but we compute it as `otz - 0`? folds.

Let me look at the actual front-end: maybe `(s32)(u32)otz` no.

OK, what about a *different* variable width that costs no insn: `u32 otz`? same mode.

Let me look at what makes combine fold: `combine.c` combine_simplify... The fold of (set r80 v0) into (set a0 r80) happens because of the LOG_LINK and REG_DEAD. What if r80 is used in an insn that combine doesn't process — like a `NOTE`? no.

What if we add a `(void)otz;` statement? Folded at tree level (no RTL).

Hmm, `(void)otz` — gcc's tree for a cast-to-void of a variable: does it emit RTL? A COMPOUND_EXPR? Actually `(void)x;` as a statement produces no RTL (it's a no-op).

What about `sizeof`? no.

What about `if (otz) ;` — an empty if statement. The front end might emit a test. gcc's parser: `if (otz) ;` → cond with an empty body; the tree optimizer might remove it as having no side effects. Likely removed.

What about `otz ? 0 : 0;` as a statement → removed.

What about a *volatile read*: no.

Hmm, what about using otz in the loop's `for` increment: `for (; i < 12; i += (otz, 1))` — the comma with otz... fold to 1.

What about `i += otz * 0;` — fold.

Front-end folding is thorough for constants.

**What about an opaque-but-real operation that combine can remove: a redundant extension?** E.g. `otz = (s32)(s16)otz;` costs 2 insns (sll/sra) but combine might fold them into the uses if the value is known... no, unknown.

Hmm, but wait: would `(s16)otz` add 2 insns? Yes: sll + sra. Target has 162; w2 has 161; adding 2 → 163. Unless the sll/sra fold into something. No.

OK — what about accepting the second do-while (w4) and fixing the loop-2 swap? In w4, otz=s2 and i=s1, target otz=s1 and i=s2. That's a priority flip between otz and i in the second loop. otz got boosted by the second do-while (its uses at depth 2 in loop 1). i's refs: i is used in both loops (test, increment, i != 11). 

Could we boost i? E.g. `i` used more. Or reduce otz: the do-while is in loop 1; otz's uses in loop 1 are at depth 2 now (3 uses: set, arg, and... ). 

Alternatively, wrap the second call in do-while only in loop 2? No, we need it in loop 1.

Hmm, what if we wrap the second call in loop 1 with a do-while and *counter-balance* by wrapping something that boosts i? i's refs at depth... 

This is getting long. Let me check the time budget. Started 23:05; the item budget is 20-30 min. It's probably ~23:50 now. I'm over budget on item 1 already. Per the brief: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item".

Hmm, that's for WALL. But this item is at score 3 with a clear path. Let me give it a few more tries but track time.

Let me check the time.
