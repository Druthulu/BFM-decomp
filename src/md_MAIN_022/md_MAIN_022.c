#include "common.h"

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAE0C);



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


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAEB0);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAEE8);

void func_800CAF3C(void) {
}

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAF44);

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


extern void func_800CB008(void);
void func_800CAFE8(void) {
    func_800CB008();
}


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB008);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB03C);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB0B8);

void func_800CB104(void) {
}

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB10C);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB184);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB1BC);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB2F4);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB354);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB3D0);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB3F0);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB4AC);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB4F4);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB550);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB5E4);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB630);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB68C);

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

