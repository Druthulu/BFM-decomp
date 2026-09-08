/* func_80131E38 — shared body (overlay slot 0x80128158, h_exact a082860f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131CA8(int a0, int a1);
void func_80131E38(u8 *a0) {
    *(s8 *)(a0 + 0xC1) = 0xF;
    if (*(s32 *)(a0 + 0xB4) & 0x40000) {
        *(s32 *)(a0 + 0x1C) = 6;
        *(s16 *)(a0 + 0x5C) = 0;
    }
    func_80131CA8((int)a0, 0x39);
}
