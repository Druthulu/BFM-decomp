extern s32 func_800167F0(s32 a0);
extern void func_800CF6D0(s32 a0, u32 a1);
extern s32 D_800D136C;
extern s32 D_800D1374;

void func_800CF268(void) {
    func_800CF6D0(-0x400, 0);
    if (func_800167F0(0) & 0xFFFF) {
        D_800D136C = -0x340;
        D_800D1374++;
    }
}
