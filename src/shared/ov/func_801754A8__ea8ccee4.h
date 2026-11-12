/* func_801754A8 — shared body (overlay slot 0x80128158, h_exact ea8ccee4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801754A8(void) {

    extern u8 guess_g_HudState; // Names ledger: config/names.tsv guess_g_HudState
    extern unsigned char guess_g_ActiveMenu; // Names ledger: config/names.tsv guess_g_ActiveMenu
    extern s32 D_80126B9C;
    extern DispatchFn D_801822B0[];
    u8 *p = &guess_g_HudState;
    s32 r = guess_GetStoryProgress();
    s32 flag = 0;

    if (((guess_g_ActiveMenu == 0) && ((D_80126B9C & 0x80) == 0)) ||
        (0x4AF < (u32)(r - 10))) {
        flag = 1;
    }
    p[9] = flag;
    D_801822B0[p[0]]((void *)p);
}
