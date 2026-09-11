void func_80182464(s32 a0, s32 a1)
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8017EF68(s32 a0, s32 a1, s32 a2);
    extern s16 D_801AEBAA[];
    extern s32 D_801B20E0;
    extern s32 D_801A3A0C;
    extern s32 D_801AEB74;
    register s16 *q asm("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus7)

    q = D_801AEBAA;
    *q = a0;
    func_80049CAC((s32)q - 2, (s32)q - 78);
    __asm__("" : "=r"(q) : "0"(q));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus7)
    D_801AEB74 = (s16)a1;
    *(s32 *)((s32)q - 82) = 0;
    func_8017EF68((s32)&D_801B20E0, (s32)&D_801A3A0C, (s32)q - 82);
}
