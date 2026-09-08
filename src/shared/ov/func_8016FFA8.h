/* func_8016FFA8 — shared body (overlay slot 0x80128158, h_exact a17ee33a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80171990(u8 *a0);
void func_8016FFA8(u8 *a0) {
    *(u16 *)(a0 + 0xAC) |= 0x40;
    *(u16 *)(a0 + 0xAA) |= 0x40;
    func_80171990(a0);
}
