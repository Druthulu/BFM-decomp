/* guess_PlaneDistBelowLimit — shared body (overlay slot 0x80128158, h_exact 3860aabf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_PlaneDistBelowLimit: tests whether dot(a0, a1) + a2 (a plane distance) is below -0x1800, or -0x2F00 when a3[1] >= -0xE00
 * Confidence medium, code inference: returns (a0 . a1 + a2) < t over two s16 Vec3s, t = -0x1800 for a3[1] < -0xE00 else -0x2F00; only caller func_80133CD4
 * Names ledger: config/names.tsv guess_PlaneDistBelowLimit */
s32 guess_PlaneDistBelowLimit(s16 *a0, s16 *a1, s32 a2, s16 *a3) {
    s32 t1;
    s32 sum;
    if (a3[1] < -0xE00) {
        t1 = -0x1800;
    } else {
        t1 = -0x2F00;
    }
    sum = a0[0] * a1[0] + a0[1] * a1[1];
    sum = sum + a0[2] * a1[2];
    sum = sum + a2;
    return sum < t1;
}
