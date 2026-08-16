#include "common.h"

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0230);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A03A4);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A00D8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0400);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A09E4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0A98);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0C58);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0CD0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A0D40);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A108C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1124);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A115C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A11D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1400);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A1470);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A18F4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2330);


s32 func_801A2350(s32 arg0) {
        return *(u16*)(arg0 + 0x34) == 0x6;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2364);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2C88);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A2CA4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A36A8);


void func_801A36F0(void *a0) {
        s32 v0 = *(u16 *)((s32)a0 + 0xA);
        s32 v1 = *(u16 *)((s32)a0 + 0x52);
        *(u16 *)((s32)a0 + 0x52) = 0;
        *(u16 *)((s32)a0 + 0x108) = 0;
        *(u16 *)((s32)a0 + 0xA) = v0 + v1;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A370C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3744);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3798);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A395C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A39D0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3A6C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3B08);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3B18);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3D60);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3EA8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3EEC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A3F10);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A41CC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4258);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4328);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A43EC);



void func_801A4420(void *a0) {

    extern void (*D_801AFF34[])(void);
    D_801AFF34[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A445C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A44C4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4570);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A46B8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A46D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A46F0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4724);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4A18);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4AAC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4ACC);



void func_801A4E80(void *a0) {

    extern void (*D_801B014C[])(void);
    D_801B014C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4EBC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A4FDC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5094);

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

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A54F0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5654);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5698);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5798);

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

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5CE8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5D68);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A5E60);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6184);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6330);


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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6428);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A649C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A64DC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6560);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6610);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A66DC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A67F8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6908);

extern void func_801A1E94(void);
void func_801A6A18(void) {
    func_801A1E94();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6A38);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6AD0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6BC0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6CA8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6D90);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6DF4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6E78);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6EF4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6F3C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A6FD4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A70D0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7184);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7200);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7808);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7864);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A01E8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A788C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7AF8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7B08);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7C34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7C58);


void func_801A7CC8(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x4;
        *(s16 *)((char *)a0 + 0x2) = 0x4;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7CDC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7D18);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7D34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7E5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A7F84);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8054);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A80C0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8228);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8294);



void func_801A8404(void *a0) {

    extern void (*D_801B038C[])(void);
    D_801B038C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8440);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8494);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8528);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8564);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A85A8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A861C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8670);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A86B4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A86F8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8738);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A876C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A87C4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8990);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8A64);



void func_801A8B28(void *a0) {

    extern void (*D_801B0400[])(void);
    D_801B0400[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8B64);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8C58);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8CE0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8DCC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A8E34);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A900C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A90D8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9270);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A930C);



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

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9454);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A94A0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9674);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9810);



void func_801A98CC(void *a0) {

    extern void (*D_801B072C[])(void);
    D_801B072C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9908);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9954);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A99A4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9AAC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9ADC);



void func_801A9B04(void *a0) {

    extern void (*D_801B0768[])(void);
    D_801B0768[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9B40);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9B80);

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
extern void func_801AA2F8(void);
extern void func_801AA60C(void *a0, s32 a1);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9EB0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9F5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801A9FA8);



void func_801A9FC8(void *a0) {

    extern void (*D_801B0780[])(void);
    D_801B0780[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA004);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA0B4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA160);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA210);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA2F8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA3CC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA4A8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA4EC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA540);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA584);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA60C);



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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA7E4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA91C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AA9D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AAA6C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AAB28);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AACD4);


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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AAF34);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB41C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB54C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB5D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB694);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB748);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB78C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB818);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB8C0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AB9AC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABA74);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABBA4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABC04);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABC8C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABDA4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABEE0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ABFF8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC0D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC150);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC234);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC29C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC3C8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC47C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC54C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC59C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC6C0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC794);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC8B8);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC940);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AC9CC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACA88);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACB2C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACC24);



void func_801ACD10(void *a0) {

    extern void (*D_801B07D8[])(void);
    D_801B07D8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACD4C);



void func_801ACDC8(void *a0) {

    extern void (*D_801B07E0[])(void);
    D_801B07E0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACE04);



void func_801ACE20(void *a0) {

    extern void (*D_801B07E8[])(void);
    D_801B07E8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ACE5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD068);



void func_801AD1E4(void *a0) {

    extern void (*D_801B07F4[])(void);
    D_801B07F4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD220);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD294);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD2CC);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A021C);

INCLUDE_RODATA("asm/md_SC07_004/nonmatchings/md_SC07_004", D_801A0220);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD31C);


void func_801AD4C0(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x10;
        *(s16 *)((char *)a0 + 0x2) = 0x1;
    }


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD4D4);



void func_801AD520(void *a0) {

    extern void (*D_801B081C[])(void);
    D_801B081C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD55C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD5B4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD640);



void func_801AD6C4(void *a0) {

    extern void (*D_801B0830[])(void);
    D_801B0830[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD700);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD7EC);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AD914);



void func_801AD9D4(void *a0) {

    extern void (*D_801B0884[])(void);
    D_801B0884[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADA10);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADA9C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADBB0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADC40);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADD98);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADE1C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801ADF5C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE060);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE138);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE220);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE324);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE3A4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE408);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE520);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE624);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE6D4);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE734);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE82C);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE8B0);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE908);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AE990);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEA40);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AEAE4);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF2EC);

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


INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF994);

INCLUDE_ASM("asm/md_SC07_004/nonmatchings/md_SC07_004", func_801AF9C8);
