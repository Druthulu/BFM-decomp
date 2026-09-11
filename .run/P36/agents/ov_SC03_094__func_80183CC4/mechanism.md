# func_80183CC4 (ov_SC03_094_jr_8017BEBC.c) — P36 S104 agent d36

**Result: score 0, ZERO levers, plain C. SIGNATURE CHANGE: `void` → `s32`** (parked for the structs phase per Drew S104 (d),
like d29). The whole object is byte-identical for all FIVE copies of the class (`objdump -s -r`, every section plus
relocations, md5 against `.run/P36/delever/baseline/`). Negative control: `0x70` → `0x71` gives a nonzero score and "DIFFERS".
Levers before → after: 4 (pins `$2` `$16` `$3` + keepalive) → 0.

**The non-body edit the bank needs:** both file-scope prototypes `extern void func_80183CC4(s16 *a0, s32 a1);` (TU lines 6704
and 7113) become `extern s32 …`. `--try … --body` cannot test this (the old prototype conflicts with the new definition), so
every copy was scored as a WHOLE-TU candidate: `scratch/splice.py TU FN BODY OUT [DSYM]` rewrites the prototypes and splices
the body; `scratch/try.sh BODY [TU FN DSYM]` runs it through `delever_search.py --try` (no `--body`). Spliced TUs:
`scratch/tu_v2_<fn>.c`. The call sites (TU:6717, 6734, 7125) discard the result; whole-object identity proves them
unchanged.

## (a) The residual in one sentence
Two things: (1) the target RETURNS the object (`move v0,zero` on the null path, `v0` live to `jr ra`), which the tree faked with a
keepalive of `v0` at the end of a `void` body (the d29 shape); (2) with that fixed (score 28 → 6) one `move v1,s0` is MISSING —
the three `sb` stores read a COPY of `a1`, not `s0` itself (COUNT 40 vs 41).

## (b) The pass and the decision
- (1) In a `void` function `v0 = 0` on the else path is a dead store, deleted by flow's life pass (`insn_dead_p`,
  `flow.c:1705`, applied `flow.c:1479-1492`); the asm kept `v0` live. With `s32` + `return`, `expand_value_return` writes
  `$2` (`stmt.c:2873`) and the exit USE keeps it. (Citation from d29; the byte evidence here: `scratch/v_void.c`, the same body
  as `void` with `return;`, scores 28 — the free text's score.)
- (2) The missing copy is a WIDTH defect (S103 c4's rule, generator R20/R12 family): the tree's `v1 = s0` was `s32 = s32`, a
  same-mode register copy that cse puts in `a1`'s quantity and folds away (`cse.c:7440-7474` handles `(set REG0 REG1)`;
  canon_reg then routes the readers to the older register). The original value is NARROW: the stores are `sb`, and the value
  they read is `(u8)a1` — a QImode value made from `(subreg:QI (reg:SI a1))`, which is not a REG source, so it gets its own
  pseudo and the copy survives as `move v1,s0`.
  Byte-proven: `scratch/v1.c` (`u8 c = a1;`) → 0, `scratch/v1_s16.c` (`s16 c`) → 0, `scratch/v1_s32.c` (`s32 c`) → 6 (the copy
  folded, the stores read `s0`). The pass-level reading (which cse line deletes the SI copy) is NOT dump-proven; the width
  dependence is.

## (c) The moves that closed it
1. Return type `void` → `s32`; the `if (v0 != NULL) {…} else v0 = NULL;` + keepalive → `if (obj == NULL) return 0; … return
   (s32)obj;` (the house shape of the lever-free sibling `func_80181780` in the same TU, TU:5657, which calls the same
   `func_801290DC`).
2. The three byte stores as ONE chained assignment `*(u8 *)(sub + 0x24) = *(u8 *)(sub + 0x25) = *(u8 *)(sub + 0x26) = a1;` — the
   value of an assignment to a `u8` lvalue is the `u8` value, which supplies the QImode copy. (Equivalent at 0: a `u8 c = a1;`
   local, `scratch/v1.c`.) The pins' `s0 = a1; v1 = s0;` temps are deleted; `a1` is used directly.
Neither move alone closes: move 1 alone → 6, move 2 alone (void) → 28.

## (d) GENERATOR PROPOSAL
When a pinned copy `v = w;` (same width, `s32`) feeds ONLY narrow stores (`sb`/`sh` through `*(u8 *)`/`*(u16 *)` casts) and the
residual is a MISSING `move vN,sM` before them, re-declare the copy at the store width (`u8`/`u16`) — or, when the stores are
consecutive and store the same value, fold them into one chained assignment in REVERSE order (`*A = *B = *C = w;`) — and
combine it with d29's rule (a `void` function whose last statement is a keepalive of the call result / `v0` that the else arm
nulls → `s32`, `return 0;` early, `return obj;`, prototypes rewritten).

