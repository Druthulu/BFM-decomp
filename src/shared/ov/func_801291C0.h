/* func_801291C0 — shared body (overlay slot 0x80128158, h_exact 203f8cae). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern s16 D_8011DB30;
u8 *func_801291C0(void) {
    u8 *p = (u8 *)&D_8011DB30;
    s32 i = 0;
loop:
    if (*(u16 *)p == 0) {
        func_80016714(p, 0x38);
        return p;
    }
    if (++i < 0x80) {
        p += 0x38;
        goto loop;
    }
    return 0;
}
