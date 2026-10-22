---
ts: 2026-10-22T00:22:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OALiFZKXDJqCUEfxtwYM
---
The residual: 13 (COUNT), 88 vs 89 ins.

Target:
```
13 andi v0,v0,0x3      ; mode = value & 3
14 move v1,v0          ; v1 = mode  (a COPY — the launder's tie!)
15 sh v0,254(s0)       ; store mode
...
35 (j)                | lw v1,32(s0)   <- the target has an extra lw v1,32(s0) earlier
```
Mine:
```
13 andi v1,v0,0x3      ; mode computed directly into v1
16 sh v1,254(s0)
```
So in the target, `mode` is computed into v0, then COPIED to v1 (the "move v1,v0") — the copy is the launder's re-tie! The launder `__asm__("" : "=r"(v1) : "0"(v1))` creates a copy (zero-byte) that becomes a real "move v1,v0" in the output!

So the launder here materializes a MOVE instruction. That's a "copy" lever. To reproduce without the asm: we need a C-level copy that gcc emits as a move.

In C: `v1 = mode;` where mode is a separate variable → gcc would emit a move (if it doesn't coalesce). But cse would coalesce the copy (mode is dead after) → the value stays in v0 and the store uses v0.

In the target: `andi v0,v0,0x3; move v1,v0; sh v0,254(s0)` — so the store uses v0 (mode) and v1 is the copy. The copy survived because the launder made v1 opaque (cse couldn't propagate the copy into the store).

So: the launder's effect = a real copy that cse can't fold. In plain C, how to force a copy that survives?

Option: use `mode` AFTER the copy in a way that keeps both alive:
```
mode = ...;
v1 = mode;
... use v1 ...
... use mode ...
```
Here both are used → no copy elimination! But the target's uses: v1 is used in the comparisons (v1 == 1 etc.) and mode is used in the store `unkFE = mode`.

In the current source:
```
((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
v1 = mode;
__asm__("" : "=r"(v1) : "0"(v1));
if (v1 == 1) ...
```
The store uses mode, and v1 (the copy) is used in the comparisons. If I remove the asm, gcc coalesces v1 = mode (both are the same value) → the store uses v0 and the comparisons use v0 → no move.

To force the copy to survive: the two values must differ in a way cse can't merge. E.g. make the comparisons use a *different* expression of mode that gcc can't prove equal? Hmm.

Alternative: since the target's copy is v1 = v0 (a register move), maybe we can get gcc to emit a move by making the two values have different "shapes": e.g. v1 = mode as a *different width*? A move is a move.

Hmm: what if v1 is used in a way that requires it to be a separate register: e.g. the comparisons `v1 == 1`, `v1 >= 2`, `v1 == 0` — gcc would compare v0 directly.

Idea: use a compound assignment to create a real 2nd set? E.g.:
```
v1 = mode;
v1 |= 0;   /* no-op */
```
no.

Hmm, what about the *other* launder (on e, at 3317)? The target has "lw v1,32(s0)" at 36 (mine has it at 44). So the e launder moves the load of e earlier.

Hmm, this item is complex. Let me consider the "compound assignment" trick here:
- For v1: we want a copy that survives.
- What if we write `v1 = mode;` and then use v1 in a compound assignment? e.g. `v1 &= 0xFFFFFFFF;`? That's a no-op semantically but creates an in-place op... gcc would fold `x & 0xFFFFFFFF` to x (no insn) but might keep the 2nd set. Hmm! Actually that's exactly the trick: `v1 &= 0xFFFFFFFF;` might create a real 2nd SET of v1 (in-place AND with a no-op mask) → killing the birth boost of `v1 = mode`... but the target's issue is a COPY (move), not a boost.

Hmm, wait. Let me re-read the target:
```
13 andi v0,v0,0x3
14 move v1,v0
15 sh v0,254(s0)
```
So the target computes mode in v0, copies to v1, and stores v0. Mine computes mode directly into v1 and stores v1.

If in plain C we had `v1 = mode;` (with cse NOT coalescing), gcc would emit: andi v0 (mode), move v1,v0 (the copy), sh v0 or sh v1? The store uses mode → v0. That matches the target!

So the crack: make gcc keep the copy. The launder makes v1's copy opaque (cse can't propagate v1's value back to mode, and can't propagate mode into v1).

How to keep the copy in plain C? The copy is eliminated when one of the two is dead after the copy. Here: after `v1 = mode;`, mode is used by the store (which happens BEFORE the copy in the source: `unkFE = mode;` then `v1 = mode;`). So at the copy point, mode is DEAD (its last use is the store) → the copy is dead → cse removes it → v1 = mode directly.

In the target, the copy survives because the launder's asm output is "used" by the asm (the tie), and mode is dead → so the copy is dead → but the asm forces it to exist! Hmm, the asm's output is tied to v1, so the copy v1 = mode can't be removed (the asm needs v1's reg).

