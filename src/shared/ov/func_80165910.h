/* func_80165910 — shared body (overlay slot 0x80128158, h_exact f3d22be9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s8 D_80078EC4;
s32 func_80165910(void)
{
    s32 v;
    s32 ret;
    v = (u8)D_80078EC4;
    ret = v;
    if (v == 0) {
        register s32 one __asm__("$2");
        one = 1;
        __asm__ __volatile__("" : "=r"(one) : "0"(one));
        D_80078EC4 = one;
    }
    return ret;
}
