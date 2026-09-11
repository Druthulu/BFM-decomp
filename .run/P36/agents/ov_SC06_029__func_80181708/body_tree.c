void func_80181708(int param_1) {
    s16 *psVar1;
    register s16 *psVar2 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)
    s16 *psVar5;
    s16 sVar4;
    s32 t;
    s32 acc;

    psVar1 = (s16 *)D_801DFD8C;
    psVar2 = (s16 *)D_801DFD90;
    *(s32 *)(param_1 + 0x48) = psVar1[0];
    *(s32 *)(param_1 + 0x50) = psVar1[2];
    *(s32 *)(param_1 + 0x3C) = psVar2[0];
    *(s32 *)(param_1 + 0x44) = psVar2[2];
    sVar4 = func_80012CB8(D_801904C6, psVar1[1], 0xC0);
    acc = *(s32 *)(param_1 + 0x4C) + sVar4;
    __asm__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
    t = D_801DFD90;
    *(s32 *)(param_1 + 0x4C) = acc;
    sVar4 = func_80012CB8(D_801904CE, *(s16 *)(t + 2), 0xC0);
    psVar5 = (s16 *)D_801DFD8C;
    *(s32 *)(param_1 + 0x40) += sVar4;
    if (*(s32 *)(param_1 + 0x4C) < psVar5[1])
        *(s32 *)(param_1 + 0x4C) = psVar5[1];
    if (*(s32 *)(param_1 + 0x40) < *(s16 *)(D_801DFD90 + 2))
        *(s32 *)(param_1 + 0x40) = *(s16 *)(D_801DFD90 + 2);
}
