/* func_8013A530 — shared body (overlay slot 0x80128158, h_exact 4ab0c4ef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *memcpy(void *, const void *, u32);
extern void func_80015D4C();
extern void func_80015F04();
extern void func_8013AA24(s32 a0, s32 a1);
void func_8013A530(int param_1)
{
    int iVar11;
    u16 uVar2;
    int sVar2;
    register u8 bVar1 __asm__("$8");
    int deadlocal[2];
    iVar11 = *(int *)(param_1 + 4);
    uVar2 = *(u16 *)(iVar11 + 0x18);
    sVar2 = uVar2;
    bVar1 = *(u8 *)(iVar11 + 0x22);
    if (uVar2 != 0 && uVar2 < 7) {
        if (uVar2 != 1) {
            if (sVar2 != 0 && sVar2 < 7) {
                register u32 f34 __asm__("$5");
                u32 uVar2b;
                u32 uVar6;
                short sVar5;
                register int fc __asm__("$5");
                register int zr __asm__("$0");
                int iVar7;
                f34 = *(u16 *)(iVar11 + 0x34);
                uVar6 = f34 + 0x10;
                uVar2b = *(u16 *)(iVar11 + 0x36) + 0x10;
                if (*(u8 *)(iVar11 + 0x20) != 0) {
                    uVar6 = f34 + 0x38;
                }
                sVar5 = (short)((int)((int)*(s16 *)(iVar11 + 0x28) * (uVar6 & 0xffff)) / 0x9a);
                *(s16 *)(param_1 + 8) = sVar5;
                if ((bVar1 & 8) == 0) {
                    *(s16 *)(param_1 + 8) = -sVar5;
                }
                if ((bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0) {
                    *(s16 *)(param_1 + 8) = -*(s16 *)(param_1 + 8);
                }
                sVar5 = (short)((int)((int)*(s16 *)(iVar11 + 0x2a) * (uVar2b & 0xffff)) / 0x2a);
                *(s16 *)(param_1 + 0xa) = sVar5;
                if ((bVar1 & 0x10) != 0) {
                    *(s16 *)(param_1 + 0xa) = -sVar5;
                }
                __asm__("" :: "r"(bVar1));
                fc = *(s16 *)(param_1 + 0xc);
                iVar7 = fc + zr;
                if (fc < *(s16 *)(param_1 + 0xe)) {
                    int t = iVar7 + 0x400;
                    *(s16 *)(param_1 + 0xc) = (short)t;
                    if (((t << 16) >> 16) > (int)*(s16 *)(param_1 + 0xe)) {
                        *(s16 *)(param_1 + 0xc) = *(s16 *)(param_1 + 0xe);
                    }
                } else if (*(s16 *)(param_1 + 0xe) < fc) {
                    int t = iVar7 - 0x400;
                    __asm__("" :: "r"(iVar7), "r"(t));
                    *(s16 *)(param_1 + 0xc) = (short)t;
                    if (((t << 16) >> 16) < (int)*(s16 *)(param_1 + 0xe)) {
                        *(s16 *)(param_1 + 0xc) = *(s16 *)(param_1 + 0xe);
                    }
                }
                __asm__("" :: "r"(fc));
                func_8013AA24(iVar11, param_1);
            }
        } else {
            int iVar7, iVar8;
            u32 uVar6, uVar4;
            memcpy((void *)(param_1 + 8), (void *)(iVar11 + 0x28), 4);
            uVar6 = ((*(s16 *)(iVar11 + 0x34) + 0x10) * (int)*(s16 *)(param_1 + 8)) >> 0xc;
            uVar4 = ((*(s16 *)(iVar11 + 0x36) + 0x10) * (int)*(s16 *)(param_1 + 0xa)) >> 0xc;
            iVar7 = *(u16 *)(iVar11 + 0x24) - ((uVar6 & 0xffff) >> 1);
            iVar8 = *(u16 *)(iVar11 + 0x26) - ((uVar4 & 0xffff) >> 1);
            func_80015F04((int)(s16)iVar7, (int)(s16)iVar8, (int)(s16)uVar6, (int)(s16)uVar4,
                          0xb3, 0x99, 0x4c, *(u16 *)(iVar11 + 0x1a), 4);
            func_80015F04((int)(s16)(iVar7 + 1), (int)(s16)(iVar8 + 1),
                          (int)(s16)(uVar6 - 2), (int)(s16)(uVar4 - 2),
                          0xe6, 0xcc, 0x73, *(u16 *)(iVar11 + 0x1a), 4);
            func_80015D4C((int)(s16)iVar7, (int)(s16)iVar8, (int)(s16)uVar6, (int)(s16)uVar4,
                          0xff, 0xe6, 0x99, *(u16 *)(iVar11 + 0x1a), 4);
        }
    }
    return;
}
