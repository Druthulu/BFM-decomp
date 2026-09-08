/* func_8014A6A8 — shared body (overlay slot 0x80128158, h_exact c60ba3cf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8014A6A8(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x1BD);
    if (v != 0) {
        *(u8 *)(a0 + 0x1BD) = v - 1;
    }
}
