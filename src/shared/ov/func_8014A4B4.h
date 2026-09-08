/* func_8014A4B4 — shared body (overlay slot 0x80128158, h_exact 37fed24a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029178(s32 a0);
s32 func_8014A4B4(void *a0) {
    if ((func_80029178(0x1E) & 0xFF) != 0) {
        u32 v = *(u16 *)((s32)a0 + 0xAC) & 0x40;
        return v != 0;
    }
    return 0;
}
