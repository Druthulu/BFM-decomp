/* func_8014E6F8 — shared body (overlay slot 0x80128158, h_exact 8b71d48d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014E83C(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E790(s32 a0, s16 *a1, s16 *a2);
void func_8014E6F8(struct SubE6F8 *a0) {
    s16 g1[3];
    s16 g2[3];
    u16 t8A;
    u16 tA;
    g1[0] = a0->f88;
    t8A = a0->f8A;
    g1[1] = t8A;
    g1[2] = a0->f8C;
    g2[0] = a0->f6;
    tA = a0->fA;
    g2[1] = tA;
    g2[2] = a0->fE;
    if (a0->f180 == 0) {
        g1[1] = t8A - 0x54;
        g2[1] = tA - 0x54;
        func_8014E83C((s32)a0, g1, g2);
    } else {
        func_8014E790((s32)a0, g1, g2);
    }
}
