extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8002D4C8(s32 a0, s32 a1);

extern u8 D_801AF968[];
extern u8 D_801AF940[];
extern u8 D_801AF948[];
extern u8 D_801BB960[];
extern u16 D_80126B96[];
extern s16 D_80126B98[];

void func_80184CCC(s32 a0) {
    s32 result;
    u16 val70;

    if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        *(s16 *)(a0 + 0x2) = 0xC;
        func_8012B1B4(a0, (s32)D_801AF968);
        *(s16 *)(a0 + 0x16) = -0x8;
        func_8012A828(a0, (s32)D_801BB960);
        *(s16 *)(a0 + 0x98) = 0x1;
    }

    if (*(s32 *)(a0 + 0x94) == 0xF) {
        result = func_8012D5E4(a0, (s32)D_801AF940, (s32)D_801AF948, 0x14);
        if (result == 1) {
            func_8002D4C8(0xCB2, 0);

            val70 = *(u16 *)(a0 + 0x70);
            if (((u32)val70 - 2) < 2) {
                D_80126B98[0] = 0x18;
                D_80126B96[0] = D_80126B96[0] | 0x2000;
            }
        }
    }
}
