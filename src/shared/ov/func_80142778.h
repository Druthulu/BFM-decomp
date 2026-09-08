/* func_80142778 — shared body (overlay slot 0x80128158, h_exact 9e5c3ca7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C218(void *a0);
void func_80142778(u8 *a1) {
    u8 *a0 = *(u8 **)(a1 + 0x20);
    *(u16 *)(a0 + 0x18) = *(u16 *)(a0 + 0x18) - 0x800;
    *(u16 *)(a0 + 0x1A) = *(u16 *)(a0 + 0x1A) - 0x800;
    *(u16 *)(a1 + 0xA) = *(u16 *)(a1 + 0xA) + 0x10;
    if (*(s16 *)(a0 + 0x18) <= 0) {
        func_8012C218(a1);
    }
}
