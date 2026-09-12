/* func_8012F75C — shared body (overlay slot 0x80128158, h_exact 25f2fd43). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131B14();
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012F75C(s32 a0) {
    *(u8 *)(a0 + 0xC1) = 3;
    if (*(s32 *)(a0 + 0xB4) & 0x4) {
        func_80131B14();
        *(s32 *)(a0 + 0x1C) = 0x10;
        *(s16 *)(a0 + 0x98) = 0;
    }
    func_80131CA8(a0, 6);
}
