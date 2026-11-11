/* func_8017EDB8 — shared body (overlay slot 0x80128158, h_exact 3df94c9c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017EDB8(void) {
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 guess_g_MainCameraPitchTarget;
    extern s16 guess_g_MainCameraYawTarget;
    extern s16 guess_g_MainCameraRollTarget;
    extern s16 guess_g_MainCameraRefOffsetTargetX;
    extern s16 guess_g_MainCameraRefOffsetTargetY;
    extern s16 guess_g_MainCameraRefOffsetTargetZ;
    extern u8 guess_g_MainCamera[];
    extern void func_8017EF10(void *);
    extern void func_8012A018(s32, s32);
    extern void func_8012A094(s32);

    D_80126954 = 0x1F4;
    D_8012695C = 0x384;
    guess_g_MainCameraPitchTarget = 0x238;
    guess_g_MainCameraYawTarget = 0x600;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetY = 0;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    func_8012A094((s32)guess_g_MainCamera);
    func_8012A018((s32)func_8017EF10, 0);
    func_8017EF10((void *)guess_g_MainCamera);
    func_8012A018((s32)func_8017EF10, 1);
}
