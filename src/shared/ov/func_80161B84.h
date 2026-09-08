/* func_80161B84 — shared body (overlay slot 0x80128158, h_exact f35acb39). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80149884(void);
extern void func_801599A4(void *a0);
extern void func_801498C0(void);
s32 func_80161B84(void *a0) {
    if ((((s32 *)a0)[0x11] & 0x100) != 0) {
        if (func_80149884() != 0) {
            func_801599A4(a0);
            (*(void (*)(void *))func_801498C0)(a0);
            return 1;
        }
    }
    return 0;
}
