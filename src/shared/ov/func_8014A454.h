/* func_8014A454 — shared body (overlay slot 0x80128158, h_exact 4f25dd67). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012A60(s32 a0, s32 a1);
s32 func_8014A454(s32 a0) {
    s32 v0;
    if (*(u16 *)(a0 + 0x3C) & 0x4000) {
        v0 = (s16)func_80012A60(*(s16 *)(a0 + 0x42),
                                (*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800) & 0xFFF);
        if (v0 < 0x2AA) {
            return 1;
        }
    }
    return 0;
}
