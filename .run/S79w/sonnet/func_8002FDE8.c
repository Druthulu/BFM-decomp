extern s32   D_800A469C;
extern s16   D_800A46A0;
extern s16   D_800A46A2;
extern u8    D_800A46B0;
extern s16   D_800A46D2[];
extern s32   D_800652F0[];

extern void  func_8002ED90(void);
extern void  func_800415A8(s32);
extern s32   func_80041A80(u8 *, s32, s32);
extern s32   func_800419B0(s32);

s32 func_8002FDE8(s32 idx, u8 *data) {
    func_8002ED90();
    if (D_800A46A2 >= 0) {
        func_800415A8(D_800A46A2);
        D_800A46A2 = -1;
    }
    D_800A46A0 = idx | 0x4000;
    D_800A46B0 = 1;
    __asm__ __volatile__("");
    D_800A469C = D_800652F0[idx];
    if ((D_800A46A2 = D_800A46D2[0] = func_80041A80(data, -1, D_800A469C)) == -1) {
        D_800A46B0 = 1;
        return 1;
    }
    if ((s16)func_800419B0(D_800A46A2) != -1) {
        D_800A46B0 = 0;
        return 1;
    }
    func_800415A8(D_800A46D2[0]);
    D_800A46A2 = -1;
    D_800A46B0 = 1;
    return 1;
}
