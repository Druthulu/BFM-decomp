/* func_8014A6C4 — shared body (overlay slot 0x80128158, h_exact 22e1e42e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029178(s32 a0);
s32 func_8014A6C4(s32 a0) {
    s32 r;
    if ((func_80029178(0x1F) & 0xFF) == 0) {
        r = 0;
    } else if (*(s32 *)(a0 + 0x44) & 0x4) {
        r = 0;
    } else {
        r = *(u8 *)(a0 + 0x1BE) == 0;
    }
    return r;
}
