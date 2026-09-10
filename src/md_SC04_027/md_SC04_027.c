#include "common.h"

void func_801E7DA4(void) {
    extern void func_80016714(s8 *a0, s32 a1);
    extern u16 D_801F1D88;
    func_80016714((s8 *)&D_801F1D88, 8);
}


s32 func_801E7DCC(void)
{
    extern s16 D_801F1D88;
    extern s16 D_801F1D8A;
    extern void (*D_801EB0E4[])(void);
    D_801EB0E4[D_801F1D88]();
    return ((u32)D_801F1D8A) >> 31;
}


extern s32 func_80029504(void);

void func_801E7E10(void) {

    extern s16 D_801F1D90;
    extern u16 D_801F1D88;
    extern void func_801E7EC0(s32, s32);
    s32 v1;
    u16 *p;

    v1 = func_80029504();
    if ((u32)(v1 - 5) >= 0x4B5) {
        if (v1 != 0x6A4) {
            D_801F1D90 = 1;
        } else {
            D_801F1D90 = 2;
        }
    } else {
        D_801F1D90 = 0;
    }
    func_801E7EC0(1, D_801F1D90);
    p = &D_801F1D88;
    *p = *p + 1;
}


void func_801E7E9C(void) {

    extern s16 D_801F1D8A;
    D_801F1D8A = -1;
}


s16 func_801E7EB0(void) {

    extern s16 D_801F2184;
    return D_801F2184;
}


void func_801E7EC0(s32 a0, s32 a1) {
    extern u8 D_800B9A15;
    extern unsigned char D_800B9A13;
    extern u16 D_80115110;
    extern void func_801E7F38(void);
    extern s16 D_80115126;
    extern s16 D_801F218C;
    extern s16 D_801F2188;
    extern u16 D_80115112;
    extern void *D_8011DB24;
    extern s32 func_8002D4C8(s32, s32);

    D_800B9A15 = 1;
    D_800B9A13 = 5;
    D_80115110 = 4;
    D_80115126 = (s16)a0;
    D_801F218C = (s16)a1;
    D_801F2188 = (s16)a1;
    D_80115112 = 0;
    D_8011DB24 = func_801E7F38;
    func_8002D4C8(0x1E, 0);
}


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


extern void func_800D24A0(s32);
extern void func_801E7FD8(void);
extern void func_8002AF18(void);
extern u16 D_80115112;

void func_801E7F94(void) {
    u16 *p = &D_80115112;
    ((void (*)(u32))func_800D24A0)(0x5);
    func_801E7FD8();
    func_8002AF18();
    *p = *p + 1;
}


void func_801E7FD8(void) {
    extern s32 D_801F2470;
    extern u8 D_801F2480[];
    extern s16 D_801F2188;
    extern s16 D_801F2184;
    extern s16 D_801F2190;
    extern s16 D_80115118;
    extern s32 D_801EB918;
    extern s16 D_8011512C;
    extern void *D_801EB9B0;
    extern s16 D_80115126;
    extern s32 D_80115130[];
    extern s32 D_80115134;
    extern u8 D_80115138[];
    extern s32 D_801EBA5C[];
    s16 i;
    s32 *p32;
    u16 *out;

    D_801F2470 = 0;
    for (i = 0; i < 8; i++) {
        D_801F2480[i] = 0xFF;
    }
    D_801F2184 = 0;
    D_801F2190 = 0;
    D_80115118 = 0;
    if (D_801F2188 == 0) {
        D_8011512C = 0;
        D_801EB9B0 = (void *)D_801EB918;
    } else {
        D_8011512C = 9;
        D_801EB9B0 = (void *)0x1A;
    }
    i = 0;
    p32 = D_80115130;
    *p32 = 0;
    D_80115134 = D_801EBA5C[D_80115126];
    out = (u16 *)(p32 + 10);
    for (; i < 6; i++) {
        D_80115138[i] = *(u16 *)(D_80115134 + i * 32);
        out[i] = *(u16 *)(D_80115134 + i * 32 + 2);
    }
}


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


extern s32 D_801151D0;
extern u8 D_801151C8[];
extern u8 D_800B9A15;
extern s16 D_80115126;
extern s16 D_800B9A02;
extern unsigned short D_80115112;
extern s16 D_801F2184;
extern s16 D_801F2188;
extern s32 D_801F2470;
extern s32 D_801F2474;
extern u8 D_801F2478[];
extern s32 D_801F2488;

