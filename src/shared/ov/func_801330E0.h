/* func_801330E0 — shared body (overlay slot 0x80128158, h_exact 3f5678dc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
void func_801330E0(param_1, param_2, param_3)
    void *param_1;
    s16 *param_2;
    s16 param_3;
{
    extern u8 D_800AF648;
    s32 *m;
    s32 sxyz[4];
    s32 pos[4];
    s32 flag;
    s32 z;
    m = (s32 *)&D_800AF648;
    gte_SetTransMatrix(m);
    gte_SetRotMatrix(m);
    gte_ldv0(param_1);
    gte_rtv0tr();
    gte_stlvnl(sxyz);
    gte_stflg(&flag);
    z = sxyz[2];
    pos[2] = z + param_3;
    if (z != 0) {
        pos[0] = sxyz[0] * pos[2] / z;
        pos[1] = sxyz[1] * pos[2] / z;
    } else {
        pos[1] = 0;
        pos[0] = 0;
    }
    pos[0] -= m[5];
    pos[1] -= m[6];
    pos[2] -= m[7];
    ApplyTransposeMatrixLV(m, pos, sxyz);
    param_2[0] = sxyz[0];
    param_2[1] = sxyz[1];
    param_2[2] = sxyz[2];
}
