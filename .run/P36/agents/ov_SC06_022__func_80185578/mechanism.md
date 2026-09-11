# func_80185578 (ov_SC06_022, 6 copies): closed lever-free — it returns int, and `y` is an s16 (agent c43, S103)

**Result: score 0, and the whole object is byte-identical (`objdump -drz -s` diff empty), BUT THE CLOSE NEEDS A CHANGE
OUTSIDE THE BODY.** The function returns a value, so its three in-TU declarations have to say `s32` instead of
`void`:
- `src/ov_SC06_022/ov_SC06_022_jr_80184A28.c:2998` `extern void func_80185578(s32 a0, s32 a1);` → `extern s32 ...`
- `:3288` and `:3289` (the two "SIMULATION of real-TU context" rows right above the definition) → `extern s32 ...`

`PACK/body.c` is the definition (it gives `conflicting types` under `--body` while those rows still say void).
`PACK/body_tu.c` is the whole TU with the three rows retyped, and scores 0 via `--try` without `--body`. The other two
TUs that declare it (`ov_SC06_022_jr_80184304.c:2978`, `ov_SC06_022_jr_80182D08.c:3605`) are byte-identical either
way (whole-object diffs empty with the rows retyped: `scratch/decl_*.c`), so they can be retyped for consistency or
left alone. Their callers discard the result.

**Transfer: all 6 copies score 0, and each whole object is byte-identical**, with the same edit plus that TU's own
declarations retyped (`scratch/xfer.py`; 3-4 rows per TU). The copies are ov_SC06_018 func_801874E4, SC06_020
func_80181654, SC06_022 func_80185578, SC06_024 func_80187A50, SC06_032 func_80182288, SC06_033 func_80185F6C.

## (a) The residual (counted first: mine 90, target 94)
Two independent defects:
1. **A missing `move s3,s0`** (the `y = x` copy). The target keeps `x` in `$s0`, shared later with `res`, and `y` in
   `$s3`. Lever-free, `y` and `x` became ONE pseudo (`move s2,a1`), and every register downstream shifts. The tree's
   `addu y, x, $zero` asm faked that copy.
2. **Missing `$v0` writes**: `move v0,zero` on the `flags & 4` path and `li v0,1` on the other paths. The function
   RETURNS 0 ("already set up", bit 2 of +0xE0) or 1. The tree declared it `void` and faked the return value with a
   keepalive asm `"r"(rv)` after an `epi:` label.

## (b) The passes (proved on dumps: `scratch/dumps_r6/` vs `scratch/dumps_r6s/`)
1. The copy: with `s32 y`, `.rtl` insn 13 is `(set (reg:SI 74) (reg:SI 73))`, and cse1's `(set REG0 REG1)` case
   (cse.c:7440-7474, gate :7455 wants a REG source) retargets the previous insn: `.cse` insn 6 becomes
   `(set (reg 74) (reg:SI 5 a1))` and the copy disappears. With `s16 y`, the insn is
   `(set (reg:HI 74) (subreg:HI (reg:SI 73) 0))`. Its source is a SUBREG, not a REG, so the gate fails and the copy
   survives cse (`.cse` insn 13, `movhi_internal2`). It's a separate pseudo, so it gets `$s3` while `arg1` keeps
   `$s0` and dies into the case-0 call. This is METHOD c4's width mechanism exactly: there's no PROMOTE_MODE, so the
   s16 local is an HImode pseudo.
2. The return value: `return 0` / `return 1` on an `s32` function sets `$2` on every path, which a void function
   can't do. No pass is involved; the bytes just prove the function has a return value.

What's proved on bytes: `r1` (s32 return, s32 y) = 16 [COUNT, 93 vs 94], which is the copy alone.
`r2`/`r3`/`r5`/`r6` (s32 return plus u16/s16 y, in several spellings) = 0. `r6s` (r6 with `s32 y`) = 16.
`r7` (no `y`, `arg1` used directly) = 16. history.txt's `y s32->u16` alone = 11, which is the width without the
return value.

## (c) The moves (a JOINT close; neither alone reaches 0)
- `void` → `s32`, with `return 0;` / `return 1;` in place of `rv = …; goto epi;` (plus the declarations above).
- `s16 y = arg1;` replaces `s32 x = arg1; s32 y; y = x;`, and case 0 passes `(s16)arg1`. `x` goes away entirely:
  the parameter IS `x`.

## (d) GENERATOR PROPOSAL
Two rules. (1) **When a `void` function's tree body ends in a keepalive `__asm__ volatile("" : : "r"(v))` on a
0/1 (or constant) variable assigned before gotos to the end label, the function returns that value.** Retype the
definition and every in-TU `extern void` row to `s32`, turn `v = K; goto end;` into `return K;`, and score the
WHOLE TU (`--try` without `--body`). Callers that discard the result don't change bytes (checked in 2 TUs here).
Sizing grep: `grep -rn '__asm__ volatile("" : : "r"(rv))' src` = 6 (exactly this class). The wider
`grep -rn '__asm__ volatile("" : : "r"(' src | grep keepalive` = 19; not every one of those is a return value, so
check each target for `$v0` writes before the epilogue. (2) When a `y = x` copy of a parameter is
missing and `y` is only used under a `(s16)`/`(u16)` cast, declare `y` s16/u16 (R20) — AFTER rule 1, because a
missing return value adds COUNT noise that hides whether the width move worked (history's `y->u16` scored 11 and
the search stopped there).

## (e) Tried and did not work (bytes)
- Every body-only variant: the return value can't be produced in a void function without a lever. I didn't try a
  `volatile` or asm.
- `r1`: s32 return with `s32 y` = 16. `r7`: drop `y` = 16. Both lose the copy (the cse.c:7455 swap).

## (f) Where the method fell short
- Counting first found it straight away: 4 missing = 1 copy + 3 `$v0` writes. But the brief's goal ("no change
  outside the body") is unreachable for any function the decomp mis-declared as `void`, and the `--body` scorer
  can't express the fix at all: it compiles `conflicting types`. The mechanical search (history.txt) ran 1,127
  compiles on body-only moves that could never have reached 0.
- METHOD has no row for "keepalive asm = a missing return value". It should come FIRST in the COUNT branch: the
  `$v0` writes are the cheapest instructions to account for, and one look at the target (`move v0,zero` in a `j`
  delay slot, `li v0,1` before the epilogue) settles it.
- The tree's rows at `:3287-3289` ("SIMULATION of real-TU context") are two duplicate `extern void` declarations.
  They are the lines that have to change, and the sibling TUs carry 3-4 such rows each.
