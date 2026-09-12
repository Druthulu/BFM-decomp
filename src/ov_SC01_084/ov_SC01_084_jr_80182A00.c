#include "common.h"
#include "../shared/engine_prelude.h"
#include "ov_SC01_084_shared.h"

/* ==== P31 S74 §426/§431 jtbl-span isolation =================================
 * Second piece of the former single TU src/ov_SC01_084/ov_SC01_084_jr_8017F690.c,
 * cut VERBATIM at ((void (*)())func_80182A00)(vram 0x80182A00 = file offset 0x5A8A8).
 *
 * WHY: one compiled object contributes exactly ONE contiguous .rodata run, and
 * the old subseg owned raw jump tables in TWO non-adjacent spans of the data-tail
 * island:
 *     0x801C60C8-0x801C611C  owners func_8017F690 .. func_80182328   (piece 1)
 *     0x801C6130-0x801C6198  owner  ((void (*)())func_80182A00)(piece 2)
 * separated by D_801C611C (0x801C611C-0x801C6130, 20 bytes of NON-zero data, so
 * not alignment padding and not carveable). func_80182A00's table could therefore
 * never carve while it shared an object with func_80182328's — jtbl_carve.py fails
 * loud on exactly that. This file is the isolation.
 *
 * Byte-neutral by construction: the cut is verbatim, the include set is the
 * original TU's, and the declarations that CROSS the cut live in
 * src/ov_SC01_084/ov_SC01_084_shared.h (moved, never copied). */
#include "common.h"

extern s32 D_801270D4;
extern s32 D_801270E4;
extern u8 D_80062BDC;
extern u8 D_8018AA9C[];
extern u8 D_8018AAA8[];
extern u8 D_801A1DA0[];
extern unsigned char D_801A24C8;
extern s32 D_801C611C;

extern void func_80019064(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B200(u8 *a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012C098(void *a0);
extern void func_8012E9C0(s32 a0);
extern void func_80130088(void *a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_80182D3C(s32 a0);

/* The four sw to sp+0x10..0x1C are a DEAD 16-byte local copy of D_801C611C
 * (a movstrsi block move). gcc-2.7.2's flow.c only kills a MEM that is
 * immediately re-stored, so the copy survives to the frame. It is NOT four
 * extra arguments to func_80143B6C -- $a2/$a3 are never written. */


void func_80182A00(s32 a0) {
    Blk16 sp10 = *(Blk16 *)&D_801C611C;

    func_8012E9C0(a0);
    if (*(u8 *)(a0 + 0x5E) == 5) {
        func_80019064(&D_80062BDC);
    }
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x76) = *(u16 *)(a0 + 0x76) - *(u16 *)(a0 + 0x60);
    *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (*(u16 *)(a0 + 0x62) + 0x800) & 0xFFF;
    func_8012B2CC(a0);
    func_8012B200((u8 *)a0);
    *(u16 *)(a0 + 2) = 6;
    func_80143B6C(a0, 0);
    switch (*(u16 *)(a0 + 0x5E)) {
    case 0xD:
        *(u16 *)(a0 + 2) = 8;
        *(u16 *)(a0 + 0x98) = 0;
        *(s32 *)(a0 + 0x1C) = 0;
        *(u16 *)(a0 + 0x5C) = 0;
        break;
    case 0xE:
        if (*(s16 *)(a0 + 0x70) == 2) {
            D_801270E4 -= 1;
        } else {
            D_801270D4 -= 1;
        }
        func_8012C098((void *)a0);
        break;
    case 0xA:
        *(u16 *)(a0 + 2) = 9;
        *(u16 *)(a0 + 0x98) = 0;
        *(s32 *)(a0 + 0x1C) = 0x10;
        break;
    case 9:
        *(u16 *)(a0 + 2) = 0xA;
        func_8012A828(a0, &D_801A24C8);
        func_8012B2CC(a0);
        func_8012B23C(a0);
        func_8012B14C(a0, (s32)D_8018AA9C);
        *(s32 *)(a0 + 0x1C) = 0;
        *(u16 *)(a0 + 0x76) = 0;
        *(u16 *)(a0 + 0x5C) = 0;
        func_80130088((void *)a0);
        *(u8 *)(a0 + 0xC2) = 0;
        *(u8 *)(a0 + 0xC3) = 0;
        break;
    case 0x11:
        *(u8 *)(a0 + 0xC1) = 7;
        *(u16 *)(a0 + 2) = 0xA;
        func_8012A828(a0, &D_801A24C8);
        func_8012B2CC(a0);
        func_8012B23C(a0);
        func_8012B14C(a0, (s32)D_8018AA9C);
        *(s32 *)(a0 + 0x1C) = 0;
        *(u16 *)(a0 + 0x76) = 0;
        *(u16 *)(a0 + 0x5C) = 0;
        func_80130088((void *)a0);
        *(u8 *)(a0 + 0xC2) = 0;
        *(u8 *)(a0 + 0xC3) = 0;
        func_8012B14C(a0, (s32)D_8018AAA8);
        break;
    case 0x21:
        *(u16 *)(a0 + 2) = 0xF;
        *(s32 *)(a0 + 0x1C) = 6;
        *(u16 *)(a0 + 0x5C) = 0;
        break;
    case 0xF:
        if (*(s16 *)(a0 + 0x76) > 0) {
            func_80182D3C(a0);
        } else {
            func_8002D4C8(0x6AA, 0);
            *(u16 *)(a0 + 2) = 0xA;
            func_8012A828(a0, &D_801A24C8);
            func_8012B2CC(a0);
            func_8012B23C(a0);
            func_8012B14C(a0, (s32)D_8018AA9C);
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(a0 + 0x76) = 0;
            *(u16 *)(a0 + 0x5C) = 0;
            func_80130088((void *)a0);
            *(u8 *)(a0 + 0xC2) = 0;
            *(u8 *)(a0 + 0xC3) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0x300;
            *(s32 *)(a0 + 8) = *(s32 *)(a0 + 8) - 0x240000;
            func_8012B2CC(a0);
        }
        break;
    default:
        if (*(s16 *)(a0 + 0x76) > 0) {
            *(s32 *)(a0 + 0x1C) = 0x10;
            func_8012A828(a0, D_801A1DA0);
        } else {
            func_8002D4C8(0x6AA, 0);
            *(u16 *)(a0 + 2) = 0xA;
            func_8012A828(a0, &D_801A24C8);
            func_8012B2CC(a0);
            func_8012B23C(a0);
            func_8012B14C(a0, (s32)D_8018AA9C);
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(a0 + 0x76) = 0;
            *(u16 *)(a0 + 0x5C) = 0;
            func_80130088((void *)a0);
            *(u8 *)(a0 + 0xC2) = 0;
            *(u8 *)(a0 + 0xC3) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0x300;
            *(s32 *)(a0 + 8) = *(s32 *)(a0 + 8) - 0x240000;
            func_8012B2CC(a0);
        }
        break;
    }
}



// @class: plumbing
// @unstuck(P36): none — MATCH (30 ins)

extern unsigned char D_801A2400[];

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern void func_80143CD4(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern int func_800CB0E8(int param);

void func_80182D3C(int param_1)
{
    *(short *)(param_1 + 2) = 12;
    ((int (*)(int, void *))func_8012A828)(param_1, &D_801A2400);
    ((int (*)(int))func_8012B23C)(param_1);
    *(int *)(param_1 + 0x1c) = 0x78;
    ((int (*)(int))func_80143CD4)(param_1);
    ((int (*)(int, int))func_8002D4C8)(0x47b, 0);
    ((int (*)(int, int))func_8002D4C8)(0x478, 0);
    func_800CB0E8(param_1);
    *(char *)(param_1 + 0xc1) = 6;
}


extern unsigned char D_801A24C8;
extern void func_8012A828(s32, void*);

void func_80182DB4(param_1)
int param_1;
{
    *(short *)(param_1 + 2) = 7;
    *(short *)(param_1 + 0x5c) = 0;
    func_8012A828(param_1, &D_801A24C8);
    *(int *)(param_1 + 0x1c) = 0x1e;
}


void func_80182DF8(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0xB;
        *(short *)((char *)a0 + 0x5C) = 0;
        *(int *)((char *)a0 + 0x1C) = 0x1E;
        *(short *)((char *)a0 + 0x98) = 0;
    }


#include "common.h"

/* Declarations follow the destination TU (ov_SC01_084_jr_8017CA80.c) house style,
 * verified against the fleet-wide idiom at ov_SC02_027_jr_8017AE2C.c:3651 etc.
 *   func_8012CBCC  fleet-canonical `void (s32)`; callers that need the s32 return
 *                  value cast the pointer at the use site (e.g.
 *                  ov_SC02_027_jr_8017D898.c:5522, engine_core.h idiom 9).
 *   func_8012BEE8  matches this TU's own decl at line 3546 (`s32 (s32)`).
 *   func_8012B23C  matches this TU's own decl at line 3892 (`void (s32)`).
 *   func_8002D4C8  matches this TU's own decl at line 3894/59 (`void (s32,s32)`).
 *   func_80013328  matches this TU's own decl at line 521 (`s32 (s32,s32)`),
 *                   fleet-canonical call shape `func_80013328(a0+4,(s32)&D_80126B5C)`
 *                   verified at ov_SC02_027_jr_8017AE2C.c:3651 and dozens of sibling
 *                   overlay TUs (the seq-volume-lookup idiom).
 *   D_80126B5C     fleet-canonical `extern u8 D_80126B5C;` passed as `(s32)&D_80126B5C`.
 *   func_80182F90  same-TU sibling defined later in this file (INCLUDE_ASM at
 *                  line 3923); forward-declared here.
 */
extern void func_8012CBCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80013328(s32 a0, s32 a1);
extern u8 D_80126B5C;
extern void func_80182F90(s32 a0);

void func_80182E14(s32 a0) {
    s32 s0 = a0;
    u16 state = *(u16 *)(s0 + 0x34);

    switch (state) {
    case 0: {
        s32 p;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) + 0xE0;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0;
        if (((s32 (*)(s32))func_8012CBCC)(s0) == 0) {
            return;
        }
        {
            s32 vol = func_80013328(s0 + 4, (s32)&D_80126B5C);

            if (vol < 0) {
                vol = 0;
            }
            if (vol > 0x300) {
                vol = 0x300;
            }
            vol = (0x300 - vol) * 127 / 0x300;
            if (vol < 0) {
                vol = 0;
            }
            if (vol > 0x7F) {
                vol = 0x7F;
            }
            func_8002D4C8(0x43B, (vol | 0x1000) & 0xFFFF);
        }
        func_8012B23C(s0);
        p = *(s32 *)(s0 + 0x20);
        *(s32 *)(s0 + 0x14) = 0xFFF00000;
        *(u16 *)(p + 0x10) = 0;
        *(u16 *)(s0 + 0x34) = 1;
        return;
    }
    case 1: {
        s32 p;

        if (((s32 (*)(s32))func_8012CBCC)(s0) == 0) {
            return;
        }
        func_8012B23C(s0);
        p = *(s32 *)(s0 + 0x20);
        *(u16 *)(s0 + 0x34) = 2;
        *(u16 *)(p + 0x10) = 0;
        *(s32 *)(s0 + 0x1C) = 0xA;
        return;
    }
    case 2:
        if (func_8012BEE8(s0) == 0) {
            return;
        }
        func_80182F90(s0);
        return;
    }
}


extern u8 D_801A21E0[];

void func_80182F90(s32 a0)
{
    s32 v1;

    *(s16 *)(a0 + 0x2) = 0xE;
    *(u16 *)(a0 + 0x34) = 0;
    func_8012A828(a0, D_801A21E0);
    v1 = *(s32 *)(a0 + 0x20);
    *(u16 *)(a0 + 0x5C) = 0xAA00;
    *(u16 *)(a0 + 0x5E) = 0;
    *(u16 *)(v1 + 0x14) = 0;
    *(u16 *)(v1 + 0x10) = 0;
    func_8012B23C(a0);
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern u8 D_801A21E0[];
extern u8 D_801A2848[];

void func_80182FEC(s32 param_1)
{
    s32 v1;

    *(s16 *)(param_1 + 2) = 0xE;
    *(u16 *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, D_801A21E0);
    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(param_1 + 0x5C) = 0xAA00;
    *(u16 *)(param_1 + 0x5E) = 0;
    *(u16 *)(v1 + 0x14) = 0;
    *(u16 *)(v1 + 0x10) = 0;
    func_8012B23C(param_1);
    func_8012A828(param_1, D_801A2848);
    *(s32 *)(param_1 + 0x1C) = 0x1E;
    *(u16 *)(param_1 + 0x34) = 1;
}


#include "common.h"

extern s32 D_801270D8;
extern s32 D_801270D4;
extern s32 D_801270E4;
extern u8 D_8018AA6C[];
extern u8 D_801A2940[];
extern u8 D_801A21E0[];
extern u8 D_801A2848[];

extern void func_8012C098(void *a0);
extern s32 func_801845EC(s32 a0, s32 a1);
extern s32 func_80185E68(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80183068(void *a0)
{
    s32 v1 = *(u16 *)((s32)a0 + 0x34);

    switch (v1) {
    case 0:
        if ((*(u16 *)((s32)a0 + 0x72) & 0x4000) != 0) {
            func_8012A828((s32)a0, D_801A2848);
            *(s32 *)((s32)a0 + 0x1C) = 0x1E;
            *(u16 *)((s32)a0 + 0x34) = 1;
        }
        break;
    case 1:
    case 2:
    case 3:
        if (D_801270D8 != 0) {
            if (*(s16 *)((s32)a0 + 0x70) == 2) {
                D_801270E4 -= 1;
            } else {
                D_801270D4 -= 1;
            }
            func_8012C098(a0);
        } else {
            s32 state = *(s32 *)((s32)a0 + 0x1C);
            if (state == 0xC) {
                func_801845EC((s32)a0, 0);
            } else if (state == 0xF) {
                func_80185E68((s32)a0, (s32)D_8018AA6C);
            }
            if (func_8012BEE8((s32)a0) != 0) {
                *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;
                *(s32 *)((s32)a0 + 0x1C) = 0x1E;
                if (*(u16 *)((s32)a0 + 0x34) == 4) {
                    func_8012A828((s32)a0, D_801A2940);
                }
            }
        }
        break;
    case 4:
        if ((*(u16 *)((s32)a0 + 0x72) & 0x4000) != 0) {
            s32 p20;
            *(s16 *)((s32)a0 + 2) = 0xE;
            *(u16 *)((s32)a0 + 0x34) = 0;
            func_8012A828((s32)a0, D_801A21E0);
            p20 = *(s32 *)((s32)a0 + 0x20);
            *(u16 *)((s32)a0 + 0x5C) = 0xAA00;
            *(u16 *)((s32)a0 + 0x5E) = 0;
            *(u16 *)(p20 + 0x14) = 0;
            *(u16 *)(p20 + 0x10) = 0;
            func_8012B23C((s32)a0);
            func_8012A828((s32)a0, D_801A2848);
            *(s32 *)((s32)a0 + 0x1C) = 0x1E;
            *(u16 *)((s32)a0 + 0x34) = 1;
        }
        break;
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32, s32, s32);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80143970(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 func_80047D3C(s32 a0);
extern s32 func_801807D8(s16 *a0);
extern u8 D_8018AB18[];
extern u8 D_8018CE0C[];
extern s16 D_8018AAE4;
extern s16 D_801C7748;
extern u8 D_8018AA7C[];
extern unsigned char D_801A24C8;
extern u16 D_8018AABC;
extern u16 D_8018AABE;
extern u16 D_8018AAC0;
extern s32 D_801A1A10;

void func_80183244(s32 param_1) {
    s16 tmp[3];
    s16 vec[3];
    s16 t;
    s32 e;
    s32 frac;
    s32 threshold;
    s32 s2;
    s32 sinRaw;
    s32 cosRaw;
    s32 sinVal;
    s32 cosVal;
    s32 sq0;
    s32 sq1;
    s32 ss;
    s32 ptr;

    if (func_8012C354(param_1, (s32)D_8018AB18) == 0) {
        return;
    }

    if (*(s16 *)(param_1 + 0x70) != 0) {
        func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_8018CE0C);
        *(s32 *)(param_1 + 0x78) = (s32)&D_8018AAE4;
    }
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0xBE, 0x8C);

    *(s16 *)(param_1 + 0x100) = 0;
    t = D_801C7748 + 0x800;
    *(s16 *)(param_1 + 0xDC) = t;
    e = t;
    threshold = -(e * 1536) / 12288 - 0x22;
    s2 = -(e * 160) / 12288 + 0x260;
    frac = e & 0xFFF;

    sinRaw = func_80047948(frac);
    sinVal = (sinRaw * s2) >> 12;

    cosRaw = func_8004787C(frac);
    cosVal = (cosRaw * s2) >> 12;

    tmp[0] = (s16)sinVal;
    tmp[1] = (s16)threshold;
    tmp[2] = (s16)cosVal;

    *(s16 *)(param_1 + 0x6) = tmp[0];
    *(s16 *)(param_1 + 0xA) = tmp[1];
    *(s16 *)(param_1 + 0xE) = tmp[2];

    func_80143970(param_1);
    *(s32 *)(param_1 + 0xBC) = (s32)D_8018AA7C;

    if (*(s16 *)(param_1 + 0x70) == 2) {
        *(s16 *)(param_1 + 0x2) = 0xD;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801A24C8);
        ptr = *(s32 *)(param_1 + 0x20);
        *(s16 *)(param_1 + 0x5C) = 0;
        *(s16 *)(param_1 + 0x5E) = 0;
        *(s16 *)(ptr + 0x10) = 0xE00;
        *(s16 *)(param_1 + 0x6) = D_8018AABC;
        *(s16 *)(param_1 + 0xA) = D_8018AABE;
        *(s16 *)(param_1 + 0xE) = D_8018AAC0;
        func_8012B23C(param_1);
    } else {
        *(u8 *)(param_1 + 0xC1) = 0;
        *(s16 *)(param_1 + 0x2) = 1;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801A1A10);

        *(s32 *)(param_1 + 0x1C) = 0xA;
        *(u16 *)(param_1 + 0x5C) |= 0x8000;
        *(u16 *)(param_1 + 0xFC) ^= 1;
        *(s16 *)(param_1 + 0x5E) = 0;

        vec[0] = *(u16 *)(param_1 + 0x6);
        vec[1] = *(u16 *)(param_1 + 0xA);
        vec[2] = *(u16 *)(param_1 + 0xE);

        sq0 = (s32)vec[0] * (s32)vec[0];
        sq1 = (s32)vec[2] * (s32)vec[2];
        ss = sq0 + sq1;
        *(s16 *)(param_1 + 0xDE) = func_80047D3C(ss);
        *(s16 *)(param_1 + 0xDC) = func_801807D8(vec);
    }
}


void func_801834B8(u16 *param_1) {
    extern void func_80182A00(s32 a0);
    extern void (*D_8018AB4C[])(void *);

    if (param_1[1] != 0 && (param_1[0x2E] & 1)) {
        ((void (*)())func_80182A00)();
    }
    if (param_1[0] != 0) {
        D_8018AB4C[param_1[1]](param_1);
    }
}


#include "common.h"

/* Card func_8018353C — fresh mass-lane crack (no banked twin). Shape and house
 * style adopted from same-TU neighbour func_80183A7C (shares func_8012AD80,
 * func_8012B14C, func_8012B608, func_8012B77C) — same "load 3 u16 globals into
 * two stack scratch structs, dispatch table entry + init call, then feed a
 * position/rotation triad through func_8012B77C, poke the result into a linked
 * struct at param_1+0x20" skeleton. See docs/matching-cookbook.md for the
 * general pattern. */

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8  D_8018AB8C[];

extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B77C(void *, s32, void *);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_801838F0(void *arg0);

void func_8018353C(s32 param_1) {
    register s32 a2val __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus9)
    s32 v1val;
    s32 a3val;
    s32 v0;
    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    s32 posPtr;
    s32 out;
    s16 buf1[3];
    s32 in3[3];
    s32 outVal;
    s32 v1;

    a2val = D_80126B5E;
    v1val = D_80126B62;
    a3val = D_80126B66;

    buf1[0] = (s16)a2val;
    buf1[1] = (s16)v1val;
    buf1[2] = (s16)a3val;

    v0 = *(s16 *)(param_1 + 0x70);
    v1val = v1val - 0x40;
    v0 = v0 << 5;
    v1val = v1val - v0;
    buf1[1] = (s16)v1val;

    s0 = *(s16 *)(param_1 + 0x70);

    *((s16 *)&in3[0] + 1) = (s16)a2val;
    *((s16 *)&in3[1] + 1) = (s16)v1val;
    *((s16 *)&in3[2] + 1) = (s16)a3val;

    s0 = (s0 << 2) + 6;

    func_8012B14C(param_1, (s32)D_8018AB8C);
    func_8012AD80(param_1);

    posPtr = param_1 + 4;
    func_8012B77C(&out, posPtr, in3);

    outVal = out;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)outVal;

    v0 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), outVal >> 16, s0);

    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)v1;

    if (*(s16 *)(param_1 + 0x70) == 0) {
        func_801838F0((void *)param_1);
    }
}


