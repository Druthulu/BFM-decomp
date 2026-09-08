/* func_801632F0 — shared body (overlay slot 0x80128158, h_exact 50f3905c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80115200;
s32 func_801632F0(void) {
    s32 i = 0;
    s32 *p = &D_80115200;
    s32 v0;
    do {
        v0 = p[0];
        if (v0 != 0) {
            return v0;
        }
        i++;
        p++;
    } while (i < 3);
    return 0;
}
