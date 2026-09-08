/* func_8013A860 — shared body (overlay slot 0x80128158, h_exact 6177d824). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern u8 D_8011DA80[];
void func_8013A860(void) {
    s32 i;
    u8 *p;
    i = 0;
    p = D_8011DA80;
    do {
        func_80016714(p, 0x10);
        i++;
        p += 0x10;
    } while (i < 2);
}
