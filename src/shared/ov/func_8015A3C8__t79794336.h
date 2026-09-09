/* func_8015A3C8 — shared body (overlay slot 0x80128158, h_text 79794336). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8015A3C8(arg0)
s32 arg0;
{

    extern void (*D_80181160[])(void *);

    extern s32 D_800D5428;
    extern u8 D_801810E4[];
    s32 min;
    s32 grav;
    s32 hi;
    s32 t;
    s32 lo1;
    s32 lo2;
    s32 sv;
    u8 *p;

    p = D_80078E78;
    if (currentLocationId == 0x302A) {
        min = -0xC0000;
        grav = -0x4000;
        hi = 0;
    } else {
        min = -0xB0000;
        grav = -0x1000;
        hi = 0;
    }

    if (func_80149D9C(arg0) != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149FA8)(arg0);
        return;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (((s32 (*)(s32))func_80161B84)(arg0) != 0) {
        return;
    }
    if (((s32 (*)(s32))func_80161B18)(arg0) != 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D5428) {
        if (func_8014A048(arg0) != 0) {
            D_80181160[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8014A218)(arg0);
            return;
        }
    }
    if (((s32 (*)(s32))func_80161BE0)(arg0) != 0) {
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 2:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_80181160[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_80181160[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
            return;
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
            D_80181160[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_800CCCC0)(arg0);
            return;
        }
        break;
    }

    if (func_80149CD4(arg0) != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015E880)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801488A8)(arg0) == 0) {
        sv = *(s32 *)(arg0 + 0x2C);
        D_80181160[*(u16 *)arg0]((void *)arg0);
        func_8014C010(arg0, 1);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        if (func_8015ABD4(arg0, sv, min) != 0) {
            func_8015AC48(arg0);
        }
        return;
    }

    ((void (*)(s32))func_80148AFC)(arg0);
    if (*(u32 *)(arg0 + 0x44) & 0x200) {
        if (*(s32 *)(arg0 + 0x23C) == 0) {
            func_80154150(arg0, 0xA);
            func_80154A74(arg0, 0x1C);
        }
        ((void (*)(s32, s32))func_80146DB8)(arg0, (s32)&(*(s32 *)&D_801810E4));
        func_80147AD4(arg0, 0, 0, 0);
    } else {
        switch (*(u8 *)(arg0 + 0xA9)) {
        case 0x41:
            func_80147AD4(arg0, 0, 0, grav);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                if (((s32 (*)(s32))func_801487F4)(arg0) & 4) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                } else if (func_8016F1C4() == 0) {
                    if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                            *(s32 *)(arg0 + 0x2C) = -0x40000;
                        }
                    } else if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                            *(s32 *)(arg0 + 0x2C) = -0x80000;
                        }
                    }
                }
                if (*(s32 *)(arg0 + 0x2C) < min) {
                    *(s32 *)(arg0 + 0x2C) = min;
                }
                if (*(s32 *)(arg0 + 0x2C) >= hi) {
                    *(s32 *)(arg0 + 0x2C) = hi;
                }
                lo1 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo1) {
                    func_80154150(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))func_801541D8)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    func_80154150(arg0, 6);
                }
            }
            break;
        case 0x53:
        case 0x73:
            *(s32 *)(arg0 + 0x2C) = (min * (((s32 (*)(s32))func_80148824)(arg0) & 0xFF)) / 127;
            if (func_8016F1C4() == 0) {
                if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                        *(s32 *)(arg0 + 0x2C) = -0x80000;
                    }
                }
                if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x2C) < min) {
                *(s32 *)(arg0 + 0x2C) = min;
            }
            if (*(s32 *)(arg0 + 0x2C) >= hi) {
                *(s32 *)(arg0 + 0x2C) = hi;
            }
            func_80147A84(arg0);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                lo2 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo2) {
                    func_80154150(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))func_801541D8)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    func_80154150(arg0, 6);
                }
            }
            break;
        }
    }

    ((void (*)(s32))func_801473EC)(arg0);
    if ((min >= *(s32 *)(arg0 + 0x2C)) && !(D_800B99DA & 7)) {
        func_8014C010(arg0, 2);
    }
    if (((s32 (*)(s32))func_8014D738)(arg0) != 0) {
        D_80181160[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015C6E0)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_8014E934)(arg0) != 0) {
        ((void (*)(s32))func_80155440)(arg0);
        func_80154150(arg0, 0x12);
        func_80154A74(arg0, 0x17);
        *(s32 *)(arg0 + 0x23C) = 1;
    } else {
        if (*(s32 *)(arg0 + 0x23C) != 0) {
            func_801553C0(arg0);
            func_80154150(arg0, 6);
            func_80154A74(arg0, 0x21);
        }
        *(s32 *)(arg0 + 0x23C) = 0;
    }
    if (((s32 (*)(s32))func_80161278)(arg0) == 0) {
        if (*(u16 *)(arg0 + 0xB8) & 0x2000) {
            func_80161C24(arg0, *(u16 *)(arg0 + 0x16E));
        }
        ((void (*)(s32))func_80172608)(arg0);
        ((void (*)(s32))func_801483E8)(arg0);
    }
}
