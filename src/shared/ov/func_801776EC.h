/* func_801776EC — shared body (overlay slot 0x80128158, h_exact b6119a8c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011F7AB;
void func_801776EC(u8 *a0)
{
    u8 *p;
    switch (D_8011F7AB) {
    default:
        D_8011F7AB = 0;
    case 0:
        a0[4] = 0xFF;
        a0[6] = 0x30;
        a0[5] = 0x30;
        break;
    case 1:
        a0[5] = 0xFF;
        a0[6] = 0x30;
        a0[4] = 0x30;
        break;
    case 2:
        a0[6] = 0xFF;
        a0[5] = 0x30;
        a0[4] = 0x30;
        break;
    }
    p = &D_8011F7AB;
    *p = *p + 1;
}
