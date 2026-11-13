/* func_80136C90 — shared body (overlay slot 0x80128158, h_exact 69b2badc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of func_8001534C; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x64, ov_SC03_126 objdump */
s32 func_80136C90()
{
    extern void func_8001534C(int, void *, int, int, int, int);
    extern S10_80136C90 D_8018D74C;

    S10_80136C90 buf = D_8018D74C;
    func_8001534C(0, &buf, 0x78, 0x10, 0, 0);
}
