struct B16_801841C8 { s32 w[4]; };

extern struct B16_801841C8 D_800A5EA8;
extern struct B16_801841C8 D_801BBDE4;
extern s32 D_800A5EB0;
extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32 a0, void *a1);

void func_801841C8(void *a0) {
    D_800A5EA8 = D_801BBDE4;
    D_800A5EB0 = func_8004787C(*(s16 *)((s32)a0 + 0xFE)) * 10 / 4096 - 5;
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(2, &D_800A5EA8);
}
