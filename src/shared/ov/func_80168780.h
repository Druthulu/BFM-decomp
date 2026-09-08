/* func_80168780 — shared body (overlay slot 0x80128158, h_exact baa7c44a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
void func_80168780(s32 a0) {
    func_80168BDC(a0, 8, 0, 2);
    func_801687CC(a0);
    *(u16 *)(a0 + 2) += 1;
}
