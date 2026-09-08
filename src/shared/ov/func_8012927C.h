/* func_8012927C — shared body (overlay slot 0x80128158, h_exact b7012f8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801292C8(u8 *a0);
extern s16 D_8011DB30;
void func_8012927C(void) {
    s32 i;
    u8 *p = (u8 *)&D_8011DB30;
    for (i = 0; i < 0x80; i++) {
        func_801292C8(p);
        p += 0x38;
    }
}
