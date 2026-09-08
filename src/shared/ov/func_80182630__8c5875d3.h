/* func_80182630 — shared body (overlay slot 0x80128158, h_exact 8c5875d3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399F0(s32);
extern void func_80139914(s32 a0);
void func_80182630(s32 a0)
{
    u8 *s0 = (u8 *)a0;
    register s32 v0 asm("v0");
    register s32 v1 asm("v1");
    v0 = func_801399F0(*(s32 *)(s0 + 0x198));
    if (v0 != 0) {
        func_80139914(*(s32 *)(s0 + 0x198));
        v0 = s0[0x4D];
        v1 = s0[0x214];
        s0[0x4D] = v0 - 1;
        s0[0x214] = v1 + 1;
    }
}
