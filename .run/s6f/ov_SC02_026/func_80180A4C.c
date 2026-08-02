extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_80186448[];
extern s32 D_801A9DC0[];
extern s32 D_801A9DA0[];

void func_80180A4C(s32 a0) {
    s32 t;

    if (func_8012C354(a0, (s32)D_801A9DC0) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        t = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)D_801A9DA0;
        *(s32 *)(a0 + 0xC4) = t | 0x2;

        func_8012A828(a0, (s32)D_80186448);

        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(s16 *)(a0 + 0xFE) = 1;

        func_8012C658(0x164, 0x555, a0);
        func_8012C658(0x164, 0xAAA, a0);
        func_8012C658(0x164, 0x1000, a0);
    }
}
