/* guess_WorldToScreen — shared body (overlay slot 0x80128158, h_exact d63a10fa). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8004914C();
extern void func_800491AC();
extern s32 RotTransPers(s32, s32, s32*, s32*);
/* guess_WorldToScreen: projects world point param_2 to screen coordinates with the saved world-screen matrix; writes sxy (0 on a GTE error) to *param_1
 * Confidence medium, xref chain: loads guess_g_CameraWsMatrix with SetRotMatrix/SetTransMatrix, calls RotTransPers on param_2, stores sxy (0 when flag < 0) at *param_1
 * Names ledger: config/names.tsv guess_WorldToScreen */
s32 *guess_WorldToScreen(s32 *param_1, s32 param_2) {
    extern u8 D_800AF648_b __asm__("guess_g_CameraWsMatrix");
    extern u8 guess_g_CameraWsMatrix;
    s32 sxy, p, flag;
    sxy = 0;
    { void *r4; r4 = &guess_g_CameraWsMatrix; func_8004914C(r4); }
    { void *r4; r4 = &D_800AF648_b; func_800491AC(r4); }
    ((s32 (*)(s32, s32 *, s32 *, s32 *))RotTransPers)(param_2, &sxy, &p, &flag);
    if (flag < 0) {
        *param_1 = sxy = 0;
    } else {
        *param_1 = sxy;
    }
    return param_1;
}
