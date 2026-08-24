#include "common.h"

#include "common.h"

extern void (*D_801A6B2C[])(void *);
extern void func_801A293C(void *a0);
extern void func_801A4268(void *a0);
extern void func_801A2EC8(void *a0);
extern s32 D_801F4360[];

void func_801A01D4(void *a0) {
    D_801A6B2C[*(u16 *)((s32)a0 + 0x2)](a0);
    if (*(u16 *)a0 != 0) {
        func_801A293C(a0);
        func_801A4268(a0);
        func_801A2EC8(a0);
    }
    {
        s32 i;
        for (i = 0; i < 3; i++) {
            D_801F4360[i] += 1;
        }
    }
}


/*
 * func_801A026C  (md_SC07_003, 0x801A026C, 154 ins)  ==  MATCH, byte-exact.
 *
 * Overlay/actor init: gate on the game-state id, register the actor, seed its
 * fields, spawn four sub-actors, then seed the SC07 minigame globals.
 *
 * LEVERS (each verified by removing it and re-scoring):
 *  1. The 0x58 word is written with PLAIN LITERALS:
 *       (u32)D_801A6854 | 0x10000000 | 0x40000000
 *     fold's `associate` does NOT merge the two constants because the left
 *     operand is an ADDR_EXPR, not an INTEGER_CST, so split_tree finds no
 *     constant to pull and the two `or`s survive (accumulator $v0, temp $v1).
 *     Binding either constant to a local (src/800.c lever 2) is WRONG here: it
 *     hoists the lui above the address and swaps the or order (6 mismatched);
 *     `h |= C;` statement form puts the accumulator in $v1 (10 mismatched).
 *  2. The D_801AE21C -> D_801F436C copy loop must use EXPLICIT BYTE OFFSETS
 *     (`*(s32 *)((u8 *)D_801AE21C + k)`), not `D_801AE21C[i]`.  With array
 *     indexing loop.c strength-reduces both accesses into ADDRESS givs and
 *     hoists two la pairs into the preheader (cookbook s190-A); the target
 *     keeps integer givs and re-materialises %hi/%lo inside the loop, which is
 *     one instruction longer.  This alone fixed the -1 LENGTH-DRIFT.
 *  3. The copy loop's counter is the SAME C VARIABLE `i` as the rand() loop's
 *     counter.  That pseudo is live across `jal rand`, so it is callee-saved,
 *     which is why the copy loop's counter sits in $s1 while its two offsets
 *     sit in caller-saved $a0/$v1 (cookbook s194-C read backwards).  A fresh
 *     variable puts the counter in $v1 (3 mismatched registers).
 *  4. Init order in the copy-loop preheader is source order: `i = 0; k = 0;
 *     j = 0; for (; i < 20; i++)`.  Writing `k = 0; j = 0; for (i = 0; ...)`
 *     emits the three `move ...,zero` in the wrong order (3 mismatched).
 *  5. `*(s32 *)(arg0 + 0x20)` is written RAW at all three uses.  The store to
 *     0x2C of that pointer kills cse's pointer-derived load, so the target
 *     reloads it; naming it in a local collapses two of the three intervals
 *     (cookbook s193-E).
 *  6. The two s16 fill loops index a stride-8 record and let gcc eliminate the
 *     biv, which is what produces `slti $v1, 0x388` / `slti $v1, 0x460` on the
 *     byte-offset giv.
 *
 * SYMBOL AUDIT (law 1c, done after MATCH) - every symbol re-checked against the
 * relocation lines of asm/md_SC07_003/nonmatchings/md_SC07_003/func_801A026C.s.
 * The draft's symbol set and the .s's symbol set are identical (28 names), and
 * each call site / load side / store side was walked individually:
 *   jal func_80029504 / func_8012CAE4($a0=arg0) / func_8012C354(arg0,&D_801A6874)
 *   / func_8001D0E8(*(arg0+0x20),0x7FFF,0x7FFF) / func_8012A828(arg0,&D_801F0008)
 *   / func_8012B2CC(arg0) / func_8012E8A8(arg0) / func_8012C588 x3 (0x34C,0x351,
 *   0x3AB) / func_8012C658(0x34C,2,arg0) / rand / func_8001C97C(&D_801F436C)
 *   / func_801A2E20.   &D_801A6854 -> 0x58, &D_801A68A8 -> 0x80 of *(arg0+0x20),
 *   D_801F4360 <- rand()&0x7FFF, D_801F1344/D_801F1A5C <- (s16)2,
 *   D_801AE21C -> D_801F436C, D_801AE228 -> D_801F43B4, D_801AE21C[0] ->
 *   D_801F43B8, 0 -> D_801F43BC/D_801F4358, 3 -> D_801F43C0.
 *
 * BANK NOTE (law 2): src/md_SC07_003/md_SC07_003.c declares NONE of these
 * symbols (checked name by name) and has no prototype for func_801A026C, so
 * every declaration below is free-standing and nothing had to be adopted.
 * Spellings follow the card's decl_prior: modal fleet forms for func_8012CAE4
 * (void*), func_8012A828 (s32,void*), func_8012E8A8 (u8*), func_8012C354 /
 * func_8012C588 (s32,s32), func_8012C658 (s32,s32,s32), func_8012B2CC (s32);
 * banked-DEFINITION forms for func_80029504 (s32(void)), func_8001D0E8
 * (void(s32,s32,s32)) and func_8001C97C (void(s32*) - the def wins over the
 * x41 fleet `s32` spelling).  Data externs are in their rawest form (law 4);
 * the only aggregate is the stride-8 record the two s16 fill loops walk.
 */

#include "common.h"

/* ---- callees (fleet-modal / banked-definition spellings; the destination TU
        src/md_SC07_003/md_SC07_003.c declares none of these) ---- */
extern s32  rand(void);
extern s32  func_80029504(void);
extern void func_8012CAE4(void *);
extern s32  func_8012C354(s32, s32);
extern void func_8001D0E8(s32, s32, s32);
extern void func_8012A828(s32, void *);
extern void func_8012B2CC(s32);
extern void func_8012E8A8(u8 *);
extern s32  func_8012C588(s32, s32);
extern s32  func_8012C658(s32, s32, s32);
extern void func_8001C97C(s32 *);
extern void func_801A2E20(void);

/* ---- data ---- */
extern u8  D_801A6874[];   /* passed by address to func_8012C354 */
extern u8  D_801A6854[];   /* address OR'd with 0x50000000 into arg0+0x58 */
extern u8  D_801F0008[];
extern u8  D_801A68A8[];

extern s32 D_801F4360[];   /* 3 x s32, rand()&0x7FFF                     */
extern s32 D_801AE21C[];   /* s32 source table                           */
extern s32 D_801AE228[];   /* == &D_801AE21C[3] but its own symbol       */
extern s32 D_801F436C[];   /* s32 destination table                      */

/* stride-8 records; only the s16 at +0 is touched here */
typedef struct {
    /* 0x0 */ s16 a;
    /* 0x2 */ s16 b;
    /* 0x4 */ s32 c;
} Rec8_801A026C;

extern Rec8_801A026C D_801F1344[];
extern Rec8_801A026C D_801F1A5C[];

extern s32 D_801F4358;
extern s32 D_801F43B4;
extern s32 D_801F43B8;
extern s32 D_801F43BC;
extern u16 D_801F43C0;

void func_801A026C(s32 arg0)
{
    s32 i;
    s32 j;
    s32 k;

    if ((u32)func_80029504() >= 0x640) {
        func_8012CAE4((void *)arg0);
        return;
    }

    if (func_8012C354(arg0, (s32)D_801A6874) == 0) {
        return;
    }

    func_8001D0E8(*(s32 *)(arg0 + 0x20), 0x7FFF, 0x7FFF);

    *(s32 *)(arg0 + 0x58) = (s32)((u32)D_801A6854 | 0x10000000 | 0x40000000);
    func_8012A828(arg0, (void *)D_801F0008);

    *(s16 *)(arg0 + 0x02) = 1;
    *(s32 *)(arg0 + 0x48) = 0x30000;
    *(s32 *)(arg0 + 0x08) += 0xFD8A0000;
    func_8012B2CC(arg0);
    func_8012E8A8((u8 *)arg0);

    *(s16 *)(arg0 + 0xAE) = -1;
    *(s8 *)(arg0 + 0x75) = 2;
    *(s16 *)(arg0 + 0x76) = *(u16 *)(*(s32 *)(arg0 + 0x78));
    *(s32 *)(arg0 + 0xE4) = 0x50;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) |= 0x80;
    *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x80) = (s32)D_801A68A8;

    *(s32 *)(arg0 + 0xCC) = func_8012C588(0x34C, arg0);
    *(s32 *)(arg0 + 0xD0) = func_8012C588(0x351, arg0);
    *(s32 *)(arg0 + 0xD4) = func_8012C658(0x34C, 2, arg0);
    *(s32 *)(arg0 + 0xD8) = func_8012C588(0x3AB, arg0);

    for (i = 0; i < 3; i++) {
        D_801F4360[i] = rand() & 0x7FFF;
    }

    for (i = 62; i < 113; i++) {
        D_801F1344[i].a = 2;
    }

    for (i = 52; i < 140; i++) {
        D_801F1A5C[i].a = 2;
    }

    i = 0;
    k = 0;
    j = 0;
    for (; i < 20; i++) {
        if ((i != 0) && (i != 3)) {
            *(s32 *)((u8 *)D_801F436C + j) = *(s32 *)((u8 *)D_801AE21C + k);
            j += 4;
        }
        k += 4;
    }

    func_8001C97C(D_801F436C);

    D_801F43BC = 0;
    D_801F4358 = 0;
    D_801F43C0 = 3;
    D_801F43B4 = D_801AE228[0];
    D_801F43B8 = D_801AE21C[0];

    func_801A2E20();
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A04D4);

#include "common.h"

extern s32  func_801789AC(void);
extern void func_80178D18();
extern void func_8017BF08(void *, void *, s32, s32);
extern void func_8012C218(void *);
extern s32  func_8012C194(void);
extern void func_800233CC(void *, u16);
extern void func_8001CD9C(s32, void *);
extern void func_8012A568(void *);
extern void func_8017F004(void);

extern s32 D_801F4358;
extern s32 D_801F4318;
extern s32 D_801F431C;
extern s32 D_801F4320;
extern s32 D_801F4324;

