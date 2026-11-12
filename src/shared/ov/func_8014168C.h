/* guess_GetMenuPanelCursorIndex — shared body (overlay slot 0x80128158, h_exact 78494126). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 guess_g_MenuPanelCursors[];
extern u8 D_80115149[];
extern u8 guess_g_MenuPanelSizes[];
/* guess_GetMenuPanelCursorIndex: returns the cursor of menu panel a0 as one index: row + column * rows
 * Confidence medium, xref chain: guess_g_MenuPanelCursors[a0*2] + D_80115149[a0*2] (its column byte) * guess_g_MenuPanelSizes[a0*2] (rows)
 * Names ledger: config/names.tsv guess_GetMenuPanelCursorIndex */
s16 guess_GetMenuPanelCursorIndex(s16 a0) {
    s32 i = a0 * 2;
    return guess_g_MenuPanelCursors[i] + D_80115149[i] * guess_g_MenuPanelSizes[i];
}
