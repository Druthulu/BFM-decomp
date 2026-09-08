/* func_8012BF7C — shared body (overlay slot 0x80128158, h_exact d196e56d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126CB0;
s32 func_8012BF7C(s16 *a0) {
    s32 diff;
    diff = a0[7] - D_80126CB0;
    if (diff < 0) {
        diff = -diff;
    }
    return diff >= 0x360;
}
