/* func_8016F71C — shared body (overlay slot 0x80128158, h_exact df105843). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_8011F738;
extern void func_801719A4(int a0, int a1);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
void func_8016F71C(u8 *a0) {
    func_801719A4((int)a0, 1);
    *(void **)(a0 + 0x200) = D_8011F738;
    func_80171990(a0);
    func_8016F764((s32)a0);
}
