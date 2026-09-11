# func_80185484 (src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c) — d39, P36 T7 S104 — CLOSED at 0, zero levers

**Final: score 0 (54/54 ins, byte-identical), plain C.** Levers 2 → 0 (both `launder`s, sites.txt lines 6739/6747;
the `$17` pin was already REMOVED). Start: body_free.c = 8 (the sweep's best, R12 `u16 h`, = 7).

The change against `body_free.c`:

    -    s0 = h >> 8;
    +    s0 = (s16)h >> 8;
    -    r = h2 >> 6;
    +    r = (s16)h2 >> 6;

That is S104 step 13's (d13) move, `(s16)t >> N` on the shift's operand, applied at both sites. Both casts are needed:
h's alone scores 5, h2's alone scores 4, both score 0 (`scratch/c2.c`, `c3.c`, `c1.c`). The delivered `body.c` also
drops three pieces of decompiler noise, and each drop was checked at 0: the dead `a0 = 1;` (`scratch/c4.c`), the
`ent = a0` copy (a0 is used directly), and the `p` temp (inlined). S104 (d24) says to delete a top-of-body
`T x = argN;` copy, and here doing so costs nothing.

## Copies: the same text closes all four definitions of this class (each `--try` at 0)

| function | TU | file | score |
|---|---|---|---|
| func_80185484 | src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c | body.c | 0 |
| func_801857A8 | src/ov_SC03_089/ov_SC03_089_jr_8017CA80.c | scratch/copy_func_801857A8.c | 0 |
| func_80183318 | src/ov_SC03_104/ov_SC03_104_jr_80182038.c | scratch/copy_func_80183318.c | 0 |
| func_8018632C | src/ov_SC03_091/ov_SC03_091_jr_8018326C.c | scratch/copy_func_8018632C.c (C name `aF8018632C`, keeps its body-local `func_8012F568` 6-arg extern) | 0 |

The copies were found with `grep -rn "0x4201, 0, 0x1C" src/`, which gives exactly four sites. Each copy differs only in
its `D_` table symbol and its C name.

## (a) The residual
COUNT +2 (56 vs 54). Both s16 field loads come out as `lhu; sll 16; sra 16+N` where the target has `lh; sra N`:
`lhu s0,24(v0)` … `sll s0,16; sra s0,24` vs `lh s0,24(v0)` … `sra s0,8`, and `lhu v0,26(v0); sll v0,16; sra a0,v0,22`
vs `lh v0,26(v0); sra a0,v0,6`. The two branch-target hunks are the +2 displacement. No register or order defect.
The two laundered values are exactly the two shifted values.

## (b) The pass and the decision (proved on the dumps, `scratch/dumps_free/free.i.cse`)
- Expand (`mips.md` `extendhisi2`, `force_not_mem` at -O2) emits each `(int)*(s16 *)` read as `movhi` + `ashift 16` +
  `ashiftrt 16`.
- cse1 `fold_rtx`'s associative-shift block (`cse.c:5577-5667`, `lookup_as_function (…, ASHIFTRT)` at `:5594`) folds
  `h >> 8` into `(ashiftrt (reg 84) (const_int 24))` and `h2 >> 6` into `(ashiftrt (reg 91) (const_int 22))`. Both are
  visible in the free compile's `.cse` dump (lines 57-58 and 152-153 of the function's range). Each shift then reads
  the `ashift` temp directly.
- combine can no longer merge the extension back into the load, so no `lh` is formed. In d13 the obstacle was the temp's
  second reader (`combine.c:1458`). Here h itself is dead after the fold, so the `sra 16` dies too. What remains is
  `lhu` + `(ashiftrt (ashift x 16) 24)`, which combine does not turn back into `lh` + `sra 8`. I did not trace which
  exact combine attempt fails for this shape. The cse fold itself is proved.

## (c) Why the cast closes it (bytes proven; same mechanism as d13, dumps not re-traced for the close)
`(s16)h >> 8`: with a constant right shift of an operand that narrows to short, `c-typeck.c:2418-2450` (short_shift)
does the shift in `short`. Expand then re-extends `(subreg:HI h)` through a second extension pair built on h's OWN
pseudo, not on the load's temp. cse folds into that new pair instead, so the load's extension stays intact and
combine forms `lh`. Because `num_sign_bit_copies(h) = 17 > 16`, combine's `simplify_shift_const`
(`combine.c:7930-7944`) collapses `(ashiftrt (ashift h 16) 16+N)` to `(ashiftrt h N)`. The value is unchanged,
because h is already a sign-extended s16.

## (d) GENERATOR PROPOSAL
When the residual shows `lhu; sll 16; sra 16+N` where the target has `lh; …; sra N`, rewrite EVERY constant right
shift `v >> N` whose operand `v` was loaded from an `s16` and has that residual shape as `(s16)v >> N` (`(s8)` for
`lbu`/`sra 24+N`). Enumerate the subsets of those sites. This body needed both of its two sites. d13's needed one of
two, because the second site's cast broke allocation. The tell is mechanical: the mine-side shift count is target+16.
This is the "narrow the shifted operand at the use" family that d13 proposed. This class is its second independent
confirmation, now across 4 more bodies.

## (e) What did NOT work (all `--try`)
| spelling | score |
|---|---|
| body_free.c (start) | 8 |
| sweep best, R12 `u16 h` | 7 (wrong signedness, `srl`) |
| `(s16)h >> 8` only | 5 |
| `(s16)h2 >> 6` only | 4 |
| `s16 h; s16 h2;` declarations, no cast (`scratch/c5.c`) | 8. The declaration width is inert, as d13 found |
| body-local struct `{ u8 pad[0x18]; s16 x, y; }`, field reads, no cast (`scratch/s1.c`) | 8 |

## (f) Where the method fell short
Nowhere that mattered. Step 13's (d13) line described this residual exactly and closed it on the first `--try`. The
only gap is the one d13 already reported: no sweep family puts a cast on a use site. Had R-families had a "cast the
shifted operand" rule, this class (4 bodies) and d13's (5 bodies) would have closed in the free sweep. The cookbook's
§197-A advice ("do not chase it with casts") remains the stale entry to correct.

## (g) Structs answer
Inert, and proven on bytes. Giving `*(ent + 0x20)` a struct type with `s16` fields at 0x18/0x1A (`scratch/s1.c`)
scores 8, the same as body_free. The deciding pass is cse's shift re-association on the extension pair
(`cse.c:5594`), which is keyed on the value's TYPE AT THE SHIFT. It is not a memory/aliasing decision
(`expr.c:4568-4577` does not enter into it). So this lever was a type-at-use problem, not a struct problem. A struct
type is still the right readability move for the struct phase (`ent->sub->x >> 8` would need the same `(s16)` cast,
or an equivalent).

## Signature note (not changed)
The TU declares `extern void func_80185484(s32)` and defines the body as `s32` under an asm alias. The early exits
return 0 (`move v0,zero` in the delay slots). The final path falls off after `func_8012F568`, so `$v0` is whatever
that call returned. That is consistent with `return func_8012F568(…);` in the original, but nothing in this body reads
`v0` as a keepalive. I left it as the tree has it; it is a candidate for the STRUCTS/signature phase only.
