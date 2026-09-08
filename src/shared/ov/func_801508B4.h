/* func_801508B4 — shared body (overlay slot 0x80128158, h_exact c54c2b22). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014A2E4(s32 a0);
extern void func_8014A380(s32 a0, s32 a1);
s32 func_801508B4(s32 a0)
{
    s32 r;
    r = func_8014A2E4(a0);
    if (r != 0) {
        func_8014A380(a0, r);
        return 1;
    }
    return 0;
}
