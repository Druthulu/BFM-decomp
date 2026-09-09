/* func_801681FC — shared body (overlay slot 0x80128158, h_exact c1c085b2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801681FC(s32 param_1) {

    extern u8 D_80181A58[];
    extern u8 D_80181A28[];
    extern u8 D_80181A29[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_80181A58[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80181A28[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_80181A29[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    ((void (*)(s32, s32, s32, s32))func_80166F58)(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}
