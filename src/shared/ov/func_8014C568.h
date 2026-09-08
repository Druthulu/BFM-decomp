/* func_8014C568 — shared body (overlay slot 0x80128158, h_exact 1fad7d90). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 x, s32 y);
s32 func_8014C568(s16 *a0, s16 *a1) {
    return ratan2(a0[3] - a1[0], a0[7] - a1[2]) & 0xFFF;
}
