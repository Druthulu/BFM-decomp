#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); /* derive-decl, arity 4 */
extern s32 func_80169A4C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8016A8FC(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8012B8E4(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8015E1B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015EE08(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015F7D4(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80160B34(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80165140(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80161CD0(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_80175268(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8017EC7C(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801809BC(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012DE2C(s32 a0);                        /* derive-decl, arity 1 */
extern s32 func_8012DDA4(void);                          /* derive-decl, arity 0 */
extern s32 func_801759D8(void);                          /* derive-decl, arity 0 */
extern s32 func_80175820(void);                          /* derive-decl, arity 0 */
extern s32 func_801758FC(void);                          /* derive-decl, arity 0 */
/* ==== end canonical-sig layer ==================================================== */

extern void func_80016714(void *a0, s32 a1);
extern s32 D_801D9568;
extern s32 D_801269D4;
extern s32 D_801269C8;

void func_8013C98C(void) {
    func_80016714(&D_801D9568, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}

extern void func_80019064(void *a0);
s32 func_80019198();                                /* extern */
extern M2C_UNK D_80062BC0;
extern s32 D_801D9568;
extern s8 D_801D956C;
extern s8 D_801D956D;

void func_8013C9C4(void * arg0)
{
    D_801D9568 = arg0;
    D_801D956C = 0;
    D_801D956D = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}

extern s32 D_801D9568;
extern s8 D_801D956C;
extern s8 D_801D956D;
extern s32 D_801269C8;
extern s32 D_801269D4;
void func_8013CA14(void)
{
  int *base = &D_801D9568;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801D956D;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801D956C)) * 2) + D_801D9568);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801D956D = (unsigned char) p[1];
      D_801D956C = D_801D956C + 1;
      if (D_801D956D == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801D956C = 0;
        *base = 0;
      }
    }
    else
    {
      D_801D956D = c - 1;
    }
  }
  return;
}

extern s32 D_801D958C;
extern s32 D_801D9580;
extern s32 D_801D9584;
extern s32 D_801D9590;

void func_8013CABC(void) {
    D_801D958C = 1;
    D_801D9580 = 1;
    D_801D9584 = 0;
    D_801D9590 = 1;
}

extern s32 D_801D9580;
extern s32 D_801D9584;
extern s32 D_801D9588;
extern s32 D_801D958C;
extern s32 D_801D9590;

void func_8013CAE8(void) {
    D_801D9580 = 1;
    D_801D958C = 0;
    D_801D9584 = 0;
    D_801D9588 = -1;
    D_801D9590 = 0;
}

extern s32 D_801D958C;
extern s32 D_801D9590;
extern s32 D_801D95B8;
extern s32 D_801D95BC;

void func_8013CB20(void)
{
    D_801D95B8 = D_801D9590;
    D_801D95BC = D_801D958C;
    D_801D9590 = 1;
    D_801D958C = 0;
}

extern s32 D_801D95B8;
extern s32 D_801D95BC;
extern s32 D_801D9590;
extern s32 D_801D958C;

void func_8013CB5C(void) {
    D_801D9590 = D_801D95B8;
    D_801D958C = D_801D95BC;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013CB84);

// @class: struct
// @stuck: none — MATCH (63 ins)
//
// Sets up 3 consecutive 16-byte records (at D_800A5E88[0..2]: {s32 a,b,c; u8 d,e,f,g})
// and registers each via func_80028620(i, &rec[i]).
//
// Keys to the byte match:
//  (1) The base pointer is anchored at D_800A5E94 (= &rec0.d, i.e. rec0+0xC) and materialized
//      via a NON-volatile inline-asm `la` so gcc treats it as OPAQUE (not a const symbol).
//      Opacity is what makes the base-relative stores FOLD into `off($s0)` instead of
//      const-folding to a direct `lui $at; sw %lo(sym)`. A `__asm__ __volatile__` re-tie
//      barrier (cookbook §21) also launders base, but the barrier pins the schedule and
//      pushes the first call's `a0=0` down; the non-volatile `la` avoids the barrier so the
//      scheduler still hoists `addu $a0,$zero,$zero` to the top (matches target idx1).
//  (2) rec0's inner fields (E8C/E90 ints, E95/E96 bytes) are written as DIRECT globals, not
//      base-relative — in the entry block gcc emits them as `lui $at; sw/sb %lo(sym)`. Only
//      the address-taken E88 (= call arg base-0xC) and the offset-0 E94 fold via $s0. rec1/rec2
//      fold entirely (base opaque, all offsets small).
//  (3) The three source bytes per record are loaded into temps t0/t1/t2 BEFORE the stores so
//      gcc keeps them live in three registers ($v1/$a2/$a3) as a group (not one-at-a-time in $v0).
//  (4) Statement order matches the target scheduler: rec1 stores b(=7) before the loads;
//      rec2 stores b(=-0x12) AFTER the loads (the differing constants drive the scheduler).
#include "common.h"


void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801DA9B8;
    extern u8 D_801DA9B9;
    extern u8 D_801DA9BA;
    extern u8 D_801DA9BB;
    extern u8 D_801DA9BC;
    extern u8 D_801DA9BD;
    extern u8 D_801DA9BE;
    extern u8 D_801DA9BF;
    extern u8 D_801DA9C0;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801DA9B8; t1 = D_801DA9B9; t2 = D_801DA9BA;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801DA9BB; t1 = D_801DA9BC; t2 = D_801DA9BD;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801DA9BE; t1 = D_801DA9BF; t2 = D_801DA9C0;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}


// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_801D9598;
extern s32 D_801D9580;
extern s32 D_801D959C;
extern s32 D_801D958C;
extern void func_8013D9B0();

void func_8013D064(void)
{
    if (D_801D9598 != 0) {
        if (D_801D9598 != 2) {
            if (((D_801D9598 < 3) && (D_801D9598 == 1)) &&
                (D_801D959C = D_801D959C + 1, 0x23a < D_801D959C)) {
                D_801D9580 = D_801D9598;
                D_801D9598 = 2;
            }
        } else {
            D_801D9580 = D_801D9580 + -1;
            if (D_801D9580 == 0) {
                D_801D9580 = D_801D9598;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801D958C == 0) {
                    D_801D9598 = D_801D9598 + 1;
                }
            }
        }
    }
    return;
}

extern void func_8013D9B0();
extern s32 D_801D958C;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_801D958C;
}

extern s32 D_801D9598;

void func_8013D164(void) {
    D_801D9598 = 1;
}

// @class: regalloc-order
// @stuck: none — MATCH

extern unsigned char D_801DA9B8, D_801DA9B9, D_801DA9BA, D_801DA9BB, D_801DA9BC,
                     D_801DA9BD, D_801DA9BE, D_801DA9BF, D_801DA9C0;
extern unsigned char D_801DAA78, D_801DAA79, D_801DAA7A, D_801DAA7B, D_801DAA7C,
                     D_801DAA7D, D_801DAA7E, D_801DAA7F, D_801DAA80;

void func_8013D178(void) {
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801DA9B8; v = *p; t = D_801DAA78;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9B9; v = *p; t = D_801DAA79;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9BA; v = *p; t = D_801DAA7A;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9BB; v = *p; t = D_801DAA7B;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9BC; v = *p; t = D_801DAA7C;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9BD; v = *p; t = D_801DAA7D;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9BE; v = *p; t = D_801DAA7E;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9BF; v = *p; t = D_801DAA7F;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801DA9C0; v = *p; t = D_801DAA80;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}


// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)

extern u8 D_801DAABA;
extern u8 D_801DAB2E;
extern u8 D_801DA9C2;
extern u8 D_801DAA9C;
extern u8 D_801DA998;
extern u8 D_801DA9C1;
extern s32 D_801DAAA0;

void func_8013D330(void) {
    if ((D_801DAABA & 0xff) != D_801DAB2E) {
        D_801DAABA = ((D_801DAABA & 0xff) < D_801DAB2E) ? (D_801DAABA + 1) : (D_801DAABA - 1);
    }
    if ((D_801DA9C2 & 0xff) != D_801DAA9C) {
        D_801DA9C2 = ((D_801DA9C2 & 0xff) < D_801DAA9C) ? (D_801DA9C2 + 1) : (D_801DA9C2 - 1);
    }
    if ((D_801DA998 & 0xff) != D_801DA9C1) {
        D_801DA998 = ((D_801DA998 & 0xff) < D_801DA9C1) ? (D_801DA998 + 1) : (D_801DA998 - 1);
    }
    D_801DAAA0 = 1;
}

// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)

extern u8 D_80078E78[];

extern void *D_801D9570;
extern void *D_801D9574;
extern void *D_801D9578;
extern s32 D_801D95A0;
extern s32 D_801D95A4;
extern s32 D_801D95A8;
extern s32 D_801DAA14[];

extern u8 D_8018735C[];
extern u8 D_80187404[];
extern u8 D_801872B4[];
extern u8 D_801873B0[];
extern u8 D_80187430[];
extern u8 D_80187308[];

extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{
    u8 *p = D_80078E78;

    D_801D95A0 = param_2;
    D_801D95A4 = (param_2 >> 2) & 3;
    D_801D95A8 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801D9570 = D_8018735C;
        D_801D9574 = D_80187404;
        D_801D9578 = D_801872B4;
    } else {
        D_801D9570 = D_801873B0;
        D_801D9574 = D_80187430;
        D_801D9578 = D_80187308;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801D95A8 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801D95A0 & 2) != 0) {
            D_801DAA14[0] = 0x140;
            D_801DAA14[3] = 0x80;
            if (p[0x37] == 4) {
                D_801DAA14[0] = 0x140;
                D_801DAA14[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801DAA14[0] = 0x140;
                D_801DAA14[3] = 0x80;
            }
        }
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D53C);

// @class: schedule
// @stuck: none — MATCH (45 ins, match_one verified)

extern s16 *D_801D957C;
extern void func_800599B8(s32 a0, s32 a1);

void func_8013D8FC(void)
{
    register s16 *psVar3 __asm__("$17");
    register s16 *psVar2 __asm__("$16");
    register s32 c9 __asm__("$19");
    register s32 cff __asm__("$18");
    u16 sVar1;
    s16 buf[4];

    psVar3 = D_801D957C;
    if (psVar3 != (s16 *)0x0 && (sVar1 = (u16)*psVar3, sVar1 != 0xff)) {
        c9 = 9;
        cff = 0xff;
        psVar2 = psVar3 + 5;
        do {
            if (sVar1 == c9) {
                s32 arg2 = *(s32 *)(psVar2 + 1) + psVar2[-1] * 2;
                buf[0] = psVar2[-3];
                buf[1] = psVar2[-2];
                buf[2] = psVar2[-1];
                buf[3] = *psVar2;
                func_800599B8((s32)buf, arg2);
            }
            psVar3 = psVar3 + 8;
            sVar1 = (u16)*psVar3;
            psVar2 = psVar2 + 8;
        } while (sVar1 != cff);
    }
}

// @class: regalloc-order
// @stuck: none — MATCH (141 ins). Handwritten GTE color-interp loop cracked via: 5 callee-saved
//   pins (s0-s4); inner-temp pins (puVar10=t3,puVar9=t2,iVar11=t5,iVar12=t6); mult operands pinned
//   v1/v0 so iVar12 keeps t6; per-copy "memory" barriers -> serial lhu;nop;sh store block; chained
//   $2->$12 pin -> the redundant `addu t4,v0,zero` stORGB move; chained $5->t2 launder -> the a1/t2
//   IV-init copy in the blez delay slot; scratch pins ($2) for the pixel/readback loads and the
//   2nd-slt-per-channel result (v0); byte-offset via a $2 temp -> sll v0 not a1. Launder =
//   `__asm__("":"=r"(x):"0"(x))` (defeats LICM hoist without moving the addiu).


#define gte_ldIR0z()   __asm__ __volatile__("mtc2 $0, $8")
#define gte_ldrgb(p)   __asm__ __volatile__("lwc2 $6, 0(%0)"  :: "r"(p) : "memory")
#define gte_ldIRGB(p)  __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")
#define gte_dpcl()     __asm__ __volatile__("nop\n\tnop\n\tdpcl")
#define gte_stORGB(p)  __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

void func_8013D9B0(int param_1)
{
    extern s32 D_801D9594;

    u8 buf[0x20];
    register s32 uVar13 __asm__("$16");
    register u16 *psVar14 __asm__("$17");
    register u16 *psVar15 __asm__("$18");
    register s32 uVar16 __asm__("$19");
    register void *r0 __asm__("$20");
    register u16 *puVar10 __asm__("$11");
    register u16 *puVar9 __asm__("$10");
    register s32 iVar11 __asm__("$13");
    register s32 iVar12 __asm__("$14");
    u16 sVar4;
    register u32 uVar5 __asm__("$3");
    register u32 uVar7 __asm__("$6");
    register u32 uVar1 __asm__("$7");
    register u32 uVar6 __asm__("$4");
    register u32 uVar8 __asm__("$8");
    register u32 uVar3 __asm__("$9");

    psVar15 = (*(u16 * *)&D_801D957C);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_801D9574)[param_1];
        D_801D9594 = -1;
        uVar16 = 0;
        if (sVar4 != 0xff) {
            r0 = buf + 8;
            psVar14 = psVar15 + 6;
            do {
                iVar11 = 0;
                if (sVar4 == 9) {
                    *(s16 *)(buf + 0) = psVar14[-4];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 2) = psVar14[-3];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 4) = psVar14[-2];
                    __asm__ __volatile__("" ::: "memory");
                    *(s16 *)(buf + 6) = psVar14[-1];
                    __asm__ __volatile__("" ::: "memory");
                    {
                        register s32 mw __asm__("$3") = (s32)((s16 *)psVar14)[-2];
                        register s32 mh __asm__("$2") = (s32)((s16 *)psVar14)[-1];
                        iVar12 = mw * mh;
                    }
                    uVar13 = 0;
                    puVar10 = *(u16 **)psVar14;
                    {
                        register s32 boff __asm__("$2") = iVar12 * 2;
                        register u16 *pi __asm__("$5");
                        pi = (u16 *)((s32)puVar10 + boff);
                        __asm__ __volatile__("" : "=r"(pi) : "0"(pi));
                        puVar9 = pi;
                    }
                    if (0 < iVar12) {
                        do {
                            register u32 pix __asm__("$2");
                            register u32 out __asm__("$2");
                            u32 result;
                            *(u32 *)(buf + 0xc) = (u32)*puVar10;
                            pix = (u32)*puVar9;
                            uVar5 = pix & 0x1f;
                            uVar7 = pix & 0x3e0;
                            uVar1 = pix & 0x7c00;
                            {
                                void *p1;
                                register void *pa __asm__("$2");
                                register void *pb __asm__("$12");
                                __asm__ __volatile__("");
                                p1 = buf + 0xc;
                                __asm__ __volatile__("" : "=r"(p1) : "0"(p1));
                                gte_ldIR0z();
                                gte_ldrgb(r0);
                                gte_ldIRGB(p1);
                                gte_dpcl();
                                pa = buf + 0x10;
                                __asm__ __volatile__("" : "=r"(pa) : "0"(pa));
                                pb = pa;
                                gte_stORGB(pb);
                            }
                            out = *(u32 *)(buf + 0x10);
                            uVar6 = out & 0x1f;
                            uVar8 = out & 0x3e0;
                            uVar3 = out & 0x7c00;
                            if (uVar5 != uVar6) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar5 < (s32)uVar6) uVar5 = uVar5 + 1;
                                c = (s32)uVar6 < (s32)uVar5;
                                if (c) uVar5 = uVar5 - 1;
                            }
                            if (uVar7 != uVar8) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar7 < (s32)uVar8) uVar7 = uVar7 + 0x20;
                                c = (s32)uVar8 < (s32)uVar7;
                                if (c) uVar7 = uVar7 - 0x20;
                            }
                            if (uVar1 != uVar3) {
                                register s32 c __asm__("$2");
                                uVar13 = 1;
                                if ((s32)uVar1 < (s32)uVar3) uVar1 = uVar1 + 0x400;
                                c = (s32)uVar3 < (s32)uVar1;
                                if (c) uVar1 = uVar1 - 0x400;
                            }
                            result = uVar5 | uVar7 | uVar1 | (*(u32 *)(buf + 0xc) & 0x8000);
                            if (result == 0 && *(u32 *)(buf + 0xc) != 0) {
                                result = 0x8000;
                            }
                            *puVar9 = (u16)result;
                            puVar9 = puVar9 + 1;
                            iVar11 = iVar11 + 1;
                            puVar10 = puVar10 + 1;
                        } while (iVar11 < iVar12);
                    }
                    if (uVar13 != 0) {
                        ((void (*)(void *))func_800599B8)(buf);
                    }
                    uVar16 = uVar16 | uVar13;
                }
                psVar15 = psVar15 + 8;
                sVar4 = *psVar15;
                psVar14 = psVar14 + 8;
            } while (sVar4 != 0xff);
        }
        D_801D958C = uVar16;
    }
    return;
}

// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801D9578)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.

extern void *D_801D9578;
extern s16 *D_801D957C;
extern s32 D_801D958C;
extern s32 D_801D95AC;
extern s32 D_801D95B0;
extern s32 D_801D95B4;

extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{
    int *p;
    int x, y, z;
    int flag;

    if (D_801D957C != 0) {
        D_801D958C = 0;
        p = (int *)(param_1 * 12 + (int)D_801D9578);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801D95AC != x) {
            flag = 1;
            if (D_801D95AC < x) {
                if (x - D_801D95AC < 5) {
                    D_801D95AC = x;
                } else {
                    D_801D95AC = D_801D95AC + 4;
                }
            } else {
                if (D_801D95AC - x < 5) {
                    D_801D95AC = x;
                } else {
                    D_801D95AC = D_801D95AC - 4;
                }
            }
        }
        if (D_801D95B0 != y) {
            flag = 1;
            if (D_801D95B0 < y) {
                if (y - D_801D95B0 < 5) {
                    D_801D95B0 = y;
                } else {
                    D_801D95B0 = D_801D95B0 + 4;
                }
            } else {
                if (D_801D95B0 - y < 5) {
                    D_801D95B0 = y;
                } else {
                    D_801D95B0 = D_801D95B0 - 4;
                }
            }
        }
        if (D_801D95B4 != z) {
            flag = 1;
            if (D_801D95B4 < z) {
                if (z - D_801D95B4 < 5) {
                    D_801D95B4 = z;
                } else {
                    D_801D95B4 = D_801D95B4 + 4;
                }
            } else {
                if (D_801D95B4 - z < 5) {
                    D_801D95B4 = z;
                } else {
                    D_801D95B4 = D_801D95B4 - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801D958C = flag;
    }
}

// @class: regalloc-order
// @stuck: none — MATCH (187 ins). Levers: struct-assign DRAWENV copy (align via type); pbase local for $s2-relative D_800B9A02; two-biv SPRT loop (q anchored one-above -> gcc re-anchors, no bare-deref); P_TAG_8013DD68 addPrim; single p var coalesces puVar7->puVar15; pins uVar2=$v1,iVar14=$a3,c5=$t3; biv-increment order sets q-init-before-puVar10-init; Buf 0x68 -> frame 0xA0.

typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } P_TAG_8013DD68;
typedef struct { u32 w[23]; } DrawEnv;              /* 0x5C copy unit, align 4 */
typedef struct { DrawEnv env; u8 pad[0x0C]; } Buf;  /* -> frame 0xA0 (gcc adds 0x10 for the struct-copy) */


#define IDVAL (*(u16 *)(pbase + 0xA3D2))
#define OTE ((P_TAG_8013DD68 *)(D_800BA0E4 + IDVAL * 0x10))

void func_8013DD68() {
    extern void SetDrawEnv(void *p, void *env);
    extern s32 D_800A5E60;
    extern u16 D_800AF7B8;
    extern u8 D_800AF630[];
    extern u8 D_800BA0E4[];
    extern u8 D_801874C0[];

    u32 *p;
    u16 uVar1;
    u16 *puVar16;
    u16 *q;
    u16 *puVar10;
    register u16 uVar2 __asm__("$3");
    int uVar5;
    register int iVar14 __asm__("$7");
    Buf buf;
    u8 *pbase;
    u8 *base;

    pbase = D_800AF630;
    puVar16 = (*(u16 * *)&D_801D957C);
    p = (*(u32 * *)&D_800A5E60);
    uVar1 = *puVar16;
    puVar16 = puVar16 + 1;
    base = pbase + (u32)D_800AF7B8 * 0x5C;
    buf.env = *(DrawEnv *)(base + 0x38);
    *((u8 *)&buf + 0x18) = 0;
    SetDrawEnv(p, &buf);
    ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
    OTE->addr = (u32)p;
    p = p + 0x10;
    iVar14 = 0;
    if (uVar1 != 0) {
        register int c5 __asm__("$11") = 5;
        puVar10 = (u16 *)((int)p + 0x18);
        q = puVar16 + 8;
        do {
            *(u8 *)((int)puVar10 + -0x15) = c5;
            uVar2 = q[-6];
            *(u8 *)((int)puVar10 + -0xd) = 100;
            *(u8 *)((int)puVar10 + -0x10) = (u8)(*(int*)&D_801D95AC);
            *(u8 *)((int)puVar10 + -0xf) = (u8)(*(int*)&D_801D95B0);
            uVar5 = (*(int*)&D_801D95B4);
            *(u32 *)((int)puVar10 + -0x14) = uVar2 & 0x9ff | 0xe1000400;
            *(u8 *)((int)puVar10 + -0xe) = (u8)uVar5;
            *(u16 *)((int)puVar10 + -0xc) = q[-4];
            iVar14 = iVar14 + 1;
            *(u16 *)((int)puVar10 + -0xa) = q[-3];
            *(u8 *)((int)puVar10 + -8) = (u8)*puVar16;
            uVar2 = q[-7];
            *(u16 *)((int)puVar10 + -6) = 0x7800;
            *(u8 *)((int)puVar10 + -7) = (u8)uVar2;
            puVar16 = puVar16 + 8;
            *(u16 *)((int)puVar10 + -4) = q[-2];
            *(u16 *)((int)puVar10 + -2) = q[-1];
            ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
            puVar10 = puVar10 + 0xc;
            OTE->addr = (u32)p;
            p = p + 6;
            q = q + 8;
        } while (iVar14 < (int)(u32)uVar1);
    }
    SetDrawEnv(p, D_801874C0);
    ((P_TAG_8013DD68 *)p)->addr = OTE->addr;
    OTE->addr = (u32)p;
    p = p + 0x10;
    (*(u32 * *)&D_800A5E60) = p;
    return;
}


extern s32 D_801D9594;

s32 func_8013E054(void) {
    return D_801D9594;
}

/* HANDWRITTEN GTE function (asm marked "Handwritten function"). Squared distance of
 * two SVECTORs via the GTE SQR op, then SquareRoot12 of the component sum.
 *
 * NEAR-MATCH ONLY (not byte-exact). All 36 emitted instructions are correct, but the
 * target's two GTE-latency `nop`s between the last `lwc2` and `sqr` cannot be produced:
 * the original was assembled with PsyQ asmpsx, which preserves hand-written cop2 latency
 * nops, whereas the pinned GNU `mipsel-as` STRIPS any nop between a cop2 load and a cop2
 * op (cop2 hazard handling) even under `.set noreorder` and even as `.word 0` — verified.
 * Also the target hand-schedules the final `addu` into the jal delay slot. Both are
 * toolchain-difference residuals (cookbook 5/10), not C-source reachable. Honest stub
 * is the alternative; kept as the closest achievable draft. */
DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013E064 (src/shared) */

/* HANDWRITTEN GTE function (asm marked "Handwritten function"). Squared distance of
 * two SVECTORs via the GTE SQR op, then SquareRoot12 of the component sum.
 *
 * NEAR-MATCH ONLY (not byte-exact). All 36 emitted instructions are correct, but the
 * target's two GTE-latency `nop`s between the last `lwc2` and `sqr` cannot be produced:
 * the original was assembled with PsyQ asmpsx, which preserves hand-written cop2 latency
 * nops, whereas the pinned GNU `mipsel-as` STRIPS any nop between a cop2 load and a cop2
 * op (cop2 hazard handling) even under `.set noreorder` and even as `.word 0` — verified.
 * Also the target hand-schedules the final `addu` into the jal delay slot. Both are
 * toolchain-difference residuals (cookbook 5/10), not C-source reachable. Honest stub
 * is the alternative; kept as the closest achievable draft. */
DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013E0FC (src/shared) */

/* HANDWRITTEN GTE function (asm marked "Handwritten function"). Squared distance of
 * two SVECTORs via the GTE SQR op, then SquareRoot12 of the component sum.
 *
 * NEAR-MATCH ONLY (not byte-exact). All 36 emitted instructions are correct, but the
 * target's two GTE-latency `nop`s between the last `lwc2` and `sqr` cannot be produced:
 * the original was assembled with PsyQ asmpsx, which preserves hand-written cop2 latency
 * nops, whereas the pinned GNU `mipsel-as` STRIPS any nop between a cop2 load and a cop2
 * op (cop2 hazard handling) even under `.set noreorder` and even as `.word 0` — verified.
 * Also the target hand-schedules the final `addu` into the jal delay slot. Both are
 * toolchain-difference residuals (cookbook 5/10), not C-source reachable. Honest stub
 * is the alternative; kept as the closest achievable draft. */
DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013E194 (src/shared) */

DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013E22C (src/shared) */

DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013E298 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (43/43 raw bytes verified via objcopy; match_one's "22 mismatched" is an objdump zero-run-elision artifact that drops the 2 cop2-latency nops)

DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013E2C4 (src/shared) */

DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013E370 (src/shared) */

DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013E410 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (27 ins)

DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013E448 (src/shared) */

DEFINE_func_8013E4B4()  /* dedup: shared engine-core @0x8013E4B4 (src/shared) */

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013E558 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected (simple guarded store block, byte/half/word globals + fn-ptr)

DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013E588 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH expected (clone of byte-proven func_80141874: $v0-pinned fn-ptr; +2 extra calls)

#include "common.h"

extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);

extern u16 D_8011511E;
extern u16 D_8011511C;
extern unsigned short D_80115112;
extern u16 D_80115116;
extern void (*D_80187ED0[])(void);

void func_8013E5E8(void)
{
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_80187ED0[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}

DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013E67C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern u8 D_80078EC0;
extern u16 D_8011511A;
extern u16 D_80115124;
extern u8 D_80115148[];
extern u8 D_80115140[];
extern s32 D_80187EBC;
extern u16 D_80115110;
extern s32 D_80115188;
extern s16 currentLocationId;
extern s16 D_80187E94;
extern s16 D_80187E96;
extern unsigned short D_80115112;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {
    short i;

    func_8013E83C();
    D_8011511A = 0;
    D_80115124 = D_80078EC0;
    for (i = 0; i < 8; i++) {
        *(s16 *)((char *)&D_80115148 + (i << 1)) = 0;
        D_80115140[i] = 0;
    }
    if (!((u32)func_80029504() < 5 || currentLocationId == 0x302A || currentLocationId == 0x3073)) {
        register s32 *ep __asm__("$8");
        register s32 *fp __asm__("$9");
        fp = (s32 *)&D_80115110;
        ep = (s32 *)&D_80187EBC;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_80187E94 = 2;
        D_80187E96 = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_80187E96 = 0;
        D_80187E94 = 0;
        D_80115112 = 6;
    }
}

DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013E814 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

void func_8013E83C() {
    extern int func_80029178(int);
    extern void func_8002D4C8(int, int);
    extern void func_80141C0C(int);
    extern unsigned short D_80115118;
    extern unsigned short D_80115128;
    extern unsigned short D_8011512E;
    extern unsigned int D_80115130;
    extern unsigned short D_80115158;
    extern unsigned short D_8011515A;
    extern unsigned short D_8011515C;
    extern unsigned short D_8011515E;
    extern unsigned short D_80115162;
    extern unsigned short D_80115166;
    extern void * D_801D95C8;
    extern void * D_801D95CC;
    extern unsigned char D_80187B34;
    extern unsigned char D_80187B4C;
    extern unsigned char D_80187BC0;
    extern unsigned char D_80187BC8;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_801D95C8 = &D_80187B34;
        D_801D95CC = &D_80187BC0;
    } else {
        D_801D95C8 = &D_80187B4C;
        D_801D95CC = &D_80187BC8;
    }

    D_8011515A = 0x104;
    D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;

    if (D_80115110 == 3) {
        func_8002D4C8(0x46e, 0);
    } else {
        func_80141C0C(0);
    }
}

// @class: schedule
// @stuck: none — MATCH (63 ins). The idx-32+ residual was a THIRD held base pointer for the
// D_80115188 store: the draft's `((Cell*)&D_80115188)[i].v = v` allocates a pointer, so gcc kept
// three bases (D_80115110/D_80187EBC/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80187EBC -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{
    extern void func_80139954(void);
    extern void func_8014AA28(void);
    extern s32 func_800D0488(s32);
    extern void func_80141C0C(s32);

    s16 *p = &(*(s16*)&D_80115124);
    s16 i;
    s32 v;
    s16 m;

    D_800B9A15 = 0;
    func_80139954();
    if (D_80078EC0 != *p) {
        func_8014AA28();
        if ((D_80078EC0 & 0x7F) != 0) {
            m = D_80078EC0 & 0x7F;
            *p = m;
            if (m == 0 || func_800D0488(m) == 0)
                goto loop;
        }
    }
    *p = 0;
loop:
    for (i = 0; i < 5; i++) {
        s32 *q = &((s32 *)&D_80115110)[i];
        v = ((s32 *)&D_80187EBC)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}

// @class: regalloc-order
// @stuck: none — MATCH
DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013EA54 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern void func_8013F350(void);
extern void func_8013FAF8(s32 a0, s32 a1);
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern unsigned char *func_80141CA4(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013E958(void);

extern short D_800B9A02;
extern u8 D_801151C8[];
extern s32 D_801151D0;
extern u16 D_8011511A;
extern u16 D_8011511E;
extern short D_80115128;
extern unsigned short D_80115112;
extern s16 D_8011512A;
extern s32 D_80115130;
extern unsigned char D_80187E98;

void func_8013EB7C(void) {
    s32 sp10[2];
    short sVar1;
    register short sVar2 __asm__("$2");
    s32 a0v;
    s32 iVar4;

    if ((s16)func_80141C50() == 0) {
        D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
        sVar1 = ((short (*)(void))func_8013F350)();
        if (D_8011511A >= 4) {
            func_8013FAF8((s16)D_8011511A, (s16)(D_8011511A + 1));
        }
        func_8013FAF8(0, 5);
        if (D_8011511A == 5) {
            sVar2 = ((short (*)(s32))func_8014168C)(2);
            a0v = 2;
        } else {
            sVar2 = ((short (*)(s32))func_8014168C)((s16)D_8011511A);
            a0v = (s16)D_8011511A;
        }
        iVar4 = func_8014032C(a0v, sVar2);
        if (iVar4 != 0) {
            s32 *p130 = &D_80115130;
            if (iVar4 != *p130) {
                *p130 = iVar4;
                func_80139954();
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_80187E98));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_80187E98));
            }
            (*(unsigned short *)&D_80115112) -= 1;
        } else {
            if ((D_8011511E & 0x800) != 0 || D_8011512A != 0) {
                func_8013E958();
            }
        }
    }
    (void)sp10;
}


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ED6C (src/shared) */

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_80187E96` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_80187E94` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.