extern s32 func_8002B0B4(s32, s32, void *);
extern void func_801E8DF4(void);
extern void func_801E915C(void);
extern s32 func_801E8274(void);
extern void func_801E88D0(void);

void func_801E8120(void) {
    u16 idx;
    u16 *p;
    u16 cnt;
    s32 ret;
    s32 frame_pad[1];

    (void)&frame_pad;

    idx = *(u16 *)&D_800B9A02;
    D_801151D0 = *(s32 *)(D_801151C8 + (idx << 2));
    if (*(s16 *)&D_801F2188 == 0) {
        D_801F2488 = func_8002B0B4(D_801F2470, D_801F2474, D_801F2478);
        if (D_80115126 == 0) {
            func_801E8DF4();
        } else {
            func_801E915C();
        }
    }
    ret = func_801E8274();
    func_801E88D0();
    if ((ret << 16) != 0) {
        p = &D_80115112;
        cnt = *p;
        D_801F2184 = ret;
        D_800B9A15 = 0;
        *p = cnt + 1;
    }
}


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

extern s16 D_80115126;
extern s16 D_8011512C;
extern s16 D_801F2188;
extern s16 D_801F218C;
extern s16 D_801F2190;
extern s16 func_8014168C(s16);
extern s32 D_801EB918;
extern void *D_801EB9B0;
extern s32 D_801EBA50;
extern s32 D_801F2470;
extern s32 D_801F2474;
extern s32 func_80014ED4(s32);
extern s32 func_80015018(s32);
extern void func_8002AF18(void);
extern u16 D_8011511A;
extern s16 D_80115118;
extern u8 D_801F247B[];
extern u8 D_801F2481;
extern void func_8002AF70(void *, s32);
extern s32 func_8002D4C8(s32, s32);
extern void func_801E9DD0(void);
extern void func_801E9DF8(s32);
extern s8 D_801F2194;

