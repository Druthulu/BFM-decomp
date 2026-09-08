/* func_8016C374 — shared body (overlay slot 0x80128158, h_exact c24c1e19). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 v;
    *(u16 *)(a1 + 0x0) = *(u16 *)(a1 + 0x0) - 0xA;
    if ((s16)*(u16 *)(a1 + 0x0) < 0) {
        *(u16 *)(a1 + 0x0) = 0;
    }
    *(u16 *)(a1 + 0x2) = *(u16 *)(a1 + 0x2) - 0xA;
    if ((s16)*(u16 *)(a1 + 0x2) < 0) {
        *(u16 *)(a1 + 0x2) = 0;
    }
    *(u16 *)(a1 + 0x4) = *(u16 *)(a1 + 0x4) - 0xA;
    if ((s16)*(u16 *)(a1 + 0x4) < 0) {
        *(u16 *)(a1 + 0x4) = 0;
    }
    *(u16 *)(a2 + 0x0) = *(u16 *)(a2 + 0x0) - 0xA;
    if ((s16)*(u16 *)(a2 + 0x0) < 0) {
        *(u16 *)(a2 + 0x0) = 0;
    }
    *(u16 *)(a2 + 0x2) = *(u16 *)(a2 + 0x2) - 0xA;
    if ((s16)*(u16 *)(a2 + 0x2) < 0) {
        *(u16 *)(a2 + 0x2) = 0;
    }
    *(u16 *)(a2 + 0x4) = *(u16 *)(a2 + 0x4) - 0xA;
    if ((s16)*(u16 *)(a2 + 0x4) < 0) {
        *(u16 *)(a2 + 0x4) = 0;
    }
    *(u8 *)(a3 + 0x0) = *(u16 *)(a1 + 0x0);
    *(u8 *)(a3 + 0x1) = *(u16 *)(a1 + 0x2);
    *(u8 *)(a3 + 0x2) = *(u16 *)(a1 + 0x4);
    *(u8 *)(a3 + 0x4) = *(u16 *)(a2 + 0x0);
    *(u8 *)(a3 + 0x5) = *(u16 *)(a2 + 0x2);
    *(u8 *)(a3 + 0x6) = *(u16 *)(a2 + 0x4);
    v = *(u16 *)(a2 + 0x4) | (*(u16 *)(a2 + 0x0) | *(u16 *)(a2 + 0x2));
    return (s16)v;
}
