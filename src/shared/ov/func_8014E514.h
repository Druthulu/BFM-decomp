/* func_8014E514 — shared body (overlay slot 0x80128158, h_exact e88ac80c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_8014E514(u8 *a0, s32 a1, s32 a2) {
    u8 *p;
    s32 q;
    p = *(u8 **)(a0 + 0x17C);
    if (*(u16 *)p != 0 &&
        (*(u16 *)(p + 0x5C) & 0x40) != 0 &&
        (q = *(s32 *)(p + 0x58)) != 0 &&
        func_80135888(*(s32 *)(p + 0x20), q, a1, a2) != 0) {
        goto success;
    }
    *(s32 *)(a0 + 0x17C) = 0;
    return 0;
success:
    *(u16 *)(a0 + 6) = *(u16 *)(p + 6);
    *(u16 *)(a0 + 0xE) = *(u16 *)(p + 0xE);
    return 1;
}
