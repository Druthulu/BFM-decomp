extern s32 D_800CDD30;
extern s32 D_800CDD34;
extern void func_800CD92C(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD558(void) {
    func_800CD92C(-0x400, 0, D_800CDD34);
    D_800CDD30 = -0x340;
    D_800CDD34 += 8;
    if (D_800CDD34 >= 0x80) {
        func_800116A0();
    }
}
