#include "common.h"

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CAE0C);



void func_800CAE54(void *a0) {

    extern void (*D_800CBF94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBF94[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEE0(u8 *a0);
void func_800CAE98(u8 *a0) {
    if (func_80161104()) {
        func_800CAEE0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CAEE0);

extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CAF4C(void *a0) {
    func_801466F0(0x22, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x22, (s32)a0, 0, 0, 0, 1, 0, 0);
    func_801599A4(a0);
    func_80159B3C(a0);
}


void func_800CAFCC(void) {
}


extern void func_800CB5A8(void);

void func_800CAFD4(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBFB8[])(void);
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBFB8[v0]();
    } else {
        func_800CB5A8();
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB030);

extern void func_80147324(s32 a0);
extern s32 func_80146CA0(void *a0);

void func_800CB11C(u8 *arg0) {
    u8 *s1;
    s32 var;
    s16 cur;
    s16 max;
    u16 val;
    s16 temp;

    s1 = *(u8 **)(arg0 + 0x20);
    var = *(s32 *)(arg0 + 0x58) + 0x30000;
    *(s32 *)(arg0 + 0x58) = var;
    *(s32 *)(arg0 + 8) += var;

    cur = *(s16 *)(arg0 + 0x60);
    max = *(s16 *)(arg0 + 0xA);
    if (cur < max) {
        *(s16 *)(arg0 + 0xA) = cur;
        if (*(s16 *)(arg0 + 0x62) == 0) {
            *(s16 *)(arg0 + 0x62) = *(s16 *)(arg0 + 0x62) + 1;
            func_80147324(0x8EC);
        }

        val = *(u16 *)(s1 + 0x1A);
        val -= 0x100;
        *(u16 *)(s1 + 0x1A) = val;

        temp = (s16)val;
        if (temp < 0xC00) {
            func_80146CA0(arg0);
        }
    }
}


extern s32 func_80146CA0(void *a0);

void func_800CB1CC(void *arg0) {
    s32 v1 = *(s32 *)((s32)arg0 + 0x20);
    s16 v = *(u16 *)(v1 + 0x1A) + 0x100;
    *(u16 *)(v1 + 0x1A) = v;
    if (v >= 0x1000) {
        *(u16 *)(v1 + 0x1A) = 0x1000;
        func_80146CA0(arg0);
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB218);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB3B4);

extern s32 func_80146E98(s32 a0);
extern s32 func_80146CA0(void *a0);
void func_800CB570(int param_1)
{
    if (((int (*)(void))func_80146E98)() != 0) {
        ((void (*)(int))func_80146CA0)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB5A8);


extern void func_800CB774(void);

void func_800CB5D8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBFD4[])(void);
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBFD4[v0]();
    } else {
        func_800CB774();
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB634);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB708);

extern void func_80162CCC(void);
void func_800CB774(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB794);

extern u8 D_80078EC1;
extern void (*D_800CC01C[])(void);
extern void func_80146C3C(void);

void func_800CB8B4(void *arg0) {
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC01C[v0]();
    } else {
        func_80146C3C();
    }
}


#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } SV_800CB910;   /*  8 bytes, align 2 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_800CB910; /* 0x20 bytes, align 4 */
typedef struct { s32 vx, vy, vz, pad; } V32_800CB910;  /* 16 bytes, align 4 */

