/* func_8012A62C — shared body (overlay slot 0x80128158, h_exact 9f719075). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012A62C(s32 a0) {
    extern s32 guess_g_ActiveCamera; // Names ledger: config/names.tsv guess_g_ActiveCamera
    extern BigCopy D_80126DB8;
    extern u8 D_80127504;
    D_80126DB8 = *(BigCopy *)guess_g_ActiveCamera;
    D_80127504 = a0;
}
