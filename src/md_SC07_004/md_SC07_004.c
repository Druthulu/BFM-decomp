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
    register s32 i __asm__("$4");
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

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0400);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A09E4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0D40);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1124);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A11D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1400);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1470);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1984);

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
                func_801A3D60(a0);
            }
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += 0x80;
            func_801A3EA8(a0);
        }
        func_8018503C();
        break;
    }
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1C38);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1C7C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1E74);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1E94);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A0168);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1F3C);

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
    register s32 flag __asm__("$4");

    func_80178B18(a0, (s32)&D_801AFD8C);
    flag = *(s32 *)(a0 + 0xD4);
    *(s32 *)(a0 + 0x1C) = 0x20;
    (*(u16 *)&D_801F8868) = 0;
    if (flag != 0) {
        ((void (*)(void))func_801A7D18)();
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2400);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2D78);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2DC4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2E90);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2F34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A30C8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3114);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3180);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A34C4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A34FC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3594);

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
    mag = diff;
    if ((s16)diff < 0) {
        mag = -diff;
    }
    __asm__ __volatile__("" : "=r"(diff) : "0"(diff) : "memory");
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
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");

    v0 = *(u16 *)(a0 + 0x10A);
    v1 = *(s32 *)(a0 + 0x20);
    v0 = v0 + 1;
    *(u16 *)(a0 + 0x10A) = v0;
    v0 = D_801AFE34[v0 & 7];
    *(u16 *)(v1 + 0x1C) = v0;
    *(u16 *)(v1 + 0x1A) = v0;
    *(u16 *)(v1 + 0x18) = v0;
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3744);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3798);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A395C);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3B18);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3D60);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3EA8);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3FB0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4008);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4060);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A40CC);


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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4258);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A44C4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4724);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4AAC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4ACC);



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
        __asm__ __volatile__("");
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A53F4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5414);



void func_801A5470(void *a0) {

    extern void (*D_801B0168[])(void);
    D_801B0168[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A54AC);

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
extern void func_801A5B00(void *a0);
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5AA0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5AC0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5AE0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5B00);



void func_801A5B20(void *a0) {

    extern void (*D_801B02C8[])(void);
    D_801B02C8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5B5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5C44);

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
extern void func_801A5E60(void *, void *);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5E60);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6908);

extern void func_801A1E94(void);
void func_801A6A18(void) {
    func_801A1E94();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6A38);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6D90);

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
extern void func_801A53F4(void *a0);
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6EF4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7184);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A72DC);

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
    register s32 s1 __asm__("$17");
    register void *s0 __asm__("$16");
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

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 != 0) {
        *(s32 *)(s2 + 0xD0) = s1;
        s0 = &D_801F88F8;
        func_800233CC(s0, 0x60);
        D_801F88F8 = s3[1];
        D_801F88FC = D_801A01E8;
        ((void (*)(s32, void *))func_8001CD9C)(s1, s0);
        *(u16 *)(s1 + 0x2C) = 0xC020;
        *(s32 *)(s1 + 4) = 0x50000000;
    }

    s1 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (s1 != 0) {
        *(s32 *)(s2 + 0xD4) = s1;
        s0 = &D_801F8938;
        func_800233CC(s0, 0xB0);
        D_801F8938 = s3[2];
        D_801F893C = s3[2];
        ((void (*)(s32, void *))func_8001CD9C)(s1, s0);
        *(u16 *)(s1 + 0x2C) = 0xC01E;
        *(s32 *)(s1 + 4) = 0x50000000;
        *(s16 *)(s1 + 0x1E) = 0xD00;
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

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A788C);

void func_801A7AF8(s32 a0) {
    *(u16 *)(a0 + 2) = 1;
    *(u16 *)(a0 + 0x2A) = 0;
}


extern s32 func_8004787C(s32 a0);
extern void func_801A8440(s32 a0);
extern u8 D_801F88BA;

void func_801A7B08(s32 arg0) {
    register s32 s0 __asm__("$16");
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
    __asm__("" : "=r"(r) : "0"(5));
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
    register s32 v1 __asm__("$3");
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8054);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8228);

#include "common.h"

extern void func_801A8494(void *a0);
extern void func_801292C8(u8 *a0);
extern u8 D_801F89F8[4];

void func_801A8294(void *a0) {
    register u8 *base __asm__("$17");
    s32 sub;
    s16 val;

    func_801A8494(a0);
    base = D_801F89F8;

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8564);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A85A8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A861C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8670);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A876C);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A881C);


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801A8884(s32 *a0) {
    a0[7] = 0x3;
    func_8012AD44(a0, 2);
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A88AC);



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

#define gte_ldv0_801A8B64(r0) __asm__ __volatile__ (   \
    "lwc2 $0, 0(%0)\n"                                 \
    "lwc2 $1, 4(%0)"                                   \
    :                                                  \
    : "r"(r0))

