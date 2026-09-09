/* func_80164BDC — shared body (overlay slot 0x80128158, h_exact b9aaf8bd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80164BDC(s32 param_1)
{
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_8018E920;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_8018E921 = 0xf0;
        *(u8 *)base = 0xf0;
        D_8018E922 = 0xc0;
        D_8018E926 = 0;
        D_8018E925 = 0;
        D_8018E924 = 0;
        D_8018E927 = 0;
        D_8018E923 = 0;
        *(s16 *)(iVar1 + 0x1e) = 0xccc;
        *(s16 *)(iVar1 + 0x10) = 0x400;
        *(s16 *)(p1 + 0x60) = 0x700;
        *(s16 *)(p1 + 0x62) = -0x60;
        func_80164DD0(p1);
        ((void (*)(s32))func_80146CA0)(p1);
    } else {
        ((void (*)(s32))func_80164DB0)(p1);
    }
}