s32 func_801E8274(void) {
    s32 *p;
    s32 *p2;
    u16 *ph;
    s16 *q;
    s32 pad;
    s32 flag;
    s32 st;
    s32 t;
    s32 t2;
    s32 sv;
    s32 x;
    s32 r;
    s32 unused[4];

    flag = 0;
    pad = func_80014ED4(0);
    func_80015018(0);
    func_8014168C(D_8011511A);

    if (pad & 0x40) {
        st = D_8011512C;
        switch (st) {
        case 1:
            if (D_80115126 == 0) {
                if (D_801F247B[D_8011511A] == 1) {
                    D_801EB9B0 = (void *)0x19;
                } else {
                    func_8002D4C8(0x472, 0);
                    return 0;
                }
            } else if (D_801F247B[D_8011511A] == 1) {
                D_801EB9B0 = (void *)0x16;
            } else {
                D_801EB9B0 = (void *)0x19;
            }
            D_8011512C = 2;
            func_8002D4C8(0x45D, 0);
            return 0;
        case 2:
            func_801E9DD0();
            if (D_80115126 == 0) {
                D_801EBA50 = 0x14;
                D_801F2470 = 2;
                D_801F2474 = D_8011511A - 1;
            } else {
                D_801F2474 = D_8011511A - 1;
                func_801E9DF8(1);
                func_8002AF70(&D_801F2194, D_801F2474);
                D_801EBA50 = 0xE;
                D_801F2470 = 1;
            }
            D_8011512C = 3;
            func_8002D4C8(0x45D, 0);
            return 0;
        case 4:
        case 7:
        Lcheck47:
            if (*(u16 *)&D_80115118 < 0x47) {
                goto Lreset;
            }
            return 0;
        case 9:
            p = (s32 *)&D_801EB9B0;
            if (*p == 0x1D || *p == 0x21) {
                goto Lmsg473ret1;
            }
            D_801F2188 = 0;
            D_801F2190 = 1;
            D_8011512C = 0;
            *p = D_801EB918;
            func_8002D4C8(0x45D, 0);
            return 0;
        case 5:
            goto Lload;
        case 0:
        case 3:
        case 6:
        case 8:
        case 10:
        case 11:
        case 12:
            break;
        default:
            goto Ltail;
        }
        return 0;
    } else if (pad & 0x10) {
        st = D_8011512C;
        switch (st) {
        case 0:
            if (D_801EB9B0 != (void *)0xB) {
                return 0;
            }
            /* fallthrough */
        case 1:
        Lmsg473:
            func_8002D4C8(0x473, 0);
            t = D_801F218C;
            sv = t;
            if (t == 0) {
                return 1;
            }
            x = (t == 1) ? 0x1D : 0x21;
            r = 0;
            t = 9;
            D_8011512C = t;
            D_801EB9B0 = (void *)x;
            t = 0xFF;
            goto Lstore;
        case 2:
            if (D_80115126 == 0) {
                D_801EB9B0 = (void *)0xC;
            } else {
                D_801EB9B0 = (void *)0xD;
            }
            D_8011512C = 1;
            func_8002D4C8(0x473, 0);
            return 0;
        case 5:
        case 8:
            if (D_80115126 != 0) {
                goto Lmsg473;
            }
        Lmsg473ret1:
            func_8002D4C8(0x473, 0);
            return 1;
        case 9:
            p2 = (s32 *)&D_801EB9B0;
            if (*p2 == 0x1D || *p2 == 0x21) {
                if (D_801F2190 == 0) {
                    *p2 = 0x1A;
                    func_8002D4C8(0x45D, 0);
                    return 0;
                }
                D_801F2188 = 0;
                D_8011512C = 0;
                *p2 = D_801EB918;
                func_8002AF18();
                func_8002D4C8(0x45D, 0);
                return 0;
            }
            *p2 = (D_801F218C == 1) ? 0x1D : 0x21;
            func_8002D4C8(0x473, 0);
            return 0;
        case 4:
        case 7:
            goto Lcheck47;
        case 3:
        case 6:
        case 10:
        case 11:
        case 12:
            break;
        default:
            goto Ltail;
        }
        return 0;
    } else if (pad & 0x20) {
        st = D_8011512C;
        if (st == 5) {
            D_801EBA50 = 0x17;
            D_8011512C = 6;
            func_8002D4C8(0x45D, 0);
            D_801F2470 = 3;
            return 0;
        }
        goto Ltail;
    }
Lload:
    st = D_8011512C;
Ltail:
    if (st == 4 || st == 7 || st >= 10) {
        ph = (u16 *)&D_80115118;
        if (*ph != 0) {
            *ph = *ph - 1;
            goto Lmid;
        }
    Lreset:
        *(u16 *)&D_80115118 = 0;
        if (D_80115126 == 0) {
            if (D_8011512C == 4) {
                return -1;
            }
            D_801EB9B0 = (void *)0xC;
        } else {
            t2 = D_801F218C;
            sv = t2;
            if (t2 != 0 && D_8011512C == 4) {
                t = (t2 == 1) ? 0x1D : 0x21;
                r = 0;
                D_801EB9B0 = (void *)t;
                t = 9;
                D_8011512C = t;
                t = 0xFF;
            Lstore:
                D_801F2188 = sv;
                D_801F2481 = t;
                return r;
            }
            D_801EB9B0 = (void *)0xD;
            q = &D_8011512C;
            if (*q == 0xC) {
                *q = 1;
                return 0;
            }
        }
        D_8011512C = 1;
        return 0;
    }
Lmid:
    if (D_8011512C != 1) {
        return 0;
    }
    if (pad & 0x1000) {
        t = D_8011511A;
        D_8011511A = t - 2;
        flag = 1;
        if (D_8011511A == 0 || D_8011511A >= 5) {
            D_8011511A = t + 2;
        }
    }
    if (pad & 0x4000) {
        ph = &D_8011511A;
        t2 = *ph;
        *ph = t2 + 2;
        flag = 1;
        if (*ph >= 5) {
            *ph = t2 - 2;
        }
    }
    if (pad & 0x8000) {
        ph = &D_8011511A;
        t2 = *ph;
        *ph = t2 + 1;
        flag = 1;
        if (*ph & 1) {
            *ph = t2 - 1;
        }
    }
    if (pad & 0x2000) {
        ph = &D_8011511A;
        t2 = *ph;
        *ph = t2 - 1;
        flag = 1;
        if (!(*ph & 1)) {
            *ph = t2 + 1;
        }
    }
    r = flag;
    if (r) {
        func_8002D4C8(0x45A, 0);
    }
    return 0;
}