So in plain C: we need the copy to be non-dead. That means mode must be live AFTER the copy. E.g. move the store AFTER the copy:
```
v1 = mode;
((Unkstruct_800B5CB8 *)s0)->unkFE = mode;   /* hmm, but the store is in the target BEFORE? */
```
In the target, the order is: andi v0; move v1,v0; sh v0,254(s0) — the store comes after the copy, but the store's *value* is v0 (mode). So in the source, the store could be after the copy!

So: reorder to
```
v1 = mode;
((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
```
Hmm, but wait: then at the copy point, mode is still live (used by the store) → the copy survives → gcc emits andi v0, move v1,v0, sh v0 ✓✓ !!

But hold on: the copy is `v1 = mode` where mode is a variable; gcc would emit the andi into mode's pseudo and then a copy to v1's pseudo. If both are live, the copy is emitted ✓.

But there's a subtlety: the comparisons use v1, and the store uses mode. gcc's cse might still unify them? No — cse doesn't merge two live variables unless they're proven equal (it can do that via "make_regs_eqv" for copies when the source dies). Since mode is live (used by the store), the copy can't be folded ✓.

So the fix for the v1 launder: reorder the store after the copy.

But careful: the store `unkFE = mode` is currently before `v1 = mode;`. Also note the `mode` computation: `s32 mode = CAST_SIGN(u16, (u8 *)s0, 0x70) & 3;`.

Now the second launder (on e, line 3317): in the case1 arm:
```
case1:
    func_8001C810(...);
    callarg0 = 0x199;
    e = ((Unkstruct_800B5CB8 *)s0)->unk20;
    __asm__("" : "=r"(e) : "0"(e));
    argmode = 3;
shared:
    { s32 t = CAST_WIDTH(s32, e, 4); t |= 0x8040; CAST_WIDTH(s32, e, 4) = t; func_8012C658(...); }
```
The target has "lw v1,32(s0)" at 36 (in the case1 arm) and mine at 44 (later). So the e launder makes the load of e happen early (in the case1 arm, right after `e = ...`).

Hmm: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` — the load. Then the launder ties it. Then in the shared block, `CAST_WIDTH(s32, e, 4)` reads e+4.

In the target, the load "lw v1,32(s0)" is at 36 (in the case1 arm) and the "j 2084" at 37. In mine, the load is at 44 (in the shared block).

So the difference: the load's placement. With the launder (a 2nd set of e's reg), the load stays at its source position (early). Without it, the load is boosted (single-set) → sinks to its consumer (in the shared block) → later.

Hmm, so the same "birth boost" mechanism. To kill the boost: give e's reg a 2nd set. In C: `e = ...; e &= 0xFFFFFFFF;`? Hmm, that's a no-op AND. Would gcc fold it? `x & 0xFFFFFFFF` = x. gcc's fold would remove the insn but might keep the SET (a copy)... risky.

Hmm, alternatively: the compound-assignment trick that worked: `e |= 0x8040`? no, that's later.

Hmm, what about making the e value used twice so the load's dest has 2 uses? No — sets matter.

Wait, maybe I can use the same trick as for the pv case: in the pv case, `pv &= 0xFF000000` was a REAL semantic operation (the mask) that happened to be movable out of the expression. Here, is there a similar "mask" operation on e? In the shared block: `t = CAST_WIDTH(s32, e, 4); t |= 0x8040; CAST_WIDTH(s32, e, 4) = t;` — that's a read-modify-write of e+4 with |= 0x8040.

Hmm, but that's in the shared block (later), not at the e load.

What about: in the case1 arm, after `e = ...`, add `e &= 0xFFFFFFFF;`? Hmm.

Alternatively: maybe the e launder can be removed by a different route: the target's early load of e. What if the source's `e = ...` in the case1 arm were replaced by a direct use? E.g. the shared block does `CAST_WIDTH(s32, e, 4)`.

Hmm, hold on: what if we make `e` a *fresh* variable in each arm? The doc's S2 says: "CREATE the boost (def sits too EARLY, target has it sunk): make the value a fresh single-set local instead of reusing a multi-set variable." And "Kill the boost (def sits too LATE, want it at source position): add a 2nd SET that survives cse".

We want the load EARLY (source position) → kill the boost → 2nd set.

Hmm, what if e is assigned in BOTH arms (case0 and case1)? Then e's pseudo has 2 sets (one per arm) → the boost is killed! In the current source:
```
case0:
    func_8001C810(...); callarg0 = 0x199; e = ((Unkstruct_800B5CB8 *)s0)->unk20; argmode = 2; goto shared;
