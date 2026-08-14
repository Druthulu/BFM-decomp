#include "common.h"

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7DA4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7DCC);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7E10);

void func_801E7E9C(void) {

    extern s16 D_801F1D8A;
    D_801F1D8A = -1;
}


s16 func_801E7EB0(void) {

    extern s16 D_801F2184;
    return D_801F2184;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7EC0);

extern u16 D_80115116;
extern unsigned short D_80115112;
extern void (*D_801EBB38[])(void);
extern void func_80141C04(void);

void func_801E7F38(void) {

    extern u16 D_80115112;
    extern u16 D_80115116;
    extern void (*D_801EBB38[])(void);
    u16 i;
    i = D_80115112;
    D_801EBB38[i]();
    func_80141C04();
    D_80115116++;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7F94);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E7FD8);

            typedef struct { s8 c[8]; } Blk8_8012C890_801E8104;

/* func_801E8104 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801E8104 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801E8104 in the tree is this ov_MAIN_012 one -- a
 * distinct 7-ins function that merely shares the VRAM address (overlay collision).
 *
 * Codegen note (§31 cse_expr): the target materialises the symbol address ONCE
 * (lui+addiu -> $v1) and does both the lhu and the sh off that base. Writing the global
 * directly (D_80115112 = D_80115112 + 1) instead emits TWO luis (%hi for the load, %hi for
 * the store) -> 8 ins, LENGTH-DRIFT. Taking the address into a pointer local forces the
 * single-base form. The nop at idx3 is the lhu load-delay slot (maspsx).
 *
 * D_80115112: u16 frame/state counter (same symbol used in ov_SC03_099_jr_80140608).
 */


void func_801E8104(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8120);

            typedef struct { s8 c[8]; } Blk8_8012C890_801E8200;

/* func_801E8200 @ 0x8017C24C -- ov_MAIN_012 (7 ins).
 *
 * NOTE ON TARGET IDENTITY (tier-2): the dispatched entry ("483 ins, ov_SC06_032") does not
 * exist. ov_SC06_032's func_801E8200 is a 952-ins renderer, already MATCHED/closed in
 * src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c -- and "ov_SC06_032_jr_8017C24C" is a CARVE-REGION
 * name, not a member function (that region holds only func_801902EC/func_80191070).
 * The only genuinely unmatched func_801E8200 in the tree is this ov_MAIN_012 one -- a
 * distinct 7-ins function that merely shares the VRAM address (overlay collision).
 *
 * Codegen note (§31 cse_expr): the target materialises the symbol address ONCE
 * (lui+addiu -> $v1) and does both the lhu and the sh off that base. Writing the global
 * directly (D_80115112 = D_80115112 + 1) instead emits TWO luis (%hi for the load, %hi for
 * the store) -> 8 ins, LENGTH-DRIFT. Taking the address into a pointer local forces the
 * single-base form. The nop at idx3 is the lhu load-delay slot (maspsx).
 *
 * D_80115112: u16 frame/state counter (same symbol used in ov_SC03_099_jr_80140608).
 */


void func_801E8200(void)
{

    extern unsigned short D_80115112;
    unsigned short *p = &D_80115112;
    *p = *p + 1;
}




extern void func_800D2624(void);

void func_801E821C(void) {

    extern short D_800B9A02;
    extern u16 D_80115114;
    extern u16 D_80115112;
    u16 v0 = (*(u16 *)&D_800B9A02);
    u16 v1 = D_80115114;

    v0 ^= 0x1;

    if (v1 == v0) {
        func_800D2624();
    } else {
        D_80115112++;
    }
}


INCLUDE_RODATA("asm/md_SC04_027/nonmatchings/md_SC04_027", D_801E7B28);

INCLUDE_RODATA("asm/md_SC04_027/nonmatchings/md_SC04_027", D_801E7C00);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8274);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E88D0);

            typedef struct { s8 c[8]; } Blk8_8012C890_8017C348_801E8A80;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974_801E8A80;

