/* func_8016E7C8 — shared body (overlay slot 0x80128158, h_exact d2abc2eb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern void func_80016ED4(void *a0);
    extern SVECTOR_8016E7C8 D_80181E10[4];
    extern s32 D_80181E30;
    extern s32 D_80181E38;
    extern s32 D_80181E40;
    extern s32 D_80181E48;

    Prim_8016E7C8 prim;
    MATRIX_8016E7C8 m;
    SVECTOR_8016E7C8 tmp;
    Prim_8016E7C8 *pp;   /* $s2 — force &prim into a saved reg */

    ((void (*)(void *, void *))func_80017DC4)(param_2, &m);
    m.t[0] = *(short *)(param_1 + 6);
    m.t[1] = *(short *)(param_1 + 10);
    m.t[2] = *(short *)(param_1 + 14);
    func_8004914C(&m);
    func_800491AC(&m);
    pp = &prim;
    RotTransSV(&D_80181E10[0], pp, &tmp);
    RotTransSV(&D_80181E10[1], &prim.v[1], &tmp);
    RotTransSV(&D_80181E10[2], &prim.v[2], &tmp);
    RotTransSV(&D_80181E10[3], &prim.v[3], &tmp);
    prim.v[0].vz = 3;
    prim.f5 = 0x50000000;
    prim.f0 = D_80181E30;
    prim.f1 = D_80181E38;
    prim.f2 = D_80181E40;
    prim.f3 = D_80181E48;
    prim.f4 = *param_3;
    prim.f6 = 0x27;
    func_80016ED4(pp);
}
