/* func_80145A2C — shared body (overlay slot 0x80128158, h_exact 530ca2ff). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80145A2C(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_8018108C;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_8018108C load from being
         * tail-merged with the v>=0x384 D_8018108C load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80180F6C;
    } else if (v >= 0x578) {
        p = &D_80180F48;
    } else if (v >= 0x514) {
        p = &D_80180F24;
    } else if (v >= 0x384) {
        p = &D_8018108C;
    } else if (v >= 0x258) {
        p = &D_80181068;
    } else if (v >= 0xC8) {
        p = &D_80181044;
    } else {
        p = &D_80180F00;
        if (v >= 0xA) {
            p = &D_80181020;
        }
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
