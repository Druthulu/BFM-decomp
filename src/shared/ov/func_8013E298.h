/* func_8013E298 — shared body (overlay slot 0x80128158, h_exact 811a219e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126CB0;
s32 func_8013E298(s16 *a0) {
    s32 diff;
    diff = a0[2] - D_80126CB0;
    if (diff < 0) {
        diff = -diff;
    }
    return (u32)(diff - 0x2C1) < 0x3F;
}
