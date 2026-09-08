/* func_8014AB7C — shared body (overlay slot 0x80128158, h_exact d8ca0051). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80162CCC();
extern s32 D_8011F9D0;
void func_8014AB7C(s32 arg0) {
    u8 *p;
    for (p = (u8 *)&D_8011F9D0; p < (u8 *)&D_8011F9D0 + 0x820; p += 0x68) {
        if (*(u16 *)p == arg0) {
            ((void (*)(u8 *))func_80162CCC)(p);
        }
    }
}
