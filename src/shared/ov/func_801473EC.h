/* func_801473EC — shared body (overlay slot 0x80128158, h_exact 90df300c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801473EC(s32 *a0) {
    s32 *a2;
    a2 = a0;
    a2[1] += a2[4];
    a2[2] += a2[5];
    a2[3] += a2[6];
    if (a2[4] != 0 || a2[5] != 0 || a2[6] != 0) {
        a2[0x11] |= 0x80000000;
    }
}
