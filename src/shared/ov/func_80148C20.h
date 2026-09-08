/* func_80148C20 — shared body (overlay slot 0x80128158, h_exact 2b1abb85). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80148C20(s32 a0, s16 a1) {
    s32 *p = *(s32 **)((s32)a0 + 0x20);
    *(s16*)((s32)p + 0x12) = a1;
    return 1;
}
