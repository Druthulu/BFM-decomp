# func_80185C04 — agent c53 (S103) — CLOSED, score 0, no lever

## (a) Residual
REG-caller 53 vs 53, score 27: same instructions, a rotation of `$v0/$v1/$a0` through the whole `then` arm (mine
`v1,a0,v0` where the target has `v0,v1,a0`). Nothing missing or extra.

## (b) Mechanism (pass + decision)
The free body is m2c register-literal text: two variables named `v0` and `v1` carry EVERY value in the arm (the angle,
the counter, the accumulator, the field read-modify-writes, both call results). One C variable = one pseudo, so the
`.lreg` dump of the free body shows `Register 74 (v0) ... dies in 6 places` and `Register 75 (v1) ... dies in 3 places`.
local-alloc only takes a pseudo that lives in one block and dies exactly once (`local-alloc.c:470-477`,
`reg_n_deaths[i] == 1`); both were refused and went to global.c, whose single allocno per variable (ordered by
`allocno_compare`, `global.c:604-610`) cannot reproduce the target's per-statement register choice — the tree faked it
with `$2`/`$3` pins. Written as ordinary C (one short-lived temp per expression, as the original surely was), each value
is its own local pseudo, local-alloc allocates them block by block in the order the target shows.
Proven: the `.lreg` death counts (dump of the free body), the close on bytes.

## (c) The move
Rewrite the arm as the matched sibling `func_80185ED4` (same TU, line 9854) spells its mirror image: `u16 cnt, acc`
for the counter pair, and every other field update as a single read-modify-write expression:
```c
*(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) + acc;
*(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 4;
*(s32 *)(a0 + 4) = *(s32 *)(a0 + 4) + func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x40;
*(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) - func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x40;
```
with a plain `if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) < 0x401) {...} else {...}` and the redundant `s32 s0 = a0;` copy dropped. Score 0 on the
first `--try`. Also 0: `s32` instead of `u16` for `cnt/acc`, and the sibling's goto layout — the width and the layout
are free here; the variable split is the whole close.

## (d) Generator proposal
When a lever-free body assigns one local (especially one named after a register) more than once with unrelated values
and the residual is a pure register rotation, inline each single-use value into its consumer and give each remaining
multi-use value its own local (R23's split, run to completion over every reassignment) — and first look for a matched
sibling with the same callees (`func_80185ED4` here) and copy its spelling.

## (e) What did not work
Not needed — first attempt closed. The mechanical search (history.txt) had reached 14 with R6 inline moves one at a
time; it never applied all of them together.

## (f) Method notes
`related.txt`'s first entry (`func_80185ED4`, three shared callees) was the answer. The residual text alone looked like
a register-order problem; the free body's variable names (`v0`, `v1`) were the tell.
