/* func_80175014 — shared body (overlay slot 0x80128158, h_exact 097427f4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80175014(u8 *a0, u8 *a1, s32 a2) {
    a2 = (s16)a2;
    a1 = a1 + a2 * 14;
    if (*(s16 *)(a1 + 0xC) == 0x7FFF) {
        return 1;
    }
    *(s32 *)(a0 + 0x3C) = *(s16 *)(a1 + 0);
    *(s32 *)(a0 + 0x40) = *(s16 *)(a1 + 2);
    *(s32 *)(a0 + 0x44) = *(s16 *)(a1 + 4);
    *(s32 *)(a0 + 0x48) = *(s16 *)(a1 + 6);
    *(s32 *)(a0 + 0x4C) = *(s16 *)(a1 + 8);
    *(s32 *)(a0 + 0x50) = *(s16 *)(a1 + 0xA);
    *(s32 *)(a0 + 0x54) = *(s16 *)(a1 + 0xC) << 5;
    return 0;
}
