void func_8013D8FC(void)
{

    extern s16 *D_801EDABC;
    s16 *psVar3;
    register s16 *psVar2 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 c9;
    s32 cff;
    u16 sVar1;
    s16 buf[4];

    psVar3 = D_801EDABC;
    if (psVar3 != (s16 *)0x0 && (sVar1 = (u16)*psVar3, sVar1 != 0xff)) {
        c9 = 9;
        cff = 0xff;
        psVar2 = psVar3 + 5;
        do {
            if (sVar1 == c9) {
                s32 arg2 = *(s32 *)(psVar2 + 1) + psVar2[-1] * 2;
                buf[0] = psVar2[-3];
                buf[1] = psVar2[-2];
                buf[2] = psVar2[-1];
                buf[3] = *psVar2;
                ((void (*)(s32, s32))func_800599B8)((s32)buf, arg2);
            }
            psVar3 = psVar3 + 8;
            sVar1 = (u16)*psVar3;
            psVar2 = psVar2 + 8;
        } while (sVar1 != cff);
    }
}
