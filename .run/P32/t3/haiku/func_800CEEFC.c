extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_800183E0(void *a0);
extern void func_800167B8(s32 a0);
extern void func_800118AC(void);

extern s8 D_800B9A11;
extern s32 D_800D1364;
extern s16 D_800B99E8;
extern s32 D_800D130C;

void func_800CEEFC(void) {
    D_800B9A11 = 1;
    func_8001C044();
    func_80015310();
    D_800D1364 = 0;
    func_800183E0(&D_800D130C);
    func_800167B8(0);
    D_800B99E8 = 0;
    func_800118AC();
}
