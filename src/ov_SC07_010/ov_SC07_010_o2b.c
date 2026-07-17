#include "common.h"
#include "../shared/engine_core.h"

extern void func_80016714(void *a0, s32 a1);

void func_8013C98C(void) {

    extern s32 D_801A6AA0;
    extern s32 D_801269D4;
    extern s32 D_801269C8;
    func_80016714(&D_801A6AA0, 8);
    D_801269D4 = 0;
    D_801269C8 = 0;
}


extern void func_80019064(void *a0);

void func_8013C9C4(void * arg0)
{

    extern M2C_UNK D_80062BC0;
    extern s32 D_801A6AA0;
    extern s8 D_801A6AA4;
    extern s8 D_801A6AA5;
    D_801A6AA0 = arg0;
    D_801A6AA4 = 0;
    D_801A6AA5 = 0;
    if (func_80019198() == 0) {
        func_80019064(&D_80062BC0);
    }
}



void func_8013CA14(void)
{

    extern s32 D_801A6AA0;
    extern s8 D_801A6AA4;
    extern s8 D_801A6AA5;
    extern s32 D_801269C8;
    extern s32 D_801269D4;
  int *base = &D_801A6AA0;
  signed char *p;
  unsigned char c;
  int t;
  if ((*base) != 0)
  {
    c = D_801A6AA5;
    if (c == 0)
    {
      p = (signed char *) ((((unsigned int) ((unsigned char) D_801A6AA4)) * 2) + D_801A6AA0);
      t = (int) (*p);
      D_801269D4 = t;
      D_801269C8 = t;
      D_801A6AA5 = (unsigned char) p[1];
      D_801A6AA4 = D_801A6AA4 + 1;
      if (D_801A6AA5 == 0)
      {
        D_801269D4 = 0;
        D_801269C8 = 0;
        D_801A6AA4 = 0;
        *base = 0;
      }
    }
    else
    {
      D_801A6AA5 = c - 1;
    }
  }
  return;
}




void func_8013CABC(void) {

    extern s32 D_801A6AC4;
    extern s32 D_801A6AB8;
    extern s32 D_801A6ABC;
    extern s32 D_801A6AC8;
    D_801A6AC4 = 1;
    D_801A6AB8 = 1;
    D_801A6ABC = 0;
    D_801A6AC8 = 1;
}




void func_8013CAE8(void) {

    extern s32 D_801A6AB8;
    extern s32 D_801A6ABC;
    extern s32 D_801A6AC0;
    extern s32 D_801A6AC4;
    extern s32 D_801A6AC8;
    D_801A6AB8 = 1;
    D_801A6AC4 = 0;
    D_801A6ABC = 0;
    D_801A6AC0 = -1;
    D_801A6AC8 = 0;
}




void func_8013CB20(void)
{

    extern s32 D_801A6AC4;
    extern s32 D_801A6AC8;
    extern s32 D_801A6AF0;
    extern s32 D_801A6AF4;
    D_801A6AF0 = D_801A6AC8;
    D_801A6AF4 = D_801A6AC4;
    D_801A6AC8 = 1;
    D_801A6AC4 = 0;
}




void func_8013CB5C(void) {

    extern s32 D_801A6AF0;
    extern s32 D_801A6AF4;
    extern s32 D_801A6AC8;
    extern s32 D_801A6AC4;
    D_801A6AC8 = D_801A6AF0;
    D_801A6AC4 = D_801A6AF4;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013CB84);



void func_8013CF68()
{
    extern void func_80028620();
    extern u8 D_800A5E94[];
    extern s32 D_800A5E8C;
    extern s32 D_800A5E90;
    extern u8 D_800A5E95;
    extern u8 D_800A5E96;
    extern u8 D_801A93F0;
    extern u8 D_801A93F1;
    extern u8 D_801A93F2;
    extern u8 D_801A93F3;
    extern u8 D_801A93F4;
    extern u8 D_801A93F5;
    extern u8 D_801A93F6;
    extern u8 D_801A93F7;
    extern u8 D_801A93F8;

    u8 t0, t1, t2;
    u8 *base;
    __asm__("la %0, D_800A5E94" : "=r"(base));

    *(s32 *)(base - 0xC) = 0;
    t0 = D_801A93F0; t1 = D_801A93F1; t2 = D_801A93F2;
    D_800A5E8C = 0x1E;
    D_800A5E90 = 0;
    base[0] = t0; D_800A5E95 = t1; D_800A5E96 = t2;
    func_80028620(0, base - 0xC);

    *(s32 *)(base + 4) = 0; *(s32 *)(base + 8) = 7;
    t0 = D_801A93F3; t1 = D_801A93F4; t2 = D_801A93F5;
    *(s32 *)(base + 0xC) = 0x14;
    base[0x10] = t0; base[0x11] = t1; base[0x12] = t2;
    func_80028620(1, base + 4);

    *(s32 *)(base + 0x14) = 0;
    t0 = D_801A93F6; t1 = D_801A93F7; t2 = D_801A93F8;
    *(s32 *)(base + 0x18) = -0x12;
    *(s32 *)(base + 0x1C) = 0;
    base[0x20] = t0; base[0x21] = t1; base[0x22] = t2;
    func_80028620(2, base + 0x14);
}




// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern void func_8013D9B0();

void func_8013D064(void)
{

    extern s32 D_801A6AD0;
    extern s32 D_801A6AB8;
    extern s32 D_801A6AD4;
    extern s32 D_801A6AC4;
    if (D_801A6AD0 != 0) {
        if (D_801A6AD0 != 2) {
            if (((D_801A6AD0 < 3) && (D_801A6AD0 == 1)) &&
                (D_801A6AD4 = D_801A6AD4 + 1, 0x23a < D_801A6AD4)) {
                D_801A6AB8 = D_801A6AD0;
                D_801A6AD0 = 2;
            }
        } else {
            D_801A6AB8 = D_801A6AB8 + -1;
            if (D_801A6AB8 == 0) {
                D_801A6AB8 = D_801A6AD0;
                ((void (*)(s32))func_8013D9B0)(2);
                if (D_801A6AC4 == 0) {
                    D_801A6AD0 = D_801A6AD0 + 1;
                }
            }
        }
    }
    return;
}



extern void func_8013D9B0();

s32 func_8013D13C(void) {

    extern s32 D_801A6AC4;
    func_8013D9B0();
    return D_801A6AC4;
}




void func_8013D164(void) {

    extern s32 D_801A6AD0;
    D_801A6AD0 = 1;
}



void func_8013D178(void) {

    extern u8 D_801A93F0;
    extern u8 D_801A93F1;
    extern u8 D_801A93F2;
    extern u8 D_801A93F3;
    extern u8 D_801A93F4;
    extern u8 D_801A93F5;
    extern u8 D_801A93F6;
    extern u8 D_801A93F7;
    extern u8 D_801A93F8;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    extern unsigned char D_801A9490, D_801A9491, D_801A9492, D_801A9493, D_801A9494, D_801A9495, D_801A9496, D_801A9497, D_801A9498;
    unsigned char v, t;
    register unsigned char *p __asm__("$5");

    p = &D_801A93F0; v = *p; t = D_801A9490;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F1; v = *p; t = D_801A9491;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F2; v = *p; t = D_801A9492;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F3; v = *p; t = D_801A9493;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F4; v = *p; t = D_801A9494;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F5; v = *p; t = D_801A9495;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F6; v = *p; t = D_801A9496;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F7; v = *p; t = D_801A9497;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
    p = &D_801A93F8; v = *p; t = D_801A9498;
    if (v != t) { if (v < t) *p = v + 8; else *p = v - 8; }
}




// @class: other
// @stuck: none — MATCH (three step-toward-target byte clamps + word store)


void func_8013D330(void) {

    extern u8 D_801A94D2;
    extern u8 D_801A9546;
    extern u8 D_801A93FA;
    extern u8 D_801A94B4;
    extern u8 D_801A93D8;
    extern u8 D_801A93F9;
    extern s32 D_801A94B8;
    if ((D_801A94D2 & 0xff) != D_801A9546) {
        D_801A94D2 = ((D_801A94D2 & 0xff) < D_801A9546) ? (D_801A94D2 + 1) : (D_801A94D2 - 1);
    }
    if ((D_801A93FA & 0xff) != D_801A94B4) {
        D_801A93FA = ((D_801A93FA & 0xff) < D_801A94B4) ? (D_801A93FA + 1) : (D_801A93FA - 1);
    }
    if ((D_801A93D8 & 0xff) != D_801A93F9) {
        D_801A93D8 = ((D_801A93D8 & 0xff) < D_801A93F9) ? (D_801A93D8 + 1) : (D_801A93D8 - 1);
    }
    D_801A94B8 = 1;
}



// @class: regalloc-order
// @stuck: none — MATCH (match_one 90/90); base &D_80078E78 cached in a pointer local so gcc pins it into callee-saved $s1 and hoists the addr to the prologue (live across all 4 calls); direct array access D_80078E78[0x37] instead folds %lo per use (no $s1, frame 0x18 not 0x20)




extern void func_8013D53C(void);
extern void func_8013DD68(void);
extern void func_8013D8FC(void);
extern void func_8013CF68(void);

void func_8013D3D4(int param_1, int param_2)
{

    extern u8 D_80078E78[];
    extern void *D_801A6AA8;
    extern void *D_801A6AAC;
    extern void *D_801A6AB0;
    extern s32 D_801A6AD8;
    extern s32 D_801A6ADC;
    extern s32 D_801A6AE0;
    extern s32 D_801A942C[];
    extern u8 D_80182800[];
    extern u8 D_801828A8[];
    extern u8 D_80182758[];
    extern u8 D_80182854[];
    extern u8 D_801828D4[];
    extern u8 D_801827AC[];
    u8 *p = D_80078E78;

    D_801A6AD8 = param_2;
    D_801A6ADC = (param_2 >> 2) & 3;
    D_801A6AE0 = (param_2 >> 4) & 1;
    if (((param_2 >> 2) & 3) == 0) {
        D_801A6AA8 = D_80182800;
        D_801A6AAC = D_801828A8;
        D_801A6AB0 = D_80182758;
    } else {
        D_801A6AA8 = D_80182854;
        D_801A6AAC = D_801828D4;
        D_801A6AB0 = D_801827AC;
    }
    func_8013D53C();
    if ((param_2 & 1) != 0) {
        if (D_801A6AE0 != 0) {
            func_8013DD68();
        } else {
            func_8013D8FC();
        }
        func_8013CF68();
        if ((D_801A6AD8 & 2) != 0) {
            D_801A942C[0] = 0x140;
            D_801A942C[3] = 0x80;
            if (p[0x37] == 4) {
                D_801A942C[0] = 0x140;
                D_801A942C[3] = 0;
            }
            if (p[0x37] == 0) {
                D_801A942C[0] = 0x140;
                D_801A942C[3] = 0x80;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013D53C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013D8FC);

extern void func_800599B8(s32 a0, s32 a1);
#define gte_ldIR0z()   __asm__ __volatile__("mtc2 $0, $8")
#define gte_ldrgb(p)   __asm__ __volatile__("lwc2 $6, 0(%0)"  :: "r"(p) : "memory")
#define gte_ldIRGB(p)  __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")
#define gte_dpcl()     __asm__ __volatile__("nop\n\tnop\n\tdpcl")
#define gte_stORGB(p)  __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

void func_8013D9B0(int param_1)
{

    extern void *D_801A6AAC;
    extern s16 *D_801A6AB4;
    extern s32 D_801A6AC4;
    extern s32 D_801A6ACC;

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

    psVar15 = (*(u16 * *)&D_801A6AB4);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_801A6AAC)[param_1];
        D_801A6ACC = -1;
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
        D_801A6AC4 = uVar16;
    }
    return;
}



// @class: struct
// @stuck: none — MATCH (match_one 97/97). Two levers: (1) offset-first pointer arith
//   `(int*)(param_1*12 + (int)D_801A6AB0)` makes the addu `offset+base` (dest=v0) so x/y/z
//   load into a0/a1/a2 and each global loads LATE into v1 (base-first gave addu dest=v1 →
//   global hoisted into a0, shifting x/y/z to a1/a2/a3). (2) the clamp must be NESTED
//   if/else (slti dup'd inside each <,>= branch), NOT a merged `if(diff<5)` after the
//   branch — gcc cross-jumps the identical `G=x` and `G=t` store tails into the two shared
//   sites; the merged form emits one slti + unconditional store and diverges.


extern void func_8013DD68(void);

void func_8013DBE4(int param_1)
{

    extern void *D_801A6AB0;
    extern s16 *D_801A6AB4;
    extern s32 D_801A6AC4;
    extern s32 D_801A6AE4;
    extern s32 D_801A6AE8;
    extern s32 D_801A6AEC;
    int *p;
    int x, y, z;
    int flag;

    if (D_801A6AB4 != 0) {
        D_801A6AC4 = 0;
        p = (int *)(param_1 * 12 + (int)D_801A6AB0);
        x = p[0];
        y = p[1];
        z = p[2];
        flag = 0;
        if (D_801A6AE4 != x) {
            flag = 1;
            if (D_801A6AE4 < x) {
                if (x - D_801A6AE4 < 5) {
                    D_801A6AE4 = x;
                } else {
                    D_801A6AE4 = D_801A6AE4 + 4;
                }
            } else {
                if (D_801A6AE4 - x < 5) {
                    D_801A6AE4 = x;
                } else {
                    D_801A6AE4 = D_801A6AE4 - 4;
                }
            }
        }
        if (D_801A6AE8 != y) {
            flag = 1;
            if (D_801A6AE8 < y) {
                if (y - D_801A6AE8 < 5) {
                    D_801A6AE8 = y;
                } else {
                    D_801A6AE8 = D_801A6AE8 + 4;
                }
            } else {
                if (D_801A6AE8 - y < 5) {
                    D_801A6AE8 = y;
                } else {
                    D_801A6AE8 = D_801A6AE8 - 4;
                }
            }
        }
        if (D_801A6AEC != z) {
            flag = 1;
            if (D_801A6AEC < z) {
                if (z - D_801A6AEC < 5) {
                    D_801A6AEC = z;
                } else {
                    D_801A6AEC = D_801A6AEC + 4;
                }
            } else {
                if (D_801A6AEC - z < 5) {
                    D_801A6AEC = z;
                } else {
                    D_801A6AEC = D_801A6AEC - 4;
                }
            }
        }
        if (flag != 0) {
            func_8013DD68();
        }
        D_801A6AC4 = flag;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013DD68);



s32 func_8013E054(void) {

    extern s32 D_801A6ACC;
    return D_801A6ACC;
}


DEFINE_func_8013E064()  /* dedup: shared engine-core @0x8013e064 (src/shared) */


DEFINE_func_8013E0FC()  /* dedup: shared engine-core @0x8013e0fc (src/shared) */


DEFINE_func_8013E194()  /* dedup: shared engine-core @0x8013e194 (src/shared) */


DEFINE_func_8013E22C()  /* dedup: shared engine-core @0x8013e22c (src/shared) */


DEFINE_func_8013E298()  /* dedup: shared engine-core @0x8013e298 (src/shared) */


DEFINE_func_8013E2C4()  /* dedup: shared engine-core @0x8013e2c4 (src/shared) */


DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013e370 (src/shared) */


DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013e410 (src/shared) */


DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013e448 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013E4B4);

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013e558 (src/shared) */


DEFINE_func_8013E588()  /* dedup: shared engine-core @0x8013e588 (src/shared) */



extern void func_80029444(void);
extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_800190AC(void);
extern void func_80141C04(void);


void func_8013E5E8(void)
{

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_80183374[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 -> store retires early */
    func_80029444();
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_80183374[D_80115112];
    fp();
    func_800190AC();
    func_80141C04();
    D_80115116 += 1;
}


DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013e67c (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (90 ins, relocation-masked)

extern s16 currentLocationId;

extern void func_8013E83C(void);
extern s32 func_80029504(void);

void func_8013E6AC(void) {

    extern u8 D_80078EC0;
    extern u16 D_8011511A;
    extern u16 D_80115124;
    extern u8 D_80115148[];
    extern u8 D_80115140[];
    extern s32 D_80183360;
    extern u16 D_80115110;
    extern s32 D_80115188;
    extern s16 D_80183338;
    extern s16 D_8018333A;
    extern unsigned short D_80115112;
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
        ep = (s32 *)&D_80183360;
        for (i = 0; i < 5; i++) {
            register s32 *fa __asm__("$6");
            s32 v;
            fa = (s32 *)(i * 4 + (s32)fp);
            v = ep[i] * 3 >> 2;
            fa[0x16] = v;
            *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
        }
        D_80183338 = 2;
        D_8018333A = 1;
        { u16 *q = &D_80115112; *q += 1; }
    } else {
        func_8013E83C();
        D_8011511A = 7;
        D_8018333A = 0;
        D_80183338 = 0;
        D_80115112 = 6;
    }
}


DEFINE_func_8013E814()  /* dedup: shared engine-core @0x8013e814 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (direct u16 global reads fold to lui/lhu; scheduler hoists the D_8011511A read above the prologue, reproduced by -O2)

void func_8013E83C() {

    extern u16 D_80115110;
    extern u16 D_8011511A;
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
    extern void * D_801A6B00;
    extern void * D_801A6B04;
    extern unsigned char D_80182FD8;
    extern unsigned char D_80182FF0;
    extern unsigned char D_80183064;
    extern unsigned char D_8018306C;

    D_80115118 = 0;
    D_80115130 = 0;
    if (D_8011511A >= 4) {
        D_8011511A = D_8011511A - 3;
    }
    D_80115158 = 0x106;

    if ((func_80029178(0x1c) & 0xFF) == 0) {
        D_801A6B00 = &D_80182FD8;
        D_801A6B04 = &D_80183064;
    } else {
        D_801A6B00 = &D_80182FF0;
        D_801A6B04 = &D_8018306C;
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
// three bases (D_80115110/D_80183360/D_80115188) and buried the branch-delay `sll` (i<<16 carry)
// under the extra store. Switching to the sibling func_8013E6AC's relocation-masked form
// `*(s32*)((char*)&D_80115188 + (i<<2))` recomputes that address via per-iteration %hi/%lo, leaving
// only TWO held pointers (fp=&D_80115110 -> $t0, ep=&D_80183360 -> $a3) and freeing the delay slot
// to carry `i<<16` in $a0 exactly as the target does. Head (idx 0-31) already matched; i naturally
// lands in $a2 from the goto-loop delay slots, driving the fp/ep/fa=$8/$7/$5 alloc with no pins.

void func_8013E958()
{

    extern u8 D_80078EC0;
    extern u16 D_80115110;
    extern unsigned short D_80115112;
    extern u16 D_80115124;
    extern s32 D_80115188;
    extern s32 D_80183360;
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
        v = ((s32 *)&D_80183360)[i] >> 6;
        q[0x16] = v;
        *(s32 *)((char *)&D_80115188 + (i << 2)) = v;
    }
    func_80141C0C(7);
    (*(u16*)&D_80115112) = 4;
}


DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013ea54 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (sVar2 pinned to $v0 forces in-place sll/sra sign-ext scratch)


extern s32 func_80141C50(void);
extern void func_8013F350(void);
extern void func_8013FAF8(s16 a0, s16 a1);
extern s16 func_8014168C(s16 a0);
extern s32 func_8014032C(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_801376E8(int a0, int a1);
extern void func_80137B80(void);
extern unsigned char *func_80141CA4(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013E958(void);


void func_8013EB7C(void) {

    extern short D_800B9A02;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern u16 D_8011511A;
    extern u16 D_8011511E;
    extern short D_80115128;
    extern unsigned short D_80115112;
    extern s16 D_8011512A;
    extern s32 D_80115130;
    extern unsigned char D_8018333C;
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
                func_801376E8(iVar4, (s32)&(*(u8 *)&D_8018333C));
            }
        }
        func_80137B80();
        if ((D_8011511E & 0x10) != 0 && D_8011511A < 5 && sVar1 == 0) {
            (*(s16 *)&D_80115128) = 0;
            func_8002D4C8(0x466, 0);
            if (D_8011511A != 4) {
                func_801376E8((s32)((s32 (*)(void))func_80141CA4)(), (s32)&(*(u8 *)&D_8018333C));
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


DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ed6c (src/shared) */


extern void func_801376E8(int a0, int a1);
extern void func_8013FAF8(s16 a0, s16 a1);
extern unsigned char *func_80141CA4(void);

// @class: struct
// @stuck: none — MATCH (94 ins, relocation-masked). Keys: (1) §18 array-of-STRUCT fold
//   `typedef struct{s32 f0;} E4; extern E4 arr[]; arr[i].f0` defeats gcc's base-CSE/loop-hoist so each
//   global-array access stays a per-access `lui %hi; addu idx; lw/sw %lo(sym)($at)` (a plain `s32 arr[];
//   arr[i]` HOISTS the base into a reg → wrong). (2) §21 global-RMW: the conditional `D_8018333A` bump and
//   the `D_80115112` increment keep the address in ONE reg → access via a pointer var, not the bare global.
//   (3) the 2nd-loop base `q = p-8` (=&D_80115118 kept in $s0 across the calls) is declared INSIDE the loop
//   so loop.c hoists it to the preheader slot AFTER `i=0` (an explicit pre-loop `q=` emits it BEFORE i=0,
//   +2 off). (4) dead `s32 sp10[2];(void)sp10;` reserves the extra 8 frame bytes (0x28, not 0x20).
//   Conflict-safe externs: asm-alias `aD80115188` (file-scope decl is scalar `s32 D_80115188`); `(u16)`
//   cast on the `s16 D_80183338` read for the `lhu`; `D_80115168` is undeclared elsewhere in the TU.

typedef struct { s32 f0; } E4;



s32 func_8013EE10() {

    extern short D_800B9A02;
    extern unsigned short D_80115112;
    extern u8 D_801151C8[];
    extern s32 D_801151D0;
    extern s16 D_80183338;
    extern s16 D_8018333A;
    extern unsigned char D_8018333C;
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
    r = &D_8018333A;
    if (*r < 3) {
        *r = *r + 1;
    }
    D_80183338 = (u16)D_80183338 + 2;
    p = &D_80115118;
    old = *p;
    *p = old + 1;
    if (old >= 5) {
        ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018333C);
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


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013EF88);



// @class: struct
// @stuck: none — MATCH expected (u16* base materialization for read+write, %lo-folded single-access globals)


extern unsigned char *func_80141CA4(void);
extern void func_801376E8(int a0, int a1);

void func_8013F138(void) {

    extern unsigned short D_80115118;
    extern unsigned short D_80115112;
    extern u16 D_80115110;
    extern unsigned char D_8018333C;
    u16 *p = &D_80115118;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (D_80115110 == 0) {
            ((void (*)(int, unsigned char *))func_801376E8)((int)func_80141CA4(), &D_8018333C);
        }
        D_80115112 += 1;
    }
}


DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013f1bc (src/shared) */


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013f244 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013F350);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013FAF8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8013FFD8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014032C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80140608);


// @class: iv-combine
// @stuck: none — MATCH (89 ins). Sequential struct fields fed from a running source
//         pointer compile to fixed offsets when written base[0..n]; the target advances
//         the pointer, so use post-increment `*p++` for EVERY field (gcc drops the dead
//         final increment, yielding the "increment N-2 then offset 0/2" tail).


extern s32 func_80028D58(void);
extern s32 func_80028DE0(void);
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);

