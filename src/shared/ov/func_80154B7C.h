/* func_80154B7C — shared body (overlay slot 0x80128158, h_exact 7c5dbb5a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80154B7C(u8 *a0, s32 a1) {
    *(s32 *)(a0 + 0xD0) = a1;
    *(s16 *)(a0 + 0xD6) = 1;
    *(s16 *)(a0 + 0xD4) = 1;
    a0[0xD8] = 0;
    a0[0xD9] = 0;
}
