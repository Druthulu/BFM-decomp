s32 func_800331D4(s32 arg0) {
    u16 *p;
    s32 i;

    p = D_800A46E8;
    for (i = 0; i < 8; i++, p += 0x2A) {
        if ((*p & 0x3F) == 1 && p[2] == (arg0 & 0xFFFF) && (((u32)arg0 >> 16) == 0 || ((u32)arg0 >> 16) == p[3])) {
            return ++i;
        }
    }
    return 0;
}
