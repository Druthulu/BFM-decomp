/* guess_GetPadHeld — shared body (overlay slot 0x80128158, h_exact 39a330fb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_GetPadHeld: returns the object's held pad buttons (u16 at +0xAA)
 * Confidence medium, xref chain: returns +0xAA, which func_80148648 fills from the pad record's +0x32 word (held, per guess_g_MenuPadHeld)
 * Names ledger: config/names.tsv guess_GetPadHeld */
u16 guess_GetPadHeld(s32 *a0) {
    return *(u16*)((s32)a0 + 0xAA);
}
