/* func_80132EF4 — shared body (overlay slot 0x80128158, h_exact 3dc0bf99). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);
s32 func_80132EF4(s32 a0, s32 a1) {
    s32 s0 = func_8012913C(a1 & 0xFFFF);
    if (s0 != 0) {
        func_80129350(s0, a0);
    }
    return s0;
}