/* func_801E8A80 (ov_MAIN_012 / jr_801789AC) — 188 ins, byte-exact vs
 * asm/ov_MAIN_012/nonmatchings/ov_MAIN_012_jr_801789AC/func_801E8A80.s
 *
 * Sprite/quad draw dispatcher: builds an OT chain for one "part list" entry.
 *
 * Idioms that were load-bearing here (feed these back into the cookbook):
 *  1) `dim`/`dim2`/`dim3` are DELIBERATE copies of `flag`.  The target keeps
 *     `flag` in $s7 and copies it into $s6 in each loop preheader and into $s0
 *     for the tail.  A plain `x = flag;` written in the same basic block as its
 *     use is killed by cse; it survives only when a multi-pred label separates
 *     def from use.  So: the loop-1 copy is written at the END of the outer
 *     body (loop.c hoists it into the preheader), the loop-2 copy is written in
 *     the preheader itself, and the tail copy needs a hard-register pin
 *     (`register s32 dim3 __asm__("$16")`) because nothing separates it from
 *     its uses.  Same shape as the matched sibling func_8013FAF8 (ov_SC06_008),
 *     which also needed a pin for exactly this call pair.
 *  2) `bp = sp18;` exists only to fix the ORDER of the two loop-1 preheader
 *     insns.  loop.c emits hoisted invariants in body order; writing the
 *     sp18-relative store address as an explicit pointer makes `addiu $s5,$sp,0x18`
 *     the FIRST movable, so the `dim` copy lands after it (as in the target).
 *  3) The `do { } while (0)` around the loop-1 call is a REGISTER-ALLOCATION
 *     lever, not dead syntax.  flow.c weights REG_N_REFS by loop_depth; the
 *     extra (never-iterating) loop note gives `ot` 18 weighted refs instead of
 *     16, which raises its global-alloc priority above `s` (21 refs / 159 insns)
 *     and lands the a0/a1 params in $s2/$s3 exactly as the target does.
 *     `mode` is hoisted out of the wrapper so `dim` does NOT get the same +1
 *     (that would swap $s5/$s6 between `bp` and `dim`).
 *  4) Low half of sp60[0] uses `& 0xFFFF`, NOT a (u16) cast: the mask keeps the
 *     operands in SImode so both halves load with `lh`; a (u16) cast makes
 *     gcc-2.7.2 emit `lhu`.
 */


extern s32 func_80024054(u8 *, u8 *);
extern s32 func_800D2650(s32, u8 *, s16, s16, s32, s32);
extern s32 func_800D27DC(s32, s32, void *, s16, s32);
extern s32 func_800D29F8(s32, s32, void *, s16, s32);
extern s32 func_801E8D70(s32, s16, s16, s16, s32 *);

s32 func_801E8A80(s32 ot, u8 *s, s16 c) {

    extern u16 D_8011511A;
    extern u8  D_801EBAEC[];
    extern s32 *D_801EBA64[];
    u8  sp18[72];
    s32 sp60[5];
    s32 sp78[8];
    s32 flag;
    s32 dim;
    s32 dim2;
    register s32 dim3 __asm__("$16");
    s32 t;
    s16 i;
    s16 k;
    s32 *p;
    u8 *bp;
    s16 *q;
    s32 r;
    s32 mode;

    if (c == 0) {
        flag = 0;
    } else {
        flag = -(D_8011511A != c) & 0xFF;
    }

    t = *(s32 *)(s + 0x14);
    if (t < 0) {
        func_80024054((u8 *)t, sp18);
        ot = func_800D2650(ot, sp18, *(s16 *)(s + 0x10), *(s16 *)(s + 0x12), 1,
                           flag ? 0x585858 : 0x808080);
    } else {
        p = D_801EBA64[t];
        for (k = 0; k < D_801EBAEC[*(s32 *)(s + 0x14)]; k++) {
            bp = sp18;
            dim = flag;
            for (i = 0; i < 5; i++) {
                if (i == 0) {
                    sp60[0] = (((s16 *)p)[0] + *(s16 *)(s + 0x10)) & 0xFFFF |
                              ((((s16 *)p)[1] + *(s16 *)(s + 0x12)) << 16);
                } else {
                    *(s32 *)(bp + 0x48 + i * 4) = p[i];
                }
            }
            mode = dim ? 3 : 2;
            do {
                ot = func_800D27DC(mode, ot, sp60, 1, 0);
            } while (0);
            p += 5;
        }
    }

    i = 0;
    q = *(s16 **)(s + 0x18);
    dim2 = flag;
    for (;;) {
        r = func_801E8D70(*(s32 *)(s + 0x1C), *(s16 *)s, c, i++, sp78);
        if (r == 0) {
            break;
        }
        if (r < 0) {
            func_80024054((u8 *)r, sp18);
            if (dim2 != 0) {
                sp78[0] = 0x585858;
            }
            ot = func_800D2650(ot, sp18, q[0], q[1], 1, sp78[0]);
        } else {
            p = D_801EBA64[r];
            *p = (u16)q[0] | (q[1] << 16);
            ot = func_800D27DC(dim2 ? 3 : 2, ot, p, 1, 0);
        }
        q += 2;
    }

    dim3 = flag;
    return func_800D29F8(dim3,
                         func_800D27DC(dim3 != 0, ot, (void *)*(s32 *)(s + 4),
                                       *(s16 *)(s + 0xC), 0),
                         (void *)*(s32 *)(s + 8), *(s16 *)(s + 0xE), 0);
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8D70);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E8DF4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E915C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E95E8);

