#include "common.h"
#include "../shared/engine_prelude.h"

/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8();                        /* match-first, arity 1 */
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

/* func_801457A4 (@0x801457A4) is an -O0 function; its def was moved to ov_SC01_077_o0b.c (the -O0
 * whale object, whose .text ends exactly at this address) so it compiles at -O0. See there. */

#include "../shared/ov/func_801458E0.h"

#include "../shared/ov/func_801458E8.h"

// @class: schedule
// @stuck: none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_80189054 block defeats the tail-merge of the two identical D_80189054 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);

extern u8 D_80189054;
extern u8 D_80188FC4;
extern u8 D_80188FA0;
extern u8 D_80188F7C;
extern u8 D_80189030;
extern u8 D_8018900C;
extern u8 D_80188FE8;
extern u8 D_80188F58;

void func_80145934(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_80189054;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_80189054 load from being
         * tail-merged with the v>=0x384 D_80189054 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80188FC4;
    } else if (v >= 0x578) {
        p = &D_80188FA0;
    } else if (v >= 0x514) {
        p = &D_80188F7C;
    } else if (v >= 0x384) {
        p = &D_80189054;
    } else if (v >= 0x258) {
        p = &D_80189030;
    } else if (v >= 0xC8) {
        p = &D_8018900C;
    } else if (v >= 0xA) {
        p = &D_80188FE8;
    } else {
        p = &D_80188F58;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}

// @class: other
// @stuck: none — MATCH (62 ins). Sibling func_80145934 (byte-matched, same shape) is the template. Tail is default-then-conditional-override (matches asm .L80145AEC), and a §5a cross-jump barrier prevents the two identical D_801890E4 loads (>=0x6A4 and >=0x384) from being tail-merged.

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);

extern u8 D_801890E4;
extern u8 D_80188FC4;
extern u8 D_80188FA0;
extern u8 D_80188F7C;
extern u8 D_801890C0;
extern u8 D_8018909C;
extern u8 D_80188F58;
extern u8 D_80189078;

void func_80145A2C(void) {
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &D_801890E4;
        /* §5a cross-jump barrier — LOAD-BEARING: keeps this D_801890E4 load from being
         * tail-merged with the v>=0x384 D_801890E4 load below (emits zero machine code). */
        __asm__ __volatile__("" ::: "memory");
    } else if (v >= 0x5DC) {
        p = &D_80188FC4;
    } else if (v >= 0x578) {
        p = &D_80188FA0;
    } else if (v >= 0x514) {
        p = &D_80188F7C;
    } else if (v >= 0x384) {
        p = &D_801890E4;
    } else if (v >= 0x258) {
        p = &D_801890C0;
    } else if (v >= 0xC8) {
        p = &D_8018909C;
    } else {
        p = &D_80188F58;
        if (v >= 0xA) {
            p = &D_80189078;
        }
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}

// @class: regalloc-order
// @stuck: none — MATCH (53 ins). Key: pin register u8 *p __asm__("$17") = &D_800AF630 (forces $s1 live across all calls + the -0x20 frame with $s1 saved), store *(s16*)(p+0xA3DA)=0x3000 at the end. Offset 0xA3DA = 0x800B9A0A - 0x800AF630.

#include "../shared/ov/func_80145B24.h"

#include "../shared/ov/func_80145BF8.h"

#include "../shared/ov/func_80145C54.h"

// @class: struct
// @stuck: 2 residuals — (1) target RELOADS global ptr D_80126B78 before each of its 5 field accesses (f28/f18/f1a/f1c/f2c); gcc-2.7.2 CSEs the single pointer load in every clean-C form I tried (int-cast, (s8*)/(s32) M2C_FIELD, struct*), keeping ONE load. volatile forces reloads but hoists them + leaves delay-slot nops the target fills (target is NOT volatile). (2) frame 0x20 not 0x18: target reserves an unused 8-byte stack local @0x10 (address-taken local — reproduced, but every code-free escape optimizes away and a visible escape corrupts the func_80145EE8(0) arg). Structure/order/values/callees all match; only the alias-driven reload chain + the phantom frame local remain. Family exemplar (~130 overlays).



s32 func_80145CEC() {
    extern int func_80016714();
    extern int func_8001C320();
    extern int func_801552F4();
    extern int func_80147084();
    extern int func_80147098();
    extern int func_801470AC();
    extern int func_80149210();
    extern int func_8014BE9C();
    extern int func_8016533C();
    extern int func_801627C0();
    extern int func_80162AF4();
    extern int func_80165C78();
    extern int func_801468C8();
    extern int func_80145EE8();
    extern int func_8014C968();
    extern int func_8014C6D0();
    extern int func_80165938();
    extern int func_80153C8C();
    extern int func_800290BC();
    extern s32 D_800AFAE8;
    extern s32 D_800DE2A4;
    extern s32 D_801152C8;
    extern s32 D_801884CC;
    extern s32 * D_80126B78[1];
    extern s32 * D_800AF7C8;
    extern s32 * D_80126B90;
    extern s16 D_80126BB8;
    extern s16 D_80126BBA;
    extern s16 D_80126BBC;
    extern s16 D_80126BC0;
    extern s16 D_80126BC2;
    extern s16 D_80126BC4;
    extern s16 D_80126BC8;
    extern s16 D_80126BCA;
    extern s16 D_80126BCC;
    extern s16 D_80126D10;
    extern s16 D_80126D12;
    extern s16 D_80126C4E;
    extern s16 currentLocationId;
    extern s32 D_8011F9C4;
    extern s32 D_8012707C;
    extern s32 D_8011DB10;

    unsigned int uVar1;
    s32 pad[2];
    (void)&pad;

    func_80016714(&D_80126B58, 0x254);
    D_80126B78[0] = (s32 *)&D_800AFAE8;
    D_800AF7C8 = (s32 *)&D_801152C8;
    func_8001C320(&D_800AFAE8, &D_800DE2A4);
    *(s32 *)((s32)D_80126B78[0] + 0x28) = 0x7fff7fff;
    D_80126B90 = (s32 *)&D_801884CC;
    *(u16 *)((s32)D_80126B78[0] + 0x18) = 0x1000;
    D_80126BC8 = 0x1000;
    D_80126BC0 = 0x1000;
    D_80126BB8 = 0x1000;
    *(u16 *)((s32)D_80126B78[0] + 0x1a) = 0x1000;
    D_80126BCA = 0x1000;
    D_80126BC2 = 0x1000;
    D_80126BBA = 0x1000;
    *(u16 *)((s32)D_80126B78[0] + 0x1c) = 0x1000;
    D_80126BCC = 0x1000;
    D_80126BC4 = 0x1000;
    D_80126BBC = 0x1000;
    D_80126D12 = 0x1000;
    D_80126D10 = 0x1000;
    D_80126C4E = 0x1000;
    func_801552F4(&D_80126B58);
    func_80147084(&D_80126B58);
    func_80147098(&D_80126B58);
    func_801470AC(&D_80126B58);
    *(u16 *)((s32)D_80126B78[0] + 0x2c) = *(u16 *)((s32)D_80126B78[0] + 0x2c) | 0x50;
    func_80149210(&D_80126B58, 8);
    func_8014BE9C();
    func_8016533C();
    func_801627C0();
    func_80162AF4();
    func_80165C78();
    func_801468C8(&D_80126B58, 1);
    if (currentLocationId != 0x30a2 && currentLocationId != 0x30a5) {
        func_80145EE8(0);
    }
    func_8014C968();
    func_8014C6D0();
    D_8011F9C4 = 0;
    func_80165938();
    func_80153C8C();
    D_8012707C = 0;
    D_8011DB10 = 0;
    uVar1 = ((int(*)())func_80029504)();
    if (uVar1 >= 10) {
        func_800290BC();
    }
}


// @class: schedule
// @stuck: branch layout — 3-way dispatch on param_1; trying switch form

extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);

extern unsigned char D_801884DC[];
extern unsigned char D_8018850C[];
extern unsigned char D_8018855C[];
extern unsigned char D_8018858C[];
extern unsigned char D_801885BC[];

void func_80145EE8(s32 param_1)
{
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))func_80029178)(0x1F) != 0) {
            ((void (*)(void *))func_80146014)(D_801884DC);
        }
        if (((unsigned char (*)(int))func_80029178)(0x21) != 0) {
            ((void (*)(void *))func_80146014)(D_8018850C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1E) != 0) {
            ((void (*)(void *))func_80146014)(D_8018855C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1D) != 0) {
            ((void (*)(void *))func_80146014)(D_8018858C);
        }
        if (((unsigned char (*)(int))func_80029178)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))func_80146014)(D_801885BC);
        break;
    case 1:
        ((void (*)(void *))func_80146014)(D_801884DC);
        ((void (*)(void *))func_80146014)(D_8018850C);
        ((void (*)(void *))func_80146014)(D_8018855C);
        ((void (*)(void *))func_80146014)(D_8018858C);
        ((void (*)(void *))func_80146014)(D_801885BC);
        break;
    }
}

#include "../shared/ov/func_80146014.h"

#include "../shared/ov/func_80146074.h"

// @class: other
// @stuck: none — MATCH (handwritten scratchpad-stack-switch trampoline; 3 calls + a beqz guard. Direct sw $sp,0($t0) (no lw $t1 indirection); D_801D9610 stashed/tested. maspsx rules: no explicit jal-delay nop, no trailing .set reorder, %%hi/%%lo escaped.)
#include "common.h"

extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();

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
        "lui   $at, %%hi(D_801D9610)\n"
        "sw    $v0, %%lo(D_801D9610)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9610)\n"
        "lw    $v0, %%lo(D_801D9610)($v0)\n"
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

// @class: regalloc-order
// @stuck: none — MATCH (142 ins). Keys: pin $s0=&D_80126B58/$s1=D_80126B78; memcpy on u8[] symbols (unaligned lwl/lwr/swl/swr); if-branch uses D_80126B9C symbol, else-branch uses base+0x44; load p=D_80126B78 BEFORE setting base

#include "common.h"

#include "../shared/ov/func_80146128.h"

// @class: struct
// @stuck: none — MATCH (fnptr-table idiom: D_8018860C[u8 idx](&arg))
extern void (*D_8018860C[])(void *);
extern u8 D_80126BA4;

void func_80146360(void)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_80126B58;
    D_8018860C[D_80126BA4](&D_80126B58);
}




   /* size 8, align 1 -> unaligned block move */

#include "../shared/ov/func_801463A0.h"


#include "../shared/ov/func_80146534.h"

#include "../shared/ov/func_80146554.h"

#include "../shared/ov/func_80146578.h"

#include "../shared/ov/func_8014659C.h"

#include "../shared/ov/func_801465C0.h"

#include "../shared/ov/func_801465E4.h"

#include "../shared/ov/func_80146608.h"

extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);

#include "../shared/ov/func_801466B4.h"

#include "common.h"

/* func_801466F0 — packs its 7 by-value args into a 0x14-byte stack record and hands
 * the record to one of two "insert into the 8-slot table" routines.
 *
 * The record layout is READ OFF the already-matched callee DEFINE_func_8014680C()
 * (src/shared/engine_core.h): it takes `short *param_1` and touches
 *   *param_1 (0x00), param_1[1] (0x02), param_1[2] (0x04), param_1[3] (0x06),
 *   *(int*)(param_1+4) (0x08), *(int*)(param_1+6) (0x0C), *(int*)(param_1+8) (0x10).
 * => { u16, u16, u16, u16, s32, s32, s32 }  (§71 sibling-first)
 *
 * Store order in the target is exactly PARAMETER order (0x10, 0x18, 0x12, 0x14,
 * 0x16, 0x1C, 0x20), so the body assigns the fields in the order the args arrive.
 * sp5 is loaded with `lhu` => it is an unsigned short ANSI param (a K&R decl would
 * promote to int and give `lw`, §43).
 */

/* S33: Rec801466F0 lifted to src/shared/engine_types.h so this body can propagate (§100). */

#include "../shared/ov/func_801466F0.h"




#include "../shared/ov/func_80146750.h"


#include "../shared/ov/func_8014680C.h"

/* canonical-sig: engine_core.h declares `extern s32 D_8011F750;` */
#include "../shared/ov/func_801468C8.h"

#include "../shared/ov/func_80146924.h"

#include "../shared/ov/func_80146994.h"

#include "../shared/ov/func_801469C8.h"

extern void func_80146AFC(void*);
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6) __asm__("func_80146A6C");
#include "../shared/ov/func_80146A6C.h"


#include "../shared/ov/func_80146AB4.h"

/* func_80146AFC — ASCENDING twin of the byte-proven DEFINE_func_80146B9C()
 * in src/shared/engine_core.h (cookbook §71: find the already-matched sibling first).
 * Same 0x58-stride slot table (base D_8011D030), same 7-store copy body in the same
 * order, same $a2/$a1 giv pair. 80146B9C walks DOWN; this one walks UP, so the guard
 * is `p < end`, end = p + 0xA50 (30 slots x 0x58).
 *
 * DECAY ROOT CAUSE (this redraft): the stored backlog draft had been rewritten to
 * `void func_80146AFC(...)`, which drops BOTH `return 0` paths' `addu $v0,$zero,$zero`
 * and the hit path's `j .L80146B94` => LENGTH-DRIFT -2 (38 vs 40) plus $v0/$v1 regalloc
 * drift on the final lw/sw pair. Restoring the s32 return type (the fleet spelling the
 * banked sibling func_80146B9C already uses) restores MATCH at 40/40.
 *
 * RECONCILE (2026-08-01) — the whole-binary gate failed with
 *   ov_SC01_077_after.c:592: conflicting types for `D_8011D030' (previous decl :564)
 * TWO file-scope collisions were present; both are fixed HERE, with NO edit to
 * src/shared/engine_core.h and NO change to the generated code (re-verified MATCH
 * after each step):
 *
 *   1. D_8011D030 (the reported one). DEFINE_func_801469C8() emits
 *      `extern s32 D_8011D030;` at FILE scope (engine_core.h:10811, above the
 *      `s32 func_801469C8(...) {` line), and this TU expands that macro at :564 —
 *      i.e. before the splice point :570. The draft's `extern u16` therefore
 *      redeclared it incompatibly at :592. Conformed to the TU's `extern s32`.
 *      Codegen-neutral: the sole use is `(u8 *)&D_8011D030`, an address-of, so the
 *      declared object type never reaches a load/store width (cookbook §20).
 *
 *   2. func_80146AFC ITSELF (latent, would have surfaced next). DEFINE_func_8014C010()
 *      (:13510) and DEFINE_func_8014AD30() (:13524) each emit a file-scope
 *      `extern void func_80146AFC(void *a0);`, and this TU expands them at :1386 and
 *      :1541 — after the splice — so an `s32 func_80146AFC` definition collides on the
 *      RETURN axis. Fixed with the §37/§124 ASM-LABEL ALIAS: the C identifier is
 *      aF80146AFC, the emitted label is func_80146AFC, so the canonical void decl and
 *      this s32 definition never share a namespace. Callers discard the result, so the
 *      void-typed call sites stay codegen-identical.
 *
 * Both were reproduced and then cleared against the real cpp+cc1-2.7.2 pair using a
 * synthetic copy of this TU's declaration environment (.run/uc2/_recon_probe_80146AFC.c):
 * the pre-reconcile spelling emits exactly the gate's error pair; the spelling below
 * compiles clean.
 *
 * ORACLE: tools/match_one.py func_80146AFC --c .run/uc2/func_80146AFC.c
 *         --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_after  -> MATCH (40 ins)
 */