#define gte_rtps_801A8B64() __asm__ __volatile__ ("nop\nnop\nrtps")

#define gte_stsxy_801A8B64(r0) __asm__ __volatile__ (  \
    "swc2 $14, 0(%0)"                                  \
    :                                                  \
    : "r"(r0)                                          \
    : "memory")

void func_801A8B64(s32 arg0, s32 arg1)
{
    SVec16_801A8B64 v;
    SXY_801A8B64 xy0;
    SXY_801A8B64 xy1;
    register s32 g __asm__("$6");
    s32 ang;
    s32 dy, dx;
    s32 *p;

    g = (s32)&D_800AF648;

    /* gte_SetRotMatrix(&D_800AF648) */
    __asm__ __volatile__(
        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n" "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
        : : "r"(g) : "$12", "$13", "$14", "memory");

    /* gte_SetTransMatrix(&D_800AF648) */
    __asm__ __volatile__(
        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n" "ctc2 $14, $7\n"
        : : "r"(g) : "$12", "$13", "$14", "memory");

    gte_ldv0_801A8B64(arg1);
    gte_rtps_801A8B64();
    gte_stsxy_801A8B64(&xy0);

    v.vx = *(u16 *)(arg0 + 0x6);
    v.vy = *(u16 *)(arg0 + 0xA);
    v.vz = *(u16 *)(arg0 + 0xE);

    gte_ldv0_801A8B64(&v);
    gte_rtps_801A8B64();
    gte_stsxy_801A8B64(&xy1);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8CE0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8DCC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8E34);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9378);



void func_801A93B8(void *a0) {

    extern void (*D_801B05FC[])(void);
    D_801B05FC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A93F4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A94A0);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9C00);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9F5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9FA8);



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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA0B4);

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
    register u8 *pbase __asm__("$2");
    register s32 idx __asm__("$16");
    register s32 c1 __asm__("$17");
    register s32 p __asm__("$18");
    register s32 c0 __asm__("$19");
    register u8 *q __asm__("$20");
    register s32 i __asm__("$21");

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA4A8);

s32 func_801AA4EC(s32 param_1, s32 param_2)
{
    if (func_8012DF34(param_1, param_2, param_2 + 8) == 0) {
        return func_8012DF34(param_1, param_2, param_2 + 0x10) != 0;
    }
    return 1;
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA540);

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
    register s32 p1 __asm__("$17");
    register s32 s2 __asm__("$18");
    s16 q;

    p1 = param_1;
    s2 = param_2;
    func_8004914C(&D_800AF648);
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
    register s32 s1 __asm__("$17") = param_1;
    register s32 s2 __asm__("$18") = param_2;
    register s32 s3 __asm__("$19") = param_3;
    register s32 s0 __asm__("$16");

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
    register u16 *bidx __asm__("$8");
    register u32 mask1 __asm__("$7");
    register s32 rgb __asm__("$16");
    register u32 tag0 __asm__("$4");

    rgb = arg2;
    __asm__("" : "=r"(rgb) : "0"(rgb));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
    temp_v0 = func_80010A08(0x10);
    *(u8 *)((u8 *)temp_v0 + 3) = 3;
    *(s32 *)((u8 *)temp_v0 + 4) = rgb;
    *(u8 *)((u8 *)temp_v0 + 7) = 0x42;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    temp_v0_2 = RotTransPers(arg0, temp_v0 + 8, &sp10, &sp14);
    if ((temp_v0_2 > 0) && (sp14 >= 0) &&
        (RotTransPers(arg1, temp_v0 + 0xC, &sp10, &sp14) > 0) && (sp14 >= 0)) {
        /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
        mask1 = 0xFFFFFF;
        bidx = (u16 *)&D_800B9A02;
        depth4 = temp_v0_2 * 4;
        tag0 = *(u32 *)temp_v0;
        *(u32 *)temp_v0 = (tag0 & 0xFF000000) |
            (*(u32 *)(depth4 + D_800A651C[*bidx].a) & mask1);
        ot = D_800A651C[*bidx].a;
        *(u32 *)(depth4 + ot) =
            (*(u32 *)(depth4 + ot) & 0xFF000000) | ((u32)temp_v0 & mask1);
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



extern void func_801AB1A8(void);
    void func_801AB178(s32 *param) {
        if (*(u16 *)((char *)param + 0x2) == 0) {
            ((void (*)(void))func_801AB1A8)();
        }
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB1A8);

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
        register u32 m24 = 0x00FFFFFF;
        register u32 mFF = 0xFF000000;
        register s32 i4 __asm__("$6") = idx * 4;
        register u32 pv __asm__("$4");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & mFF) | (*(u32 *)(i4 + D_800A651C[D_800B9A02].a) & m24);
        i4 += D_800A651C[D_800B9A02].a;
        *(u32 *)i4 = (*(u32 *)i4 & mFF) | ((u32)p & m24);
        func_80016638(&D_800A6518[D_800B9A02 * 20], idx, 1);
    } else {
        register u32 m24 = 0x00FFFFFF;
        register u32 pv __asm__("$3");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800AE7BC[D_800B9A02].a & m24);
        __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
        ot = (u32 *)D_800AE7BC[D_800B9A02].a;
        *ot = (*ot & 0xFF000000) | ((u32)p & m24);
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB54C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB5D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB694);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB748);

