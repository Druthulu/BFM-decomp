# func_80185D44 (ov_SC06_029) — agent e22, P36 S104

**Result: score 0 with ONE marked lever (the tree's launder, re-marked in the step-9 format). Levers 1 -> 1.
No plain-C spelling found; the lever is argued irreducible below (proven on bytes for every alternative tried).**

## (a) The residual
Lever-free: score 2 (ORDER, 47 = 47 ins). The mask `0x7FFFFFFF` is emitted `lui a1,0x7fff` ... `ori a1,a1,0xffff`;
the target puts the `lui` FIRST in the block after `jal func_8001C214` (before `li v0,128`) and the `ori` after
`lw v1,32(s0)`; mine puts the `lui` after `li v0,-2`. Same instructions, one moved.

## (b) The pass and the decision
- cse.c `fold_rtx`: `m = 0x7FFF0000; ... m |= 0xFFFF;` folds to ONE `(set m (const_int 0x7fffffff))` at the `|=`'s
  position (mips.h:2669 `CONST_COSTS` returns 0 for every CONST_INT, so the constant always wins); the first set is dead.
  Seen in the `.combine` dump: insn 92 `(set (reg/v:SI 75) (const_int 2147483647))` after the `+0x18` store.
- sched.c:4830 `try_split` splits that insn by mips.md:3208 (`large_int`) into `lui`+`ori` (uids 112/113) with
  ADJACENT luids (`sched_analyze` numbers insns in order, sched.c:2170-2175).
- sched.c:2428 `rank_for_schedule` ties on `INSN_LUID` (higher luid picked first by the backward scheduler). The target's
  backward pick order is ... 60, **113 (ori)**, 66, 57, 54, 51, 48, 45, **112 (lui)**: the ori must beat `t = -2` (57) and
  the `lw v1` (66) on luid, the lui must lose to 45..57 on luid — i.e. luid(lui) < luid(45) < luid(57) < luid(ori), which
  two adjacent luids cannot satisfy. None of these insns gets the birthing boost (`t` is set twice, the split halves
  set reg 75 twice; `birthing_insn_p` sched.c:2469 needs `reg_n_sets == 1`), so priority does not break the tie either.
  => the original compiled the two halves as TWO RTL insns, which needs cse to NOT know m's value at the `|=`.

## (c) The move
None closes it in plain C. Delivered: the tree body with its one launder, marked
`// !FAKE: launder m — ... (P36 S104 e22 minimum-lever)`; `--try` = 0.

## (d) Generator proposal
When the residual is a `lui X,hi` / `ori X,X,lo` pair whose lui sits EARLIER than the lever-free placement and the ori
stays put, the source must emit the halves as two insns: try `m = HI<<16; <stmts>; m |= LO;` with the first set placed
at the lui's block position (a generator can compute that position from the target objdump); if cse folds it (it
always has so far), the case is a launder class for the STRUCTS phase, not a search target.

## (e) Tried and failed (bytes)
- `m = 0x7FFFFFFF;` placed before each of the 7 statement positions (scratch/gen1.py, g1/v0..v6): 4, 6, 2, 2, 2, 2, 2.
  v0 (at the top) puts the lui first as the target does but drags the ori with it (adjacent luids) — the prediction.
- `do { m = 0x7FFF0000; } while (0);` (cse1 stops at NOTE_INSN_LOOP_END, cse.c:8055) -> 2: cse2 (`after_loop`)
  ignores the note and folds anyway. Same with `t = 0x80` inside the do-while -> 2.
- `*(s32 *)(p + 4) &= m | 0xFFFF;` -> 2. The s104_all regen (R2-R41) best is also 2 (177 compiles), and an
  EXHAUSTIVE pass of every R-family candidate on body_free (244 candidates via `tools/delever.py recipe_candidates`,
  read-only import, scratch/regen.py) has best 2 too.
- m = 0x7FFFFFFF at 7 positions x the a0/p stores as struct vs non-struct accesses (scratch/gen3.py, 28 bodies): best 2
  — memory-dependence edges do not reach two halves of one split constant.
- Every cse-visible spelling of the constant (shift of a narrow const, union field insert, bitfield clear at bit 31)
  reaches the same `(const_int 0x7fffffff)` by reasoning (store_fixed_bit_field's `mask_rtx` is a CONST_INT); not all
  compiled.

## (f) Where the method fell short
Nothing in steps 12-16 targets a sched1 SPLIT insn; the luid arithmetic (adjacent split halves) is the whole answer and
it needs the `.sched` ready-list trace plus the pre-sched `.combine` order, not the allocation table.
Survey: across the 4,284 baseline objects, lui/ori gaps >= 4 are common, but the ones I sampled (func_8017E590,
func_80183A70, func_801810B0, func_801439FC) are all reorg filling a branch delay slot with the lui — a different, natural
mechanism that does not apply here (no branch after the call).

## (g) Structs
No. The lever keeps a CONSTANT opaque to cse's constant folding; giving `p`/`a0` struct types changes the addressing
of the stores (aggregate MEM flags, expr.c:4568-4577) and so possibly their dependence edges in sched, but it cannot
stop fold_rtx from folding `0x7FFF0000 | 0xFFFF`, which is what forces the single insn. The split needs the halves to
be distinct RTL, and no struct shape produces that.
