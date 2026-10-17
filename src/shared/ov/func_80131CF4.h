/* func_80131CF4 — shared body (overlay slot 0x80128158, h_exact 9d2db9ce). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80131CF4(s32 *a0, s32 a1)
{
    if (a0 == 0) {
        return 0;
    }
    while (a0[0] != 0) {
        if (a0[0] == 0xD) {
            a0 = (s32 *)a0[1];
        } else if (a0[0] == a1) {
            return a0[1];
        } else {
            a0 = (s32 *)((u8 *)a0 + 8);
        }
    }
    return 0;
}
