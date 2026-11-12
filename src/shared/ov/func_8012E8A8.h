/* guess_HideObjectModel — shared body (overlay slot 0x80128158, h_exact e562f27d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_HideObjectModel: sets bit 31 of the word +0x4 of a0's +0x20 model, so the model is not drawn
 * Confidence medium, xref chain: +0x20 model +0x4 |= 0x80000000; guess_ShowObjectModel clears it; func_8001FB8C skips negative
 * Names ledger: config/names.tsv guess_HideObjectModel */
void guess_HideObjectModel(u8 *a0) {
    s32 *p = *(s32 **)(a0 + 0x20);
    p[1] = p[1] | 0x80000000;
}
