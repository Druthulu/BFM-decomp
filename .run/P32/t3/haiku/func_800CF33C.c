extern s32 D_800D136C;
extern s32 D_800D1374;
extern void func_800CF6D0(s32 a0, u32 a1);
extern s32 func_800167F0(s32 a0);

void func_800CF33C(void) {
    func_800CF6D0(D_800D136C, 0);
    if ((func_800167F0(4) & 0xFFFF) != 0) {
        D_800D1374++;
    }
}
