/* func_801399F0 — shared body (overlay slot 0x80128158, h_exact b8c9276b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801399F0(s32 a0) {
    s32 v1;
    if (*(s32*)(a0 + 0x0) == 0) return -1;
    v1 = *(s16*)(a0 + 0x4);
    if (v1 == 0) return -1;
    if (v1 == 0xE) return -1;
    if (v1 == 0xD) return *(s8*)(a0 + 0x1F);
    return 0;
}
