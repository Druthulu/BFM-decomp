/* func_8014CC28 — shared body (overlay slot 0x80128158, h_exact 90056bd9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014D3E0();
extern void func_8014D04C(void);
extern void func_8014CCB4(void);
void func_8014CC28(s32 a0) {
    if (*(s32 *)(a0 + 0x44) < 0) {
        if (*(s16 *)(a0 + 0xA) != *(s16 *)(a0 + 0x8A)) {
            func_8014D3E0(a0);
            return;
        }
        if (*(s16 *)(a0 + 0x6) != *(s16 *)(a0 + 0x88) ||
            *(s16 *)(a0 + 0xE) != *(s16 *)(a0 + 0x8C)) {
            func_8014D04C();
            return;
        }
    }
    func_8014CCB4();
}
