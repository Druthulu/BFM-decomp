/* func_80149DD8 — shared body (overlay slot 0x80128158, h_exact 2a6a0a35). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
extern s32 func_80149F2C(s32 a0, s32 a1);
s32 func_80149DD8(s32 a0) {
    u8 *p;
    if (*(s32 *)(a0 + 0x178) != 0) {
        return 0;
    }
    if (*(s32 *)(a0 + 0x44) & 0x404) {
        return 0;
    }
    if ((*(u16 *)(a0 + 0xAC) & 0x80) == 0) {
        return 0;
    }
    *(s32 *)(a0 + 0x190) = 0;
    for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) {
        if (func_80149F2C(a0, (s32)p) != 0) {
            return 1;
        }
    }
    return 0;
}
