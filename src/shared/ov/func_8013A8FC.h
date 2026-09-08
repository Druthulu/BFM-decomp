/* func_8013A8FC — shared body (overlay slot 0x80128158, h_exact aa10f517). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011DA80[];
extern void func_8013A9B4(s32 a0, s32 a1);
s32 func_8013A8FC(s32 arg0) {
    s32 p;
    s32 i;
    s32 v1;
    if (*(u16*)(arg0 + 0x18) == 0) {
        return 1;
    }
    if (*(s32*)(arg0 + 0x40) == 0) {
        i = 0;
        do {
            if (*(s16*)(i + (s32)D_8011DA80) == 0) {
                p = i + (s32)D_8011DA80;
                goto post;
            }
            i += 0x10;
        } while (i < 0x20);
        i = 0;
        p = i;
    post:
        if (p != 0) {
            v1 = *(u16*)(arg0 + 0x18);
            if (v1 < 7) {
                if (v1 != 0) {
                    func_8013A9B4(arg0, p);
                    return 1;
                }
            }
        }
    }
    return 0;
}
