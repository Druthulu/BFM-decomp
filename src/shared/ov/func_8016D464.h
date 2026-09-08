/* func_8016D464 — shared body (overlay slot 0x80128158, h_exact 678d835a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D22E4(s32 a0);
extern short func_8016CF04();
void func_8016D464(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x34);
    s32 v0;
    func_800D22E4((s32)a0);
    func_8016CF04((s32)a0, 1);
    v0 = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v0;
    if (v0 == -1 || *(u16 *)s1 != 1) {
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}
