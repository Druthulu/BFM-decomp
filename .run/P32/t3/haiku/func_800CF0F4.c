extern s32 D_800D1368;
extern s32 D_800D1374;
extern void func_800CF408(s32 a0, s32 a1);
extern s32 func_800167F0(s32 a0);

void func_800CF0F4(void) {
    func_800CF408(0, D_800D1368);

    if (func_800167F0(0) & 0xFFFF) {
        D_800D1374++;
    }
}
