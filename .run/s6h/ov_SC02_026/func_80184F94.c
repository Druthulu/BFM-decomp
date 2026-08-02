void func_80184F94(s32 a0) {
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32 a0, s32 a1);

    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 D_80127078;
    extern u8 D_801AF930[];
    extern u8 D_801AF938[];
    extern u8 D_801BC760[];
    extern char D_801BD010[];

    s32 result;

    result = func_8012DEB8(a0, (s32)&D_801AF930, (s32)&D_801AF938);

    if (result == 1) {
        D_80126B96 = 0x400F;
        D_80126B98 = 0;
        D_80127078 = a0;
        *(u16 *)(a0 + 0x2) = 0x12;
        func_8012A828(a0, (s32)&D_801BC760);
    } else {
        func_8012A828(a0, (s32)&D_801BD010);
        *(u16 *)(a0 + 0x2) = 0x6;
    }
}
