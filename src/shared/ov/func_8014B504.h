/* func_8014B504 — shared body (overlay slot 0x80128158, h_exact 6969ca26). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016F1AC(void);
extern s16 D_80078E9A;
extern s32 D_80078E98;
void func_8014B504(u16 *a0) {
    s32 v1;
    if (func_8016F1AC() != 0) {
        return;
    }
    if (*a0 == 0x1E || *a0 == 0x1A) {
        return;
    }
    if ((D_80078E9A & 0x8000) == 0) {
        return;
    }
    v1 = D_80078E98 + 0x1555;
    D_80078E98 = v1;
    if (0x257F6A < (v1 & 0x7FFF0000)) {
        D_80078E98 = 0;
    }
}
