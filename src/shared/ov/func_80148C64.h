/* func_80148C64 — shared body (overlay slot 0x80128158, h_exact b7381679). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148C64(s32 a0, s32 a1) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x800) & 0xFFF;
    return 1;
}
