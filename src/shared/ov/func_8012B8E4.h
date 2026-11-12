/* guess_TurnStepToTarget — shared body (overlay slot 0x80128158, h_exact 018880c8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126CB8;
extern s16 D_80126CB4;
extern s32 ratan2(s32 a0, s32 a1);
/* guess_TurnStepToTarget: returns a signed yaw step that turns object arg0 toward a target point at 1/arg1 of the remaining angle (0 when already facing it)
 * Confidence medium, code inference: yaw toward (D_80126CB4, D_80126CB8) minus the facing at +0x12 of *(a0+0x20), wrapped to +-0x800, / arg1, at least +-1; the target point is not known
 * Names ledger: config/names.tsv guess_TurnStepToTarget */
s32 guess_TurnStepToTarget(s32 arg0, s32 arg1) {
    register s32 d __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B headers1) wall:lreg-priority
    s32 s1ang;
    s32 u5; s32 u6; s32 iVar4; s32 q; s32 t;
    d = arg1;
    s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    u5 = (ratan2(*(s16 *)(arg0 + 0xE) - D_80126CB8, D_80126CB4 - *(s16 *)(arg0 + 6)) - 0x400) & 0xFFF;
    do { d = (s16)d; } while (0);  // !FAKE: do-while
    u6 = s1ang & 0xFFF;
    if (u6 == u5) return 0;
    iVar4 = u5 - u6;
    if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
    if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
    if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; }
    else { q = iVar4 / d; if (q == 0) q = -1; }
    return q;
}
