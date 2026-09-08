/* func_8013A8BC — shared body (overlay slot 0x80128158, h_exact ea637cd0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011DA80[];
s32 func_8013A8BC(void) {
    s32 p;
    s32 i;
    p = (s32)D_8011DA80;
    for (i = 0; i < 0x20; i += 0x10) {
        if (*(s16*)((s32)D_8011DA80 + i) == 0) {
            return p;
        }
        p += 0x10;
    }
    return 0;
}
