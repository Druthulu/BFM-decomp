/* func_8017B614 — shared body (overlay slot 0x80128158, h_exact 2d7795bc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern void guess_RotTransSVWithObjMatrix(s32 a0, s32 a1, s32 a2);
    extern void guess_UpdateCamera(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80182BB8[];
    extern s16 D_8018F98C;
    extern s16 D_8018F98E;
    extern s16 D_8018F990;
    extern s16 D_8018F984;
    extern s16 D_8018F986;
    extern s16 D_8018F988;
    extern u8 D_8012694C[];
    extern s32 guess_g_MainCameraRefPointZ;
    extern s32 guess_g_MainCameraViewPointX;
    extern s32 guess_g_MainCameraViewPointY;
    extern s32 guess_g_MainCameraViewPointZ;

    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_80182BB8[((u32)param_2) * 0x10];
        a2addr = (s32)&D_80182BB8[((u32)param_2) * 0x10 + 8];
        guess_RotTransSVWithObjMatrix(param_1, (s32)src, (s32)&buf[0]);
        guess_RotTransSVWithObjMatrix(param_1, a2addr, (s32)&buf[8]);
    }
    *(Blk8_8017B614 *)&D_8018F98C = *(Blk8_8017B614 *)&buf[0];
    *(Blk8_8017B614 *)&D_8018F984 = *(Blk8_8017B614 *)&buf[8];
    func_8012A018((s32)func_8017BE60, 0);
    D_8012694C[0] = 0;
    D_8018FAB0 = 1;
    D_8018F914 = 0x1E;
    guess_g_MainCameraRefPointX = ((SV4_8017B368 *)&D_8018F98C)->v[0];
    guess_g_MainCameraRefPointY = D_8018F98E;
    guess_g_MainCameraRefPointZ = D_8018F990;
    guess_g_MainCameraViewPointX = ((SV4_8017B368 *)&D_8018F984)->v[0];
    guess_g_MainCameraViewPointY = D_8018F986;
    guess_g_MainCameraViewPointZ = D_8018F988;
    guess_UpdateCamera();
}
