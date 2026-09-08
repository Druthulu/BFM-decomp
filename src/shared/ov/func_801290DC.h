/* func_801290DC — shared body (overlay slot 0x80128158, h_exact abb6f1fe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 *func_8012913C(s32 a0);
u8 *func_801290DC(s32 a0, u8 *a1) {
    u8 *v1 = func_8012913C(a0 & 0xFFFF);
    if (v1 != 0) {
        *(u16 *)(v1 + 0x6) = *(u16 *)(a1 + 0x0);
        *(u16 *)(v1 + 0xA) = *(u16 *)(a1 + 0x2);
        *(u16 *)(v1 + 0xE) = *(u16 *)(a1 + 0x4);
    }
    return v1;
}