extern s32 D_8011D030;

s32 aF80146AFC(void *arg0) __asm__("func_80146AFC");

#include "../shared/ov/func_80146AFC.h"


#include "../shared/ov/func_80146B9C.h"

#include "../shared/ov/func_80146C3C.h"


#include "../shared/ov/func_80146C98.h"

/* func_80146CA0: lhu 0x2; addiu +1; sh 0x2; jr (sh in delay slot)
 * void form avoids a trailing andi v0,0xffff that a returned u16 value could force. */
#include "../shared/ov/func_80146CA0.h"

/* func_80146CB4: lhu 0x2; addiu -1; sh 0x2; jr (sh in delay slot)
 * void form avoids a trailing andi v0,0xffff that a returned u16 value could force. */
#include "../shared/ov/func_80146CB4.h"

#include "../shared/ov/func_80146CC8.h"

#include "../shared/ov/func_80146D30.h"

#include "../shared/ov/func_80146D80.h"

#include "../shared/ov/func_80146D90.h"

#include "../shared/ov/func_80146DB8.h"

#include "../shared/ov/func_80146DE8.h"

#include "../shared/ov/func_80146DF8.h"

#include "../shared/ov/func_80146E90.h"

#include "../shared/ov/func_80146E98.h"

#include "../shared/ov/func_80146EC0.h"

#include "../shared/ov/func_80146F58.h"

#include "../shared/ov/func_80146FC4.h"

#include "../shared/ov/func_8014704C.h"

#include "../shared/ov/func_80147054.h"

#include "../shared/ov/func_80147060.h"

#include "../shared/ov/func_8014706C.h"

#include "../shared/ov/func_80147078.h"

#include "../shared/ov/func_80147084.h"

#include "../shared/ov/func_8014708C.h"

#include "../shared/ov/func_80147098.h"

#include "../shared/ov/func_801470A0.h"

#include "../shared/ov/func_801470AC.h"

#include "../shared/ov/func_801470B4.h"

#include "../shared/ov/func_801470C0.h"

#include "../shared/ov/func_80147118.h"

#include "../shared/ov/func_80147264.h"

#include "../shared/ov/func_80147290.h"

/* func_801472B4: lhu 0x7E; andi 0xFFFD; sh 0x7E; jr (sh in delay slot)
 * void form: no return value => no extra truncation past the mask op. */
#include "../shared/ov/func_801472B4.h"

#include "../shared/ov/func_801472C8.h"

#include "../shared/ov/func_801472DC.h"

#include "../shared/ov/func_801472F0.h"

#include "../shared/ov/func_80147300.h"

#include "../shared/ov/func_80147324.h"

#include "../shared/ov/func_80147364.h"

#include "../shared/ov/func_801473DC.h"

#include "../shared/ov/func_801473EC.h"

#include "../shared/ov/func_80147460.h"

#include "../shared/ov/func_80147478.h"

#include "../shared/ov/func_801474D8.h"

#include "../shared/ov/func_801474EC.h"

#include "common.h"

#include "../shared/ov/func_80147514.h"

#include "../shared/ov/func_80147628.h"

#include "../shared/ov/func_80147718.h"

#include "../shared/ov/func_80147788.h"

#include "../shared/ov/func_801477A8.h"

#include "../shared/ov/func_801477C8.h"

#include "../shared/ov/func_801477E8.h"

#include "../shared/ov/func_80147814.h"

extern void func_80147928(int a0, int a1);
extern void func_8014799C(int a0, int a1);
extern void func_80147A10(int a0, int a1);

#include "../shared/ov/func_80147860.h"

#include "../shared/ov/func_801478B8.h"

#include "../shared/ov/func_80147928.h"

#include "../shared/ov/func_80147948.h"

#include "../shared/ov/func_8014799C.h"

#include "../shared/ov/func_801479BC.h"

#include "../shared/ov/func_80147A10.h"

#include "../shared/ov/func_80147A30.h"

#include "../shared/ov/func_80147A84.h"

#include "../shared/ov/func_80147AAC.h"

#include "../shared/ov/func_80147AD4.h"

#include "../shared/ov/func_80147B18.h"

#include "../shared/ov/func_80147B5C.h"

// @class: loose-typing
// @stuck: none -- MATCH (38 ins). Three separate pointers (s32 *p0=&D_80127090; p1=&D_80127094; p2=&D_80127098)
//         force gcc to RELOAD each named global through its pointer for the param-store readback (the sibling
//         func_80146D30 's32 *p=&D_80127090' idiom, extended to all three), reproducing the target's fresh
//         lui+lw per access + the hoisted D_80127090 reload. Reading the globals directly CSEs (no reload).

#include "../shared/ov/func_80147C30.h"

#include "../shared/ov/func_80147CC8.h"

#include "../shared/ov/func_80147D38.h"

#include "../shared/ov/func_80147DC0.h"

#include "../shared/ov/func_80147E44.h"

#include "../shared/ov/func_80147F50.h"

#include "../shared/ov/func_80147F78.h"


#include "../shared/ov/func_80148038.h"

/*
 * func_80148094 — MATCH (213 ins), Fable5 crack 2026-07-07 (from CLOSE=72 count-exact).
 *   asm-subdir: asm/ov_SC01_077/nonmatchings/ov_SC01_077
 *   verify: .venv/bin/python tools/match_one.py func_80148094 --c <this> \
 *           --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077 --work .run/t7b/work/func_80148094
 *
 * ROOT (RTL-dump + gcc-2.7.2-source verified; supersedes the close-draft's "local-alloc
 * first-fit" story): the fac<->param2c $a0/$a1 swap was a GLOBAL-ALLOC ORDER race, an
 * allocno_compare NEAR-TIE (global.c:588-601: pri = floor_log2(refs)*refs/live_length
 * *10000*size; equal pri => lower allocno first):
 *   - fac (pseudo 79, 7 refs / 33 insns)            pri 4242
 *   - <0x201-arm p2c (pseudo 183, 3 refs / 7 insns) pri 4285  -> allocated FIRST
 *   183 carries preferences {4,5} (set_preference via the unwrap-first-operand rule:
 *   `(set X (plus (reg 183) ..))` with X local-allocated; prune_preferences removed hard-2)
 *   so 183 pref-took $a0 and pushed fac (conflicting, first-fit hard{2,3,29}) to $a1.
 *   Target world: fac wins the order -> $a0 by first-fit; 183's pref-4 then conflicts,
 *   pref-5 hits -> `lw $a1,0x2C` (why it skips FREE $v1 — preference beats first-fit).
 *
 * THE THREE LEVERS (each byte-gated):
 *   L1 fac ref-boost (the 10-byte reg tie): `__asm__("" :: "r"(fac));` placed at the TOP
 *      of the <0x200 block, where fac is ALREADY LIVE-THROUGH -> +1 flow-time ref, zero
 *      live-range extension, zero bytes: refs 7->8 crosses the floor_log2 step (2->3) ->
 *      pri 4242 -> ~7058 > 4285 -> fac allocated before 183. The identical construct at
 *      the DEF SITE (prior agent, "-> 220 ins, live-range blowup") was NEVER wrong about
 *      the reg — the +7 was the un-merge of the 0x201 product tails (see L2); placement
 *      inside an already-live-through block is the safe form.
 *   L2 arm layout (`else if (sVar1 >= 0x201) {...} else {==0x200 arm}`): the ==0x200 arm
 *      must sit PHYSICALLY LAST so it is the fall-through predecessor of the exit tail.
 *      jump.c cross-jump extends a merge backward only while the jumping tail matches the
 *      FALL-THROUGH tail; with the ==0x200 arm last, the common suffix [lw 0x2C][sw 0x18]
 *      forms .L8014836C/.L80148370 exactly as target. (Layout alone, old regs = 216: the
 *      a0/a0 product tails then merge where target's a0/a1 ones cannot. Reg fix alone,
 *      old layout = 220. The levers are a PAIR.)
 *   L3 store order in the three direct-out0 arms: `out[0]=*(0x24); out[1]=0;` (out[0]
 *      FIRST) -> sched2 fills the lw's load-delay with the zero-store: [lw][sw 0][sw v0],
 *      no nop. m2c's `out[1]=0;`-first order costs +1 nop per arm (3 total).
 *
 * A/B record: base 213/72 -> L1 only 220/104 -> L1+L2 216/95 -> L1+L2+L3 MATCH 213.
 *             L2+L3 only (no asm) = 213/213 close=10: fac def-copy + 6 negus + 183's
 *             lw/mult/addu triplet — the pure reg-tie residue.
 * Dead ends verified: q(v0)-fac and ratan2#2-fac variable merges — both merge-candidates'
 * live windows cross an arg-load `(set (reg 4 a0) ..)` post-sched1 (q conflicts hard-4,
 * .greg row `117 conflicts: .. 4 ..`), so a merged pseudo can never take $a0. The /s-dep
 * lattice lever does not apply (all mem ops register-addressed; no fixed-address globals).
 */
#include "../shared/ov/func_80148094.h"

#include "../shared/ov/func_801483E8.h"

#include "../shared/ov/func_801484B0.h"

#include "../shared/ov/func_801484E8.h"

#include "../shared/ov/func_80148534.h"

#include "../shared/ov/func_8014856C.h"

#include "../shared/ov/func_801485B8.h"

/* func_80148634: ori v0,0x8080; sh 0 @0xAA; sh 0 @0xAC; sh 0x8080 @0xAE
 * 0x8080 loaded via ori (positive 16-bit imm) => store an unsigned 16-bit value. */
#include "../shared/ov/func_80148634.h"

#include "../shared/ov/func_80148648.h"

#include "../shared/ov/func_801487F4.h"

#include "../shared/ov/func_80148800.h"

#include "../shared/ov/func_8014880C.h"

#include "../shared/ov/func_80148818.h"

#include "../shared/ov/func_80148824.h"

#include "../shared/ov/func_801488A8.h"

#include "../shared/ov/func_8014891C.h"

#include "../shared/ov/func_80148980.h"

#include "../shared/ov/func_801489E8.h"

#include "../shared/ov/func_80148A48.h"

#include "../shared/ov/func_80148AAC.h"

// @class: regalloc-order
// @stuck: none — MATCH (71 ins). switch binary-tree; s1 angle = pin-source-of-copy ($5 temp + retie); 2nd-block double-load + 0x80-clobber via $v1/$v0/$a0 pins + lazy hi-pin reusing dead c80 reg

extern s32 D_801151D4;
extern s32 ratan2(s32 a0, s32 a1);
extern ActorFn D_80188614[];

