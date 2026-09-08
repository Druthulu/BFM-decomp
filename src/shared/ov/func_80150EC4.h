/* func_80150EC4 — shared body (overlay slot 0x80128158, h_exact f04f51c2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800AE6C0;
extern s16 D_800AE6C8;
extern s16 D_800AE6CA;
extern u8 D_80126948[];
extern s16 D_800AE6CC;
extern s32 D_800AE6C4;
extern s16 D_800AE6CE;
extern u8 D_800AE6BE;
extern s32 D_800AE6B0;
extern u8 D_801201F8[];
void func_80150EC4(s32 a0, s32 a1) {
    D_800AE6C0 = 1;
    D_800AE6C8 = *(u16 *)(a0 + 0x6);
    D_800AE6CA = *(u16 *)(a0 + 0xA);
    D_800AE6CC = *(u16 *)(a0 + 0xE);
    D_800AE6CE = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
    D_800AE6B0 = *(s32 *)(((a1 << 2) + D_800AE6C4) + 4);
    D_800AE6BE = a1 + 1;
    *(struct copy00 *)D_801201F8 = *(struct copy00 *)D_80126948;
}
