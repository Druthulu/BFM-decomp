/* func_80186424 — shared body (overlay slot 0x80128158, h_exact fac91b25). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 D_801E8270;
extern s32 D_801E8274;
extern s32 D_801E8278;
extern s32 D_801E8280;
extern s32 D_801E8284;
extern s32 D_801E8288;
extern s32 D_801E8290;
extern s32 D_801E8294;
extern s32 D_801E8298;
void func_80186424(s32 param_1)
{
    extern s32 rand(void);
    SV4_L_8017C294 vec;   /* sp+0x10 */
    MTX_L_8017C294 mtx;   /* sp+0x18 */
    s32 prim;
    s32 mode;
    s32 code;
    s32 hi;
    s32 val;
    if ((rand() & 0xF) != 0) {
        mode = 0x40000000;
    } else {
        mode = 0x50000000;
    }
    prim = *(s32 *)(param_1 + 0x20);
    code = *(s32 *)(prim + 4) & 0xCFFFFFFF;
    hi = 0x40000000;
    *(s32 *)(prim + 4) = code | (mode | hi);
    val = *(u16 *)(param_1 + 0x108) + 0x80;
    *(u16 *)(param_1 + 0x108) = val;
    vec.a = val;
    val = *(u16 *)(param_1 + 0x10A) + 0x100;
    *(u16 *)(param_1 + 0x10A) = val;
    vec.b = val;
    vec.c = 0;
    RotMatrixYXZ(&vec, &mtx);
    vec.b = 0;
    vec.a = 0;
    vec.c = 0x200;
    ApplyMatrixSV(&mtx, &vec, &vec);
    D_801E8290 = vec.a;
    D_801E8280 = vec.a;
    D_801E8270 = vec.a;
    D_801E8294 = vec.b;
    D_801E8284 = vec.b;
    D_801E8274 = vec.b;
    D_801E8298 = vec.c;
    D_801E8288 = vec.c;
    D_801E8278 = vec.c;
}
