/* func_80130360 — shared body (overlay slot 0x80128158, h_exact 24a27bf0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131CA8(s32 a0, s32 a1);
void func_80130360(s32 a0) {
    *(u8*)(a0 + 0xC1) = 2;
    if (*(s32*)(a0 + 0xB4) & 2) {
        *(s16*)(a0 + 0x5C) = 0;
        *(s16*)(a0 + 0x98) = 0;
        *(s32*)(a0 + 0x1C) = 0;
    }
    func_80131CA8(a0, 1);
}
