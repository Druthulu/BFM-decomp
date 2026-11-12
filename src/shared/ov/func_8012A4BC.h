/* guess_BlendToPresetCamera — shared body (overlay slot 0x80128158, h_exact bb9bde6e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_g_ActiveCamera;
extern BigCopy D_80126DB8;
extern BigCopy D_80114EE8;
extern u8 D_80127504;
/* guess_BlendToPresetCamera: saves the active camera into D_80126DB8, makes the preset D_80114EE8 active and sets the 0x30-frame blend counter D_80127504
 * Confidence medium, xref chain: D_80126DB8 = *guess_g_ActiveCamera; *guess_g_ActiveCamera = D_80114EE8; D_80127504 = 0x30; guess_UpdateCamera eases D_80126DB8 while it counts
 * Names ledger: config/names.tsv guess_BlendToPresetCamera */
void guess_BlendToPresetCamera(void) {
    D_80126DB8 = *(BigCopy *)guess_g_ActiveCamera;
    *(BigCopy *)guess_g_ActiveCamera = D_80114EE8;
    D_80127504 = 0x30;
}
