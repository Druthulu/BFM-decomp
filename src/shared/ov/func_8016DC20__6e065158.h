/* func_8016DC20 — shared body (overlay slot 0x80128158, h_exact 6e065158). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016DC20(s16 *param_1) {

    extern s16 D_8018F4B8;
    extern s16 D_8018F4BC;
    extern u8 D_8018257C[];
    extern u8 D_80182588[];
    u16 *psVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    s16 i;
    s16 sp[6];

    i = 0;
    psVar1 = (u16 *)&D_8011D030;
    iVar4 = *(s32 *)((u8 *)param_1 + 0x34);
    do {
        if ((psVar1 != (u16 *)param_1) && (*psVar1 == 0x34)) goto end;
        i = i + 1;
        psVar1 = psVar1 + 0x2c;
    } while (i < 0x1e);
    func_80149374(iVar4, (s32)param_1 + 4);
    iVar2 = func_801619D0((void *)iVar4);
    i = 0;
    if (iVar2 == 0) goto ddb0;
    psVar1 = (u16 *)&D_8011D030;
    do {
        if (*psVar1 == 0x11) goto ddb0;
        i = i + 1;
        psVar1 = psVar1 + 0x2c;
    } while (i < 0x1e);
    func_80146A6C(0x11, param_1, *(s16 *)((u8 *)param_1 + 6),
                  (s16)(*(u16 *)((u8 *)param_1 + 0xa) - 8),
                  *(s16 *)((u8 *)param_1 + 0xe), 0, 0);
    sp[0] = *(u16 *)((u8 *)param_1 + 6);
    sp[1] = *(u16 *)((u8 *)param_1 + 0xa);
    sp[2] = *(u16 *)((u8 *)param_1 + 0xe);
    func_800D20C0(&sp[0], &sp[4], 0);
    sp[5] = 0;
    func_800D23D0(&sp[4]);
    i = 0;
    do {
        iVar3 = func_80146A6C(0x12, param_1, *(s16 *)(iVar4 + 6),
                              *(s16 *)(iVar4 + 0xa), *(s16 *)(iVar4 + 0xe),
                              i, 0);
        if (iVar3 != 0) {
            *(u16 *)(iVar3 + 0x12) = sp[4];
            *(u16 *)(iVar3 + 0x16) = sp[5];
            *(u16 *)(iVar3 + 0x1a) = 0;
        }
        i = i + 2;
    } while (i < 3);
    goto end;
ddb0:
    if (((D_8018F4B8 != *(s16 *)(iVar4 + 6)) || (D_8018F4BC != *(s16 *)(iVar4 + 0xe))) &&
        (iVar2 = func_800D21C4((s32)param_1, D_8018257C, 0x18), iVar2 != 0)) {
        D_8018F4B8 = *(u16 *)(iVar4 + 6);
        D_8018F4BC = *(u16 *)(iVar4 + 0xe);
        func_800D1FC8((s32)param_1, 7);
        *(s32 *)((u8 *)param_1 + 0x20) = iVar2;
        *(u16 *)(iVar2 + 0x1a) = 0x3000;
        *(u16 *)(iVar2 + 0x18) = 0x3000;
        *(u8 *)(iVar2 + 0x26) = 0xff;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x50000000;
        func_80128EA8(iVar2, (s32)param_1 + 0x24, (s32)D_80182588);
        func_80128ED8((void *)iVar2, (void *)((s32)param_1 + 0x24));
        *(u16 *)((u8 *)param_1 + 2) = *(u16 *)((u8 *)param_1 + 2) + 1;
        return;
    }
end:
    ((void (*)(s16 *))func_80146C3C)(param_1);
}
