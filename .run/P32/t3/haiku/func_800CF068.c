extern void func_8001AA98(void *a0);
extern s32 D_800D1368;
extern s32 D_800D1370;
extern s32 D_800D1374;
extern void func_800167B8(s32 a0);
extern void func_800118AC(void);
extern char D_800CEDFC[];

void func_800CF068(void) {
    func_8001AA98(D_800CEDFC);
    D_800D1368 = 0;
    D_800D1370 = 0;
    D_800D1374 = 0;
    func_800167B8(0);
    func_800118AC();
}
