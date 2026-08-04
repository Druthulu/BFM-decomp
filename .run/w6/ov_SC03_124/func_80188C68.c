/* func_80188C68 - 15-way dispatcher on (s16)(a0 - 1) via jtbl_801E047C.
 * a1 (s16) is the effect/slot value, kept in $s0 across the whole body.
 * Case order in the source follows the emission order of the target .s:
 *   0/1/3/5, 2, 4, 11, 12, 13, 9, 6, 7, 14, 10   (case 8 is absent -> default).
 * The message-and-return-0 exits funnel through one shared tail chain
 * (tail472 / tail_arg0 / tailcall / ret0) = .L801894D0/D4/D8/E0.
 */

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  func_800291B4(s32 arg);
extern void func_800291A0(s32, s32);
extern void func_80029124(s32, s32);
extern void func_80029514(s32);
extern void func_8018654C(void);
extern void func_8018953C(s32);
extern s16  func_8018957C(s32);
extern int  func_800D0F8C(int a0);
extern s32  func_800D0EC4(void);
extern void func_800D0F0C(s32, s32);
extern int  func_800D0FE0(int a0);
extern void func_800D128C(s32, s32);
extern s32  func_8017ADE8(s32 a0);
extern void func_80139A44(s32, s32);
extern void func_80139A68(s32, s32);

extern u16 D_8011511A;
extern s16 D_801E1C88;
extern u8  D_8011514E;
extern s16 D_8011514C;
extern s16 D_80115126;
extern u8  D_80115148[];
extern u16 D_80115112;
extern s32 D_801E2358;
extern u8 *D_801E2354;
extern u8 *D_801E234C;
extern u8  D_801E2410[];
extern s16 D_800A6586[];
extern s16 D_8010EDEC;
extern s16 D_8010EDEE;
extern u8  D_8010EDF1;
extern u8  D_8010EDF2;
extern s16 D_801E23E4;
extern s16 D_801E23EC;
extern s32 D_801DE7D8[];
extern s32 D_801DE908[];
extern s32 D_801E4160;
extern s32 D_801E40FC;
extern s32 D_801E40C4;
extern s32 D_801E4488;
extern s32 D_801E73C0;
extern s8  D_801BCB68[];
extern s32 *D_801E23CC[];