typedef struct { s32 f0; } E4;



s32 func_8013EE10() {
    extern E4 aD80115188[] __asm__("D_80115188");
    extern E4 D_80115168[];
    extern unsigned short D_80115118;

    short i;
    u16 *p;
    u16 old;
    s16 *r;
    u16 *c;
    s32 sp10[2];

    D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
    func_8013FAF8(0, 5);
    for (i = 0; i < 5; i++) {
        s32 t = D_80115168[i].f0 * 3 >> 2;
        aD80115188[i].f0 = t;
        D_80115168[i].f0 = D_80115168[i].f0 - t;
    }
    r = &D_80187E96;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_80187E94 = (u16)D_80187E94 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_80187E98);
        for (i = 0; i < 5; i++) {
            s32 *q = (s32 *)((char *)p - 8);
            *(s32 *)((char *)&q[i] + 0x78) = 0;
            D_80115168[i].f0 = 0;
        }
        c = &D_80115112;
        *c += 1;
    }
    (void)sp10;
}


// @class: struct
// @stuck: none — MATCH (108 ins, relocation-masked)

typedef struct {
    unsigned short field0;   /* 0x00  D_80115118 */
    unsigned char  _pad[0xAE];
    int            arrB0[128];/* 0xB0 */
} S115118;



s32 func_8013EF88() {
    extern int func_800D0488(int);
    extern void func_800D2624(void);
    extern S115118 D_80115118;
    extern int D_80115168;
    extern unsigned short D_80115114;

    unsigned short v;
    short i;
    register short *p124 __asm__("$16");

    v = D_80115118.field0;
    if (v != 0) {
        v = v - 1;
        D_80115118.field0 = v;
        if (v != 0) {
            (*(int*)&D_801151D0) = D_80115118.arrB0[(*(unsigned short*)&D_800B9A02)];
            ((void(*)(int, int))func_8013FAF8)(0, 5);
            for (i = 0; i < 5; i++) {
                int a = *(int *)((char *)&(*(int*)&D_80115188) + (i << 2));
                int b = *(int *)((char *)&D_80115168 + (i << 2));
                int w = a * 3;
                *(int *)((char *)&(*(int*)&D_80115188) + (i << 2)) = w;
                *(int *)((char *)&D_80115168 + (i << 2)) = b + w;
            }
            if (D_80115118.field0 < 3) {
                unsigned short *p96 = &(*(unsigned short*)&D_80187E96);
                *p96 = *p96 - 1;
            }
            {
                unsigned short *p94 = &(*(unsigned short*)&D_80187E94);
                short t = *p94 - 2;
                *p94 = t;
                if (t < 0) *p94 = 0;
            }
        }
    }
    p124 = &(*(short*)&D_80115124);
    {
        short x124 = *p124;
        if (x124 != 0) {
            if (func_800D0488(x124) == 0) return;
            *p124 = 0;
        }
    }
    if (D_80115118.field0 == 0) {
        if (D_80115114 == ((*(unsigned short*)&D_800B9A02) ^ 1)) {
            func_800D2624();
        } else {
            D_80115112 = D_80115112 + 1;
        }
    }
}


// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)

extern unsigned short D_80115118;
extern unsigned short D_80115112;
extern u16 D_80115110;
extern unsigned char D_80187E98;

extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_80187E98);
        }
        D_80115112 += 1;
    }
}

DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013F1BC (src/shared) */

// @class: other
// @stuck: none — MATCH (cached &D_8011511A pointer for the $a1 accesses; test (iVar2<<16) without storing back so $v1 stays live)

DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013F244 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013F350);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013FAF8);

/* func_8013FFD8 — 213 ins, double jump-table, per-location family (134 members). */

extern s32 func_80029178(s32 arg);
extern s32 func_800291B4(s32 arg);

extern short D_80115128;

s32 func_8013FFD8(s16 arg0, s32 arg1, s32 *arg2) {

    extern u8  D_80187BB8[];
    extern u8 D_80187BD0;
    extern u8  D_80187BDC[];
    extern u8  D_80187BE3[];
    extern u8  D_80187BE4[];
    extern s32 D_80187B0C;
    extern s32 D_80187B24[];
    extern char *D_80187AE0;
    extern unsigned short D_80187AF4[];
    extern u8 D_80187B64;
    extern u8 D_80187B68;
    extern u8 *D_80187B74;
    extern s32 D_8010F3C4[];
    extern s32 D_8010EDE8[];
    extern u8  D_80115143;
    extern void * D_801D95CC;
    extern void * D_801D95C8;
    s32 ret;

    *arg2 = 0x808080;
    ret = 0;

    switch (arg0) {                                   /* jtbl_801D8898 */
    case 0: {
        s16 s0 = (s16) arg1;
        if (s0 < 6) {
            if ((((s32 (*)(u8))func_80029178)(D_80187BB8[s0]) & 0xFF) == 0) {
                return 1;
            }
            ret = ((s32 *)&D_80187B0C)[s0];
        }
        break;
    }
    case 1: {
        s16 v1 = (s16) arg1;
        if (v1 < 4) {
            ret = D_80187B24[v1];
        }
        break;
    }
    case 2:
        switch ((*(s16 *)&D_80115128)) {                         /* jtbl_801D88B8 */
        case 0: {
            s16 v1 = (s16) arg1;
            if (v1 < 5) {
                ret = ((s32 *)&D_80187AE0)[v1];
            }
            break;
        }
        case 1: {
            s16 v1 = (s16) arg1;
            if (v1 < 0xC) {
                s32 v3 = ((s32 (*)(u8, s32))func_800291B4)(((u8 *)&D_80187BD0)[v1], arg1) & 0xFF;
                if (v3 == 0) {
                    return 1;
                }
                ret = D_8010EDE8[v3 * 3];
            }
            break;
        }
        case 2: {
            s16 s0 = (s16) arg1;
            if (s0 < 6) {
                if ((((s32 (*)(u8))func_80029178)((*(u8 * *)&D_801D95CC)[s0]) & 0xFF) == 0) {
                    return 1;
                }
                ret = (*(s32 * *)&D_801D95C8)[s0];
            }
            break;
        }
        case 3: {
            s16 s0 = (s16) arg1;
            if (s0 < 6) {
                if ((((s32 (*)(u8))func_80029178)(D_80187BDC[s0]) & 0xFF) == 0) {
                    return 1;
                }
                ret = ((s32 *)D_80187AF4)[s0];
            }
            break;
        }
        case 4: {
            s16 v1 = (s16) arg1;
            if (v1 < 5) {
                ret = ((s32 *)&D_80187B74)[v1];
            }
            break;
        }
        }
        break;
    case 3: {
        s16 t = (s16) arg1;
        if (t <= 0) {
            s16 s0 = t + D_80115143;
            if (s0 != 0) {
                if ((((s32 (*)(u8, s32))func_800291B4)(D_80187BE3[s0], arg1) & 0xFF) == 0) {
                    *arg2 = 0x804040;
                }
                ret = D_8010F3C4[s0];
            } else {
                ret = (*(s32 *)&D_80187B64);
            }
        }
        break;
    }
    case 5: {
        s16 v1 = (s16) arg1;
        if (v1 < 3) {
            ret = ((s32 *)&D_80187B68)[v1];
        }
        break;
    }
    case 6: {
        s16 s0 = (s16) arg1;
        if (s0 < 0x28) {
            s32 idx;
            if ((((s32 (*)(u8, s32))func_800291B4)(D_80187BE4[s0], arg1) & 0xFF) == 0) {
                *arg2 = 0x804040;
            }
            idx = s0 + 1;
            ret = D_8010F3C4[idx];
        }
        break;
    }
    case 7: {
        s16 v1 = (s16) arg1;
        if (v1 < 5) {
            ret = ((s32 *)&D_80187B74)[v1];
        }
        break;
    }
    }
    return ret;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014032C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140608);

