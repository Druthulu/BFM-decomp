# func_800336A8 (src/800_b_2.c) — S104 agent e16 — CLOSED at 0, ZERO levers (1 barrier -> 0)

## (a) The residual
Score 7 lever-free (sweep best 6), COUNT 120 vs 121: ONE missing `nop` — reorg fills the `beqz v0,<mono>` delay slot of
the `if (D_800A4F19 != 0)` stereo/mono test with the stereo arm's head `sll v0,v1,1`; the target leaves it empty. Every
other difference is branch-offset fallout. The tree's lever was a `__asm__ __volatile__("")` at the stereo arm's head
(ASM_INPUT stops `fill_slots_from_thread`'s scan, `stop_search_p` reorg.c:675-704).

## (b) The pass and the decision
reorg.c `fill_eager_delay_slots` (reorg.c:3632-3736): `beqz` is an EQ test, `mostly_true_jump` returns 0
(reorg.c:1407-1408), so the owned fall-through (the stereo arm) is tried first and its head `sll v0,v1,1` is taken
unless it "sets a resource needed at the opposite thread" (reorg.c:3368-3369, `opposite_needed` from
`mark_target_live_regs` on the mono arm, reorg.c:2441-2766). The mono arm's head is a 2-word `lui/lhu` (not eligible), so
nothing else can fill the slot: the target's `nop` means `v0` counted as LIVE at the mono arm.

PROVEN on the `.jump2` dumps (scratch/free.j2 vs scratch/win.j2, both from `tools/cc1_dumps_tu.sh`): the only structural
difference is where the `n == 0` arm (`v = m;` = `move v0,a1`) is laid out. Lever-free (n == 0 arm first) the mono arm
falls straight into the shared `sh v0,10/8(a3)` tail. With the n == 0 arm LAST, the mono arm ends in `j L447` over the
n == 0 arm's `move v0,a1` (label 280), which is the target of the `beqz v1` (n == 0) branch.
READING (consistent with the bytes, not traced pass by pass): the `beqz v1` branch steals that `move v0,a1` from its
owned target thread into its own slot (the target's `beqz v1,…; move v0,a1`); `update_block` (reorg.c:2233-2249) leaves
a `(use (insn move v0,a1))` marker where the move was; once relax deletes the mono arm's `j` to the next active insn
(reorg.c:3945-3970), the mono arm falls through that marker and `mark_target_live_regs`'s forward scan marks every
register the marked insn sets as live (reorg.c:2696-2704) — so `v0` is in `opposite_needed` and the `sll` is refused.
NECESSITY PROVEN on bytes (scratch/v/x1_nomove.c): the same n == 0-last layout with the n == 0 arm storing `m` directly
(no `move v0,a1` to steal) fills the slot with the `sll` again.

## (c) The move that closed it (PROVEN on bytes, `--try` 0)
Invert the outer if/else: `if (n == 0) { v = m; … } else { clamp; stereo/mono }` ->
`if (n != 0) { clamp; stereo/mono } else { v = m; … }`. No other change; the tree's barrier and its comment deleted.
The bytes are identical because jump/cross-jump/reorg re-derive the same final layout (the n == 0 path still becomes
`beqz v1,<sh tail>; move v0,a1`).

## (d) GENERATOR PROPOSAL
When the residual is ONE missing `nop` in a conditional branch's delay slot (the fall-through arm's head stolen) and the
tree carries a zero-byte `asm("")` barrier at that arm's head, try inverting an ENCLOSING if/else whose trivial arm
(a register copy + the same stores as a sibling arm) comes first: put the trivial arm last. Its copy gets stolen into
the outer branch's slot, and the `update_block` USE marker (reorg.c:2233) makes the copied register live at the inner
branch's target, which denies the steal the barrier was faking. (Arm-order/polarity is residual_moves.md row 10; this is
the case where the arm to swap is the ENCLOSING one, not the one whose slot differs.)

## (e) What did not work (bytes)
- Inverting the D_800A4F19 test itself (`== 0` / `!D_800A4F19`, mono first): 25 (mono laid out first).
- `switch (D_800A4F19)` default-first: 7; case-0-first: 25. A marked `do { stereo } while (0)`: 7 (notes do not stop
  the scan; the loop's start label is unused and deleted by jump).
- `if (D_800A4F19 == 0) { mono; goto next; } stereo`: 25. Stereo products into two temps `l`/`r`: 14.
  `v = m;` hoisted above `if (n == 0)`: 7. `D_8007319E[0x80 - n]` without `q`: 13; `(D_8007319E + 1)[0x7F - n]`: 7.
- The sweep (320 compiles, R5/R7/R8/R9/R10) never swaps an if/else's arms, which is the move.

## (f) Where the method fell short
The residual points at the D_800A4F19 branch; the fix is one level OUT (the enclosing `n == 0` if/else). Reading reorg's
liveness (`mark_target_live_regs` + `update_block`'s markers) from the source is slow and the `.dbr` dump drops the USE
markers before it is written; an enumeration of "swap every if/else's arms" would have found it in seconds. That
enumeration belongs in the generator set (it is cheap: one compile per if/else in the body).

## (g) Structs
No. `Chan336A8`/`Voice336A8`/`Req336A8` are already structs here; the decision is reorg's register liveness across a
branch, not an aggregate/scalar alias question.
