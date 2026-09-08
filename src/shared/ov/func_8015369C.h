/* func_8015369C — shared body (overlay slot 0x80128158, h_exact 69296635). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_8011DB28)(s32 a0);
void func_8015369C(s32 a0) {
    if (D_8011DB28 != 0) {
        D_8011DB28(a0 + 0xA0);
    }
    *(u8 *)(a0 + 0xDE) = 0x5A;
}