// @class: iv-combine
// @stuck: none — MATCH (89 ins). Sequential struct fields fed from a running source
//         pointer compile to fixed offsets when written base[0..n]; the target advances
//         the pointer, so use post-increment `*p++` for EVERY field (gcc drops the dead
//         final increment, yielding the "increment N-2 then offset 0/2" tail).

extern u8 *D_80187B74;
extern u8 *D_80187B78;
extern u8 *D_80187B7C;
extern u8 *D_80187B80;
extern u8 *D_80187B84;
extern u16 *D_80187B88[];
extern u16 *D_80187B90[];
extern u16 *D_80187BB0[];

extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);

void func_801407F4(void)
{
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_80187B74;
    iVar2 = func_80028D58();
    puVar3 = D_80187B88[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_80187B78;
    iVar2 = func_80028DE0();
    puVar3 = D_80187B88[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_80187B7C + 0x18) = *D_80187B90[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_80187B80 + 0x18) = *D_80187B90[iVar2];

    puVar1 = D_80187B84;
    iVar2 = func_80028D9C();
    puVar3 = D_80187BB0[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140958);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140D68);

// @class: struct
// @stuck: none — MATCH

extern unsigned char D_80078E7F;
extern unsigned char D_80078E7E;
extern unsigned char D_80078E7D;
extern M2C_UNK D_80187AB0;

extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

void func_80140E6C(void) {
    void *puVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;

    puVar1 = (*(void * *)&D_80187AB0);
    uVar2 = func_800D2CA8(D_80078E7F, 0x18);
    uVar3 = func_800D2CA8(D_80078E7E, 0xc);
    uVar4 = func_800D2CA8(D_80078E7D, 0);
    func_800D2D10(uVar2 | 0xb00000 | uVar3 | 0xb00 | uVar4, 8, puVar1, 0);
}


// @class: plumbing
// @stuck: none — MATCH (128/128 ins, match_one confirmed)

extern short D_80115128;
extern u8 D_80187AC0;
extern char *D_80187AE0;
extern char *D_80187AE4;
extern char *D_80187AE8;
extern char *D_80187AEC;
extern char *D_80187AF0;

extern int func_80029FE4(void);
extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);
extern char *func_8002AAB4(void);
extern char *strcpy(char *, const char *);
extern int func_8002A26C(void);
extern int func_8002A2B0(void);
extern int func_8002A4B8(void);
extern s32 func_8002A4FC(s32 a0);
extern int func_8002A998(void);
extern int func_8002A9DC(void);
extern int func_8002A728(void);
extern int func_8002A76C(void);
extern int func_80029FD4(void);

void func_80140F00(void) {
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_80187AC0);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_80187AE0;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80187AE4;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80187AE8;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80187AEC;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80187AF0;
        r = func_800D2CA8(func_80029FD4(), 4);
        func_800D2D10(r, 7, p + 0x18, -1);
    }
}


// @class: other
// @stuck: none — MATCH

extern short D_80115128;
extern unsigned short D_80115172;
extern unsigned short D_8018797A;
extern unsigned short D_8018797E;
extern unsigned short D_80187982;
extern unsigned short D_80187986;

extern s32 func_8002A1B4(void);
extern short func_8002A28C(void);
extern short func_8002A27C(void);
extern s32 func_8002A400(void);
extern short func_8002A4D8(void);
extern short func_8002A4C8(void);
extern s32 func_8002A8E0(void);
extern short func_8002A9B8(void);
extern short func_8002A9A8(void);
extern s32 func_8002A670(void);
extern short func_8002A748(void);
extern short func_8002A738(void);
extern int func_801412A8(int, int, int, int, int, int);

int func_80141100(int param_1)
{
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_8018797A;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_8018797E;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80187982;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80187986;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801412A8);

// @class: regalloc-order
// @stuck: none — MATCH (51 ins, match_one relocation-masked)

#include "common.h"

DEFINE_func_801415C0()  /* dedup: shared engine-core @0x801415C0 (src/shared) */

DEFINE_func_8014168C()  /* dedup: shared engine-core @0x8014168C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (45 ins, relocation-masked)

DEFINE_func_801416D4()  /* dedup: shared engine-core @0x801416D4 (src/shared) */

extern unsigned short D_80115112;
extern void (*D_80187F10[])(void);

void func_80141788(void)
{
    D_80187F10[D_80115112]();
}

DEFINE_func_801417C4()  /* dedup: shared engine-core @0x801417C4 (src/shared) */

DEFINE_func_801417F8()  /* dedup: shared engine-core @0x801417F8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH

#include "common.h"

extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_80141C04(void);

extern u16 D_8011511E;
extern u16 D_8011511C;
extern unsigned short D_80115112;
extern u16 D_80115116;
extern void (*D_80187F1C[])(void);

void func_80141874(void) {
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 → store retires early */
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_80187F1C[D_80115112];
    fp();
    func_80141C04();
    D_80115116 += 1;
}

// @class: loose-typing
// @stuck: none — MATCH (90 ins). Key levers:
//   (1) D_8011511A must be a DIRECT volatile global (block-scope `extern volatile unsigned short`),
//       NOT `*(volatile u16*)&D_8011511A`. Volatile forces the store-2-then-read-back reload (else
//       gcc folds 2>=4 and drops the branch); direct-global access recomputes %hi/%lo per reference
//       (3 fresh lui) whereas the `&`-cast pointer form CSEs the address into ONE register (2 ins short).
//   (2) Reconcile with the TU/engine_core canonical types: D_80115158 is `u8[]` (decays -> `*(u16*)D_80115158`),
//       D_8011515C is `u8` (halfword store -> `*(u16*)&D_8011515C`), func_80029178 is `s32(s32)`. Do not
//       redeclare these — the shared DEFINE macros already provide them (conflicting-types hard error).

extern void func_800D24A0(int);
extern void func_8002D4C8(int, int);
extern void func_80141C0C(int);
extern u16 D_8011515A;
extern u16 D_8011515E;
extern u16 D_80115162;
extern u16 D_80115166;
extern u16 D_8011512E;
extern void *D_801D95C8;
extern void *D_801D95CC;
extern u8 D_80187B34;
extern u8 D_80187B4C;
extern u8 D_80187BC0;
extern u8 D_80187BC8;

s32 func_801418F8(void) {
    extern volatile unsigned short D_8011511A;
    extern s32 func_80029178(s32);
    unsigned short t;

    func_800D24A0(1);
    D_8011511A = 2;
    t = D_8011511A;
    D_80115118 = 0;
    D_80115130 = 0;
    if (t >= 4) {
        D_8011511A = t - 3;
    }
    *(u16*)D_80115158 = 0x106;
    if ((func_80029178(0x1C) & 0xFF) == 0) {
        D_801D95C8 = &D_80187B34;
        D_801D95CC = &D_80187BC0;
    } else {
        D_801D95C8 = &D_80187B4C;
        D_801D95CC = &D_80187BC8;
    }
    D_8011515A = 0x104;
    *(u16*)&D_8011515C = 0x104;
    D_8011515E = 0x129;
    D_80115162 = 0x103;
    D_80115166 = 0x105;
    D_80115128 = 0;
    D_8011512E = 0;
    if (D_80115110 == 3) {
        func_8002D4C8(0x46E, 0);
    } else {
        func_80141C0C(0);
    }
    D_80115128 = 1;
    D_80187E94 = 0xE;
    D_80187E96 = 3;
    D_80115112 += 1;
}

// @class: plumbing
// @stuck: TBD — first pass