void func_801E88D0(void) {
    typedef struct { u32 *ot; u32 pad[4]; } Env_801E9BE0;   /* 0x14 stride */
    extern s32 D_801151D0;
    extern s16 D_8011512C;
    extern s32 D_80115134;
    extern s16 D_800B9A02;
    extern Env_801E9BE0 D_800AE7BC[];
    extern s32 *func_801E9BE0(s32 *);
    extern s32 func_801E8A80(s32, u8 *, s16);
    extern s32 func_8005A600(s32, s32, s32, s32, s32);
    s32 ot;
    u8 *s2;
    s16 n;
    s16 i;

    ot = D_801151D0;
    s2 = (u8 *)D_80115134;

    if (D_8011512C == 1 || D_8011512C == 2) {
        ot = (s32)func_801E9BE0((s32 *)ot);
    }

    switch (D_8011512C) {
    case 0:
    case 5:
    case 8:
    case 9:
        n = 1;
        break;
    case 1:
    case 2:
        n = 5;
        break;
    case 3:
    case 4:
    case 10:
    case 11:
        n = 5;
        goto CALL;
    case 6:
    case 7:
    case 12:
        n = 1;
    CALL:
        ot = func_801E8A80(ot, s2 + 0xA0, 0);
        break;
    }

    for (i = 0; i < n; i++) {
        ot = func_801E8A80(ot, s2, i);
        s2 += 0x20;
    }

    func_8005A600(ot, 0, 0, 0x15, 0);

    *(s32 *)ot = 0x02000000;
    *(s32 *)ot = (D_800AE7BC[*(u16 *)&D_800B9A02].ot[2] & 0xFFFFFF) | 0x02000000;
    D_800AE7BC[*(u16 *)&D_800B9A02].ot[2] =
        (D_800AE7BC[*(u16 *)&D_800B9A02].ot[2] & 0xFF000000) | ((u32)ot & 0xFFFFFF);

    ot += 0x28;
    ((struct { s32 f; } *)&D_801151D0)->f = ot;
}


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
    register s32 dim3 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
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


extern u8 D_80115158[];

s32 func_801E8D70(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s32 *arg4) {
    s32 ret;
    s16 var;
    u8 thr;

    *arg4 = 0x808080;
    ret = 0;
    thr = D_80115158[arg2 * 2];
    if (arg1 < 5) {
        if (arg1 > 0) {
            var = arg3;
        } else if (arg1 == 0) {
            goto end;
        } else {
            var = arg3;
        }
    } else if (arg1 == 5) {
        goto end;
    } else {
        var = arg3;
    }
    if (var < thr) {
        ret = *(s32 *)(arg0 + var * 4);
    }
end:
    return ret;
}


