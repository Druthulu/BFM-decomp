/* func_80141A60 — shared body (overlay slot 0x80128158, h_exact 74c515f5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80141A60(void)
{

    extern u8  D_8011514D;
    extern u8  D_8011515C;
    extern u16 guess_g_MenuFrameCounter; // Names ledger: config/names.tsv guess_g_MenuFrameCounter
    s32 iVar1;
    s32 pad[2];
    (void)&pad;   /* §36#3 frame-pad induction: force frame 0x20 (vs 0x18) */

    guess_g_MenuPacketPtr = ((s32 *)guess_g_MenuPacketBases)[(*(u16 *)&guess_g_DoubleBufferIndex)];
    func_8013F350();
    if ((*(u16 *)&guess_g_MenuPanel) >= 4) {
        func_8013FAF8((*(u16 *)&guess_g_MenuPanel), (*(u16 *)&guess_g_MenuPanel) + 1);
    }
    func_8013FAF8(2, 3);
    iVar1 = func_8014032C(2, (s16)((*(u8 *)&D_8011514C) + D_8011514D * D_8011515C));
    if (iVar1 != 0 && iVar1 != guess_g_MenuHelpText) {
        guess_g_MenuHelpText = iVar1;
        guess_CloseTextWindow0();
        guess_OpenTextWindowCenteredAt(iVar1, (int)&D_8017FE40);
    }
    func_80137B80();
    iVar1 = func_800D0EC4();
    if (iVar1 != 0) {
        guess_g_MenuFrameCounter = 0xfff8;
        guess_g_MenuStep = guess_g_MenuStep + 1;
    }
}
