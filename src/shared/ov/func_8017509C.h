/* func_8017509C — shared body (overlay slot 0x80128158, h_exact d229cf67). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8017509C(u8 *a0, s32 a1, u8 *a2, u8 *a3) {
    a1 = (s16)a1;
    a0 = a0 + a1 * 14;
    if (*(s16 *)(a0 + 0xC) == 0x7FFF) {
        return 1;
    }
    *(u16 *)(a2 + 0) = *(u16 *)(a0 + 0);
    *(u16 *)(a2 + 2) = *(u16 *)(a0 + 2);
    *(u16 *)(a2 + 4) = *(u16 *)(a0 + 4);
    *(u16 *)(a3 + 0) = *(u16 *)(a0 + 6);
    *(u16 *)(a3 + 2) = *(u16 *)(a0 + 8);
    *(u16 *)(a3 + 4) = *(u16 *)(a0 + 0xA);
    return 0;
}
