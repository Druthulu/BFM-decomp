/* func_8013E410 — shared body (overlay slot 0x80128158, h_exact 734fbf89). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
s32 func_8013E410(void) {
    s32 a0;
    s32 v1;
    v1 = (s32)D_801202A0;
    for (a0 = 0; a0 < 0x60; a0++, v1 += 0x10C) {
        if (*(u16 *)v1 == 0) {
            return v1;
        }
    }
    return 0;
}
