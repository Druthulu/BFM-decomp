/* func_8016BBE0 — shared body (overlay slot 0x80128158, h_exact 5db18f2a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8016BBE0(s32 param_1) {
    extern void func_8016BF34(void *a0);
    extern void func_8016BF50(s32);
    extern void func_8001CF00(s32);
    extern M2C_UNK D_8018EDBC;
    extern u8 D_8018EDBD;
    extern u8 D_8018EDBE;
    extern M2C_UNK D_8018EDC0;
    extern u8 D_8018EDC1;
    extern u8 D_8018EDC2;

    int iVar1;
    int temp;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    *(int *)(((int)param_1) + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32))func_8016BF34)(((int)param_1));
        func_8016BF50(((int)param_1));
        func_8001CF00(iVar1);
        *(s16 *)(iVar1 + 0x10) = 0;
        temp = *(int *)(((int)param_1) + 0x2c);
        *(s16 *)(iVar1 + 0x14) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x12) = temp * 0x555;
        *(s16 *)(((int)param_1) + 0x10) = 0;
        *(s16 *)(((int)param_1) + 0x14) = 0;
        (*(u8 *)&D_8018EDBC) = 0x20;
        D_8018EDBD = 0x20;
        D_8018EDBE = 0;
        (*(u8 *)&D_8018EDC0) = 0xc0;
        D_8018EDC1 = 0xc0;
        D_8018EDC2 = 0;
        *(u16 *)(((int)param_1) + 2) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(((int)param_1));
    }
}
