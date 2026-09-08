/* func_80148D0C — shared body (overlay slot 0x80128158, h_exact d04fb717). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148D0C(s32 a0, s32 a1) {
    s32 v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x12) = (a1 - 0x400) & 0xFFF;
    return 1;
}
