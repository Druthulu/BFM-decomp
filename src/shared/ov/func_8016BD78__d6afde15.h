/* func_8016BD78 — shared body (overlay slot 0x80128158, h_exact d6afde15). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8016BD78(s32 param_1)
{
    extern void func_8016BF50(void);
    extern u8 D_8018EDBD;
    extern u8 D_8018EDBE;
    extern u8 D_8018EDC1;
    extern u8 D_8018EDC2;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    func_8016BF50();

    p1 = &(*(u8 *)&D_8018EDBC);
    if (*p1 != 0) *p1 -= 4;
    if (D_8018EDBD != 0) D_8018EDBD -= 4;
    if (D_8018EDBE != 0) D_8018EDBE -= 4;
    p2 = &(*(u8 *)&D_8018EDC0);
    if (*p2 != 0) *p2 -= 4;
    if (D_8018EDC1 != 0) D_8018EDC1 -= 4;
    if (D_8018EDC2 != 0) D_8018EDC2 -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}
