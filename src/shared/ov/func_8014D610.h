/* func_8014D610 — shared body (overlay slot 0x80128158, h_exact 9af217fd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_8014C918(s32 a0, s32 a1);
s32 func_8014D610(s32 param_1, s32 param_2, u16 *param_3) {
    extern u8 D_801202A0[];
    u16 *psVar4;
    u8 *puVar3;
    s32 iVar2;
    psVar4 = (u16 *)D_801202A0;
    while (psVar4 < (u16 *)(D_801202A0 + 0x6480)) {
        puVar3 = (u8 *)psVar4 + 0x75;
        if (*psVar4 != 0 && (*(u16 *)(puVar3 - 0x19) & 0x400) != 0 &&
            *(s32 *)(puVar3 - 0x1D) != 0 &&
            *(s16 *)(puVar3 - 0x6B) >= *(s16 *)(param_1 + 0xA)) {
            iVar2 = ((s32 (*)(s32, s32, s32, u16 *))func_80135A4C)(
                *(s32 *)(puVar3 - 0x55), *(s32 *)(puVar3 - 0x1D), param_2, param_3);
            if (iVar2 != 0) {
                *(s32 *)(param_1 + 0x174) = (s32)psVar4;
                puVar3[-1] = 1;
                *(u16 *)(param_1 + 6) = param_3[0];
                *(u16 *)(param_1 + 0xA) = param_3[1];
                *(u16 *)(param_1 + 0xE) = param_3[2];
                *(u16 *)(param_1 + 0x16E) = func_8014C918(param_1, *puVar3) & 0xff;
                return 1;
            }
        }
        psVar4 += 0x86;
    }
    return 0;
}
