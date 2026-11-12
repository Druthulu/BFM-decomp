/* guess_CloseTextWindow0 — shared body (overlay slot 0x80128158, h_exact 0972af43). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013A8B0(s32 *a0);
extern u16 D_80126A08;
extern s16 D_801269F4;
extern s32 guess_g_TextBoxes; // Names ledger: config/names.tsv guess_g_TextBoxes
extern s32 *D_80126A30;
/* guess_CloseTextWindow0: frees text window record 0 of guess_g_TextBoxes as guess_CloseTextWindow frees any record
 * Confidence medium, xref chain: D_801269F4 (+4) = 0, guess_g_TextBoxes (+0) = 0; D_80126A08 (+0x18) and D_80126A30 (+0x40) -> func_8013A8B0; menu calls it before reopening
 * Names ledger: config/names.tsv guess_CloseTextWindow0 */
void guess_CloseTextWindow0(void) {
    u16 v = D_80126A08;
    D_801269F4 = 0;
    guess_g_TextBoxes = 0;
    if (v != 0) {
        if (D_80126A30 != 0) {
            func_8013A8B0(D_80126A30);
        }
    }
}
