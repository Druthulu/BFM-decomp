/* func_8014168C — shared body (overlay slot 0x80128158, h_exact 78494126). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 guess_g_MenuPanelCursors[];
extern u8 D_80115149[];
extern u8 guess_g_MenuPanelSizes[];
s16 func_8014168C(s16 a0) {
    s32 i = a0 * 2;
    return guess_g_MenuPanelCursors[i] + D_80115149[i] * guess_g_MenuPanelSizes[i];
}
