/* func_801518D8 — shared body (overlay slot 0x80128158, h_exact 96025766). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801518D8(s32 a0) {
    u8 v1 = *(u8*)(a0 + 0x3E);
    if (v1 == 0x1B) return 1;
    if (v1 == 0x1C) return 1;
    if (v1 == 0xF) return 1;
    if (v1 == 0x10) return 1;
    if (v1 == 0x3) return 1;
    if (v1 != 0x13) return v1 == 0x17;
    return 1;
}
