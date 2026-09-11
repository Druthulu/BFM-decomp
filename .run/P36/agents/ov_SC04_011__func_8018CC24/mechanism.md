# func_8018CC24 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e17)

**Result: score 0 in plain C, on the first `--try`.** No pin, no asm, no added volatile. Levers go from 1 to 0 (the `$2`
pin on `v0`). Signature unchanged. The same edit closes `func_8018CCB8` (the next function, same shape plus a `Blk8`
stack copy and a different callee); no copy of the class exists in another TU (grep of
`v1_sign = *(s16 *)(s0 + 0xA);` finds only these two).

## (a) The residual in one sentence
Same count (37/37). A pure v0/v1 permutation: the decompiler variable `v0` (the field sums and the `+0x1C` counter) is in
`v1` in mine and in `v0` in the target, and `v1`/`v1_sign` take the other register.

## (b) The pass and the decision (read on the `.lreg`/`.greg` dumps; proven on bytes)
- The free body REUSES `v0` for four values (two field sums, the `& 3` test's load, the counter) and `v1` for two. In the
  `.lreg` of `scratch/dumps_free/`, `r75` (`v0`) "dies in 4 places" and `r74`/`r76` die in 2. local-alloc refuses a
  pseudo that dies more than once (`local-alloc.c:472`), so all three become GLOBAL allocnos (`.greg` order `75 72 76 74`).
- global.c then takes them in priority order (`allocno_compare`, `global.c:594-610`). `r75` is first (35000) but it
  CONFLICTS with hard `v0`: the local compare temps (`r82`, `r85`, `r77`, allocated to `v0` by local-alloc before global
  runs) are live while `r75` is live, e.g. the `slti` of the final test is born before the counter's `sw`. `find_reg`
  (`global.c:945-990`) therefore skips `v0` and gives `r75` `v1`; the later allocnos take `v0`. The pin forced `r75` into
  `v0`. (`scratch/dumps_free/`, `tools/alloc_table.py free func_8018CC24 scratch`.)
- With one name per value every temp is born and dies in one block, local-alloc allocates it (`qty_compare`), and each
  sum lands in `v0` next to the `v1` addend, exactly as the target and the lever-free sibling `func_8018CA04` have it.

## (c) The move that closed it
One variable per value (S103 c1/c8, generator R23), applied to BOTH `v0` and `v1` at once. The delivered `body.c` is the
text of the lever-free same-TU sibling `func_8018CA04` (first entry of `related.txt`) with the `func_8012AD80` call moved
first (that is the only structural difference in the bytes): the sums written in place,
`*(u16 *)(a0 + 0x10) = *(u16 *)(a0 + 0x10) + *(u16 *)(arg0 + 0x106);`, the counter as
`*(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;`, the test on `*(s16 *)(arg0 + 0xA)` directly. Also proven:
- `scratch/vA_split.c` (the free body with `x1,y1,x2,y2,c1,c2` as separate names, `s0 = a0` kept): 0.
- `scratch/vE_sharedptr.c` (the same with ONE pointer local reused for both `+0x20` loads): 0 — the pointer's reuse is
  harmless, only the value temps matter.

## (d) Generator proposal
When a register residual is a pure pair permutation and the `.lreg` shows two or more named temps that "die in N>1
places", split EVERY such temp into one name per value in a single candidate (R23 splits one variable at a time and each
single split scores worse here: 10 and 19).

## (e) What did NOT work (byte evidence)
- Splitting only `v0` (`scratch/vC_splitv0only.c`): 10 (a `v1`/`a0` swap remains).
- Splitting only `v1` (`scratch/vD_splitv1only.c`): 19.
- The sweep (R12 widths, R6/R8/R9/R10/R18, R4, R7): best 2, all COUNT-class. No generator produces the joint split.

## (f) Where the method fell short
Nothing blocked. `related.txt`'s first entry (`func_8018CA04`, 3 shared callees) is the same function with the call in a
different place; reading it and matching the call position closed it on the first `--try`. The sweep should try
"port the top related.txt body" before any generator.

## (g) Structs question
No. The lever was a local-alloc/global-alloc decision about register temps reused across statement groups; no memory
access order is involved. `arg0` is clearly an actor struct (`+0x0A` s16 y?, `+0x1C` frame counter, `+0x20` child
pointer with u16 fields at `+0x10`/`+0x14`, `+0x106`/`+0x108` u16 deltas), and a struct would make the text readable,
but it would not change this allocation.

Files: `body.c` (score 0), `scratch/vA_split.c`, `scratch/vE_sharedptr.c` (0), `scratch/vC_splitv0only.c` (10),
`scratch/vD_splitv1only.c` (19), `scratch/dumps_free/`.
