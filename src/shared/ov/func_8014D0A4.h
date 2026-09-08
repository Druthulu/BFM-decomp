/* func_8014D0A4 — shared body (overlay slot 0x80128158, h_exact d852a554). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014D2A0(s32 a0, void *a1, void *a2);
extern s32 func_8014D12C();
void func_8014D0A4(s32 a0) {
    s16 buf1[4];
    s16 buf2[4];
    buf1[0] = *(u16 *)(a0 + 0x88);
    buf1[1] = *(u16 *)(a0 + 0x8A);
    buf1[2] = *(u16 *)(a0 + 0x8C);
    buf2[0] = *(u16 *)(a0 + 0x6);
    buf2[1] = *(u16 *)(a0 + 0xA);
    buf2[2] = *(u16 *)(a0 + 0xE);
    if (*(s32 *)(a0 + 0x174) == 0) {
        func_8014D2A0(a0, buf1, buf2);
    } else {
        func_8014D12C(a0, buf1, buf2);
    }
}
