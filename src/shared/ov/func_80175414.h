/* func_80175414 — shared body (overlay slot 0x80128158, h_exact 89f3232d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
void func_80175414(s32 _arg0)
{
    unsigned char *p = &D_8011F7A8;
    if (*p == 1) {
        *p = 0;
        D_8011F7AD = 10;
        D_8011F7A9 = 0;
        D_8011F7AE = 0x37;
    }
    return;
}
