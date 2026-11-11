/* func_801748EC — shared body (overlay slot 0x80128158, h_exact 79386ba5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012A018(s32 a, s32 b);
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
void func_801748EC(void) {
    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x384;
    guess_g_MainCameraPitchTarget = 0x1C7;
    guess_g_MainCameraYawTarget = 0x600;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetY = 0;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    func_8012A018((s32)func_8017496C, 0);
}
