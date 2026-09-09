/* func_801336E8 — shared body (overlay slot 0x80128158, h_exact d1d2a178). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801336E8(void *a0, int a1, int a2) {
    if (a0 != 0) {
        (*(void * *)&D_8018E6E8) = a0;
        ((void (*)(void))func_80136BC4)();
    }
    (*(int *)&D_8018E6EC) = a1;
    D_8018E6F0 = a2;
}
