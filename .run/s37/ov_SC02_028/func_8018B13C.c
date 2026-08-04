typedef struct { s32 w[4]; } Blk16_8018B13C;

extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32, void *);
extern Blk16_8018B13C D_800A5EA8;
extern Blk16_8018B13C D_801D0320;
extern s32 D_800A5EB0;

void func_8018B13C(s32 a0) {
    Blk16_8018B13C *s1 = &D_800A5EA8;

    *s1 = D_801D0320;
    D_800A5EB0 = func_8004787C(*(s16 *)(a0 + 0xFE)) * 10 / 4096 - 5;
    *(s16 *)(a0 + 0xFE) = (*(u16 *)(a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(2, s1);
}
