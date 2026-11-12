/* func_80181B4C — shared body (overlay slot 0x80128158, h_exact 86367a03). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 guess_g_MainCameraPitchTarget; // Names ledger: config/names.tsv guess_g_MainCameraPitchTarget
extern s16 guess_g_MainCameraYawTarget; // Names ledger: config/names.tsv guess_g_MainCameraYawTarget
extern s16 guess_g_MainCameraRefOffsetTargetY; // Names ledger: config/names.tsv guess_g_MainCameraRefOffsetTargetY
extern u16 guess_g_PlayerPosX; // Names ledger: config/names.tsv guess_g_PlayerPosX
extern s16 guess_g_MainCameraRollTarget; // Names ledger: config/names.tsv guess_g_MainCameraRollTarget
extern s16 guess_g_MainCameraRefOffsetTargetX; // Names ledger: config/names.tsv guess_g_MainCameraRefOffsetTargetX
extern s16 guess_g_MainCameraRefOffsetTargetZ; // Names ledger: config/names.tsv guess_g_MainCameraRefOffsetTargetZ
extern s32 D_801269E4;
extern u8 D_801269E8;
extern s16 D_801274E8;
extern u8 guess_g_MainCamera[]; // Names ledger: config/names.tsv guess_g_MainCamera
extern void func_80181D2C(u8*);
extern void guess_SetMainCameraHandler(s32 a, s32 b);
extern void func_8012A094(s32);
extern void guess_UpdateCamera(void);
void func_80181B4C(void)
{
    u16 v1;
    D_80126954 = 0x12C;
    D_8012695C = 0x190;
    guess_g_MainCameraPitchTarget = 0x80;
    guess_g_MainCameraYawTarget = 0x800;
    guess_g_MainCameraRefOffsetTargetY = -0x80;
    v1 = guess_g_PlayerPosX;
    guess_g_MainCameraRollTarget = 0;
    guess_g_MainCameraRefOffsetTargetX = 0;
    guess_g_MainCameraRefOffsetTargetZ = -0xC8;
    D_801269E4 = 0;
    D_801269E8 = 0;
    D_801274E8 = v1;
    guess_SetMainCameraHandler((s32)func_80181D2C, 0x2);
    guess_g_MainCameraPitchTarget = 0x120;
    func_8012A094(guess_g_MainCamera);
    guess_UpdateCamera();
}