void func_801E8DF4(void) {
    extern s32 D_801F2488;
    extern s16 D_8011512C;
    extern u8  D_801F2479;
    extern void func_8002B00C(void *);
    extern void func_801E9DF8(s32);
    extern void func_80029774(s32);
    extern s16 D_80115118;
    extern s32 D_801EBA50;
    extern s16 D_801150D4;
    extern s32 func_8002D4C8(s32, s32);
    extern u16 D_8011511A;
    extern s32 D_801F2470;
    extern u8  D_801F2481;
    extern u8  D_801F2478[];
    extern u8  D_801F2480[];
    extern u8  D_801F247C[];
    extern u8  D_801F247D;
    extern u8  D_801F247E;
    extern u8  D_801F247F;
    extern s32 D_801F248C[];
    extern s32 D_801F2490;
    extern s32 D_801F2494;
    extern s32 D_801F2498;
    extern s32 func_8002AF48(s32);
    extern s32 func_8002AF60(void);
    extern void func_801E95E8(void);
    extern void *D_801EB9B0;
    extern s8  D_801F2194;

    s32 ret;
    short i;

    ret = 0;
    if (D_801F2488 != 0) {
        if (D_801F2488 == 1) {
            s16 *p = &D_8011512C;

            if (*p == 3 && D_801F2479 == 8) {
                func_8002B00C(&D_801F2194);
                func_801E9DF8(0);
                func_80029774(0);
                *p = 4;
                D_80115118 = 0x4B;
                D_801EBA50 = 0x15;
                D_801150D4 = D_8011511A;
                func_8002D4C8(0xB3B, 0);
            } else {
                *p = 0;
            }
        } else {
            D_8011512C = 0xA;
            D_801EBA50 = 0x1B;
            D_80115118 = 0x4B;
            D_801F2470 = 0;
            return;
        }
        D_801F2470 = 0;
        D_801F2481 = 0xFF;
    }

    if (D_8011512C == 4) {
        return;
    }
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    if (D_8011512C == 0xA) {
        return;
    }
    if (D_801F2479 == D_801F2481) {
        return;
    }

    for (i = 0; i < 8; i++) {
        D_801F2480[i] = D_801F2478[i];
    }

    switch (D_801F2479) {
    case 0:
        break;
    case 1:
        ret = 0xA;
        D_8011512C = 0;
        D_8011511A = 0;
        break;
    case 2:
        ret = 0xB;
        D_801150D4 = 0;
        D_8011512C = 0;
        D_8011511A = 0;
        break;
    case 3:
        ret = 0x1F;
        D_801150D4 = 0;
        D_8011512C = 8;
        break;
    case 4:
    case 5:
    case 6:
    reset_state:
        ret = 0x13;
        D_801150D4 = 0;
        D_8011512C = 8;
        break;
    case 7:
        ret = 0xA;
        break;
    case 8:
        ret = 0xC;
        if ((D_801F247C[0] | D_801F247D | D_801F247E | D_801F247F) == 0) {
            goto reset_state;
        }
        for (i = 0; i < 4; i++) {
            if (D_801F247C[i] == 1) {
                D_801F248C[i] = func_8002AF48(i);
            } else {
                D_801F248C[i] = 0;
            }
        }
        if (D_801F248C[0] == 0 && D_801F248C[1] == 0 && D_801F248C[2] == 0 &&
            D_801F248C[3] == 0) {
            goto reset_state;
        }
        D_8011512C = 1;
        D_8011511A = (func_8002AF60() & 3) + 1;
        func_801E95E8();
        break;
    }

    if (ret != 0) {
        D_801EB9B0 = (void *)ret;
    }
}


