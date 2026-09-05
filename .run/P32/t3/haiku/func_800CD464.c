extern s32 D_800CDD2C;
extern s32 D_800CDD34;
extern void func_800CD674(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD464(void) {
    func_800CD674(0, D_800CDD2C, D_800CDD34);
    D_800CDD2C--;
    if (D_800CDD2C >= -0x10F) {
        return;
    }
    D_800CDD2C = -0x110;
    func_800116A0();
}
