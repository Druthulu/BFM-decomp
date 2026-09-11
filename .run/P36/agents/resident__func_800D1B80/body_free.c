s32 func_800D1B80(u8 *arg0) {
    extern s32 DsMix();
    s32 (*fp)(void);
    u8 *p;

    fp = *(s32 (**)(void)) (arg0 + 0xC);
    if (fp() != 0) {
        p = arg0 + 0;
        p[0x14] = arg0[0x14] + 1;
        return DsMix(p);
    }
    return 0;
}
