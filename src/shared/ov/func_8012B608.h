/* func_8012B608 — shared body (overlay slot 0x80128158, h_exact 97bdbab6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012B608(s32 a0, s32 a1, s32 a2) {
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
