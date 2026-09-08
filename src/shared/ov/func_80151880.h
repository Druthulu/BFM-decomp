/* func_80151880 — shared body (overlay slot 0x80128158, h_exact c0e868eb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80151880(s32 a0) {
    u16 h;
    s32 v1;
    h = *(u16*)(a0 + 0x3E);
    v1 = h & 0xFF;
    if (v1 == 0x1B) return 1;
    if (v1 == 0x1C) return 1;
    if (v1 == 0xF) return 1;
    if (v1 == 0x10) return 1;
    if (v1 == 0xB) return 2;
    if (v1 != 0x1F) return (h >> 8) & 2;
    return 1;
}
