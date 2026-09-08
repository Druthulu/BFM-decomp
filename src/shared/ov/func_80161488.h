/* func_80161488 — shared body (overlay slot 0x80128158, h_exact 27836390). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801615C4(void *a0, s32 a1);
extern s32 func_80161774(int param_1, u32 param_2);
extern s32 func_8016197C(s32 a0, s32 a1);
s32 func_80161488(void *a0) {
    s32 v0 = func_801615C4(a0, 0);
    if (*(u8 *)((u8 *)a0 + 0x1C6) == 0) {
        func_80161774(a0, v0);
    } else {
        return func_8016197C((s32)a0, v0) & -0x8;
    }
    /* fall off end: returns clobbered v0 (matches original) */
}
