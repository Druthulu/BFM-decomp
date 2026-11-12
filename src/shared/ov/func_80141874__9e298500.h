/* func_80141874 — shared body (overlay slot 0x80128158, h_exact 9e298500). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80141874(void) {

    extern u16 guess_g_MenuPadHeld[]; // Names ledger: config/names.tsv guess_g_MenuPadHeld
    extern u16 guess_g_MenuFrameCounter; // Names ledger: config/names.tsv guess_g_MenuFrameCounter
    extern void (*D_8017FEC4[])(void);
    func_801754A8();
    guess_g_MenuPadPressed = func_80014ED4(0);
    guess_g_MenuPadHeld[0] = func_80015018(0);
    D_8017FEC4[guess_g_MenuStep]();
    func_80141C04();
    guess_g_MenuFrameCounter += 1;
}
