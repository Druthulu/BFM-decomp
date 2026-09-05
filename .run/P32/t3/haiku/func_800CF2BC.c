extern void func_800CF6D0(s32 a0, u32 a1);
extern void func_800167B8(s32 a0);
extern s32 D_800D136C;
extern s32 D_800D1374;

void func_800CF2BC(void) {
    if (func_800CF3B0() != 0) {
        return;
    }
    func_800CF6D0(D_800D136C++, 0);
    if (D_800D136C < 0x141) {
        return;
    }
    func_800167B8(4);
    D_800D1374++;
}
