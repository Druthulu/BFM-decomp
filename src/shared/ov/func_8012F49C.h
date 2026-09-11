/* func_8012F49C — shared body (overlay slot 0x80128158, h_exact c9866fcb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8004914C();
extern void func_800491AC();
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
s32 *func_8012F49C(s32 *param_1, s32 param_2, s32 param_3) {
    extern u8 D_800AF648_b __asm__("D_800AF648");
    extern u8 D_800AF648;
    s16 sv[4];
    s32 out[2];
    s32 sxy, p, flag;
    s32 m;
    void *pv;
    m = *(s32 *)(param_2 + 0x20) + 0x34;
    ((void (*)(s32))func_8004914C)(m);
    ((void (*)(s32))func_800491AC)(m);
    pv = (void *)sv;
    ((void (*)(s32, void *, s32 *))RotTransSV)(param_3, pv, &out[0]);
    sxy = 0;
    /* $a0-pinned scopes force the &D_800AF648 constant to be rematerialized
       (lui/addiu) before each call instead of CSE-hoisting it. */
    { void *r4; r4 = &D_800AF648_b; func_8004914C(r4); }
    { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
    ((s32 (*)(void *, s32 *, s32 *, s32 *))RotTransPers)(pv, &sxy, &p, &flag);
    if (flag < 0) {
        out[0] = sxy = 0;
    } else {
        out[0] = sxy;
    }
    *param_1 = out[0];
    return param_1;
}
