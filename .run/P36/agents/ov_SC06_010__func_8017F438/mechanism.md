# func_8017F438 (ov_SC06_010_jr_8017A4AC.c) — T7 e26, P36 S104

**Score 0, ZERO levers** (free start 18 = regen best 18). Tree levers: 4 (two `$2` pins on `val`, two `asm("")`
barriers) + 1 unmarked dead `s32 pad_[4]` -> 0 (no pin, no asm, no pad). The same text closes func_8017F600 (its own
pack) and the same-TU siblings listed in scratch/siblings.md.

The move (twice, once per attached object), plus the dead `pad_[4]`, `q`, `uVar1` and `val` deleted:
```
-        q = *(s32 *)(s0 + 0x20);
-        if (*(s32 *)(q + 4) < 0) {
-            u32 val;
-            val = *(u32 *)(p + 4);
-            uVar1 = val | 0x80000000;
-        } else {
-            uVar1 = *(u32 *)(p + 4) & 0x7FFFFFFF;
-        }
-        *(u32 *)(p + 4) = uVar1;
+        if (*(u32 *)(*(s32 *)(s0 + 0x20) + 4) & 0x80000000) {
+            *(u32 *)(p + 4) |= 0x80000000;
+        } else {
+            *(u32 *)(p + 4) &= 0x7FFFFFFF;
+        }
```
The one move that matters is the CONDITION: `x & 0x80000000` instead of `(s32)x < 0`. The per-arm compound stores are
readability; the free body's `uVar1`/`val` form with only the condition changed (and the pad deleted) also scores 0
(scratch/c4.c). With the pad kept, both score 6 (frame 56 vs 40).

## (a) The residual
Same 114 instructions, two identical defects: in the `< 0` arm the loaded word took `$v1` and the constant `$v0`
(`lw v1; lui v0; j; or v0,v1,v0`), where the target has `bgez …; lui v1,0x8000` (the constant in the branch DELAY SLOT)
then `lw v0; j; or v0,v0,v1`.

## (b) The passes and decisions (dumps: scratch/dumps_free, dumps_c1, dumps_c3, dumps_tree)
1. **With `< 0` the constant is born inside the arm.** Block 4 (the or-arm) has two quantities, the load r104 and the
   constant r105; sched1 must put the load first (its latency queues it: `.sched` "launching 117 before 120"), so the
   constant's life is shorter, `qty_compare` (local-alloc.c:1486-1507, 2-qty case) ranks it first -> `$v0`, load -> `$v1`.
   Even with the register order fixed (c1: the store written in each arm, so the load ties to the local ior result)
   reorg fills the `bgez` slot from the TARGET thread (`lui v1,0x7fff` of the else arm): a `ge 0` test is predicted
   taken (`mostly_true_jump`, reorg.c:1335-1420, GE vs const0 -> 1) and `fill_eager_delay_slots` tries the target
   thread first (reorg.c:3700-3712). Score 8.
2. **`x & 0x80000000` loads the mask BEFORE the branch.** The `.flow` has insn 111 `(set r104 (const_int 0x80000000))`
   and insn 112 `(set r103 (and r102 r104))` feeding the `eq 0` jump; cse gives the arm's `|= 0x80000000` the same
   pseudo r104 (the constant is already in a register). combine rewrites the `(eq (and x 0x80000000) 0)` test as the sign
   test `bgez`, deleting the AND, but r104 still feeds the arm's `or`, so its load stays in the block before the branch.
   sched2 places it last, and `fill_simple_delay_slots` moves it into the `bgez` slot from BEFORE the branch
   (reorg.c:2799ff., always safe) — the target's `bgez v0,…; lui v1,0x8000`. The arm now has one quantity (the load)
   -> `$v0`; r104 is block-global -> `$v1`.
3. **The frame's 16 bytes are the dead AND result, not a pad.** combine plants `(use (reg:SI 103))` for the eliminated
   AND result (combine.c:10831-10845; `.combine` insns 223/224, one per if); r103 then has a reference but no set,
   gets no hard register, and reload gives it a stack slot (`.greg`: `(use (mem:SI (plus sp 16)))`) -> frame 40, the
   target's. The tree's unmarked `s32 pad_[4]` was faking exactly these slots (with the bit test AND the pad: frame 56).
   Same artefact as d34's func_80181408 (METHOD S103 c35 / d34 (b)3).
The tree's levers faked (1)-(2): the `$2` pin forced the load into `$v0`; the `asm("")` at the head of the else arm
stops reorg's target-thread search (`stop_search_p` on an asm insn), so the slot came from the fall-through thread.
Proven on bytes (18 -> 8 c1 -> 6 c2 -> 0 c3; c4 = condition only, 0) and on dumps (`.flow` insns 111/112, `.combine`
`(use)`, `.greg` stack slot).

## (c) The moves
- Test the bit with its mask: `if (*(u32 *)(q + 4) & 0x80000000)` (both copies).
- Delete the dead `s32 pad_[4];` (the dead AND results size the frame now).
- Readability (also 0): the arms as `|= 0x80000000` / `&= 0x7FFFFFFF` on the field; `q`, `uVar1`, `val` deleted.

## (d) GENERATOR PROPOSAL
**R-bittest-mask**: when a body tests `(s32)X < 0` (or `>= 0`) and then sets or clears bit 31 (`| 0x80000000`,
`& 0x7FFFFFFF`) in the same if, emit the variant `X & 0x80000000` for the test (unsigned read) — and, if the body carries a
dead `pad[N]`, the variant without it. Trigger: a `bgez`/`bltz` whose delay slot in the target holds `lui rK,0x8000`
used later in one arm, or a frame larger than the locals explain. Generalises to any sign test followed by a use of the
sign-bit mask (combine turns the mask test into the sign branch but keeps the mask register cse shared).

## (e) What did not work (bytes)
- body_free: 18. All R2–R38 families: 18 (history.txt: temp/block/do-while/inline `q`).
- c1 = `< 0` with a compound store per arm: 8 (registers right, delay slot filled from the else arm, see (b)1).
- c2 = c1 + the bit test, pad kept: 6 (frame 56). c5 = free body + bit test, pad kept: 6 (frame 56).

## (f) Where the method fell short / what helped
- The residual looked like a local-alloc register swap (METHOD step 4); the register half WAS a 2-quantity ranking,
  but the delay-slot half is invisible in the residual hunk (the `lui` sits in the slot) and only the whole objdump
  (METHOD S103 step 1) shows that the constant lives BEFORE the branch in the target — which no spelling of a `< 0`
  test can produce. "A constant in a branch delay slot that one arm uses = the constant was computed before the
  branch — look for a test that uses it" is worth a line in step 3.
- The dead `pad_[4]` was an unmarked lever: re-check any pad against `.greg`'s `(use (mem sp…))` artefacts whenever
  the condition text changes (d34 said the same).

## (g) Structs
No. The decisive fact is the CONDITION's spelling (a mask test vs a sign test), which decides whether the mask constant
exists before the branch; a struct type for the model/object (`obj->flags |= 0x80000000`, `model->flags & 0x80000000`)
keeps every insn and would match only if the test is still written with the mask. The `expr.c:4568-4577` aggregate
channel (memory ordering) is not involved. The five sibling copies in this TU (scratch/siblings.md) suggest a shared
inline/macro "copy transform + mirror bit 31" in the original — worth a named helper in the structs phase.
