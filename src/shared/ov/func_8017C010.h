/* func_8017C010 — shared body (overlay slot 0x80128158, h_exact 60e98391). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C010(s32 a0, s32 a1, s32 a2) {
    extern u8 D_801202A0[];
    u8 *p;
    short i;
    p = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x6B) {
            *(s16 *)(p + 0x70) = a2;
            *(s32 *)(p + 0xD4) = a0;
            *(s32 *)(p + 0xD8) = a1;
            return;
        }
        p += 0x10C;
    }
}
