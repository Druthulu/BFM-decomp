---
ts: 2026-10-22T00:24:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GtiFar9SPiEEMsssPhlW
---
Now I can see the target's structure:

```
11 lhu v0,112(s0)      ; mode = (u16)s0->unk70
13 andi v0,v0,0x3      ; mode & 3
14 move v1,v0          ; the launder's copy
15 sh v0,254(s0)       ; store mode (unkFE)
16 li v0,1
17 beq v1,v0,2064      ; if (v1 == 1) → case1
18 slti v0,v1,2        ; v1 < 2
19 beqz v0,202c        ; → case0
21 beqz v1,2040        ; v1 == 0
23 j 20f4              ; tail
25 slti v0,v1,4
26 beqz v0,20f4        ; v1 >= 4 → tail
28 j 20a0              ; case23
30 lw a0,32(s0)        ; case0: e = s0->unk20
31 lui a1,0x0
32 addiu a1,a1,0
33 jal func_8001C810
35 li a0,409
36 lw v1,32(s0)        ; e loaded AGAIN (case0's e load at 30 AND 36?)
37 j 2084
38 li a1,2             ; argmode = 2
39 lw a0,32(s0)        ; case1: e = s0->unk20
40 lui a1,0x0
41 addiu a1,a1,0
42 jal func_8001C810
44 li a0,409
45 lw v1,32(s0)        ; the e launder's load, in the case1 arm
46 li a1,3             ; argmode = 3
47 lw v0,4(v1)         ; the shared block: t = *(s32*)(e+4)
48 move a2,s0
49 ori v0,v0,0x8040
50 jal func_8012C658
51 sw v0,4(v1)
52 j 20f4
```

Interesting! In the case0 arm: "lw a0,32(s0)" at 30 (the call arg) and "lw v1,32(s0)" at 36 (the e load, at the end of the case0 arm, after the call). In the case1 arm: "lw a0,32(s0)" at 39 (call arg) and "lw v1,32(s0)" at 45 (the e load, at the end of the case1 arm).

So in BOTH arms, the e load is at the END of the arm (after the call). And the shared block (at 47) uses v1 directly — the load is NOT in the shared block!

So the target has the e load in each arm, at the end of the arm. My candC (e launder removed) put the load in the shared block (at 44).

So the fix: keep the load of e in each arm (not sunk into the shared block). This is a *cross-jump/cross-jump-optimization* artifact: gcc moved the load into the shared block.

How to prevent that in plain C? The load is `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` — assigned in each arm, used in the shared block. gcc's "cross-jump optimization" (cross_jump) can move code into the common successor. Also the RTL "sinking" of a load into a common block.

Since the load is in each arm already (in the source), the target's shape is natural. But gcc sank it to the shared block. Why? Because the load is single-set → boosted → placed as late as possible → in the shared block (its consumer). Hmm, no: the boost makes it sink to just before its consumer, and the consumer is in the shared block. Hmm, but "just before its consumer" would still be in the shared block.

Hmm, in the target the load is in the arm (before the jump). So the load's position = its source position (the arm). So the boost is killed in the target (the launder gives e's reg a 2nd set) ✓ same mechanism as before.

So: to kill the boost for e's load, e's pseudo needs 2 sets. The two arms each assign e → but they're in different blocks → the SAME pseudo e has 2 sets! (e is a function-level variable assigned in both arms.) Hmm! So e's pseudo should already have 2 sets → no boost → the load should stay in the arm. But in candC the load moved to the shared block.

Hmm, unless gcc split e into two pseudos (one per arm) — or the "cross-jump" optimization moved it.

Hmm, wait: in candC, the case0 arm's load is at 30 (the call arg "lw a0,32(s0)") and the case1 arm's at ... the diff showed mine[44]=lw v1,32(s0) vs target[45]. So in mine there's ONE load in the shared block (at 44) and the target has one in each arm (36 and 45). So gcc CSE'd the two arms' loads into one in the shared block (both arms load the same address, and after the calls... hmm, the calls could modify memory, so CSE across the call is invalid; but gcc's "cross-jump" moved it).

Hmm, actually: with the e launder in the case1 arm only, the case1 arm's load can't be CSE'd with the case0 arm's (the launder makes it opaque) → so the target has 2 separate loads (36 in case0, 45 in case1). In candC (no launder), gcc merged them into one in the shared block → 88/89 ins? The diff said mine 89 = target 89. Hmm, both 89.

So: in candC, the two arms' loads were merged into one (in the shared block) and... the count stays the same because the other insns are the same. Hmm, so the target has 2 loads and candC has 1 load? Then the counts would differ by 1. Unless in candC, the case0 arm's load at 30 (the call arg "lw a0,32(s0)") is separate.

