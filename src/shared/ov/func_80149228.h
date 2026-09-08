/* func_80149228 — shared body (overlay slot 0x80128158, h_exact 7a1c7e78). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80149228(s32 a0) {
    u32 a1;
    s32 v0;
    if (*(s16*)(a0 + 0x1E4) == 0) {
        *(s32*)(a0 + 0x1DC) = 0;
        *(s32*)(a0 + 0x1E0) = 0;
        *(s16*)(a0 + 0x1E4) = *(u16*)(a0 + 0x1E6);
    }
    a1 = *(u16*)(a0 + 0xAC);
    if (a1 != 0) {
        s32 v0t = *(s32*)(a0 + 0x1E0);
        u16 v1t = *(u16*)(a0 + 0x1E6);
        s32 r;
        *(s32*)(a0 + 0x1E0) = a1;
        r = a1 & v0t;
        *(s16*)(a0 + 0x1E4) = v1t;
        *(s32*)(a0 + 0x1DC) = r;
    }
    v0 = *(u16*)(a0 + 0x1E4);
    v0 -= 1;
    *(s16*)(a0 + 0x1E4) = v0;
    return v0;
}