extern void func_8001CF00(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_801465C0(void);
extern void func_80146C3C();
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_800CBF24(void);
extern int rand(void);

extern SV_800CB910 D_800CC028[]; /* stride 8, align 2 -> lwl/lwr + swl/swr copy */
extern V32_800CB910 D_800CC058;   /* 16 bytes, align 4 -> plain lw/sw copy      */
extern u16     D_800CC068[]; /* stride 2 scale table                       */

/* func_800CB910 -- SMALL-EDIT sibling of ov_SC02_041:func_8017D7C0 (proven byte
 * match). Diff vs the seed (wave7b_slate.json[16], 5 sites / 13 ins):
 *   1) `buf[1] -= 0x40;` inserted right before func_80015954((s32)buf, param_1+4)
 *      -- the store lands in the jal's delay slot (same idiom already used two
 *      statements earlier in this same function for `*(p+4) |= 0x80000000`).
 *   2) `if (*(s32*)(param_1+0x2c) == 0) func_800CBF24();` inserted right after,
 *      before the sc/D_800CC068 table read. func_800CBF24 takes no args (it just
 *      writes a global constant -- see asm/md_MAIN_036/nonmatchings/md_MAIN_036/
 *      func_800CBF24.s), so `bnez ..; nop; jal func_800CBF24; nop` with no a0
 *      setup matches a void-arg call.
 *   3/4/5) the extra $s0 save/restore + the extra `addu $s0,$v0,$zero` are pure
 *      register-allocator fallout of the two new statements above increasing
 *      live-range pressure on "p" -- not hand-authored, expected to fall out of
 *      the compile once (1) and (2) are in place.
 */
void func_800CB910(s32 param_1) {
    s16 buf[4];
    SV_800CB910 rot;
    MTX_800CB910 m;
    V32_800CB910 vel;
    s32 obj;
    s32 p;
    s32 p2;
    s16 *q;
    s32 i;
    u16 sc;

    obj = *(s32 *)(param_1 + 0x34);
    p = ((s32 (*)(void))func_801465C0)();
    p2 = p;
    *(s32 *)(param_1 + 0x20) = p;

    if (p != 0) {
        func_8001CF00(p);
        *(s32 *)(p + 0x4) |= 0x80000000;
        func_80015978(obj + 4, (s32 *)buf);
        buf[1] -= 0x40;
        func_80015954((s32)buf, param_1 + 4);

        if (*(s32 *)(param_1 + 0x2c) == 0) {
            func_800CBF24();
        }

        sc = D_800CC068[*(s32 *)(param_1 + 0x30)];
        *(u16 *)(p2 + 0x18) = *(u16 *)(p2 + 0x1a) = *(u16 *)(p2 + 0x1c) = sc;

        vel = D_800CC058;
        rot = D_800CC028[*(s32 *)(param_1 + 0x2c)];

        if (*(s32 *)(param_1 + 0x30) != 0) {
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.vx = ((rand() & 0x1f) - 0x10) << 18;
            vel.vy = ((rand() & 0x1f) - 0x10) << 18;
            vel.vz = ((rand() & 0x1f) - 0x10) << 18;
        }

        func_80049CAC((s32)&rot, (s32)&m);
        func_800484EC((s32)&m, (s32)&vel, (s32)&vel);

        *(s32 *)(param_1 + 0x10) = vel.vx;
        *(s32 *)(param_1 + 0x14) = vel.vy;
        *(s32 *)(param_1 + 0x18) = vel.vz;

        q = (s16 *)(param_1 + 0x38);
        i = 0;
        *(s32 *)(param_1 + 0x4c) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x50) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x54) = ((rand() & 0x1f) - 0x10) * 11;

        do {
            i++;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
        } while (i < 3);

        func_80146E90((s32 *)param_1, 2);
        *(s16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBC14);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBC90);

extern void func_800CBD54(s32 param_1, s32 *param_2);

void func_800CBD2C(s32 param_1) {
    extern s32 D_800CBFE0;
    func_800CBD54(param_1, &D_800CBFE0);
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBD54);



void func_800CBEB0(s32 a0) {
    s32 p;
    *(s32 *)(a0 + 0x4) += *(s32 *)(a0 + 0x10);
    *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x14);
    *(s32 *)(a0 + 0xC) += *(s32 *)(a0 + 0x18);
    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x10) += *(s32 *)(a0 + 0x4C);
    *(u16 *)(p + 0x12) += *(s32 *)(a0 + 0x50);
    *(u16 *)(p + 0x14) += *(s32 *)(a0 + 0x54);
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBF24);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBF3C);
