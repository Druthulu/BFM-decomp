extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80153C74(s16 a0, s16 a1);

extern s32 aD801BC890 __asm__("D_801BC890");
extern s32 aD801AF930 __asm__("D_801AF930");
extern s32 aD801AF938 __asm__("D_801AF938");

void func_80184C00(s32 a0) {
    u16 val;

    if (func_80153BD8(a0) == 0) {
        ((void (*)(s32))func_80153BF0)(a0);
        func_8012A828(a0, (s32)&aD801BC890);
        *(s16 *)(a0 + 0x34) = 7;
        *(s16 *)(a0 + 0x2) = 0x13;
        *(s32 *)(a0 + 0x1C) = 0x1E;
    }

    if (*(s32 *)(a0 + 0x94) == 0x17) {
        if (func_8012DEB8(a0, (s32)&aD801AF930, (s32)&aD801AF938) == 1) {
            func_8002D4C8(0xCB2, 0);
            val = *(u16 *)(a0 + 0x70);
            if ((u16)(val - 2) < 2u) {
                func_80153C74(3, 0x18);
            } else {
                func_80153C74(1, 0x14);
            }
        }
    }
}
