/* func_8017CFE0 -- ov_SC03_002 / ov_SC03_002_jr_8017AE2C */

/* --- copied VERBATIM from the TU (src/ov_SC03_002/ov_SC03_002_jr_8017AE2C.c) --- */
extern u8 D_80126B5C;   /* TU line 361 */
extern s32 rand(void);  /* TU line 957 (line 1092 has the compatible `extern int rand(void);`) */

/* --- project-standard engine-core prototype (src/shared/engine_core.h DEFINE_func_8012B6D4);
       NOT declared in this TU, so no conflict. --- */
extern s32 func_8012B6D4(s16 *a0, s16 *a1);

/* --- overlay-local data; none of these are declared anywhere in the TU or in
       include/ or src/shared/ (audited). --- */
extern s16 D_801CB908;
extern s32 D_801CB914;
extern s32 D_801CB91C;
extern u8 D_801891A8[];
extern s16 D_801891C8[];
extern s16 D_801891CA[];

void func_8017CFE0(s16 *a0) {
    /* The target frame is 0x28 with only $s0/$s1/$ra saved at 0x18/0x1C/0x20, i.e. 8 bytes
       of locals sit below the register save area and are never touched. The original source
       declared a local it no longer uses; the same fossil is visible in the neighbours
       (func_8017C594 carries 16 such bytes). gcc-2.7.2 still reserves the slot. */
    s32 sp10[2];
    s32 a, b, t, r, off, x, y;

    a = (func_8012B6D4((s16 *)&D_80126B5C, &D_801CB908) >> 7) & 0x18;
    b = func_8012B6D4(a0 + 2, &D_801CB908);
    t = a | ((b >> 9) & 7);
    off = D_801891A8[t] << 2;
    r = rand();

    /* The struct reads are plain INDIRECT_REFs, not ARRAY_REFs: an `a0[0x46]` here sets
       MEM_IN_STRUCT_P, which lets gcc-2.7.2's true_dependence() drop the dependence against
       the constant-address store and hoist the second `lh` above `sw D_801CB914`. */
    x = *(s16 *)((s32)a0 + 0x88) + *(s16 *)((u8 *)D_801891C8 + off) - 0x100;
    x += (r & 0x7F) << 2;
    D_801CB914 = x << 16;

    y = *(s16 *)((s32)a0 + 0x8C) + *(s16 *)((u8 *)D_801891CA + off) - 0x100;
    y += (unsigned)(r & 0x7F00) >> 6;
    D_801CB91C = y << 16;
}