void func_801E915C(void) {
    extern s32 D_801F2488;
    extern s32 D_801F2470;
    extern u8 D_801F2478[];
    extern u8 D_801F2479;
    extern u8 D_801F247C[];
    extern u8 D_801F2480[];
    extern u8 D_801F2481;
    extern s32 D_801F248C[];
    extern s32 D_801F2490;
    extern s32 D_801F2494;
    extern s32 D_801F2498;
    extern s16 D_8011512C;
    extern s16 D_80115118;
    extern u16 D_8011511A;
    extern u16 D_801150D4;
    extern s32 D_801EBA50;
    extern void *D_801EB9B0;
    extern void func_80029774(s32 a0);
    extern s32 func_8002D4C8(s32 a0, s32 a1);
    extern s32 func_8002AF48(s32 a0);
    extern s32 func_8002AF60(void);
    extern void func_801E95E8(void);

    s32 ret;
    s16 i;
    s16 *p;

    ret = 0;
    if (D_801F2488 != 0) {
        if (D_801F2488 == 1) {
            p = &D_8011512C;
            if (*p == 3) {
                if (D_801F2479 == 8) {
                    func_80029774(0);
                    *p = 4;
                    D_80115118 = 0x4B;
                    D_801150D4 = 0;
                    D_801EBA50 = 0xF;
                    func_8002D4C8(0xB3B, 0);
                } else {
                    *p = 0;
                }
            } else {
                if (D_801F2479 == 6) {
                    *p = 7;
                    D_80115118 = 0x4B;
                    D_801EBA50 = 0x18;
                } else {
                    *p = 0;
                }
            }
        } else {
            if ((D_801F2470 & 3) == 1) {
                D_8011512C = 0xB;
                D_801EBA50 = 0x12;
            } else {
                D_8011512C = 0xC;
                D_801EBA50 = 0x1C;
            }
            D_80115118 = 0x4B;
        }
        D_801F2470 = 0;
        D_801F2481 = 0xFF;
    }

    if (D_8011512C == 0xB || D_8011512C == 0xC) {
        return;
    }
    if (D_801F2479 == D_801F2481) {
        return;
    }

    for (i = 0; i < 8; i++) {
        D_801F2480[i] = D_801F2478[i];
    }

    switch (D_801F2479) {
    case 0:
        break;
    case 1:
        ret = 0xA;
        D_8011512C = 0;
        D_8011511A = 0;
        break;
    case 2:
        ret = 0xB;
        D_801150D4 = 0;
        D_8011512C = 0;
        D_8011511A = 0;
        break;
    case 3: {
        s16 *q = &D_8011512C;
        D_801150D4 = 0;
        if (((struct { s16 h; } *)q)->h != 0xC) {
            ret = 0x11;
            *q = 5;
        }
        break;
    }
    case 4:
        D_801150D4 = 0;
        D_8011512C = 8;
        ret = 0xB;
        break;
    case 5:
        D_8011512C = 8;
        ret = 0x10;
        break;
    case 6: {
        s16 *q = &D_8011512C;
        D_801150D4 = 0;
        if ((*q != 6) && (*q != 7) && (*q != 0xB)) {
            ret = 0xD;
            *q = 1;
        }
        for (i = 0; i < 4; i++) {
            D_801F248C[i] = 0;
        }
        D_8011511A = 1;
        func_801E95E8();
        break;
    }
    case 7:
        ret = 0xA;
        break;
    case 8: {
        s16 *q;
        if ((D_8011512C != 0xB) && (D_8011512C != 3) && (D_8011512C != 4)) {
            ret = 0xD;
        }
        for (i = 0; i < 4; i++) {
            if (D_801F247C[i] == 1) {
                D_801F248C[i] = func_8002AF48(i);
            } else {
                D_801F248C[i] = 0;
            }
        }
        q = &D_8011512C;
        if (*q == 0) {
            *q = 1;
            if ((u32)(D_801150D4 - 1) < 4) {
                D_8011511A = D_801150D4;
            } else {
                D_8011511A = (func_8002AF60() & 3) + 1;
            }
            if ((D_801F248C[0] == 0) && (D_801F2490 == 0) && (D_801F2494 == 0) &&
                (D_801F2498 == 0)) {
                D_801150D4 = 0;
                D_8011511A = 1;
            }
        }
        func_801E95E8();
        break;
    }
    }

    if (ret != 0) {
        D_801EB9B0 = (void *)ret;
    }
}


typedef struct {
    char c[3];
} Blk3_801E95E8;

extern char *strcpy(char *, const char *);
extern u32 func_801E9B00(s32 a0, s32 a1);
extern void func_801E9B68(unsigned int val, short n, unsigned short *dst, short flag);

extern void *D_801F248C[]; /* status ptr per slot */
extern void *D_801EB98C[]; /* HUD prim ptr array per slot */
extern char *D_801EB894[]; /* label strings */
extern s32 D_801EBB20[];   /* level thresholds */
extern u16 *D_801EB8F8[];  /* icon tables */
extern char *D_801EB8B4;
extern Blk3_801E95E8 D_801E7C00;