extern void func_801292C8(u8 *a0);
extern u8 D_801F88BA;

void func_801AB78C(void *a0) {
    register volatile u8 *p __asm__("$5") = &D_801F88BA;
    register s32 b __asm__("$3");
    s32 t;
    if (*p == 0) {
        func_801292C8((u8 *)a0);
    } else {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += 0x200;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18);
        b = *p;
        t = b - 0x10;
        if (b != 0) {
            b = t;
            if (t < 0) {
                b = 0;
            }
            *p = (u8)b;
        }
    }
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB818);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB8C0);

extern u16 D_8019FF8A;
extern void func_801A8884(s32 *a0);
extern void func_801A88AC(s32 a0);
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABBA4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABC8C);

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
    register s32 r0 __asm__("$16") = (s32)a0;
    register s32 ptr1 __asm__("$17");
    register s32 s2 __asm__("$18");
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
            register s32 inner __asm__("$17") = *(s32 *)(s2 + 0xCC);
            if (inner != 0) {
                val = (v1 + 0x500) << 4;
                *(s16 *)(inner + 0x1A) = val;
                *(s16 *)(inner + 0x18) = val;
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC150);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC234);

#include "common.h"

extern s32 func_8001D074(s32 a0, s32 a1);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_801A94A0(void *a0);

extern u8 D_801B0610[];

void func_801AC29C(void *a0) {
    void *s1;
    s32 s0;
    s32 v0;
    s32 v1;

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
        register void *ra0 __asm__("$4") = s1;
        __asm__ __volatile__("" : "=r"(ra0) : "0"(ra0));
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC54C);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC940);

extern void func_80016714(void *a0, s32 a1);
extern s32 func_8017D7D4(void *a0, void *a1, void *a2, s32 a3);

