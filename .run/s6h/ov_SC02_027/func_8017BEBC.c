/* func_8017BEBC — ov_SC02_027_jr_8017AE2C (76 ins)
 * Decls copied VERBATIM from the TU:
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:168  ApplyMatrixSV
 *   src/ov_SC02_027/ov_SC02_027_jr_8017AE2C.c:1698 RotMatrixYXZ
 * D_801D9E90..D_801D9EB8 are NOT declared anywhere in the TU (grepped whole file).
 */
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);

extern s32 D_801D9E90;
extern s32 D_801D9E94;
extern s32 D_801D9E98;
extern s32 D_801D9EA0;
extern s32 D_801D9EA4;
extern s32 D_801D9EA8;
extern s32 D_801D9EB0;
extern s32 D_801D9EB4;
extern s32 D_801D9EB8;

void func_8017BEBC(s32 param_1, s32 param_2)
{
    /* 8-byte short-only vector (SVECTOR); 32-byte MATRIX_L48 (t[] at +0x14) */
    typedef struct { s16 a, b, c, d; } SV4_L;
    typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_L;

    SV4_L vec;                              /* sp+0x10 */
    MTX_L mtx;                              /* sp+0x18 */
    s32 obj = *(s32 *)(param_1 + 0xCC);
    s32 prim = *(s32 *)(param_1 + 0x20);
    s32 mode;
    s32 val;
    s32 hi;
    s32 code;
    s32 t;

    if ((s16)param_2 != 0) {
        mode = 0x40000000;
        val = 0x1000;
    } else {
        mode = 0x50000000;
        val = 0x1333;
    }
    code = *(s32 *)(prim + 4) & 0xCFFFFFFF;
    hi = 0x40000000;
    *(s32 *)(prim + 4) = code | (mode | hi);

    if (*(u16 *)(*(s32 *)(param_1 + 0xCC)) != 0) {
        *(s16 *)(obj + 0x1A) = val;
        *(s16 *)(obj + 0x18) = val;
    }

    t = *(u16 *)(param_1 + 0xFC) + 0x80;
    *(u16 *)(param_1 + 0xFC) = t;
    vec.a = t;
    t = *(u16 *)(param_1 + 0xFE) + 0x100;
    *(u16 *)(param_1 + 0xFE) = t;
    vec.b = t;
    vec.c = 0;
    RotMatrixYXZ(&vec, &mtx);

    vec.b = 0;
    vec.a = 0;
    vec.c = 0x100;
    ApplyMatrixSV(&mtx, &vec, &vec);

    D_801D9EB0 = vec.a;
    D_801D9EA0 = vec.a;
    D_801D9E90 = vec.a;
    D_801D9EB4 = vec.b;
    D_801D9EA4 = vec.b;
    D_801D9E94 = vec.b;
    D_801D9EB8 = vec.c;
    D_801D9EA8 = vec.c;
    D_801D9E98 = vec.c;
}
