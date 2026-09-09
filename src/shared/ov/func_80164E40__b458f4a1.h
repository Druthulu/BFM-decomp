/* func_80164E40 — shared body (overlay slot 0x80128158, h_exact b458f4a1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80164E40(void) {
    u8 *p = &D_8018E920;
    if (*p != 0) {
        *p -= 0x10;
    }
    if (D_8018E921 != 0) {
        D_8018E921 -= 0x10;
    }
    if (D_8018E922 != 0) {
        D_8018E922 -= 0x10;
    }
    return *(s32 *)p == 0;
}
