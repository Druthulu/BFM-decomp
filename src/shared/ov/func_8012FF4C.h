/* func_8012FF4C — shared body (overlay slot 0x80128158, h_exact 66f0ca14). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80131CA8();  // K&R: 2 of 1 args (P37 unalias t4_ua7)
void func_8012FF4C(s32 a0) {
    *(s8 *)(a0 + 0xC1) = 5;
    if (*(s32 *)(a0 + 0xB4) & 0x20) {
        s32 v1 = *(s32 *)(a0 + 0x20);
        *(s16 *)(a0 + 0x5C) = 0;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(s16 *)(a0 + 0x98) = 0;
        *(s16 *)(v1 + 0x10) = 0;
    }
    func_80131CA8(a0, 0xF);
}