#include "common.h"

extern s16 D_801C7748;
extern s16 D_801C774A;
extern s16 D_8018AB98;
extern s16 D_8018AB9A;
extern u16 D_8018AB9C;
extern s16 D_8018AB9E;
extern s16 D_8018ABA0;

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80183630(s32 a0) {
    s32 sum1;
    s32 sum2;
    s32 frac;
    s32 threshold;
    s32 ret;
    s32 val0;
    u16 tmp[3];
    s32 cnt1;
    s32 cnt2;
    s32 ptr;
    s32 k5;

    sum1 = D_801C7748 + D_8018AB98;
    frac = sum1 & 0xFFF;
    sum2 = D_801C774A;
    sum2 += D_8018AB9A;

    threshold = -(sum1 * 1536) / 12288 - 0x22;

    ret = func_80047948(frac);
    val0 = (ret * sum2) >> 12;

    ret = func_8004787C(frac);
    k5 = D_8018ABA0;
    tmp[0] = val0;
    tmp[1] = threshold;
    tmp[2] = (ret * sum2) >> 12;

    cnt1 = *(s32 *)(a0 + 0x1C);
    tmp[1] -= D_8018AB9C + k5 * cnt1;

    *(s16 *)(a0 + 0x6) = tmp[0];
    *(s16 *)(a0 + 0xA) = tmp[1];
    *(s16 *)(a0 + 0xE) = tmp[2];

    ptr = *(s32 *)(a0 + 0x20);
    *(s16 *)(ptr + 0x12) = ((-sum1) & 0xFFF) + 0x400;

    cnt2 = *(s32 *)(a0 + 0x1C) + 1;
    *(s32 *)(a0 + 0x1C) = cnt2;

    if (cnt2 >= D_8018AB9E) {
        *(s32 *)(a0 + 0x1C) = 0;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    }
}


#include "common.h"

/* Row-specific tuning constants for this instance (family group with func_80183630/func_80183AF0 etc.
   each hardcodes its OWN row of a 5 x s16 table spaced 0xC apart -- not an indexed array access in
   this TU, see wave card notes). Types by access width (law 2 -- absent from this TU). */
extern s16 D_801C7748;
extern s16 D_801C774A;
extern s16 D_8018ABA4;
extern s16 D_8018ABA6;
extern u16 D_8018ABA8;
extern s16 D_8018ABAA;
extern s16 D_8018ABAC;

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80183790(s32 a0) {
    s32 sum1;
    s32 sum2;
    s32 frac;
    s32 threshold;
    s32 ret;
    s32 val0;
    u16 tmp[3];
    s32 cnt1;
    s32 cnt2;
    s32 ptr;
    s32 k5;

    sum1 = D_801C7748 + D_8018ABA4;
    frac = sum1 & 0xFFF;
    sum2 = D_801C774A + D_8018ABA6;

    threshold = -(sum1 * 1536) / 12288 - 0x22;

    ret = func_80047948(frac);
    val0 = (ret * sum2) >> 12;

    ret = func_8004787C(frac);
    k5 = D_8018ABAC;
    tmp[0] = val0;
    tmp[1] = threshold;
    tmp[2] = (ret * sum2) >> 12;

    cnt1 = *(s32 *)(a0 + 0x1C);
    tmp[1] -= D_8018ABA8 + k5 * cnt1;

    *(s16 *)(a0 + 0x6) = tmp[0];
    *(s16 *)(a0 + 0xA) = tmp[1];
    *(s16 *)(a0 + 0xE) = tmp[2];

    ptr = *(s32 *)(a0 + 0x20);
    *(s16 *)(ptr + 0x12) = (-sum1) & 0xFFF;

    cnt2 = *(s32 *)(a0 + 0x1C) + 1;
    *(s32 *)(a0 + 0x1C) = cnt2;

    if (cnt2 >= D_8018ABAA) {
        *(s32 *)(a0 + 0x1C) = 0x3C;
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    }
}


extern void func_8012A828(s32, void*);
extern M2C_UNK D_8018A568;

void func_801838F0(void *arg0) {
    ((void (*)(void *, void *))func_8012A828)(arg0, &D_8018A568);
    *(s16 *)((s32)arg0 + 0x2) = 0x3;
    *(s16 *)((s32)arg0 + 0x34) = 0;
}


#include "common.h"

/* Structural twin of func_80183A7C (0.9704 similarity) in this TU: same
 * angle/sin/cos setup, same buf1/in3 layout, same call sequence, differing
 * only in the literal constants (offset, multiplier, data symbol, and the
 * two magic args at the tail). */

extern s16 D_801C7748;
extern u8  D_8018ABB0[];

extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B77C(void *, s32, void *);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_80013478(s32 a0, s32 a1);

