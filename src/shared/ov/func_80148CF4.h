/* func_80148CF4 — shared body (overlay slot 0x80128158, h_exact d4ff85f0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148CF4(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x600) & 0xFFF;
    return 1;
}
