/* func_8013767C — shared body (overlay slot 0x80128158, h_exact 5887ff3a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399A8(void);
extern void func_801377B4(s32 a0, s32 a1, s32 a2);
s32 func_8013767C(s32 a0) {
    s32 s0 = func_801399A8();
    if (s0 != 0) {
        func_801377B4(a0, 0, s0);
    }
    return s0;
}
