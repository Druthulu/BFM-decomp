/* func_80149BEC — shared body (overlay slot 0x80128158, h_exact a55cd599). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80149BEC(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x223);
    if (v != 0) {
        *(u8 *)(a0 + 0x223) = v - 1;
    }
}
