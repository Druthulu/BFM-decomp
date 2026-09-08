/* func_8012DBD0 — shared body (overlay slot 0x80128158, h_exact e4bcf01d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012DE2C(s32 a0);
extern s32 func_8012DDA4(void);
extern void func_80013350(s32 a0, void *a1);
s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 param_1 __asm__("$18");  /* $s2 */
    register s32 param_2 __asm__("$20");  /* $s4 */
    register s32 param_3 __asm__("$21");  /* $s5 */
    register s32 param_4 __asm__("$19");  /* $s3 */
    register s32 iVar1 __asm__("$16");    /* $s0 */
    register s32 iVar5 __asm__("$17");    /* $s1 (running max, then its square) */
    s32 iVar4;
    register s32 t __asm__("$2");          /* $v0: keep the loaded halfword in $v0 so abs copies $v0->$v1 */
    u32 uVar3;
    param_1 = arg0;
    param_2 = arg1;
    param_3 = arg2;
    param_4 = arg3;
    iVar1 = func_8012DE2C(param_1);
    if (iVar1 == 0) {
        return 0;
    }
    if (*(u32 *)(param_1 + 0x58) == 0) {
        iVar5 = 0x80;
    } else {
        uVar3 = *(u32 *)(param_1 + 0x58) & 0xfffffff;
        t = (s32)*(s16 *)(uVar3 + 4);
        iVar4 = (s32)*(s16 *)(uVar3 + 6);
        iVar5 = t;
        if (t < 0) {
            iVar5 = -iVar5;
        }
        if (iVar4 < 0) {
            iVar4 = -iVar4;
        }
        __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4));
        if (iVar5 < iVar4) {
            iVar5 = iVar4;
        }
        t = (s32)*(s16 *)(uVar3 + 8);
        iVar4 = t;
        if (t < 0) {
            iVar4 = -iVar4;
        }
        __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4));
        if (iVar5 < iVar4) {
            iVar5 = iVar4;
        }
        t = (s32)*(s16 *)(uVar3 + 10);
        iVar4 = t;
        if (t < 0) {
            iVar4 = -iVar4;
        }
        __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4));
        if (iVar5 < iVar4) {
            iVar5 = iVar4;
        }
        t = (s32)*(s16 *)(uVar3 + 0xc);
        iVar4 = t;
        if (t < 0) {
            iVar4 = -iVar4;
        }
        __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4));
        if (iVar5 < iVar4) {
            iVar5 = iVar4;
        }
        t = (s32)*(s16 *)(uVar3 + 0xe);
        iVar4 = t;
        if (t < 0) {
            iVar4 = -iVar4;
        }
        __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4));
        if (iVar5 < iVar4) {
            iVar5 = iVar4;
        }
    }
    iVar5 = iVar5 * iVar5;
LAB_8012dcf8:
    do {
        u16 uVar6 = *(u16 *)(iVar1 + 0x5c);
        if ((uVar6 & 0x8000) != 0) {
            if ((uVar6 & 0x4000) == 0) {
                if (*(u16 *)(iVar1 + 0x5e) != param_4) {
                    if ((*(u16 *)(iVar1 + 0xae) & 1) == 0) {
                        if (((s32(*)(s32, s32))func_80013350)(param_1 + 4, iVar1 + 4) < iVar5) {
                            *(u16 *)(iVar1 + 0x60) = param_2;
                            *(u16 *)(iVar1 + 0x62) = param_3;
                            *(u16 *)(iVar1 + 0x5e) = param_4;
                            *(u16 *)(iVar1 + 0x5c) = *(u16 *)(iVar1 + 0x5c) | 1;
                        }
                    }
                }
            }
        }
        iVar1 = func_8012DDA4();
    } while (iVar1 != 0);
    return 0;
}
