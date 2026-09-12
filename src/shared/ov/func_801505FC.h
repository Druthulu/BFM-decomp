/* func_801505FC — shared body (overlay slot 0x80128158, h_exact 4370c660). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
s32 func_801505FC(s32 a0) {
    u8 *p = D_801202A0;
    if (p < D_801202A0 + 0x6480) {
        u8 *end = D_801202A0 + 0x6480;
        do {
            if (*(u16 *)(p + 0x0) != 0) {
                if (*(u16 *)(p + 0x5C) & 0x100) {
                    if (func_8014C278(a0, (s32)p, 0x30) != 0) {
                        func_801506A4(a0, (s32)p);
                        return 1;
                    }
                }
            }
            p += 0x10C;
        } while (p < end);
    }
    return 0;
}
