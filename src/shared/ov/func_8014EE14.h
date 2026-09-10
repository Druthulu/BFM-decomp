/* func_8014EE14 — shared body (overlay slot 0x80128158, h_exact d6ee7093). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_800B99DA;
extern u8 D_801202A0[];
extern s32 D_801150D8;
extern u8 D_80126720[];
extern s16 D_80126724;
extern s16 D_801152AA;
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2)
{
    s32 param_1;   /* $s0 */
    s32 param_2;   /* $s7 */
    s16 *param_3;  /* $s2 */
    s32 sVar6;     /* $s4 */
    s32 sVar7;     /* $s5 */
    s32 uVar8;     /* $s6 */
    u16 *psVar4;
    s32 *piVar5;
    s32 iVar2;
    param_3 = arg2;
    uVar8 = 0;
    sVar7 = 8;
    sVar6 = 8;
    switch ((D_800B99DA & 0x60) >> 5) {
    case 0:
    case 1:
        sVar7 = 7;
        break;
    case 2:
        sVar6 = 7;
        break;
    }
    if ((*(u32 *)(arg0 + 0x44) & 0x100000) != 0) {
        psVar4 = (u16 *)D_801202A0;
        while (psVar4 < (u16 *)(D_801202A0 + 0x6480)) {
            piVar5 = (s32 *)((u8 *)psVar4 + 0x58);
            if (*psVar4 != 0 && *piVar5 != 0 &&
                psVar4 != *(u16 **)(arg0 + 0x178) &&
                psVar4 != *(u16 **)(arg0 + 0x174) &&
                (piVar5[1] & 0x1800) != 0) {
                D_801150D8 = 0;
                iVar2 = ((s32 (*)(s32, s32, s32, s16 *))func_80135A4C)(piVar5[-0xe], ((struct { s32 w; } *)piVar5)->w, arg1, param_3);
                if (iVar2 != 0) {
                    if ((D_801150D8 & 1) != 0) {
                        if (-1 < (s32)*(s16 *)D_80126720 - (s32)*param_3)
                            *(s16 *)(arg0 + 6) = *param_3 - sVar7;
                        else
                            *(s16 *)(arg0 + 6) = *param_3 + sVar7;
                        if (-1 < (s32)D_80126724 - (s32)param_3[2])
                            *(s16 *)(arg0 + 0xE) = param_3[2] - sVar6;
                        else
                            *(s16 *)(arg0 + 0xE) = param_3[2] + sVar6;
                        uVar8 = 1;
                    } else {
                        *(s16 *)(arg0 + 6) = ((u16 *)param_3)[0];
                        *(s16 *)(arg0 + 0xA) = ((u16 *)param_3)[1] + 0x10;
                        uVar8 = 1;
                        *(s16 *)(arg0 + 0xE) = ((u16 *)param_3)[2];
                    }
                }
            }
            psVar4 += 0x86;
        }
    } else {
        psVar4 = (u16 *)D_801202A0;
        while (psVar4 < (u16 *)(D_801202A0 + 0x6480)) {
            piVar5 = (s32 *)((u8 *)psVar4 + 0x58);
            if (*psVar4 != 0 && *piVar5 != 0 &&
                psVar4 != *(u16 **)(arg0 + 0x178) &&
                psVar4 != *(u16 **)(arg0 + 0x174) &&
                (piVar5[1] & 0x1800) != 0) {
                D_801150D8 = 0;
                iVar2 = ((s32 (*)(s32, s32, s32, s16 *))func_80135A4C)(piVar5[-0xe], ((struct { s32 w; } *)piVar5)->w, arg1, param_3);
                if (iVar2 != 0) {
                    if ((D_801150D8 & 1) != 0) {
                        if (-1 < (s32)*(s16 *)D_80126720 - (s32)*param_3)
                            *(s16 *)(arg0 + 6) = *param_3 - sVar7;
                        else
                            *(s16 *)(arg0 + 6) = *param_3 + sVar7;
                        if (-1 < (s32)D_80126724 - (s32)param_3[2])
                            *(s16 *)(arg0 + 0xE) = param_3[2] - sVar6;
                        else
                            *(s16 *)(arg0 + 0xE) = param_3[2] + sVar6;
                    } else {
                        *(s16 *)(arg0 + 6) = ((u16 *)param_3)[0];
                        *(s16 *)(arg0 + 0xA) = ((u16 *)param_3)[1] + 0x10;
                        *(s16 *)(arg0 + 0xE) = ((u16 *)param_3)[2];
                        uVar8 = 1;
                        if (*piVar5 < 0) {
                            s32 av = D_801152AA;
                            if (av < 0) av = -av;
                            if (0x800 < (s16)av) {
                                if (-1 < (s32)*(s16 *)D_80126720 - (s32)*param_3)
                                    *(s16 *)(arg0 + 6) = *param_3 - sVar7;
                                else
                                    *(s16 *)(arg0 + 6) = *param_3 + sVar7;
                                if (-1 < (s32)D_80126724 - (s32)param_3[2])
                                    *(s16 *)(arg0 + 0xE) = param_3[2] - sVar6;
                                else
                                    *(s16 *)(arg0 + 0xE) = param_3[2] + sVar6;
                            }
                        }
                    }
                }
            }
            psVar4 += 0x86;
        }
    }
    return uVar8;
}
