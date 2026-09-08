/* func_8017869C — shared body (overlay slot 0x80128158, h_exact d2e5c8ae). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80178744(s32 a0, s32 a1);
void func_8017869C(s32 a0) {
    s32 v1;
    s32 a1;
    if (*(s16 *)(a0 + 0xAA) == 0) {
        return;
    }
    *(s16 *)(a0 + 0xAA) = *(s16 *)(a0 + 0xAA) - 1;
    v1 = *(s16 *)(a0 + 0xAA);
    if (v1 == 0) {
        a1 = 0x1000;
        if (*(u16 *)(a0 + 0x5E) == 0x1E) {
            *(s16 *)(a0 + 0x5E) = 0;
        }
    } else if (v1 >= 0xF1) {
        a1 = 0x1000 - (0x100 - v1) * 0x90;
    } else {
        if (v1 < 0x10) {
            a1 = 0x1000 - v1 * 0x90;
        } else {
            a1 = 0x700;
        }
    }
    func_80178744(a0, a1);
}
