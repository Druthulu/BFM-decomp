/* func_80149E94 — shared body (overlay slot 0x80128158, h_exact 4e8df088). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
extern s32 func_8016F1AC(void);
extern s32 func_80149F2C(s32 a0, s32 a1);
s32 func_80149E94(s32 arg0) {
    u8 *p;
    if ((func_8016F1AC() == 0) && (*(u8 *)(arg0 + 0x1C5) != 0)) {
        *(u8 *)(arg0 + 0x1C5) = 0;
        for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) {
            if (func_80149F2C(arg0, (s32)p) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