s32 func_80141A60()
{
    int v;
    s32 frame_pad[2];
    (void)&frame_pad;

    D_801151D0 = ((int *)D_801151C8)[(*(unsigned short *)&D_800B9A02)];
    func_8013F350();
    if ((*(unsigned short *)&D_8011511A) >= 4) {
        func_8013FAF8((short)(*(unsigned short *)&D_8011511A), (short)((*(unsigned short *)&D_8011511A) + 1));
    }
    func_8013FAF8(2, 3);
    v = ((int(*)(int, int))func_8014032C)(2, (short)((*(unsigned char *)&D_8011514C) + (*(unsigned char *)&D_8011514D) * (*(unsigned char *)&D_8011515C)));
    if (v != 0 && v != D_80115130) {
        D_80115130 = v;
        func_80139954();
        ((void (*)(int, void *))func_801376E8)(v, &(*(int *)&D_80187E98));
    }
    func_80137B80();
    if (func_800D0EC4() != 0) {
        (*(unsigned short *)&D_80115116) = 0xFFF8;
        (*(unsigned short *)&D_80115112) = (*(unsigned short *)&D_80115112) + 1;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141B90);

DEFINE_func_80141C04()  /* dedup: shared engine-core @0x80141C04 (src/shared) */

// @class: struct
// @stuck: none — MATCH expected (indexed u16 global: (s16)param_1*2 + D_80115110, *2 array stride)

extern u16 D_80115110;
extern u8 D_80187E70;
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80141C0C(s32 param_1)
{
    func_8002D4C8(*(u16 *)(&D_80187E70 + (((param_1 << 16) >> 15) + (u32)D_80115110) * 2), 0);
}

DEFINE_func_80141C50()  /* dedup: shared engine-core @0x80141C50 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (476 ins). Levers: $v1-pinned cmp temp; default-first early-return form; §5a cross-jump barrier on 0x3ca twin

DEFINE_func_80141CA4()  /* dedup: shared engine-core @0x80141CA4 (src/shared) */

DEFINE_func_80142414()  /* dedup: shared engine-core @0x80142414 (src/shared) */

DEFINE_func_80142454()  /* dedup: shared engine-core @0x80142454 (src/shared) */

// @class: struct
// @stuck: none — MATCH (58 ins). STRUCT branch reconstruction + 3 levers: (1) §3-T4 branch-polarity
//   invert in the ==0 arm so the func_8012C218 cold path sinks to the tail; (2) *(volatile int*) on
//   the two extra param_1[0x32] reloads to defeat gcc CSE (gcc reloads via register reuse, not a store);
//   (3) param_1[0x7e] pinned to $v1 (register __asm__("$3")) + an input-only scheduling barrier
//   __asm__ __volatile__("" : : "r"(a)) on the 0xA read so the pinned load is anchored AFTER it in the
//   ==0 arm (matches the load2-reused-as-$v1 ordering).

extern void (*D_80187F40[])(void);
extern void func_8012C218(void *a0);

void func_801424E4(short *param_1) {
    short sVar1;
    int iVar2;
    register unsigned short t __asm__("$3");

    (*D_80187F40[(unsigned short)param_1[1]])();
    if (*(unsigned short *)param_1 != 0) {
        if (param_1[0x38] != 0) {
            iVar2 = *(int *)(param_1 + 0x32);
            if (iVar2 == 0) {
                return;
            }
            *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
            t = (unsigned short)param_1[0x7e];
            sVar1 = *(unsigned short *)(iVar2 + 10) + t;
            param_1[5] = sVar1;
            *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
        } else {
            unsigned short a;
            iVar2 = *(int *)(param_1 + 0x32);
            if ((iVar2 != 0) && (*(short *)(iVar2 + 0x36) == param_1[0x7f])) {
                *(int *)(param_1 + 2) = *(int *)(iVar2 + 4);
                a = *(unsigned short *)(*(volatile int *)(param_1 + 0x32) + 10);
                __asm__ __volatile__("" : : "r"(a));
                t = (unsigned short)param_1[0x7e];
                sVar1 = a + t;
                iVar2 = *(volatile int *)(param_1 + 0x32);
                param_1[5] = sVar1;
                *(int *)(param_1 + 6) = *(int *)(iVar2 + 0xc);
                return;
            }
            ((void (*)(short *))func_8012C218)(param_1);
        }
    }
    return;
}

extern s32 (*D_80187F50[])();

s32 func_801425CC(s16 *a0) {
    return D_80187F50[(u16)a0[1]]();
}

// @class: schedule
// @stuck: none — MATCH expected; CAE4 block fallthrough, AD50 block goto-tail

extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_80187F34;

void func_80142608(s32 param_1)
{
    register s32 iVar1 __asm__("$16");

    if (*(short *)(param_1 + 0x70) != 0) {
        iVar1 = ((s32 (*)(void))func_8012C1B8)();
    } else {
        iVar1 = func_8012C1DC(*(s32 *)(param_1 + 100));
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CA1C(iVar1, (s32)&D_80187F34);
        *(short *)(iVar1 + 0x1a) = 0x200;
        *(short *)(iVar1 + 0x18) = 0x200;
        *(short *)(param_1 + 0xfc) = 0x40;
        if (*(short *)(param_1 + 0x70) != 0) {
            goto ad50;
        }
        if (*(s32 *)(param_1 + 100) != 0) {
            *(short *)(param_1 + 0xfe) = *(short *)(*(s32 *)(param_1 + 100) + 0x36);
            goto ad50;
        }
    }
    ((void (*)(s32))func_8012CAE4)(param_1);
    return;
ad50:
    *(short *)(param_1 + 0x98) = 0;
    *(s32 *)(param_1 + 0x90) = 0;
    ((void (*)(s32))func_8012AD50)(param_1);
}

DEFINE_func_801426D4()  /* dedup: shared engine-core @0x801426D4 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected (param saved in $s0 across call, guarded tail call)
DEFINE_func_80142740()  /* dedup: shared engine-core @0x80142740 (src/shared) */

extern void func_8012C218(void *a0);

void func_80142778(u8 *a1) {
    u8 *a0 = *(u8 **)(a1 + 0x20);

    *(u16 *)(a0 + 0x18) = *(u16 *)(a0 + 0x18) - 0x800;
    *(u16 *)(a0 + 0x1A) = *(u16 *)(a0 + 0x1A) - 0x800;
    *(u16 *)(a1 + 0xA) = *(u16 *)(a1 + 0xA) + 0x10;
    if (*(s16 *)(a0 + 0x18) <= 0) {
        func_8012C218(a1);
    }
}

DEFINE_func_801427DC()  /* dedup: shared engine-core @0x801427DC (src/shared) */

DEFINE_func_801427E4()  /* dedup: shared engine-core @0x801427E4 (src/shared) */

// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_80187F64[])();

void func_801427EC(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_80187F64[*(u16 *)(param_1 + 2)]();
    }
}

DEFINE_func_80142838()  /* dedup: shared engine-core @0x80142838 (src/shared) */

DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428CC (src/shared) */

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one)

extern u16 D_801270C0;
extern void (*D_80187F80[])(void);

void func_8014292C(s32 param_1)
{
    if ((s16)D_801270C0 != 3) {
        D_80187F80[*(u16 *)(param_1 + 2)]();
    }
}

// @class: struct
// @stuck: none — MATCH (mirrors func_801425CC func-ptr-table idiom + (s16) guard)
extern u16 D_801270C0;
extern s32 (*D_80188150[])();

void func_80142978(s16 *a0) {
    if ((s16)D_801270C0 != 3) {
        D_80188150[(u16)a0[1]]();
    }
}

extern u16 D_801270C0;
extern void (*D_80188208[])(void);
void func_801429C4(short *param_1)
{
  short new_var2;
  short *new_var;
  new_var2 = D_801270C0;
  if (new_var2 != 3)
  {
    new_var = param_1;
    D_80188208[(unsigned short) new_var[1]]();
  }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142A10);

// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)

extern u16 D_800B99D8;
extern struct packed_word D_801D8920;
extern u8 D_801D95D0;
extern u8 D_801D95D1;
extern u8 D_801D95D2;

void func_80142A80(void)
{
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_801D8920;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_801D95D0 = mul * (local.b[0] >> 4);
    D_801D95D1 = mul * (local.b[1] >> 4);
    D_801D95D2 = mul * (local.b[2] >> 4);
}

void func_80142C84(s32 a0);
void func_80143994(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_80142B2C(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0x1c) = 0x180;
    *(s16 *)((u8 *)arg0 + 0x5c) = 0x100;
    *(u16 *)((u8 *)arg0 + 0x100) = *(u16 *)((u8 *)arg0 + 0x70) & 0x100;
    *(u16 *)((u8 *)arg0 + 0x70) = *(u16 *)((u8 *)arg0 + 0x70) & 3;
    *(u16 *)((u8 *)arg0 + 0x72) = *(u16 *)((u8 *)arg0 + 0x72) | 0x1000;
    if (*(s16 *)((u8 *)arg0 + 0x100) == 0) {
        ((void (*)(void))func_80142C84)();
    }
    *(s32 *)((u8 *)arg0 + 0xcc) =
        ((s32 (*)(s32, s32))func_80143994)(
            (s32)arg0, (s32)*(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x18));
    func_8012AD50(arg0);
}

DEFINE_func_80142BB4()  /* dedup: shared engine-core @0x80142BB4 (src/shared) */

DEFINE_func_80142C7C()  /* dedup: shared engine-core @0x80142C7C (src/shared) */

DEFINE_func_80142C84()  /* dedup: shared engine-core @0x80142C84 (src/shared) */

DEFINE_func_80142C9C()  /* dedup: shared engine-core @0x80142C9C (src/shared) */

DEFINE_func_80142D38()  /* dedup: shared engine-core @0x80142D38 (src/shared) */

