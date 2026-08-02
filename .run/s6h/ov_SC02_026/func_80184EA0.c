void func_80184EA0(s32 entity) {
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32 a0, s32 a1);

    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 D_80127078;
    extern u8 D_801AF930[];
    extern u8 D_801AF938[];
    extern u8 D_801BC420[];
    extern u8 D_801BCBA0[];

    s32 result;

    result = func_8012DEB8(entity, (s32)&D_801AF930, (s32)&D_801AF938);

    if (result == 1) {
        D_80126B96 = 0x400F;
        D_80126B98 = 0;
        D_80127078 = entity;
        *(u16 *)(entity + 0x2) = 0x10;
        func_8012A828(entity, (s32)&D_801BC420);
    } else {
        func_8012A828(entity, (s32)&D_801BCBA0);
        *(u16 *)(entity + 0x2) = 3;
        *(u16 *)(entity + 0xFC) = 0;
        *(u16 *)(entity + 0xFE) = 1;
    }
}
