/* func_80143BDC — shared body (overlay slot 0x80128158, h_exact 78b3d886). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012C51C(void *a0, s32 a1);
void func_80143BDC(u16 *a0) {
    struct S80143BDC sp;
    u16 t;
    sp.f0 = a0[0];
    sp.f2 = a0[1];
    t = a0[2];
    sp.f6 = 0x1C;
    sp.f8 = 1;
    sp.fA = 0;
    sp.f10 = 0;
    sp.fE = 0;
    sp.f4 = t;
    func_8012C51C(&sp, 0);
}
