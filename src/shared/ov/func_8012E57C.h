/* func_8012E57C — shared body (overlay slot 0x80128158, h_exact f24a0b0c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
s32 func_8012E57C(s32 a0, s32 a1) {
    u8 *p = D_801202A0;
    u8 *end = D_801202A0 + 0x6480;
    if (p != end) {
        s32 key = (s16)a1;
        do {
            if (*(u16 *)(p + 0x0) == a0) {
                if (*(s16 *)(p + 0x70) == key) {
                    return (s32)p;
                }
            }
            p += 0x10C;
        } while (p != end);
    }
    return 0;
}