case1:
    func_8001C810(...); callarg0 = 0x199; e = ((Unkstruct_800B5CB8 *)s0)->unk20; __asm__(...); argmode = 3;
shared:
    ...
```
Both arms assign e → in the RTL, e's pseudo (or two different pseudos) — if it's the same pseudo with 2 sets → the boost is killed ✓. But then the launder would be unnecessary... yet the banked version has it in the case1 arm only. Hmm, because in the case1 arm the load must be EARLY (at 36) while in the case0 arm it's later?

Wait: the target's "lw v1,32(s0)" at 36 is in the case1 arm (the diff shows mine[35]=j, target[36]=lw). And mine has the load at 44 (in the shared block). So in the target, the case1 arm's load of e is materialized right there.

Hmm, and in the case0 arm? The case0 arm also assigns e = ... The target's code must have a load in the case0 arm too (or shares it). Since the diff shows only ONE difference region (the load at 36 vs 44), the case0 arm's load must be at the same place in both.

Hmm, actually if e is assigned in both arms with the same expression, gcc's cse would CSE them into ONE load (hoisted to the common part) — but the target has the load in the case1 arm. Hmm, cse can hoist a load to the common dominator... but the two arms are separate blocks; the load would be in each block unless CSE merges them (CSE can merge loads across blocks if they're the same and no aliasing in between — there's a call in between (func_8001C810) which kills CSE).

Hmm, so in the target, the case1 arm has its own load (at 36) and the case0 arm has its own (elsewhere). With the launder, the case1 arm's load stays at its source position (early). Without the launder, it sinks into the shared block (44) — the shared block is a common successor, so the load is moved there (gcc's "tail merging"/cross-jump optimization? or the load is CSE'd into the shared block since both arms load the same address?).

Hmm, since the shared block is reached from case0, case1, and case23, and the value e is only used in the shared block, gcc's cross-jump/hoisting might move the load into the shared block. With the launder, the case1 arm's load is tied (a 2nd set) → it can't be sunk/hoisted → it stays.

So for the e launder, the fix would be to keep the case1 arm's load in the case1 arm. In C: make the case1 arm use `e` in the arm itself? Hmm.

OK, let me take it step by step: first fix the v1 launder (the reorder of the store) and see the residual. Then handle e.

Let me try:
Candidate A:
```
        ((Unkstruct_800B5CB8 *)s0)->unkFE = mode;    <- moved AFTER v1 = mode
        v1 = mode;
```
i.e. swap the two lines:
```
        v1 = mode;
        ((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
```
Hmm, but the target's order is: andi v0; move v1,v0; sh v0,254(s0) — the store AFTER the copy ✓ (matches this swap).

And the e launder: keep it for now (only remove the v1 launder) to see the effect. Actually, I need to remove BOTH (the row kind is "launder" — the whole launder set must go). But for diagnosis, let me remove the v1 one and keep e's, then see.

Let me generate:
candA = base.c with the store moved after `v1 = mode;` and the v1 launder removed (keep the e launder).
candB = candA with the e launder removed.

Let me write the sed for candA from base.c:
- s|        ((Unkstruct_800B5CB8 \*)s0)->unkFE = mode;\n        v1 = mode;|        v1 = mode;\n        ((Unkstruct_800B5CB8 *)s0)->unkFE = mode;|

Careful: in base.c the launder line was removed, so the text is:
```
        ((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
        v1 = mode;
```
✓.

Then also candB: from candA, remove the e launder.

Let me do both in one sed -z command with h/g.

Also: I could also try a variant where the e load is kept in the arm: e.g. in the case1 arm, use e directly:
```
case1:
    ...
    e = ((Unkstruct_800B5CB8 *)s0)->unk20;
    argmode = 3;
```
Hmm.

Let me first do candA/candB.
