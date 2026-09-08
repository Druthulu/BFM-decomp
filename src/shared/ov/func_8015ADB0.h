/* func_8015ADB0 — shared body (overlay slot 0x80128158, h_exact 6363dfde). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015ADB0(s32 arg0) {
    extern s32 D_8011F730;
    extern void func_80161124(void *a0);
    extern void func_801477E8(s32 *a0, s32 a1);
    extern void func_8014C010(s32 a0, s32 a1);
    extern void func_80146CA0(void *a0);
    if (*(u8 *)(arg0 + 0xA8) >= 0x19) {
        *(u8 *)(arg0 + 0xA8) = 0x18;
    }
    func_80161124(arg0);
    ((void (*)(s32, s32))func_801477E8)(arg0, 0xFFEE0000);
    func_8014C010(arg0, 2);
    D_8011F730 |= 1;
    ((void (*)(s32))func_80146CA0)(arg0);
}