void func_801AC9CC(void *arg0) {
    void *temp_a0;
    s16 sp10[8];
    s32 v0;
    s32 v1;
    u16 a3;

    temp_a0 = *(void **)((u8 *)arg0 + 0x20);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
        *(void **)((u8 *)arg0 + 0x20) = NULL;
    }
    sp10[0] = *(u16 *)((u8 *)arg0 + 0x6);
    sp10[1] = *(u16 *)((u8 *)arg0 + 0xA);
    sp10[2] = *(u16 *)((u8 *)arg0 + 0xE);
    v0 = *(s16 *)((u8 *)arg0 + 0x30);
    __asm__ __volatile__("" ::: "memory");
    a3 = *(u16 *)((u8 *)arg0 + 0x30);
    if (v0 == 0) {
        a3 = 6;
    }
    v0 = func_8017D7D4(sp10, NULL, (u8 *)arg0 + 0x34, (s8)a3);
    v1 = *(s16 *)((u8 *)arg0 + 0x32);
    *(s32 *)((u8 *)arg0 + 0x2C) = v0;
    if (v1 == 0) {
        *(s32 *)((u8 *)arg0 + 0x1C) = 0x10;
    } else {
        *(s32 *)((u8 *)arg0 + 0x1C) = v1;
    }
    *(u16 *)((u8 *)arg0 + 0x2) = *(u16 *)((u8 *)arg0 + 0x2) + 1;
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACE5C);

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
        /* target keeps this guard value in $v1; unpinned it lands in $a0 (5 mismatches) */
        register s32 v1 __asm__("$3") = *(s32 *)((u8 *)arg0 + 0x1C);
        s32 t;      /* address-taken => lives in 0x10($sp); every assignment is a real store */
        s32 *p;

        if (v1 < 15) {
            s32 v0;

            /* arms textually swapped vs. the natural reading so gcc emits the real
               `j .L801AD0D8` + delay slot instead of a delay-slot-fused shortcut */
            if (v1 >= 12) {
                v0 = 0xF - v1;
                v0 = v0 << 5;
            } else {
                v0 = v1 << 3;
            }
            func_80016450(v0 & 0xF8, 1);
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

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD31C);


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
    register s32 obj __asm__("$17") = a0;
    register s32 i __asm__("$18");
    register s32 c700 __asm__("$19");
    register s32 c100 __asm__("$20");
    register s32 val __asm__("$16");
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADA10);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADA9C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADBB0);

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
    register void *pos __asm__("$10") = a0;
    register u16 *data __asm__("$11") = a1;
    register u16 *out __asm__("$8");

    __asm__ __volatile__("" : "=r"(pos) : "0"(pos) : "memory");
    __asm__ __volatile__("" : "=r"(data) : "0"(data) : "memory");
    i = 0;
    out = data;
    for (; i < 16; i++) {
        register u32 c0 __asm__("$5");
        register u32 c2 __asm__("$4");
        register u32 c1 __asm__("$3");
        s32 k = i * 3;

        if (a2[k + 0] > 0) {
            a2[k + 0] -= a3[k + 0];
        }
        if (a2[k + 0] < 0) {
            a2[k + 0] = 0;
        }

        if (a2[k + 1] > 0) {
            a2[k + 1] -= a3[k + 1];
        }
        if (a2[k + 1] < 0) {
            a2[k + 1] = 0;
        }

        if (a2[k + 2] > 0) {
            a2[k + 2] -= a3[k + 2];
        }
        if (a2[k + 2] < 0) {
            a2[k + 2] = 0;
        }

        c0 = (u8)a2[k + 0] & 0x7C;
        c1 = (u8)a2[k + 1] & 0x7C;
        c2 = (u8)a2[k + 2] & 0x7C;

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

    register void *p __asm__("$3");

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
    __asm__("" : "=r"(p) : "0"(p));
    *(void **)p = &D_801F76B0;
    D_800B9AC8 = &D_801F74A8;
    __asm__ __volatile__("");
    func_801298F4((void *)((u8 *)p - 0x4C));

    {
        register s32 mask __asm__("$7");
        register s16 one __asm__("$6");
        register s32 rv0 __asm__("$2");
        register s32 rv1 __asm__("$3");
        register s32 ra1 __asm__("$5");

        mask = 0xF7FFFFFF;
        __asm__ __volatile__("");
        one = 1;
        __asm__ __volatile__("");
        rv0 = 0x2000;
        __asm__ __volatile__("");
        rv1 = 0x118;
        __asm__ __volatile__("");

        D_800B9AA4 = (s16)rv0;
        D_800B9AA6 = (s16)rv0;

        rv0 = 0x8C;
        __asm__ __volatile__("");

        D_800B9A90 = (s16)rv1;
        D_800B9A92 = (s16)rv1;
        D_800B9AB4 = (s16)rv1;
        D_800B9AB6 = (s16)rv1;

        __asm__ __volatile__("");

        rv1 = D_800B9A88;
        __asm__ __volatile__("");
        ra1 = 0x100;
        __asm__ __volatile__("");

        D_800B9AA0 = (s16)rv0;
        D_800B9AA2 = (s16)rv0;

        rv0 = 0x1E0;
        __asm__ __volatile__("");

        rect.x = (s16)ra1;
        rect.w = (s16)ra1;

        ra1 = (s32)&D_801F8B18;
        __asm__ __volatile__("");

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
    register s32 d __asm__("$17") = (s32)param_1;
    register s32 obj __asm__("$16");
    register s32 w __asm__("$18");

    obj = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(d + 0x20) = obj;
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE3A4);

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
    register void *s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    s32 p;
    s32 q;
    s32 r;

    s0 = a0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
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


typedef struct { u8 unk0[4]; } M4_801AE734;

extern s32 func_801AEA40(s32 a0, s32 a1, s32 a2);
extern M4_801AE734 D_801B0838[];
extern u8 D_801B0868[];

void func_801AE734(s32 arg0) {
    s32 s0;
    register s32 t1 __asm__("$9");
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE82C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE8B0);

extern void func_801ADA10();
extern void func_801AEAE4();
extern void func_801292C8(u8 *a0);

void func_801AE908(void *a0) {
    register s32 p __asm__("$4");
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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEB04);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEB94);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEC38);


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

    s1 = (s32 *)a0;
    v0_const = 0x0B;
    __asm__("");
    s0 = *(s32 **)((u8 *)s1 + 0x20);

    
    *(u16 *)((u8 *)s0 + 0x2) = v0_const;

    
    *(s32 *)((u8 *)s0 + 0x4) |= 0x50000000;

    
    if (*(s16 *)((u8 *)s0 + 0x18) == 0) {
        *(s16 *)((u8 *)s0 + 0x18) = 0x600;
    }

    
    rand_val = rand();
    *(u16 *)((u8 *)s0 + 0x14) = (u16)(rand_val & 0xFF0);

    
    val_ptr = (u16 *)((u8 *)s1 + 0x2);
    *val_ptr = *val_ptr + 1;

    
    *(s16 *)((u8 *)s1 + 0x30) = 0x100;
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF368);




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

