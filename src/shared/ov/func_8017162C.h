/* func_8017162C — shared body (overlay slot 0x80128158, h_exact c089d1e2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_8011F738;
extern s32 func_801716AC(s32 a0, void *a1, s32 *a2);
extern void func_80171928(void *a0);
void func_8017162C(void *a0) {
    void *s1 = a0;
    void *s0 = D_8011F738;
    s32 local;
    local = 0;
    func_801716AC(0, s0, &local);
    func_801716AC(1, s0, &local);
    func_801716AC(2, s0, &local);
    if (local == 0) {
        func_80171928(s1);
    }
}
