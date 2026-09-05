extern s32 D_800CDD30;
extern s32 D_800CDD34;
extern void func_800CD92C(s32 a0, s32 a1, s32 a2);
extern void func_800116A0(void);

void func_800CD5B8(void) {
    func_800CD92C(D_800CDD30, 0, D_800CDD34);
    D_800CDD30++;
    if (D_800CDD30 >= 0x141) {
        func_800116A0();
    }
}
