/* func_80145934 — shared body (overlay slot 0x80128158, h_exact 2d4ffe49). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80145934(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_801817B0;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_801817B0 load from being
         * tail-merged with the v>=0x384 D_801817B0 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80181720;
    } else if (v >= 0x578) {
        p = &D_801816FC;
    } else if (v >= 0x514) {
        p = &D_801816D8;
    } else if (v >= 0x384) {
        p = &D_801817B0;
    } else if (v >= 0x258) {
        p = &D_8018178C;
    } else if (v >= 0xC8) {
        p = &D_80181768;
    } else if (v >= 0xA) {
        p = &D_80181744;
    } else {
        p = &D_801816B4;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
