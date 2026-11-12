/* func_8013E5E8 — shared body (overlay slot 0x80128158, h_exact 0b4494b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013E5E8(void)
{
    extern u16 guess_g_MenuPadPressed; // Names ledger: config/names.tsv guess_g_MenuPadPressed
    extern u16 guess_g_MenuPadHeld; // Names ledger: config/names.tsv guess_g_MenuPadHeld
    extern unsigned short guess_g_MenuStep; // Names ledger: config/names.tsv guess_g_MenuStep
    extern u16 guess_g_MenuFrameCounter; // Names ledger: config/names.tsv guess_g_MenuFrameCounter
    extern void (*D_8017FE78[])(void);
    void (**new_var)(void);
    void (*fp)(void);
    func_80029444();
    func_801754A8();
    guess_g_MenuPadPressed = func_80014ED4(0);
    guess_g_MenuPadHeld = func_80015018(0);
    new_var = &D_8017FE78[guess_g_MenuStep];
    fp = *new_var;
    fp();
    func_800190AC();
    func_80141C04();
    guess_g_MenuFrameCounter += 1;
}
