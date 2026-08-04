// STEP 0 magic-literal grep: D_800A5E88 / func_8002850C / func_80028620 / func_8012AD44
// all found together in this same TU (ov_SC02_027_jr_8017D898.c). Siblings func_8018A758,
// func_8018A808, func_8018A8B8, func_8018A970 (all banked, same TU) establish the byte-proven
// idioms reused here: struct-assignment for 16-byte Blk16 records (`dst[0]=src[0];` etc.),
// and `extern void func_8012AD44(s32 *a0, s16 a1);` cast-at-call. func_8018A8B8/func_8018A970
// also already declare D_801D69B4 / D_801D69EC as a *singular* Blk16_8018A8B8 elsewhere in
// this TU, and D_800A5E88 likewise — since my splice point (replacing the func_8018A564
// INCLUDE_ASM stub) sits ABOVE those file-scope decls/typedef, I cannot reuse the
// Blk16_8018A8B8 name here (typedef not yet visible) without a forward-reference problem, and
// per §138 (reconcile direction) redeclaring those two symbols with an INCOMPATIBLE type at
// file scope risks a clash once banked. So every symbol here is declared block-scoped (function
// body) using a locally-named struct type — block-scope externs don't collide with another
// function's block-scope externs for the same symbol (§S38/D2).

typedef struct { s32 w[4]; } LBlk16; /* 16-byte record, block-scoped local name only */

void func_8018A564(void *a0)
{
    extern void func_8002850C(s32 a0, s32 a1, s32 a2);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern void func_80028620(s32 a0, void *a1);

    extern s16 D_801D693C, D_801D693E, D_801D6940;
    extern LBlk16 D_801D6944;

    extern s16 D_801D6974, D_801D6976, D_801D6978;
    extern LBlk16 D_801D697C;

    extern s16 D_801D69AC, D_801D69AE, D_801D69B0;
    extern LBlk16 D_801D69B4;

    extern s16 D_801D69E4, D_801D69E6, D_801D69E8;
    extern LBlk16 D_801D69EC;

    extern LBlk16 D_800A5E88;

    s32 v1 = *(s16 *)((s32)a0 + 0xFC);
    LBlk16 *s0;

    *(s16 *)((s32)a0 + 0xFE) = 0;

    switch (v1) {
    case 0:
        func_8002850C(D_801D693C, D_801D693E, D_801D6940);
        s0 = &D_801D6944;
        func_8012AD44((s32 *)a0, 1);
        break;
    case 1:
        func_8002850C(D_801D6974, D_801D6976, D_801D6978);
        s0 = &D_801D697C;
        func_8012AD44((s32 *)a0, 2);
        break;
    case 2:
        func_8002850C(D_801D69AC, D_801D69AE, D_801D69B0);
        s0 = &D_801D69B4;
        func_8012AD44((s32 *)a0, 3);
        break;
    case 3:
        func_8002850C(D_801D693C, D_801D693E, D_801D6940);
        s0 = &D_801D6944;
        func_8012AD44((s32 *)a0, 4);
        break;
    case 4:
        func_8002850C(D_801D69E4, D_801D69E6, D_801D69E8);
        s0 = &D_801D69EC;
        func_8012AD44((s32 *)a0, 5);
        break;
    }

    {
        LBlk16 *dst = &D_800A5E88;
        LBlk16 *src = s0;

        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];

        func_80028620(0, &dst[0]);
        func_80028620(1, &dst[1]);
        func_80028620(2, &dst[2]);
    }
}
