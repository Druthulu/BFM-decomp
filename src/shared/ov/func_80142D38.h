/* func_80142D38 — shared body (overlay slot 0x80128158, h_exact d2c087e1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BEE8(s32 a0);
s32 func_80142D38(s32 *a0) {
    if (func_8012BEE8((s32)a0) == 1) {
        return 1;
    }
    if (a0[0x1C / 4] & 1) {
        ((s32 *)a0[0x20 / 4])[1] |= 0x80000000;
    } else {
        ((s32 *)a0[0x20 / 4])[1] &= 0x7FFFFFFF;
    }
    return 0;
}
