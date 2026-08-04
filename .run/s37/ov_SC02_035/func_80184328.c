typedef struct { s32 w[4]; } Blk16_80184328;

extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32, void *);
extern s32 D_800A5E90;
extern Blk16_80184328 D_800A5E88;
extern Blk16_80184328 D_801BBE34;

void func_80184328(s32 a0) {
    Blk16_80184328 *s1 = &D_800A5E88;

    *s1 = D_801BBE34;
    D_800A5E90 = func_8004787C(*(s16 *)(a0 + 0xFE)) * 20 / 4096 - 10;
    *(s16 *)(a0 + 0xFE) = (*(u16 *)(a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(0, s1);
}
