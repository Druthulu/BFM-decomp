/* func_80172358 — shared body (overlay slot 0x80128158, h_exact 7e92fd5b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80172358(u8 *a0, u8 *a1) {
    *(u16 *)(a0 + 6) = *(u16 *)(a1 + 0);
    *(u16 *)(a0 + 0xA) = *(u16 *)(a1 + 2);
    *(u16 *)(a0 + 0xE) = *(u16 *)(a1 + 4);
    *(struct U8 *)(a0 + 0x90) = *(struct U8 *)(a1 + 0);
    *(struct U8 *)(a0 + 0x88) = *(struct U8 *)(a0 + 0x90);
}
