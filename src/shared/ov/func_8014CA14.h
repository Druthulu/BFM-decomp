/* func_8014CA14 — shared body (overlay slot 0x80128158, h_exact 7576525b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 func_8014CA70(s32 a0, s32 a1);
extern void func_80147364(u16 param_1, u16 param_2);
extern void *D_8012707C;
s32 func_8014CA14(s32 a0, s32 a1) {
    u16 x = func_8014CA70(a0, a1);
    if (x == 0) {
        return 1;
    }
    if (x != (s32)D_8012707C) {
        func_80147364(x, 0);
        return 0;
    }
    D_8012707C = 0;
    return 0;
}