DEFINE_func_80142DB8()  /* dedup: shared engine-core @0x80142DB8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (combined store-assign `*(p)=v0=call()` keeps test/store on $v0, copy to $s0 for the else)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);

extern int D_80187F58;

void func_80142DC4(int param_1)
{
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, s32))func_8001CA1C)(v0, (s32)&D_80187F58);
        *(short *)(v0 + 0x1a) = 0x1800;
        *(short *)(v0 + 0x18) = 0x1800;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}

// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);

extern unsigned char D_80187F74[];

void func_80142E38(int param_1)
{
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, &D_80187F74);
        sVar1 = (*(unsigned short *)(param_1 + 0x70) & 0xf) * 0x600 + 0x1200;
        *(short *)(iVar2 + 0x1a) = sVar1;
        *(short *)(iVar2 + 0x18) = sVar1;
        *(short *)(param_1 + 0xfc) = 0;
        ((void (*)(int))func_80142B2C)(param_1);
    }
}

// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);

extern s32 D_80188140[];

void func_80142EC0(s32 param_1) {
    register s32 d   __asm__("$16") = param_1;   /* $s0 */
    register s32 obj __asm__("$17");             /* $s1 */
    s32 ret;
    s16 sVar2;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(d + 0x20) = ret;
    obj = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(d);
    } else {
        func_8001CA1C(obj, 0);
        sVar2 = (s16)((*(u16 *)(d + 0x70) & 0xf) * 0x600 + 0xc00);
        *(s16 *)(obj + 0x1a) = sVar2;
        *(s16 *)(obj + 0x18) = sVar2;
        *(s16 *)(d + 0xfc) = 0;
        ((void (*)(s32, s32))func_8012A828)(d, D_80188140[*(u16 *)(d + 0x70) & 0xf]);
        ((void (*)(s32))func_80142B2C)(d);
    }
}

DEFINE_func_80142F68()  /* dedup: shared engine-core @0x80142F68 (src/shared) */

DEFINE_func_80142FFC()  /* dedup: shared engine-core @0x80142FFC (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (38 ins). $16=param pin; explicit $17 copy of the call result
//         survives across func_8001CA1C while $v0 serves the pre-call store/test;
//         store BEFORE the s1 copy so the store keeps $v0 (not the saved copy).

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);

extern unsigned char D_80188160[];
extern unsigned char D_801881C0[];

void func_8014305C(int param_1)
{
    register int s0_param __asm__("$16") = param_1;
    register int s1_copy __asm__("$17");
    int iVar2;
    short sVar1;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(s0_param + 0x20) = iVar2;
    s1_copy = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(s0_param);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_80188160);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_801881C0);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}

DEFINE_func_801430F4()  /* dedup: shared engine-core @0x801430F4 (src/shared) */

DEFINE_func_80143188()  /* dedup: shared engine-core @0x80143188 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (memcpy unaligned copy; $s0 survivor pinned, store-before-copy keeps $v0 for early store/branch)

extern void *memcpy(void *, const void *, u32);

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern s32 func_8012E504(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80142B2C(void *arg0);

extern u8 D_801D891C;
extern u8 D_801D95D0;
extern u8 D_801D95D4;

void func_801431E8(s32 param_1) {
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_801D891C, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_801D95D0);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_801D95D0, 0x10);
            memcpy(&D_801D95D4, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}

DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432FC (src/shared) */

DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */

struct vec;
DEFINE_func_801433F0()  /* dedup: shared engine-core @0x801433F0 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (pending gate)

extern u8 D_800D387C[];
extern u32 D_80188318[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80143458(s32 param_1)
{
    s32 p;
    u16 v;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_800D387C;

    p = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(p + 4) == 0) {
        *(s32 *)(p + 4) = 0x50000000;
    }

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x9c;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
        *(u16 *)(p + 0x18) = v;
    }

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24,
                  D_80188318[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}

struct vec;
DEFINE_func_8014350C()  /* dedup: shared engine-core @0x8014350C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014358C);

DEFINE_func_80143640()  /* dedup: shared engine-core @0x80143640 (src/shared) */

DEFINE_func_801437D8()  /* dedup: shared engine-core @0x801437D8 (src/shared) */

DEFINE_func_80143970()  /* dedup: shared engine-core @0x80143970 (src/shared) */

DEFINE_func_80143994()  /* dedup: shared engine-core @0x80143994 (src/shared) */

DEFINE_func_801439C0()  /* dedup: shared engine-core @0x801439C0 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (key: (s0+4)&=0x7FFFFFFF stmt placed AFTER the 3 sp[]->struct stores; §2-T2/§21 stmt-order)
DEFINE_func_801439FC()  /* dedup: shared engine-core @0x801439FC (src/shared) */

extern void (*D_80188440[])(void *);

