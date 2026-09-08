/* func_80129258 — shared body (overlay slot 0x80128158, h_exact 29ec542f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_8011DB30;
void func_80129258(void) {
    s16 *p = &D_8011DB30;
    s32 i = 0x7F;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x38);
        i--;
    } while (i >= 0);
}
