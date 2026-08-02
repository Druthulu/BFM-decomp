extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern u8 D_801BBB78[];

void func_80184B6C(void *a0) {
    s16 val70;
    u16 val72;

    if (*(s32 *)(a0 + 0x94) == 0x17) {
        val70 = *(s16 *)(a0 + 0x70);
        if (val70 == 0x2) {
            func_8012C588(0x1A7, (s32)a0);
        } else {
            func_8002D4C8(0xCB3, 0);
            func_8012C588(0x19F, (s32)a0);
        }
    }

    val72 = *(u16 *)(a0 + 0x72);
    if ((val72 & 0x4000) != 0) {
        func_8012A828((s32)a0, (s32)D_801BBB78);
        *(s16 *)(a0 + 0x2) = 0x3;
        *(s16 *)(a0 + 0xFC) = 0;
        *(s16 *)(a0 + 0xFE) = 0;
    }
}
