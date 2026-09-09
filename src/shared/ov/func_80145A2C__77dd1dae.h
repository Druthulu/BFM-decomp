/* func_80145A2C — shared body (overlay slot 0x80128158, h_exact 77dd1dae). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80145A2C(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80181840;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80181840 load from being
         * tail-merged with the v>=0x384 D_80181840 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80181720;
    } else if (v >= 0x578) {
        p = &D_801816FC;
    } else if (v >= 0x514) {
        p = &D_801816D8;
    } else if (v >= 0x384) {
        p = &D_80181840;
    } else if (v >= 0x258) {
        p = &D_8018181C;
    } else if (v >= 0xC8) {
        p = &D_801817F8;
    } else {
        p = &D_801816B4;
        if (v >= 0xA) {
            p = &D_801817D4;
        }
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
