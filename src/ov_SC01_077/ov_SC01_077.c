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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013CF68);

// @class: schedule
// @stuck: testing if/else-if with ==2 placed as the else (tail) block

extern s32 D_801D9598;
extern s32 D_801D9580;
extern s32 D_801D959C;
extern s32 D_801D958C;
extern void func_8013D9B0(void);

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

extern void func_8013D9B0(void);
extern s32 D_801D958C;

s32 func_8013D13C(void) {
    func_8013D9B0();
    return D_801D958C;
}

extern s32 D_801D9598;

void func_8013D164(void) {
    D_801D9598 = 1;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D178);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D9B0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013DD68);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E83C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E958);

// @class: regalloc-order
// @stuck: none — MATCH
DEFINE_func_8013EA54()  /* dedup: shared engine-core @0x8013EA54 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013EB7C);

DEFINE_func_8013ED6C()  /* dedup: shared engine-core @0x8013ED6C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013EE10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013EF88);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013FFD8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140E6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140F00);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801418F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141A60);

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
