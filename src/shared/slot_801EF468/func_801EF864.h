/* func_801EF864 — shared body (module slot 0x801EF468, h_exact 9d4f4704). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801EF928(void *a0);
void func_801EF864(void) {
    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 guess_g_MainCameraPitchTarget;
    extern s16 guess_g_MainCameraYawTarget;
    extern s16 guess_g_MainCameraRollTarget;
    extern s16 guess_g_MainCameraRefOffsetTargetX;
    extern s16 guess_g_MainCameraRefOffsetTargetY;
    extern s16 guess_g_MainCameraRefOffsetTargetZ;
    extern u8 guess_g_MainCamera[];
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;
    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    guess_g_MainCameraPitchTarget = 0xFB1;
    guess_g_MainCameraYawTarget = 0x7C7;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetY = -0x36;
    guess_g_MainCameraRefOffsetTargetZ = 0;
    func_8012A018((s32)func_801EF928, 0);
    func_801EF928(guess_g_MainCamera);
    func_8012A094((s32)guess_g_MainCamera);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}
