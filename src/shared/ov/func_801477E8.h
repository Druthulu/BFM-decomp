/* func_801477E8 — shared body (overlay slot 0x80128158, h_exact d2f74e8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801477E8(s32 *a0, s32 a1) {
    a0[0xD] = a1;
    if (a1 < -0x1F0000) {
        a0[0xD] = -0x1F0000;
    } else if (a1 > 0x1F0000) {
        a0[0xD] = 0x1F0000;
    }
}
