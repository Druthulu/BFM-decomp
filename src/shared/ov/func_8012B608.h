/* guess_GetAngleStepToward — shared body (overlay slot 0x80128158, h_exact 97bdbab6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_GetAngleStepToward: returns the signed shortest difference from angle a0 to a1 (12-bit, wrapped to -0x800..0x800) divided by a2, at least +-1 unless equal
 * Confidence high, code inference: a0, a1 & 0xFFF; 0 when equal; d = a1 - a0 wrapped by 0x1000 into -0x800..0x800; d / a2, or +-1 when that is 0
 * Names ledger: config/names.tsv guess_GetAngleStepToward */
s32 guess_GetAngleStepToward(s32 a0, s32 a1, s32 a2) {
    s32 v1;
    s32 t;
    a0 &= 0xFFF;
    a1 &= 0xFFF;
    v1 = a1 - a0;
    if (a0 == a1) {
        return 0;
    }
    if (v1 >= 0x801) {
        t = a0 + 0x1000;
        v1 = a1 - t;
    }
    if (v1 < -0x800) {
        t = a0 - 0x1000;
        v1 = a1 - t;
    }
    if (v1 >= 0) {
        v1 = v1 / a2;
        if (v1 != 0) {
            return v1;
        }
        v1 = 1;
    } else {
        v1 = v1 / a2;
        if (v1 != 0) {
            return v1;
        }
        v1 = -1;
    }
    return v1;
}
