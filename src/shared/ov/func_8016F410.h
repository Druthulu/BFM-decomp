/* func_8016F410 — shared body (overlay slot 0x80128158, h_exact 4cd92ed2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016F44C(s32 a0);
extern void func_8016F470(s32 a0);
s32 func_8016F410(s32 a0) {
    if (func_8016F44C(a0) == 0) {
        return 0;
    }
    func_8016F470(a0);
    return 1;
}
