/* func_80161278 — shared body (overlay slot 0x80128158, h_exact f1ff88ab). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801152BC;
extern s32 func_801612B8(void *a0, s32 a1);
extern int func_80161374(int param_1, unsigned int param_2);
void func_80161278(void *a0) {
    s32 r;
    D_801152BC = 0;
    r = func_801612B8(a0, 1);
    func_80161374(a0, r);
}
