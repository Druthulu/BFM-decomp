/* func_8014E48C — shared body (overlay slot 0x80128158, h_exact b608acbd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014E5B4(s32 a0, void *a1, void *a2);
extern s32 func_8014E514(u8 *a0, s32 a1, s32 a2);
void func_8014E48C(s32 a0) {
    s16 buf1[4];
    s16 buf2[4];
    buf1[0] = *(u16 *)(a0 + 0x88);
    buf1[1] = *(u16 *)(a0 + 0x8A);
    buf1[2] = *(u16 *)(a0 + 0x8C);
    buf2[0] = *(u16 *)(a0 + 0x6);
    buf2[1] = *(u16 *)(a0 + 0xA);
    buf2[2] = *(u16 *)(a0 + 0xE);
    if (*(s32 *)(a0 + 0x17C) == 0) {
        func_8014E5B4(a0, buf1, buf2);
    } else {
        func_8014E514(a0, buf1, buf2);
    }
}
