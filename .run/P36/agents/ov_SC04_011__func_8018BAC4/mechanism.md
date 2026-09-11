# func_8018BAC4 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e30)

**Result: score 0 in plain C.** No pin, no asm, no added volatile. Levers go from 2 to 0 (the two `$3` pins on `x` and `r`).
Signature unchanged. No copy of the class elsewhere in `src/` (grep of `- 0xD;` finds only this body).

## (a) The residual in one sentence
Same count (32/32). In each of the three blocks the target loads the byte into `v1`, subtracts into `v0`, and copies the
difference back into `v1` (`addiu v0,v1,-24; bgez v0; move v1,v0; move v1,zero; sb v1`). The free body has either no
copy at all (s32 spellings, score 35) or the load in `v0` (u8 spellings, score 9).

## (b) The passes and the decisions (read on the `.jump`/`.cse`/`.combine`/`.lreg` dumps, proven on bytes)
Two separate defects, and one width change removes both.
1. **cse deletes the copy.** With `x` merged into `r` at `s32`, the insn `x = t` is `(set (reg x) (reg t))`, right after
   `t = x - 24`. `x` lives past the cse block end on one of the two skip-block paths (`Processing block from 2 to 32`),
   so `make_regs_eqv` makes it canonical (`cse.c:846-862`), and the `(set REG0 REG1)` swap (`cse.c:7440-7474`) rewrites
   the producer to set `x` directly. `t` is gone, and so is the `move` (`scratch/c3/D_s32_1.c`: 35).
2. **combine moves the load into a new pseudo.** With `u8 x` the copy survives (it is a SUBREG copy, not a REG copy),
   but cse merges the two identical `(zero_extend:SI x)` of the test and of `x - 24` into one pseudo. combine then folds
   the load and the single extension into `(set tmp (zero_extend:SI (mem:QI)))`, and `x`'s first value is gone. `tmp`
   is global (blocks 0 and 1) and takes a non-copy preference for `v0` from `t = tmp - 24` (`set_preference`,
   `global.c:1535`, the `copy = 0` operand case), so the load lands in `v0` (`scratch/c3/D_u8_1.c`: 9,
   `tools/alloc_table.py`: `r79 … prefers v0`).
3. **`s16 t` fixes both.** `t = x - 0x18` with `t` a `short` is expanded as `(zero_extend:HI x)` → `(plus:SI (subreg …)
   -24)` → `(set t:HI (subreg:HI …))` (`.rtl` insns 19-23). The test still uses `(zero_extend:SI x)`. The two
   extensions have DIFFERENT modes, so cse cannot merge them. The load has two users, so combine cannot fold it into
   either one, and it turns each extension of the `lbu`-loaded reg into a paradoxical `(subreg:SI (reg:QI x))` instead.
   The load stays in `x` (`.combine` insn 12: `(set (reg/v:QI 73) (mem:QI …))`). The `(s16)` sign extension of the
   `t < 0` test is dropped by combine (the difference of a zero-extended byte and 24 has more than 16 sign-bit copies),
   so the branch tests the SI difference `r77` directly, as the target does. `x = t` becomes
   `(set x:QI (subreg:QI r77))`, which is not a REG-REG copy, so the cse swap does not fire. `x` (18 refs, one pseudo for
   load and result) is live while `r77` is, so it conflicts with `v0` (r77 is local, `v0`) and takes `v1`:
   `.greg` order `73 72`, r73 `conflicts v0`.

## (c) The move that closed it
Two moves, both needed at once:
- merge `r` into `x` (the two locals that the tree pinned to the SAME `$3` are one variable, METHOD S104 d12), and
- give the difference its real width: `s16 t` (with `x` as `u8`, `u16` or `s16`; all 12 combos with `t` `s16`/`short`
  and `x` merged score 0: `scratch/c5/scores.txt`).
```c
    u8 *pa;
    u8 x;
    s16 t;
    ...
    x = *pa;
    if (x != 0) {
        t = x - 0x18;
        x = t;
        if (t < 0) {
            x = 0;
        }
        *pa = x;
    }
```
Per-block splitting of `x`/`t` makes no difference (the `_1` variants also score 0).

## (d) Generator proposal
When a register residual shows a loaded value and a result sharing one register around a copy of a `t = x - K` difference,
and the tree pins two locals to that register: merge the two locals into one and try the difference temp at `s16`/`short`
(and `s8`). The narrower difference keeps the copy (no same-mode `(set REG REG)` for `cse.c:7454`), and the two
different-mode extensions keep the load in the merged variable (combine cannot fold a load with two users). Today R12
tries one width at a time and R34 merges without a width change; neither reaches the joint move.

## (e) What did NOT work (byte evidence, all in `scratch/`)
- `x`/`r` merged at `s32`, any if/else or ternary form (`c3/A,C,D_s32_*`): 35, the copy is swapped away by cse.
- Merged at `u8`/`u16`/`s16` with `s32 t` (`c1/m1_*`, `c2/*`, `c3/A,D_*`): 9, the load is in a combine temp in `v0`.
- `if (t >= 0) x = t; else x = 0;` and the ternary (`c3/B_*`, `C_*`): 12-21. jump1's store-flag turns the clamp
  into a `nor/sra/and` mask.
- Computing `t` before the `x != 0` test (`c4/*_before`): 21-38. `x` becomes canonical and the branch tests `x`.
- The sweep's best was 9 (R12 width `r` s32->u16).

## (f) Where the method fell short
- METHOD step 12 d12 (merge the same-register pair) was necessary but not sufficient on its own. The deciding step was
  reading `.combine` for WHERE the load went (a separate zero-extend pseudo), which is a count/placement question and
  not an allocation-order one. The allocation table showed the `prefers v0`, but it did not show why a temp existed.
- A 120-body width enumeration (5 x-widths × 4 t-widths × 3 r-shapes × split) found it in one batch. Cheap
  enumeration of widths on every local is worth doing before reading dumps on a small body.

## (g) Structs question
No. The lever came from register-level decisions (the cse copy swap, combine's load folding, global allocation). The
only memory is three byte globals accessed through `pa`, and no store has to stay ordered against a load. A struct
would not change this. Not tested: there was nothing to test.

Files: `body.c` (score 0), `scratch/c5/` (the width batch, `scores.txt`), `scratch/c1`-`c4/` (the failures above),
`scratch/d_win/` and `scratch/d_Du8/`, `scratch/d_Ds32/` (dumps).
