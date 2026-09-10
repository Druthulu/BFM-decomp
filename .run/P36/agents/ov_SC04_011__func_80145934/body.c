void func_80145934(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80192964;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80192964 load from being
         * tail-merged with the v>=0x384 D_80192964 load below (emits zero machine code). */
    } else if (v >= 0x5DC) {
        p = &D_801928D4;
    } else if (v >= 0x578) {
        p = &D_801928B0;
    } else if (v >= 0x514) {
        p = &D_8019288C;
    } else if (v >= 0x384) {
        p = &D_80192964;
    } else if (v >= 0x258) {
        p = &D_80192940;
    } else if (v >= 0xC8) {
        p = &D_8019291C;
    } else if (v >= 0xA) {
        p = &D_801928F8;
    } else {
        p = &D_80192868;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
