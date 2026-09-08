/* func_801633A8 — shared body (overlay slot 0x80128158, h_exact a4be12c0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80115100;
extern s32 D_80115200;
s32 func_801633A8(void) {
    s32 *p = &D_80115100;
    s32 *q = &D_80115200;
    s32 i;
    for (i = 0; i < 3; i++) {
        s32 v1 = q[i];
        if (v1 != 0) {
            if ((*(u16*)(p[i] + 0x5C) & 0x400) == 0) {
                return v1;
            }
        }
    }
    return 0;
}
