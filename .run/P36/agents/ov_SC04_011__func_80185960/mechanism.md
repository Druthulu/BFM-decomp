# func_80185960 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent d1)

**Result: score 0 in plain C.** No pin, no asm, no added volatile. Levers go from 1 to 0 (the `launder` at the old line 8802).
The class has 10 copies. They share the text, so the same edit should apply to all 10 (for example `func_80185DAC` in
`src/ov_SC06_032/ov_SC06_032_jr_80182890.c:5139`). The coordinator's gate decides that.

## (a) The residual in one sentence
Target: the sign test `(s16)diff < 0` appears twice, each time as `sll v0,a3,16; bgez v0`. Mine: cse computes the
sign-extension `sll/sra a3` once and the later `if ((s16)diff < 0)` reuses it. The count is 35 vs 33, and 12 of the
edit distance is the kept `sra` plus the `move` and `nop` that follow from it.

## (b) The pass and the decision (read, then proven on dumps and bytes)
- **cse, the skip-blocks path extension.** The lever-free text is `mag = diff; if ((s16)diff < 0) mag = -diff;`. That is
  a one-armed block: the branch jumps around one insn to a label with `LABEL_NUSES == 1` and no BARRIER before it.
  `cse_end_of_basic_block` (`cse.c:8101-8106` condition, `:8149` "Detect a branch around a block of code") keeps the
  path going PAST the join label. `invalidate_skipped_block` kills only `mag`, so the entry
  `(sign_extend (subreg:HI diff))` in reg 82 survives into the second test. The `.cse` dump of the free body shows it:
  `Processing block from 39 to 98`, and insn 62 tests reg 82. Because reg 82 now has 2 uses, combine can no longer
  fold `ashiftrt(ashift x 16) 16 >= 0` into `ashift >= 0`, and the `sra` is kept. `-fcse-skip-blocks` is an -O2 flag
  (`toplev.c:3390`).
- **jump1 undoes the obvious fix.** Writing `if ((s16)diff < 0) mag = -diff; else mag = diff;` does not help (score
  12). `jump.c:699-750` ("Simplify if (...) x = a; else x = b; → x = b; if (...) x = a;") rewrites the diamond back
  into the skip shape before cse. Its guard is `jump.c:739-741`: the ELSE value `b` must be a REG, SUBREG or constant,
  and here `b` is `diff`.
- **The ternary is dead too.** `mag = (s16)diff < 0 ? -diff : diff;` and `mag = (s16)diff >= 0 ? diff : -diff;` both
  score 12. When one arm is a NEGATE of the other, expand_expr's COND_EXPR singleton path (`expr.c:5808-5814`, emitted
  at `:5866-5890`) generates `mag = diff; if (!c) mag = -mag;` already in the `.rtl` (3 barriers, no diamond).

## (c) The move that closed it
```c
    if ((s16)diff >= 0) {
        mag = diff;
    } else {
        mag = -diff;
    }
```
This is an if/else with the NON-simple value (`-diff`, a NEG) in the ELSE arm. The jump.c:739 guard fails, so the
diamond survives to cse. Now the taken branch reaches a barrier-preceded else label (the follow_jumps case,
`cse.c:8116`), and the scan stops at the join CODE_LABEL (`cse.c:8039`). The `.cse` dump confirms it:
`Processing block from 38 to 54` ends at the join, and `56 to 103` starts with a fresh table. The second test then
recomputes its own `sll`, and combine folds each one into `sll; bgez`. The diamond lasts to `.sched2` (4 barriers) and
reorg removes it in `.dbr` (3 barriers): `move v1,a3` lands in the `bgez` delay slot, the same as the target. Proven
on bytes: `--try` gives score 0, 33/33 instructions.

## (d) Generator proposal
When the target recomputes a test (or any expression) after a one-armed `x = a; if (c) x = f(a);` block, and mine reuses
it from a kept register, rewrite the block as `if (!c) x = a; else x = f(a);`: an if/else whose ELSE arm holds the
non-REG/SUBREG/constant value. That keeps the jump.c:739 guard from collapsing the diamond, so cse's path ends at the
join. Never use a `?:` for this, because expr.c's singleton path collapses it at expansion. The row-3 move in
`residual_moves.md` ("put a real CODE_LABEL join between the copy and its use") was missing this precondition: which
arm must hold the non-simple value.

## (e) What did NOT work (byte evidence)
- The free body gives 12. `free_020` (diff as `s16`) gives 9: the reuse is still there, only one `move` fewer.
- `if (c) mag=-diff; else mag=diff;` gives 12 (jump1 collapses it, see above).
- `s16 mag` with the test on `mag` or on `(s16)diff` (v1/v2) gives 16. cse still matches the canonicalised
  sign-extension across the subreg.
- `(s16)mag < 0` on the copy (v3) gives 12, and both `diff`/`mag` as `s16` (v4) gives 12.
- Both ternary spellings (c3/c4) give 12 (collapsed at `.rtl`).

## (f) Where the method fell short / what helped
- `neighbours.txt` had no relevant note. The crack came from METHOD step 3's grep across the corpus for the same shape
  (`| 0xF000`). `src/ov_SC03_010/ov_SC03_010_jr_8017C730.c:3400-3405` records "a one-armed form leaves a barrier-free
  skippable block, -fcse-skip-blocks rides the equivalence past the join … MUST be a real if/ELSE". It does not say that
  the arm order matters. That is the jump.c:739 precondition added here.
- The free sweep (R2-R26) has no "if/else with the arms swapped" move or "one-armed → if/else" move, which is why it
  stopped at 9. A generator for (d) would have found this mechanically.
- Reading the `.cse` "Processing block from S to E" lines was the deciding measurement. It took one dump and was
  cheaper than an allocation table (this residual was not a register residual).

## (g) Structs question
No. The lever was a cse EBB-path effect on a pure register value (`diff`), and cse decides it from control-flow shape
(label use counts, barriers), not from memory. The only memory is `*cur` (a plain `u16 *`), and nothing in the defect
touches it. A struct type would not change the `expr.c:4568-4577` aggregate-vs-scalar channel here, because no store
has to be kept ordered against a load. Not tested: there was nothing to test.