OK whatever: the shape differs. In the target, each arm has its own e load; in candC, one load in the shared block.

To get 2 separate loads in plain C: the two arms' loads must not be CSE-able. CSE merges them if they're the same expression and no memory clobber in between. But there IS a call between them (func_8001C810) — a call clobbers memory, so CSE shouldn't merge loads across it. Hmm, but the loads are in different blocks that both flow into the shared block: CSE would consider the shared block as a candidate place for the load (if it's "safe" — the memory state at the shared block differs per path, so gcc's CSE must prove the memory is the same → it can't (a call in between) → so it can't merge).

Hmm, so why did candC merge them? Maybe it didn't merge: maybe in candC the case0 arm's load is at 30 ("lw a0,32(s0)" — that's the call arg, a different address? no, the same address 32(s0)).

Hmm: in the target, the case0 arm has "lw a0,32(s0)" (30) and "lw v1,32(s0)" (36) — TWO loads of the same address! (One for the call arg a0, one for e.) And the case1 arm has "lw a0,32(s0)" (39) and "lw v1,32(s0)" (45).

So the target has 4 loads of s0->unk20 (2 per arm). In candC: the case0 arm has "lw a0,32(s0)" (30) and the case1 arm has "lw a0,32(s0)" (39)... and the shared block has "lw v1,32(s0)" (44). So 3 loads. But the counts are equal (89) — hmm, so maybe candC has 4 loads elsewhere. Whatever.

The key: in the target, the e load is in each arm (not merged into the shared block). In candC, it's in the shared block.

In plain C, how to keep the e load in the arm? Idea: use e in the arm itself! E.g. in the case1 arm, the launder's tie made e's reg "used" by the asm. In plain C, we could use e in the arm in a way that's free (no extra instructions)... e.g. `e = e;`? (identity, disallowed, and folded).

Hmm, what if the arm's code uses e in a computation that's already there? In the case1 arm:
```
case1:
    func_8001C810(...);
    callarg0 = 0x199;
    e = ((Unkstruct_800B5CB8 *)s0)->unk20;
    argmode = 3;
shared:
    { s32 t = CAST_WIDTH(s32, e, 4); t |= 0x8040; CAST_WIDTH(s32, e, 4) = t; func_8012C658(callarg0, argmode, (s32)s0); }
```
The shared block does `CAST_WIDTH(s32, e, 4)` = *(s32*)(e+4).

What if the shared block is restructured so that each arm does its own work? I.e. duplicate the shared block into both arms:
```
case0:
    func_8001C810(...); callarg0 = 0x199; e = ...; argmode = 2;
    { s32 t = CAST_WIDTH(s32, e, 4); t |= 0x8040; CAST_WIDTH(s32, e, 4) = t; func_8012C658(callarg0, argmode, (s32)s0); }
    goto tail;
case1:
    ... same with argmode = 3 ...
```
Then the loads stay in the arms ✓ (each arm has its own load, used locally). But the generated code would then have TWO copies of the shared block → more instructions than the target (which has one shared block). Unless gcc's cross-jump optimization re-merges them (it does: cross-jump merges identical blocks — but then the load might move to the shared block again... hmm, cross_jump merges the tails; the loads are before the merge point?).

Hmm. The target's shape: the shared block is entered from case0 (j 2084 at 37), case1 (falls through at 45-46), and case23 (at 54-56?). Hmm, actually looking at the target: 37 "j 2084" → 2084 is the shared block; the case1 arm falls through to 47 (the shared block) directly.

So the target has the shared block with 3 predecessors, and the e load in each of the two arms that set e (case0 at 36, case1 at 45).

For gcc to produce that, the load must not be hoisted/sunk into the shared block. gcc's RTL sinking: the load is in the arm's block; the shared block uses e. Since the load is in the arm and the use in the shared block, the load could be sunk into the shared block (it's "safe" only if the memory is unchanged — but a call intervenes in the *other* arm... hmm, for the case1 arm: the load at 45 is AFTER the call at 42; the shared block is after that → sinking is safe for that path but not for the case0 path (where the load at 36 is also after the call)).

The reason gcc sank it: the load's dest pseudo (e) is single-set in the merged version...

OK, I need to stop the deep analysis. Practical: try the "duplicate the shared block" restructuring, and other variants:

V-a: duplicate the shared block into each arm (case0, case1) and remove the goto shared.
V-b: in each arm, use e in a way that keeps it alive: e.g. assign `p4 = e + 4`? Hmm, that changes the code (the target computes "lw v0,4(v1)").

Hmm, V-a: after duplication, gcc's cross-jump may merge the two blocks back into one (the tail merging) — and the loads? The loads are in the arms before the merge → they'd stay ✓.

Let me try V-a. But the source's `shared:` label is also reached from case23? Let me look: case23 (line 3329-3338) does its own thing and falls into `tail:`. And `goto shared` is from case0 and case1 only. Let me re-read the source:

```
    check4:
        if (v1 >= 4) goto tail;
        goto case23;
    case0:
        func_8001C810(...); callarg0 = 0x199; e = ...; argmode = 2; goto shared;
    case1:
        func_8001C810(...); callarg0 = 0x199; e = ...; [launder] argmode = 3;
    shared:
        { s32 t = CAST_WIDTH(s32, e, 4); t |= 0x8040; CAST_WIDTH(s32, e, 4) = t; func_8012C658(callarg0, argmode, (s32)s0); }
        goto tail;
    case23:
        ...
    tail:
        ...
```
So `shared` has 2 predecessors (case0 via goto, case1 by fallthrough).

If I duplicate the shared block into case0 and case1 (each with its own `goto tail`), then there are 2 identical blocks → gcc's cross-jump would merge them into one (tail merging) → the merged block would be the shared one, and the loads would be... hmm, cross_jump merges the ENDS of blocks: it would create a common tail. The loads (before the merge point) stay in the arms ✓. But then the merged block's e value: each arm has its own load; after merging, the shared block uses e — but e differs per path?! Since both arms load the same address, the values are the same but gcc can't know that (calls in between) → it would need phi nodes → gcc 2.7 has no phi → it can't merge the blocks if e differs!

Hmm, so duplicating the shared block would produce 2 copies of the block in the output (more instructions) → not the target.

Hmm. But wait: in the TARGET, the shared block uses v1 which was loaded in each arm (2 different loads of the same address) — the target's shared block has a single predecessor? No: 37 "j 2084" (from case0) and the case1 arm falls through to 47. So the shared block has 2 predecessors and uses v1 (loaded in each arm) — with NO phi. That's possible because both arms load the SAME address, and the loads are "equivalent" from gcc's perspective? But gcc can't merge them (a call in between could change the memory)...

Hmm, actually gcc's RTL for the case0 arm: the load happens after the call (at 36, after the jal at 33) ✓ and the case1 arm's load at 45 is after its call (42) ✓. So each load is after its own call → each is valid at the merge point ✓. gcc's RTL would have: in each arm, a load into a pseudo; at the merge, the pseudo must be the SAME (no phi) → so gcc must have used the SAME pseudo e for both loads → then e's pseudo has 2 sets ✓ → no boost → the loads stay in their source positions (in the arms) ✓✓✓.

So in the TARGET, e's pseudo has 2 sets (one per arm) → the boost is dead → the loads stay in the arms.

And in candC, the loads got merged into the shared block: because with the launder removed... hmm, why? The launder was only in the case1 arm. Removing it → in the case1 arm, e's load's dest is a temp with 1 set → boosted → sunk to its consumer (the shared block) → and then the case0 arm's load (also boosted) → hmm.

OK, so the difference is that in the target, the case1 arm's load is NOT boosted (the launder gives it a 2nd set) → stays in the arm.

So the fix: make the case1 arm's load of e have 2 sets (or otherwise not be boosted). In plain C: e's pseudo already has 2 sets (both arms assign e)! But gcc apparently created a separate temp for the case1 arm's load (or the launder was needed for another reason).

Hmm, wait. In the target, the launder's tie is in the case1 arm: `__asm__("" : "=r"(e) : "0"(e));` — a copy of e's reg. So in the target, the case1 arm's load is a copy-ish thing: the load writes a temp T, then the asm's tie copies T into e's pseudo? Hmm, actually: `e = load` → T = load; the asm's output = a copy of e's reg...

Ugh, whatever. The point: the launder's tie in the case1 arm makes the case1 arm's e value "opaque" so that gcc's cross-jump/cse can't merge the arms' loads.

So in plain C: to keep the case1 arm's load separate, the two arms' loads must not be merged. gcc merges them if it can prove the memory is unchanged between the load and the merge point. In the case1 arm: the load is at the end of the arm (after the call) and the merge is right after → the load could be sunk to the merge point. In the case0 arm: the load at 36 (after the call at 33) then "j 2084" → the merge point.

Both arms' loads are "after their call" → so at the merge point, the memory state is unknown per path → gcc can't have ONE load for both → it must keep 2 loads (in the arms) OR sink one to the shared block (which requires the memory to be the same on all paths → it isn't) — hmm, but candC DID put a load in the shared block.

Hmm, in candC, maybe gcc sank the case1 arm's load into the shared block and kept the case0 arm's load in its arm. Then the shared block's load is only executed on the case1 path, and the case0 path's e value (in the arm) would need a phi → impossible → so gcc would have to duplicate the shared block.

Hmm, but the count stayed 89. So maybe candC kept both loads in the arms but at different positions? The diff showed:
```
36  j	207c | lw	v1,32(s0)
37  --      | j	2084
44  --      | lw	v1,32(s0)   (insert)
44  lw	v1,32(s0) | --
```
So mine has the load at 44 (in the shared block, or at the end of the case1 arm?) and the target at 36 (end of case0 arm) and 45 (end of case1 arm).

Hmm, mine[44] = "lw v1,32(s0)" — where is that? In mine, the case0 arm ends with "j 207c" at 36 and the case1 arm at 39-43 (call), then 44 = the load, 45 = ... So in mine the load is in the case1 arm but AFTER the "li a1,2" (argmode=2)? Hmm, the diff at 36: mine "j 207c" vs target "lw v1,32(s0); j 2084" — so in mine, the case0 arm does NOT have the e load; it jumps directly. And in mine the e load is at 44 (in the case1 arm or the shared block).

So in candC, gcc sank the case0 arm's e load into the shared block (or merged them). Since the case0 arm's e load was at 36 in the target, in candC it moved later.

OK, so the fix for the e launder: keep the case0 arm's load of e in the case0 arm. Hmm, but the launder is in the case1 arm! And its effect was to keep the case1 arm's load in the case1 arm (at 45), and consequently the case0 arm's load also stayed in the case0 arm (at 36) — because the merge was prevented (the two loads couldn't be unified).

In plain C (candC), the two arms' loads got unified into one in the shared block (at 44) — that's the "cross-jump" merging.

To prevent the unification in plain C: make the two arms' loads provably different? They're the same address...

Hmm, what if the case0 and case1 arms use DIFFERENT expressions for e that gcc can't unify but that produce the same code? E.g.:
- case0: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;`
- case1: `e = *(s32 *)((u8 *)s0 + 0x20);`   (the same address, different spelling)
CSE would unify them (same address, same type) → merged. Hmm, CSE's alias analysis: the same base+offset → the same → unified.

What if one of them is spelled through a `volatile` pointer? That changes the code (a volatile load is the same instruction, but it can't be CSE'd or sunk!). Hmm! `*(volatile s32 *)((u8 *)s0 + 0x20)` — the load instruction is identical (lw), but volatile prevents sinking/merging!

But is a volatile load a "lever"? It's not in the AB_KINDS list (pin, barrier, launder, keepalive, instruction, gte-lever, asm-body). Hmm, but "no new lever of any kind" — a volatile load is a "barrier"-ish thing (it prevents reordering). The lever census might classify volatile as class C/D ("a byte-needed `volatile`"). The brief says the row kind is "launder" and the constraint is "no new lever of any kind". A volatile pointer cast is arguably a new lever (it forces the load to stay). Risky. And the census may flag it.

Hmm.

Alternatively — maybe the whole item is a WALL. The two launders here are: (1) a re-tie that produces a real `move` (unreproducible in plain C due to cse-copy-merge), and (2) a re-tie that keeps a load in its arm (unreproducible without volatile/asm).

Given the doc's S2 ("Kill the boost: add a 2nd SET that survives cse — the re-tie ... A plain C reassignment does NOT work if cse/flow can eliminate it"), and the t5/t6 proofs, I think this item is a WALL with tag "cse-copy-merge" (for the v1 part).

But before declaring a WALL, let me try 2-3 cheap variants:
(a) The v1 part: make the copy survive by using `mode` after the copy in a way that prevents the merge: e.g. the store uses mode AFTER the copy (tried — cse merged anyway).
(b) What if v1 is assigned from a *volatile* source? no.
(c) What if we avoid the copy entirely by making the comparisons use `mode` directly and v1 something else? The target HAS the copy, so we need it.
(d) What if the copy is made "real" by using a union/pointer trick: e.g. `v1 = *(s32 *)&mode;`? That forces a memory access. no.
(e) What if the copy is `v1 = mode;` where mode is `volatile s32`? → the store `unkFE = mode` would re-load. Hmm: with `volatile s32 mode = ...;` the load happens once (at the init) and each read is a re-load → extra instructions. no.

Hmm, what about making the copy survive by using a *different type* for v1 that forces a conversion... e.g. `v1 = (s32)(u8)mode;`? The conversion is a no-op (mode ∈ 0..3) → folded.

What about `v1 = mode + 0;`? Folded.

So (a)-(e) fail. Let me consider the PARTIAL option: remove just the e launder (candC = 6, not 0) — not 0, so no PARTIAL there. Remove just the v1 launder (candD) — let me score it; if it's 0, then PARTIAL:launder (the e launder kept) — but the v1 launder removal alone doesn't help since the e one is the problem... let me check.

Let me score candD (v1 launder removed, e launder kept).

Also, let me try the "duplicate the shared block" variant and a variant where the case1 arm's e is loaded via a different spelling.

Let me score candD first.
