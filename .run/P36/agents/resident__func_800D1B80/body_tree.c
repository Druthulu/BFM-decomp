s32 func_800D1B80(u8 *arg0) {
    extern s32 DsMix();
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus10)
    s32 (*fp)(void);
    u8 *p;

    fp = *(s32 (**)(void)) (arg0 + 0xC);
    if (fp() != 0) {
        p = arg0 + zr;
        p[0x14] = arg0[0x14] + 1;
        return DsMix(p);
    }
    return 0;
}
