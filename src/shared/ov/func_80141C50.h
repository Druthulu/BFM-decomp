/* func_80141C50 — shared body (overlay slot 0x80128158, h_exact 5cf539f1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80015144(void);
extern u16 guess_g_MenuPadHeld;
extern u16 guess_g_MenuPadPressed;
s32 func_80141C50(void) {
    if (guess_g_MenuPadHeld != 0x90F) {
        return 0;
    }
    if ((guess_g_MenuPadPressed & 0x800) == 0) {
        return 0;
    }
    return func_80015144() != 0;
}
