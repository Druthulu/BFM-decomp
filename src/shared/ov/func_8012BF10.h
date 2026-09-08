/* func_8012BF10 — shared body (overlay slot 0x80128158, h_exact e6f14df1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012BF10(s32 a0, s32 a1) {
    s32 v0;
    v0 = *(s32*)(a0 + 0x1C);
    if (v0 == 0) {
        v0 = 1;
    } else {
        v0 -= 1;
        *(s32*)(a0 + 0x1C) = v0;
        v0 = (u32)v0 < 1;
    }
    if (v0 != 0) {
        *(s32*)(a0 + 0x1C) = a1;
        return 1;
    }
    return 0;
}
