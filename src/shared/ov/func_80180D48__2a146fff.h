/* func_80180D48 — shared body (overlay slot 0x80128158, h_exact 2a146fff). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80180BDC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801BC508[];
void func_80180D48(s32 a0) {
    s32 v0;
    v0 = func_80180BDC(a0);
    if ((v0 << 16) != 0) {
        return;
    }
    func_8012A828(a0, &D_801BC508);
    *(u16 *)(a0 + 2) += 1;
}
