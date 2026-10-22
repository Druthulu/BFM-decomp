---
ts: 2026-10-22T13:13:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bd6ldCgAGNiq0VkLi4yf
---
All 4 orig.c still match the current src ✓ (the "dumps" dir is my dump folder — I'll delete it).

Note the date: 07:13 — hmm, earlier the date showed 06:47 for the sweep and now 07:13. So my elapsed time is 06:37 → 07:13 = 36 minutes?! Hmm, but I thought more time had passed. The clock says 07:13. So the whole session is ~36 minutes of wall time. Hmm, but I estimated 3 hours — I was wrong (the model's internal sense of time is unreliable).

So the per-item wall times:
- All started ~06:37.
- Item 2's sweep: 06:47-06:50.
- Now: 07:13.

Hmm, so the total is 36 minutes for 4 items — well under the 20-30 min per item budget! Hmm, but the WALL requires "≥ 20 min and ≥ 30 scored tries on that item". Hmm! The tries are ≥30 ✓ but the wall time per item... The wall time per item: I did all 4 items concurrently-ish (I worked on items 1&2, then 3, then 4). The per-item wall time is hard to attribute. Hmm.

Hmm, "Budget 20-30 min wall per item (`date` at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

Hmm, this suggests: to record a WALL, the item must have had ≥20 min of work and ≥30 scored tries. My total session is 36 min for 4 items → ~9 min per item on average ✗ (below the 20-min minimum).

Hmm! So strictly, I haven't spent 20 min on each item. But the tries requirement is met (≥30 each).

Hmm. Should I spend more time per item? The budget says 20-30 min per item. With 4 items, that's 80-120 min total. I'm at 36 min. So I have time to spend more per item — and more tries might crack something!

Given that, let me continue working on the items, especially:
- Item 2/3 (the base-in-a-register problem): I've established the mechanism. More spelling exploration might not help... but let me think about the ONE thing that could work: a compare. Hmm.

WAIT!!! **A NEW IDEA FOR ITEMS 2/3!!!** What if the base participates in a compare that ALREADY EXISTS in the code — by *replacing* the bound variable's role?

In C2D0:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;      /* the bound */
    ...
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```
Hmm, what if the source used the BASE in the compare and the bound elsewhere? E.g., what if the loop's exit test were `if (it == p)` where `p` is... hmm.

**!!!!!!!!!! WHAT ABOUT THIS: THE LOOP'S EXIT TEST `it != p` COULD BE SPELLED `it - 0x10C != p - 0x10C`?** ✗ (different code).

**!!!!!!!!!! WHAT IF THE BOUND `p` IS SPELLED AS A *SUM OF THE BASE AND A RUNTIME VALUE*?** ✗.

**!!!!!!!!!! WHAT ABOUT MAKING THE BASE THE *OTHER* OPERAND OF THE EXISTING COMPARE BY REVERSING THE ROLES OF `it` AND `p`?**

Hmm: the compare is (it, p) where it = the loop pointer and p = the bound. What if the SOURCE were:

```c
    p = (s32)D_80120194;      /* p = the base */
    it = p + 0x10C;           /* hmm, the loop pointer = D_801202A0 ✗ (the reloc) */
```
✗.

Hmm hmm. What if:
```c
    p = (s32)D_80120194;      /* p = the base */
    bound = p + 0x658C;       /* the bound */
    it = (s32)D_801202A0;
    ...
    if (it == bound) goto zero;
```
The base's use is only in `bound = p + 0x658C` ✗ (1 use).

Hmm!!! But WAIT: what if the compare used `p` (the base) somewhere...

Hmm, what if the loop's exit test compared the pointer against the base+offset *inline*: `if (it != p + 0x658C)` → the compare's operand = (reg p + 658C) → if p's value is the base (a constant), cse folds `p + 0x658C` → the constant address ✗.

Hmm, unless p's value is NOT a constant...

OK OK. Let me think about the ONE remaining possibility: **make the base's value non-constant via a runtime value that's provably zero but not foldable**.

In C2D0: NO runtime values at all (a void function with no globals read). Hmm! But wait — what about the LOAD of `*(u16*)it`? That's a runtime value ✓ but it's inside the loop.

Hmm, what if the base were computed as `base = (s32)D_80120194 + (s32)(*(u16*)it)`? ✗ (semantics).

So item 2 (C2D0) is truly a WALL: the base is a compile-time constant and cse always folds it.

**BUT WAIT!!!** Hmm, what about the *pin* trick: the brief says pins may STAY. Could I ADD a pin? No ("never added").

Hmm, and for items 1/3, the same.

**HOLD ON!!! WHAT ABOUT THE `volatile` QUALIFIER?** Hmm: "no new lever of any kind". Is `volatile` a lever? In the lever census (dl.REMOVABLE / AB_KINDS), the kinds are: pin, barrier, launder, keepalive, instruction, gte-lever, asm-body. A volatile cast would be classified as... hmm, in the census, a volatile read is probably a "barrier" or "keepalive" kind. The lever_free_body docstring says: "A class C/D site the tree still carries (a byte-needed `volatile` cast or bare `register`) STAYS" — so a volatile cast is a class C/D site = a "byte-needed" thing, NOT a lever to be removed. Hmm! So adding a volatile cast is... hmm, it's a class C/D site (kept as ordinary C). But adding one is "adding a lever of another kind"? Hmm, class C/D sites are not levers (they're not in AB_KINDS). Hmm!

Hmm, "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

Hmm, "no pin, launder, barrier, keepalive macro or asm" — a volatile cast could be seen as a barrier/keepalive ✗. I'd rather not.

Hmm, BUT: would a volatile even help? `volatile u8 *vp = D_80120194;` — the ADDRESS is still constant ✗ (the volatile affects the loads, not the address).

Hmm, what about a volatile READ of a global? ✗ (an extra load).

OK. So items 1-3 are WALLs. I'm confident in the mechanism now (verified by the cc1 RTL dump: the launder makes the value opaque; cse substitutes the constant address into the use; without the launder the address is rematerialised/folded).

**AND ITEM 4**: the mechanism is the free second set. The best is 4 (one extra `andi` + the ay+117 sink).

Hmm, let me spend a bit more time on item 4 since it's the closest (4). The remaining issues:
(a) the extra `andi s4,s4,0xffff` (by's (u16) zero-extension on the pinned $20).
(b) the ay+117 (addiu s1,s1,117) sink: the target has it late (after the index chain), mine early.

For (a): the andi comes from the zero-extension of a 32-bit value to 16 bits. Hmm! **WHAT IF by's 2nd set is a 16-bit value that GCC knows is already in range?** Hmm.

**!!!!!!!!!! IDEA: WHAT IF THE 2ND SET IS `by = (u16)by;` BUT by's VALUE AT THAT POINT IS THE RESULT OF A *16-BIT* OPERATION, i.e. by's VALUE IS ALREADY ZERO-EXTENDED?** Then the andi would be redundant — but GCC 2.7 has no VRP ✗.

**!!!!!!!!!! IDEA: WHAT IF THE 2ND SET IS SPELLED `by = by & 0xffff;` WHERE by IS u32 → the same andi ✗.

**!!!!!!!!!! IDEA: WHAT IF WE DON'T GIVE `by` A 2ND SET BUT GIVE `ax` TWO 2ND SETS?** Hmm, o3/o4 showed both are needed.

**!!!!!!!!!! IDEA: WHAT IF THE 2ND SET IS ON A *DIFFERENT VARIABLE* THAT THE TARGET ALSO 2-SETS?** The target's 2 sets are on ax and by (from the launders). Hmm.

Hmm, hold on: **what if the 2nd set could be achieved by a variable that is READ (not written) twice?** Hmm, "2 sets" = 2 definitions.

Hmm, what about the `mat` variable (pinned $23)? It has 1 set (the initializer) + `mat += 0x18` (a 2nd set!) ✓ — mat already has 2 sets naturally!

Hmm! And what about `white`? 1 set. `in`/`out`? The structs.

Hmm, so the target's ax/by 2 sets must come from the source.

**!!!!!!!!!! THE BIG QUESTION: WAS THE ORIGINAL'S ax/by REALLY 2-SET? OR DID THE ORIGINAL HAVE A DIFFERENT SHAPE THAT PRODUCED THE SAME SCHEDULING?**

The decompiler inserted the launders to match, so the original differed. Maybe the original had ax/by as *different variables* (e.g. the original computed the corner-1 values into separate variables that were reused in corner 3, giving them more refs → a higher priority → a different allocation).

**!!!!!!!!!! WHAT IF THE ORIGINAL HAD *MORE* VARIABLES (e.g. separate temps for the corner-1 and corner-3 values)?** Hmm! The current source reuses ax/by/ay/bx for both blocks. If the original had, e.g., separate variables for the second block (ax2/by2/ay2/bx2), the priorities would differ → a different allocation/scheduling ✓.

Hmm! But the target's registers are reused (s0/s1/s2/s4 in both blocks) → the same variables (or a coalesced copy) ✓.

Hmm, hmm. What if the original had the second block's values assigned from the first block's variables (as now) ✓ — that's the current source.

OK, let me try a few more item-4 variants on the theme "give ax/by a real 2nd set for free":

- r1: `by = (u16)by;` with by declared **u16** and ax declared u16 too, but the 2nd set is a *copy from a 32-bit temp*... hmm.

Hmm, what about this: **the 2nd set could be a 16-bit truncation of a 32-bit value that GCC computes for free: `by = (u16)(bx - 0x5D);` — hmm, the value is wrong (bx changed).

Hmm, hold on!!! What if we change the SOURCE so that `bx` is NOT modified in place, and instead the second block's bx is computed from a saved value? Hmm, the target has `addiu s2,s2,-87` (bx = bx - 0x57) in the first block ✓ and the second block uses bx (s2) ✓ — the same variable.

Hmm, so `by` = bx_old - 0x5D and bx_new = bx_old - 0x57. What if the source computed by from bx_new: `by = bx - 6` (after bx's update)? Then the ORDER of the source statements changes: bx = bx - 0x57 first, then by = bx - 6 ✓ — and the target's order is by, ax, bx, ay — hmm, the source order would be ax, bx, by ✗ (the target's order is by first).

Hmm! But the scheduler can reorder. Hmm, and the values: by = bx_new - 6 = bx_old - 0x5D ✓ CORRECT!

So: the source could be:
```c
        bx = out.vy;
        ay = out.vx;
        ax = ay + 0x7B;
        bx = bx - 0x57;
        by = bx - 6;             /* = the old bx - 0x5D */
        ...
```
Then by's 1st set is `by = bx - 6` — hmm, but then by has only ONE set ✗ (we need 2 sets).

Hmm, and the extra addiu ✗.

OK. Let me try to kill the andi differently: **what if by's 2nd set is `by = (u16)by;` and by is declared u32, but the by PIN is changed from $20 to... hmm, the pin is what forces $20.

Hmm, hold on! **WHAT IF THE `andi` IS ACTUALLY FINE — i.e., what if the TARGET has an andi somewhere that I'm misreading?** The target's 207 insns: the diff showed mine[85] = `andi s4,s4,0xffff` with no counterpart ✗. So no.

**!!!!!!!!!!! WHAT IF THE 2ND SET IS A *STORE* OF by TO THE STACK AND A RELOAD? ✗ (2 insns).

**!!!!!!!!!!! WHAT IF THE 2ND SET IS `by = (u16)by;` AND by IS DECLARED u32 AND THE STORES USE `by` — AND WE COMPENSATE THE EXTRA INSN BY MAKING ANOTHER INSN DISAPPEAR?** Hmm! The target has 207 and mine has 208. Is there an instruction in the target that my body could avoid? E.g., the `op` launder's removal already avoided something. Hmm, the target's `sh s1,36(sp)` etc. — all needed.

Hmm, what if the ay+117 sinking (issue b) means that in the target the ay+117 is scheduled into a DELAY SLOT (free)? Let me look: the target's 153c `addiu s1,s1,117` — the instruction before is 1538 `addu a1,a1,s5` and the branch at 1590 (jal). Hmm, so 153c is not in a delay slot. Hmm, but wait: maybe there IS a branch between 1538 and 153c? The listing shows 1538: addu a1,a1,s5; 153c: addiu s1,s1,117; 1540: sh s1,36(sp). So no branch ✓ (the jal is at 154c, whose delay slot is 1550).

OK so the target's ay+117 is a regular insn placed after the index chain.

**ISSUE (b) FIX**: the ay+117's position. In the target, the order in that region is: [by, ax, bx addiu's] → [the index chain: sll, addu, sll, addu] → [ay+117] → [the stores]. Hmm, so the index chain comes BEFORE ay+117. In mine (n1): [by, ax, bx addiu's] → [ay+117] → [the index chain] → [the stores].

Hmm, so in the target the index chain is scheduled earlier (before ay+117). Hmm, the index chain computes `aD800B9A02 * 0x14` — hmm, it's the address computation for the aGsSortLine argument.

So the target's sched2 puts the index chain before ay+117. In mine, ay+117 comes first.

Hmm, what would make ay+117 sink? A lower priority → hmm, or the "S2" thing: ay's 2nd set.

Hmm! Since ay is a u16 variable with 2 sets (ay = out.vx; ay = ay + 0x75), the 2nd set's pseudo is single-set → the birth boost → it gets boosted EARLY (mine). In the target, it's late.

To kill the boost: give the ay+117 pseudo a 2nd set too — i.e. ay would need a 3rd set! E.g. `ay = (u16)ay;`?? — ay is u16 → a no-op ✗ folded.

Hmm, what if ay were u32 with a (u16) cast → the andi ✗ + the loads would become lh ✗.

Hmm!! Wait, but what if the ay+117's pseudo's boost is killed by a different mechanism: hmm.

Hmm, in the ORIGINAL (with the launders), the ay+117 is late. The launders (on ax/by) affect the group. Hmm, but why would the ax/by launders affect ay's scheduling? The comment says "boost (same for by) -> by/ax/bx/ chain/ay revert to source order" — so the by launder's boost affects the whole chain including ay.

Hmm, in GCC's sched1, when a pseudo has multiple sets, the scheduler's "ready list" ordering changes.

Hmm, honestly: maybe the ay+117's position follows from the by/ax 2nd sets + the exact source structure.

Let me try: what if the 2nd sets are placed at a different position (q1 = 5, q2 = 25)? Hmm.

Let me try a couple more placements: the 2nd sets right before the second block's `prim.attr = 0;` (that's where they are now: after the first aGsSortLine) vs. right after `op`'s definition (before ay = ay + 0x75).

Hmm, in the current source, the order is:
```c
        {
        Gline_801372B0 *op = ...;
        [op launder]
        ay = ay + 0x75;
        prim.x0 = ay; prim.y0 = by; prim.x1 = ax; prim.y1 = bx;
        aGsSortLine(&prim, op, 0);
        }
        [ax launder]
        [by launder]
        prim.attr = 0;
        ...
```
So the launders are AFTER the first aGsSortLine. In n1, the (u16) casts are in the same place ✓.

Hmm, what if the casts were placed INSIDE the block (before the aGsSortLine)? Let me test that (r1).

Also: what if the casts were placed before `ay = ay + 0x75`?

Let me run a few placement variants. And also try the `op` handling: what if `op` gets a real 2nd set too (a plain-C equivalent)? The op launder was removed and the score went 25 → 24 (with the other levers). In n1, the op launder is removed ✓.

Let me run:
- r1: the (u16) casts placed inside the block, right after `op = ...;` (before ay = ay + 0x75).
- r2: the casts placed right before `prim.attr = 0;` (as now, but after the first aGsSortLine — that IS now).
- r3: the casts placed at the very start of the second block (before prim.attr = 0) — same as now.
- r4: n1 with `ay = ay + 0x75;` moved after the prim stores? ✗ semantics.

Let me test r1 and a couple of others, then wrap up.

Actually, let me also try: what if `white` is declared as u32 (it holds 0xFF) — the target has `li s3,255` ✓ and `sb s3,44(sp)` ✓ (a byte store). Hmm, with white as u32, the store would be `sb` ✓ (the truncation is free) and the li ✓. That might change the priorities/scheduling! Let me test that too.

And: what if `white` is declared u16? `li s3,255` ✓ + `sb` ✓.

Let me batch these.
