# func_8018CCB8 (ov_SC04_011_jr_8017D494.c): mechanism (P36 T7 S104, agent e17)

**Result: score 0 in plain C, on the first `--try`.** No pin, no asm, no added volatile. Levers go from 1 to 0 (the `$2`
pin on `v0`). Signature unchanged.

This is the same class as `func_8018CC24` (the function just before it): identical body plus a `Blk8 sp10 = D_801ED9AC[0];`
stack copy, `func_8018B0B0(arg0, &sp10, 0, 8)` in place of `func_8018A7E8`, and `-0x77F` in the last test. The full reading
is in `../ov_SC04_011__func_8018CC24/mechanism.md`; in short:

## (a) The residual
Same count (53/53), a pure v0/v1 permutation (`v1->v0 x14, v0->v1 x8`).

## (b) The pass
The free body reuses `v0` for four values and `v1` for two; each dies in several places, so local-alloc refuses them
(`local-alloc.c:472`) and they go global. The counter/sum pseudo conflicts with hard `v0` (the local compare temps sit in
`v0` while it is live), so `find_reg` (`global.c:945-990`) gives it `v1`.

## (c) The move
One name per value, both variables at once. Delivered as the lever-free sibling text (`func_8018CA04`'s spelling, the call
first, the sums and the counter written in place). `scratch/vA_split.c` (free body, `x1,y1,x2,y2,c1,c2` split, `s0`/`ptr`
kept): 0 too.

## (d) Generator proposal
Split every multi-death temp named in `.lreg` in ONE candidate (R23 splits one at a time).

## (e) What did not work
The sweep: best 2 (R12 width `v0` s32->s16). Single splits were measured on the twin (10 and 19).

## (f) Method
`related.txt`'s top entry gave the text.

## (g) Structs question
No; a register-allocation decision about reused temps. `sp10` is an 8-byte struct copy (`Blk8`), already typed.

Files: `body.c` (score 0), `scratch/vA_split.c` (0).
