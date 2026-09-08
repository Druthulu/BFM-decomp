/* func_8014C918 — shared body (overlay slot 0x80128158, h_exact 9b204ab4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801151F0[];
s32 func_8014C918(s32 a0, s32 a1) {
    s32 v1;
    s32 ret;
    if (a1 == 0x18) {
        return 0x8;
    }
    v1 = 0;
    goto search;
found:
    return ret;
search:
    do {
        ret = v1 & 0xFF;
        if (D_801151F0[ret] == a1) {
            goto found;
        }
        v1 += 1;
    } while ((u32)(v1 & 0xFF) < 0x8);
    return 0;
}
