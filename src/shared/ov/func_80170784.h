/* func_80170784 — shared body (overlay slot 0x80128158, h_exact e3c0e81b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801719A4(int a0, int a1);
extern s32 func_80171990(u8 *a0);
extern void func_801707D4(void *a0);
extern void *D_8011F738;
void func_80170784(u8 *a0) {
    func_801719A4((int)a0, 1);
    (*(void (*)(void))D_8011F738)();
    func_80171990(a0);
    func_801707D4(a0);
}
