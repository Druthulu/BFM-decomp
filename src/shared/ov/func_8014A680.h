/* func_8014A680 — shared body (overlay slot 0x80128158, h_exact 8d816aae). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014A680(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x1BC);
    if (v != 0) {
        *(u8 *)(a0 + 0x1BC) = v - 1;
    }
}