int func_80148AFC(void *a0) {
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
        return D_80188614[*(u16 *)(p + 0xAA) >> 12](a0) & 0xFF;
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

#include "../shared/ov/func_80148C18.h"

#include "../shared/ov/func_80148C20.h"

#include "../shared/ov/func_80148C34.h"

#include "../shared/ov/func_80148C4C.h"

#include "../shared/ov/func_80148C64.h"

#include "../shared/ov/func_80148C7C.h"

#include "../shared/ov/func_80148C84.h"

#include "../shared/ov/func_80148C9C.h"

/* func_80148CB4: addiu a1,-0x400; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1
 * v0 = *(a0+0x20) deref; store (a1-0x400)&0xFFF as halfword at v0+0x12; return 1. */
#include "../shared/ov/func_80148CB4.h"

/* func_80148CCC: addiu a1,-0x200; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
#include "../shared/ov/func_80148CCC.h"

#include "../shared/ov/func_80148CE4.h"

#include "../shared/ov/func_80148CEC.h"

/* func_80148CF4: addiu a1,-0x600; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
#include "../shared/ov/func_80148CF4.h"

/* func_80148D0C: addiu a1,-0x400; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
#include "../shared/ov/func_80148D0C.h"

#include "../shared/ov/func_80148D24.h"

#include "../shared/ov/func_80148D3C.h"

// @class: schedule
// @stuck: none — MATCH (68 ins)
extern s32 ratan2(s32 a0, s32 a1);
extern s32 D_801151D4;
extern u8 D_80126C01;
extern u16 D_80126C02;
extern u16 D_80126C06;
extern s32 D_80188654[];

s32 func_80148D44(void) {
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
    return (s32)(s16)((s16 (*)())(D_80188654[D_80126C02 >> 0xc]))();
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

extern s32 ratan2(s32, s32);
extern s32 D_801151D4;
/* derived from asm: lui/addu/lw %lo(D_80188694) indexed by (u16>>12)*4, then jalr with no args;
 * the result is sign-extended from 16 bits => the table's functions return s16. */
extern s16 (*D_80188694[])();

s32 func_80148E54(s32 arg0) {
    register s32 tmp __asm__("$4") = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                                             *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 ang;
    __asm__("" : "=r"(tmp) : "0"(tmp));
    ang = tmp;

    switch (*(u8 *)(arg0 + 0xA9)) {
    case 0x41:
        return D_80188694[*(u16 *)(arg0 + 0xAA) >> 12]();
    case 0x53:
    case 0x73:
        if ((*(u16 *)(arg0 + 0xAE) & 0xFF) == 0x80 && (*(u16 *)(arg0 + 0xAE) >> 8) == 0x80) {
            return -1;
        }
        return (ang + ratan2((*(u16 *)(arg0 + 0xAE) & 0xFF) - 0x80,
                             0x80 - (*(u16 *)(arg0 + 0xAE) >> 8))) & 0xFFF;
    }
}


#include "../shared/ov/func_80148F60.h"

#include "../shared/ov/func_80148F68.h"

#include "../shared/ov/func_80148F74.h"

#include "../shared/ov/func_80148F80.h"

#include "../shared/ov/func_80148F8C.h"

#include "../shared/ov/func_80148F98.h"

#include "../shared/ov/func_80148FA0.h"

#include "../shared/ov/func_80148FAC.h"

#include "../shared/ov/func_80148FB8.h"

#include "../shared/ov/func_80148FC4.h"

#include "../shared/ov/func_80148FD0.h"

#include "../shared/ov/func_80148FD8.h"

#include "../shared/ov/func_80148FE0.h"

#include "../shared/ov/func_80148FEC.h"

#include "../shared/ov/func_80148FF8.h"

#include "../shared/ov/func_80149004.h"

#include "../shared/ov/func_8014900C.h"

#include "../shared/ov/func_80149020.h"

#include "../shared/ov/func_80149034.h"

#include "../shared/ov/func_80149048.h"

#include "../shared/ov/func_8014905C.h"

#include "../shared/ov/func_80149078.h"

#include "../shared/ov/func_801490E0.h"

#include "../shared/ov/func_801490E8.h"

#include "../shared/ov/func_801490F0.h"

#include "../shared/ov/func_801490F8.h"

#include "../shared/ov/func_80149184.h"

#include "../shared/ov/func_801491C4.h"

#include "../shared/ov/func_80149204.h"

#include "../shared/ov/func_80149210.h"

#include "../shared/ov/func_80149228.h"

#include "../shared/ov/func_80149284.h"

#include "../shared/ov/func_80149290.h"

#include "../shared/ov/func_80149350.h"

// @class: regalloc-order
// @solved: MATCH (23 ins) via .run/gccmap/cse_expr.md §2 (hoist-vs-remat IS steerable).
//   Old @stuck: gcc cached &sp18 in freed $s0 (addiu s0,sp,24 + move a2/a0,s0); target remats
//   addiu $aN,$sp,0x18 per call. Fix: name the first use through a nested-block pointer local,
//   then kill its CSE class AFTER the call with a volatile OUTPUT-ONLY asm (no "0"(q) input --
//   that keeps q live across the call and re-caches). LOAD-BEARING: cse.c invalidate_for_call
//   only kills HARD regs; the asm re-SET is the only C-reachable pseudo-class kill.
//   Leaf-proven only (match_one, asm/ov_SC04_005) -- still needs whole-binary gate_stage.
#include "../shared/ov/func_80149374.h"

#include "../shared/ov/func_801493D0.h"

#include "../shared/ov/func_8014942C.h"

#include "../shared/ov/func_80149450.h"


#include "../shared/ov/func_801494CC.h"


#include "../shared/ov/func_80149544.h"

/* arg-forwarding wrapper: stack buffer passed to two callees.
 * §17 array-decay — buf declared as a local array and passed bare so gcc
 * rematerializes addiu $sp,0x10 per use instead of hoisting into a
 * callee-saved reg (frame 0x20, only $s0 saved — matches target). */
#include "../shared/ov/func_80149584.h"

/* func_801495C4  (ov_SC01_077, 34 ins) — clone of the banked sibling func_8014964C.
 *
 * REGISTER-PIN-FREE byte-match (close=0). The sibling's engine_core.h macro pins
 * `register s32 p2 __asm__("$16")` to force a1->$s0; that pin is REMOVED here — once
 * the &buf CSE-hoist is broken, natural density allocation puts a1 in $s0 by itself
 * (a1: 7 refs / 21 insns crosses 2 calls; &buf pseudo out-densities it otherwise).
 *
 * Wall (pure-C, zero-asm): gcc-2.7.2 CSE commons the two identical stack-address
 * computations `&buf` (sp+0x20, passed to both calls) into ONE call-crossing pseudo,
 * which then wins $s0 over a1 (RC-2/K2 density) and spills a1 to $s1 (frame 0x30->0x38).
 * v1 (buf declared first, buf@sp+0x10) rematerializes &buf and matches everything but
 * the in/buf slot offsets; but correct slots REQUIRE `in,result,buf` decl order, which
 * puts buf@sp+0x20 and triggers the hoist. Every zero-asm CSE-break tried (2 pointer
 * vars, single ptr 2-set, struct, (char*)result+8, buf[z-z], a1&0, volatile ptr) is
 * folded/re-commoned by gcc. The two `m1/m2` reg-tie barriers below make the two &buf
 * opaque so each is materialized fresh (as the target does); `pin`/`mtx` barriers fix
 * the call-1 arg-materialization schedule order. These are __asm__ value-barriers, NOT
 * `register __asm__("$N")` pins.
 */
#include "../shared/ov/func_801495C4.h"


// @class: regalloc-order
// @stuck: none — MATCH (34 ins). param_2 pinned to $s0; the two stack out-bufs (in@0x10,
//   mid@0x20,out@0x18) would be HOISTED into $s1 across call1 (frame 0x38, +s1 save) — break
//   that with a per-use CSE-break barrier (`__asm__("":"=r"(p):"0"(p))`) on &in, mid(call1),
//   mid(call2) so each rematerializes `addiu reg,$sp,off` (frame 0x30, only $s0 saved). The
//   two independent arg setups (`lw $a0,0x20($a0)` vs `addiu $a2,$sp,0x20`) tie in sched2 —
//   force target order with VOLATILE barriers in textual order pin(&in)->mtx-load->mid.

#include "../shared/ov/func_8014964C.h"

#include "../shared/ov/func_801496D4.h"

#include "../shared/ov/func_80149704.h"

#include "../shared/ov/func_80149724.h"

#include "../shared/ov/func_80149744.h"

#include "../shared/ov/func_80149788.h"

#include "../shared/ov/func_801497A8.h"


#include "../shared/ov/func_80149864.h"

#include "../shared/ov/func_80149884.h"

#include "../shared/ov/func_801498C0.h"

/* func_801498E0 — overlay ov_SC01_077 shared core */
#include "../shared/ov/func_801498E0.h"

#include "../shared/ov/func_80149954.h"

#include "../shared/ov/func_80149A64.h"

#include "../shared/ov/func_80149AA8.h"

#include "../shared/ov/func_80149AD4.h"

#include "../shared/ov/func_80149B14.h"

#include "../shared/ov/func_80149B54.h"

#include "../shared/ov/func_80149BAC.h"

#include "../shared/ov/func_80149BEC.h"

#include "common.h"

#include "../shared/ov/func_80149C08.h"

#include "../shared/ov/func_80149C94.h"

#include "../shared/ov/func_80149CB4.h"

#include "../shared/ov/func_80149CD4.h"

#include "../shared/ov/func_80149D10.h"

#include "../shared/ov/func_80149D9C.h"

#include "../shared/ov/func_80149DD8.h"

#include "../shared/ov/func_80149E94.h"

#include "../shared/ov/func_80149F2C.h"


#include "../shared/ov/func_80149FA8.h"

// @class: regalloc-order
// @stuck: none — MATCH (38 ins)
extern s32 D_801886D4[];
extern u8 D_80078E78[];
extern s16 currentLocationId;

s32 func_80149FB0(s32 a0) {
    s32 *p = &D_801886D4[0];
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

// @class: struct
// @stuck: none — MATCH (90 ins). Keys: (1) single Loc struct pins the 0x10..0x25 stack
//   region (frame 0x40) for the func_8012F14C/func_80135260 out-params; (2) loop is a
//   while(1) with the 6 checks &&-chained in the loop CONDITION + the "found" block AFTER
//   the loop (fall-through) so the success path is a forward j .L8014A190 — matches the
//   target CFG (Ghidra-C while-form); (3) the base &D_801202A0 must be RECOMPUTED inside
//   the loop, not hoisted: `s0 = (s32)D_801202A0 + s2;` + the in-place re-tie barrier
//   `__asm__ __volatile__("":"=r"(s0):"0"(s0));` (cookbook §21) forces the lui/addiu/addu
//   per iteration instead of caching the symbol addr in $s4 (kills 1 ins + $s4); (4) u32
//   counter -> sltiu; (5) bef8-fail uses `goto ret0;` to a ret0 label placed AFTER the
//   success block -> gives the bef8 v0=0 its own .L8014A18C block (delay slot = a1 setup);
//   (6) setup-store SOURCE order a30,a2e,a2c,a1e,a20,a1c makes the scheduler hold a2c(0xE)
//   in $v1 (loaded early, stored last at 0x14) while a2e(0xA) stores immediately at 0x12.

#include "../shared/ov/func_8014A048.h"

#include "../shared/ov/func_8014A1B0.h"

#include "../shared/ov/func_8014A218.h"

#include "../shared/ov/func_8014A238.h"

#include "../shared/ov/func_8014A2E4.h"

#include "../shared/ov/func_8014A380.h"

#include "../shared/ov/func_8014A3E0.h"

#include "../shared/ov/func_8014A454.h"

#include "../shared/ov/func_8014A4B4.h"

#include "../shared/ov/func_8014A4FC.h"

#include "../shared/ov/func_8014A51C.h"

// @class: schedule
// @stuck: none — MATCH (39 ins). Body-primary if/else (D=0 tail), call-result-first (add in $v1),
//         and a scheduling barrier in the clamp block to keep the bnez delay slot a nop.
#include "common.h"

#include "../shared/ov/func_8014A59C.h"

#include "../shared/ov/func_8014A638.h"

#include "../shared/ov/func_8014A674.h"

#include "../shared/ov/func_8014A680.h"

#include "../shared/ov/func_8014A69C.h"

#include "../shared/ov/func_8014A6A8.h"

#include "../shared/ov/func_8014A6C4.h"

#include "../shared/ov/func_8014A71C.h"








#include "../shared/ov/func_8014A738.h"


#include "../shared/ov/func_8014A830.h"

// @class: schedule
// @stuck: none — MATCH (109 ins, relocation-masked)
#include "common.h"

#include "../shared/ov/func_8014A850.h"

#include "../shared/ov/func_8014AA04.h"

#include "../shared/ov/func_8014AA28.h"

#include "../shared/ov/func_8014AB5C.h"

#include "../shared/ov/func_8014AB7C.h"

#include "../shared/ov/func_8014ABF0.h"

#include "../shared/ov/func_8014AC10.h"

#include "../shared/ov/func_8014ACC0.h"

#include "../shared/ov/func_8014ACE8.h"

#include "../shared/ov/func_8014AD30.h"

#include "../shared/ov/func_8014AD7C.h"

#include "../shared/ov/func_8014ADA8.h"

// @class: plumbing
// @stuck: none — MATCH. Verified TWICE: match_one 139/139 standalone, AND 139/139
//   relocation-masked through the REAL src/ov_SC01_077/ov_SC01_077_after.c with all 481
//   DEFINE_ macros expanded (cpp -> cc1 -> maspsx --expand-div -> as, exit 0, zero
//   `conflicting types`). The in-TU compile is the check the prior draft never got: it
//   ALSO hit match_one 139/139, but match_one compiles STANDALONE with the draft's own
//   externs (§17a-1 / §20), so it never saw the two real in-TU decl conflicts below —
//   that, not codegen, is why it was a B3-near-miss.
//
//   (1) DEFINE_func_80146128() @line 353 (BEFORE our slot @1162) declares
//       `extern void func_8014ADE0(s32 a0);` -> the def sig MUST be `(s32 a0)`, not the
//       prior draft's `struct Ent *`. Param reached via casts (`*(u16*)a0`), neutral.
//   (2) DEFINE_func_8014B034() @line 1166 declares `extern s16 D_80078E90;` -> the prior
//       draft's file-scope `extern s32 D_80078E90;` is a hard conflict. Fixed with a
//       BLOCK-scope `extern s32 D_80078E90;` inside the function (see the note at the
//       decl). NOTE the two forms that FAIL here, both measured:
//         - `*(s32*)&D_80078E90` (the obvious "keep the s16 extern" dodge): the cast
//           changes the type so gcc can't collapse `*(&x)`, the address becomes a real
//           value, and with 4 uses CSE hoists it into a reg — ~100 insns shift. This is
//           the §18 `&sym` materialization trap wearing a different hat.
//         - file-scope `extern s32` — `conflicting types`, the original B3 blocker.
//   Callee externs pinned to the exact sigs the in-TU DEFINE_ macros define (func_8014B154
//   takes `s32*`, the rest `s32` args), with call-site casts (§17a-1).
//   Structs dropped for raw casts: identical RTL, and it keeps the body free of local types
//   so dedup_propagate (§19 compiles_standalone) can lift it.
//
// Codegen levers (byte-proven, retained from the prior draft):
//   - base &D_80078E78 cached in a pointer local pinned to $s1 -> addr hoisted to the
//     prologue, live across all calls (§17); direct array access instead folds %lo per use
//     (no $s1, frame 0x18 not 0x20).
//   - var_a1 as if/else-if (not "=4 then conditional 0xA") -> caller-saved $a1
//     rematerialized into both beqz delay slots; the 0xA branch as fall-through fixes the
//     2nd beqz polarity.
//   - NO $s2 pin on temp_s2 -> gcc uses a fresh $a1 for (temp>>16) instead of clobbering
//     $s2 in place, which also pushes the /60 magic 0x88888889 into $a2.
//   - `*(s16*)(p+0x1A)` emits `lh` at the plain uses but `lhu; sll; sra` inside the /60:
//     gcc-2.7.2's extendhisi2 force_not_mem's the HImode mem, and combine only folds the
//     shift-pair back into `lh` when the `x<<16` temp has ONE use — the division needs it
//     twice (sra 16 for the value, sra 31 for the sign fix), so it stays unfolded.

#include "../shared/ov/func_8014ADE0.h"


#include "../shared/ov/func_8014B00C.h"

#include "../shared/ov/func_8014B034.h"

#include "../shared/ov/func_8014B084.h"

#include "../shared/ov/func_8014B12C.h"

#include "../shared/ov/func_8014B154.h"

#include "../shared/ov/func_8014B160.h"

#include "../shared/ov/func_8014B190.h"

#include "../shared/ov/func_8014B2A8.h"

#include "../shared/ov/func_8014B2D0.h"

#include "../shared/ov/func_8014B2F8.h"

#include "../shared/ov/func_8014B310.h"

#include "../shared/ov/func_8014B33C.h"

#include "../shared/ov/func_8014B350.h"

#include "../shared/ov/func_8014B4C4.h"

#include "../shared/ov/func_8014B4D4.h"

#include "../shared/ov/func_8014B504.h"

#include "../shared/ov/func_8014B598.h"

#include "../shared/ov/func_8014B5B0.h"

#include "../shared/ov/func_8014B5B8.h"

#include "../shared/ov/func_8014B5C4.h"

#include "../shared/ov/func_8014B5D0.h"

#include "../shared/ov/func_8014B5D8.h"

#include "../shared/ov/func_8014B6F0.h"

#include "../shared/ov/func_8014B768.h"

// @class: regalloc-order
// @stuck: none — MATCH

#include "../shared/ov/func_8014B7A4.h"

// @class: schedule
// @stuck: none — MATCH (sep EA6 u16 sym re-folds w/ (s16) cast=lh; mem barrier orders EA4 store before EA6 load)

#include "../shared/ov/func_8014B944.h"

#include "../shared/ov/func_8014BB0C.h"

#include "../shared/ov/func_8014BB24.h"

#include "../shared/ov/func_8014BC0C.h"

#include "../shared/ov/func_8014BC44.h"

#include "../shared/ov/func_8014BC80.h"

#include "../shared/ov/func_8014BCC0.h"

#include "../shared/ov/func_8014BCEC.h"

#include "../shared/ov/func_8014BD24.h"

#include "../shared/ov/func_8014BD60.h"

#include "../shared/ov/func_8014BD98.h"

#include "../shared/ov/func_8014BDC8.h"

#include "../shared/ov/func_8014BDE0.h"

#include "../shared/ov/func_8014BDE8.h"

#include "../shared/ov/func_8014BE78.h"

#include "../shared/ov/func_8014BE9C.h"

#include "../shared/ov/func_8014BEC0.h"

#include "../shared/ov/func_8014BEF8.h"

#include "../shared/ov/func_8014BF18.h"

#include "../shared/ov/func_8014BF48.h"

#include "../shared/ov/func_8014BF6C.h"

#include "../shared/ov/func_8014BF8C.h"

#include "../shared/ov/func_8014BFB0.h"

#include "../shared/ov/func_8014BFD4.h"

#include "../shared/ov/func_8014BFF4.h"

#include "../shared/ov/func_8014C010.h"

#include "../shared/ov/func_8014C050.h"

#include "../shared/ov/func_8014C088.h"

#include "../shared/ov/func_8014C0C8.h"

#include "../shared/ov/func_8014C118.h"

#include "common.h"

#include "../shared/ov/func_8014C168.h"

extern void func_8014C1C8(s32 arg0, s32 arg1, void *arg2);
extern u8 D_8018875C[];

void func_8014C1A0(s32 arg0, s32 arg1) {
    func_8014C1C8(arg0, arg1, D_8018875C);
}

#include "../shared/ov/func_8014C1C8.h"


#include "../shared/ov/func_8014C278.h"

extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_80012A60(s32 a0, s32 a1);

#include "../shared/ov/func_8014C2B0.h"

#include "../shared/ov/func_8014C308.h"

#include "../shared/ov/func_8014C3A4.h"

#include "../shared/ov/func_8014C3D0.h"

#include "../shared/ov/func_8014C43C.h"

/* func_8014C4AC @0x8014C4AC — 47 ins, reach x138 (134 *_after.c + 4 *_jr_80140608.c)
 *
 * STATUS: match_one MATCH (47/47) — and MATCH *with the fleet-canonical declaration present in the
 *         same TU*, which is what the previous draft could not do.
 *
 * ==== INTEGRATION — SOLVED T0, NO HEADER EDIT (cookbook §37/§73/§124 asm-label alias) ===========
 * The blocker was the §73 RETURN axis: the byte-true def MUST return a value ($v0 is written on every
 * path — `addu $v0,$zero,$zero` x3 and `addu $v0,$t0,$zero`, and the final `sb $v1,0xC8($v0)` is based
 * on the RETURN pseudo), but `src/shared/engine_core.h` declares
 *     extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
 * inside 8 DEFINE_func_* macros (8014A380 / 8015E714 / 8014A1B0 / 8014C43C / 8015E5B0 / 8015DD74 /
 * 8014A850 / 801571C4).  FOUR of them are instantiated at FILE scope in ov_SC01_077_after.c itself
 * (lines 1254 / 1262 / 1368 / 1583) — all ABOVE the INCLUDE_ASM stub at 1585 — so the def collides:
 * `conflicting types for func_8014C4AC`.
 *
 * MEASURED, not assumed (probes kept in .run/uc/):
 *   - p_void_naive.c  : conform the def to `void` -> compiles CLEAN (so the PARAM axis is already
 *                       canonical — the conflict is purely the return type) but 45 ins vs 47, 13
 *                       mismatched, class LENGTH-DRIFT.  The two `addu $v0,$zero,$zero` delay-slot
 *                       copies, the `addu $v0,$t0,$zero` and the `j .L8014C560` all vanish.  A void
 *                       def CANNOT carry this body.
 *   - p_v1.c          : void + `register s32 rv __asm__("$2")` used as the base of the last store —
 *                       byte-identical to the naive void output; the pin is a preference and gcc
 *                       coalesced rv into $t0 (§72), and the dead `rv = 0` sets are DCE'd.
 *   - p_v2.c          : ...+ `volatile` on the pinned reg — forces a stack frame (`addiu $sp,-8`),
 *                       47 ins / 45 mismatched.  Worse.
 *   => the RETURN axis here is NOT dissolvable from the def side by casts or by pins.
 *
 * THE FIX (zero blast radius, T0, travels to all 138 siblings): the §37/§73 ASM-LABEL ALIAS — the same
 * form already banked for func_8016191C x137 and explicitly supported by family_remap's
 * `_alias_decl_for` (§124).  The definition takes a DIFFERENT C identifier — so it never binds against
 * the canonical `extern void func_8014C4AC` — and a GNU asm label binds the emitted SYMBOL:
 *
 *     s32 aF8014C4AC(...) __asm__("func_8014C4AC");
 *
 * Verified: `nm t.o` => `00000000 T func_8014C4AC` (global, correct name; no `aF8014C4AC` symbol).
 * Verified compilable ALONGSIDE the conflict: .run/uc/p_alias4.c carries FOUR copies of the canonical
 * `extern void func_8014C4AC(...)` AND a caller that calls it through that prototype, above the def —
 * MATCH (47 ins).  Verified sweep-readable: `family_remap._alias_decl_for` resolves this file to
 * ('aF8014C4AC', line 2) and `_def_head_at` accepts the K&R head, so the ×138 propagation path is the
 * standard one.  §30 #2's fleet `void`->`s32` widen of engine_core.h is therefore NOT needed and is
 * NOT proposed (it would be a T2/R22 edit; this is T0).  Per §124: "Fix the reader, not the source."
 * ================================================================================================
 *
 * Body levers (unchanged from the isolation-MATCH draft — all C-level, no pins, no permuter):
 *  1. §48-C2 block copy: the lwl/lwr+swl/swr 8-byte move == a plain struct assign of a 2-byte-aligned
 *     4x u16 struct.  BLOCK scope so it cannot collide with engine_types.h (§100/§102, rule D).
 *  2. THE CRACK (2 -> 0): NO local pointer variable — use the s32 param with a cast at every use.  A
 *     local `u8 *p = (u8 *)a0;` makes gcc coalesce the a0 PARM copy away and emit the body insn AFTER
 *     the a4 stack-parm CONVERSION insn that assign_parms appends via `conversion_insns` — giving
 *     `lhu $v1,0x10($sp)` BEFORE `addu $t0,$a0,$zero`, i.e. the first two instructions swapped.  Not a
 *     scheduling residual — assign_parms emission order.
 *  3. `u16 a4` in a K&R parameter list (§43/§99): gives the narrow `lhu $v1,0x10($sp)` stack read while
 *     default-promoting to int, so it stays compatible with the ambient `s32 a4` prototype.
 *  4. Body inside the positive `||` arm with the bare `return 0;` LAST: that is what puts the shared
 *     zero-return block AFTER the body (.L8014C55C) so reorg can copy `addu $v0,$zero,$zero` into the
 *     two branch delay slots and retarget them to .L8014C560.  The inverted `&&` + early-`return 0`
 *     form puts the zero block BEFORE the body -> closeness 2.
 *  5. Global types: `lw` D_80126CD0 => s32; `lhu`-then-`sb` D_8012693A / D_801152B8 => u16 (identical
 *     to engine_core.h's own macro-local decls at 19666/19667, so no conflict either way).  Declared
 *     at BLOCK scope so the unit carries no file-scope decl into any of the 138 sibling TUs.
 */
#include "common.h"

/* §37/§73/§124 asm-label alias: the fleet canon declares this `extern void` (engine_core.h, inside 8
 * DEFINE_func_* macros); the byte-true body must return s32.  Aliasing the C name sidesteps the
 * RETURN-axis conflict with no header edit.  This line MUST travel with the body. */
s32 aF8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4) __asm__("func_8014C4AC");

#include "../shared/ov/func_8014C4AC.h"


#include "../shared/ov/func_8014C568.h"


#include "../shared/ov/func_8014C59C.h"

extern u8 D_80188764;
extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {
    return func_8014C5FC(a0, a1, &D_80188764);
}

#include "../shared/ov/func_8014C5FC.h"

#include "../shared/ov/func_8014C6AC.h"

#include "../shared/ov/func_8014C6C0.h"

#include "../shared/ov/func_8014C6D0.h"

#include "../shared/ov/func_8014C6E0.h"



// @class: schedule
// @stuck: none — MATCH (match_one 91/91)
//
// Levers used (all byte-gated on ov_SC07_006):
//  1. §struct  8-byte alignment-1 struct copy `*(M8_8014C6F4*)(a+0x164) = *(M8_8014C6F4*)(p+0x10)`
//     -> the lwl/lwr,lwl/lwr,swl/swr,swl/swr block (engine_types.h M8_xxx convention).
//  2. §17 base-pointer cache: `u8 *p = D_80078E78;` (NOT a direct D_80078E78[0x49]) so gcc pins
//     the base into callee-saved $s1 and hoists the la into the prologue (live across the jal).
//  3. §17 register pins: the search result `e` MUST be $v0 and the limit `lim` $v1, else
//     local-alloc swaps the loop IV/limit pair ($v1<->$a0) and coalesces `e` into the IV.
//  4. DELAY-SLOT lever (new): writing the compare constant as its own pre-loop statement
//     (`want = 0x22;`) instead of the literal `0x22` inside the loop test. With the literal,
//     loop.c hoists the `li $a1,0x22` into the loop PREHEADER (after the duplicated entry test),
//     so reorg.c's guard branch has nothing local to take and instead COPIES the branch-target
//     insn (`addu $v0,$zero,$zero`) into its delay slot and redirects past it — a +1 shift that
//     also lets the loop-back branch steal the same insn (nop -> move). Materialising the
//     constant in the block BEFORE the entry test makes fill_simple_delay_slots take it from
//     the preceding insns, reproducing `beqz $v0,.L8014C7F4 / addiu $a1,$zero,0x22` and leaving
//     the loop-back delay slot a nop. `want` needs no pin — gcc lands it in $a1 on its own.


#include "../shared/ov/func_8014C6F4.h"


#include "../shared/ov/func_8014C860.h"

#include "../shared/ov/func_8014C88C.h"

#include "common.h"

#include "../shared/ov/func_8014C8C8.h"

#include "../shared/ov/func_8014C8F0.h"

#include "../shared/ov/func_8014C918.h"

#include "../shared/ov/func_8014C968.h"

#include "../shared/ov/func_8014C978.h"

#include "../shared/ov/func_8014C98C.h"

extern s32 func_80029178(s32 arg);
extern s32 func_8016F1AC(void);
extern void func_80139914(s32 a0);
extern void func_80029124(s32, s32);

#include "../shared/ov/func_8014C99C.h"

#include "../shared/ov/func_8014CA00.h"

#include "../shared/ov/func_8014CA14.h"

#include "../shared/ov/func_8014CA70.h"

#include "../shared/ov/func_8014CA88.h"

#include "../shared/ov/func_8014CAE4.h"

#include "../shared/ov/func_8014CAFC.h"

#include "../shared/ov/func_8014CB0C.h"

#include "../shared/ov/func_8014CB1C.h"

#include "../shared/ov/func_8014CB2C.h"

#include "../shared/ov/func_8014CB58.h"

#include "../shared/ov/func_8014CB68.h"

#include "../shared/ov/func_8014CB7C.h"

#include "../shared/ov/func_8014CB8C.h"

#include "../shared/ov/func_8014CB9C.h"

#include "../shared/ov/func_8014CBD8.h"

#include "../shared/ov/func_8014CBE8.h"

#include "../shared/ov/func_8014CBF8.h"

#include "../shared/ov/func_8014CC28.h"

// @class: other
// @stuck: fully-handwritten scratchpad-stack-switch sequencer (manipulates $sp) — modeled on the byte-proven DEFINE_func_80128678 inline-asm precedent
#include "common.h"

extern void func_8014CD0C(u8 *a0);

void func_8014CCB4(void)
{
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
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

/* func_8014CD0C — overlay ov_SC01_077 shared core */
#include "../shared/ov/func_8014CD0C.h"

#include "../shared/ov/func_8014CD80.h"

// @class: loop-guard
// @stuck: none — MATCH (82 ins), symcheck SYMS-OK (4 symbols agree)
//
// Keys (template for the 137-member h_seq family):
//  (1) THE LOOP-BOUND DUALITY. The entry guard is register-relative (`addiu $v0,$s0,0x6480` +
//      `sltu`) but the BACK EDGE rematerialises the absolute bound (`lui/addiu %hi/%lo(D_80126720)`
//      + `sltu`). A plain `for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C)` also reaches
//      MATCH (82 ins) under relocation masking, but it relocates the back edge against
//      D_801202A0+0x6480 and symcheck reports `MISSING D_80126720` — i.e. it cannot be trusted to
//      bank on the symbol set. The split form below (entry guard `p < p + 0x6480`, back edge
//      `(u32)p < (u32)D_80126720`) yields the same 82 bytes AND the target's symbol set. This is
//      the func_8014DD8C / engine_core.h split-guard idiom, reused verbatim.
//  (2) TWO INDUCTION VARIABLES, secondary base +0x75. $s1 = $s0 + 0x75 is the giv gcc combines all
//      of 0x0A/0x20/0x58/0x5C/0x74/0x75 onto (the two BYTE accesses at 0x74/0x75 force an unaligned
//      base, so `q` must be u8*, not the s32* of the func_8014EA4C sibling). Written explicitly as
//      `q = p + 0x75` with negative displacements (-0x6B/-0x55/-0x1D/-0x19/-0x1).
//  (3) The `!=`-nested if ladder (not `&&`-chained, not `continue`d) reproduces the fall-through-to-
//      .L8014D00C CFG; the success block returns 1 so both exits merge on the shared epilogue.
//  (4) `t = *(s32 *)(q - 0x1D)` is loaded ONCE and reused as arg1 of func_80135A4C — that is why
//      `lw $a1, -0x1D($s1)` sits at the zero-test, not at the call.
//  (5) `& 0xFF` on the func_8014C918 result is load-bearing: it is the `andi $v1,$v0,0xFF` before
//      `sh $v1, 0x16E($s2)` (§I2 — sh alone would not mask).
//  Register fallout is natural, no pins needed: a0->$s2, a2->$s3, a1->$s4 (param_3 outranks param_2
//  on allocno priority because of its 4 extra uses in the success block).

#include "../shared/ov/func_8014CF04.h"


// @class: other
// @stuck: none — MATCH (22 ins; handwritten scratchpad-stack-switch via *(0x1F8003FC); modeled on byte-proven sibling func_8014CCB4; omit explicit jal-delay nop — maspsx auto-inserts it)
#include "common.h"

extern void func_8014D0A4(s32 a0);

void func_8014D04C(void)
{
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
        "jal   func_8014D0A4\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014D0A4.h"


#include "../shared/ov/func_8014D12C.h"


// @class: iv-combine
// @stuck: none — MATCH (80 ins, symcheck SYMS-OK 4/4). Keys: (1) §31#2 / loop.md L1 — ONE walked
//   base pointer `p` with every field as a plain `*(T*)(p+k)` byte-offset; a separate `q = p+0x75`
//   pointer (the Ghidra-C two-pointer read) strength-reduces a SPURIOUS 3rd IV (+ a `*q` bare deref
//   keeps q alive as its own biv) -> 84 ins, $s5 spilled, frame 0x30 instead of 0x28. (2) The
//   L1-rule-6 anchor falls out for free: the LAST-emitted DEST_ADDR giv is the `*(u8*)(p+0x75)` lbu
//   in the func_8014C918 arg list, so combine_givs anchors the single giv at +0x75 and every other
//   field becomes a negative offset off $s2 (-0x19/-0x1D/-0x6B/-0x55) exactly as the target shows.
//   (3) `*(u16*)p` stays a BARE deref (mult 1, add 0 -> find_mem_givs excludes it) so the biv $s0
//   itself does `lhu 0($s0)` and stays live for the two `beq $s0,$v0` identity checks. (4) The entry
//   guard must be written `p < p + 0x6480` off the VARIABLE (per DEFINE_func_8014DD8C precedent):
//   two symbol_refs would fold, the variable form emits the target's `addiu $v0,$s0,0x6480; sltu`,
//   while the do-while bottom test against `D_80126720` materialises the full lui/addiu address.
//   (5) `t` (the +0x58 field) is a single-use temp -> local-alloc parks it directly in $a1 across
//   the beqz and into the call, matching `lw $a1,-0x1D($s2)`.
#include "common.h"

#include "../shared/ov/func_8014D2A0.h"


// @class: other
// @stuck: none — MATCH (22 ins; handwritten scratchpad-stack-switch trampoline via *(0x1F8003FC); mechanical remap of byte-proven sibling func_8014D04C in this same overlay — same D_801D9618 stash, callee swapped to func_8014D438; omit explicit jal-delay nop, maspsx auto-inserts it)
#include "common.h"

extern void func_8014D438(s32 a0);

void func_8014D3E0(s32 _arg0)
{
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
        "jal   func_8014D438\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014D438.h"

#include "../shared/ov/func_8014D4C0.h"


#include "../shared/ov/func_8014D610.h"


// @class: other
// @stuck: none — MATCH (handwritten scratchpad-stack-switch sequencer manipulating $sp; modeled on byte-proven func_8014CCB4. KEY: maspsx auto-fills the jal delay slot with a nop, so DO NOT write an explicit nop after `jal func_8014D790` — put `lui $at,%hi(D_801D9618)` directly after the jal and maspsx's auto-nop becomes the delay slot, yielding jal/nop/lui exactly as target)
#include "common.h"

extern void func_8014D790(s32 a0);

void func_8014D738(void)
{
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
        "jal   func_8014D790\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014D790.h"

// @class: schedule
// @stuck: none — MATCH (304/304), symcheck SYMS-OK 12/12, and the whole-TU cc1 stage now compiles CLEAN
//
// ══════════════════════════════════════════════════════════════════════════════
// SESSION-22 RE-DERIVATION + THE ROOT-CAUSE FIX FOR THE "ASSEMBLER-STAGE" FAILURE
// ══════════════════════════════════════════════════════════════════════════════
// The SESSION-21 draft did reach match_one MATCH (re-verified this session, 304/304)
// and symcheck SYMS-OK — but the whole-binary build died with an opaque `Error 33`
// that was logged as "an ASSEMBLER-stage failure I did not finish diagnosing".
//
// IT IS NOT AN ASSEMBLER FAILURE. Stage-by-stage isolation of the real pipeline
// (cpp | cc1 | maspsx | as) over a scratch copy of src/ov_SC01_077/ov_SC01_077_after.c
// with this function spliced in place of its INCLUDE_ASM gives:
//     cpp    rc=0
//     cc1    rc=33   <-- ".../tu.c:1901: conflicting types for `Ent'"
//                        "src/shared/engine_types.h:434: previous declaration of `Ent'"
//     maspsx rc=0
//     as     rc=0    (only benign "used $at without .set noat" warnings)
// `33` is CC1's exit code, surfaced by the recipe's `set -o pipefail` (Makefile:560).
// Because `as` is the LAST stage in that pipe, make attributes the failure to the
// assembler — the same misread that made func_8012AAAC's "opaque Error 33" look
// assembler-shaped until it was isolated stage by stage.
//
// ROOT CAUSE: the draft declared `typedef struct Ent { ... } Ent;` at FILE scope.
// `Ent` is already a shared engine type (src/shared/engine_types.h:434,
//   typedef struct { u16 guard; u16 pad; u16 field; u8 rest[14]; } Ent;
// a 20-byte struct), pulled into every overlay TU through
// src/ov_SC01_077/../shared/engine_core.h. gcc-2.7.2 rejects the redefinition
// outright (an ERROR, not the "type mismatch with previous external decl"
// WARNING that the rest of this TU is full of), so cc1 aborts.
//
// THE FIX, and why this shape: all three helper types are now declared at BLOCK
// scope inside func_8014D820 itself. That is strictly better than renaming to
// `Ent_8014D820` at file scope, because this function is an h_seq family EXEMPLAR
// with 138 members: a file-scope type name has to stay unique against 138 distinct
// overlay TUs *and* against whatever engine_types.h grows next, while a block-scope
// typedef can never collide with anything, in any TU, ever. It also matches the
// fleet convention — src/shared/engine_core.h contains ZERO `typedef struct`
// (all 0 of them); every DEFINE_ macro body uses engine_types.h types or local ones.
// Typedefs emit no code and create no allocno, so the move is byte-neutral:
// re-verified MATCH (304 ins) after the change, and the local DECLARATION ORDER
// below is untouched (§76 — declaration order is the dominant regalloc lever here).
//
// ══════════════════════════════════════════════════════════════════════════════
// THE BODY (SESSION-21 derivation, each lever re-verified this session)
// ══════════════════════════════════════════════════════════════════════════════
// func_8014D820 (304 ins, ov_SC01_077, h_seq family exemplar, 138 members).
// The whole residual off the SESSION-18 close=9 seed was a sched1 PERMUTATION
// inside ONE basic block (idx 79..101, the pos/desc set-up between the `slti 0x400`
// guard and the `currentLocationId` test): identical multiset of insns, identical
// register assignment, wrong positions. §66d-5 exactly — classed WIDTH [structural]
// at every waypoint and not structural at all.
//
// The lever (reusable): that block is 12 statements over a small dependency poset
// (load x0/y0/z0 -> add -> store pos.* / desc.*), so source ORDER is the only
// control and the space of linear extensions is enumerable. A dependency-respecting
// sweep found MATCH at
//   x0; pos.x; y0; pos.y; z0; tx; pos.z; tz; desc.x; desc.z; ty; desc.y
// i.e. all three loads and both pos stores first, then the two adds, then the desc
// stores, with the y accumulator (`ty`) computed LAST. No pin, no barrier, no
// permuter run. Eleven hand attempts on this window (SESSION-18) were inert or
// worse — hand-reading a 12-statement schedule permutation is the wrong tool;
// brute-forcing the linear extensions is the right one.
//
// Load-bearing levers (each re-verified by removal this session):
//   * the `a0v` launder (`__asm__("" : "=r"(a0v) : "0"(a0))`) — drop => 9 mismatched
//   * the `a2` $7 pin                                         — drop => 5
//   * the `a2x -> a2` launder (vs a plain copy)               — drop => 1
//   * `new_var3` (the s16 stash of dx feeding ratan2)         — drop => 2
//   * `new_var2` (the desc.y + 0x10 accumulator)              — drop => 2
// The `a2` pin's live range ENDS before the first `jal` (last use is
// `desc.z = a2[2] - a1[2]`), so it is §42e-CORRECTION / §74-safe to propagate.
//
// SYMBOLS (§58 rule 1/2): all five data externs use the canonical splat spelling and
// the engine_core.h type — `u8 D_801202A0[]`, `u8 D_801152A8[]`, `s16 D_801152AC`,
// `u8 D_8018876C[]`, `s16 currentLocationId`. symcheck: SYMS-OK, 12 symbols agree.
//
// The one deliberate divergence (§27 step 2 / rule 3): func_80135A4C's canonical
// extern is 4-arg but this call site sets only $a0-$a2, so the canonical decl is
// kept verbatim (it is also the TU's own spelling at ov_SC01_077_after.c:1651/1709)
// and the ARITY is cast at the call site.
//
// BANKING NOTE for the orchestrator (carried forward from SESSION-18, still true):
// 1 `self_decl_hdr` axis remains — DEFINE_func_8014D790's body declares
// func_8014D820, so that macro in engine_core.h needs the §85 return-axis widen
// (already applied). With the `Ent` collision gone the TU's cc1 stage is clean.










extern s16 currentLocationId;
extern u8 D_801202A0[];
extern u8 D_8018876C[];
extern u8 D_801152A8[];
extern s16 D_801152AC;
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 a0, s32 a1, s32 a2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
s32 func_8014D820(s32 a0, u16 *a1, u16 *a2x)
{
  /* BLOCK-SCOPE types — see the header note. `Ent` at file scope collides with
     src/shared/engine_types.h:434 and kills the TU's cc1 stage (exit 33). */
  typedef struct
  {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
  } V4;
  typedef struct EntD820
  {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 x;
    u16 f8;
    u16 y;
    u16 fC;
    u16 z;
    u8 p10[0x10];
    s32 f20;
    u8 p24[0x34];
    s32 f58;
    u16 f5C;
    u16 f5E;
    u8 p60[0x10C - 0x60];
  } Ent;
  int new_var2;
  s16 new_var3;
register u16 *a2 __asm__("$7");
  V4 out[3];
  V4 pos;
  Desc desc;
  Ent *ent;
  Ent *p;
  s32 dx;
  s32 dz;
  s32 ex;
  s32 ez;
  s32 r1;
  s32 r2;
  s32 r3;
  s32 ang;
  s32 x0;
  s32 y0;
  s32 z0;
  s32 tx;
  s32 tz;
  s32 ty;
  s32 r;
  s32 t;
  s32 u;
  s32 a0v;
__asm__ __volatile__("" : "=r"(a2) : "0"(a2x));
  t = a2[0];
  u = a1[0];
  dx = t - u;
__asm__ __volatile__("" : "=r"(a0v) : "0"(a0));
  new_var3 = (s16) dx;
  t = a2[2];
  u = a1[2];
  dz = t - u;
  if (((s16) (dx | dz)) == 0)
  {
    goto fail;
  }
  desc.x = dx;
  desc.y = a2[1] - a1[1];
  desc.z = a2[2] - a1[2];
  ent = *((Ent **) (a0v + 0x170));
  if (ent->f0 == 0)
  {
    goto fail;
  }
  if ((ent->f5C & 0x1000) == 0)
  {
    goto fail;
  }
  if (ent->f58 == 0)
  {
    goto fail;
  }
  if (((s32 (*)(s32, s32, s32)) func_80135A4C)(ent->f20, ent->f58, (s32) a1) == 0)
  {
    goto fail;
  }
  ex = ent->x - (*((u16 *) (a0v + 6)));
  ez = ent->z - (*((u16 *) (a0v + 0xE)));
  r1 = (s16) ratan2((s16) dz, new_var3);
  r2 = (s16) ratan2((s16) ez, (s16) ex);
  r3 = (s16) func_80012A60(r1, r2);
  if (0x400 <= r3)
  {
    goto fail;
  }
  desc.f20 = 0;
  desc.f1C = 0;
  desc.f18 = 0;
  x0 = ent->x;
  pos.x = x0;
  y0 = ent->y;
  pos.y = y0;
  z0 = ent->z;
  tx = x0 + desc.x;
  pos.z = z0;
  tz = z0 + desc.z;
  desc.x = tx;
  desc.z = tz;
  ty = (y0 + desc.y) + 8;
  desc.y = ty;
  if (currentLocationId != 0x3008)
  {
    for (p = (Ent *) D_801202A0; p < (Ent *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      func_80135888(p->f20, p->f58, (s32) (&pos), (s32) (&desc));
    }

  }
  else
  {
    ang = ratan2(((s16) x0) - ((s16) tx), ((s16) z0) - ((s16) tz)) & 0xFFF;
    func_800139C8(ang, D_8018876C, &out[0]);
    func_800139C8((s16) (ang - 0x155), D_8018876C, &out[1]);
    func_800139C8((s16) (ang + 0x155), D_8018876C, &out[2]);
    out[0].x += pos.x;
    out[0].y = pos.y;
    out[0].z += pos.z;
    out[1].x += pos.x;
    out[1].y = pos.y;
    out[1].z += pos.z;
    out[2].x += pos.x;
    out[2].y = pos.y;
    out[2].z += pos.z;
    for (p = (Ent *) D_801202A0; p < (Ent *) (D_801202A0 + 0x6480); p++)
    {
      if (p == ent)
      {
        continue;
      }
      if (p->f0 == 0)
      {
        continue;
      }
      if (p->f5C == 0)
      {
        continue;
      }
      if (p->f58 == 0)
      {
        continue;
      }
      if (func_8014DCE0((s32) p, (s32) (&pos), (s32) (&out[0])) != 0)
      {
        __builtin_memcpy((void *) ((s32) (&desc)), (void *) ((s32) (&pos)), 8);
      }
    }

  }
  r = func_80133784(0, &pos, (s32) (&desc));
  if ((r == 0) || ((r == 0x2000) && (((*(u16 *) D_801152A8) | ((u16) D_801152AC)) == 0)))
  {
    ent->x = desc.x - desc.f18;
    ent->y = desc.y;
    ent->z = desc.z - desc.f20;
    desc.x -= pos.x;
    desc.y -= pos.y;
    desc.z -= pos.z;
    *((u16 *) (a0v + 6)) = a1[0] + desc.x;
    new_var2 = desc.y;
    new_var2 = new_var2 + 0x10;
    *((u16 *) (a0v + 0xA)) = a1[1] + new_var2;
    *((u16 *) (a0v + 0xE)) = a1[2] + desc.z;
  }
  else
  {
    *((u16 *) (a0v + 6)) = a1[0];
    *((u16 *) (a0v + 0xA)) = a1[1] + 0x10;
    *((u16 *) (a0v + 0xE)) = a1[2];
  }
  return 1;
  fail:
  *((s32 *) (a0v + 0x170)) = 0;

  return 0;
}


#include "common.h"

#include "../shared/ov/func_8014DCE0.h"

#include "../shared/ov/func_8014DD8C.h"

// @class: other
// @stuck: none — MATCH (fully-handwritten scratchpad-stack-switch sequencer; byte-proven sibling DEFINE precedent func_8014CCB4, same idiom, only the jal target differs)
#include "common.h"

extern void func_8014DF94(s32 arg0);

void func_8014DF3C(void)
{
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
        "jal   func_8014DF94\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "common.h"

#include "../shared/ov/func_8014DF94.h"

/* e1b — T5b Fable5 spike: unpinned + REUSED load temps (the S11 fence) + t2 for b[2].
 * Theory: the original paired the delta loads via REUSED u16 temps (output/anti deps
 * forbid sched1 from hoisting pair-2 above subu-dx; the shared pseudos then take one
 * scratch each (v1/v0) for both pairs and reload/sched2 anti-webs lock the pairing). */
#include "common.h"

#include "../shared/ov/func_8014E048.h"

// @class: regalloc-order
// @stuck: none — MATCH (108 ins, match_one relocation-masked)
//
// Keys to the crack (all four were load-bearing; the B3 near-miss was NOT a register-pin job —
// pinning actively HURTS here, see (2)):
//
// (1) POINTER loop over an array-of-struct with sizeof == the 0x10C stride (§18 %lo-fold idiom
//     generalized to the giv layer). `for (p = base; p < base + 96; p++)` reproduces BOTH halves
//     of the "gcc loop-guard / IV-final-value" residual §17a filed as unsteerable on the sibling
//     func_8012C2D0: the ENTRY guard CSEs the bound off the just-materialized base
//     (`addiu $v0,$s3,0x6480; sltu $s3,$v0`) while the loop-BOTTOM test — rewritten by loop.c
//     AFTER invariant motion — re-materializes the folded address `%hi/%lo(D_801202A0+0x6480)`
//     (which splat names D_80126720). No separate `end` symbol is needed; do NOT try to write the
//     bound as its own extern.
// (2) The two-register walk ($s3 = p, $s2 = p+0xE) is gcc's combine_givs, NOT a source construct
//     and NOT pinnable. `record_giv` PREPENDS to bl->giv, so the LAST-discovered `p+const` address
//     becomes the combining representative -> here `p->f0E` (last in body order) -> base = p+0xE,
//     everything else folds to 0x4A/0x4E/0x12/-0x8($s2). The bare-biv address `(reg p)` is never
//     given a giv, so `p->f00` stays `0($s3)` and `sw $s3,0x170` keeps p live (biv not eliminable).
//     => Body access ORDER is load-bearing: f00, f58, f5C, f20, f06, f0E. Pinning p to `$s3`
//     DESTROYS this (loop.c rejects hard-reg bivs) -> strength reduction dies, $s2 vanishes, and
//     the entry guard folds away. Register pins were the wrong tool for this class.
// (3) `s16 dx/dz/ax/az` (HImode pseudos) give the target's `subu $v0,..` + `addu $fp,$v0,$zero`
//     truncation-move pair and the raw (unextended) live value + `sll/sra` at each use. The
//     `if ((s16)(dx|dz) != 0)` fold is what emits `or; sll 16; beqz` (one branch, not two).
// (4) DENSITY: the ax/az subtractions must happen BEFORE the first ratan2 call. Holding the four
//     u16 operands across the call instead needs 4 callee-saved regs, which starves dx/dz and
//     SPILLS them to the frame (frame 0x48 vs 0x38, +3 ins). Likewise `s32 r1 = (s16)ratan2(...)`
//     (extend eagerly, keep the extended value across call 2) vs `s16 r1` (move now, extend later)
//     — that one alone was the final 3-instruction residual.

#include "common.h"

/* stride 0x10C == the D_801202A0 entry size; keeps the symbol_ref through gcc's array-index
   addressing (§18). Named uniquely: the TU-canonical decl of the symbol itself stays `u8 []`
   (engine_core.h / DEFINE_func_8014A048 already declare it that way at file scope). */

#include "../shared/ov/func_8014E284.h"


// @class: other
// @stuck: none — MATCH (hand-written scratchpad-stack-switch trampoline; inline-asm precedent func_8014CCB4, byte-proven)
#include "common.h"

extern void func_8014E48C(s32 a0);

void func_8014E434(void)
{
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
        "jal   func_8014E48C\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014E48C.h"

#include "../shared/ov/func_8014E514.h"

#include "common.h"

// @class: loop-guard  (h_norm family exemplar, reach x138)
// @stuck: none — MATCH (59 ins) under match_one. Sibling/template: func_8014CF04 in
//         ov_SC03_099_after.c:1592.
//
// RECONCILE FIX (2026-08-01, RECONCILE lane): the whole-binary gate died with
//     src/ov_SC01_077/ov_SC01_077_after.c:2717: conflicting types for `func_8014E5B4'
//     || previous declaration at :2644
// Line 2644 is `DEFINE_func_8014E48C()`, whose macro body (src/shared/engine_core.h:13392)
// expands a file-scope `extern void func_8014E5B4(s32 a0, void *a1, void *a2);` eight lines
// above where this definition splices in. The conflict is on func_8014E5B4 ITSELF and it is
// purely the RETURN axis (params are already spelled canonically: s32/void*/void*).
//
// The return type is LOAD-BEARING here (see DECAY note below), so `void` is not an option.
// Fix = the §37/§124 ASM-LABEL ALIAS, the same lever that banked func_8014C4AC today
// (.run/sweep/*/func_8014C4AC.c): define the body under the C name aF8014E5B4 carrying
// __asm__("func_8014E5B4"). The emitted symbol is unchanged, the C identifier never collides
// with the macro's extern, and NO tracked header edit is needed — the engine_core.h:13392
// §85 return-axis widen described in the old banking note is now UNNECESSARY.
// Byte-checked: match_one MATCH (0 mismatches) before and after the rename.
// The alias line MUST travel with the body to every sibling overlay.
//
// DECAY FIX (2026-08-01, REDRAFT lane) — why the return type cannot be `void`: with `void`,
// gcc-2.7.2 drops the value axis entirely: no `addiu $v0,$zero,0x1`, no `addu $v0,$zero,$zero`
// at .L8014E674, and the `j .L8014E678` merge disappears (the taken path falls straight into
// the shared epilogue), which also frees $v0 so the last `lhu` lands in $v0 instead of the
// target's $v1. `s32` fixes all 23 mismatches at once.
//
// Keys (same D_801202A0 96-entry / stride-0x10C sweep as the func_8014CF04 and func_8014D2A0
// siblings, so most of it is the already-banked idiom):
//
//  (1) LOOP-BOUND DUALITY, register-relative BOTH ends (differs from func_8014CF04!). The
//      target computes `addiu $v1,$s1,0x6480` for the ENTRY guard and then a separate
//      `addu $s5,$v1,$zero` AFTER the guard branch for the loop-carried bound. That extra
//      copy is 1 whole instruction: the plain `e = p + 0x6480; if (p < e)` spelling folds it
//      away and compiles to 58 ins. The spelling that reproduces it is
//        `if (p < p + 0x6480) { e = p + 0x6480; ... }`
//      — the guard makes $v1, CSE turns the in-body `e = p + 0x6480` into a copy of it, and
//      regalloc does not coalesce (gcc-2.7.2 has no coalescing, regalloc.md K8). The back edge
//      then uses the register ($s5), NOT a rematerialised %hi/%lo(D_80126720) as in
//      func_8014CF04 — so do NOT reuse that sibling's absolute-bound half here.
//
//  (2) TWO INDUCTION VARIABLES, secondary base +0xE. `q = p + 0xE` carries every access except
//      the two that use the entry pointer itself (`*(u16 *)p` and `*(u8 **)(a0+0x17C) = p`):
//      offsets -0x8 / 0x0 / 0x12 / 0x4A / 0x4E off q  ==  0x6 / 0xE / 0x20 / 0x58 / 0x5C off p.
//      A single-pointer spelling is NOT equivalent: gcc emits ONE base and the function comes
//      out 56 ins (verified). The negative displacement is the tell that the second pointer is
//      in the source, not a compiler-made giv.
//
//  (3) REGISTER PINS ($16/$17) — the one non-obvious lever, and it is a genuine density
//      knife-edge (regalloc.md K2 / §RC-15). Unpinned, the .lreg reads
//        p:  9 refs / 24 insns -> floor_log2(9)*9/24 = 1.125
//        q:  8 refs / 22 insns -> floor_log2(8)*8/22 = 1.091
//      so p wins $s0 by ~3% and the whole function comes out with p/q SWAPPED (17 mismatches,
//      every one of them a bare $s0<->$s1 rename). The target wants q in $s0. Decl-order swap
//      does nothing (ties are not what decides it — p genuinely out-scores q). Rather than
//      hunt a +1-ref anchor (§RC-11 `#APP` would sit next to three delay slots that maspsx
//      fills: the `beqz $a1` slot, the `jal` slot and the `bnez` slot), pin both:
//        register u8 *p __asm__("$17");  register u8 *q __asm__("$16");
//      Both are callee-saved, so the live-across-`jal` range is §42e/§74-safe by construction
//      (the ov_SC03_099 func_8014D820 caveat only applies to caller-saved pins). Everything
//      else falls out naturally: a0->$s2, a1->$s3, a2->$s4, e->$s5.
//
//  (4) `t = *(s32 *)(q + 0x4A)` is loaded ONCE and reused as arg1 of func_80135888 — that is
//      why `lw $a1, 0x4A($s0)` sits at the zero-test rather than at the call.
//
// The func_80135888 decl below is byte-compatible with the one this TU already carries at
// ov_SC01_077_after.c:2303, so it is not a second conflict axis.

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

/* §37/§124 asm-label alias: the fleet canon declares this `extern void` (engine_core.h:13392,
 * inside DEFINE_func_8014E48C()); the byte-true body must return s32. Aliasing the C name
 * sidesteps the RETURN-axis conflict with no header edit. This line MUST travel with the body. */
s32 aF8014E5B4(s32 a0, void *a1, void *a2) __asm__("func_8014E5B4");

#include "../shared/ov/func_8014E5B4.h"


// @class: other
// @stuck: none — MATCH (handwritten scratchpad-stack-switch; exact sibling of byte-proven func_8014CCB4, only the jal callee differs)
#include "common.h"

extern void func_8014E6F8(struct SubE6F8 *a0);

void func_8014E6A0(void)
{
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
        "jal   func_8014E6F8\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014E6F8.h"

s32 func_80135888(s32, s32, M2C_UNK, M2C_UNK);      /* extern */

#include "../shared/ov/func_8014E790.h"

#include "../shared/ov/func_8014E83C.h"

// @class: other
// @stuck: none — MATCH. Inline-asm scratchpad-stack-switch sequencer (manipulates $sp), modeled on func_8014CCB4 twin. KEY FIXES vs the existing precedent: (1) NO explicit nop after `jal` (maspsx auto-inserts exactly one delay-slot nop; an explicit one doubles it); (2) NO trailing `.set reorder` (it adds an extra trailing nop). Only the jal target differs (func_8014E98C vs func_8014CD0C).
#include "common.h"

void func_8014E934(s32 _arg0)
{
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
        "jal   func_8014E98C\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014E98C.h"

// func_8014EA4C  ov_SC01_077 — MATCH (183 ins, match_one verified; Fable5 crack of CLOSE=6).
//
// Prior structural fixes (kept from the close draft, .run/t7b/close/func_8014EA4C.c):
//  FIX1: (*(s16 *)&D_80126720) read as s16 VALUE (scalar decl here; canonical banked form is
//    `extern u8 (*(s16 *)&D_80126720)[]` + `*(s16*)(*(s16 *)&D_80126720)` per engine_core.h — reconcile at bank
//    time). As an array-ptr operand the sign-test folds constant-true and deletes 17 ins.
//  FIX2: memcpy dest at sp+0x20 = buf+16 (swl 0x23/swr 0x20).
//
// FABLE5 LEVERS (all three byte-verified this run; siblings/citations):
//  L1 (C1, idx69-71 "sw wedged between the arg loads"): arg-2 must be read as a STRUCT
//    MEMBER — ((struct { s32 w; } *)q)->w — not q[0]/*q. gcc-2.7.2 sched.c:817-839
//    true_dependence lets a varying-address load cross a fixed-symbol store ONLY if the
//    load MEM has /s (MEM_IN_STRUCT_P); expr.c:4568-4577 sets /s iff the INDIRECT_REF
//    address "was computed by addition" (PLUS_EXPR) or is aggregate. q[-0xe] keeps its
//    PLUS_EXPR -> /s -> hoists; q[0] folds +0 away -> plain MEM -> spurious dep on
//    `sw $0,D_801150D8` -> stuck below it. COMPONENT_REF -> /s -> dep gone -> backward
//    scheduler emits [lw a0][lw a1][sw][jal] = target. (Same lever as matched sibling
//    DEFINE_func_8014EE14, engine_core.h:24926; guards stay plain *q so CSE still reloads.)
//  L2 (C2, idx135-137 abs copy): the |D_801152AA| test must be `s32 t = D_801152AA;
//    if (t < 0) t = -t; if (0x800 < (s16)t)`. With s16 t, `t = -t` is HImode: neg into a
//    fresh SImode pseudo + subreg-truncate copy back -> `move $3,$2; negu $3,$3` (dbr fills
//    the bgez slot with the copy). With s32 t the neg is SImode in-place -> `negu $2,$2`,
//    nop slot, and the (s16) cast at the USE gives the joined sll/sra pair. (Sibling
//    DEFINE_func_8014EE14 uses exactly this form.)
//  L3 (frame 0x60 — the "knife-edge" dissolved): the close draft's 0x60 was buf[16]
//    (0x10 @sp+0x10) + THREE phantom 8-byte spill slots. A phantom = a combine-orphaned
//    sign-extend intermediate: mips.md:2340-2359 extendhisi2 at -O2 force_not_mem's every
//    lh site into HI-load + ashift/ashiftrt pair with a fresh SImode temp; combine remerges
//    them into one lh and, when the REG_DEAD home-search hits a CODE_LABEL, parks the note
//    on a bare (use (reg)) insn (combine.c:10829-10841); regclass then sees only the
//    constraint-less USE -> preferred class none (".lreg: ST_REGS or none") -> no hard reg
//    -> reload alter_reg (reload1.c:2309, assign_stack_local at :2352) gives it a stack
//    slot, +8 bytes each (STACK_BOUNDARY=64), emitting ZERO insns. Two phantoms here are
//    intrinsic (the label-headed *(s16*)(a2+0)/(a2+4) arm sites); `s16 t` contributed the
//    third. Retyping t s32 (L2) removes one phantom (-8); buf[16]->buf[24] repays the 8
//    (dest buf+16 stays sp+0x20, identical swl/swr; the copy is no longer OOB). Frame
//    parity is PHANTOM-SLOT COUNT parity — count `(use (reg:SI` in the .combine dump
//    (the shipped cc1 DOES emit -dr/-dc/-dl/-dg dumps; only .sched/.greg-era claims of
//    "stripped" were wrong for these flags).

#include "../shared/ov/func_8014EA4C.h"

// @class: other
// @stuck: none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper; no trailing .set reorder — that adds a stray epilogue nop)
/*
 * HANDWRITTEN scratchpad-stack-switch wrapper: temporarily repoints $sp into the
 * D-cache scratchpad stack held at *(0x1F8003FC), calls func_8014ED80, stashes the
 * return value through D_801D9618, restores $sp and returns it.
 * Manipulating $sp is not expressible in C; full inline asm (manages its own frame).
 */
extern s32 func_8014ED80(struct SubED80 *a0);
extern int D_801D9618;

void func_8014ED28(s32 _arg0)
{
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
        "jal   func_8014ED80\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014ED80.h"

// @class: schedule
// @stuck: none — MATCH (248 ins, match_one verified). The long-standing §20 "store-vs-load"
//   near-miss, closed by TWO new byte-proven levers (both read straight out of gcc-2.7.2 source):
//
//   (1) PROLOGUE PAIR ORDER (sched1 "birthing" boost, sched.c adjust_priority): sched1 schedules
//       each bb BACKWARD and boosts any insn whose dest reg is set EXACTLY ONCE in the fn
//       (birthing_insn_p: REG_N_SETS==1) to max priority -> placed LATE in the block. The pinned
//       param copies (s0=a0/s7=a1/s2=a2, single-set) got boosted and sank BELOW the multi-set
//       constant inits (s6=0/s5=8/s4=8 — reassigned in switch/loops, so never boosted).
//       FIX: one zero-byte NON-volatile re-tie asm per param — __asm__("" : "=r"(x) : "0"(x)) —
//       placed in a LATER basic block (after the switch). It counts as a 2nd SET of the pinned reg
//       (REG_N_SETS=2 -> boost off) while emitting nothing, and being in another bb it adds no
//       scheduling edges inside bb0. All six inits then tie at priority 1 and the LUID (source
//       order) tie-break puts params first = target. (volatile would work too but risks acting as
//       a barrier; non-volatile with a USED output is kept and is codegen-free.)
//
//   (2) STORE-VS-LOAD (sched.c true_dependence + expr.c MEM_IN_STRUCT_P): the target loads BOTH
//       call args (lw a0,-0x38(s3); lw a1,0(s3)) BEFORE the `D_801150D8 = 0` store; ours pinned
//       the a1 load below the store. Root cause: gcc-2.7.2's scheduler CAN reorder a pointer load
//       across a fixed-symbol store ONLY when the load's MEM has the /s flag (MEM_IN_STRUCT_P);
//       expr.c sets that flag iff the address was "computed by addition" (PLUS_EXPR) or is a
//       struct member. `piVar5[-0xe]` (offset!=0) gets /s and hoists; `*piVar5` / `piVar5[0]`
//       (front end folds +0 away) stays a plain mem -> conservative true-dependence on the store
//       -> stuck below it. FIX: read the arg as a struct member — ((struct { s32 w; }*)piVar5)->w —
//       which is a COMPONENT_REF -> /s flag -> dependence gone -> the hazard-driven backward
//       scheduler emits [lw a0][lw a1][sw $0,sym][jal] exactly like the target. The loop guards
//       stay `*piVar5` (plain) so CSE's fixed-scalar-store invalidation still forces the separate
//       reload the target shows.
//
//   Regalloc forced with §17 pins (s0/s7/s2/s6/s5/s4); the loop IV pair (psVar4/piVar5) is left
//   unpinned so loop strength-reduction still derives piVar5 as a giv (preheader addiu s3,s1,0x58
//   + latch bump) and naturally claims $s1/$s3 (the only free callee-saved regs).
//
//   WHOLE-BINARY GATE (banked:1) — the §20 DEF-side conflict was NOT intrinsic here; resolved:
//   the banked caller macro DEFINE_func_8014ED80 (engine_core.h:13403) declared `extern VOID
//   func_8014EE14(...)`, which in-TU precedes this s32 def -> `conflicting types` compile error
//   (the def MUST be s32: void return DCEs uVar8 -> frame 0x60, s6 gone, no byte-match). FIX =
//   change that macro's extern VOID->S32 (byte-NEUTRAL for func_8014ED80 fleet-wide: it discards
//   func_8014EE14's return, so `jal` + arg setup are identical; verified via make check-all,
//   136/136 still byte-identical). The general lever for a §20 DEF-side return-type wall: if the
//   ONLY conflicting caller-decl is a shared macro that DISCARDS the return, widening that macro's
//   extern to the def's return type is byte-neutral and dissolves the wall (no INCLUDE_ASM-side
//   escape needed — the macro DOES declare the C symbol, unlike a bare INCLUDE_ASM stub).
//   DATA: D_80126720 canonicalized to `u8 []` (array symbol), read `(s32)*(s16*)D_80126720` per
//   the `lh` (signedness-agnostic store sites unaffected). Callee func_80135A4C extern below is the
//   canonical (engine_core.h:11555), called through the §17a-1 fn-ptr cast idiom.
#include "../shared/ov/func_8014EE14.h"

// @class: other
// @stuck: none — MATCH (fully-handwritten scratchpad-stack-switch sequencer; manipulates $sp; modeled byte-for-byte on the proven sibling func_8014CCB4 in ov_SC01_077.c)
#include "common.h"

extern s32 func_8014F24C(struct SubF24C *a0);

void func_8014F1F4(void)
{
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
        "jal   func_8014F24C\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014F24C.h"

#include "../shared/ov/func_8014F2E0.h"

#include "../shared/ov/func_8014F3E8.h"


// @class: other
// @stuck: none — MATCH (handwritten scratchpad-stack-switch sequencer; byte-proven DEFINE_func_8014CCB4 precedent. Do NOT write an explicit nop in the jal delay slot: maspsx 2.56 reorders the following lui %hi into the slot and re-emits the nop, so an explicit one is a redundant +1 ins.)
#include "common.h"

extern s32 func_8014F4C0();

s32 func_8014F468(void)
{
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
        "lui   $at, %%hi(D_801D961C)\n"
        "sw    $v0, %%lo(D_801D961C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D961C)\n"
        "lw    $v0, %%lo(D_801D961C)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

// @class: plumbing
// @stuck: none — MATCH 141/141 both standalone (match_one) AND byte-verified IN-TU (draft
//         substituted into the real src/ov_SC01_077/ov_SC01_077_after.c, full cpp+cc1+maspsx+as:
//         0 mismatched). Needs ONE byte-neutral decl fix the drafter may not touch:
//           tools/fix_arity_callers.py --apply --funcs func_8014F4C0 --binary ov_SC01_077 \
//                                      --drafts .run/drafts-t3-wave
//         (rewrites ov_SC01_077_after.c:1898 `extern s32 func_8014F4C0(void);` -> `(...)();`.
//          --binary is REQUIRED: the tool defaults to engine_core.h only, but this caller decl
//          lives in the overlay's own .c.) Without it the TU fails `conflicting types for
//          func_8014F4C0` — that lone error is the whole B3 gate gap; with it the TU compiles
//          clean and the bytes are identical.

/* func_8014F4C0 — the simpler twin of the already-banked DEFINE_func_8014F74C()
 * (src/shared/engine_core.h:25443). Same shape: build a PosT probe + a MoveT move vector from
 * the entity, call the collision query func_80133784, then splat one of three canned 8-byte
 * blobs into e+0x120 per the returned hit mask. Every idiom below (PosT/MoveT locals, the
 * x6/xA/xE forwarding temps, *(u8*)&w / (u32)w>>13, __builtin_memcpy for the byte-aligned
 * 8-byte blob copies) is lifted verbatim from that byte-proven sibling, and every extern uses
 * that sibling's canonical type — in particular `extern s16 D_801152B0;` (NOT `u8 D_801152B0[]`),
 * because DEFINE_func_8014F74C() is instantiated later in this same TU
 * (src/ov_SC01_077/ov_SC01_077_after.c:1973) and re-declares it at block scope.
 *
 * NOTE: func_8014F74C is called with NO argument — the asm has a bare `jal func_8014F74C; nop`
 * with no $a0 setup (it inherits the incoming $a0). Declared no-proto to stay compatible with
 * the DEFINE_func_8014F74C() def `int func_8014F74C(s32 arg0)` instantiated later in the TU.
 *
 * DEF-SIG / GATE NOTE: this TU already carries a file-scope `extern s32 func_8014F4C0(void);` at
 * ov_SC01_077_after.c:1898, written only so the inline-asm caller func_8014F468 has a name in
 * scope (its `jal` is inside __asm__, so the decl emits nothing and is byte-neutral). It
 * conflicts with this def's parameter. Return type is s32 and the param is s32 (promotion-safe),
 * so the §17a-3b no-proto rewrite `extern s32 func_8014F4C0();` (fix_arity_callers.py) resolves
 * it; deleting line 1898 outright is equally byte-neutral. */

#include "common.h"

#ifndef BFM_ENGINE_TYPES_H


#endif

#include "../shared/ov/func_8014F4C0.h"


// @class: plumbing
// @stuck: none — MATCH (22 ins, relocation-masked). Handwritten scratchpad-stack-switch
//         wrapper, full inline asm like DEFINE_func_80155FF8. NOTE: do NOT write an explicit
//         "nop" after "jal func_8014F74C" — maspsx --aspsx-version=2.56 auto-fills the jal
//         delay slot with a nop; an explicit one yields a double-nop (+1 ins). %hi/%lo must be
//         escaped as %%hi/%%lo inside __asm__ (bare % is read as an operand placeholder).

/* HANDWRITTEN scratchpad-stack-switch wrapper (same idiom as func_80155FF8 /
 * func_80128564): temporarily repoints $sp into the D-cache scratchpad stack held
 * at *(0x1F8003FC), calls func_8014F74C, stores its $v0 result to D_801D961C, then
 * restores $sp and returns the stored value. Manipulating $sp is not expressible in
 * C; full inline asm (manages its own frame). */

extern int func_8014F74C();

int func_8014F6F4(void) {
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
        "jal   func_8014F74C\n"
        "lui   $at, %%hi(D_801D961C)\n"
        "sw    $v0, %%lo(D_801D961C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D961C)\n"
        "lw    $v0, %%lo(D_801D961C)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

// @class: schedule
// @stuck: none — MATCH (174 ins). Last mile: §5a volatile barrier blocked gcc jump-threading
//         the bnez through .L8014F92C; literal `return 0/0x8000` (not the s1 var) in the ret==0
//         cascade; compound `ret &= ~0x2000; ret |= 0x4000;` forced the in-place and/ori.

#include "../shared/ov/func_8014F74C.h"

// @class: other
// @stuck: none — MATCH (full inline-asm $sp-switch trampoline w/ 0x40000 guard, jal func_8014FA70, stash D_801D961C; maspsx auto-fills jal delay slot)

extern s32 func_8014FA70(s32 a0);
extern s32 D_801D961C;

void func_8014FA04(s32 a0)
{
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
        "lui   $at, %%hi(D_801D961C)\n"
        "sw    $v0, %%lo(D_801D961C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D961C)\n"
        "lw    $v0, %%lo(D_801D961C)($v0)\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014FA70.h"

// @class: other
// @stuck: none — MATCH (22 ins, relocation-masked). Handwritten scratchpad-stack-switch
//   trampoline: byte-identical to the matched in-TU sibling func_8014F6F4 (line ~2005),
//   differing ONLY in the callee (func_8014FC18 vs func_8014F74C). Full inline asm manages
//   its own frame; both the callee and the D_801D961C global live inside the asm, so NO C
//   externs are declared — this sidesteps the canonical-sig-layer reconcile that CC1_FAILed
//   the register-asm draft (func_8014FC18/D_801D961C are declared elsewhere in the TU).
//   maspsx --aspsx-version=2.56 auto-fills the jal delay slot with a nop, so do NOT write an
//   explicit nop after `jal` (double-nop = +1 ins); %hi/%lo escaped as %% inside __asm__.
//   gcc emits only the `jr $ra; nop` epilogue (leaf, no locals it can see) → exactly 22 ins.
int func_8014FBC0(void) {
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
        "jal   func_8014FC18\n"
        "lui   $at, %%hi(D_801D961C)\n"
        "sw    $v0, %%lo(D_801D961C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D961C)\n"
        "lw    $v0, %%lo(D_801D961C)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_8014FC18.h"

// @class: other
// @stuck: none — MATCH; handwritten scratchpad-stack-switch sequencer (manipulates $sp), modeled on byte-proven func_8014CCB4 precedent (identical body, callee swapped to func_8014FD54)
#include "common.h"

extern int func_8014FD54(int param_1);

void func_8014FCFC(void)
{
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
        "jal   func_8014FD54\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

// @class: regalloc-order
// @stuck: none — MATCH; pinned result to $v0 so ret lands in $v1 (target's alloc); func_80149290 3-arg via call-site cast

#include "../shared/ov/func_8014FD54.h"

#include "../shared/ov/func_8014FDF4.h"

#include "../shared/ov/func_8014FE60.h"

#include "common.h"

#include "../shared/ov/func_8014FFDC.h"


#include "../shared/ov/func_80150150.h"






#include "../shared/ov/func_80150170.h"



#include "../shared/ov/func_801502EC.h"


#include "../shared/ov/func_80150460.h"

// @class: other
// @stuck: none — MATCH (fully-handwritten scratchpad-stack-switch sequencer; manipulates $sp directly around a call — no normal C produces this; modeled verbatim on the byte-proven func_8014CCB4 inline-asm precedent in this same overlay)
#include "common.h"

extern void func_801504D8(u16 *a0);

s32 func_80150480(s32 _arg0)
{
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
        "jal   func_801504D8\n"
        "lui   $at, %%hi(D_801D9618)\n"
        "sw    $v0, %%lo(D_801D9618)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801D9618)\n"
        "lw    $v0, %%lo(D_801D9618)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}

#include "../shared/ov/func_801504D8.h"

#include "../shared/ov/func_80150528.h"

#include "../shared/ov/func_801505FC.h"



s32 func_801506A4(s32 arg0, s32 arg1) {
    extern void func_80150820(int, unsigned short);
    extern void func_8015086C(int);
    extern unsigned short D_8018877C[];
    extern unsigned short D_80188784[];
    extern unsigned short D_8018878C[];

    int mode;

    mode = ((struct Ent_801506A4 *)arg1)->unk0;
    ((struct Ent_801506A4 *)arg1)->unk5C |= 1;
    switch (mode) {
    case 0x31:
        ((void(*)(int))func_80147324)(0x452);
        ((void(*)(int, unsigned))func_8014ADA8)(((int)arg0), D_8018877C[((struct Ent_801506A4 *)arg1)->unk70]);
        ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 3, D_8018877C[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0x32:
        if ((*(unsigned short*)&D_80078EB4) != 0) {
            ((void(*)(int))func_80147324)(0x452);
            ((void(*)(int, unsigned, int))func_8014BB24)(((int)arg0), D_80188784[((struct Ent_801506A4 *)arg1)->unk70], 1);
            ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 2, D_80188784[((struct Ent_801506A4 *)arg1)->unk70]);
        }
        break;
    case 0x33:
        ((void(*)(int))func_80147324)(0x452);
        func_80150820(((int)arg0), D_8018878C[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0xC5:
    case 0x27B:
        ((void(*)(int))func_80147324)(0x452);
        func_8015086C(((int)arg0));
        break;
    }
}


#include "../shared/ov/func_80150820.h"

// @class: plumbing
// @stuck: none — MATCH expected; param reused across calls naturally lands in $s0

#include "../shared/ov/func_8015086C.h"

#include "../shared/ov/func_801508B4.h"

#include "../shared/ov/func_801508F8.h"

// @class: struct
// @stuck: none — MATCH (73 ins)
#include "common.h"

extern S16 D_801D8924;
extern s32 D_80188794;
extern s32 D_80126990;
extern s32 D_80126994;
extern u8 D_80126948[];
extern s32 func_80021174(s32 a0, s32 a1);

s32 func_8015094C(s32 param_1) {
    struct { s32 x, mid, y; s32 _pad[9]; } arg;   /* 0x30 @ 0x10 */
    S16 local;                                     /* 0x10 @ 0x40 */
    s32 pad1[4];                                    /* 0x10 @ 0x50 */
    register u8 *cam __asm__("$17") = D_80126948;
    s32 ret;

    local = D_801D8924;
    arg.x = *(short *)(param_1 + 6);
    arg.mid = D_80126994;
    arg.y = *(short *)(param_1 + 0xe);
    ret = func_80021174(D_80188794, (s32)&arg);
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

// @class: other
// @stuck: none — MATCH (46 ins)
// Full inline-asm $sp-switch trampoline (same idiom as byte-proven sibling func_8014FA04):
// 3x lh short-circuit guard (6/0x88, 0xA/0x8A, 0xE/0x8C) then a 0x40000 flag guard;
// when the flag is clear, repoints $sp into the D-cache scratchpad stack held at
// *(0x1F8003FC), calls func_8014FA70(s0) on that stack and stashes $v0 to D_801D961C,
// then restores $sp; finally calls func_80015978(s0+4, s0+0x88). Manipulating $sp is not
// expressible in C, so this is full inline asm (manages its own frame).
//
// maspsx gotcha (the lever for this fn): match_one's maspsx STRIPS each inline-asm line, so
// a space-form ".set noreorder" loses its tab and is NOT recognized (line 845 needs ".set\t")
// -> is_reorder stays True -> maspsx auto-inserts a "nop  # branch/jump" after every `bne`/
// `beq`/`jal` (clobbering the real delay-slot instrs in this fn). FIX: write ".set\tnoreorder"
// with a literal TAB so maspsx honors it and inserts NO nops (we fill every delay slot by hand).
// Then close with ".set\treorder" (tab) so maspsx re-pads the delay slot of cc1's epilogue
// `j $31` -> yields the trailing `jr $ra; nop`. (NOTE: `bnez`/`beqz` are NOT in maspsx's
// branch_mnemonics set, which is why the sibling's space-form ".set noreorder" happened to
// work — it had no `bne`/`beq`; this fn does, so the tab form is required.)
#include "common.h"

extern s32 func_8014FA70(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 D_801D961C;

void func_80150A70(s32 a0)
{
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
        "lui   $at, %%hi(D_801D961C)\n"
        "sw    $v0, %%lo(D_801D961C)($at)\n"
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

extern s32 D_800AE6B0;
extern void (*D_80188798[])(void);

void func_80150B28(int param_1) {
    u32 idx;
    register u32 sub __asm__("$2");

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_80188798[sub]();
        }
    }
    *(u16 *)(param_1 + 0x16C) = 0;
}

#include "../shared/ov/func_80150B9C.h"

#include "../shared/ov/func_80150BA4.h"

#include "../shared/ov/func_80150BC8.h"

#include "../shared/ov/func_80150C48.h"

#include "../shared/ov/func_80150CA0.h"

#include "../shared/ov/func_80150CC4.h"

#include "../shared/ov/func_80150CE4.h"

#include "../shared/ov/func_80150D04.h"

#include "../shared/ov/func_80150D24.h"

#include "../shared/ov/func_80150D44.h"

#include "../shared/ov/func_80150D64.h"

#include "../shared/ov/func_80150D84.h"

#include "../shared/ov/func_80150DA4.h"

#include "../shared/ov/func_80150DC4.h"

#include "../shared/ov/func_80150DE4.h"

#include "../shared/ov/func_80150E04.h"

#include "../shared/ov/func_80150E24.h"

#include "../shared/ov/func_80150E44.h"

#include "../shared/ov/func_80150E64.h"

#include "../shared/ov/func_80150E84.h"

#include "../shared/ov/func_80150EA4.h"

#include "../shared/ov/func_80150EC4.h"

#include "../shared/ov/func_80150F78.h"

#include "../shared/ov/func_80150F80.h"

#include "../shared/ov/func_80150FB4.h"

#include "../shared/ov/func_80150FD8.h"

#include "../shared/ov/func_80151014.h"

#include "../shared/ov/func_80151038.h"

#include "../shared/ov/func_80151070.h"

#include "../shared/ov/func_80151094.h"

#include "../shared/ov/func_801510B8.h"

#include "../shared/ov/func_801510C0.h"

#include "../shared/ov/func_801510C8.h"

#include "../shared/ov/func_801510EC.h"

#include "../shared/ov/func_80151110.h"

#include "../shared/ov/func_80151130.h"

#include "../shared/ov/func_80151138.h"

#include "../shared/ov/func_8015115C.h"

#include "../shared/ov/func_80151164.h"

#include "../shared/ov/func_80151184.h"

#include "../shared/ov/func_801511A8.h"

#include "../shared/ov/func_801511C4.h"

#include "../shared/ov/func_801511E0.h"

#include "../shared/ov/func_80151204.h"

#include "../shared/ov/func_80151238.h"

#include "../shared/ov/func_8015126C.h"

/* func_80151664 — INTEGRATE lane.
 * Fleet canon (src/shared/engine_core.h:2924, inside DEFINE_func_8015410C()) declares
 *   extern void func_80151664(void);
 * so a `void func_80151664(s32 a0)` definition is `conflicting types` in every TU that
 * expands that macro (ov_SC01_077_after.c:3910 does).  Cookbook §73 PARAMS axis / §42:
 * keep the canonical (void) signature and read the incoming argument through a $a0 pin.
 * The decl below is reproduced verbatim so this file compiles the real conflict. */
extern void func_80151664(void);

extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_801472B4(void *a0);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80153C18();  /* fleet canon: K&R empty prototype (engine_core.h:75, :1682 defines it (void));
                                 * a prototyped (s32) decl is `conflicting types` in this TU. Arg still
                                 * passes in $a0 under default promotions -> codegen unchanged. */

#include "../shared/ov/func_80151664.h"


#include "../shared/ov/func_801516F0.h"

#include "../shared/ov/func_8015173C.h"

// @class: regalloc-order
// @stuck: none — MATCH (D_8011DB1A held in $a0 via register pin $4 after the func_801725CC call)
#include "common.h"

#include "../shared/ov/func_80151780.h"

#include "../shared/ov/func_80151878.h"

#include "../shared/ov/func_80151880.h"

#include "../shared/ov/func_801518D8.h"

#include "../shared/ov/func_80151924.h"



void func_80151944(void *a0) {

    extern void (*D_8018882C[])(void);
    D_8018882C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80151980.h"

// @class: plumbing
// @stuck: none — MATCH (71 ins, relocation-masked)
#include "common.h"

#include "../shared/ov/func_801519C8.h"

// @class: plumbing
// @stuck: none — MATCH expected; func_801542DC called 3-arg vs 2-arg canonical needs call-site cast

#include "common.h"

#include "../shared/ov/func_80151AE4.h"

#include "common.h"

/* func_80151B98 — modelled on the byte-proven near-twin DEFINE_func_80152500()
 * in src/shared/engine_core.h: same lhu(+0xB8)==0x8000 head and the identical
 * explicit-goto switch tail (case bodies sunk out-of-line in target memory
 * order, case 1 ending in `j` to the shared 8014C010 tail). */

#include "../shared/ov/func_80151B98.h"


#include "common.h"

/* Signatures follow the shared engine-core convention (cf. DEFINE_func_80152790,
 * the near-identical sibling): func_80153C18 keeps the K&R empty prototype because
 * every engine-core caller passes it an argument the real definition ignores. */
#include "../shared/ov/func_80151C54.h"


extern void (*D_8018883C[])(void *);

void func_80151D24(void *a0)
{
    D_8018883C[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_80151D60.h"

// @class: schedule
// @stuck: none — MATCH (50/50). Branch-polarity invert (if>=0x401 -> fall-through 0xC00 case) fixed bnez/li-swap; zero-code __asm__ barrier before func_80149020 anchored the two stores ahead of the call's a0=s0 delay-slot fill.

#include "../shared/ov/func_80151DB0.h"

#include "../shared/ov/func_80151E78.h"

#include "../shared/ov/func_80151ECC.h"

#include "../shared/ov/func_80151F38.h"

#include "../shared/ov/func_80151FB4.h"

extern void (*D_80188860[])(void *);

void func_80152058(void *a0)
{
    D_80188860[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_80152094.h"

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
extern u8 D_80062C04[];
extern M2C_UNK D_80188850;

void func_801520DC(s32 arg0)
{
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80188850);
    func_801477E8(arg0, 0x40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146A6C(0x10, arg0, M2C_FIELD(arg0, s16 *, 6), M2C_FIELD(arg0, s16 *, 0xA), (s32) M2C_FIELD(arg0, s16 *, 0xE), 0, 0);
    func_80147324(0x441);
    func_80146CA0(arg0);
}

#include "../shared/ov/func_80152194.h"

#include "../shared/ov/func_8015220C.h"

#include "../shared/ov/func_80152254.h"

#include "../shared/ov/func_801522CC.h"


extern void (*D_80188874[])(void *);

void func_80152370(void *a0)
{
    D_80188874[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_801523AC.h"

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

extern u8 D_80062C04[];
extern M2C_UNK D_800D5880;
extern s32 D_800D58AC;
extern u8 D_80188880[];

void func_801523F4(s32 arg0)
{
    s32 pad[4];
    s32 buf[4];
    register s32 s0a __asm__("$16");                    /* $s0 = buf */
    register s32 s2a __asm__("$18") = (s32)&D_80188880; /* $s2 = &D_80188880 */

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

// @class: schedule
// @stuck: none — MATCH (61 ins). Keys: lhu+0x8000 (unsigned short, not lh+-0x8000), and explicit goto chain in target memory order so both case bodies sink out-of-line (case1 ends in j tail).

#include "../shared/ov/func_80152500.h"

#include "../shared/ov/func_801525F4.h"

extern void (*D_80188890[])(void *);

void func_80152698(void *a0)
{
    D_80188890[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_801526D4.h"

#include "../shared/ov/func_80152714.h"

#include "../shared/ov/func_80152790.h"

extern void (*D_801888A8[])(void *);

void func_8015282C(void *a0)
{
    D_801888A8[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_80152868.h"

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
extern u8 D_80062C04[];
extern M2C_UNK D_800D5880;
extern M2C_UNK D_80188898;

void func_801528B0(s32 arg0)
{
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_80188898);
    func_801477E8(arg0, 0xFFF00000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}

#include "../shared/ov/func_8015294C.h"

#include "../shared/ov/func_80152A08.h"

#include "../shared/ov/func_80152A50.h"

#include "../shared/ov/func_80152AC8.h"

extern void (*D_801888BC[])(void *);

void func_80152B6C(void *a0)
{
    D_801888BC[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_80152BA8.h"

#include "../shared/ov/func_80152BF0.h"

#include "../shared/ov/func_80152C40.h"

#include "../shared/ov/func_80152C80.h"


extern void (*D_801888D8[])(void *);

void func_80152D24(void *a0)
{
    D_801888D8[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_80152D60.h"

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
extern s32 D_80062C14;
extern M2C_UNK D_800D5880;
extern M2C_UNK D_801888C8;

void func_80152DA8(s32 arg0)
{
    func_80019064(&D_80062C14);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    M2C_FIELD(arg0, s8 *, 0xDF) = 8;
    func_80146DB8(arg0, &D_801888C8);
    func_801477E8(arg0, 0xFFE40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}

#include "../shared/ov/func_80152E4C.h"

#include "../shared/ov/func_80152EFC.h"

#include "../shared/ov/func_80152F44.h"

#include "../shared/ov/func_80152FBC.h"

extern void (*D_801888EC[])(void *);

void func_80153060(void *a0)
{
    D_801888EC[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_8015309C.h"

#include "../shared/ov/func_801530E4.h"

#include "../shared/ov/func_80153150.h"

#include "../shared/ov/func_801531BC.h"

#include "../shared/ov/func_80153204.h"

#include "../shared/ov/func_8015327C.h"

extern void (*D_80188900[])(void *);

void func_80153320(void *a0)
{
    D_80188900[*(u16 *)((s32)a0 + 0x2)](a0);
}

#include "../shared/ov/func_8015335C.h"

extern void func_80019064(void *a0);
extern void func_80149020(s32 *a0);
struct S;
#include "../shared/ov/func_801533A4.h"

#include "../shared/ov/func_80153410.h"

#include "../shared/ov/func_80153490.h"

#include "../shared/ov/func_801534D8.h"

#include "../shared/ov/func_80153550.h"

#include "common.h"

void func_8014ED28(s32 a0);
void func_80146D90(s32 a0);
void func_8014CC28(s32 a0);
void func_8014FA04(s32 a0);

#include "../shared/ov/func_801535F4.h"

#include "../shared/ov/func_8015369C.h"

// @class: regalloc-order
// @stuck: none — MATCH
#include "../shared/ov/func_801536DC.h"

// @class: schedule
// @stuck: none — MATCH (94 ins). Keys: shared-ret0 goto into nonzero block (§16);
//   memcpy(dst,src,8) for the unaligned lwl/lwr/swl/swr 8-byte copies (sibling func_80146FC4);
//   pin the bVar1*4 temp to $3/v1 so it lands in the bnez delay slot, s2 is a separate copy,
//   and the subtract reuses v1 (the loop-entry schedule).

#include "../shared/ov/func_80153800.h"

#include "../shared/ov/func_80153978.h"

#include "common.h"

#include "../shared/ov/func_801539F8.h"

#include "../shared/ov/func_80153B58.h"

#include "../shared/ov/func_80153BD8.h"

#include "../shared/ov/func_80153BF0.h"

#include "../shared/ov/func_80153C18.h"

#include "../shared/ov/func_80153C30.h"

#include "common.h"

#include "../shared/ov/func_80153C44.h"

#include "../shared/ov/func_80153C74.h"

#include "../shared/ov/func_80153C8C.h"

#include "../shared/ov/func_80153C9C.h"

#include "../shared/ov/func_80153CBC.h"

// @class: struct
// @stuck: none — MATCH (expected); dispatch-table %lo-fold via extern fn-ptr array, s0 holds param across both calls
extern void func_80019064(void *a0);
extern s32 D_80188914;
extern void (*D_8018893C[])(void *a0);
extern s16 D_8011DB0C;
extern u16 D_8011F748;

void func_80153CCC(S80153CCC *a0) {
    ((s32 (*)(s32))func_80019064)((s32)&D_80188914);
    D_8018893C[a0->idx](a0);
    D_8011DB0C = 0;
    D_8011F748 = 0;
}

#include "../shared/ov/func_80153D34.h"

// @class: regalloc-order
// @stuck: none — MATCH (33/33)

extern void func_80147324(s32 arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern s16 currentLocationId;
extern u8 D_8018891C;

void func_80153D7C(s32 param_1)
{
    func_80147324(0x451);
    func_80154274((s32 *)param_1, (s32)&D_8018891C);
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

// @class: regalloc-order
// @stuck: none — MATCH (195 ins). Levers: pins s0/s1/s2/s3 + (u16) masks force redundant andi + handler blocks placed last via forward-goto (switch + DB0C dispatch) + the mask-temp `t` pinned to $2/$v0 to break gcc's andi-into-$s1 coalescing (andi v0,s1 / srl s1,v0). D_8011DB0C typed u16 (lhu) but loaded into s32 db0c for slti compares. void-decl callees (153C18/15410C/14B310) called with a0=s0 via call-site cast.

#include "../shared/ov/func_80153E00.h"

#include "../shared/ov/func_8015410C.h"

#include "../shared/ov/func_80154134.h"

#include "../shared/ov/func_80154150.h"

#include "../shared/ov/func_80154190.h"

#include "../shared/ov/func_801541D8.h"

#include "../shared/ov/func_80154218.h"

#include "../shared/ov/func_80154274.h"

#include "../shared/ov/func_801542A4.h"

#include "../shared/ov/func_801542DC.h"

#include "common.h"

#include "../shared/ov/func_8015430C.h"

#include "common.h"

#include "../shared/ov/func_80154358.h"

#include "../shared/ov/func_80154418.h"
