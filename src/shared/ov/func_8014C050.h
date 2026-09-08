/* func_8014C050 — shared body (overlay slot 0x80128158, h_exact d9a7e628). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_8011D030;
s32 func_8014C050(s32 a0, s32 a1) {
    u32 i = 0;
    s32 p = (s32)&D_8011D030;
    for (; i < 0x1E; i++) {
        if (*(u16 *)p == a1) {
            return p;
        }
        p += 0x58;
    }
    return 0;
}
