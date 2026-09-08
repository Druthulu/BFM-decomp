/* func_80177F84 — shared body (overlay slot 0x80128158, h_exact 8041750b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80177F84(s32 param_1, s32 param_2) {
    u16 uVar4;
    s16 iVar3;
    register u8 *pcVar2 __asm__("$6");
    u32 uVar1;
    register s32 c5 __asm__("$10");
    register s32 cmask __asm__("$9");
    uVar4 = 0x100;
    iVar3 = 0;
    c5 = 5;
    cmask = -257;
    pcVar2 = (u8 *)(param_1 + 0xc);
    do {
        register u32 src __asm__("$2");
        register u32 byteval __asm__("$3");
        register u32 testval __asm__("$4");
        src = (param_2 >> 0x10) & 0xf;
        __asm__ __volatile__("" : : "r"(src));
        byteval = src;
        __asm__ __volatile__("" : "=r"(byteval) : "0"(byteval));
        testval = src;
        __asm__ __volatile__("" : : "r"(byteval), "r"(testval));
        param_2 = param_2 << 4;
        if ((iVar3 == c5) || (testval != 0)) {
            uVar4 = 0;
        }
        pcVar2 += 0x14;
        iVar3 += 1;
        {
            register s32 r __asm__("$4");
            r = *(u16 *)(pcVar2 - 2);
            pcVar2[0] = (u8)(byteval * 8 + 8);
            *(u16 *)(pcVar2 - 2) = uVar4 | (r & cmask);
        }
    } while (iVar3 < 5);
}
