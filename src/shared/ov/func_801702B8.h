/* func_801702B8 — shared body (overlay slot 0x80128158, h_exact 22788e91). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171928(void *a0);
extern void *D_8011F738;
void func_801702B8(s32 a0) {
    if (func_80171AB0(a0, &D_8011F738) == 0) {
        func_80171928((void *)a0);
    }
}
