/* func_80174808 — shared body (overlay slot 0x80128158, h_exact 0e3d12a0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80174808(u8 *a0) {
    s32 v = (s32)a0[0x214] + 1;
    a0[0x214] = (u8)v;
    return v;
}
