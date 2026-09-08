/* func_80148038 — shared body (overlay slot 0x80128158, h_exact a1d2a451). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80148038(s32 a0, s32 a1) {
    s32 v1 = *(s32*)(a0 + 0x34);
    if (v1 < 0) {
        if (a1 < 0) {
            if ((s32)0xFFE10000 < v1) {
            } else {
                a1 = 0;
            }
        }
    } else {
        if (a1 > 0) {
            if (0x1EFFFF < v1) {
                a1 = 0;
            }
        }
    }
    *(s32*)(a0 + 0x34) += a1;
}
