void func_80145934(void) {

    extern u8 D_8018C944;
    extern u8 D_8018C8B4;
    extern u8 D_8018C890;
    extern u8 D_8018C86C;
    extern u8 D_8018C920;
    extern u8 D_8018C8FC;
    extern u8 D_8018C8D8;
    extern u8 D_8018C848;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_8018C944;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_8018C944 load from being
         * tail-merged with the v>=0x384 D_8018C944 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus2)
    } else if (v >= 0x5DC) {
        p = &D_8018C8B4;
    } else if (v >= 0x578) {
        p = &D_8018C890;
    } else if (v >= 0x514) {
        p = &D_8018C86C;
    } else if (v >= 0x384) {
        p = &D_8018C944;
    } else if (v >= 0x258) {
        p = &D_8018C920;
    } else if (v >= 0xC8) {
        p = &D_8018C8FC;
    } else if (v >= 0xA) {
        p = &D_8018C8D8;
    } else {
        p = &D_8018C848;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