u32 func_801E9B00(s32 a0, s32 a1) {
    s32 t0;
    s32 a2;
    s32 a3;
    t0 = 0;
    a2 = a0;
    a3 = 0;
    while (a2 >= 10) {
        a0 = a0 / 10;
        t0 = t0 | ((a2 - (a0 * 2 + a0 * 8)) << a3);
        a2 = a0;
        a3 += 4;
    }
    t0 = t0 | (a2 << a3);
    return t0 << a1;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E9B68);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E9BE0);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801E9DD0);


/* 152-byte engine block, copied whole (struct assignment -> 9x16B block move + 8B tail).
 * Uniquely suffixed: the host TU already sees `Blk152` from engine_types.h, and a C89
 * re-typedef of a visible name is a redefinition error. Same layout, same codegen. */
typedef struct { u32 w[38]; } Blk152_8017DF40_801E9DF8;
/* ALIGN-1 4-byte element => lwl/lwr + swl/swr (cookbook §160a); a u32[] loop is wrong. */
typedef struct { u8 b[4]; } Blk4_8017DF40_801E9DF8;



/* Param is declared s32 by the host TU's file-scope prototype (:3695); the true test is
 * 16-bit (`sll $a0,$a0,16 ; bnez`, no sra), so the truncation lives in the test instead. */
void func_801E9DF8(s32 arg0) {

    extern u8  D_80078E78[];   /* live: 152-byte block            (host TU declares this identically) */
    extern u16 D_800A6588[];   /* live: u16[64]                                                      */
    extern u8  D_800AE648[];   /* live: u8[64]                                                       */
    extern u8  D_800BA1B8[];   /* live: u8[256]                                                      */
    extern u8  D_800BA2B8[];   /* live: 4-byte struct[24], align 1                                   */
    extern u8  D_801F21B8[];   /* shadow: +0x000 */
    extern u16 D_801F2250[];   /* shadow: +0x098 */
    extern u8  D_801F22D0[];   /* shadow: +0x118 */
    extern u8  D_801F2310[];   /* shadow: +0x158 */
    extern u8  D_801F2410[];   /* shadow: +0x258 */
    s16 i;

    if ((s16)arg0 == 0) {
        *(Blk152_8017DF40_801E9DF8 *)D_80078E78 = *(Blk152_8017DF40_801E9DF8 *)D_801F21B8;
        for (i = 0; i < 64; i++) {
            D_800A6588[i] = D_801F2250[i];
        }
        for (i = 0; i < 64; i++) {
            D_800AE648[i] = D_801F22D0[i];
        }
        for (i = 0; i < 256; i++) {
            D_800BA1B8[i] = D_801F2310[i];
        }
        for (i = 0; i < 24; i++) {
            ((Blk4_8017DF40_801E9DF8 *)D_800BA2B8)[i] = ((Blk4_8017DF40_801E9DF8 *)D_801F2410)[i];
        }
    } else {
        *(Blk152_8017DF40_801E9DF8 *)D_801F21B8 = *(Blk152_8017DF40_801E9DF8 *)D_80078E78;
        for (i = 0; i < 64; i++) {
            D_801F2250[i] = D_800A6588[i];
        }
        for (i = 0; i < 64; i++) {
            D_801F22D0[i] = D_800AE648[i];
        }
        for (i = 0; i < 256; i++) {
            D_801F2310[i] = D_800BA1B8[i];
        }
        for (i = 0; i < 24; i++) {
            ((Blk4_8017DF40_801E9DF8 *)D_801F2410)[i] = ((Blk4_8017DF40_801E9DF8 *)D_800BA2B8)[i];
        }
    }
}


