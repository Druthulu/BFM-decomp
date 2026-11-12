/* guess_GetPadPressed — shared body (overlay slot 0x80128158, h_exact fa593ea1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_GetPadPressed: returns the object's newly-pressed pad buttons (u16 at +0xAC)
 * Confidence medium, xref chain: returns +0xAC, which func_80148648 fills from the pad record's +0x3A word (newly pressed, per guess_g_MenuPadPressed)
 * Names ledger: config/names.tsv guess_GetPadPressed */
u16 guess_GetPadPressed(s32 *a0) {
    return *(u16*)((s32)a0 + 0xAC);
}
