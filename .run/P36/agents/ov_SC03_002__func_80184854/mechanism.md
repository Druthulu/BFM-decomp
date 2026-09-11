# func_80184854 (ov_SC03_002_jr_8018431C.c) — CLOSED, score 0, no lever (agent c40, S103)

## (a) The residual
Lever-free text: 65 ins vs 67. The `beqz $v0` after `func_8012CB64` is INVERTED into `bnez $v0,<epilogue>` with
`li $v0,1` in its slot and the `j <epilogue>` deleted; the target keeps `beqz $v0,<bne>` with a COPY of
`addiu $s1,$s1,0x10C` (stolen from the branch target, label advanced) in its slot, then `j <epilogue>; li $v0,1`.
Counted, not guessed: 2 instructions missing (the `j` and the duplicated `addiu`), every other difference is a
branch offset shifted by those two.

## (b) The pass and the decision (read in `tools/reference/gcc-2.7.2/reorg.c`, proven with `-dd` .dbr dumps)
- `fill_eager_delay_slots` (reorg.c:3632) asks `mostly_true_jump` (reorg.c:1335) for a prediction. For the
  `beqz $v0 -> continue` branch: `rare_destination` is 0 for both threads, the condition is EQ, so it returns 0
  (predicted not taken) and reorg tries the FALL-THROUGH thread first (reorg.c:3703-3720).
- The fall-through thread is `li $v0,1` / `j <epilogue>` (the `j` already holds `li $v0,1` from fill_simple's
  backward scan). `fill_slots_from_thread` stops on the SEQUENCE (`stop_search_p`, reorg.c:675) and
  `steal_delay_list_from_fallthrough` (reorg.c:1699) takes `li $v0,1` — nothing live at the continue label needs
  `$v0`. Then `relax_delay_slots`' "branch around an unconditional jump" (reorg.c:3784-3812) sees the now-empty `j`
  right after the branch and inverts the branch onto the `j`'s target, deleting the `j`. = the 65-ins text.
- The tree's `__asm__("")` before `return 1` worked because an ASM_INPUT insn stops the fall-through search
  (`stop_search_p`, reorg.c:699) with nothing to steal, so the target thread was tried next and the
  `addiu $s1` copied (INSN_FROM_TARGET_P, `/s` in the .dbr dump), and the branch's next active insn is the asm, not
  the `j`, so no inversion.
- **The plain-C close**: `mostly_true_jump` also scans forward from the branch's target label for a
  `NOTE_INSN_LOOP_VTOP` (reorg.c:1364-1372) and predicts TAKEN (1) if it finds one. That note exists only in a loop
  whose exit test jump.c's `duplicate_loop_exit_test` copied to the top (jump.c:2306 — a `for`/`while` loop, not
  the hand-rotated `if (p != end) do { } while (p != end);`). In the `for` version the continue label is followed by
  `NOTE_INSN_LOOP_VTOP` (the `.jump2` dump: `code_label 120` -> `note 144 NOTE_INSN_LOOP_VTOP`; the do-while version
  has `NOTE_INSN_LOOP_CONT` and no VTOP), so prediction = 1, `fill_eager_delay_slots` tries the TARGET thread first
  (reorg.c:3690) and copies `addiu $s1,$s1,0x10C` (the .dbr dump: `insn/s 122` in the branch's SEQUENCE), and relax's
  inversion test fails because the next active insn is the filled `j` SEQUENCE. Proven on bytes (score 0) and in
  the `.jump2`/`.dbr` dumps (`scratch/dumps_v2/`).

## (c) The move
Rewrite the hand-rotated `if (p != end) do { ... p += 0x10C; } while (p != end);` as the plain loop it rotates:
`p = D_801202A0; end = p + 0x6480; for (; p != end; p += 0x10C) { ... }`.
(Keep `p` assigned before `end`: `for (p = D_801202A0; ...)` with `end = D_801202A0 + 0x6480` above it scored 8 —
the `lui/addiu` of the end pointer then comes first and the start is derived as `end - 0x6480`.)

## (d) Generator proposal
When the only residual is a conditional branch INVERTED onto an epilogue jump (`bnez rX,<epilogue>` + the
return value in its slot, where the target has `beqz rX,<L+4>` + a copied loop-step instruction, then
`j <epilogue>` + return value) inside a loop written as `if (c) do { } while (c);`, rewrite the loop as
`for (; c; step)` / `while (c)` so jump.c emits NOTE_INSN_LOOP_VTOP and reorg predicts the branch to the loop's
continue point as taken; conversely, when the target shows the inverted form and yours has the copy, rotate the
loop into a do-while.

## (e) What did not work / was not needed
- `for (p = D_801202A0; p != end; p += 0x10C)` with `end = D_801202A0 + 0x6480;` first: score 8 (the
  prologue computes end first, start = end - 0x6480, s0 = end - 25714). The tail was already right (67 ins).
- The mechanical search's R7 do-while/block, R8 temps, R10 param copy, R12 width moves: all 9 — none of them
  touches the loop's form, which is what the prediction reads.

## (f) Where the method fell short
The header comment in the tree (written when the lever was banked) correctly named the pass (reorg's eager
filler + relax inversion) but not the prediction (`mostly_true_jump`), which is where a source-level handle
exists. Reading the delay-slot passes needs `-dd` (the .dbr dump), which `tools/cc1_dumps_tu.sh` does not write —
`scratch/dump.sh` adds it with a second cc1 run. A `NOTE_INSN_LOOP_*` diff between two `.jump2` dumps would have
found this in one step.
