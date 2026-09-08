/* func_8014C0C8 — shared body (overlay slot 0x80128158, h_exact cf112312). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
s32 func_8014C0C8(s32 a0_unused, s32 a1, s32 a2) {
    s32 i = 0;
    s32 key = (s16)a2;
    u8 *p = D_801202A0;
    do {
        if (*(u16 *)(p + 0x0) == a1) {
            if (*(s16 *)(p + 0xFC) == key) {
                return (s32)p;
            }
        }
        i += 1;
        p += 0x10C;
    } while ((u32)i < 0x60);
    return 0;
}
