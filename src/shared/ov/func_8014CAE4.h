/* func_8014CAE4 — shared body (overlay slot 0x80128158, h_exact 6e0975b0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
u16 func_8014CAE4(s32 *a0, s32 a1) {
    s32 base = a0[0x78 / 4];
    return *(u16 *)(base + a1 * 2 + 0x1C);
}
