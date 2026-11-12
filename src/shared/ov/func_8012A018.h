/* guess_SetMainCameraHandler — shared body (overlay slot 0x80128158, h_exact 6d717730). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012A048(void *a0, s32 a1, u8 a2);
/* guess_SetMainCameraHandler: installs handler a0 with argument a1 in the main camera and restarts its follow point at the player position
 * Confidence medium, xref chain: func_8012A048(guess_g_MainCamera, a0, a1): stores +0x0 = a0, +0x4 = a1, clears +0x9C/+0xA0/+0xA2, copies the player position
 * Names ledger: config/names.tsv guess_SetMainCameraHandler */
void guess_SetMainCameraHandler(s32 a0, s32 a1)
{
    extern u8 guess_g_MainCamera[];
    func_8012A048(guess_g_MainCamera, a0, a1);
}
