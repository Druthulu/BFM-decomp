/* func_80130AC4 — shared body (overlay slot 0x80128158, h_exact d4a500b3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80130AC4(s32 a0) {
    s16 v0;
    v0 = *(u16*)(a0 + 0xAC) - 1;
    *(u16*)(a0 + 0xAC) = v0;
    if (v0 == 0) {
        *(u8*)(a0 + 0xC1) = 0;
        *(s16*)(a0 + 0x5E) = 0;
    }
}
