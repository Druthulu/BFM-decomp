# func_8018632C (ov_SC03_091_jr_8018326C.c; C name `aF8018632C`) — P36 S104 agent e36

**Result: score 0 in plain C, zero levers** (2 NEEDED `launder`s → 0; the `$17` pin was already REMOVED). 54/54 ins, MATCH.
Closed on the FIRST `--try` with d39's port (`.run/P36/agents/ov_SC03_090__func_80185484/scratch/copy_func_8018632C.c`),
copied verbatim to `PACK/body.c` (= `scratch/c1.c`).

## (a) The residual
COUNT +2 (56 vs 54): both s16 field loads came out `lhu; sll 16; sra 16+N` where the target has `lh; sra N`
(`+0x18` → `>> 8`, `+0x1A` → `>> 6`). The two launders were exactly on the two shifted values.

## (b) The pass and the decision (d39's reading, `ov_SC03_090__func_80185484/mechanism.md` (b)/(c); not re-traced here)
cse1 `fold_rtx`'s associative-shift fold (`cse.c:5577-5667`) folds `h >> 8` into `(ashiftrt (ashift x 16) 24)` built on the
load's own extension temp, so combine never re-forms `lh`. `(s16)h >> N` makes `short_shift` (`c-typeck.c:2418-2450`) re-extend
on h's own pseudo; cse folds that pair instead, combine forms `lh` and `simplify_shift_const` (`combine.c:7930-7944`) collapses
the rest to `sra N`.

## (c) The moves
1. `s0 = h >> 8;` → `s0 = (s16)h >> 8;`
2. `r = h2 >> 6;` → `r = (s16)h2 >> 6;` (both needed — d39: 5 and 4 alone)
3. readability, each checked by d39 at 0: `ent = a0` copy and the `p` temp inlined, the dead `a0 = 1;` deleted.

## (d) Generator proposal
When the residual shows `lhu; sll 16; sra 16+N` against the target's `lh; sra N`, rewrite every constant right shift `v >> N`
of an s16-loaded `v` as `(s16)v >> N`, enumerating the subsets of the sites (d13 needed one, this class needs both).

## (e) What did not work
Nothing tried beyond the port; the port closed first time.

## (f) Where the method fell short
Nothing: step 13 (d13) + "copies close with the same text" (d39 already had this TU's copy ready).

## (g) Structs
Neutral (d39 did not need one; the channel here is cse's shift fold on a narrowing extension, not aggregate-vs-scalar MEM flags).
A struct for the sub-object at `+0x20` (s16 +0x18 radius, s16 +0x1A range) would read better but does not touch the fold.

## Copies (all closed by d39 at 0 with this same text)
func_80185484 (ov_SC03_090), func_801857A8 (ov_SC03_089), func_80183318 (ov_SC03_104), func_8018632C (this TU).
