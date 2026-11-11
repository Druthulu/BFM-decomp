/* func_8012A1BC — shared body (overlay slot 0x80128158, h_exact 497f8cc9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8012A1BC(void) {
    extern s16 D_80120218;
    extern s16 D_80120222;
    extern s16 D_80120224;
    extern s16 D_80120226;
    extern s16 D_80120228;
    extern s16 D_8012022A;
    extern s16 D_8012029A;
    extern s32 D_80120200, D_80120204, D_80120208, D_8012020C;
    extern s16 D_80120210;
    extern s16 D_80120220;
    extern s32 D_80120294;
    extern s16 D_80120298;
    extern s32 D_80126950, D_80126954, D_80126958, D_8012695C;
    extern Blk8 D_80126960, guess_g_MainCameraPitchTarget;
    extern u16 D_80126970, D_80126972, D_80126974, guess_g_MainCameraRefOffsetTargetX, guess_g_MainCameraRefOffsetTargetY, guess_g_MainCameraRefOffsetTargetZ;
    extern s32 D_801269E4;
    extern u16 D_801269E8, D_801269EA;
    s32 r2, r3, r4, r5;
    u16 r6, r7;
    s32 r8;
    u16 r9, r10;
    s32 s2, s3, s4, s5;
    r2 = D_80120200; r3 = D_80120204; r4 = D_80120208; r5 = D_8012020C;
    r6 = (*(u16 *)&D_80120228); r7 = (*(u16 *)&D_8012022A); r8 = D_80120294; r9 = (*(u16 *)&D_80120298); r10 = (*(u16 *)&D_8012029A);
    do { D_80126950 = r2; D_80126954 = r3; D_80126958 = r4; D_8012695C = r5; } while (0);  // !FAKE: do-while
    do { D_80126960 = (*(Blk8 *)&D_80120210); } while (0);  // !FAKE: do-while
    s2 = (*(u16 *)&D_80120220); s3 = (*(u16 *)&D_80120222); s4 = (*(u16 *)&D_80120224); s5 = (*(u16 *)&D_80120226);
    do { guess_g_MainCameraPitchTarget = (*(Blk8 *)&D_80120218); } while (0);  // !FAKE: do-while
    guess_g_MainCameraRefOffsetTargetY = r6; guess_g_MainCameraRefOffsetTargetZ = r7; D_801269E4 = r8; D_801269E8 = r9; D_801269EA = r10;
    D_80126970 = s2; D_80126972 = s3; D_80126974 = s4; guess_g_MainCameraRefOffsetTargetX = s5;
}
