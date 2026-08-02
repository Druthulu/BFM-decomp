extern s32 func_80153BD8(s32);
extern s32 func_80153BF0(s32 a0);
extern void func_8012A828(s32, s32);
extern s32 func_8012DEB8(s32, s32, s32);
extern void func_8002D4C8(s32, s32);
extern void func_80153C74(s16, s16);

extern u8 D_801BBB78;
extern u8 D_801AF930[];
extern u8 D_801AF938[];

void func_80184A94(s32 s0) {
    s32 v0;

    v0 = func_80153BD8(s0);
    if (!v0) {
        func_80153BF0(s0);
        func_8012A828(s0, (s32)&D_801BBB78);
        *(s16 *)(s0 + 0x2) = 0x13;
        *(s16 *)(s0 + 0x34) = 0x3;
        *(s16 *)(s0 + 0xFC) = 0;
        *(s32 *)(s0 + 0x1C) = 0x1E;
    }

    if ((*(s32 *)(s0 + 0x94) == 0x0A) || (*(s32 *)(s0 + 0x94) == 0x1A)) {
        v0 = func_8012DEB8(s0, (s32)&D_801AF930, (s32)&D_801AF938);
        if (v0 == 1) {
            func_8002D4C8(0xCB2, 0);
            v0 = *(u16 *)(s0 + 0x70) - 2;
            if ((u32)v0 < 2) {
                func_80153C74(3, 0x18);
            } else {
                func_80153C74(1, 0x14);
            }
        }
    }
}
