/* func_80162438 — shared body (overlay slot 0x80128158, h_exact e113e304). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80162438(s32 _unused0) {
    extern s32 func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_80181DE4[];
    extern s32 D_80181DFC;
    extern u8 D_8018E8CC[];
    extern u8 D_8018E8F4[];
    extern u8 D_8018E910[];
    extern int D_8018E8C0[];
    extern u16 guess_g_TargetTimeLabel1;
    extern u16 guess_g_TargetTimeLabel2;
    extern u16 guess_g_TargetTimeDigits;
    extern u16 guess_g_ScreenWidth;
    extern u16 guess_g_ScreenHeight;
    extern s16 guess_g_TargetTimeLabel1X;
    extern s16 guess_g_TargetTimeLabel1Y;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 guess_g_TargetTimeLabel2X;
    extern s16 guess_g_TargetTimeLabel2Y;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 guess_g_TargetTimeDigitsX;
    extern s16 guess_g_TargetTimeDigitsY;
    extern s16 D_800B5C74;

    u32 uVar2;
    u8 *base;
    u8 *item;

    base = &(*(u8 *)&guess_g_RenderWork);
    uVar2 = func_800291DC(0x12);
    if ((uVar2 & 0x8000) != 0) {
        if (guess_g_TargetTimeLabel1 == 0) {
            D_8018E8C0[0] = (s32)(base + 0x65A8);
            item = base + 0x65A8;
            func_80024054(D_80181DE4, D_8018E8CC);
            func_8001CE28(item, D_8018E8CC);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            guess_g_TargetTimeLabel1X = -guess_g_ScreenWidth / 2 + 0xD0;
            guess_g_TargetTimeLabel1Y = -guess_g_ScreenHeight / 2 + 0x28;
        }
        if (guess_g_TargetTimeLabel2 == 0) {
            D_8018E8C0[1] = (s32)(base + 0x65E0);
            item = base + 0x65E0;
            func_80024054(((u8 *)&D_80181DFC), D_8018E8F4);
            func_8001CE28(item, D_8018E8F4);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            guess_g_TargetTimeLabel2X = -guess_g_ScreenWidth / 2 + 0xD0;
            guess_g_TargetTimeLabel2Y = -guess_g_ScreenHeight / 2 + 0x30;
        }
        if (guess_g_TargetTimeDigits == 0) {
            D_8018E8C0[2] = (s32)(base + 0x6618);
            item = base + 0x6618;
            func_800242D0((s16)func_801626B8(), D_8018E910, 0x84);
            func_8001CE68(item, D_8018E910);
            D_800B5C74 = 1;
            guess_g_TargetTimeDigitsX = -guess_g_ScreenWidth / 2 + 0xD0;
            guess_g_TargetTimeDigitsY = -guess_g_ScreenHeight / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_8018E910, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&guess_g_ClockMinute)) {
            func_80162760();
        }
    }
}
