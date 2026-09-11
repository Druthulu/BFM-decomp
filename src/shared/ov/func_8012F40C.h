/* func_8012F40C — shared body (overlay slot 0x80128158, h_exact d63a10fa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8004914C();
extern void func_800491AC();
extern s32 RotTransPers(s32, s32, s32*, s32*);
s32 *func_8012F40C(s32 *param_1, s32 param_2) {
    extern u8 D_800AF648_b __asm__("D_800AF648");
    extern u8 D_800AF648;
    s32 sxy, p, flag;
    sxy = 0;
    { void *r4; r4 = &D_800AF648; func_8004914C(r4); }  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
    ((s32 (*)(s32, s32 *, s32 *, s32 *))RotTransPers)(param_2, &sxy, &p, &flag);
    if (flag < 0) {
        *param_1 = sxy = 0;
    } else {
        *param_1 = sxy;
    }
    return param_1;
}
