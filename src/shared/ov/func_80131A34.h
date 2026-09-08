/* func_80131A34 — shared body (overlay slot 0x80128158, h_exact d5151bad). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012A828(s32 a0, void *a1);
s32 func_80131A34(s32 a0, s32 a1)
{
    extern s32 func_80131CF4(s32);
    void *p;
    p = (void *)((int (*)(int, int))func_80131CF4)(*(s32 *)(a0 + 0xBC), a1);
    if (p != 0) {
        if (a1 == 0xB || a1 == 8 || a1 == 0x20) {
            *(s32 *)(a0 + 0xC4) |= 4;
        } else {
            *(s32 *)(a0 + 0xC4) &= -5;
        }
        func_8012A828(a0, p);
        return 1;
    }
    return 0;
}
