/* func_8017D468 — shared body (overlay slot 0x80128158, h_exact f3b49c43). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetMainCameraHandler(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D500(void *a0);
void func_8017D468(void) {
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 guess_g_MainCameraPitchTarget;
    extern s16 guess_g_MainCameraYawTarget;
    extern s16 guess_g_MainCameraRollTarget;
    extern s16 guess_g_MainCameraRefOffsetTargetX;
    extern s16 guess_g_MainCameraRefOffsetTargetY;
    extern s16 guess_g_MainCameraRefOffsetTargetZ;
    extern u8 guess_g_MainCamera[];
    D_80126954 = 0x12C;
    D_8012695C = 0x384;
    guess_g_MainCameraPitchTarget = 0x155;
    guess_g_MainCameraYawTarget = 0x800;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetY = 0;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    guess_SetMainCameraHandler((s32)func_8017D500, 0);
    func_8012A094((s32)guess_g_MainCamera);
    func_8017D500(guess_g_MainCamera);
}
