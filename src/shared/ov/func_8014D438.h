/* func_8014D438 — shared body (overlay slot 0x80128158, h_exact 9151c10a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014D610(s32 a0, s32 a1, u16 *a2);
extern s32 func_8014D4C0(s32 a0, void *a1, void *a2);
void func_8014D438(s32 a0) {
    s16 buf1[4];
    s16 buf2[4];
    buf1[0] = *(u16 *)(a0 + 0x88);
    buf1[1] = *(u16 *)(a0 + 0x8A);
    buf1[2] = *(u16 *)(a0 + 0x8C);
    buf2[0] = *(u16 *)(a0 + 0x6);
    buf2[1] = *(u16 *)(a0 + 0xA);
    buf2[2] = *(u16 *)(a0 + 0xE);
    if (*(s32 *)(a0 + 0x174) == 0) {
        func_8014D610(a0, buf1, buf2);
    } else {
        func_8014D4C0(a0, buf1, buf2);
    }
}
