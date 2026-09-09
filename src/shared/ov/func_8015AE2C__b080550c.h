/* func_8015AE2C — shared body (overlay slot 0x80128158, h_exact b080550c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8015AE2C(arg0)
s32 arg0;
{
    extern void (*D_80181914[])(void *);
    extern s16 D_801152A0;
    extern u8 D_800D4BE0[];
    extern s32 D_800D4E94;
    extern s32 D_800D4ED4;
    extern u8 D_800D4F8C[];
    extern s32 D_800D4A9C;
    extern s32 D_800D4B48;

    s32 flag;
    s32 r;
    s32 lim;
    s32 doit;
    s32 t;

    flag = 0;
    if ((func_80161A60(arg0) != 0) && (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) && (*(s32 *)(arg0 + 0x34) >= 0)) {
        flag = 1;
        if (*(s32 *)(arg0 + 0x5C) == 0) {
            *(s32 *)(arg0 + 0x58) = 0;
            *(s32 *)(arg0 + 0x54) = 0;
            *(s32 *)(arg0 + 0x50) = 0;
        }
        *(s32 *)(arg0 + 0x5C) = 1;
    } else {
        *(s32 *)(arg0 + 0x5C) = 0;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (*(s32 *)(arg0 + 0x1B0) == 0) {
        switch (((s32 (*)(s32))func_801619A4)(arg0)) {
        case 0:
        case 1:
        case 2:
        case 6:
            if (*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) {
                if (func_80149C08(arg0) != 0) {
                    D_80181914[*(u16 *)arg0]((void *)arg0);
                    ((void (*)(s32))func_801577C8)(arg0);
                    return;
                }
            }
            if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
                if (func_8015B6F4(arg0) == 0) {
                    ((void (*)(s32))func_8015B7B4)(arg0);
                }
            } else {
                if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
                    func_80154A74(arg0, 0x22);
                    ((void (*)(s32))func_8015B8F8)(arg0);
                    *(u32 *)(arg0 + 0x44) &= ~2;
                    if (flag != 0) {
                        ((void (*)(s32, s32, s32, s32))func_80146994)(0x3B, arg0, 0, 0);
                    }
                }
            }
            break;
        case 3:
            ((void (*)(s32))func_801498E0)(arg0);
            break;
        case 4:
            ((void (*)(s32))func_80149954)(arg0);
            break;
        case 5:
            if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
                D_80181914[*(u16 *)arg0]((void *)arg0);
                func_800CCCC0(arg0);
                return;
            }
            break;
        }
    }
    if (*(u32 *)(arg0 + 0x44) & 2) {
        ((void (*)(s32, s32))func_80155FF8)(arg0, *(u8 *)(arg0 + 0x1AA));
    } else {
        if ((*(s32 *)(arg0 + 0x240) == 0) && (((s32 (*)(s32))func_8015B858)(arg0) != 0)) {
            *(s32 *)(arg0 + 0x240) += 1;
        }
        if ((*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) && (*(u16 *)(arg0 + 0xB8) & 0x8000)) {
            ((void (*)(s32))func_8015B8F8)(arg0);
        } else if ((*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) ||
                   (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4B48)) {
            if (*(u16 *)(arg0 + 0xB8) & 0x8000) {
                if (*(s32 *)(arg0 + 0x34) >= 0) {
                    *(u16 *)(arg0 + 0xB8) += 1;
                }
            }
        }
    }
    if (*(u8 *)(arg0 + 0x1C6) != 0) {
        if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
            func_80148038(arg0, 0xFFFE6000);
        } else {
            func_80148038(arg0, 0x1A000);
        }
        lim = 0x40000;
        if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
            lim = 0xC0000;
        }
        if (*(s32 *)(arg0 + 0x34) < -lim) {
            *(s32 *)(arg0 + 0x34) = -lim;
        } else if (lim < *(s32 *)(arg0 + 0x34)) {
            *(s32 *)(arg0 + 0x34) = lim;
        }
        func_80147460(arg0);
    } else {
        if (*(s32 *)(arg0 + 0x34) < 0) {
            if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
                func_80147814(arg0, 0xFFFF0000);
            }
            func_80147814(arg0, 0x10000);
        }
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = ((*(u16 *)&D_801152A0) + func_801491C4(arg0)) & 0xFFF;
    }
    if (flag == 0) {
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            ((void (*)(s32, s32))func_80146E90)(arg0, 4);
            if (*(s32 *)(arg0 + 0x2C) > -0x80000) {
                *(s32 *)(arg0 + 0x2C) = -0x80000;
                func_80147A30(arg0, -0x10000, 0xBA000);
            } else {
                func_80147A30(arg0, -0x1000, 0xBA000);
            }
        } else {
            if (func_80146E98(arg0) != 0) {
                func_80146D90(arg0);
            }
        }
        func_80147A84(arg0);
        ((void (*)(s32))func_801473EC)(arg0);
        if (*(u8 *)(arg0 + 0x1C6) == 0) {
            func_80148038(arg0, 0x1A000);
            func_80147460(arg0);
        }
    } else {
        ((void (*)(s32))func_80172644)(arg0);
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            func_80146D90(arg0);
            func_80147AD4(arg0, 0, 0, 0xFFFF4000);
            *(s32 *)(arg0 + 0x50) += *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 0x54) += *(s32 *)(arg0 + 0x14);
            *(s32 *)(arg0 + 0x58) += *(s32 *)(arg0 + 0x18);
            if (*(s32 *)(arg0 + 0x50) > 0xBA000) {
                *(s32 *)(arg0 + 0x50) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x50) < -0xBA000) {
                *(s32 *)(arg0 + 0x50) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x54) > 0xBA000) {
                *(s32 *)(arg0 + 0x54) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x54) < -0xBA000) {
                *(s32 *)(arg0 + 0x54) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x58) > 0xBA000) {
                *(s32 *)(arg0 + 0x58) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x58) < -0xBA000) {
                *(s32 *)(arg0 + 0x58) = -0xBA000;
            }
            *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
            ((void (*)(s32))func_801473EC)(arg0);
        } else {
            doit = 0;
            if (*(s32 *)(arg0 + 0x50) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x50) >= 0) {
                    *(s32 *)(arg0 + 0x50) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x50) < 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x50) += 0x8000;
                    if (*(s32 *)(arg0 + 0x50) >= 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x54) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x54) >= 0) {
                    *(s32 *)(arg0 + 0x54) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x54) < 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x54) += 0x8000;
                    if (*(s32 *)(arg0 + 0x54) >= 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x58) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x58) >= 0) {
                    *(s32 *)(arg0 + 0x58) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x58) < 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x58) += 0x8000;
                    if (*(s32 *)(arg0 + 0x58) >= 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                }
            }
            if (doit != 0) {
                *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
                *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
                *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
                ((void (*)(s32))func_801473EC)(arg0);
            }
            if (!(*(u32 *)(arg0 + 0x44) & 2)) {
                ((void (*)(s32, s32, s32))func_801541D8)(arg0, 0xF, 0x12);
            }
        }
        t = func_8014C050(arg0, 0x3B);
        if (t != 0) {
            func_800CCB78(t);
        }
        if ((*(u16 *)(arg0 + 0x1C8) & 0x1F) == 0) {
            ((void (*)(s32, s32, s32, s32))func_80146994)(0x3C, arg0, 0, 0);
        }
    }
    if (*(s32 *)(arg0 + 0x1B0) != 0) {
        if (*(s32 *)(arg0 + 0x1B0) == 1) {
            func_80154A74(arg0, 0x22);
            func_80154150(arg0, 0xF);
        } else {
            ((void (*)(s32, s32))func_80154274)(arg0, *(s32 *)(arg0 + 0x1B4));
        }
    }
    r = ((s32 (*)(s32))func_80161488)(arg0);
    if (r & 5) {
        *(u32 *)(arg0 + 0x44) &= ~2;
        if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) {
            func_80154150(arg0, 0xE);
        } else {
            func_80154150(arg0, 0x10);
        }
        ((void (*)(s32))func_80146CA0)(arg0);
    }
    if (r == 0) {
        if ((((s32 (*)(s32))func_8014A674)(arg0) != 0) && (((s32 (*)(s32))func_8014E434)(arg0) != 0)) {
            D_80181914[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CC40)(arg0);
        } else if ((((s32 (*)(s32))func_8014A69C)(arg0) != 0) && (((s32 (*)(s32))func_8014E6A0)(arg0) != 0)) {
            D_80181914[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CF8C)(arg0);
        } else {
            ((void (*)(s32))func_801725A4)(arg0);
        }
    }
}
