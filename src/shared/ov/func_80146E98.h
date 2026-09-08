/* func_80146E98 — shared body (overlay slot 0x80128158, h_exact 1f7e636d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80146E98(s32 a0) {
    s32 v0;
    v0 = *(s32*)(a0 + 0x1C);
    if (v0 != 0) {
        v0 = v0 - 1;
        *(s32*)(a0 + 0x1C) = v0;
        return (u32)v0 < 1;
    }
    return 1;
}
