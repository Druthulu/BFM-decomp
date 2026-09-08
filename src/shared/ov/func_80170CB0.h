/* func_80170CB0 — shared body (overlay slot 0x80128158, h_exact 56339eab). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801719A4(int a0, int a1);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
void func_80170CB0(u8 *a0) {
    func_801719A4((int)a0, 3);
    a0[0x217] = 0;
    func_8017197C(a0);
    func_80170CF0(a0);
}
