/* func_8015AB7C — shared body (overlay slot 0x80128158, h_exact 70b23b1b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D48DC;
s32 func_8015AB7C(s32 a0) {
    u8 v1;
    if (*(s32*)(a0 + 0xB4) == (s32)&D_800D48DC) {
        v1 = *(u8*)(a0 + 0xDC);
        if (v1 < 6) {
            return 0x10;
        }
        if (v1 < 0xB) {
            return 0x12;
        }
        if (v1 < 0x10) {
            return 0x7;
        }
        return 0x9;
    }
    return *(u8*)(a0 + 0xBC);
}