void func_8018392C(s32 param_1) {
    s32 t;
    s32 x;
    s32 s2;
    s32 angle;
    s32 s1;
    s32 v0dead;
    s32 angle2;
    s32 r1;
    s32 sinVal;
    s32 r2;
    s32 cosVal;
    s32 posPtr;
    s32 out;
    s16 buf1[3];
    s32 in3[3];
    s32 v0;
    s32 v1;
    s32 outVal;

    t = D_801C7748 + 0x400;
    x = -(t * 1536);
    angle = t & 0xFFF;
    s2 = 0x180;
    s1 = x / 12288;

    r1 = func_80047948(angle);
    sinVal = (r1 * s2) >> 12;

    r2 = func_8004787C(angle);
    cosVal = (r2 * s2) >> 12;

    v0dead = s1 - 0x22;
    angle2 = s1 - 0x32;

    buf1[0] = (s16)sinVal;
    *(volatile s16 *)&buf1[1] = (s16)v0dead;
    buf1[1] = (s16)angle2;
    *((s16 *)&in3[0] + 1) = (s16)sinVal;
    *((s16 *)&in3[1] + 1) = (s16)angle2;
    buf1[2] = (s16)cosVal;
    *((s16 *)&in3[2] + 1) = (s16)cosVal;

    func_8012B14C(param_1, (s32)D_8018ABB0);
    func_8012AD80(param_1);

    posPtr = param_1 + 4;
    func_8012B77C(&out, posPtr, in3);

    outVal = out;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)outVal;

    v0 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), outVal >> 16, 6);

    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)v1;
    v0 = func_80013478(posPtr, (s32)buf1);

    v1 = 0x28;
    if (v0 < 0x1000) {
        v0 = *(u16 *)(param_1 + 0x34);
        *(s32 *)(param_1 + 0x1C) = v1;
        v0 = v0 + 1;
        *(u16 *)(param_1 + 0x34) = (s16)v0;
    }
}


#include "common.h"

/* Card func_80183A7C — fresh mass-lane crack (no banked twin, no cookbook hit
 * found for this shape). Layout derived purely from the target .s; struct/
 * field types are unknown so raw byte-offset casts are used throughout,
 * matching this TU's own established idiom (see func_80186688 etc.). */

extern s16 D_801C7748;
extern s16 D_801C774A;
extern u8  D_8018ABBC[];

extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_8012B77C(void *, s32, void *);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_80013478(s32 a0, s32 a1);

void func_80183A7C(s32 param_1) {
    s32 t;
    s32 x;
    s32 s2;
    s32 angle;
    s32 s1;
    s32 v0dead;
    s32 angle2;
    s32 r1;
    s32 sinVal;
    s32 r2;
    s32 cosVal;
    s32 posPtr;
    s32 out;
    s16 buf1[3];
    s32 in3[3];
    s32 v0;
    s32 v1;
    s32 outVal;

    t = D_801C7748 + 0x200;
    x = -(t * 1536);
    angle = t & 0xFFF;
    s2 = D_801C774A;
    s1 = x / 12288;

    r1 = func_80047948(angle);
    sinVal = (r1 * s2) >> 12;

    r2 = func_8004787C(angle);
    cosVal = (r2 * s2) >> 12;

    v0dead = s1 - 0x22;
    angle2 = s1 - 0x32;

    buf1[0] = (s16)sinVal;
    *(volatile s16 *)&buf1[1] = (s16)v0dead;
    buf1[1] = (s16)angle2;
    *((s16 *)&in3[0] + 1) = (s16)sinVal;
    *((s16 *)&in3[1] + 1) = (s16)angle2;
    buf1[2] = (s16)cosVal;
    *((s16 *)&in3[2] + 1) = (s16)cosVal;

    func_8012B14C(param_1, (s32)D_8018ABBC);
    func_8012AD80(param_1);

    posPtr = param_1 + 4;
    func_8012B77C(&out, posPtr, in3);

    outVal = out;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)outVal;

    v0 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), outVal >> 16, 4);

    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)v1;
    v0 = func_80013478(posPtr, (s32)buf1);

    v1 = 0x78;
    if (v0 < 0x1000) {
        v0 = *(u16 *)(param_1 + 0x34);
        *(s32 *)(param_1 + 0x1C) = v1;
        v0 = v0 + 1;
        *(u16 *)(param_1 + 0x34) = (s16)v0;
    }
}


#include "common.h"

/* Declarations copied verbatim from src/ov_SC01_084/ov_SC01_084_jr_8017CA80.c:
 *   func_80047D3C  @270,  func_80047948 @2207, func_8004787C @2208,
 *   func_8012B8E4  @4181, func_8012BEE8 @4182, func_8012A828 @3891,
 *   D_8018A568     @4003 (file-scope M2C_UNK spelling).
 * func_801807D8 has no C prototype in the TU (still INCLUDE_ASM @3668). */
extern s32 func_801807D8(s16 *a0);
extern s32 func_80047D3C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern M2C_UNK D_8018A568;

void func_80183BD0(s32 param_1) {
    s16 tmp[3];
    s32 t;
    s32 ss;
    s32 sq0;
    s32 sq1;
    s32 s2;
    s32 frac;
    s32 threshold;
    s32 sinRaw;
    s32 cosRaw;
    s32 sinVal;
    s32 cosVal;
    s32 ptr;
    s32 v0;
    unsigned short *p;

    tmp[0] = *(u16 *)(param_1 + 0x6);   /* +0x06 vel.x  */
    tmp[1] = *(u16 *)(param_1 + 0xA);   /* +0x0A vel.y  */
    tmp[2] = *(u16 *)(param_1 + 0xE);   /* +0x0E vel.z  */

    t = func_801807D8(tmp);
    sq0 = (s32)tmp[0] * (s32)tmp[0];
    sq1 = (s32)tmp[2] * (s32)tmp[2];
    ss = sq0 + sq1;
    s2 = func_80047D3C(ss);

    /* §193-B LEVER (this is the whole match): `t -= 4` is written BELOW the
     * func_80047D3C call.  combine.c:929 refuses to combine across a CALL_INSN,
     * so the `addu $s0,$v0,$zero` return-value copy survives as its own insn and
     * the subtract stays a separate `addiu $s0,$s0,-0x4` (90 ins, not 89).
     * sched2 then sinks BOTH of them into the second mult->mflo interlock slot,
     * reproducing the target's `mult ; addu s0 ; addiu s0 ; mflo` filler order.
     * Writing `t -= 4` above the call (or fencing it with a zero-byte __asm__)
     * either folds to one `addiu $s0,$v0,-4` or leaves only ONE filler before
     * the mflo -- both were tried and both miss. */
    t -= 4;

    frac = t & 0xFFF;
    threshold = -(t * 1536) / 12288;

    sinRaw = func_80047948(frac);
    sinVal = (sinRaw * s2) >> 12;

    cosRaw = func_8004787C(frac);
    cosVal = (cosRaw * s2) >> 12;

    tmp[0] = (s16)sinVal;
    /* §194-J: the target really does store 0x12($sp) twice back-to-back
     * (sh $v0 then sh $s1); the first store must be volatile or flow.c's
     * last_mem_set deletes it. */
    *(volatile s16 *)&tmp[1] = (s16)(threshold - 0x22);
    tmp[1] = (s16)(threshold - 0x32);
    tmp[2] = (s16)cosVal;

    *(s16 *)(param_1 + 0x6) = tmp[0];
    *(s16 *)(param_1 + 0xA) = tmp[1];
    *(s16 *)(param_1 + 0xE) = tmp[2];

    v0 = func_8012B8E4(param_1, 8);
    ptr = *(s32 *)(param_1 + 0x20);
    p = (unsigned short *)(ptr + 0x12);
    *p = (unsigned short)(*p + v0);

    if (func_8012BEE8(param_1) != 0) {
        func_8012A828(param_1, &D_8018A568);
        *(s16 *)(param_1 + 0x2) = 3;
        *(s16 *)(param_1 + 0x34) = 0;
    }
}


extern void (*D_8018ABC8[])();
extern void (*D_8018ABD8[])();

void func_80183D38(void *a0) {
    if (*(s16 *)((u8 *)a0 + 0x70) != 1) {
        D_8018ABC8[*(u16 *)((u8 *)a0 + 0x2)](a0);
    } else {
        D_8018ABD8[*(u16 *)((u8 *)a0 + 0x2)](a0);
    }
}


#include "common.h"

/* func_80183DA4 - ov_SC01_084 / ov_SC01_084_jr_8017F690 - MATCH (187 ins)
 *
 * A vertical "beam"/ribbon builder: walks a start SVECTOR downward 64 units per
 * step, projects two consecutive rungs through RotTransPers, and while both
 * rungs are in front of the OT window emits one textured POLY_FT4 quad per step
 * linked into D_800A651C[D_800B9A02].a at otz*4.  The loop is a `for (;;)` -- it
 * only ever leaves through an early return.
 *
 * TU-adopted spellings (law 2, grepped against this TU):
 *   D_801270C0  u16 (TU:1125)  -> read with the TU's own (s32)(s16) idiom so the
 *                                 compare emits `lh`, not `lhu`.
 *   D_800B9A02  s16 (TU:2463/2465) -> indexed as (u16) to get the target's `lhu`
 *                                 (func_801809C4 does the same via a u16* alias).
 *   D_800A651C  OtBlk (0x14 stride, .a at +0) - block scope, exactly as
 *               func_801809C4 declares it (engine_core.h DEFINE_ macros declare
 *               this symbol scalar inside their own bodies).
 *   func_8004914C/func_800491AC void(void*) (TU:2637/2638); RotTransPers
 *   s32(s32,s32,s32*,s32*) (TU:4971); func_80010A08 void*(s32) (TU:3541);
 *   AddPrim s32(s32,void*) (TU:3543).  D_801C74D8 is undeclared anywhere and is
 *   typed s32 from its own lw/sw width.
 *
 * ---- THE THREE LEVERS (139 -> 72 -> 11 -> 4 -> 0) -----------------------
 *
 * 1. FRAME LAYOUT: sxy0/sxy1 are s32 SCALARS, and the 16-bit reads go through a
 *    cast-to-struct-pointer, `((DVec *)&sxy0)->vx`.  Both halves are load-bearing
 *    and they pull in opposite directions:
 *      - As real DVECTOR structs the decls are BLKmode, so expand_decl gives them
 *        a slot AT DECLARATION TIME via assign_stack_temp(...,align 0) ==
 *        BIGGEST_ALIGNMENT (8 on this target).  That yields sxy0@0x20 sxy1@0x28
 *        and pushes pp/flag (which only get slots later, when `&pp` first calls
 *        mark_addressable/put_var_into_stack) to 0x30/0x34 -> frame 0x68, not
 *        0x60.  As SImode scalars all four slots are handed out at &-time, in
 *        &-order: sxy0 0x20, pp 0x24, flag 0x28, sxy1 0x2C -- the target exactly.
 *      - But the LOAD must still be MEM_IN_STRUCT_P.  Written `((u16*)&sxy0)[0]`
 *        the MEM is (not-in-struct, non-varying) and gcc-2.7.2 true_dependence
 *        drops the dependence against the (in-struct, varying) `p->x0` store, so
 *        cse keeps the load live across it and folds the x0/x1 (and x2/x3) pair
 *        onto one `lhu` -- 7 instructions short, with the load-delay nops gone.
 *        A COMPONENT_REF through the cast sets MEM_IN_STRUCT_P, the store re-kills
 *        the value, and all eight `lhu`+nop reloads come back.
 *        (This is the mirror image of func_801809C4's note 2 in this same TU: there
 *        an ARRAY_REF was needed to SET MEM_IN_STRUCT_P on a global read.)
 *
 * 2. GUARD EVALUATION ORDER: `if ((D_801C74D8 >> 3) >= RotTransPers(...))` puts
 *    the global read BEFORE the jal, where cse finds the previous block's
 *    `sra` still valid, parks it in a callee-saved reg and never reloads (-4:
 *    lui/lw/nop/sra).  Naming the call result first --
 *      otz2 = RotTransPers(...);  d = D_801C74D8;  if ((d >> 3) >= otz2)
 *    -- forces the reload the target has, and that single reload then also feeds
 *    the `d << 3` dividend (the target's $a1 reuse).
 *
 * 3. $s7=0xF0 AND $s5=0 ARE ORDINARY PRE-LOOP VARIABLES, NOT loop.c MOVABLES.
 *    A literal `p->v0 = 0` compiles to `sb $zero` (no register at all), so a
 *    register holding 0 already proves a variable; and `addiu $v0,$s5,0x3F`
 *    proves `v + 63`, not the constant 63.  The 0xF0 half is provable only from
 *    the preheader SCHEDULE ORDER: loop.c emits its movables last, immediately
 *    before the loop, so anything hoisted sorts after every source statement.
 *    The target's order is s7=0xF0, s5=0, s4=&pp, s3=&flag, s6=0xF7 -- 0xF0 and 0
 *    ahead of the two address movables -> both must be explicit source statements
 *    (`uu = 0xF0; vv = 0;`) ahead of the loop, while 0xF7 stays a literal and is
 *    the one true movable, landing last.  Writing only `vv = 0` gives
 *    s5,s4,s3,s7 -- 4 mismatches that no amount of statement shuffling inside the
 *    loop can fix.
 *
 * Minor: `p->tpage` is stored BEFORE `p->clut` in source; the scheduler then fills
 * the tpage load-delay with `addu $a0,$s2` + the clut store, which is the target's
 * lhu/addu/sh-clut/sh-tpage quartet.  The reverse source order flips that pair.
 */

typedef struct { s32 a; s32 b[4]; } OtBlk_80183DA4;        /* 0x14 stride */
typedef struct { u16 vx, vy, vz, pad; } SVec_80183DA4;     /* 0x08 stride */
typedef struct { u16 vx, vy; } DVec_80183DA4;              /* read through a cast */

