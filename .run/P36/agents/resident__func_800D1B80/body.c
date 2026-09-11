s32 func_800D1B80(u8 *arg0) {
    extern s32 DsMix();
    s32 (*fp)(u8 *);

    fp = *(s32 (**)(u8 *)) (arg0 + 0xC);
    if (fp(arg0) != 0) {
        arg0[0x14]++;
        return DsMix(arg0);
    }
    return 0;
}
