/* func_8012D5E4 — shared body (overlay slot 0x80128158, h_exact 45a2d18d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126B98;
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3) {
    if (func_8012DEB8(a0, a1, a2) != 0) {
        D_80126B98 = a3;
        return 1;
    }
    return 0;
}
