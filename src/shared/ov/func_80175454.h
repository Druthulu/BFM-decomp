/* func_80175454 — shared body (overlay slot 0x80128158, h_exact d8ffcad5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
void func_80175454(void) {
    u8 *p = &D_8011F7A8;
    if (*p == 0) {
        *p = 1;
        D_8011F7A9 = 0;
        D_8011F7AD = 0xA;
        D_8011F7AE = 0;
    }
}
