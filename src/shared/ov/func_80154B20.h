/* func_80154B20 — shared body (overlay slot 0x80128158, h_exact 4cdcd2ce). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80154B20(s32 a0, s32 a1, s32 a2) {
    s32 *base = *(s32 **)(a0 + 0xCC);
    s32 v1 = base[a1];
    *(s16 *)(a0 + 0xD6) = 1;
    *(s16 *)(a0 + 0xD4) = 1;
    *(s8 *)(a0 + 0xD8) = a2;
    *(s8 *)(a0 + 0xD9) = a2;
    *(s32 *)(a0 + 0xD0) = v1;
}
