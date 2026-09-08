/* func_801502EC — shared body (overlay slot 0x80128158, h_exact 8e65f9ef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80135D20(s32 a0, s32 a1, void *a2);
s32 func_801502EC(s32 e, void *a1, void *a2) {
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    extern u8 D_801152A8[];
    Vec8_c1 save;
    Vec8_c1 test;
    s32 found;
    u8 *p;
    found = 0;
    __builtin_memcpy(&save, a1, 8);
    *(s16 *)((s32)a1 + 2) = 0x7fff;
    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if (*(u16 *)p != 0) {
                if ((*(u16 *)(p + 0x5C) & 0x400) != 0) {
                    if (*(s32 *)(p + 0x58) != 0) {
                        test = save;
                        if (func_80135D20(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), &test) != 0) {
                            found = 1;
                            if (test.unk2 < *(s16 *)((s32)a1 + 2)) {
                                __builtin_memcpy(a1, &test, 8);
                                __builtin_memcpy(a2, D_801152A8, 8);
                            }
                        }
                    }
                }
            }
            p += 0x10C;
        } while (p < D_80126720);
    }
    return found;
}
