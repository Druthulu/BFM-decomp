/* func_801380E0 — shared body (overlay slot 0x80128158, h_exact 0f3b7f18). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801380E0(s32 arg0) {
    extern void func_8001931C(s32);
    extern void func_8001AAD0(s32, s32);
    extern s32 func_8001B22C(void);
    extern void func_80029124(s32, s32);
    extern s32 func_800CF864(s32, s32);
    extern void func_80138AB4(s32, s32);
    extern s32 func_80138C60(s32, s32);
    extern void func_80138D58(s32, s32);
    extern s32 func_80138DE0(u8 *arg0, u8 arg1, s32 arg2);
    extern void func_801391F0(s32, s32);
    extern void func_80139220(s32, s32);
    extern void func_80139788(s32);
    extern void func_80139914(s32);
    extern void func_80139A8C(s32);
    extern void func_80139B18(s32);
    extern s16 D_8012752C;
    extern s32 D_80127530[];

    u16 *p;
    s32 base;
    s32 cont;
    u32 cmd;
    s32 sub;
    s32 pc;
    s32 t;
    s32 f;
    s32 f0;
    s32 q18;
    s32 q19;
    s32 q20;
    u32 idx;
    s16 *snd;

    t = *(u8 *)(arg0 + 0xC);
    if (t != 0) {
        *(u8 *)(arg0 + 0xC) = t - 1;
        goto done;
    }

    for (;;) {
        cont = 0;
        snd = &D_8012752E;
        if (*(s32 *)(arg0 + 8) & 0x400) {
            base = D_80127530[*(u16 *)(arg0 + 0x4A)];
            p = (u16 *)(arg0 + 0x44);
        } else {
            p = (u16 *)(arg0 + 0x10);
            base = *(s32 *)(arg0 + 0);
        }
        pc = *p;
        cmd = *(u8 *)(pc + base);
        sub = *(u8 *)(pc + base + 1);

        if (cmd >= 0x20) {
            cont = ((s32 (*)(s32, s32, s32))func_80138DE0)(arg0, cmd, sub);
            if (!(*(s32 *)(arg0 + 8) & 0x80220)) {
                cont = 0;
            }
        } else if (cmd != 0) {
            switch (cmd) {
            case 10:
                func_80139220(arg0, cmd);
                *p += 1;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) & ~0x80000;
                break;

            case 7:
                if (*(s32 *)(arg0 + 8) & 0x10000) {
                    cont = 1;
                } else {
                    *(s16 *)(arg0 + 4) = 3;
                }
                *p += 1;
                break;

            case 8:
                func_801391F0(arg0, cmd);
                *p += 1;
                break;

            case 1:
                *(u8 *)(arg0 + 0x23) = sub;
                cont = 1;
                *p += 2;
                break;

            case 2:
                *(u8 *)(arg0 + 0x22) = sub;
                *(u8 *)(arg0 + 0x20) = *(u8 *)(*p + base + 2);
                *p += 3;
                if (func_80138C60(arg0, cmd) == 0) {
                    func_80139914(arg0);
                    return;
                }
                *(s16 *)(arg0 + 4) = 9;
                if (*(u8 *)(base + *p) == 5) {
                    *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4000;
                    *p += 1;
                }
                break;

            case 22:
                *(s32 *)(arg0 + 8) = (*(s32 *)(arg0 + 8) & ~0x20) | 0x4001;
                cont = 1;
                *p += 1;
                break;

            case 5:
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4000;
                cont = 1;
                *p += 1;
                break;

            case 4:
                *(u8 *)(arg0 + 0xD) = sub;
                cont = 1;
                *p += 2;
                break;

            case 3:
                if (*(s32 *)(arg0 + 8) & 0x20000) {
                    cont = 1;
                    *p += 2;
                } else {
                    *(s16 *)(arg0 + 4) = 0xB;
                    *(u8 *)(arg0 + 0xD) = sub;
                    *(s32 *)(arg0 + 8) = (*(s32 *)(arg0 + 8) | 0x8000) & ~0x20;
                }
                break;

            case 6:
                *(s16 *)(arg0 + 4) = 4;
                *p += 1;
                break;

            case 11:
                if ((*snd != 0) || (*(s32 *)(arg0 + 8) & 0x20)
                    || (func_800CF864(pc, cmd) == 0)) {
                    cont = 1;
                    *p += 4;
                } else {
                    snd[-1] = *(u8 *)(*p + base + 2) + (*(u8 *)(*p + base + 3) << 8);
                    *p += 4;
                    *(s32 *)(arg0 + 8) = (*(s32 *)(arg0 + 8) & ~0x60020) | 0x10000;
                    if (snd[-1] != 0) {
                        func_8001AAD0(sub & 0x7F, snd[-1]);
                        if (sub & 0x80) {
                            *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x40000;
                        }
                        if ((*(u8 *)(base + *p) == 2) || (*(s32 *)(arg0 + 8) & 0x40000)) {
                            cont = 1;
                        } else {
                            *(s16 *)(arg0 + 4) = 0x10;
                        }
                        if (func_8001B22C() == 0) {
                            f = *(s32 *)(arg0 + 8);
                            if (f & 1) {
                                func_8001931C(f);
                            } else {
                                *(s32 *)(arg0 + 8) = (f & ~0x10000) | 0x20020;
                                func_80139788(f);
                            }
                            *(s16 *)(arg0 + 4) = 2;
                        }
                    } else {
                        cont = 1;
                    }
                }
                break;

            case 12:
                *(s16 *)(arg0 + 4) = 6;
                *(u8 *)(arg0 + 0x21) = 2;
                *p += 1;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4300;
                break;

            case 13:
                *(s16 *)(arg0 + 4) = 6;
                *(u8 *)(arg0 + 0x21) = 3;
                *p += 1;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x4300;
                break;

            case 9:
                func_80138D58(arg0, sub);
                cont = 1;
                *p += 2;
                break;

            case 14:
                *(s16 *)(arg0 + 4) = 8;
                *(u16 *)(arg0 + 0x44) = 0;
                func_80138AB4(arg0, cmd);
                *p += 1;
                break;

            case 15:
                *(u16 *)(arg0 + 0x44) = 0;
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x400;
                cont = 1;
                *p += 1;
                break;

            case 16:
                func_80029124(sub | (*(u8 *)(*p + base + 2) << 8), 1);
                cont = 1;
                *p += 3;
                break;

            case 17:
                func_80029124(sub | (*(u8 *)(*p + base + 2) << 8), 0);
                cont = 1;
                *p += 3;
                break;

            case 18:
                if (((u8(*)(s32, s32))func_80029178)(sub | (*(u8 *)(*p + base + 2) << 8), cmd)) {
                    q18 = *p;
                    *p = *(u8 *)(q18 + base + 3) + (q18 + 4);
                } else {
                    *p = *p + 4;
                }
                cont = 1;
                break;

            case 19:
                if (!((u8(*)(s32, s32))func_80029178)(sub | (*(u8 *)(*p + base + 2) << 8), cmd)) {
                    q19 = *p;
                    *p = *(u8 *)(q19 + base + 3) + (q19 + 4);
                } else {
                    *p = *p + 4;
                }
                cont = 1;
                break;

            case 20:
                if (!(*(s32 *)(arg0 + 8) & 0x20000)) {
                    q20 = *p + base;
                    *(u16 *)(arg0 + 0xE) = *(u8 *)(q20 + 1) + (*(u8 *)(q20 + 2) << 8);
                }
                cont = 1;
                *p += 3;
                break;

            case 21:
                if (*(u16 *)(arg0 + 0xE) != 0) {
                    *(s16 *)(arg0 + 4) = 0xF;
                } else {
                    cont = 1;
                }
                *p += 1;
                break;

            case 23:
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 2;
                cont = 1;
                *p += 1;
                break;

            case 24:
                *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 8) | 0x80000;
                cont = 1;
                *p += 1;
                break;

            case 25:
                *p += 1;
                if ((*(s32 *)(arg0 + 8) & 0x10000) && (D_8012752C != 0)) {
                    *(s16 *)(arg0 + 4) = 0x10;
                } else {
                    cont = 1;
                }
                break;

            default:
                *p = pc + 1;
                cont = 1;
                break;
            }
        } else {
            f0 = *(s32 *)(arg0 + 8);
            if (f0 & 0x400) {
                idx = *(u16 *)(arg0 + 0x4A);
                *(s32 *)(arg0 + 8) = f0 & ~0x400;
                if (idx < 3) {
                    *(u16 *)(arg0 + 0x4A) = idx + 1;
                }
            } else if (f0 & 0x2000) {
                *(s16 *)(arg0 + 4) = 0xD;
                return;
            } else {
                *(s16 *)(arg0 + 4) = 0xA;
                return;
            }
        }

        if (cont == 0) {
            break;
        }
    }

    if (*(u8 *)(arg0 + 0xC) == 0) {
        *(u8 *)(arg0 + 0xC) = *(u8 *)(arg0 + 0xD);
    }
done:
    func_80139A8C(arg0);
    func_80139B18(arg0);
}
