/* guess_SetMainCameraDefaults — shared body (overlay slot 0x80128158, h_exact 79386ba5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetMainCameraHandler(s32 a, s32 b);
extern s32 func_8017496C(void *a0);
extern s32 D_80126954;
extern s32 D_80126950;
extern s32 D_8012695C;
extern s16 guess_g_MainCameraPitchTarget;
extern s16 guess_g_MainCameraYawTarget;
extern s16 guess_g_MainCameraRollTarget;
extern s16 guess_g_MainCameraRefOffsetTargetX;
extern s16 guess_g_MainCameraRefOffsetTargetY;
extern s16 guess_g_MainCameraRefOffsetTargetZ;
/* guess_SetMainCameraDefaults: resets the main camera's parameters and angle/offset targets to scene defaults and installs camera handler func_8017496C
 * Confidence medium, xref chain: writes 0x1F4/0x1F4/0x384 and the pitch/yaw/roll targets 0x1C7/0x600/0 and zero offset targets, then guess_SetMainCameraHandler(func_8017496C, 0)
 * Names ledger: config/names.tsv guess_SetMainCameraDefaults */
void guess_SetMainCameraDefaults(void) {
    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x384;
    guess_g_MainCameraPitchTarget = 0x1C7;
    guess_g_MainCameraYawTarget = 0x600;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetY = 0;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    guess_SetMainCameraHandler((s32)func_8017496C, 0);
}
