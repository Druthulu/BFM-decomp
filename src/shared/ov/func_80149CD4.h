/* func_80149CD4 — shared body (overlay slot 0x80128158, h_exact 2d82e9ac). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80149CD4(s32 a0) {
    s32 v0;
    if (*(s32*)(a0 + 0x44) & 0x404) {
        v0 = 0;
    } else if (*(s16*)(a0 + 0x1C8) != 0) {
        v0 = 0;
    } else {
        v0 = *(u16*)(a0 + 0xAA) & 8;
        v0 = v0 != 0;
    }
    return v0;
}
