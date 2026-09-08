/* func_8016F95C — shared body (overlay slot 0x80128158, h_exact 9d42bc94). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern void func_80171928(void *a0);
extern u16 D_8011F73E;
void func_8016F95C(void *a0) {
    u16 *p = &D_8011F73E;
    u16 v = *p;
    s32 r;
    if (v == 0) {
        r = func_80171CC4(a0, p - 3);
    } else {
        r = func_80171D1C(a0, p - 3, v & 0xFF);
    }
    if (r != 0) {
        func_80171928(a0);
    }
}