typedef struct {
    u32 tag;                    /* 0x00 */
    u8  r0, g0, b0, code;       /* 0x04 */
    s16 x0, y0;                 /* 0x08 */
    u8  u0, v0;  u16 clut;      /* 0x0C */
    s16 x1, y1;                 /* 0x10 */
    u8  u1, v1;  u16 tpage;     /* 0x14 */
    s16 x2, y2;                 /* 0x18 */
    u8  u2, v2;  u16 pad2;      /* 0x1C */
    s16 x3, y3;                 /* 0x20 */
    u8  u3, v3;  u16 pad3;      /* 0x24 */
} Ft4_80183DA4;                 /* 0x28 */

extern u16 D_801270C0;
extern u8  D_800AF648;
extern s32 D_80126950;
extern s32 D_801C74D8;
extern s16 D_800B9A02;

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32  GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32  GetClut(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void *func_80010A08(s32 a0);
extern void SetPolyFT4(void *a0);
extern s32  AddPrim(s32 a0, void *a1);

void func_80183DA4(SVec_80183DA4 *arg0) {
    extern OtBlk_80183DA4 D_800A651C[];

    SVec_80183DA4 tmp;      /* 0x10 */
    SVec_80183DA4 vec;      /* 0x18 */
    s32 sxy0;               /* 0x20 */
    s32 pp;                 /* 0x24 */
    s32 flag;               /* 0x28 */
    s32 sxy1;               /* 0x2C */
    u16 tpage;
    u16 clut;
    Ft4_80183DA4 *p;
    s32 ot;
    s32 otz;
    s32 otz2;
    s32 d;
    s32 w;
    s32 uu;
    s32 vv;

    if ((s16)D_801270C0 == 3) {
        return;
    }
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    D_801C74D8 = D_80126950;
    tpage = GetTPage(0, 0, 0x300, 0x100);
    clut = GetClut(0x160, 0x14C);
    vec.vx = arg0->vx;
    vec.vy = arg0->vy;
    vec.vz = arg0->vz;
    uu = 0xF0;
    vv = 0;

    for (;;) {
        tmp.vx = vec.vx;
        tmp.vy = vec.vy - 0x40;
        tmp.vz = vec.vz;
        otz = RotTransPers((s32)&tmp, (s32)&sxy0, &pp, &flag);
        if ((D_801C74D8 >> 3) >= otz) {
            return;
        }
        if (flag < 0) {
            return;
        }
        otz2 = RotTransPers((s32)&vec, (s32)&sxy1, &pp, &flag);
        d = D_801C74D8;
        if ((d >> 3) >= otz2) {
            return;
        }
        if (flag < 0) {
            return;
        }
        ot = D_800A651C[(u16)D_800B9A02].a + otz * 4;
        w = (d << 3) / (otz * 4);
        if ((s16)((DVec_80183DA4 *)&sxy0)->vy < 120) {
            if ((s16)((DVec_80183DA4 *)&sxy1)->vy < -119) {
                return;
            }
            if ((s16)w >= 2) {
                p = (Ft4_80183DA4 *)func_80010A08(0x28);
                *(s32 *)((u8 *)p + 4) = 0x808080;
                SetPolyFT4(p);
                p->x0 = ((DVec_80183DA4 *)&sxy0)->vx - w;
                p->y0 = ((DVec_80183DA4 *)&sxy0)->vy;
                p->x1 = ((DVec_80183DA4 *)&sxy0)->vx + w;
                p->y1 = ((DVec_80183DA4 *)&sxy0)->vy;
                p->x2 = ((DVec_80183DA4 *)&sxy1)->vx - w;
                p->y2 = ((DVec_80183DA4 *)&sxy1)->vy;
                p->x3 = ((DVec_80183DA4 *)&sxy1)->vx + w;
                p->y3 = ((DVec_80183DA4 *)&sxy1)->vy;
                p->u0 = uu;
                p->v0 = vv;
                p->u1 = 0xF7;
                p->v1 = vv;
                p->u2 = uu;
                p->v2 = vv + 0x3F;
                p->u3 = 0xF7;
                p->v3 = vv + 0x3F;
                p->tpage = tpage;
                p->clut = clut;
                AddPrim(ot, p);
            }
        }
        vec.vy -= 0x40;
    }
}


extern void func_8012B21C(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_80126B62;

void func_80184090(void *a0) {
    u16 t;

    t = *(u16 *)((s32)a0 + 0x5C);
    *(u16 *)((s32)a0 + 0x2) = 2;
    *(u16 *)((s32)a0 + 0x34) = 0;
    *(u16 *)((s32)a0 + 0x5C) = t & 0x7FFE;
    func_8012B21C(a0);
    *(s32 *)((s32)a0 + 0x1C) = 0;
    *(u16 *)((s32)a0 + 0x24) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)((s32)a0 + 0x28) = *(u16 *)((s32)a0 + 0xE);
    *(u16 *)((s32)a0 + 0x26) = D_80126B62;
    func_8002D4C8(0x4B4, 0);
}



extern void (*D_8018AC10[])(void);

void func_801840FC(void *a0) {
    D_8018AC10[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* func_80184138 - ov_SC01_084 / ov_SC01_084_jr_8017F690 (187 ins)
 *
 * Structural twin of func_80183DA4 (same TU, MATCH, 187 ins) -- the same
 * vertical "beam"/ribbon builder with a different texture window and step:
 *   D_801C74D8 -> D_801C74DC, GetClut y 0x14C -> 0x14D, uu 0xF0 -> 0xF8,
 *   the u1/u3 literal 0xF7 -> 0xFF, and the tail step vec.vy -= 0x40 -> 0x3C.
 * All three of func_80183DA4's levers carry over verbatim:
 *   1. sxy0/sxy1 are s32 SCALARS read through a cast-to-struct-pointer, so the
 *      four stack slots are handed out in &-order (0x20/0x24/0x28/0x2C) while
 *      the loads stay MEM_IN_STRUCT_P and are re-killed by the p->x0 store.
 *   2. `otz2 = RotTransPers(...); d = D_801C74DC; if ((d >> 3) >= otz2)` forces
 *      the reload the target has, and that reload feeds the `d << 3` dividend.
 *   3. `uu = 0xF8; vv = 0;` are ordinary pre-loop statements (they precede the
 *      &pp/&flag address movables in the preheader); 0xFF stays a literal and is
 *      the one true loop.c movable, landing last.
 */

typedef struct { s32 a; s32 b[4]; } OtBlk_80184138;        /* 0x14 stride */
typedef struct { u16 vx, vy, vz, pad; } SVec_80184138;     /* 0x08 stride */
typedef struct { u16 vx, vy; } DVec_80184138;              /* read through a cast */

typedef struct {
    u32 tag;                    /* 0x00 */
    u8  r0, g0, b0, code;       /* 0x04 */
    s16 x0, y0;                 /* 0x08 */
    u8  u0, v0;  u16 clut;      /* 0x0C */
    s16 x1, y1;                 /* 0x10 */
    u8  u1, v1;  u16 tpage;     /* 0x14 */
    s16 x2, y2;                 /* 0x18 */
    u8  u2, v2;  u16 pad2;      /* 0x1C */
    s16 x3, y3;                 /* 0x20 */
    u8  u3, v3;  u16 pad3;      /* 0x24 */
} Ft4_80184138;                 /* 0x28 */


extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32  GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32  GetClut(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void *func_80010A08(s32 a0);
extern void SetPolyFT4(void *a0);
extern s32  AddPrim(s32 a0, void *a1);

void func_80184138(SVec_80184138 *arg0) {

    extern s32 D_801C74DC;
    extern OtBlk_80184138 D_800A651C[];

    SVec_80184138 tmp;      /* 0x10 */
    SVec_80184138 vec;      /* 0x18 */
    s32 sxy0;               /* 0x20 */
    s32 pp;                 /* 0x24 */
    s32 flag;               /* 0x28 */
    s32 sxy1;               /* 0x2C */
    u16 tpage;
    u16 clut;
    Ft4_80184138 *p;
    s32 ot;
    s32 otz;
    s32 otz2;
    s32 d;
    s32 w;
    s32 uu;
    s32 vv;

    if ((s16)D_801270C0 == 3) {
        return;
    }
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    D_801C74DC = D_80126950;
    tpage = GetTPage(0, 0, 0x300, 0x100);
    clut = GetClut(0x160, 0x14D);
    vec.vx = arg0->vx;
    vec.vy = arg0->vy;
    vec.vz = arg0->vz;
    uu = 0xF8;
    vv = 0;

    for (;;) {
        tmp.vx = vec.vx;
        tmp.vy = vec.vy - 0x40;
        tmp.vz = vec.vz;
        otz = RotTransPers((s32)&tmp, (s32)&sxy0, &pp, &flag);
        if ((D_801C74DC >> 3) >= otz) {
            return;
        }
        if (flag < 0) {
            return;
        }
        otz2 = RotTransPers((s32)&vec, (s32)&sxy1, &pp, &flag);
        d = D_801C74DC;
        if ((d >> 3) >= otz2) {
            return;
        }
        if (flag < 0) {
            return;
        }
        ot = D_800A651C[(u16)D_800B9A02].a + otz * 4;
        w = (d << 3) / (otz * 4);
        if ((s16)((DVec_80184138 *)&sxy0)->vy < 120) {
            if ((s16)((DVec_80184138 *)&sxy1)->vy < -119) {
                return;
            }
            if ((s16)w >= 2) {
                p = (Ft4_80184138 *)func_80010A08(0x28);
                *(s32 *)((u8 *)p + 4) = 0x808080;
                SetPolyFT4(p);
                p->x0 = ((DVec_80184138 *)&sxy0)->vx - w;
                p->y0 = ((DVec_80184138 *)&sxy0)->vy;
                p->x1 = ((DVec_80184138 *)&sxy0)->vx + w;
                p->y1 = ((DVec_80184138 *)&sxy0)->vy;
                p->x2 = ((DVec_80184138 *)&sxy1)->vx - w;
                p->y2 = ((DVec_80184138 *)&sxy1)->vy;
                p->x3 = ((DVec_80184138 *)&sxy1)->vx + w;
                p->y3 = ((DVec_80184138 *)&sxy1)->vy;
                p->u0 = uu;
                p->v0 = vv;
                p->u1 = 0xFF;
                p->v1 = vv;
                p->u2 = uu;
                p->v2 = vv + 0x3F;
                p->u3 = 0xFF;
                p->v3 = vv + 0x3F;
                p->tpage = tpage;
                p->clut = clut;
                AddPrim(ot, p);
            }
        }
        vec.vy -= 0x3C;
    }
}



extern void (*D_8018AC2C[])(void);

void func_80184424(void *a0) {
    D_8018AC2C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Card func_80184460 — fresh mass-lane crack (no banked twin, no cookbook hit).
 * Layout derived purely from the target .s; struct/field types unknown so raw
 * byte-offset casts are used throughout, matching this TU's own established
 * idiom (see func_80183A7C / func_8017DECC etc).
 *
 * TU-adopted signatures (law 2 — verified by grep against this TU):
 *   func_8012B0B4(unsigned int *, int, int)   void   (TU:3728)
 *   func_8012AD80(s32)                        void   (TU:4028)
 *   func_8012C218(void *)                     void   (TU:4547)
 *   func_8012E32C(void)                       void   (TU:3729)
 *   RotTransPers(s32, s32, s32 *, s32 *)      s32    (TU:3731)
 *   D_80126B62                                u16    (TU:1795/3263), read via
 *                                             the TU's own (s32)(s16) idiom
 * func_801845A0 is the next INCLUDE_ASM stub in this same TU (TU:4129) — no
 * declaration exists anywhere in the TU, so it is typed from this call site.
 * D_801C774C / D_80126CBA / D_801270CC are likewise undeclared in this TU and
 * are typed by this function's own access widths (lh/lh/sw -> s16/s16/s32).
 * Other overlays' TUs give D_801C774C/D_801270CC different types — that is
 * different overlay-local data at the same relocatable offset, not evidence.
 *
 * ---- THE LEVER (second-pass repair; new cookbook candidate) --------------
 * The first pass parked at closeness=40 on a BRANCH-POLARITY/LENGTH-DRIFT
 * residual: the D_80126CBA test wants
 *     beqz -> .L80184510 / fallthrough = {li 1; sh 0xFC; j .L80184520}
 *              .L80184510: {call func_801845A0; j epilogue}
 * but EVERY spelling of the inner if/else (both polarities, explicit gotos,
 * shared-epilogue goto) compiled to the inverted, block-SWAPPED shape
 * (bnez -> store-block / fallthrough = call).
 *
 * Root cause found in the compiler source: jump.c:1799 "Look for
 * if (foo) bar; else break;" — a RANGE-SWAP that inverts the condjump and
 * physically splices the two arms when
 *     JUMP_LABEL(insn) == next_label(insn) == label1, LABEL_NUSES(label1)==1,
 *     range1 ends in a simplejump to label2 == next_label(label1),
 *     range2 ends in a jump followed by a BARRIER.
 * Our if/else satisfies all of those, so the swap is unavoidable ONCE IT IS
 * REACHED. But the guard is `! first` (jump.c:1818): jump_optimize's
 * `while (changed)` loop only clears `first` at the END of a round
 * (jump.c:2037), so the swap can only fire in round 2+ — i.e. only if
 * SOMETHING ELSE IN THE FUNCTION changed in round 1.
 *
 * `if (X) goto L;` and mid-function `return;` both expand to a conditional
 * jump around an unconditional jump, which jump.c:1737 collapses in round 1 —
 * that single change is what enabled round 2 and swapped our arms. Writing
 * the whole guard chain as nested/&&-joined ifs (no goto, no early return
 * except the one the target itself needs) leaves jump pass 1 with NOTHING to
 * do in round 1, the loop exits, and the arms stay in source order.
 * ⇒ Class name for §31: "jump.c:1799 range-swap, armed by a round-1 change".
 *    The C dial is NOT the if's polarity — it is REMOVING the unrelated
 *    goto/early-return elsewhere in the function.
 *
 * The $v0/$v1 pins are still load-bearing (a separate, real regalloc-order
 * residual in the func_8012AD80 setup block: without them the 0x64 reloads
 * and the a0 copy reorder, 11 mismatches).
 */
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8012E32C(void);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_801845A0(void *a0);
extern u16 D_80126B62;
extern s16 D_801C774C;
extern s16 D_80126CBA;
extern s32 D_801270CC;

void func_80184460(void *a0) {
    void *s0;
    void *v0p;
    s32 buf[2];      /* sp+0x10..0x17 — reused below as the u16 triple for
                       * func_8012E32C / RotTransPers' input vector */
    s32 sxy;         /* sp+0x18 */
    s32 pp;          /* sp+0x1c */
    s32 flag;        /* sp+0x20 */
    s32 v0;
    s32 v1;

    s0 = a0;

    v0p = *(void **)((u8 *)s0 + 0x20);
    func_8012B0B4((unsigned int *)buf, *(s16 *)((u8 *)v0p + 0x12), 0x18);

    /* offset 0x64 is re-dereferenced (not cached) — matches this TU's
     * per-access raw-cast idiom and the target's two separate loads. */
    v1 = buf[0];
    v0 = *(u16 *)((u8 *)*(void **)((u8 *)s0 + 0x64) + 0x6);
    *(s16 *)((u8 *)s0 + 0x6) = (v0 + v1);
    v0 = *(u16 *)((u8 *)*(void **)((u8 *)s0 + 0x64) + 0xE) + (v1 >> 16);
    *(s16 *)((u8 *)s0 + 0xE) = v0;
    func_8012AD80((s32)s0);

    if (*(s16 *)((u8 *)s0 + 0xFC) == 0 &&
        *(s16 *)((u8 *)s0 + 0xA) <= (s32)(s16)D_80126B62 &&
        D_801C774C == 1) {
        if (D_80126CBA != 0) {
            *(s16 *)((u8 *)s0 + 0xFC) = 1;
        } else {
            func_801845A0(s0);
            return;
        }
    }

    if (*(s16 *)((u8 *)s0 + 0xFC) == 1) {
        *(u16 *)((u8 *)buf + 0x0) = *(u16 *)((u8 *)s0 + 0x6);
        *(u16 *)((u8 *)buf + 0x2) = *(u16 *)((u8 *)s0 + 0xA);
        *(u16 *)((u8 *)buf + 0x4) = *(u16 *)((u8 *)s0 + 0xE);
        func_8012E32C();

        RotTransPers((s32)buf, (s32)&sxy, &pp, &flag);

        if (*((s16 *)&sxy + 1) < -0x6F) {
            D_801270CC = 0;
            func_8012C218(s0);
        }
    }
}


void func_801845A0(void *arg0) {
    extern void func_8012A828(s32, void*);
    extern s32 D_801A2750;

    ((void (*)(void *, void *))func_8012A828)(arg0, &D_801A2750);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x2;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x1E;
    *(s16 *)((u8 *)arg0 + 0x34) = 0;
    *(s16 *)((u8 *)arg0 + 0xFC) = 1;
}


struct S845EC_in { s16 f00, f02, f04, f06, f08, f0A, f0C, f0E; s32 f10; };
struct S845EC_out { s16 a, b, c; };

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern u8 D_8018AA6C[];

s32 func_801845EC(s32 a0, s32 a1)
{
    s32 s1;
    struct S845EC_in in;
    struct S845EC_out out;

    func_8012F214(a0, (s32)&D_8018AA6C[a1 * 8], (s32)&out);
    in.f00 = out.a;
    in.f02 = out.b;
    in.f04 = out.c;
    in.f06 = 0x20;
    in.f08 = a1;
    in.f0A = 0;
    in.f10 = 0;
    in.f0E = 0;
    s1 = func_8012C51C((void *)&in, a0);

    if (a1 == 0 && s1 != 0) {
        s32 t = *(s32 *)(a0 + 0x20);
        if (t != 0) {
            *(unsigned short *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(unsigned short *)(t + 0x12);
        }
        func_8012B2CC(s1);
    }
    return s1;
}


#include "common.h"

/* wave_p31z func_801846B4 — mass lane, fresh crack.
 * Seed twin: md_SC07_003:func_801A27A4 (sim 0.5714) — same S80190C84_846B4 "spawn
 * record" struct + func_8012C51C tail, minus the tmp.fC assignment (target
 * asm never writes sp+0x24, so that field is left uninitialized on purpose).
 * TU-neighbour func_80184C90 supplies the "*p = *p + v" accumulate idiom and
 * the int param_1 / raw-pointer-cast house style adopted throughout.
 * S80190C84/SV3 are real shared/engine_types.h types (src/shared/engine_types.h:612,1337);
 * re-declared locally here per the md_SC07_003.c precedent since this standalone
 * draft can't reach the src/shared/ include path. */

struct S80190C84_846B4 {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
};

typedef struct { short a, b, c; } SV3_846B4;

extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_80185E68(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32, void*);
extern void func_8012B200(u8 *a0);

extern s32 D_8018AA74;
extern s32 D_801A2378;
extern s32 D_8018AC34;

void func_801846B4(int param_1)
{
    s32 t;
    s32 cond;
    s32 v;
    unsigned short *p;

    {
        unsigned int buf;
        func_8012B0B4(&buf, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), 0x18);
        t = (s32)buf;
    }

    *(s16 *)(param_1 + 0x6) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x6) + t;
    *(s16 *)(param_1 + 0xE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE) + (t >> 16);
    v = func_8012B8E4(param_1, 4);

    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);

    cond = *(s32 *)(param_1 + 0x1C);
    if (cond == 0x11) {
        func_80185E68(param_1, (s32)&D_8018AA74);
    } else if (cond == 0xF) {
        struct S80190C84_846B4 tmp;
        SV3_846B4 out;

        func_8012F214(param_1, (s32)&D_8018AA74, (s32)&out);
        tmp.f0 = out.a;
        tmp.f2 = out.b;
        tmp.f4 = out.c;
        tmp.f6 = 0x20;
        tmp.f8 = 1;
        tmp.fA = 0;
        tmp.f10 = 0;
        tmp.fE = 0;
        func_8012C51C(&tmp, param_1);
    }

    if (func_8012BEE8(param_1) != 0) {
        func_8012A828(param_1, (void *)&D_801A2378);
        *(s16 *)(param_1 + 0x2) = 1;
        func_8012B200((u8 *)param_1);
        *(s32 *)(param_1 + 0x14) = D_8018AC34;
    }
}


extern void (*D_8018AC38[])(void);

void func_801847F8(void *a0) {
    D_8018AC38[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80184834(s32 param_1) {
    extern s32 func_80014C54(s32, s32, s32);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 D_8018A978[];
    s16 v;
    u16 t;
    s32 iVar3;
    s32 base;

    v = func_80014C54(1, 0, 0x40);
    if (v != 0) {
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) += 0x200;
    }
    v = func_80014C54(1, 0, 0x20);
    if (v != 0) {
        t = *(u16 *)(param_1 + 0xFC) + 1;
        *(u16 *)(param_1 + 0xFC) = t;
        base = D_8018A978[*(s16 *)(param_1 + 0x70)];
        iVar3 = *(s32 *)(((t << 16) >> 14) + base);
        if (iVar3 == 0) {
            *(u16 *)(param_1 + 0xFC) = 0;
            iVar3 = *(s32 *)D_8018A978[*(s16 *)(param_1 + 0x70)];
        }
        func_8012A828(param_1, (void *)iVar3);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern void (*D_8018A984[])(void);
extern void (*D_8018A978[])(void);

void func_80184908(s32 param_1)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    func_8001C214(v0, (s32)D_8018A984[*(s16 *)(param_1 + 0x70)]);
    func_8012A828(param_1, ((void **)D_8018A978[*(s16 *)(param_1 + 0x70)])[*(s16 *)(param_1 + 0xFC)]);
    *(u16 *)(param_1 + 2) = 1;
}


extern s32 func_8012BEE8(s32);
    extern void func_80180CBC(s32);
    void func_801849A0(s32 arg0) {
        if (func_8012BEE8(arg0)) {
            func_80180CBC(arg0);
        }
    }


void func_801849D8(void *a0) {
        M2C_FIELD(a0, s16 *, 0xA) = -0x4BD;
    }


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8005C2C8(s32 a0, s32 a1);
extern u8 D_801BE010[];
extern s32 D_80186B78;
extern u8 D_8018A9C0[];
extern s16 D_8018A91A;
extern s16 D_801C7748;

void func_801849E4(s32 param_1) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    *(u32 *)(v0 + 4) |= 0x70000000;
    func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_801BE010);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0xBE, 0xD0);
    *(s32 *)(param_1 + 0x58) = (s32)D_8018A9C0;
    *(u16 *)(param_1 + 0x5C) |= 0x8000;
    D_8018A91A = -1;
    func_8012A828(param_1, &D_80186B78);
    *(u16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 0x14;
    *(s32 *)(param_1 + 0xE0) = 0;
    *(s32 *)(param_1 + 0xDC) = 0;
    func_8012B2CC(param_1);
    *(s32 *)(param_1 + 0xCC) = func_8012C588(0x17, 0);
    func_8005C2C8((s32)&D_801C7748, 0xC);
}


extern void func_8012CBA4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_801818E0();
void func_80184AD0(s32 a0) {
    func_8012CBA4(a0);
    if (func_8012BEE8(a0)) {
        func_801818E0(a0);
    }
}


extern void (*D_8018AA40)(void *);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_80181978(void *a0);
extern void func_80181920(void *a0);

void func_80184B10(s32 *a0)
{
    s32 s1 = (s32)D_8018AA40;
    if (func_8012BEE8((s32)a0) != 0) {
        if (func_8012BD3C((s32)a0, 0x400, s1 * s1) != 0) {
            func_80181978(a0);
        } else {
            func_80181920(a0);
        }
    }
}


#include "common.h"

extern void func_8012CBA4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B21C(void *a0);

extern s32 D_8018AA44;
extern u8 D_801A1820[];

void func_80184B80(s32 a0) {
    s32 sp10[3];
    s32 ret;
    s32 v0;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = D_8018AA44;

    if (*(u16 *)(a0 + 0x34) == 0) {
        v0 = *(s32 *)(a0 + 0x20);
        ret = func_8012B608(*(s16 *)(v0 + 0x12), *(s16 *)(a0 + 0xDC) + 0x800, 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += ret;
        if (*(s32 *)(a0 + 0x1C) == 0x28) {
            *(u16 *)(a0 + 0x34) = 1;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (*(u16 *)(a0 + 0xDC) + 0x800) & 0xFFF;
            func_8012B2CC(a0);
            func_8012B21C((void *)a0);
            func_8012B14C(a0, (s32)sp10);
        }
    } else {
        /* TU declares func_8012CBA4 void (line 4162); this call site uses the
         * return value, so adopt the TU prototype and cast at the call (idiom9). */
        if (((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) {
            *(s32 *)(a0 + 0x14) = 0;
        }
    }

    if (func_8012BEE8(a0)) {
        func_8012A828(a0, D_801A1820);
        *(s16 *)(a0 + 0x2) = 1;
        func_8012B21C((void *)a0);
        *(s32 *)(a0 + 0x1C) = 0x14;
    }
}



// @class: plumbing
// @unstuck(P36): none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801819D0(s32 a0);

void func_80184C90(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        func_801819D0(param_1);
    }
}


extern s32 func_80143B6C(s32 arg0, s32 arg1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B21C(void *a0);
extern u8 D_801A1820[];

void func_80184CE8(s32 a0) {
    u16 timer;

    timer = *(u16 *)(a0 + 0xFC) - 1;
    *(u16 *)(a0 + 0xFC) = timer;
    if ((s16)timer <= 0) {
        func_80143B6C(a0, 0);
        *(u16 *)(a0 + 0xFC) = 8;
    }
    if (((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) {
        *(s32 *)(a0 + 0x14) = 0;
    }
    if (func_8012BEE8(a0)) {
        func_8012A828(a0, D_801A1820);
        *(u16 *)(a0 + 2) = 1;
        func_8012B21C((void *)a0);
        *(s32 *)(a0 + 0x1C) = 0x14;
    }
}


void func_80184D88(void) {
}

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B21C(void *a0);
extern s32 func_80143970(s32 a0);

void func_80184D90(void *a0) {
    extern u8 D_80191B50[];
    extern u8 D_801A1820[];
    s32 v0;
    s32 v1;
    s32 v2;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&(*(s32 *)D_80191B50));
        v1 = *(s32 *)((s32)a0 + 0x20);
        v2 = *(u16 *)((s32)a0 + 0xA);
        v1 = *(u16 *)(v1 + 0x12);
        v2 = v2 - 0x80;
        *(u16 *)((s32)a0 + 0xA) = v2;
        *(u16 *)((s32)a0 + 0xDC) = v1;
        func_80143970((s32)a0);
        func_8012A828((s32)a0, (s32)&D_801A1820);
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012B21C(a0);
        *(s32 *)((s32)a0 + 0x1C) = 0x14;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_801807D8(s16 *a0);
extern s32 D_801A1A10;

void func_80184E28(s32 param_1)
{
    s16 tmp[3];
    s32 sq;

    if (func_8012BEE8(param_1) != 0) {
        *(u8 *)(param_1 + 0xC1) = 0;
        *(s16 *)(param_1 + 0x2) = 1;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801A1A10);
        *(s32 *)(param_1 + 0x1C) = 0xA;
        *(u16 *)(param_1 + 0x5C) |= 0x8000;
        *(u16 *)(param_1 + 0x5E) = 0;
        *(u16 *)(param_1 + 0xFC) ^= 1;
        tmp[0] = *(s16 *)(param_1 + 0x6);
        tmp[1] = *(s16 *)(param_1 + 0xA);
        tmp[2] = *(s16 *)(param_1 + 0xE);
        sq = (tmp[0] * tmp[0]) + (tmp[2] * tmp[2]);
        *(s16 *)(param_1 + 0xDE) = func_80047D3C(sq);
        *(s16 *)(param_1 + 0xDC) = func_801807D8(tmp);
    }
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80142414(void *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80181F3C(s32 a0);

void func_80184EEC(s32 param_1)
{
    s32 v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(s32 *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (*(s32 *)(param_1 + 0x1C) == 0xF) {
        func_8002D4C8(0x6A9, 0);
        func_80142414((void *)param_1, -0x78);
    }
    if (func_8012BEE8(param_1) != 0) {
        func_80181F3C(param_1);
    }
}


extern void func_8012E364(void);
    void func_80184F6C(void) {
        func_8012E364();
    }


extern s32 func_8012E470(s32 a0);
extern s32 func_8012E4C8(void *a0);
void func_80184F8C(int param_1)
{
    if (((int (*)(void))func_8012E470)() != 0) {
        ((void (*)(int))func_8012E4C8)(param_1);
    }
}



// @class: plumbing
// @unstuck(P36): none — MATCH expected (clean structural stub)

extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern unsigned char D_801A24C8;

void func_80184FC4(int param_1)
{
    ((void (*)(void))func_8012BEE8)();
    if (*(int *)(param_1 + 0x1c) == 1) {
        func_8012A828(param_1, &D_801A24C8);
    }
    return;
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80182FEC(int param_1);
extern void D_801A1AB8;

void func_8018500C(int param_1)
{
    int iVar1;

    iVar1 = func_8012BEE8((s32)param_1);
    if (iVar1 != 0) {
        if (*(s16 *)(param_1 + 0x70) == 2) {
            func_80182FEC(param_1);
        } else {
            *(u16 *)(param_1 + 0x5e) = 0;
            *(u16 *)(param_1 + 0x5c) = 0xAA00;
            func_8012A828((s32)param_1, &D_801A1AB8);
            *(u16 *)(param_1 + 2) = 3;
            *(u16 *)(param_1 + 0xfe) = 0;
        }
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80047D3C(s32 a0);
extern s32 func_801807D8(s16 *a0);
extern s32 D_801A1A10;
extern void func_8012CBA4(s32 a0);

void func_80185080(s32 param_1)
{
    s16 tmp[3];
    s32 sq;

    func_8012CBA4(param_1);
    if (func_8012BEE8(param_1) != 0) {
        *(u16 *)(param_1 + 0xFC) = 0;
        *(u8 *)(param_1 + 0xC1) = 0;
        *(s16 *)(param_1 + 0x2) = 1;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8012A828(param_1, &D_801A1A10);
        *(s32 *)(param_1 + 0x1C) = 0xA;
        *(u16 *)(param_1 + 0x5C) |= 0x8000;
        *(u16 *)(param_1 + 0x5E) = 0;
        *(u16 *)(param_1 + 0xFC) ^= 1;
        tmp[0] = *(s16 *)(param_1 + 0x6);
        tmp[1] = *(s16 *)(param_1 + 0xA);
        tmp[2] = *(s16 *)(param_1 + 0xE);
        sq = (tmp[0] * tmp[0]) + (tmp[2] * tmp[2]);
        *(s16 *)(param_1 + 0xDE) = func_80047D3C(sq);
        *(s16 *)(param_1 + 0xDC) = func_801807D8(tmp);
    }
}


extern s32 D_801270D4;
extern s32 D_801270E4;

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void *a0);

void func_80185150(s32 param_1) {
    s32 v1;

    func_8012AD80(param_1);
    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v1 + 0x10) = *(u16 *)(v1 + 0x10) - 0x100;
    if (func_8012BEE8(param_1) != 0) {
        if (*(s16 *)(param_1 + 0x70) == 2) {
            D_801270E4 -= 1;
        } else {
            D_801270D4 -= 1;
        }
        func_8012C098((void *)param_1);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80130D48(s32 a0);
extern void func_8012C098(void *a0);
extern s32 D_801270D4;
extern s32 D_801270E4;

void func_801851EC(s32 param_1) {
    s32 *p;
    s32 mask;

    mask = 0x80000000;
    p = *(s32 **)(param_1 + 0x20);
    p[1] ^= mask;
    if (((s32 (*)(s32 a0))func_8012BEE8)(param_1) == 0) {
        return;
    }
    func_80130D48(param_1);
    if (*(s16 *)(param_1 + 0x70) == 2) {
        D_801270E4 -= 1;
    } else {
        D_801270D4 -= 1;
    }
    func_8012C098(param_1);
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80183630(s32 a0);
extern void func_80183790(s32 a0);

void func_8018528C(void *a0) {
    void *s0;
    register unsigned short state __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)

    s0 = a0;
    state = *(u16 *)((u8 *)s0 + 0x34);

    switch (state) {
    case 0:
        ((struct { unsigned short h; } *)((u8 *)s0 + 0x34))->h = state + 1;
        ((struct { s32 f; } *)((u8 *)s0 + 0x1C))->f = 0;
        func_8002D4C8(0x4AA, 0);
        break;
    case 1:
        func_80183630((s32)s0);
        break;
    case 2:
        func_80183790((s32)s0);
        break;
    case 3:
        if (func_8012BEE8((s32)s0) != 0) {
            *(u16 *)((u8 *)s0 + 0x34) = 0;
        }
        break;
    }
}


#include "common.h"

void func_80185348(s32 param_1) {
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        func_8018392C(param_1);
        break;
    case 1:
        func_80183A7C(param_1);
        break;
    case 2:
        func_80183BD0(param_1);
        break;
    }
}


void func_801853C4(void) {
}

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32, s32, s32);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801BB3C0[];
extern s32 D_8018A568;

void func_801853CC(s32 param_1) {
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    func_8001C214(v0, (s32)D_801BB3C0);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0xAA, 0xD0);
    func_8012A828(param_1, &D_8018A568);
    *(u16 *)(param_1 + 2) = 2;
    *(u16 *)(param_1 + 0x34) = 0;
    *(s32 *)(param_1 + 0x1C) = 0;
}


void func_8018544C(s32 arg0)
{
    s16 sp10[3];
    s16 temp_v0;
    s32 temp_a0;

    temp_v0 = *(s16 *)(arg0 + 0xDC) + 0x10;
    *(s16 *)(arg0 + 0xDC) = temp_v0;
    temp_a0 = func_8004787C(temp_v0);
    *(s16 *)(arg0 + 0xA) = *(s16 *)(arg0 + 0xDE) + (temp_a0 << 5 >> 12);
    sp10[0] = *(u16 *)(arg0 + 6);
    sp10[1] = *(u16 *)(arg0 + 0xA);
    sp10[2] = *(u16 *)(arg0 + 0xE);
    *(u16 *)(*(s32 *)(arg0 + 0xCC) + 8) = sp10[0];
    *(u16 *)(*(s32 *)(arg0 + 0xCC) + 0xA) = sp10[1];
    *(u16 *)(*(s32 *)(arg0 + 0xCC) + 0xC) = sp10[2];
    func_80183DA4(sp10);
    if (*(u16 *)(arg0 + 0x5C) & 1) {
        if (*(u16 *)(arg0 + 0x5E) == 0x10) {
            func_80184090(arg0);
        } else {
            *(u16 *)(arg0 + 0x5C) = *(u16 *)(arg0 + 0x5C) & ~1;
        }
    }
}


extern void func_8012AD80(s32 a0);
extern void func_80183DA4();
extern void func_8005C2C8(s32 a0, s32 a1);
extern void func_8012C098(void *a0);
extern s32 D_8018ABF4;

void func_80185528(void *arg0)
{
    u16 sp10[3];

    func_8012AD80((s32)arg0);
    sp10[0] = *(u16 *)((s32)arg0 + 0x6);
    sp10[1] = *(u16 *)((s32)arg0 + 0xA);
    sp10[2] = *(u16 *)((s32)arg0 + 0xE);
    *(u16 *)(*(s32 *)((s32)arg0 + 0xCC) + 0x8) = sp10[0];
    *(u16 *)(*(s32 *)((s32)arg0 + 0xCC) + 0xA) = sp10[1];
    *(u16 *)(*(s32 *)((s32)arg0 + 0xCC) + 0xC) = sp10[2];
    *(u16 *)((s32)arg0 + 0x26) = *(u16 *)((s32)arg0 + 0x26) - D_8018ABF4;
    func_80183DA4((s32)arg0 + 0x24);
    *(s32 *)((s32)arg0 + 0x1C) += 1;
    if (*(s32 *)((s32)arg0 + 0x1C) >= 0x28) {
        func_8005C2C8(*(s32 *)((s32)arg0 + 0xCC), 0x84);
        func_8012C098(arg0);
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8005C2C8(s32 a0, s32 a1);
extern s32 rand(void);
extern u8 D_8018ABF8[];
extern void (*D_8018ABE4[])(void *);

void func_801855EC(s32 param_1)
{
    s32 s0v = param_1;
    s32 s1v;
    u16 uVar2;

    s1v = ((s32 (*)(void))func_8012C1B8)();
    if (s1v == 0) {
        ((void (*)(s32))func_8012CAE4)(s0v);
        return;
    }
    ((void (*)(s32, void *))func_8001CA1C)(s1v,
        &D_8018ABF8[(*(u16 *)(s0v + 0x70) & 1) * 12]);
    do { *(u16 *)(s1v + 0x1C) = 0x3000; } while (0);
    *(u16 *)(s1v + 0x1A) = 0x3000;
    *(u16 *)(s1v + 0x18) = 0x3000;
    *(s32 *)(s0v + 0x20) = ((s32 (*)(void))func_8012C1B8)();
    if (*(s32 *)(s0v + 0x20) == 0) {
        ((void (*)(s32, s32))func_8005C2C8)(s1v, 0x84);
        ((void (*)(s32))func_8012CAE4)(s0v);
        return;
    }
    uVar2 = *(u16 *)(s0v + 0xA);
    *(s32 *)(s0v + 0xCC) = s1v;
    *(u16 *)(s0v + 0xDE) = uVar2;
    ((void (*)(s32, s32))func_8001C214)(*(s32 *)(s0v + 0x20), 0);
    *(s32 *)(s0v + 0x58) = (s32)D_8018ABE4;
    *(u16 *)(s0v + 0x2) = 1;
    *(u16 *)(s0v + 0x5C) |= 0x8000;
    *(u16 *)(s0v + 0x72) |= 0x1000;
    *(u16 *)(s0v + 0xDC) = rand() & 0xFFF;
}


extern void func_80184138();
extern void func_80183DA4();
extern s16 D_8018A914;
extern s16 D_8018A91A;
extern s32 D_801270C8;
extern s32 D_801270CC;
extern s32 func_8012C51C(void *a0, s32 a1);

void func_801856D8(int param_1)
{
    u16 sp10[3];   /* sp+0x10 */
    u16 sp18[10];  /* sp+0x18 .. 0x2B */
    s16 *p;

    if (func_8012BEE8((s32)param_1) != 0) {
        sp10[0] = *(u16 *)(param_1 + 6);
        sp10[1] = *(u16 *)(param_1 + 0xA);
        sp10[2] = *(u16 *)(param_1 + 0xE);
        func_80184138(sp10);
        p = &D_8018A91A;
        if (*p == 0) {
            func_80183DA4((s32)p - 6);
        }
    }
    if (D_801270C8 != 0) {
        void *a0pin = sp18;
        __asm__ __volatile__("" : : "r"(a0pin));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
        if (D_801270CC == 0) {
            D_801270CC = 1;
            sp18[0] = *(u16 *)(param_1 + 6);
            sp18[1] = *(u16 *)(param_1 + 0xA);
            sp18[2] = *(u16 *)(param_1 + 0xE);
            sp18[3] = 0x1E;
            sp18[5] = 0;
            sp18[4] = 0;
            *(s32 *)&sp18[8] = 0;
            sp18[7] = 0;
            func_8012C51C(a0pin, (s32)param_1);
        }
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s16 D_8018AC1C;

void func_801857BC(s32 param_1)
{
    s32 iVar1;
    u16 uVar2;

    iVar1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, s32))func_8001C214)(iVar1, 0);
    uVar2 = *(u16 *)(param_1 + 0x72);
    *(s32 *)(param_1 + 0x58) = (s32)&D_8018AC1C;
    *(s16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 0x10;
    *(u16 *)(param_1 + 0xFC) = 0;
    *(u16 *)(param_1 + 0x72) = uVar2 | 0x1000;
}


void func_80185834(s32 param_1) {
    s32 v0;
    s32 a;
    s32 pad[2];

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern u8 D_8018CE0C[];
    extern void func_8001C214(s32, s32);
    extern void func_8001D0E8(s32, s32, s32);
    extern void func_8012B2CC(s32);
    extern s32 ratan2(s32, s32);
    extern void func_8012A828(s32, void *);
    extern void func_8012B200(u8 *);
    extern u8 D_800D3918[];
    extern u8 D_800D391C[];
    extern s32 D_801A2378;
    extern s32 D_8018AC34;

    (void)&pad;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    ((void (*)(void *, void *))func_8001C214)((void *)v0, D_8018CE0C);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0xBE, 0x8C);
    func_8012B2CC(param_1);
    a = ratan2(*(s16 *)D_800D391C - *(s16 *)(*(s32 *)(param_1 + 0x20) + 0xC),
               *(s16 *)(*(s32 *)(param_1 + 0x20) + 8) - *(s16 *)D_800D3918);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (a - 0x400) & 0xFFF;
    func_8012A828(param_1, &D_801A2378);
    *(s16 *)(param_1 + 2) = 1;
    func_8012B200((u8 *)param_1);
    *(s32 *)(param_1 + 0x14) = D_8018AC34;
}


extern void func_800183E0(s32 a0);
    extern s32 D_801C4854;
    void func_80185904(void) {
        ((void (*)(void *))func_800183E0)(&D_801C4854);
    }



extern void (*D_8018AC44[])(void);

void func_8018592C(void *a0) {
    D_8018AC44[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012BF4C(s32 *a0, s32 a1);
    extern s32 func_8012AD50(void *a0);
    void func_80185968(s32 arg0) {
        ((void (*)(s32, s32))func_8012BF4C)(arg0, 0);
        ((void (*)(void *))func_8012AD50)((void *)arg0);
    }


#include "common.h"

/* func_8018599C — spawn 4 particles/effects (id 0x67) at jittered offsets around
 * the actor's world position, then re-arm the actor timer.
 *
 * S55 second-pass crack. Residual class the first pass parked on was
 * "REGALLOC-COALESCE (mag/delta persistence-across-call)": the target keeps the
 * magnitude in $s1 live across the sign-deciding rand() call while the signed
 * delta lives in $s0, and a plain `s32 delta = mag;` lets cse copy-propagate
 * delta into the `negu` so mag dies at the copy ($v0, 83 ins / wrong regs).
 *
 * Three levers, in order of yield:
 *   1. §194-B WIDTH IS A DIAL — `delta` is declared **16-bit**. The truncating
 *      copy is not a plain reg-reg copy, so copy-propagation cannot rewrite the
 *      `negu`'s operand; mag stays a separate pseudo live across the call and
 *      earns its own callee-saved register (the 5th, which is why the target
 *      saves $s0..$s4 and not $s0..$s3).  58 mismatches -> 12.
 *      No sign-extension appears because combine drops it: the sum is only ever
 *      consumed by an `sh` (same reason `in[]` reads as lhu, not lh).
 *   2. The two shift/mask steps of r0 are written as SELF-ASSIGNMENTS
 *      (`r0 &= 0xF; r0 <<= 6;`) rather than one `r0 = (r0 & 0xF) << 6;`.
 *      The single-expression form spawns a fresh pseudo for the `&` result and
 *      local_alloc parks it in $v1 (`andi $v1,$s0,0xF ; sll $s0,$v1,6`);
 *      the split form reuses r0's own register in place, as the target does.
 *   3. §178/pin — with 1+2 the only residual was a straight $s0<->$s1 swap of
 *      mag/delta that no declaration-order permutation moved (3 tried, all 8).
 *      `register s16 delta __asm__("$16")` pins delta to $s0 and mag falls into
 *      $s1 on its own.  MATCH.
 *
 * in/out are two 3-halfword stack vectors at sp+0x10 / sp+0x18 (the
 * func_80186688 house idiom, §193-I: a 6-byte aggregate strides 8 in the frame).
 * They are plain s16[3] rather than the TU's `SV3` typedef ONLY so this file
 * compiles standalone in the match harness — SV3 is already visible in the
 * destination TU via engine_core.h and re-typedef'ing it would be a
 * redefinition error at bank time (§183.1). Layout/bytes are identical.
 *
 * Declarations: D_80126B58 / func_80015978 / func_8012BEE8 / func_8012BF4C /
 * rand are copied verbatim from this TU's existing rows; func_801290DC has no
 * TU row, so the fleet-consensus u8 *(s32, u8 *) (n=1494) is used.
 */

extern s32 func_8012BEE8(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 D_80126B58;
extern s32 rand(void);

void func_8018599C(s32 param_1)
{
    s16 in[3];                              /* sp+0x10 (x,y,z) */
    s16 out[3];                             /* sp+0x18 (x,y,z) */
    u8 *base = (u8 *)&D_80126B58;
    s32 i;
    u8 *p;
    s32 r0, r1, r2;
    s32 mag, mag2;                                /* -> $s1, live across the sign rand() */
    s16 delta;
    s32 t;

    if (func_8012BEE8(param_1) == 0) {
        return;
    }

    func_80015978(param_1 + 4, (s32 *)in);

    for (i = 0; i < 4; i++) {
        if (*(s32 *)(param_1 + 0xDC) != 0) {
            /* jitter X: +/- ((rand&0xF)<<6 + (rand&0xF)<<2) */
            r0 = rand();
            r1 = rand();
            r0 &= 0xF;
            r0 <<= 6;
            r1 = (r1 & 0xF) << 2;
            mag = r0 + r1;
            delta = mag;
            r2 = rand();
            if ((r2 & 1) != 0) {
                delta = -mag;
            }
            out[0] = in[0] + delta;

            /* jitter Z, same shape */
            r0 = rand();
            r1 = rand();
            r0 &= 0xF;
            r0 <<= 6;
            r1 = (r1 & 0xF) << 2;
            mag2 = r0 + r1;
            delta = mag2;
            r2 = rand();
            if ((r2 & 1) != 0) {
                delta = -mag2;
            }
            out[2] = in[2] + delta;
            out[1] = *(u16 *)(base + 0xA) - 0x200;   /* D_80126B58+0xA: camera/ground Y */
        }

        p = func_801290DC(0x67, (u8 *)out);
        if (p != NULL) {
            *(u16 *)(p + 0x2E) = *(u16 *)(param_1 + 0xFC);
        }
    }

    t = rand() & 0x1F;
    func_8012BF4C((s32 *)param_1, t + 8);
}



extern void (*D_8018AC50[])(void);

void func_80185AF8(void *a0) {
    D_8018AC50[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);

void func_80185B34(s32 param_1) {
    *(s32 *)(param_1 + 0x14) = 0x20000;
    *(s32 *)(param_1 + 0x1C) = rand() & 0x1F;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


#include "common.h"

extern void func_80185C0C(s32 arg0);
extern void func_8012931C(void *a0, s32 a1);
extern void func_801292C8(u8 *a0);

void func_80185B78(void *a0) {
    s8 *s0;
    s32 pad[2];
    s32 cnt;
    s32 t;
    void *a02;
    a02 = a0;

    s0 = (s8 *)a02;
    cnt = *(s32 *)(s0 + 0x1C);

    if (cnt == 0) {
        func_80185C0C((s32)s0);
        *(s32 *)(s0 + 0x10) = *(s32 *)(s0 + 0x10);
        t = *(s32 *)(s0 + 0x18);
        *(s32 *)(s0 + 0x18) = t;
        *(s32 *)(s0 + 0x14) = *(s32 *)(s0 + 0x14) + 0xC000;
        func_8012931C(s0, t);
        if (*(s16 *)(s0 + 0x2E) < *(s16 *)(s0 + 0xA)) {
            *(s16 *)(s0 + 0xA) = *(s16 *)(s0 + 0x2E);
            ((void (*)(u8 *))func_801292C8)((u8 *)s0);
        }
    } else {
        *(s32 *)(s0 + 0x1C) = cnt - 1;
    }
}


#include "common.h"

/* ---------------------------------------------------------------------------
 * BANKING PRE-FLIGHT (dest TU: src/ov_SC01_084/ov_SC01_084_jr_8017CA80.c)
 *
 *  ALREADY IN THE TU -- DELETE MY COPIES WHEN BANKING (verified token-identical):
 *    line  119 : extern void func_80015978(s32 a0, s32 *a1);   <- adopted verbatim
 *    line 2704 : gte_ldv3      line 2725 : gte_rtpt      line 2734 : gte_stsxy3
 *    line 2791 : gte_stszotz   line 2800 : gte_stflg
 *
 *  MUST BE ADDED TO THE TU (not present anywhere in it):
 *    gte_SetRotMatrix / gte_SetTransMatrix   (bodies below; identical to the
 *      already-banked pair in ov_SC03_099_jr_8017BEBC.c lines 3784/3798)
 *    extern s32 func_8012EF34(s32 a0, s32 a1);   <-- SEE WARNING
 *    extern void func_80017D98(void *a0);        (matches the def in src/800.c)
 *    extern void func_8001739C(void *a0);        (the spelling every other TU uses)
 *    extern s16 D_8018AC58/5C/60/64/68/6C;       (raw-word form, law 4)
 *
 *  WARNING (§181 law 2/4): every other TU spells func_8012EF34 `extern void
 *  func_8012EF34(s32 a0, s32 a1);` because no other caller consumes its return.
 *  THIS caller does (`and $v0,$v0,-0x1001; bnez`), so the draft needs the s32
 *  return type.  ov_SC01_084_jr_8017CA80.c declares func_8012EF34 NOWHERE today,
 *  so there is no in-TU conflict -- but if another draft in this wave lands the
 *  `void` spelling in this same TU, the two collide.  Reconcile to the s32 form
 *  (a `void` callee called for value is what the shared DEFINE actually leaks).
 *
 *  No other symbol in this draft appears in the TU.  D_8018AC50 (line 3886) is a
 *  different symbol.  All type names are suffixed _80185C0C, so no §183.1 clash.
 * ------------------------------------------------------------------------- */


/* func_80185C0C @ 0x80185C0C  (ov_SC01_084, TU ov_SC01_084_jr_8017CA80.c)
 *
 * Splat calls this "handwritten" only because the body is full of cop2 traffic.
 * It is ordinary gcc-2.7.2 -O2 C using the project's PsyQ inline GTE macros
 * (the $12/$13/$14 scratch triple and the "nop;nop;rtpt" spelling are the tell) --
 * exactly the macro set the destination TU already carries at lines 2698-2812.
 *
 * Shape:  project the owner's world position, then draw a 4-way mirrored
 * triangle fan through func_8001739C using an identity rot-matrix.
 */

extern void func_80015978(s32 a0, s32 *a1);
/* NOTE: the shared DEFINE_func_8012EF34() spells this `void func_8012EF34(s32,s32)`.
 * This call site consumes the $v0 that leaks out of its tail call, so the draft must
 * declare an s32 return.  The destination TU declares func_8012EF34 nowhere, so there
 * is no in-TU conflict to reconcile (see notes). */
extern s32 func_8012EF34(s32 a0, s32 a1);
extern void func_80017D98(void *a0);
extern void func_8001739C(void *a0);

/* three separate 8-byte SVECTOR-ish globals; each store below emits its own lui/%lo */
extern s16 D_8018AC58;   /* vert0 .vx/.vy word */
extern s16 D_8018AC5C;   /* vert0 .vz        */
extern s16 D_8018AC60;   /* vert1 .vx/.vy    */
extern s16 D_8018AC64;   /* vert1 .vz        */
extern s16 D_8018AC68;   /* vert2 .vx/.vy    */
extern s16 D_8018AC6C;   /* vert2 .vz        */








typedef struct {
    s16 x;      /* +0x0 */
    s16 y;      /* +0x2 */
    s16 c;      /* +0x4 */
    s16 pad;    /* +0x6 */
} Vtx_80185C0C;                     /* 0x08 */

typedef struct {
    Vtx_80185C0C v[3];              /* +0x00 +0x08 +0x10 */
    u8 r0, g0, b0, code;            /* +0x18 .. +0x1B */
    u8 r1, g1, b1, pad1;            /* +0x1C .. +0x1F */
    u8 r2, g2, b2, pad2;            /* +0x20 .. +0x23 */
    u32 color;                      /* +0x24 */
} Prim_80185C0C;                    /* 0x28 */

typedef struct {
    u16 x;      /* +0x0 */
    u16 y;      /* +0x2 */
    u16 z;      /* +0x4 */
} Pos_80185C0C;                     /* 0x06 -> 8-byte frame stride, §193-I */

typedef struct {
    u16 vx;     /* +0x0 */
    u16 vy;     /* +0x2 */
    u16 vz;     /* +0x4 */
    u16 pad;    /* +0x6 */
} Sxy_80185C0C;                     /* 0x08 */

typedef struct {
    s16 m[3][3];                    /* +0x00, padded to 0x14 */
    s32 t[3];                       /* +0x14 +0x18 +0x1C */
} Mtx_80185C0C;                     /* 0x20 */

void func_80185C0C(s32 arg0)
{
    Prim_80185C0C prim;             /* sp+0x10 */
    Pos_80185C0C wpos;              /* sp+0x38 */
    Pos_80185C0C spos;              /* sp+0x40 */
    Sxy_80185C0C sxy[4];            /* sp+0x48 (only 0..2 used; 4th slot fills 0x60) */
    Mtx_80185C0C mtx;               /* sp+0x68 */
    s32 otz;                        /* sp+0x88 */
    s32 flag;                       /* sp+0x8C */
    s32 t;
    Prim_80185C0C *p = &prim;

    func_80015978(arg0 + 4, (s32 *)&wpos);
    if ((func_8012EF34((s32)&wpos, (s32)&spos) & ~0x1000) == 0) {
        gte_stszotz(&otz);
        D_8018AC5C = spos.z;
        D_8018AC64 = spos.z;
        D_8018AC6C = spos.z;
        func_80017D98(&mtx);
        /* emitted 0x84/0x80/0x7C -> source runs t[2] first */
        mtx.t[2] = 0;
        mtx.t[1] = 0;
        mtx.t[0] = 0;
        gte_SetRotMatrix(&mtx);
        gte_SetTransMatrix(&mtx);
        gte_ldv3(&D_8018AC58, &D_8018AC60, &D_8018AC68);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_stflg(&flag);
        if (flag >= 0) {
            /* per-vertex colour written b,g,r: the shared-constant groups keep
             * source order inside each group (0xC0 -> 0x2A,0x29,0x28 etc.) */
            p->b0 = 0xC0;
            p->g0 = 0xC0;
            p->r0 = 0xC0;
            p->b1 = 0x40;
            p->g1 = 0x20;
            p->r1 = 0x20;
            p->b2 = 0x40;
            p->g2 = 0x20;
            p->r2 = 0x20;
            p->color = 0x50000000;
            p->v[0].x = sxy[0].vx + spos.x;
            p->v[0].y = sxy[0].vy + spos.y;
            p->v[1].x = sxy[1].vx + spos.x;
            p->v[1].y = sxy[1].vy + spos.y;
            p->v[2].x = sxy[2].vx + spos.x;
            p->v[2].y = sxy[2].vy + spos.y;
            p->v[0].c = otz;
            func_8001739C(p);
            t = sxy[1].vy;
            p->v[1].y = spos.y - t;
            func_8001739C(p);
            t = sxy[2].vx;
            p->v[2].x = spos.x - t;
            func_8001739C(p);
            p->v[1].y = sxy[1].vy + spos.y;
            func_8001739C(p);
        }
    }
}


extern s32 func_800CF854(s32);

s32 func_80185E38(void)
{
    register s32 r __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 v;

    v = ((s32 (*)(void))func_800CF854)();
    r = 3;
    if (v != 0)
        r = 4;
    return r;
}



extern s32 D_801C7728;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80185E68(s32 a0, s32 a1) {
    D_801C7728 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801C7728;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @unstuck(P36): none — MATCH (145/145 ins, match_one confirmed)




s32 func_80185E98(s32 param_1) {

    extern M2C_UNK D_80186B78;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_8018AC84;
    extern MATRIX *D_8018ACB8;     /* matrix pool cursor */
    extern MATRIX D_801C7708[];    /* matrix pool end */

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    MATRIX *m;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_8018AC84) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80186B78));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801C7728, &s60);
    s50 = s60;
    sStack_58.vz = 0x1800;
    sStack_58.vy = 0x1800;
    sStack_58.vx = 0x1800;
    ((void (*)(void *, void *))func_80017DC4)(&sStack_58, auStack_48);
    RotMatrixZ(rand() & 0xfff, auStack_48);
    MulMatrix0(iVar8, auStack_48, iVar5 + 0x34);
    ((void (*)(void *, s32))func_80017E68)(&s50, iVar5 + 0x34);

    /* take the next matrix from the pool (wraps near the end); the post-increment
       is what keeps the load in $v0 and the copy into $s1. */
    m = D_8018ACB8++;
    *(MATRIX **)(param_1 + 0xcc) = m;
    if (D_8018ACB8 > D_801C7708) {
        D_8018ACB8 = D_801C7708 - 9;
    }
    func_800D20C0(&s60, &sStack_58, 7);
    func_800D23D0(&sStack_58);
    ((void(*)(void *, void *))RotMatrixYXZ)(&sStack_58, m);
    ((void (*)(void *, s32))func_80017E68)(&s60, (s32)m);

    uVar3 = *(u16 *)((char *)&s50 + 2);
    if (((s32 (*)(void *))func_80134510)(&s50) != 0 &&
        (s32)(s16)uVar3 - (s32)*(s16 *)((char *)&s50 + 2) < 0x80) {
        *(s16 *)((char *)&s50 + 2) = *(s16 *)((char *)&s50 + 2) - 4;
        m = D_8018ACB8++;
        *(MATRIX **)(param_1 + 0xd0) = m;
        if (D_8018ACB8 > D_801C7708) {
            D_8018ACB8 = D_801C7708 - 9;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), m);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)m);
    }
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 func_80017758(void *a0, void *a1);
extern void func_8012C218(void *a0);


// @class: regalloc-order
// @unstuck(P36): none — MATCH (168 ins). Keys: (1) pin param->$s1 via `register int self __asm__("$17")=param_1`
//   (natural alloc put the short loop-counter in $s1); (2) block2's guarded dest via a test-temp
//   `td=load; if(td){dest=td; ...}` forces the range-split `lw $a1; addu $s3,$a1,$0` the target has;
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).

s32 func_801860DC(s32 param_1) {

    extern signed char D_8018AC70[];
    int self = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    do { iVar1 = *(int *)(self + 0x1c); } while (0);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_8018AC70;
        i = 0;
        dest = *(int *)(self + 0xcc);
        t = *(unsigned short *)(self + 0x70);
        *(short *)(buf + 0x0c) = 0;
        *(short *)(buf + 0x0a) = 0;
        *(short *)(buf + 0x08) = 0;
        *(short *)(buf + 0x1c) = 0;
        *(short *)(buf + 0x14) = 0;
        *(short *)(buf + 0x04) = 0;
        buf[0x22] = 0;
        buf[0x21] = 0;
        buf[0x20] = 0;
        buf[0x2a] = 0;
        buf[0x29] = 0;
        buf[0x28] = 0;
        buf[0x2e] = 0;
        buf[0x2d] = 0;
        buf[0x2c] = 0;
        *(int *)(buf + 0x30) = 0x50000000;
        buf[0x25] = t;
        buf[0x26] = t;
        buf[0x24] = t;
        do {
            *(short *)(buf + 0x00) = *p++;
            *(short *)(buf + 0x02) = *p++;
            *(short *)(buf + 0x10) = *p++;
            *(short *)(buf + 0x12) = *p++;
            *(short *)(buf + 0x18) = *p++;
            *(short *)(buf + 0x1a) = *p--;
            func_80017758(buf, (void *)dest);
            i++;
        } while (i < 4);

        td = *(int *)(self + 0xd0);
        if (td != 0) {
            dest = td;
            p = D_8018AC70;
            i = 0;
            t = *(unsigned short *)(self + 0x70);
            *(short *)(buf + 0x0c) = 0;
            *(short *)(buf + 0x0a) = 0;
            *(short *)(buf + 0x08) = 0;
            *(short *)(buf + 0x1c) = 0;
            *(short *)(buf + 0x14) = 0;
            *(short *)(buf + 0x04) = 0;
            buf[0x22] = 0;
            buf[0x21] = 0;
            buf[0x20] = 0;
            buf[0x2a] = 0;
            buf[0x29] = 0;
            buf[0x28] = 0;
            buf[0x2e] = 0;
            buf[0x2d] = 0;
            buf[0x2c] = 0;
            *(int *)(buf + 0x30) = 0x50000000;
            buf[0x25] = t;
            buf[0x26] = t;
            buf[0x24] = t;
            do {
                *(short *)(buf + 0x00) = *p++;
                *(short *)(buf + 0x02) = *p++;
                *(short *)(buf + 0x10) = *p++;
                *(short *)(buf + 0x12) = *p++;
                *(short *)(buf + 0x18) = *p++;
                *(short *)(buf + 0x1a) = *p--;
                func_80017758(buf, (void *)dest);
                i++;
            } while (i < 4);
        }
        do { *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1; } while (0);
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        func_8012C218((void *)self);
    }
}


extern void (*D_8018ACBC[])(void);

void func_8018637C(void *a0) {
    D_8018ACBC[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @unstuck(P36): none — MATCH (94 ins). Keys: (1) cache out[0] in a local `o` before the switch so gcc
//   holds it in $a0 across the case stores (else it reloads/`lh` per case, +3 ins); (2) declare the
//   `in` struct BEFORE `out[2]` so in@sp+0x10 / out@sp+0x20; (3) the 0x14 word is written via
//   `*(s32*)&in.lo = D_80126B60` then the high short RMW'd `in.hi -= 0x20` (memory lhu/sh, not reg);
//   (4) order the three global assigns B60,B5C,B64 (B60 first → v0/v1/a2 alloc); (5) explicit
//   `case 2: break;` after case 3 so gcc emits the `beq $v1,2` test with case1 falling into case3.

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8002D4C8(s32, s32);
extern void func_8012A828(s32, void *);
extern void func_8012B77C(void *, s32, void *);
extern void func_8012B2CC(s32);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_801863B8(s32 param_1) {

    extern M2C_UNK D_801A2F28;
    extern u8   D_801A2D00;
    extern u8 D_80126B5C;
    extern s32  D_80126B60;
    extern s32  D_80126B64;
    s32 iVar1;
    struct In in;
    s32 out[2];
    s32 t;
    s32 o;

    iVar1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001C214)(iVar1, &(*(u8 *)&D_801A2F28));
    if ((*(u16 *)(param_1 + 0x70) & 0x1000) == 0) {
        func_8002D4C8(0x43A, 0);
    } else {
        func_8002D4C8(0x6D6, 0);
    }
    func_8012A828(param_1, &D_801A2D00);
    *(s16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 100;

    *(s32 *)&in.lo = D_80126B60;
    in.hi -= 0x20;
    in.w0 = (*(s32 *)&D_80126B5C);
    in.w2 = D_80126B64;
    func_8012B77C(out, param_1 + 4, &in);

    o = out[0];
    t = *(u16 *)(param_1 + 0x70) & 0xF;
    switch (t) {
    case 0:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
        break;
    case 1:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
    case 3:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)(o >> 16);
        break;
    case 2:
        break;
    }

    if (*(u16 *)(param_1 + 0x70) & 0x1000) {
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) << 1;
    }
    func_8012B2CC(param_1);
    ((void (*)(s32, s32))func_8012C588)(0xBC, param_1);
}



extern void (*D_801A2D9C[])(void);

void func_80186530(void *a0) {
    D_801A2D9C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801A2DB0[])(void);

void func_8018656C(void *a0) {
    D_801A2DB0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_801A2D88;
extern s32 D_801A2D94;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_801865A8(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_801A2D88);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_801A2D94, (s32)&D_800D3918, 0x19) == 0 &&
            (*(s16 *)(s0 + 0x70) == 2 || D_80126D50 == 0) &&
            func_8012BEE8(s0) == 0) {
            return;
        }
    }
    func_8012C218((void *)s0);
}



// @class: schedule
// @unstuck(P36): none — MATCH (71 ins). Tail schedule: read out.c into an explicit temp BEFORE the 0x5a/1 const stores so gcc hoists its lhu early (load-delay filled by li 0x5a) and stores out.c last from a held reg; without the temp gcc instead deferred out.b's store. in/out are two separate SV3{s16 a,b,c} stack slots (sp+0x10, sp+0x18) for ((void (*)(int, void *, void *))func_8012F214)(a0,&in,&out). 0x34 compare reads u16 (lhu, not lh).

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern int D_801A2DA4;

void func_80186688(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801A2DA4);
        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        ((void (*)(int, void *, void *))func_8012F214)(param_1, &in, &out);
        *(short *)(param_1 + 6) = out.a;
        *(short *)(param_1 + 0xa) = out.b;
        c = out.c;
        *(int *)(param_1 + 0x1c) = 0x5a;
        *(short *)(param_1 + 0x34) = 1;
        *(short *)(param_1 + 0xe) = c;
    }
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) - 0x80;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 4;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 5;
    func_8012AD80(param_1);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(int))func_8012C218)(param_1);
    }
}



// @class: other
// @unstuck(P36): none — MATCH (expected); 16-bit sh stores via short* casts, s0=param_1 call-crossing

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_801A3058;

void func_801867A4(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801A3058);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}