void func_801A0524(s32 a0) {
    s32 s0;
    s32 *p;

    s0 = a0;
    if (func_801789AC() == 1) {
        func_80178D18(s0);
        func_8017BF08((void *)(s0 + 0x76), (void *)*(s32 *)(s0 + 0x78), 0xA, 0x120);
        *(s16 *)(s0 + 2) = 3;
        func_8012C218(*(void **)(s0 + 0xD8));
        *(s32 *)(s0 + 0xD8) = 0;
        D_801F4358 = func_8012C194();
        if (D_801F4358 != 0) {
            p = &D_801F4318;
            *p = 0;
            D_801F431C = 0;
            D_801F4320 = 0;
            D_801F4324 = 0;
            func_800233CC(p, 0x60);
            func_8001CD9C(D_801F4358, p);
            *(u16 *)(D_801F4358 + 0x2C) = 0xC010;
            *(s32 *)(D_801F4358 + 4) |= 0x50000000;
        }
        func_8012A568(func_8017F004);
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801F0008[];

void func_801A060C(s32 arg0) {
    *(s16 *)(arg0 + 0x02) = 4;
    *(s32 *)(arg0 + 0x1C) = 0x40;
    *(s32 *)(arg0 + 0xE4) = 0x50;
    func_8012A828(arg0, D_801F0008);
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012BD14(s32);

void func_801A0648(s32 arg0) {
    if (func_8012BEE8(arg0) != 0) {
        *(s16 *)(arg0 + 2) = 7;
    }
    if (*(s32 *)(arg0 + 0x1C) < 0x20) {
        if (((s32 (*)(s32))func_8012BD14)(arg0) <= 0x10000) {
            *(s16 *)(arg0 + 2) = 0xF;
        }
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801F0008[];

void func_801A06AC(s32 arg0) {
    *(s16 *)(arg0 + 0x02) = 6;
    *(s32 *)(arg0 + 0x1C) = 0x14;
    *(s32 *)(arg0 + 0xE4) = 0x50;
    func_8012A828(arg0, D_801F0008);
}


extern s32 func_8012BEE8(s32 a0);

void func_801A06E8(s32 arg0) {
    if (func_8012BEE8(arg0) != 0) {
        *(s16 *)(arg0 + 2) = 7;
        *(s32 *)(arg0 + 0xE0) &= ~0x40;
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A072C);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A079C);

extern void func_801A28AC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 rand(void);
extern u16 D_801F1EC0[];

void func_801A0940(void *a0) {
    s32 d;

    func_801A28AC((s32)a0);
    *(s16 *)((s32)a0 + 0x2) = 0xA;
    *(s32 *)((s32)a0 + 0xE4) = 0x50;
    *(u16 *)((s32)a0 + 0x34) = 0;
    func_8012A828((s32)a0, D_801F1EC0);
    d = rand();
    *(s32 *)((s32)a0 + 0x1C) = d % 64 + 0x40;
    *(s32 *)((s32)a0 + 0xE0) &= ~8;
}


INCLUDE_RODATA("asm/md_SC07_003/nonmatchings/md_SC07_003", D_801A00D8);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A09C8);

extern void func_801A28AC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80184C70(void);
extern void func_80184DB0(s32 a0, void *a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_801A6544[];
extern s32 D_801A6B90;

void func_801A0DA4(void *a0) {
    func_801A28AC((s32)a0);
    *(s16 *)((s32)a0 + 2) = 0xC;
    *(u16 *)((s32)a0 + 0x34) = 0;
    *(s32 *)((s32)a0 + 0xE4) = 0x50;
    func_8012A828((s32)a0, D_801A6544);
    func_80184C70();
    func_80184DB0(0, &D_801A6B90, -8);
    *(s32 *)((s32)a0 + 0xE0) &= ~0x4;
    func_8002D4C8(0xC35, 0);
}


#include "common.h"

/* 8-byte, 2-byte-aligned vector triple (the lwl/lwr/swl/swr block move at the tail
   proves alignment 2 and size 8).  Fields are u16 because every read site uses `lhu`;
   the two negative literals are written through an s16 alias so the constant stays
   signed (`addiu $v0,$zero,-0x180`) instead of becoming `ori 0xFE80`. */
typedef struct {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
} Vec8_801A0E28;

extern u16 D_801F43C0;
extern u8 D_801A68D4[];
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801F4310[];
extern u16 D_801F4312;
extern u16 D_801F4314;

extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012BD14(s32 a0);
extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern s32 func_8012BA10(s32 a0, s32 a1);
extern void func_80184E20(void *a0);
extern void func_80184E98();
extern void func_8018503C(void);
extern s32 func_801A3054(s32 a0, s32 a1, s32 a2);

void func_801A0E28(s32 a0) {
    s32 s1 = a0;
    s32 sp10[8];                /* 0x10: 32-byte matrix */
    Vec8_801A0E28 sp30;         /* 0x30 */
    u16 sp38[8];                /* 0x38: 16 bytes, fields at +2/+6/+10 */
    struct {
        u16 f0;                 /* 0x48 */
        u16 f2;
        u16 f4;
        u16 f6;
        u16 f8;
        u16 fA;
        u16 fC;
        u16 fE;
        s32 f10;                /* 0x58 */
    } sp48;                     /* 20 bytes -> 24 of frame (S54 law 24) */
    s32 st;

    if (*(s32 *)(s1 + 0x94) < 0x23) {
        s32 r = func_8012BA10(s1, 8);
        s32 p = *(s32 *)(s1 + 0x20);
        s32 k = D_801F43C0;

        *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + r;
        func_8012EC04(s1, k, sp10);
        func_8012F14C((s32)sp10, (s32)D_801A68D4, (s32)&sp30);
        sp38[1] = sp30.a;
        sp38[3] = sp30.b;
        sp38[5] = sp30.c;
        func_80184E20(sp38);
        if ((*(s32 *)(s1 + 0x94) & 1) == 0) {
            func_80184E98(rand() & 0xFF0, 0x40);
        }
        func_8018503C();
    }

    st = *(s32 *)(s1 + 0x94);
    if (st == 0x23) {
        if (((s32 (*)(s32))func_8012BD14)(s1) > 0x23FFF) {
            sp30.a = sp30.b = 0;
            *(s16 *)&sp30.c = -0x180;
            func_8012F214(s1, (s32)&sp30, (s32)&sp30);
            if (func_801A3054(s1, (s32)&sp30, 0x200) != 0) {
                D_801F4310[0] = D_80126B5E;
                D_801F4312 = D_80126B62;
                D_801F4314 = D_80126B66;
            } else {
                /* S54 law 22 (S193-C): the shared tail is written in BOTH arms so
                   cross_jump merges the scheduled common suffix, leaving each arm's
                   own `$a1` setup ($s0 copy vs a fresh addiu) above the merge point. */
                sp30.a = sp30.b = 0;
                *(s16 *)&sp30.c = -0x200;
                func_8012F214(s1, (s32)&sp30, (s32)&sp30);
                *(Vec8_801A0E28 *)D_801F4310 = sp30;
            }
        } else {
            sp30.a = sp30.b = 0;
            *(s16 *)&sp30.c = -0x200;
            func_8012F214(s1, (s32)&sp30, (s32)&sp30);
            *(Vec8_801A0E28 *)D_801F4310 = sp30;
        }
        st = *(s32 *)(s1 + 0x94);
    }

    if (st == 0x2F || st == 0x40 || st == 0x51) {
        func_8012EC04(s1, D_801F43C0, sp10);
        func_8012F14C((s32)sp10, (s32)D_801A68D4, (s32)&sp30);
        sp48.f0 = sp30.a;
        sp48.f2 = sp30.b;
        sp48.f4 = sp30.c;
        sp48.f6 = 0x378;
        sp48.f8 = sp48.fA = 0;
        sp48.fE = sp48.f10 = 0;
        sp48.fC = 0x7FFF;
        func_8012C51C(&sp48, s1);
        sp48.f8 = 0x8000;
        func_8012C51C(&sp48, s1);
        *(s32 *)(s1 + 0xE0) |= 4;
        func_8002D4C8(0xB54, 0);
    }

    if (*(s16 *)(s1 + 0x98) == 0) {
        *(s16 *)(s1 + 2) = 0x13;
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A10B0);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A1120);

extern void func_801A28AC();
extern s32 func_8012BA10(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801F1898[];
extern u8 D_801F1978[];
extern s16 D_801F435C;
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801A13A0(s32 arg0) {
    s32 s0 = arg0;

    func_801A28AC(s0);
    *(s16 *)(s0 + 2) = 0x10;
    *(s16 *)(s0 + 0x34) = 0;
    *(s32 *)(s0 + 0xE4) = 0x50;
    if (func_8012BA10(s0, 1) < 0) {
        func_8012A828(s0, D_801F1898);
        D_801F435C = 1;
    } else {
        func_8012A828(s0, D_801F1978);
        D_801F435C = -1;
    }
    *(s32 *)(s0 + 0xE0) |= 2;
    func_8002D4C8(0xB56, 0);
}


#include "common.h"

extern s32 rand(void);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s16 D_801F435C;

/* PsyQ VECTOR (16 bytes: vx, vy, vz, pad) */
typedef struct {
    s32 vx, vy, vz, pad;
} Vec801A143C;

/* the 20-byte spawn descriptor handed to func_8012C51C */
typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
} Spawn801A143C;

void func_801A143C(s32 a0) {
    Vec801A143C vin;
    Vec801A143C vout;
    Spawn801A143C stk;
    s32 i;
    s32 pick;
    s32 obj;
    register s32 t __asm__("$16");
    s32 r;

    if (*(s32 *)(a0 + 0x94) == 4) {
        /* This is `x += D * -112` written as explicit shift-arithmetic ON PURPOSE.
           Spelled `D_801F435C * -112`, expmed.c:2192 takes the negate_variant
           (synth_mult on +112 -> `(D<<3) - D`, then a NEG) and combine folds the NEG
           into the `+=`, giving `sll 3 / subu D8,D / sll 4 / SUBU` -- the target has
           `sll 3 / subu D,D8 / sll 4 / ADDU`, i.e. the negative chain built directly. */
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += (D_801F435C - D_801F435C * 8) * 16;
    }

    if ((u32)(*(s32 *)(a0 + 0x94) - 7) < 0x12) {
        /* 240 == ((x << 4) - x) << 4 */
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += D_801F435C * 240;
        pick = rand() % 8;

        vin.vy = 0;
        vin.vz = 0x400000;
        for (i = 0; i < 8; i++, vin.vz += 0x400000) {
            obj = func_80132EF4(a0, 0x22);
            if (obj == 0) {
                continue;
            }
            /* The $16 pin on `t` is load-bearing (LENGTH-DRIFT +1 without it).
               expand_divmod's internal `t1 = copy_to_mode_reg(op0)` (expmed.c:2986)
               spans basic blocks, so global_alloc owns it and -- crossing 0 calls --
               prefers a call-clobbered reg, taking $v0 and forcing the rand() result
               into $v1 via an extra `move`, which also leaves the bgez delay slot a
               nop.  Pinning the result variable to $16 makes t1/quotient/t3/remainder
               all land on $16, op0 stays in the raw return reg $v0, and the surviving
               `t1 = op0` copy fills the delay slot exactly as the target does. */
            t = (rand() % 64) << 16;
            if ((rand() & 1) == 0) {
                t = -t;
            }
            vin.vx = t;
            func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, (s32)&vin, (s32)&vout);

            *(s32 *)(obj + 0x4) += vout.vx;
            *(s32 *)(obj + 0x8) += vout.vy;
            *(s32 *)(obj + 0xC) += vout.vz;

            r = rand();
            *(u16 *)(obj + 0x34) = (((r % 8192) + 0x5000) & ~0xF) | (rand() & 1);
            *(u16 *)(*(s32 *)(obj + 0x20) + 0x2C) = 0xC004;

            if (pick != i) {
                continue;
            }

            stk.f0 = (*(s32 *)(a0 + 0x4) + vout.vx) >> 16;
            stk.f2 = (*(s32 *)(a0 + 0x8) + vout.vy) >> 16;
            stk.f4 = (*(s32 *)(a0 + 0xC) + vout.vz) >> 16;
            stk.f6 = 0x376;
            stk.f8 = 0;
            stk.fA = 0;
            stk.f10 = 0;
            stk.fE = 0;
            stk.fC = 0x7FFF;
            func_8012C51C(&stk, a0);
        }
    }

    if (*(s16 *)(a0 + 0x98) == 0) {
        *(s16 *)(a0 + 0x2) = 3;
        *(s32 *)(a0 + 0xE0) &= ~2;
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A16BC);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A1724);

#include "common.h"

typedef struct {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
} Vec8_801A1924;

extern u8  D_801A68FC[];
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 D_80126B78[];

extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  func_8012B70C(s16 *a0, s16 *a1);

void func_801A1924(s32 arg0) {
    s32 sp10[8];                /* 0x10 */
    Vec8_801A1924 sp30;         /* 0x30 */
    u16 sp38[4];                /* 0x38 */

    func_8012EC04(arg0, 0x10, sp10);
    func_8012F14C((s32)sp10, (s32)D_801A68FC, (s32)&sp30);
    func_8012F14C((s32)sp10, (s32)(D_801A68FC + 8), (s32)sp38);
    D_80126B5E = sp30.a;
    D_80126B62 = sp30.b;
    D_80126B66 = sp30.c;
    *(s16 *)(*(s32 *)D_80126B78 + 0x12) = func_8012B70C((s16 *)sp38, (s16 *)&sp30);
}


#include "common.h"

/*
 * func_801A19C8  (md_SC07_003, 0x801A19C8, 65 ins)  ==  MATCH, byte-exact.
 *
 * "Can this actor be locked on?"  Gate on the global u16 flag D_80126B94's
 * 0x8000 bit; then for each of the two candidate ids in D_801A6B94[] build a
 * screen-space test out of the 16-byte descriptor D_801A68FC[i] and ask
 * func_80013478 for a distance.  First candidate under 0x4001 wins: pop the
 * indicator (func_8012F568), latch the actor in D_80127078, return 1.
 *
 * ---------------------------------------------------------------------------
 * RESIDUAL CLASS SOLVED: GIV-fusion-over-reduction (combine_givs mult+symbol-base).
 *
 * The first-pass draft was NEAR/53 at 64 ins.  Its loop strength-reduced the
 * &D_801A68FC[i*0x10] address into an accumulating pointer ($sN += 16) where
 * the target re-materialises  sll/lui/addiu/addu  every iteration.  The whole
 * residual is decided by loop.c arithmetic, and all three levers below are
 * that one arithmetic statement:
 *
 *      move_movables admits a movable iff  threshold * savings * lifetime >= insn_count
 *        (loop.c:1631; threshold = (loop_has_call?1:2)*(1+n_non_fixed_regs) = 29,
 *         and  threshold -= 3  after EVERY hoist, loop.c:1719/1904)
 *
 * The `la D_801A68FC` movable has savings 1 and lifetime 1, so its product is
 * just the current threshold.  If it is hoisted, the symbol lands in an
 * invariant pseudo, `(plus (ashift i 4) (that pseudo))` becomes a giv with
 * add_val = a register, combine_givs merges it with the bare i<<4 giv, the
 * merged benefit clears 0, and it strength-reduces.  Un-hoisted, the symbol
 * pseudo is set INSIDE the loop, invariant_p says no, the plus is not a giv at
 * all, and the lone i<<4 giv carries benefit 2 - add_cost*biv_count = 0 =>
 * "not worth while" (loop.c:3823, cookbook s164-67's n=1 floor).  So the whole
 * job is to push the threshold under insn_count BEFORE that movable is reached.
 *
 *  LEVER 1 - `D_801A6B94[i]`, NOT a walking `u16 *p`.
 *      A source pointer biv makes the D_801A6B94 base an insn-29 biv init and
 *      costs the loop one `addiu p,p,2`; insn_count stays 25 and the la is
 *      movable #1 at threshold 29 (29 >= 25 => hoisted).  Array indexing turns
 *      it into an ADDRESS giv whose add_val is the SYMBOL_REF itself, so
 *      emit_iv_add_mult(symbol + 0*2) puts `la $s1,D_801A6B94` in the
 *      preheader's THIRD stratum (cookbook s190-A) - which is exactly where the
 *      target has it, AFTER the hoisted `addiu $s2,$sp,0x38` - and it raises
 *      insn_count 25 -> 27.
 *
 *  LEVER 2 - `u16 *o = out;` as the FIRST statement of the loop body.
 *      Naming a stack address forces a pseudo that scan_loop can record
 *      (cookbook s164-35: written inline at a call site there is no insn to
 *      move).  Body order is movable-list order, so this becomes movable #1 and
 *      spends the first `threshold -= 3` (29 -> 26).  `buf` is deliberately
 *      left UNNAMED: the target recomputes `addiu $a2,$sp,0x18` twice inside
 *      the loop, so it must stay inline.  With levers 1+2 the D_801A68FC la is
 *      movable #3 at threshold 23 < insn_count 27 and cc1 -dL prints
 *      "Insn 64: regno 87 (life 1), move-insn savings 1 not desirable".
 *
 *  LEVER 3 - `s32 *m = &D_80126B58;` declared ABOVE the flag test.
 *      The target computes `lui/addiu $s4,D_80126B58` in the ENTRY block -
 *      before the `bnez` - and then spells the argument `addiu $a0,$s4,4`.
 *      loop.c can only hoist as far as the preheader (after the branch), so
 *      this cannot be invariant motion: it is source position.  A pointer local
 *      initialised before the `if` leaves `(set p (symbol_ref))` in the entry
 *      block; cse cannot fold it into the loop because the loop body starts a
 *      fresh extended basic block, so `m + 1` survives as a register + 4.
 *      Writing `(s32)&D_80126B58 + 4` inline instead folds to one CONST and
 *      emits `lui/addiu` INSIDE the loop - that was the last 3 instructions
 *      (2 in-loop la, plus the missing sw/lw $s4 pair) of the -1/-3 drift.
 *
 * Declarations: none of these symbols is declared in md_SC07_003.c, and every
 * spelling below matches the sibling drafts already staged for this TU
 * (extern s32 D_80126B58; extern u8 D_801152A8[]; extern u16 D_801A6B94[]).
 */

extern u16 D_80126B94;
extern s32 D_80126B58;
extern u16 D_801A6B94[];
extern u8  D_801A68FC[];
extern u8  D_801152A8[];
extern s32 D_80127078;

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32  func_80013478(s32 a0, s32 a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_801A19C8(s32 arg0) {
    s32 buf[8];   /* 0x18(sp) - scratch handed to func_8012EC04/func_8012F14C */
    u16 out[4];   /* 0x38(sp) - the projected point both later calls read      */
    s32 i;
    s32 *m = &D_80126B58;   /* LEVER 3: entry-block `la`, used as m+1 == +4 */

    if (!(D_80126B94 & 0x8000)) {
        return 0;
    }

    for (i = 0; i < 2; i++) {
        u16 *o = out;       /* LEVER 2: first movable, eats threshold 29 -> 26 */
        func_8012EC04(arg0, D_801A6B94[i], buf);            /* LEVER 1 */
        func_8012F14C((s32)buf, (s32)&D_801A68FC[i * 0x10], (s32)o);
        if (func_80013478((s32)(m + 1), (s32)o) < 0x4001) {
            func_8012F568(1, 0x401C,
                *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) & 0xFFF, 0x50,
                (s32)o, (s32)D_801152A8);
            D_80127078 = arg0;
            return 1;
        }
    }
    return 0;
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A1ACC);

#include "common.h"

/* func_801A1B28 — md_SC07_003 entity update (fresh mass-lane crack, no banked twin).
 *
 * arg0 is the standard 0x10C-ish entity record:
 *   +0x02 s16 state/anim id      +0x1C s32 tick counter
 *   +0x20 s32 -> render object (its +0x34 is a MATRIX, its +0x2C a u16 gpu code)
 *   +0x34 u16 "done" counter     +0x72 u16 flag word   +0x76 s16 hp-ish
 *   +0x90 s32 script ptr         +0x94 s32 script sub-state
 *   +0x98 s16 busy flag          +0xD8 s32 -> u16-tagged record
 *   +0xE0 s32 flag word          +0xE8/+0xEC s32
 *
 * Stack (frame 0x58 = 0x10 outgoing args + 0x38 locals + 0x10 saves):
 *   sp+0x10 MATRIX mtx (0x20)   sp+0x30 SVECTOR sv (0x08)   sp+0x38 VECTOR vec (0x10)
 */

typedef struct { s16 m[3][3]; s32 t[3]; } MTX_801A1B28;   /* 0x20 */
typedef struct { u16 vx, vy, vz, pad; } SV_801A1B28;      /* 0x08 */
typedef struct { s32 vx, vy, vz, pad; } VEC_801A1B28;     /* 0x10 */

extern s32 func_8012E544(s32 a0);
extern s32 func_8017F2D8(void);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 RotMatrixX(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);

extern u8 D_801A63FC[];
extern u16 D_801F43C0;
extern u8 D_801A68DC[];
extern u8 D_801A6504[];

void func_801A1B28(s32 arg0) {
    MTX_801A1B28 mtx;
    SV_801A1B28 sv;
    VEC_801A1B28 vec;
    s32 obj;
    s32 p;

    if (*(s32 *)(arg0 + 0xE0) & 0x10) {
        if (func_8012E544(0x352) == 0) {
            func_8017F2D8();
            *(s32 *)(arg0 + 0xE0) &= ~0x10;
        }
    }

    if (*(s32 *)(arg0 + 0xE0) & 0x21) {
        if (*(s16 *)(arg0 + 0x76) <= 0) {
            *(s16 *)(arg0 + 0x2) = 0x17;
        } else {
            *(s16 *)(arg0 + 0x2) = 0x15;
        }
        return;
    }

    if (*(u16 *)(arg0 + 0x34) == 0) {
        if (*(u16 *)(arg0 + 0x72) & 0x4000) {
            *(s32 *)(arg0 + 0x1C) += 1;
        }
        if (*(s32 *)(arg0 + 0x90) == (s32)D_801A63FC && *(s32 *)(arg0 + 0x94) == 0) {
            obj = func_80132EF4(arg0, 0x22);
            if (obj != 0) {
                func_8012EC04(arg0, D_801F43C0, (s32 *)&mtx);
                func_8012F14C((s32)&mtx, (s32)D_801A68DC, (s32)&sv);
                *(u16 *)(obj + 0x6) = sv.vx;
                *(u16 *)(obj + 0xA) = sv.vy + 0x20;
                *(u16 *)(obj + 0xE) = sv.vz;
                *(s16 *)(obj + 0x34) = 0x6000;
                *(u16 *)(*(s32 *)(obj + 0x20) + 0x2C) = 0xC010;
                mtx = *(MTX_801A1B28 *)(*(s32 *)(arg0 + 0x20) + 0x34);
                vec.vy = 0;
                vec.vx = 0;
                vec.vz = -0xC0000;
                RotMatrixX(0x200, &mtx);
                func_800484EC((s32)&mtx, (s32)&vec, obj + 0x10);
            }
            func_8002D4C8(0xB9C, 0);
        }
        if (*(s32 *)(arg0 + 0x1C) >= 4) {
            func_8012A828(arg0, D_801A6504);
            *(u16 *)(arg0 + 0x34) += 1;
        }
    } else {
        if (*(s16 *)(arg0 + 0x98) == 0) {
            *(s16 *)(arg0 + 0x2) = 3;
            *(s32 *)(arg0 + 0xEC) = 0x10000;
            *(s32 *)(arg0 + 0xE8) = 0;
            *(s32 *)(arg0 + 0xE0) |= 0x100;
            p = *(s32 *)(arg0 + 0xD8);
            if (p != 0) {
                if (*(u16 *)p != 0) {
                    func_8012C218((void *)p);
                }
            }
        }
    }
}


extern void func_801A28AC(s32);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);

extern u8 D_801F0798[];
extern u8 D_801F0840[];

void func_801A1D94(void *arg0) {
    s32 s0 = (s32)arg0;

    ((void (*)(void *))func_801A28AC)(arg0);
    if (*(u32 *)(s0 + 0xE0) & 1) {
        func_8012A828(s0, D_801F0798);
        *(u16 *)(s0 + 0x34) = 0;
    } else {
        func_8012A828(s0, D_801F0840);
        *(u16 *)(s0 + 0x34) = 1;
        func_8012B178(s0, 0x30000);
    }
    *(u16 *)(s0 + 2) = 0x16;
    *(s32 *)(s0 + 0xE4) = 0x30;
    *(s32 *)(s0 + 0xE0) = *(u32 *)(s0 + 0xE0) | 0x40;
    *(s32 *)(s0 + 0x1C) = 0x10;
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012ADE4(u8 *a0);
extern void func_8012CBA4(s32 a0); /* canonical void; return read via fn-ptr cast */
extern s32 func_8012E544(s32 a0);
extern s32 func_8017F2D8(void);
extern void func_801A24E8(s32 a0);

void func_801A1E30(s32 a0) {
    s32 v1;

    if (*(u32 *)(a0 + 0xE0) & 0x10) {
        if (func_8012E544(0x352) == 0) {
            func_8017F2D8();
            *(u32 *)(a0 + 0xE0) &= ~0x10;
        }
    }

    if (*(u16 *)(a0 + 0x34) != 0) {
        v1 = *(s32 *)(a0 + 0x94);
        if ((u32)v1 < 0x33) {
            if (v1 == 0x18) {
                func_8002D4C8(0xC34, 0);
            }
            if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) == 0) {
                func_8012ADE4((u8 *)a0);
            }
            func_801A24E8(a0);
        }
    }

    if (*(s16 *)(a0 + 0x98) == 0) {
        if (*(u32 *)(a0 + 0xE0) & 0x20) {
            *(u32 *)(a0 + 0xE8) = 0;
            *(u32 *)(a0 + 0xEC) = 0x10000;
            *(u32 *)(a0 + 0xE0) |= 0x100;
        }
        *(s16 *)(a0 + 2) = 5;
        *(u32 *)(a0 + 0xE0) &= ~0x21;
    }
}


#include "common.h"

extern void func_80016714(s8 *a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern s32 func_80178B18(s32 a0, s32 a1);
extern void func_8017C068(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern s16 D_801A6964;
extern s16 D_801A6966;
extern s16 D_801A6968;
extern s16 D_801A696C;
extern s16 D_801A6AE4;
extern u8 D_801F1A58[];
extern s32 D_801F4358;

void func_801A1F38(s32 arg0) {
    s32 s0 = arg0;

    D_801A6964 = 0;
    D_801A6966 = -0x90;
    D_801A6968 = 0;

    D_801A696C = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF;

    func_80178B18((s32)s0, (s32)&D_801A6AE4);

    *(s16 *)(s0 + 0x2) = 0x18;
    *(s16 *)(s0 + 0x34) = 0;
    *(s16 *)(s0 + 0x98) = 0;
    *(s32 *)(s0 + 0x1C) = 0;
    *(s32 *)(s0 + 0xE4) = 0x10000;
    func_8017C068();

    func_8012A828((s32)s0, D_801F1A58);
    func_8012B178((s32)s0, 0x30000);
    func_800D0C48(1);
    func_8002D4C8(0xC73, 0);

    if (D_801F4358 != 0) {
        func_80016714((s8 *)D_801F4358, 0x38);
        D_801F4358 = 0;
    }
}


/* func_801A2014  (md_SC07_003, 154 ins) -- MATCH, fresh crack from the .s.
 *
 * BANKING NOTES (the destination TU src/md_SC07_003/md_SC07_003.c is 100% INCLUDE_ASM,
 * so it declares NOTHING; every spelling below is the fleet-modal one from the card's
 * decl_prior EXCEPT where marked):
 *   - func_8012CBA4  RECONCILED (slate lane, S54): originally declared with the rival
 *     ('s32',('s32',)) spelling because this call site CONSUMES the return
 *     ("andi $v0,$v0,0x2000" right after the jal). That clashed with func_801A1E30 in the
 *     same TU, which uses the canonical ('void',('s32',)) def + the tree's fn-ptr-cast
 *     idiom. Adopted the canonical void extern here too and routed the return through
 *     ((s32 (*)(s32))func_8012CBA4)(...) at the call -- re-verified MATCH, byte-neutral.
 *   - func_80178970 / func_80178D18 / func_80181A00: declared with UNSPECIFIED parameter
 *     lists "()" on purpose. The first two are defined ('s32',()) / ('void',()) yet this
 *     site passes $a0; func_80181A00 is defined ('s32',('u8','u8','u8','u8')) yet this
 *     site passes NO arguments (the "jal func_80181A00" has a bare nop delay slot).
 *     Adopting either prototype makes this TU fail to compile -- keep "()" (STEP 0c: an
 *     unspecified list is compatible with any prototype in C89 and is never a conflict).
 *   - D_801A6BB8 / D_801A6BBE are the two splat symbols the target's own relocations name
 *     (the table is really one 8-byte-stride SVECTOR-ish array; splat split it at +6
 *     because both halves carry their own %hi).
 *   - RotTransSV uses the src/shared/engine_core.h spelling ('void',('s32','s32','void*')).
 */
#include "common.h"

/* --- PsyQ inline GTE macros (copied verbatim from the banked
 *     src/ov_SC06_008/ov_SC06_008_jr_8017C294.c spelling) ------------------ */
#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern s32  func_8004787C(s32 a0);
extern s32  func_80047948(s32 a0);
extern void func_8012CBA4(s32 a0); /* canonical void; return read via fn-ptr cast */
extern void func_8012ADE4(u8 *a0);
extern s32  func_8012C51C(void *a0, s32 a1);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern s32  func_80132EF4(s32 a0, s32 a1);
extern s32  func_80178970();
extern void func_80178D18();
extern s32  func_80181A00();
extern void func_801A227C();
extern void func_801A24E8(s32 a0);

extern u8  D_801A6BB8[];
extern u16 D_801A6BBE[];

typedef struct Prim801A2014 {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 f06;
    /* 0x08 */ s16 f08;
    /* 0x0A */ s16 f0A;
    /* 0x0C */ s16 f0C;
    /* 0x0E */ s16 f0E;
    /* 0x10 */ s32 f10;
} Prim801A2014;   /* 0x14 bytes */

void func_801A2014(s32 p)
{
    Prim801A2014 prim;   /* sp+0x10 */
    u16 sv[4];           /* sp+0x28 */
    s32 m[8];            /* sp+0x30 */
    s32 flag;            /* sp+0x50 */
    s32 i;
    s32 off;

    switch (*(u16 *)(p + 0x34)) {
    case 0:
        if ((u32)*(s32 *)(p + 0x94) < 0x33) {
            if (((((s32 (*)(s32))func_8012CBA4)(p)) & 0x2000) == 0) {
                func_8012ADE4((u8 *)p);
            }
            func_801A24E8(p);
        }
        if ((u32)(*(s32 *)(p + 0x94) - 0x32) < 0x3D) {
            *(u16 *)(p + 0x50) += func_8004787C(*(s32 *)(p + 0x1C)) >> 9;
            *(u16 *)(p + 0x54) += func_80047948(*(s32 *)(p + 0x1C)) >> 9;
            *(s32 *)(p + 0x1C) += 0x400;
        }
        if (*(s32 *)(p + 0x94) == 0x6B) {
            func_8002D4C8(0xC8C, 0);
        }
        break;

    case 1:
        func_8012EC04(p, 4, m);
        gte_SetRotMatrix(m);
        gte_SetTransMatrix(m);
        for (i = 0; i < 16; i++) {
            off = i * 8;
            RotTransSV((s32)(D_801A6BB8 + off), (s32)sv, &flag);
            prim.x = sv[0];
            prim.y = sv[1];
            prim.z = sv[2];
            prim.f06 = 0x38A;
            prim.f08 = i;
            prim.f0A = 0;
            /* §190-B / sched1 LUID tie-break: the 0x0E / 0x10 / 0x0C stores must be
             * written in THIS order -- it is the only ordering of the nine field stores
             * that reproduces the target's sched1+sched2 interleave (see notes). */
            prim.f0E = *(u16 *)(*(s32 *)(p + 0x20) + 0x12) +
                       *(u16 *)((u8 *)D_801A6BBE + off);
            prim.f10 = 0;
            prim.f0C = 0x7FFF;
            func_8012C51C(&prim, p);
        }
        func_8002D4C8(0xB9E, 0);
        *(s16 *)(p + 0x34) = 3;
        break;

    case 2:
        *(s32 *)(p + 0xD8) = func_8012C588(0x380, p);
        func_80132EF4(p, 0x6E);
        *(s16 *)(p + 0x34) = 3;
        break;
    }

    if (func_80178970(p) == 1) {
        func_80178D18(p);
        func_801A227C(p);
        func_80029514(0x640);
        func_80181A00();
    }
}


extern void func_8012C218(void *a0);
extern void func_80016450(s32 a0, s32 a1);

void func_801A227C(void *arg0) {
    void *v0;
    if (*(void **)((u8 *)arg0 + 0xCC) != NULL) {
        func_8012C218(*(void **)((u8 *)arg0 + 0xCC));
    }
    if (*(void **)((u8 *)arg0 + 0xD0) != NULL) {
        func_8012C218(*(void **)((u8 *)arg0 + 0xD0));
    }
    if (*(void **)((u8 *)arg0 + 0xD4) != NULL) {
        func_8012C218(*(void **)((u8 *)arg0 + 0xD4));
    }
    v0 = *(void **)((u8 *)arg0 + 0xD8);
    if (v0 != NULL) {
        func_80016450(*(u8 *)((u8 *)v0 + 0xFC), 0);
        func_8012C218(*(void **)((u8 *)arg0 + 0xD8));
    }
    func_8012C218(arg0);
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD80(void);

s32 func_801A2318(s32 arg0) {
    s32 temp;

    temp = *(s32 *)(arg0 + 0xD8);
    ((void (*)(s32))func_8012AD80)(temp);

    if (--*(s32 *)(arg0 + 0xF8) == 0) {
        *(s32 *)(temp + 0x14) = 0x60000;
        func_8002D4C8(4, 0xC36);
        return 1;
    }
    return 0;
}




extern void func_8012AD80(void);
    s32 func_801A2384(s32 arg0) {
        ((void (*)(s32))func_8012AD80)(*(s32 *)(arg0 + 0xd8));
    }


extern void func_8012A828(s32 a0, void *a1);

void func_801A23A8(void *arg0) {
    func_8012A828((s32)arg0, *(void **)((s32)arg0 + 0xF8));
}


#include "common.h"

s32 func_801A23CC(s32 arg0) {
    if (*(s16 *)(arg0 + 0x98) == 0 || (*(u16 *)(arg0 + 0x72) & 0x4000)) {
        return 1;
    }
    return 0;
}


#include "common.h"

extern void func_8012CBCC(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_801A2658(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

extern u16 D_80186F44[];
extern u8  D_801A68BC[];

s32 func_801A23FC(s32 arg0) {
    s32 s1;
    s32 v;
    s32 p;

    s1 = 0;
    v = *(s32 *)(arg0 + 0xD0);
    if (v != 0) {
        s1 = v;
        *(u16 *)(*(s32 *)(s1 + 0x20) + 0x18) += 0x266;
        *(u16 *)(*(s32 *)(s1 + 0x20) + 0x1A) += 0x266;
    }

    if (((s32 (*)(s32))func_8012CBCC)(arg0) & 0x2000) {
        func_8013C9C4(D_80186F44);
        func_801A2658(arg0, (s32)D_801A68BC);
        func_801A2658(arg0, (s32)(D_801A68BC + 8));
        if (s1 != 0) {
            p = *(s32 *)(s1 + 0x20);
            *(u16 *)(p + 0x1A) = 0x3000;
            *(u16 *)(p + 0x18) = 0x3000;
        }
        *(s32 *)(arg0 + 0xE0) |= 4;
        func_8002D4C8(0xB52, 0);
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A24E8);

#include "common.h"

extern s32 D_801F1FD8;

extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern u8 *func_8012913C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_801A2658(s32 arg0, s32 arg1) {
    s32 buf[8];
    s16 vec[3];
    struct {
        s16 f0, f1, f2, f3, f4, f5, f6, f7;
        s32 f8;
    } eff;
    s32 i;
    u8 *ent;
    s32 delta;

    delta = *(s16 *)(arg1 + 0x6);
    if (*(s32 *)(arg0 + 0x90) == (s32)&D_801F1FD8) {
        delta -= 1;
    }
    func_8012EC04(arg0, delta, buf);
    func_8012F14C((s32)buf, arg1, (s32)vec);

    for (i = 0; i < 0x1000; i += 0x100) {
        ent = func_8012913C(0x22);
        if (ent != 0) {
            *(s16 *)(ent + 0x6) = vec[0];
            *(s16 *)(ent + 0xA) = vec[1];
            *(s16 *)(ent + 0xE) = vec[2];
            *(s32 *)(ent + 0x10) = func_80047948(i) * 320;
            *(s32 *)(ent + 0x18) = func_8004787C(i) * 320;
            *(s16 *)(ent + 0x34) = 0x4000;
            *(u16 *)(*(s32 *)(ent + 0x20) + 0x2C) = 0xC002;
        }
    }

    eff.f3 = 0x376;
    eff.f4 = 0;
    eff.f5 = 0;
    eff.f8 = 0;
    eff.f7 = 0;
    eff.f6 = 0x7FFF;
    eff.f0 = vec[0];
    eff.f1 = vec[1];
    eff.f2 = vec[2];

    for (i = 0; i < 8; i++) {
        func_8012C51C(&eff, arg0);
    }
}


#include "common.h"

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_801A27A4(void *a0, void *a1)
{
    s32 buf1[8];
    u16 pos[3];
    u8 *ent;
    s32 i;

    struct {
        u16 f0;
        u16 f2;
        u16 f4;
        u16 f6;
        u16 f8;
        u16 fA;
        u16 fC;
        u16 fE;
        s32 f10;
    } tmp;

    func_8012EC04((s32)a0, *(s16 *)((s32)a1 + 0x6), buf1);
    func_8012F14C((s32)buf1, (s32)a1, (s32)pos);

    ent = func_8012913C(0x22);

    if (ent != NULL) {
        *(u16 *)((s32)ent + 0x6)  = pos[0];
        *(u16 *)((s32)ent + 0xA)  = pos[1];
        *(u16 *)((s32)ent + 0xE)  = pos[2];
        *(s32 *)((s32)ent + 0x10) = -(*(s32 *)((s32)a0 + 0x10));
        *(s32 *)((s32)ent + 0x18) = -(*(s32 *)((s32)a0 + 0x18));
        *(u16 *)((s32)ent + 0x34) = 0x7001;
        *(u16 *)((s32)(*(s32 *)((s32)ent + 0x20)) + 0x2C) = 0xC002;
    }

    tmp.f0 = pos[0];
    tmp.f2 = pos[1];
    tmp.f4 = pos[2];
    tmp.f6 = 0x376;
    tmp.f8 = 0;
    tmp.fA = 0;
    tmp.f10 = 0;
    tmp.fE = 0;
    tmp.fC = 0x7FFF;

    for (i = 0; i < 2; i++) {
        func_8012C51C(&tmp, (s32)a0);
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A28AC);

s32 func_801A2918(s32 arg0) {
    register s32 r __asm__("$2");
    s32 p;
    r = 1;
    p = *(s32 *)(arg0 + 0xD8);
    if (p != 0) {
        r = *(s32 *)(p + 0xE0) != 0;
    }
    return r;
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A293C);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A2E20);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A2EC8);

extern void func_8017F578(void);
void func_801A3014(void) {
    func_8017F578();
}


extern void func_8017F004(void);
void func_801A3034(void) {
    func_8017F004();
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A3054);

extern void func_8018672C(int);
void func_801A30EC(void) {
    func_8018672C(0x9);
}


extern void func_80186758(void);
void func_801A310C(void) {
    func_80186758();
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A312C);



void func_801A3190(void *a0) {

    extern void (*D_801A6D8C[])(void);
    D_801A6D8C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A31CC);

#include "common.h"

extern void func_8012C218(void *a0);
extern void func_801A38E4(void *a0, void *a1, s32 a2, s32 a3, s32 a4);
extern void func_801A3BCC(void *a0);

extern u16 D_801F43C0;
extern u8 D_801A6DA4[4];

void func_801A3334(void *a0) {
    void *s1;      /* the actor          */
    void *s2;      /* linked actor @+0x64 */
    void *s3;      /* &s1->parts[0]  (+0xCC), strides 0x10 */
    s32 s4;        /* part-id bias: -2 when D_801F43C0 == 0x11 */
    s32 s5;
    s32 i;

    s1 = a0;
    s3 = (u8 *)s1 + 0xCC;
    s2 = *(void **)((u8 *)s1 + 0x64);
    s4 = 0;

    /* +0x00 is a u16 type tag; anything but 0x322 takes the generic path */
    if (*(u16 *)s2 != 0x322) {
        func_8012C218(a0);
        return;
    }

    if (D_801F43C0 == 0x11) {
        s4 = -2;
    }

    /* i = 0 must be the FIRST statement of the join block: reorg steals it into
       the bne's delay slot, leaving `s5 = 1` at .L801A339C (§194 delay-slot steal). */
    i = 0;
    s5 = 1;
    /* the s3 stride lives in the for-clause, AFTER i++ -- that ordering is what
       puts the a3/lbu group ahead of `a1 = s3` in sched1's arg setup. */
    for (; i < 3; i++, s3 = (u8 *)s3 + 0x10) {
        func_801A38E4(s2, s3, D_801A6DA4[i] + s4, i, s5);
    }

    /* unaligned (align-1) 8-byte copy: (*(s1+0x20))[+0x10] = (*(s2+0x20))[+0x10] */
    {
        typedef struct { u16 a, b, c, d; } Vec8;
        *(Vec8 *)((u8 *)*(u32 *)((u8 *)s1 + 0x20) + 0x10) =
            *(Vec8 *)((u8 *)*(u32 *)((u8 *)s2 + 0x20) + 0x10);
    }

    *(s32 *)((u8 *)s1 + 0x4) = *(s32 *)((u8 *)s2 + 0x4);
    *(s32 *)((u8 *)s1 + 0x8) = *(s32 *)((u8 *)s2 + 0x8);
    *(s32 *)((u8 *)s1 + 0xC) = *(s32 *)((u8 *)s2 + 0xC);

    if (*(s32 *)((u8 *)s2 + 0xE0) & 0x2) {
        *(u16 *)((u8 *)s1 + 0x5C) = *(u16 *)((u8 *)s1 + 0x5C) & 0xF7FF;
        func_801A3BCC(s1);
    } else {
        *(u16 *)((u8 *)s1 + 0x5C) = *(u16 *)((u8 *)s1 + 0x5C) | 0x0800;
    }
}


#include "common.h"

/* Sibling shape: src/shared/engine_types.h:1337 `struct S80190C84` (0x14-byte
 * spawn record: 8x s16 + trailing s32). Re-declared locally here since the
 * include path for src/shared/ isn't reachable from this standalone draft. */
struct S80190C84 {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
};

/* decl_prior (card func_801A3490): modal fleet spellings adopted verbatim. */
extern void func_8012E9C0(s32 a0);
extern void func_8002A520(s32 a0);
extern void func_8002A790(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012C218(void *a0);

/* No fleet data for these two (only referenced inside this TU, itself still
 * unmatched) -- typed by access width per law 2's fallback. Kept s32 (not
 * void*) so `p` never forms a pointer-typed value: a void* cast on the
 * cross-branch-live `p` forces gcc-2.7.2 to materialize a SECOND pseudo
 * (an extra callee-saved reg, observed as a stray `move $s2,$s0`). */
extern void func_801A38E4(void *a0, void *a1, s32 a2, s32 a3, s32 a4);
extern u16 D_801F43C0;

/* Sibling shape: an 8-byte, align-2 vector -- same idiom as func_80131340's
 * `struct V8` (lwl/lwr + swl/swr unaligned block move, cookbook S48-C2). */
struct V8 { u16 vx, vy, vz, pad; };

void func_801A3490(s32 p)
{
    s32 linked;
    s32 pCC;

    pCC = p + 0xCC;
    linked = *(s32 *)(p + 0x64);

    if (*(u16 *)(p + 0x5C) & 1) {
        s32 tbl;
        s32 dec;

        *(u16 *)(p + 0x60) = 0x280;
        func_8012E9C0(p);

        if (*(u16 *)(p + 0x5E) != 0x1D) {
            if (*(u8 *)(p + 0xC8)) func_8002A520(p);
            if (*(u8 *)(p + 0xC9)) func_8002A790(p);
        }

        tbl = *(s32 *)(p + 0x78);
        dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(tbl + 0x30)) >> 12;
        if (dec <= 0) {
            dec = 1;
        }

        {
            s16 t = *(u16 *)(linked + 0x76) - dec;
            *(s16 *)(linked + 0x76) = t;
            if (t < 0) {
                *(s16 *)(linked + 0x76) = 0;
            }
        }

        *(s32 *)(linked + 0xE0) |= 0x20;
        func_8002D4C8(0xB9F, 0);

        {
            struct S80190C84 sp;
            sp.f0 = *(u16 *)(p + 0x7C);
            sp.f2 = *(u16 *)(p + 0x7E);
            sp.f4 = *(u16 *)(p + 0x80);
            sp.f6 = 0x3D5;
            sp.fA = 0;
            sp.f8 = 0;
            sp.f10 = 0;
            sp.fE = 0;
            sp.fC = 0x7FFF;
            func_8012C51C(&sp, p);
        }

        func_8012C218((void *)p);
    } else {
        func_801A38E4((void *)linked, (void *)pCC, (s32)D_801F43C0, 3, 1);

        *(struct V8 *)(*(s32 *)(p + 0x20) + 0x10) =
            *(struct V8 *)(*(s32 *)(linked + 0x20) + 0x10);

        *(s32 *)(p + 4) = *(s32 *)(linked + 4);
        *(s32 *)(p + 8) = *(s32 *)(linked + 8);
        *(s32 *)(p + 0xC) = *(s32 *)(linked + 0xC);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801A43E8(void *a0);
extern void func_801A38E4(void *a0, void *a1, s32 a2, s32 a3, s32 a4);
extern u16 D_801F43C0;

/* Entity/effect-slot per-frame update. s1 = the linked slot *(s0+0x64).
 *
 * Clears the "just spawned" bit (0x5C bit0); if the entity has not already
 * latched a state (0x1C == 0) and the linked slot is neither timed-out
 * (*(s1+0xE8) <= 0xFFFF, signed) nor blocked ((*(s1+0xE0) & 0x140) == 0),
 * runs the setup callback func_801A43E8, re-tags the linked slot
 * (0x2 = 0x15, 0xE0 = (v|1) & ~2, 0x5C |= 0x800), latches this entity's own
 * state (0x1C = 0x14) and fires two sound/queue events via func_8002D4C8.
 * 0x5E is always cleared on the spawn frame.
 *
 * Then unconditionally forwards to func_801A38E4(slot, s0+0xCC, D_801F43C0,
 * 5, 1), copies an 8-byte align-1 block (lwl/lwr/swl/swr — cookbook §160a
 * Blk8) from *(s1+0x20)+0x10 to *(s0+0x20)+0x10, and mirrors the three s32
 * fields 0x4/0x8/0xC from the slot onto this entity.
 *
 * S54 second pass: the first draft's only residual was a 7-instruction
 * reorder around the 0xE0 / 0x5C read-modify-writes. It was NOT a hoist that
 * needed a fence — it was §190-B. The first draft wrote the 0x5C update
 * before the 0xE0 update; the target's interleave (lw 0xE0 and the -0x3
 * constant floating above the 0x2 store, the 0xE0 store sinking below the
 * 0x5C store, and -0x3 landing in $a2 rather than $v0) is exactly what sched1
 * produces from the PLAIN natural order 0x2 -> 0xE0 -> 0x5C -> 0x1C. Swapping
 * the two RMW statements back into that order matches byte-for-byte with no
 * fence, no pin and no temp.
 */
void func_801A3638(void *a0) {
    void *s0 = a0;
    void *s1;
    void *s2;
    u16 flags;

    s1 = *(void **)((u8 *)s0 + 0x64);
    func_8012BEE8((s32)s0);
    s2 = (u8 *)s0 + 0xCC;

    flags = *(u16 *)((u8 *)s0 + 0x5C);
    if (flags & 1) {
        *(u16 *)((u8 *)s0 + 0x5C) = flags & 0xFFFE;
        if (*(s32 *)((u8 *)s0 + 0x1C) == 0
            && *(s32 *)((u8 *)s1 + 0xE8) <= 0xFFFF
            && (*(s32 *)((u8 *)s1 + 0xE0) & 0x140) == 0) {
            func_801A43E8(s0);
            *(u16 *)((u8 *)s1 + 0x2) = 0x15;
            *(s32 *)((u8 *)s1 + 0xE0) = (*(s32 *)((u8 *)s1 + 0xE0) | 1) & ~2;
            *(u16 *)((u8 *)s1 + 0x5C) |= 0x800;
            *(s32 *)((u8 *)s0 + 0x1C) = 0x14;
            func_8002D4C8(4, 0xB79);
            func_8002D4C8(4, 0xB56);
        }
        *(u16 *)((u8 *)s0 + 0x5E) = 0;
    }

    func_801A38E4(s1, s2, D_801F43C0, 5, 1);

    {
        typedef struct { char c[8]; } Blk8;
        void *dst = *(void **)((u8 *)s0 + 0x20);
        void *src = *(void **)((u8 *)s1 + 0x20);

        *(Blk8 *)((u8 *)dst + 0x10) = *(Blk8 *)((u8 *)src + 0x10);
    }

    *(s32 *)((u8 *)s0 + 0x4) = *(s32 *)((u8 *)s1 + 0x4);
    *(s32 *)((u8 *)s0 + 0x8) = *(s32 *)((u8 *)s1 + 0x8);
    *(s32 *)((u8 *)s0 + 0xC) = *(s32 *)((u8 *)s1 + 0xC);
}


#include "common.h"

extern void func_8012C218(void *a0);
extern void func_801A38E4(void *a0, void *a1, s32 a2, s32 a3, s32 a4);
extern s32 func_801A419C(s32 a0);
extern s32 func_80153BD8(s32 a0);

typedef struct { s16 a, b, c, d; } V8x_801A3788; /* 8-byte, align-2 quad of s16 */

void func_801A3788(void *arg0) {
    register s32 s0 __asm__("$16") = (s32)arg0;
    s32 s1;
    u16 v1;
    s32 v1s;
    s32 pad[8];

    s1 = *(s32 *)(s0 + 0x64);

    if (*(s16 *)(s1 + 0x36) != *(s32 *)(s0 + 0xF8)) {
        func_8012C218((void *)s0);
        return;
    }

    func_801A38E4((void *)s1, (void *)(s0 + 0xCC), 0x10, 6, 0);

    *(V8x_801A3788 *)(*(s32 *)(s0 + 0x20) + 0x10) = *(V8x_801A3788 *)(*(s32 *)(s1 + 0x20) + 0x10);

    *(s32 *)(s0 + 0x4) = *(s32 *)(s1 + 0x4);
    *(s32 *)(s0 + 0x8) = *(s32 *)(s1 + 0x8);
    *(s32 *)(s0 + 0xC) = *(s32 *)(s1 + 0xC);

    v1 = *(u16 *)(s0 + 0x34);

    switch (v1) {
    default:
        v1s = v1;
        if (v1s < 2) {
            if (v1 != 0) {
                break;
            }
            if (func_801A419C(s0) == 1) {
                (*(u16 *)(s0 + 0x34))++;
            }
        }
        break;
    case 1:
        if (func_80153BD8(s0) != 0) {
            *(s32 *)(s1 + 0xE0) |= 8;
        }
        (*(u16 *)(s0 + 0x34))++;
        break;
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A38A8);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A38E4);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A3BCC);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A419C);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A4268);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A43E8);



void func_801A44C8(void *a0) {

    extern void (*D_801A6F00[])(void);
    D_801A6F00[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

void func_801A4504(void *arg0) {
    s32 v0 = func_8012C1B8();
    *(s32 *)((u8 *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(arg0);
        return;
    }
    func_8001C214(v0, 0);
    *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x2C) |= 0x10;
    {
        s32 t = *(s32 *)((u8 *)arg0 + 0x20);
        *(s16 *)(t + 0x1A) = 1;
        *(s16 *)(t + 0x18) = 1;
    }
    {
        u16 x = *(u16 *)(*(s32 *)((u8 *)arg0 + 0x64) + 0x36);
        *(s16 *)((u8 *)arg0 + 0x2) = *(u16 *)((u8 *)arg0 + 0x2) + 1;
        *(s16 *)((u8 *)arg0 + 0x10A) = x;
    }
}


#include "common.h"

extern void func_8012C218(void *a0);
extern s32 func_80134510(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);
extern void func_801A4680(void *a0);

extern u8 D_801152A8[];
extern s16 D_801152AA;
extern s16 D_801152AC;

void func_801A4590(s32 a0) {
    s32 v0 = *(s32 *)(a0 + 0x64);
    s16 sp[3];

    if (*(s16 *)(v0 + 0x36) != *(s16 *)(a0 + 0x10A)) {
        func_8012C218((void *)a0);
        return;
    }

    sp[0] = *(u16 *)(v0 + 6);
    sp[1] = *(u16 *)(v0 + 0xA) - 0x10;
    sp[2] = *(u16 *)(v0 + 0xE);
    if (func_80134510((s32)&sp[0]) == 0) {
        return;
    }

    *(s16 *)(a0 + 6) = sp[0];
    *(s16 *)(a0 + 0xA) = sp[1];
    *(s16 *)(a0 + 0xE) = sp[2];

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = ratan2(D_801152AC, D_801152AA) + 0x400;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = ratan2(*(s16 *)D_801152A8, D_801152AA);
    func_801A4680((void *)a0);
}


#include "common.h"

/* ---- local layout typedef (standalone match_one compilation) --------------
 * SVec: {s16 vx,vy,vz,pad;} 8 bytes.
 * Prim: v[4] @0x00 (0x20 bytes), 8 UV/coord shorts @0x20 (0x10 bytes),
 *       bcast(u32) @0x30, tag(s32) @0x34, code(u8) @0x38, padded to 0x40.
 *       frame: prim @ sp+0x10..sp+0x50 -> var_size 0x40, matches the 0x68
 *       frame with 6 callee-saves (s0-s4, ra).
 * Same shape as func_80183F84 (ov_SC03_105) / func_8018DA64 (ov_SC04_011).
 */
typedef struct { s16 vx, vy, vz, pad; } SVec_801A4680;
typedef struct {
    SVec_801A4680 v[4];                  /* 0x00 */
    s16 u0, t0, u1, t1, u2, t2, u3, t3;  /* 0x20 */
    u32 bcast;                           /* 0x30 */
    s32 tag;                             /* 0x34 */
    u8  code;                            /* 0x38 */
    u8  pad39[7];                        /* -> 0x40 */
} Prim_801A4680;

extern void func_80016EF8(void *a0, void *a1);

void func_801A4680(void *a0) {
    Prim_801A4680 prim;
    s32 i, j;

    prim.bcast = 0x808080;
    prim.tag = 0x50000000;
    prim.code = 0x8F;

    prim.v[3].vy = -0x40;
    prim.v[2].vy = -0x40;
    prim.v[1].vy = -0x40;
    prim.v[0].vy = -0x40;

    prim.v[3].vz = 0;
    prim.v[2].vz = 0;
    prim.v[1].vz = 0;
    prim.v[0].vz = 0;

    prim.t3 = 0x80;
    prim.t2 = 0x80;
    prim.t1 = 0x80;
    prim.t0 = 0x80;

    for (i = 0; i < 8; i++) {
        prim.v[3].vx = -0x40;
        prim.v[2].vx = -0x40;
        prim.v[1].vx = -0x40;
        prim.v[0].vx = -0x40;

        prim.u3 = 0xB80;
        prim.u2 = 0xB80;
        prim.u1 = 0xB80;
        prim.u0 = 0xB80;

        prim.v[2].vy += 0x10;
        prim.v[3].vy += 0x10;
        prim.t2 += 0xF;
        prim.t3 += 0xF;

        for (j = 0; j < 8; j++) {
            prim.v[1].vx += 0x10;
            prim.v[3].vx += 0x10;
            prim.u1 += 0xF;
            prim.u3 += 0xF;

            func_80016EF8(&prim, (void *)(*(s32 *)((u8 *)a0 + 0x20) + 0x34));

            prim.v[0].vx = prim.v[1].vx;
            prim.v[2].vx = prim.v[3].vx;
            prim.u0 = prim.u1;
            prim.u2 = prim.u3;
        }

        prim.v[0].vy = prim.v[2].vy;
        prim.v[1].vy = prim.v[3].vy;
        prim.t0 = prim.t2;
        prim.t1 = prim.t3;
    }
}




void func_801A4810(void *a0) {

    extern void (*D_801A7308[])(void);
    D_801A7308[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801A484C(s32 a0, s32 a1) {
    s32 ent = func_8012C658(0x378, a1 & 0xFFFF, a0);
    if (ent != 0 && (a1 & 0xFFFF) < 7u) {
        func_801A484C(ent, (a1 + 1) & 0xFFFF);
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B260(u8 *a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);
extern void func_801A484C(s32 a0, s32 a1);

extern u8 D_801A6F08[];
extern u8 D_801A7148[];
extern u16 D_801A7314[];

void func_801A48A8(void *arg0) {
    register s32 s0 __asm__("$16") = (s32)arg0;
    register s32 s1 __asm__("$17");

    s1 = func_8012C1B8();
    if (s1 == 0) {
        func_8012CAE4((void *)s0);
        return;
    }

    *(s32 *)(s0 + 0x20) = s1;
    func_8001CA1C(s1, (s32)D_801A6F08);
    func_8012A828(s0, (void *)D_801A7148);

    {
        u16 t70 = *(u16 *)(s0 + 0x70);
        s16 val = 0x5000 - ((t70 & 0xF) << 11);
        *(s16 *)(s1 + 0x1C) = val;
        *(s16 *)(s1 + 0x1A) = val;
        *(s16 *)(s1 + 0x18) = val;
    }
    *(s32 *)(s1 + 0x4) = *(s32 *)(s1 + 0x4) | 0x50000000;
    *(s16 *)(s1 + 0x2C) = *(u16 *)(s1 + 0x2C) | 0x90;

    *(s16 *)(s0 + 0x10A) = *(u16 *)(*(s32 *)(s0 + 0x64) + 0x36);

    if ((*(u16 *)(s0 + 0x70) & 0xF) == 0) {
        s32 p = *(s32 *)(*(s32 *)(s0 + 0x64) + 0x20);
        u16 t = *(u16 *)(p + 0x12);
        s16 sum;
        s32 d;
        s32 v0;

        *(s16 *)(s1 + 0x14) = t;
        sum = t + D_801A7314[*(u16 *)(s0 + 0x70) >> 15];
        *(s16 *)(s1 + 0x14) = sum;
        func_8012B2CC(s0);

        d = rand();
        s1 = s0 + 0xE4;
        *(s32 *)(s0 + 0x94) = d % 0x10;
        *(s32 *)(s0 + 0x1C) = 0xC;
        *(s32 *)(*(s32 *)(s0 + 0x20) + 0x80) = s1;
        *(s16 *)(s0 + 0xE8) = 0x80;
        *(s16 *)(s0 + 0xE6) = 0x80;
        *(s16 *)(s0 + 0xE4) = 0x80;
        v0 = func_8012C658(0x378, 1, s0);
        if (v0 != 0) {
            func_801A484C(v0, 2);
        }
        *(s16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
        return;
    }

    {
        s32 p = *(s32 *)(*(s32 *)(s0 + 0x64) + 0x20);
        s32 slot = *(s32 *)(s0 + 0x20);
        s32 d;
        *(s32 *)(slot + 0x80) = *(s32 *)(p + 0x80);
        d = rand();
        *(s32 *)(s0 + 0x94) = d % 0x10;
        *(s16 *)(s0 + 0x2) = 2;
        func_8012B260((u8 *)s0);
    }
}


#include "common.h"

extern void func_801A4D58(s32 a0, s32 a1);
extern s32 func_801A4DFC(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);

extern u16 D_801F4310[];

void func_801A4A78(s32 arg0) {
    s32 t;
    s32 p;
    s32 q;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        func_801A4D58(arg0, -0x100000);
        if (func_8012BEE8(arg0) == 0) {
            break;
        }
        *(s32 *)(arg0 + 0x1C) = 0xC;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;

    case 1:
        t = func_8012B744((void *)(arg0 + 4), D_801F4310);
        t = func_8012B608(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x14), t, 8);
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x14) += t;
        func_801A4D58(arg0, -0x100000);
        if (((s32 (*)(s32, u16 *))func_8012BE98)(arg0, D_801F4310) > 0x4000) {
            if (func_8012BEE8(arg0) == 0) {
                break;
            }
        }
        *(s32 *)(arg0 + 0x1C) = 0x50;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;

    case 2:
        t = func_8012B8A4((s16 *)arg0);
        t = func_8012B608(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x14), t, 0x18);
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x14) += t;
        func_801A4D58(arg0, -0x100000);
        if (*(s32 *)(arg0 + 0x1C) == 0x10) {
            *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) |= 0x80;
            p = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x80);
            *(s16 *)(p + 4) = 0x80;
            *(s16 *)(p + 2) = 0x80;
            *(s16 *)(p + 0) = 0x80;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
        /* fallthrough */
    case 3:
        if (*(s32 *)(arg0 + 0x1C) < 0x11) {
            p = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x80);
            *(u16 *)(p + 0) -= 8;
            *(u16 *)(p + 2) -= 8;
            *(u16 *)(p + 4) -= 8;
        }
        if (func_8012BEE8(arg0) != 0) {
            func_8012C218((void *)arg0);
            return;
        }
        break;
    }

    if (*(u16 *)(arg0 + 0x72) & 0x4000) {
        q = func_80132EF4(arg0, 0x6F);
        if (q != 0) {
            *(s32 *)(q + 0x10) = -(*(s32 *)(arg0 + 0x10) * 2);
            *(s32 *)(q + 0x14) = *(s32 *)(arg0 + 0x14);
            *(s32 *)(q + 0x18) = -(*(s32 *)(arg0 + 0x18) * 2);
        }
    }
    func_801A4DFC((void *)arg0);
    if (((s32 (*)(s32))func_8012CBCC)(arg0) != 0) {
        func_8012C218((void *)arg0);
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A4CF4);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A4D58);

#include "common.h"

/* func_801A4DFC (md_SC07_003, 95 ins).
 *
 * STEP-0 TWIN: ov_SC02_027:func_80180770 (87 ins, sim 0.5714) documents the
 * same "mtx = D_800AE620;" 32-byte struct-copy idiom (8-word lw/lw/lw +
 * sw/sw/sw grouping straight after the prologue). D_800AE620's global type
 * (Mtx32 in src/gsgap3.c: { s16 m[3][3]; s32 t[3]; }, 0x20 bytes) is reused
 * here under a local typedef name per law 8 (do not adopt the name alone
 * without the same field layout guarantee across TUs).
 *
 * Callee signatures adopted verbatim from src/shared/engine_core.h's
 * DEFINE_func_8012F14C / DEFINE_func_8012F568 / DEFINE_func_8012B8A4 macros
 * (the actual banked definitions), and from the fleet-uniform
 * `extern void RotMatrixY(s32 a0, void *a1);` spelling used across many TUs.
 * func_80135888's 4-arg s32-returning shape matches its many banked
 * definitions (e.g. src/ov_SC02_027/ov_SC02_027_jr_80135888.c).
 *
 * D_80126B58 is declared raw-scalar (`extern s32 D_80126B58;`, matching its
 * fleet-wide spelling in e.g. src/ov_SC03_099/ov_SC03_099.c) and indexed at
 * +0x20/+0x38 via byte-pointer casts at the use site (law 4). D_801A7318 is
 * this overlay's own local data (asm/md_SC07_003/data/tail.data.s), a 5-
 * entry array of 0x10-byte records each holding two 8-byte sub-fields; not
 * declared elsewhere in the fleet under this name, so it is typed by the
 * raw stride the asm walks (s32[4] per record; only base addresses are
 * ever taken, never dereferenced structurally, so the element type does not
 * affect codegen). D_801152A8 is declared `extern u8 D_801152A8[];` per its
 * many fleet occurrences (e.g. src/ov_SC03_099/ov_SC03_099_jr_801588CC.c).
 */

typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_801A4DFC;

extern Mtx32_801A4DFC D_800AE620;
extern void RotMatrixY(s32 a0, void *a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012B8A4(s16 *a0);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 D_80126B58;
extern s32 D_801A7318[];
extern u8 D_801152A8[];

s32 func_801A4DFC(void *a0)
{
    Mtx32_801A4DFC mtx;
    s32 buf1[2];
    s32 buf2[2];
    u8 *p;
    u8 *q;
    u8 *b58;
    u8 *base;
    s32 i;
    s32 v0;

    mtx = D_800AE620;

    RotMatrixY(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14), &mtx);

    b58 = (u8 *)&D_80126B58;
    i = 0;

    mtx.t[0] = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x48);
    mtx.t[1] = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4C);

    base = (u8 *)D_801A7318;
    q = base + 8;

    mtx.t[2] = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x50);

    p = base;

    for (; i < 10; q += 0x10, i += 2, p += 0x10) {
        func_8012F14C((s32)&mtx, (s32)p, (s32)buf1);
        func_8012F14C((s32)&mtx, (s32)q, (s32)buf2);
        v0 = func_80135888(*(s32 *)(b58 + 0x20),
                            *(s32 *)(b58 + 0x38),
                            (s32)buf1, (s32)buf2);
        if (v0 != 0) {
            v0 = func_8012B8A4((s16 *)a0);
            func_8012F568(1, 0x4201, v0, 0x32, (s32)buf2, (s32)D_801152A8);
            return 1;
        }
    }

    return 0;
}




void func_801A4F78(void *a0) {

    extern void (*D_801A73B4[])(void);
    D_801A73B4[*(u16 *)((s32)a0 + 0x2)]();
}



// @stuck: none — MATCH (42 ins), iteration 1, rtu_match clean.
// Saturating add of a 3-byte RGB triple by a signed delta.
// Idioms: (1) `s8` by-value param => entry `sll/sra 24` for the sign test only;
//   combine folds the extension back out of `~a1`/`-a1`/`a0[i]+a1` because every
//   consumer is 8-bit (andi 0xFF / sb), so $a1 is used RAW after the test.
// (2) branch sense read off the target `sltu` operand ORDER (§3-T4): positive arm
//   `sltu lim,p[i]` => store when `p[i] <= lim`; negative arm `sltu p[i],lim`
//   => store when `p[i] >= lim`.
// (3) the third `if` written out in BOTH arms; jump.c cross-jumps the identical
//   tails into the shared `j .L8018C344` (§5a) — do not hoist it after the if/else.
void func_801A4FB4(u8 *a0, s8 a1) {
    u8 lim;

    if (a1 == 0) {
        return;
    }
    if (a1 > 0) {
        lim = ~a1;
        if (a0[0] <= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] <= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] <= lim) {
            a0[2] = a0[2] + a1;
        }
    } else {
        lim = -a1;
        if (a0[0] >= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] >= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] >= lim) {
            a0[2] = a0[2] + a1;
        }
    }
}




