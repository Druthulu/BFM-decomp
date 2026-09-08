/* func_8012DF34 — shared body (overlay slot 0x80128158, h_exact 934e4124). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126B58;
extern u8 D_801152A8[];
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
s32 func_8012DF34(s32 a0, s32 a1, s32 a2) {
    s32 s0 = a2;
    s32 *p = &D_80126B58;
    if (a0 != 0) {
        if (*(s16 *)(a0 + 0xAA) != 0) {
            return 0;
        }
    }
    if (func_80135888(*(s32 *)((s32)p + 0x20), *(s32 *)((s32)p + 0x38), a1, s0) != 0) {
        func_8012F568(1, 1, 0, 0xA, s0, (s32)D_801152A8);
        return 1;
    }
    return 0;
}
