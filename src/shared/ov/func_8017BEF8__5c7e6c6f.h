/* func_8017BEF8 — shared body (overlay slot 0x80128158, h_exact 5c7e6c6f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017BEF8(param_1)
s32 param_1;
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    extern u8 D_80182C64[];
    s32 v0;

    s1 = param_1;
    v0 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = v0;
    s0 = v0;

    if (v0 == 0) {
        ((void (*)(s32))func_80146C3C)(s1);
        return;
    }

    func_8001CC3C(s0, D_80182C64, 0x290, 0x100);
    *(u8 *)(s0 + 0x27) = 0x64;
    *(s16 *)(s0 + 0x1A) = 0x2000;
    *(s16 *)(s0 + 0x18) = 0x2000;
    *(s16 *)(s0 + 0x14) = -0xE3;
    *(s32 *)(s0 + 4) |= 0x8000000;
    func_80146E90((s32 *)s1, 4);
    *(u16 *)(s1 + 2) += 1;
}
