# func_80013694 (main, src/800.c) — T7 agent e15 (S104)

**Result: score 0, lever-free** (no pin, no asm except Sony's GTE macros from `include/gte_inline.h`, no volatile, no
do-while). Levers 2 -> 0 (the NEEDED `$2` pin on `v0p` and the NEEDED `__asm__ __volatile__("")` barrier; the fused
hand-written 57-line asm block is gone too). Signature unchanged. Whole-object check on the `--try --keep` object:
`.text` (101,572 bytes), `.data`, `.rodata` byte-equal to `.run/P36/delever/baseline/src/800.o`
(`scratch/cmpobj.sh`).

`body.c` (= `scratch/r1.c`):
```c
    v = 0x1000;
    rot[0] = v;
    v = -sin_val;
    rot[4] = cos_val;
    rot[8] = cos_val;
    rotp = rot;
    rot[7] = sin_val;
    matp = matrix;
    rot[1] = 0; rot[2] = 0; rot[3] = 0;
    rot[5] = v;
    rot[6] = 0;

    gte_SetRotMatrix(matp);
    gte_ldclmv(rotp);      gte_rtir(); gte_stclmv(matp);
    gte_ldclmv(rotp + 1);  gte_rtir(); gte_stclmv(matp + 1);
    gte_ldclmv(rotp + 2);  gte_rtir(); gte_stclmv(matp + 2);
```

## (a) Residual
Free body (one fused asm block, `v0p` unpinned): `v0p` took `$v1` and the `-sin` store moved; score 9 COUNT-class but
really 102 = 102 with a v1->v0 swap. The fused block was the decompiler's paste of eight GTE macros whose second and
third `ldclmv`/`stclmv` inputs (`rotp + 1`, `matp + 1`, ...) had been hard-coded as `addiu $2,$sp,50` etc. inside the
asm text — that clobbered `$2` and forced the pin on the first input.

## (b) Pass and decision (PROVEN on dumps `scratch/dumps_r0/`, `scratch/dumps_r1/` + bytes)
1. With the Sony macros the compiler computes `rotp + 1` etc. itself: every macro input is a short block-local
   pseudo, local-alloc gives each `$2` (`;; Register 79/85-88 in 2.` in `dumps_r1/r1.i.lreg`). This is the same-TU
   sibling func_80013CFC's (src/800.c:1329) text, which is lever-free and byte-matched: port it, swap in the X-axis
   rotation elements. Score 5 after the port (`scratch/r0.c`).
2. The remaining 5: the target builds `0x1000` in `$v1`, stores it, then `negu v1,s0` — ONE register for both values.
   In `r0.c` (`rot[0] = 0x1000;` plus a separate `v = -sin_val;`) the `-sin` pseudo is block-local and local-alloc
   gives it `$16`/`$a0` (`;; Register 85 in 3.` only for the constant). The tree's text reuses ONE variable:
   `v = 0x1000; rot[0] = v; v = -sin_val;` — `.lreg`: `Register 78 used 4 times across 11 insns in block 0; dies in 2
   places` — local-alloc refuses a pseudo that dies more than once (`local-alloc.c:472`, `reg_n_deaths[i] == 1`), so it
   goes to global.c, which gives it `$3` (no `;; Register 78 in` line in `.lreg`: not locally allocated). Bytes: 0.
   Widths s32/s16/u16/u32 for `v` all give 0 (`scratch/a.c`–`d.c`).

## (c) Moves
1. The fused asm block -> the Sony GTE macros (`gte_SetRotMatrix`, `gte_ldclmv`, `gte_rtir`, `gte_stclmv`) with
   `rotp + k` / `matp + k` inputs, as the sibling func_80013CFC; `vec0[9]` + `pad[4]` -> `s16 rot[16]`: 9 -> 5.
2. `v = 0x1000; rot[0] = v; v = -sin_val;` (one variable, two values — the tree's own `v1` reuse): 5 -> 0.

## (d) Generator proposal
When a body carries a hand-fused GTE asm block whose text contains `addiu $2,$sp,K` lines (an input address the
decompiler baked in), split it back into the `gte_inline.h` macros with `base + (K - base_off)/2` pointer inputs and
delete the `$2` pin and barrier; then, if a constant and a later value share one target register, keep them in ONE
variable (a two-death pseudo is refused by local-alloc, `local-alloc.c:472`, and global allocates it).

## (e) What did not work
`r0.c` (constant stored directly, `v` only for `-sin`) = 5: `negu a0,s0`, the constant in `$v1` — two separate
registers. The sweep's best (R7 do-while + R6 inline v1, best 4) worked on the fused asm block and could not move the
hard-coded `$2`.

## (f) Where the method fell short
Nothing new: step 12 (d2/d6) "grep for another definition" + neighbours.txt found it — func_80013CFC (Z-axis rotation,
`m[2][2] = 0x1000`) and func_800139C8 (Y-axis, `m[1][1] = 0x1000`) are the same function for the other two axes,
lever-free; this one is the X axis (`m[0][0] = 0x1000`). A generator that recognises the fused GTE
block and splits it into macros would have reached score 5 mechanically.

## (g) Structs
Tested on bytes: a body-local `struct { s16 m[3][3]; s16 pad; s32 t[3]; } ident, rotm;` (the `MTX_139C8` shape of
the sibling func_800139C8, `scratch/st.c`) with `rotm.m[r][c]` stores also scores 0. It does not change the deciding
pass decision (local-alloc's one-death rule on `v`); the struct is readability only. (MTX_139C8 is declared after
this function in the TU, so a file-scope use needs the typedef moved up — the struct phase's call.)
