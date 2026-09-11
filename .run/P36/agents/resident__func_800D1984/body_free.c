s32 aF800D1984(u8 *arg0) {
    extern s32 func_800D19DC();
    s32 (*fp)(void);
    u8 *p;

    fp = *(s32 (**)(void)) (arg0 + 0xC);
    if (fp() != 0) {
        p = arg0 + 0;
        p[0x14] = arg0[0x14] + 1;
        return func_800D19DC(p);
    }
    return 0;
}