extern void func_8014B00C(void);
extern void func_80029344(void);
void func_801EA0E4(void) {
    func_8014B00C();
    func_80029344();
}


#include "common.h"

extern u8 D_801EBBAC[];

void func_800167B8(int);
void func_80175414(s32 _arg0);

int func_801EA10C(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801EBBAC;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_801EA164(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA188);



extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);

s32 func_801EA1DC(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801EA27C(void) {
    func_800D1EBC();
}




void func_801EA29C(void *a0) {

    extern void (*D_801EBB50[])(void);
    D_801EBB50[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA2D8);



void func_801EA344(void *a0) {

    extern void (*D_801EBBDC[])(void);
    D_801EBBDC[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801EA380(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


typedef struct { u8 c[8]; } Blk8;
const Blk8 D_801E7D80 = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801EA3A8(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E7D80;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EA410(void *arg0) {

    extern u8 D_801EBBAC[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EBBAC));
        func_80171A1C(arg0);
    }
}


void func_801EA468(void) {
}



void func_801EA470(void *a0) {

    extern void (*D_801EBBEC[])(void);
    D_801EBBEC[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801EA4AC(void) {
    ((void (*)(void))func_80171A1C)();
}



const Blk8 D_801E7D88 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801EA4CC(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E7D88;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


void func_801EA534(void) {
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801EA600(void *a0);

void func_801EA53C(void) {

    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    D_80126968 = 0xFB1;
    D_8012696A = 0x7C7;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x36;
    D_8012697A = 0;
    func_8012A018((s32)func_801EA600, 0);
    func_801EA600(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801EA600(void *a0) {

    extern void (*D_801EBBF8[])(void);
    D_801EBBF8[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA63C);


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801EA664;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801EA664;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801EA664(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801EBBFC[];
    extern u16 D_801EBC00[];

    MATRIX_801EDED4_801EA664  m1;
    SVECTOR_801EDED4_801EA664 svec_in;
    SVECTOR_801EDED4_801EA664 svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801EBBFC[t];
        *(s16 *)(param_1 + 0x2E) = D_801EBC00[*(u8 *)(param_1 + 5)];
    }

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  0xA);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 0xA);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 0xA);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 0xA);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 0xA);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0xA);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0xA);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0xA);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_2[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_2[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}



u8 func_801EA85C(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0x16;
}




extern void func_8001ABBC(u32, u32, void *, u32, u32);

void func_801EA88C(void) {

    extern u8 D_800AF040[];
    func_8001ABBC(0, 0, D_800AF040, 0, 0);
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EA8C0);



void func_801EAA0C(void *a0) {

    extern void (*D_801EBD48[])(void);
    D_801EBD48[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAA48);



void func_801EAA58(void) {

    extern s32 D_801F24A0;
    D_801F24A0 = 1;
}




s32 func_801EAA6C(void) {

    extern s32 D_801F24A0;
    return D_801F24A0;
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAA7C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAB04);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAB8C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAC10);


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801EAD2C(void *a0) {
    extern s32 D_801F1D5C;
    extern s32 D_801B9A50;
    extern s32 D_801EBC04;
    extern s32 D_801EBC34;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F1D5C);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801B9A50);
        func_8012E8E0((s32)a0, (s32)&D_801EBC04);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801EBC34);
    }
}


INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EADC4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF00);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF84);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAF9C);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EAFE4);

INCLUDE_ASM("asm/md_SC04_027/nonmatchings/md_SC04_027", func_801EB014);

extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801EB064(void) {
    func_80029124(0xFD, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}


extern s32 func_80029504(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 arg0);

void func_801EB0A4(void) {
    func_80029124(0xFE, 0x1);
    if (((s32 (*)(void))func_80029504)() == 0x136) {
        ((void (*)(s32))func_80029514)(0x140);
    }
}

