#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CBD48;
    func_800183E0(&D_800CBD48);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CBC90[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBC90[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern void func_801655E4();
void func_800CAEB0(void *a0) {
    func_801655E4(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAEE8);

void func_800CAF3C(void) {
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CB008();
void func_800CAF44(s32 *a0) {
    func_80147078(a0, 34);
    ((void (*)(void *))func_800CB008)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFAC(void *a0);
void func_800CAF78(s32 *a0) {
    func_80147078(a0, 34);
    func_800CAFAC(a0);
}




void func_800CAFAC(void *a0) {

    extern void (*D_800CBC9C[])(void);
    D_800CBC9C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CB008();
void func_800CAFE8(void) {
    func_800CB008();
}


    extern void func_80154150(s32 *a0, s16 a1);
    extern void func_80146CA0(s32);
    void func_800CB008(s32 *a0) {
        func_80154150(a0, 0);
        func_80146CA0(a0);
    }


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB03C);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB0B8);

void func_800CB104(void) {
}

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB10C);

void func_800CB184(void *a0) {
    extern void func_80146E90(s32 *a0, s32 a1);
    func_80146E90((s32 *)a0, *(s32 *)((s32)a0 + 0x50) << 2);
    func_80146CA0((s32)a0);
}


extern s32 func_80146E98(s32 a0);
extern void func_80146578(void);
extern void func_8001CD9C(void *a0, void *a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80146CA0(s32);
extern void func_800CB3D0();

extern u8 D_800CBD68;
extern u8 D_800CBD69;
extern u8 D_800CBD6A;
extern u8 D_800CBD6B;
extern u8 D_800CBD6C;
extern u8 D_800CBD6D;
extern u8 D_800CBD6E;
extern u8 D_800CBD6F;

void func_800CB1BC(void *a0)
{
    void *s0;
    void *s2;
    s32 v0;
    s32 vtemp;

    if (func_80146E98((s32)a0) != 0) {
        s2 = ((void *(*)(void))func_80146578)();
        *(void **)((u8 *)a0 + 0x20) = s2;

        if (s2 != NULL) {
            s0 = &D_800CBD68;
            func_8001CD9C(s2, s0);
            func_800233CC(s0, 0x20);

            vtemp = *(s32 *)((u8 *)s2 + 4);
            *(s16 *)((u8 *)s2 + 0x1A) = 0;
            *(s16 *)((u8 *)s2 + 0x18) = 0;
            *(s32 *)((u8 *)s2 + 4) = vtemp | 0x50000000;

            *(s16 *)((u8 *)a0 + 0x62) = 0x1000;
            *(s16 *)((u8 *)a0 + 0x60) = 0;
            *(s16 *)((u8 *)s2 + 0x14) = -0x155;

            v0 = *(s32 *)((u8 *)a0 + 0x54);
            *(s16 *)((u8 *)s2 + 0x12) =
                v0 * 1365 + *(s32 *)((u8 *)a0 + 0x50) * 11;

            *(u8 *)s0 = 0xF0;
            D_800CBD69 = 0xF0;
            D_800CBD6A = 0xF0;
            D_800CBD6B = 0;
            D_800CBD6C = 0;
            D_800CBD6D = 0x20;
            D_800CBD6E = 0x20;
            D_800CBD6F = 0;

            func_80146CA0((s32)a0);
        } else {
            func_800CB3D0(a0);
        }
    }
}


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB2F4);

extern void func_80146CA0(s32);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_800CB354(void *a0) {
    void *v1;
    s16 v0;

    v1 = *(void **)((s32)a0 + 0x20);
    v0 = *(u16 *)((s32)a0 + 0x62) - 0x40;
    *(u16 *)((s32)a0 + 0x62) = v0;
    if (v0 < 0) {
        func_80146CA0((s32)a0);
        return;
    }
    *(u16 *)((s32)v1 + 0x12) = (*(u16 *)((s32)v1 + 0x12) - 0x71) & 0xFFF;
    func_80146A6C(0x3E, a0, *(s16 *)((s32)a0 + 0x6), *(s16 *)((s32)a0 + 0xA),
                  *(s16 *)((s32)a0 + 0xE), 0, 0);
}


extern void func_80162CCC(void);
void func_800CB3D0(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB3F0);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB4AC);

extern u8 D_80078EC1;
extern void (*D_800CBD0C[])();
extern void func_80146C3C();

void func_800CB4F4(int param_1)
{
    if (D_80078EC1 != 4) {
        func_80146C3C();
    } else {
        D_800CBD0C[*(u16 *)(param_1 + 2)]();
    }
}


#include "common.h"

extern void *func_800D2294(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C3C();

void func_800CB550(void *a0) {
    extern u8 D_800CBCCC;
    void *base;
    void *ptr;

    base = &D_800CBCCC;
    ptr = func_800D2294((s32)a0, (s32)base);
    *(void **)((s32)a0 + 0x20) = ptr;
    if (ptr != NULL) {
        func_800233CC(base, 0x20);
        *(s32 *)((s32)ptr + 4) |= 0x50000000;
        func_80146E90((s32 *)a0, 8);
        *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();

void func_800CB5E4(void *a0) {
    s32 v0;
    s32 v1;

    v0 = *(s32 *)((s32)a0 + 0x1C) << 9;
    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x1A) = v0;
    *(u16 *)(v1 + 0x18) = v0;
    if (func_80146E98((s32)a0) != 0) {
        func_80146C3C(a0);
    }
}



extern void func_80146C3C(void);

void func_800CB630(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBD14[])(void);
    if (D_80078EC1 == 0x4) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBD14[v0]();
    } else {
        func_80146C3C();
    }
}


typedef struct { s32 w[8]; } Blk20_800CB68C;

extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801465C0(void);

void func_800CB68C(s32 param_1)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern void func_800CBAA4(s32);
    extern void RotMatrixY(s32 a0, void *a1);
    extern u8 D_800CBDB0;
    extern u8 D_800CBDB1;
    extern u8 D_800CBDB2;
    extern u8 D_800CBDB4;
    extern u8 D_800CBDB5;
    extern u8 D_800CBDB6;

    s32 iVar8;
    short sVar1;

    iVar8 = *(s32 *)((u8 *)((void *)param_1) + 0x34);
    if ((*(u32 *)((u8 *)((void *)param_1) + 0x2c) & 0x8000) == 0) {
        register s32 iNew __asm__("$17");
        s32 base;
        iNew = ((s32(*)())func_801465C0)();
        if (iNew == 0) {
            return;
        }
        base = (s32)&D_800CBDB0;
        D_800CBDB2 = 0xc0;
        *(u8 *)base = 0xc0;
        D_800CBDB1 = 0;
        D_800CBDB6 = 0;
        D_800CBDB5 = 0;
        D_800CBDB4 = 0;
        ((void(*)(void *, unsigned short))func_800233CC)((void *)base, 0x40);
        func_8001CD50(iNew, base);
        *(s32 *)(iNew + 0x34) = (s32)((u8 *)((void *)param_1) + 0x38);
        *(s16 *)(iNew + 0x1a) = 0;
        *(s16 *)(iNew + 0x18) = 0;
        *(u32 *)(iNew + 4) = *(u32 *)(iNew + 4) | 0x50000000;
        ((void (*)(void *))func_800CBAA4)(((void *)param_1));
        {
            register s32 t10 __asm__("$3");
            t10 = 0x10;
            *(s32 *)((u8 *)((void *)param_1) + 0x20) = iNew;
            *(s32 *)((u8 *)((void *)param_1) + 0x1c) = t10;
        }
        sVar1 = *(u16 *)((u8 *)((void *)param_1) + 2) + 1;
    } else {
        short asStack_60[20];
        Blk20_800CB68C localMatrix;
        s32 uVar2;
        extern s32 D_800AE620;
        extern s32 rand(void);
        extern void ApplyMatrixSV(void *a0, void *a1, void *a2);

        asStack_60[0] = 0;
        asStack_60[1] = 0;
        asStack_60[2] = 0x20;
        localMatrix = (*(Blk20_800CB68C*)&D_800AE620);
        uVar2 = ((s32(*)())rand)();
        RotMatrixY((uVar2 & 0x7f00) >> 3, &localMatrix);
        ApplyMatrixSV(&localMatrix, asStack_60, asStack_60);
        *(s16 *)((u8 *)((void *)param_1) + 6) = D_80126B5E + asStack_60[0];
        *(s16 *)((u8 *)((void *)param_1) + 0xa) = D_80126B62 - ((u16)uVar2 & 0x3f);
        *(s16 *)((u8 *)((void *)param_1) + 0xe) = D_80126B66 + asStack_60[2];
        *(Blk20_800CB68C *)((u8 *)((void *)param_1) + 0x38) = *(Blk20_800CB68C *)((u8 *)iVar8 + 0x38);
        *(s32 *)((u8 *)((void *)param_1) + 0x2c) = 0x1000;
        *(s32 *)((u8 *)((void *)param_1) + 0x30) = 0xff;
        *(s32 *)((u8 *)((void *)param_1) + 0x1c) = 0x10;
        __asm__ __volatile__("" ::: "memory");
        sVar1 = 4;
    }
    *(s16 *)((u8 *)((void *)param_1) + 2) = sVar1;
}


extern void func_800CBAA4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_800CB8A4(s32 a0) {
    s32 s1;
    s32 v;
    s1 = *(s32 *)(a0 + 0x20);
    func_800CBAA4(a0);
    v = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v;
    if (v != 0) {
        func_80146A6C(0x41, (void *)a0, 0, 0, 0, 0x8000, 0);
        *(s16 *)(s1 + 0x18) = *(u16 *)(s1 + 0x18) + 0x100;
        *(s16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0x1A) + 0x140;
        return;
    }
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


extern void func_800CBAA4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_800CB944(s32 *a0) {
    func_800CBAA4((s32)a0);
    if (--a0[0x1C / 4] != 0) {
        func_80146A6C(0x41, a0, 0, 0, 0, 0x8000, 0);
    } else {
        a0[0x1C / 4] = 0x10;
        *(u16 *)((char *)a0 + 2) += 1;
    }
}


extern void func_800CBAA4(s32 a0);
extern void func_80146C3C();
void func_800CB9C0(void *a0) {
    s32 *s1 = *(s32 **)((s32)a0 + 0x20);
    func_800CBAA4((s32)a0);
    if (--*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(u16 *)((s32)s1 + 0x18) -= 0x100;
        *(u16 *)((s32)s1 + 0x1A) -= 0x120;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}


extern void func_800D22E4(s32 a0);
extern void func_800CBB38(void *a0, void *a1);
extern void func_80146C3C();
void func_800CBA30(void *a0) {
    s32 v0;
    v0 = *(s32*)((s32)a0 + 0x1C) - 1;
    *(s32*)((s32)a0 + 0x1C) = v0;
    if (v0 != 0) {
        func_800D22E4((s32)a0);
        *(s16*)((s32)a0 + 0x16) = *(u16*)((s32)a0 + 0x16) - 3;
        *(s32*)((s32)a0 + 0x30) = *(s32*)((s32)a0 + 0x30) - 0xE;
        func_800CBB38(a0, (void*)((s32)a0 + 0x38));
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
void func_800CBAA4(s32 a0) {
    s16 src[4];
    u8 mtx[8];
    s32 p;
    p = *(s32 *)(a0 + 0x34);
    src[0] = *(u16 *)(p + 0x6);
    src[1] = *(u16 *)(p + 0xA) - 0x28;
    src[2] = *(u16 *)(p + 0xE);
    func_800D20C0((void *)src, (void *)mtx, 6);
    *(s16 *)(a0 + 0x6) = src[0];
    *(s16 *)(a0 + 0xA) = src[1];
    *(s16 *)(a0 + 0xE) = src[2];
    func_800D23D0((void *)mtx);
    RotMatrixYXZ((void *)mtx, (void *)(a0 + 0x38));
}


/* func_800CBB38 -- tier-2 (codegen shaping).  MATCH (86/86 ins), 0 warnings.
 *
 * Target metadata per tier-1's correction (the brief's was stale): the live function is the
 * 86-instruction (0x158-byte) fn in md_MAIN_022, NOT a 528-ins md_MAIN_011 fn.
 *   verify: .venv/bin/python tools/match_one.py func_800CBB38 --c <this> \
 *           --asm-subdir asm/md_MAIN_022/nonmatchings/md_MAIN_022
 *
 * BANKING: replace md_MAIN_022.c:174's INCLUDE_ASM with this body. No in-TU conflicts --
 * line 137 already declares `extern void func_800CBB38(void *a0, void *a1);`, which is
 * exactly this signature, and the three callees are not declared elsewhere in that TU.
 *
 * ---- how the 51-instruction tier-1 residual closed (two levers, no pins/barriers) ----
 *
 * The diagnosed class was "S11 regalloc-order". That was the SYMPTOM. The cause was:
 *
 * LEVER 1 -- hoist-vs-remat.  t1 had `vp = buf + 0x00;` as a live pointer variable. gcc
 * kept it in a callee-saved reg (`addiu $s1,$sp,0x10` once, then `move $a0,$s1` twice);
 * the target rematerializes `addiu $a0,$sp,0x10` before EACH func_80017758 call. Deleting
 * `vp` and passing `buf` directly freed $s1, and the entire callee-saved assignment then
 * fell into place on its own -- a0->$s1, a1->$s6, consts->$s5/$s4/$s3/$s2. No
 * `register __asm__` pin (§17) and no scheduling barrier were needed: the regalloc "fight"
 * was entirely an artifact of one extra live pointer competing for the same class.
 * (`p = buf + 0x38` IS a real live variable -- it stays in $s0 across all four calls.)
 *
 * LEVER 2 -- statement order is literal.  Verified in BOTH directions that gcc-2.7.2 -O2
 * does not reorder these independent same-base stack stores: t1's ascending source emitted
 * ascending; the target's permuted order emits the target's permutation. So the target's
 * "odd" store order could be read straight off the asm rather than reasoned about, and the
 * constants' FIRST-USE order (7, -7, 3, -3) is precisely what lands them in $s5,$s4,$s3,$s2.
 * The three orders that matter, all transcribed verbatim below:
 *   verts   v0.x, v2.x, v1.x, v3.x, v1.y, v3.y, v0.y, v2.y, v3.z, v2.z, v1.z, v0.z
 *   colors  grouped by source register: the four `c`, then the two `c>>2`, then the six `c>>4`
 *   angle   buf+0x5A written BEFORE buf+0x58
 *
 * Reusable rule: when a near-miss is pure register/stack-slot drift with zero structural
 * delta, check for a hoisted address temp FIRST and re-read the store order off the target
 * before reaching for §17 pins -- both are free, and either can masquerade as S11.
 *
 * ---- layout (buf-relative; real $sp offset = buf offset + 0x10) ----
 *   buf+0x00..0x1F  4x SVECTOR-shaped {s16 x,y,z,pad} offset vectors
 *   buf+0x20..0x2F  4x {u8 r,g,b,pad} colors derived from *(u8*)(a0+0x30)
 *   buf+0x30        u32 0x50000000
 *   buf+0x38        p: MATRIX built by func_80017DC4, combined via func_80048EAC(a1, p),
 *                   then its translation (buf+0x4C/0x50/0x54) set from a0+0x6/0xA/0xE
 *   buf+0x58/0x5A   the angle pair seeded from *(u16*)(a0+0x2C)
 */

extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);

void func_800CBB38(void *a0, void *a1) {
    u8 buf[0x60];
    u8 *p;
    u8 c, c2, c4;
    u16 ang;

    p = buf + 0x38;

    *(s16 *)(buf + 0x00) = 7;
    *(s16 *)(buf + 0x10) = 0;
    *(s16 *)(buf + 0x08) = 0;
    *(s16 *)(buf + 0x18) = -7;
    *(s16 *)(buf + 0x0A) = 3;
    *(s16 *)(buf + 0x1A) = 0;
    *(s16 *)(buf + 0x02) = 0;
    *(s16 *)(buf + 0x12) = -3;
    *(s16 *)(buf + 0x1C) = 0;
    *(s16 *)(buf + 0x14) = 0;
    *(s16 *)(buf + 0x0C) = 0;
    *(s16 *)(buf + 0x04) = 0;

    c  = *(u8 *)((s32)a0 + 0x30);
    c2 = c >> 2;
    c4 = c2 >> 2;

    *(u8 *)(buf + 0x2A) = c;
    *(u8 *)(buf + 0x26) = c;
    *(u8 *)(buf + 0x28) = c;
    *(u8 *)(buf + 0x24) = c;
    *(u8 *)(buf + 0x29) = c2;
    *(u8 *)(buf + 0x25) = c2;
    *(u8 *)(buf + 0x2C) = c4;
    *(u8 *)(buf + 0x20) = c4;
    *(u8 *)(buf + 0x2E) = c4;
    *(u8 *)(buf + 0x22) = c4;
    *(u8 *)(buf + 0x2D) = c4;
    *(u8 *)(buf + 0x21) = c4;

    *(s32 *)(buf + 0x30) = 0x50000000;

    ang = *(u16 *)((s32)a0 + 0x2C);
    *(s16 *)(buf + 0x5A) = ang;
    *(s16 *)(buf + 0x58) = ang;
    func_80017DC4((void *)(buf + 0x58), p);

    func_80048EAC(a1, p);

    *(s32 *)(buf + 0x4C) = *(s16 *)((s32)a0 + 0x6);
    *(s32 *)(buf + 0x50) = *(s16 *)((s32)a0 + 0xA);
    *(s32 *)(buf + 0x54) = *(s16 *)((s32)a0 + 0xE);

    func_80017758(buf, p);

    *(s16 *)(buf + 0x00) = 3;
    *(s16 *)(buf + 0x10) = 0;
    *(s16 *)(buf + 0x08) = 0;
    *(s16 *)(buf + 0x18) = -3;
    *(s16 *)(buf + 0x0A) = 7;
    *(s16 *)(buf + 0x1A) = 0;
    *(s16 *)(buf + 0x02) = 0;
    *(s16 *)(buf + 0x12) = -7;

    func_80017758(buf, p);
}