void func_801A505C(void *a0) {

    extern void (*D_801A73BC[])(void);
    D_801A73BC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A5098);


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_801A50D4(void * arg0) {
        *(s8 *)((char *)arg0 + 0xfc) = 0x8;
        ((void (*)(s32, s32))func_8012AD44)((int)arg0, 0x2);
    }




void func_801A50FC(void *a0) {

    extern void (*D_801A73C4[])(void);
    D_801A73C4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32  func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32  func_8012C194(void);
extern void func_800233CC(void *a0, u16 a1);
extern void func_8001CD9C(s32 a0, void *a1);
extern s32  rand(void);

extern u16 D_801A73D4[];
extern s32 D_801F4484;
extern s32 D_801F4488;
extern s32 D_801F448C;
extern s32 D_801F4490;

void func_801A5138(s32 a0) {
    s32 s2;
    s32 obj;
    s32 o1;
    s32 o2;
    s32 base;
    s32 off;
    s32 v;
    s32 s1;
    s32 p64;
    u16 tmp;
    s32 *p;

    s2 = a0;
    obj = func_8012C1B8();
    *(s32 *)(s2 + 0x20) = obj;
    if (obj == 0) {
        func_8012CAE4((void *)s2);
        return;
    }

    func_8001C214(obj, 0);

    o1 = *(s32 *)(s2 + 0x20);
    *(u16 *)(o1 + 0x10) = D_801A73D4[*(s16 *)(s2 + 0x70)];

    o2 = *(s32 *)(s2 + 0x20);
    off = rand() % 0x100;
    base = *(s16 *)(s2 + 0xFC);
    if (rand() & 1) {
        v = base + off;
    } else {
        v = base - off;
    }
    *(s16 *)(o2 + 0x12) = v;

    func_8012B2CC(s2);

    *(s16 *)(s2 + 0xFE) = (rand() % 0x20) + 0x20;

    p64 = *(s32 *)(s2 + 0x64);
    tmp = *(u16 *)(p64 + 0x36);
    *(u16 *)(s2 + 0x2) = *(u16 *)(s2 + 0x2) + 1;
    *(s16 *)(s2 + 0x10A) = tmp;

    s1 = func_8012C194();
    if (s1 == 0) {
        return;
    }

    *(s32 *)(s2 + 0xCC) = s1;
    p = &D_801F4484;
    *p = 0xC0C0C0;
    D_801F4488 = 0;
    D_801F448C = 0;
    D_801F4490 = 0;
    func_800233CC((void *)p, 0x60);
    func_8001CD9C(s1, (void *)p);
    *(u16 *)(s1 + 0x2C) = 0xC010;
    *(s32 *)(s1 + 0x4) = *(s32 *)(s1 + 0x4) | 0x50800000;
    *(u16 *)(s1 + 0x8) = *(u16 *)(s2 + 0x6);
    *(u16 *)(s1 + 0xA) = *(u16 *)(s2 + 0xA);
    *(u16 *)(s1 + 0xC) = *(u16 *)(s2 + 0xE);
}


typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_801A52DC;

typedef struct { short vx, vy, vz, pad; } SVECTOR_801A52DC;

typedef struct {
    SVECTOR_801A52DC v[4];
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
} Prim_801A52DC;

#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

extern void func_80016714(s8 *a0, s32 a1);
extern void func_8012C218(void *a0);
extern Mtx32_801A4DFC D_800AE620;
extern void RotMatrixY(s32 a0, void *a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern u8 D_800AF648;
extern void func_800176F0(void *a0);

void func_801A52DC(s32 param_1)
{
    Prim_801A52DC prim;
    Mtx32_801A52DC m;
    s32 otz[4];
    s32 flag;
    SVECTOR_801A52DC *p;
    s32 i;
    s32 a, b, t;
    s16 h;

    if (*(s16 *)(*(s32 *)(param_1 + 0x64) + 0x36) != *(s16 *)(param_1 + 0x10A)) {
        if (*(s32 *)(param_1 + 0xCC) != 0) {
            func_80016714((s8 *)(*(s32 *)(param_1 + 0xCC)), 0x38);
        }
        func_8012C218((void *)param_1);
        return;
    }

    t = *(s32 *)(param_1 + 0xE0) - 0x80;
    *(s32 *)(param_1 + 0xE0) = t;
    if (t < -0x400) {
        *(s32 *)(param_1 + 0xE0) = -0x400;
    }

    prim.v[0].vx = -0x10;
    prim.v[1].vx = 0x10;
    h = *(u16 *)(param_1 + 0xE0);
    prim.v[3].vy = 0;
    prim.v[2].vy = 0;
    prim.v[3].vx = 0;
    prim.v[2].vx = 0;
    prim.v[1].vy = 0;
    prim.v[0].vy = 0;
    prim.v[1].vz = 0;
    prim.v[0].vz = 0;
    prim.v[3].vz = h;
    prim.v[2].vz = h;

    m = (*(Mtx32_801A52DC *)&D_800AE620);
    RotMatrixY(*(s16 *)(param_1 + 0xFE), &m);
    func_8012F14C((s32)&m, (s32)&prim.v[2], (s32)&prim.v[2]);

    m = (*(Mtx32_801A52DC *)&D_800AE620);
    RotMatrixY(-*(s16 *)(param_1 + 0xFE), &m);
    func_8012F14C((s32)&m, (s32)&prim.v[3], (s32)&prim.v[3]);

    gte_SetRotMatrix((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    gte_SetTransMatrix((void *)(*(s32 *)(param_1 + 0x20) + 0x34));

    RotTransSV((s32)&prim.v[0], (s32)&prim.v[0], &flag);
    RotTransSV((s32)&prim.v[1], (s32)&prim.v[1], &flag);
    RotTransSV((s32)&prim.v[2], (s32)&prim.v[2], &flag);
    RotTransSV((s32)&prim.v[3], (s32)&prim.v[3], &flag);

    gte_SetRotMatrix(&D_800AF648);
    gte_SetTransMatrix(&D_800AF648);

    for (i = 0, p = &prim.v[0]; i < 4; i++, p++) {
        gte_ldv0(p);
        gte_rtps();
        gte_stsxy(p);
        gte_stflg(&flag);
        gte_stszotz(&otz[i]);
        if (flag & ~0x1000) {
            return;
        }
    }

    a = otz[2];
    if (otz[3] < a) {
        a = otz[3];
    }
    b = otz[0];
    if (otz[1] < b) {
        b = otz[1];
    }
    if (b > a) {
        b = a;
    }
    prim.f0 = 0x808080;
    prim.f1 = 0x808080;
    prim.v[0].vz = b;
    prim.f2 = 0;
    prim.f3 = 0;
    prim.f4 = 0x50000000;
    func_800176F0(&prim);
}




void func_801A5638(void *a0) {

    extern void (*D_801A73F4[])(void);
    D_801A73F4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* func_801A5674 — per-frame tick for a 3-state "rising bar" effect entity.
 *
 * Frame map (0x68):
 *   sp+0x00..0x0F  outgoing arg area
 *   sp+0x10..0x17  u16 out[4]     (result of func_8012F14C)
 *   sp+0x18..0x37  s32 buf[8]     (matrix scratch for func_8012EC04)
 *   sp+0x38..0x57  Prim801A5674   (2 SVECs + 2 packed colours + tag)
 *   sp+0x58 s0, sp+0x5C s1, sp+0x60 ra
 */

typedef struct { s16 x; s16 y; s16 z; s16 pad; } SVec801A5674;
typedef struct { SVec801A5674 v[2]; s32 col[2]; s32 tag; s32 pad; } Prim801A5674;

extern void func_8012C218(void *a0);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012CC40(s32 a0, s32 a1);
extern s32 func_80016A5C();

void func_801A5674(void *arg0) {
    u16 out[4];        /* sp+0x10 */
    s32 buf[8];        /* sp+0x18 */
    Prim801A5674 prim; /* sp+0x38 */
    s32 e;
    u16 st;
    s32 p;

    e = (s32)arg0;
    if (*(s16 *)(e + 0xA) >= 0x10) {
        func_8012C218(arg0);
        return;
    }

    switch (*(u16 *)(e + 0x34)) {
    case 0:
        p = *(s32 *)(e + 0x64);
        if (*(s16 *)(e + 0x10A) == *(s16 *)(p + 0x36)) {
            func_8012EC04(p, *(s16 *)(e + 0xFC), buf);
            ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, *(s32 *)(e + 0xDC), out);
            *(u16 *)(e + 0x6) = out[0];
            *(u16 *)(e + 0xA) = out[1];
            *(u16 *)(e + 0xE) = out[2];
        }
        *(s32 *)(e + 0xE4) += *(s32 *)(e + 0xE8);
        if (*(s32 *)(e + 0xE4) >= *(s32 *)(e + 0xE0)) {
            *(s32 *)(e + 0xE4) = *(s32 *)(e + 0xE0);
            *(u16 *)(e + 0x34) += 1;
        }
        break;
    case 1:
        out[2] = 0;
        out[0] = 0;
        out[1] = *(s32 *)(e + 0xE4);
        if (((s32 (*)(s32, u16 *))func_8012CC40)(e, out) & 0x2000) {
            *(u16 *)(e + 0x34) += 1;
        }
        break;
    case 2:
        *(s32 *)(e + 0xEC) += 0x10;
        if (*(s32 *)(e + 0xEC) >= *(s32 *)(e + 0xE4)) {
            func_8012C218((void *)e);
            return;
        }
        break;
    }

    prim.v[1].z = 0;
    prim.v[1].x = 0;
    prim.v[0].z = 0;
    prim.v[0].x = 0;
    prim.tag = 0x50000000;
    st = *(u16 *)(e + 0x34);
    prim.col[0] = 0x808080;
    prim.col[1] = 0x101010;
    if (st < 2) {
        prim.v[0].y = *(s32 *)(e + 0xE4);
        prim.v[1].y = 0;
    } else {
        prim.v[0].y = *(s32 *)(e + 0xE4);
        prim.v[1].y = *(s32 *)(e + 0xEC);
    }
    func_80016A5C(&prim, *(s32 *)(e + 0x20) + 0x34);
}




void func_801A5860(void *a0) {

    extern void (*D_801A73FC[])(void);
    D_801A73FC[*(u16 *)((s32)a0 + 0x2)]();
}




void func_801A589C(void *a0) {

    extern void (*D_801A7414[])(void);
    D_801A7414[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX;
typedef struct { s16 vx, vy, vz, pad; } SVECTOR;

extern void (*D_801A7434[])(void);

extern u16 D_801A7422;
extern u16 D_801A7424;
extern u16 D_801A7426;
extern u16 D_801A742E;
extern u16 D_801A7430;
extern u16 D_801A7432;

extern u8 D_800D3918[];

extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);

void func_801A58D8(void *a0) {
    s32 p;
    s32 v0;
    s32 v1;
    MATRIX m1;
    SVECTOR svec_out;

    D_801A7434[*(u16 *)((s32)a0 + 0x2)]();

    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        p = *(s32 *)((s32)a0 + 0x64);
        v0 = *(s32 *)(p + 0x20);
        v1 = *(s32 *)(v0 + 0x20);

        D_801A7422 = *(u16 *)(v1 + 0xD2);
        D_801A7424 = *(u16 *)(v1 + 0xD4);
        D_801A7426 = *(u16 *)(v1 + 0xD6);
        D_801A742E = *(u16 *)(v1 + 0xDE);
        D_801A7430 = *(u16 *)(v1 + 0xE0);
        D_801A7432 = *(u16 *)(v1 + 0xE2);

        func_8012EC04(p, 0x11, (s32 *)&m1);
        func_8012F14C((s32)&m1, (s32)D_800D3918, (s32)&svec_out);

        *(s16 *)((s32)a0 + 0x6) = svec_out.vx;
        *(s16 *)((s32)a0 + 0xA) = svec_out.vy;
        *(s16 *)((s32)a0 + 0xE) = svec_out.vz;
        func_8012B2CC((s32)a0);
    }
}




void func_801A59D4(void *a0) {

    extern void (*D_801A743C[])(void);
    D_801A743C[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_801A7368[];
extern u8 D_801A7374[];

void func_801A5A10(s32 param_1)
{
    s32 p;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_801A7368;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x5A;

    p = *(s32 *)(param_1 + 0x20);
    *(u16 *)(p + 0x1A) = 0x3000;
    *(u16 *)(p + 0x18) = 0x3000;

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_801A7374);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);
extern void func_8012931C(void *);

void func_801A5A9C(s32 a0) {
    s32 s0 = a0;
    func_8012931C((void *)a0);
    if (((s32 (*)(s32, void *))func_80128ED8)(*(s32 *)(s0 + 0x20), (void *)(s0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(s0);
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A5AE0);

#include "common.h"

extern void func_801A4FB4(u8 *, s8);
extern void func_800233CC(void *, u16);
extern void func_801292C8(u8 *);

extern u8 D_801F4448[];

void func_801A5BBC(s32 arg0) {
    s16 var;

    var = *(s16 *)(arg0 + 0x2C);
    if (var < 0x700) {
        *(s16 *)(arg0 + 0x2C) = var + 0x30;
        func_801A4FB4(D_801F4448, -4);
        func_800233CC(D_801F4448 - 4, *(u16 *)(arg0 + 0x2C));
    } else {
        func_801292C8((u8 *)arg0);
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_801A5098(s32 a0);

extern s32 D_801F28F8;
extern s32 D_801F30A8;

void func_801A5C34(s32 param_1)
{
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }

    func_8001C810(v0, (s32)&D_801F28F8);

    v0 = func_8012C1B8();
    *(s32 *)(param_1 + 0xCC) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        v0 = *(s32 *)(param_1 + 0x20);
        *(s16 *)v0 = 0;
        return;
    }

    func_8001C810(v0, (s32)&D_801F30A8);

    *(u8 *)(param_1 + 0xC0) = 0;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x90;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x80) = param_1 + 0xFC;

    *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0xCC) + 0x2C) |= 0x90;
    *(s32 *)(*(s32 *)(param_1 + 0xCC) + 0x80) = param_1 + 0xFC;

    *(s16 *)(param_1 + 0xFC) = 0x100;
    *(s16 *)(param_1 + 0xFE) = 0x100;
    *(s16 *)(param_1 + 0x100) = 0x100;
    *(s16 *)(param_1 + 0x102) = -2;

    func_801A5098(param_1);
}


#include "common.h"

extern void func_801A50D4(void *arg0);

void func_801A5D4C(s32 param_1)
{
    s32 a1;
    u16 v0;
    u16 v1;

    a1 = *(s32 *)(param_1 + 0xCC);
    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    if (v1 < 0x5000) {
        s32 p20;

        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = v1 + 0x100;

        p20 = *(s32 *)(param_1 + 0x20);
        v1 = *(u16 *)(p20 + 0x18);
        *(u16 *)(p20 + 0x1C) = v1;
        *(u16 *)(p20 + 0x1A) = v1;

        v0 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = v0 + 0x100;

        *(u16 *)(a1 + 0x12) = *(u16 *)(a1 + 0x12) - 0x100;

        *(u16 *)(a1 + 0x8) = *(u16 *)(param_1 + 0x6) + *(u16 *)(param_1 + 0x50);
        *(u16 *)(a1 + 0xA) = *(u16 *)(param_1 + 0xA) + *(u16 *)(param_1 + 0x52);
        *(u16 *)(a1 + 0xC) = *(u16 *)(param_1 + 0xE) + *(u16 *)(param_1 + 0x54);

        *(u16 *)(a1 + 0x18) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
        *(u16 *)(a1 + 0x1A) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A);
        *(u16 *)(a1 + 0x1C) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1C);
    } else {
        func_801A50D4((void *)param_1);
    }
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A5E44);

void func_801A5F18(void *a0) {
    u32 v;
    u32 m;
    v = *(u8 *)((s32)a0 + 0xFC);
    v -= 3;
    m = v & 0xFF;
    *(u8 *)((s32)a0 + 0xFC) = v;
    if (m >= 9) {
        func_80016450(m, 0);
    } else {
        func_8012C218(a0);
    }
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 rand(void);

void func_801A5F6C(s32 a0) {
    s32 v0;
    s32 v1;
    s32 p64;
    u16 tmp;

    v0 = func_8012C1B8();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C214(v0, 0);

    *(s32 *)(a0 + 0xE0) = rand() % 64 + 0x20;

    *(s32 *)(a0 + 0xE8) = rand() % 5 + 4;
    *(s32 *)(a0 + 0x48) = 0xC000;

    p64 = *(s32 *)(a0 + 0x64);
    tmp = *(u16 *)(p64 + 0x36);
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    *(u16 *)(a0 + 0x10A) = tmp;
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern u8 D_801F3208[];
extern u8 D_801A7404[];
extern u16 D_80126B62;
extern u16 D_80126BE2;
extern u16 D_80126B5E;
extern u16 D_80126BE0;
extern u16 D_80126B66;
extern u16 D_80126BE4;

void func_801A6038(void *a0) {
    register s32 s0 __asm__("$16") = (s32)a0;
    register s32 v0 __asm__("$2");

    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s0);
        return;
    }

    func_8001C214(v0, (s32)D_801F3208);

    *(s32 *)(s0 + 0x58) = (s32)D_801A7404 | 0x40000000;
    *(u16 *)(s0 + 0x5C) = 0xC00;
    *(u16 *)(s0 + 0x6) = 0;

    *(s16 *)&D_80126B62 = -0x120;
    *(s16 *)&D_80126BE2 = -0x120;
    *(s16 *)&D_80126B5E = 0;
    *(s16 *)&D_80126BE0 = 0;
    *(s16 *)(s0 + 0xE) = -0x462;
    *(s16 *)&D_80126B66 = -0x462;
    *(s16 *)&D_80126BE4 = -0x462;
    *(s16 *)(s0 + 0xA) = -0x100;
    *(s32 *)(s0 + 0x14) = 0xFFFA0000;
    *(u8 *)(s0 + 0x75) = 2;
    *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
}


INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A6108);

INCLUDE_ASM("asm/md_SC07_003/nonmatchings/md_SC07_003", func_801A6138);

extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_8012BA10(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);

void func_801A61C4(s32 arg0) {
    if (func_8012BDBC(arg0, 0x280) != 0) {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) += func_8012BA10(arg0, 8);
    } else {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) += func_8012B608(
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12),
            *(s16 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x12),
            8);
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_800233CC(void *a0, u16 a1);
extern s32 func_8001CA88(s32 a0, void *a1);

extern s32 D_801F44C4;
extern s32 D_801F44C8;
extern s32 D_801F44CC;
extern s32 D_801F44D0;

void func_801A623C(void *a0) {
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    {
        void *s0 = &D_801F44C4;
        *(s32 *)s0 = 0x808080;
        D_801F44C8 = 0;
        D_801F44CC = 0;
        D_801F44D0 = 0;
        func_800233CC(s0, 0x60);
        func_8001CA88(*(s32 *)((s32)a0 + 0x20), s0);
    }

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = 1;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1E) = 0xAAA;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2E) = 0xC010;

    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x50000000;

    *(u16 *)((s32)a0 + 0x2) += 1;
}


extern s32 D_801F44C4;
extern void func_8012C218(void *a0);

void func_801A6334(s32 arg0) {
    s32 *p;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) += 0xE00;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) += 0xE00;
    p = &D_801F44C4;
    *p += 0xFFFBFBFC;
    if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) >= 0x7001) {
        func_8012C218((void *)arg0);
    }
}

