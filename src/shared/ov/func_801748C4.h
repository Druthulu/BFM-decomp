/* func_801748C4 — shared body (overlay slot 0x80128158, h_exact b5fb89b6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801748C4(s32 a0) {
    u8 v = *(u8 *)(a0 + 0x214) + 1;
    *(s32 *)(a0 + 0x44) |= 0x4000000;
    *(u8 *)(a0 + 0x214) = v;
}
