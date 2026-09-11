#include "common.h"

#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void GsMapModelingData(u32 *p);
extern void func_8017D7B0();
extern void func_801A1E94(void);
extern void func_801A3B08(s32 a0);
extern s32 func_801A44C4(s32 a0);
extern void func_801A1E74(s32 a0);

extern s32 D_801AFBE4;
extern s32 D_801F871C;
extern s32 D_801B6E94[0x11];
extern s32 D_801F86D0[0x11];
extern s32 D_801B872C;
extern s32 D_801AFC18[1];
extern u16 D_801F885C;
extern u16 D_801F8718;
extern s16 D_801F8714;

void func_801A0230(s32 a0) {
    s32 v0;
    s32 v1;
    register s32 i __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    s32 *p;

    if (func_8012C354(a0, (s32) &D_801AFBE4) != 0) {
        v0 = *(s32 *)(a0 + 0x20);
        v1 = *(u16 *)(v0 + 0x2C);
        D_801F871C = a0;
        v1 |= 0x10;
        *(u16 *)(v0 + 0x2C) = v1;
        *(u16 *)(a0 + 0xE) = 0;
        *(u16 *)(a0 + 0x6) = 0;
        *(s16 *)(a0 + 0xA) = -0x240;

        for (i = 0; i < 0x44; i += 4) {
            *(s32 *)((u8 *)D_801F86D0 + i) = *(s32 *)((u8 *)D_801B6E94 + i);
        }

        for (p = &D_801B872C; *p != 0; p++) {
            GsMapModelingData((u32 *)(*p + 4));
        }

        v0 = func_801A44C4(a0);
        *(s32 *)(a0 + 0xD8) = v0;
        func_8012C588(0x3BB, a0);

        v1 = *(s32 *)(a0 + 0xC4);
        D_801F885C = 0;
        *(u8 *)(a0 + 0xC0) = 1;
        *(s16 *)(a0 + 0xAE) = -1;
        *(s32 *)(a0 + 0xB4) = 0;
        *(s32 *)(a0 + 0xBC) = (s32) D_801AFC18;
        *(u8 *)(a0 + 0xC1) = 0;
        v1 |= 2;
        *(s32 *)(a0 + 0xC4) = v1;
        v0 = func_80143970(a0);
        *(s32 *)(a0 + 0xD0) = v0;

        D_801F8718 = 0xC62;
        D_801F8714 = 0xC62;
        func_801A3B08(a0);
        func_8017D7B0();

        if (*(s32 *)(a0 + 0x64) != 0) {
            ((void (*)(s32))func_801A1E94)(a0);
        } else {
            func_801A1E74(a0);
        }
    }
}


extern void func_801A4328(s32 a0);
extern void func_801A34C4(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801EEEA0;

void func_801A03A4(s32 a0) {
    func_801A4328(2);
    *(u16 *)(a0 + 0x5C) &= 0xDFFF;
    func_801A34C4(a0);
    func_8012A828(a0, &D_801EEEA0);
    func_8012AD44((s32 *)a0, 2);
}


INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A00D8);

#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B200(u8 *a0);
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern void func_8013240C(s32 a0);
extern void func_801A3180(s32 a0, s32 a1);
extern void func_801A3624(s32 a0, u16 *a1, s32 a2);
extern void func_801A36A8(s32 a0);
extern void func_801A4328(s32 a0);

extern u16 D_8019FF8A;
extern s32 D_801AFBA4;
extern s32 D_801AFBB4;
extern s16 D_801AFBB8;
extern s32 D_801B6EC0;
extern s32 D_801B6EC4;
extern s32 D_801B6EC8;
extern s32 D_801B872C;
extern s32 D_801EEAC8;
extern s32 D_801EF270;
extern s32 D_801EF3B8;
extern s32 D_801EF6D0;
extern s32 D_801EF7D8;
extern s16 D_801F8714;
extern s32 D_801F8734;
extern s16 D_801F873A;
extern s32 D_801F8740;
extern s32 D_801F86FC;
extern s32 D_801F8700;
extern s32 D_801F8704;
extern u16 D_801F885C;

void func_801A0400(s32 arg0) {
    s32 *p;
    s32 v0;
    s32 v1;
    s32 r6;
    s32 rt;
    s32 flag;
    s16 sv0;
    s16 sv3;
    s16 sv5;
    s16 sv10;
    s16 sw5;
    s16 sw10;
    s32 d10;
    s32 q10;

    flag = 1;
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        sv0 = *(s16 *)(arg0 + 0xA);
        *(s16 *)(arg0 + 0xA) = (sv0 < -0x220) ? sv0 + 2 : -0x220;
        if (*(s32 *)(arg0 + 0x94) == 0x10) {
            goto incr;
        }
        break;
    case 1:
        *(u16 *)(arg0 + 0xA) -= 6;
        if (*(s32 *)(arg0 + 0x94) != 0x24) {
            break;
        }
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        func_8002D4C8(0xBA5, 0);
        break;
    case 2:
        *(u16 *)(arg0 + 0xA) += 0xA;
        if (*(s32 *)(arg0 + 0x94) == 0x28) {
            D_801B6EC4 = 0x1000000;
            D_801B6EC8 = 0x1000000;
            D_801F885C = 0x70;
            D_801B6EC0 = D_801B872C;
            D_8019FF8A |= 4;
        }
        if (*(s32 *)(arg0 + 0x94) == 0x30) {
            goto incr;
        }
        break;
    case 3:
        sv3 = *(s16 *)(arg0 + 0xA);
        *(s16 *)(arg0 + 0xA) = (sv3 < -0x23F) ? -0x240 : sv3 - 3;
        if (*(s32 *)(arg0 + 0x94) == 0x3C) {
            goto incr;
        }
        break;
    case 4:
        if (*(s16 *)(arg0 + 0x98) == 0) {
            func_801A3180(arg0, 0x100);
            if (!(D_8019FF8A & 0x40)) {
                *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            }
        }
        func_801A36A8(arg0);
        break;
    case 5:
        sv5 = *(s16 *)(arg0 + 0xA);
        if (sv5 < -0x200) {
            sw5 = sv5 + 8;
            *(s16 *)(arg0 + 0xA) = sw5;
            if (sw5 < -0x200) {
                break;
            }
        }
        func_8012A828(arg0, &D_801EF270);
        func_8012B200((u8 *) arg0);
        func_8012B178(arg0, -0x60000);
        goto incr;
    case 6:
        flag = 0;
        if ((u32) (*(s32 *)(arg0 + 0x94) - 8) < 0x19) {
            r6 = func_8012B8A4((s16 *) arg0);
            *(s16 *)(arg0 + 0xFE) = r6;
            func_801A3624((s16) r6, (u16 *) (*(s32 *)(arg0 + 0x20) + 0x12), 0x20);
            func_8012AD80(arg0);
            if (*(s32 *)(arg0 + 0x94) == 0x1B) {
                func_8012AD80(arg0);
            }
        }
        if (*(s32 *)(arg0 + 0x94) == 0x1C) {
            func_8012C658(0xD, 2, arg0);
        }
        if (*(s16 *)(arg0 + 0x98) != 0) {
            break;
        }
        *(s32 *)(arg0 + 0x1C) = 0x10;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;
    case 7:
        flag = 1;
        if (func_8012BEE8(arg0) == 0) {
            break;
        }
        func_8012A828(arg0, &D_801EF3B8);
        goto incr;
    case 8:
        flag = 0;
        v1 = *(s32 *)(arg0 + 0x94);
        switch (v1) {
        case 0xB:
            v0 = 0;
            break;
        case 0x17:
            v0 = 1;
            break;
        default:
            v0 = -1;
            break;
        }
        if (v0 >= 0) {
            func_8012C658(0xD, v0, arg0);
        }
        if (*(s16 *)(arg0 + 0x98) != 0) {
            break;
        }
        func_8012A828(arg0, &D_801EF6D0);
        func_8012B200((u8 *) arg0);
        goto incr;
    case 9:
        flag = 0;
        func_8012AD80(arg0);
        if (*(s32 *)(arg0 + 0x94) == 8) {
            func_8012B178(arg0, 0x7C000);
            func_8002D4C8(0xBA6, 0);
        }
        if (*(s32 *)(arg0 + 0x94) == 0x1C) {
            func_8012B200((u8 *) arg0);
        }
        if (*(s16 *)(arg0 + 0x98) != 0) {
            break;
        }
        func_80132288(&D_801F8734, &D_801AFBB4, D_801B872C);
        *(s32 *)(arg0 + 0x18) = 0;
        *(s32 *)(arg0 + 0x10) = 0;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;
    case 10:
        do { p = &D_801F8734; } while (0);  // !FAKE: do-while — a LOOP-note scheduling barrier (sched.c:2058-2074; P36 R7)
        func_8013240C((s32) p);
        d10 = D_801AFBB8;
        q10 = 0x70 / d10;
        D_801F885C = ((d10 - D_801F873A) + 1) * q10 & 0xFFFE;
        if (D_801F8740 & 0x4000) {
            D_801B6EC0 = D_801F86FC;
            D_801B6EC4 = D_801F8700;
            D_801B6EC8 = D_801F8704;
            D_8019FF8A &= 0xFFFB;
        }
        sv10 = *(s16 *)(arg0 + 0xA);
        if (sv10 >= -0x23F) {
            sw10 = sv10 - 2;
            *(s16 *)(arg0 + 0xA) = sw10;
            if (sw10 >= -0x23F) {
                break;
            }
        }
        *(s16 *)(arg0 + 0xA) = -0x240;
        func_80132288(p, &D_801AFBA4, D_801B872C);
        func_8012A828(arg0, &D_801EF7D8);
    incr:
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;
    case 11:
        func_8013240C((s32) &D_801F8734);
        if (*(s16 *)(arg0 + 0x98) != 0) {
            break;
        }
        *(u16 *)(arg0 + 0x5C) |= 0x2000;
        func_8012A828(arg0, &D_801EEAC8);
        *(s32 *)(arg0 + 0x1C) = (s16) (D_801F8714 / 79) + 0x18;
        func_8012B200((u8 *) arg0);
        func_8012AD44((s32 *) arg0, 1);
        func_801A4328(0);
        break;
    }
    if (flag) {
        rt = func_8012B8A4((s16 *) arg0);
        *(s16 *)(arg0 + 0xFE) = rt;
        func_801A3624((s16) rt, (u16 *) (*(s32 *)(arg0 + 0x20) + 0x12), 0x40);
    }
}


extern void func_801A4328(s32 a0);
extern void func_8017F880(void);
extern void func_801A34C4(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801EF088;
extern u16 D_8019FF8A;

void func_801A09E4(s32 a0) {
    s32 v1;
    s32 v0;
    s32 v2;

    func_801A4328(3);
    func_8017F880();
    func_801A34C4(a0);
    func_8012A828(a0, &D_801EF088);
    *(s32 *)(a0 + 0xCC) = func_8012C658(0x32A, 0, a0);

    v1 = *(volatile s32 *)(a0 + 0xCC);
    D_8019FF8A &= 0xFEFF;
    if (v1 != 0) {
        D_8019FF8A |= 2;
    }

    v0 = D_8019FF8A | 0x80;
    v2 = *(u16 *)(a0 + 0x5C) & 0xDFFF;
    D_8019FF8A = v0;
    *(u16 *)(a0 + 0x5C) = v2;
    func_8012AD44((s32 *)a0, 3);
}


extern void func_801A3B08(s32 a0);
extern void func_801A3180(s32 a0, s32 a1);
extern void func_801A3B18(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern u16 D_8019FF8A;
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801EEAC8;
extern s16 D_801F8714;
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801A4328(s32 a0);
extern void func_8017F418(void);
extern void func_801A36A8(s32 a0);
extern s32 func_8012B8A4(s16 *a0);
extern void func_801A3624(s32 a0, u16 *a1, s32 a2);

void func_801A0A98(s32 arg0)
{
    s32 v0;
    s32 v1;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (*(s16 *)(arg0 + 0x98) != 0) {
            break;
        }
        *(s32 *)(arg0 + 0x1C) = 0x100;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        func_801A3B08(arg0);
        break;
    case 1:
        func_801A3180(arg0, 0x280);
        if (*(s32 *)(arg0 + 0x1C) < 0xF0) {
            func_801A3B18(arg0);
        }
        if (func_8012BEE8(arg0) == 0) {
            break;
        }
        v1 = *(u16 *)(arg0 + 0x34) + 1;
        D_8019FF8A |= 0x100;
        *(u16 *)(arg0 + 0x34) = v1;
        break;
    case 2:
        if (D_8019FF8A & 2) {
            break;
        }
        func_8012A828(arg0, &D_801EEAC8);
        *(s32 *)(arg0 + 0x1C) = (s16)(D_801F8714 / 79) + 0x18;
        func_8012B200((u8 *)arg0);
        func_8012AD44((s32 *)arg0, 1);
        func_801A4328(0);
        func_8017F418();
        v0 = D_8019FF8A & 0xFF7F;
        v1 = *(u16 *)(arg0 + 0x5C) | 0x2000;
        D_8019FF8A = v0;
        *(u16 *)(arg0 + 0x5C) = v1;
        break;
    }
    func_801A36A8(arg0);
    v0 = func_8012B8A4((s16 *)arg0);
    *(s16 *)(arg0 + 0xFE) = v0;
    func_801A3624((s16)v0, (u16 *)(*(s32 *)(arg0 + 0x20) + 0x12), 0x40);
}


extern void func_801A36F0(void *a0);
extern void func_801A34C4(s32 a0);
extern void func_801A4328(s32 a0);
extern void func_8017F9CC(void);
extern void func_8012A828(s32 a0, void *a1);
extern s32 rand(void);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801EEB70;

void func_801A0C58(s32 *a0)
{
    s32 *s0 = a0;
    s32 v0;

    func_801A36F0(s0);
    func_801A34C4((s32)s0);
    func_801A4328(6);
    func_8017F9CC();

    v0 = *(u16 *)((s32)s0 + 0x5C);
    *(u16 *)((s32)s0 + 0x5C) = v0 & 0xDFFF;
    func_8012A828((s32)s0, &D_801EEB70);

    *(u16 *)((s32)s0 + 0x100) = 0;
    *(u16 *)((s32)s0 + 0x102) = rand() & 3;
    func_8012AD44(s0, 4);
}


extern void func_801A36F0(void *a0);
extern void func_801A34C4(s32 a0);
extern void func_801A4328(s32 a0);
extern s16 func_8017F730(void);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801EEB70;
extern s16 D_801F8E98;

void func_801A0CD0(s32 *a0)
{
    s32 *s0;
    u16 v0;

    s0 = a0;
    func_801A36F0(s0);
    func_801A34C4((s32)s0);
    func_801A4328(1);
    func_8017F730();
    v0 = *(u16 *)((s32)s0 + 0x5C);
    *(u16 *)((s32)s0 + 0x5C) = v0 & 0xDFFF;
    func_8012A828((s32)s0, &D_801EEB70);
    D_801F8E98 = 0;
    func_8012AD44(s0, 5);
}


#include "common.h"

/* func_801A0D40 — md_SC07_004 state machine on *(u16 *)(a0 + 0x34).

   Three spellings are load-bearing (byte-proven, do not "clean up"):
     - the 0xA clamps in cases 0 and 5 read the FIELD twice and store in each
       arm (memory operands, not a temp). The register form drops the target's
       `addu $v1,$v0,$zero` cse copy and flips the branch polarity.
     - case 2 reuses the PARAMETER as the 7/8 sfx temp; a separate local is a
       second global allocno and costs a saved $s1 + 16 bytes of frame.
     - case 5's 8/0x20 pick stores in BOTH arms; a temp there splits the
       `0x34`-increment block and loses its cross-jump with case 4.  */

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012B8A4(s16 *a0);
extern void func_8017F418(void);
extern void func_801A3624(s32 a0, u16 *a1, s32 a2);
extern void func_801A3EEC(s32 a0);
extern void func_801A4328(s32 a0);
extern void func_801A108C(s32 arg0);
extern void func_801A1124(s32 a0);
extern void func_801A9AAC(void);
extern s32 func_801A9ADC(void);
extern s32 D_801EF4C0;
extern s32 D_801AFC60;
extern s32 D_801EF5C8;
extern s32 D_801EEAC8;
extern s16 D_801F8714;

void func_801A0D40(s32 a0) {
    s32 v0;
    s32 v1;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (*(s16 *)(a0 + 0xA) >= -0x220) {
            *(s16 *)(a0 + 0xA) = -0x220;
        } else {
            *(s16 *)(a0 + 0xA) = *(s16 *)(a0 + 0xA) + 2;
        }
        if (*(s32 *)(a0 + 0x94) == 0x14) {
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            func_8002D4C8(0xBA5, 0);
        }
        break;
    case 1:
        v0 = *(u16 *)(a0 + 0xA) - 0x10;
        *(s16 *)(a0 + 0xA) = v0;
        if (*(s32 *)(a0 + 0x94) == 0x1A) {
            func_8012C658(0x3A4, *(u16 *)(a0 + 2) == 4, a0);
            *(s32 *)(a0 + 0x1C) = 0x14;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 2:
        if (*(s16 *)(a0 + 0x98) != 0) {
            break;
        }
        if (func_8012BEE8(a0) != 0) {
            func_8012A828(a0, &D_801EF4C0);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            if (*(u16 *)(a0 + 2) == 4) {
                a0 = 8;
                func_801A9AAC();
            } else {
                a0 = 7;
            }
            func_801A3EEC(a0);
        }
        break;
    case 3:
        if (*(s16 *)(a0 + 0x98) == 0) {
            func_8012A828(a0, &D_801AFC60);
            *(s32 *)(a0 + 0x1C) = 0x60;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            break;
        }
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
        if (*(u16 *)(a0 + 2) == 4) {
            func_801A108C(a0);
            func_801A9ADC();
        } else {
            func_801A1124(a0);
        }
        break;
    case 4:
        if (func_8012BEE8(a0) != 0) {
            func_8012A828(a0, &D_801EF5C8);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        } else if (*(u16 *)(a0 + 2) == 4) {
            func_801A108C(a0);
        } else {
            func_801A1124(a0);
        }
        if (*(u16 *)(a0 + 2) == 4) {
            func_801A9ADC();
        }
        break;
    case 5:
        if (*(s16 *)(a0 + 0xA) < -0x240) {
            *(s16 *)(a0 + 0xA) = *(s16 *)(a0 + 0xA) + 1;
        }
        if (*(s16 *)(a0 + 0x98) == 0 && *(s16 *)(a0 + 0xA) >= -0x240) {
            if (*(u16 *)(a0 + 2) == 4) {
                *(s32 *)(a0 + 0x1C) = 8;
            } else {
                *(s32 *)(a0 + 0x1C) = 0x20;
            }
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        if (*(u16 *)(a0 + 2) == 4) {
            func_801A9ADC();
        }
        break;
    case 6:
        v1 = func_8012B8A4((s16 *)a0);
        *(s16 *)(a0 + 0xFE) = v1;
        func_801A3624((s16)v1, (u16 *)(*(s32 *)(a0 + 0x20) + 0x12), 0x40);
        if (func_8012BEE8(a0) != 0) {
            func_8012A828(a0, &D_801EEAC8);
            *(s32 *)(a0 + 0x1C) = (s16)(D_801F8714 / 79) + 0x18;
            func_8012B200((u8 *)a0);
            func_8012AD44((s32 *)a0, 1);
            func_801A4328(0);
            func_8017F418();
            func_801A3EEC(1);
            *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) | 0x2000;
            break;
        }
        if (*(u16 *)(a0 + 2) == 4) {
            func_801A9ADC();
        }
        break;
    }
}


void func_801A108C(s32 arg0)
{
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

    s32 temp;

    temp = *(s32 *)(arg0 + 0x1C);
    if (temp == (temp / 24) * 24) {
        if (*(s16 *)(arg0 + 0x100) == *(s16 *)(arg0 + 0x102)) {
            func_8012C658(0x34, 1, arg0);
        } else {
            func_8012C588(0x34, arg0);
        }
        *(u16 *)(arg0 + 0x100) = *(u16 *)(arg0 + 0x100) + 1;
    }
}


void func_801A1124(s32 a0) {
    s32 v0;
    v0 = *(s32 *)(a0 + 0x1C);
    if ((v0 & 3) == 0) {
        func_8012C588(0x44, a0);
    }
}


#include "common.h"

extern void func_8017F184(void *a0);
extern void func_801A4328(s32 a0);
extern void func_801A36F0(void *a0);
extern void func_801A34C4(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801EECB8;

void func_801A115C(s32 a0) {
    *(u16 *)(a0 + 0x5C) &= 0xDFFF;
    func_8017F184((void *)a0);
    func_801A4328(5);
    func_801A36F0((void *)a0);
    func_801A34C4(a0);
    func_8012A828(a0, &D_801EECB8);
    func_8012AD44((s32 *)a0, 6);
    func_8002D4C8(0xBA5, 0);
}


/* func_801A11D4 - md_SC07_004, 139 ins, 5-case jump-table state tick (jtbl_801A012C).
 *
 * All declarations are the house spellings already used by the neighbour
 * func_801A0A98 in src/md_SC07_004/md_SC07_004.c (law 2), including
 * `extern s16 D_801F8714;` + the `(s16)(D_801F8714 / 79) + 0x18` divide-by-79
 * idiom, which is the byte-identical source of the lhu/sll16/sra16 + magic
 * 0x67B23A55 / mfhi / sra 5 sequence at 801A137C-801A13B0.
 *
 * The ONE fix over the prior draft (.run/wave_ds1/shard54): in case 4 the
 * `*(s16 *)(arg0 + 0xA) = -0x240;` store is BEFORE func_8012A828, not after
 * (§176-A - statement order around the call).  With it before, sched1 puts the
 * `sh $v0, 0xA($s0)` in the jal delay slot and the `addu $a0,$s0,$zero` in the
 * guard's slot; with it after, both slots go to nops and the body drifts +1.
 *
 * §195-D check: the four internal `j` words are masked by match_one, so they
 * were verified by hand against the objdump - 0x5C->0x148, 0x94->0x118,
 * 0x124->0x218, 0x148->0x218, all equal to the target's .L801A131C /
 * .L801A12EC / .L801A13EC offsets.  Every symbol below appears in this
 * function's own relocation lines (law 1c).
 */

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801830D8(s32 a0);
extern void func_8013C9C4(void *a0);
extern s32 D_80186F44;
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801EEAC8;
extern s16 D_801F8714;
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801A4328(s32 a0);
extern void func_8017F418(void);

void func_801A11D4(s32 arg0) {
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        *(u16 *)(arg0 + 0xA) -= 8;
        if (*(s32 *)(arg0 + 0x94) == 0x1A) {
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
        break;
    case 1:
        *(u16 *)(arg0 + 0xA) -= (0x1F - *(s32 *)(arg0 + 0x94)) * 2;
        if (*(s32 *)(arg0 + 0x94) == 0x1E) {
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            func_8002D4C8(0xBA6, 0);
        }
        break;
    case 2:
        if (*(s32 *)(arg0 + 0x94) == 0x28) {
            *(u16 *)(arg0 + 0x98) = 0;
        }
        if (*(s16 *)(arg0 + 0xA) < -0x200) {
            *(s16 *)(arg0 + 0xA) = *(s16 *)(arg0 + 0xA) + 0x18;
            if (*(s16 *)(arg0 + 0xA) < -0x200) {
                break;
            }
        }
        *(s16 *)(arg0 + 0xA) = -0x200;
        *(u16 *)(arg0 + 0x52) = 0;
        func_801830D8(arg0);
        func_8013C9C4(&D_80186F44);
        *(s32 *)(arg0 + 0x1C) = 0x40;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        func_8002D4C8(0xABC, 0);
        break;
    case 3:
        if (func_8012BEE8(arg0) == 0) {
            break;
        }
        *(u16 *)(arg0 + 0x98) = 1;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;
    case 4:
        if (*(s16 *)(arg0 + 0xA) >= -0x23F) {
            *(s16 *)(arg0 + 0xA) = *(s16 *)(arg0 + 0xA) - 4;
        }
        if (*(s16 *)(arg0 + 0x98) != 0) {
            break;
        }
        if (*(s16 *)(arg0 + 0xA) >= -0x23F) {
            break;
        }
        *(s16 *)(arg0 + 0xA) = -0x240;
        func_8012A828(arg0, &D_801EEAC8);
        *(s32 *)(arg0 + 0x1C) = (s16)(D_801F8714 / 79) + 0x18;
        func_8012B200((u8 *)arg0);
        func_8012AD44((s32 *)arg0, 1);
        *(u16 *)(arg0 + 0x108) = 0;
        func_801A4328(0);
        func_8017F418();
        *(u16 *)(arg0 + 0x5C) |= 0x2000;
        break;
    }
}


extern void func_801A4328(s32 a0);
extern void func_8017F928(void);
extern void func_801A36F0(void *a0);
extern void func_801A34C4(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801EF8A0;

void func_801A1400(s32 *a0)
{
    s32 *s0 = a0;
    u16 v0;

    func_801A4328(4);
    func_8017F928();
    func_801A36F0(s0);
    *(u16 *)((s32)s0 + 0x102) = 0;
    func_801A34C4((s32)s0);
    v0 = *(u16 *)((s32)s0 + 0x5C);
    *(u16 *)((s32)s0 + 0x5C) = v0 & 0xDFFF;
    func_8012A828((s32)s0, &D_801EF8A0);
    func_8012AD44(s0, 7);
}


#include "common.h"

extern void func_801A3FB0(void *arg0);
extern void func_801A4008(s32 a0);
extern void func_801A41CC(void);
extern void func_801A417C(s32 arg0);
extern void func_801A4328(s32 a0);
extern void func_801A5414(s32 param_1);
extern void func_801A5654(s32 param_1, s16 param_2, s32 param_3);
extern void func_801A5698(u8 *s2, s32 a1);
extern void func_801A6330(void);
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017F418(void);
extern s32 D_801F8844[];
extern s32 D_801F8858;
extern s16 D_801F8714;
extern s32 D_801EF928;
extern s32 D_801EEAC8;

typedef struct { u8 pad0[0x34]; u16 f34; } S34_801A1470;

void func_801A1470(s32 s0) {
    s32 v0;
    s32 v1;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + 2;
        if (*(s32 *)(s0 + 0x94) == 0xA) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 1:
        *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x10;
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) > 0) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) = *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) - 0x200;
            if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) <= 0) {
                *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) = -1;
            }
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        }
        if (*(s16 *)(s0 + 0x98) != 0) {
            break;
        }
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) >= 0) {
            break;
        }
        func_801A3FB0((void *)s0);
        *(s32 *)(s0 + 0x1C) = 0x20;
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        break;
    case 2:
        if (func_8012BEE8(s0) == 0) {
            break;
        }
        *(u16 *)(s0 + 0x100) = 0;
        func_801A5698((u8 *)s0, 0);
        *(s16 *)(s0 + 0xA) = -0x200;
        func_801A4008(s0);
        func_8012A828(s0, &D_801EF928);
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        break;
    case 3:
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = func_8012B8A4((s16 *)s0);
        func_801A5698((u8 *)s0, *(s16 *)(s0 + 0x100));
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) < 0x1000) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) = *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) + 0x200;
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
            if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) < 0x1000) {
                break;
            }
        }
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) = 0x1000;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = 0x1000;
        D_801F8858 = 0;
        *(s32 *)(s0 + 0x1C) = 0;
        ((S34_801A1470 *)s0)->f34 = ((S34_801A1470 *)s0)->f34 + 1;
        break;
    case 4:
        if (*(s32 *)(s0 + 0x1C) != 0) {
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) - 1;
        } else {
            v1 = D_801F8858;
            *(s32 *)(s0 + 0x1C) = 5;
            if (v1 < 5) {
                v0 = ((s32 (*)(s32, s16, s32))func_801A5654)(s0, *(s16 *)(s0 + 0x100), v1);
                D_801F8844[D_801F8858] = v0;
                D_801F8858 = D_801F8858 + 1;
                func_8002D4C8(0xABA, 0);
            }
        }
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x88;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = func_8012B8A4((s16 *)s0);
        func_801A5698((u8 *)s0, *(s16 *)(s0 + 0x100));
        if (*(s16 *)(s0 + 0x100) >= 0x1000) {
            func_801A41CC();
            func_801A3FB0((void *)s0);
            *(u16 *)(s0 + 0x6) = 0;
            *(u16 *)(s0 + 0xE) = 0;
            func_801A6330();
            *(u16 *)(s0 + 0x100) = 0;
            *(s32 *)(s0 + 0x1C) = 0x30;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 5:
        *(u16 *)(s0 + 0x102) = *(u16 *)(s0 + 0x102) + 0x10;
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 6:
        if (func_8012BEE8(s0) == 0) {
            break;
        }
        v0 = D_801F8844[*(s16 *)(s0 + 0x100)];
        if (v0 == 0) {
            break;
        }
        func_801A5414(v0);
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 1;
        if (*(s16 *)(s0 + 0x100) >= 5) {
            *(s32 *)(s0 + 0x1C) = 0x40;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        } else {
            *(s32 *)(s0 + 0x1C) = 0xC;
        }
        break;
    case 7:
        if (func_8012BEE8(s0) == 0) {
            break;
        }
        *(s16 *)(s0 + 0xA) = -0x240;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) = 0x200;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = 0x200;
        func_801A417C(s0);
        func_801A4008(s0);
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        break;
    case 8:
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18) + 0x200;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18);
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x18) < 0x1000) {
            break;
        }
        func_8012A828(s0, &D_801EEAC8);
        *(s32 *)(s0 + 0x1C) = (s16)(D_801F8714 / 79) + 0x18;
        func_8012B200((u8 *)s0);
        func_8012AD44((s32 *)s0, 1);
        func_801A4328(0);
        func_8017F418();
        *(u16 *)(s0 + 0x5C) = *(u16 *)(s0 + 0x5C) | 0x2000;
        break;
    }
}


extern void func_8012AD44(s32 *a0, s16 a1);
extern s16 D_801F8714;
extern s32 D_801AFBD4;

void func_801A18F4(s32 a0) {
    *(s32 *)(a0 + 0x1C) = (s16)(D_801F8714 / 39) + 0x20;
    *(s16 *)(a0 + 0xAE) = -3;
    *(s32 *)(a0 + 0x58) = (s32)&D_801AFBD4 | 0x40000000 | 0x20000000;
    *(u16 *)(a0 + 0x5C) &= 0xDFFF;
    func_8012AD44((s32 *)a0, 9);
}


extern void func_801A36F0(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A1984(s32 a0)
{
    s32 *s0 = a0;

    func_801A36F0(s0);
    s0[7] = 0x14;
    func_8012AD44(s0, 10);
}


#include "common.h"

/* 4-byte, alignment-1 rodata blob ("  @") -> lwl/lwr + swl/swr block move */
typedef struct M4_801A0168 {
    u8 unk0[4];
} M4_801A0168;

extern M4_801A0168 D_801A0168;
extern u16 D_8019FF8A;

extern void func_801A370C(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_801A85A8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801AAA6C(s32 a0);
extern void func_80184C70(void);
extern void func_80184DB0(s32 a0, void *a1, s32 a2);
extern void func_801A3B08(s32 a0);
extern void func_801A3EEC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801A395C(s32 a0, s32 a1);
extern void func_801A1C38(s32 a0);
extern s32 func_801A861C(s32 a0, s16 a1);
extern void func_801A8DCC(s32 a0, s32 a1);
extern void func_80184E20(void *a0);
extern void func_80184E98(s32 a0, s32 a1);
extern void func_801A3D60(s32 a0);
extern void func_801A3EA8(s32 a0);
extern void func_8018503C(void);
extern int rand(void);

void func_801A19C0(s32 a0) {
    M4_801A0168 sp10;

    sp10 = D_801A0168;
    func_801A370C(a0);
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_8012BEE8(a0) != 0) {
            func_801A85A8(a0, 0x1600000, 0, 0x300);
            *(s32 *)(a0 + 0x1C) = 0x10;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 1:
        if (func_8012BEE8(a0) != 0) {
            func_801A85A8(a0, 0x1600000, 1, 0x300);
            *(s32 *)(a0 + 0x1C) = 0x18;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 2:
        if (func_8012BEE8(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0x80;
            *(u16 *)(a0 + 0x100) = 0;
            func_80184C70();
            func_80184DB0(0, &sp10, -8);
            *(u16 *)(a0 + 0xE4) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
            func_801A3B08(a0);
            func_801A3EEC(9);
            func_8002D4C8(0xB5A, 0);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        } else {
            func_801AAA6C(a0);
        }
        break;
    case 3:
        func_801A395C(a0, -0x230);
        if (func_8012BEE8(a0) != 0) {
            D_8019FF8A &= 0xFFFE;
            func_801A1C38(a0);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(a0 + 0xE4);
            func_801A3EEC(1);
            func_8002D4C8(4, 0xB5A);
        } else {
            if ((*(s32 *)(a0 + 0x1C) & 0xF) == 0) {
                if (func_801A861C(a0, *(s16 *)(a0 + 0x100)) != 0) {
                    *(u16 *)(a0 + 0x100) = *(u16 *)(a0 + 0x100) + 1;
                    func_8002D4C8(0xB59, 0);
                }
            }
            if ((u32)(*(s32 *)(a0 + 0x1C) - 0x19) < 0x57) {
                func_801A8DCC(a0, 0);
                func_80184E20((void *)(a0 + 4));
                func_80184E98(rand() & 0xFF8, 0x60);
                ((void (*)())func_801A3D60)(a0);
            }
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += 0x80;
            func_801A3EA8(a0);
        }
        func_8018503C();
        break;
    }
}


extern void func_801A36F0(void *a0);
extern void func_801A3744(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A1C38(s32 a0) {
    *(s16 *)(a0 + 0xAE) = -1;
    func_801A36F0(a0);
    func_801A3744(a0);
    func_8012AD44((s32 *)a0, 0xB);
}


#include "common.h"

extern void func_801A395C(s32 a0, s32 a1);
extern void func_8013240C(s32 a0);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A860(void *a0, int a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801A4328(s32 a0);
extern void func_800183E0(s32 a0);

extern s32 D_801B6E94[0x11];
extern u8 D_801EF9A8;
extern s32 D_801EEAC8;
extern s16 D_801F8714;
extern s16 D_801F872A;
extern s32 D_801F8730;
extern s32 D_801AFBC4;
extern s32 D_801C65E4;
extern s32 D_801C6644;
extern u16 D_8019FF8A;

void func_801A1C7C(s32 s0) {
    s32 *p;
    u16 t5c;
    s32 v0;
    s32 *q;
    u16 f9;

    v0 = ((s32 (*)(s32, s32))func_801A395C)(s0, -0x240);
    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        q = &D_801F8730;
        *q &= ~0x4000;
        D_801F872A -= 4;
        if (D_801F872A < -1) {
            D_801F872A = -1;
        }
        func_8013240C((s32)q - 0xC);
        if (D_801F872A <= 0) {
            *(u16 *)(s0 + 0x34) += 1;
        }
        break;
    case 1:
        func_8001C924(*(s32 *)(s0 + 0x20), D_801B6E94);
        func_8012A860((void *)s0, (int)&D_801EF9A8);
        *(u16 *)(s0 + 0x34) += 1;
        break;
    case 2:
        if (*(s16 *)(s0 + 0x98) == 0 && v0 != 0) {
            func_8012A828(s0, &D_801EEAC8);
            *(s32 *)(s0 + 0x1C) = (s16)(D_801F8714 / 79) + 0x18;
            func_8012B200((u8 *)s0);
            func_8012AD44((s32 *)s0, 1);
            *(s32 *)(s0 + 0x1C) = 0x10;
            func_801A4328(0);
            p = &D_801C65E4;
            *(s16 *)(s0 + 0xAE) = -1;
            *(s32 *)(s0 + 0x58) = (s32)&D_801AFBC4 | 0x40000000 | 0x20000000;
            t5c = *(u16 *)(s0 + 0x5C) | 0x2000;
            f9 = D_8019FF8A & 0xF9F7;
            *(u16 *)(s0 + 0x5C) = t5c;
            D_8019FF8A = f9;
            ((s32 (*)(s32 *))func_800183E0)(p);
            ((s32 (*)(s32 *))func_800183E0)(&D_801C6644);
        }
        break;
    }
}


void func_801A1E74(s32 a0) {
    func_8012AD44((s32 *)a0, 0xD);
}


extern void func_8001C924(s32 a0, void *a1);
extern void func_80132288(s32 *arg_a0, s32 *a1, s32 a2);
extern s32 func_801A8528(s32 a0);
extern void func_80178B18(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern s32 D_801BF01C;
extern s32 D_801F8724;
extern s32 D_801AFB58;
extern s32 D_801AFCF8;

/* Definition is (void) to agree with the pre-existing TU declarations
   (md_SC07_004.c lines 10/1941). The entity pointer arrives in $a0; the
   pin-to-local copy forces gcc to home it in a callee-saved reg exactly as
   the target's `addu $s0,$a0,$zero`. */
void func_801A1E94(void)
{
    register s32 param_1 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    s32 p;
    s32 *s0;
    s32 *s1;

    p = param_1;
    s0 = (s32 *)p;
    s1 = &D_801BF01C;
    func_8001C924(*(s32 *)(p + 0x20), s1);
    func_80132288(&D_801F8724, &D_801AFB58, *s1);
    *(s16 *)(p + 0xA) = -0x240;
    *(s16 *)(p + 0xE) = 0x30;
    *(s32 *)(p + 0xD4) = func_801A8528(p);
    func_80178B18(p, (s32)&D_801AFCF8);
    *(s32 *)(p + 0x1C) = 0x60;
    *(s16 *)(p + 0x100) = 0xFF;
    *(s16 *)(p + 0x84) = 0;
    func_8012AD44((s32 *)p, 0xE);
}


INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A0168);

#include "common.h"

/* func_801A1F3C - md_SC07_004 (245 ins).  Three levers were needed:
 *
 * 1. case 0 re-reads *(s16 *)(s0 + 0x100) inside the guard instead of caching it
 *    in a local.  A cached local coalesces straight into $a0 (`lh $a0` + `andi`),
 *    but the target keeps the tested value in $v0 and copies it
 *    (`lh $v0` / `addu $a0,$v0,$zero` / `andi $a0,$a0,0xFF`).  The re-read also
 *    fixes the frame: gcc-2.7.2 gives var_size 16 (frame 0x28) here, 8 (0x20) with
 *    the cached local -- same one-line edit closed BOTH the +1 length drift and the
 *    prologue/epilogue offsets.  (A `register s32 __asm__("$4")` pin reproduces the
 *    copy but NOT the frame; the re-read does both.)
 * 2. case 1 splits `D_8019FF8A |= 0x4000` into a read / store-to-0x34 / write, the
 *    TU house idiom (cf. func_801A0A98, func_801A1C7C).  A single `|=` makes the
 *    0x34 store land in the jal delay slot, which then lets cross_jump merge case 0's
 *    tail into case 1's (-3 instructions).  Splitting it puts `sh $v1,0x34($s0)` in
 *    the load shadow and `addu $a1,$zero,$zero` in the delay slot, as the target has.
 * 3. `lw $a0, 0xD4($s0)` is a copy-suggestion, not a pin: the loaded word IS the
 *    argument of func_801A7CDC (defined in this TU as `s32 func_801A7CDC(void *a0)`),
 *    so local-alloc gives its pseudo $a0 and the argument copy folds away -- which is
 *    also why func_801A7CDC's delay slot is a bare nop.
 *
 * NOTE for banking: md_SC07_004.c already carries this typedef and the
 * `extern M4_801A0168 D_801A0168;` at file scope (~L366) -- drop the duplicate
 * typedef when merging (an identical extern is legal, an identical typedef is not).
 */

/* 4-byte, alignment-1 rodata blob -> lwl/lwr + swl/swr block move */


extern M4_801A0168 D_801A0168;
extern u16 D_8019FF8A;
extern s32 D_801AFD58;
extern s32 D_801EEAC8;
extern s16 D_801F8714;
extern u16 D_801F8718;

extern void func_80016450(s32 a0, s32 a1);
extern void func_801AAA6C(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_801A3EEC(s32 a0);
extern void func_80184C70(void);
extern void func_80184DB0(s32 a0, void *a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013C9C4(void *a0);
extern void func_801A3744(s32 a0);
extern s32 func_801A7CDC(void *a0);
extern s32 func_801A861C(s32 a0, s16 a1);
extern void func_801A8DCC(s32 a0, s32 a1);
extern void func_80184E20(void *a0);
extern void func_80184E98(s32 a0, s32 a1);
extern void func_8018503C(void);
extern int rand(void);
extern s32 func_801A3798(s32 a0, s32 a1);
extern void func_801A40CC(s32 a0);
extern s32 func_8001AAA0(s32 a0);
extern void func_8017F558(void);
extern s32 func_80178970(s32 a0);
extern void func_80178D18(s32 a0);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void func_8017F004(void);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A1F3C(s32 s0)
{
    M4_801A0168 sp10;
    s32 v0;
    void *p;

    sp10 = D_801A0168;
    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        if (*(s16 *)(s0 + 0x100) != 0) {
            func_80016450(*(s16 *)(s0 + 0x100) & 0xFF, 1);
            if (((*(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) - 4) << 16) < 0) {
                *(u16 *)(s0 + 0x100) = 0;
            }
        }
        func_801AAA6C(s0);
        if (func_8012BEE8(s0) != 0) {
            func_801A3EEC(9);
            func_80184C70();
            func_80184DB0(0, &sp10, -8);
            *(s32 *)(s0 + 0x1C) = 0x20;
            *(u16 *)(s0 + 0x34) = 1;
            func_8002D4C8(0xB4B, 0);
        }
        break;
    case 1:
        func_801AAA6C(s0);
        if ((*(s32 *)(s0 + 0x1C) & 7) == 0) {
            func_8013C9C4(&D_801AFD58);
        }
        if (func_8012BEE8(s0) != 0) {
            u16 t;

            *(s32 *)(s0 + 0x1C) = 0x140;
            t = D_8019FF8A;
            *(u16 *)(s0 + 0x34) = 2;
            D_8019FF8A = t | 0x4000;
            func_8002D4C8(0xB5A, 0);
        }
        break;
    case 2:
        if (func_8012BEE8(s0) != 0) {
            func_801A3744(s0);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0;
            *(u16 *)(s0 + 0x34) = 3;
            func_8002D4C8(4, 0xB4B);
            func_8002D4C8(4, 0xB5A);
            break;
        }
        func_801AAA6C(s0);
        p = *(void **)(s0 + 0xD4);
        if (p != NULL) {
            v0 = *(s32 *)(s0 + 0x1C) & 0x1F;
            if (v0 == 7 || v0 == 0x14 || v0 == 0x17) {
                func_801A7CDC(p);
            }
        }
        if ((*(s32 *)(s0 + 0x1C) & 7) == 0) {
            func_8013C9C4(&D_801AFD58);
        }
        if ((*(s32 *)(s0 + 0x1C) & 0x1F) == 0) {
            if (func_801A861C(s0, *(s16 *)(s0 + 0x100)) != 0) {
                *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 1;
                func_8002D4C8(0xB59, 0);
            }
        }
        if (*(s32 *)(s0 + 0x1C) >= 0x11) {
            func_801A8DCC(s0, 0);
            func_80184E20((void *)(s0 + 4));
            func_80184E98(rand() & 0xFF8, 0x60);
        }
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) += 0x80;
        break;
    case 3:
        if (func_801A3798(s0, 0) != 0) {
            func_801A40CC(s0);
            *(u16 *)(s0 + 0x34) = 4;
        }
        break;
    case 4:
        if (*(s16 *)(s0 + 0x84) != 0) {
            func_8001AAA0(0x8C);
            *(u16 *)(s0 + 0x34) = 5;
            func_8017F558();
        }
        break;
    case 5:
    case 6:
        break;
    }
    func_8018503C();
    if (*(s16 *)(s0 + 0x84) == 0) {
        *(u16 *)(s0 + 0x84) = func_8001AAA0(0x9D);
    }
    if (func_80178970(s0) != 0) {
        func_80178D18(s0);
        func_801A3EEC(1);
        func_8017BF08(&D_801F8714, &D_801F8718, 0xB, 0x120);
        func_8017F004();
        func_8012A828(s0, &D_801EEAC8);
        *(s32 *)(s0 + 0x1C) = (s16)(D_801F8714 / 79) + 0x18;
        func_8012B200((u8 *)s0);
        func_8012AD44((s32 *)s0, 1);
        *(s32 *)(s0 + 0x1C) = 0x10;
    }
}


extern void func_8017F578(void);
void func_801A2310(void) {
    func_8017F578();
}


extern s32 D_801F871C;

void func_801A2330(void) {
    if (D_801F871C != 0) {
        *(u16 *)(D_801F871C + 0x34) = 6;
    }
}



s32 func_801A2350(s32 arg0) {
        return *(u16*)(arg0 + 0x34) == 0x6;
    }


extern void func_80178B18(s32 a0, s32 a1);
extern void func_801A7D18(s32);
extern void func_801A36F0(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_800D0C48(u16 a0);
extern void func_8002A088(s32 a0);
extern void func_8002A2D4(s32 a0);
extern void func_8002A544(s32 a0);
extern void func_8002A7B4(s32 a0);
extern s32 D_801AFD8C;
extern s16 D_801F8868;
extern s32 D_801F8720;

void func_801A2364(s32 a0)
{
    s32 flag;

    func_80178B18(a0, (s32)&D_801AFD8C);
    flag = *(s32 *)(a0 + 0xD4);
    *(s32 *)(a0 + 0x1C) = 0x20;
    (*(u16 *)&D_801F8868) = 0;
    if (flag != 0) {
        ((void (*)(s32 arg0))func_801A7D18)(flag);
        *(s32 *)(a0 + 0xD4) = 0;
        func_801A36F0((void *)a0);
    }
    func_8012AD44((s32 *)a0, 0xF);
    func_800D0C48(1);
    D_801F8720 = 0;
    func_8002A088(0x320);
    func_8002A2D4(0x64);
    func_8002A544(0x190);
    func_8002A7B4(0x12C);
}


#include "common.h"

/* ---------------------------------------------------------------------------
 * TU SPLICE NOTE: md_SC07_004.c already has, at FILE SCOPE above line 645,
 *   :361-364  typedef struct M4_801A0168 { u8 unk0[4]; } M4_801A0168;
 *             extern M4_801A0168 D_801A0168;
 * DROP the two lines below when inserting this body into the TU (they are here
 * only so the standalone match_one compile has them).  Everything else in this
 * header is either a fresh symbol or a verbatim copy of the TU's own spelling.
 * ------------------------------------------------------------------------- */

extern M4_801A0168 D_801A0168;

/* 16-byte VECTOR / 8-byte SVECTOR / 32-byte matrix, local-suffixed per this
 * TU's house style (cf. Mtx32_801A3180 / SVec_801A3180 at :901-903). */
typedef struct { s32 vx, vy, vz, pad; } Vec32_801A2400;
typedef struct { s16 vx, vy, vz, pad; } SVec_801A2400;
typedef struct { s32 w[8]; } Mtx32_801A2400;

extern u16 D_8019FF8A;
/* §250: D_801F8EB2 is materialised as a lui/addiu BASE (lhu 0($v0) / sh 0($v0))
 * => array shape; its neighbour D_801F8EB0 keeps the %lo load + $at store of a
 * plain scalar.  The two spellings are what makes the pair's asm asymmetric. */
extern u16 D_801F8EB2[];
extern u16 D_801F8EB0;
extern s32 D_801F8720;
extern s32 D_80062BC0;
extern s32 D_801AFDDC;
extern u8 D_8018A27C[];

/* --- declarations copied verbatim from this TU's own spellings ------------- */
extern s32 func_8012BEE8(s32 a0);            /* :135  */
extern void func_801A34C4(s32 a0);           /* :80   */
extern void func_801A34FC(s32 arg0, u16 *arg1); /* :924 */
extern s32 func_8012B744(void *a0, void *a1);   /* :919 */
extern void RotMatrixY(s32 a0, void *a1);       /* :921 */
extern void func_800484EC(s32 a0, s32 a1, s32 a2); /* :923 */
extern s32 func_8004787C(s32 a0);            /* :1132 */
extern void func_801A3624(s32 a0, u16 *a1, s32 a2); /* :146 */
extern void func_8012AD80(s32 a0);           /* :915  */
extern s32 func_801A3594(void *a0);          /* :916  */
extern void func_801A3744(s32 a0);           /* :457  */
extern s32 func_801A3798(s32 a0, s32 a1);    /* :3036 */
extern void func_801A395C(s32 a0, s32 a1);   /* :380 — real sig returns s32, cast at the call (:3006 house idiom) */
extern s32 func_8012C588(s32 a0, s32 a1);    /* :6    */
extern void func_80184C70(void);             /* :375  */
extern void func_80184DB0(s32 a0, void *a1, s32 a2); /* :376 */
extern void func_8002D4C8(s32 a0, s32 a1);   /* :379  */
extern void func_801A8DCC(s32 a0, s32 a1);   /* :383  */
extern void func_80184E20(void *a0);         /* :384  */
extern void func_80184E98(s32 a0, s32 a1);   /* :385  */
extern void func_8018503C(void);             /* :388  */
extern int rand(void);                       /* :389  */
extern s32 func_801A8564(s32 a0);            /* :1193 */
extern void func_80016450(s32 a0, s32 a1);   /* :675  */
/* defined later in this TU — spellings copied from the definitions */
extern void func_801A2C88(void);             /* :667 — call site passes $a0, cast */
extern void func_801A2CA4(void);             /* :679 — ditto */
extern void func_801A4060(s32 a0);           /* :1598 */
extern void func_801A43EC(s32 a0);           /* :1778 — call site passes nothing, cast */
extern void func_801ADC40(u8 *a0);           /* :8027 */
extern void func_801AD5B4(s32 a0, s32 a1);   /* :7750 */
extern void func_801A86F8(void);             /* :4243 */
extern void func_801A876C(s32 a0, s16 a1, s32 a2); /* :4267 */
extern void func_801A87C4(s32 a0, s16 a1, s32 a2); /* :4278 */
extern void func_801ADA9C(s32 a0);           /* :7957 */
extern void func_801AEB94(void);             /* :8810 */
extern s32 func_801A8670(s32 a0);            /* :4214 */
extern s32 func_801A86B4(s32 a0);            /* :4228 */
extern void func_801AD294(void);             /* :7610 */
extern void func_801AD640(s32 a0, s32 a1);   /* :7777 */
extern void func_801AD2CC(void);             /* :7618 */
extern s32 func_801ACE04(s32 a0);            /* :7379 */
/* not in this TU — card signatures */
extern s32 func_80019198(void);
extern void func_80019064(void *a0);
extern void func_800D1724(s32 a0);
extern s32 func_80178970();

void func_801A2400(s32 arg0) {
    /* D_800AE620 at BLOCK scope exactly as func_801A3180 (:931): the file-scope
     * spelling `extern Mtx32_801A90D8 D_800AE620;` lands LATER (:2001) and a
     * second file-scope spelling is a hard gcc-2.7.2 conflicting-types error. */
    extern s32 D_800AE620[8];
    Vec32_801A2400 sp10;
    SVec_801A2400 sp20;
    Mtx32_801A2400 m;          /* sp+0x28 */
    Vec32_801A2400 sp48;
    M4_801A0168 sp58;          /* sp+0x58 (house style: cf. func_801A19C0) */
    s32 s1;
    s32 s0;
    s32 v0;
    s32 v1;

    s1 = arg0;
    switch (*(u16 *)(s1 + 0x34)) {
    case 0:
        if (func_8012BEE8(s1) != 0) {
            v0 = *(s16 *)(s1 + 6) * *(s16 *)(s1 + 6) +
                 *(s16 *)(s1 + 0xE) * *(s16 *)(s1 + 0xE);
            *(u16 *)(s1 + 0x102) = 0;
            *(s32 *)(s1 + 0x1C) = 0x20;
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
            if (v0 >= 0x41) {
                D_8019FF8A |= 0x40;
                sp20.vz = 0;
                sp20.vy = 0;
                sp20.vx = 0;
                func_801A34FC(s1, (u16 *)&sp20);
                v0 = func_8012B744((void *)(s1 + 4), &sp20);
                m = *(Mtx32_801A2400 *)&D_800AE620;
                RotMatrixY((s16)v0, &m);
                sp10.vy = 0;
                sp10.vx = 0;
                sp10.vz = 0xFFFC0000;
                func_800484EC((s32)&m, (s32)&sp10, s1 + 0x10);
            } else {
                func_801A34C4(s1);
            }
        } else {
            if (*(s32 *)(s1 + 0x1C) == 0x10) {
                ((void (*)(s32))func_801A2C88)(s1);
            }
            ((void (*)(s32))func_801A2CA4)(s1);
        }
        break;
    case 1:
        func_8012BEE8(s1);
        if (((*(u16 *)(s1 + 0x102) >> 8) & 0x7F) == 0) {
            ((void (*)(s32))func_801A2C88)(s1);
        }
        ((void (*)(s32))func_801A2CA4)(s1);
        v0 = *(u16 *)(s1 + 0x102) + 0x400;
        *(u16 *)(s1 + 0x102) = v0;
        v0 = func_8004787C((s16)v0);
        *(u16 *)(s1 + 0xA) = *(u16 *)(s1 + 0xA) + (v0 >> 10);
        func_801A4060(s1);
        func_801A3624(0, (u16 *)(*(s32 *)(s1 + 0x20) + 0x12), 0x20);
        s0 = 1;
        if (D_8019FF8A & 0x40) {
            func_8012AD80(s1);
            s0 = func_801A3594((void *)s1);
            if (s0 != 0) {
                func_801A34C4(s1);
            }
        }
        if (s0 != 0 && *(s32 *)(s1 + 0x1C) == 0) {
            func_801A3744(s1);
            *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = 0;
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        }
        break;
    case 2:
        if ((*(u16 *)(s1 + 0x102) >> 8) == 0) {
            ((void (*)(s32))func_801A2C88)(s1);
        }
        ((void (*)(s32))func_801A2CA4)(s1);
        v0 = *(u16 *)(s1 + 0x102) + 0x400;
        *(u16 *)(s1 + 0x102) = v0;
        v0 = func_8004787C((s16)v0);
        *(u16 *)(s1 + 6) = *(u16 *)(s1 + 6) + (v0 >> 9);
        func_801A4060(s1);
        func_801A3798(s1, 0);
        if (*(s16 *)(s1 + 0xE6) < 0) {
            *(u16 *)(s1 + 0x98) = 0;
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        }
        break;
    case 3:
        if ((*(u16 *)(s1 + 0x102) >> 8) == 0) {
            ((void (*)(s32))func_801A2C88)(s1);
        }
        ((void (*)(s32))func_801A2CA4)(s1);
        v0 = *(u16 *)(s1 + 0x102) + 0x400;
        *(u16 *)(s1 + 0x102) = v0;
        v0 = func_8004787C((s16)v0);
        *(u16 *)(s1 + 0xA) = *(u16 *)(s1 + 0xA) + (v0 >> 10);
        func_801A4060(s1);
        if (((s32 (*)(s32, s32))func_801A395C)(s1, -0x2A0) != 0) {
            func_8012C588(0x1FE, s1);
            *(s32 *)(s1 + 0x1C) = 0x70;
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
            func_80184C70();
            sp58 = D_801A0168;
            func_80184DB0(0, &sp58, -8);
            func_8002D4C8(0xB5A, 0);
        }
        break;
    case 4:
        v0 = *(u16 *)(s1 + 0x102) + 0x400;
        *(u16 *)(s1 + 0x102) = v0;
        v0 = func_8004787C((s16)v0);
        *(u16 *)(s1 + 0xA) = *(u16 *)(s1 + 0xA) + (v0 >> 10);
        func_801A4060(s1);
        sp20.vx = 0;
        sp20.vy = -0x40;
        sp20.vz = 0x20;
        func_801A8DCC(s1, (s32)&sp20);
        func_801A8DCC(s1, (s32)&sp20);
        sp48.vx = *(s32 *)(s1 + 4);
        sp48.vy = *(s32 *)(s1 + 8) + 0xFFC00000;
        sp48.vz = *(s32 *)(s1 + 0xC);
        func_80184E20(&sp48);
        func_80184E98(rand() & 0xFF8, 0x60);
        func_801ADC40((u8 *)s1);
        func_8012BEE8(s1);
        v1 = *(s32 *)(s1 + 0x1C);
        if ((v1 & 7) == 0) {
            func_801AD5B4(s1, (v1 & 0x18) >> 3);
            func_8002D4C8(0xB59, 0);
        }
        if (*(s32 *)(s1 + 0x1C) == 0x64) {
            *(s32 *)(s1 + 0xD4) = func_801A8564(s1);
        }
        if (*(s32 *)(s1 + 0x1C) < 0x60) {
            func_801A86F8();
            if (*(s32 *)(s1 + 0xD4) != 0) {
                func_801A876C(*(s32 *)(s1 + 0xD4), 0x1600, 0x30);
            }
        }
        if (*(s32 *)(s1 + 0x1C) == 0xE) {
            func_801ADA9C(s1);
        }
        if (*(s32 *)(s1 + 0x1C) < 0xF) {
            D_801F8EB2[0] += 0xA;
            D_801F8EB0 += 0xC;
            func_801AEB94();
        }
        if (*(s32 *)(s1 + 0x1C) == 8) {
            func_801A8670(s1);
            func_801A86B4(s1);
            func_8002D4C8(0xB4D, 0);
        }
        if (*(s32 *)(s1 + 0x1C) == 0) {
            *(s32 *)(s1 + 0x1C) = 0x60;
            *(u16 *)(s1 + 0x34) = 5;
            func_8002D4C8(4, 0xB5A);
        }
        break;
    case 5:
        D_801F8EB2[0] += 0xA;
        D_801F8EB0 += 0xC;
        func_801AEB94();
        func_801A86F8();
        if (*(s32 *)(s1 + 0xD4) != 0) {
            if (*(s32 *)(s1 + 0x1C) < 0x10) {
                func_801A87C4(*(s32 *)(s1 + 0xD4), 0x1000, 0x100);
            } else {
                func_801A876C(*(s32 *)(s1 + 0xD4), 0x1600, 0x30);
            }
        }
        if (func_8012BEE8(s1) != 0 && D_801F8720 != 0) {
            func_801AD294();
            *(u16 *)(s1 + 0x100) = 1;
            *(s32 *)(s1 + 0x1C) = 0x50;
            *(u16 *)(s1 + 0x34) = 6;
        }
        break;
    case 6:
        if ((*(s32 *)(s1 + 0x1C) & 0xF) == 0) {
            func_8012C588(0x39D, s1);
            func_801AD640(s1, *(u16 *)(s1 + 0x100) & 3);
            *(u16 *)(s1 + 0x100) = *(u16 *)(s1 + 0x100) + 2;
            if (func_80019198() == 0) {
                func_80019064(&D_80062BC0);
            }
        }
        func_801AEB94();
        if (func_8012BEE8(s1) != 0) {
            *(s32 *)(s1 + 0xCC) = func_8012C588(0x39F, s1);
            func_801AD2CC();
            *(u16 *)(s1 + 0x34) = 7;
        }
        break;
    case 7:
        s0 = 1;
        if (*(s32 *)(s1 + 0xCC) != 0) {
            s0 = func_801ACE04(*(s32 *)(s1 + 0xCC)) != 0;
        }
        if (s0 != 0) {
            *(u16 *)(s1 + 0x100) = 0;
            *(u16 *)(s1 + 0x34) = 8;
        }
        *(s32 *)(s1 + 0x1C) = *(s32 *)(s1 + 0x1C) + 1;
        if ((*(s32 *)(s1 + 0x1C) & 7) == 0 && func_80019198() == 0) {
            func_80019064(&D_801AFDDC);
        }
        break;
    case 8:
        if (*(s16 *)(s1 + 0x100) < 0xFF) {
            *(s16 *)(s1 + 0x100) += 4;
            if (*(s16 *)(s1 + 0x100) >= 0x100) {
                *(s16 *)(s1 + 0x100) = 0xFF;
                *(u16 *)(s1 + 0x34) = 9;
                func_800D1724((s32)D_8018A27C);
            } else if (*(s16 *)(s1 + 0x100) < 0x80) {
                *(s32 *)(s1 + 0x1C) = *(s32 *)(s1 + 0x1C) + 1;
                if ((*(s32 *)(s1 + 0x1C) & 7) == 0 && func_80019198() == 0) {
                    func_80019064(&D_801AFDDC);
                }
            }
        }
        func_80016450(*(u8 *)(s1 + 0x100), 1);
        break;
    case 9:
        func_80016450(0xFF, 1);
        break;
    }
    func_8018503C();
    ((void (*)(void))func_801A43EC)();
    func_80178970(s1);
}


s32 func_801A2C4C(void) {
    return 0;
}



s32 func_801A2C54(s32 arg0) {
        return *(u16*)(arg0 + 0x34) == 0x7;
    }


extern void func_8017C068(void);
void func_801A2C68(void) {
    func_8017C068();
}


extern s16 D_801F8868;
extern s16 D_801F886C;

void func_801A2C88(void) {
    D_801F8868 = 1;
    D_801F886C = 0;
}


#include "common.h"

extern void func_80016450(s32 a0, s32 a1);
extern s16 D_801F8868;
extern s16 D_801F886C;

void func_801A2CA4(void) {
    if (D_801F8868 != 0) {
        switch (D_801F8868) {
        case 1:
            D_801F886C = (u16)D_801F886C + 48;
            if (D_801F886C >= 96) {
                D_801F8868 = 2;
            }
            break;
        case 2:
            D_801F886C = (u16)D_801F886C - 24;
            if (D_801F886C < 0) {
                D_801F886C = 0;
            }
            if (D_801F886C == 0) {
                D_801F8868 = 0;
            }
            break;
        }
        func_80016450(*(u8 *)&D_801F886C, 1);
    }
}


extern void (*D_801AFDF4[])(void);
extern void func_801A4258(void);
extern void func_801A3F10(void);

void func_801A2D78(void *a0) {
    D_801AFDF4[*(u16 *)((s32)a0 + 0x2)]();
    func_801A4258();
    func_801A3F10();
}


#include "common.h"

extern u16 D_8019FF8A;
extern s16 D_801F8714;
extern void func_8016AA50(s32 a0, s32 a1);
extern void func_8016B3F4(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801A2DC4(s32 arg0) {
    s32 var;
    s16 cae;
    u16 c76;
    u16 t5c;
    u16 dv;
    u16 tmp0;

    var = arg0;
    cae = -1;
    *(s16 *)(var + 0xAE) = cae;
    c76 = 0x800;
    *(u16 *)(var + 0x76) = c76;
    tmp0 = *(u16 *)(var + 0x5C);
    t5c = tmp0;
    *(u8 *)(var + 0xC1) = 0;
    dv = D_8019FF8A;
    *(u16 *)(var + 0x5E) = 0;
    t5c = t5c & 0xFFFE;
    *(u16 *)(var + 0x5C) = t5c;
    D_8019FF8A = (dv | 0x400);
    func_8016AA50(arg0, 0x27A);

    if (D_801F8714 != 0) {
        D_801F8714 -= 0x27A;
        if (D_801F8714 < 0) {
            D_801F8714 = 0;
        }
    }

    *(u16 *)(arg0 + 0x7C) = *(u16 *)(arg0 + 6);
    *(u16 *)(arg0 + 0x7E) = *(u16 *)(arg0 + 0xA) + *(u16 *)(arg0 + 0x52);
    *(u16 *)(arg0 + 0x80) = *(u16 *)(arg0 + 0xE);
    func_8016B3F4(arg0);
    func_8002D4C8(0xB4C, 0);
}


extern u16 D_8019FF8A;
extern u8 D_801C6614;
extern u8 D_801C6674;
extern u8 D_801EF9A8;
extern s16 D_801F8860;

extern void func_800183E0(s32 a0);

void func_801A2E90(s32 a0)
{
    s32 s0;
    u16 v0;
    u16 v1;
    s32 v2;

    s0 = a0;
    func_801A36F0((void *)s0);
    func_801A34C4(s0);
    *(s16 *)(s0 + 0xE6) = -1;
    v0 = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    v1 = D_8019FF8A | 0x208;
    *(u16 *)(s0 + 0x5C) = v0;
    D_8019FF8A = v1;
    func_800183E0((s32)&D_801C6614);
    func_800183E0((s32)&D_801C6674);
    func_8012A828(s0, &D_801EF9A8);
    v2 = D_801F8860;
    *(s16 *)(s0 + 0xF8) = 0;
    if (v2 != 1) {
        func_801A3EEC(1);
    }
}


#include "common.h"

extern void func_8013240C(s32 a0);
extern void func_8001C924(s32 a0, void *a1);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern void func_8014CBD8(void);
extern void func_801A3114(s32 *a0);

extern s32 D_80126B58[4];
extern u16 D_80126CE0;
extern u16 D_800B99DA;
extern s16 D_801AFB90;
extern s32 D_801AFAB8;
extern s32 D_801BC9EC;
extern u8 D_80063548[];
extern s32 D_801F8724;
extern s16 D_801F872A;
extern s32 D_801F8730;

void func_801A2F34(s32 a0) {
    s16 *p;
    s32 *s2;
    s32 *s0;
    s16 v1;
    s32 v0;

    v1 = *(s16 *)(a0 + 0xE6);
    s2 = D_80126B58;
    if (v1 == 0) {
        p = &D_801F872A;
        *p = (s16)D_80126CE0 >> 1;
        func_8013240C((s32)p - 6);
        if ((D_801F8730 & 0x4000) != 0) {
            *(u16 *)(a0 + 0xE6) = *(u16 *)(a0 + 0xE6) + 1;
        }
    } else if (v1 != 1) {
        if (*(s16 *)(a0 + 0x98) == 0 && *(s16 *)&D_80126CE0 >= D_801AFB90) {
            s0 = &D_801BC9EC;
            func_8001C924(*(s32 *)(a0 + 0x20), s0);
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = (s32)D_80063548;
            *(s16 *)(a0 + 0xE6) = 0;
            func_80132288(&D_801F8724, &D_801AFAB8, *s0);
        }
    }
    if ((D_800B99DA & 1) != 0) {
        if (*(s16 *)((s32)s2 + 0x188) > 0) {
            *(s16 *)((s32)s2 + 0x188) = *(s16 *)((s32)s2 + 0x188) - 1;
        }
    }
    if (*(s16 *)((s32)s2 + 0x188) == 0) {
        v0 = *(u16 *)(a0 + 0xF8) + 1;
        *(u16 *)(a0 + 0xF8) = v0;
        if ((s16)v0 >= 0x19) {
            func_8014CBD8();
            func_801A3114((s32 *)a0);
        }
    } else {
        *(u16 *)(a0 + 0xF8) = 0;
    }
}


extern void func_801A46B8(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A30C8(s32 a0)
{
    s32 s0;
    u16 v0;

    s0 = a0;
    v0 = *(u16 *)(s0 + 0x5C);
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(u16 *)(s0 + 0x10A) = 0;
    *(u16 *)(s0 + 0x5C) = v0 & 0xDFFF;
    func_801A46B8(s0);
    func_8012AD44((s32 *)s0, 8);
}


extern void func_801A36F0(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012A860(void *a0, int a1);
extern u8 D_801EF9A8;

void func_801A3114(s32 *a0)
{
    s32 *s0 = a0;
    u16 v0;

    v0 = *(u16 *)((s32)s0 + 0x5C);
    *(u16 *)((s32)s0 + 0x5E) = 0;
    *(u8 *)((s32)s0 + 0xC1) = 0;
    *(u16 *)((s32)s0 + 0x5C) = v0 & 0xDFFE;
    func_801A36F0((void *)s0);
    func_8012AD44(s0, 12);
    if (*(s16 *)((s32)s0 + 0xE6) < 0) {
        *(u16 *)((s32)s0 + 0x34) = 2;
        func_8012A860((void *)s0, (int)&D_801EF9A8);
    }
}


#include "common.h"

/* 32-byte shared matrix global, 8-byte SVECTOR and 16-byte VECTOR, local-suffixed
 * per this TU's house style (cf. Mtx32_801A90D8 / SVec_801A3B18 further down). */
typedef struct { s32 w[8]; } Mtx32_801A3180;
typedef struct { s16 vx, vy, vz, pad; } SVec_801A3180;
typedef struct { s32 vx, vy, vz, pad; } Vec32_801A3180;

/* Declarations copied verbatim from this TU's own spellings:
 * RotMatrixY/D_80126B5E/D_80126B66 (:1096,:1106,:1108), ApplyMatrixSV +
 * func_800484EC (:4359,:4214), ratan2 (:4108), func_8012AD80 (:2997),
 * func_8012B744 (:4212), D_8019FF8A (:105), and the definitions that follow
 * this function in the file: func_801A34C4 (:841), func_801A34FC (:848),
 * func_801A3594 (:875), func_801A41CC (:1329). */
extern u16 D_8019FF8A;
extern s16 D_80126B5E;
extern s16 D_80126B66;
extern void func_801A41CC(void);
extern void func_8012AD80(s32 a0);
extern s32 func_801A3594(void *a0);
extern void func_801A34C4(s32 a0);
extern s32 func_80047D3C(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 ratan2(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_801A34FC(s32 arg0, u16 *arg1);

void func_801A3180(s32 arg0, s32 arg1) {
    /* D_800AE620 is the shared 32-byte matrix global, declared at BLOCK scope
     * exactly as md_SC07_004.c:1127-1133 does: the file-scope spelling this TU
     * settles on (`extern Mtx32_801A90D8 D_800AE620;`) lives below, and a second
     * file-scope spelling is a hard `conflicting types` error in gcc-2.7.2. */
    extern s32 D_800AE620[8];
    Mtx32_801A3180 m;      /* sp+0x10 */
    SVec_801A3180 sp30;    /* sp+0x30 */
    SVec_801A3180 sp38;    /* sp+0x38 */
    Vec32_801A3180 sp40;   /* sp+0x40 */
    s32 dist0;
    s32 var_s2;
    s16 var_s3;
    /* NARROW LOCAL (cookbook 194-B/162j1): `var_a0` and `sd` are s16 so their
     * defining copies are (set (reg:HI) (subreg:HI …)) — SET_SRC is a SUBREG, so
     * local-alloc.c:1002-1007 never calls optimize_reg_copy_1 and the later uses
     * keep reading the PRE-copy register ($v1 / $a0) exactly as the target does. */
    s16 var_a0;
    s16 sd;
    s32 raw;
    s32 diff;
    s32 dist;
    s16 t1;
    s16 t2;

    if (D_8019FF8A & 0x40) {
        func_801A41CC();
        func_8012AD80(arg0);
        if (func_801A3594((void *)arg0)) {
            func_801A34C4(arg0);
        }
        return;
    }
    t1 = D_80126B5E;
    t2 = D_80126B66;
    dist0 = func_80047D3C(t1 * t1 + t2 * t2);
    if (dist0 < 0x100) {
        sp30.vz = 0;
        sp30.vy = 0;
        sp30.vx = 0;
    } else {
        m = *(Mtx32_801A3180 *)&D_800AE620;
        RotMatrixY((ratan2(-D_80126B66, D_80126B5E) - 0x400) & 0xFFF, &m);
        sp38.vy = 0;
        sp38.vx = 0;
        /* Tested `>=` (not `< 0x301`): gcc branches on the false arm, so this
         * spelling puts the -0x300 arm in the `j`'s delay slot, as the target has. */
        if (dist0 - 0x100 >= 0x301) {
            sp38.vz = -0x300;
        } else {
            sp38.vz = 0x100 - dist0;
        }
        ApplyMatrixSV(&m, &sp38, &sp30);
    }
    /* `raw` (the raw return, $v0) is consumed by the subtraction; `var_s3` is the
     * s16 copy that survives the calls in $s3 and is sign-extended at its use. */
    raw = func_8012B744((void *)(arg0 + 4), &sp30);
    var_s3 = raw;
    diff = (raw - *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;
    var_a0 = diff;
    if (diff >= 0x800) {
        var_a0 = diff | 0xF000;
    }
    /* if/else (not `sd = var_a0;` + `if`): the copy has to sit BELOW the sign
     * test so optimize_reg_copy_1's forward scan cannot rewrite the test's
     * operand (cookbook 165-33); reorg then parks it in the bgez delay slot. */
    if (var_a0 < 0) {
        sd = -var_a0;
    } else {
        sd = var_a0;
    }
    var_s2 = sd;
    if (var_s2 >= 0x401) {
        return;
    }
    dist = func_80047D3C((sp30.vx - *(s16 *)(arg0 + 6)) * (sp30.vx - *(s16 *)(arg0 + 6)) +
                         (sp30.vz - *(s16 *)(arg0 + 0xE)) * (sp30.vz - *(s16 *)(arg0 + 0xE)));
    sp40.vy = 0;
    sp40.vx = 0;
    if (!(D_8019FF8A & 0x80) && dist >= 0x101 && var_s2 < 0x300) {
        D_8019FF8A |= 0x40;
        func_801A34FC(arg0, (u16 *)&sp30);
        D_8019FF8A |= 0x10;
        sp40.vz = 0xFFF00000;
    } else {
        sp40.vz = -((0x400 - sd) * arg1);
    }
    m = *(Mtx32_801A3180 *)&D_800AE620;
    RotMatrixY(var_s3, &m);
    func_800484EC((s32)&m, (s32)&sp40, (s32)&sp40);
    *(s32 *)(arg0 + 0x10) = sp40.vx;
    *(s32 *)(arg0 + 4) += sp40.vx;
    *(s32 *)(arg0 + 0x18) = sp40.vz;
    *(s32 *)(arg0 + 0xC) += sp40.vz;
}


extern void func_8012B200(u8 *a0);
extern u16 D_8019FF8A;

void func_801A34C4(s32 a0) {
    func_8012B200((u8 *)a0);
    D_8019FF8A &= 0xFFAF;
}


void func_801A34FC(s32 arg0, u16 *arg1) {
    s16 *p;
    s16 ax;
    s16 ay;

    *(u16 *)(arg0 + 0xE8) = *(u16 *)(arg1 + 0);
    *(u16 *)(arg0 + 0xEA) = *(u16 *)(arg1 + 2);
    p = (s16 *)(arg0 + 0xEC);
    p[0] = *(u16 *)(arg0 + 0xE8) - *(u16 *)(arg0 + 6);
    p[1] = *(u16 *)(arg0 + 0xEA) - *(u16 *)(arg0 + 0xE);
    if (p[0] < 0) {
        ax = -p[0];
    } else {
        ax = p[0];
    }
    *(s16 *)(arg0 + 0x106) = 0;
    if (p[1] < 0) {
        ay = -p[1];
    } else {
        ay = p[1];
    }
    if (ax < ay) {
        *(s16 *)(arg0 + 0x106) = 1;
    }
}


s32 func_801A3594(void *a0) {
    s16 buf[12];
    s16 diff;
    s16 v1;
    s16 t16;
    s16 xr;

    v1 = *(s16 *)((s32)a0 + 0x106);
    switch (v1) {
    case 0: {
        s32 tw;

        diff = *(u16 *)((s32)a0 + 0xE8) - *(u16 *)((s32)a0 + 0x6);
        buf[0] = diff;
        tw = *(s16 *)((s32)a0 + 0xEC);
        t16 = tw;
        if (tw == 0) {
            return 1;
        }
        break;
    }
    case 1: {
        s32 tw;

        diff = *(u16 *)((s32)a0 + 0xEA) - *(u16 *)((s32)a0 + 0xE);
        buf[1] = diff;
        tw = *(s16 *)((s32)a0 + 0xEE);
        t16 = tw;
        if (tw == 0) {
            return 1;
        }
        break;
    }
    default:
        goto default_case;
    }

    if (diff == 0) goto ret1;
    xr = diff ^ t16;
    if (xr >= 0) goto default_case;
ret1:
    return 1;
default_case:
    return 0;
}


typedef struct { s16 m[3][3]; s32 t[3]; } MTX_CF90_801A3624;

void func_801A3624(s32 target, u16 *cur, s32 step)
{
    s32 t;
    s32 diff;
    s32 mag;

    t = (target - *cur) & 0xFFF;
    if (t < 0x800) {
        diff = t;
    } else {
        diff = t | 0xF000;
    }
    if ((s16)diff >= 0) {
        mag = diff;
    } else {
        mag = -diff;
    }
    if ((s16)mag > (u16)step) {
        if ((s16)diff < 0) {
            *cur = *cur - step;
        } else {
            *cur = *cur + step;
        }
    } else {
        *cur = target;
    }
}


extern s32 func_8004787C(s32 a0);

void func_801A36A8(s32 a0) {
    s16 v;

    v = *(u16 *)((s32)a0 + 0x108) + 0x30;
    *(u16 *)((s32)a0 + 0x108) = v;
    *(s16 *)((s32)a0 + 0x52) = func_8004787C(v) >> 8;
}



void func_801A36F0(void *a0) {
        s32 v0 = *(u16 *)((s32)a0 + 0xA);
        s32 v1 = *(u16 *)((s32)a0 + 0x52);
        *(u16 *)((s32)a0 + 0x52) = 0;
        *(u16 *)((s32)a0 + 0x108) = 0;
        *(u16 *)((s32)a0 + 0xA) = v0 + v1;
    }


#include "common.h"

extern u16 D_801AFE34[8];

void func_801A370C(s32 a0) {
    s32 v0;
    s32 v1;

    do { v0 = *(u16 *)(a0 + 0x10A); } while (0);
    v1 = *(s32 *)(a0 + 0x20);
    v0 = v0 + 1;
    *(u16 *)(a0 + 0x10A) = v0;
    v0 = D_801AFE34[v0 & 7];
    *(u16 *)(v1 + 0x1C) = v0;
    *(u16 *)(v1 + 0x1A) = v0;
    *(u16 *)(v1 + 0x18) = v0;
}


extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern s32 *D_801AFB8C;
extern s32 D_801BF01C;
extern s32 D_801F8724;

void func_801A3744(s32 a0) {
    *(s16 *)(a0 + 0xE6) = 4;
    func_80132288(&D_801F8724, D_801AFB8C, D_801BF01C);
    *(s16 *)(a0 + 0x100) = -0x40;
}


#include "common.h"

extern void func_801A395C(s32 a0, s32 a1);
extern void func_8013240C(s32 a0);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A860(void *a0, int a1);
extern void func_801A3A6C(u8 *s0);
extern void func_8012B2CC(s32 a0);
extern void func_801A7D18(s32 arg0);
extern s32 func_801A8564(s32 a0);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern void func_801292C8(u8 *a0);

extern s32 D_801B6E94[0x11];
extern u8 D_801EF9A8;
extern s32 D_801F8724;
extern s32 D_801F8730;
extern s32 D_801BC9EC;
extern s32 *D_801AFB7C[];
extern u16 D_8019FF8A;

/* Three zero-byte levers carry this body; all three are load-bearing (single-axis A/B'd):
 *
 *  1. `y = arg1 + zr` with `zr` pinned to $0 (§36 "$0-add opaque copy").  The target keeps
 *     TWO callee-saved registers holding arg1 ($s2 = the parameter home, $s1 = a copy born
 *     after the jal).  A plain `y = arg1;` is head-promoted by cse.c make_regs_eqv and the
 *     copy vanishes (LENGTH-DRIFT -1, and $s0/$s1 instead of $s0/$s1/$s2).
 *  2. The non-volatile re-tie `__asm__("" : "=r"(y) : "0"(y))` gives `y` a second RTL SET,
 *     which kills the sched1 birthing boost on the copy and emits it BEFORE the call's
 *     return-value copy — so dbr steals `addu $a0,$v0,$zero` for the bltz delay slot
 *     instead of the arg1 copy (§47-addendum / §34 reg_n_sets==2).
 *  3. `goto ret0` instead of `return 0` after the func_80132288 tail.  With an in-block
 *     `return 0` the tail block's rare_destination flips and reorg refuses to steal
 *     `addiu $v0,$zero,3` into the `bnez $v0` delay slot (an unfillable +1 nop).  Routing
 *     the exit through one shared `ret0:` tail restores the fill (§16 / §3-B shared-ret0).
 *
 * `t <<= 16; v1 = t >> 16;` (rather than `v1 = (s16)t;`) makes the sll reuse $v0 in place,
 * which is what stops dbr from sinking `sh $v0,0xE6($s0)` into the bltz delay slot.
 */
s32 func_801A3798(s32 s0, s32 arg1) {
    s32 v0;
    s32 v1;
    u16 y;
    s32 t;
    s32 p;
    u16 f9;

    y = arg1 + 0;
    v0 = ((s32 (*)(s32, s32))func_801A395C)(s0, (s16)(*(u16 *)(s0 + 0x100) - 0x240));
    v1 = *(s16 *)(s0 + 0xE6);
    if (v1 >= 0) {
        func_8013240C((s32)&D_801F8724);
        if (D_801F8730 & 0x4000) {
            t = *(u16 *)(s0 + 0xE6) - 1;
            *(u16 *)(s0 + 0xE6) = t;
            t <<= 16;
            v1 = t >> 16;
            if (v1 >= 0) {
                if (v1 >= 3) {
                    if (v1 != 3) {
                        goto other;
                    }
                    func_8001C924(*(s32 *)(s0 + 0x20), &D_801BC9EC);
                    if (*(s32 *)(s0 + 0xD4) != 0) {
                        func_801A7D18(*(s32 *)(s0 + 0xD4));
                        *(s32 *)(s0 + 0xD4) = 0;
                    }
                    func_801A3A6C((u8 *)s0);
                    *(u16 *)(s0 + 0x100) = 0;
                    func_8012B2CC(s0);
                    if ((arg1 << 16) != 0) {
                        *(s32 *)(s0 + 0xD4) = func_801A8564(s0);
                    }
                }
                func_80132288(&D_801F8724, D_801AFB7C[*(s16 *)(s0 + 0xE6)], D_801BC9EC);
                goto ret0;
            }
        other:
            func_8001C924(*(s32 *)(s0 + 0x20), D_801B6E94);
            func_8012A860((void *)s0, (int)&D_801EF9A8);
            if ((y << 16) != 0) {
                f9 = D_8019FF8A & 0xFFF7;
                p = *(s32 *)(s0 + 0xD4);
                D_8019FF8A = f9;
                if (p != 0) {
                    func_801292C8((u8 *)p);
                }
            }
        }
    ret0:
        return 0;
    }
    return (*(s16 *)(s0 + 0x98) == 0) && (v0 != 0);
}


#include "common.h"

void func_801A395C(s32 a0, s32 a1) {
    s32 ret;
    s16 cur;
    s16 t;
    s32 overshot;

    t = (s16)a1;
    cur = *(s16 *)(a0 + 0xA);
    if (cur == t) {
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
        ret = 1;
    } else {
        if (t < cur) {
            cur -= 2;
            *(s16 *)(a0 + 0xA) = cur;
            overshot = (t < cur);
        } else {
            cur += 2;
            *(s16 *)(a0 + 0xA) = cur;
            overshot = (cur < t);
        }
        if (overshot) {
            ret = 0;
        } else {
            *(s16 *)(a0 + 0xA) = t;
            ret = 1;
        }
    }
    __asm__ __volatile__("" :: "r"(ret));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
}


extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);

typedef struct { s16 vx, vy, vz, pad; } SVec_801A39D0;

void func_801A39D0(s32 param_1)
{
    SVec_801A39D0 sv;
    s32 flag;

    func_8004914C((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(param_1 + 0x20) + 0x34));

    sv.vx = 0;
    sv.vy = -0x40;
    sv.vz = 0x30;
    RotTransSV((s32)&sv, (s32)&sv, &flag);

    *(s16 *)(param_1 + 0x06) = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48) = sv.vx;
    *(s16 *)(param_1 + 0x0A) = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C) = sv.vy;
    *(s16 *)(param_1 + 0x0E) = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50) = sv.vz;
}


extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);

void func_801A3A6C(u8 *s0)
{
    s16 vec[3];           /* sp+0x10 */
    s32 flag;             /* sp+0x18 */

    func_8004914C((void *)(*(s32 *)(s0 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(s0 + 0x20) + 0x34));

    vec[1] = 0x40;
    vec[0] = 0;
    vec[2] = -0x30;
    RotTransSV((s32)vec, (s32)vec, &flag);

    *(s16 *)(s0 + 0x6) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x48) = vec[0];
    *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4C) = vec[1];
    *(s16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x50) = vec[2];
}


extern s32 D_801F8864;

void func_801A3B08(s32 a0) {
    D_801F8864 = 0;
}


#include "common.h"

typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_801A3B18;
typedef struct { s16 vx, vy, vz, pad; } SVec_801A3B18;

extern void RotMatrixY(s32 a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8014CB8C(void);
extern s32 func_8017267C(s32 *a0);
extern void ApplyRotMatrixLV(void *in, void *out);

extern s16 D_80126B5E;
extern s16 D_80126B62;
extern s16 D_80126B66;
extern s32 D_80126B58[4];
extern s32 D_801F8864;

void func_801A3B18(s32 param_1)
{
    Mtx32_801A3B18 mtx;   /* sp+0x10 */
    SVec_801A3B18 sv;     /* sp+0x30 */
    SVec_801A3B18 sv2;    /* sp+0x38 */
    s32 vec[4];           /* sp+0x40 */
    s32 flag;             /* sp+0x50 */
    s32 v0;
    s32 amt;
    s16 ang;
    s16 mag;
    s32 *p;
    /* D_800AE620 is the shared 32-byte matrix global; this TU already declares it
     * later as `extern Mtx32_801A90D8 D_800AE620;` (md_SC07_004.c:1569). Declared
     * here at BLOCK scope on purpose: a second file-scope spelling is a hard
     * `conflicting types` error in gcc-2.7.2, while a block-scope one is only a
     * warning — and re-typedef'ing Mtx32_801A90D8 above line 1565 would break the
     * definition that already lives there. */
    extern s32 D_800AE620[8];

    mtx = *(Mtx32_801A3B18 *)&D_800AE620;

    RotMatrixY(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), &mtx);

    mtx.t[0] = *(s16 *)(param_1 + 0x6);
    mtx.t[1] = *(s16 *)(param_1 + 0xA);
    mtx.t[2] = *(s16 *)(param_1 + 0xE);
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    sv.vy = 0;
    sv.vx = 0;
    sv.vz = 0x80;
    RotTransSV((s32)&sv, (s32)&sv, &flag);

    sv2.vx = (u16)D_80126B5E;
    sv2.vy = (u16)D_80126B62;
    sv2.vz = (u16)D_80126B66;

    p = D_80126B58;
    ang = (func_8012B70C((s16 *)&sv, (s16 *)&sv2) -
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12)) & 0xFFF;
    if (ang >= 0x800) {
        ang |= 0xF000;
    }
    if (ang < 0) {
        mag = -ang;
    } else {
        mag = ang;
    }

    v0 = ((s32 (*)(s32))func_8012BE54)(param_1);

    if (func_8014CB8C() == 0 && v0 <= 0x23FFF && mag < 0x200 &&
        func_8017267C(p) == 0) {
        if (D_801F8864 > -0x1E0000) {
            D_801F8864 -= 0xC000;
        }
    } else {
        if (D_801F8864 < 0) {
            D_801F8864 += 0x10000;
            if (D_801F8864 > 0) {
                D_801F8864 = 0;
            }
        }
    }

    amt = D_801F8864;
    if (amt != 0) {
        vec[1] = 0;
        vec[0] = 0;
        vec[2] = amt;
        ApplyRotMatrixLV(vec, vec);
        p[1] += vec[0];
        p[3] += vec[2];
    }
}


typedef struct { s32 w[8]; } Mtx32_801A3D60;

extern void RotMatrixY(s32 a0, void *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_8017267C(s32 *a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

extern s32 D_801F8864;
extern s32 D_80126B58[4];
extern s32 D_80126B5C;
extern s32 D_80126B64;

void func_801A3D60(s32 a0)
{
    /* D_800AE620 is the shared 32-byte matrix global; this TU's real file-scope
     * spelling (`extern Mtx32_801A90D8 D_800AE620;`) is declared LATER in the
     * file. A second file-scope spelling here is a hard `conflicting types`
     * error in gcc-2.7.2 (see func_801A3180 / func_801A3B18 above it), so this
     * copy is BLOCK scope, matching this TU's own house style. */
    extern s32 D_800AE620[8];
    Mtx32_801A3D60 m;   /* sp+0x10 */
    s32 buf[3];         /* sp+0x30 */
    s32 s0;
    s32 *s1;
    s32 r;

    s0 = a0;
    m = *(Mtx32_801A3D60 *)&D_800AE620;
    s1 = (s32 *)&m;

    if (D_801F8864 <= 0xAFFFF) {
        D_801F8864 = D_801F8864 + 0x4000;
    }

    r = ((s32 (*)(s32))func_8012BE54)(s0);
    RotMatrixY((s16)func_8012B8A4((s16 *)s0), s1);
    s0 = r;

    if (D_801F8864 != 0 && s0 >= 0x101) {
        if (func_8017267C(D_80126B58) == 0) {
            buf[1] = 0;
            buf[0] = 0;
            buf[2] = D_801F8864;
            func_800484EC((s32)s1, (s32)buf, (s32)buf);
            D_80126B5C += buf[0];
            D_80126B64 += buf[2];
        }
    }
}


void func_801A3EA8(s32 param_1) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_801A54F0();

    if (func_801A54F0(param_1, 0x20)) {
        D_80126B98 = 0x60;
        D_80126B96 |= 0x4000;
    }
}


extern u16 D_8019FF8A;
extern s16 D_801F8860;

void func_801A3EEC(s32 a0) {
    D_801F8860 = a0;
    D_8019FF8A |= 0x820;
}


extern u16 D_8019FF8A;
extern s16 D_801F8860;
extern s32 func_8013D13C(s16 a0);
extern s32 func_8018184C(s16 a0);

void func_801A3F10(void) {
    if (D_8019FF8A & 0x20) {
        if (func_8013D13C(D_801F8860) == 0) {
            D_8019FF8A &= 0xFFDF;
        }
    }
    if (D_8019FF8A & 0x800) {
        if (func_8018184C(D_801F8860) == 0) {
            D_8019FF8A &= 0xF7FF;
        }
    }
}


extern void func_801439C0(u8 *a0);

void func_801A3FB0(void *arg0) {
    void *s0;
    u8 *a0;
    s32 *v0p;

    s0 = arg0;
    v0p = *(s32 **)((char *)s0 + 0x20);
    *(s32 *)((char *)v0p + 4) |= 0x80000000;

    a0 = *(u8 **)((char *)s0 + 0xD0);
    if (a0 != NULL) {
        func_801439C0(a0);
        *(u8 **)((char *)s0 + 0xD0) = NULL;
    }
}


extern s32 func_80143970(s32 a0);

void func_801A4008(s32 a0) {
    *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
    if (*(s32 *)(a0 + 0xD0) == 0) {
        *(s32 *)(a0 + 0xD0) = func_80143970(a0);
    }
}


extern s32 func_8004787C(s32 a0);

void func_801A4060(s32 a0) {
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = (func_8004787C(*(s16 *)(a0 + 0xFE)) >> 3) + 0x1000;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = (func_8004787C(*(s16 *)(a0 + 0xFE) + 0x800) >> 3) + 0x1000;
    *(u16 *)(a0 + 0xFE) += 0x80;
}


typedef struct { char c[4]; } Blk4_801A40CC;

extern void func_800233CC(void *a0, unsigned short a1);
extern void func_801A417C(s32 arg0);
extern u8 D_801F8744[];
extern u8 D_801AFEF8[];
extern s32 D_801A01B4[];

__asm__(  // !FAKE: instruction .section — REFUSED asm-data: a `.section` block defines data as assembly (a rodata carve, not a compiler steer) — T7 (P36 rung B tus11)
    ".section .rodata\n"
    "dlabel D_801A01B4\n"
    ".word 0x00000000\n"
    ".word 0x00000000\n"
    "enddlabel D_801A01B4\n"
    ".section .text\n"
);

void func_801A40CC(s32 a0) {
    u8 *base;
    u8 *p;
    u8 *q;
    s32 i;

    i = 0;
    base = D_801F8744;
    q = base + 4;
    p = base;

    for (; i < 4; i++) {
        func_800233CC((void *)p, 0x40);
        *(Blk4_801A40CC *)p = *(Blk4_801A40CC *)&D_801AFEF8;
        *(Blk4_801A40CC *)q = *(Blk4_801A40CC *)&D_801A01B4;
        q += 0x40;
        p += 0x40;
    }

    func_801A417C(a0);
}



extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_801A417C(s32 arg0) {
    s32 i;

    for (i = 0; i < 15; i++) {
        func_8012C658(0x31f, i, arg0);
    }
}


extern u8 D_801F8744[];

void func_801A41CC(void) {
    s32 i;
    u8 *src;
    s32 n;
    s32 dst;
    i = 1;
    src = D_801F8744;
    n = 4;
    dst = 0x40;
    while (i < 4) {
        D_801F8744[dst + 0] = (src[0] >> 2) * (n - i);
        D_801F8744[dst + 1] = (src[1] >> 2) * (n - i);
        D_801F8744[dst + 2] = (src[2] >> 2) * (n - i);
        dst += 0x40;
        i++;
    }
}


extern u8 D_801F8744[];
extern s16 D_801F8870;
extern s16 D_801F8872;
extern s16 D_801F8874;
extern s16 D_801F8878;
extern s16 D_801F887A;
extern s16 D_801F887C;
extern s16 D_801F8880;
extern s16 D_801F8882;
extern s16 D_801F8884;

void func_801A4258(void) {
    s16 *p;
    p = &D_801F8870;

    if (*p != D_801F8878) {
        *p += (u16)D_801F8880;
        D_801F8744[0] = *p >> 7;
    }

    if (D_801F8872 != D_801F887A) {
        D_801F8872 += (u16)D_801F8882;
        D_801F8744[1] = D_801F8872 >> 7;
    }

    if (D_801F8874 != D_801F887C) {
        D_801F8874 += (u16)D_801F8884;
        D_801F8744[2] = D_801F8874 >> 7;
    }
}


extern u8 D_801F8744[];
extern u8 D_801AFEF8[];
extern u8 D_801AFEF9[];
extern u8 D_801AFEFA[];
extern s16 D_801F8870;
extern s16 D_801F8872;
extern s16 D_801F8874;
extern s16 D_801F8878;
extern s16 D_801F887A;
extern s16 D_801F887C;
extern s16 D_801F8880;
extern s16 D_801F8882;
extern s16 D_801F8884;

void func_801A4328(s32 a0) {
    s32 idx;
    s32 b0;
    s32 b1;
    s32 b2;
    s32 p;
    s32 q;
    s32 r;

    idx = a0 * 4;
    b0 = D_801F8744[0];
    b1 = D_801F8744[1];
    b2 = D_801F8744[2];
    D_801F8870 = b0 << 7;
    D_801F8872 = b1 << 7;
    D_801F8874 = b2 << 7;
    p = D_801AFEF8[idx];
    D_801F8878 = p << 7;
    q = D_801AFEF9[idx];
    D_801F887A = q << 7;
    r = D_801AFEFA[idx];
    D_801F8880 = (p - b0) << 4;
    D_801F8882 = (q - b1) << 4;
    D_801F887C = r << 7;
    D_801F8884 = (r - b2) << 4;
}


#include "common.h"

extern s32 D_801F8720;
extern s32 func_801819CC(s32 a0);

void func_801A43EC(s32 a0) {
    if (D_801F8720 == 0) {
        D_801F8720 = func_801819CC(a0);
    }
}




void func_801A4420(void *a0) {

    extern void (*D_801AFF34[])(void);
    D_801AFF34[*(u16 *)((s32)a0 + 0x2)]();
}


extern u16 D_8019FF8A;
extern void func_801A9C00(void *a0);

void func_801A445C(void *arg0) {
    u16 v0;
    s32 v1;

    v0 = *(u16 *)((u8 *)arg0 + 0x5C);
    v1 = *(s16 *)((u8 *)arg0 + 0xFE);
    *(u8 *)((u8 *)arg0 + 0xC1) = 0;
    *(u16 *)((u8 *)arg0 + 0x5E) = 0;
    *(u16 *)((u8 *)arg0 + 0x5C) = v0 & 0xFFFE;
    if (v1 == 0) {
        if ((D_8019FF8A & 0x200) == 0) {
            func_801A9C00(arg0);
            *(s16 *)((u8 *)arg0 + 0xFE) = 8;
        }
    }
}


extern s32 func_8012C31C(void);
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

s32 func_801A44C4(s32 a0) {
    s32 v0;
    s32 v1;
    s16 sp[10];

    if (a0 != 0 && *(u16 *)a0 != 0) {
        sp[0] = *(u16 *)(a0 + 0x6);
        sp[1] = *(u16 *)(a0 + 0xA);
        sp[2] = *(u16 *)(a0 + 0xE);
    } else {
        sp[2] = 0;
        sp[1] = 0;
        sp[0] = 0;
    }
    sp[3] = 0x332;
    sp[5] = 0;
    sp[4] = 0;
    *(s32 *)&sp[8] = 0;
    sp[7] = 0;
    sp[6] = 0x7FFF;
    v0 = func_8012C31C();
    if (v0 != 0) {
        v1 = func_8012C890((s32)&sp[0], v0, a0);
    } else {
        v1 = 0;
    }
    return v1;
}


#include "common.h"

/* Local 3x s16 vector (+pad) -- same shape as SV_801AAF8C used later in this
 * TU by func_801AAF8C, but declared under our own name because this
 * function's INCLUDE_ASM site precedes that typedef in file order. */
typedef struct { s16 vx, vy, vz, pad; } SV3_801A4570;

/* fleet-dominant spelling (decl_prior, n=1383): canonical void -> cast at use */
extern void func_8012BE54(s32 a0);
/* fleet-dominant spelling (decl_prior, n=1347) */
extern s32  func_8012B8A4(s16 *a0);
/* TU already declares these identically (func_801AAF8C block, this file) */
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
/* local sibling in this TU, still INCLUDE_ASM; only ever called with 1 arg */
extern void func_801A9C00(void *a0);

/* TU already declares these identically (func_801AAF8C block, this file) */
extern s16  D_80126B5E;
extern s16  D_80126B62;
extern s16  D_80126B66;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];

void func_801A4570(void *arg0)
{
    SV3_801A4570 localA; /* sp+0x18 */
    SV3_801A4570 localB; /* sp+0x20 */
    s16 v0;

    v0 = *(s16 *)((u8 *)arg0 + 0xFE);
    if (v0 != 0) {
        *(s16 *)((u8 *)arg0 + 0xFE) = v0 - 1;
        return;
    }

    if (((s32 (*)(s32))func_8012BE54)((s32)arg0) >= 0x640) {
        return;
    }

    {
        u16 diff = (u16)D_80126B62 -
            (*(u16 *)((u8 *)arg0 + 0xA) + *(u16 *)((u8 *)arg0 + 0x52)) + 0x8F;
        if (diff >= 0xDF) {
            return;
        }
    }

    func_801A9C00(arg0);
    *(s16 *)((u8 *)arg0 + 0xFE) = 8;

    localA.vx = *(u16 *)((u8 *)arg0 + 0x6) + *(u16 *)((u8 *)arg0 + 0x50);
    localA.vy = *(u16 *)((u8 *)arg0 + 0xA) + *(u16 *)((u8 *)arg0 + 0x52) - 0x40;
    localA.vz = *(u16 *)((u8 *)arg0 + 0xE) + *(u16 *)((u8 *)arg0 + 0x54);

    localB.vx = (u16)D_80126B5E;
    localB.vy = (u16)D_80126B62 - 0x20;
    localB.vz = (u16)D_80126B66;

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&localA, (s32)&localB) != 0) {
        s32 dist = func_8012B8A4((s16 *)arg0);
        func_8012F568(1, 4, dist, 0x40, (s32)&localB, (s32)D_801152A8);
    }
}


void func_801A46B8(s32 arg0) {
    *(u16 *)(*(s32 *)(arg0 + 0xD8) + 0x5C) &= 0x7FFF;
}


void func_801A46D4(s32 a0) {
    s32 v1;
    v1 = *(s32 *)(a0 + 0xD8);
    *(u16 *)(v1 + 0x5C) |= 0x8000;
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A46F0(s32 *a0) {
    s32 *v0;

    v0 = *(s32 **)(((u8 *)a0) + 0x20);
    *(s32 *)(((u8 *)a0) + 0x1C) = 0;
    *(s16 *)(((u8 *)v0) + 0x1C) = 0;
    *(s16 *)(((u8 *)v0) + 0x1A) = 0;
    *(s16 *)(((u8 *)v0) + 0x18) = 0;
    func_8012AD44(a0, 1);
}


#include "common.h"

extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern void func_8013240C(s32 a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_801A4A18(s32 a0);

extern s32 D_801F8888;
extern s32 D_801F8894;
extern s32 D_801F8898;
extern s32 D_801B001C;
extern s32 D_801B002C;
extern s32 D_801B003C;
extern s32 D_801B004C;
extern s32 D_801B005C;
extern s32 D_801B006C;
extern s32 D_801B75EC;
extern u8 D_801B80FC[];

void func_801A4724(void *arg0)
{
    s32 mirror;
    u16 state;
    s32 newState;

    state = *(u16 *)((u8 *)arg0 + 0x34);
    mirror = *(s32 *)((u8 *)arg0 + 0xCC);

    switch (state) {
    case 0:
        if (*(s16 *)((u8 *)arg0 + 0x70) != 0) {
            break;
        }
        if (*(s32 *)((u8 *)arg0 + 0x1C) != 0x16) {
            break;
        }
        func_80132288(&D_801F8888, &D_801B001C, D_801B75EC);
        if (mirror != 0) {
            func_80132288(&D_801F8898, &D_801B002C, *(s32 *)D_801B80FC);
        }
        goto inc;
    case 1:
    case 3:
        func_8013240C((s32)&D_801F8888);
        if (mirror != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        if (!(D_801F8894 & 0x4000)) {
            break;
        }
        goto inc;
    case 2:
        if (*(s32 *)((u8 *)arg0 + 0x1C) != 0x2F) {
            break;
        }
        func_80132288(&D_801F8888, &D_801B003C, D_801B75EC);
        if (mirror != 0) {
            func_80132288(&D_801F8898, &D_801B004C, *(s32 *)D_801B80FC);
        }
        goto inc;
    case 4:
        if (*(s32 *)((u8 *)arg0 + 0x1C) != 0x3C) {
            break;
        }
        func_80132288(&D_801F8888, &D_801B005C, D_801B75EC);
        if (mirror != 0) {
            func_80132288(&D_801F8898, &D_801B006C, *(s32 *)D_801B80FC);
        }
        goto inc;

    inc:
        *(u16 *)((u8 *)arg0 + 0x34) = *(u16 *)((u8 *)arg0 + 0x34) + 1;
        break;

    case 5:
        func_8013240C((s32)&D_801F8888);
        if (mirror != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        if (!(D_801F8894 & 0x4000)) {
            break;
        }
        func_801A4A18((s32)arg0);
        func_801A4A18(*(s32 *)((u8 *)arg0 + 0x6C));
        break;
    }

    newState = *(s32 *)((u8 *)arg0 + 0x1C) + 1;
    *(s32 *)((u8 *)arg0 + 0x1C) = newState;
    if (newState < 0x33) {
        *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x1A) = (newState << 12) / 50;
        *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x1C) = *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x1A);
        *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x14) = (0x32 - *(s32 *)((u8 *)arg0 + 0x1C)) << 4;
        if (*(s16 *)((u8 *)arg0 + 0x70) == 0) {
            *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x18) = *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x1A);
            *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x14) = -(s32)*(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x14);
        } else {
            *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x18) = -(s32)*(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x1A);
        }
    }

    func_80132784((s32)arg0, *(s32 *)((u8 *)arg0 + 0x64), 0);
}


#include "common.h"

extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);

extern s32 D_801F8888;
extern s32 D_801F8898;
extern s32 D_801B007C;
extern s32 D_801B00B4;
extern s32 D_801B75EC;
extern u8 D_801B80FC[];

void func_801A4A18(s32 a0)
{
    s16 cond;
    s32 mirror;

    cond = *(s16 *)(a0 + 0x70);
    mirror = *(s32 *)(a0 + 0xCC);

    if (cond == 0) {
        func_80132288(&D_801F8888, &D_801B007C, D_801B75EC);
        if (mirror != 0) {
            func_80132288(&D_801F8898, &D_801B00B4, (*(s32 *)D_801B80FC));
        }
    }

    *(s16 *)(a0 + 0x84) = 0;
    func_8012AD44((s32 *)a0, 2);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A4AAC(void *a0) {
    func_8012AD44((s32 *)a0, 3);
}


#include "common.h"

extern void func_8013240C(s32 a0);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012C218(void *a0);

extern s32 D_801F8888;
extern s32 D_801F888C;
extern s32 D_801F888E;
extern s32 D_801F8894;
extern s32 D_801F8898;
extern s32 D_801B00EC;
extern s32 D_801B00FC;
extern s32 D_801B010C;
extern s32 D_801B011C;
extern s32 D_801B012C;
extern s32 D_801B013C;
extern s32 D_801B75EC;
extern u8 D_801B80FC[];
extern u16 D_8019FF8A;

void func_801A4ACC(void *a0)
{
    s32 *s0;
    s32 s1;
    s32 v0;
    s32 v1;

    s0 = (s32 *)a0;
    v1 = *(u16 *)((s32)s0 + 0x34);
    s1 = *(s32 *)((s32)s0 + 0xCC);
    if ((u32)v1 >= 5) {
        goto end;
    }

    switch (v1) {
    case 0: {
        s32 *s2;

        if (*(s16 *)((s32)s0 + 0x70) != 0) {
            goto end;
        }
        s2 = &D_801F8888;
        func_8013240C((s32)s2);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        if ((*(u16 *)&D_801F888C | *(u16 *)&D_801F888E) != 0) {
            goto end;
        }
        func_80132288(s2, &D_801B00EC, D_801B75EC);
        if (s1 != 0) {
            func_80132288(&D_801F8898, &D_801B00FC, *(s32 *)D_801B80FC);
        }
        func_8002D4C8(4, 0xABE);
        goto inc;
    }
    case 1: {
        s32 *s2;

        s2 = &D_801F8888;
        func_8013240C((s32)s2);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        if ((D_801F8894 & 0x4000) == 0) {
            goto end;
        }
        func_80132288(s2, &D_801B010C, D_801B75EC);
        if (s1 != 0) {
            func_80132288(&D_801F8898, &D_801B011C, *(s32 *)D_801B80FC);
        }
        goto inc;
    }
    case 2: {
        s32 *s2;

        s2 = &D_801F8888;
        func_8013240C((s32)s2);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        if ((D_801F8894 & 0x4000) == 0) {
            goto end;
        }
        func_80132288(s2, &D_801B012C, D_801B75EC);
        if (s1 != 0) {
            func_80132288(&D_801F8898, &D_801B013C, *(s32 *)D_801B80FC);
        }
    }
    inc:
        *(u16 *)((s32)s0 + 0x34) += 1;
        goto end;
    case 3:
        func_8013240C((s32)&D_801F8888);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        if ((D_801F8894 & 0x4000) == 0) {
            goto end;
        }
        v0 = *(u16 *)((s32)s0 + 0x34);
        v1 = *(s32 *)((s32)s0 + 0x6C);
        *(u16 *)((s32)s0 + 0x34) = v0 + 1;
        if (v1 == 0) {
            goto end;
        }
        *(u16 *)(v1 + 0x34) = 4;
        goto end;
    case 4:
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) -= 0x80;
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1C) = *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A);
        if (*(s16 *)((s32)s0 + 0x70) != 0) {
            goto dec;
        }
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x14) -= 0x10;
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18) = *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A);
        if (*(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) > 0) {
            goto end;
        }
        *(s32 *)(*(s32 *)((s32)s0 + 0x64) + 0xCC) = 0;
        if (s1 != 0) {
            func_8012C218((void *)s1);
        }
        func_8012C218((void *)s0);
        D_8019FF8A &= 0xFFFD;
        return;
    dec:
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x14) += 0x10;
        *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18) = -*(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A);
        if (*(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) > 0) {
            goto end;
        }
        if (s1 != 0) {
            func_8012C218((void *)s1);
        }
        func_8012C218((void *)s0);
        return;
    }

end:
    func_80132784((s32)s0, *(s32 *)((s32)s0 + 0x64), 0);
}




void func_801A4E80(void *a0) {

    extern void (*D_801B014C[])(void);
    D_801B014C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Mat32 layout (engine_types.h:637), local-suffixed for standalone compile:
 * { s32 w0,w4,w8,wC; s16 h10,hpad; s32 t0,t1,t2; } == 8 words / 32 bytes. */
typedef struct { s32 w[8]; } Mtx32_801A90D8;
typedef struct { s32 w0, w4, w8, wC; s16 h10, hpad; s32 t0, t1, t2; } Mat32_801A4EBC;

extern s32 D_801F888C;
extern Mtx32_801A90D8 D_800AE620;
extern void func_8002D4C8(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_801A4FDC(void);
extern void func_801A5094(void);

void func_801A4EBC(u8 *a0)
{
    u8 *s1;
    Mat32_801A4EBC m;
    void *mp;
    s32 v0;
    s32 *p;

    s1 = a0;
    p = &D_801F888C;
    v0 = *(u16 *)p;
    if ((u32)(v0 - 2) < 3) {
        if (*p == 2) {
            func_8002D4C8(0xABE, 0);
        }

        m = *(Mat32_801A4EBC *)&D_800AE620;
        mp = &m;

        RotMatrixY(*(s16 *)(*(s32 *)(*(s32 *)(s1 + 0x64) + 0x20) + 0x12), mp);

        m.t0 = *(s16 *)(*(s32 *)(s1 + 0x64) + 0x6);
        m.t1 = *(s16 *)(*(s32 *)(s1 + 0x64) + 0xA);
        m.t2 = *(s16 *)(*(s32 *)(s1 + 0x64) + 0xE);

        func_8004914C(mp);
        func_800491AC(mp);
        func_801A4FDC();
        func_801A5094();
    }
}


#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } Vec16_801A4FDC;
typedef struct { s32 vx, vy, vz, pad; } Vec32_801A4FDC;

extern int rand(void);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern u8 * func_801290DC(s32 a0, u8 *a1);
extern void ApplyRotMatrixLV(void *in, void *out);

void func_801A4FDC(void)
{
    Vec16_801A4FDC vec0;
    Vec32_801A4FDC vec1;
    s32 flag;
    s32 p;

    vec0.vx = (rand() & 0xFF) - 0x80;
    vec0.vy = 0;
    vec0.vz = -(rand() & 0x7F);

    RotTransSV((s32)&vec0, (s32)&vec0, &flag);

    vec0.vy = -0x200;
    p = (s32)func_801290DC(0x22, (u8 *)&vec0);
    if (p != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC020;
        vec1.vx = 0;
        vec1.vy = -0x40000;
        vec1.vz = -(((rand() & 0xF) + 0x1C) << 16);
        ApplyRotMatrixLV(&vec1, (void *)(p + 0x10));
        *(s16 *)(p + 0x34) = 0x3000;
    }
}


#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } Vec16_801A5094;
typedef struct { s32 vx, vy, vz, pad; } Vec32_801A5094;

extern int rand(void);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern u8 * func_801290DC(s32 a0, u8 *a1);
extern void ApplyRotMatrixLV(void *in, void *out);
extern u8 D_801F8744[];
extern u8 D_801F8747[];

void func_801A5094(void)
{
    Vec16_801A5094 vec0;
    Vec32_801A5094 vec1;
    s32 flag;
    s32 p;
    s32 r;

    vec0.vx = (rand() % 320) - 160;
    vec0.vy = -((rand() & 0x7F) + 0x40);
    vec0.vz = -((rand() & 0x3F) + 0x20);

    RotTransSV((s32)&vec0, (s32)&vec0, &flag);

    p = (s32)func_801290DC(0x2E, (u8 *)&vec0);
    if (p != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC020;
        vec1.vx = 0;
        vec1.vy = 0;
        r = rand();
        vec1.vz = -(((r & 7) + 0x20) << 16);
        ApplyRotMatrixLV(&vec1, (void *)(p + 0x10));
        D_801F8747[0] = 1;
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
        *(s32 *)(p + 0x34) = *(s32 *)D_801F8744;
        *(s16 *)(p + 0x30) = 6;
    }
}


#include "common.h"

extern void func_80133060(u8 *a0, s32 *a1, s32 a2);

typedef struct {
    s32 w[8];
} Blk32_801A5194;

void func_801A5194(s32 arg0) {
    s32 sp10[3];

    sp10[0] = *(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x48) << 16;
    sp10[1] = *(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x4C) << 16;
    sp10[2] = *(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x50) << 16;
    func_80133060((u8 *)sp10, (s32 *)(arg0 + 4), -0x60);

    *(Blk32_801A5194 *)(*(s32 *)(arg0 + 0x20) + 0x34) =
        *(Blk32_801A5194 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x34);
    *(Blk32_801A5194 *)(*(s32 *)(arg0 + 0x20) + 0x54) =
        *(Blk32_801A5194 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x54);

    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x48) = *(s16 *)(arg0 + 0x6);
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x4C) = *(s16 *)(arg0 + 0xA);
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x50) = *(s16 *)(arg0 + 0xE);
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x68) = *(s16 *)(arg0 + 0x6);
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x6C) = *(s16 *)(arg0 + 0xA);
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x70) = *(s16 *)(arg0 + 0xE);

    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) =
        (*(s16 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x18) * 7) >> 3;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) =
        (*(s16 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x1A) * 7) >> 3;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1C) =
        (*(s16 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x1C) * 7) >> 3;

    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) =
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) | 1;
}




void func_801A53B8(void *a0) {

    extern void (*D_801B0160[])(void);
    D_801B0160[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801A53F4(s32 *arg0)
{
    func_8012AD44(arg0, 1);
}


void func_801A5414(s32 param_1) {
    extern void func_8012B178(s32 a0, s32 a1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern void func_8002D4C8(s32 a0, s32 a1);

    *(s32 *)(param_1 + 0xF0) = -0xC0000;
    func_8012B178(param_1, -0xC0000);
    *(s32 *)(param_1 + 0x1C) = 0x18;
    *(s16 *)(param_1 + 0x100) = 1;
    func_8012AD44((s32 *)param_1, 2);
    func_8002D4C8(0xABB, 0);
}




void func_801A5470(void *a0) {

    extern void (*D_801B0168[])(void);
    D_801B0168[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801A54AC(s32 param_1) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_801A54F0();

    if (func_801A54F0(param_1, 0x40)) {
        D_80126B98 = 0x78;
        D_80126B96 |= 0x4000;
    }
}


#include "common.h"

extern void RotMatrixY(s32 a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_801A54F0;
typedef struct { s16 vx, vy, vz, pad; } SV_801A54F0;

extern Mtx32_801A90D8 D_800AE620;
extern s16 D_80126B62;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8 D_801152A8[];

s32 func_801A54F0(s32 param_1, s32 param_2)
{
    Mtx32_801A54F0 mtx;  /* sp+0x18 */
    SV_801A54F0 pos;     /* sp+0x38 */
    SV_801A54F0 vec2;    /* sp+0x40 */
    SV_801A54F0 out;     /* sp+0x48 */
    s32 v1;
    s32 t;

    mtx = *(Mtx32_801A54F0 *)&(*(Mtx32_801A54F0 *)&D_800AE620);

    RotMatrixY((s16)func_8012B8A4((s16 *)param_1), &mtx);
    func_8004914C(&mtx);

    v1 = *(u16 *)(param_1 + 6);
    t = (u16)D_80126B62 - 0x20;
    pos.vx = v1;
    arr0:
    mtx.t[0] = (s16)v1;
    pos.vy = t;
    mtx.t[1] = (s16)t;
    pos.vz = *(u16 *)(param_1 + 0xE);
    mtx.t[2] = pos.vz;
    func_800491AC(&mtx);

    vec2.vy = 0;
    vec2.vx = 0;
    vec2.vz = -param_2;
    RotTransSV((s32)&vec2, (s32)&vec2, &out);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&pos, (s32)&vec2) != 0) {
        func_8012F568(1, 1, 0, 0xA, (s32)&vec2, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_801A5654(s32 param_1, s16 param_2, s32 param_3) {
    s32 v0;

    v0 = func_8012C658(0x339, param_3, param_1);
    if (v0 != 0) {
        *(s16 *)(v0 + 0xFE) = param_2;
    }
}


#include "common.h"

/* PsyQ MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14.
 * D_800AE620 is a shared 32-byte "identity-ish" matrix global also seen
 * (same layout, different local names) in gsgap3.c (Mtx32) and several
 * ov_SC03_099 TUs (Blk20). No declaration for it exists earlier in THIS
 * TU, so this is a fresh local typedef, per law 8 (own name + own layout,
 * never adopt a foreign typedef name alone). */

typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_801A5698;

/* 4x s16 vector, matches SV_801AAF8C's layout in this same TU. */
typedef struct { s16 vx, vy, vz, pad; } SVec_801A5698;

extern void RotMatrixY(s32 a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);

extern Mtx32_801A90D8 D_800AE620;
extern s16 D_80126B5E;
extern s16 D_80126B62;
extern s16 D_80126B66;

void func_801A5698(u8 *s2, s32 a1)
{
    Mtx32_801A5698 mtx;
    SVec_801A5698 sv;
    s32 flag;
    s32 angle;

    mtx = *(Mtx32_801A5698 *)&D_800AE620;
    mtx.t[0] = D_80126B5E;
    mtx.t[1] = D_80126B62;
    mtx.t[2] = D_80126B66;

    angle = (s16)a1 + *(s16 *)(*(s32 *)(s2 + 0x64) + 0x102);
    RotMatrixY(angle, &mtx);

    sv.vy = 0;
    sv.vx = 0;
    sv.vz = 0x1A0;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV((s32)&sv, (s32)&sv, &flag);

    *(u16 *)(s2 + 0x6) = sv.vx;
    *(u16 *)(s2 + 0xE) = sv.vz;
}


void func_801A5798(s32 arg0) {
    s32 i;

    for (i = 0; i < 10; i++) {
        func_8012C658(0x31f, i + 0x100, arg0);
    }
}


#include "common.h"

extern s32 func_8001D074(s32 a0, s32 a1);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8001CD9C(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801A5AA0(void *a0);
extern void func_801A5AE0(void *a0);
extern void func_801A5B00();
extern int rand(void);   /* canonical: identical decl already at md_SC07_004.c:1116 */

/* 8-byte-stride record indexed by *(s16*)(obj+0x70).  The .s spells the four
 * fields as four separate %lo symbols; .a/.b/.c/.d are the SAME addresses:
 *   D_801B0174/.a  D_801B0176/.b  D_801B0178/.c  D_801B017A/.d
 *   D_801AFE44/.a  D_801AFE46/.b  D_801AFE48/.c  D_801AFE4A/.d
 * One array-of-struct decl per table (instead of four u16[] with [i*4]) is what
 * keeps gcc from CSE-ing the repeated symbol address into a spilled pseudo --
 * the four u16[] form byte-matches the body but inflates the frame to 0x30
 * (vars=16) instead of the target's 0x20.  D_801B0174 / D_801AFE44 are real
 * dlabels in asm/md_SC07_004/data/tail.data.s, so +2/+4/+6 relocate exactly. */
typedef struct { u16 a, b, c, d; } Rec8_801A57E8;
extern Rec8_801A57E8 D_801B0174[];
extern Rec8_801A57E8 D_801AFE44[];

extern u8 D_801AFEBC[];
extern u8 D_801B01C4[];
extern u8 D_801B01EC[];
extern s32 D_801B02B8[];
extern u8 D_801F8744[];

void func_801A57E8(void *a0) {
    s32 s1;
    s32 v0;
    s32 v;

    s1 = func_8001D074(0x7E, 0x100);
    *(s32 *)((s32)a0 + 0xCC) = s1;
    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0 || s1 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C2C4(v0);

    if (*(u16 *)((s32)a0 + 0x70) & 0x100) {
        *(s16 *)((s32)a0 + 0x104) = *(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36);
    }
    *(s16 *)((s32)a0 + 0x70) = *(u8 *)((s32)a0 + 0x70);

    /* NOTE: 0xD4 is written THIRD in the source but the scheduler sinks/raises
     * it to land between the 0x102 and 0xFE stores, exactly as in the target. */
    if (*(s16 *)((s32)a0 + 0x104) != 0) {
        *(s16 *)((s32)a0 + 0x102) = D_801B0174[*(s16 *)((s32)a0 + 0x70)].d & 0xF000;
        *(s16 *)((s32)a0 + 0xFE) = D_801B0174[*(s16 *)((s32)a0 + 0x70)].d & 0xFFF;
        *(s32 *)((s32)a0 + 0xD4) = (s32)D_801B01C4;
        *(s16 *)((s32)a0 + 0x6) = D_801B0174[*(s16 *)((s32)a0 + 0x70)].a;
        *(s16 *)((s32)a0 + 0xA) = D_801B0174[*(s16 *)((s32)a0 + 0x70)].b;
        *(s16 *)((s32)a0 + 0xE) = D_801B0174[*(s16 *)((s32)a0 + 0x70)].c;
    } else {
        *(s16 *)((s32)a0 + 0x102) = D_801AFE44[*(s16 *)((s32)a0 + 0x70)].d & 0xF000;
        *(s16 *)((s32)a0 + 0xFE) = D_801AFE44[*(s16 *)((s32)a0 + 0x70)].d & 0xFFF;
        *(s32 *)((s32)a0 + 0xD4) = (s32)D_801AFEBC;
        *(s16 *)((s32)a0 + 0x6) = D_801AFE44[*(s16 *)((s32)a0 + 0x70)].a;
        *(s16 *)((s32)a0 + 0xA) = D_801AFE44[*(s16 *)((s32)a0 + 0x70)].b;
        *(s16 *)((s32)a0 + 0xE) = D_801AFE44[*(s16 *)((s32)a0 + 0x70)].c;
    }

    if (*(s16 *)((s32)a0 + 0x102) != 0) {
        func_8001CC3C(s1, (s32)D_801B01EC, 0, 0);
        func_80128EA8(s1, (s32)a0 + 0xF0, D_801B02B8[rand() & 3]);
        *(s16 *)((s32)a0 + 0xF4) = (*(s16 *)((s32)a0 + 0xFE) * 3) & 7;
        *(s16 *)(s1 + 0x1A) = 0x2000;
        *(s16 *)(s1 + 0x18) = 0x2000;
        *(s8 *)(s1 + 0x27) = 0x64;
        func_801A5AE0(a0);
        v = 0x8010;
    } else {
        func_8001CD9C(s1, (s32)D_801F8744);
        *(s16 *)((s32)a0 + 0x100) = ((*(s16 *)((s32)a0 + 0xFE) * 3) << 8) & 0xFFF;
        if (*(s16 *)((s32)a0 + 0x104) != 0) {
            func_801A5B00(a0);
        } else {
            func_801A5AA0(a0);
        }
        v = 0xC020;
    }
    *(s16 *)(s1 + 0x2C) = v;
    *(s32 *)(s1 + 0x4) |= 0x50800000;
}


void func_801A5AA0(void *arg0) {
    func_8012AD44((s32 *)arg0, 1);
}


void func_801A5AC0(void *a0) {
    func_8012AD44((s32 *)a0, 2);
}


void func_801A5AE0(void *a0) {
    func_8012AD44((s32 *)a0, 3);
}


void func_801A5B00(s32 *a0) {
    func_8012AD44(a0, 4);
}




void func_801A5B20(void *a0) {

    extern void (*D_801B02C8[])(void);
    D_801B02C8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern u16 D_8019FF8A;
extern s32 D_801B6E94[0x11];

void func_801A5B5C(void *arg0)
{
    s32 *s1;
    s32 w;

    s1 = *(s32 **)((u8 *)arg0 + 0xCC);

    if (D_801B6E94[*(s16 *)((u8 *)arg0 + 0xFE)] == 0x1000000
        || *(s32 *)((u8 *)*(s32 *)(*(s32 *)((u8 *)arg0 + 0x64) + 0x20) + 4) < 0
        || (D_8019FF8A & 8) != 0)
    {
        *(s32 *)((u8 *)s1 + 4) |= 0x80000000;
        return;
    }

    func_80132784((s32)arg0, *(s32 *)((u8 *)arg0 + 0x64), (u16)*(s16 *)((u8 *)arg0 + 0xFE));
    *(s16 *)((u8 *)s1 + 8) = *(s32 *)((u8 *)*(s32 **)((u8 *)arg0 + 0x20) + 0x48);
    *(s16 *)((u8 *)s1 + 0xA) = *(s32 *)((u8 *)*(s32 **)((u8 *)arg0 + 0x20) + 0x4C);
    w = *(s32 *)((u8 *)s1 + 4);
    *(s16 *)((u8 *)s1 + 0xC) = *(s32 *)((u8 *)*(s32 **)((u8 *)arg0 + 0x20) + 0x50);
    *(s32 *)((u8 *)s1 + 4) = w & 0x7FFFFFFF;
}


extern s32 func_8004787C(s32 a0);

void func_801A5C44(void) {
    register s32 a0 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    s32 s0 = a0;
    s32 s2;
    s32 s1;
    s32 temp;

    temp = *(s16 *)(s0 + 0x100);
    s2 = *(s32 *)(s0 + 0xCC);
    s1 = *(s32 *)(s0 + 0xD4);
    temp = func_8004787C(temp) >> 4;
    *(s16 *)(s2 + 0x18) = *(u16 *)(s1 + (*(s16 *)(s0 + 0x70) * 4)) + temp;
    temp = func_8004787C(*(s16 *)(s0 + 0x100) + 0x800) >> 4;
    *(s16 *)(s2 + 0x1A) = *(u16 *)(s1 + (*(s16 *)(s0 + 0x70) * 4) + 2) + temp;
    *(u16 *)(s0 + 0x100) += 0x40;
}


typedef struct { s16 vx, vy, vz, pad; } SVec_801A5CE8;

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern u16 D_801F885C;
extern u8 D_801F88A8[];
extern u8 D_801F88B0[];

void func_801A5CE8(void *a0)
{
    SVec_801A5CE8 in;
    SVec_801A5CE8 out;

    func_8004914C((void *)(*(s32 *)((u8 *)a0 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)((u8 *)a0 + 0x20) + 0x34));

    in.vz = 0;
    in.vy = 0;
    in.vx = 0;
    RotTransSV((s32)&in, (s32)D_801F88A8, &out);

    in.vy = D_801F885C;
    RotTransSV((s32)&in, (s32)D_801F88B0, &out);
}


#include "common.h"

/* D_801B02DC / D_801B02DE: two u16 fields of the same 4-byte-stride table at
   0x801B02DC, indexed by the enum byte stream at D_801B030C.  The target's own
   relocations name BOTH symbols (%hi/%lo of D_801B02DC and of D_801B02DE), so
   they are modelled as two independent 4-byte-stride arrays whose low u16 is
   the only field read. */
typedef struct {
    u16 v;                                  /* 0x0 */
    u16 pad;                                /* 0x2 */
} Pair4_801B02DC;

/* The 4-entry scratch record built on the stack at sp+0x10 and handed to
   func_801A5E60.  Only f0/f2/f4 are written here; f6 is stride padding
   (8-byte stride == the target's `addiu $a0, $a0, 8` giv step). */
typedef struct {
    u16 f0;                                 /* 0x0 */
    u16 f2;                                 /* 0x2 */
    u16 f4;                                 /* 0x4 */
    u16 f6;                                 /* 0x6 */
} Entry8_801A5D68;

extern u8 D_801B0328[];
extern u8 D_801B0330[];
extern u8 D_801B030C[];                     /* 0xFF-terminated enum byte stream */
extern u16 D_801F885C;
extern Pair4_801B02DC D_801B02DC[];
extern Pair4_801B02DC D_801B02DE[];

extern void func_801A6184(u8 *, s32, s32);
extern void func_801A5E60();

void func_801A5D68(void *arg) {
    Entry8_801A5D68 buf[4];
    u8 *p;
    s32 i;
    u16 val;

    func_801A6184((u8 *)arg, (s32)D_801B0328, (s32)D_801B0330);
    p = D_801B030C;
    /* Plain `while` (NOT if + do-while): the front end emits LOOP_BEG followed
       by a simplejump to the bottom test, which is exactly the precondition for
       jump.c:2131 duplicate_loop_exit_test to COPY the 0xFF test to the top.
       That reproduces the target's two textually-identical guard/back-edge test
       blocks.  Writing `if (...) do { } while (...)` instead makes jump.c
       cross-jump the two inverse conditional blocks back together into the
       `j <bottom test>` shape (38-instruction residual, first-pass draft). */
    while (*p != 0xFF) {
        /* Indexing by `i` (not a walking `Entry8 *`) keeps ONE address giv:
           loop.c reduces &buf[i] to a single pointer stepped by 8 and reaches
           every field through 0x0/0x2/0x4 displacements.  A walking pointer
           splits into TWO givs (base+0 and base+4) and costs 2 extra insns.
           Preheader strata (cookbook 190-A) then fall out exactly: biv init
           `i = 0`, hoisted invariant `D_801F885C`, giv init `$a0 = $s2`. */
        for (i = 0; i < 4; i++) {
            buf[i].f0 = D_801B02DC[*p].v;
            /* f2 is cleared AFTER f0 in source order so sched1 sinks the
               `sh $zero, 0x2($a0)` into the `lhu`'s load-delay slot; written
               first it emits at the block top and leaves a `nop` behind
               (+1 instruction). */
            buf[i].f2 = 0;
            val = D_801B02DE[*p].v;
            buf[i].f4 = val;
            if (*p >= 6) {
                buf[i].f4 = val + D_801F885C;
            }
            p++;
        }
        func_801A5E60(arg, buf);
    }
}


typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } P_TAG;


void func_801A5E60(s32 a0, u8 *v)
{
    extern void *func_80010A08(s32);
    extern u8 D_800A6610[];
    extern u16 D_800B9A02;
    extern u8 D_801F8744[];
    extern u8 D_801F8745[];
    extern u8 D_801F8746[];

    u8 *pv;
    u32 *pot;
    s32 pz;
    s32 flag, flag2, otz;
    u8 *pkt;
    u8 *q;
    u32 *otp;

    pv = v;
    {
        u32 tv = *(u16 *)&D_800B9A02;
        u32 bv = (u32)&D_800A6610;
        pot = (u32 *)((tv << 14) + bv);
    }
    pkt = func_80010A08(0x24);
    pkt[3] = 8;
    pkt[7] = 0x38;

    gte_ldv3(pv, pv + 8, pv + 0x10);
    gte_rtpt();
    gte_stflg(&flag);
    gte_stsxy3(pkt + 8, pkt + 0x10, pkt + 0x18);
    gte_ldv0(pv + 0x18);
    gte_rtps();
    gte_stflg(&flag2);
    flag |= flag2;
    gte_stsxy(pkt + 0x20);
    gte_avsz4();
    gte_stotz(&otz);

    if ((flag & ~0x1000) == 0) {
        {
            s32 ozt = otz;
            pz = ozt - 8;
        }
        if ((u32)pz < 0x1000) {
            if (*(u16 *)(pv + 4) & 1) {
                pkt[4] = 0; pkt[5] = 0; pkt[6] = 0;
            } else {
                pkt[4] = D_801F8744[0]; pkt[5] = D_801F8745[0]; pkt[6] = D_801F8746[0];
            }
            if (*(u16 *)(pv + 0xC) & 1) {
                pkt[0xC] = 0; pkt[0xD] = 0; pkt[0xE] = 0;
            } else {
                pkt[0xC] = D_801F8744[0]; pkt[0xD] = D_801F8745[0]; pkt[0xE] = D_801F8746[0];
            }
            if (*(u16 *)(pv + 0x14) & 1) {
                pkt[0x14] = 0; pkt[0x15] = 0; pkt[0x16] = 0;
            } else {
                pkt[0x14] = D_801F8744[0]; pkt[0x15] = D_801F8745[0]; pkt[0x16] = D_801F8746[0];
            }
            if (*(u16 *)(pv + 0x1C) & 1) {
                pkt[0x1C] = 0; pkt[0x1D] = 0; pkt[0x1E] = 0;
            } else {
                pkt[0x1C] = D_801F8744[0]; pkt[0x1D] = D_801F8745[0]; pkt[0x1E] = D_801F8746[0];
            }
            {
                u32 m24 = 0x00FFFFFF;
                u32 mFF = 0xFF000000;

                otp = (u32 *)(pz * 4 + (u32)pot);
                pkt[7] |= 2;
                ((P_TAG *)pkt)->addr = ((P_TAG *)otp)->addr;
                ((P_TAG *)otp)->addr = (u32)pkt;
                q = func_80010A08(8);
                q[3] = 1;
                *(u32 *)(q + 4) = 0xE1000020;
                ((P_TAG *)q)->addr = ((P_TAG *)otp)->addr;
                ((P_TAG *)otp)->addr = (u32)q;
            }
        }
    }
}


#include "common.h"

/* MATRIX-style 0x20-byte matrix: s16 m[3][3] (18B) + 2B pad + s32 t[3] (12B).
 * Same shape as the TU-neighbour's MTX_801AAF8C (func_801AAF8C @ md_SC07_004.c). */
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx_801A6184;

/* 8-byte SVECTOR-style: x,y,z,pad (s16 each). Same shape as SV_801AAF8C. */
typedef struct { s16 x, y, z, pad; } Svec_801A6184;

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32  ratan2(s32 a0, s32 a1);
extern void CompMatrix(void *a0, void *a1, void *a2);

extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern u8  D_800AF648;

void func_801A6184(u8 *s2, s32 p1, s32 p2)
{
    s32 pos[3];           /* sp+0x10 */
    Svec_801A6184 out1;   /* sp+0x20 : RotTransSV(p1) result   */
    Svec_801A6184 out2;   /* sp+0x28 : RotTransSV(p2) result   */
    Svec_801A6184 mid;    /* sp+0x30 : (out1+out2)>>1          */
    Svec_801A6184 diff;   /* sp+0x38 : out2-out1, then rot vec */
    Mtx_801A6184  mtx;    /* sp+0x40 */
    s32 flag;             /* sp+0x60 */

    func_8004914C((void *)(*(s32 *)(s2 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(s2 + 0x20) + 0x34));

    RotTransSV(p1, (s32)&out1, &flag);
    RotTransSV(p2, (s32)&out2, &flag);

    mid.x = (out1.x + out2.x) >> 1;
    mid.y = (out1.y + out2.y) >> 1;
    mid.z = (out1.z + out2.z) >> 1;
    diff.x = out2.x - out1.x;
    diff.y = out2.y - out1.y;
    diff.z = out2.z - out1.z;

    func_800D23D0(&diff);
    RotMatrixYXZ(&diff, &mtx);

    pos[0] = D_801269A4 - mid.x;
    pos[1] = D_801269A8 - mid.y;
    pos[2] = D_801269AC - mid.z;
    ApplyTransposeMatrixLV(&mtx, pos, pos);

    diff.z = -ratan2(pos[0], pos[1]);
    RotMatrixYXZ(&diff, &mtx);

    mtx.t[0] = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x48);
    mtx.t[1] = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x4C);
    mtx.t[2] = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x50);
    CompMatrix(&D_800AF648, &mtx, &mtx);

    func_8004914C(&mtx);
    func_800491AC(&mtx);
}


extern u16 D_801202A0[];
extern void func_801A63A8(void *arg0);

void func_801A6330(void) {
    u16 *p;
    s32 i;

    p = D_801202A0;
    i = 0;
    do {
        if (*p == 0x31F) {
            if (*(s16 *)(p + 0x82) == 0) {
                func_801A63A8(p);
            }
        }
        i = i + 1;
        p = p + 0x86;
    } while (i < 0x60);
}



/* func_801A63A8 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801A63A8(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}




void func_801A63EC(void *a0) {

    extern void (*D_801B0338[])(void);
    D_801B0338[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80132EF4(s32 a0, s32 a1);

void func_801A6428(void *a0) {
    s32 *v1;

    v1 = (s32 *)func_80132EF4((s32)a0, 0x6A);
    if (v1 != NULL) {
        *(s32 *)((u8 *)v1 + 0x34) = (s32)a0;
        *(s32 *)((u8 *)v1 + 0x10) = -(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x10) >> 1);
        *(s32 *)((u8 *)v1 + 0x18) = -(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x18) >> 1);
    }
}




void func_801A649C(void *a0, u16 a1, u16 a2) {
    u16 buf[4];

    buf[2] = 0x10;
    buf[0] = a1;
    buf[1] = a2;
    buf[3] = 1;
    StoreImage((s32)&buf, (void *)a0);
}


extern s16 D_801AFBC8;
extern s16 D_801AFBCA;
extern s16 D_801AFBCC;
extern s16 D_801AFBCE;
extern s16 D_801AFBD0;
extern s16 D_801AFBD2;
extern s32 D_801F871C;

void func_801A64DC(s32 arg0) {
    s32 var = D_801F871C;

    *(u16 *)(arg0 + 0) = *(u16 *)(var + 6) + ((D_801AFBC8 + D_801AFBCA) >> 1);
    *(u16 *)(arg0 + 2) = *(u16 *)(var + 0x52) + (*(u16 *)(var + 0xA) + ((D_801AFBCC + D_801AFBCE) >> 1));
    *(u16 *)(arg0 + 4) = *(u16 *)(var + 0xE) + ((D_801AFBD0 + D_801AFBD2) >> 1);
}


#include "common.h"

extern void func_801A5C44(void);
extern void func_801A5B5C(void *a0);
extern void func_801A5D68(void *a0);
extern void func_801A5CE8(void *a0);
extern void func_8017E5D4(void *a0);
extern void func_8017E1E8(void *a0, void *a1, void *a2);

extern u16 D_8019FF8A;
extern u8 D_801F88A8[];
extern u8 D_801F88B0[];

extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A6560(s32 arg0) {
    func_801A5C44();
    func_801A5B5C((void *)arg0);

    if (!(D_8019FF8A & 4)) {
        if (*(void **)(arg0 + 0xD0) != NULL) {
            func_8017E5D4(*(void **)(arg0 + 0xD0));
            *(void **)(arg0 + 0xD0) = NULL;
        }
        func_8012AD44((s32 *)arg0, 1);
    } else {
        func_801A5D68((void *)arg0);
        func_801A5CE8((void *)arg0);
        if (*(s32 *)(arg0 + 0xD0) != 0) {
            func_8017E1E8(*(void **)(arg0 + 0xD0), D_801F88A8, D_801F88B0);
        }
    }
}


extern void func_801A3180(s32 a0, s32 a1);
extern void func_801A36A8(s32 a0);
extern s32 func_8012B8A4(s16 *a0);
extern void func_801A3624(s32 target, u16 *cur, s32 step);
extern s32 func_8012BEE8(s32 a0);
extern u16 D_8019FF8A;
extern void (*D_801AFC48[])(void);

void func_801A6610(s32 arg0) {
    s32 v0;

    func_801A3180(arg0, 0x100);
    func_801A36A8(arg0);
    v0 = func_8012B8A4((s16 *)arg0);
    *(u16 *)((s8 *)arg0 + 0xFE) = v0;
    func_801A3624((s16)v0, (u16 *)(*(s32 *)(arg0 + 0x20) + 0x12), 0x40);
    if (func_8012BEE8(arg0) != 0) {
        if (!(D_8019FF8A & 0x40)) {
            ((void (*)(s32))D_801AFC48[*(s16 *)((s8 *)arg0 + 0x104)])((s32)arg0);
            v0 = *(u16 *)((s8 *)arg0 + 0x104) + 1;
            *(u16 *)((s8 *)arg0 + 0x104) = v0;
            if ((s16)v0 >= 6) {
                *(u16 *)((s8 *)arg0 + 0x104) = 0;
            }
        }
    }
}


#include "common.h"

extern void func_8001C924(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_801A39D0(s32 a0);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern s32 func_801A8528(s32 a0);
extern void func_801A85A8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801A8A64(s32 a0);
extern void func_8017FA74(void);
extern void func_8013240C(s32 a0);
extern void func_801A18F4(s32 a0);

extern s32 D_801BF01C;
extern s32 *D_801AFB78;
extern s32 D_801F8724;
extern s32 D_801F8730;
extern u16 D_8019FF8A;

void func_801A66DC(s32 a0) {
    s32 *sp;
    u8 pad[8];

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        sp = &D_801BF01C;
        func_8001C924(*(s32 *)(a0 + 0x20), sp);
        func_8012B2CC(a0);
        func_801A39D0(a0);
        func_80132288(&D_801F8724, D_801AFB78, *sp);
        D_8019FF8A |= 1;
        *(s32 *)(a0 + 0xD4) = func_801A8528(a0);
        func_801A85A8(a0, 0x28080A0, 0, 0x200);
        func_801A8A64(a0);
        func_8017FA74();
        *(u16 *)(a0 + 0x34) += 1;
        break;
    case 1:
        func_8013240C((s32)&D_801F8724);
        if (D_801F8730 & 0x4000) {
            func_801A18F4(a0);
        }
        break;
    }
}


#include "common.h"

/* Destination TU declares func_801A395C as ('void', ('s32','s32')) at
 * src/md_SC07_004/md_SC07_004.c:56, but this function's asm checks $v0
 * immediately after the jal (beqz $v0, .L801A6820) -- the only call site
 * of func_801A395C in the whole fleet -- proving the real signature
 * returns s32. The existing void call site (func_801A19C0, line 103)
 * discards the value, so widening void->s32 there is byte-neutral.
 * TU EDIT NEEDED: change line 56 to `extern void func_801A395C(s32 a0, s32 a1);`
 */
extern void func_801A395C(s32 a0, s32 a1);

extern u16 D_8019FF8A;
extern s16 D_801F8714;

extern s32 func_8012BEE8(s32 a0);
extern void func_801A370C(s32 a0);
extern void func_801A85A8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801AAA6C(s32 a0);
extern void func_801A36A8(s32 a0);
extern void func_801A36F0(void *a0);
extern void func_801A7C58();
extern void func_801A8C58(s32 a0);
extern void func_801A1984(s32 a0);
extern void func_801A2364();

void func_801A67F8(s32 a0) {
    if (((s32 (*)(s32, s32))func_801A395C)(a0, -0x250) != 0) {
        func_801A36A8(a0);
    }
    func_801AAA6C(a0);
    func_801A370C(a0);
    if (D_8019FF8A & 0x400) {
        func_801A36F0((void *)a0);
        {
            void *v0 = *(void **)(a0 + 0xD4);
            if (v0 != NULL) {
                func_801A7C58(v0);
            }
        }
        func_801A8C58(a0);
        func_801A85A8(a0, 0x1A040A0, 0, 0x200);
        if (D_801F8714 != 0) {
            func_801A1984(a0);
            *(s32 *)(a0 + 0x1C) = 0x30;
        } else {
            func_801A2364(a0);
        }
    } else if (func_8012BEE8(a0) != 0) {
        u16 v0 = D_8019FF8A;
        *(s16 *)(a0 + 0xAE) = -1;
        D_8019FF8A = v0 & 0xFFFE;
        func_801A1984(a0);
    }
}


extern s32 func_801A3798(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801A4328(s32 a0);
extern void func_800183E0(s32);
extern void func_8017F418(void);
extern void func_801A46D4(s32 a0);
extern s32 D_801EEAC8;
extern s16 D_801F8714;
extern s32 D_801C65E4;
extern s32 D_801AFBC4;
extern u16 D_8019FF8A;
extern s32 D_801C6644;

void func_801A6908(s32 s0) {
    s32 *p;
    u16 t5c;
    u16 f9;
    if (func_801A3798(s0, 1) != 0) {
        func_8012A828(s0, &D_801EEAC8);
        *(s32 *)(s0 + 0x1C) = (s16)(D_801F8714 / 79) + 0x18;
        func_8012B200((u8 *)s0);
        func_8012AD44((s32 *)s0, 1);
        *(s32 *)(s0 + 0x1C) = 1;
        func_801A4328(0);
        p = &D_801C65E4;
        t5c = *(u16 *)(s0 + 0x5C) | 0x2000;
        *(s32 *)(s0 + 0x58) = (s32)&D_801AFBC4 | 0x40000000 | 0x20000000;
        f9 = D_8019FF8A & 0xF9FF;
        *(u16 *)(s0 + 0x5C) = t5c;
        D_8019FF8A = f9;
        ((s32 (*)(s32 *))func_800183E0)(p);
        ((s32 (*)(s32 *))func_800183E0)(&D_801C6644);
        func_8017F418();
        func_801A46D4(s0);
    }
}


extern void func_801A1E94(void);
void func_801A6A18(void) {
    func_801A1E94();
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern void func_8012AD50(void *a0);

extern u8 D_801AFF14[];
extern u8 D_801AFF24[];

void func_801A6A38(void *a0) {
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C2C4(v0);

    *(s32 *)((s32)a0 + 0x58) = (s32)D_801AFF14 | 0x40000000;
    *(u16 *)((s32)a0 + 0x5C) = 0x8800;
    *(u8 *)((s32)a0 + 0xC0) = 1;
    *(s32 *)((s32)a0 + 0xB4) = 0;
    *(u16 *)((s32)a0 + 0xAE) = 0;
    *(s32 *)((s32)a0 + 0xBC) = (s32)D_801AFF24;
    *(u8 *)((s32)a0 + 0xC1) = 0;
    *(s32 *)((s32)a0 + 0xC4) |= 2;
    func_8012AD50(a0);
}


#include "common.h"

/* decl_prior: fleet-modal ('void', ('s32',)), n=2449 (no rivals) */
extern void func_8012B2CC(s32 a0);
/* decl_prior fleet says ('s32', ('s32',)) n=12 elsewhere, but THIS call site is byte-proven
   to pass NO argument (see notes) -- K&R empty-parens is non-conflicting per-TU (C89 '?'). */
extern s32 func_8017DAEC();
/* body is INCLUDE_ASM'd later in this same TU; no other TU declares it. Return value unused
   here so declared void; args() unspecified since caller passes one s32. */
extern void func_801A4570(void *a0);
/* already declared in this TU (md_SC07_004.c:45) as u16 -- same spelling adopted. */
extern u16 D_8019FF8A;

/* 8-byte, 2-byte-aligned struct: forces gcc-2.7.2's emit_block_move to take the unaligned
   lwl/lwr + swl/swr path even between two naturally-4-aligned struct fields (cookbook §48-C2). */
typedef struct { u16 a, b, c, d; } Blk8_801A6AD0;

void func_801A6AD0(s32 arg0) {
    /* sync three u16 fields from *(arg0+0x64) into arg0 itself */
    *(s16 *)(arg0 + 0x6) = *(s16 *)(*(s32 *)(arg0 + 0x64) + 0x6);
    *(s16 *)(arg0 + 0xA) = *(s16 *)(*(s32 *)(arg0 + 0x64) + 0xA);
    *(s16 *)(arg0 + 0xE) = *(s16 *)(*(s32 *)(arg0 + 0x64) + 0xE);

    /* 8-byte struct copy at offset 0x50 */
    *(Blk8_801A6AD0 *)(arg0 + 0x50) =
        *(Blk8_801A6AD0 *)(*(s32 *)(arg0 + 0x64) + 0x50);

    /* 8-byte struct copy at offset 0x10 of the nested (+0x20) struct */
    *(Blk8_801A6AD0 *)(*(s32 *)(arg0 + 0x20) + 0x10) =
        *(Blk8_801A6AD0 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x10);

    func_8012B2CC(arg0);

    if (*(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x4) >= 0) {
        if ((D_8019FF8A & 0x200) == 0) {
            func_801A4570((void *)arg0);
        }
    }

    func_8017DAEC();
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 D_801B75EC;
extern u16 D_801AFF3C;
extern u16 D_801AFF3E;
extern u16 D_801AFF40;

void func_801A6BC0(void *a0) {
    s32 v0;
    s32 v1;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801B75EC);

        v1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)((s32)a0 + 0x6) = D_801AFF3C;
        *(s16 *)((s32)a0 + 0xA) = D_801AFF3E;
        *(s16 *)((s32)a0 + 0xE) = D_801AFF40;
        *(s32 *)(v1 + 0x4) |= 0x40;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;

        if (*(s16 *)((s32)a0 + 0x70) == 0) {
            *(s32 *)((s32)a0 + 0x6C) =
                func_8012C658(0x32A, 1, *(s32 *)((s32)a0 + 0x64));
        }
        *(s32 *)((s32)a0 + 0xCC) =
            func_8012C658(0xB1, *(s16 *)((s32)a0 + 0x70), (s32)a0);
        func_801A46F0((s32 *)a0);
    }
}


#include "common.h"

extern void func_8013240C(s32 a0);
extern void func_801A4EBC(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_801A4AAC(void *a0);

extern s32 D_801F8888;
extern s32 D_801F8898;
extern s32 D_801F888C;
extern u16 D_8019FF8A;

void func_801A6CA8(void *arg0) {
    void *s0;
    s32 s1;

    s0 = arg0;
    s1 = *(s32 *)((u8 *)s0 + 0xCC);

    if (*(s16 *)((u8 *)s0 + 0x70) == 0) {
        func_8013240C((s32)&D_801F8888);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        func_801A4EBC(s0);
        if (D_801F888C == 1) {
            func_8002D4C8(0xAB9, 0);
            if (*(s16 *)((u8 *)s0 + 0x84) == 0) {
                func_8002D4C8(0xABE, 0);
                *(u16 *)((u8 *)s0 + 0x84) += 1;
            }
        }
    }

    func_80132784((s32)s0, *(s32 *)((u8 *)s0 + 0x64), 0);
    if (D_8019FF8A & 0x100) {
        func_801A4AAC(s0);
    }
}


#include "common.h"

extern void func_8013240C(s32 a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);

extern s32 D_801F8888;

void func_801A6D90(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0x34) == 0) {
        func_8013240C((s32)&D_801F8888);
        *(u16 *)((u8 *)arg0 + 0x34) += 1;
    }

    func_80132784((s32)arg0, *(s32 *)((u8 *)arg0 + 0x64), 0);
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012AD50(void *a0);

extern u8 D_801B80FC[];

void func_801A6DF4(void *a0)
{
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C810(v0, (s32)D_801B80FC);

    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) |= 0x50000040;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    func_8012AD50(a0);
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_801A5798(s32);
extern s32 func_80143970(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_801A53F4();
extern u8 D_801BA9E8[];
extern u8 D_801EFA00[];

void func_801A6E78(void *a0) {
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)D_801BA9E8);
        ((void (*)(void *))func_801A5798)(a0);
        *(s32 *)((s32)a0 + 0xD0) = func_80143970((s32)a0);
        func_8012A828((s32)a0, D_801EFA00);
        func_801A53F4(a0);
    }
}


extern s32 func_8012B8A4(s16 *a0);
extern void func_801A5698(u8 *s2, s32 a1);
extern void func_801A54AC(s32 a0);

void func_801A6EF4(void *arg0) {
    s32 s0;

    s0 = (s32)arg0;
    *(u16 *)(*(s32 *)((u8 *)s0 + 0x20) + 0x12) = func_8012B8A4((s16 *)s0);
    func_801A5698((u8 *)s0, *(s16 *)((u8 *)s0 + 0xFE));
    func_801A54AC(s0);
}


extern void func_8012AD80(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_801439C0(u8 *a0);
extern void func_801A54AC(s32 a0);
extern s32 D_801F8844[];

void func_801A6F3C(s32 param_1) {
    func_8012AD80(param_1);
    *(s32 *)(param_1 + 0xF0) = *(s32 *)(param_1 + 0xF0) - 0x20000;
    func_8012B178(param_1, *(s32 *)(param_1 + 0xF0));
    if (func_8012BEE8(param_1) != 0) {
        D_801F8844[*(s16 *)(param_1 + 0x70)] = 0;
        func_8012C218((void *)param_1);
        if (*(u8 **)(param_1 + 0xD0) != NULL) {
            func_801439C0(*(u8 **)(param_1 + 0xD0));
        }
    } else {
        func_801A54AC(param_1);
    }
}


#include "common.h"

extern u16 D_8019FF8A;
extern u16 D_800B99DA;
extern u8 D_801F88A8[];
extern u8 D_801F88B0[];
extern u8 D_801F8747[];

extern void func_801A5C44(void);
extern void func_801A5B5C(void *a0);
extern void func_801A5AC0(void *a0);
extern void func_801A5D68(void *a0);
extern void func_801A5CE8(void *a0);
extern void func_801A6428(void *a0);
extern s32 func_8017D7D4(void *a0, void *a1, void *a2, s32 a3);

void func_801A6FD4(void *arg0) {
    void *s1;
    s32 v0;

    s1 = *(void **)((u8 *)arg0 + 0xCC);
    func_801A5C44();
    func_801A5B5C(arg0);

    if ((D_8019FF8A & 4) && *(s16 *)((u8 *)arg0 + 0xFE) == 0xB) {
        func_801A5AC0(arg0);
        func_801A5D68(arg0);
        func_801A5CE8(arg0);
        D_801F8747[0] = 1;
        v0 = func_8017D7D4(D_801F88A8, D_801F88B0, D_801F8747 - 3, 6);
        *(s32 *)((u8 *)arg0 + 0xD0) = v0;
    } else if ((D_8019FF8A & 0x10) && *(s32 *)((u8 *)s1 + 4) >= 0 && (D_800B99DA & 1)) {
        func_801A6428(arg0);
    }
}


#include "common.h"

extern u16 D_8019FF8A;
extern s32 D_801B02B8[];
extern void func_801A5B5C(void *a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern int rand(void);
extern s32 func_80128ED8(s32 a0, s32 *a1);

void func_801A70D0(void *arg0) {
    s32 s1;
    void *s2;

    s1 = *(s32 *)((u8 *)arg0 + 0xCC);
    func_801A5B5C(arg0);
    s2 = (u8 *)arg0 + 0xF0;

    if ((D_8019FF8A & 4) && *(s16 *)((u8 *)arg0 + 0xFE) == 0xB) {
        *(s32 *)(s1 + 4) |= 0x80000000;
    }

    if (func_80128ED8(s1, (s32 *)s2) != 0) {
        func_80128EA8(s1, (s32)s2, D_801B02B8[rand() & 3]);
    }
}


#include "common.h"

extern void func_801A5C44(void);
extern void func_801A5B5C(void *a0);
extern void func_801A63A8(void *a0);
extern void func_801A6428(void *a0);

void func_801A7184(void *arg0)
{
    if (*(s16 *)((u8 *)arg0 + 0x104) != *(s16 *)(*(void **)((u8 *)arg0 + 0x64) + 0x36)) {
        func_801A63A8(arg0);
    } else {
        ((void (*)(void *))func_801A5C44)(arg0);
        func_801A5B5C(arg0);
        if (*(s16 *)(*(void **)((u8 *)arg0 + 0x64) + 0x100) != 0) {
            func_801A6428(arg0);
        }
    }
}


#include "common.h"

extern void func_8001CD9C(s32, s32);
extern u8 D_801F8744[];

void func_801A7200(s32 param_1)
{
    s32 s1;
    s32 s2;

    s1 = *(s32 *)(param_1 + 0x34);
    s2 = *(s32 *)(s1 + 0xCC);
    *(u16 *)(param_1 + 0x2C) = 0;
    func_8001CD9C(*(s32 *)(param_1 + 0x20), (s32)D_801F8744);
    *(u16 *)(param_1 + 6) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x48);
    *(u16 *)(param_1 + 0xA) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x4C);
    *(u16 *)(param_1 + 0xE) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x50);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = *(u16 *)(s2 + 0x18);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = *(u16 *)(s2 + 0x1A);
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50800000;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) = 0xC020;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern u8 D_801F8744[];

void func_801A72DC(void *a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);

    s32 v0;

    v0 = *(u16 *)((s32)a0 + 0x2C) + 1;
    *(u16 *)((s32)a0 + 0x2C) = v0;
    if ((s16)v0 >= 4) {
        func_801292C8((u8 *)a0);
        return;
    }
    func_8012931C((struct vec *)a0);
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x20) =
        (s32)D_801F8744 + (*(s16 *)((s32)a0 + 0x2C) << 6);
}


#include "common.h"

/* §160a: lwl/lwr + swl/swr == emit_block_move on an ALIGN-1 4-byte struct. */
typedef struct { char c[4]; } Blk4_801A7358;

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32, s32, void*);
extern s32 func_8001D074(s32, s32);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8001CD9C(s32, s32);
extern int func_801AF9C8(short *pos, int a1, int a2);
extern void func_8012AD50(void *a0);

extern u8 D_801B0360[];
extern Blk4_801A7358 *D_801B0358[];
extern Blk4_801A7358 D_801A01E8;
extern Blk4_801A7358 D_801F88B8;
extern Blk4_801A7358 D_801F88BC;
extern Blk4_801A7358 D_801F88F8;
extern Blk4_801A7358 D_801F88FC;
extern Blk4_801A7358 D_801F8938;
extern Blk4_801A7358 D_801F893C;

void func_801A7358(u8 *s2)
{
    Blk4_801A7358 *s3;
    s32 s1, s12, s13;
    void *s0;
    s32 v0;
    s32 t;
    u16 idx;
    s32 p;
    u16 sv[4];
    s32 flag;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(s2 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s2);
        return;
    }

    func_8001C2C4(v0);
    t = *(s32 *)(s2 + 0x20);
    *(s16 *)(t + 0x1A) = 0x400;
    *(s16 *)(t + 0x18) = 0x400;
    func_8004914C((void *)(*(s32 *)(*(s32 *)(s2 + 0x64) + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(*(s32 *)(s2 + 0x64) + 0x20) + 0x34));
    ((void (*)(void *, void *, void *))RotTransSV)(D_801B0360, sv, &flag);
    *(u16 *)(s2 + 0x6) = sv[0];
    *(u16 *)(s2 + 0xA) = sv[1];
    *(u16 *)(s2 + 0xE) = sv[2];
    idx = *(u16 *)(s2 + 0x70) & 1;
    *(u16 *)(s2 + 0x70) = idx;
    s3 = D_801B0358[idx];

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 != 0) {
        *(s32 *)(s2 + 0xCC) = s1;
        s0 = &D_801F88B8;
        func_800233CC(s0, 0x80);
        D_801F88B8 = s3[0];
        D_801F88BC = D_801A01E8;
        ((void (*)(s32, void *))func_8001CD9C)(s1, s0);
        *(u16 *)(s1 + 0x2C) = 0xC020;
        *(s32 *)(s1 + 4) = 0x50000000;
    }

    s12 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s12 != 0) {
        *(s32 *)(s2 + 0xD0) = s12;
        s0 = &D_801F88F8;
        func_800233CC(s0, 0x60);
        D_801F88F8 = s3[1];
        D_801F88FC = D_801A01E8;
        ((void (*)(s32, void *))func_8001CD9C)(s12, s0);
        *(u16 *)(s12 + 0x2C) = 0xC020;
        *(s32 *)(s12 + 4) = 0x50000000;
    }

    s13 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s13 != 0) {
        *(s32 *)(s2 + 0xD4) = s13;
        s0 = &D_801F8938;
        func_800233CC(s0, 0xB0);
        D_801F8938 = s3[2];
        D_801F893C = s3[2];
        ((void (*)(s32, void *))func_8001CD9C)(s13, s0);
        *(u16 *)(s13 + 0x2C) = 0xC01E;
        *(s32 *)(s13 + 4) = 0x50000000;
        *(s16 *)(s13 + 0x1E) = 0xD00;
    }

    sv[3] = 0x1A;
    p = func_801AF9C8((short *)sv, 0, 0x404040);
    if (p != 0) {
        *(s32 *)(s2 + 0xD8) = p;
        *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = 0x1C00;
    }
    *(s32 *)(s2 + 0x14) = 0xFFE00000;
    *(s32 *)(s2 + 0x1C) = 0x18;
    func_8012AD50(s2);
}


#include "common.h"

extern u8 D_801B0368[];
extern u8 D_801B036A[];
extern u8 D_801B036C[];

extern void func_801AB21C(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801A7604(void *arg0) {
    s16 idx;

    switch (*(u16 *)((u8 *)arg0 + 0x34)) {
    case 0:
        idx = *(s16 *)((u8 *)arg0 + 0x70);
        *(u16 *)((u8 *)arg0 + 0xFE) += *(u16 *)(D_801B0368 + idx * 8);
        idx = *(s16 *)((u8 *)arg0 + 0x70);
        *(u16 *)((u8 *)arg0 + 0x100) += *(u16 *)(D_801B036A + idx * 8);
        idx = *(s16 *)((u8 *)arg0 + 0x70);
        *(u16 *)((u8 *)arg0 + 0x102) += *(u16 *)(D_801B036C + idx * 8);
        func_801AB21C(1, *(u8 *)((u8 *)arg0 + 0xFF), *(u8 *)((u8 *)arg0 + 0x101), *(u8 *)((u8 *)arg0 + 0x103));
        if (func_8012BEE8((s32)arg0) != 0) {
            *(s32 *)((u8 *)arg0 + 0x1C) = 8;
            *(u16 *)((u8 *)arg0 + 0x34) = *(u16 *)((u8 *)arg0 + 0x34) + 1;
        }
        break;
    case 1:
        idx = *(s16 *)((u8 *)arg0 + 0x70);
        *(u16 *)((u8 *)arg0 + 0xFE) -= (s16)(*(u16 *)(D_801B0368 + idx * 8)) >> 1;
        idx = *(s16 *)((u8 *)arg0 + 0x70);
        *(u16 *)((u8 *)arg0 + 0x100) -= (s16)(*(u16 *)(D_801B036A + idx * 8)) >> 1;
        idx = *(s16 *)((u8 *)arg0 + 0x70);
        *(u16 *)((u8 *)arg0 + 0x102) -= (s16)(*(u16 *)(D_801B036C + idx * 8)) >> 1;
        func_801AB21C(1, *(u8 *)((u8 *)arg0 + 0xFF), *(u8 *)((u8 *)arg0 + 0x101), *(u8 *)((u8 *)arg0 + 0x103));
        if (func_8012BEE8((s32)arg0) != 0) {
            if (*(void **)((u8 *)arg0 + 0xCC) != NULL) {
                func_80016714(*(void **)((u8 *)arg0 + 0xCC), 0x38);
            }
            if (*(void **)((u8 *)arg0 + 0xD0) != NULL) {
                func_80016714(*(void **)((u8 *)arg0 + 0xD0), 0x38);
            }
            if (*(void **)((u8 *)arg0 + 0xD4) != NULL) {
                func_80016714(*(void **)((u8 *)arg0 + 0xD4), 0x38);
            }
            func_8012C218(arg0);
        }
        break;
    }
}




void func_801A77CC(void *a0) {

    extern void (*D_801B0378[])(void);
    D_801B0378[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801A7808(s32 a0, s32 a1) {
    if (a1 != 0) {
        *(u16 *)(a1 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(a1 + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(a1 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(a1 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(a1 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
    }
}


extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

s32 func_801A7864(void *a0, s32 a1) {
    return func_8012C658(0x3A4, a1 & 1, (s32)a0);
}


INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A01E8);

#include "common.h"

/* SPLICE NOTE: md_SC07_004.c already typedefs Blk4_801A7358 at file scope (L3485).
   DROP THE NEXT LINE when splicing into the TU -- it is here only so the standalone
   matcher compiles this draft on its own. */


extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8001CD9C(s32, s32);
extern void func_801A7AF8(s32);
extern void func_801A7C34(s32);
extern void func_801A7D34(s32);
extern void func_801A7F84(s32);
extern void func_801A8054(s32);
extern void func_801A8228(s32);

extern Blk4_801A7358 D_801A01E8;
extern Blk4_801A7358 D_801A01EC;
extern Blk4_801A7358 D_801F88B8;
extern Blk4_801A7358 D_801F88BC;
extern Blk4_801A7358 D_801F88F8;
extern Blk4_801A7358 D_801F8938;

/* §304/§8 rodata island: D_801A01EC (0x00A06060) lives ONLY in this function's
 * migrated .s (spimdisasm put it there) and has no INCLUDE_RODATA line in the TU;
 * while the function was INCLUDE_ASM the word rode in on the stub. Re-emit it at the
 * stub's own emission position so the island bytes are unchanged and the symbol is
 * not dropped from the link. Same form as D_801A0214 in this TU (:6516). */
__asm__(".section .rodata\nD_801A01EC:\n.word 0x00A06060\n.section .text");  // !FAKE: instruction .section — REFUSED asm-data: a `.section` block defines data as assembly (a rodata carve, not a compiler steer) — T7 (P36 rung B tus11)

void func_801A788C(s32 a0) {
    /* Block scope on purpose: md_SC07_004.c declares these four at FILE scope with
       other types further down (u8[3] / Blk4_801AB8C0 / s32[] / u8[4]); a file-scope
       Blk4_801A7358 decl here would be a conflicting-types error for the whole TU. */
    extern Blk4_801A7358 D_801F8978;
    extern Blk4_801A7358 D_801F897C;
    extern Blk4_801A7358 D_801F89B8;
    extern Blk4_801A7358 D_801F89F8;
    void *s0;
    s32 v1;

    switch (*(s16 *)(a0 + 0x2E)) {
    case 0:
        s0 = &D_801F88B8;
        func_800233CC(s0, 0x80);
        D_801F88B8 = D_801A01E8;
        D_801F88BC = D_801A01E8;
        func_8001CD9C(*(s32 *)(a0 + 0x20), (s32)s0);
        v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = 0xC020;
        v1 = *(s32 *)(a0 + 0x20);
        *(s32 *)(v1 + 4) = 0x50000000;
        func_801A7AF8(a0);
        break;
    case 1:
        s0 = &D_801F8978;
        func_800233CC(s0, 0x80);
        D_801F8978 = D_801A01EC;
        D_801F897C = D_801A01E8;
        func_8001CD9C(*(s32 *)(a0 + 0x20), (s32)s0);
        v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = 0xC020;
        v1 = *(s32 *)(a0 + 0x20);
        *(s32 *)(v1 + 4) = 0x50800000;
        func_801A7C34(a0);
        break;
    case 2:
        *(s32 *)(a0 + 0x24) = (s32)&D_801F88F8;
        func_801A7D34(a0);
        break;
    case 3:
        *(s32 *)(a0 + 0x24) = (s32)&D_801F8938;
        func_801A7D34(a0);
        break;
    case 4:
        *(s32 *)(a0 + 0x24) = (s32)&D_801F88F8;
        *(s32 *)(a0 + 0x30) = 0x404;
        func_801A7F84(a0);
        break;
    case 5:
        *(s32 *)(a0 + 0x24) = (s32)&D_801F8938;
        *(s32 *)(a0 + 0x30) = 0x40004;
        func_801A7F84(a0);
        break;
    case 6:
        s0 = &D_801F89B8;
        func_800233CC(s0, 0x80);
        func_8001CD9C(*(s32 *)(a0 + 0x20), (s32)s0);
        v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = 0xC020;
        v1 = *(s32 *)(a0 + 0x20);
        *(s32 *)(v1 + 4) = 0x50000000;
        v1 = *(s32 *)(a0 + 0x20);
        *(s16 *)(v1 + 0x1E) = 0xE00;
        func_801A8054(a0);
        break;
    case 7:
        s0 = &D_801F89F8;
        func_800233CC(s0, 0x80);
        func_8001CD9C(*(s32 *)(a0 + 0x20), (s32)s0);
        v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = 0xC080;
        v1 = *(s32 *)(a0 + 0x20);
        *(s32 *)(v1 + 4) = 0x50800000;
        func_801A8228(a0);
        break;
    }
}


void func_801A7AF8(s32 a0) {
    *(u16 *)(a0 + 2) = 1;
    *(u16 *)(a0 + 0x2A) = 0;
}


extern s32 func_8004787C(s32 a0);
extern void func_801A8440(s32 a0);
extern u8 D_801F88BA;

void func_801A7B08(s32 arg0) {
    s32 s0;
    u8 *p;
    s0 = arg0;
    func_801A8440(s0);

    switch (*(s16 *)((s32)s0 + 0x2C)) {
    case 0: {
        s16 t = *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18);
        if (t >= 0x401) {
            *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18) = t - 0xA0;
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18);
        }
        p = &D_801F88BA;
        if (*p < 0xF0) {
            *p += 0xC;
        }
        if ((*(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18) < 0x401) &&
            (*p >= 0xF0)) {
            *(u16 *)((s32)s0 + 0x2A) = 0;
            *(u16 *)((s32)s0 + 0x2C) += 1;
        }
        break;
    }

    case 1:
        *(u16 *)((s32)s0 + 0x2A) += 0x40;
        *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x18) =
            (func_8004787C(*(s16 *)((s32)s0 + 0x2A)) >> 5) + 0x400;
        *(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) =
            (func_8004787C(*(s16 *)((s32)s0 + 0x2A) + 0x800) >> 5) + 0x400;
        break;
    }
}


void func_801A7C34(s32 a0) {
    s32 v0;

    v0 = *(s32 *)(a0 + 0x20);
    *(u16 *)(v0 + 0x1A) = 0;
    *(u16 *)(v0 + 0x18) = 0;
    *(s32 *)(a0 + 0x1C) = 1;
    *(u16 *)(a0 + 0x2) = 2;
}


extern u8 D_801F88C8[];
extern u8 D_801F88CA[];
extern u8 D_801F8A38[];
extern u8 D_801F8A3A[];

void func_801A7C58(s32 a0) {
    s32 i;
    s32 j;
    s32 v;
    s32 temp;

    i = 0;
    j = 0;
    do {
        v = *(u16 *)(D_801F88C8 + i);
        *(u16 *)(D_801F8A38 + j) = v;
        v = *(u16 *)(D_801F88CA + i);
        i += 8;
        *(u16 *)(D_801F8A3A + j) = v;
        j += 4;
    } while (i < 0x30);

    temp = *(s32 *)(a0 + 0x20);
    *(s32 *)(a0 + 0x1C) = 6;
    *(u16 *)(temp + 0x1A) = 0x400;
    *(u16 *)(temp + 0x18) = 0x400;
    *(u16 *)(a0 + 2) = 3;
    *(u16 *)(a0 + 0x2C) = 0;
}



void func_801A7CC8(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x4;
        *(s16 *)((char *)a0 + 0x2) = 0x4;
    }



extern Blk4_801A7358 D_801F88B8;

s32 func_801A7CDC(void *a0)
{
    void *v1;
    s32 r;

    *(s32 *)((char *)a0 + 0x30) = *(s32 *)&D_801F88B8;
    v1 = *(void **)((char *)a0 + 0x20);
    *(s16 *)((char *)v1 + 0x1A) = 0x2000;
    *(s16 *)((char *)v1 + 0x18) = 0x2000;
    v1 = *(void **)((char *)a0 + 0x20);
    *(u16 *)((char *)v1 + 0x2C) = 0xC040;
    *(s32 *)((char *)a0 + 0x1C) = 1;
    r = 5;
    *(s16 *)((char *)a0 + 2) = (s16)r;
    return r;
}


void func_801A7D18(s32 arg0) {
    s32 var;

    var = *(s32 *)(arg0 + 0x20);
    *(u16 *)(var + 0x1A) = 0x400;
    *(u16 *)(var + 0x18) = 0x400;
    *(u16 *)(arg0 + 0x2) = 6;
}


#include "common.h"

/* §160a idiom, already established in this TU (func_801A7358, L637-638):
 * lwl/lwr + swl/swr == emit_block_move on an ALIGN-1 4-byte struct. */


extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8001CD9C(s32, s32);
extern Blk4_801A7358 D_801A01E8;

void func_801A7D34(s32 a0) {
    s32 s1;
    s32 v1;
    s32 t;

    s1 = *(s32 *)(a0 + 0x24);
    func_800233CC((void *)s1, 0x80);
    *(Blk4_801A7358 *)(s1 + 0x0) = *(Blk4_801A7358 *)(a0 + 0x30);
    *(Blk4_801A7358 *)(s1 + 0x4) = D_801A01E8;
    func_8001CD9C(*(s32 *)(a0 + 0x20), s1);

    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v1 + 0x1E) = 0xC00;

    v1 = *(s32 *)(a0 + 0x20);
    *(u16 *)(v1 + 0x2C) = 0xC040;

    if (*(s32 *)(a0 + 0x30) & 0x2000000) {
        v1 = *(s32 *)(a0 + 0x20);
        *(s32 *)(v1 + 0x4) = 0x60000000;
    } else {
        v1 = *(s32 *)(a0 + 0x20);
        *(s32 *)(v1 + 0x4) = 0x50000000;
    }

    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v1 + 0x1A) = 0x100;
    *(s16 *)(v1 + 0x18) = 0x100;

    t = *(u8 *)(s1 + 0x0) >> 4;
    *(s16 *)(a0 + 0x12) = t;
    if (t == 0) {
        *(s16 *)(a0 + 0x12) = 1;
    }

    t = *(u8 *)(s1 + 0x1) >> 4;
    *(s16 *)(a0 + 0x16) = t;
    if (t == 0) {
        *(s16 *)(a0 + 0x16) = 1;
    }

    t = *(u8 *)(s1 + 0x2) >> 4;
    *(s16 *)(a0 + 0x1A) = t;
    if (t == 0) {
        *(s16 *)(a0 + 0x1A) = 1;
    }

    *(s16 *)(a0 + 0x2) = 7;
}


#include "common.h"

extern void func_801292C8(u8 *a0);

void func_801A7E5C(void *a0) {
    u8 *obj = *(u8 **)((s32)a0 + 0x24);
    s32 b;
    s16 t[3];

    b = obj[0];
    t[0] = b;
    if (b != 0) {
        t[0] = b - *(u16 *)((s32)a0 + 0x12);
        if (t[0] < 0) {
            t[0] = 0;
        }
        obj[0] = (u8)t[0];
    }

    b = obj[1];
    t[1] = b;
    if (b != 0) {
        t[1] = b - *(u16 *)((s32)a0 + 0x16);
        if (t[1] < 0) {
            t[1] = 0;
        }
        obj[1] = (u8)t[1];
    }

    b = obj[2];
    t[2] = b;
    if (b != 0) {
        t[2] = b - *(u16 *)((s32)a0 + 0x1A);
        if (t[2] < 0) {
            t[2] = 0;
        }
        obj[2] = (u8)t[2];
    }

    if (t[0] | t[1] | t[2]) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += *(u16 *)((s32)a0 + 0x2C);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
    } else {
        func_801292C8((u8 *)a0);
    }
}



extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8001CD9C(s32, s32);
extern Blk4_801A7358 D_801A01E8;
extern Blk4_801A7358 D_801F88F8;

void func_801A7F84(s32 a0) {
    s32 v1;
    s32 t;
    s32 buf;

    buf = *(s32 *)(a0 + 0x24);
    func_800233CC((void *)buf, 0x80);
    *(Blk4_801A7358 *)(buf + 0x0) = D_801A01E8;
    *(Blk4_801A7358 *)(buf + 0x4) = D_801A01E8;
    func_8001CD9C(*(s32 *)(a0 + 0x20), (s32)&D_801F88F8);

    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v1 + 0x1A) = 0x3800;
    *(s16 *)(v1 + 0x18) = 0x3800;

    *(s32 *)(a0 + 0x1C) = 0x10;

    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v1 + 0x1E) = 0xD00;

    t = *(s32 *)(a0 + 0x20);
    *(s32 *)(t + 0x4) |= 0x60000000;

    v1 = *(s32 *)(a0 + 0x20);
    *(u16 *)(v1 + 0x2C) = 0xC040;

    *(s16 *)(a0 + 0x2) = 8;
}




extern Blk4_801A7358 D_801A01E8;
extern s32 D_801F89B8[];
extern u8 D_801B0388;
extern u8 D_801F89BC;

void func_801A8054(s32 a0)
{
    s32 v0;

    *(Blk4_801A7358 *)&D_801F89B8 = *(Blk4_801A7358 *)&D_801A01E8;
    *(Blk4_801A7358 *)&D_801F89BC = *(Blk4_801A7358 *)&D_801B0388;

    v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;

    *(s32 *)(a0 + 0x1C) = 1;
    *(s16 *)(a0 + 2) = 9;
}


#include "common.h"

extern void func_801A8494(void *a0);
extern void func_800234E4(void *a0, s32 a1, s32 a2);
extern void func_801292C8(u8 *a0);

extern s32 D_801F89B8[];

extern u8 D_801F89BC;
extern u8 D_801B0388;
extern u8 D_801B0389;
extern u8 D_801B038A;

void func_801A80C0(void *a0) {
    u16 v0;

    func_801A8494(a0);

    v0 = *(u16 *)((s32)a0 + 0x2A) + 8;
    *(u16 *)((s32)a0 + 0x2A) = v0;
    func_800234E4((void *)D_801F89B8, 0x80, v0);

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) < 0x1E00) {
        if (*(s32 *)((s32)a0 + 0x1C) != 0) {
            *(s32 *)((s32)a0 + 0x1C) -= 1;
            if (*(s32 *)((s32)a0 + 0x1C) == 0) {
                s32 p = *(s32 *)((s32)a0 + 0x20);
                *(u16 *)(p + 0x1A) = 0x800;
                *(u16 *)(p + 0x18) = 0x800;
            }
        }

        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) + 0x2C0;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);

        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) >= 0x1E00) {
            *(s32 *)((s32)a0 + 0x1C) = 0x30;
        }
    } else {
        if (*(s32 *)((s32)a0 + 0x1C) != 0) {
            *(s32 *)((s32)a0 + 0x1C) -= 1;
        } else {
            u8 *p = &D_801F89BC;
            D_801F89BC -= (D_801B0388 >> 4);
            p[1] -= (D_801B0389 >> 4);
            p[2] -= (D_801B038A >> 4);
            if (D_801F89BC == 0) {
                func_801292C8((u8 *)a0);
            }
        }
    }
}


__asm__(".section .rodata\nD_801A0210:\n.word 0x00C0C0C0\n.section .text");  // !FAKE: instruction .section — REFUSED asm-data: a `.section` block defines data as assembly (a rodata carve, not a compiler steer) — T7 (P36 rung B tus11)

void func_801A8228(s32 a0)
{
    typedef struct { char c[4]; } Blk4;

    extern s32 D_801A0210;
    extern s32 D_801F89FC;
    extern u8 D_801F89F8[];
    extern Blk4_801A7358 D_801A01E8;

    s32 v0;

    *(Blk4 *)&D_801F89F8 = *(Blk4 *)&D_801A0210;
    *(Blk4 *)&D_801F89FC = *(Blk4 *)&(*(struct {char c [ 4 ] ;} *)&D_801A01E8);

    v0 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(a0 + 0x1C) = 1;
    *(s16 *)(a0 + 2) = 0xA;
}


#include "common.h"

extern void func_801A8494(void *a0);
extern void func_801292C8(u8 *a0);
extern u8 D_801F89F8[4];

void func_801A8294(void *a0) {
    u8 *base;
    s32 sub;
    s16 val;

    base = D_801F89F8;
    func_801A8494(a0);

    sub = *(s32 *)((s32)a0 + 0x20);
    val = *(s16 *)(sub + 0x18);

    if (val < 0x3000) {
        if (*(s32 *)((s32)a0 + 0x1C) != 0) {
            *(s32 *)((s32)a0 + 0x1C) -= 1;
        } else {
            *(s16 *)(sub + 0x1A) = 0x6000;
            *(s16 *)(sub + 0x18) = 0x6000;
            *(s32 *)((s32)a0 + 0x1C) = 0x30;
        }
        return;
    }

    if (val > 0x3000) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = val - 0x100;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        return;
    }

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        u8 b0 = *base;

        if (b0 == 0xC0) {
            *base = b0 - 0x10;
            D_801F89F8[1] -= 0x10;
            D_801F89F8[2] -= 0x10;
        } else {
            *base = b0 + 0x10;
            D_801F89F8[1] += 0x10;
            D_801F89F8[2] += 0x10;
        }
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        return;
    }

    *base -= 0x10;
    D_801F89F8[1] -= 0x10;
    D_801F89F8[2] -= 0x10;
    if (*base == 0) {
        func_801292C8((u8 *)a0);
    }
}




void func_801A8404(void *a0) {

    extern void (*D_801B038C[])(void);
    D_801B038C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801A8440(s32 a0) {
    s32 a1;

    a1 = *(s32 *)(a0 + 0x34);
    if (a1 != 0) {
        *(u16 *)(a0 + 0x6) = *(u16 *)(a1 + 0x6) + *(u16 *)(a1 + 0x50);
        *(u16 *)(a0 + 0xA) = *(u16 *)(a1 + 0xA) + *(u16 *)(a1 + 0x52);
        *(u16 *)(a0 + 0xE) = *(u16 *)(a1 + 0xE) + *(u16 *)(a1 + 0x54);
    }
}


typedef struct { s16 x, y, z, pad; } Svec_801A8494;

void func_801A8494(void *a0)
{
    Svec_801A8494 vec;   /* sp+0x10 : RotTransSV in/out */
    s32 flag;            /* sp+0x18 */
    void *t;

    t = *(void **)((u8 *)a0 + 0x34);
    func_8004914C((void *)(*(s32 *)((u8 *)t + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)((u8 *)t + 0x20) + 0x34));

    vec.y = -0x40;
    vec.x = 0;
    vec.z = 0x20;

    RotTransSV((s32)&vec, (s32)&vec, &flag);

    *(u16 *)((u8 *)a0 + 0x06) = vec.x;
    *(u16 *)((u8 *)a0 + 0x0A) = vec.y;
    *(u16 *)((u8 *)a0 + 0x0E) = vec.z;
}


extern s32 func_80132EF4(s32 a0, s32 a1);

s32 func_801A8528(s32 a0) {
    s32 var;

    var = func_80132EF4(a0, 0x30);
    if (var != 0) {
        *(u16 *)(var + 0x2E) = 0;
        *(s32 *)(var + 0x34) = a0;
    }
    return var;
}


extern s32 func_80132EF4(s32 a0, s32 a1);

s32 func_801A8564(s32 a0) {
    s32 var;

    var = func_80132EF4(a0, 0x30);
    if (var != 0) {
        *(u16 *)(var + 0x2E) = 1;
        *(s32 *)(var + 0x34) = a0;
    }
    return var;
}


s32 func_801A85A8_body(s32 a0, s32 a1, s32 a2, s32 a3) __asm__("func_801A85A8");
s32 func_801A85A8_body(s32 a0, s32 a1, s32 a2, s32 a3) {
    extern s32 func_80132EF4(s32 a0, s32 a1);

    s32 ret;

    ret = func_80132EF4(a0, 0x30);
    if (ret != 0) {
        *(u16 *)(ret + 0x2E) = (a2 & 1) + 2;
        *(s32 *)(ret + 0x30) = a1;
        *(s32 *)(ret + 0x34) = a0;
        *(s16 *)(ret + 0x2C) = a3;
    }
    return ret;
}


extern s32 func_80132EF4(s32 a0, s32 a1);

s32 func_801A861C(s32 a0, s16 a1) {
    s32 var;

    var = func_80132EF4(a0, 0x30);
    if (var != 0) {
        *(u16 *)(var + 0x2E) = (a1 & 1) + 4;
        *(s32 *)(var + 0x34) = a0;
    }
    return var;
}


extern s32 func_80132EF4(s32 a0, s32 a1);

s32 func_801A8670(s32 arg0) {
    s32 var_v1;

    var_v1 = func_80132EF4(arg0, 0x30);
    if (var_v1 != 0) {
        *(u16 *)(var_v1 + 0x2E) = 6;
        *(s32 *)(var_v1 + 0x34) = arg0;
    }
    return var_v1;
}


extern s32 func_80132EF4(s32 a0, s32 a1);

s32 func_801A86B4(s32 a0) {
    s32 var;

    var = func_80132EF4(a0, 0x30);
    if (var != 0) {
        *(u16 *)(var + 0x2E) = 7;
        *(s32 *)(var + 0x34) = a0;
    }
    return var;
}


extern u8 D_801F8978[3];
extern void func_801A8738();

void func_801A86F8(void) {
    u8 *p = D_801F8978;
    func_801A8738(p);
    func_801A8738(&p[1]);
    func_801A8738(&p[2]);
}


void func_801A8738(s32 a0) {
    s32 v;
    s16 c;

    c = *(u8 *)a0;
    if (c == 0xFF) {
        return;
    }
    c += 2;
    if (c > 0xFF) {
        c = 0xFF;
    }
    *(u8 *)a0 = c;
}


void func_801A876C(s32 arg0, s16 arg1, s32 arg2) {
    if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) < arg1) {
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + arg2;
    }

    if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) < arg1) {
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) + arg2;
    }
}


void func_801A87C4(s32 a0, s16 a1, s32 a2) {
    s16 varA;
    s16 varB;

    varA = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18);
    if (a1 < varA) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = varA - a2;
    }
    varB = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
    if (a1 < varB) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = varB - a2;
    }
}


extern s32 rand(void);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A881C(s32 a0)
{
    s32 r1;
    s32 r2;

    *(u16 *)((s32)a0 + 0xFE) = 0x10;
    r1 = rand();
    *(u16 *)((s32)a0 + 0x100) = r1;
    r2 = (rand() & 0x1F) + 0x40;
    *(u16 *)((s32)a0 + 0x102) = r2;
    if ((r2 & 1) != 0) {
        *(u16 *)((s32)a0 + 0x102) = -r2;
    }
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
    func_8012AD44(a0, 1);
}



extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A8884(s32 *a0) {
    a0[7] = 0x3;
    func_8012AD44(a0, 2);
}


extern void VectorNormal();
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A88AC(void *arg0)
{
    s32 sp10[3];

    sp10[0] = *(s16 *)(*(s32 *)((u8 *)arg0 + 0x64) + 0x6) - *(s16 *)((u8 *)arg0 + 0x6);
    sp10[1] = *(s16 *)(*(s32 *)((u8 *)arg0 + 0x64) + 0xA) - *(s16 *)((u8 *)arg0 + 0xA);
    sp10[2] = *(s16 *)(*(s32 *)((u8 *)arg0 + 0x64) + 0xE) - *(s16 *)((u8 *)arg0 + 0xE);
    VectorNormal(sp10, sp10);

    *(s32 *)((u8 *)arg0 + 0x10) = sp10[0] << 9;
    *(s32 *)((u8 *)arg0 + 0x14) = sp10[1] << 9;
    *(s32 *)((u8 *)arg0 + 0x18) = sp10[2] << 9;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x20;

    func_8012AD44((s32 *)arg0, 3);
}




void func_801A8954(void *a0) {

    extern void (*D_801B03B8[])(void);
    D_801B03B8[*(u16 *)((s32)a0 + 0x2)]();
}


typedef struct { u16 vx, vy, vz, pad; } SV_801A8990;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_801A8990;

void func_801A8990(void *a0)
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern s32 func_8004787C(s32 a0);
    extern void RotTransSV(s32 a0, s32 a1, void *a2);

    SV_801A8990 vec;   /* sp+0x10 */
    MTX_801A8990 mtx;  /* sp+0x18 */
    MTX_801A8990 *mp;
    s32 flag[3];       /* sp+0x38 */
    s32 v1;
    s32 prod;

    mp = &mtx;
    func_80049CAC(*(s32 *)((s32)a0 + 0x20) + 0x10, (s32)mp);

    mtx.t[0] = *(s16 *)((s32)a0 + 0x104);
    mtx.t[1] = *(s16 *)((s32)a0 + 0x106);
    mtx.t[2] = *(s16 *)((s32)a0 + 0x108);

    func_8004914C(mp);
    func_800491AC(mp);

    vec.vy = 0;
    vec.vx = 0;

    prod = func_8004787C(*(s16 *)((s32)a0 + 0x100));
    v1 = *(s16 *)((s32)a0 + 0xFE);
    vec.vz = v1 + ((v1 * prod) >> 15);

    RotTransSV((s32)&vec, (s32)&vec, &flag[0]);

    *(s16 *)((s32)a0 + 0x6) = vec.vx;
    *(s16 *)((s32)a0 + 0xA) = vec.vy;
    *(s16 *)((s32)a0 + 0xE) = vec.vz;
}


extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s16 D_801B03CC;
extern u8 D_801B03CE[];

void func_801A8A64(s32 a0) {
    s16 *s0;
    s32 s1;
    s32 s4;
    s32 s2 = 0;

    if (D_801B03CC == 0xFFF) {
        return;
    }
    s4 = 0xFFF;
    s0 = &D_801B03CC;
    s1 = 0;
    do {
        s32 ret = func_8012C658(0xC1, s2, a0);
        if (ret != 0) {
            *(s16 *)(*(s32 *)(ret + 0x20) + 0x12) = *(u16 *)(D_801B03CE + s1);
            *(s16 *)(*(s32 *)(ret + 0x20) + 0x14) = *(u16 *)s0;
        }
        s0 += 2;
        s1 += 4;
        s2 += 1;
    } while (*s0 != s4);
}




void func_801A8B28(void *a0) {

    extern void (*D_801B0400[])(void);
    D_801B0400[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* TU already declares these exact spellings (law 2) */
extern u8 D_800AF648;
extern s32 ratan2(s32 a0, s32 a1);

/* GTE input vertex {vx,vy,vz,pad} -- own name/layout, per law 8 */
typedef struct {
    s16 vx, vy, vz, pad;
} SVec16_801A8B64;

/* GTE screen-space xy result {x,y,z,pad} -- only x/y are read back */
typedef struct {
    s16 x, y, z, pad;
} SXY_801A8B64;




void func_801A8B64(s32 arg0, s32 arg1)
{
    SVec16_801A8B64 v;
    SXY_801A8B64 xy0;
    SXY_801A8B64 xy1;
    register s32 g __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus9)
    s32 ang;
    s32 dy, dx;
    s32 *p;

    g = (s32)&D_800AF648;

    /* gte_SetRotMatrix(&D_800AF648) */
    __asm__ __volatile__(  // !FAKE: gte direct — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n" "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
        : : "r"(g) : "$12", "$13", "$14", "memory");

    /* gte_SetTransMatrix(&D_800AF648) */
    __asm__ __volatile__(  // !FAKE: gte direct — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n" "ctc2 $14, $7\n"
        : : "r"(g) : "$12", "$13", "$14", "memory");

    gte_ldv0(arg1);
    gte_rtps();
    gte_stsxy(&xy0);

    v.vx = *(u16 *)(arg0 + 0x6);
    v.vy = *(u16 *)(arg0 + 0xA);
    v.vz = *(u16 *)(arg0 + 0xE);

    gte_ldv0(&v);
    gte_rtps();
    gte_stsxy(&xy1);

    dy = xy1.y - xy0.y;
    dx = xy1.x - xy0.x;
    ang = ratan2(dy, dx);

    p = *(s32 **)(arg0 + 0x20);
    *(s16 *)((u8 *)p + 0x14) = ang + 0x400;
}


#include "common.h"

extern int rand(void);
extern void func_801A8CE0(s32 a0, s16 a1, s32 a2, s32 a3);
extern void func_801A900C(s32 a0);

void func_801A8C58(s32 s2)
{
    s32 i;
    s32 base;
    s32 y;
    s32 sel;

    i = 0;
    base = -0x40;
    while (i < 0x10) {
        y = base + (rand() & 0x7F);
        sel = (i & 1) ? 0xC0000 : 0x140000;
        func_801A8CE0(s2, (s16)y, sel, 0x14);
        i++;
        base += 0x100;
    }
    func_801A900C(s2);
}


extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012B744(void *a0, void *a1);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

typedef struct { s16 x, y, z, pad; } Svec_A8CE0;
typedef struct { s16 m[3][3]; s16 t[3]; s16 pad[4]; } Mtx_A8CE0 __attribute__((aligned(8)));

void func_801A8CE0(s32 a0, s16 a1, s32 a2, s32 a3)
{
    Svec_A8CE0 sp10;
    s32 flag[3];
    Mtx_A8CE0 mtx;
    s32 var_s1;
    s32 ret;

    var_s1 = func_80132EF4((s32)a0, 0x70);
    if (var_s1 != 0) {
        *(u16 *)(var_s1 + 0xA) += *(u16 *)((s32)a0 + 0x52);
        *(s32 *)(var_s1 + 0x1C) = (s16)a3;
        sp10.x = D_801269A4;
        sp10.y = D_801269A8;
        sp10.z = D_801269AC;
        ret = func_8012B744((void *)((s32)a0 + 4), &sp10);
        sp10.x = 0x200;
        sp10.y = ret;
        sp10.z = a1;
        RotMatrixYXZ(&sp10, &mtx);
        flag[0] = a2;
        flag[1] = flag[2] = 0;
        func_800484EC((s32)&mtx, (s32)flag, var_s1 + 0x10);
        *(u16 *)(var_s1 + 0x2C) = 0;
    }
}


extern int rand(void);
extern void func_801A8E34(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_801A8DCC(s32 a0, s32 a1)
{
    s32 s0;
    s32 v0;

    s0 = rand() & 0xFF8;
    v0 = rand();
    func_801A8E34(a0, a1, s0, ((v0 & 0xF) + 0x38) << 15, 0x14);
}


#include "common.h"

/* Declarations copied verbatim from this TU's existing externs
   (md_SC07_004.c:2223-2225, :2321, :4039, :4041, :4998). */
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8004978C(s16 *a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

/* Local stack aggregates; suffixed names per this TU's house style
   (cf. Struct801AD7EC_Local / Blk8_801AD914 above). */
typedef struct { s16 m[4]; } SVec801A8E34;   /* sp+0x10 */
typedef struct { s32 m[4]; } Vec801A8E34;    /* sp+0x18 */
typedef struct { s16 m[16]; } Mat801A8E34;   /* sp+0x28 */

/* NOTE (cookbook §167-13 bound): parameter 2 is `s16`, not `s32`.  The narrow
   declaration is load-bearing, not cosmetic — assign_parms emits a promotion
   insn whose SET_SRC is a PSEUDO, which terminates sched.c:3186-3213's bb0
   parameter-copy pin run after the a0/a1 copies.  That frees the a2/a3 copies
   and the stack-arg load, and sched1's backward birthing boost then emits them
   last, reversed: sw $s6/lw $s6 / li $a1,0x70 / sw $s5/move $s5 / sw $s4/move
   $s4.  Widening a2 to s32 re-pins all four copies and costs 7 mismatches. */
void func_801A8E34(a0, a1, a2, a3, a4) s32 a0; s32 a1; s16 a2; s32 a3; s32 a4; {
    SVec801A8E34 h;
    Vec801A8E34 st;
    Mat801A8E34 buf;
    s32 s1;
    s32 t;

    s1 = func_80132EF4(a0, 0x70);
    if (s1 == 0) {
        return;
    }

    h.m[0] = D_801269A4;
    h.m[1] = D_801269A8;
    h.m[2] = D_801269AC;
    t = func_8012B744((void *) (a0 + 4), &h);

    h.m[0] = 0x200;
    h.m[1] = t;
    h.m[2] = a2;
    func_8004978C((s16 *) &h, &buf);

    st.m[0] = -a3;
    st.m[2] = 0;
    st.m[1] = 0;
    func_800484EC((s32) &buf, (s32) &st, s1 + 0x10);

    t = (s16) a4;
    *(s32 *) (s1 + 0x1C) = t;
    *(s32 *) (s1 + 0x4) -= *(s32 *) (s1 + 0x10) * t;
    *(s32 *) (s1 + 0x8) -= *(s32 *) (s1 + 0x14) * t;
    *(s32 *) (s1 + 0xC) -= *(s32 *) (s1 + 0x18) * t;
    if (t >= 2) {
        *(s32 *) (s1 + 0x1C) = t - 1;
    }

    *(u16 *) (s1 + 0x2C) = 1;
    *(s32 *) (s1 + 0x34) = a0;

    *(u16 *) (s1 + 0x2E) = *(u16 *) (s1 + 0x6) - *(u16 *) (a0 + 0x6);
    *(u16 *) (s1 + 0x30) = *(u16 *) (s1 + 0xA) - *(u16 *) (a0 + 0xA);
    *(u16 *) (s1 + 0x32) = *(u16 *) (s1 + 0xE) - *(u16 *) (a0 + 0xE);

    if (a1 != 0) {
        *(u16 *) (s1 + 0x2E) += *(u16 *) (a1 + 0x0);
        *(u16 *) (s1 + 0x30) += *(u16 *) (a1 + 0x2);
        *(u16 *) (s1 + 0x32) += *(u16 *) (a1 + 0x4);
    }
}


extern void func_801AA91C(s32 a0, s32 a1, s32 a2);

void func_801A900C(s32 a0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_801AA91C(a0, -0x300, (s16)(i << 10));
        func_801AA91C(a0, 0x300, (s16)(i << 10));
    }

    for (i = 0; i < 8; i++) {
        func_801AA91C(a0, -0x180, (0x1000000 + i * 0x2000000) >> 16);
        func_801AA91C(a0, 0x180, (0x1000000 + i * 0x2000000) >> 16);
        func_801AA91C(a0, 0, (s16)(i << 9));
    }
}


#include "common.h"

extern int rand(void);   /* canonical: identical decl already at md_SC07_004.c:1116 */
extern void RotMatrixY(s32 a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8012AD44(s32 *a0, s16 a1);   /* verbatim from md_SC07_004.c:866 */
extern s16 D_80126B5E;                        /* verbatim from md_SC07_004.c:1301 */
extern s16 D_80126B66;                        /* verbatim from md_SC07_004.c:1303 */

/* PsyQ MATRIX-shaped 0x20-byte template; copied whole onto the stack (house
 * style: md_MAIN_022.c:140 Blk20_800CB68C / ov_MAIN_012 func_80168664 Blk20).
 * The TU's own MTX_801AAF8C typedef (line 1289) is declared BELOW this
 * function's INCLUDE_ASM slot (line 910), so it is not in scope here — hence
 * the local per-function typedef, matching the sibling md_SC07_004 drafts
 * (func_801A4EBC / func_801A5698 do the same). Banking pass reconciles. */

extern Mtx32_801A90D8 D_800AE620;

/* SVECTOR-shaped 4x s16 (vx,vy,vz,pad) — same shape as this TU's own
 * SV_801AAF8C (line 1287), likewise out of scope at line 910. */
typedef struct { s16 vx, vy, vz, pad; } SV_801A90D8;

void func_801A90D8(s32 a0)
{
    s16 dx;
    s16 dz;
    s32 distSq;
    s32 s2;

    dx = D_80126B5E;
    dz = D_80126B66;
    distSq = dx * dx + dz * dz;
    s2 = *(s32 *)(a0 + 0xCC);          /* the mirrored/render node */

    *(s16 *)(a0 + 0xA) = (s16)-0x500;  /* y */

    if ((rand() & 0xF) != 0 || 0xF8100 < distSq) {
        Mtx32_801A90D8 mtx;
        SV_801A90D8 vin;
        SV_801A90D8 vout;
        s32 ang;
        s32 r2;

        ang = rand();
        mtx = D_800AE620;              /* 8-word template copy to sp+0x10 */
        RotMatrixY(ang & 0xFF8, &mtx);
        /* BOTH zero stores are written BEFORE the rand() call: cc1 emits them
         * in source order ahead of the jal and reorg then lifts the LAST one
         * (vin.vx, sp+0x30) into the call's delay slot, leaving vin.vy
         * (sp+0x32) plain above it — exactly the target's split.  Writing
         * vin.vx AFTER the call instead leaves it stranded below and costs the
         * 7-instruction rotation this draft's predecessor carried. */
        vin.vy = 0;
        vin.vx = 0;
        r2 = rand();
        vin.vz = -(r2 & 0x3F8);
        ApplyMatrixSV(&mtx, &vin, &vout);
        *(s16 *)(a0 + 0x6) = vout.vx + 0x90;   /* x */
        *(s16 *)(a0 + 0xE) = vout.vz;          /* z */
    } else {
        *(u16 *)(a0 + 0x6) = (u16)D_80126B5E + 0x90;
        *(u16 *)(a0 + 0xE) = (u16)D_80126B66;
    }

    *(u16 *)(s2 + 0x8) = *(u16 *)(a0 + 0x6);
    *(u16 *)(s2 + 0xA) = *(u16 *)(a0 + 0xA);
    *(u16 *)(s2 + 0xC) = *(u16 *)(a0 + 0xE);
    *(s32 *)(a0 + 0x14) = 0x200000;
    *(s32 *)(a0 + 0x10) = (s32)0xFFFA0000;
    *(s32 *)(a0 + 0x1C) = 0;
    /* Likewise before the call: a0[0x84]=8 is the last pre-jal store, so reorg
     * takes it as the delay filler and `sw zero,0x1C(a0)` stays plain above.
     * No `register ... __asm__("$4")` pin is needed — once the store order is
     * right, optimize_reg_copy_1 (§193-D) re-bases the whole block onto $a0
     * by itself. */
    *(s16 *)(a0 + 0x84) = 8;
    func_8012AD44((s32 *)a0, 1);
}


#include "common.h"

extern int rand(void);
extern void func_801439C0(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s16 D_801F8E98;

void func_801A9270(void *a0) {
    s32 p;
    s32 t;
    s32 g;

    t = (rand() & 7) + 0x50;
    p = *(s32 *)((s32)a0 + 0xD0);
    *(s32 *)((s32)a0 + 0x1C) = t;
    if (p != 0) {
        func_801439C0((u8 *)p);
    }
    func_8012AD44((s32 *)a0, 2);
    func_8012C658(0x44, 1, (s32)a0);
    g = D_801F8E98;
    *(u16 *)((s32)a0 + 6) = *(u16 *)((s32)a0 + 6) - 0x20;
    if (g == 0) {
        func_8002D4C8(0xABD, 0);
    }
    D_801F8E98 = D_801F8E98 + 1;
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A930C(s32 arg0)
{
    *(s32 *)(arg0 + 0x1C) = *(s32 *)(*(s32 *)(arg0 + 0x64) + 0x1C);
    func_8012AD44((s32 *)arg0, 3);
}




void func_801A933C(void *a0) {

    extern void (*D_801B0494[])(void);
    D_801B0494[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801A9378(void *a0) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_801AAF34();
    if (func_801AAF34(a0, 0, 0x20)) {
        D_80126B96 = 0x400B;
        D_80126B98 = 0x50;
    }
}




void func_801A93B8(void *a0) {

    extern void (*D_801B05FC[])(void);
    D_801B05FC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);

/* §200 DEF-side alias: the TU prototypes this symbol `void func_801A93F4(void *)`
 * (md_SC07_004.c:5645, written for caller func_801ABEE0), but the body provably
 * returns s0 (beqz delay slot holds `addu $v0,$s0,$zero`, §162f1) — a void
 * definition loses that slot (near 9 / 23 ins). Private C name, same symbol. */
s32 aF801A93F4(void *a0) __asm__("func_801A93F4");

s32 aF801A93F4(void *a0) {
    s32 s0;

    s0 = func_80132EF4(a0, 0x2D);
    if (s0 != 0) {
        *(s32 *)(s0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
        *(u16 *)(s0 + 0x2C) = rand() & 1;
    }
    return s0;
}


s32 func_801A9454(s32 self, s32 amount) {
    s32 obj;
    u16 v;

    obj = func_80132EF4(self, 0x2D);
    if (obj != 0) {
        v = *(u16 *)(obj + 0xA);
        *(u16 *)(obj + 0x2C) = 2;
        *(u16 *)(obj + 0xA) = v + amount;
    }
    return obj;
}




extern void RotMatrixY(s32 a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B21C(void *a0);
extern s32 rand(void);
extern s32 ratan2(s32 a0, s32 a1);

void func_801A94A0(s32 *s1)
{
    s16 angle;
    s32 vz;
    s32 t;
    s16 flag;
    Mtx32_801A90D8 mtx;
    SV_801A90D8 vin;
    SV_801A90D8 vout;

    func_8012B21C(s1);
    if (*(s16 *)((s8 *)s1 + 0xFE) != 0) {
        *(s16 *)((s8 *)s1 + 0xA) = -0x500;
        if (*(s16 *)((s8 *)s1 + 0x70) == 0) {
            angle = rand() & 0xFF8;
            t = rand();
            vz = -(t % 704);
            flag = 1;
        } else {
            s16 dx = D_80126B5E;
            s16 dz = D_80126B66;
            if (dx * dx + dz * dz <= 0x78FFF) {
                *(s16 *)((s8 *)s1 + 6) = dx;
                *(u16 *)((s8 *)s1 + 0xE) = *(u16 *)&D_80126B66;
                flag = 0;
            } else {
                angle = (ratan2(-dz, dx) - 0x400) & 0xFFF;
                vz = -0x2C0;
                flag = 1;
            }
        }
        {
            s32 doMatrix;
            doMatrix = flag;
        if (doMatrix != 0) {
            mtx = D_800AE620;
            RotMatrixY(angle, &mtx);
            vin.vy = 0;
            vin.vx = 0;
            vin.vz = vz;
            ApplyMatrixSV(&mtx, &vin, &vout);
            *(u16 *)((s8 *)s1 + 6) = vout.vx;
            *(u16 *)((s8 *)s1 + 0xE) = vout.vz;
        }
        }
        *(s32 *)((s8 *)s1 + 0x14) = 0x80000;
    } else {
        *(s32 *)((s8 *)s1 + 0x48) = 0x12000;
    }
    func_8012AD44((s32 *)s1, 1);
}


#include "common.h"

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_8012AD80(s32 a0);
extern void func_801A9810();
extern void func_801A9908(void *a0, s32 a1);
extern void func_801A9954(void *a0);
extern u16 D_801B070C[];

void func_801A9674(void *a0) {
    void *s0 = a0;
    void *s1;
    void *s2;
    s32 s3;
    s32 sq0;
    s32 sq1;

    s1 = *(void **)((s32)s0 + 0xCC);
    s2 = *(void **)((s32)s0 + 0xD0);

    func_80128ED8((s32)s1, (s32 *)((s32)s0 + 0xF0));

    *(u8 *)((s32)s1 + 0x27) = (u8)D_801B070C[*(s16 *)((s32)s0 + 0xF4)];

    func_8012AD80((s32)s0);

    *(s16 *)((s32)s1 + 0x8) = *(u16 *)((s32)s0 + 0x6);
    *(s16 *)((s32)s1 + 0xA) = *(u16 *)((s32)s0 + 0xA);
    *(s16 *)((s32)s1 + 0xC) = *(u16 *)((s32)s0 + 0xE);

    if (*(s16 *)((s32)s0 + 0xFE) != 0) {
        s3 = 0x30;
        *(s16 *)((s32)s1 + 0x18) = (*(s16 *)((s32)s0 + 0xA) + 0x1400) * 2;
        *(s16 *)((s32)s1 + 0x1A) = (0x1000 - *(s16 *)((s32)s0 + 0xA)) * 6;
    } else {
        s3 = 0x18;
    }

    if (*(s16 *)((s32)s0 + 0xA) >= -0x200) {
        sq0 = *(s16 *)((s32)s0 + 0x6) * *(s16 *)((s32)s0 + 0x6);
        sq1 = *(s16 *)((s32)s0 + 0xE) * *(s16 *)((s32)s0 + 0xE);
        *(s16 *)((s32)s0 + 0xA) = -0x200;
        if (sq0 + sq1 > 0xFFFFF) {
            func_801A9954(s0);
            return;
        }
        func_801A9810(s0);
    } else {
        if (*(s16 *)((s32)s0 + 0xFE) != 0 && s2 != NULL) {
            s1 = *(void **)((s32)s2 + 0xCC);
            if (s1 != NULL) {
                s32 v = (*(s16 *)((s32)s0 + 0xA) + 0x500) * 40;
                *(s16 *)((s32)s1 + 0x1A) = v;
                *(s16 *)((s32)s1 + 0x18) = v;
            }
        }
    }
    func_801A9908(s0, s3);
}


#include "common.h"

extern void func_801439C0(u8*);
extern void func_801AA60C();
extern void func_801A99A4();
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);

extern u8 D_801B0604[];
extern u8 D_801B061C[];
extern u8 D_801B0694[];

void func_801A9810(void *a0) {
    s32 s1;

    s1 = *(s32 *)((s32)a0 + 0xCC);
    if (*(s32 *)((s32)a0 + 0xD0) != 0) {
        ((void (*)(s32))func_801439C0)(*(s32 *)((s32)a0 + 0xD0));
        *(s32 *)((s32)a0 + 0xD0) = 0;
    }
    if (*(s16 *)((s32)a0 + 0xFE) != 0) {
        func_801AA60C(a0, 0xAB7);
        func_801A99A4(a0);
        func_80128EA8(s1, (s32)a0 + 0xF0, (s32)D_801B061C);
    } else {
        func_80128EA8(s1, (s32)a0 + 0xF0, (s32)D_801B0694);
    }
    *(s32 *)(s1 + 0x20) = (s32)D_801B0604;
    *(s16 *)(s1 + 0x28) = 0x340;
    *(s16 *)(s1 + 0x2A) = 0x100;
    func_8012AD44((s32 *)a0, 2);
}




void func_801A98CC(void *a0) {

    extern void (*D_801B072C[])(void);
    D_801B072C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801A9908(void *a0, s32 a1) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_801AAF34();
    if (func_801AAF34(a0, 0, (s16)a1)) {
        D_80126B98 = 0x46;
        D_80126B96 |= 0x4000;
    }
}


extern void func_801439C0(u8 *a0);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801A9954(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xD0);
    if (temp_a0 != NULL) {
        func_801439C0(temp_a0);
    }
    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    func_80016714(temp_a0, 0x38);
    func_8012C218(arg0);
}


#include "common.h"



extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern Mtx32_801A90D8 D_800AE620;
extern s32 D_801B0738;
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_801A99A4(s32 a0)
{
    Mtx32_801A90D8 mtx;
    s16 i;

    for (i = 0; i < 0x1000; i += 0x200) {
        s32 *obj = (s32 *)func_8012C658(0x34, 0x100, a0);
        if (obj != NULL) {
            mtx = D_800AE620;
            RotMatrixY(i, &mtx);
            func_800484EC((s32)&mtx, (s32)&D_801B0738, (s32)obj + 0x10);
            *(s32 *)((s32)obj + 4) += *(s32 *)((s32)obj + 0x10);
            *(s32 *)((s32)obj + 0xC) += *(s32 *)((s32)obj + 0x18);
        }
    }
}


void func_801A9AAC(void) {
    extern void func_80128D60(s32, s32 *, s32 *);
    extern s32 D_801F8A50;
    extern s32 D_801B0748;

    func_80128D60(0, &D_801F8A50, &D_801B0748);
}


s32 func_801A9ADC(void) {
    extern s32 func_80128DB4(s32, s32 *);
    extern s32 D_801F8A50;

    return func_80128DB4(0, &D_801F8A50);
}




void func_801A9B04(void *a0) {

    extern void (*D_801B0768[])(void);
    D_801B0768[*(u16 *)((s32)a0 + 0x2)]();
}


extern void StoreImage(s32, void *);

void func_801A9B40(void *a0, u16 a1, u16 a2) {
    u16 buf[4];

    buf[2] = 0x10;
    buf[0] = a1;
    buf[1] = a2;
    buf[3] = 1;
    StoreImage((s32)&buf, (void *)a0);
}


extern void func_800599B8(void*, void*);

void func_801A9B80(s32 *a0, u16 a1, u16 a2) {
    s32 t1;
    s32 t2;
    s32 i;
    u16 buf[4];

    t1 = a0[7];
    t2 = a0[6];

    i = 7;
    do {
        a0[i] = a0[i - 2];
        a0[i - 1] = a0[i - 3];
        i -= 2;
    } while (i >= 3);

    a0[i] = t1;
    a0[i - 1] = t2;

    buf[2] = 0x10;
    buf[0] = a1;
    buf[1] = a2;
    buf[3] = 1;

    ((void (*)(u16 *, s32 *))func_800599B8)(buf, a0);
}


extern s32 func_8012C2D0(void);
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

void func_801A9C00(void *a0) {
    s32 v0;
    s16 sp[10];
    if (a0 != 0 && *(u16 *)a0 != 0) {
        sp[0] = *(u16 *)((s32)a0 + 0x6);
        sp[1] = *(u16 *)((s32)a0 + 0xA);
        sp[2] = *(u16 *)((s32)a0 + 0xE);
    } else {
        sp[2] = 0;
        sp[1] = 0;
        sp[0] = 0;
    }
    sp[3] = 0x43;
    sp[5] = 0;
    sp[4] = 0;
    *(s32 *)&sp[8] = 0;
    sp[7] = 0;
    sp[6] = 0x7FFF;
    v0 = func_8012C2D0();
    if (v0 != 0) {
        func_8012C890((s32)&sp[0], v0, (s32)a0);
    } else {
        __asm__ __volatile__("addu\t$v0,$zero,$zero");  // !FAKE: instruction addu — REFUSED instruction `addu` has no C spelling in the table (P36 rung B tus9)
    }
}


#include "common.h"

extern u8 D_801B0770[];
extern u8 D_801EFC18[];

extern s32 func_8001D074(s32 a0, s32 a1);
extern void func_8001CB6C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_801A9EB0(void *a0);
extern void func_801A9F5C(void *a0);
extern void func_801A9FA8(void *a0);
extern void func_801AA2F8();
extern void func_801AA60C();

void func_801A9CAC(void *a0) {
    s32 pad[2];
    s32 p;
    s32 r;
    s32 q;

    switch (*(s16 *)((s32)a0 + 0x70)) {
    case 0:
    case 1:
        p = func_8001D074(0x7E, 0x100);
        if (p == 0) {
            func_8012CAE4(a0);
            break;
        }
        *(s32 *)((s32)a0 + 0x20) = p;
        func_8001CB6C(p, (s32)&D_801B0770, 0x280, 0x180);
        *(u8 *)(p + 0x27) = 0xFF;
        *(s16 *)(p + 0x10) = 0x400;
        *(s32 *)(p + 0x4) |= 0x51000000;
        *(s16 *)(p + 0x14) =
            -*(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
        if (*(s16 *)((s32)a0 + 0x70) == 0) {
            *(s16 *)((s32)a0 + 0xFE) = -0x20;
            *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) + 0x180;
        } else {
            *(s16 *)((s32)a0 + 0xFE) = 0x20;
            *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x180;
        }
        *(s16 *)((s32)a0 + 0xA) = *(u16 *)((s32)a0 + 0xA) - 0x40;
        func_801A9EB0(a0);
        func_801AA60C(a0, 0xAB6);
        break;
    case 2:
        func_801AA2F8();
        /* fallthrough */
    case 3:
        q = func_8012C1B8();
        *(s32 *)((s32)a0 + 0x20) = q;
        if (q == 0) {
            func_8012CAE4(a0);
            break;
        }
        func_8001C214(q, (s32)&D_801EFC18);
        r = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(r + 0x2C) = *(u16 *)(r + 0x2C) | 0x10;
        *(s16 *)((s32)a0 + 0xA) = -0x200;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
        if (*(s16 *)((s32)a0 + 0x70) == 2) {
            r = *(s32 *)((s32)a0 + 0x20);
            *(s16 *)(r + 0x1C) = 0x400;
            *(s16 *)(r + 0x18) = 0x400;
            r = *(s32 *)((s32)a0 + 0x20);
            *(s16 *)(r + 0x1A) = 0x600;
            func_801A9F5C(a0);
            func_801AA60C(a0, 0xAB5);
        } else {
            q = *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x18);
            r = *(s32 *)((s32)a0 + 0x20);
            *(s16 *)(r + 0x1C) = q;
            *(s16 *)(r + 0x1A) = q;
            *(s16 *)(r + 0x18) = q;
            func_801A9FA8(a0);
        }
        break;
    }
}


extern void func_8012AD80(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8017D7D4(void *a0, void *a1, void *a2, s32 a3);
extern void func_801AA004(void *a0, void *a1);
extern void func_801AA210(void *a0, void *a1, void *a2);
extern s32 D_801B077C;

void func_801A9EB0(void *arg0) {
    void *s2;
    s8 sp10[0x20];
    s8 sp30[0x18];

    func_801AA004(arg0, sp10);
    func_8012AD80((s32)arg0);
    func_8012AD80((s32)arg0);
    func_801AA210(arg0, sp10, sp30);
    s2 = &D_801B077C;
    *(s32 *)((u8 *)arg0 + 0xCC) = func_8017D7D4(sp30, sp30 + 8, s2, 12);
    *(s32 *)((u8 *)arg0 + 0xD0) = func_8017D7D4(sp30, sp30 + 0x10, s2, 12);
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x30;
    func_8012AD44((s32 *)arg0, 1);
}


extern void func_801AA0B4(void *a0);
extern void func_8012AD80(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A9F5C(void *arg0) {
    *(s32 *)((s32)arg0 + 0x1C) = 0x40;
    func_801AA0B4(arg0);
    func_8012AD80((s32)arg0);
    func_8012AD80((s32)arg0);
    func_8012AD44((s32 *)arg0, 2);
}


void func_801A9FA8(void *arg0) {
    func_8012AD44((s32 *)arg0, 3);
}




void func_801A9FC8(void *a0) {

    extern void (*D_801B0780[])(void);
    D_801B0780[*(u16 *)((s32)a0 + 0x2)]();
}



typedef struct { s32 vx, vy, vz; } Vec32_801AA004;

extern Mtx32_801A90D8 D_800AE620;
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_801AA004(void *arg0, void *arg1)
{
    Vec32_801AA004 off;

    *(Mtx32_801A90D8 *)arg1 = D_800AE620;
    RotMatrixY(-*(s16 *)(*(s32 *)((s32)arg0 + 0x20) + 0x14), arg1);
    off.vy = 0;
    off.vx = 0;
    off.vz = 0xFFE40000;
    func_800484EC((s32)arg1, (s32)&off, (s32)arg0 + 0x10);
}




extern Mtx32_801A90D8 D_800AE620;
extern void RotMatrixY(s32 a0, void *a1);
extern void func_8004914C(void *a0);
extern void ApplyRotMatrixLV(void *a0, void *a1);

void func_801AA0B4(void *a0)
{
    Mtx32_801A90D8 mtx;
    Vec32_801AA004 vel;

    mtx = D_800AE620;
    RotMatrixY(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12), &mtx);
    vel.vy = 0;
    vel.vx = 0;
    vel.vz = 0xFFE40000;
    func_8004914C(&mtx);
    ApplyRotMatrixLV(&vel, (void *)((s32)a0 + 0x10));
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern void ApplyRotMatrix(void *a0, void *a1);
extern void ApplyRotMatrixLV(void *a0, void *a1);

extern u8 D_801B0790[];
extern u8 D_801B07A0[];

void func_801AA160(s32 arg0, s32 arg1)
{
    s32 vec[12]; /* sp+0x10 */
    s32 s1;
    s32 s0;

    s1 = arg1;
    s0 = func_80132EF4(arg0, 0x22);
    if (s0 != 0) {
        ApplyRotMatrix((void *)(D_801B0790 + (s1 << 3)), vec);
        *(u16 *)(s0 + 0x6) += vec[0];
        *(u16 *)(s0 + 0xA) += vec[1];
        *(u16 *)(s0 + 0xE) += vec[2];
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = 0xC020;
        ApplyRotMatrixLV((void *)(D_801B07A0 + (s1 << 4)), (void *)(s0 + 0x10));
        *(u16 *)(s0 + 0x34) = 0x3400;
    }
}


typedef struct { s16 vx, vy, vz; } SV_801AA210;

extern void func_80020F34(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);

void func_801AA210(void *a0, void *a1, void *a2)
{
    SV_801AA210 sv;   /* sp+0x10 */
    u16 arr[3];       /* sp+0x18 */
    s32 flag;         /* sp+0x20 */

    *(s32 *)((s8 *)a1 + 0x14) = *(s16 *)((s8 *)a0 + 0x6);
    *(s32 *)((s8 *)a1 + 0x18) = *(s16 *)((s8 *)a0 + 0xA);
    *(s32 *)((s8 *)a1 + 0x1C) = *(s16 *)((s8 *)a0 + 0xE);

    arr[0] = *(u16 *)(*(s32 *)((s8 *)a0 + 0x20) + 0x18);
    arr[1] = 0x1000;
    arr[2] = *(u16 *)(*(s32 *)((s8 *)a0 + 0x20) + 0x1A);

    func_80020F34((s32)a1, (s32)arr);
    func_8004914C(a1);
    func_800491AC(a1);

    sv.vy = 0;
    sv.vx = 0;
    sv.vz = -0x50;
    RotTransSV((s32)&sv, (s32)a2, &flag);

    sv.vx = -0x38;
    sv.vz = -0x18;
    RotTransSV((s32)&sv, (s32)((s8 *)a2 + 8), &flag);

    sv.vx = 0x38;
    RotTransSV((s32)&sv, (s32)((s8 *)a2 + 0x10), &flag);
}




extern void func_800233CC(void *a0, unsigned short a1);
extern Blk4_801A7358 D_801A01E8;
extern Blk4_801A7358 D_801F88B8;
extern u8 D_801F88B9[];
extern u8 D_801F88BA;

void func_801AA2F8(void) {
    u8 *pbase;
    s32 idx;
    s32 c1;
    s32 p;
    s32 c0;
    u8 *q;
    s32 i;

    i = 0;
    pbase = ((u8 *)&D_801F88B8);
    q = pbase + 4;
    c1 = -1;
    c0 = -0x40;
    p = (s32)pbase;
    idx = 0;

    do {
        func_800233CC((void *)p, 0x20);
        ((u8 *)&D_801F88B8)[idx] = c0;
        D_801F88B9[idx] = c1;
        ((u8 *)&D_801F88BA)[idx] = c1;
        *(Blk4_801A7358 *)q = D_801A01E8;
        q += 0x40;
        c1 -= 0x40;
        c0 -= 0x30;
        p += 0x40;
        idx += 0x40;
        i++;
    } while (i < 4);
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);
extern void ApplyRotMatrix(void *a0, void *a1);
extern void ApplyRotMatrixLV(void *a0, void *a1);

void func_801AA3CC(s32 arg0)
{
    s16 rot[3]; /* sp+0x10 */
    s32 vec[3]; /* sp+0x18 */
    s32 s1;

    s1 = func_80132EF4(arg0, 0x2C);
    if (s1 != 0) {
        rot[0] = (rand() & 0x3F) - 0x20;
        rot[1] = -(rand() & 0x3F);
        rot[2] = rand() & 0x3F;
        ApplyRotMatrix(&rot, &vec);
        *(u16 *)(s1 + 0x6) += vec[0];
        *(u16 *)(s1 + 0xA) += vec[1];
        *(u16 *)(s1 + 0xE) += vec[2];
        vec[2] = 0x40000;
        vec[0] = rot[0] << 14;
        vec[1] = rot[1] << 13;
        ApplyRotMatrixLV(&vec, (void *)(s1 + 0x10));
    }
}


void func_801AA4A8(void *arg0, void *arg1) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_801AA4EC();

    if (func_801AA4EC(arg0, arg1)) {
        D_80126B98 = 100;
        D_80126B96 |= 0x4000;
    }
}


s32 func_801AA4EC(s32 param_1, s32 param_2)
{
    if (func_8012DF34(param_1, param_2, param_2 + 8) == 0) {
        return func_8012DF34(param_1, param_2, param_2 + 0x10) != 0;
    }
    return 1;
}


void func_801AA540(void *arg0) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_801AA584();

    if (func_801AA584()) {
        D_80126B98 = 100;
        D_80126B96 |= 0x4000;
    }
}


extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);

s32 func_801AA584(s32 a0) {
    s16 local_10[3]; /* sp+0x10 */
    s16 local_18[3]; /* sp+0x18 */
    s32 v0;

    local_18[0] = 0x18;
    local_10[0] = 0x18;
    local_18[1] = -0x30;
    local_10[1] = 0;
    local_18[2] = -0x20;
    local_10[2] = -0x20;

    v0 = func_8012DEB8(a0, (s32)local_10, (s32)local_18);

    if (v0 == 0) {
        local_18[0] = -0x18;
        local_10[0] = -0x18;
        v0 = func_8012DEB8(a0, (s32)local_10, (s32)local_18);
        return (v0 != 0) ? 1 : 0;
    }

    return 1;
}


extern u8 D_800AF648;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801AA60C(s32 param_1, s32 param_2)
{
    struct { s16 in[3]; s16 pad; s16 xy[2]; s32 p; s32 flag; } f;
    s32 p1;
    s32 s2;
    s16 q;

    s2 = param_2;
    func_8004914C(&D_800AF648);
    p1 = param_1;
    func_800491AC(&D_800AF648);
    f.in[0] = *(s16 *)(p1 + 6);
    f.in[1] = *(s16 *)(p1 + 0xA);
    f.in[2] = *(s16 *)(p1 + 0xE);
    RotTransPers((s32)f.in, (s32)f.xy, &f.p, &f.flag);
    if (f.flag >= 0 && (u16)(f.xy[0] + 0xC8) < 0x191 && (u16)(f.xy[1] + 0xAA) < 0x155) {
        f.xy[0] = f.xy[0] + 0xA0;
        q = (f.xy[0] * 128) / 320;
        if (q <= 0) {
            q = 1;
        }
        if (q >= 128) {
            q = 127;
        }
        func_8002D4C8(s2 & 0xFFFF, (q | 0x2000) & 0xFFFF);
    }
}




void func_801AA730(void *a0) {

    extern void (*D_801B07C0[])(void);
    D_801B07C0[*(u16 *)((s32)a0 + 0x2)]();
}




void func_801AA76C(void *a0) {

    extern void (*D_801B07C8[])(void);
    D_801B07C8[*(u16 *)((s32)a0 + 0x2)]();
}




void func_801AA7A8(void *a0) {

    extern void (*D_801B07D0[])(void);
    D_801B07D0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Local psyq-style helper structs, same shape as SV_801AAF8C/MTX_801AAF8C
 * used later in this TU (func_801AAF8C) but declared locally here since
 * this function precedes that typedef in the source file. */
typedef struct { s16 vx, vy, vz, pad; } SV_801AA7E4;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_801AA7E4;

extern void func_8004914C(void *a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004978C(s16 *a0, void *a1);
extern void ApplyRotMatrix(void *a0, void *a1);
extern void ApplyRotMatrixLV(void *a0, void *a1);

void func_801AA7E4(u8 *s2)
{
    MTX_801AA7E4 mtx;   /* sp+0x10 */
    SV_801AA7E4 rot;    /* sp+0x30 */
    s32 vec[3];         /* sp+0x38 */

    if (*(s16 *)(s2 + 0x32) == 0) {
        rot.vx = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x10);
        rot.vy = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x12);
        rot.vz = 0;
        func_80049CAC((s32)&rot, (s32)&mtx);

        func_8004914C(&mtx);
        vec[1] = 0;
        vec[0] = 0;
        vec[2] = 0xFFE60000;
        ApplyRotMatrixLV(&vec, (void *)(s2 + 0x10));

        rot.vz = 0;
        rot.vx = 0;
        rot.vy = 3;
        ApplyRotMatrix(&rot, &vec);
    } else {
        func_8004978C((s16 *)(*(s32 *)(s2 + 0x20) + 0x10), &mtx);

        func_8004914C(&mtx);
        vec[0] = 0x480000;
        vec[2] = 0;
        vec[1] = 0;
        ApplyRotMatrixLV(&vec, (void *)(s2 + 0x10));

        rot.vy = 0;
        rot.vx = 0;
        rot.vz = 8;
        ApplyRotMatrix(&rot, &vec);
    }

    *(s16 *)(*(s32 *)(s2 + 0x20) + 0x2E) = vec[0];
    *(s16 *)(*(s32 *)(s2 + 0x20) + 0x30) = vec[1];
    *(s16 *)(*(s32 *)(s2 + 0x20) + 0x32) = vec[2];
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);

void func_801AA91C(s32 param_1, s32 param_2, s32 param_3)
{
    s32 s1 = param_1;
    s32 s2 = param_2;
    s32 s3 = param_3;
    s32 s0;

    s0 = func_80132EF4(param_1, 0x71);

    if (s0 != 0) {
        *(u16 *)(s0 + 0xA) += *(u16 *)(s1 + 0x52);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = s2;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = s3;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x14) = 0;
        *(u16 *)(s0 + 0x30) = 5;
        *(u16 *)(s0 + 0x32) = 0;
        if (rand() & 1) {
            *(s32 *)(s0 + 0x34) = 0x180FF80;
        } else {
            *(s32 *)(s0 + 0x34) = 0x1FF8080;
        }
    }
}


void func_801AA9D4(s32 a0, s32 a1) {
    extern u8 *func_8012913C(s32 a0);

    typedef struct { u16 w0, w1, w2, w3; } Blk8;

    s32 work;
    s32 ptr;

    work = (s32)func_8012913C(0x71);

    if (a0 != 0) {
        *(u16 *)(work + 0x6) = *(u16 *)(a0 + 0x6);
        *(u16 *)(work + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(work + 0xE) = *(u16 *)(a0 + 0xE);
        ptr = *(s32 *)(work + 0x20);
        *(Blk8 *)(ptr + 0x10) = *(Blk8 *)a1;
        *(u16 *)(work + 0x30) = 5;
        *(u16 *)(work + 0x32) = 1;
        *(u32 *)(work + 0x34) = 0x180F0F0;
    }
}


/* Local mirror of SV4_801AAB28 (that typedef sits below this point in the TU,
   so this card carries its own identically-laid-out record: 4 x u16, size 8).
   Kept a distinct name on purpose -- same shape, different spelling site. */
typedef struct {
    u16 x;      /* +0x0 */
    u16 y;      /* +0x2 */
    u16 num;    /* +0x4 */
    u16 count;  /* +0x6 */
} SV4R_801AAA6C;

/* no-proto on purpose: the real definition (with SV4_801AAB28* params) lives
   further down this TU; a prototyped extern here would be a types conflict */
extern void func_801AAB28();

void func_801AAA6C(s32 a0)
{
    SV4R_801AAA6C r1;   /* sp+0x10 : base point + running offset */
    SV4R_801AAA6C r2;   /* sp+0x18 : {yOff, seg<<10, 0x24, 5} */
    s32 j = 0;
    s16 yOff = -0x200;
    s32 i;

    r1.x = *(u16 *)(a0 + 0x06) + *(u16 *)(a0 + 0x50);
    r1.y = *(u16 *)(a0 + 0x0A) + *(u16 *)(a0 + 0x52);
    r1.num = *(u16 *)(a0 + 0x0E) + *(u16 *)(a0 + 0x54);
    r2.num = 0x24;
    r2.count = 5;
    for (; j < 2; j++) {
        for (i = 0; i < 4; i++) {
            r2.x = yOff;
            r2.y = i * 0x400;
            func_801AAB28(&r1, &r2, 0x101820);
        }
        yOff += 0x400;
    }
}


#include "common.h"

/* 8-byte SVECTOR-shaped record.  Fields 0/2 are the x/y position; on the *a1
   ("spec") side fields 4/6 carry the total amount and the segment count.
   NOT unified with the TU's SV_801AAF8C: that one is s16 and this one must be
   unsigned (every read below is an `lhu`).  Same shape, different signedness
   => own name, per law 8 / cookbook 183.1. */
typedef struct {
    u16 x;      /* +0x0 */
    u16 y;      /* +0x2 */
    u16 num;    /* +0x4 */
    u16 count;  /* +0x6 */
} SV4_801AAB28;

extern int rand(void);
extern void func_801AACD4(void *a0, void *a1, u32 a2, s32 a3);

void func_801AAB28(SV4_801AAB28 *a0, SV4_801AAB28 *a1, s32 a2)
{
    SV4_801AAB28 local1;    /* sp+0x10 : block copy of *a0 (unaligned lwl/lwr) */
    SV4_801AAB28 local2;    /* sp+0x18 : block copy of *a1, x/y then randomised */
    SV4_801AAB28 prev;      /* sp+0x20 : previous emitted x/y (only .x/.y used) */
    SV4_801AAB28 spare;     /* sp+0x28 : never referenced, but the target frame
                               reserves it (var_size 0x20, not 0x18).  A declared
                               aggregate always gets its slot in gcc-2.7.2, so the
                               original had a fourth record here (cookbook 193-I). */
    u32 count;
    u16 num;
    u16 quotient;
    u16 accum;
    s32 n;
    s32 last;
    s32 i;
    s32 r;
    u16 offY;

    count = a1->count;
    num = a1->num;
    /* The `& 0xFFFF` is load-bearing, not cosmetic.  `count` is a u32 fed by an
       `lhu`, so combine folds the mask away for free -- but at cse time the
       compare operand is an AND rather than a bare REG, so record_jump_cond
       (cse.c:5839, "GET_CODE (op0) != REG => return") records NOTHING.  Written
       as a plain `count == 0` cse remembers count != 0 on the fall-through and
       then deletes the loop-entry guard below, costing an instruction and
       shifting the whole preheader. */
    if ((count & 0xFFFF) == 0) {
        return;
    }
    if (num < count) {
        return;
    }
    accum = 0;
    quotient = num / count;

    local1 = *a0;
    local2 = *a1;

    i = 0;
    /* Guard OUTSIDE the loop so `n`/`last` land in the preheader (after the
       branch), which is where the target computes them. */
    if (count != 0) {
        n = count;
        last = n - 1;
        do {
            if (i != 0) {
                r = rand();
                local2.x = prev.x + (r & 0x7FF) - 0x400;
                r = rand();
                offY = prev.y + (r & 0x7FF) - 0x400;
            } else {
                r = rand();
                local2.x = a1->x + (r & 0x1FF) - 0x100;
                r = rand();
                offY = a1->y + (r & 0x1FF) - 0x100;
            }
            local2.y = offY;
            if (i != last) {
                func_801AACD4(&local1, &local2, quotient, a2);
                prev.x = local2.x;
                prev.y = local2.y;
            } else {
                /* narrowed in u16 first: convert_to_integer distributes the
                   truncation into the MINUS, giving `subu` then `andi` (the
                   target shape) instead of widening both operands. */
                func_801AACD4(&local1, &local2, (u16)(num - accum), a2);
            }
            i++;
            accum += quotient;
        } while (i < n);
    }
}


#include "common.h"

/* 8-byte SVECTOR-shaped record (align 2 -> §48-C2 lwl/lwr+swl/swr block copy) */
typedef struct { s16 vx, vy, vz, pad; } SV_801AACD4;
/* PsyQ MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_801AACD4;

void func_801AACD4(void *a0, void *a1, u32 a2, s32 a3)
{
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_801AADA8(s32 a0, s32 a1, s32 a2);

    MTX_801AACD4 mtx;    /* sp+0x10 */
    SV_801AACD4 sv;      /* sp+0x30 */
    s32 flag;            /* sp+0x38 */

    func_80049CAC((s32)a1, (s32)&mtx);
    mtx.t[0] = *(s16 *)((u8 *)a0 + 0);
    mtx.t[1] = *(s16 *)((u8 *)a0 + 2);
    mtx.t[2] = *(s16 *)((u8 *)a0 + 4);
    func_8004914C(&mtx);
    func_800491AC(&mtx);
    sv.vy = 0;
    sv.vx = 0;
    sv.vz = -a2;
    RotTransSV((s32)&sv, (s32)&sv, &flag);
    func_801AADA8((s32)a0, (s32)&sv, a3);
    *(SV_801AACD4 *)a0 = sv;
}



/* func_801AADA8 — allocates a semi-trans LineF2 GPU packet, projects two
 * world-space points via RotTransPers, and (if both are on-screen with
 * non-negative depth-clip flags) links the packet into the current
 * double-buffer's OT at the first point's depth, then notifies via
 * func_80016638.
 *
 * STEP 0 sibling search (§160g) — three already-MATCHED exemplars supplied
 * the whole shape, none needed independent discovery:
 *
 *   1. src/shared/engine_core.h DEFINE_func_8012D3B4() — identical prologue
 *      (temp_v0=func_80010A08(0x10); word4=arg2; func_8004914C/func_800491AC
 *      (&D_800AF648); two RotTransPers calls with the exact
 *      `(d>0) && (flag>=0) && (RotTransPers(...)>0) && (flag>=0)` guard) but
 *      calls a real `SetLineF2()` (code 0x40, no semi-trans) and a real
 *      `AddPrim()` (single evaluation).  Our target's asm has NEITHER a
 *      `jal SetLineF2` NOR a `jal AddPrim` — both are fully inlined, which
 *      is the key structural difference this draft encodes (code 0x42 =
 *      semi-trans LineF2 needs hand-set fields; AddPrim needs the classic
 *      macro body since a *variable* depth offset appears nowhere in the
 *      real AddPrim()-calling siblings).
 *
 *   2. src/ov_SC03_119/ov_SC03_119_jr_8017FB84.c func_80185944 — byte-MATCH
 *      (177/177 ins).  Its header names this exact tail idiom: "link-ins
 *      the packet into the current double-buffer's OT (the PSY-Q `addPrim`
 *      macro pair) and calls func_80016638", with `func_80016638(&D_800A6518
 *      [*bidx*20], depth, 1)` as its literal call form (there depth=0x10
 *      constant, here depth=temp_v0_2).  Confirms the "3 lhu D_800B9A02,
 *      address cached / value reloaded" shape and the general addPrim(ot,p)
 *      == setaddr(p,getaddr(ot)); setaddr(ot,p) reading.
 *
 *   3. src/ov_SC03_119/ov_SC03_119_jr_8017FB84.c func_801860E8 (same TU,
 *      just above func_80185944) — its own header documents **Lever B**,
 *      byte-measured: "THE OT TABLE MUST BE AN ARRAY_REF (`D_800A651C[i].a`),
 *      NOT `*(s32*)((u8*)&D_800A651C + i*20)`. With the pointer-arith
 *      spelling gcc allocates a phantom 8-byte stack temp that is never
 *      referenced... The temp only appears when the SAME lookup expression
 *      occurs in two statements; the ARRAY_REF form kills it." This was the
 *      load-bearing fix for this draft too — confirmed empirically here via
 *      the `cpp|cc1 … | grep '.frame'` pipeline (§162i's own diagnostic
 *      method): pointer-arith form gave `vars=16` (0x38 frame, +8 over
 *      target's 0x30); switching every `D_800A651C` reference to
 *      `D_800A651C[idx].a` ARRAY_REF form (using the `OtBlk` shape from
 *      engine_types.h:525, local-suffixed here since match_one compiles
 *      standalone) dropped it straight to `vars=8` (0x30, exact). This
 *      generalizes §162i1's "only a BLKmode local reserves frame space" law
 *      to a second, distinct anonymous-temp source (a raw-pointer-arith
 *      symbol expression repeated in 2 statements) — worth a cookbook
 *      addendum since §162i1 as written only covers dead-local pads.
 *
 * REGISTER-ALLOCATION LEVERS (found empirically, byte-verified against this
 * function's own .frame/.s, not inherited from the exemplars above):
 *   - `bidx` pinned to $8 ($t0): natural (unpinned) allocation put the
 *     shared D_800B9A02-address pointer in $a3 instead, cascading a
 *     one-register shift through the whole mask/index register set.
 *   - `mask1` (0xFFFFFF) pinned to $7 ($a3); `tag0` (the packet's old tag
 *     word, read once before the first addPrim half) pinned to $4 ($a0) —
 *     both needed to reproduce the target's exact a2/a3/t0/t1 register
 *     picks for the addPrim RMW pair.  `mask2` (0xFF000000) and `depth4`
 *     (temp_v0_2*4) are explicitly NOT pinned — pinning them re-introduced a
 *     2-instruction schedule swap between the depth<<2 and the 0xFF000000
 *     `lui`; left as plain (named, for depth4) / literal (for mask2)
 *     locals, natural allocation lands them correctly.
 *   - `rgb` (arg2, the color word) pinned to $16 ($s0): unpinned, arg2 and
 *     the &D_800AF648 matrix address land in $s1/$s0 (swapped from target).
 *     `rgb`'s single SET made it a sched1 "birthing insn"
 *     (`birthing_insn_p`: `reg_n_sets==1`) — boosted to max priority in
 *     sched1's BACKWARD scan, which schedules a boosted insn late (cookbook
 *     "birthing-boost prologue-order" lever). A zero-byte non-volatile
 *     re-tie `__asm__("" : "=r"(rgb) : "0"(rgb));` placed immediately after
 *     `rgb = arg2;` gives it a 2nd SET (boost dead) with zero emitted code,
 *     and the 3-instruction prologue cluster (save $s0 / set $s0=arg2 / set
 *     $a0=0x10 for the alloc call) reorders to the target's exact sequence.
 *
 * INTEGRATION SURFACE (checked against destination TU
 * src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c):
 *   func_80010A08, func_8004914C, func_800491AC, RotTransPers, D_800AF648,
 *   D_800B9A02, D_800A6518 all match the TU's own existing extern spellings
 *   verbatim (grepped at TU lines 2448/2632-2633/4674 and the
 *   func_8018F694/func_8018F060 block). D_800A651C and func_80016638 have NO
 *   file-scope declaration anywhere in the TU (only ever appear inside other
 *   INCLUDE_ASM'd/unbanked functions) — declared here exactly as the
 *   func_801860E8/func_80185944 MATCHed precedent declares them: `OtBlk
 *   D_800A651C[]` (locally as `OtBlk_8018A974_801AADA8` — match_one compiles
 *   standalone without ../shared/engine_core.h; at bank time this collapses
 *   onto the TU's own already-visible `OtBlk` from engine_types.h:525,
 *   identical layout, a copy-edit not a fresh investigation) and
 *   `void func_80016638(void *a0, s32 a1, s32 a2)`.
 */

typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974_801AADA8;   /* == engine_types.h OtBlk (0x14) */

void func_801AADA8(s32 arg0, s32 arg1, s32 arg2)
{
    extern void *func_80010A08(s32);
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern s32 RotTransPers(s32, s32, s32 *, s32 *);
    extern u8 D_800AF648;
    extern OtBlk_8018A974_801AADA8 D_800A651C[];
    extern u8 D_800A6518[];
    extern short D_800B9A02;
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    s32 sp10;
    s32 sp14;
    s32 temp_v0_2;
    void *temp_v0;
    s32 ot;
    s32 depth4;
    u16 *bidx;
    u32 tag;

    temp_v0 = func_80010A08(0x10);
    *(s32 *)((u8 *)temp_v0 + 4) = arg2;
    *(u8 *)((u8 *)temp_v0 + 3) = 3;
    *(u8 *)((u8 *)temp_v0 + 7) = 0x42;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    temp_v0_2 = RotTransPers(arg0, temp_v0 + 8, &sp10, &sp14);
    if ((temp_v0_2 > 0) && (sp14 >= 0) &&
        (RotTransPers(arg1, temp_v0 + 0xC, &sp10, &sp14) > 0) && (sp14 >= 0)) {
        /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
        bidx = (u16 *)&D_800B9A02;
        depth4 = temp_v0_2 * 4;
        tag = *(u32 *)temp_v0;
        tag &= 0xFF000000;
        tag |= *(u32 *)(depth4 + D_800A651C[*bidx].a) & 0xFFFFFF;
        *(u32 *)temp_v0 = tag;
        ot = D_800A651C[*bidx].a;
        *(u32 *)(depth4 + ot) =
            (*(u32 *)(depth4 + ot) & 0xFF000000) | ((u32)temp_v0 & 0xFFFFFF);
        func_80016638(&D_800A6518[*bidx * 20], temp_v0_2, 1);
    }
}


extern s32 func_801AAF8C();

void func_801AAF34(s32 a0, s32 a1, s16 a2)
{
    s16 sv[3];

    sv[0] = *(u16 *)(a0 + 6) + *(u16 *)(a0 + 0x50);
    sv[1] = *(u16 *)(a0 + 0xA) + *(u16 *)(a0 + 0x52);
    sv[2] = *(u16 *)(a0 + 0xE) + *(u16 *)(a0 + 0x54);
    func_801AAF8C(sv, a1, a2);
}


#include "common.h"

/* 4x s16 vector (align 2 -> §48-C2 gives the lwl/lwr + swl/swr block copy) */
typedef struct { s16 vx, vy, vz, pad; } SV_801AAF8C;
/* PsyQ MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_801AAF8C;

extern s32  ratan2(s32 a0, s32 a1);
extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

extern s16  D_80126B5E;
extern s16  D_80126B62;
extern s16  D_80126B66;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];

s32 func_801AAF8C(SV_801AAF8C *src, SV_801AAF8C *ofs, s32 arg2)
{
    MTX_801AAF8C mtx;   /* sp+0x18 */
    SV_801AAF8C  rot;   /* sp+0x38 */
    SV_801AAF8C  pos;   /* sp+0x40 */
    SV_801AAF8C  sv;    /* sp+0x48 */
    s32          flag;  /* sp+0x50 */
    s32 dx, dy, dz;
    s32 ang;
    s32 s;
    s32 t;

    pos = *src;
    if (ofs != 0) {
        pos.vx += ofs->vx;
        pos.vy += ofs->vy;
        pos.vz += ofs->vz;
    }

    dz = D_80126B66 - pos.vz;
    dx = D_80126B5E - pos.vx;
    t  = pos.vy + 0x20;
    dy = D_80126B62 - t;

    ang = (ratan2(-dz, dx) - 0x400) & 0xFFF;
    rot.vy = ang;
    s = func_80047948(ang);
    dz = (dz * s + dx * func_8004787C(rot.vy)) >> 12;
    rot.vx = ratan2(dy, -dz);
    rot.vz = 0;
    func_80049CAC((s32)&rot, (s32)&mtx);

    func_8004914C(&mtx);
    mtx.t[0] = pos.vx;
    mtx.t[1] = pos.vy;
    mtx.t[2] = pos.vz;
    func_800491AC(&mtx);

    sv.vy = 0;
    sv.vx = 0;
    sv.vz = -arg2;
    RotTransSV((s32)&sv, (s32)&sv, &flag);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&pos, (s32)&sv) != 0) {
        func_8012F568(1, 1, 0, 0xA, (s32)&sv, (s32)D_801152A8);
        return 1;
    }
    return 0;
}



extern void func_801AB1A8();
    void func_801AB178(s32 *param) {
        if (*(u16 *)((char *)param + 0x2) == 0) {
            ((void (*)(void))func_801AB1A8)();
        }
    }


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012AD50(void *a0);

extern u8 D_801F7490[];

void func_801AB1A8(void *a0) {
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, (s32)&D_801F7490);
    *(u16 *)((s32)a0 + 0xE) = 0;
    *(u16 *)((s32)a0 + 0xA) = 0;
    *(u16 *)((s32)a0 + 6) = 0;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x28) = 0x1000100;
    func_8012AD50(a0);
}


#include "common.h"

/* == engine_types.h OtBlk (0x14); at bank time delete this typedef and use the
 * TU's existing OtBlk_8018A974_801AADA8 (src/md_SC07_004/md_SC07_004.c:766) */


/* 0x18-byte POLY_F4 */
typedef struct {
    u8  addr[3];
    u8  len;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} F4_801AB21C;

void func_801AB21C(s32 a0, s32 a1, s32 a2, s32 a3)
{
    extern void *func_80010A08(s32);
    extern void func_80016638(void *a0, s32 a1, s32 a2);
    extern u16 D_800B9A02;
    extern OtBlk_8018A974_801AADA8 D_800A651C[];
    extern u8 D_800A6518[];
    extern OtBlk_8018A974_801AADA8 D_800AE7BC[];
    extern u8 D_800AE7B8[];

    F4_801AB21C *p;
    u32 *ot;
    s32 idx;

    p = (F4_801AB21C *)func_80010A08(0x18);

    p->len = 5;
    p->code = 0x2A;
    p->r0 = a1;
    p->g0 = a2;
    p->b0 = a3;
    p->x0 = p->x2 = -160;
    p->x1 = p->x3 = 160;
    p->y0 = p->y1 = -120;
    p->y2 = p->y3 = 120;
    idx = a0 & 0xFFFF;
    if (idx != 0) {
        s32 i4 = idx * 4;
        u32 tag;
        /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
        tag = *(u32 *)p;
        tag &= 0xFF000000;
        tag |= *(u32 *)(i4 + D_800A651C[D_800B9A02].a) & 0xFFFFFF;
        *(u32 *)p = tag;
        i4 += D_800A651C[D_800B9A02].a;
        *(u32 *)i4 = (*(u32 *)i4 & 0xFF000000) | ((u32)p & 0xFFFFFF);
        func_80016638(&D_800A6518[D_800B9A02 * 20], idx, 1);
    } else {
        u32 tag;
        tag = *(u32 *)p;
        tag &= 0xFF000000;
        tag |= *(u32 *)D_800AE7BC[D_800B9A02].a & 0xFFFFFF;
        *(u32 *)p = tag;
        ot = (u32 *)D_800AE7BC[D_800B9A02].a;
        *ot = (*ot & 0xFF000000) | ((u32)p & 0xFFFFFF);
        func_80016638(&D_800AE7B8[D_800B9A02 * 20], 0, 1);
    }
}


#include "common.h"

/* §160a: lwl/lwr + swl/swr == emit_block_move on an ALIGN-1 4-byte struct. */


extern Blk4_801A7358 *D_801B0358[];
extern Blk4_801A7358 D_801F88F8;
extern u8 D_801F88F9;
extern u8 D_801F88FA;

extern void func_8012AD80(s32 a0);
extern void func_801A7808();
extern s32 func_8012BEE8(s32 a0);
extern void func_8012AD50(void *a0);

void func_801AB41C(void *arg0)
{
    s16 idx;
    s32 flag;
    Blk4_801A7358 *a2;
    u8 *src;
    void *v1;

    idx = *(s16 *)((u8 *)arg0 + 0x70);
    a2 = D_801B0358[idx];
    flag = *(s32 *)((u8 *)arg0 + 0x1C) & 1;
    if (flag != 0) {
        D_801F88F8 = a2[1];
    } else {
        src = (u8 *)a2;
        *(u8 *)&D_801F88F8 = src[4] >> 1;
        D_801F88F9 = src[5] >> 1;
        D_801F88FA = src[6] >> 1;
    }

    func_8012AD80((s32)arg0);
    func_801A7808(arg0, *(void **)((u8 *)arg0 + 0xCC));
    func_801A7808(arg0, *(void **)((u8 *)arg0 + 0xD0));
    func_801A7808(arg0, *(void **)((u8 *)arg0 + 0xD4));

    v1 = *(void **)((u8 *)arg0 + 0xD8);
    if (v1 != NULL) {
        *(u16 *)((u8 *)v1 + 0x6) = *(u16 *)((u8 *)arg0 + 0x6);
        *(u16 *)((u8 *)v1 + 0xA) = *(u16 *)((u8 *)arg0 + 0xA);
        *(u16 *)((u8 *)v1 + 0xE) = *(u16 *)((u8 *)arg0 + 0xE);
    }

    if (func_8012BEE8((s32)arg0) != 0) {
        *(u16 *)((u8 *)arg0 + 0x102) = 0;
        *(u16 *)((u8 *)arg0 + 0x100) = 0;
        *(u16 *)((u8 *)arg0 + 0xFE) = 0;
        *(s32 *)((u8 *)arg0 + 0x1C) = 4;
        func_8012AD50(arg0);
    }
}


void func_801AB54C(void *a0) {
    func_801A8494(a0);

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        return;
    }

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) < 0x600) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += 0x100;
    }

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) < 0xA00) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) += 0x140;
    }
}


extern u8 D_801F88C8[];
extern u8 D_801F8A38[];
extern u8 D_801F8A3A[];
extern void func_80016450(s32 a0, s32 a1);
extern void func_801A7CC8(void *a0);

void func_801AB5D4(void *arg0) {
    void *s0;
    register u8 *a1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
    s32 a2;

    s0 = arg0;
    if (*(s32 *)((u8 *)s0 + 0x1C) < 5) {
        {
            s32 a0;
            a2 = 0;
            a1 = D_801F88C8;
            do {
                a0 = (a2 >> 1) << 2;
                *(u16 *)(a1 + 0) += *(u16 *)(D_801F8A38 + a0);
                *(u16 *)(a1 + 2) += *(u16 *)(D_801F8A3A + a0);
                a2 += 2;
                a1 += 8;
            } while (a2 < 0xC);
        }

        {
            s32 v0;
            v0 = *(u16 *)((u8 *)s0 + 0x2C);
            v0 += 0x10;
            *(u16 *)((u8 *)s0 + 0x2C) = v0;
            func_80016450(v0 & 0xFF, 1);
        }
    }

    {
        s32 v0;
        v0 = *(s32 *)((u8 *)s0 + 0x1C);
        v0 -= 1;
        *(s32 *)((u8 *)s0 + 0x1C) = v0;
        if (v0 == 0) {
            func_801A7CC8(s0);
        }
    }
}


extern u8 D_801F88C8[];
extern u8 D_801F8A38[];
extern u8 D_801F8A3A[];
extern void func_80016450(s32 a0, s32 a1);

void func_801AB694(void *arg0) {
    void *s0;
    register u8 *a1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
    s32 a2;

    s0 = arg0;
    {
        s32 a0;
        a2 = 0;
        a1 = D_801F88C8;
        do {
            a0 = (a2 >> 1) << 2;
            *(u16 *)(a1 + 0) -= *(u16 *)(D_801F8A38 + a0);
            *(u16 *)(a1 + 2) -= *(u16 *)(D_801F8A3A + a0);
            a2 += 2;
            a1 += 8;
        } while (a2 < 0xC);
    }

    {
        s32 a0;
        a0 = *(u16 *)((u8 *)s0 + 0x2C);
        a0 -= 0x10;
        *(u16 *)((u8 *)s0 + 0x2C) = a0;
        func_80016450(a0 & 0xFF, 1);
    }

    {
        s32 v0;
        v0 = *(s32 *)((u8 *)s0 + 0x1C);
        v0 -= 1;
        *(s32 *)((u8 *)s0 + 0x1C) = v0;
        if (v0 == 0) {
            *(u16 *)((u8 *)s0 + 2) = 1;
            *(u16 *)((u8 *)s0 + 0x2A) = 0;
        }
    }
}


void func_801AB748(s32 a0) {
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(a0 + 0x1C);
    if (v0 != 0) {
        v0 = v0 - 1;
        *(s32 *)(a0 + 0x1C) = v0;
    } else {
        v1 = *(s32 *)(a0 + 0x20);
        *(s16 *)(v1 + 0x1A) = 0x400;
        *(s16 *)(v1 + 0x18) = 0x400;
        v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = 0xC020;
        *(s16 *)(a0 + 2) = 1;
    }
}


extern void func_801292C8(u8 *a0);
extern u8 D_801F88BA;

void func_801AB78C(void *a0) {
    volatile u8 *p = &D_801F88BA;
    u8 b;
    s16 t;
    if (*p == 0) {
        func_801292C8((u8 *)a0);
    } else {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += 0x200;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        b = *p;
        if (b != 0) {
            t = b - 0x10;
            b = t;
            if (t < 0) {
                b = 0;
            }
            *p = b;
        }
    }
}


#include "common.h"

extern void func_801A8440(s32 a0);
extern void func_801292C8(u8 *a0);

/* helper view used only to force gcc's unaligned SImode store idiom
 * (lwl/lwr + swl/swr) when writing back through *(a0+0x24) — see
 * cookbook §48-C2 / §160a: a struct type with alignment < 4 takes the
 * unaligned-move path even between provably 4-aligned slots.
 * Named uniquely: this TU already defines U16x2 / U16x2L. */
typedef struct {
    u16 a, b;
} U16x2N;

void func_801AB818(void *a0) {
    u8 *s1 = *(u8 **)((s32)a0 + 0x24);

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        U16x2N tmp;

        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_801A8440((s32)a0);

        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) -= 0x370;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);

        /* tmp is stored twice and the target keeps both stores: the addend read between them resets flow.c's
         * last_mem_set; as ((s32 *)a0)[12] it is an in-struct access, which sched1 hoists above the frame store. */
        *(s32 *)&tmp = *(s32 *)(s1 + 0);
        *(s32 *)&tmp += ((s32 *)a0)[12];
        *(U16x2N *)(s1 + 0) = tmp;
    } else {
        func_801292C8((u8 *)a0);
    }
}


#include "common.h"

typedef struct { char c[4]; } Blk4_801AB8C0;

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_800233CC(void *a0, unsigned short a1);
extern s32 func_8001CA88(s32 a0, void *a1);
extern void func_801A881C(s32 a0);

extern u8 D_801F8978[3];
extern Blk4_801AB8C0 D_801F897C;
extern Blk4_801A7358 D_801A01E8;
extern u8 D_801A0214;

/* §8 rodata island: D_801A0214 (0x00800000) lives only in this function's
 * migrated .s and has no INCLUDE_RODATA line in the TU; while the function
 * was INCLUDE_ASM the island rode in on the stub. Re-emit it here so the
 * banked C does not drop the symbol from the link. */
__asm__(".section .rodata\nD_801A0214:\n.word 0x00800000\n.section .text");  // !FAKE: instruction .section — REFUSED asm-data: a `.section` block defines data as assembly (a rodata carve, not a compiler steer) — T7 (P36 rung B tus11)

void func_801AB8C0(s32 s1)
{
    s32 a0;
    s32 a1;
    s32 v1;
    u8 *s0;

    if ((*(s32 *)(s1 + 0x20) = func_8012C1B8()) == 0) {
        func_8012CAE4((void *)s1);
        return;
    }

    if (*(s16 *)(s1 + 0x70) == 0) {
        s0 = D_801F8978;
        func_800233CC(s0, 0x30);
        *(Blk4_801AB8C0 *)s0 = *(Blk4_801AB8C0 *)&D_801A0214;
        D_801F897C = (*(Blk4_801AB8C0 *)&D_801A01E8);
    }

    func_8001CA88(*(s32 *)(s1 + 0x20), D_801F8978);

    a0 = s1;
    a1 = *(s32 *)(a0 + 0x20);
    *(s32 *)(a1 + 4) |= 0x50000000;
    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(v1 + 0x1A) = 0x200;
    *(s16 *)(v1 + 0x18) = 0x200;
    func_801A881C(a0);
}


extern u16 D_8019FF8A;
extern void func_801A8884(s32 *a0);
extern void func_801A88AC();
extern void func_801A8990();

void func_801AB9AC(s32 arg0) {
    s32 v1;

    v1 = D_8019FF8A;
    if (!(v1 & 1)) {
        func_801A8884(arg0);
    } else if (v1 & 0x400) {
        func_801A88AC(arg0);
    }

    *(u16 *)(arg0 + 0x104) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 6);
    *(u16 *)(arg0 + 0x106) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 0xA);
    *(u16 *)(arg0 + 0x108) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 0xE);
    func_801A8990(arg0);

    if (*(s16 *)(arg0 + 0xFE) < 0x28) {
        *(s16 *)(arg0 + 0xFE) = *(s16 *)(arg0 + 0xFE) + 2;
    }
    *(u16 *)(arg0 + 0x100) += 0x28;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) += *(u16 *)(arg0 + 0x102);
}


extern void func_801A8990();
extern s32 func_8012BEE8(s32 a0);
extern void func_8017E5D4(void *a0);
extern void func_8012C218(void *a0);

void func_801ABA74(s32 arg0) {
    s32 v0;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        *(u16 *)(arg0 + 0xFE) += 0x14;
        *(u16 *)(arg0 + 0x104) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 6);
        *(u16 *)(arg0 + 0x106) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 0xA);
        *(u16 *)(arg0 + 0x108) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 0xE);
        func_801A8990(arg0);
        if (func_8012BEE8(arg0) != 0) {
            *(u16 *)(arg0 + 0x34) += 1;
        }
        break;
    case 1:
        v0 = *(u16 *)(arg0 + 0xFE) - 8;
        *(u16 *)(arg0 + 0xFE) = v0;
        if ((s16)v0 < 8) {
            if (*(s32 *)(arg0 + 0xCC) != 0) {
                func_8017E5D4(*(void **)(arg0 + 0xCC));
            }
            func_8012C218((void *)arg0);
            return;
        } else {
            *(u16 *)(arg0 + 0x104) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 6);
            *(u16 *)(arg0 + 0x106) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 0xA);
            *(u16 *)(arg0 + 0x108) = *(u16 *)(*(s32 *)(arg0 + 0x64) + 0xE);
            func_801A8990(arg0);
        }
        break;
    }
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) += *(u16 *)(arg0 + 0x102);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8017E5D4(void *a0);
extern void func_8012C218(void *a0);
extern void func_8012AD80(s32 a0);

void func_801ABBA4(void *arg0) {
    if (func_8012BEE8((s32)arg0) != 0) {
        if (*(void **)((u8 *)arg0 + 0xCC) != NULL) {
            func_8017E5D4(*(void **)((u8 *)arg0 + 0xCC));
        }
        func_8012C218(arg0);
    } else {
        func_8012AD80(arg0);
    }
}


#include "common.h"

extern u8 D_801B03F4[];
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern int rand(void);

void func_801ABC04(void *a0) {
    s32 t;
    u16 h;

    func_8001CC3C(*(s32 *)((s32)a0 + 0x20), (s32)D_801B03F4, 0x2F8, 0x1C0);

    *(u32 *)(*(s32 *)((s32)a0 + 0x20) + 4) |= 0x58000000;

    h = (rand() & 0xF8) | 0x200;
    t = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(t + 0x1A) = h;
    *(u16 *)(t + 0x18) = h;

    *(u8 *)(*(s32 *)((s32)a0 + 0x20) + 0x27) = 0x55;

    *(u16 *)((s32)a0 + 2) += 1;
}


#include "common.h"

void func_801ABC8C(void *a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);
    extern void func_801A8B64(s32 a0, s32 a1);

    u16 local[3];

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        (*(s32 *)((s32)a0 + 0x1C))--;
        local[0] = *(u16 *)((s32)a0 + 0x6);
        local[1] = *(u16 *)((s32)a0 + 0xA);
        local[2] = *(u16 *)((s32)a0 + 0xE);

        if (*(s16 *)((s32)a0 + 0x2C) == 0) {
            func_8012931C((struct vec *)a0);
        } else {
            void *s1 = *(void **)((s32)a0 + 0x34);

            *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x2E);
            *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)a0 + 0x30);
            *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)a0 + 0x32);
            func_8012931C((struct vec *)a0);

            *(u16 *)((s32)a0 + 0x2E) = *(u16 *)((s32)a0 + 0x6);
            *(u16 *)((s32)a0 + 0x30) = *(u16 *)((s32)a0 + 0xA);
            *(u16 *)((s32)a0 + 0x32) = *(u16 *)((s32)a0 + 0xE);

            if (s1 != 0) {
                *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x6) + *(u16 *)((s32)s1 + 0x6);
                *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)a0 + 0xA) + *(u16 *)((s32)s1 + 0xA);
                *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)a0 + 0xE) + *(u16 *)((s32)s1 + 0xE);
            }
        }

        func_801A8B64((s32)a0, (s32)local);
    } else {
        func_801292C8((u8 *)a0);
    }
}


#include "common.h"

extern s32 func_8001D074(s32 a0, s32 a1);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_801A90D8();
extern void func_801A930C();

extern u8 D_801B0408[];
extern u8 D_801B0414[];

void func_801ABDA4(void *a0) {
    s32 s0;
    s32 q;
    s32 v1;
    u16 v2;

    s0 = func_8001D074(0x7E, 0x100);
    *(s32 *)((s32)a0 + 0xCC) = s0;
    q = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = q;
    if (q == 0 || s0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C2C4(q);

    func_8001CC3C(s0, (s32)D_801B0408, 0x340, 0x100);
    *(s8 *)(s0 + 0x27) = 0x59;
    *(s16 *)(s0 + 0x18) = 0x3000;
    *(s16 *)(s0 + 0x1A) = 0x3000;
    v2 = 0xC018;
    *(s16 *)(s0 + 0x2C) = v2;
    *(s32 *)(s0 + 0x4) |= 0x50000000;

    func_80128EA8(*(s32 *)((s32)a0 + 0xCC), (s32)a0 + 0xF0, (s32)D_801B0414);

    if (*(s16 *)((s32)a0 + 0x70) == 0) {
        v1 = func_80143994(a0, 1);
        *(s32 *)((s32)a0 + 0xD0) = v1;
        if (v1 != 0) {
            s0 = *(s32 *)(v1 + 0xCC);
            if (s0 != 0) {
                *(s16 *)(s0 + 0x2C) = v2;
            }
        }
        func_801A90D8((s32)a0);
    } else {
        s32 t1;
        t1 = *(u16 *)((s32)a0 + 0x6) + 0x20;
        *(u16 *)((s32)a0 + 0x6) = t1;
        *(u16 *)(s0 + 0x8) = t1;
        t1 = *(u16 *)((s32)a0 + 0xA);
        *(u16 *)(s0 + 0xA) = t1;
        t1 = *(u16 *)((s32)a0 + 0xE);
        *(u16 *)(s0 + 0xC) = t1;
        func_801A930C(a0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801A9270(void *a0);
extern void func_801A9378(void *a0);
extern void func_801A93F4(void *a0);
extern void func_801AA60C();

void func_801ABEE0(void *a0) {
    s32 r0 = (s32)a0;
    s32 ptr1;
    s32 s2;
    s16 v1;
    s32 val;
    s16 orig;
    s16 dec;

    ptr1 = *(s32 *)(r0 + 0xCC);
    s2 = *(s32 *)(r0 + 0xD0);
    func_8012AD80(r0);
    *(s16 *)(ptr1 + 0x8) = *(u16 *)(r0 + 0x6);
    *(s16 *)(ptr1 + 0xA) = *(u16 *)(r0 + 0xA);
    *(s16 *)(ptr1 + 0xC) = *(u16 *)(r0 + 0xE);
    v1 = *(s16 *)(r0 + 0xA);
    if (v1 >= -0x200) {
        *(s16 *)(r0 + 0xA) = -0x200;
        func_801A9270((void *)r0);
    } else {
        if (s2 != 0) {
            ptr1 = *(s32 *)(s2 + 0xCC);
            if (ptr1 != 0) {
                val = (v1 + 0x500) << 4;
                *(s16 *)(ptr1 + 0x1A) = val;
                *(s16 *)(ptr1 + 0x18) = val;
            }
        }
        *(s32 *)(r0 + 0x1C) += 1;
        if ((*(s32 *)(r0 + 0x1C) & 1) == 0) {
            func_801A93F4((void *)r0);
        }
    }
    func_80128ED8(*(s32 *)(r0 + 0xCC), (s32 *)(r0 + 0xF0));
    func_801A9378((void *)r0);
    orig = *(s16 *)(r0 + 0x84);
    if (orig != 0) {
        dec = orig - 1;
        *(s16 *)(r0 + 0x84) = dec;
        if (dec == 0) {
            func_801AA60C((void *)r0, 0xAB8);
        }
    }
}


extern s32 func_80128ED8(s32 a0, s32 *a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_801A9454(s32, s32);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_801A9378(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s16 D_801F8E98;

void func_801ABFF8(void *arg0) {
    s32 s1;
    s16 val;

    s1 = *(s32 *)((char *)arg0 + 0xCC);
    func_80128ED8(s1, (s32 *)((char *)arg0 + 0xF0));

    val = *(s16 *)((char *)s1 + 0x1A);
    if (val >= 0x1801) {
        *(s16 *)((char *)s1 + 0x1A) = val - 0x400;
    }

    if (func_8012BEE8((s32)arg0) != 0) {
        ((void (*)(s32, s32))func_801A9454)((s32)arg0, 0x10);
        func_80016714(*(void **)((char *)arg0 + 0xCC), 0x38);
        func_8012C218(arg0);
        if (--D_801F8E98 == 0) {
            func_8002D4C8(4, 0xABD);
        }
    } else {
        if ((*(s32 *)((char *)arg0 + 0x1C) & 7) == 0) {
            ((void (*)(s32, s32))func_801A9454)((s32)arg0, 0);
        }
        func_801A9378(arg0);
    }
}


#include "common.h"

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_8012BEE8(s32 a0);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801AC0D4(void *arg0) {
    void *s0;
    s16 val;

    s0 = *(void **)((char *)arg0 + 0xCC);
    func_80128ED8((s32)s0, (s32 *)((char *)arg0 + 0xF0));

    val = *(s16 *)((char *)s0 + 0x1A);
    if (val >= 0x1801) {
        *(s16 *)((char *)s0 + 0x1A) = val - 0x400;
    }

    if (func_8012BEE8((s32)arg0) != 0) {
        func_80016714(*(void **)((char *)arg0 + 0xCC), 0x38);
        func_8012C218(arg0);
    }
}


extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 D_801B05F0[];
extern u8 D_801B04A4[];

void func_801AC150(void *a0) {
    s32 s0;
    s32 v1;
    u16 v2;

    s0 = D_801B05F0[*(s16 *)((s32)a0 + 0x2C)];
    func_8001CC3C(*(s32 *)((s32)a0 + 0x20), (s32)D_801B04A4, *(s16 *)s0, *(s16 *)(s0 + 2));
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s8 *)(v1 + 0x27) = 0x5A;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = 0x3000;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = 0x3000;
    v2 = 0xC018;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) = v2;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x50000000;
    func_80128EA8(*(s32 *)((s32)a0 + 0x20), (s32)a0 + 0x24, s0);
    if (*(s16 *)((s32)a0 + 0x2C) == 2) {
        *(s32 *)((s32)a0 + 0x14) = -0x80000;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = 0x5000;
    }
    (*(u16 *)((s32)a0 + 0x2))++;
}


extern s32 func_80128ED8(s32 a0, s32 *a1);

void func_801AC234(void *a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);

    func_8012931C((struct vec *)a0);
    if (func_80128ED8(*(s32 *)((char *)a0 + 0x20), (s32 *)((char *)a0 + 0x24)) != 0 ||
        (*(s16 *)((char *)a0 + 0x2C) != 2 && *(s16 *)((char *)a0 + 0xA) >= -0x200)) {
        func_801292C8((u8 *)a0);
    }
}


#include "common.h"

extern s32 func_8001D074(s32 a0, s32 a1);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_801A94A0();

extern u8 D_801B0610[];

void func_801AC29C(void *a0) {
    void *s1;
    s32 s0;
    s32 v0;
    u16 v1;

    s1 = a0;
    s0 = func_8001D074(0x7E, 0x100);
    *(s32 *)((s32)s1 + 0xCC) = s0;
    v0 = func_8012C1B8();
    *(s32 *)((s32)s1 + 0x20) = v0;
    if (v0 == 0 || s0 == 0) {
        func_8012CAE4(s1);
        return;
    }
    func_8001C2C4(v0);

    func_8001CC3C(s0, (s32)D_801B0610, 0x300, 0x100);
    *(s8 *)(s0 + 0x27) = 0x64;
    *(s16 *)(s0 + 0x8) = *(u16 *)((s32)s1 + 0x6);
    *(s16 *)(s0 + 0xA) = *(u16 *)((s32)s1 + 0xA);
    *(s16 *)(s0 + 0xC) = *(u16 *)((s32)s1 + 0xE);
    *(u16 *)(s0 + 0x2C) = 0xC040;
    *(s32 *)(s0 + 0x4) |= 0x50000000;

    if (!(*(u16 *)((s32)s1 + 0x70) & 0x100)) {
        v1 = 1;
        *(s16 *)((s32)s1 + 0xFE) = v1;
    } else {
        *(s16 *)(s0 + 0x18) = 0x1800;
        *(s16 *)(s0 + 0x1A) = 0x5000;
        v1 = 0x3000;
        *(s16 *)((s32)s1 + 0xFE) = 0;
    }

    {
        void *ra0 = s1;
        *(u16 *)((s32)s1 + 0x70) = *(u8 *)((s32)s1 + 0x70);
        v0 = ((s32 (*)(s32, s32))func_80143994)((s32)ra0, v1);
    }
    *(s32 *)((s32)s1 + 0xD0) = v0;
    if (v0 != 0) {
        s0 = *(s32 *)(v0 + 0xCC);
        if (s0 != 0) {
            *(u16 *)(s0 + 0x2C) = 0xC030;
        }
    }
    func_801A94A0(s1);
}


#include "common.h"

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801A9908(void *a0, s32 a1);
extern void func_801A9954(void *a0);
extern u16 D_801B070C[];

void func_801AC3C8(void *a0) {
    void *s1;
    s16 t;

    s1 = *(void **)((s32)a0 + 0xCC);
    if (func_80128ED8((s32)s1, (s32 *)((s32)a0 + 0xF0)) != 0) {
        func_801A9954(a0);
        return;
    }

    *(u8 *)((s32)s1 + 0x27) = (u8)D_801B070C[*(s16 *)((s32)a0 + 0xF4)];

    t = *(s16 *)((s32)a0 + 0xF4) * 14 + 0x30;
    if (*(s16 *)((s32)a0 + 0xFE) == 0) {
        t = t >> 1;
    }
    func_801A9908(a0, t);
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(void *a0, s32 a1);
extern void func_801A9B40(void*, u16, u16);
extern void func_8012AD50(void *a0);

extern u8 D_801F0688;
extern u8 D_801F8A58;

void func_801AC47C(void *a0) {
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, (s32)&D_801F0688);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = 0x3000;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = 0x4000;
    *(s16 *)((s32)a0 + 0xA) = -0x40;
    *(s16 *)((s32)a0 + 0x6) = 0;
    *(s16 *)((s32)a0 + 0xE) = 0x28;
    func_8001C1E4(*(void **)((s32)a0 + 0x20),
                  *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20));
    ((void (*)(void *, s32, s32))func_801A9B40)(&D_801F8A58, 0x160, 0x157);
    *(s32 *)((s32)a0 + 0x1C) = 8;
    func_8012AD50(a0);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_801A9B80(s32 *a0, u16 a1, u16 a2);
extern u8 D_801F8A58;

void func_801AC54C(s32 param_1) {
    if (func_8012BEE8(param_1) != 0) {
        func_8012C218((void *)param_1);
    } else {
        func_801A9B80(&D_801F8A58, 0x160, 0x157);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8017E5D4(void *a0);
extern void func_8017E1E8(void *a0, void *a1, void *a2);
extern void func_8012AD80(s32 a0);
extern void func_801AA004(void *a0, void *a1);
extern void func_801AA210(void *a0, void *a1, void *a2);
extern void func_801AA4A8(void *a0, void *a1);

void func_801AC59C(void *arg0) {
    void *s2;
    s8 sp10[0x20];
    s8 sp30[0x18];

    s2 = *(void **)((u8 *)arg0 + 0x20);
    if (func_8012BEE8((s32)arg0) != 0) {
        if (*(void **)((u8 *)arg0 + 0xCC) != NULL) {
            func_8017E5D4(*(void **)((u8 *)arg0 + 0xCC));
        }
        if (*(void **)((u8 *)arg0 + 0xD0) != NULL) {
            func_8017E5D4(*(void **)((u8 *)arg0 + 0xD0));
        }
        func_8012C218(arg0);
    } else {
        s16 v0;
        s16 v1;

        v0 = *(s16 *)((u8 *)s2 + 0x18);
        v1 = v0;
        if (v0 < 0x1800) {
            v1 += 0x100;
            *(s16 *)((u8 *)s2 + 0x18) = v1;
            *(u16 *)((u8 *)s2 + 0x1A) += 0x40;
        }
        func_801AA004(arg0, sp10);
        func_801AA210(arg0, sp10, sp30);
        if (*(void **)((u8 *)arg0 + 0xCC) != NULL) {
            func_8017E1E8(*(void **)((u8 *)arg0 + 0xCC), sp30, sp30 + 8);
        }
        if (*(void **)((u8 *)arg0 + 0xD0) != NULL) {
            func_8017E1E8(*(void **)((u8 *)arg0 + 0xD0), sp30, sp30 + 0x10);
        }
        *(u16 *)((u8 *)s2 + 0x14) += *(u16 *)((u8 *)arg0 + 0xFE);
        func_8012AD80((s32)arg0);
        func_801AA4A8(arg0, sp30);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_8012B8A4(s16 *a0);
extern void func_801AA0B4(void *a0);
extern void func_801AA160(s32 arg0, s32 arg1);
extern void func_801AA3CC(s32 arg0);
extern void func_8012AD80(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern u16 D_800B99DA;

void func_801AC6C0(s32 arg0) {
    s32 s0;
    s32 s1;

    s0 = arg0;
    s1 = (*(s16 *)((s8 *)s0 + 6)) * (*(s16 *)((s8 *)s0 + 6))
       + (*(s16 *)((s8 *)s0 + 0xE)) * (*(s16 *)((s8 *)s0 + 0xE));
    if (func_8012BEE8(s0) != 0 || s1 > 0x100000) {
        func_8012C218((void *)s0);
    } else {
        func_801A3624((s32)(s16)func_8012B8A4((s16 *)s0),
                      (u16 *)(*(s32 *)((s8 *)s0 + 0x20) + 0x12), 0x10);
        func_801AA0B4(s0);
        func_801AA160(s0, D_800B99DA & 1);
        func_801AA3CC(s0);
        func_8012AD80(s0);
        func_8012C658(0xD, 3, s0);
    }
}


#include "common.h"

extern void func_8012C218(void *a0);
extern void func_801AA540(void *arg0);

void func_801AC794(void *arg0) {
    switch (*(u16 *)((u8 *)arg0 + 0x34)) {
    case 0:
        *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18) += 0x800;
        *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x1C) = *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18);
        *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x1A) = *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18)
            + ((s16)*(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18) >> 1);
        if (*(s16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18) >= 0x2400) {
            *(u16 *)((u8 *)arg0 + 0x34) += 1;
        }
        break;
    case 1:
        *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18) -= 0x400;
        {
            s16 tmp = *(s16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18);
            if (tmp > 0) {
                *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x1C) = tmp;
                *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x1A) = *(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18)
                    + ((s16)*(u16 *)(*(u32 *)((u8 *)arg0 + 0x20) + 0x18) >> 1);
            } else {
                func_8012C218(arg0);
                return;
            }
        }
        break;
    }
    func_801AA540(arg0);
}




extern void func_8001CD9C(s32, s32);
extern int rand(void);
extern Blk4_801A7358 D_801F88B8;

void func_801AC8B8(s32 param_1)
{
    s32 t;
    s32 ptr;

    *(u16 *)(param_1 + 0x2C) = 0;
    func_8001CD9C(*(s32 *)(param_1 + 0x20), (s32)&D_801F88B8);
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) = 0xC020;
    t = (rand() & 0x1F0) + 0x500;
    ptr = *(s32 *)(param_1 + 0x20);
    *(u16 *)(ptr + 0x1A) = t;
    *(u16 *)(ptr + 0x18) = t;
    *(s32 *)(param_1 + 0x1C) = 0x14;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}



extern Blk4_801A7358 D_801F88B8;

void func_801AC940(s32 arg0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);

    s32 a1 = arg0;
    s32 v0;
    s16 v1;

    v0 = *(s32 *)(a1 + 0x1C);
    if (v0 == 0) {
        func_801292C8((u8 *)a1);
        return;
    }
    v0 = v0 - 1;
    *(s32 *)(a1 + 0x1C) = v0;
    if ((v0 & 3) == 0 && *(s16 *)(a1 + 0x2C) < 3) {
        v1 = *(s16 *)(a1 + 0x2C);
        v1 = v1 + 1;
        *(s16 *)(a1 + 0x2C) = v1;
        *(s32 *)(*(s32 *)(a1 + 0x20) + 0x20) = (s32)&D_801F88B8 + (v1 << 6);
    }
    func_8012931C((struct vec *)a1);
}


extern void func_80016714(void *a0, s32 a1);
extern s32 func_8017D7D4(void *a0, void *a1, void *a2, s32 a3);

void func_801AC9CC(void *arg0) {
    void *temp_a0;
    s16 sp10[4];
    s16 a3;
    s32 v1;

    temp_a0 = *(void **)((u8 *)arg0 + 0x20);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
        *(void **)((u8 *)arg0 + 0x20) = NULL;
    }
    sp10[0] = *(u16 *)((u8 *)arg0 + 0x6);
    sp10[1] = *(u16 *)((u8 *)arg0 + 0xA);
    sp10[2] = *(u16 *)((u8 *)arg0 + 0xE);
    a3 = *(s16 *)((u8 *)arg0 + 0x30);
    if (a3 == 0) {
        a3 = 6;
    }
    *(s32 *)((u8 *)arg0 + 0x2C) = func_8017D7D4(sp10, NULL, (u8 *)arg0 + 0x34, (s8)a3);
    v1 = *(s16 *)((u8 *)arg0 + 0x32);
    if (v1 == 0) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 0x10;
    } else {
        *(s32 *)((u8 *)arg0 + 0x1C) = v1;
    }
    *(u16 *)((u8 *)arg0 + 0x2) += 1;
}


void func_801ACA88(void *a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);
    extern void func_8017E5D4(void *a0);
    extern void func_8017E1E8(void *a0, void *a1, void *a2);

    s16 buf[4];
    s32 v0;

    v0 = *(s32 *)((s32)a0 + 0x1C);
    if (v0 == 0) {
        if (*(void **)((s32)a0 + 0x2C) != NULL) {
            func_8017E5D4(*(void **)((s32)a0 + 0x2C));
        }
        func_801292C8((u8 *)a0);
    } else {
        *(s32 *)((s32)a0 + 0x1C) = v0 - 1;
        func_8012931C((struct vec *)a0);

        buf[0] = *(u16 *)((s32)a0 + 0x6);
        buf[1] = *(u16 *)((s32)a0 + 0xA);
        buf[2] = *(u16 *)((s32)a0 + 0xE);

        if (*(void **)((s32)a0 + 0x2C) != NULL) {
            func_8017E1E8(*(void **)((s32)a0 + 0x2C), &buf[0], NULL);
        }
    }
}


#include "common.h"

void func_801ACB2C(void *a0)
{
    extern void func_801AA7E4(u8 *a0);
    extern s32 func_8017D858(void *a0, void *a1, void *a2, s8 a3);

    s16 buf[8];
    s32 t0, t1, t2;
    s32 v0;
    s16 param3;

    func_801AA7E4((u8 *)a0);

    buf[0] = t0 = *(u16 *)((s32)a0 + 0x6);
    buf[1] = t1 = *(u16 *)((s32)a0 + 0xA);
    buf[2] = t2 = *(u16 *)((s32)a0 + 0xE);

    t0 += *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2E);
    buf[4] = t0;
    t1 += *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x30);
    buf[5] = t1;
    t2 += *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x32);
    buf[6] = t2;

    param3 = *(s16 *)((s32)a0 + 0x30);
    if (*(s16 *)((s32)a0 + 0x30) == 0)
        param3 = 6;

    if (*(s16 *)((s32)a0 + 0x32) == 0) {
        buf[3] = 0;
        *(s32 *)((s32)a0 + 0x1C) = 0x10;
    } else {
        buf[3] = -0x3F00;
        *(s32 *)((s32)a0 + 0x1C) = 0x18;
    }

    v0 = func_8017D858(&buf[0], &buf[4], (void *)((s32)a0 + 0x34), (s8)param3);
    *(s32 *)((s32)a0 + 0x2C) = v0;

    *(u16 *)((s32)a0 + 0x2) += 1;
}


void func_801ACC24(void *a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);
    extern void func_8017E5D4(void *a0);
    extern void func_8017E1E8(void *a0, void *a1, void *a2);

    s16 buf[8];
    s32 t0, t1, t2;
    s32 v0;

    v0 = *(s32 *)((s32)a0 + 0x1C);
    if (v0 == 0) {
        if (*(void **)((s32)a0 + 0x2C) != NULL) {
            func_8017E5D4(*(void **)((s32)a0 + 0x2C));
        }
        func_801292C8((u8 *)a0);
        return;
    }

    *(s32 *)((s32)a0 + 0x1C) = v0 - 1;
    func_8012931C((struct vec *)a0);

    buf[0] = t0 = *(u16 *)((s32)a0 + 0x6);
    buf[1] = t1 = *(u16 *)((s32)a0 + 0xA);
    buf[2] = t2 = *(u16 *)((s32)a0 + 0xE);

    t0 += *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2E);
    buf[4] = t0;
    t1 += *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x30);
    buf[5] = t1;
    t2 += *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x32);
    buf[6] = t2;

    if (*(void **)((s32)a0 + 0x2C) != NULL) {
        func_8017E1E8(*(void **)((s32)a0 + 0x2C), &buf[0], &buf[4]);
    }
}




void func_801ACD10(void *a0) {

    extern void (*D_801B07D8[])(void);
    D_801B07D8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_800599B8(void *, void *);
extern u8 D_801F8B18;

void func_801ACD4C(void) {
    u16 sp10[4];
    u16 *base;
    u16 *p;
    s32 i;
    u16 first;
    u16 t;

    base = (u16 *) &D_801F8B18;
    first = base[0];
    i = 0;
    p = base;
    do {
        t = p[1];
        i++;
        p[0] = t;
        p++;
    } while (i < 0x5E);
    base[i] = first;
    sp10[0] = 0x100;
    sp10[1] = 0x1E0;
    sp10[2] = 0x100;
    sp10[3] = 1;
    func_800599B8(sp10, (void *) &D_801F8B18);
}




void func_801ACDC8(void *a0) {

    extern void (*D_801B07E0[])(void);
    D_801B07E0[*(u16 *)((s32)a0 + 0x2)]();
}


s32 func_801ACE04(s32 arg0) {
    return *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) >= 0x801;
}




void func_801ACE20(void *a0) {

    extern void (*D_801B07E8[])(void);
    D_801B07E8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* §8 rodata island: D_801A0218 (0x000020E0) lives only in this function's own
   .s rodata block, so this draft owns its definition. Same __asm__ island spelling the TU
   already uses for its other single-word rodata islands. */
__asm__(".section .rodata\nD_801A0218:\n.word 0x000020E0\n.section .text");  // !FAKE: instruction .section — REFUSED asm-data: a `.section` block defines data as assembly (a rodata carve, not a compiler steer) — T7 (P36 rung B tus11)

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_801ADD98(u8 *a0, volatile u8 *a1, volatile u8 *a2);
extern s32 func_8001D074(s32 a0, s32 a1);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8001CD9C(s32 a0, s32 a1);
extern void func_8012AD50(void *a0);

extern u8 D_801F0C90[];
extern u8 D_801F8A78[];
extern u8 D_801F8AB8[];
extern u8 D_801F8AE8[];

extern s32 D_801F8D18;
extern s32 D_801F8D1C;
extern s32 D_801F8D58;
extern s32 D_801F8D5C;

void func_801ACE5C(void *a0) {
    /* §160a / §48-C2: align-1 4-byte block copy => lwl/lwr + swl/swr */
    typedef struct { char c[4]; } Blk4;
    extern s32 D_801A0218;
    extern s32 D_801A021C;
    extern s32 D_801A0220;

    s32 v0;
    s32 v1;
    s32 s1;
    s32 t;
    void *p;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, (s32)D_801F0C90);

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x40;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(v1 + 0x1C) = 0x200;
    *(s16 *)(v1 + 0x18) = 0x200;

    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = 0x300;

    t = *(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0xA);
    *(u16 *)((s32)a0 + 0xE) += 0x20;
    *(s16 *)((s32)a0 + 0x52) = -0x200 - t;
    func_801ADD98(D_801F8A78, D_801F8AB8, D_801F8AE8);

    s1 = func_8001D074(0x7E, 0x100);
    *(s32 *)((s32)a0 + 0xCC) = s1;
    if (s1 != 0) {
        p = (void *)&D_801F8D18;
        func_800233CC(p, 0x80);
        *(Blk4 *)p = *(Blk4 *)&D_801A0218;
        *(s32 *)((s32)a0 + 0xE0) = 0x20C;
        *(Blk4 *)&D_801F8D1C = *(Blk4 *)&D_801A021C;
        func_8001CD9C(s1, (s32)p);
        *(u16 *)(s1 + 0x2C) = 0xC100;
        *(s32 *)(s1 + 0x4) = 0x50000000;
    }

    s1 = func_8001D074(0x7E, 0x100);
    *(s32 *)((s32)a0 + 0xD0) = s1;
    if (s1 != 0) {
        p = (void *)&D_801F8D58;
        func_800233CC(p, 0x60);
        *(Blk4 *)p = *(Blk4 *)&D_801A0220;
        *(s32 *)((s32)a0 + 0xE4) = 0xC02;
        *(Blk4 *)&D_801F8D5C = *(Blk4 *)&D_801A021C;
        func_8001CD9C(s1, (s32)p);
        *(u16 *)(s1 + 0x2C) = 0xC100;
        *(s32 *)(s1 + 0x4) = 0x50000000;
    }

    *(s32 *)((s32)a0 + 0x1C) = 0x10;
    func_8012AD50(a0);
}


#include "common.h"

/* Declarations copied verbatim from the destination TU src/md_SC07_004/md_SC07_004.c
   (lines 48/545/546 and 734-736, its own func_801A7604 / func_801A63A8) -- law 2. */
extern s32 func_8012BEE8(s32 a0);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
/* not present in the TU; fleet canonical form (src/800.c:2120, 6 sites) */
extern void func_80016450(s32 a0, s32 a1);

/* same-TU, still INCLUDE_ASM stubs in md_SC07_004.c (lines 1544 / 1614); no declaration
   exists anywhere in the tree, so these are free choice -- rawest form (law 4). */
extern void func_801ADE1C(void *a0, u16 *a1, s8 *a2, u8 *a3);
extern void func_801AD220();

extern u8 D_801B07F0[];
extern u8 D_801F8A98[];
extern u8 D_801F8AB8[];
extern u8 D_801F8AE8[];

extern s32 D_801F8D18;
extern s32 D_801F8D58;

/* Write-back of D_801F8D18/D_801F8D58 goes through gcc-2.7.2's align-1 struct-assign idiom
   (lwl/lwr out of the source temp + swl/swr into the destination) while the READ side stays a
   plain aligned lw -- so only the STORE is spelled through a 1-byte-aligned 4-byte struct. */
typedef struct { s32 v; } __attribute__((packed, aligned(1))) Align1W_801AD068;

/* arg0's +0xE0/+0xE4 deltas are read through a real COMPONENT_REF, NOT a raw pointer cast.
   That is load-bearing, not cosmetic: expr.c:4888 stamps MEM_IN_STRUCT_P on a COMPONENT_REF,
   and sched.c:817 true_dependence() returns 0 for an in-struct varying-address READ against a
   not-in-struct fixed-address (sp-relative) WRITE. Without the struct spelling the scheduler
   keeps a false dependence on the `t` stack slot and cannot hoist `lw 0xE0($s0)` into the
   preceding load-delay slot -- costing exactly two nops per write-back block. */
typedef struct {
    u8 pad[0xE0];
    s32 dE0;  /* 0xE0 */
    s32 dE4;  /* 0xE4 */
} Obj_801AD068;

void func_801AD068(void *arg0) {
    if (func_8012BEE8((s32)arg0) != 0) {
        func_80016714(*(void **)((u8 *)arg0 + 0xCC), 0x38);
        func_80016714(*(void **)((u8 *)arg0 + 0xD0), 0x38);
        func_8012C218(arg0);
    } else {
        s32 v1 = *(s32 *)((u8 *)arg0 + 0x1C);
        s32 t;      /* address-taken => lives in 0x10($sp); every assignment is a real store */
        s32 *p;

        if (v1 < 15) {
            func_80016450((v1 >= 12 ? (0xF - v1) << 5 : v1 << 3) & 0xF8, 1);
        }

        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x18) += 0x1C0;
        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x1C) =
            *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x18);
        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x1A) += 0x80;
        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x12) += 0x100;

        func_801ADE1C(D_801B07F0, (u16 *)D_801F8A98, (s8 *)D_801F8AB8, (u8 *)D_801F8AE8);

        /* the two write-backs are ASYMMETRIC IN THE TARGET and the asymmetry is spelled here:
           D_801F8D18 is reached through a NAMED POINTER LOCAL, so its address is materialised
           (lui+addiu $a0) before the read and the read folds onto it (`lw 0($a0)`), sharing one
           base with the swl/swr. D_801F8D58 is named bare, so the read %lo-folds
           (`lw %lo(D_801F8D58)($v0)`) and the store re-materialises its own base ($a1). */
        p = &D_801F8D18;
        t = *p;
        t -= ((Obj_801AD068 *)arg0)->dE0;
        *(Align1W_801AD068 *)p = *(Align1W_801AD068 *)&t;
        func_801AD220(arg0, *(void **)((u8 *)arg0 + 0xCC));

        t = D_801F8D58;
        t -= ((Obj_801AD068 *)arg0)->dE4;
        *(Align1W_801AD068 *)&D_801F8D58 = *(Align1W_801AD068 *)&t;
        func_801AD220(arg0, *(void **)((u8 *)arg0 + 0xD0));
    }
}




void func_801AD1E4(void *a0) {

    extern void (*D_801B07F4[])(void);
    D_801B07F4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801AD220(s32 a0, s32 a1) {
    s32 v0;
    s16 v1;

    if (a1 != 0) {
        v0 = *(s32 *)(a0 + 0x64);
        *(u16 *)(a1 + 8) = *(u16 *)(v0 + 6);
        v0 = *(s32 *)(a0 + 0x64);
        *(u16 *)(a1 + 0xA) = *(u16 *)(v0 + 0xA) - 0x40;
        v0 = *(s32 *)(a0 + 0x64);
        *(u16 *)(a1 + 0xC) = *(u16 *)(v0 + 0xE) + 0x20;
        v1 = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        v0 = v1 * 3;
        *(u16 *)(a1 + 0x18) = v0;
        *(u16 *)(a1 + 0x1A) = v0;
    }
}


extern u8 D_801B07F0[];
extern u8 D_801B07F2[];
extern u8 D_801F8A78[];
extern void func_801A649C();

void func_801AD294(void) {
    func_801A649C(D_801F8A78, *(u16 *)D_801B07F0, *(u16 *)D_801B07F2);
}



extern u8 D_801B07F0[];

void func_801AD2CC(void) {
    extern u8 D_801B07F2[];
    extern u8 D_801F8A78[];
    Rec8_801A57E8 rect;

    rect.c = 0x10;
    rect.d = 1;
    rect.a = *(u16 *)D_801B07F0;
    rect.b = (*(u16 *)D_801B07F2);
    func_800599B8(&rect, D_801F8A78);
}


INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A021C);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A0220);

#include "common.h"

/* §160a idiom: lwl/lwr + swl/swr == emit_block_move on an ALIGN-1 4-byte struct
   (same idiom the TU already names Blk4_801A7358 for other rodata globals). */
typedef struct { char c[4]; } Blk4_801AD31C;

/* §160c: the target .s's rodata island IS the definition -- this draft owns both symbols.
   Bytes straight off the splat: ".asciz @@"+pad -> 40 40 00 00; .word 0x002040F0 -> F0 40 20 00. */
const Blk4_801AD31C D_801A0224 = {{'@', '@', 0, 0}};
const Blk4_801AD31C D_801A0228 = {{0xF0, 0x40, 0x20, 0}};

extern u8 D_801F8D98[];
extern Blk4_801AD31C D_801A021C;

extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_801AD4C0(void *a0);
extern void func_801AD4D4(void *a0);

void func_801AD31C(void *s1)
{
    u8 *s0;
    u16 v0;
    u16 flags;
    u16 c;
    s32 sub;

    v0 = *(u16 *)((u8 *)s1 + 0x2E);
    s0 = D_801F8D98 + ((v0 & 3) << 6);
    flags = v0 & 0xF00;

    switch (flags) {
    case 0:
        func_800233CC(s0, 0x80);
        *(Blk4_801AD31C *)(s0 + 0) = D_801A021C;
        *(Blk4_801AD31C *)(s0 + 4) = D_801A021C;
        func_8001CD50(*(s32 *)((u8 *)s1 + 0x20), (s32)s0);
        sub = *(s32 *)((u8 *)s1 + 0x20);
        c = 0x5000;
        *(s16 *)(sub + 0x1A) = c;
        *(s16 *)(sub + 0x18) = c;
        *(s16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x10) = 0xC00;
        *(s16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x12) = *(u16 *)((u8 *)s1 + 0x2C);
        *(s16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x1E) = 0xD00;
        *(s32 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x4) = 0x50000000;
        *(u16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x2C) = 0xC040;
        func_801AD4C0(s1);
        break;
    case 0x100:
        func_800233CC(s0, 0x80);
        *(Blk4_801AD31C *)(s0 + 0) = D_801A0224;
        *(Blk4_801AD31C *)(s0 + 4) = D_801A0228;
        func_8001CD50(*(s32 *)((u8 *)s1 + 0x20), (s32)s0);
        sub = *(s32 *)((u8 *)s1 + 0x20);
        c = 0x100;
        *(s16 *)(sub + 0x1A) = c;
        *(s16 *)(sub + 0x18) = c;
        *(s16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x10) = 0xC80;
        *(s16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x12) = *(u16 *)((u8 *)s1 + 0x2C);
        *(s16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x1E) = 0xC00;
        *(s32 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x4) = 0x50000000;
        *(u16 *)(*(s32 *)((u8 *)s1 + 0x20) + 0x2C) = 0xC100;
        func_801AD4D4(s1);
        break;
    }
}



void func_801AD4C0(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x10;
        *(s16 *)((char *)a0 + 0x2) = 0x1;
    }


void func_801AD4D4(void *a0) {
    extern void func_801AD55C(void *a0);
    extern void func_801AD700();
    extern void func_8002D4C8(s32 a0, s32 a1);

    func_801AD55C(a0);
    func_801AD700(a0);
    *(s32 *)((char *)a0 + 0x1c) = 0x10;
    *(s16 *)((char *)a0 + 0x2) = 0x2;
    func_8002D4C8(0xBA3, 0);
}




void func_801AD520(void *a0) {

    extern void (*D_801B081C[])(void);
    D_801B081C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801AD55C(void *a0) {
    void *a1;

    a1 = *(void **)((char *)a0 + 0x34);
    if (a1 != NULL) {
        *(u16 *)((char *)a0 + 0x6) = *(u16 *)((char *)a1 + 0x6) + *(u16 *)((char *)a1 + 0x50);
        *(u16 *)((char *)a0 + 0xA) = *(u16 *)((char *)a1 + 0xA) + *(u16 *)((char *)a1 + 0x52) - 0x40;
        *(u16 *)((char *)a0 + 0xE) = *(u16 *)((char *)a1 + 0xE) + *(u16 *)((char *)a1 + 0x54);
    }
}


#include "common.h"

extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);
extern u16 D_801B0828[];

void func_801AD5B4(s32 param_1, s32 param_2) {
    s32 s2;
    s32 s0;
    s32 s1;
    s32 r;
    s32 b;

    s2 = param_1;
    s0 = param_2;
    s1 = func_80132EF4(param_1, 0x2F);

    if (s1 != 0) {
        r = rand();
        s0 = s0 & 3;
        b = D_801B0828[s0] - 0x40;
        *(u16 *)(s1 + 0x2C) = b + (r & 0x7C);
        r = rand();
        *(u16 *)(s1 + 0x2E) = s0 + ((r & 3) << 12);
        *(s32 *)(s1 + 0x34) = s2;
    }
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);
extern u16 D_801B0828[];

void func_801AD640(s32 param_1, s32 param_2) {
    s32 s2;
    s32 s0;
    s32 s1;
    s32 r;
    s32 b;
    s32 i;

    s2 = param_1;
    s1 = param_2;
    s0 = func_80132EF4(param_1, 0x2F);

    if (s0 != 0) {
        r = rand();
        i = s1 & 3;
        b = D_801B0828[i];
        *(u16 *)(s0 + 0x2E) = i + 0x100;
        *(s32 *)(s0 + 0x34) = s2;
        *(u16 *)(s0 + 0x2C) = b - 0x40 + (r & 0x7C);
    }
}




void func_801AD6C4(void *a0) {

    extern void (*D_801B0830[])(void);
    D_801B0830[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* 12-byte arg-block built at sp+0x10 for the func_800484EC call */
typedef struct { s32 f10, f14, f18; } S12_801AD700;

extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012B414(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_801AD700(void *a0)
{
    void *s0;
    S12_801AD700 sp10;
    s16 i;

    for (i = 0x100; i < 0x1000; i += 0x200) {
        s0 = (void *)func_8012C588(0x3A1, 0);
        if (s0 != NULL) {
            *(u16 *)((s32)s0 + 0x6) = *(u16 *)((s32)a0 + 0x6);
            *(u16 *)((s32)s0 + 0xA) = *(u16 *)((s32)a0 + 0xA);
            *(u16 *)((s32)s0 + 0xE) = *(u16 *)((s32)a0 + 0xE);
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x10) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10);
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
            *(u16 *)(*(s32 *)((s32)s0 + 0x20) + 0x14) = i;
            func_8012B414((s32)s0);
            sp10.f18 = 0;
            sp10.f10 = 0;
            sp10.f14 = 0x400000;
            func_800484EC(*(s32 *)((s32)s0 + 0x20) + 0x34, (s32)&sp10, (s32)s0 + 0x10);
        }
    }
}


#include "common.h"

/* Local 3xs16 stack aggregate whose address is passed to func_801AD914;
   because the address escapes, gcc cannot prove the z field (offset 4)
   is dead even though it is never re-read here. */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Struct801AD7EC_Local;

extern void func_801AD914();

void func_801AD7EC(s32 a0) {
    /* register pins reproduce the target's density-priority regalloc order
       (cookbook §32#1 / regalloc-order): val->$s0, obj->$s1, i->$s2,
       c700->$s3, c100->$s4 -- matching the sw/addiu prologue order. */
    s32 obj = a0;
    s32 i;
    s32 c700;
    s32 c100;
    s32 val;
    Struct801AD7EC_Local local;

    local.z = 0;

    i = 0;
    c100 = 0x100;
    c700 = 0x700;
    val = 0x200;
    for (; i < 4; i++) {
        local.y = val;
        local.x = c100;
        func_801AD914(obj, &local, 0x400000);
        local.x = c700;
        func_801AD914(obj, &local, 0x400000);
        val += 0x400;
    }

    i = 0;
    val = 0xC0;
    for (; i < 8; i++) {
        local.y = val;
        local.x = 0x200;
        func_801AD914(obj, &local, 0x400000);
        local.x = 0x300;
        func_801AD914(obj, &local, 0x400000);
        local.x = 0x400;
        func_801AD914(obj, &local, 0x400000);
        local.x = 0x500;
        func_801AD914(obj, &local, 0x400000);
        local.x = 0x600;
        func_801AD914(obj, &local, 0x400000);
        val += 0x200;
    }
}


#include "common.h"

/* decl_prior: fleet-modal ('void', ('s32',)), n=2449 -- identical to this TU's own
 * declarations at md_SC07_004.c:993/1107. */
extern void func_8012B2CC(s32 a0);
/* atlas tu-authoritative: ('s32', ('s32','s32','s32')) n=1337; same as this TU's
 * existing decl at md_SC07_004.c:353. */
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
/* atlas fleet: ('s32', ('s32','s32','s32')) n=3554 */
extern void func_800484EC(s32, s32, s32);

/* 8-byte, 2-byte-aligned struct -> emit_block_move lwl/lwr + swl/swr (cookbook §48-C2,
 * same idiom as func_801A6AD0 above in this TU). */
typedef struct { u16 a, b, c, d; } Blk8_801AD914;

/* 12-byte arg-block built at sp+0x10 for the func_800484EC call */
typedef struct { s32 f10, f14, f18; } S12_801AD914;

void func_801AD914(s32 arg0, void *arg1, s32 arg2) {
    void *sp0;
    S12_801AD914 sp10;
    s32 inner;

    sp0 = (void *)func_8012C658(0x3A1, 1, arg0);
    if (sp0 != NULL) {
        *(Blk8_801AD914 *)(*(s32 *)((s32)sp0 + 0x20) + 0x10) = *(Blk8_801AD914 *)arg1;
        func_8012B2CC((s32)sp0);
        sp10.f18 = 0;
        sp10.f10 = 0;
        sp10.f14 = arg2;
        ((s32 (*)(s32, s32, s32))func_800484EC)(*(s32 *)((s32)sp0 + 0x20) + 0x34, (s32)&sp10, (s32)sp0 + 0x10);
        inner = *(s32 *)((s32)sp0 + 0x20);
        *(u16 *)(inner + 0x1C) = 0x500;
        *(u16 *)(inner + 0x1A) = 0x500;
        *(u16 *)(inner + 0x18) = 0x500;
        *(s32 *)((s32)sp0 + 0x1C) = 0x20;
    }
}




void func_801AD9D4(void *a0) {

    extern void (*D_801B0884[])(void);
    D_801B0884[*(u16 *)((s32)a0 + 0x2)]();
}


/* Hoisted from func_801AE734 (was :10174): func_801ADA10 above also needs it and a
 * second identical typedef is a hard error in gcc 2.7.2. Typedefs emit no bytes. */
typedef struct { u8 unk0[4]; } M4_801AE734;


extern M4_801AE734 D_801B0838[];

void func_801ADA10(s32 a0) {
    s32 m;
    s32 d;

    m = (s16)(*(u16 *)(a0 + 0x2E) + 1) % 6;
    *(u16 *)(a0 + 0x2E) = *(u16 *)(a0 + 0x2E) + 1;
    d = *(s32 *)(a0 + 0x34);
    *(M4_801AE734 *)(d + 0x14) = D_801B0838[(s16)(m * 2)];
    *(M4_801AE734 *)(d + 0x18) = D_801B0838[(s16)(m * 2) + 1];
}


#include "common.h"

extern void func_801AE990(void *a0);
extern void func_801ADBB0(s32 a0, s32 a1, s32 a2);

void func_801ADA9C(s32 arg0) {
    s16 sp10[3];
    s16 *p = (s16 *)arg0;
    s32 i;
    s32 j;

    sp10[0] = p[3];
    sp10[1] = p[5] - 0x40;
    sp10[2] = p[7] + 0x20;
    func_801AE990(sp10);

    j = 2;
    i = 0;
    func_801ADBB0(0x400, 0, 0);
    func_801ADBB0(-0x400, 0, 1);

    for (; i < 8; i++) {
        func_801ADBB0(0, (i << 25) >> 16, (j << 16) >> 16);
        j++;
    }

    for (i = 0; i < 8; i++) {
        func_801ADBB0(0x200, (0x1000000 + i * 0x2000000) >> 16, (j << 16) >> 16);
        j++;
    }

    for (i = 0; i < 8; i++) {
        func_801ADBB0(-0x200, (0x1000000 + i * 0x2000000) >> 16, (j << 16) >> 16);
        j++;
    }
}


void func_801ADBB0(s32 x, s32 y, s32 z)
{
    extern u8 *func_8012913C(s32 a0);

    u16 tx = x;
    u16 ty = y;
    s16 dup = z;
    u8 *work;

    work = func_8012913C(0x74);

    if (work != NULL) {
        *(u16 *)(work + 0x2C) = dup;
        *(u16 *)(*(s32 *)(work + 0x20) + 0x10) = tx;
        *(u16 *)(*(s32 *)(work + 0x20) + 0x12) = ty;
        *(u16 *)(*(s32 *)(work + 0x20) + 0x14) = (s16)z * 0x300;
    }
}


#include "common.h"

/* house style: local structs mirroring src/md_SC07_004/md_SC07_004.c's
   SV_801AAF8C / MTX_801AAF8C (see func_801AAF8C) */
typedef struct { s16 vx, vy, vz, pad; } SV_801ADC40;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_801ADC40;
typedef struct { s32 vx, vy, vz; } VEC32_801ADC40;

extern int rand(void);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void ApplyRotMatrixLV(void *in, void *out);
extern s32 D_801B0894[];

void func_801ADC40(u8 *a0)
{
    SV_801ADC40 sv;    /* sp+0x10 */
    VEC32_801ADC40 vec; /* sp+0x18 */
    MTX_801ADC40 mtx;  /* sp+0x28 */
    s32 flag;          /* sp+0x48 */
    s32 v1;

    sv.vx = (rand() & 0x7FF) - 0x400;
    sv.vy = rand() & 0xFFF;
    sv.vz = 0;
    func_80049CAC((s32)&sv, (s32)&mtx);

    func_8004914C(&mtx);
    mtx.t[0] = *(s16 *)(a0 + 0x6) + *(s16 *)(a0 + 0x50);
    mtx.t[1] = *(s16 *)(a0 + 0xA) + *(s16 *)(a0 + 0x52) - 0x40;
    mtx.t[2] = *(s16 *)(a0 + 0xE) + *(s16 *)(a0 + 0x54);
    func_800491AC(&mtx);

    sv.vy = 0;
    sv.vx = 0;
    sv.vz = -0x310;
    RotTransSV((s32)&sv, (s32)&sv, &flag);

    a0 = func_801290DC(0x2E, (u8 *)&sv);
    if (a0 != 0) {
        v1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1 + 0x2C) = 0xC020;
        vec.vx = 0;
        vec.vy = 0;
        vec.vz = 0x300000;
        ApplyRotMatrixLV(&vec, a0 + 0x10);
        *(s16 *)(a0 + 0x30) = 8;
        *(s16 *)(a0 + 0x32) = 0x10;
        *(s32 *)(a0 + 0x34) = D_801B0894[rand() % 6];
    }
}


void func_801ADD98(u8 *a0, volatile u8 *a1, volatile u8 *a2) {
    s32 ctr;
    s32 v1;

    ctr = 0;
    do {
        a1[0] = (*(u16 *)a0 >> 8) & 0x7C;
        ctr++;
        v1 = (a1[0] << 24) >> 28;
        a1[1] = (*(u16 *)a0 >> 3) & 0x7C;
        a1[2] = (*a0 << 2) & 0x7C;
        a2[0] = v1;
        a2[1] = (a1[1] << 24) >> 28;
        a0 += 2;
        a2[2] = (a1[2] << 24) >> 28;
        a1 += 3;
        a2 += 3;
    } while (ctr < 0x10);
}


#include "common.h"

/* TU-adopted (src/md_SC07_004/md_SC07_004.c:437): same 4x u16 layout used here for a
 * VRAM upload rect {x,y,w,h}. Same name AND same body (law 8/§183.1). */


extern void func_800599B8(void *rect, void *data);

void func_801ADE1C(void *a0, u16 *a1, s8 *a2, u8 *a3) {
    Rec8_801A57E8 rect;
    s32 i;
    void *pos = a0;
    u16 *data = a1;
    u16 *out;
    s8 *a22;
    do { a22 = a2; } while (0);

    i = 0;
    out = data;
    for (; i < 16; i++) {
        u32 c0;
        u32 c2;
        u32 c1;
        s32 k = i * 3;

        if (a22[k + 0] > 0) {
            a22[k + 0] -= a3[k + 0];
        }
        if (a22[k + 0] < 0) {
            a22[k + 0] = 0;
        }

        if (a22[k + 1] > 0) {
            a22[k + 1] -= a3[k + 1];
        }
        if (a22[k + 1] < 0) {
            a22[k + 1] = 0;
        }

        if (a22[k + 2] > 0) {
            a22[k + 2] -= a3[k + 2];
        }
        if (a22[k + 2] < 0) {
            a22[k + 2] = 0;
        }

        c0 = (u8)a22[k + 0] & 0x7C;
        c1 = (u8)a22[k + 1] & 0x7C;
        c2 = (u8)a22[k + 2] & 0x7C;

        c2 >>= 2;
        c0 <<= 8;
        c1 <<= 3;
        c1 |= 0xFFFF8000u;
        c0 |= c1;
        *out = c2 | c0;

        out++;
    }

    rect.a = *(u16 *)pos;
    rect.b = *(u16 *)((u8 *)pos + 2);
    rect.c = 16;
    rect.d = 1;

    func_800599B8(&rect, data);
}


#include "common.h"

extern void func_801298F4(void *arg0);
extern void func_8012AD50(void *a0);
extern void StoreImage(s32, void *);

extern s32 D_801F76B0;
extern s32 D_801F74A8;
extern u8 D_801F8B18;

extern void *D_800B9AC4;
extern void *D_800B9AC8;
extern s32 D_800B9A88;
extern s16 D_800B9A90;
extern s16 D_800B9A92;
extern s16 D_800B9AA0;
extern s16 D_800B9AA2;
extern s16 D_800B9AA4;
extern s16 D_800B9AA6;
extern s16 D_800B9AAE;
extern s16 D_800B9AB4;
extern s16 D_800B9AB6;
extern s16 D_800B9AB8;
extern s16 D_800B9ABA;

void func_801ADF5C(void *a0)
{
    void *s0;
    struct { s16 x, y, w, h; } rect;

    void *p;

    s0 = a0;

    /* D_800B9AC4/D_800B9AC8 are fields of the struct rooted at D_800B9A78
     * (see engine_core.h's Ent_956C / func_8012956C); the func_801298F4
     * call target is that struct's base, computed as p - 0x4C so the
     * compiler reuses the already-materialized D_800B9AC4 address instead
     * of emitting a second relocation. A plain `&D_800B9AC4 - 0x4C`
     * constant-folds at compile time into a FRESH symbolic constant
     * (its own lui/addiu, computed before the stores) instead of runtime
     * register arithmetic, so the address is pinned into a real pseudo
     * with the same zero-byte re-tie idiom func_8012956C uses for its
     * `base` pointer. */
    p = &D_800B9AC4;
    *(void **)p = &D_801F76B0;
    D_800B9AC8 = &D_801F74A8;
    func_801298F4((void *)((u8 *)p - 0x4C));

    {
        s32 mask;
        s16 one;
        register s32 rv0 __asm__("$2");  // !FAKE: pin $2 rv0 — the 0x2000/0x8C/0x1E0 holder is a 3-death pseudo, global.c find_reg (global.c:945-990) hands it $a2 once the single-death locals hold $v0/$v1 (P36 S105 f3 minimum-lever)
        register s32 rv1 __asm__("$3");  // !FAKE: pin $3 rv1 — the 0x118/D_800B9A88 holder, same global.c:945-990 contest (P36 S105 f3 minimum-lever)
        register s32 ra1 __asm__("$5");  // !FAKE: pin $5 ra1 — keeps `ra1 = &D_801F8B18` a second SET of one pseudo (combine.c:1460 otherwise folds it into the call argument and the 0x100 load becomes a birthing insn, sched.c:2477-2490) (P36 S105 f3 minimum-lever)

        mask = 0xF7FFFFFF;
        one = 1;
        __asm__ __volatile__("");  // !FAKE: barrier after one/mask — sched1 birthing boost (sched.c:2477-2544) would sink `li 1` to its first store; the target keeps it at the block top (P36 S105 f3 minimum-lever)
        rv0 = 0x2000;
        rv1 = 0x118;

        D_800B9AA4 = (s16)rv0;
        D_800B9AA6 = (s16)rv0;

        rv0 = 0x8C;

        D_800B9A90 = (s16)rv1;
        D_800B9A92 = (s16)rv1;
        D_800B9AB4 = (s16)rv1;
        D_800B9AB6 = (s16)rv1;


        rv1 = D_800B9A88;
        __asm__ __volatile__("");  // !FAKE: barrier after the D_800B9A88 load — keeps the 0x8C/0x100 group below the load (sched1 hazard tie-break, sched.c:2620-2690, otherwise lifts the load and the 0x118 stores past it) (P36 S105 f3 minimum-lever)
        ra1 = 0x100;

        D_800B9AA0 = (s16)rv0;
        D_800B9AA2 = (s16)rv0;

        rv0 = 0x1E0;

        rect.x = (s16)ra1;
        rect.w = (s16)ra1;

        ra1 = (s32)&D_801F8B18;

        D_800B9AAE = one;
        D_800B9ABA = 0;
        D_800B9AB8 = 0;

        rect.y = (s16)rv0;
        rect.h = one;

        D_800B9A88 = rv1 & mask;

        StoreImage((s32)&rect, (void *)ra1);
    }

    func_8012AD50(s0);
}


extern s32 D_800B9AA8;
extern s16 D_800B9AA4;
extern s16 D_800B9AA6;
extern s16 D_800B9AB8;
extern s16 D_800B9ABA;

void func_801AE060(s32 a0) {
    s32 s0 = a0;
    s32 t;
    s32 *p = &D_800B9AA8;

    *p = *p - 0x300;

    t = *(u16 *)(s0 + 0xFE);
    t += 0x18;
    *(u16 *)(s0 + 0xFE) = t;
    D_800B9AA4 = func_8004787C((s16)t) + 0x2700;
    D_800B9AA6 = func_8004787C(*(s16 *)(s0 + 0xFE) + 0x400) + 0x2700;

    D_800B9AB8 -= 1;
    D_800B9ABA += 1;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        break;
    case 1:
        func_801ACD4C();
        break;
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012AD50(void *a0);

extern u8 D_801F2538[];

void func_801AE138(void *param_1)
{
    s32 d = (s32)param_1;
    s32 obj;
    s32 w;

    obj = ((s32 (*)(void))func_8012C1B8)();
    do { *(s32 *)(d + 0x20) = obj; } while (0);
    if (obj == 0) {
        func_8012CAE4((void *)d);
        return;
    }
    func_8001C810(obj, (s32)D_801F2538);
    w = 0x200;
    *(u32 *)(obj + 4) |= 0x50000000;
    *(u16 *)(obj + 0x2C) |= 0x10;
    *(s16 *)(obj + 0x1C) = w;
    *(s16 *)(obj + 0x1A) = w;
    *(s16 *)(obj + 0x18) = w;
    *(s16 *)(d + 0xA) -= 0x40;
    *(s16 *)(d + 0xE) += 0x20;
    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj != 0) {
        *(s32 *)(d + 0xCC) = obj;
        *(s16 *)(obj + 0x1A) = 0x300;
        *(u16 *)(obj + 0x2C) |= 0x10;
        *(u32 *)(obj + 4) |= 0x40;
        *(s16 *)(obj + 0x1C) = w;
        *(s16 *)(obj + 0x18) = w;
    }
    func_8012AD50((void *)d);
}


#include "common.h"

extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801AD7EC(s32 a0);

void func_801AE220(s32 a0) {
    s32 v20;
    s32 r;
    u16 tmp;
    s16 val0;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        func_8012C588(0x3A0, a0);
        *(s32 *)(a0 + 0x1C) = 6;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        func_8002D4C8(0xB4E, 0);
        break;
    case 1:
        if (func_8012BEE8(a0) != 0) {
            func_8012C588(0x3A0, a0);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            func_801AD7EC(a0);
        }
        break;
    case 2:
        break;
    case 3:
        break;
    }

    val0 = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18);
    if (val0 < 0x2400) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = val0 + 0xC0;
        v20 = *(s32 *)(a0 + 0x20);
        tmp = *(u16 *)(v20 + 0x18);
        *(u16 *)(v20 + 0x1C) = tmp;
        *(u16 *)(v20 + 0x1A) = tmp;
        r = *(s32 *)(a0 + 0xCC);
        if (r != 0) {
            u16 tmp2 = *(u16 *)(r + 0x18) + 0xC0;
            *(u16 *)(r + 0x18) = tmp2;
            *(u16 *)(r + 0x1C) = tmp2;
            *(u16 *)(r + 0x1A) = tmp2;
        }
    }
}


#include "common.h"

extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8012AD50(void *a0);

extern u8 D_801F2D48[];

void func_801AE324(void *a0) {
    s32 v0;
    s32 v1;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, (s32)&D_801F2D48);
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(v1 + 0x2C) = *(u16 *)(v1 + 0x2C) | 0x10;
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(v1 + 0x1C) = 1;
    *(s16 *)(v1 + 0x1A) = 1;
    *(s16 *)(v1 + 0x18) = 1;
    func_8012AD50(a0);
}


extern void func_8012C218(void *a0);

void func_801AE3A4(void *arg0) {
    s16 val;
    s32 *ptr;
    u16 rd;

    val = *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x18);
    if (val >= 0x2801) {
        func_8012C218(arg0);
    } else {
        *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x18) = val + 0x180;
        ptr = (s32 *)(*(s32 *)((char *)arg0 + 0x20));
        rd = *(u16 *)((char *)ptr + 0x18);
        *(u16 *)((char *)ptr + 0x1C) = rd;
        *(u16 *)((char *)ptr + 0x1A) = rd;
    }
}


#include "common.h"

extern void func_801AD55C(void *a0);
extern void func_801292C8(u8 *a0);

extern u8 D_801F8D98[];
extern s32 D_801B07FC[];
extern s32 D_801B0800[];

/* helper view used only to force gcc's unaligned SImode store idiom
 * (lwl/lwr + swl/swr) when writing back into D_801F8D98's element —
 * see cookbook §48-C2 / §160a: any struct type with alignment < 4
 * takes the unaligned-move path even between provably 4-aligned slots. */
typedef struct {
    u16 a, b;
} U16x2;

void func_801AE408(void *a0) {
    u8 *s1 = D_801F8D98 + ((*(u16 *)((s32)a0 + 0x2E) & 3) << 6);

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        /* §193-I: an aggregate local gets an 8-byte frame stride (ceil(size,8)),
         * not its raw size — declaring the reinterpret temp AS the struct type
         * (rather than s32+&cast) is what supplies the target's extra 8 bytes. */
        U16x2 tmp;
        s32 idx2;
        /* unused, but required to reach the target's 0x30 frame (§193-I
         * padding math accounts for 0x28; this local supplies the last 8
         * bytes — see notes: not independently verified against source). */
        u16 pad[4];

        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_801AD55C(a0);

        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) -= 0x4F0;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += 0x60;

        idx2 = (*(u16 *)((s32)a0 + 0x2E) & 3) * 2;

        *(s32 *)&tmp = *(s32 *)(s1 + 0);
        *(s32 *)&tmp += D_801B07FC[idx2];
        *(U16x2 *)(s1 + 0) = tmp;

        *(s32 *)&tmp = *(s32 *)(s1 + 4);
        *(s32 *)&tmp += D_801B0800[idx2];
        *(U16x2 *)(s1 + 4) = tmp;

    } else {
        func_801292C8((u8 *)a0);
    }
}


#include "common.h"

extern void func_801AD55C(void *a0);
extern void func_801292C8(u8 *a0);

extern u8 D_801F8D98[];
extern s32 D_801B07FC[];
extern s32 D_801B0800[];

typedef struct {
    u16 a, b;
} U16x2L;

void func_801AE520(void *a0) {
    u8 *s1 = D_801F8D98 + ((*(u16 *)((s32)a0 + 0x2E) & 3) << 6);

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        U16x2L tmp;

        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_801AD55C(a0);

        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += 0x700;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += 0x60;

        *(s32 *)&tmp = *(s32 *)(s1 + 0);
        *(s32 *)&tmp -= D_801B07FC[0];
        *(U16x2L *)(s1 + 0) = tmp;

        *(s32 *)&tmp = *(s32 *)(s1 + 4);
        *(s32 *)&tmp -= D_801B0800[0];
        *(U16x2L *)(s1 + 4) = tmp;

    } else {
        func_801292C8((u8 *)a0);
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012AD50(void *a0);

extern u8 D_801F07E0[];

void func_801AE624(void *a0) {
    void *s0;
    s32 v0;
    s32 p;
    s32 q;
    s32 r;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    s0 = a0;
    *(s32 *)((s32)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
        return;
    }
    func_8001C810(v0, (s32)D_801F07E0);

    p = *(s32 *)((s32)s0 + 0x20);
    *(s32 *)(p + 4) |= 0x50000000;

    q = *(s32 *)((s32)s0 + 0x20);
    *(u16 *)(q + 0x2C) |= 0x10;

    r = *(s32 *)((s32)s0 + 0x20);
    *(s16 *)(r + 0x18) = *(s16 *)(r + 0x1A) = *(s16 *)(r + 0x1C) = 0x300;

    if (*(s32 *)((s32)s0 + 0x1C) == 0) {
        *(s32 *)((s32)s0 + 0x1C) = 0x18;
    }
    func_8012AD50(s0);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012AD80(s32 a0);
extern void func_8012B414(s32 a0);

void func_801AE6D4(void *arg0) {
    if (func_8012BEE8((s32)arg0) != 0) {
        func_8012C218(arg0);
    } else {
        func_8012AD80((s32)arg0);
        if (*(s16 *)((u8 *)arg0 + 0x70) == 0) {
            func_8012B414((s32)arg0);
        }
    }
}



extern s32 func_801AEA40(s32 a0, s32 a1, s32 a2);
extern M4_801AE734 D_801B0838[];
extern u8 D_801B0868[];

void func_801AE734(s32 arg0) {
    s32 s0;
    s32 t1;
    s32 m;

    s0 = arg0;
    t1 = func_801AEA40(0x200, *(s32 *)(s0 + 0x20) + 0x10, 0x50000000);
    if (t1 != 0) {
        m = (s16)*(u16 *)(s0 + 0x2C) % 6;
        *(s32 *)(s0 + 0x34) = t1;
        *(u16 *)(s0 + 0x2E) = *(u16 *)(s0 + 0x2C);
        *(M4_801AE734 *)(t1 + 0x14) = D_801B0838[(s16)(m * 2)];
        *(M4_801AE734 *)(t1 + 0x18) = D_801B0838[(s16)(m * 2) + 1];
        *(s16 *)(t1 + 0x12) = -0x3F80;
        *(u16 *)(t1 + 0x10) = 0x200;
        *(u16 *)(t1 + 0xC) = 0x200;
        m = D_801B0868[*(s16 *)(s0 + 0x2C)];
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        *(s32 *)(s0 + 0x1C) = m;
    }
}


extern void func_801ADA10();

void func_801AE82C(s32 a0) {
    s32 p;

    p = *(s32 *)(a0 + 0x34);
    if (*(s32 *)(a0 + 0x1C) != 0) {
        *(s32 *)(a0 + 0x1C) -= 1;
    } else if (*(s16 *)(p + 0xC) < 0x1000) {
        *(s16 *)(p + 0xC) += 0x400;
        *(s16 *)(p + 0x10) = *(s16 *)(p + 0xC);
    } else {
        *(u16 *)(a0 + 2) += 1;
        *(s32 *)(a0 + 0x1C) = 0x48;
    }
    if (*(s32 *)(a0 + 0x1C) & 1) {
        func_801ADA10(a0);
    }
}


extern void func_801ADA10();

void func_801AE8B0(s32 a0) {
    if (--*(s32 *)(a0 + 0x1C) == 0) {
        *(u16 *)(a0 + 2) += 1;
    }
    if (*(s32 *)(a0 + 0x1C) & 1) {
        func_801ADA10(a0);
    }
}


extern void func_801ADA10();
extern void func_801AEAE4();
extern void func_801292C8(u8 *a0);

void func_801AE908(void *a0) {
    register s32 p __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    u16 t;

    p = *(s32 *)((s32)a0 + 0x34);
    t = *(u16 *)(p + 0xC) - 0x400;
    *(u16 *)(p + 0xC) = t;
    *(u16 *)(p + 0x10) = t;
    if (*(s16 *)(p + 0xC) > 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        if (*(s32 *)((s32)a0 + 0x1C) & 1) {
            func_801ADA10(a0);
        }
    } else {
        func_801AEAE4();
        func_801292C8((u8 *)a0);
    }
}


extern void func_80016714(void *a0, s32 a1);

typedef struct {
    u16 a, b, c, d;
} U16x4;

extern U16x4 D_801F8EA0[];
extern u16 D_801F8EA2;
extern u16 D_801F8EA4;

void func_801AE990(void *a0) {
    U16x4 *dst;
    s32 i;
    u8 *p;

    dst = D_801F8EA0;

    if (a0 != NULL) {
        *dst = *(U16x4 *)a0;
    } else {
        D_801F8EA4 = 0;
        D_801F8EA2 = 0;
        *(u16 *)dst = 0;
    }

    *(u16 *)((u8 *)dst + 0xC) = 0x1000;
    *(u16 *)((u8 *)dst + 0xA) = 0x1000;
    *(u16 *)((u8 *)dst + 0x8) = 0x1000;
    *(u16 *)((u8 *)dst + 0x14) = 0;
    *(u16 *)((u8 *)dst + 0x12) = 0;
    *(u16 *)((u8 *)dst + 0x10) = 0;

    p = (u8 *)dst + 0x18;
    i = 0;
    do {
        func_80016714(p, 0x24);
        i++;
        p += 0x24;
    } while (i < 0x20);
}


extern s32 func_801AEAAC(void);
extern void func_801AEB04(s32 a0, s16 a1, s32 a2, s32 a3);

s32 func_801AEA40(s32 a0, s32 a1, s32 a2) {
    s32 ret;
    ret = func_801AEAAC();
    if (ret != 0) {
        func_801AEB04(ret, (s16)a0, a1, a2);
    }
    return ret;
}


s32 func_801AEAAC(void) {

    extern u8 D_801F8EB8[];
    s32 a0;
    s32 v1;
    v1 = (s32)D_801F8EB8;
    for (a0 = 0; a0 < 0x20; a0++, v1 += 0x24) {
        if (*(u16 *)v1 == 0) {
            return v1;
        }
    }
    return 0;
}


extern void func_80016714(void *a0, s32 a1);

void func_801AEAE4(void *a0) {
    func_80016714(a0, 0x24);
}


typedef struct {
    u8 unk0[8];
} B8_801AEB04;

typedef struct {
    u8 unk0[4];
} M4_801AEB04;

const s8 D_801A022C[4] = { 0, 0, 0, 0 };

void func_801AEB04(s32 a0, s16 a1, s32 a2, s32 a3) {
    *(u16 *)(a0 + 0x00) = 1;
    *(u16 *)(a0 + 0x02) = a1;
    *(B8_801AEB04 *)(a0 + 0x04) = *(B8_801AEB04 *)a2;
    *(u16 *)(a0 + 0x10) = 0x1000;
    *(u16 *)(a0 + 0x0E) = 0x1000;
    *(u16 *)(a0 + 0x0C) = 0x1000;
    *(u16 *)(a0 + 0x12) = 0;
    *(s32 *)(a0 + 0x20) = a3;
    *(M4_801AEB04 *)(a0 + 0x14) = *(M4_801AEB04 *)&D_801A022C;
    *(M4_801AEB04 *)(a0 + 0x18) = *(M4_801AEB04 *)&D_801A022C;
    *(M4_801AEB04 *)(a0 + 0x1C) = *(M4_801AEB04 *)&D_801A022C;
}




extern U16x4 D_801F8EA0[];
extern u16 D_801F8EA2;
extern u16 D_801F8EA4;
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_801AEC38(s32 a0, s32 a1, s32 a2);

void func_801AEB94(void)
{
    s32 q; /* $s0 */
    s32 i; /* $s1 */
    s32 p; /* $s2 */
    s32 loc[8];

    p = (s32)D_801F8EA0;
    func_80049CAC(p + 0x10, (s32)loc);

    loc[5] = *(s16 *)p;
    loc[6] = (s16)D_801F8EA2;
    loc[7] = (s16)D_801F8EA4;
    func_80020F34((s32)loc, p + 8);

    q = p + 0x18;
    for (i = 0; i < 0x20; i++, q += 0x24) {
        if (*(u16 *)q != 0) {
            func_801AEC38(p, q, (s32)loc);
        }
    }
}


#include "common.h"

/* MATRIX-style 0x20-byte matrix: s16 m[3][3] (18B) + 2B pad + s32 t[3] (12B).
 * Same spelling as the TU-neighbour Mtx_801A6184 (func_801A6184). */
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx_801AEC38;

/* 8-byte SVECTOR-style GTE input vertex. */
typedef struct { s16 x, y, z, pad; } Svec_801AEC38;

/* OT/primitive tag: 24-bit next-pointer + 8-bit length, then the RGB/code word.
 * Same spelling as the TU-neighbour P_TAG (func_801A5E60). */
typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } PTag_801AEC38;

/* File-scope spellings the TU already uses verbatim (law 2). */
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80020F34(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);



/* one column of a s16[3][3] through the rotation matrix, in place */

/* the s32 t[3] through the same matrix, in place */


/* Levers that closed this one (all byte-verified with match_one):
 *  1. Params used DIRECTLY (no `s2 = (u8 *)a1;` locals).  The explicit copy
 *     statements make sched1 sink `sw $s1`/`addu $s1` below the RotMatrixYXZ
 *     argument setup; letting assign_parms emit them puts the pair back at
 *     the top of the prologue exactly as the target has it.  (-4 ins of diff)
 *  2. `pad0[48]` / `pad1[8]`: the frame has 60 dead bytes.  Aggregates get
 *     their slots at block entry, address-taken SCALARS only when `&x` is
 *     expanded -- so pad0 lands before sv[] (top-level) and pad1 AFTER
 *     flag/flag2/otz because it is declared in an inner block.  Slots are
 *     8-byte aligned, so pad1[8] @ sp+0x90 lands the frame on -0xB0.
 *  3. `register s32 raw __asm__("$4")`: gcc folds a plain `raw = w;` away, so
 *     the target's `addu $a0, $v1, $zero` never appears.  The $a0 pin forces
 *     the copy, and the in-place `w &= 0xC000` keeps the mask in the lh's reg.
 *  4. ONE variable `d` holds BOTH the 0xC000 compare constant and the 0xFFF
 *     mask.  Written as two separate temps the mask coalesces onto the dying
 *     hard reg $a0; reusing the constant's pseudo puts it in $v0 (and CSE
 *     still hoists the duplicated `raw & 0xFFF` into the bne delay slot, so
 *     the duplication costs zero instructions). */
void func_801AEC38(s32 a0, s32 a1, s32 a2)
{
    /* Block-scope, byte-identical to the spellings the TU's other functions
     * use for these four globals + the allocator (md_SC07_004.c:8742-8745,
     * :5723) -- a file-scope `extern u16 D_800B9A02;` would collide with the
     * `extern short` those blocks declare. */
    extern u8 D_800AF648;
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern void *func_80010A08(s32);

    Mtx_801AEC38 mtx;           /* sp+0x10 */
    u8 pad0[48];                /* sp+0x30 */
    Svec_801AEC38 sv[4];        /* sp+0x60 */
    s32 flag;                   /* sp+0x80 */
    s32 flag2;                  /* sp+0x84 */
    s32 otz;                    /* sp+0x88 */
    s32 s3;
    s32 w;
    u32 *pot;
    u32 *otp;
    u8 *pkt;
    u8 *q;
    s32 pz;
    s32 w1;
    s32 w2;

    {
        u32 tv = *(u16 *)&D_800B9A02;
        u32 bv = (u32)&D_800A6610;
        pot = (u32 *)((tv << 14) + bv);
    }
    s3 = *(s32 *)(((u8 *)a1) + 0x20);

    RotMatrixYXZ(((u8 *)a1) + 4, &mtx);

    mtx.t[2] = 0;
    mtx.t[1] = 0;
    mtx.t[0] = 0;
    func_80020F34((s32)&mtx, (s32)(((u8 *)a1) + 0xC));

    gte_SetRotMatrix(((u8 *)a2));
    gte_mulcol((u8 *)&mtx);
    gte_mulcol((u8 *)&mtx + 2);
    gte_mulcol((u8 *)&mtx + 4);
    gte_SetTransMatrix(((u8 *)a2));
    gte_multrans((u8 *)mtx.t);

    gte_SetRotMatrix(&D_800AF648);
    gte_mulcol((u8 *)&mtx);
    gte_mulcol((u8 *)&mtx + 2);
    gte_mulcol((u8 *)&mtx + 4);
    gte_SetTransMatrix(&D_800AF648);
    gte_multrans((u8 *)mtx.t);

    func_8004914C(&mtx);
    func_800491AC(&mtx);

    sv[0].z = 0;
    sv[0].y = 0;
    sv[0].x = 0;
    w1 = *(u16 *)(((u8 *)a1) + 2) >> 5;
    sv[1].y = 0;
    sv[1].x = w1;
    w2 = *(u16 *)(((u8 *)a1) + 2) * 3 >> 2;
    sv[2].x = -w1;
    sv[2].y = 0;
    sv[3].y = 0;
    sv[3].x = 0;
    sv[1].z = w2;
    sv[2].z = w2;
    sv[3].z = *(u16 *)(((u8 *)a1) + 2);

    pkt = func_80010A08(0x24);
    pkt[3] = 8;
    pkt[7] = 0x38;
    if (s3 & 0x40000000) {
        pkt[7] = 0x3A;
    }

    gte_ldv3(&sv[0], &sv[1], &sv[2]);
    gte_rtpt();
    gte_stflg(&flag);
    gte_stsxy3(pkt + 8, pkt + 0x10, pkt + 0x18);
    gte_ldv0(&sv[3]);
    gte_rtps();
    gte_stflg(&flag2);
    flag |= flag2;
    gte_stsxy(pkt + 0x20);
    gte_avsz4();
    gte_stotz(&otz);

    if ((flag & ~0x1000) == 0) {
        u8 pad1[8];             /* sp+0x90 */
        register s32 raw __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        s32 d;

        pz = otz + 1;
        w = *(s16 *)(((u8 *)a1) + 0x12);
        raw = w;
        w &= 0xC000;
        if (w != 0) {
            d = 0xC000;
            if (w == d) {
                d = raw & 0xFFF;
                pz -= d;
                if (pz < 0) {
                    pz = 0;
                }
            } else {
                d = raw & 0xFFF;
                pz += d;
            }
        }
        if ((u32)pz < 0x1000) {
            pkt[4] = ((u8 *)a1)[0x14];
            pkt[5] = ((u8 *)a1)[0x15];
            pkt[6] = ((u8 *)a1)[0x16];
            pkt[0xC] = ((u8 *)a1)[0x18];
            pkt[0xD] = ((u8 *)a1)[0x19];
            pkt[0xE] = ((u8 *)a1)[0x1A];
            pkt[0x14] = ((u8 *)a1)[0x18];
            pkt[0x15] = ((u8 *)a1)[0x19];
            pkt[0x16] = ((u8 *)a1)[0x1A];
            pkt[0x1C] = ((u8 *)a1)[0x1C];
            pkt[0x1D] = ((u8 *)a1)[0x1D];
            pkt[0x1E] = ((u8 *)a1)[0x1E];

            otp = (u32 *)(pz * 4 + (u32)pot);
            ((PTag_801AEC38 *)pkt)->addr = ((PTag_801AEC38 *)otp)->addr;
            ((PTag_801AEC38 *)otp)->addr = (u32)pkt;

            if (s3 & 0x40000000) {
                q = D_800A5E60;
                D_800A5E60 = q + 8;
                q[3] = 1;
                *(u32 *)(q + 4) = (((u32)s3 >> 23) & 0x60) | 0xE1000000;
                ((PTag_801AEC38 *)q)->addr = ((PTag_801AEC38 *)otp)->addr;
                ((PTag_801AEC38 *)otp)->addr = (u32)q;
            }
        }
    }
}



extern void func_801AF2EC(void *a0);
extern void func_801AF368(void *a0);
extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_801AF1EC(void *a0) {
    if (*(u16 *)((s32)a0 + 0x2) == 0) {
        func_801AF2EC(a0);
        return;
    }

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_8012931C((struct vec *)a0);

        if (*(s16 *)((s32)a0 + 0x32) == 0) {
            u16 t = *(u16 *)((s32)a0 + 0xA) + 0x1000;
            if (t >= 0x1001) {
                func_801292C8((u8 *)a0);
                return;
            }
        }
    } else {
        func_801292C8((u8 *)a0);
        return;
    }

    *(s32 *)((s32)a0 + 0x14) += *(s32 *)((s32)a0 + 0x34);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += *(u16 *)((s32)a0 + 0x30);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x8) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xA) = *(u16 *)((s32)a0 + 0xA);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xC) = *(u16 *)((s32)a0 + 0xE);
    func_801AF368((void *)*(s32 *)((s32)a0 + 0x20));
}




void func_801AF2EC(void *a0) {
    s32 *s1;
    s32 *s0;
    u16 v0_const;
    s32 rand_val;
    u16 *val_ptr;
    void *a02;
    a02 = a0;

    s1 = (s32 *)a02;
    v0_const = 0x0B;
    s0 = *(s32 **)((u8 *)s1 + 0x20);

    // Store 0x0B as halfword at offset 0x2
    *(u16 *)((u8 *)s0 + 0x2) = v0_const;

    // Load word from offset 0x4, OR with 0x50000000, store back
    *(s32 *)((u8 *)s0 + 0x4) |= 0x50000000;

    // If the halfword at offset 0x18 is 0, store 0x600
    if (*(s16 *)((u8 *)s0 + 0x18) == 0) {
        *(s16 *)((u8 *)s0 + 0x18) = 0x600;
    }

    // Call rand, mask to 0xFF0, store at offset 0x14
    rand_val = rand();
    *(u16 *)((u8 *)s0 + 0x14) = (u16)(rand_val & 0xFF0);

    // Load halfword at offset 0x2 of s1, increment, store back
    val_ptr = (u16 *)((u8 *)s1 + 0x2);
    *val_ptr = *val_ptr + 1;

    // Store 0x100 as halfword at offset 0x30 of s1
    *(s16 *)((u8 *)s1 + 0x30) = 0x100;
}










#define RD16(p) (((struct { u16 v; } *)(p))->v)
#define RW32(p) (((struct { u32 v; } *)(p))->v)

void func_801AF368(void *a0)
{
    extern u8 D_800AF648;
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern void RotMatrixZ(s32 a0, void *a1);

    u8 stk[0x60];                        /* sp+0x10 .. sp+0x6F */
    u32 flags;
    u32 idx;
    u32 ot;
    u32 t2;
    u8 *pkt;
    u8 *p1;
    u8 *p2;
    u8 *pkb;
    s32 d;
    u32 *otp;
    register u32 tv __asm__("$3");       /* twin §137 pin */  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 tv2 __asm__("$4");      /* twin §137 pin */  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)

    u8 *rotm;

    flags = *(u32 *)((s32)a0 + 4);
    rotm = &D_800AF648;

    gte_SetRotMatrix(rotm);
    gte_SetTransMatrix(rotm);
    gte_ldv0((s32)a0 + 8);
    gte_rtps();
    gte_stsxy(stk);
    gte_stflg(stk + 0x48);
    gte_stsz(stk + 0x4c);
    gte_stszotz(stk + 0x50);

    if ((*(u32 *)(stk + 0x48) & 0xFFFFEFFF) == 0) {
        idx = *(s32 *)(stk + 0x50) + 1;
        ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
        {
            u16 flags2 = *(u16 *)((s32)a0 + 0x2c);
            if ((flags2 & 0xC000) != 0) {
                if ((flags2 & 0xC000) == 0xC000) {
                    idx = idx - (flags2 & 0xFFF);
                    if ((s32)idx < 0) idx = 0;
                } else {
                    idx = idx + (flags2 & 0xFFF);
                }
            }
        }

        if (idx < 0x1000) {
            d = (s32)&stk[0x08];

            *(u16 *)(stk + 0x08) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x0a) = 0;
            *(u16 *)(stk + 0x0c) = 0;
            *(u16 *)(stk + 0x0e) = 0;
            *(u16 *)(stk + 0x10) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x12) = 0;
            *(u16 *)(stk + 0x14) = 0;
            *(u16 *)(stk + 0x16) = 0;
            *(u16 *)(stk + 0x18) = 0x1000;
            *(u32 *)(stk + 0x24) = 0;
            *(u32 *)(stk + 0x20) = 0;
            *(u32 *)(stk + 0x1c) = 0;

            RotMatrixZ(*(s16 *)((s32)a0 + 0x14), (void *)d);
            gte_SetRotMatrix((void *)d);
            gte_SetTransMatrix((void *)d);

            *(u16 *)(stk + 0x28) = 0x20;
            *(u16 *)(stk + 0x2a) = 0;
            *(s16 *)(stk + 0x2c) = (s16)*(u32 *)(stk + 0x4c);
            gte_ldv0(stk + 0x28);
            gte_rtps();
            gte_stsxy(stk + 0x54);

            d = (u16)((s16)(RD16(stk + 0x54)) >> 3);
            d |= (s32)((s16)(RD16(stk + 0x56)) >> 3) << 16;

            pkt = D_800A5E60;
            p1 = pkt + 0x18;
            *(u8 *)(pkt + 0x3) = 5;
            *(u8 *)(pkt + 0x7) = 0x28;
            *(u8 *)(p1 + 0x3) = 5;
            t2 = flags & 0x40000000;
            *(u8 *)(p1 + 0x7) = 0x28;
            if (t2 != 0) {
                *(u8 *)(pkt + 0x7) = *(u8 *)(pkt + 0x7) | 2;
                *(u8 *)(p1 + 0x7) = *(u8 *)(p1 + 0x7) | 2;
            }
            *(u8 *)(pkt + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(pkt + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(pkt + 0x6) = *(u8 *)((s32)a0 + 0x26);
            *(u8 *)(p1 + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(p1 + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(p1 + 0x6) = *(u8 *)((s32)a0 + 0x26);

            *(s16 *)(pkt + 0x8) = RD16(stk) + RD16(stk + 0x54);
            *(s16 *)(pkt + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x56);
            *(s16 *)(pkt + 0xc) = RD16(stk) - (d >> 16);
            *(s16 *)(pkt + 0xe) = RD16(stk + 0x02) + d;
            *(s16 *)(pkt + 0x10) = RD16(stk) + (d >> 16);
            *(s16 *)(pkt + 0x12) = RD16(stk + 0x02) - d;
            *(s16 *)(pkt + 0x14) = RD16(stk) - RD16(stk + 0x54);
            *(s16 *)(pkt + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0x8) = RD16(stk) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x54);
            *(s16 *)(p1 + 0xc) = RD16(stk) - d;
            *(s16 *)(p1 + 0xe) = RD16(stk + 0x02) - (d >> 16);
            *(s16 *)(p1 + 0x10) = RD16(stk) + d;
            *(s16 *)(p1 + 0x12) = RD16(stk + 0x02) + (d >> 16);
            *(s16 *)(p1 + 0x14) = RD16(stk) + RD16(stk + 0x56);
            *(s16 *)(p1 + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x54);

            /* addPrim(otp, pkt); addPrim(otp, p1); */
            otp = (u32 *)((idx << 2) + ot);
            tv = RW32(pkt);
            RW32(pkt) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
            tv = RW32(p1);
            RW32(p1) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);

            pkb = D_800A5E60;
            p2 = pkb + 0x30;
            D_800A5E60 = p2;
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p1 & 0xFFFFFF);

            if (t2 != 0) {
                D_800A5E60 = pkb + 0x38;
                *(u8 *)(p2 + 3) = 1;
                RW32(p2 + 4) = ((flags >> 23) & 0x60) | 0xE1000000;
                tv2 = RW32(p2);
                RW32(p2) = (tv2 & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
                RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p2 & 0xFFFFFF);
            }
        }
    }
}





// @class: loose-typing
// @stuck: none — MATCH (99 ins). short* for param_2/param_3: gcc emits lh where sign is live (<<1 for signed div), lhu where truncated to short (arith result / direct copy)

extern int rand(void);
extern int func_801AF9C8(short *pos, int a1, int a2);

void func_801AF808(unsigned short *param_1, short *param_2, short *param_3,
                   unsigned int param_4, int param_5)
{
    int r;
    int d;
    short buf[4];
    int p;

    if ((*param_1 & (short)((1 << param_4) - 1)) == 0) {
        r = rand();
        d = param_3[0] << 1;
        buf[0] = (param_2[0] + (r % d)) - param_3[0];
        r = rand();
        d = param_3[1] << 1;
        buf[1] = (param_2[1] + (r % d)) - param_3[1];
        r = rand();
        d = param_3[2] << 1;
        buf[2] = (param_2[2] + (r % d)) - param_3[2];
        buf[3] = param_3[3];
        p = func_801AF9C8(buf, 0, param_5);
        if (p != 0) {
            *(short *)(*(int *)(p + 0x20) + 0x18) = param_2[3];
        }
    }
    *param_1 = *param_1 + 1;
}


extern int func_801AF9C8(short *pos, int a1, int a2);

int func_801AF994(short *pos, int a1, int a2) {
    int ret;
    ret = func_801AF9C8(pos, a1, a2);
    if (ret != 0) {
        *(s16 *)(ret + 0x32) = 1;
    }
    return ret;
}


extern u8 *func_801290DC(s32 a0, u8 *a1);

int func_801AF9C8(short *pos, int a1, int a2)
{
    u8 *v1;

    v1 = func_801290DC(0x55, (u8 *)pos);

    if (v1 != 0) {
        *(s32 *)(v1 + 0x1C) = pos[3];

        if (a1 != 0) {
            *(s32 *)(v1 + 0x10) = *(s32 *)(a1 + 0x0);
            *(s32 *)(v1 + 0x14) = *(s32 *)(a1 + 0x4);
            *(s32 *)(v1 + 0x18) = *(s32 *)(a1 + 0x8);
            *(s32 *)(v1 + 0x34) = *(s32 *)(a1 + 0xC);
        }

        if (a2 != 0) {
            u8 *ptr = *(u8 **)(v1 + 0x20);
            *(s32 *)(ptr + 0x24) = a2;
        }
    }

    return (int)v1;
}

