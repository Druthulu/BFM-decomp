/* func_80154AB4 — shared body (overlay slot 0x80128158, h_exact 51f0c666). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80154AB4(s32 a0, s32 a1) {
    s32 *base = *(s32 **)(a0 + 0xCC);
    s32 v1 = base[a1];
    *(s16 *)(a0 + 0xD6) = 1;
    *(s16 *)(a0 + 0xD4) = 1;
    *(s8 *)(a0 + 0xD8) = 0;
    *(s8 *)(a0 + 0xD9) = 0;
    *(s32 *)(a0 + 0xD0) = v1;
}
