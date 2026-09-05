extern s32 func_80029504(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern void func_80029124(s32 a0, s32 a1);
extern s32 func_80029178(s32 a0);
extern s32 func_8018766C(s32 a0, s32 a1);
extern void func_800D0F4C(s32 a0);

extern s16 D_801F1480;
extern s16 D_801F1482;
extern s32 D_801F10C0;
extern s32 D_801F10E0;
extern s32 D_801F10F8;
extern s32 D_801F1118;
extern s32 D_801F1138;
extern s32 D_801F1158;

void func_801EF558(void *param_1) {
    s16 step;
    s32 v0;

    step = 6;
    *(s16 *)((s32)param_1 + 0x2) = step;
    D_801F1480 = 0;
    D_801F1482 = 0;
    v0 = func_80029504();
    if (v0 < 0x28) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F10C0);
        func_80029514(0x28);
        func_80029124(0xE3, 1);
        *(s16 *)((s32)param_1 + 0x34) = 0;
    } else if (v0 < 0x32) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F10E0);
        *(s16 *)((s32)param_1 + 0x34) = 1;
    } else if ((u8)func_80029178(0xE4) != 0) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F10F8);
        *(s16 *)((s32)param_1 + 0x34) = 5;
    } else if (v0 < 0x3C) {
        func_8002D4C8(0x12, 0);
        func_80178CBC((s32)param_1, (s32)&D_801F1118);
        *(s16 *)((s32)param_1 + 0x34) = 2;
    } else if (v0 < 0x46) {
        if (func_8018766C(0, 5) != 0) {
            func_8002D4C8(0x12, 0);
            func_80178CBC((s32)param_1, (s32)&D_801F1158);
            func_800D0F4C(0x4D);
            *(s16 *)((s32)param_1 + 0x34) = step;
        } else {
            func_8002D4C8(0x12, 0);
            func_80178CBC((s32)param_1, (s32)&D_801F1138);
            *(s16 *)((s32)param_1 + 0x34) = 2;
        }
    }
}
