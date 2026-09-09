/* func_80165240 — shared body (overlay slot 0x80128158, h_exact 2568f863). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80165240(void *param_1, void *param_2, void *param_3)
{

    extern u8 D_80181EAC[];
    extern u32 D_80181ECC, D_80181ED0, D_80181ED4, D_80181ED8;
    extern u32 D_80181ECC, D_80181ED0, D_80181ED4, D_80181ED8;
    extern u32 D_80181ECC, D_80181ED0, D_80181ED4, D_80181ED8;
    extern u32 D_80181ECC, D_80181ED0, D_80181ED4, D_80181ED8;
    u8 prim[0x40];   /* $sp+0x10 .. 0x50 */
    u8 mat[0x20];    /* $sp+0x50 .. 0x70 */
    u8 *p = prim;

    func_80017DC4(param_2, mat);
    ApplyMatrixSV(mat, &D_80181EAC[0x00], p);
    ApplyMatrixSV(mat, &D_80181EAC[0x08], prim + 0x08);
    ApplyMatrixSV(mat, &D_80181EAC[0x10], prim + 0x10);
    ApplyMatrixSV(mat, &D_80181EAC[0x18], prim + 0x18);

    *(s16 *)(prim + 0x04) = 3;
    prim[0x38] = 0x2c;
    *(u32 *)(prim + 0x20) = D_80181ED4;
    *(u32 *)(prim + 0x24) = D_80181ECC;
    *(u32 *)(prim + 0x28) = D_80181ED8;
    *(u32 *)(prim + 0x2c) = D_80181ED0;
    *(struct W4 *)(prim + 0x30) = *(struct W4 *)param_3;
    *(u32 *)(prim + 0x34) = 0x50000000;

    func_80016ED4(p);
}
