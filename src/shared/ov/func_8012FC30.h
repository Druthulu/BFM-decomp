/* func_8012FC30 — shared body (overlay slot 0x80128158, h_exact 5e7855f1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131B14();
extern void func_8012B23C(s32 a0);
extern s32 func_80131A34(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012FC30(s32 a0) {
    *(s8 *)(a0 + 0xC1) = 0xA;
    if (*(s32 *)(a0 + 0xB4) & 0x400) {
        func_80131B14();
        *(s8 *)(a0 + 0xC2) = 0;
        *(u16 *)(a0 + 0x98) = 0;
        func_8012B23C(a0);
        func_80131A34(a0, 8);
        func_8002D4C8(0xA74, 0);
    }
    func_80131CA8(a0, 0x1A);
}
