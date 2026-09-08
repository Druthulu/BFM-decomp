/* func_80173980 — shared body (overlay slot 0x80128158, h_exact c0ab9406). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171A1C(u8 *a0);
extern s16 D_80126B30;
void func_80173980(u8 *a0) {
    if (D_80126B30 == 0) {
        *(u16 *)(a0 + 0xAC) |= 0x80;
        *(u16 *)(a0 + 0xAA) |= 0x80;
    } else {
        *(u16 *)(a0 + 0xAC) |= 0x10;
    }
    func_80171A1C(a0);
}
