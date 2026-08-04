typedef struct { s32 w[4]; } Blk16_8018B29C;

extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32, void *);
extern Blk16_8018B29C D_800A5E88;
extern Blk16_8018B29C D_801D03A8;
extern s32 D_800A5E90;

void func_8018B354(s32 a0) {
    Blk16_8018B29C *s1 = &D_800A5E88;

    *s1 = D_801D03A8;
    D_800A5E90 = func_8004787C(*(s16 *)(a0 + 0xFE)) / 512 + 8;
    *(s16 *)(a0 + 0xFE) = (*(u16 *)(a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(0, s1);
}