void func_801E95E8(void) {
    s16 k;
    s16 i;
    s16 j;
    u8 *p;
    void **arr;
    u32 a;
    u32 b;
    s32 r;
    s32 n;
    u16 *ico;

    for (k = 0; k < 4; k++) {
        p = (u8 *)D_801F248C[k];
        arr = (void **)D_801EB98C[k];
        if (p != NULL) {
            for (i = 0; i < 7; i++) {
                strcpy((char *)arr[i], D_801EB894[i]);
                switch (i) {
                case 0:
                    for (j = 0; j < 5; j++) {
                        if (*(s16 *)(p + 8) < D_801EBB20[j]) {
                            break;
                        }
                    }
                    if (p[0x4E] != 0) {
                        j = (*(s32 *)p == 0) ? 0x1A : 0x1C;
                    }
                    *(s32 *)arr = j + 4;
                    break;
                case 1:
                    a = p[7];
                    if (a >= 100) {
                        a = 99;
                    }
                    b = p[6];
                    if (b >= 60) {
                        b = 59;
                    }
                    func_801E9B68((func_801E9B00((u16)a, 0x18) | 0xB00000) |
                                      func_801E9B00(b, 0xC),
                                  5, (unsigned short *)((u8 *)arr[1] + 0x12), 0);
                    break;
                case 2:
                    a = *(u16 *)(p + 0x34);
                    if (a >= 1000) {
                        a = 999;
                    }
                    func_801E9B68(func_801E9B00((u16)a, 0x14), 3,
                                  (unsigned short *)((u8 *)arr[2] + 8), 1);
                    n = p[0x42];
                    if (n >= 7) {
                        n = 6;
                    }
                    ico = D_801EB8F8[n];
                    *(u16 *)((u8 *)arr[2] + 0x10) = *ico++;
                    *(u16 *)((u8 *)arr[2] + 0x12) = ico[0];
                    *(u16 *)((u8 *)arr[2] + 0x14) = ico[1];
                    a = p[0x39];
                    if (a >= 0x18) {
                        a = 0x17;
                    }
                    b = p[0x38];
                    if (b >= 0x3C) {
                        b = 0x3B;
                    }
                    func_801E9B68((func_801E9B00((u16)a, 0x18) | 0xB00000) |
                                      func_801E9B00(b, 0xC),
                                  5, (unsigned short *)((u8 *)arr[2] + 0x18), 0);
                    break;
                case 3:
                    a = *(u16 *)(p + 0x3C);
                    if (a >= 1000) {
                        a = 999;
                    }
                    b = *(u16 *)(p + 0x3A);
                    if (b >= 1000) {
                        b = 999;
                    }
                    r = func_801E9B00((u16)a, 0x14);
                    if (r == 0) {
                        r = 0xD00000;
                    }
                    func_801E9B68(r | (func_801E9B00(b, 4) | 0xC0000), 7,
                                  (unsigned short *)((u8 *)arr[3] + 6), 1);
                    break;
                case 4:
                    a = *(u16 *)(p + 0x40);
                    if (a >= 1000) {
                        a = 999;
                    }
                    b = *(u16 *)(p + 0x3E);
                    if (b >= 1000) {
                        b = 999;
                    }
                    r = func_801E9B00((u16)a, 0x14);
                    if (r == 0) {
                        r = 0xD00000;
                    }
                    func_801E9B68(r | (func_801E9B00(b, 4) | 0xC0000), 7,
                                  (unsigned short *)((u8 *)arr[4] + 6), 1);
                    break;
                case 5:
                    a = *(u32 *)(p + 0x14);
                    if (a > 99999) {
                        a = 99999;
                    }
                    func_801E9B68(func_801E9B00(a, 0xC), 5,
                                  (unsigned short *)((u8 *)arr[5] + 2), 1);
                    break;
                case 6:
                    a = *(u16 *)(p + 0xC);
                    if (a >= 0x24) {
                        a = 0x23;
                    }
                    r = func_801E9B00((u16)a, 0x18);
                    if (r == 0) {
                        r = 0xD000000;
                    }
                    func_801E9B68(r, 2, (unsigned short *)((u8 *)arr[6] + 0x10), 1);
                    break;
                }
            }
        } else {
            for (i = 0; i < 7; i++) {
                if (i == 0) {
                    *(s32 *)arr = 4;
                } else if (i == 1) {
                    strcpy((char *)arr[i], D_801EB894[i]);
                } else if (i == 4) {
                    strcpy((char *)arr[i], D_801EB8B4);
                } else {
                    *(Blk3_801E95E8 *)arr[i] = D_801E7C00;
                }
            }
        }
    }
}


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


void func_801E9B68(unsigned int val, short n, unsigned short *dst, short flag) {
    extern unsigned short *D_801EB8B8[];
    unsigned int d;
    short i;
    u16 idx;

    for (i = 0; i < n; i++) {
        d = val >> 28;
        idx = d;
        if (flag != 0) {
            if (d != 0) {
                flag = 0;
            } else {
                idx = 10;
            }
        }
        val <<= 4;
        *dst = *D_801EB8B8[idx];
        dst++;
    }
}


