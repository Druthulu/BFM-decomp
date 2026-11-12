/* func_8013E83C — shared body (overlay slot 0x80128158, h_exact 624fc4aa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013E83C() {
    extern void func_80141C0C(int);
    extern unsigned short guess_g_MenuTransitionTimer; // Names ledger: config/names.tsv guess_g_MenuTransitionTimer
    extern unsigned short guess_g_MenuCategory; // Names ledger: config/names.tsv guess_g_MenuCategory
    extern unsigned short guess_g_MenuSwapSlot; // Names ledger: config/names.tsv guess_g_MenuSwapSlot
    extern unsigned int guess_g_MenuHelpText; // Names ledger: config/names.tsv guess_g_MenuHelpText
    extern unsigned short guess_g_MenuPanelSizes; // Names ledger: config/names.tsv guess_g_MenuPanelSizes
    extern unsigned short D_8011515A;
    extern unsigned short D_8011515C;
    extern unsigned short D_8011515E;
    extern unsigned short D_80115162;
    extern unsigned short D_80115166;
    extern void * D_8018E7C0;
    extern void * D_8018E7C4;
    extern unsigned char D_80180290;
    extern unsigned char D_801802A8;
    extern unsigned char D_8018031C;
    extern unsigned char D_80180324;


    guess_g_MenuTransitionTimer = 0;
    guess_g_MenuHelpText = 0;
    if (guess_g_MenuPanel >= 4) {
        guess_g_MenuPanel = guess_g_MenuPanel - 3;
    }
    guess_g_MenuPanelSizes = 0x106;

    if ((((int(*)(int))guess_TestGameFlag)(0x1c) & 0xFF) == 0) {
        D_8018E7C0 = &D_80180290;
        D_8018E7C4 = &D_8018031C;
    } else {
        D_8018E7C0 = &D_801802A8;
        D_8018E7C4 = &D_80180324;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    guess_g_MenuCategory = 0;
    guess_g_MenuSwapSlot = 0;

    if (guess_g_OpenMenuId == 3) {
        ((void(*)(int, int))guess_RequestSound)(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}
