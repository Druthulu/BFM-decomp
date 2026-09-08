/* func_8014C088 — shared body (overlay slot 0x80128158, h_exact 6b14b5f2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_8011F9D0;
s32 func_8014C088(s32 a0, s32 a1) {
    u8 *p;
    u8 *end;
    p = (u8 *)&D_8011F9D0;
    end = p + 0xC30;
    if (p >= end) {
        return 0;
    }
    do {
        if (*(u16 *)p == a1) {
            return (s32)p;
        }
        p += 0x68;
    } while (p < end);
    return 0;
}