void func_80143B30(void *a0)
{
    D_80188440[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80143B6C()  /* dedup: shared engine-core @0x80143B6C (src/shared) */

DEFINE_func_80143BDC()  /* dedup: shared engine-core @0x80143BDC (src/shared) */

extern void (*D_8018844C[])(void *);

void func_80143C38(void *a0)
{
    D_8018844C[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80143C74()  /* dedup: shared engine-core @0x80143C74 (src/shared) */

extern void (*D_80188454[])(void *);

void func_80143C98(void *a0)
{
    D_80188454[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80143CD4()  /* dedup: shared engine-core @0x80143CD4 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (80 ins, relocation-masked). iVar2/iVar3 pinned $s1/$s2; sVar4 is an
//   int set BEFORE the call so it naturally takes callee-saved $s3; chained assignment
//   a=b=c=sVar4 materializes the value once (the addu $v0,$s3,$zero move) + delay-slot store.

     /* size 0x0c */

extern MatEntry D_80188478[];
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80143D28(s32 param_1) {
    register s32 iVar3 __asm__("$18") = *(s32 *)(param_1 + 0x20); /* $s2 */
    register s32 iVar2 __asm__("$17") = *(s32 *)(param_1 + 0x64); /* $s1 */
    MatEntry *p = &D_80188478[*(s16 *)(param_1 + 0x70)];
    s32 sVar4;
    s32 iVar1;

    *(s16 *)(iVar3 + 0x14) = p->f8;
    *(u16 *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + p->fa;
    sVar4 = 0x1000;
    ApplyMatrixSV((void *)(*(s32 *)(param_1 + 0x20) + 0x34), p, (void *)(param_1 + 0x50));

    if (*(s16 *)(param_1 + 0xfe) == 0 &&
        (iVar2 == 0 || *(s16 *)(iVar2 + 0x36) != *(s16 *)(param_1 + 0xfc) ||
         *(u8 *)(iVar2 + 0xc1) != 6)) {
        if (0x10 < *(s32 *)(param_1 + 0x1c)) {
            *(s32 *)(param_1 + 0x1c) = 0x10;
        }
        *(s16 *)(param_1 + 0xfe) = 1;
    }

    iVar1 = *(s32 *)(param_1 + 0x1c);
    if (iVar1 < 0x11) {
        sVar4 = iVar1 << 8;
    }
    if (0x73 < iVar1) {
        sVar4 = (0x78 - iVar1) << 10;
    }
    *(s16 *)(iVar3 + 0x18) = *(s16 *)(iVar3 + 0x1a) = *(s16 *)(iVar3 + 0x1c) = sVar4;

    if (func_8012BEE8(param_1)) {
        func_8012C218((void *)param_1);
    }
}

extern void (*D_8018849C[])(void *);

void func_80143E68(void *a0)
{
    D_8018849C[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80143EA4()  /* dedup: shared engine-core @0x80143EA4 (src/shared) */

DEFINE_func_80143EAC()  /* dedup: shared engine-core @0x80143EAC (src/shared) */

DEFINE_func_80143EB4()  /* dedup: shared engine-core @0x80143EB4 (src/shared) */

DEFINE_func_80143EBC()  /* dedup: shared engine-core @0x80143EBC (src/shared) */

extern void (*D_801884B0[])(void *);

void func_80144054(void *a0)
{
    D_801884B0[*(u16 *)((s32)a0 + 0x2)](a0);
}

// @class: regalloc-order
// @stuck: 154/154 ins structural match (callees/consts/ctrl-flow/stack/GPU-packet all byte-correct); residual 25 = caller-saved temp-reg coalescing in the final ring-vertex block (target reuses dead $s0=iVar3 for iVar3-(iVar4>>6) subu where gcc reuses iVar4>>6's reg; iVar4 mflo -> $a3 vs target $v0) + 2-ins schedule swap of giv-increment vs iVar2*4 -> permuter grinder territory (§27 step-5)

 /* 0x14 stride */

extern void *func_80010A08(s32);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 AddPrim(s32, void *);
extern OtBlk D_800A651C[];
extern u8 D_800AF648;
extern short D_800B9A02;

void func_80144090(s32 param_1) {
    void *iVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    s32 iVar5;
    s32 iVar6;
    struct {
        s16 v10[4];
        u16 sxy[2];
        s32 p;
        s32 flag;
    } L;

    iVar1 = func_80010A08(0x140);
    if (iVar1 != 0) {
        *(s32 *)(param_1 + 4) = *(s32 *)(param_1 + 4) + *(s32 *)(param_1 + 0x10);
        *(s32 *)(param_1 + 8) = *(s32 *)(param_1 + 8) + *(s32 *)(param_1 + 0x14);
        *(s32 *)(param_1 + 0xc) = *(s32 *)(param_1 + 0xc) + *(s32 *)(param_1 + 0x18);
        L.v10[0] = *(u16 *)(param_1 + 6);
        L.v10[1] = *(u16 *)(param_1 + 0xa);
        L.v10[2] = *(u16 *)(param_1 + 0xe);
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648);
        iVar2 = RotTransPers((s32)L.v10, (s32)L.sxy, &L.p, &L.flag);
        iVar2 = iVar2 + 4;
        if (iVar2 < 0) {
            iVar2 = 0;
        }
        iVar6 = 0;
        do {
            *(s32 *)((u8 *)iVar1 + 4) = 0xffffff;
            *(u8 *)((u8 *)iVar1 + 3) = 4;
            *(u8 *)((u8 *)iVar1 + 7) = 0x20;
            if (*(s32 *)(param_1 + 0x1c) - 6 < 1) {
                *(s16 *)((u8 *)iVar1 + 8) = L.sxy[0];
                *(s16 *)((u8 *)iVar1 + 0xa) = L.sxy[1];
            } else {
                iVar5 = func_8004787C(iVar6);
                *(s16 *)((u8 *)iVar1 + 8) = L.sxy[0] + ((iVar5 * ((*(s32 *)(param_1 + 0x1c) - 6) << 4)) >> 0xc);
                iVar5 = func_80047948(iVar6);
                *(s16 *)((u8 *)iVar1 + 0xa) = L.sxy[1] + ((iVar5 * ((*(s32 *)(param_1 + 0x1c) - 6) << 4)) >> 0xc);
            }
            iVar3 = func_8004787C(iVar6) * (*(s32 *)(param_1 + 0x1c) << 4);
            iVar4 = func_80047948(iVar6) * (*(s32 *)(param_1 + 0x1c) << 4);
            iVar6 = iVar6 + 0x100;
            *(s16 *)((u8 *)iVar1 + 0x10) = L.sxy[0] + ((iVar3 + (iVar4 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0x12) = L.sxy[1] + ((iVar4 + (iVar3 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0xc) = L.sxy[0] + ((iVar3 - (iVar4 >> 6)) >> 0xc);
            *(s16 *)((u8 *)iVar1 + 0xe) = L.sxy[1] + ((iVar4 - (iVar3 >> 6)) >> 0xc);
            AddPrim(D_800A651C[(u16)D_800B9A02].a + (iVar2 * 4), iVar1);
            iVar1 = (u8 *)iVar1 + 0x14;
        } while (iVar6 < 0x1000);
    }
}

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one); fn-ptr dispatch table + 0x1c counter, sibling idiom (func_801427EC/func_80143B30)

extern void (*D_801884B8[])();

void func_801442F8(int param_1)
{
    int iVar1;

    D_801884B8[*(u16 *)(param_1 + 2)]();
    iVar1 = *(int *)(param_1 + 0x1c) + 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (0x1d < iVar1) {
        func_8012C218(param_1);
    }
}

// @class: plumbing
// @stuck: none — MATCH expected; call-crossing param_1->$s1, iVar3->$s0 natural regalloc
#include "common.h"

extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80188434;

void func_80144364(int param_1) {
    int iVar3;
    u16 uVar2;
    s16 sVar1;

    iVar3 = ((s32 (*)(void))func_8012C194)();
    if (iVar3 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        uVar2 = *(u16 *)(*(int *)(param_1 + 0x64) + 0x36);
        *(int *)(param_1 + 0xCC) = iVar3;
        *(u16 *)(param_1 + 0xFC) = uVar2;
        func_8001CB6C((u8 *)iVar3, (s32)&D_80188434, 0x250, 0x1A0);
        *(s32 *)(iVar3 + 4) = 0x60000000;
        *(u8 *)(iVar3 + 0x27) = 0x14;
        *(u16 *)(iVar3 + 0x10) = 0x400;
        *(u16 *)(iVar3 + 8) = *(u16 *)(*(int *)(param_1 + 0x64) + 6);
        *(u16 *)(iVar3 + 0xA) = *(u16 *)(*(int *)(param_1 + 0x64) + 0xA);
        *(u16 *)(iVar3 + 0xC) = *(u16 *)(*(int *)(param_1 + 0x64) + 0xE);
        sVar1 = *(s16 *)(param_1 + 0x70);
        if (sVar1 != 0) {
            *(s16 *)(iVar3 + 0x1A) = sVar1;
            *(s16 *)(iVar3 + 0x18) = sVar1;
        } else {
            *(u16 *)(iVar3 + 0x1A) = 0x2000;
            *(u16 *)(iVar3 + 0x18) = 0x2000;
        }
        *(u16 *)(param_1 + 2) = 1;
    }
}

extern void func_80016714(void *a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80128ED8(void *a0, void *a1);
extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_80188448;

void func_80144458(void *arg0) {
    s32 temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_s2 = M2C_FIELD(arg0, void **, 0xCC);
    if (M2C_FIELD(arg0, s16 *, 0x70) == 0) {
        temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x64), void **, 0x20);
        if (temp_v0 != NULL) {
            temp_s0 = (M2C_FIELD(temp_v0, s16 *, 0x12) - 0x400) & 0xFFF;
            M2C_FIELD(arg0, s32 *, 0x10) = (s32) (func_80047948(temp_s0) * D_80188448 * 0x10);
            M2C_FIELD(arg0, s32 *, 0x18) = (s32) (func_8004787C(temp_s0) * -D_80188448 * 0x10);
            func_8012AD80(arg0);
        }
    }
    M2C_FIELD(temp_s2, u16 *, 8) = (u16) M2C_FIELD(arg0, u16 *, 6);
    M2C_FIELD(temp_s2, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
    M2C_FIELD(temp_s2, u16 *, 0xC) = (u16) M2C_FIELD(arg0, u16 *, 0xE);
    if (func_80128ED8(temp_s2, arg0 + 0xD0) != 0) {
        func_80016714(temp_s2, 0x38);
        func_8012C218(arg0);
    }
}

// @class: plumbing
// @stuck: none — MATCH (53 ins). Natural regalloc (iVar1->$s0, param_1->$s1) matched without pins; only plumbing note: func_8012C194 canonical is void(void) but asm uses $v0, so gate may need call-site cast / s32 decl reconciliation.
#include "common.h"

DEFINE_func_80144558()  /* dedup: shared engine-core @0x80144558 (src/shared) */

DEFINE_func_8014462C()  /* dedup: shared engine-core @0x8014462C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (match_one 54/54, relocation-masked)

DEFINE_func_801446A4()  /* dedup: shared engine-core @0x801446A4 (src/shared) */

// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_8018845C;
extern u8 D_80188468;

void func_8014477C(void *param_1) {
    s32 v0;
    s32 v1;
    register s32 uVar2 __asm__("$2");
    register s32 addr __asm__("$3");
    s32 gv;
    s32 fv;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001CA1C)(v0, &D_8018845C);
    if (*(u16 *)(*(s32 *)((s32)param_1 + 0x64)) != 0) {
        *(s16 *)((s32)param_1 + 0xFC) = *(u16 *)(*(s32 *)((s32)param_1 + 0x64) + 0x36);
        uVar2 = *(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x58);
        if (uVar2 != 0) {
            addr = uVar2 & 0xFFFFFFF;
            gv = *(u16 *)((addr | 0x80000000) + 8);
            fv = *(u16 *)((s32)param_1 + 0xA) - 0x30;
            *(u16 *)((s32)param_1 + 0xA) = gv + fv;
        } else {
            *(u16 *)((s32)param_1 + 0xA) = *(u16 *)((s32)param_1 + 0xA) - 0x60;
        }
    }
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_80188468);
    v1 = (s32)*(s16 *)((s32)param_1 + 0x70) << 0xC;
    *(s16 *)((s32)param_1 + 0x2) = 1;
    *(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) = v1 / 3;
    *(s32 *)((s32)param_1 + 0x1C) = 0x78;
}

// @class: regalloc-order
// @stuck: none — MATCH (66 ins). Pins: $s0=func_8012C194 result, $s1=param, $v0=byte const b (forces sb-first + $v0 reuse for 0x6000/0x400/0x4000); separate var e for the 0xE load keeps it in $v1 stored last.
#include "common.h"

extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

extern u8 D_80188434;
extern u8 D_801884A4;

void func_80144880(s32 param_1)
{
    register s32 obj  __asm__("$16");   /* $s0 */
    register s32 self __asm__("$17") = param_1;  /* $s1 */
    register s32 b    __asm__("$2");    /* $v0 */
    s32 e;

    obj = ((s32 (*)(void))func_8012C194)();
    if (obj == 0) {
        ((void (*)(s32))func_8012CAE4)(self);
    } else {
        *(u16 *)(self + 0xFC) = *(u16 *)(*(s32 *)(self + 0x64) + 0x36);
        *(s32 *)(self + 0xCC) = obj;
        if (*(s16 *)(self + 0x70) == 1) {
            func_8001CB6C((u8 *)obj, (s32)&D_80188434, 0x250, 0x1A0);
            b = 0x14;
        } else {
            func_8001CB6C((u8 *)obj, (s32)&D_801884A4, 0x300, 0x1D0);
            b = 0x6A;
        }
        *(u8 *)(obj + 0x27) = (u8)b;
        *(s32 *)(obj + 4) = 0x60000000;
        *(u16 *)(obj + 0x10) = 0x400;
        *(u16 *)(obj + 8) = *(u16 *)(*(s32 *)(self + 0x64) + 6);
        *(u16 *)(obj + 0xA) = *(u16 *)(*(s32 *)(self + 0x64) + 0xA);
        e = *(u16 *)(*(s32 *)(self + 0x64) + 0xE);
        *(u16 *)(obj + 0x1A) = 0x4000;
        *(u16 *)(obj + 0x18) = 0x4000;
        *(u16 *)(obj + 0xC) = (u16)e;
        *(s16 *)(self + 2) = *(s16 *)(self + 2) + 1;
    }
}

DEFINE_func_80144988()  /* dedup: shared engine-core @0x80144988 (src/shared) */

extern void (*D_801884C0[])(void *);

void func_801449C8(void *a0)
{
    D_801884C0[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80144A04()  /* dedup: shared engine-core @0x80144A04 (src/shared) */

extern void (*D_801884C8[])(void *);

void func_80144A2C(void *a0)
{
    D_801884C8[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80144A68()  /* dedup: shared engine-core @0x80144A68 (src/shared) */

DEFINE_func_80144A90()  /* dedup: shared engine-core @0x80144A90 (src/shared) */

DEFINE_func_80144A98()  /* dedup: shared engine-core @0x80144A98 (src/shared) */

DEFINE_func_80144AEC()  /* dedup: shared engine-core @0x80144AEC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144B14);
