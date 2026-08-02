extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8 D_800AF648;
extern s16 D_801EADE4;
extern s16 D_801EADE6;

void func_8018A774(s32 a0) {
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801EADE4 = sxy[0];
    D_801EADE6 = sxy[1];
}
