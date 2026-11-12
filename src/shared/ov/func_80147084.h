/* guess_ClearHideRequest221 — shared body (overlay slot 0x80128158, h_exact 2cd92c4b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* guess_ClearHideRequest221: clears hide request byte +0x221 of a0; while any of +0x220/+0x221/+0x222 is set the player update keeps the model from drawing
 * Confidence medium, xref chain: +0x221 = 0; func_801470C0 sets model +0x4 bit 31 (not drawn) while +0x220|+0x221|+0x222 != 0, else clears it; func_8014708C sets the byte
 * Names ledger: config/names.tsv guess_ClearHideRequest221 */
void guess_ClearHideRequest221(s32 *a0) {
    *(s8*)((s32)a0 + 0x221) = 0;
}
