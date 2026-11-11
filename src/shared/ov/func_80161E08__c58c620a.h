/* func_80161E08 — shared body (overlay slot 0x80128158, h_exact c58c620a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80161E08(s32 param_1) {
    extern s32 func_80024054(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern void func_800242D0(s32 a0, void *a1, s32 a2);
    extern void func_8001CE68(void *a0, void *a1);
    extern int func_801620C4(void);
    extern void func_801622C4(void);
    extern u16 guess_g_ScreenWidth;
    extern u16 guess_g_ScreenHeight;
    extern s16 guess_g_ClockMinute;
    extern u16 guess_g_TargetTimeLabel1;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 guess_g_TargetTimeLabel1X;
    extern s16 guess_g_TargetTimeLabel1Y;
    extern u16 guess_g_TargetTimeLabel2;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 guess_g_TargetTimeLabel2X;
    extern s16 guess_g_TargetTimeLabel2Y;
    extern u16 guess_g_TargetTimeDigits;
    extern s16 D_800B5C74;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern u8 * D_8018E868[];
    extern u8 D_80181D80[];
    extern u8 D_80181DA0[];
    extern u8 D_8018E874[];
    extern u8 D_8018E89C[];
    extern u8 D_8018E8B4[];

    u8 *base = &(*(u8 *)&guess_g_RenderWork);
    u8 *p;
    s32 a2;

    if (*((u16 *)param_1) != 0x1A &&
        currentLocationId != 0x3012 &&
        currentLocationId != 0x3054 &&
        currentLocationId != 0x3079 &&
        currentLocationId != 0x3096 &&
        ((a2 = func_800291DC(8)) & 0x8000) != 0) {

        if (guess_g_TargetTimeLabel1 == 0) {
            p = D_8018E868[0] = base + 0x65A8;
            func_80024054(&D_80181D80, &D_8018E874);
            func_8001CE28(p, &D_8018E874);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            guess_g_TargetTimeLabel1X = -(s32)(u16)guess_g_ScreenWidth / 2 + 0xD0;
            guess_g_TargetTimeLabel1Y = -(s32)(u16)guess_g_ScreenHeight / 2 + 0x28;
        }

        if (guess_g_TargetTimeLabel2 == 0) {
            p = D_8018E868[1] = base + 0x65E0;
            func_80024054(&D_80181DA0, &D_8018E89C);
            func_8001CE28(p, &D_8018E89C);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            guess_g_TargetTimeLabel2X = -(s32)(u16)guess_g_ScreenWidth / 2 + 0xD0;
            guess_g_TargetTimeLabel2Y = -(s32)(u16)guess_g_ScreenHeight / 2 + 0x30;
        }

        if (guess_g_TargetTimeDigits == 0) {
            p = D_8018E868[2] = base + 0x6618;
            func_800242D0((s16)func_801620C4(), &D_8018E8B4, 0x84);
            func_8001CE68(p, &D_8018E8B4);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)guess_g_ScreenWidth / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)guess_g_ScreenHeight / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_8018E8B4, 0x84);
        if ((a2 & 0x7FFF) == (s32)guess_g_ClockMinute) {
            func_801622C4();
        }
    }
}
