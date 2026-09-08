/* func_80154ED8 — shared body (overlay slot 0x80128158, h_exact bd2f9eeb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80078E96;
extern u8 D_800D8D10[];
extern s16 D_80078E9E;
extern u16 D_80078EA6;
extern void func_801550FC(s32 a0);
void func_80154ED8(s32 a0, s32 a1) {
    *(s32 *)(a0 + 0xC8) = a1;
    if (D_80078E96 & 0x8000) {
        *(s32 *)(a0 + 0xC8) = a1 | 0x1000000;
        func_801550FC((s32)D_800D8D10);
        return;
    }
    if (D_80078E9E >= 0x10) {
        if (*(s16 *)&D_80078EA6 >= 0x10) {
            goto and_path;
        }
    }
    if ((*(s32 *)(a0 + 0x44) & 0xC0) != 0) {
        goto and_path;
    }
    *(s32 *)(a0 + 0xC8) = a1 | 0x1000000;
    func_801550FC(0x40000002);
    return;
and_path:
    *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) & 0xC0FFFFFF;
    func_801550FC(a1);
}
