/* func_80168430 — shared body (overlay slot 0x80128158, h_exact 9905ba29). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80168430(s32 param_1) {

    extern u8 D_80181A64[];
    extern u8 D_80181A3C[];
    extern u8 D_80181A3D[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_80181A64[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80181A3C[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_80181A3D[iVar1];
    ((void (*)(s32, s32, s32, s32))func_80166F58)(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}
