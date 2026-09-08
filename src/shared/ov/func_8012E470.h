/* func_8012E470 — shared body (overlay slot 0x80128158, h_exact 7d21c7fa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012E470(s32 a0) {
    s32 a1 = *(s32*)(a0 + 0x20);
    s32 v1 = *(s16*)(a1 + 0x18);
    s32 v0 = v1 + (0x1000 - v1) / 4;
    *(s16*)(a1 + 0x18) = (*(s16*)(a1 + 0x1C) = v0);
    v0 = *(s32*)(a0 + 0x1C);
    if (v0 != 0) {
        v0 -= 1;
        *(s32*)(a0 + 0x1C) = v0;
        v1 = v0;
        return (u32)v1 < 1;
    }
    return 1;
}
