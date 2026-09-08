/* func_801717A0 — shared body (overlay slot 0x80128158, h_exact 50693661). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801719A4(int a0, int a1);
extern int func_800D0F8C(int a0);
extern int func_800D0FE0(int a0);
extern void func_80171928(void *a0);
extern void *D_8011F738;
void func_801717A0(void *a0) {
    int v0;
    func_801719A4((int)a0, 1);
    v0 = func_800D0F8C(*(u8 *)&D_8011F738);
    if (v0 != 0) {
        func_800D0FE0(v0);
    }
    func_80171928(a0);
}
