void func_800384A8(s32 arg0) {
    u8 *entry;
    u8 *p;
    u8 *q;
    s32 j;
    u8 *b;
    s32 *m;
    s32 *mb;
    s32 i;
    s32 one;

    entry = &D_800B9CD8[arg0 * 0x1FC];
    p = entry + 0x1A;
    i = 0;
    one = 1;
    mb = (s32 *)D_80073140;
    D_800A4F1D = 1;
    entry[0x1FA] = 0;
    for (; i < 0x10; i++) {
        q = p + 9;
        j = 0;
        b = D_800C6E2D;
        m = mb;
        for (; j < 0x10; j++) {
            if (*q++ != 0) {
                b[1] = one;
                b[0] = 0;
                func_8003916C(j);
                func_8002EFF8(0, *m);
            }
            m++;
            b += 0x60;
        }
        p += 0x1A;
    }
    D_800A4F1D = 0;
    *(s32 *)entry = *(s32 *)(entry + 4);
}