s32 func_80188C68(s32 a0, s16 a1) {
    s16 sel = a0 - 1;
    s32 msg;
    s32 arg;

    switch (sel) {
    case 0:
    case 1:
    case 3:
    case 5:
        if (a1 == 2) {
            goto ret_neg1;
        }
        func_8002D4C8(0x46F, 0);
        D_8011511A = a1 + 1;
        return 0;

    case 2:
        if (a1 == 2) {
            goto ret_neg1;
        }
        D_8011511A = 2;
        msg = 0x46F;
        goto tail_arg0;

    case 4:
        if (a1 == 1) {
            D_801E1C88 = 1;
            func_8002D4C8(0x474, 0);
        ret_neg1:
            return -1;
        }
        if (a1 == 3) {
            goto ret_neg1;
        }
        func_8002D4C8(0x46F, 0);
        if (a1 != 0) {
            D_8011511A = a1;
            return 0;
        }
        D_8011511A = 2;
        return 0;

    case 11:
        D_8011511A = 3;
        *(s16 *)&D_8011514E = 0;
        msg = 0x46F;
        arg = 0;
        goto tailcall;

    case 12: {
        u8 b = D_801E2354[a1];
        s32 s2 = b + 0x62;
        s32 f = func_800291B4(s2) & 0xFF;

        __asm__ __volatile__("" : "=r"(f) : "0"(f));
        if ((f & 0xF0) != 0x80) {
            goto tail472;
        }
        if (func_8018957C(-D_800A6586[b]) != 0) {
        fail3:
            func_8018953C(3);
            msg = 0x472;
            goto tail_arg0;
        }
        func_800291A0(s2, f | 0x40);
        func_8018654C();
        {
            u8 *p = (u8 *)&D_8011514C;
            s16 d;
            __asm__ __volatile__("" : "=r"(p) : "0"(p));
            d = (s8)p[0] - (s8)p[-0xA];
            if (d >= 6) {
                p[-0xA] = p[0] - 5;
            } else if (d < 0) {
                p[-0xA] = p[0];
            }
        }
        func_8018953C(1);
        msg = 0x5EE;
        goto tail_arg0;
    }

    case 13: {
        s32 b = D_801E2410[a1] + 1;
        s32 s2;
        s32 f;
        s2 = b + 0x62;
        f = func_800291B4(s2) & 0xFF;
        __asm__ __volatile__("" : "=r"(f) : "0"(f));
        if ((f & 0xF0) != 0xC0) {
            goto tail472;
        }
        func_8018957C(D_800A6586[b] * 9 / 10);
        func_800291A0(s2, f & 0xBF);
        func_8018654C();
        D_801E2410[a1] = 0xFF;
        func_8018953C(4);
        msg = 0x5EE;
        goto tail_arg0;
    }

    case 9: {
        s32 b = D_801E234C[a1];
        s32 v = b;
        __asm__ __volatile__("" : "=r"(v) : "0"(v));

        if (v < 0x6F) {
            s16 w;
            s16 r;
            s16 x;

            if (v == 0xA) {
                if (func_800D0F8C(0xA) != 0) {
                    msg = 0x472;
                    goto tail_arg0;
                }
            }
            w = func_800D0EC4();
            if (w == 0) {
                func_8018953C(2);
                msg = 0x45F;
                goto tail_arg0;
            }
            x = D_801E23E4;
            if (x != 0) {
                if (D_80115126 == 0) {
                    r = *(s16 *)((u8 *)&D_8010EDEC + b * 0xC) * (100 - x) / 100;
                } else {
                    r = *(u16 *)((u8 *)&D_8010EDEC + b * 0xC) - x;
                }
            } else {
                r = *(u16 *)((u8 *)&D_8010EDEC + b * 0xC);
            }
            if (func_8018957C(-r) != 0) {
                func_8018953C(3);
                msg = 0x472;
                arg = 3;
                goto tailcall;
            }
            func_8002D4C8(0x5EE, 0);
            {
                s32 c = b;
                __asm__ __volatile__("" : "=r"(c) : "0"(c));
                func_800D0F0C(w, c);
                if (c == 0xA) {
                    func_8018654C();
                }
            }
        } else {
            if (func_8018957C(-*(s16 *)((u8 *)&D_8010EDEC + v * 0xC)) != 0) {
                goto fail3;
            }
            func_800D128C(b, 0);
        }
        func_8018953C(1);
        return 0;
    }

    case 6:
    case6:
    {
        s32 s1 = a1 + 0x2F;
        s32 f = func_800291B4(s1) & 0xFF;
        s16 fv;

        if (f == 0) {
            goto tail472;
        }
        fv = *(s16 *)((u8 *)&D_8010EDEE + f * 0xC);
        if (fv == 0 || D_80115126 != *(&D_8010EDF2 + f * 0xC)) {
            func_8018953C(5);
            msg = 0x472;
            goto tail_arg0;
        }
        func_8018957C(fv);
        func_800D0FE0(s1);
        if (f == 0xA) {
            func_8018654C();
        }
        func_8018953C(4);
        msg = 0x5EE;
        goto tail_arg0;
    }

    case 7:
        if (D_80115148[0] != 0) {
            goto case6;
        }
        {
            s32 f = func_800291B4(a1 + 0x2F) & 0xFF;
            s16 rec0;
            s32 p;

            if (f == 0) {
                goto tail472;
            }
            rec0 = *(s16 *)((u8 *)&D_8010EDEC + f * 0xC);
            if (rec0 >= 0) {
                D_801E2358 = (s32)&D_801E4160;
                msg = 0x472;
                goto tail_arg0;
            }
            if (rec0 & 0x4000) {
                p = D_801DE7D8[f];
            } else {
                p = D_801DE908[((s32)*(&D_8010EDF1 + f * 0xC) - 0x14) >> 1];
            }
            D_801E2358 = (s32)&D_801E40FC;
            func_80139A44(p, 0);
            {
                u16 *pc = &D_80115112;
                *pc = *pc + 1;
            }
            goto ret0;
        }

    case 14: {
        s32 s2 = a1 + 0x2F;
        s32 idx = (func_800291B4(s2) & 0xFF) * 0xC;
        u16 rec0 = *(u16 *)((u8 *)&D_8010EDEC + idx);
        s32 rec5 = *(&D_8010EDF1 + idx);

        if (rec0 & 0x4000) {
            s32 c = rec5;
            __asm__ __volatile__("" : "=r"(c) : "0"(c));
            func_80029124(c, 1);
            func_800D0FE0(s2);
            D_801E1C88 = rec5 - 0x1C;
            if (c != 0x1F) {
                return 0;
            }
            func_80029514(0x64);
            func_80029124(0xEB, 1);
            func_80029124(0x91, 1);
            func_800291A0(0xCE, 1);
            return 0;
        }
        func_800D0F0C(s2, rec5);
        return 0;
    }

    case 10:
        if (D_80115126 == 4) {
            if (D_80115148[0] == 0) {
                if (D_801E23CC[a1] != 0) {
                    msg = 0x472;
                    goto tail_arg0;
                }
                if (func_8018957C(D_801BCB68[a1]) != 0) {
                    goto fail3;
                }
                D_801E2358 = (s32)&D_801E73C0;
                D_80115112 = D_80115112 + 1;
                func_80139A68((s16)(a1 + 1), 0);
                msg = 0x5EE;
                goto tail_arg0;
            } else {
                s32 **pp = &D_801E23CC[a1];
                s32 *e = *pp;
                s32 h;

                if (e == 0) {
                    msg = 0x472;
                    goto tail_arg0;
                }
                h = e[1];
                if (h == 0) {
                    msg = 0x472;
                    goto tail_arg0;
                }
                D_801E2358 = h;
                if (e[3] != 0) {
                    ((void (*)(void))e[3])();
                }
                func_8017ADE8((*pp)[2]);
            }
        } else {
            s32 *e = D_801E23CC[a1];

            if (e == 0) {
                msg = 0x472;
                goto tail_arg0;
            }
            func_8017ADE8(D_801E23CC[a1][2]);
            D_801E2358 = e[1];
            D_801E23EC = 0;
            if (D_801E2358 == (s32)&D_801E40C4) {
                D_801E23EC = 1;
            }
            if (D_801E2358 == (s32)&D_801E4488) {
                D_801E23EC = 2;
            }
        }
        func_8002D4C8(0x45D, 0);
        D_80115112 = D_80115112 + 1;
        return 0;
    }

    goto ret0;

tail472:
    msg = 0x472;
tail_arg0:
    arg = 0;
tailcall:
    func_8002D4C8(msg, arg);
ret0:
    return 0;
}
