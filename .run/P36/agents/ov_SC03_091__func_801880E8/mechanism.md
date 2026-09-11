# func_801880E8 (ov_SC03_091_jr_8018326C.c) — P36 S104 agent e36

**Result: score 0 in plain C, ZERO levers.** Levers 3 NEEDED (`$2/$3/$4` pins, a launder on `s`, a keepalive) → 0.
54/54 ins; the WHOLE object is identical to the baseline snapshot (`objdump -s -r` md5 `12d084b9…`, `scratch/p1.o`).
Closed on the FIRST `--try`: `PACK/body.c` (= `scratch/p1.c`).

## (a) The residual
COUNT +6 (60 vs 54) plus a shuffled prologue: the tree's hand-unrolled 8-word copy through three pinned temps came out as
eight `lui/lw` absolute pairs (the launder was meant to keep `&D_800AE620` in one register) and one `addiu a1,a1,4`
where the target has ONE `lui/addiu a1` and the canonical MIPS block move: `lw v0,v1,a0` ×3 / `sw` ×3, twice, then 2+2.

## (b) The pass and the decision
Not a pass decision at all — the target is `movstrsi_internal`, gcc's own block move for a 32-byte aggregate assignment:
`expand_block_move` (`config/mips/mips.c:2331`, the `bytes <= 2*MAX_MOVE_BYTES` branch at `:2361-2364`, `MAX_MOVE_REGS 4`
at `:2216`) → `output_block_move` (`:2444`) emits loads in groups of up to three temps then their stores — exactly the
`v0/v1/a0` triples with `sw` in between. The decompiler's element-wise copy can never reproduce it (each element is its
own SImode load from an absolute address; cse's `find_best_addr` keeps them absolute). Proven on bytes.

## (c) The move
The whole pinned block `{ Blk20 *s = &D_800AE620; register t0,t1,t2 …; m.w[i] = …; keepalive }` → `m = D_800AE620;`
(a struct assignment; `Blk20` is `struct { s32 w[8]; }`, `src/shared/engine_types.h:472`). Nothing else changed; the dead
`s32 hole[4]` stays — without it the frame is 80 not 96 (`scratch/p2.c`, the accepted dead-local idiom, cookbook idiom 6).

## (d) Generator proposal
When a body copies N consecutive words of one aggregate/global into a local through temps (a run of `m.w[k] = s->w[k]`,
`dst[k] = src[k]`, or three pinned temps ferrying triples) and the residual shows the target's `lw ×3 / sw ×3` groups
(or 2+2 / 4+4) from one base register, replace the run with a single struct assignment `m = SRC;` (declare a
`struct { s32 w[N]; }` type if none exists). Also: **grep the whole `src/` for the callee combination first** — this body's
lever-free twin was banked in two other overlays (`RotMatrixY(func_8012B6D4(` gives three sites).

## (e) What did not work
Nothing tried before the port. The sweep's best (29, R9+R18 reordering the temps) only reshuffled the element copies.

## (f) Where the method fell short
Nothing — step 12 (d2/d6, "a lever-free SAME-shape variant in another binary is the answer half the time"):
`func_801826C8` (`src/ov_SC03_098/ov_SC03_098_jr_8017D898.c:5211`) and `func_80181EC0`
(`src/ov_SC03_094/ov_SC03_094_jr_8017BEBC.c:5971`) are this exact body, lever-free, under a `mat = D_800AE620;` copy.
The pack builder's `related.txt` searches one overlay; a src-wide grep for `D_800AE620` finds 20 lever-free struct copies.

## (g) Structs
This close IS the struct answer: the lever existed only because the copy was spelled element-wise. The aggregate
assignment is the only C spelling that reaches `movstrsi`. `Blk20` is the 8-word (MATRIX-sized, 32-byte) rotation
matrix seed at `D_800AE620` (the identity matrix passed to `RotMatrixY`); `vec` is an s32[3] translation.

## Copies
None under this name; the two same-shape functions in other overlays are already banked lever-free (above).
