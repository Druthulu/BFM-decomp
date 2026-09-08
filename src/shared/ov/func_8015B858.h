/* func_8015B858 — shared body (overlay slot 0x80128158, h_exact 05353a78). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D4BE0[];
extern s32 D_8011F730;
extern s32 func_8014A51C();
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
s32 func_8015B858(u8 *a0) {
    if (*(u8 *)(a0 + 0x1C6) != 0) return 0;
    if (*(s32 *)(a0 + 0x240) != 0) return 0;
    if (func_8014A51C() == 0) return 0;
    *(s32 *)(a0 + 0x23C) = *(s32 *)(a0 + 0xB4);
    *(u8 *)(a0 + 0x244) = *(u8 *)(a0 + 0xBC);
    func_801477E8((s32 *)a0, 0xFFF20000);
    func_80154274((s32 *)a0, (s32)D_800D4BE0);
    D_8011F730 |= 2;
    return 1;
}
