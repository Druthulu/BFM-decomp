s32 aF800D1984(u8 *arg0) {
    extern s32 func_800D19DC();
    s32 (*fp)(u8 *);

    fp = *(s32 (**)(u8 *)) (arg0 + 0xC);
    if (fp(arg0) != 0) {
        arg0[0x14]++;
        return func_800D19DC(arg0);
    }
    return 0;
}
