/* guess_ShowObjectModel — shared body (overlay slot 0x80128158, h_exact 8d47a3a2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ShowObjectModel: clears bit 31 of the attribute word +0x4 of object a0's model (+0x20), which the model draw loop skips while set
 * Confidence medium, xref chain: model +0x4 &= 0x7FFFFFFF; func_8001FB8C returns before drawing when +0x4 < 0; guess_HideObjectModel sets the bit, func_8012E8C4 toggles it
 * Names ledger: config/names.tsv guess_ShowObjectModel */
void guess_ShowObjectModel(u8 *a0) {
    s32 *p = *(s32 **)(a0 + 0x20);
    p[1] = p[1] & 0x7FFFFFFF;
}
