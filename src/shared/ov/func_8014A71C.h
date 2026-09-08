/* func_8014A71C — shared body (overlay slot 0x80128158, h_exact 2c9ffe88). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014A71C(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x1BE);
    if (v != 0) {
        *(u8 *)(a0 + 0x1BE) = v - 1;
    }
}
