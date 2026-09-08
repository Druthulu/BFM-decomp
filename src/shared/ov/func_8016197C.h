/* func_8016197C — shared body (overlay slot 0x80128158, h_exact 9c46b293). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8016197C(s32 a0, s32 a1) {
    s32 v0;
    if (a1 & 1) {
        v0 = 1;
    } else if (a1 & 0x4000) {
        v0 = 2;
    } else {
        v0 = ((u32)a1 >> 11) & 4;
    }
    return v0;
}
