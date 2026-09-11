s32 func_800348A8(u32 arg0) {
    u16 *p;
    s32 i;

    p = D_800A46E8;
    for (i = 0; i < 8; i++, p += 0x2A) {
        if (p[0] == 5 && p[2] == (arg0 & 0xFFFF) && ((arg0 >> 16) == 0 || p[3] == (arg0 >> 16))) {
            return ++i;
        }
    }
    return 0;
}
