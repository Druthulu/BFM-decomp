void func_8018270C(void) {
    extern s32 D_801B20E0;
    extern s32 D_8019FD8C;
    extern s32 D_80197B60;
    extern s32 D_801AEC08;
    extern s32 D_801AEBCC;
    extern s32 D_801AEC60;
    extern s16 D_801AEAFE;
    extern void func_8013373C(s16 a0);
    extern void func_8017EF68(s32 a0, s32 a1, s32 a2);

    s32 *p;
    __asm__("la %0, D_801AEBCC" : "=r"(p));  // !FAKE: instruction la — NEEDED DIFFERS (P36 rung B tus7)

    p[-7] = 0;
    p[0] = D_801AEAFE;
    func_8017EF68((s32)&D_801B20E0, (s32)&D_8019FD8C, (s32)(p - 7));
    func_8017EF68((s32)&D_801B20E0, (s32)&D_80197B60, (s32)&D_801AEC08);
    D_801AEC60 = 2;
    func_8013373C(0);
}
