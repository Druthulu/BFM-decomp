/* func_8015640C — shared body (overlay slot 0x80128158, h_exact d17a7fc1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801564B0(s32 a0);
extern s32 func_80029178(s32 a0);
s32 func_8015640C(s32 a0, s32 a1) {
    if ((func_801564B0(a0) & 0xFFFF) != 0) {
        if ((func_80029178(0x1C) & 0xFF) != 0) {
            return (((175 * (a1 & 0xFFFF)) / 100) & 0xFFFF) | 0x8000;
        } else {
            return (((150 * (a1 & 0xFFFF)) / 100) & 0xFFFF) | 0x8000;
        }
    }
    return a1 & 0xFFFF;
}
