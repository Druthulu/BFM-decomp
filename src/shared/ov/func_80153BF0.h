/* func_80153BF0 — shared body (overlay slot 0x80128158, h_exact a6a39041). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801151FC;
extern s32 D_80127518;
s32 func_80153BF0(s32 a0) {
    if (a0 == D_801151FC) {
        D_80127518 = 0;
        return 1;
    }
    return 0;
}
