# func_801651B8 (ov_MAIN_012, TU src/ov_MAIN_012/ov_MAIN_012_jr_8015A3C8.c) — agent c54, S103

**Status: score 0. Already banked in the tree.** Commit 321b540e7 (the re-propagation that ignores body-local
externs) replaced this TU's copy with the ov_SC04_011 spelling after this pack was built (pack files 17:15). The tree's
current text scores 0 under `--try`, and every `void func_801651B8(void * param_1)` definition in `src/` now has 0
`!FAKE` levers, so there is nothing left to bank for this class. The pack's `body_tree.c` is stale.

`PACK/body.c` = the tree's current text (the ov_SC04_011 port): `tbl = (Slot_80165140 *)&D_80184398;` then
`for (i = 0; i < 8; i++) { p = &tbl[i]; ... }`. Score 0.

## (a) Residual
Starting text (`body_free.c`): 38 ins vs 34. `--keep` objdump shows TWO walked pointers, `$s1 = puVar1` and
`$s0 = puVar1 + 12` (`addiu s0,s1,12` before the loop, `lw/sw 0(s0)`), each stepped by 16 every iteration, plus a
fourth callee-saved register `$s3` for the parameter. That is 4 extra instructions: the `$s3` save and restore, the
`addiu s0,s1,12` before the loop, and one extra step inside it. The register renames follow from that.

## (b) Pass and decision
loop.c strength reduction (`strength_reduce`, loop.c:3214). When the pointer is its own biv (`puVar1 += 4`), the
`puVar1[3]` memory address is a DEST_ADDR giv of that pointer biv, and it gets reduced into its own register. When
the pointer is recomputed from the counter (`p = &tbl[i]`), the counter is the only biv. Then the three addresses
`D+16i`, `D+16i+8` and `D+16i+12` are givs with the same mult, and `combine_givs_p` (loop.c:5458; its
`express_from` + `memory_address_p` arm) folds them into ONE reduced register. That gives the target's `lw 12(s0)`
and `addiu a2,s0,8`.
Proven on bytes: the move below closes the pack's own text 29 → 0. The claim about which giv arm fires comes from
reading the source; I did not dump `-dL` to confirm it.

## (c) The move
A single move on the pack's own `body_free.c` text closes it (score 0, `PACK/scratch/m1.c`). Delete `puVar1 = &D`
before the loop and `puVar1 = puVar1 + 4` inside it, and write `puVar1 = &(&D_80184398)[iVar2 * 4];` at the top of
the loop body. Everything else stays, including the do-while, the cast calls and `a0v`. The launder and the $16 pin
were both faking this one loop-shape difference.
Differences from the banked sibling (ov_SC04_011): the symbol (D_801EDCA8 → D_80184398) and nothing else. The
ov_MAIN_012 copy already carries the sibling's text.

## (d) Generator proposal
When a loop walks a pointer biv `p += K` and reads `p[j]` with j != 0, and the target shows ONE pointer register
(`lw 4j(sN)`) where yours shows two (`addiu sM,sN,4j` before the loop and two steps inside it), rewrite as
`p = &base[i*K]` recomputed at the top of the loop body from the loop counter, and delete the step. This is the same
class as S103 c2's `q = p + k`. Here the second pointer is not written in the source: loop.c creates it from the
`p[3]` field read.

## (e) Did not work
Not re-tried. history.txt shows the mechanical search stuck at 8 with R6/R7/R12/R4 moves. None of them removes the
pointer biv, which is the only thing that matters here.

## (f) Method
The pack was stale: the class had already been banked by propagation before the agent ran. A pack builder should
re-check the tree's current `!FAKE` count for the function (or re-score the tree text) before handing it out. The
first `--try` of the tree's own text shows this in 0.3 s.
