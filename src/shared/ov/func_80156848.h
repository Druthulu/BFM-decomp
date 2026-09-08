/* func_80156848 — shared body (overlay slot 0x80128158, h_exact 6818a35c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801151E0[];
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];
void func_80156848(s32 param_1, s32 param_2) {
    extern s32 D_801151E0[];
    extern u8 D_80126730[];
    extern S8 D_80126AF0[];
    extern B8 D_80128120[];
    extern B8 D_80128138[];
    extern void func_80013E94(void *a0, void *a1);
    extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80156A1C(s32 a0, s32 a1);
    u32 uVar1;
    s32 i;
    u32 uVar3;
    u32 local_20[2];
    uVar3 = 0;
    i = 0;
    do {
        uVar1 = D_801151E0[uVar3];
        if (uVar1 & 1) {
            func_80013E94(&D_80128120[i], local_20);
            ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(*(u8 *)(param_2 + 8), param_1, (s32)D_80126AF0[i].a,
                          (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0],
                          *(u8 *)(param_2 + 9));
        } else if (uVar1 & 6) {
            func_80156A1C(param_1, uVar3);
            func_80013E94(&D_80128138[i], local_20);
            if ((D_801151E0[uVar3] & 6) == 4) {
                local_20[0] = local_20[0] | 0x80000000;
            }
            ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(6, param_1, (s32)D_80126AF0[i].a,
                          (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0], 0);
            if (D_80126730[uVar3] == 0x24) {
                ((void (*)(s32, s32, s32, s32, s32, s32, s32, s32))func_801469C8)(0x53, param_1, (s32)D_80126AF0[i].a,
                              (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0], 0, 0x14);
            }
        }
        uVar3 = uVar3 + 1;
        i = i + 1;
    } while (uVar3 < 3);
}
