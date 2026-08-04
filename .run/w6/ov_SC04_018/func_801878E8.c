extern s16 D_800B9A02;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern s16 D_80115126;
extern u16 D_80115112;
extern u16 D_8011511A;
extern u8 D_80115138[];
extern u8 D_80115148[];
extern s32 D_80115130;
extern u8 D_800B9A15;

extern s16 D_801E7708;
extern u16 D_801E770C;
extern s16 D_801E7710;
extern s32 D_801E7700;
extern s32 D_801E7704;
extern s16 D_801E7790;
extern s16 D_801E7794;
extern s16 D_801E7798;
extern s16 D_801E779C;
extern s16 D_801E77A0;
extern s16 D_801E77A4;
extern s16 D_801E77A8;
extern s16 D_801E77AC;
extern s32 D_801E7778;
extern s16 D_801E7030;

extern s32 D_801EC928;
extern s32 D_801E930C;
extern s32 D_801E9968;
extern s32 D_801B9410;
extern u8 D_801B94A4[];
extern s32 D_801B946C[];
extern s32 resLoad_lastId;

extern s32 rand(void);
extern int func_8001AAA0(void);
extern s32 func_800149E0(s32 a0);
extern void func_80029124(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80137B80(void);
extern s32 func_801376E8(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_80139A68(s32 a0, u16 a1);
extern s32 func_801399F0(s32 a0);
extern s16 func_8014168C(s16 a0);
extern s32 func_8017ADE8(s32 a0);
extern void func_80188778(void);
extern s32 func_80189540(s32 a0, s16 a1);
extern s16 func_80189E54(s32 a0);

void func_801878E8(void) {
    s32 s0;
    s32 pad[2];
    (void)&pad;

    D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];

    if (D_80115126 == 4) {
        if (func_801399F0(D_801E7704) != 0) {
            if (D_80115148[0] == 0) {
                if (D_801E7700 == (s32)&D_801EC928) {
                    D_801E7708 = 0x60;
                    D_801E7710 = 0;
                    D_801E770C = 0;
                    D_801E7700 = 0;
                    if (resLoad_lastId == 0x16) {
                        D_801E7790 = 1;
                        ((s32 (*)(s32))func_8001AAA0)(0x35);
                    } else {
                        D_801E7790 = 0;
                    }
                    D_80115112 = 6;
                } else {
                    D_80115112 = D_80115112 - 1;
                }
            } else {
                D_801E7700 = 0;
                func_8017ADE8(0x12);
                func_8002D4C8(0x46F, 0);
                D_8011511A = 0;
                D_80115112 = D_80115112 - 1;
            }

            if (D_801E7700 != 0) {
                D_80115130 = D_801E7700;
                func_80139954();
                D_801E7704 = func_801376E8(D_801E7700, (s32)&D_801B9410);
            }
        }
    } else if (D_80115126 == 5) {
        if (D_801E7700 != 0) {
            if ((D_801E77AC = func_801399F0(D_801E7704)) != 0) {
                D_801E7700 = 0;
            }
        } else if ((func_800149E0(0) & 0x50) != 0 || D_801E77AC > 0) {
            switch (D_801E7794) {
            case 0:
                D_801E7794 = -1;
                break;

            case 1:
                if (D_801E77AC < 0) {
                    D_801E7700 = (s32)&D_801E930C;
                } else if (D_801E77AC == 1) {
                    u16 *p = &D_80115112;
                    D_801E7030 = 1;
                    func_80139954();
                    D_800B9A15 = 0;
                    *p = *p + 1;
                } else {
                    D_801E7794 = -2;
                }
                break;

            case 2:
                D_801E77A8 = 0;
                D_801E7798 = 0;
                /* fallthrough */
            case 5:
            case 6:
                D_801E7794 = ((u16)D_801E7794 + 1) | 0x100;
                break;

            case 3:
                if (D_801E77AC == 1) {
                    D_801E7794 = (u16)D_801E7794 + 1;
                    if (D_801E77A8 == 0) {
                        if (func_80189E54(-0xA) != 0) {
                            func_8002D4C8(0x472, 0);
                            D_801E7794 = 0x10C;
                            break;
                        }
                        func_8002D4C8(0x5EE, 0);
                        D_801E7798 = 0;
                        D_801E77A8 = 0;
                        D_801E779C = rand() % 9 + 3;
                        func_80139A68(D_801E779C, 0);
                    } else {
                        func_80139A68(D_801E779C, 0);
                        D_801E7794 = 0x106;
                        break;
                    }
                }
                D_801E7794 = ((u16)D_801E7794 + 1) | 0x100;
                break;

            case 4:
            case 12:
            case 13:
                if (D_801E7798 != 0) {
                    func_80189E54(D_801E7798);
                    func_8002D4C8(0x5EE, 0);
                }
                D_801E7794 = -1;
                break;

            case 7:
                D_801E77A4 = (u16)D_801E77AC - 1;
                D_801E77A0 = rand() % 13 + 1;
                func_80139A68(D_801E77A0, 0);
                D_801E7794 = ((u16)D_801E7794 + 1) | 0x100;
                break;

            case 8:
            case 9:
                if (D_801E779C == D_801E77A0) {
                    D_801E77A0 = rand() % 13 + 1;
                    func_80139A68(D_801E77A0, 0);
                    D_801E7794 = 0x109;
                    break;
                }
                if (D_801E77A4 == 0 ? D_801E779C < D_801E77A0 : D_801E77A0 < D_801E779C) {
                    if (D_801E7798 == 0) {
                        D_801E7798 = 0xA;
                    }
                    D_801E7798 = (u16)D_801E7798 * 2;
                    func_80139A68(D_801E7798, 0);
                    func_8002D4C8(0x5EE, 0);
                    if (D_801E7798 >= 0x2800) {
                        func_80029124(0x11A, 1);
                        D_801E7794 = 0x10D;
                        *(s32 *)(D_801E7778 + 4) = (s32)&D_801E9968;
                    } else {
                        s32 r;
                        D_801E77A8 = (u16)D_801E77A8 + 1;
                        s0 = D_801B94A4[D_801E77A8];
                        r = rand() % (9 - s0 * 2);
                        s0 = s0 + 3;
                        D_801E779C = r + s0;
                        func_80139A68(D_801E7798, 0);
                        D_801E7794 = 0x10A;
                    }
                } else {
                    D_801E7798 = 0;
                    D_801E77A8 = 0;
                    D_801E7794 = 0x10B;
                    func_8002D4C8(0xC62, 0);
                }
                break;

            case 10:
            case 11:
                D_801E7794 = 0x103;
                break;
            }

            if (D_801E7794 < 0) {
                func_8017ADE8(0xA);
                if (D_801E7794 == -1) {
                    func_8002D4C8(0x46F, 0);
                }
                {
                    u16 *p = &D_80115112;
                    D_801E7794 = 0;
                    *p = *p - 1;
                }
            }
            if (D_801E7794 >= 0x100) {
                s32 t = D_801E7794 & 0xFF;
                D_801E7794 = t;
                D_801E7700 = D_801B946C[t];
            }

            if (D_801E7700 != 0) {
                D_80115130 = D_801E7700;
                func_80139954();
                D_801E7704 = func_801376E8(D_801E7700, (s32)&D_801B9410);
            }
        }
    } else {
        if (D_801E7700 != 0) {
            if (func_801399F0(D_801E7704) != 0) {
                D_801E7700 = 0;
            }
        } else if ((func_800149E0(0) & 0x50) != 0) {
            u16 idx = D_8011511A;
            if (D_80115138[idx] == 8) {
                func_80189540(0xF, func_8014168C((s16)idx));
            }
            if (D_801E7030 != 0) {
                func_80139954();
                D_800B9A15 = 0;
                func_8002D4C8(0x474, 0);
                D_80115112 = D_80115112 + 1;
            } else {
                func_8002D4C8(0x46F, 0);
                D_80115112 = D_80115112 - 1;
            }
        }
    }

    func_80188778();
    func_80137B80();
}
