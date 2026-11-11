/* func_80181820 — shared body (overlay slot 0x80128158, h_exact 07c2791e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 guess_g_MainCameraPitchTarget;
extern s16 guess_g_MainCameraYawTarget;
extern s16 guess_g_MainCameraRefOffsetTargetX;
extern s16 guess_g_MainCameraRollTarget;
extern s16 guess_g_MainCameraRefOffsetTargetY;
extern s16 guess_g_MainCameraRefOffsetTargetZ;
extern u8 guess_g_MainCamera[];
extern void func_8012A018(s32 a, s32 b);
extern void func_80181D2C(u8*);
extern void func_8012A094(s32 a0);
void func_80181820(void) {
    u8 *ptr;
    D_80126954 = 0x12C;
    D_8012695C = 0x3E8;
    guess_g_MainCameraPitchTarget = 0x80;
    guess_g_MainCameraYawTarget = 0x200;
    guess_g_MainCameraRefOffsetTargetX = 0x50;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetY = -0xC8;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    func_8012A018((s32)func_80181D2C, 0);
    ptr = guess_g_MainCamera;
    ((void (*)(void *))func_80181D2C)(ptr);
    func_8012A094((s32)ptr);
}
