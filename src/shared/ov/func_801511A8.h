/* func_801511A8 — shared body (overlay slot 0x80128158, h_exact 7262cd86). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801511A8(u8 *a0) {
    u16 v = *(u16 *)(a0 + 0x3C);
    *(s16 *)(a0 + 0x3E) = 0;
    *(s16 *)(a0 + 0x40) = 0;
    *(s16 *)(a0 + 0x42) = 0;
    *(u16 *)(a0 + 0x3C) = v & 0xFFFE;
}