s32 *func_801E9BE0(s32 *out) {
    typedef struct { u32 addr : 24; u32 len : 8; } PTag_801E9BE0;
    typedef struct { u32 *ot; u32 pad[4]; } Env_801E9BE0;   /* 0x14 stride */
    typedef struct { u16 f0; u16 f2; } Prim4_801E9BE0;
    typedef struct {
        s16 f0;                     /* 0x00 */
        s16 f2;                     /* 0x02 */
        void *f4;                   /* 0x04 */
        void *f8;                   /* 0x08 */
        s16 fC;                     /* 0x0C */
        s16 fE;                     /* 0x0E */
        s16 f10;                    /* 0x10 */
        s16 f12;                    /* 0x12 */
        void *f14;                  /* 0x14 */
        Prim4_801E9BE0 *f18;        /* 0x18 */
        void *f1C;                  /* 0x1C */
    } Panel_801E9BE0;               /* 0x20 stride */

    extern Env_801E9BE0 D_800AE7BC[];
    extern u16 D_801EBB10[];
    extern u16 D_8011511A;
    extern s32 D_80115134;      /* fixed by this TU's file-scope decl */
    extern s16 D_8011512C;
    extern u16 D_80115116;
    extern s16 D_800B9A02;

    extern s32 func_8005A600(s32, s32, s32, s32, s32);

    Prim4_801E9BE0 *q;
    volatile u16 *pb;
    s32 n;
    s32 d;

    /* D_80115134 is an s32 table base here -- keep s32 arithmetic,
       fold +0x18 into the load displacement. */
    q = *(Prim4_801E9BE0 **)((*(s16 *)&D_8011511A << 5) + D_80115134 + 0x18);
    if (D_8011512C == 1) {
        n = D_801EBB10[D_80115116 & 7];
    } else {
        n = 0;
    }

    out[0] = 0x04000000;
    *((u8 *)out + 0xC) = 0x70;
    *((u8 *)out + 0xD) = 0x10;
    out[1] = 0x64808080;
    pb = (u16 *)&D_800B9A02;
    *(u16 *)((u8 *)out + 0xE) = 0x4056;

    d = n - 0x60;                                   /* [L2] */
    *(s16 *)((u8 *)out + 0x8) = q->f0 + d;
    *(s16 *)((u8 *)out + 0xA) = q->f2 - 2;
    *(s16 *)((u8 *)out + 0x12) = 0x10;
    *(s16 *)((u8 *)out + 0x10) = 0x10;

    ((PTag_801E9BE0 *)out)->addr =
        ((PTag_801E9BE0 *)(D_800AE7BC[*pb].ot + 2))->addr;
    ((PTag_801E9BE0 *)(D_800AE7BC[*pb].ot + 2))->addr = (u32)out;

    out += 5;                                       /* [L1] */
    func_8005A600((s32)out, 0, 0, 0x15, 0);

    ((PTag_801E9BE0 *)out)->addr =
        ((PTag_801E9BE0 *)(D_800AE7BC[*pb].ot + 2))->addr;
    {
        u32 *op;
        register u32 v __asm__("$2");               /* [L3] */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
        op = D_800AE7BC[*pb].ot;
        v = op[2];
        v = (v & 0xFF000000) | (((u32)out) & 0xFFFFFF);
        op[2] = v;
    }

    return out + 2;
}


extern void func_80016714(s8 *a0, s32 a1);
extern s8 D_801F2194;

void func_801E9DD0(void) {
    func_80016714(&D_801F2194, 0x2DC);
}



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


s32 func_801EA188(s32 param_1) {
    extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
    extern void func_801EA470(void *a0);
    extern s32 D_801F249C;

    D_801F249C = 0;
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EA470, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 0x10;
    return 0;
}




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


s32 func_801EA2D8(void *a0) {

    extern void (*D_801EBB58[])(void);
    extern void func_801EA88C(void);
    extern s32 D_801F249C;

    if (((s32 (*)(void))D_801EBB58[*(u8 *)((s32)a0 + 0x15)])() != 0 && D_801F249C != 0) {
        return 1;
    }
    D_801F249C = ((s32 (*)(void))func_801EA88C)();
    return 0;
}




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


void func_801EA63C(s32 arg0) {
    extern s16 D_801274E8;
    extern void func_801EA664(s32, s16 *);
    func_801EA664(arg0, &D_801274E8);
}



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
