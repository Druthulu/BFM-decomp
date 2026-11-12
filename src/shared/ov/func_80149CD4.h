/* guess_IsR1Held — shared body (overlay slot 0x80128158, h_exact 2d82e9ac). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_IsR1Held: returns 1 while R1 is held (bit 0x8 of the held pad word +0xAA), 0 when +0x44 & 0x404 or the s16 +0x1C8 blocks it
 * Confidence medium, xref chain: +0x44 & 0x404 -> 0; +0x1C8 != 0 -> 0; else (+0xAA & 8) != 0; +0xAA is guess_GetPadHeld's word; 0x8 is R1 in the PlayStation button word
 * Names ledger: config/names.tsv guess_IsR1Held */
s32 guess_IsR1Held(s32 a0) {
    s32 v0;
    if (*(s32*)(a0 + 0x44) & 0x404) {
        v0 = 0;
    } else if (*(s16*)(a0 + 0x1C8) != 0) {
        v0 = 0;
    } else {
        v0 = *(u16*)(a0 + 0xAA) & 8;
        v0 = v0 != 0;
    }
    return v0;
}