## (e) What did not work (byte evidence)
- Every generator family (R2–R37) on the `void` text: best 27 — none can change the return type, and move 1 is worth 22 of the
  28 points. R12 widened `s0`/`v1` to `u16`/`s16`/`u8` (history.txt) but only on the void text, where the missing `move v0,zero`
  and the register shuffle it causes swamp the gain.
- `s32 c = a1;` with the return fixed → 6 (the copy folds).

## (f) Where the method fell short
- `--try --body` cannot test a signature change (conflicting prototypes); whole-TU `--try` with a splicer is needed — d29 wrote
  the same splicer. A `--proto s32` flag on `--try` (rewrite the TU's `extern void FN(` prototypes) would make this a
  one-liner; the free sweep could then run d29's rule mechanically on every class whose tree ends in a `v0` keepalive.
- The brief's d29 note in METHOD step 15 was exactly the right pointer: the target's tail `j <epilogue>; sb …; move v0,zero`
  reads as a return value on the first objdump.

## (g) Structs answer
No lever remains, so a struct type is not needed for the bytes. Would it change a decision? No: every access is a constant-
offset store (plus one read-modify-write of `sub+0x4`) with no load that a scalar store could be scheduled past, so the
`expr.c:4568-4577` aggregate channel has nothing to act on. For readability the structs phase could give `obj` a type
(`+0x1C s32`, `+0x20 Sub *sub`, `+0x2C s32`) and `Sub` (`+0x04 u32 flags`, `+0x18/+0x1A u16`, `+0x20 void *`, `+0x24..+0x26 u8`
×3 set to one value, `+0x27 u8`, `+0x28/+0x2A u16`) — the same layout `func_80181780` (TU:5657) writes. Untested on bytes
(nothing to test against); the chained `u8` store must survive as a chained field assignment `s->b24 = s->b25 = s->b26 = a1;`.

## Copies (all score 0 through whole-TU `--try`, whole object IDENTICAL to baseline)
| function | TU | per-copy body | symbol |
|---|---|---|---|
| func_80183CC4 | src/ov_SC03_094/ov_SC03_094_jr_8017BEBC.c | PACK/body.c | D_801AE958 |
| func_80184FB0 | src/ov_SC03_097/ov_SC03_097_jr_80182B9C.c | scratch/ov_SC03_097__func_80184FB0.body.c | D_8019EAD4 |
| func_80180850 | src/ov_SC03_095/ov_SC03_095_jr_8017BEBC.c | scratch/ov_SC03_095__func_80180850.body.c | D_80194FF8 |
| func_80182288 | src/ov_SC03_093/ov_SC03_093_jr_8017D898.c | scratch/ov_SC03_093__func_80182288.body.c | D_801A46B4 |
| func_801803D0 | src/ov_SC03_096/ov_SC03_096_jr_8017BEBC.c | scratch/ov_SC03_096__func_801803D0.body.c | D_80193AAC (`u8[]`; `&D` works) |

Each TU needs its two `extern void FN(s16 *a0, s32 a1);` prototypes changed to `extern s32` (lines: 097 3661/4081, 095
4573/4985, 093 4618/5056, 096 4363/4783). func_801803D0 (096) carried a different lever text (pins `$2` `$3` `$2` + an else-arm
keepalive) — the same function; the same body closes it. No other TU declares any of the five names in the same overlay.
