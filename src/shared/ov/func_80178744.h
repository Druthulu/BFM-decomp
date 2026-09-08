/* func_80178744 — shared body (overlay slot 0x80128158, h_exact f083aa8e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80178744(s32 a0, s32 a1);
void func_80178744(s32 a0, s32 a1) {
    s32 v0;
    s16 sv;
    if (*(s32 *)(a0 + 0x6C) != 0) {
        func_80178744(*(s32 *)(a0 + 0x6C), a1);
    }
    v0 = *(s32 *)(a0 + 0x20);
    sv = a1;
    *(s16 *)(v0 + 0x1C) = sv;
    *(s16 *)(v0 + 0x1A) = sv;
    *(s16 *)(v0 + 0x18) = sv;
    if (a1 == 0x1000) {
        s32 v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = *(u16 *)(v1 + 0x2C) & 0xFFEF;
    } else {
        s32 v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = *(u16 *)(v1 + 0x2C) | 0x10;
    }
}
