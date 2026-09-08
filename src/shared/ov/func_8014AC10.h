/* func_8014AC10 — shared body (overlay slot 0x80128158, h_exact f5d1e453). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80016714(void *a0, s32 a1);
extern s32 D_8011D030;
void func_8014AC10(s32 arg0) {
    u8 *p;
    u8 *end;
    u8 *t;
    s32 one;
    void *a0;
    s32 a1;
    p = (u8 *)&D_8011D030;
    t = p + 0xA50;
    if (p < t) {
        one = 1;
        end = t;
        do {
            if (*(u16 *)p == arg0) {
                a0 = *(void **)(p + 0x20);
                if (a0 != 0) {
                    a1 = 0x38;
                    if (*(u16 *)a0 == one) {
                        a1 = 0x84;
                    }
                    func_80016714(a0, a1);
                }
                func_80016714(p, 0x58);
            }
            p += 0x58;
        } while (p < end);
    }
}
