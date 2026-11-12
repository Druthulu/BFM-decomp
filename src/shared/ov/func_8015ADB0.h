/* func_8015ADB0 — shared body (overlay slot 0x80128158, h_exact 6363dfde). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015ADB0(s32 arg0) {
    extern s32 D_8011F730;
    extern void func_80161124(void *a0);
    extern void guess_SetVertSpeed(s32 *a0, s32 a1);
    extern void guess_SpawnSmallObjectType2(s32 a0, s32 a1);
    extern void guess_NextStep(void *a0);
    if (*(u8 *)(arg0 + 0xA8) >= 0x19) {
        *(u8 *)(arg0 + 0xA8) = 0x18;
    }
    func_80161124(arg0);
    ((void (*)(s32, s32))guess_SetVertSpeed)(arg0, 0xFFEE0000);
    guess_SpawnSmallObjectType2(arg0, 2);
    D_8011F730 |= 1;
    ((void (*)(s32))guess_NextStep)(arg0);
}
