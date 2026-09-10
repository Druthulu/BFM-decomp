void func_80145A2C(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_801929F4;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_801929F4 load from being
         * tail-merged with the v>=0x384 D_801929F4 load below (emits zero machine code). */
    } else if (v >= 0x5DC) {
        p = &D_801928D4;
    } else if (v >= 0x578) {
        p = &D_801928B0;
    } else if (v >= 0x514) {
        p = &D_8019288C;
    } else if (v >= 0x384) {
        p = &D_801929F4;
    } else if (v >= 0x258) {
        p = &D_801929D0;
    } else if (v >= 0xC8) {
        p = &D_801929AC;
    } else {
        p = &D_80192868;
        if (v >= 0xA) {
            p = &D_80192988;
        }
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
