/* func_8015ABD4 — shared body (overlay slot 0x80128158, h_exact e609793f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016F1AC(void);
extern s32 func_80029178(s32 a0);
extern s32 D_8011F9C4;
s32 func_8015ABD4(s32 a0, s32 a1, s32 a2) {
    if (func_8016F1AC() != 0) {
        return 0;
    }
    if (a2 < a1) {
        if (D_8011F9C4 == 0) {
            return 0;
        }
        if ((func_80029178(0x21) & 0xFF) != 0) {
            return 0;
        }
    }
    return 1;
}
