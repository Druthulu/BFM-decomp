/* func_80145934 — shared body (overlay slot 0x80128158, h_exact 1b5f376e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80145934(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80180FFC;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80180FFC load from being
         * tail-merged with the v>=0x384 D_80180FFC load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers2)
    } else if (v >= 0x5DC) {
        p = &D_80180F6C;
    } else if (v >= 0x578) {
        p = &D_80180F48;
    } else if (v >= 0x514) {
        p = &D_80180F24;
    } else if (v >= 0x384) {
        p = &D_80180FFC;
    } else if (v >= 0x258) {
        p = &D_80180FD8;
    } else if (v >= 0xC8) {
        p = &D_80180FB4;
    } else if (v >= 0xA) {
        p = &D_80180F90;
    } else {
        p = &D_80180F00;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
