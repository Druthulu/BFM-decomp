# func_80013B64 (main, src/800.c) — T7 agent e25 (S104)

**Result: score 0, lever-free** — no pin, no barrier; the only asm is Sony's GTE macros (`gte_SetRotMatrix`,
`gte_ldclmv`, `gte_rtir`, `gte_stclmv` from `include/gte_inline.h`, which src/800.c already includes and which its
siblings func_80013694/func_800139C8/func_80013CFC use). Levers 3 -> 0 (the NEEDED `$2` pin on `v0p`, the two NEEDED
`""` barriers), and the hand-written 60-line monolithic GTE asm block is gone. Signature unchanged.

```c
void func_80013B64(s32 param_1, s32 param_2, s32 param_3)
{
    s16 matrix[16];
    s16 rot[16];
    s32 sin_val;
    s32 cos_val;
    u16 v1;
    s16 *rotp;
    s16 *matp;

    func_80013F3C(matrix);
    sin_val = func_8004787C((s16)param_1);
    cos_val = func_80047948((s16)param_1);

    v1 = -sin_val;
    rot[0] = cos_val;
    rot[4] = cos_val;
    rot[8] = 0x1000;
    rotp = rot;
    rot[3] = sin_val;
    matp = matrix;
    rot[1] = v1;
    rot[2] = 0;
    rot[5] = 0;
    rot[6] = 0;
    rot[7] = 0;

    gte_SetRotMatrix(matp);
    gte_ldclmv(rotp);
    gte_rtir();
    gte_stclmv(matp);
    gte_ldclmv(rotp + 1);
    gte_rtir();
    gte_stclmv(matp + 1);
    gte_ldclmv(rotp + 2);
    gte_rtir();
    gte_stclmv(matp + 2);

    func_8001282C(matp);
    func_800484EC(matp, param_2, param_3);
}
```

## (a) Residual
Free body: 10 — the first `gte_ldclmv` reads `rot` through `v1` instead of `v0` (`lhu t4,0(v1)` vs `0(v0)`), and the
`-sin` is computed in place in `s0` after the `rot[3]` store (`negu s0,s0; sh s0,50`) instead of into `v1` before the
stores (`negu v1,s0` first, `sh v1,50` later).

## (b) Passes and decisions
1. **Not a compiler decision — the asm template.** The tree's single asm block is `gte_MulMatrix0(matrix, rot, matrix)`
   hand-flattened: it hard-codes `addiu $2,$sp,50` / `$sp,18` / `$sp,52` / `$sp,20` for `rot+1`, `matrix+1`, … and so
   CLOBBERS `$2`; an input operand can never be allocated to a clobbered register, so `%0` (`rot`) took `v1` and the
   tree needed the `$2` pin. Written as Sony's per-step macros, gcc computes `rotp + 1` etc. itself (the `addiu v0,sp,50`
   the template copied) and `rotp` is in `v0` with no pin. This is exactly the sibling func_80013CFC's text (same
   layout: Z-rotation, `rot[0]=rot[4]=cos`, `rot[8]=0x1000`, `rot[3]=sin`, `rot[1]=-sin`; only the last callee
   differs, `ApplyMatrixSV` vs `func_800484EC`). PROVEN on bytes (`scratch/a1.c`, the sibling's text renamed, = 0 on the
   first `--try`).
2. **sched1 birthing priority on the negation** (S104 d8's rule, `birthing_insn_p` `sched.c:2477-2490`): with `s32 v1`
   the `neg` sets a whole REG once -> birthing -> `max_priority` (`adjust_priority` `sched.c:2530-2537`) -> scheduled
   last among the stores, after `rot[3] = sin_val`, so `sin_val` dies AT the neg (`dumps_a3/a3.i.lreg` insn 37,
   `REG_DEAD 75`) and local-alloc ties `v1` into `sin_val`'s `s0` (`combine_regs`, `local-alloc.c:1722`): `negu s0,s0`
   after `sh s0,54` = 5 (`scratch/a3.c`). With `u16 v1` the neg's destination is `(subreg:SI (reg:HI 77))`
   (`dumps_a2/a2.i.lreg` insn 41) — not birthing, it keeps source order (first), `sin_val` stays live to its store, no
   tie, the neg gets `v1`. PROVEN (dumps + bytes: `u16`/`s16` 0, `s32` 5). This is the move the sweep found alone (6).

## (c) Moves (joint)
1. the monolithic asm block + `$2` pin + both barriers -> Sony's `gte_SetRotMatrix / gte_ldclmv / gte_rtir / gte_stclmv`
   per step (the sibling func_80013CFC's text).
2. `s32 v1` -> `u16 v1` (as func_80013CFC declares it).
   The array spelling (`rot[i]`) and the cast spelling (`*(s16 *)((s32)rot + 2*i)`, func_80013CFC's) give the same
   bytes (`a1.c` and `a2.c` both 0); `body.c` carries the indexed one.

## (d) Generator proposal
When a body carries an asm block whose text is the concatenation of Sony GTE macro templates with hard-coded `$2`
address arithmetic (`addiu $2,$sp,K` between template copies) and a `$2` input pin, replace it by the macro sequence
(`gte_MulMatrix0` = SetRotMatrix + 3×(ldclmv/rtir/stclmv) on `p`, `p+1`, `p+2`) — and before anything, grep the TU for
a sibling that differs only by a callee name (func_80013CFC here) and port it.

## (e) What did not work
`scratch/a3.c` (the macros with `s32 v1`) = 5 — move 1 alone does not close. The sweep's `u16 v1` alone = 6 (move 2
alone does not close either; the asm template still forces `v1`).

## (f) Where the method fell short
Step 0 says "read neighbours.txt"; the header-less sibling func_80013CFC (src/800.c:1273, 60 lines below) carried the
answer in its BODY, not in a note — step 3's "DIFF the target against every same-TU function" (the coordinator's brief)
is what found it. A cheap tool check would have too: the target's bytes vs func_80013CFC's differ only in one `jal`
relocation. Note for the coordinator: func_800134FC (src/800.c:886) carries the SAME monolithic hand-flattened GTE asm
(not a Sony macro) — if the phase counts that as a lever, the per-step macro rewrite is its likely lever-free spelling
(not tried; not my function).

## (g) Structs
No. Neither decision involves an aggregate-vs-scalar alias: (1) is an asm operand constraint, (2) is sched1's birthing
test on a SUBREG destination. The local `rot`/`matrix` arrays are really `MATRIX` (`s16 m[3][3]; s16 pad; s32 t[3]`,
func_800139C8 already declares it as `MTX_139C8`): giving them that struct type is a readability move for the struct
phase and is byte-neutral here: PROVEN, `scratch/s1.c` (a body-local `struct { s16 m[3][3]; s16 pad; s32 t[3]; }
matrix, rot;` with `rot.m[i][j]` field stores) = 0. `body.c` keeps the arrays to match the three siblings' spelling.
