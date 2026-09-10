/* func_801612B8 — shared body (overlay slot 0x80128158, h_exact 5fffbf1e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
s32 func_801612B8(void * a0, s32 a1)
{
    s32 p;
    s32 v0;
    s32 v1;
    p = a0;
    if ((a1 & 1) == 0) {
        func_8014E934(p);
    }
    v0 = ((s32 (*)(s32))func_8014CC28)(p);
    do { v1 = ((s32 (*)(s32))func_8014F3E8)(p); } while (0);
    return v0 | v1;
}
