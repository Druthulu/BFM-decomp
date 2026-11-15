/* func_80156B74 — shared body (overlay slot 0x80128158, h_exact 892f5585). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80156B74(s32 param_1, u32 param_2, u8 *param_3) {
    extern SVECTOR D_80126AF0[];
    extern SVECTOR D_801270A8;
    extern void guess_GetPlayerFramePointsA(s32 a0, s32 a1);
    extern void func_801484E8(s32 a0, s32 a1);
    extern void guess_GetPlayerFramePointsB(s32 a0, s32 a1);
    extern void func_8014856C(s32 a0, s32 a1);
    extern void func_800139C8(s32 a0, void *a1, void *a2);
    extern void func_80156ECC(s32 a0, void *a1, void *a2, void *a3, void *a4);
    u16 local_28[3];
    Unkstruct_8013B83C auStack_20;
    s32 v1 = *(s32 *)(param_1 + 0x20);
    D_801270A8.vx = 0;
    D_801270A8.vy = -0x1E;
    D_801270A8.vz = 0;
    if (param_2 == 0) {
        if (*(s32 *)(v1 + 0x20) != 0) {
            ((void (*)(void *, void *))guess_GetPlayerFramePointsA)(local_28, &auStack_20);
            D_80126AF0[0].vx = local_28[0];
            D_80126AF0[0].vy = local_28[1];
            D_80126AF0[0].vz = local_28[2];
            ((void (*)(void *, void *))func_801484E8)(local_28, &auStack_20);
            D_80126AF0[1].vx = local_28[0];
            D_80126AF0[1].vy = local_28[1];
            D_80126AF0[1].vz = local_28[2];
            goto L_call;
        }
        goto L_zero;
    }
    if (param_2 != 1) goto L_not1;
    if (*(s32 *)(v1 + 0x20) != 0) {
        ((void (*)(void *, void *))guess_GetPlayerFramePointsB)(local_28, &auStack_20);
        D_80126AF0[0].vx = local_28[0];
        D_80126AF0[0].vy = local_28[1];
        D_80126AF0[0].vz = local_28[2];
        ((void (*)(void *, void *))func_8014856C)(local_28, &auStack_20);
        D_80126AF0[1].vx = local_28[1];
        D_80126AF0[1].vy = local_28[1];
        D_80126AF0[1].vz = local_28[2];
        goto L_call;
    }
L_zero:
    D_80126AF0[0].vx = 0;
    D_80126AF0[0].vy = 0;
    D_80126AF0[0].vz = 0;
    D_80126AF0[1].vx = 0;
    D_80126AF0[1].vy = 0;
    D_80126AF0[1].vz = 0;
    goto L_call;
L_not1:
    if (param_2 == 2) {
        D_80126AF0[0].vx = 0;
        D_80126AF0[0].vy = -0x1E;
        D_80126AF0[0].vz = -0x52;
        func_800139C8((s32)(s16)(*(u16 *)(param_1 + 0x24A) - *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12)),
                      &D_80126AF0[0], &D_80126AF0[0]);
        D_80126AF0[1].vx = 0;
        D_80126AF0[1].vy = -0x1E;
        D_80126AF0[1].vz = -0x52;
        goto L_call;
    }
    {
        u32 uVar1 = param_2 & 0x80FFFFFF;
        D_80126AF0[0].vx = (s8)*(u8 *)(*param_3 * 3 + uVar1);
        D_80126AF0[0].vy = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 1);
        D_80126AF0[0].vz = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 2);
        D_80126AF0[1].vx = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 3);
        D_80126AF0[1].vy = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 4);
        D_80126AF0[1].vz = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 5);
    }
L_call:
    if ((param_2 & 0xF000000) == 0) {
        *param_3 = *param_3 + 1;
    }
    func_80156ECC(param_1, &D_801270A8, &D_80126AF0[0], &D_80126AF0[1], &D_80126AF0[2]);
}
