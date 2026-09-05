extern s32 D_800CDD2C;
extern s32 D_800CDD34;

void func_800CD674(s32, s32, s32);
void func_800116A0(void);

void func_800CD4C8(void) {
    func_800CD674(0, D_800CDD2C, D_800CDD34);

    D_800CDD34 -= 8;
    if (D_800CDD34 <= 0) {
        func_800116A0();
    }
}
