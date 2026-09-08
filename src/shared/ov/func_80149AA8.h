/* func_80149AA8 — shared body (overlay slot 0x80128158, h_exact d0967f29). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80149AA8(s32 *a0) {
    s32 v0;
    if (a0[0x44 / 4] & 0x404) {
        v0 = 0;
    } else {
        v0 = *(u16 *)((s32)a0 + 0xAC) & 0x80;
        v0 = v0 != 0;
    }
    return v0;
}
