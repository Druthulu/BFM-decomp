/* func_801700B8 — shared body (overlay slot 0x80128158, h_exact 9427ade0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_8011F738;
extern void func_801719A4(int a0, int a1);
extern s32 func_8013767C(s32 a0);
extern void func_80171928(void *a0);
void func_801700B8(u8 *a0) {
    func_801719A4((int)a0, 1);
    *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_8011F738);
    func_80171928((void *)a0);
}