void func_801407F4(void)
{

    extern u8 *D_80183018;
    extern u8 *D_8018301C;
    extern u8 *D_80183020;
    extern u8 *D_80183024;
    extern u8 *D_80183028;
    extern u16 *D_8018302C[];
    extern u16 *D_80183034[];
    extern u16 *D_80183054[];
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_80183018;
    iVar2 = func_80028D58();
    puVar3 = D_8018302C[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_8018301C;
    iVar2 = func_80028DE0();
    puVar3 = D_8018302C[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_80183020 + 0x18) = *D_80183034[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_80183024 + 0x18) = *D_80183034[iVar2];

    puVar1 = D_80183028;
    iVar2 = func_80028D9C();
    puVar3 = D_80183054[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80140958);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80140D68);


// @class: struct
// @stuck: none — MATCH


extern int func_800D2CA8(int, int);
extern void func_800D2D10(int, int, void *, int);

void func_80140E6C(void) {

    extern unsigned char D_80078E7F;
    extern unsigned char D_80078E7E;
    extern unsigned char D_80078E7D;
    extern M2C_UNK D_80182F54;
    void *puVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned int uVar4;

    puVar1 = (*(void * *)&D_80182F54);
    uVar2 = func_800D2CA8(D_80078E7F, 0x18);
    uVar3 = func_800D2CA8(D_80078E7E, 0xc);
    uVar4 = func_800D2CA8(D_80078E7D, 0);
    func_800D2D10(uVar2 | 0xb00000 | uVar3 | 0xb00 | uVar4, 8, puVar1, 0);
}




// @class: plumbing
// @stuck: none — MATCH (128/128 ins, match_one confirmed)


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

    extern short D_80115128;
    extern u8 D_80182F64;
    extern char *D_80182F84;
    extern char *D_80182F88;
    extern char *D_80182F8C;
    extern char *D_80182F90;
    extern char *D_80182F94;
    char *p;
    int r;

    if (D_80115128 == 0) {
        p = (*(char * *)&D_80182F64);
        r = func_800D2CA8(func_80029FE4() + 1, 0x18);
        func_800D2D10(r, 2, p + 4, 1);
        strcpy(p + 0xA, func_8002AAB4());

        p = D_80182F84;
        r = func_800D2CA8(func_8002A26C() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A2B0(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80182F88;
        r = func_800D2CA8(func_8002A4B8() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(((int (*)(void))func_8002A4FC)(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80182F8C;
        r = func_800D2CA8(func_8002A998() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A9DC(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80182F90;
        r = func_800D2CA8(func_8002A728() + 1, 0x18);
        func_800D2D10(r, 2, p + 0x12, 1);
        r = func_800D2CA8(func_8002A76C(), 0x18);
        func_800D2D10(r, 2, p + 0x22, -1);

        p = D_80182F94;
        r = func_800D2CA8(func_80029FD4(), 4);
        func_800D2D10(r, 7, p + 0x18, -1);
    }
}




// @class: other
// @stuck: none — MATCH


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

    extern short D_80115128;
    extern unsigned short D_80115172;
    extern unsigned short D_80182E1E;
    extern unsigned short D_80182E22;
    extern unsigned short D_80182E26;
    extern unsigned short D_80182E2A;
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_80182E1E;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_80182E22;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80182E26;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_80182E2A;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801412A8);

DEFINE_func_801415C0()  /* dedup: shared engine-core @0x801415c0 (src/shared) */


DEFINE_func_8014168C()  /* dedup: shared engine-core @0x8014168c (src/shared) */


DEFINE_func_801416D4()  /* dedup: shared engine-core @0x801416d4 (src/shared) */




void func_80141788(void)
{

    extern unsigned short D_80115112;
    extern void (*D_801833B4[])(void);
    D_801833B4[D_80115112]();
}


DEFINE_func_801417C4()  /* dedup: shared engine-core @0x801417c4 (src/shared) */


DEFINE_func_801417F8()  /* dedup: shared engine-core @0x801417f8 (src/shared) */



extern void func_801754A8(void);
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_80141C04(void);


void func_80141874(void) {

    extern u16 D_8011511E;
    extern u16 D_8011511C;
    extern unsigned short D_80115112;
    extern u16 D_80115116;
    extern void (*D_801833C0[])(void);
    register void (*fp)(void) __asm__("$2"); /* pin fn-ptr to $v0 → store retires early */
    func_801754A8();
    D_8011511E = func_80014ED4(0);
    D_8011511C = func_80015018(0);
    fp = D_801833C0[D_80115112];
    fp();
    func_80141C04();
    D_80115116 += 1;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801418F8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80141A60);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80141B90);

void func_80141C04(void) {
}


// @class: struct
// @stuck: none — MATCH expected (indexed u16 global: (s16)param_1*2 + D_80115110, *2 array stride)

extern void func_8002D4C8(s32 a0, s32 a1);

void func_80141C0C(s32 param_1)
{

    extern u16 D_80115110;
    extern u8 D_80183314;
    func_8002D4C8(*(u16 *)(&D_80183314 + (((param_1 << 16) >> 15) + (u32)D_80115110) * 2), 0);
}


DEFINE_func_80141C50()  /* dedup: shared engine-core @0x80141c50 (src/shared) */


DEFINE_func_80141CA4()  /* dedup: shared engine-core @0x80141ca4 (src/shared) */


DEFINE_func_80142414()  /* dedup: shared engine-core @0x80142414 (src/shared) */


DEFINE_func_80142454()  /* dedup: shared engine-core @0x80142454 (src/shared) */



// @class: struct
// @stuck: none — MATCH (58 ins). STRUCT branch reconstruction + 3 levers: (1) §3-T4 branch-polarity
//   invert in the ==0 arm so the func_8012C218 cold path sinks to the tail; (2) *(volatile int*) on
//   the two extra param_1[0x32] reloads to defeat gcc CSE (gcc reloads via register reuse, not a store);
//   (3) param_1[0x7e] pinned to $v1 (register __asm__("$3")) + an input-only scheduling barrier
//   __asm__ __volatile__("" : : "r"(a)) on the 0xA read so the pinned load is anchored AFTER it in the
//   ==0 arm (matches the load2-reused-as-$v1 ordering).

extern void func_8012C218(void *a0);

void func_801424E4(short *param_1) {

    extern void (*D_801833E4[])(void);
    short sVar1;
    int iVar2;
    register unsigned short t __asm__("$3");

    (*D_801833E4[(unsigned short)param_1[1]])();
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




void func_801425CC(void *a0) {

    extern void (*D_801833F4[])(void);
    D_801833F4[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: schedule
// @stuck: none — MATCH expected; CAE4 block fallthrough, AD50 block goto-tail

extern void func_8012C1B8(void);
extern s32 func_8012C1DC(s32 a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern s32 func_8012AD50(void *a0);

void func_80142608(s32 param_1)
{

    extern s32 D_801833D8;
    register s32 iVar1 __asm__("$16");

    if (*(short *)(param_1 + 0x70) != 0) {
        iVar1 = ((s32 (*)(void))func_8012C1B8)();
    } else {
        iVar1 = func_8012C1DC(*(s32 *)(param_1 + 100));
    }
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CA1C(iVar1, (s32)&D_801833D8);
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


DEFINE_func_801426D4()  /* dedup: shared engine-core @0x801426d4 (src/shared) */


DEFINE_func_80142740()  /* dedup: shared engine-core @0x80142740 (src/shared) */


DEFINE_func_80142778()  /* dedup: shared engine-core @0x80142778 (src/shared) */


void func_801427DC(void) {
}

void func_801427E4(void) {
}


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_801427EC(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80183408[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80183408[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80142838);

DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428cc (src/shared) */



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_8014292C(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_80183424[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_80183424[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_80142978(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_801835F4[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_801835F4[*(u16 *)(param_1 + 2)]();
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)


void func_801429C4(int param_1)
{

    extern u16 D_801270C0;
    extern void (*D_801836AC[])();
    if (*(s16 *)&D_801270C0 != 3) {
        D_801836AC[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80142A10);


// @class: struct
// @stuck: none — MATCH (packed-word struct -> lwl/lwr unaligned copy; union byte[] -> $sp-direct lbu; branch-polarity invert -> beqz)


void func_80142A80(void)
{

    extern u16 D_800B99D8;
    extern struct packed_word D_801A61B8;
    extern u8 D_801A6B08;
    extern u8 D_801A6B09;
    extern u8 D_801A6B0A;
    u16 flags;
    union word_bytes local;
    s32 mul;

    flags = D_800B99D8;
    local.pw = D_801A61B8;

    if (flags & 0x10) {
        mul = (s8)((flags & 0xf) >> 1) + 9;
    } else {
        mul = 0x10 - (s8)((flags & 0xf) >> 1);
    }

    D_801A6B08 = mul * (local.b[0] >> 4);
    D_801A6B09 = mul * (local.b[1] >> 4);
    D_801A6B0A = mul * (local.b[2] >> 4);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80142B2C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80142BB4);

void func_80142C7C(void) {
}

DEFINE_func_80142C84()  /* dedup: shared engine-core @0x80142c84 (src/shared) */


DEFINE_func_80142C9C()  /* dedup: shared engine-core @0x80142c9c (src/shared) */


DEFINE_func_80142D38()  /* dedup: shared engine-core @0x80142d38 (src/shared) */


DEFINE_func_80142DB8()  /* dedup: shared engine-core @0x80142db8 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (combined store-assign `*(p)=v0=call()` keeps test/store on $v0, copy to $s0 for the else)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80142B2C(void *arg0);


void func_80142DC4(int param_1)
{

    extern int D_801833FC;
    int v0;

    *(int *)(param_1 + 0x20) = v0 = ((int (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, s32))func_8001CA1C)(v0, (s32)&D_801833FC);
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


void func_80142E38(int param_1)
{

    extern unsigned char D_80183418[];
    short sVar1;
    int iVar2;

    *(int *)(param_1 + 0x20) = iVar2 = ((int (*)(void))func_8012C1B8)();
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((void (*)(int, void *))func_8001CA1C)(iVar2, &D_80183418);
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


void func_80142EC0(s32 param_1) {

    extern s32 D_801835E4[];
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
        ((void (*)(s32, s32))func_8012A828)(d, D_801835E4[*(u16 *)(d + 0x70) & 0xf]);
        ((void (*)(s32))func_80142B2C)(d);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80142F68);

DEFINE_func_80142FFC()  /* dedup: shared engine-core @0x80142ffc (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (38 ins). $16=param pin; explicit $17 copy of the call result
//         survives across func_8001CA1C while $v0 serves the pre-call store/test;
//         store BEFORE the s1 copy so the store keeps $v0 (not the saved copy).

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142B2C(void *arg0);


void func_8014305C(int param_1)
{

    extern unsigned char D_80183604[];
    extern unsigned char D_80183664[];
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
        ((void (*)(int, void *))func_8001CA1C)(s1_copy, D_80183604);
        sVar1 = (*(unsigned short *)(s0_param + 0x70) & 0xf) * 0x600 + 0xc00;
        *(short *)(s1_copy + 0x1a) = sVar1;
        *(short *)(s1_copy + 0x18) = sVar1;
        *(short *)(s0_param + 0xfc) = 0;
        func_8012A828(s0_param, D_80183664);
        ((void (*)(int))func_80142B2C)(s0_param);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801430F4);

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


void func_801431E8(s32 param_1) {

    extern u8 D_801A61B4;
    extern u8 D_801A6B08;
    extern u8 D_801A6B0C;
    u8 buf[8];
    s32 iVar5;
    u16 uVar2;
    s16 sVar4;

    register s32 d __asm__("$16");
    memcpy(buf, &D_801A61B4, 4);
    iVar5 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar5;
    d = iVar5;
    if (iVar5 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001CA88)(d, &D_801A6B08);
        uVar2 = *(u16 *)(param_1 + 0x70);
        *(s16 *)(d + 0x76) = -0x10;
        sVar4 = (uVar2 & 0xf) * 0x600 + 0xc00;
        *(s16 *)(d + 0x1a) = sVar4;
        *(s16 *)(d + 0x18) = sVar4;
        *(u32 *)(d + 4) = *(u32 *)(d + 4) | 0x50000000;
        if (func_8012E504(param_1, 0x33) == 0) {
            *(s16 *)(param_1 + 0xfc) = 1;
            func_800233CC(&D_801A6B08, 0x10);
            memcpy(&D_801A6B0C, buf, 4);
        } else {
            *(s16 *)(param_1 + 0xfc) = 0;
        }
        ((void (*)(s32))func_80142B2C)(param_1);
    }
}


DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432fc (src/shared) */


DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801433F0);


// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80143458(s32 param_1)
{

    extern u8 D_800D387C[];
    extern u32 D_801837BC[];
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
                  D_801837BC[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014350C);


// @class: plumbing
// @stuck: none — MATCH (pending gate)


extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8014358C(s32 param_1)
{

    extern u8 D_801837CC[];
    extern u32 D_801838C8[];
    s32 p;
    u16 v;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_801837CC;

    p = *(s32 *)(param_1 + 0x20);
    if (*(s32 *)(p + 4) == 0) {
        *(s32 *)(p + 4) = 0x50000000;
    }

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x90;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
        *(u16 *)(p + 0x18) = v;
    }

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24,
                  D_801838C8[*(u16 *)(param_1 + 0x34) & 3]);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


DEFINE_func_80143640()  /* dedup: shared engine-core @0x80143640 (src/shared) */


DEFINE_func_801437D8()  /* dedup: shared engine-core @0x801437d8 (src/shared) */


DEFINE_func_80143970()  /* dedup: shared engine-core @0x80143970 (src/shared) */


DEFINE_func_80143994()  /* dedup: shared engine-core @0x80143994 (src/shared) */


DEFINE_func_801439C0()  /* dedup: shared engine-core @0x801439c0 (src/shared) */


DEFINE_func_801439FC()  /* dedup: shared engine-core @0x801439fc (src/shared) */




void func_80143B30(void *a0) {

    extern void (*D_801838E4[])(void);
    D_801838E4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143B6C()  /* dedup: shared engine-core @0x80143b6c (src/shared) */


DEFINE_func_80143BDC()  /* dedup: shared engine-core @0x80143bdc (src/shared) */




void func_80143C38(void *a0) {

    extern void (*D_801838F0[])(void);
    D_801838F0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143C74()  /* dedup: shared engine-core @0x80143c74 (src/shared) */




void func_80143C98(void *a0) {

    extern void (*D_801838F8[])(void);
    D_801838F8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80143CD4()  /* dedup: shared engine-core @0x80143cd4 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (80 ins, relocation-masked). iVar2/iVar3 pinned $s1/$s2; sVar4 is an
//   int set BEFORE the call so it naturally takes callee-saved $s3; chained assignment
//   a=b=c=sVar4 materializes the value once (the addu $v0,$s3,$zero move) + delay-slot store.

     /* size 0x0c */

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80143D28(s32 param_1) {

    extern MatEntry D_8018391C[];
    register s32 iVar3 __asm__("$18") = *(s32 *)(param_1 + 0x20); /* $s2 */
    register s32 iVar2 __asm__("$17") = *(s32 *)(param_1 + 0x64); /* $s1 */
    MatEntry *p = &D_8018391C[*(s16 *)(param_1 + 0x70)];
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




void func_80143E68(void *a0) {

    extern void (*D_80183940[])(void);
    D_80183940[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80143EA4(void) {
}

void func_80143EAC(void) {
}

void func_80143EB4(void) {
}

DEFINE_func_80143EBC()  /* dedup: shared engine-core @0x80143ebc (src/shared) */




void func_80144054(void *a0) {

    extern void (*D_80183954[])(void);
    D_80183954[*(u16 *)((s32)a0 + 0x2)]();
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

void func_80144090(s32 param_1) {

    extern OtBlk D_800A651C[];
    extern u8 D_800AF648;
    extern short D_800B9A02;
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


extern void func_8012C218(void *a0);

// @class: struct
// @stuck: none — MATCH (relocation-masked match_one); fn-ptr dispatch table + 0x1c counter, sibling idiom (func_801427EC/func_80143B30)


void func_801442F8(int param_1)
{

    extern void (*D_8018395C[])();
    int iVar1;

    D_8018395C[*(u16 *)(param_1 + 2)]();
    iVar1 = *(int *)(param_1 + 0x1c) + 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (0x1d < iVar1) {
        func_8012C218(param_1);
    }
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);

void func_80144364(int param_1) {

    extern u8 D_801838D8;
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
        func_8001CB6C((u8 *)iVar3, (s32)&D_801838D8, 0x250, 0x1A0);
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


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80144458);

DEFINE_func_80144558()  /* dedup: shared engine-core @0x80144558 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014462C);

DEFINE_func_801446A4()  /* dedup: shared engine-core @0x801446a4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (65 ins, match_one). Levers: uVar2/$2 + addr/$3 pins; split (uVar2&0xFFFFFFF) into addr then (addr|0x80000000)+8 deref; %hi/%lo of 0x80000008 via plain 0x80000000+8 (match_one masks the target's D_80000008 reloc, real bytes identical); v1/3 magic-divide; gv+fv reassoc (field-0x30 in own temp) loads field first
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8014477C(void *param_1) {

    extern u8 D_80183900;
    extern u8 D_8018390C;
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
    ((void (*)(s32, void *))func_8001CA1C)(v0, &D_80183900);
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
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_8018390C);
    v1 = (s32)*(s16 *)((s32)param_1 + 0x70) << 0xC;
    *(s16 *)((s32)param_1 + 0x2) = 1;
    *(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) = v1 / 3;
    *(s32 *)((s32)param_1 + 0x1C) = 0x78;
}



extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);


void func_80144880(s32 param_1)
{

    extern u8 D_801838D8;
    extern u8 D_80183948;
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
            func_8001CB6C((u8 *)obj, (s32)&D_801838D8, 0x250, 0x1A0);
            b = 0x14;
        } else {
            func_8001CB6C((u8 *)obj, (s32)&D_80183948, 0x300, 0x1D0);
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




void func_801449C8(void *a0) {

    extern void (*D_80183964[])(void);
    D_80183964[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A04()  /* dedup: shared engine-core @0x80144a04 (src/shared) */




void func_80144A2C(void *a0) {

    extern void (*D_8018396C[])(void);
    D_8018396C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80144A68()  /* dedup: shared engine-core @0x80144a68 (src/shared) */


void func_80144A90(void) {
}

DEFINE_func_80144A98()  /* dedup: shared engine-core @0x80144a98 (src/shared) */


DEFINE_func_80144AEC()  /* dedup: shared engine-core @0x80144aec (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80144B14);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80144B9C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801457A4);

void func_801458E0(void) {
}

DEFINE_func_801458E8()  /* dedup: shared engine-core @0x801458e8 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_801844F8 block defeats the tail-merge of the two identical D_801844F8 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145934(void) {

    extern u8 D_801844F8;
    extern u8 D_80184468;
    extern u8 D_80184444;
    extern u8 D_80184420;
    extern u8 D_801844D4;
    extern u8 D_801844B0;
    extern u8 D_8018448C;
    extern u8 D_801843FC;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_801844F8;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_801844F8 load from being
         * tail-merged with the v>=0x384 D_801844F8 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80184468;
    } else if (v >= 0x578) {
        p = &D_80184444;
    } else if (v >= 0x514) {
        p = &D_80184420;
    } else if (v >= 0x384) {
        p = &D_801844F8;
    } else if (v >= 0x258) {
        p = &D_801844D4;
    } else if (v >= 0xC8) {
        p = &D_801844B0;
    } else if (v >= 0xA) {
        p = &D_8018448C;
    } else {
        p = &D_801843FC;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}



// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_80184588 block defeats the tail-merge of the two identical D_80184588 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);


void func_80145A2C(void) {

    extern u8 D_80184588;
    extern u8 D_80184468;
    extern u8 D_80184444;
    extern u8 D_80184420;
    extern u8 D_80184564;
    extern u8 D_80184540;
    extern u8 D_8018451C;
    extern u8 D_801843FC;
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80184588;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80184588 load from being
         * tail-merged with the v>=0x384 D_80184588 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80184468;
    } else if (v >= 0x578) {
        p = &D_80184444;
    } else if (v >= 0x514) {
        p = &D_80184420;
    } else if (v >= 0x384) {
        p = &D_80184588;
    } else if (v >= 0x258) {
        p = &D_80184564;
    } else if (v >= 0xC8) {
        p = &D_80184540;
    } else if (v >= 0xA) {
        p = &D_8018451C;
    } else {
        p = &D_801843FC;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}


DEFINE_func_80145B24()  /* dedup: shared engine-core @0x80145b24 (src/shared) */


DEFINE_func_80145BF8()  /* dedup: shared engine-core @0x80145bf8 (src/shared) */


DEFINE_func_80145C54()  /* dedup: shared engine-core @0x80145c54 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80145CEC);



// @class: schedule
// @stuck: branch layout — 3-way dispatch on param_1; trying switch form

extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);


void func_80145EE8(s32 param_1)
{

    extern unsigned char D_80183980[];
    extern unsigned char D_801839B0[];
    extern unsigned char D_80183A00[];
    extern unsigned char D_80183A30[];
    extern unsigned char D_80183A60[];
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))func_80029178)(0x1F) != 0) {
            ((void (*)(void *))func_80146014)(D_80183980);
        }
        if (((unsigned char (*)(int))func_80029178)(0x21) != 0) {
            ((void (*)(void *))func_80146014)(D_801839B0);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1E) != 0) {
            ((void (*)(void *))func_80146014)(D_80183A00);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1D) != 0) {
            ((void (*)(void *))func_80146014)(D_80183A30);
        }
        if (((unsigned char (*)(int))func_80029178)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))func_80146014)(D_80183A60);
        break;
    case 1:
        ((void (*)(void *))func_80146014)(D_80183980);
        ((void (*)(void *))func_80146014)(D_801839B0);
        ((void (*)(void *))func_80146014)(D_80183A00);
        ((void (*)(void *))func_80146014)(D_80183A30);
        ((void (*)(void *))func_80146014)(D_80183A60);
        break;
    }
}


DEFINE_func_80146014()  /* dedup: shared engine-core @0x80146014 (src/shared) */


void func_80146074(void) {
}


extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0(void);

void func_8014607C(void)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_80146128\n"
        "lui   $at, %%hi(D_801A6B48)\n"
        "sw    $v0, %%lo(D_801A6B48)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B48)\n"
        "lw    $v0, %%lo(D_801A6B48)($v0)\n"
        "nop\n"
        "beqz  $v0, .L80146114\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_80146360\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "addu  $t0, $v1, $zero\n"
        "sw    $sp, 0($t0)\n"
        "addiu $t0, $t0, -4\n"
        "addu  $sp, $t0, $zero\n"
        "jal   func_801463A0\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        ".L80146114:\n"
        "nop\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_80146128()  /* dedup: shared engine-core @0x80146128 (src/shared) */



// @class: struct
// @stuck: none — MATCH (fnptr-table idiom: D_80183AB0[u8 idx](&arg))

void func_80146360(void)
{

    extern void (*D_80183AB0[])(void *);
    extern u8 D_80126BA4;
    extern s32 D_80126B58;
    D_80183AB0[D_80126BA4](&D_80126B58);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801463A0);

DEFINE_func_80146534()  /* dedup: shared engine-core @0x80146534 (src/shared) */


DEFINE_func_80146554()  /* dedup: shared engine-core @0x80146554 (src/shared) */


DEFINE_func_80146578()  /* dedup: shared engine-core @0x80146578 (src/shared) */


DEFINE_func_8014659C()  /* dedup: shared engine-core @0x8014659c (src/shared) */


DEFINE_func_801465C0()  /* dedup: shared engine-core @0x801465c0 (src/shared) */


DEFINE_func_801465E4()  /* dedup: shared engine-core @0x801465e4 (src/shared) */


DEFINE_func_80146608()  /* dedup: shared engine-core @0x80146608 (src/shared) */


DEFINE_func_801466B4()  /* dedup: shared engine-core @0x801466b4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801466F0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80146750);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014680C);

DEFINE_func_801468C8()  /* dedup: shared engine-core @0x801468c8 (src/shared) */


DEFINE_func_80146924()  /* dedup: shared engine-core @0x80146924 (src/shared) */


DEFINE_func_80146994()  /* dedup: shared engine-core @0x80146994 (src/shared) */


DEFINE_func_801469C8()  /* dedup: shared engine-core @0x801469c8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80146A6C);

DEFINE_func_80146AB4()  /* dedup: shared engine-core @0x80146ab4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80146AFC);

DEFINE_func_80146B9C()  /* dedup: shared engine-core @0x80146b9c (src/shared) */


DEFINE_func_80146C3C()  /* dedup: shared engine-core @0x80146c3c (src/shared) */


DEFINE_func_80146C98()  /* dedup: shared engine-core @0x80146c98 (src/shared) */


DEFINE_func_80146CA0()  /* dedup: shared engine-core @0x80146ca0 (src/shared) */


DEFINE_func_80146CB4()  /* dedup: shared engine-core @0x80146cb4 (src/shared) */


DEFINE_func_80146CC8()  /* dedup: shared engine-core @0x80146cc8 (src/shared) */


DEFINE_func_80146D30()  /* dedup: shared engine-core @0x80146d30 (src/shared) */


DEFINE_func_80146D80()  /* dedup: shared engine-core @0x80146d80 (src/shared) */


DEFINE_func_80146D90()  /* dedup: shared engine-core @0x80146d90 (src/shared) */


DEFINE_func_80146DB8()  /* dedup: shared engine-core @0x80146db8 (src/shared) */


DEFINE_func_80146DE8()  /* dedup: shared engine-core @0x80146de8 (src/shared) */


DEFINE_func_80146DF8()  /* dedup: shared engine-core @0x80146df8 (src/shared) */


DEFINE_func_80146E90()  /* dedup: shared engine-core @0x80146e90 (src/shared) */


DEFINE_func_80146E98()  /* dedup: shared engine-core @0x80146e98 (src/shared) */


DEFINE_func_80146EC0()  /* dedup: shared engine-core @0x80146ec0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80146F58);

DEFINE_func_80146FC4()  /* dedup: shared engine-core @0x80146fc4 (src/shared) */


DEFINE_func_8014704C()  /* dedup: shared engine-core @0x8014704c (src/shared) */


DEFINE_func_80147054()  /* dedup: shared engine-core @0x80147054 (src/shared) */


DEFINE_func_80147060()  /* dedup: shared engine-core @0x80147060 (src/shared) */


DEFINE_func_8014706C()  /* dedup: shared engine-core @0x8014706c (src/shared) */


DEFINE_func_80147078()  /* dedup: shared engine-core @0x80147078 (src/shared) */


DEFINE_func_80147084()  /* dedup: shared engine-core @0x80147084 (src/shared) */


DEFINE_func_8014708C()  /* dedup: shared engine-core @0x8014708c (src/shared) */


DEFINE_func_80147098()  /* dedup: shared engine-core @0x80147098 (src/shared) */


DEFINE_func_801470A0()  /* dedup: shared engine-core @0x801470a0 (src/shared) */


DEFINE_func_801470AC()  /* dedup: shared engine-core @0x801470ac (src/shared) */


DEFINE_func_801470B4()  /* dedup: shared engine-core @0x801470b4 (src/shared) */


DEFINE_func_801470C0()  /* dedup: shared engine-core @0x801470c0 (src/shared) */


DEFINE_func_80147118()  /* dedup: shared engine-core @0x80147118 (src/shared) */


DEFINE_func_80147264()  /* dedup: shared engine-core @0x80147264 (src/shared) */


DEFINE_func_80147290()  /* dedup: shared engine-core @0x80147290 (src/shared) */


DEFINE_func_801472B4()  /* dedup: shared engine-core @0x801472b4 (src/shared) */


DEFINE_func_801472C8()  /* dedup: shared engine-core @0x801472c8 (src/shared) */


DEFINE_func_801472DC()  /* dedup: shared engine-core @0x801472dc (src/shared) */


DEFINE_func_801472F0()  /* dedup: shared engine-core @0x801472f0 (src/shared) */


DEFINE_func_80147300()  /* dedup: shared engine-core @0x80147300 (src/shared) */


DEFINE_func_80147324()  /* dedup: shared engine-core @0x80147324 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80147364);

DEFINE_func_801473DC()  /* dedup: shared engine-core @0x801473dc (src/shared) */


DEFINE_func_801473EC()  /* dedup: shared engine-core @0x801473ec (src/shared) */


DEFINE_func_80147460()  /* dedup: shared engine-core @0x80147460 (src/shared) */


DEFINE_func_80147478()  /* dedup: shared engine-core @0x80147478 (src/shared) */


DEFINE_func_801474D8()  /* dedup: shared engine-core @0x801474d8 (src/shared) */


DEFINE_func_801474EC()  /* dedup: shared engine-core @0x801474ec (src/shared) */


DEFINE_func_80147514()  /* dedup: shared engine-core @0x80147514 (src/shared) */


DEFINE_func_80147628()  /* dedup: shared engine-core @0x80147628 (src/shared) */


DEFINE_func_80147718()  /* dedup: shared engine-core @0x80147718 (src/shared) */


DEFINE_func_80147788()  /* dedup: shared engine-core @0x80147788 (src/shared) */


DEFINE_func_801477A8()  /* dedup: shared engine-core @0x801477a8 (src/shared) */


DEFINE_func_801477C8()  /* dedup: shared engine-core @0x801477c8 (src/shared) */


DEFINE_func_801477E8()  /* dedup: shared engine-core @0x801477e8 (src/shared) */


DEFINE_func_80147814()  /* dedup: shared engine-core @0x80147814 (src/shared) */


DEFINE_func_80147860()  /* dedup: shared engine-core @0x80147860 (src/shared) */


DEFINE_func_801478B8()  /* dedup: shared engine-core @0x801478b8 (src/shared) */


DEFINE_func_80147928()  /* dedup: shared engine-core @0x80147928 (src/shared) */


DEFINE_func_80147948()  /* dedup: shared engine-core @0x80147948 (src/shared) */


DEFINE_func_8014799C()  /* dedup: shared engine-core @0x8014799c (src/shared) */


DEFINE_func_801479BC()  /* dedup: shared engine-core @0x801479bc (src/shared) */


DEFINE_func_80147A10()  /* dedup: shared engine-core @0x80147a10 (src/shared) */


DEFINE_func_80147A30()  /* dedup: shared engine-core @0x80147a30 (src/shared) */


DEFINE_func_80147A84()  /* dedup: shared engine-core @0x80147a84 (src/shared) */


DEFINE_func_80147AAC()  /* dedup: shared engine-core @0x80147aac (src/shared) */


DEFINE_func_80147AD4()  /* dedup: shared engine-core @0x80147ad4 (src/shared) */


DEFINE_func_80147B18()  /* dedup: shared engine-core @0x80147b18 (src/shared) */


DEFINE_func_80147B5C()  /* dedup: shared engine-core @0x80147b5c (src/shared) */


DEFINE_func_80147C30()  /* dedup: shared engine-core @0x80147c30 (src/shared) */


DEFINE_func_80147CC8()  /* dedup: shared engine-core @0x80147cc8 (src/shared) */


DEFINE_func_80147D38()  /* dedup: shared engine-core @0x80147d38 (src/shared) */


DEFINE_func_80147DC0()  /* dedup: shared engine-core @0x80147dc0 (src/shared) */


DEFINE_func_80147E44()  /* dedup: shared engine-core @0x80147e44 (src/shared) */


DEFINE_func_80147F50()  /* dedup: shared engine-core @0x80147f50 (src/shared) */


DEFINE_func_80147F78()  /* dedup: shared engine-core @0x80147f78 (src/shared) */


DEFINE_func_80148038()  /* dedup: shared engine-core @0x80148038 (src/shared) */


DEFINE_func_80148094()  /* dedup: shared engine-core @0x80148094 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801483E8);

DEFINE_func_801484B0()  /* dedup: shared engine-core @0x801484b0 (src/shared) */


DEFINE_func_801484E8()  /* dedup: shared engine-core @0x801484e8 (src/shared) */


DEFINE_func_80148534()  /* dedup: shared engine-core @0x80148534 (src/shared) */


DEFINE_func_8014856C()  /* dedup: shared engine-core @0x8014856c (src/shared) */


DEFINE_func_801485B8()  /* dedup: shared engine-core @0x801485b8 (src/shared) */


DEFINE_func_80148634()  /* dedup: shared engine-core @0x80148634 (src/shared) */


DEFINE_func_80148648()  /* dedup: shared engine-core @0x80148648 (src/shared) */


DEFINE_func_801487F4()  /* dedup: shared engine-core @0x801487f4 (src/shared) */


DEFINE_func_80148800()  /* dedup: shared engine-core @0x80148800 (src/shared) */


DEFINE_func_8014880C()  /* dedup: shared engine-core @0x8014880c (src/shared) */


DEFINE_func_80148818()  /* dedup: shared engine-core @0x80148818 (src/shared) */


DEFINE_func_80148824()  /* dedup: shared engine-core @0x80148824 (src/shared) */


DEFINE_func_801488A8()  /* dedup: shared engine-core @0x801488a8 (src/shared) */


DEFINE_func_8014891C()  /* dedup: shared engine-core @0x8014891c (src/shared) */


DEFINE_func_80148980()  /* dedup: shared engine-core @0x80148980 (src/shared) */


DEFINE_func_801489E8()  /* dedup: shared engine-core @0x801489e8 (src/shared) */


DEFINE_func_80148A48()  /* dedup: shared engine-core @0x80148a48 (src/shared) */


DEFINE_func_80148AAC()  /* dedup: shared engine-core @0x80148aac (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (71 ins). switch binary-tree; s1 angle = pin-source-of-copy ($5 temp + retie); 2nd-block double-load + 0x80-clobber via $v1/$v0/$a0 pins + lazy hi-pin reusing dead c80 reg

extern s32 ratan2(s32 a0, s32 a1);

int func_80148AFC(void *a0) {

    extern s32 D_801151D4;
    extern ActorFn D_80183AB8[];
    s32 p = (s32)a0;
    s32 iVar5 = *(s32 *)(p + 0x20);
    register s32 tmp __asm__("$5") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                        *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 sVar3;
    u8 bVar1;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    sVar3 = tmp;
    bVar1 = *(u8 *)(p + 0xA9);

    switch (bVar1) {
    case 0x41:
        return D_80183AB8[*(u16 *)(p + 0xAA) >> 12](a0) & 0xFF;
    case 0x53:
    case 0x73:
        {
            register u32 bb __asm__("$3");
            register s32 c80 __asm__("$2") = 0x80;
            register s32 lo __asm__("$4");
            register s32 hi __asm__("$2");
            bb = *(u16 *)(p + 0xAE);
            lo = bb & 0xFF;
            if (lo != c80 || (hi = bb >> 8) != 0x80) {
                s32 sVar4;
                __asm__ __volatile__("" : : : "memory");
                sVar4 = ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8));
                *(u16 *)(iVar5 + 0x12) = (sVar3 + sVar4) & 0xFFF;
                return 1;
            }
            return 0;
        }
    }
}


DEFINE_func_80148C18()  /* dedup: shared engine-core @0x80148c18 (src/shared) */


DEFINE_func_80148C20()  /* dedup: shared engine-core @0x80148c20 (src/shared) */


DEFINE_func_80148C34()  /* dedup: shared engine-core @0x80148c34 (src/shared) */


DEFINE_func_80148C4C()  /* dedup: shared engine-core @0x80148c4c (src/shared) */


DEFINE_func_80148C64()  /* dedup: shared engine-core @0x80148c64 (src/shared) */


DEFINE_func_80148C7C()  /* dedup: shared engine-core @0x80148c7c (src/shared) */


DEFINE_func_80148C84()  /* dedup: shared engine-core @0x80148c84 (src/shared) */


DEFINE_func_80148C9C()  /* dedup: shared engine-core @0x80148c9c (src/shared) */


DEFINE_func_80148CB4()  /* dedup: shared engine-core @0x80148cb4 (src/shared) */


DEFINE_func_80148CCC()  /* dedup: shared engine-core @0x80148ccc (src/shared) */


DEFINE_func_80148CE4()  /* dedup: shared engine-core @0x80148ce4 (src/shared) */


DEFINE_func_80148CEC()  /* dedup: shared engine-core @0x80148cec (src/shared) */


DEFINE_func_80148CF4()  /* dedup: shared engine-core @0x80148cf4 (src/shared) */


DEFINE_func_80148D0C()  /* dedup: shared engine-core @0x80148d0c (src/shared) */


DEFINE_func_80148D24()  /* dedup: shared engine-core @0x80148d24 (src/shared) */


DEFINE_func_80148D3C()  /* dedup: shared engine-core @0x80148d3c (src/shared) */



// @class: schedule
// @stuck: none — MATCH (68 ins)
extern s32 ratan2(s32 a0, s32 a1);

s32 func_80148D44(void) {

    extern s32 D_801151D4;
    extern u8 D_80126C01;
    extern u16 D_80126C02;
    extern u16 D_80126C06;
    extern s32 D_80183AF8[];
    register s32 ang __asm__("$16");
    register s32 a __asm__("$4");
    s32 p;
    s32 res;
    s32 d;

    p = D_801151D4;
    a = (ratan2(*(s32 *)(p + 0x44) - *(s32 *)(p + 0x50),
                  *(s32 *)(p + 0x48) - *(s32 *)(p + 0x3c)) - 0x400) & 0xFFF;
    d = (s32)D_80126C01;
    __asm__ __volatile__("" : : "r"(a));
    ang = a;
    if (d == 0x53) {
        goto final;
    }
    if (d < 0x54) {
        if (d == 0x41) {
            goto call;
        }
        return 0x41;
    }
    if (d != 0x73) {
        return 0x73;
    }
    goto final;
call:
    return (s32)(s16)((s16 (*)())(D_80183AF8[D_80126C02 >> 0xc]))();
final:
    {
        u32 e = D_80126C06;
        if (((e & 0xff) == 0x80) && ((e >> 8) == (e & 0xff))) {
            return -1;
        }
        __asm__ __volatile__("" : : : "memory");
        res = (ang + ratan2((D_80126C06 & 0xff) - 0x80, 0x80 - (D_80126C06 >> 8))) & 0xFFF;
    }
    return res;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80148E54);

DEFINE_func_80148F60()  /* dedup: shared engine-core @0x80148f60 (src/shared) */


DEFINE_func_80148F68()  /* dedup: shared engine-core @0x80148f68 (src/shared) */


DEFINE_func_80148F74()  /* dedup: shared engine-core @0x80148f74 (src/shared) */


DEFINE_func_80148F80()  /* dedup: shared engine-core @0x80148f80 (src/shared) */


DEFINE_func_80148F8C()  /* dedup: shared engine-core @0x80148f8c (src/shared) */


DEFINE_func_80148F98()  /* dedup: shared engine-core @0x80148f98 (src/shared) */


DEFINE_func_80148FA0()  /* dedup: shared engine-core @0x80148fa0 (src/shared) */


DEFINE_func_80148FAC()  /* dedup: shared engine-core @0x80148fac (src/shared) */


DEFINE_func_80148FB8()  /* dedup: shared engine-core @0x80148fb8 (src/shared) */


DEFINE_func_80148FC4()  /* dedup: shared engine-core @0x80148fc4 (src/shared) */


DEFINE_func_80148FD0()  /* dedup: shared engine-core @0x80148fd0 (src/shared) */


DEFINE_func_80148FD8()  /* dedup: shared engine-core @0x80148fd8 (src/shared) */


DEFINE_func_80148FE0()  /* dedup: shared engine-core @0x80148fe0 (src/shared) */


DEFINE_func_80148FEC()  /* dedup: shared engine-core @0x80148fec (src/shared) */


DEFINE_func_80148FF8()  /* dedup: shared engine-core @0x80148ff8 (src/shared) */


DEFINE_func_80149004()  /* dedup: shared engine-core @0x80149004 (src/shared) */


DEFINE_func_8014900C()  /* dedup: shared engine-core @0x8014900c (src/shared) */


DEFINE_func_80149020()  /* dedup: shared engine-core @0x80149020 (src/shared) */


DEFINE_func_80149034()  /* dedup: shared engine-core @0x80149034 (src/shared) */


DEFINE_func_80149048()  /* dedup: shared engine-core @0x80149048 (src/shared) */


DEFINE_func_8014905C()  /* dedup: shared engine-core @0x8014905c (src/shared) */


DEFINE_func_80149078()  /* dedup: shared engine-core @0x80149078 (src/shared) */


DEFINE_func_801490E0()  /* dedup: shared engine-core @0x801490e0 (src/shared) */


DEFINE_func_801490E8()  /* dedup: shared engine-core @0x801490e8 (src/shared) */


DEFINE_func_801490F0()  /* dedup: shared engine-core @0x801490f0 (src/shared) */


DEFINE_func_801490F8()  /* dedup: shared engine-core @0x801490f8 (src/shared) */


DEFINE_func_80149184()  /* dedup: shared engine-core @0x80149184 (src/shared) */


DEFINE_func_801491C4()  /* dedup: shared engine-core @0x801491c4 (src/shared) */


DEFINE_func_80149204()  /* dedup: shared engine-core @0x80149204 (src/shared) */


DEFINE_func_80149210()  /* dedup: shared engine-core @0x80149210 (src/shared) */


DEFINE_func_80149228()  /* dedup: shared engine-core @0x80149228 (src/shared) */


DEFINE_func_80149284()  /* dedup: shared engine-core @0x80149284 (src/shared) */


DEFINE_func_80149290()  /* dedup: shared engine-core @0x80149290 (src/shared) */


extern void func_8012F14C(s32);
void func_80149350(s32 arg0) {
    func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80149374);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801493D0);

extern void func_8012F038(s32);
void func_8014942C(s32 arg0) {
    func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80149450);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801494CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80149544);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80149584);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801495C4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014964C);

DEFINE_func_801496D4()  /* dedup: shared engine-core @0x801496d4 (src/shared) */


DEFINE_func_80149704()  /* dedup: shared engine-core @0x80149704 (src/shared) */


DEFINE_func_80149724()  /* dedup: shared engine-core @0x80149724 (src/shared) */


DEFINE_func_80149744()  /* dedup: shared engine-core @0x80149744 (src/shared) */


DEFINE_func_80149788()  /* dedup: shared engine-core @0x80149788 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801497A8);

DEFINE_func_80149864()  /* dedup: shared engine-core @0x80149864 (src/shared) */


DEFINE_func_80149884()  /* dedup: shared engine-core @0x80149884 (src/shared) */


DEFINE_func_801498C0()  /* dedup: shared engine-core @0x801498c0 (src/shared) */


DEFINE_func_801498E0()  /* dedup: shared engine-core @0x801498e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80149954);

DEFINE_func_80149A64()  /* dedup: shared engine-core @0x80149a64 (src/shared) */


DEFINE_func_80149AA8()  /* dedup: shared engine-core @0x80149aa8 (src/shared) */


DEFINE_func_80149AD4()  /* dedup: shared engine-core @0x80149ad4 (src/shared) */


DEFINE_func_80149B14()  /* dedup: shared engine-core @0x80149b14 (src/shared) */


DEFINE_func_80149B54()  /* dedup: shared engine-core @0x80149b54 (src/shared) */


DEFINE_func_80149BAC()  /* dedup: shared engine-core @0x80149bac (src/shared) */


DEFINE_func_80149BEC()  /* dedup: shared engine-core @0x80149bec (src/shared) */


DEFINE_func_80149C08()  /* dedup: shared engine-core @0x80149c08 (src/shared) */


DEFINE_func_80149C94()  /* dedup: shared engine-core @0x80149c94 (src/shared) */


DEFINE_func_80149CB4()  /* dedup: shared engine-core @0x80149cb4 (src/shared) */


DEFINE_func_80149CD4()  /* dedup: shared engine-core @0x80149cd4 (src/shared) */


DEFINE_func_80149D10()  /* dedup: shared engine-core @0x80149d10 (src/shared) */


DEFINE_func_80149D9C()  /* dedup: shared engine-core @0x80149d9c (src/shared) */


DEFINE_func_80149DD8()  /* dedup: shared engine-core @0x80149dd8 (src/shared) */


DEFINE_func_80149E94()  /* dedup: shared engine-core @0x80149e94 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80149F2C);

void func_80149FA8(void) {
}


// @class: regalloc-order
// @stuck: none — MATCH (38 ins)
extern s16 currentLocationId;

s32 func_80149FB0(s32 a0) {

    extern s32 D_80183B78[];
    extern u8 D_80078E78[];
    s32 *p = &D_80183B78[0];
    register s32 v __asm__("$3") = *p;
    u8 *q = &D_80078E78[0];
    s32 loc;

    if (v != 0) {
        loc = currentLocationId;
        p = p + 1;
        do {
            if (loc == v) {
                goto ret0;
            }
            v = *p;
            p = p + 1;
        } while (v != 0);
    }

    if ((*(u32 *)(a0 + 0x44) & 0x400) != 0) {
        return 0;
    }
    if (*(s16 *)(a0 + 0x1C8) != 0) {
        return 0;
    }
    if ((*(u16 *)(a0 + 0xAC) & 0x100) == 0) {
    ret0:
        return 0;
    }
    v = q[0x48];
    q[0x48] = v ^ 0x80;
    return 1;
}


extern u8 func_8014BEF8(void);
extern void func_8012F14C(s32);
extern s32 func_80135260(s32, s32, s32, s32);
extern void func_8014A1B0(s32 a0, s32 a1);
s32 func_8014A048(s32 param_1) {

    extern u8 D_801202A0[];
    Loc L;
    s32 s0;
    s32 s2;
    u32 s3;
    if ((*(u32 *)(param_1 + 0x44) & 0x400) != 0) {
        return 0;
    }
    if ((*(u16 *)(param_1 + 0xAC) & 0x80) == 0) {
        if ((*(u16 *)(param_1 + 0xAC) & 0x10) == 0) {
            return 0;
        }
        if (((s32 (*)(s32))func_8014BEF8)(param_1) == 0) {
            goto ret0;
        }
    }
    L.a30 = *(s16 *)(param_1 + 6);
    L.a2e = *(s16 *)(param_1 + 0xA);
    L.a2c = *(s16 *)(param_1 + 0xE);
    L.a1e = -0x10;
    L.a20 = 0;
    L.a1c = -0x20;
    ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&L.a20, (s32)L.buf);
    s3 = 0;
    s2 = 0;
    while (1) {
        s0 = (s32)D_801202A0 + s2;
        __asm__ __volatile__("" : "=r"(s0) : "0"(s0));
        if ((*(u16 *)s0 != 0) &&
            (*(s32 *)(s0 + 0x58) != 0) &&
            (*(s16 *)(s0 + 0xAA) == 0) &&
            (*(s32 *)(param_1 + 0x184) != s0) &&
            ((*(u16 *)(s0 + 0x5C) & 0x200) != 0) &&
            (((s32 (*)(s32, s32, s32, s32))func_80135260)(*(s32 *)(s0 + 0x20), *(s32 *)(s0 + 0x58), (s32)&L.a30, (s32)L.buf) != 0)) {
            break;
        }
        s3++;
        s2 += 0x10C;
        if (s3 >= 0x60) {
            return 0;
        }
    }
    *(s32 *)(param_1 + 0x178) = s0;
    func_8014A1B0(param_1, s0);
    return 1;
ret0:
    return 0;
}


DEFINE_func_8014A1B0()  /* dedup: shared engine-core @0x8014a1b0 (src/shared) */


DEFINE_func_8014A218()  /* dedup: shared engine-core @0x8014a218 (src/shared) */


DEFINE_func_8014A238()  /* dedup: shared engine-core @0x8014a238 (src/shared) */


DEFINE_func_8014A2E4()  /* dedup: shared engine-core @0x8014a2e4 (src/shared) */


DEFINE_func_8014A380()  /* dedup: shared engine-core @0x8014a380 (src/shared) */


DEFINE_func_8014A3E0()  /* dedup: shared engine-core @0x8014a3e0 (src/shared) */


DEFINE_func_8014A454()  /* dedup: shared engine-core @0x8014a454 (src/shared) */


DEFINE_func_8014A4B4()  /* dedup: shared engine-core @0x8014a4b4 (src/shared) */


DEFINE_func_8014A4FC()  /* dedup: shared engine-core @0x8014a4fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014A51C);

DEFINE_func_8014A59C()  /* dedup: shared engine-core @0x8014a59c (src/shared) */


DEFINE_func_8014A638()  /* dedup: shared engine-core @0x8014a638 (src/shared) */


DEFINE_func_8014A674()  /* dedup: shared engine-core @0x8014a674 (src/shared) */


DEFINE_func_8014A680()  /* dedup: shared engine-core @0x8014a680 (src/shared) */


DEFINE_func_8014A69C()  /* dedup: shared engine-core @0x8014a69c (src/shared) */


DEFINE_func_8014A6A8()  /* dedup: shared engine-core @0x8014a6a8 (src/shared) */


DEFINE_func_8014A6C4()  /* dedup: shared engine-core @0x8014a6c4 (src/shared) */


DEFINE_func_8014A71C()  /* dedup: shared engine-core @0x8014a71c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014A738);

DEFINE_func_8014A830()  /* dedup: shared engine-core @0x8014a830 (src/shared) */


DEFINE_func_8014A850()  /* dedup: shared engine-core @0x8014a850 (src/shared) */


DEFINE_func_8014AA04()  /* dedup: shared engine-core @0x8014aa04 (src/shared) */


DEFINE_func_8014AA28()  /* dedup: shared engine-core @0x8014aa28 (src/shared) */


DEFINE_func_8014AB5C()  /* dedup: shared engine-core @0x8014ab5c (src/shared) */


DEFINE_func_8014AB7C()  /* dedup: shared engine-core @0x8014ab7c (src/shared) */


DEFINE_func_8014ABF0()  /* dedup: shared engine-core @0x8014abf0 (src/shared) */


DEFINE_func_8014AC10()  /* dedup: shared engine-core @0x8014ac10 (src/shared) */


DEFINE_func_8014ACC0()  /* dedup: shared engine-core @0x8014acc0 (src/shared) */


DEFINE_func_8014ACE8()  /* dedup: shared engine-core @0x8014ace8 (src/shared) */


DEFINE_func_8014AD30()  /* dedup: shared engine-core @0x8014ad30 (src/shared) */


DEFINE_func_8014AD7C()  /* dedup: shared engine-core @0x8014ad7c (src/shared) */


DEFINE_func_8014ADA8()  /* dedup: shared engine-core @0x8014ada8 (src/shared) */


DEFINE_func_8014ADE0()  /* dedup: shared engine-core @0x8014ADE0 (src/shared) */

DEFINE_func_8014B00C()  /* dedup: shared engine-core @0x8014b00c (src/shared) */


DEFINE_func_8014B034()  /* dedup: shared engine-core @0x8014b034 (src/shared) */


DEFINE_func_8014B084()  /* dedup: shared engine-core @0x8014b084 (src/shared) */


DEFINE_func_8014B12C()  /* dedup: shared engine-core @0x8014b12c (src/shared) */


DEFINE_func_8014B154()  /* dedup: shared engine-core @0x8014b154 (src/shared) */


DEFINE_func_8014B160()  /* dedup: shared engine-core @0x8014b160 (src/shared) */


DEFINE_func_8014B190()  /* dedup: shared engine-core @0x8014b190 (src/shared) */


DEFINE_func_8014B2A8()  /* dedup: shared engine-core @0x8014b2a8 (src/shared) */


DEFINE_func_8014B2D0()  /* dedup: shared engine-core @0x8014b2d0 (src/shared) */


DEFINE_func_8014B2F8()  /* dedup: shared engine-core @0x8014b2f8 (src/shared) */


DEFINE_func_8014B310()  /* dedup: shared engine-core @0x8014b310 (src/shared) */


DEFINE_func_8014B33C()  /* dedup: shared engine-core @0x8014b33c (src/shared) */


DEFINE_func_8014B350()  /* dedup: shared engine-core @0x8014b350 (src/shared) */


DEFINE_func_8014B4C4()  /* dedup: shared engine-core @0x8014b4c4 (src/shared) */


DEFINE_func_8014B4D4()  /* dedup: shared engine-core @0x8014b4d4 (src/shared) */


DEFINE_func_8014B504()  /* dedup: shared engine-core @0x8014b504 (src/shared) */


DEFINE_func_8014B598()  /* dedup: shared engine-core @0x8014b598 (src/shared) */


DEFINE_func_8014B5B0()  /* dedup: shared engine-core @0x8014b5b0 (src/shared) */


DEFINE_func_8014B5B8()  /* dedup: shared engine-core @0x8014b5b8 (src/shared) */


DEFINE_func_8014B5C4()  /* dedup: shared engine-core @0x8014b5c4 (src/shared) */


DEFINE_func_8014B5D0()  /* dedup: shared engine-core @0x8014b5d0 (src/shared) */


DEFINE_func_8014B5D8()  /* dedup: shared engine-core @0x8014b5d8 (src/shared) */


DEFINE_func_8014B6F0()  /* dedup: shared engine-core @0x8014b6f0 (src/shared) */


DEFINE_func_8014B768()  /* dedup: shared engine-core @0x8014b768 (src/shared) */


DEFINE_func_8014B7A4()  /* dedup: shared engine-core @0x8014b7a4 (src/shared) */


DEFINE_func_8014B944()  /* dedup: shared engine-core @0x8014b944 (src/shared) */


DEFINE_func_8014BB0C()  /* dedup: shared engine-core @0x8014bb0c (src/shared) */


DEFINE_func_8014BB24()  /* dedup: shared engine-core @0x8014bb24 (src/shared) */


DEFINE_func_8014BC0C()  /* dedup: shared engine-core @0x8014bc0c (src/shared) */


DEFINE_func_8014BC44()  /* dedup: shared engine-core @0x8014bc44 (src/shared) */


DEFINE_func_8014BC80()  /* dedup: shared engine-core @0x8014bc80 (src/shared) */


DEFINE_func_8014BCC0()  /* dedup: shared engine-core @0x8014bcc0 (src/shared) */


DEFINE_func_8014BCEC()  /* dedup: shared engine-core @0x8014bcec (src/shared) */


DEFINE_func_8014BD24()  /* dedup: shared engine-core @0x8014bd24 (src/shared) */


DEFINE_func_8014BD60()  /* dedup: shared engine-core @0x8014bd60 (src/shared) */


DEFINE_func_8014BD98()  /* dedup: shared engine-core @0x8014bd98 (src/shared) */


DEFINE_func_8014BDC8()  /* dedup: shared engine-core @0x8014bdc8 (src/shared) */


void func_8014BDE0(void) {
}

DEFINE_func_8014BDE8()  /* dedup: shared engine-core @0x8014bde8 (src/shared) */


DEFINE_func_8014BE78()  /* dedup: shared engine-core @0x8014be78 (src/shared) */


DEFINE_func_8014BE9C()  /* dedup: shared engine-core @0x8014be9c (src/shared) */


DEFINE_func_8014BEC0()  /* dedup: shared engine-core @0x8014bec0 (src/shared) */


DEFINE_func_8014BEF8()  /* dedup: shared engine-core @0x8014bef8 (src/shared) */


DEFINE_func_8014BF18()  /* dedup: shared engine-core @0x8014bf18 (src/shared) */


DEFINE_func_8014BF48()  /* dedup: shared engine-core @0x8014bf48 (src/shared) */


DEFINE_func_8014BF6C()  /* dedup: shared engine-core @0x8014bf6c (src/shared) */


DEFINE_func_8014BF8C()  /* dedup: shared engine-core @0x8014bf8c (src/shared) */


DEFINE_func_8014BFB0()  /* dedup: shared engine-core @0x8014bfb0 (src/shared) */


DEFINE_func_8014BFD4()  /* dedup: shared engine-core @0x8014bfd4 (src/shared) */


DEFINE_func_8014BFF4()  /* dedup: shared engine-core @0x8014bff4 (src/shared) */


DEFINE_func_8014C010()  /* dedup: shared engine-core @0x8014c010 (src/shared) */


DEFINE_func_8014C050()  /* dedup: shared engine-core @0x8014c050 (src/shared) */


DEFINE_func_8014C088()  /* dedup: shared engine-core @0x8014c088 (src/shared) */


DEFINE_func_8014C0C8()  /* dedup: shared engine-core @0x8014c0c8 (src/shared) */


DEFINE_func_8014C118()  /* dedup: shared engine-core @0x8014c118 (src/shared) */


DEFINE_func_8014C168()  /* dedup: shared engine-core @0x8014c168 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014C1A0);

DEFINE_func_8014C1C8()  /* dedup: shared engine-core @0x8014c1c8 (src/shared) */


DEFINE_func_8014C278()  /* dedup: shared engine-core @0x8014c278 (src/shared) */


DEFINE_func_8014C2B0()  /* dedup: shared engine-core @0x8014c2b0 (src/shared) */


DEFINE_func_8014C308()  /* dedup: shared engine-core @0x8014c308 (src/shared) */


DEFINE_func_8014C3A4()  /* dedup: shared engine-core @0x8014c3a4 (src/shared) */


DEFINE_func_8014C3D0()  /* dedup: shared engine-core @0x8014c3d0 (src/shared) */


DEFINE_func_8014C43C()  /* dedup: shared engine-core @0x8014c43c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014C4AC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014C568);

DEFINE_func_8014C59C()  /* dedup: shared engine-core @0x8014c59c (src/shared) */



extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {

    extern u8 D_80183C08;
    return func_8014C5FC(a0, a1, &D_80183C08);
}


DEFINE_func_8014C5FC()  /* dedup: shared engine-core @0x8014c5fc (src/shared) */


DEFINE_func_8014C6AC()  /* dedup: shared engine-core @0x8014c6ac (src/shared) */


DEFINE_func_8014C6C0()  /* dedup: shared engine-core @0x8014c6c0 (src/shared) */


DEFINE_func_8014C6D0()  /* dedup: shared engine-core @0x8014c6d0 (src/shared) */


DEFINE_func_8014C6E0()  /* dedup: shared engine-core @0x8014c6e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014C6F4);

DEFINE_func_8014C860()  /* dedup: shared engine-core @0x8014c860 (src/shared) */


DEFINE_func_8014C88C()  /* dedup: shared engine-core @0x8014c88c (src/shared) */


DEFINE_func_8014C8C8()  /* dedup: shared engine-core @0x8014c8c8 (src/shared) */


DEFINE_func_8014C8F0()  /* dedup: shared engine-core @0x8014c8f0 (src/shared) */


DEFINE_func_8014C918()  /* dedup: shared engine-core @0x8014c918 (src/shared) */


DEFINE_func_8014C968()  /* dedup: shared engine-core @0x8014c968 (src/shared) */


DEFINE_func_8014C978()  /* dedup: shared engine-core @0x8014c978 (src/shared) */


DEFINE_func_8014C98C()  /* dedup: shared engine-core @0x8014c98c (src/shared) */


DEFINE_func_8014C99C()  /* dedup: shared engine-core @0x8014c99c (src/shared) */


DEFINE_func_8014CA00()  /* dedup: shared engine-core @0x8014ca00 (src/shared) */


DEFINE_func_8014CA14()  /* dedup: shared engine-core @0x8014ca14 (src/shared) */


DEFINE_func_8014CA70()  /* dedup: shared engine-core @0x8014ca70 (src/shared) */


DEFINE_func_8014CA88()  /* dedup: shared engine-core @0x8014ca88 (src/shared) */


DEFINE_func_8014CAE4()  /* dedup: shared engine-core @0x8014cae4 (src/shared) */


DEFINE_func_8014CAFC()  /* dedup: shared engine-core @0x8014cafc (src/shared) */


DEFINE_func_8014CB0C()  /* dedup: shared engine-core @0x8014cb0c (src/shared) */


DEFINE_func_8014CB1C()  /* dedup: shared engine-core @0x8014cb1c (src/shared) */


DEFINE_func_8014CB2C()  /* dedup: shared engine-core @0x8014cb2c (src/shared) */


DEFINE_func_8014CB58()  /* dedup: shared engine-core @0x8014cb58 (src/shared) */


DEFINE_func_8014CB68()  /* dedup: shared engine-core @0x8014cb68 (src/shared) */


DEFINE_func_8014CB7C()  /* dedup: shared engine-core @0x8014cb7c (src/shared) */


DEFINE_func_8014CB8C()  /* dedup: shared engine-core @0x8014cb8c (src/shared) */


DEFINE_func_8014CB9C()  /* dedup: shared engine-core @0x8014cb9c (src/shared) */


DEFINE_func_8014CBD8()  /* dedup: shared engine-core @0x8014cbd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014CBE8);

DEFINE_func_8014CBF8()  /* dedup: shared engine-core @0x8014cbf8 (src/shared) */


DEFINE_func_8014CC28()  /* dedup: shared engine-core @0x8014cc28 (src/shared) */



extern void func_8014CD0C(u8 *a0);

void func_8014CCB4(void)
{

    extern int D_801A6B50;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014CD0C\n"
        "lui   $at, %%hi(D_801A6B50)\n"
        "sw    $v0, %%lo(D_801A6B50)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B50)\n"
        "lw    $v0, %%lo(D_801A6B50)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014CD0C()  /* dedup: shared engine-core @0x8014cd0c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014CD80);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014CF04);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D04C);

DEFINE_func_8014D0A4()  /* dedup: shared engine-core @0x8014d0a4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D12C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D2A0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D3E0);

DEFINE_func_8014D438()  /* dedup: shared engine-core @0x8014d438 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D4C0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D610);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D738);

DEFINE_func_8014D790()  /* dedup: shared engine-core @0x8014d790 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014D820);

DEFINE_func_8014DCE0()  /* dedup: shared engine-core @0x8014dce0 (src/shared) */


DEFINE_func_8014DD8C()  /* dedup: shared engine-core @0x8014dd8c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014DF3C);

DEFINE_func_8014DF94()  /* dedup: shared engine-core @0x8014df94 (src/shared) */


DEFINE_func_8014E048()  /* dedup: shared engine-core @0x8014e048 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014E284);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014E434);

DEFINE_func_8014E48C()  /* dedup: shared engine-core @0x8014e48c (src/shared) */


DEFINE_func_8014E514()  /* dedup: shared engine-core @0x8014e514 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014E5B4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014E6A0);

DEFINE_func_8014E6F8()  /* dedup: shared engine-core @0x8014e6f8 (src/shared) */


DEFINE_func_8014E790()  /* dedup: shared engine-core @0x8014e790 (src/shared) */


DEFINE_func_8014E83C()  /* dedup: shared engine-core @0x8014e83c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014E934);

DEFINE_func_8014E98C()  /* dedup: shared engine-core @0x8014e98c (src/shared) */


DEFINE_func_8014EA4C()  /* dedup: shared engine-core @0x8014ea4c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014ED28);

DEFINE_func_8014ED80()  /* dedup: shared engine-core @0x8014ed80 (src/shared) */


DEFINE_func_8014EE14()  /* dedup: shared engine-core @0x8014ee14 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014F1F4);

DEFINE_func_8014F24C()  /* dedup: shared engine-core @0x8014f24c (src/shared) */


DEFINE_func_8014F2E0()  /* dedup: shared engine-core @0x8014f2e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014F3E8);


extern void func_8014F4C0(u8 *a0);

void func_8014F468(void)
{

    extern int D_801A6B54;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "lui   $v1, 0x1f80\n"
        "ori   $v1, $v1, 0x03fc\n"
        "sw    $ra, 16($sp)\n"
        "addu  $t0, $v1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014F4C0\n"
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B54)\n"
        "lw    $v0, %%lo(D_801A6B54)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014F4C0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014F6F4);

DEFINE_func_8014F74C()  /* dedup: shared engine-core @0x8014f74c (src/shared) */



// @class: other
// @stuck: none — MATCH (full inline-asm $sp-switch trampoline w/ 0x40000 guard, jal func_8014FA70, stash D_801A6B54; maspsx auto-fills jal delay slot)

extern s32 func_8014FA70(s32 a0);

void func_8014FA04(s32 a0)
{

    extern s32 D_801A6B54;
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $ra, 16($sp)\n"
        "lw    $v0, 68($a0)\n"
        "lui   $v1, 0x4\n"
        "and   $v0, $v0, $v1\n"
        "bnez  $v0, 1f\n"
        "addu  $v0, $zero, $zero\n"
        "lui   $a1, 0x1f80\n"
        "ori   $a1, $a1, 0x03fc\n"
        "addu  $t0, $a1, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FA70\n"
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801A6B54)\n"
        "lw    $v0, %%lo(D_801A6B54)($v0)\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


DEFINE_func_8014FA70()  /* dedup: shared engine-core @0x8014fa70 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014FBC0);

DEFINE_func_8014FC18()  /* dedup: shared engine-core @0x8014fc18 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014FCFC);

DEFINE_func_8014FD54()  /* dedup: shared engine-core @0x8014fd54 (src/shared) */


DEFINE_func_8014FDF4()  /* dedup: shared engine-core @0x8014fdf4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014FE60);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8014FFDC);

DEFINE_func_80150150()  /* dedup: shared engine-core @0x80150150 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80150170);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801502EC);

DEFINE_func_80150460()  /* dedup: shared engine-core @0x80150460 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80150480);

DEFINE_func_801504D8()  /* dedup: shared engine-core @0x801504d8 (src/shared) */


DEFINE_func_80150528()  /* dedup: shared engine-core @0x80150528 (src/shared) */


DEFINE_func_801505FC()  /* dedup: shared engine-core @0x801505fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801506A4);

DEFINE_func_80150820()  /* dedup: shared engine-core @0x80150820 (src/shared) */


DEFINE_func_8015086C()  /* dedup: shared engine-core @0x8015086c (src/shared) */


DEFINE_func_801508B4()  /* dedup: shared engine-core @0x801508b4 (src/shared) */


DEFINE_func_801508F8()  /* dedup: shared engine-core @0x801508f8 (src/shared) */



extern s32 func_80021174(s32 a0, s32 a1);

s32 func_8015094C(s32 param_1) {

    extern S16 D_801A61BC;
    extern s32 D_80183C38;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern u8 D_80126948[];
    struct { s32 x, mid, y; s32 _pad[9]; } arg;   /* 0x30 @ 0x10 */
    S16 local;                                     /* 0x10 @ 0x40 */
    s32 pad1[4];                                    /* 0x10 @ 0x50 */
    register u8 *cam __asm__("$17") = D_80126948;
    s32 ret;

    local = D_801A61BC;
    arg.x = *(short *)(param_1 + 6);
    arg.mid = D_80126994;
    arg.y = *(short *)(param_1 + 0xe);
    ret = func_80021174(D_80183C38, (s32)&arg);
    if (ret == 0) {
        {
            short cur = *(short *)(param_1 + 6);
            s32 diff = D_80126990 - cur;
            s32 av = (diff < 0) ? -diff : diff;
            if (av >= 5) {
                *(short *)(param_1 + 6) = (diff >= 0) ? cur + 4 : cur - 4;
            }
        }
        {
            short cur = *(short *)(param_1 + 0xe);
            s32 diff = *(s32 *)(cam + 0x50) - cur;
            s32 av = (diff < 0) ? -diff : diff;
            if (av >= 5) {
                *(short *)(param_1 + 0xe) = (diff >= 0) ? cur + 4 : cur - 4;
            }
        }
        (void)&pad1;
        return 1;
    }
    return 0;
}



extern s32 func_8014FA70(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);

void func_80150A70(s32 a0)
{

    extern s32 D_801A6B54;
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -24\n"
        "sw    $s0, 16($sp)\n"
        "addu  $s0, $a0, $zero\n"
        "sw    $ra, 20($sp)\n"
        "lh    $v1, 6($s0)\n"
        "lh    $v0, 136($s0)\n"
        "nop\n"
        "bne   $v1, $v0, 1f\n"
        "nop\n"
        "lh    $v1, 10($s0)\n"
        "lh    $v0, 138($s0)\n"
        "nop\n"
        "bne   $v1, $v0, 1f\n"
        "nop\n"
        "lh    $v1, 14($s0)\n"
        "lh    $v0, 140($s0)\n"
        "nop\n"
        "beq   $v1, $v0, 3f\n"
        "nop\n"
    "1:\n"
        "lw    $v0, 68($s0)\n"
        "lui   $v1, 0x4\n"
        "and   $v0, $v0, $v1\n"
        "bnez  $v0, 2f\n"
        "addiu $a0, $s0, 4\n"
        "lui   $a2, 0x1f80\n"
        "ori   $a2, $a2, 0x03fc\n"
        "addu  $t0, $a2, $zero\n"
        "lw    $t1, 0($t0)\n"
        "nop\n"
        "sw    $sp, 0($t1)\n"
        "addiu $t1, $t1, -4\n"
        "addu  $sp, $t1, $zero\n"
        "jal   func_8014FA70\n"
        "addu  $a0, $s0, $zero\n"
        "lui   $at, %%hi(D_801A6B54)\n"
        "sw    $v0, %%lo(D_801A6B54)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "addiu $a0, $s0, 4\n"
    "2:\n"
        "jal   func_80015978\n"
        "addiu $a1, $s0, 136\n"
    "3:\n"
        "lw    $ra, 20($sp)\n"
        "lw    $s0, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        ".set\treorder\n"
        : : : "memory");
}



// @class: regalloc-order
// @stuck: none — MATCH (fn-ptr table; split idx-1 into a $v0-pinned temp to stop (idx-1)*4 strength-reducing into a -4 load offset AND land the subtract in $v0)


void func_80150B28(int param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_80183C3C[])(void);
    u32 idx;
    register u32 sub __asm__("$2");

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_80183C3C[sub]();
        }
    }
    *(u16 *)(param_1 + 0x16C) = 0;
}


void func_80150B9C(void) {
}

DEFINE_func_80150BA4()  /* dedup: shared engine-core @0x80150ba4 (src/shared) */


DEFINE_func_80150BC8()  /* dedup: shared engine-core @0x80150bc8 (src/shared) */


DEFINE_func_80150C48()  /* dedup: shared engine-core @0x80150c48 (src/shared) */


DEFINE_func_80150CA0()  /* dedup: shared engine-core @0x80150ca0 (src/shared) */


DEFINE_func_80150CC4()  /* dedup: shared engine-core @0x80150cc4 (src/shared) */


DEFINE_func_80150CE4()  /* dedup: shared engine-core @0x80150ce4 (src/shared) */


DEFINE_func_80150D04()  /* dedup: shared engine-core @0x80150d04 (src/shared) */


DEFINE_func_80150D24()  /* dedup: shared engine-core @0x80150d24 (src/shared) */


DEFINE_func_80150D44()  /* dedup: shared engine-core @0x80150d44 (src/shared) */


DEFINE_func_80150D64()  /* dedup: shared engine-core @0x80150d64 (src/shared) */


DEFINE_func_80150D84()  /* dedup: shared engine-core @0x80150d84 (src/shared) */


DEFINE_func_80150DA4()  /* dedup: shared engine-core @0x80150da4 (src/shared) */


DEFINE_func_80150DC4()  /* dedup: shared engine-core @0x80150dc4 (src/shared) */


DEFINE_func_80150DE4()  /* dedup: shared engine-core @0x80150de4 (src/shared) */


DEFINE_func_80150E04()  /* dedup: shared engine-core @0x80150e04 (src/shared) */


DEFINE_func_80150E24()  /* dedup: shared engine-core @0x80150e24 (src/shared) */


DEFINE_func_80150E44()  /* dedup: shared engine-core @0x80150e44 (src/shared) */


DEFINE_func_80150E64()  /* dedup: shared engine-core @0x80150e64 (src/shared) */


DEFINE_func_80150E84()  /* dedup: shared engine-core @0x80150e84 (src/shared) */


DEFINE_func_80150EA4()  /* dedup: shared engine-core @0x80150ea4 (src/shared) */


DEFINE_func_80150EC4()  /* dedup: shared engine-core @0x80150ec4 (src/shared) */


void func_80150F78(void) {
}

DEFINE_func_80150F80()  /* dedup: shared engine-core @0x80150f80 (src/shared) */


DEFINE_func_80150FB4()  /* dedup: shared engine-core @0x80150fb4 (src/shared) */


DEFINE_func_80150FD8()  /* dedup: shared engine-core @0x80150fd8 (src/shared) */


DEFINE_func_80151014()  /* dedup: shared engine-core @0x80151014 (src/shared) */


DEFINE_func_80151038()  /* dedup: shared engine-core @0x80151038 (src/shared) */


DEFINE_func_80151070()  /* dedup: shared engine-core @0x80151070 (src/shared) */


DEFINE_func_80151094()  /* dedup: shared engine-core @0x80151094 (src/shared) */


void func_801510B8(void) {
}

void func_801510C0(void) {
}

DEFINE_func_801510C8()  /* dedup: shared engine-core @0x801510c8 (src/shared) */


DEFINE_func_801510EC()  /* dedup: shared engine-core @0x801510ec (src/shared) */


DEFINE_func_80151110()  /* dedup: shared engine-core @0x80151110 (src/shared) */


void func_80151130(void) {
}

DEFINE_func_80151138()  /* dedup: shared engine-core @0x80151138 (src/shared) */


DEFINE_func_8015115C()  /* dedup: shared engine-core @0x8015115c (src/shared) */


DEFINE_func_80151164()  /* dedup: shared engine-core @0x80151164 (src/shared) */


DEFINE_func_80151184()  /* dedup: shared engine-core @0x80151184 (src/shared) */


DEFINE_func_801511A8()  /* dedup: shared engine-core @0x801511a8 (src/shared) */


DEFINE_func_801511C4()  /* dedup: shared engine-core @0x801511c4 (src/shared) */


DEFINE_func_801511E0()  /* dedup: shared engine-core @0x801511e0 (src/shared) */


DEFINE_func_80151204()  /* dedup: shared engine-core @0x80151204 (src/shared) */


DEFINE_func_80151238()  /* dedup: shared engine-core @0x80151238 (src/shared) */


DEFINE_func_8015126C()  /* dedup: shared engine-core @0x8015126c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80151664);

DEFINE_func_801516F0()  /* dedup: shared engine-core @0x801516f0 (src/shared) */


DEFINE_func_8015173C()  /* dedup: shared engine-core @0x8015173c (src/shared) */


DEFINE_func_80151780()  /* dedup: shared engine-core @0x80151780 (src/shared) */


void func_80151878(void) {
}

DEFINE_func_80151880()  /* dedup: shared engine-core @0x80151880 (src/shared) */


DEFINE_func_801518D8()  /* dedup: shared engine-core @0x801518d8 (src/shared) */


DEFINE_func_80151924()  /* dedup: shared engine-core @0x80151924 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80151944);

DEFINE_func_80151980()  /* dedup: shared engine-core @0x80151980 (src/shared) */


DEFINE_func_801519C8()  /* dedup: shared engine-core @0x801519c8 (src/shared) */


DEFINE_func_80151AE4()  /* dedup: shared engine-core @0x80151ae4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80151B98);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80151C54);



void func_80151D24(void *a0) {

    extern void (*D_80183CE0[])(void);
    D_80183CE0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80151D60()  /* dedup: shared engine-core @0x80151d60 (src/shared) */


DEFINE_func_80151DB0()  /* dedup: shared engine-core @0x80151db0 (src/shared) */


DEFINE_func_80151E78()  /* dedup: shared engine-core @0x80151e78 (src/shared) */


DEFINE_func_80151ECC()  /* dedup: shared engine-core @0x80151ecc (src/shared) */


DEFINE_func_80151F38()  /* dedup: shared engine-core @0x80151f38 (src/shared) */


DEFINE_func_80151FB4()  /* dedup: shared engine-core @0x80151fb4 (src/shared) */




void func_80152058(void *a0) {

    extern void (*D_80183D04[])(void);
    D_80183D04[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152094()  /* dedup: shared engine-core @0x80152094 (src/shared) */



extern void func_80019064(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_801472C8(struct S *a0);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);

void func_801520DC(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_80183CF4;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80183CF4);
    func_801477E8(arg0, 0x40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146A6C(0x10, arg0, M2C_FIELD(arg0, s16 *, 6), M2C_FIELD(arg0, s16 *, 0xA), (s32) M2C_FIELD(arg0, s16 *, 0xE), 0, 0);
    func_80147324(0x441);
    func_80146CA0(arg0);
}


DEFINE_func_80152194()  /* dedup: shared engine-core @0x80152194 (src/shared) */


DEFINE_func_8015220C()  /* dedup: shared engine-core @0x8015220c (src/shared) */


DEFINE_func_80152254()  /* dedup: shared engine-core @0x80152254 (src/shared) */


extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80153C18();
void func_801522CC(s32 a0) {
    s32 v1;
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    func_80154A74(a0, 0x11);
    func_801553C0(a0);
    func_801470AC((s32 *)a0);
    func_801472B4((void *)a0);
    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(a0 + 0x3E) = 0;
    *(s16 *)(a0 + 0x40) = 0;
    *(s16 *)(a0 + 0x42) = 0;
    *(u8 *)(a0 + 0xDD) = 0;
    *(u16 *)(a0 + 0x3C) = *(u16 *)(a0 + 0x3C) & 0xFFFE;
    *(s16 *)(v1 + 0x10) = 0;
    *(u16 *)(a0 + 0x60) = 0x1000;
    *(u16 *)(a0 + 0x62) = 0x1000;
    *(u16 *)(a0 + 0x64) = 0x1000;
    func_801477E8((s32 *)a0, 0);
    func_80153C18(a0);
}




void func_80152370(void *a0) {

    extern void (*D_80183D18[])(void);
    D_80183D18[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801523AC()  /* dedup: shared engine-core @0x801523ac (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (67 ins)

extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80019064(void *a0);
extern int func_80151204(int arg, int a1);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);


void func_801523F4(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_800D5880;
    extern s32 D_800D58AC;
    extern u8 D_80183D24[];
    s32 pad[4];
    s32 buf[4];
    register s32 s0a __asm__("$16");                    /* $s0 = buf */
    register s32 s2a __asm__("$18") = (s32)&D_80183D24; /* $s2 = &D_80183D24 */

    ((void (*)(s32, s32))func_80146E90)(arg0, 0);
    func_80019064(&D_80062C04);
    ((void (*)(s32, s32))func_80151204)(arg0, *(s16 *)(arg0 + 0xF2));
    if ((s16)func_80012A60((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12),
                           (s32)*(s16 *)(arg0 + 0xF4)) >= 0x401) {
        ((void (*)(s32, s32))func_80154274)(arg0, (s32)&D_800D5880);
    } else {
        ((void (*)(s32, s32))func_80154274)(arg0, (s32)&D_800D58AC);
    }
    func_80154A74(arg0, 0x16);
    ((void (*)(s32))func_80149020)(arg0);
    s0a = (s32)buf;
    ((void (*)(s32, s32, s32))func_8001382C)((*(u16 *)(arg0 + 0xF4) - *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF,
                  s2a, s0a);
    ((void (*)(s32, s32))func_80146DB8)(arg0, s0a);
    ((void (*)(s32, s32))func_801477E8)(arg0, *(s32 *)(s2a + 0xC));
    func_80147324(0x451);
    ((void (*)(s32))func_80146CA0)(arg0);
    (void)pad;
}


DEFINE_func_80152500()  /* dedup: shared engine-core @0x80152500 (src/shared) */


DEFINE_func_801525F4()  /* dedup: shared engine-core @0x801525f4 (src/shared) */




void func_80152698(void *a0) {

    extern void (*D_80183D34[])(void);
    D_80183D34[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801526D4()  /* dedup: shared engine-core @0x801526d4 (src/shared) */


DEFINE_func_80152714()  /* dedup: shared engine-core @0x80152714 (src/shared) */


DEFINE_func_80152790()  /* dedup: shared engine-core @0x80152790 (src/shared) */




void func_8015282C(void *a0) {

    extern void (*D_80183D4C[])(void);
    D_80183D4C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152868()  /* dedup: shared engine-core @0x80152868 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);
extern void func_80154274(s32 *a0, s32 a1);

void func_801528B0(s32 arg0)
{

    extern u8 D_80062C04[];
    extern M2C_UNK D_800D5880;
    extern M2C_UNK D_80183D3C;
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80183D3C);
    func_801477E8(arg0, 0xFFF00000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_8015294C()  /* dedup: shared engine-core @0x8015294c (src/shared) */


DEFINE_func_80152A08()  /* dedup: shared engine-core @0x80152a08 (src/shared) */


DEFINE_func_80152A50()  /* dedup: shared engine-core @0x80152a50 (src/shared) */


DEFINE_func_80152AC8()  /* dedup: shared engine-core @0x80152ac8 (src/shared) */




void func_80152B6C(void *a0) {

    extern void (*D_80183D60[])(void);
    D_80183D60[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152BA8()  /* dedup: shared engine-core @0x80152ba8 (src/shared) */


DEFINE_func_80152BF0()  /* dedup: shared engine-core @0x80152bf0 (src/shared) */


DEFINE_func_80152C40()  /* dedup: shared engine-core @0x80152c40 (src/shared) */


DEFINE_func_80152C80()  /* dedup: shared engine-core @0x80152c80 (src/shared) */




void func_80152D24(void *a0) {

    extern void (*D_80183D7C[])(void);
    D_80183D7C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80152D60()  /* dedup: shared engine-core @0x80152d60 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147324(s32 a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_8014CBF8(void *a0);
extern int func_80151204(int arg, int a1);
extern void func_80154274(s32 *a0, s32 a1);

void func_80152DA8(s32 arg0)
{

    extern s32 D_80062C14;
    extern M2C_UNK D_800D5880;
    extern M2C_UNK D_80183D6C;
    func_80019064(&D_80062C14);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    M2C_FIELD(arg0, s8 *, 0xDF) = 8;
    func_80146DB8(arg0, &D_80183D6C);
    func_801477E8(arg0, 0xFFE40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_80152E4C()  /* dedup: shared engine-core @0x80152e4c (src/shared) */


DEFINE_func_80152EFC()  /* dedup: shared engine-core @0x80152efc (src/shared) */


DEFINE_func_80152F44()  /* dedup: shared engine-core @0x80152f44 (src/shared) */


DEFINE_func_80152FBC()  /* dedup: shared engine-core @0x80152fbc (src/shared) */




void func_80153060(void *a0) {

    extern void (*D_80183D90[])(void);
    D_80183D90[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015309C()  /* dedup: shared engine-core @0x8015309c (src/shared) */


DEFINE_func_801530E4()  /* dedup: shared engine-core @0x801530e4 (src/shared) */


DEFINE_func_80153150()  /* dedup: shared engine-core @0x80153150 (src/shared) */


DEFINE_func_801531BC()  /* dedup: shared engine-core @0x801531bc (src/shared) */


DEFINE_func_80153204()  /* dedup: shared engine-core @0x80153204 (src/shared) */


DEFINE_func_8015327C()  /* dedup: shared engine-core @0x8015327c (src/shared) */




void func_80153320(void *a0) {

    extern void (*D_80183DA4[])(void);
    D_80183DA4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015335C()  /* dedup: shared engine-core @0x8015335c (src/shared) */


DEFINE_func_801533A4()  /* dedup: shared engine-core @0x801533a4 (src/shared) */


DEFINE_func_80153410()  /* dedup: shared engine-core @0x80153410 (src/shared) */


DEFINE_func_80153490()  /* dedup: shared engine-core @0x80153490 (src/shared) */


DEFINE_func_801534D8()  /* dedup: shared engine-core @0x801534d8 (src/shared) */


DEFINE_func_80153550()  /* dedup: shared engine-core @0x80153550 (src/shared) */


extern void func_80146D90(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014ED28(s32 _arg0);
extern void func_8014FA04(s32 a0);

s32 func_801535F4(void *arg0) {
    s32 var_s1;
    register u32 flags __asm__("$4");
    register u32 fcopy __asm__("$3");
    s32 ret;

    var_s1 = 0;
    if (((s32 (*)(void))func_8014ED28)() != 0) {
        func_80146D90((s32)arg0);
    }
    if ((*(s32 *)((u8 *)arg0 + 0x34) > 0) &&
        (((s32 (*)(s32))func_8014CC28)((s32)arg0) != 0)) {
        var_s1 = 1;
    }
    flags = ((s32 (*)(s32))func_8014FA04)((s32)arg0);
    fcopy = flags;
    if (flags & 0x4000) {
        ret = 2;
    } else if (flags & 0x2000) {
        ret = 1;
    } else {
        ret = 4;
        if ((fcopy & 0x8000) == 0) {
            ret = var_s1;
        }
    }
    __asm__ __volatile__("" : : "r"(flags));
    return ret;
}


DEFINE_func_8015369C()  /* dedup: shared engine-core @0x8015369c (src/shared) */


DEFINE_func_801536DC()  /* dedup: shared engine-core @0x801536dc (src/shared) */


DEFINE_func_80153800()  /* dedup: shared engine-core @0x80153800 (src/shared) */


DEFINE_func_80153978()  /* dedup: shared engine-core @0x80153978 (src/shared) */


DEFINE_func_801539F8()  /* dedup: shared engine-core @0x801539f8 (src/shared) */


DEFINE_func_80153B58()  /* dedup: shared engine-core @0x80153b58 (src/shared) */


DEFINE_func_80153BD8()  /* dedup: shared engine-core @0x80153bd8 (src/shared) */


DEFINE_func_80153BF0()  /* dedup: shared engine-core @0x80153bf0 (src/shared) */


DEFINE_func_80153C18()  /* dedup: shared engine-core @0x80153c18 (src/shared) */


DEFINE_func_80153C30()  /* dedup: shared engine-core @0x80153c30 (src/shared) */


DEFINE_func_80153C44()  /* dedup: shared engine-core @0x80153c44 (src/shared) */


DEFINE_func_80153C74()  /* dedup: shared engine-core @0x80153c74 (src/shared) */


DEFINE_func_80153C8C()  /* dedup: shared engine-core @0x80153c8c (src/shared) */


DEFINE_func_80153C9C()  /* dedup: shared engine-core @0x80153c9c (src/shared) */


DEFINE_func_80153CBC()  /* dedup: shared engine-core @0x80153cbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (expected); dispatch-table %lo-fold via extern fn-ptr array, s0 holds param across both calls
extern void func_80019064(void *a0);

void func_80153CCC(S80153CCC *a0) {

    extern s32 D_80183DB8;
    extern void (*D_80183DE0[])(void *a0);
    extern s16 D_8011DB0C;
    extern u16 D_8011F748;
    ((s32 (*)(s32))func_80019064)((s32)&D_80183DB8);
    D_80183DE0[a0->idx](a0);
    D_8011DB0C = 0;
    D_8011F748 = 0;
}


DEFINE_func_80153D34()  /* dedup: shared engine-core @0x80153d34 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (33/33)

extern void func_80147324(s32 arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern s16 currentLocationId;

void func_80153D7C(s32 param_1)
{

    extern u8 D_80183DC0;
    func_80147324(0x451);
    func_80154274((s32 *)param_1, (s32)&D_80183DC0);
    func_80149020((s32 *)param_1);
    *(u16 *)(param_1 + 0x244) = *(u16 *)(param_1 + 6);
    *(u16 *)(param_1 + 0x246) = *(u16 *)(param_1 + 10);
    *(u16 *)(param_1 + 0x248) = *(u16 *)(param_1 + 0xe);
    if (currentLocationId == 0x3075) *(u8 *)(param_1 + 0xde) = 0x14;
    else *(u8 *)(param_1 + 0xde) = 10;
    *(u8 *)(param_1 + 0xdf) = 0;
    __asm__ __volatile__("" ::: "memory");
    func_80146CA0((void *)param_1);
}


DEFINE_func_80153E00()  /* dedup: shared engine-core @0x80153e00 (src/shared) */


DEFINE_func_8015410C()  /* dedup: shared engine-core @0x8015410c (src/shared) */


DEFINE_func_80154134()  /* dedup: shared engine-core @0x80154134 (src/shared) */


DEFINE_func_80154150()  /* dedup: shared engine-core @0x80154150 (src/shared) */


DEFINE_func_80154190()  /* dedup: shared engine-core @0x80154190 (src/shared) */


DEFINE_func_801541D8()  /* dedup: shared engine-core @0x801541d8 (src/shared) */


DEFINE_func_80154218()  /* dedup: shared engine-core @0x80154218 (src/shared) */


DEFINE_func_80154274()  /* dedup: shared engine-core @0x80154274 (src/shared) */


DEFINE_func_801542A4()  /* dedup: shared engine-core @0x801542a4 (src/shared) */


DEFINE_func_801542DC()  /* dedup: shared engine-core @0x801542dc (src/shared) */


DEFINE_func_8015430C()  /* dedup: shared engine-core @0x8015430c (src/shared) */


DEFINE_func_80154358()  /* dedup: shared engine-core @0x80154358 (src/shared) */


DEFINE_func_80154418()  /* dedup: shared engine-core @0x80154418 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015444C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801549F8);

DEFINE_func_80154A74()  /* dedup: shared engine-core @0x80154a74 (src/shared) */


DEFINE_func_80154AB4()  /* dedup: shared engine-core @0x80154ab4 (src/shared) */


DEFINE_func_80154AE0()  /* dedup: shared engine-core @0x80154ae0 (src/shared) */


DEFINE_func_80154B20()  /* dedup: shared engine-core @0x80154b20 (src/shared) */


DEFINE_func_80154B4C()  /* dedup: shared engine-core @0x80154b4c (src/shared) */


DEFINE_func_80154B7C()  /* dedup: shared engine-core @0x80154b7c (src/shared) */


DEFINE_func_80154B98()  /* dedup: shared engine-core @0x80154b98 (src/shared) */


DEFINE_func_80154BC8()  /* dedup: shared engine-core @0x80154bc8 (src/shared) */


DEFINE_func_80154BE4()  /* dedup: shared engine-core @0x80154be4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80154C24);

DEFINE_func_80154ED8()  /* dedup: shared engine-core @0x80154ed8 (src/shared) */


DEFINE_func_80154F9C()  /* dedup: shared engine-core @0x80154f9c (src/shared) */



// @class: struct
// @stuck: none — MATCH (array-of-struct stride-8 base materialize + addu, %lo folded into addiu)

extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_800183E0(s32 a0);


void func_801550FC(s32 arg0)
{

    extern ImgRect8 D_80183DEC[];
    if (arg0 & 0x40000000) {
        MoveImage(&D_80183DEC[arg0 & 0xFF], 0x200, 0x100);
    } else {
        ((void (*)(void))func_800183E0)();
    }
}


DEFINE_func_80155150()  /* dedup: shared engine-core @0x80155150 (src/shared) */


DEFINE_func_801552F4()  /* dedup: shared engine-core @0x801552f4 (src/shared) */


DEFINE_func_80155344()  /* dedup: shared engine-core @0x80155344 (src/shared) */


DEFINE_func_80155394()  /* dedup: shared engine-core @0x80155394 (src/shared) */


DEFINE_func_801553A8()  /* dedup: shared engine-core @0x801553a8 (src/shared) */


DEFINE_func_801553C0()  /* dedup: shared engine-core @0x801553c0 (src/shared) */


DEFINE_func_80155440()  /* dedup: shared engine-core @0x80155440 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; decrement persists as separate addiu in delay slot


s32 func_80155458(s32 param_1)
{

    extern int (*D_80183E2C[])(void);
    int idx;

    idx = *(unsigned char *)(param_1 + 0x4e);
    if (idx != 0) {
        idx = idx - 1;
        if ((*D_80183E2C[idx])() == 0) {
            *(unsigned char *)(param_1 + 0x4e) = 0;
        }
    }
    return *(unsigned char *)(param_1 + 0x4e);
}


DEFINE_func_801554B8()  /* dedup: shared engine-core @0x801554b8 (src/shared) */


DEFINE_func_80155518()  /* dedup: shared engine-core @0x80155518 (src/shared) */


DEFINE_func_8015554C()  /* dedup: shared engine-core @0x8015554c (src/shared) */




void func_80155580(void *a0) {

    extern void (*D_80183E30[])(void);
    D_80183E30[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801555BC()  /* dedup: shared engine-core @0x801555bc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801555F4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80155800);

DEFINE_func_80155A44()  /* dedup: shared engine-core @0x80155a44 (src/shared) */


DEFINE_func_80155B20()  /* dedup: shared engine-core @0x80155b20 (src/shared) */


DEFINE_func_80155B9C()  /* dedup: shared engine-core @0x80155b9c (src/shared) */


DEFINE_func_80155C0C()  /* dedup: shared engine-core @0x80155c0c (src/shared) */


DEFINE_func_80155C64()  /* dedup: shared engine-core @0x80155c64 (src/shared) */


DEFINE_func_80155D70()  /* dedup: shared engine-core @0x80155d70 (src/shared) */


DEFINE_func_80155E30()  /* dedup: shared engine-core @0x80155e30 (src/shared) */


DEFINE_func_80155EA4()  /* dedup: shared engine-core @0x80155ea4 (src/shared) */


void func_80155F58(void) {
}

DEFINE_func_80155F60()  /* dedup: shared engine-core @0x80155f60 (src/shared) */


DEFINE_func_80155F80()  /* dedup: shared engine-core @0x80155f80 (src/shared) */


DEFINE_func_80155FB0()  /* dedup: shared engine-core @0x80155fb0 (src/shared) */


DEFINE_func_80155FD4()  /* dedup: shared engine-core @0x80155fd4 (src/shared) */


DEFINE_func_80155FF8()  /* dedup: shared engine-core @0x80155ff8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80156044);

DEFINE_func_8015616C()  /* dedup: shared engine-core @0x8015616c (src/shared) */


DEFINE_func_80156370()  /* dedup: shared engine-core @0x80156370 (src/shared) */




S801563EC *func_801563EC(u16 idx) {

    extern S801563EC D_80184024[];
    return &D_80184024[idx];
}


DEFINE_func_8015640C()  /* dedup: shared engine-core @0x8015640c (src/shared) */


DEFINE_func_801564B0()  /* dedup: shared engine-core @0x801564b0 (src/shared) */


DEFINE_func_801565C0()  /* dedup: shared engine-core @0x801565c0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80156600);

DEFINE_func_80156648()  /* dedup: shared engine-core @0x80156648 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80156670);

DEFINE_func_801567BC()  /* dedup: shared engine-core @0x801567bc (src/shared) */


DEFINE_func_80156848()  /* dedup: shared engine-core @0x80156848 (src/shared) */


DEFINE_func_80156A14()  /* dedup: shared engine-core @0x80156a14 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; D_8011520C indexed by param_2 (byte) folds %lo; D_80184294 indexed halfword folds %lo
extern void func_80147324(s32 arg0);

void func_80156A1C(s32 param_1, s32 param_2)
{

    extern unsigned char D_8011520C[];
    extern unsigned short D_80184294[];
    if (*(unsigned char *)(param_1 + 0xDA) == 0) {
        func_80147324(D_80184294[D_8011520C[param_2]]);
        *(unsigned char *)(param_1 + 0xDA) = *(unsigned char *)(param_1 + 0xDA) + 1;
    }
}


DEFINE_func_80156A88()  /* dedup: shared engine-core @0x80156a88 (src/shared) */


DEFINE_func_80156B74()  /* dedup: shared engine-core @0x80156b74 (src/shared) */


DEFINE_func_80156ECC()  /* dedup: shared engine-core @0x80156ecc (src/shared) */


DEFINE_func_80156FA8()  /* dedup: shared engine-core @0x80156fa8 (src/shared) */


DEFINE_func_80157158()  /* dedup: shared engine-core @0x80157158 (src/shared) */


DEFINE_func_801571C4()  /* dedup: shared engine-core @0x801571c4 (src/shared) */


DEFINE_func_801574DC()  /* dedup: shared engine-core @0x801574dc (src/shared) */


DEFINE_func_80157510()  /* dedup: shared engine-core @0x80157510 (src/shared) */




void func_80157544(void *a0) {

    extern void (*D_801842A4[])(void);
    D_801842A4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80157580()  /* dedup: shared engine-core @0x80157580 (src/shared) */


DEFINE_func_801575E4()  /* dedup: shared engine-core @0x801575e4 (src/shared) */


DEFINE_func_801576A8()  /* dedup: shared engine-core @0x801576a8 (src/shared) */


DEFINE_func_8015771C()  /* dedup: shared engine-core @0x8015771c (src/shared) */


DEFINE_func_8015773C()  /* dedup: shared engine-core @0x8015773c (src/shared) */



// @class: plumbing
// @stuck: none — MATCH expected (scalar global store + two sequential calls, param_1 saved across)

extern void func_80147078(s32 *a0, s16 a1);
extern void func_801578C0(s32 a0);

void func_80157788(int param_1)
{

    extern int D_801A6B88;
    D_801A6B88 = 300;
    ((void (*)(int, int))func_80147078)(param_1, 7);
    func_801578C0(param_1);
}



// @class: plumbing
// @stuck: none — MATCH expected (scalar global store + two sequential calls, param_1 saved across)

extern void func_80147078(s32 *a0, s16 a1);
extern void func_80157808(s32 a0);

void func_801577C8(int param_1)
{

    extern int D_801A6B88;
    D_801A6B88 = 300;
    ((void (*)(int, int))func_80147078)(param_1, 7);
    func_80157808(param_1);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80157808);

DEFINE_func_80157880()  /* dedup: shared engine-core @0x80157880 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (expected); STUB: param_1 held in $s0 across calls, u8 store of 9 before func_80154274

extern void func_80156648(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147324(s32 arg0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern s32 func_801725A4(u8 *a0);

void func_801578C0(s32 param_1)
{

    extern u8 D_800D5128;
    extern u8 D_801842AC;
    ((void (*)(void))func_80156648)();
    *(u8 *)(param_1 + 0x1AA) = 9;
    func_80154274((s32 *)param_1, (s32)&D_800D5128);
    ((void (*)(s32 *, s32))func_80154A74)((s32 *)param_1, 0x15);
    func_80147324(0xC20);
    ((void (*)(s32 *, s32))func_80146DB8)((s32 *)param_1, (s32)&D_801842AC);
    ((void (*)(s32, s32 *, s32, s32))func_80146994)(4, (s32 *)param_1, 7, 0);
    ((void (*)(s32, s32 *, s32, s32))func_80146994)(5, (s32 *)param_1, 9, 0);
    ((void (*)(s32 *))func_80146CA0)((s32 *)param_1);
    ((void (*)(s32 *))func_801725A4)((s32 *)param_1);
}



// @class: other
// @stuck: none — MATCH (76 ins). Body is byte-identical with a plain transcription; the only
//   delta was frame size: target frame is 0x30 (saves at 0x20/0x24/0x28), not 0x20. Target reserves
//   a 16-byte UNREFERENCED stack local (no sp refs anywhere in the body) — gcc-2.7.2 does NOT
//   dead-strip an aggregate local even at -O2, so a dead `int frame_pad[4]` reproduces vars=16
//   (.frame $sp,48: vars=16, regs=3, args=16) with zero body footprint. match_one => MATCH.

extern void func_80147A10(int a0, int a1);
extern void func_80147A84(int);
extern void func_801473EC(s32 *a0);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_8014ED28(s32 _arg0);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern int func_80155FF8(int arg, int a1);
extern void func_80154A74(int, int);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern s32 func_801725A4(u8 *a0);


void func_8015795C(int param_1)
{

    extern unsigned char D_800D5178;
    extern unsigned char D_801842BC;
    int frame_pad[4]; /* dead 16-byte local: forces target's 0x30 frame (vars=16); never referenced */
    int iVar1;
    unsigned int uVar2;

    *(unsigned int *)(param_1 + 0x44) = *(unsigned int *)(param_1 + 0x44) | 2;
    ((int (*)(int, int))func_80147A10)(param_1, 0x400);
    if (*(int *)(param_1 + 0x2c) >= 0) {
        *(int *)(param_1 + 0x2c) = 0;
    }
    func_80147A84(param_1);
    ((void (*)(int))func_801473EC)(param_1);
    func_80148038(param_1, 0x1a000);
    func_80147460(param_1);
    iVar1 = ((int (*)(int))func_8014ED28)(param_1);
    if (iVar1 != 0) {
        func_80146D90(param_1);
    }
    uVar2 = ((int (*)(int))func_80161450)(param_1);
    if ((uVar2 & 5) != 0) {
        func_80157A8C(param_1);
        ((void (*)(int, int))func_80146E90)(param_1, 8);
        ((void (*)(int))func_80146CA0)(param_1);
    }
    if (uVar2 == 0) {
        ((void (*)(int, int))func_80155FF8)(param_1, *(unsigned char *)(param_1 + 0x1aa));
        if (*(unsigned char *)(param_1 + 0x1c0) != 0) {
            func_80154A74(param_1, 0x17);
            ((void (*)(int, void *))func_80154274)(param_1, &D_800D5178);
            ((void (*)(int, void *))func_80146DB8)(param_1, &D_801842BC);
            ((void (*)(int, int))func_801477E8)(param_1, 0xfff40000);
            *(short *)(param_1 + 2) = 4;
        }
        ((void (*)(int))func_801725A4)(param_1);
    }
    return;
}


DEFINE_func_80157A8C()  /* dedup: shared engine-core @0x80157a8c (src/shared) */


DEFINE_func_80157AC8()  /* dedup: shared engine-core @0x80157ac8 (src/shared) */


DEFINE_func_80157B74()  /* dedup: shared engine-core @0x80157b74 (src/shared) */


DEFINE_func_80157BC8()  /* dedup: shared engine-core @0x80157bc8 (src/shared) */


DEFINE_func_80157CCC()  /* dedup: shared engine-core @0x80157ccc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80157D20);

DEFINE_func_80157D74()  /* dedup: shared engine-core @0x80157d74 (src/shared) */




void func_80157DC4(void *a0) {

    extern void (*D_8018430C[])(void);
    D_8018430C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80157E00()  /* dedup: shared engine-core @0x80157e00 (src/shared) */


DEFINE_func_80157E38()  /* dedup: shared engine-core @0x80157e38 (src/shared) */


DEFINE_func_80157EA4()  /* dedup: shared engine-core @0x80157ea4 (src/shared) */


DEFINE_func_80157F64()  /* dedup: shared engine-core @0x80157f64 (src/shared) */




void func_80157FC4(void *a0) {

    extern void (*D_80184314[])(void);
    D_80184314[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80158000()  /* dedup: shared engine-core @0x80158000 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (expected); straight-line call sequence with two stores scheduled into jal delay slots

extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);


void func_80158038(void * param)
{

    extern s32 D_800D51E0;
    extern s32 D_801842E0;
    *(u8 *)(param + 0x1aa) = 0xe;
    func_80154274((s32 *)param, (s32)&D_800D51E0);
    func_80154A74(param, 0x15);
    func_80146DB8((s32 *)param, &D_801842E0);
    *(s32 *)(param + 0x234) = 0;
    func_80146994(5, param, 0xc, 0);
    func_80147324(0x455);
    func_80146CA0((void *)param);
}


DEFINE_func_801580B4()  /* dedup: shared engine-core @0x801580b4 (src/shared) */


DEFINE_func_801581AC()  /* dedup: shared engine-core @0x801581ac (src/shared) */




void func_8015824C(void *a0) {

    extern void (*D_80184320[])(void);
    D_80184320[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80158288()  /* dedup: shared engine-core @0x80158288 (src/shared) */


DEFINE_func_801582C0()  /* dedup: shared engine-core @0x801582c0 (src/shared) */


DEFINE_func_80158344()  /* dedup: shared engine-core @0x80158344 (src/shared) */



// @class: other
// @stuck: none — MATCH (branch-polarity invert on both dispatch ifs + goto block-order to put the v1!=0/L508 paths as fallthrough; phantom 0x10 frame via address-taken frame_pad[4] + (void)& — zero code)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern s32 func_801615C4(void *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern int func_80155FF8(int arg, int a1);


void func_80158434(s32 param_1)
{

    extern u8 D_801842F0;
    extern u8 D_800D533C;
    u32 uVar1;
    u32 uVar2;
    s32 frame_pad[4];
    (void)&frame_pad;

    *(u32 *)(param_1 + 0x44) = *(u32 *)(param_1 + 0x44) | 2;
    if ((*(u16 *)(param_1 + 0xB8) & 0x4000) != 0) {
        *(s32 *)(param_1 + 0x234) = *(s32 *)(param_1 + 0x234) + 1;
        ((s32 (*)(void))func_8014CBF8)();
        ((void (*)(s32))func_801474EC)(param_1);
        ((void (*)(s32, s32))func_801477E8)(param_1, 0xFFFA0000);
        ((void (*)(s32, s32))func_80146DB8)(param_1, (s32)&D_801842F0);
    }
    if (*(s32 *)(param_1 + 0x234) != 0) {
        func_80148038(param_1, 0x10000);
        func_80147460(param_1);
        func_80147AD4(param_1, 0, 0, 0);
        ((void (*)(s32))func_801473EC)(param_1);
    }
    uVar1 = ((s32 (*)(s32, s32))func_801615C4)(param_1, 0);
    if (uVar1 != 0) {
        if (uVar1 == 1) goto LAB_80158508;
        uVar2 = uVar1 & 0x2000;
    } else {
        uVar2 = func_80146E98(param_1);
    }
    if (uVar2 == 0) goto LAB_80158528;
LAB_80158508:
    ((void (*)(s32, s32))func_80154274)(param_1, (s32)&D_800D533C);
    ((void (*)(s32))func_80146CA0)(param_1);
    return;
LAB_80158528:
    ((void (*)(s32, s32))func_80155FF8)(param_1, *(u8 *)(param_1 + 0x1AA));
}


DEFINE_func_80158548()  /* dedup: shared engine-core @0x80158548 (src/shared) */


DEFINE_func_801585A4()  /* dedup: shared engine-core @0x801585a4 (src/shared) */


DEFINE_func_801585AC()  /* dedup: shared engine-core @0x801585ac (src/shared) */


DEFINE_func_801585EC()  /* dedup: shared engine-core @0x801585ec (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80158638);

void func_80158794(void) {
}


// @class: plumbing
// @stuck: none — MATCH expected (3 scalar global stores + byte store + 6 calls, source order)

extern void func_80147084(s32 *a0);
extern void func_80147098(s32 *a0);
extern void func_801470AC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80158880(s32 *param);

void func_8015879C(s32 param_1) {

    extern s32 D_801A6B90;
    extern s32 D_801A6B9C;
    extern s32 D_801A6BA0;
    D_801A6B90 = 0;
    D_801A6B9C = 1;
    D_801A6BA0 = 0;
    *(u8 *)(param_1 + 0xa8) = 0;
    ((void (*)(void))func_80147084)();
    ((void (*)(s32))func_80147098)(param_1);
    ((void (*)(s32))func_801470AC)(param_1);
    ((void (*)(s32, s32))func_80147078)(param_1, 0x1a);
    ((void (*)(s32, s32))func_80146C98)(param_1, 1);
    ((void (*)(s32))func_80158880)(param_1);
}



// @class: plumbing
// @stuck: none — MATCH (STUB: 3 global stores + byte store + 5 calls in source order)

extern void func_80147084(s32 *a0);
extern void func_80147098(s32 *a0);
extern void func_801470AC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80158880(s32 *param);

void func_80158814(void *arg0) {

    extern s32 D_801A6B90;
    extern s32 D_801A6B9C;
    extern s32 D_801A6BA0;
    D_801A6B90 = 0;
    D_801A6B9C = 1;
    D_801A6BA0 = 0;
    *(s8 *)((s32)arg0 + 0xA8) = 0;
    ((void (*)(void))func_80147084)();
    ((void (*)(void *))func_80147098)(arg0);
    ((void (*)(void *))func_801470AC)(arg0);
    ((void (*)(void *, s32))func_80147078)(arg0, 0x1A);
    ((void (*)(void *))func_80158880)(arg0);
}



extern void func_80149020(s32 *a0);

void func_80158880(s32 *param) {

    extern void (*D_8018435C[])(s32 *);
    func_80149020(param);
    D_8018435C[*(u8 *)((s32)param + 0x4F)](param);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801588CC);

DEFINE_func_80158AB4()  /* dedup: shared engine-core @0x80158ab4 (src/shared) */


DEFINE_func_80158AE4()  /* dedup: shared engine-core @0x80158ae4 (src/shared) */



extern void func_80146CA0(void *a0);
extern s32 func_801472C8(struct S *a0);
extern void func_80147324(s32 a0);
extern void func_801474D8(s32 *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);

void func_80158BB0(void *arg0) {

    extern M2C_UNK D_800D58D8;
    extern s32 D_801A6B90;
    if (D_801A6B90 == 0) {
        D_801A6B90 = 1;
    }
    func_80147324(0x456);
    func_80154274(arg0, &D_800D58D8);
    func_80154A74(arg0, 0x16);
    M2C_FIELD(arg0, s32 *, 0x234) = 0xE30000;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x10) = 0;
    func_801474EC(arg0);
    func_801474D8(arg0);
    func_801472C8(arg0);
    func_80146CA0(arg0);
}


DEFINE_func_80158C40()  /* dedup: shared engine-core @0x80158c40 (src/shared) */


DEFINE_func_80158CD8()  /* dedup: shared engine-core @0x80158cd8 (src/shared) */


DEFINE_func_80158D60()  /* dedup: shared engine-core @0x80158d60 (src/shared) */


DEFINE_func_80158E24()  /* dedup: shared engine-core @0x80158e24 (src/shared) */



// @class: other
// @stuck: none — MATCH (signed %11 magic + word-array %lo fold; ((void (*)(int))func_80146CA0)(param_1) reuses $a0 for the 0x198 store in its jal delay slot)


extern int rand(void);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_80158F00(int param_1) {

    extern s32 D_801A6B9C;
    extern s32 D_80184330[];
    int *self = (int *)param_1;
    struct Actor *act = (struct Actor *)self[0x20 / 4];
    int gate = D_801A6B9C;

    act->timer = (u16)((act->timer + 0x16) & 0xfff);

    if (gate == 0) {
        s32 r = rand();
        *(s32 *)(param_1 + 0x198) = func_8013767C(D_80184330[r % 0xb]);
        ((void (*)(int))func_80146CA0)(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH (51 ins). Key: func_801594E8 takes a 2nd arg = sVar1 (the (short)func_80159464
//        return). $a1 is set by sra BEFORE the beqz and stays live into the jal, so the value is used
//        twice (branch test + arg2) — that 2nd use is what keeps the sll;sra (gcc folds sll;sra;beqz
//        -> sll;beqz otherwise). Also: branch-polarity invert (!=0 -> 594E8 fall-through, else 767C);
//        func_8013767C arg is &(*(u8 *)&D_80110C3C) (lui%hi+addiu%lo, not a literal). Ghidra missed the 2nd arg.


extern u16 func_80148800(s32 *a0);
extern s32 func_801399F0(s32);
extern void func_80139914(s32);
extern s32 func_80159464(void);
extern void func_801594E8(s32, s32);
extern void func_80146C98(s32 *a0, s16 a1);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_80158FA4(s32 param_1)
{

    extern s32 D_801A6BA0;
    extern u8 D_80110C3C[];
    s32 v0;
    s16 sVar1;

    v0 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v0 + 0x12) = (*(u16 *)(v0 + 0x12) + 0x16) & 0xfff;
    if (((s32 (*)(void))func_80148800)() & 0xf0) {
        D_801A6BA0 = 1;
    }
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        func_80139914(*(s32 *)(param_1 + 0x198));
        *(s32 *)(param_1 + 0x198) = 0;
        sVar1 = ((s32 (*)(s32))func_80159464)(param_1);
        if (sVar1 != 0) {
            func_801594E8(param_1, sVar1);
            ((void (*)(s32, s32))func_80146C98)(param_1, 0xc);
        } else {
            *(s32 *)(param_1 + 0x198) = ((s32 (*)(u8 *))func_8013767C)(&(*(u8 *)&D_80110C3C));
            ((void (*)(s32))func_80146CA0)(param_1);
        }
    }
}


DEFINE_func_80159070()  /* dedup: shared engine-core @0x80159070 (src/shared) */


DEFINE_func_80159120()  /* dedup: shared engine-core @0x80159120 (src/shared) */


DEFINE_func_801592CC()  /* dedup: shared engine-core @0x801592cc (src/shared) */



extern void func_80145BF8(void);
extern void func_80146CA0(void *a0);

void func_8015934C(void *arg0) {

    extern u8 D_800AE6BD;
    extern s32 D_801A6B90;
    extern s32 D_801A6B98;
    void *temp_v1;

    if (D_801A6B90 == 4) {
        D_801A6B90 = 5;
    }
    if (D_801A6B98 != 0) {
        func_80145BF8();
        func_80146CA0(arg0);
        D_800AE6BD += 1;
    }
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_v1, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_v1, u16 *, 0x12) + 0x16) & 0xFFF);
}


DEFINE_func_801593E4()  /* dedup: shared engine-core @0x801593e4 (src/shared) */


DEFINE_func_80159404()  /* dedup: shared engine-core @0x80159404 (src/shared) */


DEFINE_func_80159434()  /* dedup: shared engine-core @0x80159434 (src/shared) */



extern s16 currentLocationId;
extern s32 func_80029A94(s32);


s32 func_80159464(void) {

    extern Entry D_80184398[];
    Entry *e;

    e = D_80184398;
    while (e->id != 0) {
        if (currentLocationId == e->id) {
            return e->val;
        }
        e++;
    }
    if (func_80029A94(1) != 0) {
        goto ret0;
    }
    if (func_80029A94(0) != 0) {
        goto ret0;
    }
    return -1;
ret0:
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801594E8);



void func_80159698(void *a0) {

    extern void (*D_801845AC[])(void);
    D_801845AC[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_801596D4()  /* dedup: shared engine-core @0x801596d4 (src/shared) */



// @class: iv-combine
// @stuck: none — MATCH (97 ins). Recipe: $s0=base=&(*(u8 *)&D_800AF630) hoisted at top; loop1 = for(p=base+0x65A8;
//   p<base+0x9DA8;p+=0xe) p[1]|=... (the +4 field-offset store folds into the reduced IV -> gcc emits the
//   -4 loop-inversion guard + reuses END for END+4). BOTHER: loop2 needs ab=&D_800AFAE8 POST-guard as a
//   shared base for A=ab+1,B=ab+0x22 -> a for-loop hoists it PRE-guard (fold or perm); the fix is a manual
//   guarded do-while `if(base+0x2A8<base+0x65A8){ ... do{}while(q<inline base+0x65AC);}` with a DISTINCT loop
//   var (q, not p) so loop1's biv-elim survives, an INLINE while-bound (frees the delay slot for the OR
//   const), and the OR const HOISTED to a var declared first so it fills the guard delay slot (a3) and A/B
//   fall into a2/a1. Barrier after the two 0x7fff stores fixes their vs the loop-guard-low ordering.


extern void func_80174B6C(void);
extern void func_80129248(s16 a0);
extern void func_8013C938(void);
extern void func_8013CB20(void);
extern void func_8013C98C(void);
extern void func_8002850C(s32, s32, s32);
extern void func_80028620(s32, void *);


s32 func_801596F0(s32 param_1) {

    extern s16 D_800B9AAC[];
    extern s16 D_800B9B00;
    extern u16 D_801270C0;
    extern u8 D_800AF630[];
    extern u32 D_800AFAE8[];
    extern char D_801843CC[];
    u8 *base = &(*(u8 *)&D_800AF630);
    s32 v;
    u32 *p;
    u32 *q;

    v = *(s32 *)(param_1 + 0x28) - 1;
    *(s32 *)(param_1 + 0x28) = v;
    if (v == -1) {
        func_80174B6C();
        (*(s16 *)&D_800B9AAC) = 0x7fff;
        D_800B9B00 = 0x7fff;

        __asm__ __volatile__("" ::: "memory");

        for (p = (u32 *)(base + 0x65A8); p < (u32 *)(base + 0x9DA8); p += 0xe) {
            p[1] |= 0x80000000;
        }

        if ((u32 *)(base + 0x2A8) < (u32 *)(base + 0x65A8)) {
            u32 orc = 0x80000000;
            u32 *ab = D_800AFAE8;
            q = (u32 *)(base + 0x2AC);
            do {
                if (q < ab + 1 || q >= ab + 0x22) {
                    *q |= orc;
                }
                q += 0x21;
            } while (q < (u32 *)(base + 0x65AC));
        }

        (*(s16 *)&D_801270C0) = 3;
        ((void (*)(s32))func_80129248)(0);
        func_8013C938();
        func_8013CB20();
        func_8013C98C();
        func_8002850C(0x800, 0x800, 0x800);
        func_80028620(0, &(*(u8 *)&D_801843CC));
        func_80028620(1, &(*(u8 *)&D_801843CC) + 0x10);
        func_80028620(2, &(*(u8 *)&D_801843CC) + 0x20);
        *(s32 *)(param_1 + 0x28) = 0xff;
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


DEFINE_func_80159874()  /* dedup: shared engine-core @0x80159874 (src/shared) */


DEFINE_func_8015987C()  /* dedup: shared engine-core @0x8015987c (src/shared) */


DEFINE_func_801598BC()  /* dedup: shared engine-core @0x801598bc (src/shared) */


DEFINE_func_801598E0()  /* dedup: shared engine-core @0x801598e0 (src/shared) */




void func_80159968(void *a0) {

    extern void (*D_80184650[])(void);
    D_80184650[*(u8 *)((s32)a0 + 0x4D)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801599A4);

DEFINE_func_801599E0()  /* dedup: shared engine-core @0x801599e0 (src/shared) */


void func_80159A18(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80159A20);

DEFINE_func_80159B08()  /* dedup: shared engine-core @0x80159b08 (src/shared) */


DEFINE_func_80159B3C()  /* dedup: shared engine-core @0x80159b3c (src/shared) */




void func_80159B70(void *a0) {

    extern void (*D_801847A4[])(void);
    D_801847A4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80159BAC()  /* dedup: shared engine-core @0x80159bac (src/shared) */



// @class: schedule
// @stuck: none — MATCH (40 ins). Duplicate func_80154A74(arg0,K) into BOTH branch arms (not a
//         single shared-join call): forces gcc to cross-jump the jal while keeping per-arm
//         `addu $a0,$s0` setup + a `nop` join delay slot, matching the 40-ins layout. Branch
//         polarity: write `if (flag & 0x200 != 0){5,0x1C} else {4,0x11}` to get the `beqz`.

extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801553A8(s32 *a0);
extern s32 func_80172590(u8 *a0);
extern void func_80146CA0(void *a0);


void func_80159BE4(s32 arg0)
{

    extern unsigned char D_801845C0;
    int v;

    ((void (*)(int, void *))func_80146DB8)(arg0, &D_801845C0);
    if ((*(unsigned int *)(arg0 + 0x44) & 0x200) != 0) {
        func_80154150(arg0, 5);
        func_80154A74(arg0, 0x1C);
    } else {
        func_80154150(arg0, 4);
        func_80154A74(arg0, 0x11);
    }
    *(int *)(arg0 + 0x234) = 0;
    *(int *)(arg0 + 0x238) = 0;
    func_801553C0(arg0);
    ((void (*)(int))func_801553A8)(arg0);
    ((void (*)(int))func_80172590)(arg0);
    ((void (*)(int))func_80146CA0)(arg0);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80159C84);

DEFINE_func_8015A1C8()  /* dedup: shared engine-core @0x8015a1c8 (src/shared) */


DEFINE_func_8015A1FC()  /* dedup: shared engine-core @0x8015a1fc (src/shared) */


DEFINE_func_8015A230()  /* dedup: shared engine-core @0x8015a230 (src/shared) */




void func_8015A264(void *a0) {

    extern void (*D_801847AC[])(void);
    D_801847AC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015A2A0()  /* dedup: shared engine-core @0x8015a2a0 (src/shared) */



// @class: other
// @stuck: none — MATCH (60 ins). switch() gives signed slti pivot; per-case duplicated call gives per-case a0 setup + nop jal delay


extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern s32 func_80172608(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015A2D8(s32 param_1)
{

    extern int D_801845D0;
    unsigned char bVar1;

    ((void (*)(int, int *))func_80146DB8)(param_1, &D_801845D0);
    if ((*(unsigned int *)(param_1 + 0x44) & 0x200) != 0) {
        func_80154150(param_1, 10);
        func_80154A74(param_1, 0x1c);
        *(int *)(param_1 + 0x2c) = 0xfffc0000;
        goto LAB_8015a38c;
    }
    bVar1 = *(unsigned char *)(param_1 + 0xa9);
    switch (bVar1) {
    case 0x41:
        func_80154150(param_1, 7);
        break;
    case 0x53:
    case 0x73:
        func_80154150(param_1, 6);
        break;
    default:
        *(int *)(param_1 + 0x23c) = 0;
        goto LAB_8015a390;
    }
    func_80154A74(param_1, 0x21);
LAB_8015a38c:
    *(int *)(param_1 + 0x23c) = 0;
LAB_8015a390:
    func_8014C010(param_1, 2);
    ((void (*)(int))func_801553A8)(param_1);
    ((void (*)(int))func_80172608)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015A3C8);

DEFINE_func_8015AB7C()  /* dedup: shared engine-core @0x8015ab7c (src/shared) */


DEFINE_func_8015ABD4()  /* dedup: shared engine-core @0x8015abd4 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (param held in $s0 across 3 calls; lhu 0x16E; &D_801845F0 arg)
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80161CD0(s32 a0, s32 a1);

void func_8015AC48(s32 arg0)
{

    extern M2C_UNK D_801845F0;
    func_80154150(arg0, 9);
    func_80146DB8((s32 *)arg0, &D_801845F0);
    func_80161CD0(arg0, M2C_FIELD(arg0, u16 *, 0x16E));
}


DEFINE_func_8015AC90()  /* dedup: shared engine-core @0x8015ac90 (src/shared) */


DEFINE_func_8015ACC4()  /* dedup: shared engine-core @0x8015acc4 (src/shared) */


DEFINE_func_8015AD08()  /* dedup: shared engine-core @0x8015ad08 (src/shared) */




void func_8015AD3C(void *a0) {

    extern void (*D_801847B4[])(void);
    D_801847B4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015AD78()  /* dedup: shared engine-core @0x8015ad78 (src/shared) */


DEFINE_func_8015ADB0()  /* dedup: shared engine-core @0x8015adb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015AE2C);

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015b6f4 (src/shared) */


DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015b7b4 (src/shared) */


DEFINE_func_8015B858()  /* dedup: shared engine-core @0x8015b858 (src/shared) */


DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015b8f8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015B950);

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015bd8c (src/shared) */


DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015bdd0 (src/shared) */


DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015be04 (src/shared) */




void func_8015BE38(struct Obj *a0) {

    extern void (*D_801847D0[])(void);
    D_801847D0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015be74 (src/shared) */


DEFINE_func_8015BE94()  /* dedup: shared engine-core @0x8015be94 (src/shared) */


DEFINE_func_8015BEC4()  /* dedup: shared engine-core @0x8015bec4 (src/shared) */


DEFINE_func_8015BEE4()  /* dedup: shared engine-core @0x8015bee4 (src/shared) */


DEFINE_func_8015BF04()  /* dedup: shared engine-core @0x8015bf04 (src/shared) */


DEFINE_func_8015BF48()  /* dedup: shared engine-core @0x8015bf48 (src/shared) */


DEFINE_func_8015BF7C()  /* dedup: shared engine-core @0x8015bf7c (src/shared) */


DEFINE_func_8015BFB0()  /* dedup: shared engine-core @0x8015bfb0 (src/shared) */




void func_8015BFF4(void *a0) {

    extern void (*D_801847DC[])(void);
    D_801847DC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015C030);

DEFINE_func_8015C08C()  /* dedup: shared engine-core @0x8015c08c (src/shared) */


DEFINE_func_8015C0C4()  /* dedup: shared engine-core @0x8015c0c4 (src/shared) */


extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146CA0(void *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80147324(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80147A84(s32 arg0);
extern int func_80148AFC(void *a0);
extern s32 func_80149FB0(s32 a0);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_8014CC28(s32 a0);
extern void func_8014D738(void);
extern void func_8014F3E8(s32 a0);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);



s32 func_8015C128(s32 param_1) {

    extern u16 D_800B99DA;
    extern void func_8015C6E0(int);
    extern void (*D_8018465C[])(int);

    int sp10[3];
    int sp20[3];
    int temp_s0;
    int temp_v0;

    ((void(*)())func_80149FB0)();
    if (((int(*)(int))func_80148AFC)(((int)param_1)) & 0xFF) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = -0x4000;
        ((void(*)(int, int *, int *))func_8001382C)(*(short *)(*(int *)(((int)param_1) + 0x20) + 0x12), sp10, sp20);
        *(int *)(((int)param_1) + 0x234) += sp20[0];
        *(int *)(((int)param_1) + 0x238) += sp20[1];
        *(int *)(((int)param_1) + 0x23C) += sp20[2];
    }
    ((void(*)(int, int *, int *))func_8001382C)((short)(-*(unsigned short *)(*(int *)(((int)param_1) + 0x20) + 0x12)),
                  (int *)(((int)param_1) + 0x234), sp20);
    ((void(*)(int, int *))func_80146DB8)(((int)param_1), sp20);
    func_80147A84(((int)param_1));
    ((void(*)(int))func_801473EC)(((int)param_1));
    if (!(D_800B99DA & 3)) {
        ((void(*)(int, int))func_8014C010)(((int)param_1), 1);
        ((void(*)(int))func_80147324)(0x65F);
    }
    if (((int(*)(int))func_8014D738)(((int)param_1)) != 0) {
        D_8018465C[*(u16 *)((int)param_1)](((int)param_1));
        func_8015C6E0(((int)param_1));
        return;
    }
    temp_s0 = ((int(*)(int))func_8014CC28)(((int)param_1));
    temp_v0 = ((int(*)(int))func_8014F3E8)(((int)param_1));
    if (temp_v0 != 0) {
        if ((temp_v0 & 0xFF00) != 0x4000) {
            ((void(*)(int, int))func_80146E90)(((int)param_1), 6);
            ((void(*)(int))func_80146CA0)(((int)param_1));
            return;
        }
        if ((temp_v0 & 0x4000) && ((int(*)(int))func_80146E98)(((int)param_1)) != 0) {
            ((void(*)(int, int))func_80147078)(((int)param_1), 4);
            ((void(*)(int))func_8015C0C4)(((int)param_1));
        }
    } else if (temp_s0 == 0) {
        D_8018465C[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015C32C);

void func_8015C6A4(void) {
}

DEFINE_func_8015C6AC()  /* dedup: shared engine-core @0x8015c6ac (src/shared) */


DEFINE_func_8015C6E0()  /* dedup: shared engine-core @0x8015c6e0 (src/shared) */




void func_8015C714(void *a0) {

    extern void (*D_801847E8[])(void);
    D_801847E8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015C750()  /* dedup: shared engine-core @0x8015c750 (src/shared) */


DEFINE_func_8015C788()  /* dedup: shared engine-core @0x8015c788 (src/shared) */



// @class: struct
// @stuck: none — MATCH (match_one 88/88); fn-ptr-array dispatch, top-level if/else needed branch-polarity invert (small block falls through, big block at L854)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80149704(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);
extern void func_8014C010(s32 a0, s32 a1);


void func_8015C7E4(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    extern int D_80184600;
    s32 iVar1;
    u32 uVar2;

    iVar1 = ((s32 (*)(u16 *))func_80161B18)(param_1);
    if ((iVar1 == 0) && (iVar1 = ((s32 (*)(u16 *))func_80161B84)(param_1), iVar1 == 0)) {
        iVar1 = ((s32 (*)(u16 *))func_801496D4)(param_1);
        if (iVar1 != 0) {
            ((void (**)(u16*))D_8018465C)[*param_1](param_1);
            ((void (*)(u16 *))func_80149704)(param_1);
        } else {
            uVar2 = ((s32 (*)(u16 *))func_801487F4)(param_1);
            if (((uVar2 & 0x80) == 0) && (iVar1 = ((s32 (*)(u16 *))func_801488A8)(param_1), iVar1 == 0)) {
                ((void (**)(u16*))D_8018465C)[*param_1](param_1);
                ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
                ((void (*)(u16 *))func_80159B70)(param_1);
            } else {
                iVar1 = ((s32 (*)(u16 *))func_80161240)(param_1);
                if (iVar1 == 0) {
                    iVar1 = ((s32 (*)(u16 *))func_80146E98)(param_1);
                    if (iVar1 != 0) {
                        ((void (*)(u16 *))func_80148AAC)(param_1);
                        ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_80184600);
                        ((void (*)(u16 *, s32))func_80146E90)(param_1, 0x14);
                        ((void (*)(u16 *))func_80146CA0)(param_1);
                    }
                    if ((param_1[0x5c] & 0x2000) != 0) {
                        ((void (*)(u16 *, s32))func_80161C24)(param_1, param_1[0xb7]);
                        ((void (*)(u16 *, s32))func_8014C010)(param_1, 2);
                    }
                }
            }
        }
    }
    return;
}




// @class: struct
// @stuck: none — dispatch + control flow on a single callee-saved param; expect MATCH

extern s32 func_80149FB0(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);


void func_8015C944(int param_1) {

    extern void (*D_8018465C[])();
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_8018465C[*(unsigned short *)param_1])(param_1);
        ((void (*)(int, int))func_80147078)(param_1, 0);
        ((void (*)(int))func_80159B70)(param_1);
    } else {
        if (((int (*)(int))func_80161240)(param_1) == 0) {
            if (func_80146E98(param_1) != 0) {
                ((void (*)(int))func_80146CA0)(param_1);
            }
            if ((*(unsigned short *)(param_1 + 0xb8) & 0x2000) != 0) {
                func_80161C24(param_1, *(unsigned short *)(param_1 + 0x16e));
            }
        }
    }
}



// @class: schedule
// @stuck: none — MATCH (goto forces the func_80161240 block to the function tail; bnez-to-end layout vs early-return fall-through)


extern s32 func_80149FB0(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80161240(void *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80149704(void);


void func_8015CA28(u16 *param_1) {

    extern void (*D_8018465C[])(void*);
    extern int D_80184600;
    ((void (*)(void))func_80149FB0)();
    if (((int (*)(u16 *))func_80161B18)(param_1) != 0) return;
    if (((int (*)(u16 *))func_80161B84)(param_1) != 0) return;
    if (((int (*)(u16 *))func_801496D4)(param_1) != 0) {
        ((void (**)(u16*))D_8018465C)[*param_1](param_1);
        ((void (*)(u16 *))func_80149704)(param_1);
        return;
    }
    if ((((u32 (*)(u16 *))func_801487F4)(param_1) & 0x80) != 0 || ((int (*)(u16 *))func_801488A8)(param_1) != 0) {
        if ((((int (*)(u16 *))func_80148AAC)(param_1) & 0xff) != 0) {
            ((void (*)(u16 *, int, int, int))func_80147AD4)(param_1, 0, 0, 0);
            ((void (*)(u16 *))func_801473EC)(param_1);
        }
        if (((int (*)(u16 *))func_8014D738)(param_1) != 0) {
            ((void (*)(u16 *, void *))func_80146DB8)(param_1, &D_80184600);
            ((void (*)(u16 *, int))func_80146E90)(param_1, 0x14);
            ((void (*)(u16 *, int))func_80146C98)(param_1, 2);
        }
        if (*(int *)(param_1 + 0xb8) != 0)
            goto do161240;
    }
    ((void (**)(u16*))D_8018465C)[*param_1](param_1);
    ((void (*)(u16 *, int))func_80147078)(param_1, 0);
    ((void (*)(u16 *))func_80159B70)(param_1);
    return;
do161240:
    ((void (*)(u16 *))func_80161240)(param_1);
}


DEFINE_func_8015CB94()  /* dedup: shared engine-core @0x8015cb94 (src/shared) */


void func_8015CBCC(void) {
}

void func_8015CBD4(void) {
}

void func_8015CBDC(void) {
}

void func_8015CBE4(void) {
}

void func_8015CBEC(void) {
}

void func_8015CBF4(void) {
}

void func_8015CBFC(void) {
}

void func_8015CC04(void) {
}

DEFINE_func_8015CC0C()  /* dedup: shared engine-core @0x8015cc0c (src/shared) */


DEFINE_func_8015CC40()  /* dedup: shared engine-core @0x8015cc40 (src/shared) */




void func_8015CC74(s32 *a0) {

    extern void (*D_801847F8[])(void);
    D_801847F8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015ccb0 (src/shared) */


DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015ccd0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015CD20);

DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015cf24 (src/shared) */


DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015cf58 (src/shared) */


DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015cf8c (src/shared) */




void func_8015CFC0(s32 *a0) {

    extern void (*D_80184830[])(void);
    D_80184830[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015cffc (src/shared) */


extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80154274(s32 *a0, s32 a1);

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_80184820;

    int iVar4;
    register unsigned short uVar1 __asm__("$19");
    register unsigned short uVar5 __asm__("$17");
    short sVar2;
    short sVar3;

    ((void (*)(int, void *))func_80154274)(param_1, &D_800D550C);
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    iVar4 = *(short *)(*(int *)(param_1 + 0x20) + 0x12);
    uVar1 = *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x180) + 0x20) + 0x12);
    uVar5 = (uVar1 + 0x800) & 0xfff;
    sVar2 = func_80012A60(iVar4, (short)uVar1);
    sVar3 = func_80012A60(iVar4, uVar5);
    if (sVar2 < sVar3) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar1;
    } else {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) = uVar5;
    }
    *(int *)(param_1 + 0x38) = (int)&D_80184820 | 0x40000000;
    ((void (*)(int))func_801725F4)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
}




// @class: struct
// @stuck: none — MATCH (pending gate)

extern s32 func_80149FB0(s32 a0);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015D104(void *arg0) {

    extern void (*D_8018465C[])(void *);
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((void (*)(void *))func_801725F4)(arg0);
        *(s32 *)((u8 *)arg0 + 0x234) = 0xFF1D0000;
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10) = 0x600;
        *(u16 *)((u8 *)arg0 + 0x244) = *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x10);
        func_80146CA0(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015D1B8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015D380);


// @class: plumbing
// @stuck: none — MATCH


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{

    extern unsigned char D_80183970[];
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_80183970;
    *(short *)(param_1 + 0x138) = 0;
    *(short *)(param_1 + 0x13a) = 0;
    *(short *)(param_1 + 0x13c) = 0;
    *(short *)(param_1 + 0x13e) = 0;
    *(short *)(param_1 + 0xA) = *(short *)(param_1 + 0xA) + 0x48;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    ((void (*)(void))func_801553C0)();
    func_80154A74(param_1, 0x11);
}


DEFINE_func_8015D480()  /* dedup: shared engine-core @0x8015d480 (src/shared) */


DEFINE_func_8015D4B4()  /* dedup: shared engine-core @0x8015d4b4 (src/shared) */




s32 func_8015D4E8(s16 *a0) {

    extern void (*D_80184894[])(void);
    D_80184894[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015D524()  /* dedup: shared engine-core @0x8015d524 (src/shared) */


DEFINE_func_8015D544()  /* dedup: shared engine-core @0x8015d544 (src/shared) */


DEFINE_func_8015D57C()  /* dedup: shared engine-core @0x8015d57c (src/shared) */



// @class: loose-typing
// @stuck: none — MATCH (field 0xb8 compared as u16 == 0x8000, not s16 == -0x8000)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154A74(int, int);
extern s32 func_80161208();
extern void func_80154150(int, int);
extern void func_80146CA0(void *a0);
extern void func_80149374(int, int);


void func_8015D5E8(int param_1)
{

    extern unsigned char D_801848A0[];
    int iVar1;
    int iVar2;

    if (((int (*)(void))func_80161B18)() != 0)
        return;
    if (((int (*)(int))func_80161B84)(param_1) != 0)
        return;
    if ((*(unsigned short *)(param_1 + 0xb8) & 0x4000) != 0)
        func_80154A74(param_1, 0x17);
    if (((int (*)(int))func_80161208)(param_1) != 0)
        return;
    if (*(unsigned short *)(param_1 + 0xb8) == 0x8000) {
        *(int *)(param_1 + 0x234) = *(int *)(param_1 + 0x234) + -3;
        func_80154150(param_1, 0x1a);
        ((void (*)(int))func_80146CA0)(param_1);
    } else {
        iVar1 = *(int *)(param_1 + 0x178);
        if (iVar1 != 0) {
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 6) =
                (short)((signed char)D_801848A0[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xc));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 10) =
                (short)((signed char)D_801848A0[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xe));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 0xe) =
                (short)((signed char)D_801848A0[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0x10));
            func_80149374(param_1, iVar1 + 4);
        }
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015D738);

DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015da5c (src/shared) */


DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015da90 (src/shared) */


DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015dac4 (src/shared) */




void func_8015DAF8(s32 *a0) {

    extern void (*D_801848D4[])(void);
    D_801848D4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015db34 (src/shared) */


DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015db6c (src/shared) */


extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015DCB8)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DC84()  /* dedup: shared engine-core @0x8015dc84 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {

    extern s8 D_801848DC[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015dd74 (src/shared) */


DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015ddf0 (src/shared) */


DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015de24 (src/shared) */




void func_8015DE58(s32 *a0) {

    extern void (*D_801848F4[])(void);
    D_801848F4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015de94 (src/shared) */


DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015decc (src/shared) */


extern void func_8015F89C(void *arg0);
extern void func_8015F9A4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

void func_8015DF34(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015E0D4)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015E018)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015DFE4()  /* dedup: shared engine-core @0x8015dfe4 (src/shared) */



// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_8015E018(s32 param_1) {

    extern s8 D_801848DC[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_801848DC[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015e0d4 (src/shared) */


DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015e150 (src/shared) */


DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015e184 (src/shared) */




s32 func_8015E1B8(s32 a0) {

    extern void (*D_80184914[])(void);
    D_80184914[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015E1F4()  /* dedup: shared engine-core @0x8015e1f4 (src/shared) */


DEFINE_func_8015E22C()  /* dedup: shared engine-core @0x8015e22c (src/shared) */


DEFINE_func_8015E288()  /* dedup: shared engine-core @0x8015e288 (src/shared) */



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); fn-ptr table folds %lo via extern array, 0x234 single word store


extern void func_8015E40C(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161208();
extern void func_8015E5B0(u8*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);


void func_8015E344(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    ((s32 (*)(void))func_8015E40C)();
    if (((s32 (*)(u16 *))func_80161B18)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161B84)(param_1) == 0 &&
        ((s32 (*)(u16 *))func_80161208)(param_1) == 0) {
        if ((param_1[0x5c] & 0x4000) != 0) {
            ((void (*)(u16 *))func_8015E5B0)(param_1);
            *(s32 *)((char *)param_1 + 0x234) = 1;
        }
        if ((param_1[0x5c] & 0x8000) != 0) {
            ((void (**)(u16*))D_8018465C)[param_1[0]](param_1);
            ((s32 (*)(u16 *, s32))func_80147078)(param_1, 0);
            ((s32 (*)(u16 *))func_80159BE4)(param_1);
        }
    }
}


DEFINE_func_8015E40C()  /* dedup: shared engine-core @0x8015e40c (src/shared) */



// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check


extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8015E4B0(s32 param_1)
{

    extern u16 D_80184924;
    extern u16 D_80184926;
    extern u16 D_80184928;
    extern s32 D_8018492C;
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_80184924 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_80184926 + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_80184928 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_8018492C, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015E588);

DEFINE_func_8015E5B0()  /* dedup: shared engine-core @0x8015e5b0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (clean -O2 reconstruction; table-of-fnptr indexed by param_1[0])


extern s32 func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

/* function-pointer dispatch table */

void func_8015E698(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    if (func_80161208() == 0 && (param_1[0x5c] & 0x8000) != 0) {
        ((void (**)(u16*))D_8018465C)[param_1[0]](param_1);
        ((void (*)(u16 *, s32))func_80147078)(param_1, 0);
        ((void (*)(u16 *))func_80159BE4)(param_1);
    }
}


DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015e714 (src/shared) */


DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015e84c (src/shared) */


DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015e880 (src/shared) */


DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015e8b4 (src/shared) */




void func_8015E8E8(s32 *a0) {

    extern void (*D_80184948[])(void);
    D_80184948[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015e924 (src/shared) */


DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015e95c (src/shared) */


DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015e9b8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015EA3C);

DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ed6c (src/shared) */


DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015eda0 (src/shared) */


DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015edd4 (src/shared) */




s32 func_8015EE08(s32 a0) {

    extern void (*D_80184950[])(void);
    D_80184950[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015EE44()  /* dedup: shared engine-core @0x8015ee44 (src/shared) */



// @class: plumbing
// @stuck: none — MATCH (straight STUB call sequence; param saved to $s0 across calls)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);


void func_8015EE7C(s32 param_1)
{

    extern int D_800D4C48;
    extern int D_80184640;
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_80184640);
    ((int (*)(int, int))func_801477E8)(param_1, 0xFFF40000);
    ((int (*)(int))func_80146CA0)(param_1);
}




extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161418(void *a0);
extern s32 func_801725A4(u8 *a0);

void func_8015EEE0(void *arg0)
{

    extern void (*D_8018465C[])(void *);
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (((s32 (*)(void *))func_80161418)(arg0) == 0) {
            ((void (*)(void *))func_801725A4)(arg0);
        }
    }
}


void func_8015EF9C(void) {
}

DEFINE_func_8015EFA4()  /* dedup: shared engine-core @0x8015efa4 (src/shared) */


DEFINE_func_8015EFD8()  /* dedup: shared engine-core @0x8015efd8 (src/shared) */




void func_8015F00C(s32 *a0) {

    extern void (*D_80184958[])(void);
    D_80184958[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015f048 (src/shared) */


DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015f080 (src/shared) */


extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8014AB5C(void);
extern void func_80159B70(void *a0);
extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern s32 func_80161208(void);
extern int func_80155FF8(int arg, int a1);

void func_8015F118(void *a0) {

    extern s32 D_80062BE8;
    extern void (*D_8018465C[])(void *);
    u16 flag;

    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        (*D_8018465C[*(u16 *)a0])(a0);
        ((void (*)(void *, s32))func_80147078)(a0, 0);
        func_80159B70(a0);
    } else {
        if (flag & 0x4000) {
            ((void (*)(s32))func_8014AB5C)(0x19);
            ((void (*)(s32))func_8014AB5C)(0x1D);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_801466F0(0x19, (s32)a0, 0, 0, 0, 1, 0, 1);
            func_801466F0(0x1D, (s32)a0, 0, 0, 0, 0, 0, 1);
            func_80019064(&D_80062BE8);
            func_80147324(0x9DA);
        }
        if (((s32 (*)(s32 *))func_80161208)(a0) == 0) {
            func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA));
        }
    }
}


DEFINE_func_8015F260()  /* dedup: shared engine-core @0x8015f260 (src/shared) */


DEFINE_func_8015F2BC()  /* dedup: shared engine-core @0x8015f2bc (src/shared) */


DEFINE_func_8015F2F0()  /* dedup: shared engine-core @0x8015f2f0 (src/shared) */




void func_8015F324(s32 *a0) {

    extern void (*D_80184960[])(void);
    D_80184960[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015f360 (src/shared) */


DEFINE_func_8015F380()  /* dedup: shared engine-core @0x8015f380 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015F448);

DEFINE_func_8015F738()  /* dedup: shared engine-core @0x8015f738 (src/shared) */


DEFINE_func_8015F76C()  /* dedup: shared engine-core @0x8015f76c (src/shared) */


DEFINE_func_8015F7A0()  /* dedup: shared engine-core @0x8015f7a0 (src/shared) */




s32 func_8015F7D4(s32 a0) {

    extern void (*D_80184998[])(void);
    D_80184998[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015F810()  /* dedup: shared engine-core @0x8015f810 (src/shared) */


DEFINE_func_8015F848()  /* dedup: shared engine-core @0x8015f848 (src/shared) */



extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208(void);

void func_8015F89C(void *arg0) {

    extern void (*D_8018465C[])(void *);
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_8018465C[*(u16 *)arg0](arg0);
            func_80147078(arg0, 0);
            func_80159B70(arg0);
            return;
        }
    } else {
        func_801466F0(1, arg0, 0, -0x1E, 0, 0, 0, 0);
    }
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_8015F948()  /* dedup: shared engine-core @0x8015f948 (src/shared) */



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208(void);

void func_8015F9A4(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_8018465C[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}


DEFINE_func_8015FA24()  /* dedup: shared engine-core @0x8015fa24 (src/shared) */


DEFINE_func_8015FA44()  /* dedup: shared engine-core @0x8015fa44 (src/shared) */


DEFINE_func_8015FA78()  /* dedup: shared engine-core @0x8015fa78 (src/shared) */




void func_8015FAAC(s32 *a0) {

    extern void (*D_801849A4[])(void);
    D_801849A4[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {

    extern void (*D_8018465C[])(void *);
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_8018465C[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 4);
        ((void (*)(void *))func_8015C0C4)(arg0);
    } else {
        ((void (*)(void *))func_8015FBE0)(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8015FBE0);

extern void func_801599A4(void *a0);

// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)


extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8015FCC8(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018465C[])(void *);
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018465C[*(u16 *)param_1](param_1);
        ((void (*)(void *, s32))func_80147078)(param_1, 0);
        func_80159B70(param_1);
    } else {
        *(u8 *)((s32)param_1 + 0x197) = 0;
        *(u8 *)((s32)param_1 + 0xBE) = 0;
        *(u8 *)((s32)param_1 + 0xBF) = 0;
        *(u8 *)((s32)param_1 + 0x1A0) = (u8)*(s32 *)((s32)param_1 + 0x184);
        ((s32 (*)(void *, s32))func_8014BFF4)(param_1, 1);
        func_80146CA0(param_1);
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple 3-call sequence with global table index


extern void func_80147324(s32 arg0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_8015FD74(int param_1)
{

    extern unsigned int D_801849B8[];
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_801849B8[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_8015FDCC()  /* dedup: shared engine-core @0x8015fdcc (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr-table dispatch + ushort struct fields)


extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80161208();

void func_8015FE70(u16 *param_1)
{

    extern void (*D_8018465C[])(void*);
    if ((param_1[0x5c] & 0x8000) != 0) {
        if (param_1[0x5d] == 0) {
            ((void (**)())D_8018465C)[param_1[0]]();
            ((void (*)(u16 *, s16))func_80147078)(param_1, 0);
            ((void (*)(u16 *))func_80159B70)(param_1);
            return;
        }
        param_1[0x5c] = param_1[0x5d];
    }
    if ((param_1[0x5c] & 0x4000) != 0) {
        ((void (*)(u16 *, s16))func_80154A74)(param_1, 0x11);
    }
    ((void (*)(u16 *))func_80161208)(param_1);
}




extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);

void func_8015FF20(void *param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018465C[])(void *);
    extern u8 D_80078EC1;
    extern u8 D_80078EC2;
    extern u16 D_801270C0;
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_8018465C[*(u16 *)param_1](param_1);
        ((void (*)(void *, s16))func_80147078)(param_1, 0);
        func_80159B70(param_1);
        return;
    }

    v2 = *(s32 *)((s32)param_1 + 0x184);
    if (v2 < 0) {
        func_80150820((s32)param_1, func_801656E8((s32)param_1, v2 & 0xFF) & 0xFF);
    } else {
        if (*(u8 *)((s32)param_1 + 0x1A0) != *(u8 *)((s32)param_1 + 0x196)) {
            *(u8 *)((s32)param_1 + 0x1A0) = (u8)v2;
            *(u8 *)((s32)param_1 + 0x197) = 0;
            *(u8 *)((s32)param_1 + 0xBE) = 0;
            *(u8 *)((s32)param_1 + 0xBF) = 0;
            func_8014BFF4((s32)param_1, 1);
        }

        cur = *(u8 *)((s32)param_1 + 0x1A0);
        D_80078EC1 = cur;
        D_80078EC2 = cur;
        func_80165670((s32)param_1, cur);
        ((void (*)(void *))func_80165840)(param_1);
        ((void (*)(void *))func_801658DC)(param_1);
        func_80154A74((s32)param_1, 0x11);
        D_801270C0 = 1;
    }

    ((void (*)(void *))func_8016004C)(param_1);
}


DEFINE_func_8016004C()  /* dedup: shared engine-core @0x8016004c (src/shared) */


DEFINE_func_8016007C()  /* dedup: shared engine-core @0x8016007c (src/shared) */


DEFINE_func_801600D0()  /* dedup: shared engine-core @0x801600d0 (src/shared) */


DEFINE_func_80160104()  /* dedup: shared engine-core @0x80160104 (src/shared) */




void func_80160138(s32 *a0) {

    extern void (*D_80184A34[])(void);
    D_80184A34[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160174()  /* dedup: shared engine-core @0x80160174 (src/shared) */


DEFINE_func_801601AC()  /* dedup: shared engine-core @0x801601ac (src/shared) */


DEFINE_func_801601E4()  /* dedup: shared engine-core @0x801601e4 (src/shared) */


DEFINE_func_80160244()  /* dedup: shared engine-core @0x80160244 (src/shared) */



extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_801602A4(s32 *a0) {

    extern void (*D_8018465C[])(void*);
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        ((void (**)())D_8018465C)[*(u16 *)a0]();
        func_80154A74((s32)a0, 0x11);
        ((void (*)(s32, s32))func_80147078)((s32)a0, 0);
        func_80159B70(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}


void func_8016032C(void) {
}

DEFINE_func_80160334()  /* dedup: shared engine-core @0x80160334 (src/shared) */


DEFINE_func_80160368()  /* dedup: shared engine-core @0x80160368 (src/shared) */




void func_8016039C(s32 *a0) {

    extern void (*D_80184A44[])(void);
    D_80184A44[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603d8 (src/shared) */


DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80160534);

DEFINE_func_801607B8()  /* dedup: shared engine-core @0x801607b8 (src/shared) */


DEFINE_func_801607E4()  /* dedup: shared engine-core @0x801607e4 (src/shared) */


DEFINE_func_80160818()  /* dedup: shared engine-core @0x80160818 (src/shared) */




void func_8016084C(s32 *a0) {

    extern void (*D_80184A4C[])(void);
    D_80184A4C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */


DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608c0 (src/shared) */



// @class: struct
// @stuck: none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)

typedef void (*code)(unsigned short *);


extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_80160920(unsigned short *param_1)
{

    extern void (*D_8018465C[])(void*);
    if ((((int (*)(void))func_801487F4)() & 8) == 0) {
        ((code *)D_8018465C)[*param_1](param_1);
        ((void (*)(unsigned short *))func_80160A74)(param_1);
    } else {
        if (((int (*)(unsigned short *))func_80161208)(param_1) == 0 && param_1[0x5c] == 0x8000) {
            ((void (*)(unsigned short *, int))func_80154150)(param_1, 0x25);
            ((void (*)(unsigned short *))func_80146CA0)(param_1);
        }
    }
    return;
}




// @class: struct
// @stuck: none — MATCH (pending byte-gate); function-pointer table %lo-fold via extern array


extern u16 func_801487F4(s32 *a0);
extern void func_80160A74(s32 *a0);
extern s32 func_80161208();

/* function-pointer dispatch table; indexed by *param_1 (×4 = ptr size) */

void func_801609B8(u16 *param_1) {

    extern void (*D_8018465C[])(void*);
    if ((((u32 (*)(void))func_801487F4)() & 8) == 0) {
        ((void (**)(u16*))D_8018465C)[*param_1](param_1);
        ((void (*)(u16 *))func_80160A74)(param_1);
    } else {
        ((void (*)(u16 *))func_80161208)(param_1);
    }
}


DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160a28 (src/shared) */


DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160a74 (src/shared) */


DEFINE_func_80160ACC()  /* dedup: shared engine-core @0x80160acc (src/shared) */


DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160b00 (src/shared) */




s32 func_80160B34(s32 a0) {

    extern void (*D_80184A58[])(void);
    D_80184A58[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160b70 (src/shared) */


DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160bb4 (src/shared) */


DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160c28 (src/shared) */


DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160cb4 (src/shared) */


extern void func_8015DBD4(void *arg0);

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_8018465C + func_80147078/func_80159B70 tail, func_80161208 else)

extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {

    extern void (*D_8018465C[])(void *);
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_8018465C[*(u16 *)arg0](arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x1AC) == 0) {
            if ((((s32 (*)(void *))func_80148800)(arg0) & 0xF0) == 0) {
                goto dd0;
            }
        } else {
            s32 t = *(s32 *)((u8 *)arg0 + 0x1AC) - 0xAAA8;
            *(s32 *)((u8 *)arg0 + 0x1AC) = t;
            if (t >= 0) {
                goto dd0;
            }
        }
        D_8018465C[*(u16 *)arg0](arg0);
    }
    ((void (*)(void *, s16))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
dd0:
    ((s32 (*)(void *))func_80161208)(arg0);
}


DEFINE_func_80160DEC()  /* dedup: shared engine-core @0x80160dec (src/shared) */


DEFINE_func_80160E3C()  /* dedup: shared engine-core @0x80160e3c (src/shared) */


DEFINE_func_80160E70()  /* dedup: shared engine-core @0x80160e70 (src/shared) */




void func_80160EA4(void *a0) {

    extern void (*D_80184A68[])(void);
    D_80184A68[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80160EE0()  /* dedup: shared engine-core @0x80160ee0 (src/shared) */


DEFINE_func_80160F00()  /* dedup: shared engine-core @0x80160f00 (src/shared) */


DEFINE_func_80160F70()  /* dedup: shared engine-core @0x80160f70 (src/shared) */


DEFINE_func_80160FE0()  /* dedup: shared engine-core @0x80160fe0 (src/shared) */



// @class: struct
// @stuck: none — MATCH

extern void func_80149020(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

void func_80161034(void *a0)
{

    extern void (*D_8018465C[])(void *);
    func_80149020(a0);
    D_8018465C[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}


DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */


void func_801610FC(void) {
}

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */


DEFINE_func_80161124()  /* dedup: shared engine-core @0x80161124 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161208);

DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */


DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */


DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612b8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016130C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161374);

DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */


DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */


DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */


DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614e4 (src/shared) */


DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151c (src/shared) */


DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */


DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158c (src/shared) */


DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615c4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016163C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161774);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161888);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016191C);

DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197c (src/shared) */


DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619a4 (src/shared) */


DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619d0 (src/shared) */


DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161a00 (src/shared) */


DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161a30 (src/shared) */


DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161a60 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161A90);

DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161b18 (src/shared) */


DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161b84 (src/shared) */


DEFINE_func_80161BE0()  /* dedup: shared engine-core @0x80161be0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161C24);


// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern void func_80147324(s32 arg0);

void func_80161C98(int param_1, u32 param_2)
{

    extern u16 D_80184A98[];
    if (param_2 < 8) {
        func_80147324(D_80184A98[param_2]);
    }
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161CD0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80161D20);

DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161d58 (src/shared) */



// @class: other
// @stuck: none — MATCH (short-circuit && chain; reused 0x80FFFFFF mask const, andi-0xFF on callee ret)

extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800D1734(void *);

void func_80161D88(void) {

    extern s32 D_800AE6B0;
    extern s32 D_800AE6A8;
    extern s32 D_80184AFC;
    if ((D_800AE6B0 & 0x80FFFFFF) == 0 && (D_800AE6A8 & 0x80FFFFFF) == 0 &&
        (func_80029178(0x141) & 0xFF) != 0) {
        func_80029124(0x141, 0);
        func_80029124(0x95, 1);
        func_800D1734(&D_80184AFC);
    }
}


extern s32 func_800291DC(s32);







void func_80161E08(s32 param_1) {

    extern u8 D_800AF630[];
    extern void func_80024054(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern void func_800242D0(s32 a0, void *a1, s32 a2);
    extern void func_8001CE68(void *a0, void *a1);
    extern int func_801620C4(void);
    extern void func_801622C4(void);
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_80078EB0;
    extern u16 D_800B5BD8;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern u16 D_800B5C10;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern u16 D_800B5C48;
    extern s16 D_800B5C74;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern u8 * D_801A6BA8[];
    extern u8 D_80184AC8[];
    extern u8 D_80184AE8[];
    extern u8 D_801A6BB4[];
    extern u8 D_801A6BDC[];
    extern u8 D_801A6BF4[];

    u8 *base = &(*(u8 *)&D_800AF630);
    u8 *p;
    s32 a2;

    if (*((u16 *)param_1) != 0x1A &&
        currentLocationId != 0x3012 &&
        currentLocationId != 0x3054 &&
        currentLocationId != 0x3079 &&
        currentLocationId != 0x3096 &&
        ((a2 = func_800291DC(8)) & 0x8000) != 0) {

        if (D_800B5BD8 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65A8));
            D_801A6BA8[0] = p;
            func_80024054(&D_80184AC8, &D_801A6BB4);
            func_8001CE28(p, &D_801A6BB4);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_801A6BA8[1] = p;
            func_80024054(&D_80184AE8, &D_801A6BDC);
            func_8001CE28(p, &D_801A6BDC);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_801A6BA8[2] = p;
            func_800242D0((s16)func_801620C4(), &D_801A6BF4, 0x84);
            func_8001CE68(p, &D_801A6BF4);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_801A6BF4, 0x84);
        if ((a2 & 0x7FFF) == (s32)D_80078EB0) {
            func_801622C4();
        }
    }
}


DEFINE_func_801620C4()  /* dedup: shared engine-core @0x801620c4 (src/shared) */


DEFINE_func_80162120()  /* dedup: shared engine-core @0x80162120 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_8016216C(void)
{

    extern int D_801A6BA8[];
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_801A6BA8;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}



extern s32 func_800291DC(s32);

s32 func_801621CC(s32 arg0) {

    extern u8 D_80078E78[];
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    extern s32 D_80184AFC;
    register s32 s0 __asm__("$16") = arg0;       /* $s0: arg0, crosses the call */
    register u8 *s1 __asm__("$17") = D_80078E78; /* $s1: base, hoisted for the loop */
    register s32 i __asm__("$5");                /* $a1: counter (pin fixes the i/d swap) */
    u32 a2;
    s32 d;                                       /* $a0: natural alloc; load via $v0 temp */
    s32 v, last, hi, lo;
    char pad[8];                                 /* phantom 8B local -> frame 0x28 (vars=8) */

    a2 = func_800291DC(8);
    if ((a2 & 0x8000) == 0) {
        return 0;
    }
    a2 &= 0x7FFF;
    if (((a2 >> 8) == D_80078EB1) && ((a2 & 0xFF) <= (u32)D_80078EB0)) {
        return (s32)&D_80184AFC;
    }
    d = s1[0x39] - 1;
    i = 0;
    if (s0 <= 0) {
        return 0;
    }
    hi = (a2 >> 8) & 0xFF;
    last = s0 - 1;
    lo = a2 & 0xFF;
    do {
        if ((s8)d < 0) {
            d = 0x17;
        }
        v = (s8)d;
        if (hi == v) {
            if (i != last) {
                return (s32)&D_80184AFC;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_80184AFC;
            }
            goto bot;
        }
        i++;
    bot:
        d--;
    } while (i < s0);
    return 0;
}



// @class: schedule
// @stuck: none — MATCH
extern void func_80029124(s32, s32);
extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

void func_801622C4(void)
{

    extern int D_801A6BA8[];
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_801A6BA8;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}




void func_80162330(void *a0) {

    extern void (*D_80184B20[])(void);
    D_80184B20[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236c (src/shared) */


DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623b8 (src/shared) */


DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */


extern s32 func_800291DC(s32);








s32 func_80162438(s32 _unused0) {

    extern s16 D_80078EB0;
    extern u8 D_800AF630[];
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_80184B2C[];
    extern s32 D_80184B44;
    extern u8 D_801A6C0C[];
    extern u8 D_801A6C34[];
    extern u8 D_801A6C50[];
    extern int D_801A6C00[];
    extern u16 D_800B5BD8;
    extern u16 D_800B5C10;
    extern u16 D_800B5C48;
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern s16 D_800B5C74;

    u32 uVar2;
    register u8 *base __asm__("$18");
    register u8 *item __asm__("$17");

    base = &(*(u8 *)&D_800AF630);
    uVar2 = func_800291DC(0x12);
    if ((uVar2 & 0x8000) != 0) {
        if (D_800B5BD8 == 0) {
            register u8 *t __asm__("$2") = base + 0x65A8;
            item = t;
            D_801A6C00[0] = (s32)item;
            func_80024054(D_80184B2C, D_801A6C0C);
            func_8001CE28(item, D_801A6C0C);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_801A6C00[1] = (s32)item;
            func_80024054(((u8 *)&D_80184B44), D_801A6C34);
            func_8001CE28(item, D_801A6C34);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_801A6C00[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_801A6C50, 0x84);
            func_8001CE68(item, D_801A6C50);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_801A6C50, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}


DEFINE_func_801626B8()  /* dedup: shared engine-core @0x801626b8 (src/shared) */


DEFINE_func_80162714()  /* dedup: shared engine-core @0x80162714 (src/shared) */



// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);


void func_80162760(void)
{

    extern int D_801A6C00[];
    int *p;
    int i;

    func_800291C8(18, 0);
    i = 0;
    p = D_801A6C00;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}


DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627c0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801627E8);



void func_80162834(void *a0) {

    extern void (*D_80184B68[])(void);
    D_80184B68[*(u8 *)((s32)a0 + 0x1)]();
}



// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);


void func_80162870(s32 param_1) {

    extern u8 D_800B5CB8;
    extern s32 D_80184B58;
    extern s32 D_800B5CBC;
    extern u8 D_800B5CDF;
    extern s32 D_800B5CEC;
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_80184B58, 0x250, 0x1A0);
    D_800B5CEC = param_1 + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(param_1);
    func_80162ACC((u8 *)param_1);
}


DEFINE_func_801628F4()  /* dedup: shared engine-core @0x801628f4 (src/shared) */


DEFINE_func_80162968()  /* dedup: shared engine-core @0x80162968 (src/shared) */


DEFINE_func_80162AC0()  /* dedup: shared engine-core @0x80162ac0 (src/shared) */


DEFINE_func_80162ACC()  /* dedup: shared engine-core @0x80162acc (src/shared) */


DEFINE_func_80162AE0()  /* dedup: shared engine-core @0x80162ae0 (src/shared) */


DEFINE_func_80162AF4()  /* dedup: shared engine-core @0x80162af4 (src/shared) */


DEFINE_func_80162B1C()  /* dedup: shared engine-core @0x80162b1c (src/shared) */


void func_80162CC4(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80162CCC);

DEFINE_func_80162D28()  /* dedup: shared engine-core @0x80162d28 (src/shared) */


DEFINE_func_80162D88()  /* dedup: shared engine-core @0x80162d88 (src/shared) */


DEFINE_func_80162DE8()  /* dedup: shared engine-core @0x80162de8 (src/shared) */


DEFINE_func_80162E48()  /* dedup: shared engine-core @0x80162e48 (src/shared) */


DEFINE_func_80162EA8()  /* dedup: shared engine-core @0x80162ea8 (src/shared) */


DEFINE_func_80162F08()  /* dedup: shared engine-core @0x80162f08 (src/shared) */


DEFINE_func_80162F60()  /* dedup: shared engine-core @0x80162f60 (src/shared) */


DEFINE_func_80162F80()  /* dedup: shared engine-core @0x80162f80 (src/shared) */


DEFINE_func_80162FA0()  /* dedup: shared engine-core @0x80162fa0 (src/shared) */


DEFINE_func_80162FC0()  /* dedup: shared engine-core @0x80162fc0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80162FF4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801630C4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80163194);

DEFINE_func_80163234()  /* dedup: shared engine-core @0x80163234 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016325C);

DEFINE_func_801632E0()  /* dedup: shared engine-core @0x801632e0 (src/shared) */


DEFINE_func_801632F0()  /* dedup: shared engine-core @0x801632f0 (src/shared) */


DEFINE_func_80163328()  /* dedup: shared engine-core @0x80163328 (src/shared) */


DEFINE_func_801633A8()  /* dedup: shared engine-core @0x801633a8 (src/shared) */



// @class: struct
// @stuck: none — MATCH (21 ins, relocation-masked)


s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    extern int func_8016345C(int, unsigned short, int, unsigned short, void *);
    extern unsigned char D_801A6448[8];

    unsigned char sp18[8];
    memcpy(sp18, D_801A6448, 8);
    return func_8016345C(((int)param_1), ((int)param_2), ((int)param_3), ((int)param_4), sp18);
}


DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345c (src/shared) */



// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)


extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{

    extern char D_801A6448[8];
    char buf[8];

    memcpy(buf, D_801A6448, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80163534);

DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */


DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636d0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80163764);

DEFINE_func_8016380C()  /* dedup: shared engine-core @0x8016380c (src/shared) */


DEFINE_func_801638A0()  /* dedup: shared engine-core @0x801638a0 (src/shared) */


DEFINE_func_80163950()  /* dedup: shared engine-core @0x80163950 (src/shared) */




void func_80163A58(void *a0) {

    extern void (*D_80184B70[])(void);
    D_80184B70[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80163A94()  /* dedup: shared engine-core @0x80163a94 (src/shared) */


DEFINE_func_80163C2C()  /* dedup: shared engine-core @0x80163c2c (src/shared) */


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern u16 func_80148800(s32 *a0);
extern void func_80149350(s32 arg0);
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
extern s32 func_8014CA00(s32 a0);
extern u16 func_80156370(u16 a0);
extern void func_80162D88(s32 *a0);

void func_80163EC8(s32 param_1) {
    extern Blk8 D_801A6450;
    extern u16 D_800B99DA;
    extern u8 func_801656D0(s32 a0, s32 a1);
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80015978(s32 a0, s32 *a1);
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

    Blk8 in;
    u16 out[4];
    s16 buf[4];
    s32 psVar6;
    s32 iVar8;
    s32 iVar7;
    register s32 uVar5 __asm__("$2");   /* PIN (flagged): uVar5 -> $v0 */
    u16 uVar4;
    u8 uVar3;

    in = D_801A6450;
    psVar6 = *(s32 *)(param_1 + 0x4c);
    iVar8 = *(s32 *)(param_1 + 0x20);
    func_80162D88((s32 *)param_1);

    if (*(s32 *)(psVar6 + 0x184) == 0) {
        uVar5 = *(s32 *)(psVar6 + 0x44);
        *(s16 *)(psVar6 + 0x18a) = 0;
        *(s16 *)(psVar6 + 0x188) = 0;
        *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
        func_80146CA0((void *)param_1);
        func_80146CA0((void *)param_1);
        return;
    }
    if (*(s16 *)(*(s32 *)(psVar6 + 0x184) + 0x36) == *(u16 *)(psVar6 + 0x194)) {
        goto LAB_matched;
    }
    *(s32 *)(psVar6 + 0x184) = 0;
    uVar5 = *(s32 *)(psVar6 + 0x44);
    *(s16 *)(psVar6 + 0x18a) = 0;
    *(s16 *)(psVar6 + 0x188) = 0;
    *(s32 *)(psVar6 + 0x44) = uVar5 & ~0x20;
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);
    return;

LAB_matched:
    *(s16 *)(psVar6 + 0x18a) = *(u16 *)(psVar6 + 0x18a) + 1;
    if ((D_800B99DA & 3) == 0) {
        if (*(s16 *)(psVar6 + 0x188) >= *(u8 *)(param_1 + 0x67)) {
            *(s16 *)(psVar6 + 0x188) = *(s16 *)(psVar6 + 0x188) - *(u8 *)(param_1 + 0x67);
        } else {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
        if (*(s16 *)(psVar6 + 0x188) < 0) {
            *(s16 *)(psVar6 + 0x188) = 0;
        }
    }

    *(s16 *)(param_1 + 0x66) = *(u16 *)(param_1 + 0x66) + 0x40;
    uVar5 = func_80148800((s32 *)psVar6);
    if ((uVar5 & 0x80) != 0) {
        *(s16 *)(param_1 + 0x66) = 0;
        uVar3 = func_801656D0(psVar6, func_8014CA00(*(s32 *)(psVar6 + 0x184)) & 0xff);
        *(s16 *)(psVar6 + 0x188) = *(u16 *)(psVar6 + 0x188) + uVar3;
        *(s16 *)(iVar8 + 0x1a) = 0x4000;
        *(s16 *)(iVar8 + 0x18) = 0x4000;
        *(s32 *)(iVar8 + 0x48) = *(s16 *)(param_1 + 0x58);
        *(s32 *)(iVar8 + 0x4c) = *(s16 *)(param_1 + 0x5a);
        *(s32 *)(iVar8 + 0x50) = *(s16 *)(param_1 + 0x5c);
        ((void (*)(s32, s32, s32))func_80149350)(param_1, (s32)&in, (s32)out);
        *(s16 *)(param_1 + 0x6) = out[0];
        *(s16 *)(param_1 + 0xa) = out[1];
        *(s16 *)(param_1 + 0xe) = out[2];
    }

    if (0x80 < *(s16 *)(psVar6 + 0x188)) {
        *(s16 *)(psVar6 + 0x188) = 0x80;
    }
    if (*(s16 *)(psVar6 + 0x188) >= 0x80) {
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0xe);
            func_8014C4AC(iVar7, 0xe, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            func_80146994(0x33, param_1, 0, iVar7);
        }
    } else {
        if (*(s16 *)(psVar6 + 0x18a) < 0x80 && *(u16 *)psVar6 != 0x19) {
            goto LAB_end;
        }
        iVar7 = *(s32 *)(psVar6 + 0x184);
        if (iVar7 != 0) {
            func_80015978(iVar7 + 4, (s32 *)buf);
            buf[3] = 0;
            uVar4 = func_80156370(0x21);
            func_8014C4AC(iVar7, 0x21, uVar4, buf, *(s16 *)(iVar8 + 0x12));
            if ((*(s32 *)(iVar7 + 0xb4) & 0x40000) != 0) {
                func_8014AD30(param_1, (u16 *)buf, 0, *(s16 *)(iVar7 + 0x60));
            }
        }
    }

    uVar5 = func_8014CA00(iVar7);
    *(s32 *)(psVar6 + 0x184) = uVar5;
    if (0x1e < (u32)uVar5) {
        *(s32 *)(psVar6 + 0x184) = 0;
    }
    func_80146E90((s32 *)param_1, 0x20);
    *(s32 *)(psVar6 + 0x44) = *(s32 *)(psVar6 + 0x44) & ~0x20;
    func_80147324(0x449);
    func_80146CA0((void *)param_1);
    func_80146CA0((void *)param_1);

LAB_end:
    uVar4 = func_80012F74(*(s16 *)(iVar8 + 0x1a), 0x1800, 3, 1);
    *(s16 *)(iVar8 + 0x1a) = uVar4;
    *(s16 *)(iVar8 + 0x18) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0x6), *(s16 *)(param_1 + 0x58), 8, 1);
    *(s16 *)(param_1 + 0x6) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xa), *(s16 *)(param_1 + 0x5a), 8, 1);
    *(s16 *)(param_1 + 0xa) = uVar4;
    uVar4 = func_80012F74(*(s16 *)(param_1 + 0xe), *(s16 *)(param_1 + 0x5c), 8, 1);
    *(s16 *)(param_1 + 0xe) = uVar4;
}


DEFINE_func_80164270()  /* dedup: shared engine-core @0x80164270 (src/shared) */


DEFINE_func_801642AC()  /* dedup: shared engine-core @0x801642ac (src/shared) */


DEFINE_func_8016432C()  /* dedup: shared engine-core @0x8016432c (src/shared) */


void func_80164410(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80164418);

DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{

    extern void (*D_80184BC4[])(void);
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_80184BC4[*(u16 *)(param_1 + 2)]();
    if (iVar1 != 0) {
        ((void (*)(s32))func_80162D28)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (relocation-masked); key was `if (iVar1 != 0) { big } else { func_80164930 }` (non-zero case first → beqz, not bnez)

extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80146CA0(void *a0);
extern void func_80164930(s32 a);


void func_801647A4(int param_1) {

    extern u16 D_800DF2E0;
    extern s32 D_80184B8C;
    extern u16 D_80184BC0;
    extern s16 D_80184BBE;
    extern s16 D_80184BBC;
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_80184B8C;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_80184BC0 = 0x80;
        D_80184BBE = 0x80;
        D_80184BBC = 0x80;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(param_1 + 0x60) = 0;
        *(u16 *)(param_1 + 0x62) = 0x200;
        ((s32 (*)(s32))func_80164A74)(param_1);
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        func_80164930(param_1);
    }
}


DEFINE_func_80164864()  /* dedup: shared engine-core @0x80164864 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80164930);

DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164a74 (src/shared) */


DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164acc (src/shared) */




void func_80164BA0(void *a0) {

    extern void (*D_80184BD0[])(void);
    D_80184BD0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);


void func_80164BDC(s32 param_1)
{

    extern u8 D_801A6C60;
    extern u8 D_801A6C61;
    extern u8 D_801A6C62;
    extern u8 D_801A6C63;
    extern u8 D_801A6C64;
    extern u8 D_801A6C65;
    extern u8 D_801A6C66;
    extern u8 D_801A6C67;
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_801A6C60;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_801A6C61 = 0xf0;
        *(u8 *)base = 0xf0;
        D_801A6C62 = 0xc0;
        D_801A6C66 = 0;
        D_801A6C65 = 0;
        D_801A6C64 = 0;
        D_801A6C67 = 0;
        D_801A6C63 = 0;
        *(s16 *)(iVar1 + 0x1e) = 0xccc;
        *(s16 *)(iVar1 + 0x10) = 0x400;
        *(s16 *)(p1 + 0x60) = 0x700;
        *(s16 *)(p1 + 0x62) = -0x60;
        func_80164DD0(p1);
        ((void (*)(s32))func_80146CA0)(p1);
    } else {
        ((void (*)(s32))func_80164DB0)(p1);
    }
}


DEFINE_func_80164CD4()  /* dedup: shared engine-core @0x80164cd4 (src/shared) */


DEFINE_func_80164D4C()  /* dedup: shared engine-core @0x80164d4c (src/shared) */


DEFINE_func_80164DB0()  /* dedup: shared engine-core @0x80164db0 (src/shared) */


DEFINE_func_80164DD0()  /* dedup: shared engine-core @0x80164dd0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80164E40);



void func_80164EA4(void *a0) {

    extern void (*D_80184BE0[])(void);
    D_80184BE0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{

    extern DStruct D_801A6CAC[];
    int i;

    for (i = 7; i >= 0; i--) {
        D_801A6CAC[i].f0 = 0;
    }
    *(short *)(param_1 + 0x2e) = 0x4000;
    *(short *)(param_1 + 0x2c) = 0x4000;
    *(short *)(param_1 + 0x60) = 0;
    *(short *)(param_1 + 0x62) = 0;
    ((void (*)(int))func_80165124)(param_1);
    *(short *)(param_1 + 0x66) = 0;
    ((void (*)(int))func_80146CA0)(param_1);
}


DEFINE_func_80164F44()  /* dedup: shared engine-core @0x80164f44 (src/shared) */


DEFINE_func_80165024()  /* dedup: shared engine-core @0x80165024 (src/shared) */


DEFINE_func_80165064()  /* dedup: shared engine-core @0x80165064 (src/shared) */


DEFINE_func_801650C4()  /* dedup: shared engine-core @0x801650c4 (src/shared) */


DEFINE_func_80165124()  /* dedup: shared engine-core @0x80165124 (src/shared) */



// @class: struct
// @stuck: none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_801A6CA0[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).


typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_80165140;
typedef struct { u8 d[4]; } __attribute__((packed, aligned(1))) B4;
typedef struct { B8_80165140 a; B4 b; s32 used; } Slot;


s32 func_80165140(s32 param_1) {
    extern Slot D_801A6CA0[8];

    int i;
    Slot *p;
    for (i = 0; i < 8; i++) {
        p = &D_801A6CA0[i];
        if (p->used == 0) {
            p->used = 8;
            p->a = *(B8_80165140 *)(((u8 *)param_1) + 0x2c);
            p->b = *(B4 *)(((u8 *)param_1) + 0x50);
            return;
        }
    }
}




// @class: schedule
// @stuck: none — MATCH (pins $s2/$s1/$s0 + zero-code barrier hoists $a0 copy into beqz delay slot)

extern s32 func_80165240(s32 a0, s32 a1, s32 a2);

void func_801651B8(void * param_1)
{

    extern s32 D_801A6CA0;
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    func_80165240(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_801A6CA0;
    do {
        if (puVar1[3] != 0) {
            s32 a0v = p;
            __asm__ __volatile__("" : "=r"(a0v) : "0"(a0v));
            func_80165240(a0v, (s32)puVar1, (s32)(puVar1 + 2));
            puVar1[3] = puVar1[3] + -1;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
    } while (iVar2 < 8);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80165240);

DEFINE_func_8016533C()  /* dedup: shared engine-core @0x8016533c (src/shared) */


DEFINE_func_80165374()  /* dedup: shared engine-core @0x80165374 (src/shared) */


DEFINE_func_801653B8()  /* dedup: shared engine-core @0x801653b8 (src/shared) */


DEFINE_func_801653F4()  /* dedup: shared engine-core @0x801653f4 (src/shared) */



// @class: struct
// @stuck: none — MATCH (54 ins)

extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

void func_801654A8(s32 arg0)
{

    extern u8 D_80078E78[];
    extern u8 D_80078EC1;
    extern void (*D_80184C24[])(void);
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_80184C24[D_80078EC1 & 0x7F])(arg0);
            }
        }
    }
    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 == 0x1A) {
        return;
    }
    if (s1[0x49] == 0x19) {
        func_800CAE0C(arg0);
    }
}



// @class: struct
// @stuck: none — MATCH (function-pointer-array dispatch; & 0x80 branch + & 0x7f index fold)

extern void func_80165B28(void *a0);

void func_80165580(s32 _arg0)
{

    extern u8 D_80078EC5;
    extern u8 D_80078EC1;
    extern void (*D_80184C24[])(void);
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_80184C24[D_80078EC1 & 0x7F]();
    }
}


DEFINE_func_801655E4()  /* dedup: shared engine-core @0x801655e4 (src/shared) */


DEFINE_func_80165624()  /* dedup: shared engine-core @0x80165624 (src/shared) */




u8 func_80165658(s32 a0, s32 a1) {

    extern u8 D_80184CA0[];
    return D_80184CA0[a1 & 0x7F];
}




void func_80165670(s32 a0, s32 a1) {

    extern s32 D_80184CC0[];
    extern s32 D_80078EC8;
    D_80078EC8 = D_80184CC0[a1 & 0x7F];
}


DEFINE_func_80165694()  /* dedup: shared engine-core @0x80165694 (src/shared) */




u8 func_801656D0(s32 a0, s32 a1) {

    extern u8 D_80184D3C[];
    return D_80184D3C[a1 & 0x7F];
}




u8 func_801656E8(s32 a0, s32 a1) {

    extern u8 D_80184D5C[];
    return D_80184D5C[a1 & 0x7F];
}




u8 func_80165700(s32 a0, s32 a1) {

    extern u8 D_80184D7C[];
    return D_80184D7C[a1 & 0x7F];
}


DEFINE_func_80165718()  /* dedup: shared engine-core @0x80165718 (src/shared) */


DEFINE_func_80165770()  /* dedup: shared engine-core @0x80165770 (src/shared) */


DEFINE_func_801657A0()  /* dedup: shared engine-core @0x801657a0 (src/shared) */


DEFINE_func_801657D8()  /* dedup: shared engine-core @0x801657d8 (src/shared) */


DEFINE_func_80165840()  /* dedup: shared engine-core @0x80165840 (src/shared) */


DEFINE_func_80165874()  /* dedup: shared engine-core @0x80165874 (src/shared) */


DEFINE_func_801658DC()  /* dedup: shared engine-core @0x801658dc (src/shared) */


DEFINE_func_801658EC()  /* dedup: shared engine-core @0x801658ec (src/shared) */


DEFINE_func_80165900()  /* dedup: shared engine-core @0x80165900 (src/shared) */


DEFINE_func_80165910()  /* dedup: shared engine-core @0x80165910 (src/shared) */


DEFINE_func_80165938()  /* dedup: shared engine-core @0x80165938 (src/shared) */


DEFINE_func_80165958()  /* dedup: shared engine-core @0x80165958 (src/shared) */


DEFINE_func_80165978()  /* dedup: shared engine-core @0x80165978 (src/shared) */


DEFINE_func_80165988()  /* dedup: shared engine-core @0x80165988 (src/shared) */


DEFINE_func_801659A8()  /* dedup: shared engine-core @0x801659a8 (src/shared) */


DEFINE_func_801659B8()  /* dedup: shared engine-core @0x801659b8 (src/shared) */


DEFINE_func_801659CC()  /* dedup: shared engine-core @0x801659cc (src/shared) */




s32 func_801659DC(u8 *a0) {

    extern void (*D_80184D9C[])(void);
    D_80184D9C[*(u8 *)((s32)a0 + 0x1A0)]();
}


void func_80165A18(void) {
}

DEFINE_func_80165A20()  /* dedup: shared engine-core @0x80165a20 (src/shared) */


DEFINE_func_80165A50()  /* dedup: shared engine-core @0x80165a50 (src/shared) */


DEFINE_func_80165A78()  /* dedup: shared engine-core @0x80165a78 (src/shared) */




void func_80165AC8(void) {

    extern u8 D_80078EC1;
    extern void (*D_80184E18[])(void);
    D_80184E18[D_80078EC1 & 0x7F]();
}


void func_80165B08(void) {
}

void func_80165B10(void) {
}

void func_80165B18(void) {
}

void func_80165B20(void) {
}



void func_80165B28(void *a0) {

    extern void (*D_80184E94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_80184E94[*(u8 *)((s32)a0 + 0x197)]();
}


DEFINE_func_80165B6C()  /* dedup: shared engine-core @0x80165b6c (src/shared) */


DEFINE_func_80165BB4()  /* dedup: shared engine-core @0x80165bb4 (src/shared) */


DEFINE_func_80165BFC()  /* dedup: shared engine-core @0x80165bfc (src/shared) */


DEFINE_func_80165C58()  /* dedup: shared engine-core @0x80165c58 (src/shared) */


DEFINE_func_80165C78()  /* dedup: shared engine-core @0x80165c78 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80165CA0);


void func_80165E2C(u16 *arg0) {

    extern M2C_UNK D_801A6458;
    func_8001534C(0, &D_801A6458, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}


DEFINE_func_80165E90()  /* dedup: shared engine-core @0x80165e90 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80165FA4);



void func_80166018(void *a0) {

    extern void (*D_80184EA0[])(void);
    D_80184EA0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80166054);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801661CC);

DEFINE_func_80166244()  /* dedup: shared engine-core @0x80166244 (src/shared) */


DEFINE_func_8016629C()  /* dedup: shared engine-core @0x8016629c (src/shared) */


DEFINE_func_801662F4()  /* dedup: shared engine-core @0x801662f4 (src/shared) */


DEFINE_func_8016634C()  /* dedup: shared engine-core @0x8016634c (src/shared) */


DEFINE_func_801663A4()  /* dedup: shared engine-core @0x801663a4 (src/shared) */




void func_801663FC(void *a0) {

    extern void (*D_80184EA8[])(void);
    D_80184EA8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80166438()  /* dedup: shared engine-core @0x80166438 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801665B4);



void func_80166618(void *a0) {

    extern void (*D_80184F70[])(void);
    D_80184F70[*(u16 *)((s32)a0 + 0x2)]();
}




void func_80166654(void *a0) {

    extern void (*D_80184F80[])(void);
    D_80184F80[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80166690);

extern void func_801484B0(s32 a0, s32 a1);
extern void func_80148534(s32 a0, s32 a1);
extern void func_80149350(s32 arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);

/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_801A6D20).
 * param_2: 0=init, 1=advance(record), 2=fadeout; param_3: trail index (s16); param_4: divisor (s16).
 *
 * K&R definition: true s16 params => callee-side lazy per-use narrow/extend with raw pseudos
 * (s3/t0/s4 hold raw a1/a2/a3; first-use extension allocates IN PLACE into the arg reg), while
 * the promoted K&R type (int x4) stays compatible with the canon-sig s32 prototype in the TU.
 * Returns s32 (v0=1 when the fadeout completes, else 0) => the //@EDIT above flips the split's
 * canon-sig prototype return type, AND engine_core.h needs the once-global ec_edit (all 5 sites,
 * byte-neutral: every caller discards the result):
 *   ec_edit old: "extern void func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 *   ec_edit new: "extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 * Without the ec_edit, cc1 hard-errors (conflicting types vs the void decls in DEFINE_ macros).
 *
 * Fully block-scoped (typedefs + externs inside the body) so the crack propagates ×134 via
 * family_remap with zero file-scope footprint. No register pins.
 */
s32 func_80166994(param_1, param_2, param_3, param_4)
    s32 param_1;
    s16 param_2;
    s16 param_3;
    s16 param_4;
{
    typedef struct { s16 f0, f1, f2, f3, f4, f5; } TrailEntry;
    typedef struct { u8 flag, idx, count, timer; TrailEntry e[16]; } Trail;
    extern u8 D_801A6D20[];
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern s32 VectorNormalSS(void *a0, void *a1);

    Trail *p = &((Trail *)D_801A6D20)[param_3];
    s32 uVar6 = *(s32 *)(param_1 + 0x34);
    s16 v10[4];
    s16 v18[4];
    s16 v20[4];
    s16 v28[4];
    s16 out[4];
    s32 c;

    switch (param_2) {
    case 0:
        p->flag = 1;
        p->count = 0;
        p->idx = 0;
        p->timer = 0xf4;
        break;
    case 1:
        v20[0] = p->e[p->idx].f0;
        v20[1] = p->e[p->idx].f1;
        v20[2] = p->e[p->idx].f2;
        v28[0] = p->e[p->idx].f3;
        v28[1] = p->e[p->idx].f4;
        v28[2] = p->e[p->idx].f5;
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
        break;
    case 2: {
        u8 bVar3 = p->timer - 0x10;
        p->timer = bVar3;
        if (bVar3 < 0x10) {
            p->flag = 0;
            return 1;
        }
        {
            u8 bVar1 = p->count;
            if (bVar1 >= 2 && (bVar3 >> 4) < bVar1) {
                p->count = bVar1 - 1;
            }
        }
        return 0;
    }
    }

    if (param_3 < 2) {
        func_801484B0((s32)v10, (s32)v18);
    } else {
        func_80148534((s32)v10, (s32)v18);
    }
    func_80165FA4(uVar6, (s32)v10, (s32)v18);
    ((void (*)(s32, s32, s32))func_80149350)(uVar6, (s32)v10, (s32)v10);
    RotTransSV(v18, v18, out);

    if (param_2 != 0) {
        v20[0] = (v10[0] + v20[0]) >> 1;
        v20[1] = (v10[1] + v20[1]) >> 1;
        v20[2] = (v10[2] + v20[2]) >> 1;
        v28[0] = (v18[0] + v28[0]) >> 1;
        v28[1] = (v18[1] + v28[1]) >> 1;
        v28[2] = (v18[2] + v28[2]) >> 1;
        v20[0] = v20[0] - v28[0];
        v20[1] = v20[1] - v28[1];
        v20[2] = v20[2] - v28[2];
        VectorNormalSS(v20, v20);
        v20[0] = v28[0] + v20[0] / param_4;
        v20[1] = v28[1] + v20[1] / param_4;
        v20[2] = v28[2] + v20[2] / param_4;
        p->e[p->idx].f0 = v20[0];
        p->e[p->idx].f1 = v20[1];
        p->e[p->idx].f2 = v20[2];
        p->e[p->idx].f3 = v28[0];
        p->e[p->idx].f4 = v28[1];
        p->e[p->idx].f5 = v28[2];
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->count < 0xf) {
            p->count = p->count + 1;
        }
    }

    p->e[p->idx].f0 = v10[0];
    p->e[p->idx].f1 = v10[1];
    p->e[p->idx].f2 = v10[2];
    p->e[p->idx].f3 = v18[0];
    p->e[p->idx].f4 = v18[1];
    p->e[p->idx].f5 = v18[2];
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80166F58);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016706C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801670E4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80167540);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80167714);



void func_801678B4(void *a0) {

    extern void (*D_80184F90[])(void);
    D_80184F90[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801678F0);



void func_80167A9C(void *a0) {

    extern void (*D_80184F9C[])(void);
    D_80184F9C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80167AD8(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80167AE0);

extern s32 func_80017758(void *a0, void *a1);
extern int func_80029178(int);


// @class: schedule
// @stuck: none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);

s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2) {

    extern u16  D_800B99DA;
    extern u8   D_80184EFC[];
    extern u8   D_80184F10[];
    u8 buf[0x54];
    u8 *p;
    s16 i;

    func_80168070(arg0, ((s16 *)arg1), ((s16 *)arg2), buf);

    *(s16 *)(buf + 0x3C) = 0;
    *(s16 *)(buf + 0x34) = 0;
    *(s16 *)(buf + 0x24) = 0;
    *(s16 *)(buf + 0x2C) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    if (D_800B99DA & 1) {
        buf[0x46] = 0x58;
    } else {
        buf[0x46] = 0x48;
    }
    buf[0x45] = buf[0x46] >> 2;
    buf[0x44] = buf[0x45];
    if (((u8 (*)(s32))func_80029178)(0x81) != 0) {
        buf[0x45] = buf[0x45] << 2;
        buf[0x46] = buf[0x46] >> 1;
    }

    p = D_80184EFC;
    buf[0x42] = 0;
    buf[0x41] = 0;
    buf[0x40] = 0;
    buf[0x4A] = 0;
    buf[0x49] = 0;
    buf[0x48] = 0;
    buf[0x4E] = 0;
    buf[0x4D] = 0;
    buf[0x4C] = 0;
    *(s32 *)(buf + 0x50) = 0x50000000;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x22) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x32) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3A) = (s8)*p--;
        func_80017758(buf + 0x20, buf);
    }

    p = D_80184F10;
    *(s16 *)(buf + 0x2C) = -0x12;
    *(s16 *)(buf + 0x3A) = 0;
    *(s16 *)(buf + 0x32) = 0;
    *(s16 *)(buf + 0x22) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    buf[0x46] = buf[0x46] << 1;
    buf[0x44] = buf[0x45] = buf[0x45] << 1;

    for (i = 0; i < 4; i++) {
        *(s16 *)(buf + 0x20) = (s8)*p++;
        *(s16 *)(buf + 0x24) = (s8)*p++;
        *(s16 *)(buf + 0x30) = (s8)*p++;
        *(s16 *)(buf + 0x34) = (s8)*p++;
        *(s16 *)(buf + 0x38) = (s8)*p++;
        *(s16 *)(buf + 0x3C) = (s8)*p--;
        if (i == 2) {
            buf[0x4E] = buf[0x46];
            buf[0x4D] = buf[0x44];
            buf[0x4C] = buf[0x4D];
        } else if (i == 3) {
            buf[0x4E] = 0;
            buf[0x4D] = 0;
            buf[0x4C] = buf[0x4D];
            buf[0x42] = buf[0x46];
            buf[0x41] = buf[0x44];
            buf[0x40] = buf[0x44];
        }
        func_80017758(buf + 0x20, buf);
    }
}


extern void func_80149350(s32 arg0);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32 ratan2(s32 a0, s32 a1);
void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) {

    extern s32 D_801269A4;
    extern s32 D_801269A8;
    extern s32 D_801269AC;
    s16 mid[3];
    s16 dir[3];
    s32 pos[3];
    mid[0] = (param_2[0] + param_3[0]) >> 1;
    mid[1] = (param_2[1] + param_3[1]) >> 1;
    mid[2] = (param_2[2] + param_3[2]) >> 1;
    ((void (*)(s32, void *, void *))func_80149350)(param_1, mid, mid);
    func_800D20C0(mid, dir, 8);
    func_80017E68(mid, param_4);
    dir[0] = (u16)param_3[0] - (u16)param_2[0];
    dir[1] = (u16)param_3[1] - (u16)param_2[1];
    dir[2] = (u16)param_3[2] - (u16)param_2[2];
    ApplyMatrixSV((void *)(*(s32 *)(param_1 + 0x20) + 0x34), dir, dir);
    func_800D23D0(dir);
    RotMatrixYXZ(dir, param_4);
    pos[0] = D_801269A4 - mid[0];
    pos[1] = D_801269A8 - mid[1];
    pos[2] = D_801269AC - mid[2];
    ApplyTransposeMatrixLV(param_4, pos, pos);
    dir[2] = -ratan2(pos[0], pos[1]);
    RotMatrixYXZ(dir, param_4);
}



extern s32 func_80029178(s32 arg);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801681FC(s32 param_1) {

    extern u8 D_80184F54[];
    extern u8 D_80184F24[];
    extern u8 D_80184F25[];
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_80184F54[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80184F24[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_80184F25[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    func_80166F58(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016829C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168328);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801683D8);


extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168430(s32 param_1) {

    extern u8 D_80184F60[];
    extern u8 D_80184F38[];
    extern u8 D_80184F39[];
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_80184F60[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80184F38[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_80184F39[iVar1];
    func_80166F58(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801684B4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168540);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801685EC);

DEFINE_func_80168640()  /* dedup: shared engine-core @0x80168640 (src/shared) */


DEFINE_func_80168664()  /* dedup: shared engine-core @0x80168664 (src/shared) */




void func_80168744(void *a0) {

    extern void (*D_80184FB4[])(void);
    D_80184FB4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168780()  /* dedup: shared engine-core @0x80168780 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801687CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168828);



void func_801689D8(void *a0) {

    extern void (*D_80184FBC[])(void);
    D_80184FBC[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168A14()  /* dedup: shared engine-core @0x80168a14 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168A88);



void func_80168AA8(void *a0) {

    extern void (*D_80184FC4[])(void);
    D_80184FC4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80168AE4()  /* dedup: shared engine-core @0x80168ae4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168B70);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168BDC);



void func_80168D58(void *a0) {

    extern void (*D_80184FCC[])(void);
    D_80184FCC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168D94);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80168EC4);

DEFINE_func_80168F40()  /* dedup: shared engine-core @0x80168f40 (src/shared) */




void func_8016901C(void *a0) {

    extern void (*D_80184FD4[])(void);
    D_80184FD4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
void func_80169058(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX */
    s16 v40[16];  /* sp+0x40 MATRIX */
    register s32 v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    if ((*(s32 *)(s1 + 0x2C) & 0x2) == 0) {
        v0 = rand();
        v1 = (v0 & 0x7F) << 3;
        v0 = ((u32)(v0 & 0x7F00)) >> 5;
        __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
        v0 = v0 + 0xC00;
    } else {
        v0 = rand();
        v1 = ((v0 & 0x7F) << 3) + 0xE40;
        v0 = (((u32)(v0 & 0x7F00)) >> 5) + 0xE00;
    }
    v10[0] = v1;
    v10[1] = v0;
    __asm__ __volatile__("" : : "r"(v1), "r"(v0));
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ApplyMatrixSV(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 c = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = c + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801691B8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80169228);



void func_801693CC(void *a0) {

    extern void (*D_80184FDC[])(void);
    D_80184FDC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80169408);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016951C);

DEFINE_func_80169584()  /* dedup: shared engine-core @0x80169584 (src/shared) */


DEFINE_func_801696D8()  /* dedup: shared engine-core @0x801696d8 (src/shared) */




void func_80169830(void *a0) {

    extern void (*D_80184FE4[])(void);
    D_80184FE4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 rand(void);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
void func_8016986C(s32 a0) {
    s32 s1 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR */
    s16 v18[4];   /* sp+0x18 SVECTOR */
    s16 v20[16];  /* sp+0x20 MATRIX */
    s16 v40[16];  /* sp+0x40 MATRIX */
    s32 v1;
    s32 t;
    v10[0] = *(u16 *)(s1 + 0x6);
    v10[1] = *(u16 *)(s1 + 0xA);
    v10[2] = *(u16 *)(s1 + 0xE);
    func_800D20C0(v10, v18, 1);
    func_800D23D0(v18);
    RotMatrixYXZ(v18, (void *)(s1 + 0x38));
    v10[0] = *(u16 *)(s1 + 0x12);
    v10[1] = *(u16 *)(s1 + 0x16);
    v10[2] = *(u16 *)(s1 + 0x1A);
    RotMatrixYXZ(v10, v40);
    v1 = rand();
    v10[0] = (v1 & 0x1FC) + 0x180;
    if (*(s32 *)(s1 + 0x2C) & 0x2) {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0x200;
    } else {
        v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0xC00;
    }
    v10[2] = 0;
    RotMatrixYXZ(v10, v20);
    func_80048EAC(v40, v20);
    if ((*(s32 *)(s1 + 0x2C) & 0x1) == 0) {
        *(s32 *)(s1 + 0x2C) = 0xE00;
    } else {
        *(s32 *)(s1 + 0x2C) = 0xA00;
    }
    v10[0] = 0;
    v10[1] = 0;
    v10[2] = 0xA;
    ApplyMatrixSV(v20, v10, v10);
    *(u16 *)(s1 + 0x12) = v10[0];
    *(u16 *)(s1 + 0x16) = v10[1];
    {
        s32 tmp = *(u16 *)(s1 + 0x2);
        s32 z = (u16)v10[2];
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x2) = tmp + 1;
        *(u16 *)(s1 + 0x1A) = z;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801699D0);

DEFINE_func_80169A4C()  /* dedup: shared engine-core @0x80169a4c (src/shared) */




void func_80169B80(void *a0) {

    extern void (*D_80185098[])(void);
    D_80185098[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80169BBC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80169E44);



void func_80169F00(void *a0) {

    extern void (*D_801850A0[])(void);
    D_801850A0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80169F3C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80169FE0);



void func_8016A020(void *a0) {

    extern void (*D_801850D8[])(void);
    D_801850D8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016a05c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016A08C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016A1CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016A290);



void func_8016A700(void *a0) {

    extern void (*D_801850E4[])(void);
    D_801850E4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016A73C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016A890);

DEFINE_func_8016A8FC()  /* dedup: shared engine-core @0x8016a8fc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016AA50);



void func_8016AB30(void *a0) {

    extern void (*D_8018512C[])(void);
    D_8018512C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016AB6C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016afb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016B114);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016B234);

DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016b3f4 (src/shared) */


DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016b428 (src/shared) */


DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016b448 (src/shared) */




void func_8016B4BC(void *a0) {

    extern void (*D_801851A8[])(void);
    D_801851A8[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);

void func_8016B4F8(int param_1)
{

    extern int D_801A6FC0;
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801A6FC0);
    if (func_8016B9F8(param_1) == 0) {
        *(int *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x14) = 0;
        *(int *)(param_1 + 0x10) = 0;
        iVar1 = func_8016B834(param_1, 0);
        *(int *)(param_1 + 0x10) = iVar1;
        if (iVar1 != 0) {
            iVar1 = func_8016B834(param_1, 1);
            *(int *)(param_1 + 0x14) = iVar1;
            if (iVar1 != 0) {
                iVar1 = func_8016B834(param_1, 2);
                *(int *)(param_1 + 0x18) = iVar1;
                if (iVar1 != 0) goto success;
            }
        }
    }
    ((void (*)(int))func_8016B984)(param_1);
    return;
success:
    func_8016B91C(param_1);
    uVar2 = *(int *)(param_1 + 0x2c);
    if (uVar2 == 0) {
        uVar2 = 0xf0;
    } else {
        uVar2 = 0x2d0;
    }
    *(int *)(param_1 + 0x1c) = uVar2;
    uVar2 = *(unsigned short *)(param_1 + 2);
    uVar2 = uVar2 + 1;
    *(unsigned short *)(param_1 + 2) = uVar2;
}




// @class: schedule
// @stuck: none — MATCH

extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B984(void *a0);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);


void func_8016B5C0(s32 param_1) {

    extern s16 D_8018519C[];
    s32 iVar4;
    s32 iVar2;
    s32 iVar5;
    s16 sVar1;
    s16 *psVar5;
    s32 i;

    iVar4 = *(s32 *)(param_1 + 0x18);
    if (((s32 (*)(void))func_8016B9F8)() != 0) {
        goto L984;
    }
    sVar1 = *(s16 *)(iVar4 + 0x1a) + 0x200;
    *(s16 *)(iVar4 + 0x1a) = sVar1;
    *(s16 *)(iVar4 + 0x18) = sVar1;
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c) / 3;
    }
    iVar5 = *(s32 *)(param_1 + 0x1c) + -0x20;
    *(s32 *)(param_1 + 0x1c) = iVar5;
    if (iVar5 >= 0) {
        goto LOOP;
    }
L984:
    ((void (*)(s32))func_8016B984)(param_1);
    return;
LOOP:
    i = 0;
    psVar5 = D_8018519C;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016B6BC);


// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);


int func_8016B834(int param_1, int param_2) {

    extern int *D_801851E0[];
    extern unsigned short D_801851E8[];
    extern unsigned short D_801851F0[];
    extern unsigned char D_801A6FC8[];
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801A6FC8 + param_2 * 0x40);
    puVar3 = D_801851E0[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_801851E8[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_801851F0[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016b91c (src/shared) */


DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016b964 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016B984);


// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)

extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{

    extern s32 D_801A6FC0;
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801A6FC0, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016ba48 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016BA68);

DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016badc (src/shared) */




void func_8016BBA4(void *a0) {

    extern void (*D_801851F8[])(void);
    D_801851F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016BBE0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016BCC0);

extern void func_8016BF50(s32);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);

// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{

    extern M2C_UNK D_801A70FC;
    extern M2C_UNK D_801A7100;
    extern u8 D_801A70FD;
    extern u8 D_801A70FE;
    extern u8 D_801A7101;
    extern u8 D_801A7102;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    ((void(*)())func_8016BF50)();

    p1 = &(*(u8 *)&D_801A70FC);
    if (*p1 != 0) *p1 -= 4;
    if (D_801A70FD != 0) D_801A70FD -= 4;
    if (D_801A70FE != 0) D_801A70FE -= 4;
    p2 = &(*(u8 *)&D_801A7100);
    if (*p2 != 0) *p2 -= 4;
    if (D_801A7101 != 0) D_801A7101 -= 4;
    if (D_801A7102 != 0) D_801A7102 -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016BEA0);

DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016bf34 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016BF50);


extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_801A7088;
    func_8016BFD0(a0, a1, a2, a3, &D_801A7088);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016BFD0);



void func_8016C14C(void *a0) {

    extern void (*D_80185228[])(void);
    D_80185228[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016C188);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016C2C4);

DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016c374 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016C49C);

DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016c74c (src/shared) */


DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016c83c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016C998);



void func_8016CB84(void *a0) {

    extern void (*D_80185230[])(void);
    D_80185230[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016CBC0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016CF04);



void func_8016D19C(void *a0) {

    extern void (*D_8018524C[])(void);
    D_8018524C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016D1D8);



void func_8016D428(void *a0) {

    extern void (*D_80185254[])(void);
    D_80185254[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016d464 (src/shared) */


DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016d4dc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016D5EC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016D64C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016D688);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016D778);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016D848);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016D984);

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016da04 (src/shared) */



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);

void func_8016DA30(int param_1)
{

    extern void (*D_801852BC[])(int);
    ((void (*)(void))func_8016DBD8)();
    D_801852BC[*(unsigned short *)(param_1 + 2)](param_1);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016DA7C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016DB34);

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016dbd8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016DC20);



void func_8016DEA4(void *a0) {

    extern void (*D_801852F0[])(void);
    D_801852F0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016DEE0);



void func_8016DF20(void *a0) {

    extern void (*D_801852F8[])(void);
    D_801852F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016DF5C);

DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016e1cc (src/shared) */


DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016e26c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016E2E8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016E358);

DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016e3cc (src/shared) */


DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016e460 (src/shared) */




void func_8016E5B8(void *a0) {

    extern void (*D_8018534C[])(void);
    D_8018534C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016E5F4);

DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016e688 (src/shared) */


DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016e6e4 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016E728);

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016e778 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016E7C8);

DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016e8f0 (src/shared) */


DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016e918 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016E95C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016E9EC);


// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{

    extern u16 D_80185380[];
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_80185380[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}



// @class: loose-typing
// @stuck: none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {

    extern u8 D_80185370[];
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_80185370[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_80185380[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.


extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{

    extern u16 D_80185380[];
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_80185380[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016EC0C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016ED6C);

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ed8c (src/shared) */


DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016edbc (src/shared) */


DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016edec (src/shared) */


DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016ee40 (src/shared) */


DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016ee94 (src/shared) */


DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016ef78 (src/shared) */


DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016efa8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016EFC8);

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016f094 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016F0AC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8016F0E4);

DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016f14c (src/shared) */


DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016f1ac (src/shared) */



// @class: schedule
// @stuck: none — MATCH

extern s16 currentLocationId;

s32 func_8016F1C4(void) {

    extern s32 D_8018539C;
    extern s32 D_80126B58;
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_8018539C;
    cur = *p;
    if (cur != 0) {
        loc = currentLocationId;
        p = p + 1;
        for (;;) {
            if (loc == cur) {
                return 1;
            }
            cur = *p;
            p = p + 1;
            if (cur == 0) {
                break;
            }
        }
    }
    v = base[0x7E];
    if (((v & 0x80FFFFFF) != 0) && ((v & 0x10000000) != 0)) {
        return 0;
    }
    return base[0x7E] & 0x80FFFFFF;
}


DEFINE_func_8016F250()  /* dedup: shared engine-core @0x8016f250 (src/shared) */


DEFINE_func_8016F264()  /* dedup: shared engine-core @0x8016f264 (src/shared) */


DEFINE_func_8016F288()  /* dedup: shared engine-core @0x8016f288 (src/shared) */


DEFINE_func_8016F2A8()  /* dedup: shared engine-core @0x8016f2a8 (src/shared) */


DEFINE_func_8016F2C8()  /* dedup: shared engine-core @0x8016f2c8 (src/shared) */


DEFINE_func_8016F2EC()  /* dedup: shared engine-core @0x8016f2ec (src/shared) */


DEFINE_func_8016F30C()  /* dedup: shared engine-core @0x8016f30c (src/shared) */


DEFINE_func_8016F330()  /* dedup: shared engine-core @0x8016f330 (src/shared) */


DEFINE_func_8016F350()  /* dedup: shared engine-core @0x8016f350 (src/shared) */


DEFINE_func_8016F374()  /* dedup: shared engine-core @0x8016f374 (src/shared) */


DEFINE_func_8016F388()  /* dedup: shared engine-core @0x8016f388 (src/shared) */


DEFINE_func_8016F398()  /* dedup: shared engine-core @0x8016f398 (src/shared) */


DEFINE_func_8016F410()  /* dedup: shared engine-core @0x8016f410 (src/shared) */


DEFINE_func_8016F44C()  /* dedup: shared engine-core @0x8016f44c (src/shared) */


DEFINE_func_8016F470()  /* dedup: shared engine-core @0x8016f470 (src/shared) */


DEFINE_func_8016F494()  /* dedup: shared engine-core @0x8016f494 (src/shared) */


DEFINE_func_8016F4C4()  /* dedup: shared engine-core @0x8016f4c4 (src/shared) */


void func_8016F4F4(void) {
}

DEFINE_func_8016F4FC()  /* dedup: shared engine-core @0x8016f4fc (src/shared) */


DEFINE_func_8016F540()  /* dedup: shared engine-core @0x8016f540 (src/shared) */


DEFINE_func_8016F578()  /* dedup: shared engine-core @0x8016f578 (src/shared) */


DEFINE_func_8016F5B0()  /* dedup: shared engine-core @0x8016f5b0 (src/shared) */


DEFINE_func_8016F5E0()  /* dedup: shared engine-core @0x8016f5e0 (src/shared) */


DEFINE_func_8016F610()  /* dedup: shared engine-core @0x8016f610 (src/shared) */


DEFINE_func_8016F648()  /* dedup: shared engine-core @0x8016f648 (src/shared) */


DEFINE_func_8016F680()  /* dedup: shared engine-core @0x8016f680 (src/shared) */


DEFINE_func_8016F6B0()  /* dedup: shared engine-core @0x8016f6b0 (src/shared) */




void func_8016F6E0(void *a0) {

    extern void (*D_80185414[])(void);
    D_80185414[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016f71c (src/shared) */


DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016f764 (src/shared) */




void func_8016F798(void *a0) {

    extern void (*D_8018541C[])(void);
    D_8018541C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016f7d4 (src/shared) */


DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016f804 (src/shared) */




void func_8016F834(void *a0) {

    extern void (*D_80185424[])(void);
    D_80185424[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016f870 (src/shared) */


DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016f8ac (src/shared) */




void func_8016F8E4(void *a0) {

    extern void (*D_8018542C[])(void);
    D_8018542C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016f920 (src/shared) */


DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016f95c (src/shared) */




void func_8016F9C4(void *a0) {

    extern void (*D_80185434[])(void);
    D_80185434[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016fa00 (src/shared) */


DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016fa44 (src/shared) */




void func_8016FA84(void *a0) {

    extern void (*D_8018543C[])(void);
    D_8018543C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016fac0 (src/shared) */


DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016fb10 (src/shared) */


DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016fb50 (src/shared) */




void func_8016FB7C(void *a0) {

    extern void (*D_80185448[])(void);
    D_80185448[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016fbb8 (src/shared) */


DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016fc24 (src/shared) */


DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016fc64 (src/shared) */




void func_8016FC90(void *a0) {

    extern void (*D_80185454[])(void);
    D_80185454[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016fccc (src/shared) */


DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016fd08 (src/shared) */


DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016fd7c (src/shared) */




void func_8016FDB4(void *a0) {

    extern void (*D_80185460[])(void);
    D_80185460[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016fdf0 (src/shared) */


DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016fe2c (src/shared) */


DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016fe78 (src/shared) */


DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016fed0 (src/shared) */




void func_8016FF30(void *a0) {

    extern void (*D_80185470[])(void);
    D_80185470[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016ff6c (src/shared) */


DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016ffa8 (src/shared) */




void func_8016FFDC(void *a0) {

    extern void (*D_80185480[])(void);
    D_80185480[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */


DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */


DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700b8 (src/shared) */


DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */




void func_80170150(void *a0) {

    extern void (*D_80185488[])(void);
    D_80185488[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018c (src/shared) */


DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701c8 (src/shared) */




void func_80170240(void *a0) {

    extern void (*D_80185490[])(void);
    D_80185490[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027c (src/shared) */


DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702b8 (src/shared) */




void func_801702FC(void *a0) {

    extern void (*D_80185498[])(void);
    D_80185498[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */


DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */




void func_801703E0(void *a0) {

    extern void (*D_801854A0[])(void);
    D_801854A0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041c (src/shared) */


DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044c (src/shared) */




void func_801704B0(void *a0) {

    extern void (*D_801854A8[])(void);
    D_801854A8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704ec (src/shared) */


DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051c (src/shared) */




void func_80170548(void *a0) {

    extern void (*D_801854B0[])(void);
    D_801854B0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */


DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705c0 (src/shared) */




void func_801705F8(void *a0) {

    extern void (*D_801854B8[])(void);
    D_801854B8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */


DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */




void func_801706AC(void *a0) {

    extern void (*D_801854C0[])(void);
    D_801854C0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706e8 (src/shared) */


DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */




void func_80170748(void *a0) {

    extern void (*D_801854C8[])(void);
    D_801854C8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */


DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707d4 (src/shared) */




void func_80170810(void *a0) {

    extern void (*D_801854D0[])(void);
    D_801854D0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084c (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801708B0);

DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */


DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */


DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709b8 (src/shared) */


DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170a00 (src/shared) */


DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170a48 (src/shared) */


DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170a90 (src/shared) */




void func_80170AD8(void *a0) {

    extern void (*D_801854D8[])(void);
    D_801854D8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170b14 (src/shared) */


DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170b48 (src/shared) */


DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170b90 (src/shared) */




void func_80170BD8(void *a0) {

    extern void (*D_801854E0[])(void);
    D_801854E0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170c14 (src/shared) */


DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170c44 (src/shared) */




void func_80170C74(void *a0) {

    extern void (*D_801854E8[])(void);
    D_801854E8[*(u8 *)((s32)a0 + 0x215)]();
}


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170cb0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80170CF0);



void func_80170D68(void *a0) {

    extern void (*D_801854F0[])(void);
    D_801854F0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170da4 (src/shared) */


DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170de0 (src/shared) */




void func_80170E34(void *a0) {

    extern void (*D_801854F8[])(void);
    D_801854F8[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170e70 (src/shared) */


DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170eac (src/shared) */




void func_80170EFC(void *a0) {

    extern void (*D_80185500[])(void);
    D_80185500[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170f38 (src/shared) */


DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170f74 (src/shared) */




void func_80170FB0(void *a0) {

    extern void (*D_80185508[])(void);
    D_80185508[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170fec (src/shared) */


DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */




void func_80171064(void *a0) {

    extern void (*D_80185510[])(void);
    D_80185510[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710a0 (src/shared) */


DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710dc (src/shared) */




void func_80171120(void *a0) {

    extern void (*D_80185518[])(void);
    D_80185518[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115c (src/shared) */


DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118c (src/shared) */




void func_801711C0(void *a0) {

    extern void (*D_80185520[])(void);
    D_80185520[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711fc (src/shared) */


DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */




void func_80171260(void *a0) {

    extern void (*D_80185528[])(void);
    D_80185528[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017129C);

DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */




void func_801714E4(void *a0) {

    extern void (*D_80185530[])(void);
    D_80185530[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */


DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162c (src/shared) */


DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716ac (src/shared) */


DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717a0 (src/shared) */


DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717f4 (src/shared) */


DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */


DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */


DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801718AC);

DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */


DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */


DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196c (src/shared) */


DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197c (src/shared) */


DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */


DEFINE_func_801719A4()  /* dedup: shared engine-core @0x801719a4 (src/shared) */


DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171a04 (src/shared) */


DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171a10 (src/shared) */


DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171a1c (src/shared) */


DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171a34 (src/shared) */


DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171a44 (src/shared) */


DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171a58 (src/shared) */


DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171a6c (src/shared) */


DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171a80 (src/shared) */


DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171a88 (src/shared) */


DEFINE_func_80171AB0()  /* dedup: shared engine-core @0x80171ab0 (src/shared) */


DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171b10 (src/shared) */


DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171b44 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80171B4C);

DEFINE_func_80171C64()  /* dedup: shared engine-core @0x80171c64 (src/shared) */


DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171cc4 (src/shared) */


DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171d1c (src/shared) */


DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171d78 (src/shared) */


DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171e08 (src/shared) */


DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171ec8 (src/shared) */



extern s32 func_8017248C(s32, s32);
extern s32 ratan2(s32, s32);
extern void func_80172170(s32, s32);
extern void func_80146D90(s32);

s32 func_80171FFC(short *a0, short *a1, s32 a2)
{
    s32 r;

    r = func_8017248C((s32)a0, (s32)a1);
    if (r != 0) {
        func_80146D90((s32)a0);
        return r;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        (ratan2(a1[0] - a0[3], a1[2] - a0[7]) + 0x800) & 0xFFF;
    func_80172170((s32)a0, a2 & 0xFF);
    return 0;
}


DEFINE_func_8017209C()  /* dedup: shared engine-core @0x8017209c (src/shared) */


DEFINE_func_80172170()  /* dedup: shared engine-core @0x80172170 (src/shared) */


DEFINE_func_801722CC()  /* dedup: shared engine-core @0x801722cc (src/shared) */


DEFINE_func_80172304()  /* dedup: shared engine-core @0x80172304 (src/shared) */


DEFINE_func_80172310()  /* dedup: shared engine-core @0x80172310 (src/shared) */


DEFINE_func_80172358()  /* dedup: shared engine-core @0x80172358 (src/shared) */


DEFINE_func_801723C4()  /* dedup: shared engine-core @0x801723c4 (src/shared) */


DEFINE_func_80172414()  /* dedup: shared engine-core @0x80172414 (src/shared) */


DEFINE_func_8017248C()  /* dedup: shared engine-core @0x8017248c (src/shared) */


DEFINE_func_801724EC()  /* dedup: shared engine-core @0x801724ec (src/shared) */


DEFINE_func_8017250C()  /* dedup: shared engine-core @0x8017250c (src/shared) */


DEFINE_func_80172560()  /* dedup: shared engine-core @0x80172560 (src/shared) */


DEFINE_func_80172588()  /* dedup: shared engine-core @0x80172588 (src/shared) */


DEFINE_func_80172590()  /* dedup: shared engine-core @0x80172590 (src/shared) */


DEFINE_func_801725A4()  /* dedup: shared engine-core @0x801725a4 (src/shared) */


DEFINE_func_801725B8()  /* dedup: shared engine-core @0x801725b8 (src/shared) */


DEFINE_func_801725CC()  /* dedup: shared engine-core @0x801725cc (src/shared) */


DEFINE_func_801725E0()  /* dedup: shared engine-core @0x801725e0 (src/shared) */


DEFINE_func_801725F4()  /* dedup: shared engine-core @0x801725f4 (src/shared) */


DEFINE_func_80172608()  /* dedup: shared engine-core @0x80172608 (src/shared) */


DEFINE_func_8017261C()  /* dedup: shared engine-core @0x8017261c (src/shared) */


DEFINE_func_80172630()  /* dedup: shared engine-core @0x80172630 (src/shared) */


DEFINE_func_80172644()  /* dedup: shared engine-core @0x80172644 (src/shared) */


DEFINE_func_80172658()  /* dedup: shared engine-core @0x80172658 (src/shared) */


DEFINE_func_80172664()  /* dedup: shared engine-core @0x80172664 (src/shared) */


DEFINE_func_80172670()  /* dedup: shared engine-core @0x80172670 (src/shared) */


DEFINE_func_8017267C()  /* dedup: shared engine-core @0x8017267c (src/shared) */


DEFINE_func_80172688()  /* dedup: shared engine-core @0x80172688 (src/shared) */


DEFINE_func_80172694()  /* dedup: shared engine-core @0x80172694 (src/shared) */


DEFINE_func_801726A0()  /* dedup: shared engine-core @0x801726a0 (src/shared) */


DEFINE_func_801726AC()  /* dedup: shared engine-core @0x801726ac (src/shared) */


DEFINE_func_801726B8()  /* dedup: shared engine-core @0x801726b8 (src/shared) */


DEFINE_func_801726C4()  /* dedup: shared engine-core @0x801726c4 (src/shared) */


DEFINE_func_801726D0()  /* dedup: shared engine-core @0x801726d0 (src/shared) */


DEFINE_func_80172710()  /* dedup: shared engine-core @0x80172710 (src/shared) */


DEFINE_func_80172738()  /* dedup: shared engine-core @0x80172738 (src/shared) */


DEFINE_func_80172760()  /* dedup: shared engine-core @0x80172760 (src/shared) */


DEFINE_func_80172780()  /* dedup: shared engine-core @0x80172780 (src/shared) */




s32 func_801727D0(void *a0) {

    extern void (*D_80185540[])(void);
    D_80185540[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280c (src/shared) */


DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */


void func_8017288C(void) {
}

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */




s32 func_801728E4(void *a0) {

    extern void (*D_8018554C[])(void);
    D_8018554C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */


DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */


void func_801729A8(void) {
}

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729b0 (src/shared) */




s32 func_801729F0(void *a0) {

    extern void (*D_80185558[])(void);
    D_80185558[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172a2c (src/shared) */


DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172a8c (src/shared) */


DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172acc (src/shared) */


void func_80172B0C(void) {
}

DEFINE_func_80172B14()  /* dedup: shared engine-core @0x80172b14 (src/shared) */




s32 func_80172B44(void *a0) {

    extern void (*D_80185568[])(void);
    D_80185568[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172b80 (src/shared) */


DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172bc8 (src/shared) */


void func_80172C48(void) {
}

extern void func_80174684(void *);
extern s32 func_80172CA0(void *a0);
void func_80172C50(void *a0) {

    extern s16 D_80126B30;
    *(struct S8_80172780 *)&D_80126B30 = *(struct S8_80172780 *)a0;
    func_80174684((void *)func_80172CA0);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80172CA0);

DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172cdc (src/shared) */


DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172d14 (src/shared) */


void func_80172D60(void) {
}

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172d68 (src/shared) */




s32 func_80172DAC(void *a0) {

    extern void (*D_80185580[])(void);
    D_80185580[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172DE8()  /* dedup: shared engine-core @0x80172de8 (src/shared) */


DEFINE_func_80172E20()  /* dedup: shared engine-core @0x80172e20 (src/shared) */


void func_80172E8C(void) {
}

DEFINE_func_80172E94()  /* dedup: shared engine-core @0x80172e94 (src/shared) */


DEFINE_func_80172ED4()  /* dedup: shared engine-core @0x80172ed4 (src/shared) */


DEFINE_func_80172EFC()  /* dedup: shared engine-core @0x80172efc (src/shared) */


DEFINE_func_80172F24()  /* dedup: shared engine-core @0x80172f24 (src/shared) */


DEFINE_func_80172F4C()  /* dedup: shared engine-core @0x80172f4c (src/shared) */


DEFINE_func_80172F9C()  /* dedup: shared engine-core @0x80172f9c (src/shared) */


DEFINE_func_80172FEC()  /* dedup: shared engine-core @0x80172fec (src/shared) */


DEFINE_func_8017303C()  /* dedup: shared engine-core @0x8017303c (src/shared) */




s32 func_80173078(void *a0) {

    extern void (*D_8018558C[])(void);
    D_8018558C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730b4 (src/shared) */


DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730fc (src/shared) */


void func_8017316C(void) {
}

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */




s32 func_8017319C(void *a0) {

    extern void (*D_80185598[])(void);
    D_80185598[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731d8 (src/shared) */



extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);

void func_80173220(void * arg0)
{

    extern M2C_UNK D_80185538;
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_80185538);
    }
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x8000) {
        func_80171A1C(arg0);
        func_80174650(arg0);
    }
}


void func_80173294(void) {
}

DEFINE_func_8017329C()  /* dedup: shared engine-core @0x8017329c (src/shared) */


DEFINE_func_801732C4()  /* dedup: shared engine-core @0x801732c4 (src/shared) */


DEFINE_func_801732F4()  /* dedup: shared engine-core @0x801732f4 (src/shared) */


DEFINE_func_8017331C()  /* dedup: shared engine-core @0x8017331c (src/shared) */


DEFINE_func_8017334C()  /* dedup: shared engine-core @0x8017334c (src/shared) */


DEFINE_func_80173374()  /* dedup: shared engine-core @0x80173374 (src/shared) */


DEFINE_func_801733A4()  /* dedup: shared engine-core @0x801733a4 (src/shared) */


DEFINE_func_801733CC()  /* dedup: shared engine-core @0x801733cc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801733FC);

DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801734BC);



void func_80173544(void *a0) {

    extern void (*D_801855A4[])(void);
    D_801855A4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173580()  /* dedup: shared engine-core @0x80173580 (src/shared) */


DEFINE_func_801735B8()  /* dedup: shared engine-core @0x801735b8 (src/shared) */


DEFINE_func_801735EC()  /* dedup: shared engine-core @0x801735ec (src/shared) */


DEFINE_func_80173648()  /* dedup: shared engine-core @0x80173648 (src/shared) */


void func_801736A8(void) {
}

DEFINE_func_801736B0()  /* dedup: shared engine-core @0x801736b0 (src/shared) */




s32 func_801736FC(void *a0) {

    extern void (*D_801855B8[])(void);
    D_801855B8[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173738()  /* dedup: shared engine-core @0x80173738 (src/shared) */


DEFINE_func_80173770()  /* dedup: shared engine-core @0x80173770 (src/shared) */


void func_801737B0(void) {
}

DEFINE_func_801737B8()  /* dedup: shared engine-core @0x801737b8 (src/shared) */




s32 func_801737E8(void *a0) {

    extern void (*D_801855C4[])(void);
    D_801855C4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173824()  /* dedup: shared engine-core @0x80173824 (src/shared) */


DEFINE_func_8017385C()  /* dedup: shared engine-core @0x8017385c (src/shared) */


void func_801738D4(void) {
}

DEFINE_func_801738DC()  /* dedup: shared engine-core @0x801738dc (src/shared) */




s32 func_8017390C(void *a0) {

    extern void (*D_801855D0[])(void);
    D_801855D0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80173948()  /* dedup: shared engine-core @0x80173948 (src/shared) */


DEFINE_func_80173980()  /* dedup: shared engine-core @0x80173980 (src/shared) */


DEFINE_func_801739D8()  /* dedup: shared engine-core @0x801739d8 (src/shared) */


void func_80173A20(void) {
}

DEFINE_func_80173A28()  /* dedup: shared engine-core @0x80173a28 (src/shared) */



extern s32 func_8014C118(void*, s32, s32);
extern void func_80174684(void *);
extern s32 func_80173B4C(void*);

void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5)
{

    extern s32 D_80126B58;
    extern s32 D_80127508;
    extern s16 D_80126B30;
    extern struct S80126B38 D_80126B38;
    extern s16 D_80126B3A;
    extern s16 D_80126B3C;
    extern s16 D_8011F9C8;
    extern s16 D_80126938;
    extern s32 D_8012750C;
    s32 *s1 = &D_80126B58;
    s32 v0;

    if (a2 != 0) {
        D_80127508 = ((s32 (*)(s32, s32, s32))func_8014C118)((s32)s1, a2, (s16)a3);
    } else {
        D_80127508 = 0;
    }

    v0 = s1[8];
    __builtin_memcpy(&D_80126B30, arg5, 8);
    (*(s16 *)&D_80126B38) = a0;
    D_80126B3A = a1;
    D_80126B3C = *(u16 *)(v0 + 0x12);
    func_80174684((void *)func_80173B4C);
    D_8011F9C8 = 0;
    D_80126938 = 0;
    D_8012750C = 0;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80173B4C);

DEFINE_func_80173B88()  /* dedup: shared engine-core @0x80173b88 (src/shared) */


DEFINE_func_80173BC0()  /* dedup: shared engine-core @0x80173bc0 (src/shared) */


DEFINE_func_80173C64()  /* dedup: shared engine-core @0x80173c64 (src/shared) */


DEFINE_func_80173CB4()  /* dedup: shared engine-core @0x80173cb4 (src/shared) */


DEFINE_func_80173E1C()  /* dedup: shared engine-core @0x80173e1c (src/shared) */


DEFINE_func_80173EF8()  /* dedup: shared engine-core @0x80173ef8 (src/shared) */


DEFINE_func_80174158()  /* dedup: shared engine-core @0x80174158 (src/shared) */


DEFINE_func_80174188()  /* dedup: shared engine-core @0x80174188 (src/shared) */


DEFINE_func_801741A8()  /* dedup: shared engine-core @0x801741a8 (src/shared) */


DEFINE_func_801741EC()  /* dedup: shared engine-core @0x801741ec (src/shared) */


void func_80174274(void) {
}

DEFINE_func_8017427C()  /* dedup: shared engine-core @0x8017427c (src/shared) */




s32 func_801742A4(void *a0) {

    extern void (*D_80185600[])(void);
    D_80185600[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801742E0()  /* dedup: shared engine-core @0x801742e0 (src/shared) */


DEFINE_func_80174318()  /* dedup: shared engine-core @0x80174318 (src/shared) */


void func_80174354(void) {
}

DEFINE_func_8017435C()  /* dedup: shared engine-core @0x8017435c (src/shared) */




s32 func_80174384(void *a0) {

    extern void (*D_8018560C[])(void);
    D_8018560C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801743C0()  /* dedup: shared engine-core @0x801743c0 (src/shared) */


DEFINE_func_801743F0()  /* dedup: shared engine-core @0x801743f0 (src/shared) */


void func_80174430(void) {
}

DEFINE_func_80174438()  /* dedup: shared engine-core @0x80174438 (src/shared) */




s32 func_80174474(void *a0) {

    extern void (*D_80185618[])(void);
    D_80185618[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801744B0()  /* dedup: shared engine-core @0x801744b0 (src/shared) */


DEFINE_func_801744E0()  /* dedup: shared engine-core @0x801744e0 (src/shared) */


void func_80174524(void) {
}

DEFINE_func_8017452C()  /* dedup: shared engine-core @0x8017452c (src/shared) */


DEFINE_func_80174554()  /* dedup: shared engine-core @0x80174554 (src/shared) */


DEFINE_func_80174584()  /* dedup: shared engine-core @0x80174584 (src/shared) */


DEFINE_func_801745AC()  /* dedup: shared engine-core @0x801745ac (src/shared) */


DEFINE_func_801745DC()  /* dedup: shared engine-core @0x801745dc (src/shared) */


DEFINE_func_80174604()  /* dedup: shared engine-core @0x80174604 (src/shared) */


DEFINE_func_80174630()  /* dedup: shared engine-core @0x80174630 (src/shared) */


DEFINE_func_80174650()  /* dedup: shared engine-core @0x80174650 (src/shared) */


DEFINE_func_80174674()  /* dedup: shared engine-core @0x80174674 (src/shared) */


DEFINE_func_80174684()  /* dedup: shared engine-core @0x80174684 (src/shared) */


DEFINE_func_801746A4()  /* dedup: shared engine-core @0x801746a4 (src/shared) */


DEFINE_func_801746DC()  /* dedup: shared engine-core @0x801746dc (src/shared) */


DEFINE_func_80174714()  /* dedup: shared engine-core @0x80174714 (src/shared) */


DEFINE_func_80174754()  /* dedup: shared engine-core @0x80174754 (src/shared) */


DEFINE_func_80174764()  /* dedup: shared engine-core @0x80174764 (src/shared) */


DEFINE_func_80174774()  /* dedup: shared engine-core @0x80174774 (src/shared) */


DEFINE_func_80174784()  /* dedup: shared engine-core @0x80174784 (src/shared) */


DEFINE_func_801747AC()  /* dedup: shared engine-core @0x801747ac (src/shared) */




s32 func_801747CC(void *a0) {

    extern void (*D_80185624[])(void);
    D_80185624[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80174808()  /* dedup: shared engine-core @0x80174808 (src/shared) */


void func_8017481C(void) {
}

DEFINE_func_80174824()  /* dedup: shared engine-core @0x80174824 (src/shared) */


DEFINE_func_8017484C()  /* dedup: shared engine-core @0x8017484c (src/shared) */




s32 func_80174888(void *a0) {

    extern void (*D_8018562C[])(void);
    D_8018562C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801748C4()  /* dedup: shared engine-core @0x801748c4 (src/shared) */


void func_801748E4(void) {
}

DEFINE_func_801748EC()  /* dedup: shared engine-core @0x801748ec (src/shared) */




s32 func_8017496C(void *a0) {

    extern void (*D_80185634[])(void);
    D_80185634[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_801749A8()  /* dedup: shared engine-core @0x801749a8 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801749C8);

DEFINE_func_80174B6C()  /* dedup: shared engine-core @0x80174b6c (src/shared) */


DEFINE_func_80174BBC()  /* dedup: shared engine-core @0x80174bbc (src/shared) */



// @class: struct
// @stuck: none — MATCH (27 ins) via func-ptr array fold extern void(*D_80185638[])()


void func_80174BF4(void * arg0)
{

    extern void (*D_80185638[])();
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_80185638[M2C_FIELD(arg0, u8 *, 4)]();
}


DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174c60 (src/shared) */


DEFINE_func_80174C80()  /* dedup: shared engine-core @0x80174c80 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80174CB0);

DEFINE_func_80174E9C()  /* dedup: shared engine-core @0x80174e9c (src/shared) */


DEFINE_func_80174ED4()  /* dedup: shared engine-core @0x80174ed4 (src/shared) */


DEFINE_func_80174EF0()  /* dedup: shared engine-core @0x80174ef0 (src/shared) */




s32 func_80174F28(void *a0) {

    extern void (*D_80185640[])(void);
    D_80185640[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_80174F64()  /* dedup: shared engine-core @0x80174f64 (src/shared) */


DEFINE_func_80174FBC()  /* dedup: shared engine-core @0x80174fbc (src/shared) */


DEFINE_func_80175014()  /* dedup: shared engine-core @0x80175014 (src/shared) */


DEFINE_func_8017509C()  /* dedup: shared engine-core @0x8017509c (src/shared) */


DEFINE_func_80175114()  /* dedup: shared engine-core @0x80175114 (src/shared) */


DEFINE_func_80175150()  /* dedup: shared engine-core @0x80175150 (src/shared) */



extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {

    extern void (*D_80185648[])(void*);
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_80185648[v1](arg0);
    } else {
        func_80175268((s32)arg0);
    }
}


DEFINE_func_801751D8()  /* dedup: shared engine-core @0x801751d8 (src/shared) */



// @class: struct
// @stuck: none — MATCH (fn-ptr table indexed by D_80078EC0-1; param preserved in $s0 across 1st call)

extern void func_80146CA0(void *a0);

s32 func_80175218(void * param_1)
{

    extern u8 D_80078EC0;
    extern void (*D_80185650[])(s32);
    s32 i = D_80078EC0 - 1;

    D_80185650[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}




s32 func_80175268(s32 param_1)
{

    extern u8 D_80078EC0;
    extern VoidFn D_80185668[];
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_80185668 + ((D_80078EC0 - 1) << 2)))();
}


DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752bc (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80175308);

DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */


DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */


DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801754A8);


extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_8017553C(s32 *param) {

    extern void (*D_801857B8[])();
    D_801857B8[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_80175590()  /* dedup: shared engine-core @0x80175590 (src/shared) */


DEFINE_func_80175624()  /* dedup: shared engine-core @0x80175624 (src/shared) */


DEFINE_func_80175668()  /* dedup: shared engine-core @0x80175668 (src/shared) */



extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_80175690(s32 *param) {

    extern void (*D_801857C4[])();
    D_801857C4[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}


DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756e4 (src/shared) */


void func_80175798(void) {
}

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757a0 (src/shared) */


DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757e0 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80175820);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801758FC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801759D8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80175AB8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80175DA8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80176144);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80176218);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80176734);

DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176d00 (src/shared) */


DEFINE_func_80176D94()  /* dedup: shared engine-core @0x80176d94 (src/shared) */


DEFINE_func_80176FF4()  /* dedup: shared engine-core @0x80176ff4 (src/shared) */


DEFINE_func_801770E0()  /* dedup: shared engine-core @0x801770e0 (src/shared) */


DEFINE_func_80177340()  /* dedup: shared engine-core @0x80177340 (src/shared) */


DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742c (src/shared) */


extern void func_801776EC(u8 *a0);
void func_801775E0(s32 param_1, s32 param_2) {

    extern u8 D_8011F83B;
    extern u8 D_8011F837;
    extern u8 D_8011F7F0;
    s32 s0 = param_1;
    s32 pp = param_2;
    u8 *base = &D_8011F7F0;
    s16 sVar1; s32 t; s32 v;
    s32 c = D_8011F83B;
    if (c != 0) {
        if (c < 0) goto store;
        if (c >= 0xf7) goto store;
        if (c < 0xf3) goto store;
        goto docall;
    }
    if (D_8011F837 != 0x80) {
        *(u8 *)(s0 + 4) = 0xff;
        *(u8 *)(s0 + 6) = 0x10;
        *(u8 *)(s0 + 5) = 0x10;
        goto L684;
    }
    func_801776EC((u8 *)s0);
    goto L684;
docall:
    func_801776EC((u8 *)s0);
    goto L684;
store:
    *(u8 *)(s0 + 5) = 0xff;
    *(u8 *)(s0 + 6) = 0x10;
    *(u8 *)(s0 + 4) = 0x10;
L684:
    sVar1 = (s16)((u32)(base[0x47] * 9) >> 4);
    t = pp + 0x48;
    *(s16 *)(s0 + 0xe) = sVar1;
    *(s16 *)(s0 + 0xa) = t - sVar1;
    if (base[0x47] != 0) { s0 = param_1 + 0x14; v = 0xa0; } else { s0 = param_1 + 0x14; v = 0x40; }
    *(u8 *)(s0 + 6) = v;
    *(s16 *)(s0 + 0xa) = pp;
}


DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776ec (src/shared) */


DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801777BC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801778A8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80177940);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80177AD4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80177B5C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80177DA8);

DEFINE_func_80177EA4()  /* dedup: shared engine-core @0x80177ea4 (src/shared) */


DEFINE_func_80177F84()  /* dedup: shared engine-core @0x80177f84 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80178004);

DEFINE_func_80178298()  /* dedup: shared engine-core @0x80178298 (src/shared) */


DEFINE_func_801783D0()  /* dedup: shared engine-core @0x801783d0 (src/shared) */



void func_80178438(u16 *arg0) {

    extern M2C_UNK D_801A66A0;
    func_8001534C(2, &D_801A66A0, 0x80, 0x88, 0, 0);
    func_800153CC(3, *arg0, 0xA8, 0x88, 0x40, 0);
}


DEFINE_func_8017849C()  /* dedup: shared engine-core @0x8017849c (src/shared) */


DEFINE_func_80178608()  /* dedup: shared engine-core @0x80178608 (src/shared) */


DEFINE_func_8017869C()  /* dedup: shared engine-core @0x8017869c (src/shared) */


DEFINE_func_80178744()  /* dedup: shared engine-core @0x80178744 (src/shared) */


DEFINE_func_801787D4()  /* dedup: shared engine-core @0x801787d4 (src/shared) */



// @class: regalloc-order
// @stuck: sll $v0,$s1,2 must be recomputed AFTER the call (target nops the delay slot)

extern void func_80019064(void *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);


void func_80178840(int param_1) {

    extern int D_80185804;
    extern int D_80185810[];
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_80185804);
        }
        ((void (*)(int, int))func_80131E00)(p, D_80185810[s1byte]);
    }
}


DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788b8 (src/shared) */



// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern int func_801789AC(void);

int func_80178970(void)
{

    extern s16 D_801A94D0;
    register int r __asm__("$2");
    int v;

    v = func_801789AC();
    r = 0;
    if (v != 0)
        r = D_801A94D0 == 0;
    return r;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801789AC);

extern void func_8017435C(void);
extern void func_801746A4(void);

// @class: struct
// @stuck: none — MATCH (pointer var forces &(*(int *)&D_801858FC) into $s0, reused for store + arg-0xC)



s32 func_80178B18(s32 param_1, s32 param_2)
{
    extern void func_80178BF8(void);
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern u16 D_801858FC;

    int *p = &(*(int *)&D_801858FC);
    *p = ((int)param_2);
    func_80178BF8();
    func_801746A4();
    func_8017435C();
    ((void (*)(int, void *))func_80178CBC)(((int)param_1), (char *)p - 0xC);
}




// @class: regalloc-order
// @stuck: none — MATCH (pending verify)

s32 func_80178B70(s32 param_1, s32 param_2)
{
    extern void func_80178BF8();
    extern void func_80178CBC();
    extern int D_801858FC;

    int *p = &D_801858FC;
    *p = ((int)param_2);
    func_80178BF8();
    func_80178CBC(((int)param_1), p - 3);
}


DEFINE_func_80178BB8()  /* dedup: shared engine-core @0x80178bb8 (src/shared) */


extern void func_80016714(void *a0, s32 a1);

// @class: other
// @stuck: none — MATCH (49 ins). Key: init loop pointers via &D_SYMBOL (not (T*)0x801da788 raw int, which emits lui+ori instead of lui%hi+addiu%lo).



void func_80178BF8(s32 _unused0, s32 _unused1)
{
    extern void func_8017B1D8(void);
    extern short D_801A9544;
    extern int D_801A7C58;
    extern short D_801A7C68;
    extern short D_801A7C64;
    extern short D_801A7C60;
    extern short D_801A7C5C;
    extern int D_801A93EC;
    extern int D_801A7C70;
    extern s16 D_801A7C50;
    extern short D_801A7C48;
    extern short D_801A7C4C;
    extern int D_801A94A0;
    extern unsigned int D_801A7CC0;
    extern unsigned short D_801A7C46;

    unsigned short *puVar1;
    int iVar2;
    unsigned int *puVar3;

    iVar2 = 9;
    puVar3 = &D_801A7CC0;
    D_801A9544 = 0;
    D_801A7C58 = 0;
    D_801A7C68 = 0;
    D_801A7C64 = 0;
    D_801A7C60 = 0;
    D_801A7C5C = 0;
    D_801A93EC = 1;
    D_801A7C70 = 0;
    (*(short *)&D_801A7C50) = 0;
    do {
        *puVar3 = 0;
        iVar2 = iVar2 + -1;
        puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
    iVar2 = 0x1ff;
    puVar1 = &D_801A7C46;
    do {
        *puVar1 = 0;
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
    D_801A7C48 = 0;
    D_801A7C4C = 0;
    ((void (*)(int *, int))func_80016714)(&D_801A94A0, 0x14);
    func_8017B1D8();
}


extern M2C_UNK func_80178D40(s32 arg0, s32 arg1);

void func_80178CBC(s32 arg0, s32 arg1) {

    extern s32 D_801A7840;
    extern short D_801A9544;
    D_801A7840 = arg1;
    do {
        func_80178D40(arg0, D_801A7840);
    } while (D_801A9544 == 3);
}



extern void func_80174714(void);

void func_80178D18(void) {

    extern short D_801A9544;
    D_801A9544 = 0;
    func_80174714();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80178D40);

DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179b28 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80179B74);

DEFINE_func_80179D30()  /* dedup: shared engine-core @0x80179d30 (src/shared) */


DEFINE_func_80179D78()  /* dedup: shared engine-core @0x80179d78 (src/shared) */


DEFINE_func_80179DCC()  /* dedup: shared engine-core @0x80179dcc (src/shared) */


DEFINE_func_80179DF8()  /* dedup: shared engine-core @0x80179df8 (src/shared) */


DEFINE_func_80179E1C()  /* dedup: shared engine-core @0x80179e1c (src/shared) */


DEFINE_func_80179E48()  /* dedup: shared engine-core @0x80179e48 (src/shared) */


DEFINE_func_80179E74()  /* dedup: shared engine-core @0x80179e74 (src/shared) */


DEFINE_func_80179EA0()  /* dedup: shared engine-core @0x80179ea0 (src/shared) */


DEFINE_func_80179EE8()  /* dedup: shared engine-core @0x80179ee8 (src/shared) */


DEFINE_func_80179F14()  /* dedup: shared engine-core @0x80179f14 (src/shared) */


DEFINE_func_80179F44()  /* dedup: shared engine-core @0x80179f44 (src/shared) */


DEFINE_func_80179F6C()  /* dedup: shared engine-core @0x80179f6c (src/shared) */


DEFINE_func_80179F98()  /* dedup: shared engine-core @0x80179f98 (src/shared) */


DEFINE_func_80179FEC()  /* dedup: shared engine-core @0x80179fec (src/shared) */


DEFINE_func_8017A040()  /* dedup: shared engine-core @0x8017a040 (src/shared) */



extern void func_80179B74(s16 *a0);

void func_8017A094(s32 arg0) {

    extern s32 D_801A7C6C;
    s16 sp10;

    D_801A7C6C = arg0;
    sp10 = 0x15;
    func_80179B74(&sp10);
}



extern void func_80179B74(s16 *a0);

void func_8017A0C4(s32 arg0) {

    extern s32 D_801A7C6C;
    s16 sp10;

    D_801A7C6C = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}


DEFINE_func_8017A0F4()  /* dedup: shared engine-core @0x8017a0f4 (src/shared) */


DEFINE_func_8017A11C()  /* dedup: shared engine-core @0x8017a11c (src/shared) */



extern void func_80179B74(s16 *a0);

void func_8017A144(s32 a0) {

    extern s32 D_801A7C94;
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_801A7C94 = a0;
}


DEFINE_func_8017A180()  /* dedup: shared engine-core @0x8017a180 (src/shared) */


DEFINE_func_8017A1A8()  /* dedup: shared engine-core @0x8017a1a8 (src/shared) */


DEFINE_func_8017A1D0()  /* dedup: shared engine-core @0x8017a1d0 (src/shared) */


DEFINE_func_8017A1F8()  /* dedup: shared engine-core @0x8017a1f8 (src/shared) */


DEFINE_func_8017A220()  /* dedup: shared engine-core @0x8017a220 (src/shared) */


DEFINE_func_8017A248()  /* dedup: shared engine-core @0x8017a248 (src/shared) */


DEFINE_func_8017A270()  /* dedup: shared engine-core @0x8017a270 (src/shared) */


DEFINE_func_8017A298()  /* dedup: shared engine-core @0x8017a298 (src/shared) */


DEFINE_func_8017A2C0()  /* dedup: shared engine-core @0x8017a2c0 (src/shared) */


DEFINE_func_8017A2E8()  /* dedup: shared engine-core @0x8017a2e8 (src/shared) */


DEFINE_func_8017A310()  /* dedup: shared engine-core @0x8017a310 (src/shared) */


DEFINE_func_8017A338()  /* dedup: shared engine-core @0x8017a338 (src/shared) */


DEFINE_func_8017A360()  /* dedup: shared engine-core @0x8017a360 (src/shared) */


DEFINE_func_8017A388()  /* dedup: shared engine-core @0x8017a388 (src/shared) */




s32 func_8017A3B0(void) {

    extern s16 D_801A7C50;
    switch (D_801A7C50) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return 1;
    }
}



// @class: regalloc-order
// @stuck: none — MATCH


extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);

int func_8017A3D8(void)
{

    extern short D_801A7C8C;
    extern short D_801A7C88;
    switch (D_801A7C8C) {
    case 0:
        func_800D0CA0(1);
        D_801A7C8C = D_801A7C8C + 1;
        return 0;
    case 100:
    {
        register int a __asm__("$4");
        a = D_801A7C88;
        if (a != -1) {
            return func_8001AAA0() != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_801A7C8C = D_801A7C8C + 1;
        if (D_801A7C8C < 0x1E) {
            return 0;
        }
        D_801A7C8C = 100;
        return 0;
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017A4AC);

DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017ad0c (src/shared) */


DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ade8 (src/shared) */


DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017ae08 (src/shared) */


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017AE2C);

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);

// @class: plumbing
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801A7CCC, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801A7CCE, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801A7CD0, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801A7CC4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801A7CC6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801A7CC8, (s32)((s16)param_2));
}


extern void func_8012A418(void);

void func_8017B1D8(void) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s16 D_801A7C54;
    extern u16 D_801A7CD4;
    extern u16 D_801A7CD6;
    extern u16 D_801A7CD8;
    extern s16 D_801A94D0;
    func_8012A418();
    D_801A94D0 = 0;
    D_801A7C54 = 0;
    D_801A7CD4 = D_80126B5E;
    D_801A7CD6 = D_80126B62;
    D_801A7CD8 = D_80126B66;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017B238);


// @class: struct
// @stuck: none — MATCH (74 ins)

typedef struct { s16 a, b, c, d; } SV4_8017B368;      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
typedef struct { SV4_8017B368 x, y; } Pair16;         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{

    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801A7C74;
    extern SV4_8017B368 D_801A7C7C;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CC4;
    extern u16 D_80185900;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801A7C74;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801A7C7C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80185900)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80185900)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801A7CCC) = loc0;
    (*(SV4_8017B368 *)&D_801A7CC4) = loc1;
    D_801A94D0 = 1;
    D_801A7C54 = 0;
}




s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801A7C74;
    extern SV4_8017B368 D_801A7C7C;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CC4;
    extern u16 D_80185900;
    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801A7C74;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801A7C7C;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80185900)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80185900)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801A7CCC) = loc0;
    (*(SV4_8017B368 *)&D_801A7CC4) = loc1;
    D_801A94D0 = 1;
    D_801A7C54 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801A7CCC).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801A7CCC).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801A7CCC).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801A7CC4).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801A7CC4).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801A7CC4).c;
}


extern void func_8012A018(s32 a, s32 b);

// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @stuck: 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.

typedef struct { u8 b[8]; } Blk8_8017B614;



s32 func_8017B614(s32 param_1, s32 param_2)
{

    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80185900[];
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;
    extern u8 D_8012694C;
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80185900[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80185900[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801A7CCC;
        s16 *p78C = &D_801A7CC4;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801A7CCE;
            v798 = D_801A7CD0;
            v78C = *p78C;
            v78E = D_801A7CC6;
            v790 = D_801A7CC8;
            __asm__ __volatile__("");
            D_801A94D0 = 1;
            D_801A7C54 = 0x1E;
            D_80126990 = v794;
            D_80126994 = v796;
            D_80126998 = v798;
            D_80126984 = v78C;
            D_80126988 = v78E;
            D_8012698C = v790;
        }
        func_80129CF8();
    }
}




// @class: plumbing
// @stuck: none — MATCH



void func_8017B7A8(void)
{

    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8 D_8012694C;
    extern s16 D_801A7C54;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;
    D_8012694C = 1;
    D_801A7C54 = 0;
    D_801A7CCC = (s16) D_80114F30;
    D_801A7CCE = (s16) D_80114F34;
    D_801A7CD0 = (s16) D_80114F38;
    D_801A7CC4 = (s16) D_80114F24;
    D_801A7CC6 = (s16) D_80114F28;
    D_801A7CC8 = (s16) D_80114F2C;
}




void func_8017B824(void) {

    extern s32 D_801151D4;
    extern s16 D_801A7CE4;
    extern s16 D_801A7CE6;
    extern s16 D_801A7CE8;
    extern s16 D_801A7CEC;
    extern s16 D_801A7CEE;
    extern s16 D_801A7CF0;
    D_801A7CE4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801A7CE6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801A7CE8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801A7CEC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801A7CEE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801A7CF0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH



void func_8017B880(void)
{

    extern s16 D_801A7CE4;
    extern s16 D_801A7CE6;
    extern s16 D_801A7CE8;
    extern s16 D_801A7CEC;
    extern s16 D_801A7CEE;
    extern s16 D_801A7CF0;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    D_80114F30 = D_801A7CE4;
    D_80114F34 = D_801A7CE6;
    D_80114F38 = D_801A7CE8;
    D_80114F24 = D_801A7CEC;
    D_80114F28 = D_801A7CEE;
    D_80114F2C = D_801A7CF0;
}



typedef struct { unsigned char b[8]; } S8_8017B8E8;


s32 func_8017B8E8(s32 src) {

    extern s16 D_801A7CC4;
    extern s16 D_801A7CCC;
    (*(S8_8017B8E8 *)&D_801A7CCC) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801A7CC4) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)




void func_8017B940(void)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_801A7CD4;
    extern u16 D_801A7CD6;
    extern u16 D_801A7CD8;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern u8  D_8012694C;
    extern s16 D_801A7C54;
    extern short D_801A7CDC;
    extern short D_801A7CDE;
    extern short D_801A7CE0;
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801A7CD4);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801A7CD6);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801A7CD8);
    (*(s16 *)&D_801A7CDC) = buf[0];
    (*(s16 *)&D_801A7CDE) = buf[1];
    (*(s16 *)&D_801A7CE0) = buf[2];
    D_801A7CCC = D_80114F30 + buf[0];
    D_801A7C54 = 0;
    D_801A7CCE = D_80114F34 + buf[1];
    D_801A7CD0 = D_80114F38 + buf[2];
    D_801A7CC4 = D_80114F24 + buf[0];
    D_801A7CC6 = D_80114F28 + buf[1];
    D_801A7CC8 = D_80114F2C + buf[2];
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017BA3C);

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_80049CAC(s32 a0, s32 a1);

typedef struct { s16 a, b, c, d; } SV4_8017BB34;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017BB34;



s32 func_8017BB34(s32 param_1, s32 param_2)
{

    extern s32 D_801A7C74;
    extern SV4_8017B368 D_801A7C7C;
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801A7C7C)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801A7C74) = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    (*(SV4_8017BB34*)&D_801A7C7C) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0


void func_8017BC38(int param_1)
{

    extern void (*D_801A7C9C[10])(int);
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801A7C9C;
    do {
        if (*p != (void (*)(int))0) {
            (*p)(param_1);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 10);
    return;
}



// @class: plumbing
// @stuck: none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);

void func_8017BCA0(int param_1) {

    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    func_8017B0E4(param_1, 0xC);
    D_801A7C54 = D_801A7C54 + 1;
    if (D_801A7C54 >= 0x1F) {
        D_801A94D0 = 2;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)


extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{

    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    func_8017B0E4(param_1, 6);
    D_801A7C54 = D_801A7C54 + 1;
    if (0x18 < D_801A7C54) {
        func_8012A4BC();
        D_801A94D0 = 0;
    }
    return;
}



// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);



void func_8017BD50(int param_1)
{

    extern s16 D_801A7C54;
    extern void (*D_801A7C98)(void);
    extern short D_801A7CDC;
    extern short D_801A7CDE;
    extern short D_801A7CE0;
    extern s16 D_801A94D0;
    extern s32 D_80114F24;
    extern s32 D_80114F28;
    extern s32 D_80114F2C;
    extern s32 D_80114F30;
    extern s32 D_80114F34;
    extern s32 D_80114F38;
    func_8017B0E4(param_1, 6);
    D_801A7C54 = D_801A7C54 + 1;
    if (D_801A7C54 >= 0x19) {
        if (D_801A7C98 != 0) {
            (*D_801A7C98)();
        } else {
            D_80114F30 = D_80114F30 + D_801A7CDC;
            D_80114F34 = D_80114F34 + D_801A7CDE;
            D_80114F38 = D_80114F38 + D_801A7CE0;
            D_80114F24 = D_80114F24 + D_801A7CDC;
            D_80114F28 = D_80114F28 + D_801A7CDE;
            D_80114F2C = D_80114F2C + D_801A7CE0;
            func_8012A4BC();
        }
        D_801A94D0 = 0;
    }
}




void func_8017BE60(void *a0) {

    extern void (*D_801859A0[])(void);
    D_801859A0[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017BE9C(void) {
}

void func_8017BEA4(void) {
}

void func_8017BEAC(void) {
}

void func_8017BEB4(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017BEBC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017C294);

int func_8017C338(short *param_1, short *param_2, short *param_3, int param_4) {
    register int i2o __asm__("$5");
    register int i4o __asm__("$9");
    short sVar1; int rx, rz, uVar5;
    i4o = param_2[1];
    __asm__ __volatile__("" : : "r"(i4o));
    i2o = param_1[1]; uVar5 = 0;
    if (i2o >= i4o) {
        rx = param_1[0] - i2o * (param_2[0] - param_1[0]);
        rz = param_1[2] - i2o * (param_2[2] - param_1[2]);
    } else {
        register int den __asm__("$3");
        int p2x = param_2[0], p2z = param_2[2];
        den = i2o - i4o;
        rx = p2x + i4o * (p2x - param_1[0]) / den;
        rz = p2z + i4o * (p2z - param_1[2]) / den;
    }
    if (rx >= -0x7fff) { i2o = 0x7fff; if (rx < 0x8000) i2o = rx; }
    else i2o = -0x7fff;
    *param_3 = (short)i2o;
    if (rz >= -0x7fff) { i2o = 0x7fff; if (rz < 0x8000) i2o = rz; }
    else i2o = -0x7fff;
    param_3[2] = (short)i2o; param_3[1] = 0; sVar1 = (short)param_4;
    if ((int)*param_3 < *param_1 - param_4) { uVar5 = 0xffffffff; *param_3 = *param_1 - sVar1; }
    if (*param_1 + param_4 < (int)*param_3) { uVar5 = 0xffffffff; *param_3 = *param_1 + sVar1; }
    if ((int)param_3[2] < param_1[2] - param_4) { uVar5 = 0xffffffff; param_3[2] = param_1[2] - sVar1; }
    if (param_1[2] + param_4 < (int)param_3[2]) { uVar5 = 0xffffffff; param_3[2] = param_1[2] + sVar1; }
    return uVar5;
}


extern void ReadGeomOffset(s32 *a0, s32 *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8004921C(s32 a0, s32 a1);
void func_8017C530(s32 a0, s32 a1) {
    s32 ofx;
    s32 ofy;
    s32 sxy;
    s32 p;
    ReadGeomOffset(&ofx, &ofy);
    func_8004921C(0, 0);
    RotTransPers(a0, a1, &sxy, &p);
    func_8004921C(ofx, ofy);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017C59C);



void func_8017D468(void *a0) {

    extern void (*D_801859FC[])(void);
    D_801859FC[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D4A4);


extern s32 func_800167F0(s32 a0);

s32 func_8017D4F8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




void func_8017D51C(void *a0) {

    extern void (*D_80185A04[])(void);
    D_80185A04[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017D558(void *a0) {
    *(s32 *)((s32)a0 + 0x28) = 0xa;
    *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017D574(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D5F0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D654);



void func_8017D688(void *a0) {

    extern void (*D_80185BF8[])(void);
    D_80185BF8[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D6C4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D708);


extern s32 func_8017DCC8(void);
    extern void func_80171928(void *a0);
    void func_8017D7E4(void *a0) {
        if (((s32 (*)(s32))func_8017DCC8)((s32)a0) == 4) {
            ((void (*)(s32))func_80171928)((s32)a0);
        }
    }




void func_8017D820(void *a0) {

    extern void (*D_80185C24[])(void);
    D_80185C24[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D85C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D898);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D91C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D974);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017D9CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DA30);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DAD0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DB14);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DC10);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DC68);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DC90);

void func_8017DCB8(s32 a0) {

    extern s32 D_801A7CF8;
    D_801A7CF8 = a0;
}




s32 func_8017DCC8(void) {

    extern s32 D_801A7CF8;
    return D_801A7CF8;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DCD8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DDA0);



void func_8017DE68(void *a0) {

    extern void (*D_80185C6C[])(void);
    D_80185C6C[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DEA4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017DEEC);



void func_8017E084(void *a0) {

    extern void (*D_80185CE8[])(void);
    D_80185CE8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E0C0);

void func_8017E168(void) {
}



void func_8017E170(void *a0) {

    extern void (*D_80185CF0[])(void);
    D_80185CF0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E1AC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E234);

void func_8017E290(void) {
}



void func_8017E298(void *a0) {

    extern void (*D_80185CFC[])(void);
    D_80185CFC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E2D4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E374);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E3EC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E4D0);

void func_8017E518(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E520);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E5B8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E70C);



void func_8017E854(void *a0) {

    extern void (*D_80185DB0[])(void);
    D_80185DB0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E890);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E900);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E914);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E97C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017E99C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EAF4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EBB8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EC6C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017ED54);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017ED74);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EE24);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EE7C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EE9C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EF4C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EFA4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017EFC4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F094);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F0EC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F10C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F1CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F214);

extern void func_8017F2BC(void);
void func_8017F29C(void) {
    func_8017F2BC();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F2BC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F2FC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F31C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F3D8);

extern s32 func_8017F51C(void *a0, void *a1);
extern s32 func_8017F478(u8 *a0);
void func_8017F438(void *a0) {

    extern void *D_80185E44;
    if (func_8017F51C(a0, &D_80185E44)) {
        func_8017F478((u8 *)a0);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F478);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F4A8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F51C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F54C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F5A4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F5FC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F638);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F778);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F798);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017F860);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FA24);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FA50);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FA94);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FBB8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FBD8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FC54);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FD54);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FED8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FF68);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8017FFB4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180138);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801802CC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180378);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801803E8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8018042C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180480);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180558);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180598);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801805E4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8018062C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180674);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180694);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801806E0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8018078C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180834);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180894);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801808F0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180944);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180A50);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180A98);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180BEC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180CD4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180D30);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180DC4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80180E68);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801810F8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801811C8);

void func_80181204(A801593E4 *a0) {
    S801593E4 *v1 = a0->p20;
    v1->field12 = (v1->field12 + 0x44) & 0xFFF;
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181224);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181270);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181304);


extern s32 func_8017DCC8(void);
    extern void func_8012C098(void *a0);
    void func_80181394(void *a0) {
        if (((s32 (*)(s32))func_8017DCC8)((s32)a0) == 12) {
            ((void (*)(s32))func_8012C098)((s32)a0);
        }
    }


extern s32 func_8001739C(s32 *a0);
void func_801813D0(void) {

    extern s32 D_80185FA8;
    func_8001739C(&D_80185FA8);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801813F8);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8018140C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181534);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181578);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181620);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_8018165C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801816D4);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181728);

void func_801817C8(void) {
}

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_801817D0);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181B2C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181B98);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181C54);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181CDC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181D48);



void func_80181E20(void *a0) {

    extern void (*D_80186090[])(void);
    D_80186090[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181E5C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181EEC);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o2b", func_80181F40);
