/* func_801418F8 — shared body (overlay slot 0x80128158, h_exact fa820ec8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801418F8(void)
{

    extern s16 guess_g_MenuSwapSlot;
    extern u8 guess_g_MenuPanelSizes[];
    extern s16 D_8011515A;
    extern u8 D_8011515C;
    extern s16 D_8011515E;
    extern s16 D_80115162;
    extern s16 D_80115166;
    extern u8  D_80180290;
    extern u8  D_801802A8;
    extern u8  D_8018031C;
    extern u8  D_80180324;
    extern void *D_8018E7C0;
    extern void *D_8018E7C4;
    u16 t;

    func_800D24A0(1);
    guess_g_MenuPanel = 2;
    t = guess_g_MenuPanel;
    (*(s16 *)&guess_g_MenuTransitionTimer) = 0;
    guess_g_MenuHelpText = 0;
    if (t >= 4) {
        guess_g_MenuPanel = t - 3;
    }
    (*(s16 *)guess_g_MenuPanelSizes) = 0x106;
    if ((guess_TestGameFlag(0x1C) & 0xFF) == 0) {
        D_8018E7C0 = &D_80180290;
        D_8018E7C4 = &D_8018031C;
    } else {
        D_8018E7C0 = &D_801802A8;
        D_8018E7C4 = &D_80180324;
    }
    D_8011515A = 0x104;
    (*(s16 *)&D_8011515C) = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    guess_g_MenuCategory = 0;
    guess_g_MenuSwapSlot = 0;
    if (guess_g_OpenMenuId == 3) {
        func_8002D4C8(0x46E, 0);
    } else {
        func_80141C0C(0);
    }
    guess_g_MenuCategory = 1;
    D_801805F0 = 0xE;
    D_801805F2 = 3;
    guess_g_MenuStep = guess_g_MenuStep + 1;
}
