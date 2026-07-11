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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801457A4);

DEFINE_func_801458E0()  /* dedup: shared engine-core @0x801458E0 (src/shared) */

DEFINE_func_801458E8()  /* dedup: shared engine-core @0x801458E8 (src/shared) */

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

DEFINE_func_80145B24()  /* dedup: shared engine-core @0x80145B24 (src/shared) */

DEFINE_func_80145BF8()  /* dedup: shared engine-core @0x80145BF8 (src/shared) */

DEFINE_func_80145C54()  /* dedup: shared engine-core @0x80145C54 (src/shared) */

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

DEFINE_func_80146014()  /* dedup: shared engine-core @0x80146014 (src/shared) */

DEFINE_func_80146074()  /* dedup: shared engine-core @0x80146074 (src/shared) */

// @class: other
// @stuck: none — MATCH (handwritten scratchpad-stack-switch trampoline; 3 calls + a beqz guard. Direct sw $sp,0($t0) (no lw $t1 indirection); D_801D9610 stashed/tested. maspsx rules: no explicit jal-delay nop, no trailing .set reorder, %%hi/%%lo escaped.)
#include "common.h"

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

DEFINE_func_80146128()  /* dedup: shared engine-core @0x80146128 (src/shared) */

// @class: struct
// @stuck: none — MATCH (fnptr-table idiom: D_8018860C[u8 idx](&arg))
extern void (*D_8018860C[])(void *);
extern u8 D_80126BA4;
extern s32 D_80126B58;

void func_80146360(void)
{
    D_8018860C[D_80126BA4](&D_80126B58);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801463A0);

DEFINE_func_80146534()  /* dedup: shared engine-core @0x80146534 (src/shared) */

DEFINE_func_80146554()  /* dedup: shared engine-core @0x80146554 (src/shared) */

DEFINE_func_80146578()  /* dedup: shared engine-core @0x80146578 (src/shared) */

DEFINE_func_8014659C()  /* dedup: shared engine-core @0x8014659C (src/shared) */

DEFINE_func_801465C0()  /* dedup: shared engine-core @0x801465C0 (src/shared) */

DEFINE_func_801465E4()  /* dedup: shared engine-core @0x801465E4 (src/shared) */

DEFINE_func_80146608()  /* dedup: shared engine-core @0x80146608 (src/shared) */

extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);

DEFINE_func_801466B4()  /* dedup: shared engine-core @0x801466B4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801466F0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80146750);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014680C);

/* canonical-sig: engine_core.h declares `extern s32 D_8011F750;` */
DEFINE_func_801468C8()  /* dedup: shared engine-core @0x801468C8 (src/shared) */

DEFINE_func_80146924()  /* dedup: shared engine-core @0x80146924 (src/shared) */

DEFINE_func_80146994()  /* dedup: shared engine-core @0x80146994 (src/shared) */

DEFINE_func_801469C8()  /* dedup: shared engine-core @0x801469C8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80146A6C);

DEFINE_func_80146AB4()  /* dedup: shared engine-core @0x80146AB4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80146AFC);

DEFINE_func_80146B9C()  /* dedup: shared engine-core @0x80146B9C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80146C3C);

DEFINE_func_80146C98()  /* dedup: shared engine-core @0x80146C98 (src/shared) */

/* func_80146CA0: lhu 0x2; addiu +1; sh 0x2; jr (sh in delay slot)
 * void form avoids a trailing andi v0,0xffff that a returned u16 value could force. */
DEFINE_func_80146CA0()  /* dedup: shared engine-core @0x80146CA0 (src/shared) */

/* func_80146CB4: lhu 0x2; addiu -1; sh 0x2; jr (sh in delay slot)
 * void form avoids a trailing andi v0,0xffff that a returned u16 value could force. */
DEFINE_func_80146CB4()  /* dedup: shared engine-core @0x80146CB4 (src/shared) */

DEFINE_func_80146CC8()  /* dedup: shared engine-core @0x80146CC8 (src/shared) */

DEFINE_func_80146D30()  /* dedup: shared engine-core @0x80146D30 (src/shared) */

DEFINE_func_80146D80()  /* dedup: shared engine-core @0x80146D80 (src/shared) */

DEFINE_func_80146D90()  /* dedup: shared engine-core @0x80146D90 (src/shared) */

DEFINE_func_80146DB8()  /* dedup: shared engine-core @0x80146DB8 (src/shared) */

DEFINE_func_80146DE8()  /* dedup: shared engine-core @0x80146DE8 (src/shared) */

DEFINE_func_80146DF8()  /* dedup: shared engine-core @0x80146DF8 (src/shared) */

DEFINE_func_80146E90()  /* dedup: shared engine-core @0x80146E90 (src/shared) */

DEFINE_func_80146E98()  /* dedup: shared engine-core @0x80146E98 (src/shared) */

DEFINE_func_80146EC0()  /* dedup: shared engine-core @0x80146EC0 (src/shared) */

DEFINE_func_80146F58()  /* dedup: shared engine-core @0x80146F58 (src/shared) */

DEFINE_func_80146FC4()  /* dedup: shared engine-core @0x80146FC4 (src/shared) */

DEFINE_func_8014704C()  /* dedup: shared engine-core @0x8014704C (src/shared) */

DEFINE_func_80147054()  /* dedup: shared engine-core @0x80147054 (src/shared) */

DEFINE_func_80147060()  /* dedup: shared engine-core @0x80147060 (src/shared) */

DEFINE_func_8014706C()  /* dedup: shared engine-core @0x8014706C (src/shared) */

DEFINE_func_80147078()  /* dedup: shared engine-core @0x80147078 (src/shared) */

DEFINE_func_80147084()  /* dedup: shared engine-core @0x80147084 (src/shared) */

DEFINE_func_8014708C()  /* dedup: shared engine-core @0x8014708C (src/shared) */

DEFINE_func_80147098()  /* dedup: shared engine-core @0x80147098 (src/shared) */

DEFINE_func_801470A0()  /* dedup: shared engine-core @0x801470A0 (src/shared) */

DEFINE_func_801470AC()  /* dedup: shared engine-core @0x801470AC (src/shared) */

DEFINE_func_801470B4()  /* dedup: shared engine-core @0x801470B4 (src/shared) */

DEFINE_func_801470C0()  /* dedup: shared engine-core @0x801470C0 (src/shared) */

DEFINE_func_80147118()  /* dedup: shared engine-core @0x80147118 (src/shared) */

DEFINE_func_80147264()  /* dedup: shared engine-core @0x80147264 (src/shared) */

DEFINE_func_80147290()  /* dedup: shared engine-core @0x80147290 (src/shared) */

/* func_801472B4: lhu 0x7E; andi 0xFFFD; sh 0x7E; jr (sh in delay slot)
 * void form: no return value => no extra truncation past the mask op. */
DEFINE_func_801472B4()  /* dedup: shared engine-core @0x801472B4 (src/shared) */

DEFINE_func_801472C8()  /* dedup: shared engine-core @0x801472C8 (src/shared) */

DEFINE_func_801472DC()  /* dedup: shared engine-core @0x801472DC (src/shared) */

DEFINE_func_801472F0()  /* dedup: shared engine-core @0x801472F0 (src/shared) */

DEFINE_func_80147300()  /* dedup: shared engine-core @0x80147300 (src/shared) */

DEFINE_func_80147324()  /* dedup: shared engine-core @0x80147324 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80147364);

DEFINE_func_801473DC()  /* dedup: shared engine-core @0x801473DC (src/shared) */

DEFINE_func_801473EC()  /* dedup: shared engine-core @0x801473EC (src/shared) */

DEFINE_func_80147460()  /* dedup: shared engine-core @0x80147460 (src/shared) */

DEFINE_func_80147478()  /* dedup: shared engine-core @0x80147478 (src/shared) */

DEFINE_func_801474D8()  /* dedup: shared engine-core @0x801474D8 (src/shared) */

DEFINE_func_801474EC()  /* dedup: shared engine-core @0x801474EC (src/shared) */

#include "common.h"

DEFINE_func_80147514()  /* dedup: shared engine-core @0x80147514 (src/shared) */

DEFINE_func_80147628()  /* dedup: shared engine-core @0x80147628 (src/shared) */

DEFINE_func_80147718()  /* dedup: shared engine-core @0x80147718 (src/shared) */

DEFINE_func_80147788()  /* dedup: shared engine-core @0x80147788 (src/shared) */

DEFINE_func_801477A8()  /* dedup: shared engine-core @0x801477A8 (src/shared) */

DEFINE_func_801477C8()  /* dedup: shared engine-core @0x801477C8 (src/shared) */

DEFINE_func_801477E8()  /* dedup: shared engine-core @0x801477E8 (src/shared) */

DEFINE_func_80147814()  /* dedup: shared engine-core @0x80147814 (src/shared) */

extern void func_80147928(int a0, int a1);
extern void func_8014799C(int a0, int a1);
extern void func_80147A10(int a0, int a1);

void func_80147860(int a0, int a1, int a2, int a3) {
    func_80147928(a0, a1);
    func_8014799C(a0, a2);
    func_80147A10(a0, a3);
}

DEFINE_func_801478B8()  /* dedup: shared engine-core @0x801478B8 (src/shared) */

DEFINE_func_80147928()  /* dedup: shared engine-core @0x80147928 (src/shared) */

DEFINE_func_80147948()  /* dedup: shared engine-core @0x80147948 (src/shared) */

DEFINE_func_8014799C()  /* dedup: shared engine-core @0x8014799C (src/shared) */

DEFINE_func_801479BC()  /* dedup: shared engine-core @0x801479BC (src/shared) */

DEFINE_func_80147A10()  /* dedup: shared engine-core @0x80147A10 (src/shared) */

DEFINE_func_80147A30()  /* dedup: shared engine-core @0x80147A30 (src/shared) */

DEFINE_func_80147A84()  /* dedup: shared engine-core @0x80147A84 (src/shared) */

DEFINE_func_80147AAC()  /* dedup: shared engine-core @0x80147AAC (src/shared) */

DEFINE_func_80147AD4()  /* dedup: shared engine-core @0x80147AD4 (src/shared) */

DEFINE_func_80147B18()  /* dedup: shared engine-core @0x80147B18 (src/shared) */

DEFINE_func_80147B5C()  /* dedup: shared engine-core @0x80147B5C (src/shared) */

// @class: loose-typing
// @stuck: none -- MATCH (38 ins). Three separate pointers (s32 *p0=&D_80127090; p1=&D_80127094; p2=&D_80127098)
//         force gcc to RELOAD each named global through its pointer for the param-store readback (the sibling
//         func_80146D30 's32 *p=&D_80127090' idiom, extended to all three), reproducing the target's fresh
//         lui+lw per access + the hoisted D_80127090 reload. Reading the globals directly CSEs (no reload).

DEFINE_func_80147C30()  /* dedup: shared engine-core @0x80147C30 (src/shared) */

DEFINE_func_80147CC8()  /* dedup: shared engine-core @0x80147CC8 (src/shared) */

DEFINE_func_80147D38()  /* dedup: shared engine-core @0x80147D38 (src/shared) */

DEFINE_func_80147DC0()  /* dedup: shared engine-core @0x80147DC0 (src/shared) */

DEFINE_func_80147E44()  /* dedup: shared engine-core @0x80147E44 (src/shared) */

DEFINE_func_80147F50()  /* dedup: shared engine-core @0x80147F50 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80147F78);

DEFINE_func_80148038()  /* dedup: shared engine-core @0x80148038 (src/shared) */

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
DEFINE_func_80148094()  /* dedup: shared engine-core @0x80148094 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801483E8);

DEFINE_func_801484B0()  /* dedup: shared engine-core @0x801484B0 (src/shared) */

DEFINE_func_801484E8()  /* dedup: shared engine-core @0x801484E8 (src/shared) */

DEFINE_func_80148534()  /* dedup: shared engine-core @0x80148534 (src/shared) */

DEFINE_func_8014856C()  /* dedup: shared engine-core @0x8014856C (src/shared) */

DEFINE_func_801485B8()  /* dedup: shared engine-core @0x801485B8 (src/shared) */

/* func_80148634: ori v0,0x8080; sh 0 @0xAA; sh 0 @0xAC; sh 0x8080 @0xAE
 * 0x8080 loaded via ori (positive 16-bit imm) => store an unsigned 16-bit value. */
DEFINE_func_80148634()  /* dedup: shared engine-core @0x80148634 (src/shared) */

DEFINE_func_80148648()  /* dedup: shared engine-core @0x80148648 (src/shared) */

DEFINE_func_801487F4()  /* dedup: shared engine-core @0x801487F4 (src/shared) */

DEFINE_func_80148800()  /* dedup: shared engine-core @0x80148800 (src/shared) */

DEFINE_func_8014880C()  /* dedup: shared engine-core @0x8014880C (src/shared) */

DEFINE_func_80148818()  /* dedup: shared engine-core @0x80148818 (src/shared) */

DEFINE_func_80148824()  /* dedup: shared engine-core @0x80148824 (src/shared) */

DEFINE_func_801488A8()  /* dedup: shared engine-core @0x801488A8 (src/shared) */

DEFINE_func_8014891C()  /* dedup: shared engine-core @0x8014891C (src/shared) */

DEFINE_func_80148980()  /* dedup: shared engine-core @0x80148980 (src/shared) */

DEFINE_func_801489E8()  /* dedup: shared engine-core @0x801489E8 (src/shared) */

DEFINE_func_80148A48()  /* dedup: shared engine-core @0x80148A48 (src/shared) */

DEFINE_func_80148AAC()  /* dedup: shared engine-core @0x80148AAC (src/shared) */

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

DEFINE_func_80148C18()  /* dedup: shared engine-core @0x80148C18 (src/shared) */

DEFINE_func_80148C20()  /* dedup: shared engine-core @0x80148C20 (src/shared) */

DEFINE_func_80148C34()  /* dedup: shared engine-core @0x80148C34 (src/shared) */

DEFINE_func_80148C4C()  /* dedup: shared engine-core @0x80148C4C (src/shared) */

DEFINE_func_80148C64()  /* dedup: shared engine-core @0x80148C64 (src/shared) */

DEFINE_func_80148C7C()  /* dedup: shared engine-core @0x80148C7C (src/shared) */

DEFINE_func_80148C84()  /* dedup: shared engine-core @0x80148C84 (src/shared) */

DEFINE_func_80148C9C()  /* dedup: shared engine-core @0x80148C9C (src/shared) */

/* func_80148CB4: addiu a1,-0x400; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1
 * v0 = *(a0+0x20) deref; store (a1-0x400)&0xFFF as halfword at v0+0x12; return 1. */
DEFINE_func_80148CB4()  /* dedup: shared engine-core @0x80148CB4 (src/shared) */

/* func_80148CCC: addiu a1,-0x200; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
DEFINE_func_80148CCC()  /* dedup: shared engine-core @0x80148CCC (src/shared) */

DEFINE_func_80148CE4()  /* dedup: shared engine-core @0x80148CE4 (src/shared) */

DEFINE_func_80148CEC()  /* dedup: shared engine-core @0x80148CEC (src/shared) */

/* func_80148CF4: addiu a1,-0x600; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
DEFINE_func_80148CF4()  /* dedup: shared engine-core @0x80148CF4 (src/shared) */

/* func_80148D0C: addiu a1,-0x400; lw v0,0x20(a0); andi a1,0xFFF; sh a1,0x12(v0); ret 1 */
DEFINE_func_80148D0C()  /* dedup: shared engine-core @0x80148D0C (src/shared) */

DEFINE_func_80148D24()  /* dedup: shared engine-core @0x80148D24 (src/shared) */

DEFINE_func_80148D3C()  /* dedup: shared engine-core @0x80148D3C (src/shared) */

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80148E54);

DEFINE_func_80148F60()  /* dedup: shared engine-core @0x80148F60 (src/shared) */

DEFINE_func_80148F68()  /* dedup: shared engine-core @0x80148F68 (src/shared) */

DEFINE_func_80148F74()  /* dedup: shared engine-core @0x80148F74 (src/shared) */

DEFINE_func_80148F80()  /* dedup: shared engine-core @0x80148F80 (src/shared) */

DEFINE_func_80148F8C()  /* dedup: shared engine-core @0x80148F8C (src/shared) */

DEFINE_func_80148F98()  /* dedup: shared engine-core @0x80148F98 (src/shared) */

DEFINE_func_80148FA0()  /* dedup: shared engine-core @0x80148FA0 (src/shared) */

DEFINE_func_80148FAC()  /* dedup: shared engine-core @0x80148FAC (src/shared) */

DEFINE_func_80148FB8()  /* dedup: shared engine-core @0x80148FB8 (src/shared) */

DEFINE_func_80148FC4()  /* dedup: shared engine-core @0x80148FC4 (src/shared) */

DEFINE_func_80148FD0()  /* dedup: shared engine-core @0x80148FD0 (src/shared) */

DEFINE_func_80148FD8()  /* dedup: shared engine-core @0x80148FD8 (src/shared) */

DEFINE_func_80148FE0()  /* dedup: shared engine-core @0x80148FE0 (src/shared) */

DEFINE_func_80148FEC()  /* dedup: shared engine-core @0x80148FEC (src/shared) */

DEFINE_func_80148FF8()  /* dedup: shared engine-core @0x80148FF8 (src/shared) */

DEFINE_func_80149004()  /* dedup: shared engine-core @0x80149004 (src/shared) */

DEFINE_func_8014900C()  /* dedup: shared engine-core @0x8014900C (src/shared) */

DEFINE_func_80149020()  /* dedup: shared engine-core @0x80149020 (src/shared) */

DEFINE_func_80149034()  /* dedup: shared engine-core @0x80149034 (src/shared) */

DEFINE_func_80149048()  /* dedup: shared engine-core @0x80149048 (src/shared) */

DEFINE_func_8014905C()  /* dedup: shared engine-core @0x8014905C (src/shared) */

DEFINE_func_80149078()  /* dedup: shared engine-core @0x80149078 (src/shared) */

DEFINE_func_801490E0()  /* dedup: shared engine-core @0x801490E0 (src/shared) */

DEFINE_func_801490E8()  /* dedup: shared engine-core @0x801490E8 (src/shared) */

DEFINE_func_801490F0()  /* dedup: shared engine-core @0x801490F0 (src/shared) */

DEFINE_func_801490F8()  /* dedup: shared engine-core @0x801490F8 (src/shared) */

DEFINE_func_80149184()  /* dedup: shared engine-core @0x80149184 (src/shared) */

DEFINE_func_801491C4()  /* dedup: shared engine-core @0x801491C4 (src/shared) */

DEFINE_func_80149204()  /* dedup: shared engine-core @0x80149204 (src/shared) */

DEFINE_func_80149210()  /* dedup: shared engine-core @0x80149210 (src/shared) */

DEFINE_func_80149228()  /* dedup: shared engine-core @0x80149228 (src/shared) */

DEFINE_func_80149284()  /* dedup: shared engine-core @0x80149284 (src/shared) */

DEFINE_func_80149290()  /* dedup: shared engine-core @0x80149290 (src/shared) */

DEFINE_func_80149350()  /* dedup: shared engine-core @0x80149350 (src/shared) */

// @class: regalloc-order
// @solved: MATCH (23 ins) via .run/gccmap/cse_expr.md §2 (hoist-vs-remat IS steerable).
//   Old @stuck: gcc cached &sp18 in freed $s0 (addiu s0,sp,24 + move a2/a0,s0); target remats
//   addiu $aN,$sp,0x18 per call. Fix: name the first use through a nested-block pointer local,
//   then kill its CSE class AFTER the call with a volatile OUTPUT-ONLY asm (no "0"(q) input --
//   that keeps q live across the call and re-caches). LOAD-BEARING: cse.c invalidate_for_call
//   only kills HARD regs; the asm re-SET is the only C-reachable pseudo-class kill.
//   Leaf-proven only (match_one, asm/ov_SC04_005) -- still needs whole-binary gate_stage.
DEFINE_func_80149374()  /* dedup: shared engine-core @0x80149374 (src/shared) */

DEFINE_func_801493D0()  /* dedup: shared engine-core @0x801493D0 (src/shared) */

DEFINE_func_8014942C()  /* dedup: shared engine-core @0x8014942C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80149450);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801494CC);

DEFINE_func_80149544()  /* dedup: shared engine-core @0x80149544 (src/shared) */

/* arg-forwarding wrapper: stack buffer passed to two callees.
 * §17 array-decay — buf declared as a local array and passed bare so gcc
 * rematerializes addiu $sp,0x10 per use instead of hoisting into a
 * callee-saved reg (frame 0x20, only $s0 saved — matches target). */
DEFINE_func_80149584()  /* dedup: shared engine-core @0x80149584 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801495C4);

// @class: regalloc-order
// @stuck: none — MATCH (34 ins). param_2 pinned to $s0; the two stack out-bufs (in@0x10,
//   mid@0x20,out@0x18) would be HOISTED into $s1 across call1 (frame 0x38, +s1 save) — break
//   that with a per-use CSE-break barrier (`__asm__("":"=r"(p):"0"(p))`) on &in, mid(call1),
//   mid(call2) so each rematerializes `addiu reg,$sp,off` (frame 0x30, only $s0 saved). The
//   two independent arg setups (`lw $a0,0x20($a0)` vs `addiu $a2,$sp,0x20`) tie in sched2 —
//   force target order with VOLATILE barriers in textual order pin(&in)->mtx-load->mid.

extern void func_8012F14C(s32);
extern void func_8012EFB8(s32 a0);

void func_8014964C(s32 param_1, s32 param_2) {
    Vec3 in;
    Vec3 out;
    s32 mid[2];
    register s32 p2 __asm__("$16");
    Vec3 *pin;
    s32 *m1;
    s32 *m2;
    s32 mtx;

    p2 = param_2;
    in.f0 = *(s16 *)(p2 + 2);
    in.f2 = *(s16 *)(p2 + 6);
    in.f4 = *(s16 *)(p2 + 0xA);
    pin = &in;
    __asm__ __volatile__("" : "=r"(pin) : "0"(pin));
    mtx = *(s32 *)(param_1 + 0x20);
    __asm__ __volatile__("" : "=r"(mtx) : "0"(mtx));
    m1 = mid;
    __asm__ __volatile__("" : "=r"(m1) : "0"(m1));
    ((void (*)(s32, Vec3 *, s32 *))func_8012F14C)(mtx + 0x34, pin, m1);
    m2 = mid;
    __asm__ __volatile__("" : "=r"(m2) : "0"(m2));
    ((void (*)(s32 *, Vec3 *))func_8012EFB8)(m2, &out);
    *(s16 *)(p2 + 2) = out.f0;
    *(s16 *)(p2 + 6) = out.f2;
    *(s16 *)(p2 + 0xA) = out.f4;
}

DEFINE_func_801496D4()  /* dedup: shared engine-core @0x801496D4 (src/shared) */

DEFINE_func_80149704()  /* dedup: shared engine-core @0x80149704 (src/shared) */

DEFINE_func_80149724()  /* dedup: shared engine-core @0x80149724 (src/shared) */

DEFINE_func_80149744()  /* dedup: shared engine-core @0x80149744 (src/shared) */

DEFINE_func_80149788()  /* dedup: shared engine-core @0x80149788 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801497A8);

DEFINE_func_80149864()  /* dedup: shared engine-core @0x80149864 (src/shared) */

DEFINE_func_80149884()  /* dedup: shared engine-core @0x80149884 (src/shared) */

DEFINE_func_801498C0()  /* dedup: shared engine-core @0x801498C0 (src/shared) */

/* func_801498E0 — overlay ov_SC01_077 shared core */
DEFINE_func_801498E0()  /* dedup: shared engine-core @0x801498E0 (src/shared) */

DEFINE_func_80149954()  /* dedup: shared engine-core @0x80149954 (src/shared) */

DEFINE_func_80149A64()  /* dedup: shared engine-core @0x80149A64 (src/shared) */

DEFINE_func_80149AA8()  /* dedup: shared engine-core @0x80149AA8 (src/shared) */

DEFINE_func_80149AD4()  /* dedup: shared engine-core @0x80149AD4 (src/shared) */

DEFINE_func_80149B14()  /* dedup: shared engine-core @0x80149B14 (src/shared) */

DEFINE_func_80149B54()  /* dedup: shared engine-core @0x80149B54 (src/shared) */

DEFINE_func_80149BAC()  /* dedup: shared engine-core @0x80149BAC (src/shared) */

DEFINE_func_80149BEC()  /* dedup: shared engine-core @0x80149BEC (src/shared) */

#include "common.h"

DEFINE_func_80149C08()  /* dedup: shared engine-core @0x80149C08 (src/shared) */

DEFINE_func_80149C94()  /* dedup: shared engine-core @0x80149C94 (src/shared) */

DEFINE_func_80149CB4()  /* dedup: shared engine-core @0x80149CB4 (src/shared) */

DEFINE_func_80149CD4()  /* dedup: shared engine-core @0x80149CD4 (src/shared) */

DEFINE_func_80149D10()  /* dedup: shared engine-core @0x80149D10 (src/shared) */

DEFINE_func_80149D9C()  /* dedup: shared engine-core @0x80149D9C (src/shared) */

DEFINE_func_80149DD8()  /* dedup: shared engine-core @0x80149DD8 (src/shared) */

DEFINE_func_80149E94()  /* dedup: shared engine-core @0x80149E94 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80149F2C);

DEFINE_func_80149FA8()  /* dedup: shared engine-core @0x80149FA8 (src/shared) */

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

extern u8 func_8014BEF8(void);
extern void func_8012F14C(s32);
extern s32 func_80135260(s32, s32, s32, s32);
extern void func_8014A1B0(s32 a0, s32 a1);
extern u8 D_801202A0[];

s32 func_8014A048(s32 param_1) {
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

DEFINE_func_8014A1B0()  /* dedup: shared engine-core @0x8014A1B0 (src/shared) */

DEFINE_func_8014A218()  /* dedup: shared engine-core @0x8014A218 (src/shared) */

DEFINE_func_8014A238()  /* dedup: shared engine-core @0x8014A238 (src/shared) */

DEFINE_func_8014A2E4()  /* dedup: shared engine-core @0x8014A2E4 (src/shared) */

DEFINE_func_8014A380()  /* dedup: shared engine-core @0x8014A380 (src/shared) */

DEFINE_func_8014A3E0()  /* dedup: shared engine-core @0x8014A3E0 (src/shared) */

DEFINE_func_8014A454()  /* dedup: shared engine-core @0x8014A454 (src/shared) */

DEFINE_func_8014A4B4()  /* dedup: shared engine-core @0x8014A4B4 (src/shared) */

DEFINE_func_8014A4FC()  /* dedup: shared engine-core @0x8014A4FC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014A51C);

// @class: schedule
// @stuck: none — MATCH (39 ins). Body-primary if/else (D=0 tail), call-result-first (add in $v1),
//         and a scheduling barrier in the clamp block to keep the bnez delay slot a nop.
#include "common.h"

DEFINE_func_8014A59C()  /* dedup: shared engine-core @0x8014A59C (src/shared) */

DEFINE_func_8014A638()  /* dedup: shared engine-core @0x8014A638 (src/shared) */

DEFINE_func_8014A674()  /* dedup: shared engine-core @0x8014A674 (src/shared) */

DEFINE_func_8014A680()  /* dedup: shared engine-core @0x8014A680 (src/shared) */

DEFINE_func_8014A69C()  /* dedup: shared engine-core @0x8014A69C (src/shared) */

DEFINE_func_8014A6A8()  /* dedup: shared engine-core @0x8014A6A8 (src/shared) */

DEFINE_func_8014A6C4()  /* dedup: shared engine-core @0x8014A6C4 (src/shared) */

DEFINE_func_8014A71C()  /* dedup: shared engine-core @0x8014A71C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014A738);

DEFINE_func_8014A830()  /* dedup: shared engine-core @0x8014A830 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (109 ins, relocation-masked)
#include "common.h"

DEFINE_func_8014A850()  /* dedup: shared engine-core @0x8014A850 (src/shared) */

DEFINE_func_8014AA04()  /* dedup: shared engine-core @0x8014AA04 (src/shared) */

DEFINE_func_8014AA28()  /* dedup: shared engine-core @0x8014AA28 (src/shared) */

DEFINE_func_8014AB5C()  /* dedup: shared engine-core @0x8014AB5C (src/shared) */

DEFINE_func_8014AB7C()  /* dedup: shared engine-core @0x8014AB7C (src/shared) */

DEFINE_func_8014ABF0()  /* dedup: shared engine-core @0x8014ABF0 (src/shared) */

DEFINE_func_8014AC10()  /* dedup: shared engine-core @0x8014AC10 (src/shared) */

DEFINE_func_8014ACC0()  /* dedup: shared engine-core @0x8014ACC0 (src/shared) */

DEFINE_func_8014ACE8()  /* dedup: shared engine-core @0x8014ACE8 (src/shared) */

DEFINE_func_8014AD30()  /* dedup: shared engine-core @0x8014AD30 (src/shared) */

DEFINE_func_8014AD7C()  /* dedup: shared engine-core @0x8014AD7C (src/shared) */

DEFINE_func_8014ADA8()  /* dedup: shared engine-core @0x8014ADA8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014ADE0);

DEFINE_func_8014B00C()  /* dedup: shared engine-core @0x8014B00C (src/shared) */

DEFINE_func_8014B034()  /* dedup: shared engine-core @0x8014B034 (src/shared) */

DEFINE_func_8014B084()  /* dedup: shared engine-core @0x8014B084 (src/shared) */

DEFINE_func_8014B12C()  /* dedup: shared engine-core @0x8014B12C (src/shared) */

DEFINE_func_8014B154()  /* dedup: shared engine-core @0x8014B154 (src/shared) */

DEFINE_func_8014B160()  /* dedup: shared engine-core @0x8014B160 (src/shared) */

DEFINE_func_8014B190()  /* dedup: shared engine-core @0x8014B190 (src/shared) */

DEFINE_func_8014B2A8()  /* dedup: shared engine-core @0x8014B2A8 (src/shared) */

DEFINE_func_8014B2D0()  /* dedup: shared engine-core @0x8014B2D0 (src/shared) */

DEFINE_func_8014B2F8()  /* dedup: shared engine-core @0x8014B2F8 (src/shared) */

DEFINE_func_8014B310()  /* dedup: shared engine-core @0x8014B310 (src/shared) */

DEFINE_func_8014B33C()  /* dedup: shared engine-core @0x8014B33C (src/shared) */

DEFINE_func_8014B350()  /* dedup: shared engine-core @0x8014B350 (src/shared) */

DEFINE_func_8014B4C4()  /* dedup: shared engine-core @0x8014B4C4 (src/shared) */

DEFINE_func_8014B4D4()  /* dedup: shared engine-core @0x8014B4D4 (src/shared) */

DEFINE_func_8014B504()  /* dedup: shared engine-core @0x8014B504 (src/shared) */

DEFINE_func_8014B598()  /* dedup: shared engine-core @0x8014B598 (src/shared) */

DEFINE_func_8014B5B0()  /* dedup: shared engine-core @0x8014B5B0 (src/shared) */

DEFINE_func_8014B5B8()  /* dedup: shared engine-core @0x8014B5B8 (src/shared) */

DEFINE_func_8014B5C4()  /* dedup: shared engine-core @0x8014B5C4 (src/shared) */

DEFINE_func_8014B5D0()  /* dedup: shared engine-core @0x8014B5D0 (src/shared) */

DEFINE_func_8014B5D8()  /* dedup: shared engine-core @0x8014B5D8 (src/shared) */

DEFINE_func_8014B6F0()  /* dedup: shared engine-core @0x8014B6F0 (src/shared) */

DEFINE_func_8014B768()  /* dedup: shared engine-core @0x8014B768 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH

DEFINE_func_8014B7A4()  /* dedup: shared engine-core @0x8014B7A4 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (sep EA6 u16 sym re-folds w/ (s16) cast=lh; mem barrier orders EA4 store before EA6 load)

DEFINE_func_8014B944()  /* dedup: shared engine-core @0x8014B944 (src/shared) */

DEFINE_func_8014BB0C()  /* dedup: shared engine-core @0x8014BB0C (src/shared) */

DEFINE_func_8014BB24()  /* dedup: shared engine-core @0x8014BB24 (src/shared) */

DEFINE_func_8014BC0C()  /* dedup: shared engine-core @0x8014BC0C (src/shared) */

DEFINE_func_8014BC44()  /* dedup: shared engine-core @0x8014BC44 (src/shared) */

DEFINE_func_8014BC80()  /* dedup: shared engine-core @0x8014BC80 (src/shared) */

DEFINE_func_8014BCC0()  /* dedup: shared engine-core @0x8014BCC0 (src/shared) */

DEFINE_func_8014BCEC()  /* dedup: shared engine-core @0x8014BCEC (src/shared) */

DEFINE_func_8014BD24()  /* dedup: shared engine-core @0x8014BD24 (src/shared) */

DEFINE_func_8014BD60()  /* dedup: shared engine-core @0x8014BD60 (src/shared) */

DEFINE_func_8014BD98()  /* dedup: shared engine-core @0x8014BD98 (src/shared) */

DEFINE_func_8014BDC8()  /* dedup: shared engine-core @0x8014BDC8 (src/shared) */

DEFINE_func_8014BDE0()  /* dedup: shared engine-core @0x8014BDE0 (src/shared) */

DEFINE_func_8014BDE8()  /* dedup: shared engine-core @0x8014BDE8 (src/shared) */

DEFINE_func_8014BE78()  /* dedup: shared engine-core @0x8014BE78 (src/shared) */

DEFINE_func_8014BE9C()  /* dedup: shared engine-core @0x8014BE9C (src/shared) */

DEFINE_func_8014BEC0()  /* dedup: shared engine-core @0x8014BEC0 (src/shared) */

DEFINE_func_8014BEF8()  /* dedup: shared engine-core @0x8014BEF8 (src/shared) */

DEFINE_func_8014BF18()  /* dedup: shared engine-core @0x8014BF18 (src/shared) */

DEFINE_func_8014BF48()  /* dedup: shared engine-core @0x8014BF48 (src/shared) */

DEFINE_func_8014BF6C()  /* dedup: shared engine-core @0x8014BF6C (src/shared) */

DEFINE_func_8014BF8C()  /* dedup: shared engine-core @0x8014BF8C (src/shared) */

DEFINE_func_8014BFB0()  /* dedup: shared engine-core @0x8014BFB0 (src/shared) */

DEFINE_func_8014BFD4()  /* dedup: shared engine-core @0x8014BFD4 (src/shared) */

DEFINE_func_8014BFF4()  /* dedup: shared engine-core @0x8014BFF4 (src/shared) */

DEFINE_func_8014C010()  /* dedup: shared engine-core @0x8014C010 (src/shared) */

DEFINE_func_8014C050()  /* dedup: shared engine-core @0x8014C050 (src/shared) */

DEFINE_func_8014C088()  /* dedup: shared engine-core @0x8014C088 (src/shared) */

DEFINE_func_8014C0C8()  /* dedup: shared engine-core @0x8014C0C8 (src/shared) */

DEFINE_func_8014C118()  /* dedup: shared engine-core @0x8014C118 (src/shared) */

#include "common.h"

DEFINE_func_8014C168()  /* dedup: shared engine-core @0x8014C168 (src/shared) */

extern void func_8014C1C8(s32 arg0, s32 arg1, void *arg2);
extern u8 D_8018875C[];

void func_8014C1A0(s32 arg0, s32 arg1) {
    func_8014C1C8(arg0, arg1, D_8018875C);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014C1C8);

DEFINE_func_8014C278()  /* dedup: shared engine-core @0x8014C278 (src/shared) */

extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_80012A60(s32 a0, s32 a1);

s32 func_8014C2B0(void *a0, void *a1, s32 a2) {
    s16 r1 = (s16)func_8014C59C(a0, a1);
    s32 v1 = *(s32 *)((u8 *)a0 + 0x20);
    s16 r2 = (s16)func_80012A60(r1, *(s16 *)(v1 + 0x12));
    return r2 < (a2 & 0xFFFF);
}

DEFINE_func_8014C308()  /* dedup: shared engine-core @0x8014C308 (src/shared) */

DEFINE_func_8014C3A4()  /* dedup: shared engine-core @0x8014C3A4 (src/shared) */

DEFINE_func_8014C3D0()  /* dedup: shared engine-core @0x8014C3D0 (src/shared) */

DEFINE_func_8014C43C()  /* dedup: shared engine-core @0x8014C43C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014C4AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014C568);

DEFINE_func_8014C59C()  /* dedup: shared engine-core @0x8014C59C (src/shared) */

extern u8 D_80188764;
extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {
    return func_8014C5FC(a0, a1, &D_80188764);
}

DEFINE_func_8014C5FC()  /* dedup: shared engine-core @0x8014C5FC (src/shared) */

DEFINE_func_8014C6AC()  /* dedup: shared engine-core @0x8014C6AC (src/shared) */

DEFINE_func_8014C6C0()  /* dedup: shared engine-core @0x8014C6C0 (src/shared) */

DEFINE_func_8014C6D0()  /* dedup: shared engine-core @0x8014C6D0 (src/shared) */

DEFINE_func_8014C6E0()  /* dedup: shared engine-core @0x8014C6E0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014C6F4);

DEFINE_func_8014C860()  /* dedup: shared engine-core @0x8014C860 (src/shared) */

DEFINE_func_8014C88C()  /* dedup: shared engine-core @0x8014C88C (src/shared) */

#include "common.h"

void func_8014C8C8(s32 dst, s32 * src)
{
    *(struct up *)(dst + 0x15c) = *(struct up *)(src + 0);
    *(s16 *)(dst + 0x162) = 0;
}

DEFINE_func_8014C8F0()  /* dedup: shared engine-core @0x8014C8F0 (src/shared) */

DEFINE_func_8014C918()  /* dedup: shared engine-core @0x8014C918 (src/shared) */

DEFINE_func_8014C968()  /* dedup: shared engine-core @0x8014C968 (src/shared) */

DEFINE_func_8014C978()  /* dedup: shared engine-core @0x8014C978 (src/shared) */

DEFINE_func_8014C98C()  /* dedup: shared engine-core @0x8014C98C (src/shared) */

extern s32 func_80029178(s32 arg);
extern s32 func_8016F1AC(void);
extern void func_80139914(s32 a0);
extern void func_80029124(s32, s32);

void func_8014C99C(u8 *a0) {
    if ((func_80029178(0x119) & 0xFF) != 0) {
        if (func_8016F1AC() != 0) {
            func_80139914(*(s32 *)(a0 + 0x198));
            *(s32 *)(a0 + 0x198) = 0;
            func_80029124(0x119, 0);
        }
    }
}

DEFINE_func_8014CA00()  /* dedup: shared engine-core @0x8014CA00 (src/shared) */

DEFINE_func_8014CA14()  /* dedup: shared engine-core @0x8014CA14 (src/shared) */

DEFINE_func_8014CA70()  /* dedup: shared engine-core @0x8014CA70 (src/shared) */

DEFINE_func_8014CA88()  /* dedup: shared engine-core @0x8014CA88 (src/shared) */

DEFINE_func_8014CAE4()  /* dedup: shared engine-core @0x8014CAE4 (src/shared) */

DEFINE_func_8014CAFC()  /* dedup: shared engine-core @0x8014CAFC (src/shared) */

DEFINE_func_8014CB0C()  /* dedup: shared engine-core @0x8014CB0C (src/shared) */

DEFINE_func_8014CB1C()  /* dedup: shared engine-core @0x8014CB1C (src/shared) */

DEFINE_func_8014CB2C()  /* dedup: shared engine-core @0x8014CB2C (src/shared) */

DEFINE_func_8014CB58()  /* dedup: shared engine-core @0x8014CB58 (src/shared) */

DEFINE_func_8014CB68()  /* dedup: shared engine-core @0x8014CB68 (src/shared) */

DEFINE_func_8014CB7C()  /* dedup: shared engine-core @0x8014CB7C (src/shared) */

DEFINE_func_8014CB8C()  /* dedup: shared engine-core @0x8014CB8C (src/shared) */

DEFINE_func_8014CB9C()  /* dedup: shared engine-core @0x8014CB9C (src/shared) */

DEFINE_func_8014CBD8()  /* dedup: shared engine-core @0x8014CBD8 (src/shared) */

DEFINE_func_8014CBE8()  /* dedup: shared engine-core @0x8014CBE8 (src/shared) */

DEFINE_func_8014CBF8()  /* dedup: shared engine-core @0x8014CBF8 (src/shared) */

DEFINE_func_8014CC28()  /* dedup: shared engine-core @0x8014CC28 (src/shared) */

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
DEFINE_func_8014CD0C()  /* dedup: shared engine-core @0x8014CD0C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014CD80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014CF04);

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

DEFINE_func_8014D0A4()  /* dedup: shared engine-core @0x8014D0A4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014D12C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014D2A0);

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


DEFINE_func_8014D438()  /* dedup: shared engine-core @0x8014D438 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014D4C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014D610);

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

DEFINE_func_8014D790()  /* dedup: shared engine-core @0x8014D790 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014D820);

#include "common.h"

DEFINE_func_8014DCE0()  /* dedup: shared engine-core @0x8014DCE0 (src/shared) */

s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2) {
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    extern s32 ratan2(s32 a0, s32 a1);
    extern s32 func_80012A60(s32 a0, s32 a1);
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);

    s16 temp_s0;
    s32 temp_s0_2;
    s16 temp_s1;
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_a1;
    s8 *var_s2;
    s8 *var_s3;

    __asm__ __volatile__("" :: "r"(((void *)arg0)));
    temp_v0 = M2C_FIELD(arg2, u16 *, 0) - M2C_FIELD(arg1, u16 *, 0);
    temp_v1 = M2C_FIELD(arg2, u16 *, 4) - M2C_FIELD(arg1, u16 *, 4);
    if (((temp_v0 | temp_v1) << 0x10) != 0) {
        var_s3 = (s8 *) D_801202A0;
        if (var_s3 < var_s3 + 0x6480) {
            var_s2 = var_s3 + 0xE;
            __asm__ __volatile__("" :: "r"(var_s2));
loop_3:
            if (M2C_FIELD(var_s3, u16 *, 0) != 0) {
                temp_a1 = M2C_FIELD(var_s2, s32 *, 0x4A);
                if ((temp_a1 != 0) && (M2C_FIELD(var_s2, u16 *, 0x4E) & 0x1000) && (func_80135A4C(M2C_FIELD(var_s2, s32 *, 0x12), temp_a1, (s32 *)arg1, (s32)arg2) != 0)) {
                    temp_s1 = M2C_FIELD(var_s2, u16 *, -8) - M2C_FIELD(((void *)arg0), u16 *, 6);
                    temp_s0 = M2C_FIELD(var_s2, u16 *, 0) - M2C_FIELD(((void *)arg0), u16 *, 0xE);
                    temp_s0_2 = (s16) ratan2(temp_v1, temp_v0);
                    if ((s16) func_80012A60(temp_s0_2, (s16) ratan2(temp_s0, temp_s1)) < 0x400) {
                        M2C_FIELD(((void *)arg0), s8 **, 0x170) = var_s3;
                        M2C_FIELD(((void *)arg0), u16 *, 6) = (u16) M2C_FIELD(arg2, u16 *, 0);
                        M2C_FIELD(((void *)arg0), s16 *, 0xA) = (s16) (M2C_FIELD(arg2, u16 *, 2) + 0x10);
                        M2C_FIELD(((void *)arg0), u16 *, 0xE) = (u16) M2C_FIELD(arg2, u16 *, 4);
                        return 1;
                    }
                }
            }
            var_s3 += 0x10C;
            var_s2 += 0x10C;
            if ((u32) var_s3 >= (u32) D_80126720) {
                goto block_10;
            }
            goto loop_3;
        }
        return 0;
    }
block_10:
    return 0;
}

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

DEFINE_func_8014DF94()  /* dedup: shared engine-core @0x8014DF94 (src/shared) */

/* e1b — T5b Fable5 spike: unpinned + REUSED load temps (the S11 fence) + t2 for b[2].
 * Theory: the original paired the delta loads via REUSED u16 temps (output/anti deps
 * forbid sched1 from hoisting pair-2 above subu-dx; the shared pseudos then take one
 * scratch each (v1/v0) for both pairs and reload/sched2 anti-webs lock the pairing). */
#include "common.h"

DEFINE_func_8014E048()  /* dedup: shared engine-core @0x8014E048 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014E284);

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

DEFINE_func_8014E48C()  /* dedup: shared engine-core @0x8014E48C (src/shared) */

DEFINE_func_8014E514()  /* dedup: shared engine-core @0x8014E514 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014E5B4);

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

DEFINE_func_8014E6F8()  /* dedup: shared engine-core @0x8014E6F8 (src/shared) */

s32 func_80135888(s32, s32, M2C_UNK, M2C_UNK);      /* extern */

DEFINE_func_8014E790()  /* dedup: shared engine-core @0x8014E790 (src/shared) */

DEFINE_func_8014E83C()  /* dedup: shared engine-core @0x8014E83C (src/shared) */

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

DEFINE_func_8014E98C()  /* dedup: shared engine-core @0x8014E98C (src/shared) */

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

DEFINE_func_8014EA4C()  /* dedup: shared engine-core @0x8014EA4C (src/shared) */

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

DEFINE_func_8014ED80()  /* dedup: shared engine-core @0x8014ED80 (src/shared) */

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
DEFINE_func_8014EE14()  /* dedup: shared engine-core @0x8014EE14 (src/shared) */

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

DEFINE_func_8014F24C()  /* dedup: shared engine-core @0x8014F24C (src/shared) */

DEFINE_func_8014F2E0()  /* dedup: shared engine-core @0x8014F2E0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014F3E8);

// @class: other
// @stuck: none — MATCH (handwritten scratchpad-stack-switch sequencer; byte-proven DEFINE_func_8014CCB4 precedent. Do NOT write an explicit nop in the jal delay slot: maspsx 2.56 reorders the following lui %hi into the slot and re-emits the nop, so an explicit one is a redundant +1 ins.)
#include "common.h"

extern s32 func_8014F4C0(void);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014F4C0);

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

DEFINE_func_8014F74C()  /* dedup: shared engine-core @0x8014F74C (src/shared) */

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

DEFINE_func_8014FA70()  /* dedup: shared engine-core @0x8014FA70 (src/shared) */

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

DEFINE_func_8014FC18()  /* dedup: shared engine-core @0x8014FC18 (src/shared) */

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

DEFINE_func_8014FD54()  /* dedup: shared engine-core @0x8014FD54 (src/shared) */

extern void func_80150170(void *a0); extern s32 func_8014FE60(void *a0); void func_8014FDF4(struct S8014FDF4 *a0) { if (a0->f6 != a0->f88 || a0->fA != a0->f8A || a0->fE != a0->f8C) { func_80150170(a0); } else { func_8014FE60(a0); } }

s32 func_8014FE60(void *e) {
    extern s32 func_8014FFDC(s32 e, void *a1, void *a2);
    extern s32 func_80150150(s32 e, s32 a1);

    u8 a[8];
    u8 b[8];
    u8 out[8];
    s32 r5;
    s32 r6;

    *(s16 *)(a + 0) = *(s16 *)(b + 0) = *(u16 *)(((s32)e) + 6);
    *(s16 *)(a + 2) = *(s16 *)(b + 2) = *(u16 *)(((s32)e) + 0xA) - 0x10;
    *(s16 *)(a + 4) = *(s16 *)(b + 4) = *(u16 *)(((s32)e) + 0xE);

    r5 = func_8014FFDC(((s32)e), a, out);
    r6 = func_80150150(((s32)e), (s32)b);

    if (r6 == 0) {
        *(s16 *)(b + 2) = 0x7fff;
    }
    if ((r5 | r6) != 0) {
        if (*(s16 *)(a + 2) < *(s16 *)(b + 2)) {
            __asm__ __volatile__("" ::: "memory");
            *(s16 *)(((s32)e) + 0x78) = *(u16 *)(a + 0);
            *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(a + 2);
            *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(a + 4);
            __builtin_memcpy((void *)(((s32)e) + 0x80), out, 8);
        } else {
            __asm__ __volatile__("" ::: "memory");
            *(s16 *)(((s32)e) + 0x78) = *(u16 *)(b + 0);
            *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(b + 2);
            *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(b + 4);
            __builtin_memcpy((void *)(((s32)e) + 0x80), D_801152A8, 8);
        }
        *(u16 *)(((s32)e) + 0x7e) &= 0xfffe;
        return 1;
    }
    {
        register s32 c __asm__("$3"); /* $v1 */
        register s32 t __asm__("$4"); /* $a0 */
        t = *(u16 *)(a + 0);
        c = 0x7fff;
        *(s16 *)(((s32)e) + 0x7a) = c;
        *(s16 *)(((s32)e) + 0x78) = t;
        t = *(u16 *)(a + 4);
        *(s16 *)(((s32)e) + 0x7c) = t;
        *(u16 *)(((s32)e) + 0x7e) |= 1;
    }
    return 0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8014FFDC);

DEFINE_func_80150150()  /* dedup: shared engine-core @0x80150150 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80150170);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801502EC);

DEFINE_func_80150460()  /* dedup: shared engine-core @0x80150460 (src/shared) */

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

DEFINE_func_801504D8()  /* dedup: shared engine-core @0x801504D8 (src/shared) */

DEFINE_func_80150528()  /* dedup: shared engine-core @0x80150528 (src/shared) */

DEFINE_func_801505FC()  /* dedup: shared engine-core @0x801505FC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801506A4);

DEFINE_func_80150820()  /* dedup: shared engine-core @0x80150820 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected; param reused across calls naturally lands in $s0

DEFINE_func_8015086C()  /* dedup: shared engine-core @0x8015086C (src/shared) */

DEFINE_func_801508B4()  /* dedup: shared engine-core @0x801508B4 (src/shared) */

DEFINE_func_801508F8()  /* dedup: shared engine-core @0x801508F8 (src/shared) */

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

DEFINE_func_80150B9C()  /* dedup: shared engine-core @0x80150B9C (src/shared) */

DEFINE_func_80150BA4()  /* dedup: shared engine-core @0x80150BA4 (src/shared) */

DEFINE_func_80150BC8()  /* dedup: shared engine-core @0x80150BC8 (src/shared) */

DEFINE_func_80150C48()  /* dedup: shared engine-core @0x80150C48 (src/shared) */

DEFINE_func_80150CA0()  /* dedup: shared engine-core @0x80150CA0 (src/shared) */

DEFINE_func_80150CC4()  /* dedup: shared engine-core @0x80150CC4 (src/shared) */

DEFINE_func_80150CE4()  /* dedup: shared engine-core @0x80150CE4 (src/shared) */

DEFINE_func_80150D04()  /* dedup: shared engine-core @0x80150D04 (src/shared) */

DEFINE_func_80150D24()  /* dedup: shared engine-core @0x80150D24 (src/shared) */

DEFINE_func_80150D44()  /* dedup: shared engine-core @0x80150D44 (src/shared) */

DEFINE_func_80150D64()  /* dedup: shared engine-core @0x80150D64 (src/shared) */

DEFINE_func_80150D84()  /* dedup: shared engine-core @0x80150D84 (src/shared) */

DEFINE_func_80150DA4()  /* dedup: shared engine-core @0x80150DA4 (src/shared) */

DEFINE_func_80150DC4()  /* dedup: shared engine-core @0x80150DC4 (src/shared) */

DEFINE_func_80150DE4()  /* dedup: shared engine-core @0x80150DE4 (src/shared) */

DEFINE_func_80150E04()  /* dedup: shared engine-core @0x80150E04 (src/shared) */

DEFINE_func_80150E24()  /* dedup: shared engine-core @0x80150E24 (src/shared) */

DEFINE_func_80150E44()  /* dedup: shared engine-core @0x80150E44 (src/shared) */

DEFINE_func_80150E64()  /* dedup: shared engine-core @0x80150E64 (src/shared) */

DEFINE_func_80150E84()  /* dedup: shared engine-core @0x80150E84 (src/shared) */

DEFINE_func_80150EA4()  /* dedup: shared engine-core @0x80150EA4 (src/shared) */

DEFINE_func_80150EC4()  /* dedup: shared engine-core @0x80150EC4 (src/shared) */

DEFINE_func_80150F78()  /* dedup: shared engine-core @0x80150F78 (src/shared) */

DEFINE_func_80150F80()  /* dedup: shared engine-core @0x80150F80 (src/shared) */

DEFINE_func_80150FB4()  /* dedup: shared engine-core @0x80150FB4 (src/shared) */

DEFINE_func_80150FD8()  /* dedup: shared engine-core @0x80150FD8 (src/shared) */

DEFINE_func_80151014()  /* dedup: shared engine-core @0x80151014 (src/shared) */

DEFINE_func_80151038()  /* dedup: shared engine-core @0x80151038 (src/shared) */

DEFINE_func_80151070()  /* dedup: shared engine-core @0x80151070 (src/shared) */

DEFINE_func_80151094()  /* dedup: shared engine-core @0x80151094 (src/shared) */

DEFINE_func_801510B8()  /* dedup: shared engine-core @0x801510B8 (src/shared) */

DEFINE_func_801510C0()  /* dedup: shared engine-core @0x801510C0 (src/shared) */

DEFINE_func_801510C8()  /* dedup: shared engine-core @0x801510C8 (src/shared) */

DEFINE_func_801510EC()  /* dedup: shared engine-core @0x801510EC (src/shared) */

DEFINE_func_80151110()  /* dedup: shared engine-core @0x80151110 (src/shared) */

DEFINE_func_80151130()  /* dedup: shared engine-core @0x80151130 (src/shared) */

DEFINE_func_80151138()  /* dedup: shared engine-core @0x80151138 (src/shared) */

DEFINE_func_8015115C()  /* dedup: shared engine-core @0x8015115C (src/shared) */

DEFINE_func_80151164()  /* dedup: shared engine-core @0x80151164 (src/shared) */

DEFINE_func_80151184()  /* dedup: shared engine-core @0x80151184 (src/shared) */

DEFINE_func_801511A8()  /* dedup: shared engine-core @0x801511A8 (src/shared) */

DEFINE_func_801511C4()  /* dedup: shared engine-core @0x801511C4 (src/shared) */

DEFINE_func_801511E0()  /* dedup: shared engine-core @0x801511E0 (src/shared) */

DEFINE_func_80151204()  /* dedup: shared engine-core @0x80151204 (src/shared) */

DEFINE_func_80151238()  /* dedup: shared engine-core @0x80151238 (src/shared) */

DEFINE_func_8015126C()  /* dedup: shared engine-core @0x8015126C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80151664);

DEFINE_func_801516F0()  /* dedup: shared engine-core @0x801516F0 (src/shared) */

DEFINE_func_8015173C()  /* dedup: shared engine-core @0x8015173C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (D_8011DB1A held in $a0 via register pin $4 after the func_801725CC call)
#include "common.h"

DEFINE_func_80151780()  /* dedup: shared engine-core @0x80151780 (src/shared) */

DEFINE_func_80151878()  /* dedup: shared engine-core @0x80151878 (src/shared) */

DEFINE_func_80151880()  /* dedup: shared engine-core @0x80151880 (src/shared) */

DEFINE_func_801518D8()  /* dedup: shared engine-core @0x801518D8 (src/shared) */

DEFINE_func_80151924()  /* dedup: shared engine-core @0x80151924 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80151944);

DEFINE_func_80151980()  /* dedup: shared engine-core @0x80151980 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (71 ins, relocation-masked)
#include "common.h"

DEFINE_func_801519C8()  /* dedup: shared engine-core @0x801519C8 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected; func_801542DC called 3-arg vs 2-arg canonical needs call-site cast

#include "common.h"

DEFINE_func_80151AE4()  /* dedup: shared engine-core @0x80151AE4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80151B98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80151C54);

extern void (*D_8018883C[])(void *);

void func_80151D24(void *a0)
{
    D_8018883C[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80151D60()  /* dedup: shared engine-core @0x80151D60 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (50/50). Branch-polarity invert (if>=0x401 -> fall-through 0xC00 case) fixed bnez/li-swap; zero-code __asm__ barrier before func_80149020 anchored the two stores ahead of the call's a0=s0 delay-slot fill.

DEFINE_func_80151DB0()  /* dedup: shared engine-core @0x80151DB0 (src/shared) */

DEFINE_func_80151E78()  /* dedup: shared engine-core @0x80151E78 (src/shared) */

DEFINE_func_80151ECC()  /* dedup: shared engine-core @0x80151ECC (src/shared) */

DEFINE_func_80151F38()  /* dedup: shared engine-core @0x80151F38 (src/shared) */

DEFINE_func_80151FB4()  /* dedup: shared engine-core @0x80151FB4 (src/shared) */

extern void (*D_80188860[])(void *);

void func_80152058(void *a0)
{
    D_80188860[*(u16 *)((s32)a0 + 0x2)](a0);
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

DEFINE_func_80152194()  /* dedup: shared engine-core @0x80152194 (src/shared) */

DEFINE_func_8015220C()  /* dedup: shared engine-core @0x8015220C (src/shared) */

DEFINE_func_80152254()  /* dedup: shared engine-core @0x80152254 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801522CC);

extern void (*D_80188874[])(void *);

void func_80152370(void *a0)
{
    D_80188874[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_801523AC()  /* dedup: shared engine-core @0x801523AC (src/shared) */

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

DEFINE_func_80152500()  /* dedup: shared engine-core @0x80152500 (src/shared) */

DEFINE_func_801525F4()  /* dedup: shared engine-core @0x801525F4 (src/shared) */

extern void (*D_80188890[])(void *);

void func_80152698(void *a0)
{
    D_80188890[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_801526D4()  /* dedup: shared engine-core @0x801526D4 (src/shared) */

DEFINE_func_80152714()  /* dedup: shared engine-core @0x80152714 (src/shared) */

DEFINE_func_80152790()  /* dedup: shared engine-core @0x80152790 (src/shared) */

extern void (*D_801888A8[])(void *);

void func_8015282C(void *a0)
{
    D_801888A8[*(u16 *)((s32)a0 + 0x2)](a0);
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

DEFINE_func_8015294C()  /* dedup: shared engine-core @0x8015294C (src/shared) */

DEFINE_func_80152A08()  /* dedup: shared engine-core @0x80152A08 (src/shared) */

DEFINE_func_80152A50()  /* dedup: shared engine-core @0x80152A50 (src/shared) */

DEFINE_func_80152AC8()  /* dedup: shared engine-core @0x80152AC8 (src/shared) */

extern void (*D_801888BC[])(void *);

void func_80152B6C(void *a0)
{
    D_801888BC[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80152BA8()  /* dedup: shared engine-core @0x80152BA8 (src/shared) */

DEFINE_func_80152BF0()  /* dedup: shared engine-core @0x80152BF0 (src/shared) */

DEFINE_func_80152C40()  /* dedup: shared engine-core @0x80152C40 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80152C80);

extern void (*D_801888D8[])(void *);

void func_80152D24(void *a0)
{
    D_801888D8[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80152D60()  /* dedup: shared engine-core @0x80152D60 (src/shared) */

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

DEFINE_func_80152E4C()  /* dedup: shared engine-core @0x80152E4C (src/shared) */

DEFINE_func_80152EFC()  /* dedup: shared engine-core @0x80152EFC (src/shared) */

DEFINE_func_80152F44()  /* dedup: shared engine-core @0x80152F44 (src/shared) */

DEFINE_func_80152FBC()  /* dedup: shared engine-core @0x80152FBC (src/shared) */

extern void (*D_801888EC[])(void *);

void func_80153060(void *a0)
{
    D_801888EC[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_8015309C()  /* dedup: shared engine-core @0x8015309C (src/shared) */

DEFINE_func_801530E4()  /* dedup: shared engine-core @0x801530E4 (src/shared) */

DEFINE_func_80153150()  /* dedup: shared engine-core @0x80153150 (src/shared) */

DEFINE_func_801531BC()  /* dedup: shared engine-core @0x801531BC (src/shared) */

DEFINE_func_80153204()  /* dedup: shared engine-core @0x80153204 (src/shared) */

DEFINE_func_8015327C()  /* dedup: shared engine-core @0x8015327C (src/shared) */

extern void (*D_80188900[])(void *);

void func_80153320(void *a0)
{
    D_80188900[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_8015335C()  /* dedup: shared engine-core @0x8015335C (src/shared) */

extern void func_80019064(void *a0);
extern void func_80149020(s32 *a0);
struct S;
DEFINE_func_801533A4()  /* dedup: shared engine-core @0x801533A4 (src/shared) */

DEFINE_func_80153410()  /* dedup: shared engine-core @0x80153410 (src/shared) */

DEFINE_func_80153490()  /* dedup: shared engine-core @0x80153490 (src/shared) */

DEFINE_func_801534D8()  /* dedup: shared engine-core @0x801534D8 (src/shared) */

DEFINE_func_80153550()  /* dedup: shared engine-core @0x80153550 (src/shared) */

#include "common.h"

void func_8014ED28(s32 a0);
void func_80146D90(s32 a0);
void func_8014CC28(s32 a0);
void func_8014FA04(s32 a0);

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

DEFINE_func_8015369C()  /* dedup: shared engine-core @0x8015369C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH
DEFINE_func_801536DC()  /* dedup: shared engine-core @0x801536DC (src/shared) */

// @class: schedule
// @stuck: none — MATCH (94 ins). Keys: shared-ret0 goto into nonzero block (§16);
//   memcpy(dst,src,8) for the unaligned lwl/lwr/swl/swr 8-byte copies (sibling func_80146FC4);
//   pin the bVar1*4 temp to $3/v1 so it lands in the bnez delay slot, s2 is a separate copy,
//   and the subtract reuses v1 (the loop-entry schedule).

DEFINE_func_80153800()  /* dedup: shared engine-core @0x80153800 (src/shared) */

DEFINE_func_80153978()  /* dedup: shared engine-core @0x80153978 (src/shared) */

#include "common.h"

DEFINE_func_801539F8()  /* dedup: shared engine-core @0x801539F8 (src/shared) */

DEFINE_func_80153B58()  /* dedup: shared engine-core @0x80153B58 (src/shared) */

DEFINE_func_80153BD8()  /* dedup: shared engine-core @0x80153BD8 (src/shared) */

DEFINE_func_80153BF0()  /* dedup: shared engine-core @0x80153BF0 (src/shared) */

DEFINE_func_80153C18()  /* dedup: shared engine-core @0x80153C18 (src/shared) */

DEFINE_func_80153C30()  /* dedup: shared engine-core @0x80153C30 (src/shared) */

#include "common.h"

DEFINE_func_80153C44()  /* dedup: shared engine-core @0x80153C44 (src/shared) */

DEFINE_func_80153C74()  /* dedup: shared engine-core @0x80153C74 (src/shared) */

DEFINE_func_80153C8C()  /* dedup: shared engine-core @0x80153C8C (src/shared) */

DEFINE_func_80153C9C()  /* dedup: shared engine-core @0x80153C9C (src/shared) */

DEFINE_func_80153CBC()  /* dedup: shared engine-core @0x80153CBC (src/shared) */

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

DEFINE_func_80153D34()  /* dedup: shared engine-core @0x80153D34 (src/shared) */

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

DEFINE_func_80153E00()  /* dedup: shared engine-core @0x80153E00 (src/shared) */

DEFINE_func_8015410C()  /* dedup: shared engine-core @0x8015410C (src/shared) */

DEFINE_func_80154134()  /* dedup: shared engine-core @0x80154134 (src/shared) */

DEFINE_func_80154150()  /* dedup: shared engine-core @0x80154150 (src/shared) */

DEFINE_func_80154190()  /* dedup: shared engine-core @0x80154190 (src/shared) */

DEFINE_func_801541D8()  /* dedup: shared engine-core @0x801541D8 (src/shared) */

DEFINE_func_80154218()  /* dedup: shared engine-core @0x80154218 (src/shared) */

DEFINE_func_80154274()  /* dedup: shared engine-core @0x80154274 (src/shared) */

DEFINE_func_801542A4()  /* dedup: shared engine-core @0x801542A4 (src/shared) */

DEFINE_func_801542DC()  /* dedup: shared engine-core @0x801542DC (src/shared) */

#include "common.h"

DEFINE_func_8015430C()  /* dedup: shared engine-core @0x8015430C (src/shared) */

#include "common.h"

DEFINE_func_80154358()  /* dedup: shared engine-core @0x80154358 (src/shared) */

DEFINE_func_80154418()  /* dedup: shared engine-core @0x80154418 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015444C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801549F8);

DEFINE_func_80154A74()  /* dedup: shared engine-core @0x80154A74 (src/shared) */

DEFINE_func_80154AB4()  /* dedup: shared engine-core @0x80154AB4 (src/shared) */

DEFINE_func_80154AE0()  /* dedup: shared engine-core @0x80154AE0 (src/shared) */

DEFINE_func_80154B20()  /* dedup: shared engine-core @0x80154B20 (src/shared) */

DEFINE_func_80154B4C()  /* dedup: shared engine-core @0x80154B4C (src/shared) */

DEFINE_func_80154B7C()  /* dedup: shared engine-core @0x80154B7C (src/shared) */

DEFINE_func_80154B98()  /* dedup: shared engine-core @0x80154B98 (src/shared) */

DEFINE_func_80154BC8()  /* dedup: shared engine-core @0x80154BC8 (src/shared) */

void func_80154C24(s32 a0, s32 *a1, s32 *a2);
void func_80154F9C(s32 a0);

DEFINE_func_80154BE4()  /* dedup: shared engine-core @0x80154BE4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80154C24);

DEFINE_func_80154ED8()  /* dedup: shared engine-core @0x80154ED8 (src/shared) */

DEFINE_func_80154F9C()  /* dedup: shared engine-core @0x80154F9C (src/shared) */

// @class: struct
// @stuck: none — MATCH (array-of-struct stride-8 base materialize + addu, %lo folded into addiu)

extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_800183E0(s32 a0);

extern ImgRect8 D_80188948[];

void func_801550FC(s32 arg0)
{
    if (arg0 & 0x40000000) {
        MoveImage(&D_80188948[arg0 & 0xFF], 0x200, 0x100);
    } else {
        ((void (*)(void))func_800183E0)();
    }
}

// @class: other
// @stuck: control-flow / branch-polarity transcription; verifying via match_one
DEFINE_func_80155150()  /* dedup: shared engine-core @0x80155150 (src/shared) */

DEFINE_func_801552F4()  /* dedup: shared engine-core @0x801552F4 (src/shared) */

DEFINE_func_80155344()  /* dedup: shared engine-core @0x80155344 (src/shared) */

DEFINE_func_80155394()  /* dedup: shared engine-core @0x80155394 (src/shared) */

DEFINE_func_801553A8()  /* dedup: shared engine-core @0x801553A8 (src/shared) */

DEFINE_func_801553C0()  /* dedup: shared engine-core @0x801553C0 (src/shared) */

DEFINE_func_80155440()  /* dedup: shared engine-core @0x80155440 (src/shared) */

// @class: struct
// @stuck: none — MATCH expected; decrement persists as separate addiu in delay slot

extern int (*D_80188988[])(void);

s32 func_80155458(s32 param_1)
{
    int idx;

    idx = *(unsigned char *)(param_1 + 0x4e);
    if (idx != 0) {
        idx = idx - 1;
        if ((*D_80188988[idx])() == 0) {
            *(unsigned char *)(param_1 + 0x4e) = 0;
        }
    }
    return *(unsigned char *)(param_1 + 0x4e);
}

s32 func_800D02D0(u8);                              /* extern */
DEFINE_func_801554B8()  /* dedup: shared engine-core @0x801554B8 (src/shared) */

DEFINE_func_80155518()  /* dedup: shared engine-core @0x80155518 (src/shared) */

DEFINE_func_8015554C()  /* dedup: shared engine-core @0x8015554C (src/shared) */

extern void (*D_8018898C[])(void *);

void func_80155580(void *a0)
{
    D_8018898C[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_801555BC()  /* dedup: shared engine-core @0x801555BC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801555F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80155800);

// @class: plumbing
// @stuck: callee-conflict (func_8014BEF8/func_80149CB4 declared void in engine_core.h) — cast at call site

DEFINE_func_80155A44()  /* dedup: shared engine-core @0x80155A44 (src/shared) */

DEFINE_func_80155B20()  /* dedup: shared engine-core @0x80155B20 (src/shared) */

DEFINE_func_80155B9C()  /* dedup: shared engine-core @0x80155B9C (src/shared) */

DEFINE_func_80155C0C()  /* dedup: shared engine-core @0x80155C0C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (67 ins). a0 is the call-crossing value -> $s0 naturally;
//   flags from func_8014FA04 held across the 0x4000/0x2000 masks; the shared
//   func_8014C010(a0,1) tail is reached by separate returns (gcc merges to the j/jal tail).

DEFINE_func_80155C64()  /* dedup: shared engine-core @0x80155C64 (src/shared) */

// @class: struct
// @stuck: none — MATCH (64-byte local sets 0x60 frame; branch-polarity invert on &0x80)

DEFINE_func_80155D70()  /* dedup: shared engine-core @0x80155D70 (src/shared) */

extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208(void);
extern int func_80155FF8(int arg, int a1);

void func_80155E30(void *a0);

DEFINE_func_80155E30()  /* dedup: shared engine-core @0x80155E30 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (reserved-local volatile spill[4] forces 0x28 frame; branch-polarity invert per cookbook T4: pair-block as if-body fall-through, func_80161208 in else)
#include "common.h"

DEFINE_func_80155EA4()  /* dedup: shared engine-core @0x80155EA4 (src/shared) */

DEFINE_func_80155F58()  /* dedup: shared engine-core @0x80155F58 (src/shared) */

DEFINE_func_80155F60()  /* dedup: shared engine-core @0x80155F60 (src/shared) */

#include "common.h"

DEFINE_func_80155F80()  /* dedup: shared engine-core @0x80155F80 (src/shared) */

DEFINE_func_80155FB0()  /* dedup: shared engine-core @0x80155FB0 (src/shared) */

DEFINE_func_80155FD4()  /* dedup: shared engine-core @0x80155FD4 (src/shared) */

/* HANDWRITTEN scratchpad-stack-switch wrapper: temporarily repoints $sp into the
 * D-cache scratchpad stack held at *(0x1F8003FC), calls func_80156044, restores $sp.
 * Manipulating $sp is not expressible in C; full inline asm (manages its own frame).
 * Signature pinned by engine_core.h: int func_80155FF8(int arg, int a1). */
extern void func_80156044(int arg, int a1); int func_80155FF8(int arg, int a1) { __asm__ __volatile__( ".set noreorder\n" "addiu $sp, $sp, -24\n" "sw $ra, 16($sp)\n" "lui $v0, 0x1f80\n" "ori $v0, $v0, 0x03fc\n" "addu $t0, $v0, $zero\n" "lw $t1, 0($t0)\n" "nop\n" "sw $sp, 0($t1)\n" "addiu $t1, $t1, -4\n" "addu $sp, $t1, $zero\n" "jal func_80156044\n" "addiu $sp, $sp, 4\n" "lw $sp, 0($sp)\n" "nop\n" "lw $ra, 16($sp)\n" "addiu $sp, $sp, 24\n" : : : "memory"); }  /* dedup: shared engine-core @0x80155FF8 (src/shared) */

// @class: schedule (delay-slot fill via void return type)
// @stuck: none — MATCH (74 ins). Requires engine_core.h DEFINE_func_80155FF8 flip
//         `extern int func_80156044` -> `extern void func_80156044` (byte-neutral; wrapper is inline-asm).
#include "common.h"

void func_80156044(int param_1, int param_2)
{
    extern u32 func_8015616C(s32 a0, u16 a1);
    extern void func_80156670(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern void func_801567BC(s32 a0);
    extern void func_80156848(s32 a0, s32 a1, s32 a2);
    extern void func_80156A88(s32 a0, s32 a1);
    extern s32 func_801565C0(s32 a0);
    extern u8 D_80188B44;
    extern u8 D_80188B58;
    extern u8 D_801889DC;

    register s32 puVar2 __asm__("$2");
    register s32 iVar3 __asm__("$3");
    u8 *puVar4;
    s32 uVar1;

    if (((u32)param_2) & 0x10000) {
        iVar3 = (((u32)param_2) & 0xffff) * 0x14;
        puVar2 = (s32)&D_80188B44;
    } else if (((u32)param_2) & 0x20000) {
        iVar3 = (((u32)param_2) & 0xffff) * 0x14;
        puVar2 = (s32)&D_80188B58;
    } else {
        iVar3 = (((u32)param_2) & 0xffff) * 0x14;
        puVar2 = (s32)&D_801889DC;
    }
    puVar4 = (u8 *)(iVar3 + puVar2);
    uVar1 = func_8015616C(((s32)param_1), *(u16 *)puVar4) & 0xffff;
    if (*(u8 *)(((s32)param_1) + 0x1a8) != 0) {
        func_80156670(((s32)param_1), *(s32 *)puVar4, uVar1, *(s32 *)(puVar4 + 4),
                      *(u8 *)(puVar4 + 0xA), *(u16 *)(puVar4 + 0x12));
        if (*(u8 *)(puVar4 + 0x10) != 0) {
            func_801567BC(((s32)param_1));
        }
        func_80156848(((s32)param_1), (s32)puVar4, uVar1);
        func_80156A88(((s32)param_1), (s32)puVar4);
        if (func_801565C0(((s32)param_1)) != 0) {
            *(u8 *)(((s32)param_1) + 0x1c0) = 1;
        }
    }
}

#include "common.h"

DEFINE_func_8015616C()  /* dedup: shared engine-core @0x8015616C (src/shared) */

// @class: other
// @stuck: none — MATCH expected (signed div/mod + u16 loads, straight from Ghidra-C)

DEFINE_func_80156370()  /* dedup: shared engine-core @0x80156370 (src/shared) */

extern S801563EC D_80188B80[];

S801563EC *func_801563EC(u16 idx) {
    return &D_80188B80[idx];
}

DEFINE_func_8015640C()  /* dedup: shared engine-core @0x8015640C (src/shared) */

DEFINE_func_801564B0()  /* dedup: shared engine-core @0x801564B0 (src/shared) */

DEFINE_func_801565C0()  /* dedup: shared engine-core @0x801565C0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80156600);

DEFINE_func_80156648()  /* dedup: shared engine-core @0x80156648 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80156670);

DEFINE_func_801567BC()  /* dedup: shared engine-core @0x801567BC (src/shared) */

#include "common.h"

extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8);
extern void func_80156A1C(s32 a0, s32 a1);

/* S8 / B8 typedefs lifted to src/shared/engine_types.h (Phase 22) so func_80156B74
 * and other struct-walled giants using these types can propagate ×134. */

DEFINE_func_80156848()  /* dedup: shared engine-core @0x80156848 (src/shared) */

DEFINE_func_80156A14()  /* dedup: shared engine-core @0x80156A14 (src/shared) */

// @class: struct
// @stuck: none — MATCH expected; D_8011520C indexed by param_2 (byte) folds %lo; D_80188DF0 indexed halfword folds %lo
extern unsigned char D_8011520C[];
extern unsigned short D_80188DF0[];
extern void func_80147324(s32 arg0);

void func_80156A1C(s32 param_1, s32 param_2)
{
    if (*(unsigned char *)(param_1 + 0xDA) == 0) {
        func_80147324(D_80188DF0[D_8011520C[param_2]]);
        *(unsigned char *)(param_1 + 0xDA) = *(unsigned char *)(param_1 + 0xDA) + 1;
    }
}

DEFINE_func_80156A88()  /* dedup: shared engine-core @0x80156A88 (src/shared) */

DEFINE_func_80156B74()  /* dedup: shared engine-core @0x80156B74 (src/shared) */

DEFINE_func_80156ECC()  /* dedup: shared engine-core @0x80156ECC (src/shared) */

#include "common.h"

DEFINE_func_80156FA8()  /* dedup: shared engine-core @0x80156FA8 (src/shared) */

extern u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3,
                           s32 a4, s32 a5, s32 a6, s32 a7,
                           s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);

void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3,
                   s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, s32 a9, u16 a10, s32 a11, s32 a12) {
    func_801571C4(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}

DEFINE_func_801571C4()  /* dedup: shared engine-core @0x801571C4 (src/shared) */

DEFINE_func_801574DC()  /* dedup: shared engine-core @0x801574DC (src/shared) */

DEFINE_func_80157510()  /* dedup: shared engine-core @0x80157510 (src/shared) */

extern void (*D_80188E00[])(void *);

void func_80157544(void *a0)
{
    D_80188E00[*(u16 *)((s32)a0 + 0x2)](a0);
}

/* Canonical callee signatures (shared set; call-site casts where the byte-match
 * needs the $v0 return of a void-canonical callee). */
DEFINE_func_80157580()  /* dedup: shared engine-core @0x80157580 (src/shared) */

DEFINE_func_801575E4()  /* dedup: shared engine-core @0x801575E4 (src/shared) */

extern void func_801599A4(void *a0);   /* canonical: void(*)(void *) */
extern void func_80159B3C(void *a0);   /* canonical: void(*)(void *) */
extern s32 func_80161208(void);        /* canonical: s32(*)(void) — call-site cast to pass arg0 */
DEFINE_func_801576A8()  /* dedup: shared engine-core @0x801576A8 (src/shared) */

DEFINE_func_8015771C()  /* dedup: shared engine-core @0x8015771C (src/shared) */

DEFINE_func_8015773C()  /* dedup: shared engine-core @0x8015773C (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected (scalar global store + two sequential calls, param_1 saved across)

extern int D_801D9650;
extern void func_80147078(s32 *a0, s16 a1);
extern void func_801578C0(s32 a0);

void func_80157788(int param_1)
{
    D_801D9650 = 300;
    ((void (*)(int, int))func_80147078)(param_1, 7);
    func_801578C0(param_1);
}

void func_801577C8(s32 arg0) {
    D_801D9650 = 0x12C;
    func_80147078(arg0, 7);
    func_80157808(arg0);
}

// @class: struct
// @stuck: none — MATCH expected (fnptr-table %lo-fold via extern array + global counter decrement + two saved-param calls)

extern void (*D_80188E28[])(void);
extern int D_801D9650;
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_80157808(void *param_1)
{
    D_80188E28[*(unsigned short *)((char *)param_1 + 2)]();
    D_801D9650 = D_801D9650 - 1;
    if (D_801D9650 == -1) {
        func_801599A4(param_1);
        func_80159B3C(param_1);
    }
}

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
extern u8 D_800D5128;
extern u8 D_80188E08;

void func_801578C0(s32 param_1)
{
    ((void (*)(void))func_80156648)();
    *(u8 *)(param_1 + 0x1AA) = 9;
    func_80154274((s32 *)param_1, (s32)&D_800D5128);
    ((void (*)(s32 *, s32))func_80154A74)((s32 *)param_1, 0x15);
    func_80147324(0xC20);
    ((void (*)(s32 *, s32))func_80146DB8)((s32 *)param_1, (s32)&D_80188E08);
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

extern unsigned char D_800D5178;
extern unsigned char D_80188E18;

void func_8015795C(int param_1)
{
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
            ((void (*)(int, void *))func_80146DB8)(param_1, &D_80188E18);
            ((void (*)(int, int))func_801477E8)(param_1, 0xfff40000);
            *(short *)(param_1 + 2) = 4;
        }
        ((void (*)(int))func_801725A4)(param_1);
    }
    return;
}

DEFINE_func_80157A8C()  /* dedup: shared engine-core @0x80157A8C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (43 ins). Fixed via §3-T4 branch-polarity: target fall-through is the (val>0) func_8016706C block, so put it in the `if` and the (val<=0) block in the `else` → blez to else, blocks in target order.

#include "common.h"

DEFINE_func_80157AC8()  /* dedup: shared engine-core @0x80157AC8 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (simple if/else STUB; lhu 0xB8 vs 0x8000)

DEFINE_func_80157B74()  /* dedup: shared engine-core @0x80157B74 (src/shared) */

DEFINE_func_80157BC8()  /* dedup: shared engine-core @0x80157BC8 (src/shared) */

DEFINE_func_80157CCC()  /* dedup: shared engine-core @0x80157CCC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80157D20);

DEFINE_func_80157D74()  /* dedup: shared engine-core @0x80157D74 (src/shared) */

extern void (*D_80188E68[])(void *);

void func_80157DC4(void *a0)
{
    D_80188E68[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80157E00()  /* dedup: shared engine-core @0x80157E00 (src/shared) */

DEFINE_func_80157E38()  /* dedup: shared engine-core @0x80157E38 (src/shared) */

DEFINE_func_80157EA4()  /* dedup: shared engine-core @0x80157EA4 (src/shared) */

/* func_80157F64 — gate on func_80029178(0x87)&0xFF, then func_80148800(a0)&0x80;
 * on the inner hit notify func_80149CB4(a0,5) and return 1, else 0.
 * NOTE: func_80149CB4 is canonically `void func_80149CB4(void)` in this TU, but the
 * .s passes a0,a1 — call via a 2-arg pointer cast to set the regs without a prototype
 * conflict against the (void) definition. */

DEFINE_func_80157F64()  /* dedup: shared engine-core @0x80157F64 (src/shared) */

extern void (*D_80188E70[])(void *);

void func_80157FC4(void *a0)
{
    D_80188E70[*(u16 *)((s32)a0 + 0x2)](a0);
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

extern s32 D_800D51E0;
extern s32 D_80188E3C;

void func_80158038(void * param)
{
    *(u8 *)(param + 0x1aa) = 0xe;
    func_80154274((s32 *)param, (s32)&D_800D51E0);
    func_80154A74(param, 0x15);
    func_80146DB8((s32 *)param, &D_80188E3C);
    *(s32 *)(param + 0x234) = 0;
    func_80146994(5, param, 0xc, 0);
    func_80147324(0x455);
    func_80146CA0((void *)param);
}

DEFINE_func_801580B4()  /* dedup: shared engine-core @0x801580B4 (src/shared) */

DEFINE_func_801581AC()  /* dedup: shared engine-core @0x801581AC (src/shared) */

extern void (*D_80188E7C[])(void *);

void func_8015824C(void *a0)
{
    D_80188E7C[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80158288()  /* dedup: shared engine-core @0x80158288 (src/shared) */

DEFINE_func_801582C0()  /* dedup: shared engine-core @0x801582C0 (src/shared) */

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

extern u8 D_80188E4C;
extern u8 D_800D533C;

void func_80158434(s32 param_1)
{
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
        ((void (*)(s32, s32))func_80146DB8)(param_1, (s32)&D_80188E4C);
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

// @class: plumbing
// @stuck: none — MATCH (branch-polarity invert §3-T4: non-zero (0x8000) case is the if-body so beqz targets the else)

DEFINE_func_80158548()  /* dedup: shared engine-core @0x80158548 (src/shared) */

DEFINE_func_801585A4()  /* dedup: shared engine-core @0x801585A4 (src/shared) */

DEFINE_func_801585AC()  /* dedup: shared engine-core @0x801585AC (src/shared) */

DEFINE_func_801585EC()  /* dedup: shared engine-core @0x801585EC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80158638);

DEFINE_func_80158794()  /* dedup: shared engine-core @0x80158794 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected (3 scalar global stores + byte store + 6 calls, source order)
extern s32 D_801D9658;
extern s32 D_801D9664;
extern s32 D_801D9668;

extern void func_80147084(s32 *a0);
extern void func_80147098(s32 *a0);
extern void func_801470AC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80158880(s32 *param);

void func_8015879C(s32 param_1) {
    D_801D9658 = 0;
    D_801D9664 = 1;
    D_801D9668 = 0;
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
extern s32 D_801D9658;
extern s32 D_801D9664;
extern s32 D_801D9668;

extern void func_80147084(s32 *a0);
extern void func_80147098(s32 *a0);
extern void func_801470AC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80158880(s32 *param);

void func_80158814(void *arg0) {
    D_801D9658 = 0;
    D_801D9664 = 1;
    D_801D9668 = 0;
    *(s8 *)((s32)arg0 + 0xA8) = 0;
    ((void (*)(void))func_80147084)();
    ((void (*)(void *))func_80147098)(arg0);
    ((void (*)(void *))func_801470AC)(arg0);
    ((void (*)(void *, s32))func_80147078)(arg0, 0x1A);
    ((void (*)(void *))func_80158880)(arg0);
}

// @class: struct
// @stuck: none — MATCH (19/19). fn-ptr-table dispatch: param saved across func_80149020 call, byte 0x4F indexes D_80188EB8[] declared extern void(*[])(s32*) so %lo folds into the lw of the fn-ptr; D_80188EB8[*(u8*)(param+0x4F)](param).
#include "common.h"

extern void func_80149020(s32 *a0);
extern void (*D_80188EB8[])(s32 *);

void func_80158880(s32 *param) {
    func_80149020(param);
    D_80188EB8[*(u8 *)((s32)param + 0x4F)](param);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801588CC);

DEFINE_func_80158AB4()  /* dedup: shared engine-core @0x80158AB4 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (expected); void-canonical callees called with param via fn-ptr cast (§17a-1)

DEFINE_func_80158AE4()  /* dedup: shared engine-core @0x80158AE4 (src/shared) */

extern void func_80146CA0(void *a0);
extern s32 func_801472C8(struct S *a0);
extern void func_80147324(s32 a0);
extern void func_801474D8(s32 *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern M2C_UNK D_800D58D8;
extern s32 D_801D9658;

void func_80158BB0(void *arg0) {
    if (D_801D9658 == 0) {
        D_801D9658 = 1;
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

DEFINE_func_80158C40()  /* dedup: shared engine-core @0x80158C40 (src/shared) */

DEFINE_func_80158CD8()  /* dedup: shared engine-core @0x80158CD8 (src/shared) */

DEFINE_func_80158D60()  /* dedup: shared engine-core @0x80158D60 (src/shared) */

// @class: plumbing
// @stuck: none — modeled on byte-matched sibling DEFINE_func_80158C40 (identical skeleton)

#include "common.h"

DEFINE_func_80158E24()  /* dedup: shared engine-core @0x80158E24 (src/shared) */

// @class: other
// @stuck: none — MATCH (signed %11 magic + word-array %lo fold; ((void (*)(int))func_80146CA0)(param_1) reuses $a0 for the 0x198 store in its jal delay slot)

extern s32 D_801D9664;
extern s32 D_80188E8C[];

extern int rand(void);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_80158F00(int param_1) {
    int *self = (int *)param_1;
    struct Actor *act = (struct Actor *)self[0x20 / 4];
    int gate = D_801D9664;

    act->timer = (u16)((act->timer + 0x16) & 0xfff);

    if (gate == 0) {
        s32 r = rand();
        *(s32 *)(param_1 + 0x198) = func_8013767C(D_80188E8C[r % 0xb]);
        ((void (*)(int))func_80146CA0)(param_1);
    }
}

// @class: plumbing
// @stuck: none — MATCH (51 ins). Key: func_801594E8 takes a 2nd arg = sVar1 (the (short)func_80159464
//        return). $a1 is set by sra BEFORE the beqz and stays live into the jal, so the value is used
//        twice (branch test + arg2) — that 2nd use is what keeps the sll;sra (gcc folds sll;sra;beqz
//        -> sll;beqz otherwise). Also: branch-polarity invert (!=0 -> 594E8 fall-through, else 767C);
//        func_8013767C arg is &(*(u8 *)&D_80110C3C) (lui%hi+addiu%lo, not a literal). Ghidra missed the 2nd arg.

extern s32 D_801D9668;
extern u8 D_80110C3C[];

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
    s32 v0;
    s16 sVar1;

    v0 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v0 + 0x12) = (*(u16 *)(v0 + 0x12) + 0x16) & 0xfff;
    if (((s32 (*)(void))func_80148800)() & 0xf0) {
        D_801D9668 = 1;
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

DEFINE_func_801592CC()  /* dedup: shared engine-core @0x801592CC (src/shared) */

extern void func_80145BF8(void);
extern void func_80146CA0(void *a0);
extern u8 D_800AE6BD;
extern s32 D_801D9658;
extern s32 D_801D9660;

void func_8015934C(void *arg0) {
    void *temp_v1;

    if (D_801D9658 == 4) {
        D_801D9658 = 5;
    }
    if (D_801D9660 != 0) {
        func_80145BF8();
        func_80146CA0(arg0);
        D_800AE6BD += 1;
    }
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_v1, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_v1, u16 *, 0x12) + 0x16) & 0xFFF);
}

DEFINE_func_801593E4()  /* dedup: shared engine-core @0x801593E4 (src/shared) */

DEFINE_func_80159404()  /* dedup: shared engine-core @0x80159404 (src/shared) */

DEFINE_func_80159434()  /* dedup: shared engine-core @0x80159434 (src/shared) */

// @class: other
// @stuck: none — MATCH (33 ins)
#include "common.h"

extern s16 currentLocationId;
extern s32 func_80029A94(s32);

extern Entry D_80188EF4[];

s32 func_80159464(void) {
    Entry *e;

    e = D_80188EF4;
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801594E8);

extern void (*D_80189108[])(void *);

void func_80159698(void *a0)
{
    D_80189108[*(u8 *)((s32)a0 + 0x15)](a0);
}

DEFINE_func_801596D4()  /* dedup: shared engine-core @0x801596D4 (src/shared) */

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

extern s16 D_800B9AAC[];
extern s16 D_800B9B00;
extern u16 D_801270C0;
extern u8 D_800AF630[];
extern u32 D_800AFAE8[];
extern char D_80188F28[];

s32 func_801596F0(s32 param_1) {
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
        func_80028620(0, &(*(u8 *)&D_80188F28));
        func_80028620(1, &(*(u8 *)&D_80188F28) + 0x10);
        func_80028620(2, &(*(u8 *)&D_80188F28) + 0x20);
        *(s32 *)(param_1 + 0x28) = 0xff;
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


DEFINE_func_80159874()  /* dedup: shared engine-core @0x80159874 (src/shared) */

DEFINE_func_8015987C()  /* dedup: shared engine-core @0x8015987C (src/shared) */

DEFINE_func_801598BC()  /* dedup: shared engine-core @0x801598BC (src/shared) */

DEFINE_func_801598E0()  /* dedup: shared engine-core @0x801598E0 (src/shared) */

extern void (*D_801891AC[])(void *);

void func_80159968(void *a0)
{
    D_801891AC[*(u8 *)((s32)a0 + 0x4D)](a0);
}

extern void (*D_801891B8[])(void *);

void func_801599A4(void *a0)
{
    D_801891B8[*(u16 *)a0](a0);
}

DEFINE_func_801599E0()  /* dedup: shared engine-core @0x801599E0 (src/shared) */

DEFINE_func_80159A18()  /* dedup: shared engine-core @0x80159A18 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80159A20);

DEFINE_func_80159B08()  /* dedup: shared engine-core @0x80159B08 (src/shared) */

DEFINE_func_80159B3C()  /* dedup: shared engine-core @0x80159B3C (src/shared) */

extern void (*D_80189300[])(void *);

void func_80159B70(void *a0)
{
    D_80189300[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80159BAC()  /* dedup: shared engine-core @0x80159BAC (src/shared) */

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

extern unsigned char D_8018911C;

void func_80159BE4(s32 arg0)
{
    int v;

    ((void (*)(int, void *))func_80146DB8)(arg0, &D_8018911C);
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80159C84);

DEFINE_func_8015A1C8()  /* dedup: shared engine-core @0x8015A1C8 (src/shared) */

DEFINE_func_8015A1FC()  /* dedup: shared engine-core @0x8015A1FC (src/shared) */

DEFINE_func_8015A230()  /* dedup: shared engine-core @0x8015A230 (src/shared) */

extern void (*D_80189308[])(void *);

void func_8015A264(void *a0)
{
    D_80189308[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_8015A2A0()  /* dedup: shared engine-core @0x8015A2A0 (src/shared) */

// @class: other
// @stuck: none — MATCH (60 ins). switch() gives signed slti pivot; per-case duplicated call gives per-case a0 setup + nop jal delay

extern int D_8018912C;

extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern s32 func_80172608(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015A2D8(s32 param_1)
{
    unsigned char bVar1;

    ((void (*)(int, int *))func_80146DB8)(param_1, &D_8018912C);
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015A3C8);

DEFINE_func_8015AB7C()  /* dedup: shared engine-core @0x8015AB7C (src/shared) */

/* func_8015ABD4 — overlay ov_SC01_077 shared core */
DEFINE_func_8015ABD4()  /* dedup: shared engine-core @0x8015ABD4 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (param held in $s0 across 3 calls; lhu 0x16E; &D_8018914C arg)
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018914C;

void func_8015AC48(s32 arg0)
{
    func_80154150(arg0, 9);
    func_80146DB8((s32 *)arg0, &D_8018914C);
    func_80161CD0(arg0, M2C_FIELD(arg0, u16 *, 0x16E));
}

DEFINE_func_8015AC90()  /* dedup: shared engine-core @0x8015AC90 (src/shared) */

DEFINE_func_8015ACC4()  /* dedup: shared engine-core @0x8015ACC4 (src/shared) */

DEFINE_func_8015AD08()  /* dedup: shared engine-core @0x8015AD08 (src/shared) */

extern void (*D_80189310[])(void *);

void func_8015AD3C(void *a0)
{
    D_80189310[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_8015AD78()  /* dedup: shared engine-core @0x8015AD78 (src/shared) */

DEFINE_func_8015ADB0()  /* dedup: shared engine-core @0x8015ADB0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015AE2C);

// @class: regalloc-order
// @stuck: none — MATCH (48 ins)

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015B6F4 (src/shared) */

DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015B7B4 (src/shared) */

DEFINE_func_8015B858()  /* dedup: shared engine-core @0x8015B858 (src/shared) */

DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015B8F8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015B950);

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015BD8C (src/shared) */

DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015BDD0 (src/shared) */

struct Obj;
DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015BE04 (src/shared) */

extern void (*D_8018932C[])(void);

void func_8015BE38(struct Obj *a0) {
    D_8018932C[a0->idx]();
}

DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015BE74 (src/shared) */

DEFINE_func_8015BE94()  /* dedup: shared engine-core @0x8015BE94 (src/shared) */

DEFINE_func_8015BEC4()  /* dedup: shared engine-core @0x8015BEC4 (src/shared) */

DEFINE_func_8015BEE4()  /* dedup: shared engine-core @0x8015BEE4 (src/shared) */

DEFINE_func_8015BF04()  /* dedup: shared engine-core @0x8015BF04 (src/shared) */

DEFINE_func_8015BF48()  /* dedup: shared engine-core @0x8015BF48 (src/shared) */

DEFINE_func_8015BF7C()  /* dedup: shared engine-core @0x8015BF7C (src/shared) */

DEFINE_func_8015BFB0()  /* dedup: shared engine-core @0x8015BFB0 (src/shared) */

extern void (*D_80189338[])(void *);

void func_8015BFF4(void *a0)
{
    D_80189338[*(u16 *)((s32)a0 + 0x2)](a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015C030);

DEFINE_func_8015C08C()  /* dedup: shared engine-core @0x8015C08C (src/shared) */

DEFINE_func_8015C0C4()  /* dedup: shared engine-core @0x8015C0C4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015C128);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015C32C);

DEFINE_func_8015C6A4()  /* dedup: shared engine-core @0x8015C6A4 (src/shared) */

DEFINE_func_8015C6AC()  /* dedup: shared engine-core @0x8015C6AC (src/shared) */

DEFINE_func_8015C6E0()  /* dedup: shared engine-core @0x8015C6E0 (src/shared) */

extern void (*D_80189344[])(void *);

void func_8015C714(void *a0)
{
    D_80189344[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_8015C750()  /* dedup: shared engine-core @0x8015C750 (src/shared) */

DEFINE_func_8015C788()  /* dedup: shared engine-core @0x8015C788 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015C7E4);

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

extern void (*D_801891B8[])();

void func_8015C944(int param_1) {
    func_80149FB0(param_1);
    func_80147AD4(param_1, 0, 0, 0);
    ((void (*)(int))func_801473EC)(param_1);
    ((void (*)(int))func_8014D738)(param_1);
    if (*(int *)(param_1 + 0x170) == 0) {
        (*D_801891B8[*(unsigned short *)param_1])(param_1);
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015CA28);

DEFINE_func_8015CB94()  /* dedup: shared engine-core @0x8015CB94 (src/shared) */

DEFINE_func_8015CBCC()  /* dedup: shared engine-core @0x8015CBCC (src/shared) */

DEFINE_func_8015CBD4()  /* dedup: shared engine-core @0x8015CBD4 (src/shared) */

DEFINE_func_8015CBDC()  /* dedup: shared engine-core @0x8015CBDC (src/shared) */

DEFINE_func_8015CBE4()  /* dedup: shared engine-core @0x8015CBE4 (src/shared) */

DEFINE_func_8015CBEC()  /* dedup: shared engine-core @0x8015CBEC (src/shared) */

DEFINE_func_8015CBF4()  /* dedup: shared engine-core @0x8015CBF4 (src/shared) */

DEFINE_func_8015CBFC()  /* dedup: shared engine-core @0x8015CBFC (src/shared) */

DEFINE_func_8015CC04()  /* dedup: shared engine-core @0x8015CC04 (src/shared) */

#include "common.h"

void func_80147078(s32 *a0, s16 a1);
s32 func_8015CCD0();

DEFINE_func_8015CC0C()  /* dedup: shared engine-core @0x8015CC0C (src/shared) */

DEFINE_func_8015CC40()  /* dedup: shared engine-core @0x8015CC40 (src/shared) */

extern void (*D_80189354[])(void);

void func_8015CC74(s32 * a0)
{
    D_80189354[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015CCB0 (src/shared) */

#include "common.h"

DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015CCD0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015CD20);

DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015CF24 (src/shared) */

#include "common.h"

void func_80147078(s32 *a0, s16 a1);
DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015CF58 (src/shared) */

DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015CF8C (src/shared) */

// @class: struct
// @stuck: none — MATCH expected (lhu @0x2 → fn-ptr array dispatch; proven idiom func_80163A58)
#include "common.h"

extern void (*D_8018938C[])(void);

void func_8015CFC0(s32 * a0)
{
    D_8018938C[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015CFFC (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


void func_8015D01C(int param_1) {
    extern s32 func_801725F4(u8 *a0);
    extern int D_800D550C;
    extern int D_8018937C;

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
    *(int *)(param_1 + 0x38) = (int)&D_8018937C | 0x40000000;
    ((void (*)(int))func_801725F4)(param_1);
    ((void (*)(int))func_80146CA0)(param_1);
}


// @class: struct
// @stuck: none — MATCH (pending gate)

extern s32 func_80149FB0(s32 a0);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void (*D_801891B8[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void func_80146CA0(void *a0);

void func_8015D104(void *arg0) {
    ((void (*)(void))func_80149FB0)();
    ((void (*)(void *))func_8014FA04)(arg0);
    if (((s32 (*)(void *))func_8014E6A0)(arg0) == 0) {
        D_801891B8[*(u16 *)arg0](arg0);
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015D1B8);

// @class: regalloc-order
// @stuck: pinning a0->$s1 and buffer-ptr->$s0; body copy already matches
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void *memcpy(void *dst, const void *src, u32 n);

extern s32 D_801893E8;

void func_8015D380(s32 a0) {
    s16 out[4];
    s32 buf[8];
    register s32 s1 __asm__("$17") = a0;
    register s32 *s0 __asm__("$16") = buf;
    ((void (*)(void *))func_80013F3C)((void *)s0);
    ((void (*)(void *, s32))func_80012558)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12));
    ((void (*)(void *, s32))func_800126C4)((void *)s0, *(s16 *)(*(s32 *)(s1 + 0x20) + 0x10));
    ApplyMatrixSV((void *)s0, (void *)&D_801893E8, (void *)out);
    memcpy((void *)(s1 + 0x138), (void *)out, 8);
}

// @class: plumbing
// @stuck: none — MATCH

extern unsigned char D_801884CC[];

extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015D414(int param_1)
{
    *(unsigned char *)(param_1 + 0x1bd) = 8;
    *(unsigned char **)(param_1 + 0x38) = D_801884CC;
    *(short *)(param_1 + 0x138) = 0;
    *(short *)(param_1 + 0x13a) = 0;
    *(short *)(param_1 + 0x13c) = 0;
    *(short *)(param_1 + 0x13e) = 0;
    *(short *)(param_1 + 0xA) = *(short *)(param_1 + 0xA) + 0x48;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    ((void (*)(void))func_801553C0)();
    func_80154A74(param_1, 0x11);
}

DEFINE_func_8015D480()  /* dedup: shared engine-core @0x8015D480 (src/shared) */

DEFINE_func_8015D4B4()  /* dedup: shared engine-core @0x8015D4B4 (src/shared) */

extern s32 (*D_801893F0[])();

s32 func_8015D4E8(s16 *a0) {
    return D_801893F0[(u16)a0[1]]();
}

DEFINE_func_8015D524()  /* dedup: shared engine-core @0x8015D524 (src/shared) */

DEFINE_func_8015D544()  /* dedup: shared engine-core @0x8015D544 (src/shared) */

DEFINE_func_8015D57C()  /* dedup: shared engine-core @0x8015D57C (src/shared) */

// @class: loose-typing
// @stuck: none — MATCH (field 0xb8 compared as u16 == 0x8000, not s16 == -0x8000)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154A74(int, int);
extern s32 func_80161208();
extern void func_80154150(int, int);
extern void func_80146CA0(void *a0);
extern void func_80149374(int, int);

extern unsigned char D_801893FC[];

void func_8015D5E8(int param_1)
{
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
                (short)((signed char)D_801893FC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xc));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 10) =
                (short)((signed char)D_801893FC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0xe));
            iVar2 = *(int *)(param_1 + 0x234);
            *(int *)(param_1 + 0x234) = iVar2 + 1;
            *(short *)(iVar1 + 0xe) =
                (short)((signed char)D_801893FC[iVar2] +
                        *(unsigned short *)(*(int *)(iVar1 + 0x78) + 0x10));
            func_80149374(param_1, iVar1 + 4);
        }
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015D738);

DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015DA5C (src/shared) */

DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015DA90 (src/shared) */

DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015DAC4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015DAF8);

DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015DB34 (src/shared) */

DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015DB6C (src/shared) */

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern void (*D_801891B8[])(void *);
extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

void func_8015DBD4(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_8015DD74)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        D_801891B8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            ((void (*)(void *))func_8015DCB8)(arg0);
        }
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}

DEFINE_func_8015DC84()  /* dedup: shared engine-core @0x8015DC84 (src/shared) */

// @class: other
// @stuck: none — MATCH (proxy gate)

extern s8 D_80189438[];
extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80189438[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80189438[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80189438[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}

extern void func_8014C1A0(s32 arg0, s32 arg1);
extern void func_80015978(s32 a0, s32 *a1);
s32 func_80029AAC();
DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015DD74 (src/shared) */

DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015DDF0 (src/shared) */

DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015DE24 (src/shared) */

// @class: struct
// @stuck: none — MATCH (fn-ptr array %lo-fold dispatch via halfword index)
extern void (*D_80189450[])(void);

void func_8015DE58(s32 * param_1)
{
    D_80189450[*(unsigned short *)((char *)param_1 + 2)]();
}

DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015DE94 (src/shared) */

DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015DECC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015DF34);

DEFINE_func_8015DFE4()  /* dedup: shared engine-core @0x8015DFE4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015E018);

void func_8014C1A0(s32 arg0, s32 arg1);
void func_80015978(s32 a0, s32 *a1);
s32 func_80029AAC(void);
void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015E0D4 (src/shared) */

DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015E150 (src/shared) */

DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015E184 (src/shared) */

// @class: struct
// @stuck: none — MATCH (function-pointer table dispatch via u16 index at offset 2)

extern void (*D_80189470[])(void);

s32 func_8015E1B8(s32 param_1)
{
    D_80189470[*(u16 *)((char *)param_1 + 2)]();
}

DEFINE_func_8015E1F4()  /* dedup: shared engine-core @0x8015E1F4 (src/shared) */

DEFINE_func_8015E22C()  /* dedup: shared engine-core @0x8015E22C (src/shared) */

DEFINE_func_8015E288()  /* dedup: shared engine-core @0x8015E288 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015E344);

DEFINE_func_8015E40C()  /* dedup: shared engine-core @0x8015E40C (src/shared) */

// @class: struct
// @stuck: none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check

extern u16 D_80189480;
extern u16 D_80189482;
extern u16 D_80189484;
extern s32 D_80189488;

extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8015E4B0(s32 param_1)
{
    u16 *psVar1;
    s16 v[3];
    s32 local_10;

    psVar1 = *(u16 **)(param_1 + 0x18c);
    if ((psVar1 != (u16 *)0) && (*psVar1 != 0)) {
        v[0] = D_80189480 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0xc);
        v[1] = D_80189482 + *(s16 *)(*(s32 *)(psVar1 + 0x3c) + 0xe) * 2;
        v[2] = D_80189484 + *(u16 *)(*(s32 *)(psVar1 + 0x3c) + 0x10);
        ((s32 (*)(s32, s16 *, s16 *))func_80149350)(param_1, &v[0], &v[0]);
        ((s32 (*)(s32 *, s32 *))func_80013E94)(&D_80189488, &local_10);
        ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x1f, param_1, v[0], v[1], v[2], local_10, 0);
    }
    return;
}

extern void func_8013C9C4(void *a0);
extern s32 D_80189490;

void func_8015E588(void) {
    func_8013C9C4(&D_80189490);
}

DEFINE_func_8015E5B0()  /* dedup: shared engine-core @0x8015E5B0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015E698);

DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015E714 (src/shared) */

DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015E84C (src/shared) */

DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015E880 (src/shared) */

DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015E8B4 (src/shared) */

// @class: struct
// @stuck: none — MATCH (function-pointer table dispatch, %lo-folded indexed load)

extern void (*D_801894A4[])(void);

void func_8015E8E8(s32 * param_1)
{
    D_801894A4[*(u16 *)((char *)param_1 + 2)]();
}

DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015E924 (src/shared) */

DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015E95C (src/shared) */

DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015E9B8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015EA3C);

DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ED6C (src/shared) */

DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015EDA0 (src/shared) */

DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015EDD4 (src/shared) */

// @class: struct
// @stuck: none — MATCH (function-pointer table dispatch, %lo folds via array index)

extern void (*D_801894AC[])(void);

s32 func_8015EE08(s32 a0) {
    D_801894AC[*(u16 *)(a0 + 2)]();
}

DEFINE_func_8015EE44()  /* dedup: shared engine-core @0x8015EE44 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (straight STUB call sequence; param saved to $s0 across calls)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);

extern int D_800D4C48;
extern int D_8018919C;

void func_8015EE7C(s32 param_1)
{
    ((int (*)(void))func_8014CBF8)();
    ((int (*)(int))func_801474EC)(param_1);
    ((int (*)(int, void *))func_80154274)(param_1, &D_800D4C48);
    ((int (*)(int, void *))func_80146DB8)(param_1, &D_8018919C);
    ((int (*)(int, int))func_801477E8)(param_1, 0xFFF40000);
    ((int (*)(int))func_80146CA0)(param_1);
}

// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + 0x8000 flag dispatch; mirrors sibling func_8015F9A4)
#include "common.h"

extern void (*D_801891B8[])(void *);

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
    ((void (*)(void *, s32))func_80148038)(arg0, 0x10000);
    ((void (*)(void *))func_80147460)(arg0);
    ((void (*)(void *, s32, s32, s32))func_80147AD4)(arg0, 0, 0, 0x1000);
    ((void (*)(void *))func_801473EC)(arg0);
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_801891B8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s32))func_80147078)(arg0, 0);
        func_80159B70(arg0);
    } else {
        if (((s32 (*)(void *))func_80161418)(arg0) == 0) {
            ((void (*)(void *))func_801725A4)(arg0);
        }
    }
}

DEFINE_func_8015EF9C()  /* dedup: shared engine-core @0x8015EF9C (src/shared) */

DEFINE_func_8015EFA4()  /* dedup: shared engine-core @0x8015EFA4 (src/shared) */

DEFINE_func_8015EFD8()  /* dedup: shared engine-core @0x8015EFD8 (src/shared) */

extern void (*D_801894B4[])(void);
void func_8015F00C(s32 * param_1)
{
  void (*new_var)(void);
  u16 *new_var2;
  new_var2 = param_1;
  new_var2 = new_var2 + 1;
  new_var = D_801894B4[*new_var2];
  new_var();
}

DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015F048 (src/shared) */

DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015F080 (src/shared) */

// @class: struct
// @stuck: none — MATCH (clean reconstruction; flag u16 -> andi 0xffff cmp; if/else with &0x4000 block; func-ptr table %lo-fold; tail func_80161208/func_80155FF8 per sibling func_80155E30)
#include "common.h"

extern void (*D_801891B8[])();
extern s32 D_80062BE8;

extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014AB5C(void);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern s32 func_80161208(void);
extern int func_80155FF8(int arg, int a1);

void func_8015F118(void *a0) {
    u16 flag;

    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        (*D_801891B8[*(u16 *)a0])(a0);
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

DEFINE_func_8015F260()  /* dedup: shared engine-core @0x8015F260 (src/shared) */

DEFINE_func_8015F2BC()  /* dedup: shared engine-core @0x8015F2BC (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015F324(s32 *a0);

void func_8015F2F0(s32 *a0) {
    func_80147078(a0, 0x14);
    func_8015F324(a0);
}

// @class: struct
// @stuck: none — MATCH (fn-ptr table dispatch, precedent func_80131EEC byte-identical)
#include "common.h"

extern void (*D_801894BC[])(void);

void func_8015F324(s32 * a0)
{
    D_801894BC[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015F360 (src/shared) */

DEFINE_func_8015F380()  /* dedup: shared engine-core @0x8015F380 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015F448);

extern void func_801553A8(s32 *a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_8015F738(s32 *a0) {
    func_801553A8(a0);
    func_80154A74((s32)a0, 0x11);
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015F848(s32 *a0);

void func_8015F76C(s32 *a0) {
    func_80147078(a0, 0x15);
    func_8015F848(a0);
}

DEFINE_func_8015F7A0()  /* dedup: shared engine-core @0x8015F7A0 (src/shared) */

// @class: struct
// @stuck: function-pointer-table dispatch; index is u16 at param+2, table base %lo-folds into the lw
#include "common.h"

extern void (*D_801894F4[])(void);

s32 func_8015F7D4(s32 param_1)
{
    D_801894F4[*(u16 *)(param_1 + 2)]();
}

DEFINE_func_8015F810()  /* dedup: shared engine-core @0x8015F810 (src/shared) */

DEFINE_func_8015F848()  /* dedup: shared engine-core @0x8015F848 (src/shared) */

extern void (*D_801891B8[])(void *);
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208(void);

void func_8015F89C(void *arg0) {
    u16 flags = *(u16 *)((u8 *)arg0 + 0xB8);
    if (!(flags & 0x4000)) {
        if (flags & 0x8000) {
            D_801891B8[*(u16 *)arg0](arg0);
            func_80147078(arg0, 0);
            func_80159B70(arg0);
            return;
        }
    } else {
        func_801466F0(1, arg0, 0, -0x1E, 0, 0, 0, 0);
    }
    ((s32 (*)(void *))func_80161208)(arg0);
}

#include "common.h"

void func_80147078(s32 *a0, s16 a1);
extern s32 func_80161104(void);
void func_80154150(s32 a0, s32 a1);
void func_80154A74(s32 a0, s32 a1);
void func_80146C98(s32 *a0, s16 a1);

DEFINE_func_8015F948()  /* dedup: shared engine-core @0x8015F948 (src/shared) */

extern void (*D_801891B8[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208(void);

void func_8015F9A4(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x8000) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
    } else {
        ((s32 (*)(void *))func_80161208)(arg0);
    }
}

DEFINE_func_8015FA24()  /* dedup: shared engine-core @0x8015FA24 (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015FBE0(s32 *a0);

void func_8015FA44(s32 *a0) {
    func_80147078(a0, 0x16);
    func_8015FBE0(a0);
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015FAAC(s32 *a0);

void func_8015FA78(s32 *a0) {
    func_80147078(a0, 0x16);
    func_8015FAAC(a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015FAAC);

// @class: struct
// @stuck: none — MATCH expected (call-crossing s0=param_1; D_801891B8 fn-ptr dispatch; 0x184 |= 0x80000000)
#include "common.h"

extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void (*D_801891B8[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

void func_8015FAE8(void *arg0) {
    s32 v;

    v = func_801612B8(arg0, 0);
    if (v == 0 || v == 0x8000) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_801891B8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 3);
        ((void (*)(void *))func_8015BE94)(arg0);
    } else if ((v & 0x4000) != 0) {
        ((void (*)(void *))func_8016007C)(arg0);
        *(u32 *)((u8 *)arg0 + 0x184) |= 0x80000000;
        D_801891B8[*(u16 *)arg0](arg0);
        ((void (*)(void *, s16))func_80147078)(arg0, 4);
        ((void (*)(void *))func_8015C0C4)(arg0);
    } else {
        ((void (*)(void *))func_8015FBE0)(arg0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015FBE0);

// @class: struct
// @stuck: none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)

extern s32 D_800AE6B0;
extern void (*D_801891B8[])(void *);

extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8015FCC8(void *param_1) {
    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_801891B8[*(u16 *)param_1](param_1);
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

extern unsigned int D_80189514[];

extern void func_80147324(s32 arg0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

void func_8015FD74(int param_1)
{
    ((int (*)(int))func_80147324)(0x18);
    *(int *)(param_1 + 0x198) = func_8013767C(D_80189514[*(unsigned char *)(param_1 + 0x1a0)]);
    ((int (*)(int))func_80146CA0)(param_1);
}

DEFINE_func_8015FDCC()  /* dedup: shared engine-core @0x8015FDCC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8015FE70);

// @class: struct
// @stuck: none — MATCH (75 ins). Key: share func_8016004C via if/else join (do NOT duplicate it in the v2<0 arm — that emits an extra move a0,s0 + shifts the tail schedule); reload 0x1A0 byte after the inner if for the two global stores + func_80165670
#include "common.h"

extern s32 D_800AE6B0;
extern void (*D_801891B8[])(void *);
extern u8 D_80078EC1;
extern u8 D_80078EC2;
extern u16 D_801270C0;

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
    s32 v2;
    u8 cur;

    if ((D_800AE6B0 & 0x80FFFFFF) != 0) {
        ((void (*)(void))func_8016007C)();
        D_801891B8[*(u16 *)param_1](param_1);
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

DEFINE_func_8016004C()  /* dedup: shared engine-core @0x8016004C (src/shared) */

DEFINE_func_8016007C()  /* dedup: shared engine-core @0x8016007C (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_801601AC(s32 *a0);

void func_801600D0(s32 *a0) {
    func_80147078(a0, 0x18);
    func_801601AC(a0);
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_80160138(s32 *a0);

void func_80160104(s32 *a0) {
    func_80147078(a0, 0x18);
    func_80160138(a0);
}

// @class: struct
// @stuck: none — MATCH (established fnptr-table dispatch idiom: D_XXXX[*(u16*)(a0+2)](a0))

extern void (*D_80189590[])(void *);

void func_80160138(s32 * a0)
{
    D_80189590[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80160174()  /* dedup: shared engine-core @0x80160174 (src/shared) */

DEFINE_func_801601AC()  /* dedup: shared engine-core @0x801601AC (src/shared) */

/* func_801601E4 — if *(u16*)(a0+0xB8) == 0x8000 run the 3-call setup sequence,
 * else dispatch func_80161208 (canonically (void); a0 passed via ptr-cast). */

DEFINE_func_801601E4()  /* dedup: shared engine-core @0x801601E4 (src/shared) */

/* func_80160244 — twin of func_801601E4 with constants 0x23/0x1B.
 * if *(u16*)(a0+0xB8) == 0x8000 run the 3-call setup, else dispatch func_80161208. */

DEFINE_func_80160244()  /* dedup: shared engine-core @0x80160244 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801602A4);

DEFINE_func_8016032C()  /* dedup: shared engine-core @0x8016032C (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_80160410(s32 *a0);

void func_80160334(s32 *a0) {
    func_80147078(a0, 0x1B);
    func_80160410(a0);
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_8016039C(s32 *a0);

void func_80160368(s32 *a0) {
    func_80147078(a0, 0x1B);
    func_8016039C(a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016039C);

DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603D8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH

DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80160534);

DEFINE_func_801607B8()  /* dedup: shared engine-core @0x801607B8 (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_801608C0(s32 *a0);

void func_801607E4(s32 *a0) {
    func_80147078(a0, 0x1C);
    func_801608C0(a0);
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_8016084C(s32 *a0);

void func_80160818(s32 *a0) {
    func_80147078(a0, 0x1C);
    func_8016084C(a0);
}

extern void (*D_801895A8[])(void *);

void func_8016084C(s32 * a0)
{
    D_801895A8[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */

DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608C0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80160920);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801609B8);

DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160A28 (src/shared) */

DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160A74 (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_80160BB4(s32 *a0);

void func_80160ACC(s32 *a0) {
    func_80147078(a0, 0x1D);
    func_80160BB4(a0);
}

DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160B00 (src/shared) */

extern void (*D_801895B4[])(void);

s32 func_80160B34(s32 a0)
{
    D_801895B4[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160B70 (src/shared) */

DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160BB4 (src/shared) */

DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160C28 (src/shared) */

DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160CB4 (src/shared) */

// @class: struct
// @stuck: none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_801891B8 + func_80147078/func_80159B70 tail, func_80161208 else)

extern void (*D_801891B8[])(void *);
extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

void func_80160D10(void *arg0) {
    if (*(u32 *)((u8 *)arg0 + 0x44) & 0x10) {
        D_801891B8[*(u16 *)arg0](arg0);
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
        D_801891B8[*(u16 *)arg0](arg0);
    }
    ((void (*)(void *, s16))func_80147078)(arg0, 0);
    func_80159B70(arg0);
    return;
dd0:
    ((s32 (*)(void *))func_80161208)(arg0);
}

DEFINE_func_80160DEC()  /* dedup: shared engine-core @0x80160DEC (src/shared) */

DEFINE_func_80160E3C()  /* dedup: shared engine-core @0x80160E3C (src/shared) */

DEFINE_func_80160E70()  /* dedup: shared engine-core @0x80160E70 (src/shared) */

// @class: struct
// @stuck: none — MATCH (array-of-funcptr %lo-fold; index = lhu at +2 << 2)

extern FuncPtr D_801895C4[];

void func_80160EA4(int param_1)
{
    D_801895C4[*(unsigned short *)(param_1 + 2)]();
}

DEFINE_func_80160EE0()  /* dedup: shared engine-core @0x80160EE0 (src/shared) */

DEFINE_func_80160F00()  /* dedup: shared engine-core @0x80160F00 (src/shared) */

DEFINE_func_80160F70()  /* dedup: shared engine-core @0x80160F70 (src/shared) */

DEFINE_func_80160FE0()  /* dedup: shared engine-core @0x80160FE0 (src/shared) */

// @class: struct
// @stuck: none — MATCH

extern void func_80149020(s32 *a0);
extern void (*D_801891B8[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

void func_80161034(void *a0)
{
    func_80149020(a0);
    D_801891B8[*(u16 *)a0](a0);
    func_80147078(a0, 0);
    func_80159B70(a0);
}

DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */

DEFINE_func_801610FC()  /* dedup: shared engine-core @0x801610FC (src/shared) */

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */

DEFINE_func_80161124()  /* dedup: shared engine-core @0x80161124 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161208);

DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */

DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */

#include "common.h"

DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612B8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016130C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161374);

DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */

DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */

DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */

DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614E4 (src/shared) */

DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151C (src/shared) */

DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */

DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158C (src/shared) */

DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615C4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016163C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161774);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161888);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016191C);

DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197C (src/shared) */

DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619A4 (src/shared) */

DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619D0 (src/shared) */

DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161A00 (src/shared) */

DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161A30 (src/shared) */

DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161A60 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161A90);

DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161B18 (src/shared) */

DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161B84 (src/shared) */

#include "common.h"

DEFINE_func_80161BE0()  /* dedup: shared engine-core @0x80161BE0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161C24);

// @class: struct
// @stuck: none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern u16 D_801895F4[];
extern void func_80147324(s32 arg0);

void func_80161C98(int param_1, u32 param_2)
{
    if (param_2 < 8) {
        func_80147324(D_801895F4[param_2]);
    }
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161CD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80161D20);

DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161D58 (src/shared) */

// @class: other
// @stuck: none — MATCH (short-circuit && chain; reused 0x80FFFFFF mask const, andi-0xFF on callee ret)

extern s32 D_800AE6B0;
extern s32 D_800AE6A8;
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800D1734(void *);
extern s32 D_80189658;

void func_80161D88(void) {
    if ((D_800AE6B0 & 0x80FFFFFF) == 0 && (D_800AE6A8 & 0x80FFFFFF) == 0 &&
        (func_80029178(0x141) & 0xFF) != 0) {
        func_80029124(0x141, 0);
        func_80029124(0x95, 1);
        func_800D1734(&D_80189658);
    }
}

// @class: regalloc-order
// @stuck: none — MATCH (175 ins, relocation-masked). Giant, 3 similar guarded blocks. base=&D_800AF630
//   hoisted to $s2 (referenced only to build the 3 stored pointers base+0x65A8/0x65E0/0x6618 -> $s1);
//   guard reads (D_800B5BD8/C10/C48) + the "=1" + coord stores use direct symbols. Coord idiom:
//   -(s32)(u16)D_800AF7BC/2 + K (negu;srl31;addu;sra1). a2=func_800291DC(8) survives in $s3 for the
//   final (a2&0x7FFF)==(s16)D_80078EB0 test. KEY RESIDUAL (cracked): target computes each pointer into
//   scratch $v0 then `addu $s1,$v0` (dead-intermediate copy) and stores $s1 — natural C ALWAYS coalesces
//   that copy into a direct `addiu $s1,$s2,off` (172 ins, 3 short). Forcing the un-coalesced copy needs
//   an explicit `move` inline-asm (an empty "=r"/"0" re-tie is only a barrier, won't emit the copy).
#include "common.h"







void func_80161E08(s32 param_1) {
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
    extern u8 * D_801D9670[];
    extern u8 D_80189624[];
    extern u8 D_80189644[];
    extern u8 D_801D967C[];
    extern u8 D_801D96A4[];
    extern u8 D_801D96BC[];

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
            D_801D9670[0] = p;
            func_80024054(&D_80189624, &D_801D967C);
            func_8001CE28(p, &D_801D967C);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -(s32)(u16)D_800AF7BE / 2 + 0x28;
        }

        if (D_800B5C10 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x65E0));
            D_801D9670[1] = p;
            func_80024054(&D_80189644, &D_801D96A4);
            func_8001CE28(p, &D_801D96A4);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -(s32)(u16)D_800AF7BE / 2 + 0x30;
        }

        if (D_800B5C48 == 0) {
            __asm__("move %0,%1" : "=r"(p) : "r"(base + 0x6618));
            D_801D9670[2] = p;
            func_800242D0((s16)func_801620C4(), &D_801D96BC, 0x84);
            func_8001CE68(p, &D_801D96BC);
            D_800B5C74 = 1;
            D_800B5C50 = -(s32)(u16)D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -(s32)(u16)D_800AF7BE / 2 + 0x10;
        }

        func_800242D0((s16)func_801620C4(), &D_801D96BC, 0x84);
        if ((a2 & 0x7FFF) == (s32)D_80078EB0) {
            func_801622C4();
        }
    }
}


DEFINE_func_801620C4()  /* dedup: shared engine-core @0x801620C4 (src/shared) */

DEFINE_func_80162120()  /* dedup: shared engine-core @0x80162120 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

extern int D_801D9670[];

void func_8016216C(void)
{
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_801D9670;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}

// @class: regalloc-order
// @stuck: none — MATCH (62 ins, relocation-masked)
#include "common.h"

extern s32 func_800291DC(s32);
extern u8 D_80078E78[];
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 D_80189658;

s32 func_801621CC(s32 arg0) {
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
        return (s32)&D_80189658;
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
                return (s32)&D_80189658;
            }
            i++;
            if ((u32)s1[0x38] < (u32)lo) {
                return (s32)&D_80189658;
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
extern int D_801D9670[];

void func_801622C4(void)
{
    int *p;
    int i;

    ((int (*)(int, int))func_80029124)(0x141, 1);
    ((int (*)(int, int))func_800291C8)(8, 0);
    i = 0;
    p = &D_801D9670;
    do {
        ((int (*)(int, int))func_80016714)(*p, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}

extern void (*D_8018967C[])(void);

void func_80162330(void *a0) {
    D_8018967C[*(u8 *)((s32)a0 + 0x15)]();
}

DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236C (src/shared) */

DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623B8 (src/shared) */

DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (160 ins, relocation-masked). Keys: (1) base=&D_800AF630 hoisted, pinned $s2;
//   uVar2 UNPINNED (a $s3 pin forced the final `uVar2 & 0x7FFF` in-place+early, breaking the lh delay
//   slot). (2) item pinned $s1, dest INLINED (D_801D96Dx in both call args) so it lands $s0 AFTER a0.
//   (3) base assigned BEFORE the func_800291DC call so the return-copy `addu $s3,$v0` schedules after
//   the base lui/addiu. (4) THE MOVE: each block's `addu $s1,$v0,$zero` = compute `base+off` into a
//   $v0-PINNED temp `t`, then `item = t`. Two distinct hard regs ($v0 vs $s1) can't coalesce, forcing
//   the exact `addiu $v0,$s2,off ; addu $s1,$v0` pair the target emits (plain `item=base+off` coalesces
//   into one `addiu $s1` — 3 ins short). (5) store D_801D96C8[i] via `extern int D_801D96C8[]` (folds
//   %lo, consistent with func_80162760). Coord = (s16)(-D_800AF7Bx / 2 + K) (negu; srl 31; addu; sra 1).

#include "common.h"








s32 func_80162438(s32 _unused0) {
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_80189688[];
    extern s32 D_801896A0;
    extern u8 D_801D96D4[];
    extern u8 D_801D96FC[];
    extern u8 D_801D9718[];
    extern int D_801D96C8[];
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
            D_801D96C8[0] = (s32)item;
            func_80024054(D_80189688, D_801D96D4);
            func_8001CE28(item, D_801D96D4);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            register u8 *t __asm__("$2") = base + 0x65E0;
            item = t;
            D_801D96C8[1] = (s32)item;
            func_80024054(((u8 *)&D_801896A0), D_801D96FC);
            func_8001CE28(item, D_801D96FC);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            register u8 *t __asm__("$2") = base + 0x6618;
            item = t;
            D_801D96C8[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_801D9718, 0x84);
            func_8001CE68(item, D_801D9718);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_801D9718, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}


DEFINE_func_801626B8()  /* dedup: shared engine-core @0x801626B8 (src/shared) */

DEFINE_func_80162714()  /* dedup: shared engine-core @0x80162714 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (24 ins). do-while; load+call first, then p++ and i++ AFTER the call so gcc schedules p++/arg ahead of jal and i++ into the delay slot.

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

extern int D_801D96C8[];

void func_80162760(void)
{
    int *p;
    int i;

    func_800291C8(0x12, 0);
    i = 0;
    p = D_801D96C8;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}

DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627C0 (src/shared) */

// @class: struct
// @stuck: none — MATCH (19 ins, relocation-masked)
//
// Tiny dispatcher: byte count at D_8011F750 (offset 0 of a 0x58-byte ctl struct;
// cf. func_801627C0 which calls func_80016714(&D_8011F750, 0x58)). If nonzero,
// call D_801896C0[count - 1]() through a word-stride fn-pointer table.
//
// Two idioms combined to match gcc-2.7.2 -O2:
//  1. The target MATERIALIZES &D_8011F750 (lui;addiu %lo) into $a0 before the lbu
//     instead of folding %lo into the load. A direct global byte read always
//     %lo-folds (lui;lbu %lo), so force the full-address materialization with the
//     §21 re-tie barrier __asm__ __volatile__("":"=r"(p):"0"(p)) and pin the
//     pointer to $a0 with register __asm__("$4") to get the exact register.
//  2. Writing `idx = idx - 1;` as its OWN statement (not inline D_801896C0[count-1])
//     keeps the array index/decrement separate so %lo(D_801896C0) folds into the
//     dispatch load (lw %lo(...)($at)) — the inline form instead constant-folds the
//     -1*4 into a -4 load offset and drops the %lo fold (1 ins short, schedule off).

extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
extern void (*D_801896C0[])(void);   /* word-stride table of dispatch fn pointers */

void func_801627E8(void)
{
    register u8 *p __asm__("$4") = (u8 *)&D_8011F750;
    s32 idx;

    __asm__ __volatile__("" : "=r"(p) : "0"(p));   /* materialize &D_8011F750 into $a0 (defeat %lo-fold of the lbu) */
    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_801896C0[idx]();
    }
}

extern void (*D_801896C4[])(void);

void func_80162834(void *a0) {
    D_801896C4[*(u8 *)((s32)a0 + 0x1)]();
}

// @class: plumbing
// @stuck: none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);

extern u8 D_800B5CB8;
extern s32 D_801896B4;
extern s32 D_800B5CBC;
extern u8 D_800B5CDF;
extern s32 D_800B5CEC;

void func_80162870(s32 param_1) {
    *(s32 *)(param_1 + 8) = (s32)&D_800B5CB8;
    func_8001CB6C(&D_800B5CB8, (s32)&D_801896B4, 0x250, 0x1A0);
    D_800B5CEC = param_1 + 0xC;
    D_800B5CDF = 0x14;
    D_800B5CBC |= 0x60000000;
    func_80162968(param_1);
    func_80162ACC((u8 *)param_1);
}

DEFINE_func_801628F4()  /* dedup: shared engine-core @0x801628F4 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (pin p/iVar4/iVar3/iVar5 to $s2/$s1/$s0/$s3; div result in a fresh non-pinned local, NOT reused $s0)

#include "common.h"

DEFINE_func_80162968()  /* dedup: shared engine-core @0x80162968 (src/shared) */

DEFINE_func_80162AC0()  /* dedup: shared engine-core @0x80162AC0 (src/shared) */

DEFINE_func_80162ACC()  /* dedup: shared engine-core @0x80162ACC (src/shared) */

DEFINE_func_80162AE0()  /* dedup: shared engine-core @0x80162AE0 (src/shared) */

DEFINE_func_80162AF4()  /* dedup: shared engine-core @0x80162AF4 (src/shared) */

DEFINE_func_80162B1C()  /* dedup: shared engine-core @0x80162B1C (src/shared) */

DEFINE_func_80162CC4()  /* dedup: shared engine-core @0x80162CC4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80162CCC);

DEFINE_func_80162D28()  /* dedup: shared engine-core @0x80162D28 (src/shared) */

DEFINE_func_80162D88()  /* dedup: shared engine-core @0x80162D88 (src/shared) */

DEFINE_func_80162DE8()  /* dedup: shared engine-core @0x80162DE8 (src/shared) */

DEFINE_func_80162E48()  /* dedup: shared engine-core @0x80162E48 (src/shared) */

DEFINE_func_80162EA8()  /* dedup: shared engine-core @0x80162EA8 (src/shared) */

DEFINE_func_80162F08()  /* dedup: shared engine-core @0x80162F08 (src/shared) */

DEFINE_func_80162F60()  /* dedup: shared engine-core @0x80162F60 (src/shared) */

DEFINE_func_80162F80()  /* dedup: shared engine-core @0x80162F80 (src/shared) */

DEFINE_func_80162FA0()  /* dedup: shared engine-core @0x80162FA0 (src/shared) */

DEFINE_func_80162FC0()  /* dedup: shared engine-core @0x80162FC0 (src/shared) */

DEFINE_func_80162FF4()  /* dedup: shared engine-core @0x80162FF4 (src/shared) */

DEFINE_func_801630C4()  /* dedup: shared engine-core @0x801630C4 (src/shared) */

DEFINE_func_80163194()  /* dedup: shared engine-core @0x80163194 (src/shared) */

DEFINE_func_80163234()  /* dedup: shared engine-core @0x80163234 (src/shared) */

DEFINE_func_8016325C()  /* dedup: shared engine-core @0x8016325C (src/shared) */

DEFINE_func_801632E0()  /* dedup: shared engine-core @0x801632E0 (src/shared) */

DEFINE_func_801632F0()  /* dedup: shared engine-core @0x801632F0 (src/shared) */

DEFINE_func_80163328()  /* dedup: shared engine-core @0x80163328 (src/shared) */

DEFINE_func_801633A8()  /* dedup: shared engine-core @0x801633A8 (src/shared) */

// @class: struct
// @stuck: none — MATCH (21 ins, relocation-masked)


s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {
    extern int func_8016345C(int, unsigned short, int, unsigned short, void *);
    extern unsigned char D_801D8BB0[8];

    unsigned char sp18[8];
    memcpy(sp18, D_801D8BB0, 8);
    return func_8016345C(((int)param_1), ((int)param_2), ((int)param_3), ((int)param_4), sp18);
}


DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345C (src/shared) */

// @class: struct
// @stuck: none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)

extern char D_801D8BB0[8];

extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5)
{
    char buf[8];

    memcpy(buf, D_801D8BB0, 8);
    ((void (*)(s32, u16, u16, s32, u16, s32))func_80163534)(param_1, param_2, param_3, param_4, param_5, (s32)buf);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80163534);

DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */

DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636D0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80163764);

DEFINE_func_8016380C()  /* dedup: shared engine-core @0x8016380C (src/shared) */

DEFINE_func_801638A0()  /* dedup: shared engine-core @0x801638A0 (src/shared) */

DEFINE_func_80163950()  /* dedup: shared engine-core @0x80163950 (src/shared) */

extern void (*D_801896CC[])(void);

void func_80163A58(void *a0) {
    D_801896CC[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: struct
// @stuck: none — MATCH (102 ins). Key: 32-byte copy 0x34..0x50 = two 16-byte struct
//   assignments (Blk16{u32 a,b,c,d}) → gcc's a0-a3 4-reg block copy, also fixing the
//   v1/v0 load order + load-delay nop. func_8014659C cast to (s32(*)(void)) for its used $v0.
#include "common.h"

extern void func_8014659C(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80147324(s32 arg0);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);

extern s32 D_800DE5A0;
extern s32 D_800636C8;

/* Blk16 lifted to src/shared/engine_types.h (Phase 22). */

DEFINE_func_80163A94()  /* dedup: shared engine-core @0x80163A94 (src/shared) */

DEFINE_func_80163C2C()  /* dedup: shared engine-core @0x80163C2C (src/shared) */

/* func_80163EC8 (234 ins, ov_SC01_077 / ov_SC01_077_after, x134) — MATCH via rtu_match.
 *
 * Actor "afterimage/trail" update: reads the actor's sub-struct at param_1+0x4C (psVar6) and
 * the render node at param_1+0x20 (iVar8), ticks func_80162D88, then either RESETS the trail
 * (id mismatch / no owner) or advances it (matched) and re-solves the wobble via func_80012F74.
 *
 * NOT the K&R s16-param class (§43) — single pointer param; raw-offset-cast house style.
 *
 * CRACK — the reset tail is written DUPLICATED INLINE in BOTH predecessors (==0 path and the
 * cond-mismatch path), NOT as one shared `goto` block. gcc-2.7.2 jump.c CROSS-JUMPS the two
 * copies into one tail, and that is what produces the target's exact dbr delay-slot schedule:
 *   - a0=param_1 (call1 arg) HOISTED into the cond1 `bnez` delay slot (serves both paths),
 *   - the `& ~0x20` mask const (`addiu $v1,-0x21`) RE-MATERIALISED per-predecessor in the
 *     `j`/`beq` delay slots (it shares $v1 with cond2's `lh`, so it can't be held), and
 *   - the reset body scheduled `sh; sh; and` (mask consumer last).
 * A single shared `goto`-tail instead leaves the mask inline (+1 insn) or fills the bnez slot
 * with the mask + an extra a0 (dbr D1/D2 wall). The duplicated-tail + cross-jump is the lever.
 *
 * Other levers:
 *  - Blk8 struct-assign for the D_801D8BB8 8-byte copy => lwl/lwr/swl/swr (real-TU-safe; a
 *    memcpy() would lower to `jal memcpy` in-TU, §42a).
 *  - func_80149350 cast to 3-arg (its in-TU DEFINE is 1-arg), like sibling func_80166994.
 *  - func_801656D0 kept u8 (its in-TU def) => the +uVar3 use emits the byte zero-extend `andi`.
 *  - if/else polarity matched to the target fall-through (§3): `>=` forms, not `<`.
 *  - ONE register pin: uVar5 -> $v0 (natural return-value reg; the reused v0 temp). PIN FLAGGED
 *    for the x134 sweep — a single benign $v0 pin on a clean structural family (low SIGABRT risk
 *    vs the §42e pin-heavy families), but --edit-remap should byte-gate each sibling.
 *
 * No //@EDIT (void return, no self canon-sig in the split) and no ec_edit (no global type flip);
 * fully block-scoped externs => zero file-scope footprint for the x134 remap.
 */
#include "common.h"

void func_80163EC8(s32 param_1) {
    extern Blk8 D_801D8BB8;
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

    in = D_801D8BB8;
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

DEFINE_func_801642AC()  /* dedup: shared engine-core @0x801642AC (src/shared) */

// @class: schedule
// @stuck: none — MATCH (match_one 57/57). Levers: decl-order regalloc (s1=a0, s0=*(s1+0x4c) like sibling func_801642AC) + branch-polarity invert on the A||B||C guard (THEN-block placed last, 17->4) + cached v44=*(s0+0x44) reused for &0x400 test and |0x10 + volatile barrier on s0 to anchor sh 0x188 before $a0 materialization (4->0).

DEFINE_func_8016432C()  /* dedup: shared engine-core @0x8016432C (src/shared) */

DEFINE_func_80164410()  /* dedup: shared engine-core @0x80164410 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80164418);

#include "common.h"

DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */

// @class: struct
// @stuck: none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void (*D_80189720[])(void);
extern void func_80162D28(s32 *a0);

void func_80164744(s32 param_1)
{
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x20);
    D_80189720[*(u16 *)(param_1 + 2)]();
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

extern u16 D_800DF2E0;
extern s32 D_801896E8;
extern u16 D_8018971C;
extern s16 D_8018971A;
extern s16 D_80189718;

void func_801647A4(int param_1) {
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_801896E8;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        D_8018971C = 0x80;
        D_8018971A = 0x80;
        D_80189718 = 0x80;
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

// @class: regalloc-order — wave-3 real-TU crack (§42a); cracked at Max.
// Fix: D_8018971C read needs direct-addressed `lhu` (u16). Cannot use `*(u16*)&D_8018971C`
// (forces &sym into a held reg -> drift) NOR a block-scoped `extern u16` (conflicting-types
// ERROR vs the ambient s16, cc1 exit 33). Solution: flip the file-scope decl (5802) to u16 —
// byte-neutral to the only other user (func_801647A4 store-only) — and reference directly.
typedef struct {
    u16 f0;
    u8 pad0[0x4e];
    int f50;
    u8 pad1[0x14];
} Ent_80164930;


void func_80164930(s32 param_1) {
    int iVar3 = *(int *)(((int)param_1) + 0x20);
    if (*(int *)(((int)param_1) + 0x50) == 0) {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x100;
        short nv;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) + 0x71;
        nv = D_8018971C - 8;
        D_8018971C = nv;
        D_8018971A = nv;
        D_80189718 = nv;
        if (nv < -0x80) {
            int i, lim;
            Ent_80164930 *p;
            for (i = 0, lim = 0x19, p = ((Ent_80164930 *)&D_8011F9D0); i < 0x14; i++) {
                if (p->f0 == lim && p->f50 != 0) {
                    ((void(*)(Ent_80164930 *))func_80162CCC)(p);
                }
                p++;
            }
            ((void(*)(Ent_80164930 *))func_80162CCC)((Ent_80164930 *)((int)param_1));
        } else {
            ((void(*)(int))func_80164ACC)(((int)param_1));
        }
    } else {
        short sVar1 = *(u16 *)(iVar3 + 0x1c) + 0x40;
        u16 uVar2;
        *(short *)(iVar3 + 0x1c) = sVar1;
        *(short *)(iVar3 + 0x18) = sVar1;
        uVar2 = *(u16 *)(iVar3 + 0x1a) - 0x200;
        *(u16 *)(iVar3 + 0x1a) = uVar2;
        if ((int)((unsigned)uVar2 << 0x10) < 0) {
            *(short *)(iVar3 + 0x1a) = 0;
        }
        *(short *)(iVar3 + 0x12) = *(u16 *)(iVar3 + 0x12) - 0x71;
    }
}

DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164A74 (src/shared) */

DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164ACC (src/shared) */

extern void (*D_8018972C[])(void);

void func_80164BA0(void *a0) {
    D_8018972C[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: regalloc-order
// @stuck: none — MATCH (pins $16/$17/$18 + branch restructure + base-relative store of D_801D9728 via $s2)
#include "common.h"

extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);

extern u8 D_801D9728;
extern u8 D_801D9729;
extern u8 D_801D972A;
extern u8 D_801D972B;
extern u8 D_801D972C;
extern u8 D_801D972D;
extern u8 D_801D972E;
extern u8 D_801D972F;

void func_80164BDC(s32 param_1)
{
    register s32 p1   __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */
    register s32 base __asm__("$18");  /* $s2 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_801D9728;
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CD50(iVar1, base);
        ((void (*)(s32, s32))func_800233CC)(base, 0x60);
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        D_801D9729 = 0xf0;
        *(u8 *)base = 0xf0;
        D_801D972A = 0xc0;
        D_801D972E = 0;
        D_801D972D = 0;
        D_801D972C = 0;
        D_801D972F = 0;
        D_801D972B = 0;
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

DEFINE_func_80164CD4()  /* dedup: shared engine-core @0x80164CD4 (src/shared) */

DEFINE_func_80164D4C()  /* dedup: shared engine-core @0x80164D4C (src/shared) */

DEFINE_func_80164DB0()  /* dedup: shared engine-core @0x80164DB0 (src/shared) */

DEFINE_func_80164DD0()  /* dedup: shared engine-core @0x80164DD0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80164E40);

extern s32 (*D_8018973C[])();

s32 func_80164EA4(s16 *a0) {
    return D_8018973C[(u16)a0[1]]();
}

// @class: struct
// @stuck: none — MATCH

  /* stride 0x10 */
extern DStruct D_801D9774[];

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

void func_80164EE0(int param_1)
{
    int i;

    for (i = 7; i >= 0; i--) {
        D_801D9774[i].f0 = 0;
    }
    *(short *)(param_1 + 0x2e) = 0x4000;
    *(short *)(param_1 + 0x2c) = 0x4000;
    *(short *)(param_1 + 0x60) = 0;
    *(short *)(param_1 + 0x62) = 0;
    ((void (*)(int))func_80165124)(param_1);
    *(short *)(param_1 + 0x66) = 0;
    ((void (*)(int))func_80146CA0)(param_1);
}

DEFINE_func_80164F44()  /* dedup: shared engine-core @0x80164F44 (src/shared) */

DEFINE_func_80165024()  /* dedup: shared engine-core @0x80165024 (src/shared) */

DEFINE_func_80165064()  /* dedup: shared engine-core @0x80165064 (src/shared) */

DEFINE_func_801650C4()  /* dedup: shared engine-core @0x801650C4 (src/shared) */

DEFINE_func_80165124()  /* dedup: shared engine-core @0x80165124 (src/shared) */

// @class: struct
// @stuck: none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_801D9768[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).


typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_80165140;
typedef struct { u8 d[4]; } __attribute__((packed, aligned(1))) B4;
typedef struct { B8_80165140 a; B4 b; s32 used; } Slot;


s32 func_80165140(s32 param_1) {
    extern Slot D_801D9768[8];

    int i;
    Slot *p;
    for (i = 0; i < 8; i++) {
        p = &D_801D9768[i];
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
extern s32 D_801D9768;

void func_801651B8(void * param_1)
{
    register s32 *puVar1 __asm__("$16"); /* $s0 */
    register s32 iVar2 __asm__("$17");   /* $s1 */
    register s32 p __asm__("$18");        /* $s2 */

    p = param_1;
    func_80165240(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_801D9768;
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80165240);

DEFINE_func_8016533C()  /* dedup: shared engine-core @0x8016533C (src/shared) */

DEFINE_func_80165374()  /* dedup: shared engine-core @0x80165374 (src/shared) */

DEFINE_func_801653B8()  /* dedup: shared engine-core @0x801653B8 (src/shared) */

DEFINE_func_801653F4()  /* dedup: shared engine-core @0x801653F4 (src/shared) */

// @class: struct
// @stuck: none — MATCH (54 ins)

extern u8 D_80078E78[];
extern u8 D_80078EC1;
extern void (*D_80189780[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

void func_801654A8(s32 arg0)
{
    u8 *s1 = D_80078E78;

    if (*(u16 *)arg0 == 0x16) {
        return;
    }
    if (*(u16 *)arg0 != 0x1A) {
        if ((*(s32 *)(arg0 + 0x1F8) & 0x80FFFFFF) == 0) {
            if (func_80165658(arg0, D_80078EC1) & 0x80) {
                ((void (*)(s32))D_80189780[D_80078EC1 & 0x7F])(arg0);
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

extern u8 D_80078EC5;
extern u8 D_80078EC1;
extern void (*D_80189780[])(void);
extern void func_80165B28(void *a0);

void func_80165580(s32 _arg0)
{
    if (D_80078EC5 & 0x80) {
        ((void (*)(void))func_80165B28)();
    } else {
        D_80189780[D_80078EC1 & 0x7F]();
    }
}

DEFINE_func_801655E4()  /* dedup: shared engine-core @0x801655E4 (src/shared) */

DEFINE_func_80165624()  /* dedup: shared engine-core @0x80165624 (src/shared) */

extern u8 D_801897FC[];

u8 func_80165658(s32 a0, s32 a1) {
    return D_801897FC[a1 & 0x7F];
}

extern s32 D_8018981C[];
extern s32 D_80078EC8;

void func_80165670(s32 a0, s32 a1) {
    D_80078EC8 = D_8018981C[a1 & 0x7F];
}

DEFINE_func_80165694()  /* dedup: shared engine-core @0x80165694 (src/shared) */

extern u8 D_80189898[];

u8 func_801656D0(s32 a0, s32 a1) {
    return D_80189898[a1 & 0x7F];
}

extern u8 D_801898B8[];

u8 func_801656E8(s32 a0, s32 a1) {
    return D_801898B8[a1 & 0x7F];
}

extern u8 D_801898D8[];

u8 func_80165700(s32 a0, s32 a1) {
    return D_801898D8[a1 & 0x7F];
}

DEFINE_func_80165718()  /* dedup: shared engine-core @0x80165718 (src/shared) */

DEFINE_func_80165770()  /* dedup: shared engine-core @0x80165770 (src/shared) */

DEFINE_func_801657A0()  /* dedup: shared engine-core @0x801657A0 (src/shared) */

DEFINE_func_801657D8()  /* dedup: shared engine-core @0x801657D8 (src/shared) */

DEFINE_func_80165840()  /* dedup: shared engine-core @0x80165840 (src/shared) */

DEFINE_func_80165874()  /* dedup: shared engine-core @0x80165874 (src/shared) */

DEFINE_func_801658DC()  /* dedup: shared engine-core @0x801658DC (src/shared) */

DEFINE_func_801658EC()  /* dedup: shared engine-core @0x801658EC (src/shared) */

DEFINE_func_80165900()  /* dedup: shared engine-core @0x80165900 (src/shared) */

DEFINE_func_80165910()  /* dedup: shared engine-core @0x80165910 (src/shared) */

DEFINE_func_80165938()  /* dedup: shared engine-core @0x80165938 (src/shared) */

DEFINE_func_80165958()  /* dedup: shared engine-core @0x80165958 (src/shared) */

DEFINE_func_80165978()  /* dedup: shared engine-core @0x80165978 (src/shared) */

DEFINE_func_80165988()  /* dedup: shared engine-core @0x80165988 (src/shared) */

DEFINE_func_801659A8()  /* dedup: shared engine-core @0x801659A8 (src/shared) */

DEFINE_func_801659B8()  /* dedup: shared engine-core @0x801659B8 (src/shared) */

DEFINE_func_801659CC()  /* dedup: shared engine-core @0x801659CC (src/shared) */

extern s32 (*D_801898F8[])();

s32 func_801659DC(u8 *a0) {
    return D_801898F8[a0[0x1A0]]();
}

DEFINE_func_80165A18()  /* dedup: shared engine-core @0x80165A18 (src/shared) */

DEFINE_func_80165A20()  /* dedup: shared engine-core @0x80165A20 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH

DEFINE_func_80165A50()  /* dedup: shared engine-core @0x80165A50 (src/shared) */

DEFINE_func_80165A78()  /* dedup: shared engine-core @0x80165A78 (src/shared) */

extern u8 D_80078EC1;
extern void (*D_80189974[])(void);

void func_80165AC8(void) {
    D_80189974[D_80078EC1 & 0x7F]();
}

DEFINE_func_80165B08()  /* dedup: shared engine-core @0x80165B08 (src/shared) */

DEFINE_func_80165B10()  /* dedup: shared engine-core @0x80165B10 (src/shared) */

DEFINE_func_80165B18()  /* dedup: shared engine-core @0x80165B18 (src/shared) */

DEFINE_func_80165B20()  /* dedup: shared engine-core @0x80165B20 (src/shared) */

extern void (*D_801899F0[])(void);

void func_80165B28(void *a0) {
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_801899F0[*(u8 *)((s32)a0 + 0x197)]();
}

DEFINE_func_80165B6C()  /* dedup: shared engine-core @0x80165B6C (src/shared) */

DEFINE_func_80165BB4()  /* dedup: shared engine-core @0x80165BB4 (src/shared) */

extern s32 func_80161208(void);
extern void func_80165C58(s32 arg0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_80165BFC(void *a0) {
    if (func_80161208() == 0) {
        if (*(u16 *)((u8 *)a0 + 0xB8) & 0x8000) {
            func_80165C58((s32)a0);
            func_801599A4(a0);
            func_80159B3C(a0);
        }
    }
}

DEFINE_func_80165C58()  /* dedup: shared engine-core @0x80165C58 (src/shared) */

DEFINE_func_80165C78()  /* dedup: shared engine-core @0x80165C78 (src/shared) */

// @class: schedule
// @stuck: none — MATCH
extern s32 D_8011D030;
extern s32 D_80126728;
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
void func_80165CA0(void) {
    extern s32 D_8011D030;
    extern s32 D_80126728;

    register s32 i __asm__("$17");
    s32 off;
    u16 *q;
    s32 a1, base;
    short *p;
    register short v __asm__("$2");
    register short w __asm__("$3");
    i = 0; q = &D_8011D030;
    do {
        if (*q != 0) (*(void (**)(u16 *))((u32)*q * 4 + D_80126728))(q);
        i = i + 1; q = q + 0x2c;
    } while (i < 0x1e);
    i = 0; off = 0;
    do {
        base = (s32)&D_8011D030; SHB(base);
        a1 = off + base;
        p = *(short **)(a1 + 0x20);
        if (p != 0) {
            s32 q2;
            if ((u16)*p == 1) {
                v = *(short *)(a1 + 6); p[4] = v; SHB(v); *(int *)(p + 0x24) = v;
                v = *(short *)(a1 + 0xa); p[5] = v; SHB(v); *(int *)(p + 0x26) = v;
                w = *(short *)(a1 + 0xe); p[6] = w; v = p[0x16] | 1; SHB(w); p[0x16] = v; *(int *)(p + 0x28) = w;
            } else if ((q2 = *(int *)(p + 0x1a)) != 0) {
                v = *(short *)(a1 + 6); p[4] = v; SHB(v); *(int *)(q2 + 0x14) = v;
                v = *(short *)(a1 + 0xa); p[5] = v; q2 = *(int *)(p + 0x1a); SHB(v); *(int *)(q2 + 0x18) = v;
                v = *(short *)(a1 + 0xe); p[6] = v; q2 = *(int *)(p + 0x1a); SHB(v); *(int *)(q2 + 0x1c) = v;
            } else {
                p[4] = *(short *)(a1 + 6); p[5] = *(short *)(a1 + 0xa); p[6] = *(short *)(a1 + 0xe);
            }
        }
        i = i + 1; off = off + 0x58;
    } while (i < 0x1e);
}

M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D8BC0;

void func_80165E2C(u16 *arg0) {
    func_8001534C(0, &D_801D8BC0, 0x80, 0x80, 0, 0);
    func_800153CC(1, *arg0, 0xA8, 0x80, 0x40, 0);
}

DEFINE_func_80165E90()  /* dedup: shared engine-core @0x80165E90 (src/shared) */

#include "common.h"

DEFINE_func_80165FA4()  /* dedup: shared engine-core @0x80165FA4 (src/shared) */

extern s32 (*D_801899FC[])();

s32 func_80166018(s16 *a0) {
    return D_801899FC[(u16)a0[1]]();
}

DEFINE_func_80166054()  /* dedup: shared engine-core @0x80166054 (src/shared) */

DEFINE_func_801661CC()  /* dedup: shared engine-core @0x801661CC (src/shared) */

DEFINE_func_80166244()  /* dedup: shared engine-core @0x80166244 (src/shared) */

DEFINE_func_8016629C()  /* dedup: shared engine-core @0x8016629C (src/shared) */

DEFINE_func_801662F4()  /* dedup: shared engine-core @0x801662F4 (src/shared) */

DEFINE_func_8016634C()  /* dedup: shared engine-core @0x8016634C (src/shared) */

DEFINE_func_801663A4()  /* dedup: shared engine-core @0x801663A4 (src/shared) */

extern s32 (*D_80189A04[])();

s32 func_801663FC(s16 *a0) {
    return D_80189A04[(u16)a0[1]]();
}

DEFINE_func_80166438()  /* dedup: shared engine-core @0x80166438 (src/shared) */

DEFINE_func_801665B4()  /* dedup: shared engine-core @0x801665B4 (src/shared) */

extern s32 (*D_80189ACC[])();

s32 func_80166618(s16 *a0) {
    return D_80189ACC[(u16)a0[1]]();
}

extern s32 (*D_80189ADC[])();

s32 func_80166654(s16 *a0) {
    return D_80189ADC[(u16)a0[1]]();
}

#include "common.h"

typedef struct { u16 h[6]; } Rec_80166690;   /* 12-byte sub-table record (stride 0xC) */

typedef struct {
    short v0, v1, v2, pad06, w0, w1, w2, pad0E;          /* 0x00..0x0F */
    short v3, v4, v5, pad16, w3, w4, w5, pad1E;          /* 0x10..0x1F */
    u8 c00, c01, c02, pad23;                             /* 0x20 */
    u8 c10, c11, c12, pad27;                             /* 0x24 */
    u8 c20, c21, c22, pad2B;                             /* 0x28 */
    u8 c30, c31, c32, pad2F;                             /* 0x2C */
    int tag;                                             /* 0x30 -> struct size 0x34; tag lands at sp+0x40 */
} Frame_80166690;

extern s32 func_80017758(void *a0, void *a1);
extern Blk20 D_800AE620;
extern u8 D_801D97E8[];

s32 func_80166690(s32 param_1, s32 param_2)
{
    Frame_80166690 c;
    Blk20 blk;
    Rec_80166690 *sub;
    Rec_80166690 *pv;
    u8 *rec;
    int i6;
    int lt2;
    int p2;
    unsigned int uVar7, uVar8, uVar9;
    int iVar3;
    unsigned int w9, w7, w, t, w3b;
    int w3;
    short sVar10;
    register unsigned int zr __asm__("$0");

    blk = D_800AE620;
    i6 = (short)param_1;
    c.tag = 0x50000000;
    rec = &D_801D97E8[i6 * 0xC4];
    sVar10 = 0;
    if (rec[0] == 0) {
        return 0;
    }
    sub = (Rec_80166690 *)(rec + 4);
    uVar9 = rec[1];
    uVar8 = rec[3];
    uVar7 = uVar8 >> 1;
    iVar3 = rec[2];
    w3 = iVar3 - 1;
    iVar3 = w3 + zr;
    if (w3 != -1) {
        lt2 = i6 < 2;
        p2 = (short)param_2;
        do {
            pv = &sub[(short)uVar9];
            c.v0 = pv->h[0];
            c.v1 = pv->h[1];
            c.v2 = pv->h[2];
            c.w0 = pv->h[3];
            c.w1 = pv->h[4];
            c.w2 = pv->h[5];
            sVar10 = sVar10 + 1;

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8 + zr;
                    c.c12 = t; c.c02 = t;
                    t = uVar7 + zr;
                } else {
                    w = ((int)(uVar8 << 16) >> 17) + ((int)(uVar8 << 16) >> 19);
                    uVar7 = w + zr;
                    c.c12 = w; c.c02 = w;
                    t = uVar8 + zr;
                }
                c.c11 = t; c.c01 = t; c.c10 = t; c.c00 = t;
            } else {
                t = uVar8 + zr;
                c.c10 = t; c.c00 = t;
                t = uVar7 + zr;
                c.c12 = t; c.c02 = t; c.c11 = t; c.c01 = t;
            }

            w9 = uVar9 - 1;
            uVar9 = w9 + zr;
            if ((int)(w9 << 16) < 0) {
                uVar9 = 0xF;
            }
            pv = &sub[(short)uVar9];
            c.v3 = pv->h[0];
            c.v4 = pv->h[1];
            c.v5 = pv->h[2];
            c.w3 = pv->h[3];
            c.w4 = pv->h[4];
            uVar8 = uVar8 - 0x10;
            w7 = uVar7 - 0x10;
            uVar7 = w7 + zr;
            c.w5 = pv->h[5];
            if ((int)(w7 << 16) < 0) {
                uVar7 = 0;
            }

            if (lt2) {
                if (p2 == 0) {
                    t = uVar8 + zr;
                    c.c32 = t; c.c22 = t;
                    t = uVar7 + zr;
                } else {
                    t = uVar7 + zr;
                    c.c32 = t; c.c22 = t;
                    t = uVar8 + zr;
                }
                c.c31 = t; c.c21 = t; c.c30 = t; c.c20 = t;
            } else {
                t = uVar8 + zr;
                c.c30 = t; c.c20 = t;
                t = uVar7 + zr;
                c.c32 = t; c.c22 = t; c.c31 = t; c.c21 = t;
            }

            __asm__ __volatile__("" :: "r"(iVar3));
            func_80017758(&c, &blk);
            w3b = iVar3 - 1;
            iVar3 = w3b + zr;
        } while ((short)w3b != -1);
    }
    return (short)sVar10;
}

/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_801D97E8).
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
    extern u8 D_801D97E8[];
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern s32 VectorNormalSS(void *a0, void *a1);

    Trail *p = &((Trail *)D_801D97E8)[param_3];
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


// @class: regalloc-order
// @stuck: none — MATCH (69 ins). Pins $s4/$s1 for param_2/param_3 + a1/a2-pinned temps
//   with non-volatile SHB barriers force the sign-ext move-form; short iVar2 (unpinned)
//   gives the temp-form counter increment that fills the skip-branch delay slots;
//   loop-invariant eq=(p2==p3) hoisted; SHB(p2) after the move serializes param_2 before
//   param_3's sign-ext (last ordering swap); param_1/param_4 left natural (arg-order saves).


#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

void func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4)
{
    extern unsigned char D_801D97E8[];

    register int p2 __asm__("$20");             /* $s4 */
    register int p3 __asm__("$17");             /* $s1 */
    register int t2 __asm__("$5");              /* a1 */
    register int t3 __asm__("$6");              /* a2 */
    unsigned short *puVar1;
    short iVar2;
    int eq;

    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    t2 = ((short)param_2); SHB(t2); p2 = t2; SHB(p2);
    t3 = ((short)param_3); SHB(t3); p3 = t3;
    eq = (p2 == p3);
    do {
        if ((puVar1 != ((unsigned short *)param_1)) &&
            ((unsigned int)*puVar1 == p2 || (unsigned int)*puVar1 == p3) &&
            (!eq ||
             *(int *)(puVar1 + 0x16) == *(int *)(((unsigned short *)param_1) + 0x16))) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
    ((void(*)(void *, int))func_80016714)(&D_801D97E8[((short)param_4) * 0xc4], 0xc4);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016706C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801670E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80167540);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80167714);

extern s32 (*D_80189AEC[])();

s32 func_801678B4(s16 *a0) {
    return D_80189AEC[(u16)a0[1]]();
}

#include "common.h"

extern s32 rand(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146C3C(void);
extern u16 D_800B99DA;

void func_801678F0(s32 a0) {
    s32 p;
    s32 r;
    s16 buf[4];

    p = *(s32 *)(a0 + 0x34);
    if ((*(s32 *)(p + 0x44) & 0x10) != 0) {
        if (*(s16 *)(a0 + 0x12) > *(s16 *)(a0 + 0x10)) {
            if (*(s32 *)(a0 + 0x1C) > 0) {
                *(u16 *)(a0 + 0x10) = rand() & 0x30;
                *(s32 *)(a0 + 0x1C) = -0x30;
            }
        } else {
            if (*(s32 *)(a0 + 0x1C) < 0) {
                *(u16 *)(a0 + 0x10) = (rand() & 0x30) + 0x40;
                *(s32 *)(a0 + 0x1C) = 0x30;
            }
        }
        *(s16 *)(a0 + 0x12) = *(u16 *)(a0 + 0x12) + *(s32 *)(a0 + 0x1C);
        if (*(s32 *)(a0 + 0x30) != 0) {
            *(s32 *)(a0 + 0x30) = *(s32 *)(a0 + 0x30) - 0xC0;
        }
        buf[0] = 0x400;
        buf[1] = 0;
        buf[2] = D_800B99DA << 8;
        RotMatrixYXZ((void *)buf, (void *)(a0 + 0x38));
        ((void (*)(s32, s32))func_80048EAC)(*(s32 *)(p + 0x20) + 0x34, a0 + 0x38);
        func_801670E4(a0, -6, -0x44, -0x18);
        r = ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0xE, a0, *(s16 *)(a0 + 6), *(s16 *)(a0 + 0xA), *(s16 *)(a0 + 0xE), 0, 0);
        if (r != 0) {
            *(Blk32 *)(r + 0x38) = *(Blk32 *)(a0 + 0x38);
        }
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}

extern s32 (*D_80189AF8[])();

s32 func_80167A9C(s16 *a0) {
    return D_80189AF8[(u16)a0[1]]();
}

DEFINE_func_80167AD8()  /* dedup: shared engine-core @0x80167AD8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH expected; mirrors already-matched sibling func_8016A290 (same 3-loop tail), swapping the inline matrix-setup for a func_80168070 call + constant color block.

#include "common.h"



typedef struct { s16 x, y, z, pad; } SVEC_80167AE0;

struct Fr {
    u8   matrix[0x20];                    /* 0x00 -> sp+0x10 */
    SVEC_80167AE0 v[4];                            /* 0x20 -> sp+0x30 */
    struct { u8 r, g, b, pad; } col[4];   /* 0x40 -> sp+0x50 */
    u32  code;                            /* 0x50 -> sp+0x60 */
};

s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3) {
    extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
    extern s32 func_80017758(void *a0, void *a1);
    extern u8 D_80189C04;
    extern u8 D_80189C18[];

    struct Fr fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;

    func_80168070(param_1, ((s16 *)param_2), ((s16 *)param_3), fr.matrix);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = 0xa0;
    } else if (flags & 2) {
        fr.col[1].r = 0xc0;
    } else {
        fr.col[1].r = 0x80;
    }

    p = ((u8 *)&D_80189C04);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 2;
    fr.col[1].g = fr.col[1].r >> 2;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_80189C18;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.matrix);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.matrix);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}


// @class: schedule
// @stuck: none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u16  D_800B99DA;
extern u8   D_80189A58[];
extern u8   D_80189A6C[];

s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2) {
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

    p = D_80189A58;
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

    p = D_80189A6C;
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


// @class: struct
// @stuck: none — MATCH (99 ins, relocation-masked); array-decay (§18) kept mid/dir/pos stack-resident

DEFINE_func_80168070()  /* dedup: shared engine-core @0x80168070 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (40 ins). Sibling func_80168430 template + leading func_80029178(0x81)&0xFF
//   sh@0x28 and (p+0x2c)&1 captured in a temp (stored AND passed as 4th arg, no reload). Key sched:
//   the mask/store of p+0x2c must come AFTER the D_80189A81[iVar3]->p+0x1c store (matches target
//   delaying andi $a3 + sw to 0x2C past the lbu); 3 reads of p+0x2c stay un-CSE'd via the temp.
#include "common.h"

extern s32 func_80029178(s32 arg);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_80189AB0[];
extern u8 D_80189A80[];
extern u8 D_80189A81[];

void func_801681FC(s32 param_1) {
    s32 iVar3;
    s32 a3;

    *(s16 *)(param_1 + 0x28) = func_80029178(0x81) & 0xFF;
    *(s32 *)(param_1 + 0x30) = D_80189AB0[*(s32 *)(param_1 + 0x2C)];
    iVar3 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80189A80[iVar3];
    *(s32 *)(param_1 + 0x1C) = D_80189A81[iVar3];
    a3 = *(s32 *)(param_1 + 0x2C) & 1;
    *(s32 *)(param_1 + 0x2C) = a3;
    func_80166F58(param_1, 4, 4, a3);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}

DEFINE_func_8016829C()  /* dedup: shared engine-core @0x8016829C (src/shared) */

DEFINE_func_80168328()  /* dedup: shared engine-core @0x80168328 (src/shared) */

#include "common.h"

s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_80166690(s32 a0, s32 a1);
DEFINE_func_801683D8()  /* dedup: shared engine-core @0x801683D8 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (33 ins). Emit D_80189ABC[*(int*)(p+0x2c)] store BEFORE iVar1; the
//   *(p+0x30) store between the two reads of p+0x2c blocks gcc-2.7.2 CSE -> it RELOADS (2nd lw).
//   Single call-crossing param naturally lands in $s0 (no pin needed).
#include "common.h"

extern u8 D_80189ABC[];
extern u8 D_80189A94[];
extern u8 D_80189A95[];
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80168430(s32 param_1) {
    s32 iVar1;

    *(s32 *)(param_1 + 0x30) = D_80189ABC[*(s32 *)(param_1 + 0x2C)];
    iVar1 = (*(s32 *)(param_1 + 0x2C) << 0x11) >> 0x10;
    *(s16 *)(param_1 + 0x2A) = D_80189A94[iVar1];
    *(s32 *)(param_1 + 0x1C) = D_80189A95[iVar1];
    func_80166F58(param_1, 5, 0x3B, 2);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}

DEFINE_func_801684B4()  /* dedup: shared engine-core @0x801684B4 (src/shared) */

DEFINE_func_80168540()  /* dedup: shared engine-core @0x80168540 (src/shared) */

DEFINE_func_801685EC()  /* dedup: shared engine-core @0x801685EC (src/shared) */

DEFINE_func_80168640()  /* dedup: shared engine-core @0x80168640 (src/shared) */

DEFINE_func_80168664()  /* dedup: shared engine-core @0x80168664 (src/shared) */

extern s32 (*D_80189B10[])();

s32 func_80168744(s16 *a0) {
    return D_80189B10[(u16)a0[1]]();
}

DEFINE_func_80168780()  /* dedup: shared engine-core @0x80168780 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (simple if/else dispatch; reload of +0x1c after call)

DEFINE_func_801687CC()  /* dedup: shared engine-core @0x801687CC (src/shared) */

// @class: decl-conflict (reconcile) — MATCH (108 ins), real-TU verified via rtu_match
// @crack: The wave-2 "8-residual SCHEDULE" note was a STALE-OBJECT / isolation phantom (§42b):
//   in the real TU the draft NOCOMPILEs — DEFINE_func_801687CC() (split line ~6757) expands
//   `extern void func_80168828(void);` right before the def, so `void func_80168828(s32 param_1)`
//   is a HARD `conflicting types` error (cc1 exit 33). RECONCILE-FIRST fix (sweep-safe, lives
//   entirely in the def — no //@EDIT, no macro edit): declare the fn `(void)` and capture a0 via
//     register s32 a0v __asm__("$4");  s32 param_1 = a0v;
//   The register-var binds incoming $a0; copying it into a NORMAL pseudo (live across the calls)
//   makes gcc allocate param_1 to a callee-saved reg, emitting the target's `addu $s1,$a0,$zero`
//   at idx2. NOTE: a DIRECT `register s32 param_1 __asm__("$4")` FAILS (param_1 stays in the
//   call-clobbered $a0 → 100-off). With this reconcile, gcc's natural schedule places the CSE'd
//   `li $v1,0x40` at idx15 with ZERO extra levers — the §42a lever-4 consumer-block reorder was
//   never needed. The $v1 pin (register c40 __asm__("$3")) is still load-bearing (else 0x40 folds
//   to a $v0 immediate). 134-overlay family exemplar: only D_80189B00 differs -> banks x134.
#include "common.h"

typedef struct {
    u16 f00, f02, f04, f06;
    s16 f08;
    u16 f0a, f0c, f0e, f10, f12, f14, f16;
    u8  f18, f19, f1a, f1b, f1c, f1d, f1e, f1f, f20, f21, f22, f23;
    u32 f24;
} Thing_80168828;


void func_80168828(void)
{
    extern s32 func_80017DC4(void *a0, void *a1);
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void func_800173BC(void *a0, void *a1);
    extern u16 D_80189B00[];

    register s32 a0v __asm__("$4");
    s32 param_1 = a0v;
    Thing_80168828 thing;
    s16 matA[16];
    s16 matB[16];
    s16 svec[4];
    u16 *p;
    short i;
    register s32 c40 __asm__("$3");   /* $v1: hold the CSE'd 0x40 (else gcc folds to $v0 immediate) */

    c40 = 0x40;
    thing.f04 = 2;
    thing.f0c = 0x24;
    thing.f14 = 0x28;
    thing.f08 = -3;
    thing.f10 = 3;
    thing.f02 = 0;
    thing.f00 = 0;
    thing.f12 = 0;
    thing.f0a = 0;
    thing.f18 = c40;
    thing.f19 = c40;
    thing.f22 = c40;
    thing.f1e = c40;
    thing.f1a = 0x10;
    thing.f20 = 0xff;
    thing.f1c = 0xff;
    thing.f21 = 0xc0;
    thing.f1d = 0xc0;
    thing.f24 = 0x50000000;

    svec[0] = *(u16 *)(param_1 + 6);
    svec[1] = *(u16 *)(param_1 + 0xA);
    svec[2] = *(u16 *)(param_1 + 0xE);
    func_80017E68(svec, matA);

    svec[0] = svec[1] = svec[2] = (*(s32 *)(param_1 + 0x1C) << 11) + 0x1000;
    ((void (*)(void *, void *))func_80017DC4)(svec, matA);

    svec[0] = *(u16 *)(param_1 + 0x12);
    svec[1] = *(u16 *)(param_1 + 0x16);
    svec[2] = *(u16 *)(param_1 + 0x1A);
    RotMatrixYXZ(svec, matB);

    func_80048EAC(matA, matB);

    svec[1] = 0;
    p = D_80189B00;
    for (i = 0; i < 4; i++) {
        svec[0] = *p++;
        svec[2] = *p++;
        ((void (*)(void *, void *))func_80049CAC)(svec, matA);
        func_80048EAC(matB, matA);
        func_800173BC(&thing, matA);
    }
}

extern s32 (*D_80189B18[])();

s32 func_801689D8(s16 *a0) {
    return D_80189B18[(u16)a0[1]]();
}

DEFINE_func_80168A14()  /* dedup: shared engine-core @0x80168A14 (src/shared) */

DEFINE_func_80168A88()  /* dedup: shared engine-core @0x80168A88 (src/shared) */

extern s32 (*D_80189B20[])();

s32 func_80168AA8(s16 *a0) {
    return D_80189B20[(u16)a0[1]]();
}

DEFINE_func_80168AE4()  /* dedup: shared engine-core @0x80168AE4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80168B70);

// @class: schedule
// @stuck: none — MATCH (95 ins, relocation-masked)
//   No prologue pins needed: gcc naturally allocates param_1->$s0/param_2->$s4/param_3->$s3/
//   param_4->$s2 and emits the arg-copies in parameter order. The loop-bottom is the only quirk:
//   the target splits the counter increment into a temp ($v0 = i+1) reused in BOTH the beqz delay
//   slot and the r!=0 path end, with i ($s1) committed once at the merge AND the loop test reading
//   the TEMP ($v0), not $s1. Reproduced by pinning the increment temp to $v0 ($2) + a zero-code
//   __asm__ barrier ('""' : "=r"(i) : "0"(i)) on i=tmp that blocks gcc CSE-ing i==tmp so the
//   (short)tmp test reads $v0 (sll $v0,$v0) instead of $s1 (sll $v0,$s1). Without the barrier: 1-off.
DEFINE_func_80168BDC()  /* dedup: shared engine-core @0x80168BDC (src/shared) */

extern s32 (*D_80189B28[])();

s32 func_80168D58(s16 *a0) {
    return D_80189B28[(u16)a0[1]]();
}

// @class: regalloc-order
// @stuck: none — MATCH (pins $2/$3/$4/$5 + 0xC00 opaque-asm barrier + mem barrier for store-before-addr schedule)
DEFINE_func_80168D94()  /* dedup: shared engine-core @0x80168D94 (src/shared) */

DEFINE_func_80168EC4()  /* dedup: shared engine-core @0x80168EC4 (src/shared) */

#include "common.h"

extern s32 func_80016A5C();
extern Blk20 D_800AE620;

/* First stack record: sp+0x10 .. sp+0x28 (struct-relative offsets). Mixed widths;
 * offsets 0x06/0x0E/0x13/0x17 are never written (alignment gaps). */

/* Second stack record at sp+0x30. 40 bytes reserved (the frame is 0x60); only the
 * leading 8 words (0x30..0x4C) are populated from D_800AE620 via the Bv view. */

DEFINE_func_80168F40()  /* dedup: shared engine-core @0x80168F40 (src/shared) */

extern DispatchFn D_80189B30[];

s32 func_8016901C(void *a0) {
    return D_80189B30[*(u16 *)((s32)a0 + 2)]();
}

// @class: schedule
// @stuck: none — MATCH (88 ins). $v0/$v1 pins fix the rand-block regalloc; one asm barrier
//         forces addiu (not ori) on the +0xC00 no-bit-overlap add; explicit end-block temps
//         (c=*(s1+2), z=(u16)v10[2]) fix load-order/lhu; a 2nd zero-code asm barrier on v1,v0
//         anchors the v10[0]/v10[1] stores BEFORE the RotMatrixYXZ arg-address setup.

DEFINE_func_80169058()  /* dedup: shared engine-core @0x80169058 (src/shared) */

DEFINE_func_801691B8()  /* dedup: shared engine-core @0x801691B8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80169228);

extern void (*D_80189B38[])(void);

void func_801693CC(void *a0) {
    D_80189B38[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: regalloc-order
// @stuck: none — MATCH (proxy); s2/s1/s0 pins + array-decay reproduce the call-crossing regalloc

DEFINE_func_80169408()  /* dedup: shared engine-core @0x80169408 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (clean structural reconstruction; store-in-delay-slot is the unconditional pre-branch store)

DEFINE_func_8016951C()  /* dedup: shared engine-core @0x8016951C (src/shared) */

// @class: schedule
// @stuck: none — MATCH (s0 pin for param_1+0x38 across calls + memory barrier after the two post-merge sb stores to keep them before the $a0 materialization)

DEFINE_func_80169584()  /* dedup: shared engine-core @0x80169584 (src/shared) */

DEFINE_func_801696D8()  /* dedup: shared engine-core @0x801696D8 (src/shared) */

extern void (*D_80189B40[])(void);

void func_80169830(void *a0) {
    D_80189B40[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8016986C()  /* dedup: shared engine-core @0x8016986C (src/shared) */

#include "common.h"

DEFINE_func_801699D0()  /* dedup: shared engine-core @0x801699D0 (src/shared) */

DEFINE_func_80169A4C()  /* dedup: shared engine-core @0x80169A4C (src/shared) */

extern void (*D_80189BF4[])(void);

void func_80169B80(void *a0) {
    D_80189BF4[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80169BBC);

DEFINE_func_80169E44()  /* dedup: shared engine-core @0x80169E44 (src/shared) */

extern void (*D_80189BFC[])(void);

void func_80169F00(void *a0) {
    D_80189BFC[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: plumbing
// @stuck: none — MATCH (expected; simple straight-line + single branch, one call-crossing local in $s0)

extern void func_800D1FC8(s32 a0, s32 a1);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(void);

extern char D_80189BAC[];
extern char D_80189B6C[];

void func_80169F3C(int param_1)
{
    int iVar1;

    ((int (*)(int, int))func_800D1FC8)(param_1, 6);
    iVar1 = func_800D21C4(param_1, D_80189BAC, 0x16);
    if (iVar1 != 0) {
        *(int *)(param_1 + 0x20) = iVar1;
        *(short *)(iVar1 + 0x1a) = 0x2000;
        *(short *)(iVar1 + 0x18) = 0x2000;
        *(char *)(iVar1 + 0x26) = 0x60;
        *(char *)(iVar1 + 0x25) = 0x60;
        *(char *)(iVar1 + 0x24) = 0x60;
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50000000;
        ((void (*)(int, int, void *))func_80128EA8)(iVar1, param_1 + 0x24, D_80189B6C);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    } else {
        ((void (*)(int))func_80146C3C)(param_1);
    }
}

DEFINE_func_80169FE0()  /* dedup: shared engine-core @0x80169FE0 (src/shared) */

extern void (*D_80189C34[])(void);

void func_8016A020(void *a0) {
    D_80189C34[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016A05C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH

DEFINE_func_8016A08C()  /* dedup: shared engine-core @0x8016A08C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (iVar1 pinned to $v0 via register __asm__("$2") so the global value
//         is reused in $v0 for the subtraction chain instead of cc1 spilling iVar1 to $v1)
DEFINE_func_8016A1CC()  /* dedup: shared engine-core @0x8016A1CC (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (284 ins). Loop-counter biv update: pinned $v0 temp + $0-add opaque copy (i = t + zr) forces the target's 2-insn `addiu v0,s1,1; addu s1,v0,zero` and keeps CSE from rewriting the (s16)t test to read s1.

#include "common.h"



typedef struct { s16 x, y, z, pad; } SVEC_8016A290;

struct Fr_8016A290 {
    SVEC_8016A290 center;                          /* 0x00 -> sp+0x10 */
    SVEC_8016A290 diff;                            /* 0x08 -> sp+0x18 */
    s32  pos[3];                          /* 0x10 -> sp+0x20 */
    s32  _pad1c;                          /* 0x1C -> sp+0x2C */
    s16  mtx[32];                         /* 0x20 -> sp+0x30 */
    SVEC_8016A290 v[4];                            /* 0x60 -> sp+0x70 */
    struct { u8 r, g, b, pad; } col[4];   /* 0x80 -> sp+0x90 */
    u32  code;                            /* 0x90 -> sp+0xA0 */
};

void func_8016A290(s32 param_1, void *param_2, void *param_3) {
    extern u8 D_80189C04;
    extern u8 D_80189C18[];

    struct Fr_8016A290 fr;
    u8 *p;
    s32 i;
    register s32 t __asm__("$2");
    register s32 zr __asm__("$0");
    s32 flags;
    s32 iVar3;

    iVar3 = *(s32 *)(param_1 + 0x34);

    fr.center.x = (*((s16 *)param_2) + *((s16 *)param_3)) >> 1;
    fr.center.y = (((s16 *)param_2)[1] + ((s16 *)param_3)[1]) >> 1;
    fr.center.z = (((s16 *)param_2)[2] + ((s16 *)param_3)[2]) >> 1;
    ((void(*)(s32, void *, void *))func_80149350)(iVar3, &fr.center, &fr.center);

    *(u16 *)(param_1 + 0x6) = *(u16 *)&fr.center.x;
    *(u16 *)(param_1 + 0xA) = *(u16 *)&fr.center.y;
    *(u16 *)(param_1 + 0xE) = *(u16 *)&fr.center.z;
    func_800D20C0(&fr.center, &fr.diff, 8);
    func_80017E68(&fr.center, fr.mtx);

    fr.diff.x = *(u16 *)((s16 *)param_3) - *(u16 *)((s16 *)param_2);
    fr.diff.y = *(u16 *)(((s16 *)param_3) + 1) - *(u16 *)(((s16 *)param_2) + 1);
    fr.diff.z = *(u16 *)(((s16 *)param_3) + 2) - *(u16 *)(((s16 *)param_2) + 2);
    ((void(*)(s32, void *, void *))ApplyMatrixSV)(*(s32 *)(iVar3 + 0x20) + 0x34, &fr.diff, &fr.diff);
    func_800D23D0(&fr.diff);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.pos[0] = D_801269A4 - fr.center.x;
    fr.pos[1] = D_801269A8 - fr.center.y;
    fr.pos[2] = D_801269AC - fr.center.z;
    ApplyTransposeMatrixLV(fr.mtx, fr.pos, fr.pos);
    fr.diff.z = -((s32(*)(s32, s32))ratan2)(fr.pos[0], fr.pos[1]);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.v[3].z = 0;
    fr.v[2].z = 0;
    fr.v[0].z = 0;
    fr.v[1].z = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    flags = D_800B99DA;
    if (flags & 1) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x20;
    } else if (flags & 2) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x40;
    } else {
        fr.col[1].r = *(s32 *)(param_1 + 0x30);
    }

    p = ((u8 *)&D_80189C04);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 3;
    fr.col[1].g = fr.col[1].r >> 3;
    i = 0;
L1:
        fr.v[0].x = (s8)*p++;
        fr.v[0].y = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].y = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].y = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L1;

    fr.v[3].y = 0;
    fr.v[2].y = 0;
    fr.v[0].y = 0;
    fr.v[1].y = 0;
    fr.v[1].x = 0;
    fr.v[1].z = -0x20;
    p = D_80189C18;
    i = 0;
L2:
        fr.v[0].x = (s8)*p++;
        fr.v[0].z = (s8)*p++;
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p--;
        func_80017758(fr.v, fr.mtx);
        if ((s16)i == 1) {
            fr.v[1].z = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + zr;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].x = 0;
    fr.v[0].z = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].x = (s8)*p++;
        fr.v[2].z = (s8)*p++;
        fr.v[3].x = (s8)*p++;
        fr.v[3].z = (s8)*p++;
        func_80017758(fr.v, fr.mtx);
        t = i + 1;
        i = t + zr;
        if ((s16)t < 2) goto L3;
}


extern void (*D_80189C40[])(void);

void func_8016A700(void *a0) {
    D_80189C40[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016A73C);

DEFINE_func_8016A890()  /* dedup: shared engine-core @0x8016A890 (src/shared) */

// @class: struct
// @stuck: none — expect MATCH (single-call leaf, stack-struct prim build + averaging writeback)

extern s32 func_80016A5C();
extern Blk20 D_800AE620;

s32 func_8016A8FC(s32 a0)
{
    Prim p;
    int ptr;

    ptr = *(int *)(a0 + 0x34);

    p.v0 = (short)*(int *)(a0 + 0x4C);
    p.v1 = (short)*(int *)(a0 + 0x50);
    p.v2 = (short)*(int *)(a0 + 0x54);

    p.w0 = *(unsigned short *)(ptr + 6);
    p.w1 = *(unsigned short *)(ptr + 0xA);
    p.w2 = *(unsigned short *)(ptr + 0xE);

    p.v0 = (short)(((int)*(short *)(a0 + 6) + *(int *)(a0 + 0x4C)) >> 1);
    p.v1 = (short)(((int)*(short *)(a0 + 0xA) + *(int *)(a0 + 0x50)) >> 1);
    p.v2 = (short)(((int)*(short *)(a0 + 0xE) + *(int *)(a0 + 0x54)) >> 1);

    *(short *)(a0 + 6) = (short)*(int *)(a0 + 0x4C);
    p.w0 = (short)(((int)*(short *)(a0 + 6) + (int)*(short *)(ptr + 6)) >> 1);
    *(int *)(a0 + 0x4C) = p.w0;

    *(short *)(a0 + 0xA) = (short)*(int *)(a0 + 0x50);
    p.w1 = (short)(((int)*(short *)(a0 + 0xA) + (int)*(short *)(ptr + 0xA)) >> 1);
    *(int *)(a0 + 0x50) = p.w1;

    *(short *)(a0 + 0xE) = (short)*(int *)(a0 + 0x54);
    p.w2 = (short)(((int)*(short *)(a0 + 0xE) + (int)*(short *)(ptr + 0xE)) >> 1);
    *(int *)(a0 + 0x54) = p.w2;

    p.b11 = 0x10;
    p.b15 = 0x80;
    p.b16 = 0x20;
    p.b14 = 0x20;
    p.b12 = 0;
    p.b10 = 0;
    p.w18 = 0x50000000;

    ((s32 (*)(void *, void *))func_80016A5C)(&p, &D_800AE620);
}

// @class: regalloc-order
// @stuck: none — MATCH
#include "common.h"

DEFINE_func_8016AA50()  /* dedup: shared engine-core @0x8016AA50 (src/shared) */

extern void (*D_80189C88[])(void);

void func_8016AB30(void *a0) {
    D_80189C88[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016AB6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016AFB0 (src/shared) */

#include "common.h"

DEFINE_func_8016B114()  /* dedup: shared engine-core @0x8016B114 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016B234);

DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016B3F4 (src/shared) */

DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016B428 (src/shared) */

DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016B448 (src/shared) */

extern void (*D_80189D04[])(void);

void func_8016B4BC(void *a0) {
    D_80189D04[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: struct
// @stuck: none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);
extern int D_801D9A88;

void func_8016B4F8(int param_1)
{
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801D9A88);
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

extern s16 D_80189CF8[];

void func_8016B5C0(s32 param_1) {
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
    psVar5 = D_80189CF8;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016B6BC);

// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);

extern int *D_80189D3C[];
extern unsigned short D_80189D44[];
extern unsigned short D_80189D4C[];
extern unsigned char D_801D9A90[];

int func_8016B834(int param_1, int param_2) {
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801D9A90 + param_2 * 0x40);
    puVar3 = D_80189D3C[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_80189D44[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_80189D4C[param_2];
    }
    return iVar1;
}

DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016B91C (src/shared) */

DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016B964 (src/shared) */

DEFINE_func_8016B984()  /* dedup: shared engine-core @0x8016B984 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)

extern s32 D_801D9A88;
extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801D9A88, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}

DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016BA48 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016BA68);

DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016BADC (src/shared) */

extern void (*D_80189D54[])(void);

void func_8016BBA4(void *a0) {
    D_80189D54[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: plumbing
// @stuck: none — MATCH (56 ins, match_one relocation-masked)




s32 func_8016BBE0(s32 param_1) {
    extern void func_8016BF34(void *a0);
    extern void func_8016BF50(s32);
    extern void func_8001CF00(s32);
    extern M2C_UNK D_801D9BC4;
    extern u8 D_801D9BC5;
    extern u8 D_801D9BC6;
    extern M2C_UNK D_801D9BC8;
    extern u8 D_801D9BC9;
    extern u8 D_801D9BCA;

    int iVar1;
    int temp;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    *(int *)(((int)param_1) + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32))func_8016BF34)(((int)param_1));
        func_8016BF50(((int)param_1));
        func_8001CF00(iVar1);
        *(s16 *)(iVar1 + 0x10) = 0;
        temp = *(int *)(((int)param_1) + 0x2c);
        *(s16 *)(iVar1 + 0x14) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x12) = temp * 0x555;
        *(s16 *)(((int)param_1) + 0x10) = 0;
        *(s16 *)(((int)param_1) + 0x14) = 0;
        (*(u8 *)&D_801D9BC4) = 0x20;
        D_801D9BC5 = 0x20;
        D_801D9BC6 = 0;
        (*(u8 *)&D_801D9BC8) = 0xc0;
        D_801D9BC9 = 0xc0;
        D_801D9BCA = 0;
        *(u16 *)(((int)param_1) + 2) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(((int)param_1));
    }
}


extern void func_80146E90(s32 *a0, s32 a1);
M2C_UNK func_8016BF50();                            /* extern */
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D9BC4;
extern M2C_UNK D_801D9BC8;

void func_8016BCC0(void *arg0) {
    u16 temp_a2;
    u16 temp_v0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x20);
    func_8016BF50();
    temp_a2 = M2C_FIELD(arg0, u16 *, 0x10) + 0x60;
    M2C_FIELD(arg0, u16 *, 0x10) = temp_a2;
    temp_v0 = M2C_FIELD(temp_s0, u16 *, 0x1A) + temp_a2;
    M2C_FIELD(temp_s0, u16 *, 0x1A) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x18) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_s0, u16 *, 0x12) + 0x71) & 0xFFF);
    func_8016BFA8(arg0, &D_801D9BC4, &D_801D9BC8, temp_s0 + 0x18);
    if ((s16) M2C_FIELD(temp_s0, u16 *, 0x1A) >= 0x1001) {
        M2C_FIELD(temp_s0, u16 *, 0x18) = 0x1000U;
        M2C_FIELD(temp_s0, u16 *, 0x1A) = 0x1000U;
        func_80146E90(arg0, M2C_FIELD(arg0, s32 *, 0x30));
        M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1);
    }
}

// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{
    extern u8 D_801D9BC5;
    extern u8 D_801D9BC6;
    extern u8 D_801D9BC9;
    extern u8 D_801D9BCA;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    ((void(*)())func_8016BF50)();

    p1 = &(*(u8 *)&D_801D9BC4);
    if (*p1 != 0) *p1 -= 4;
    if (D_801D9BC5 != 0) D_801D9BC5 -= 4;
    if (D_801D9BC6 != 0) D_801D9BC6 -= 4;
    p2 = &(*(u8 *)&D_801D9BC8);
    if (*p2 != 0) *p2 -= 4;
    if (D_801D9BC9 != 0) D_801D9BC9 -= 4;
    if (D_801D9BCA != 0) D_801D9BCA -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}


// @class: plumbing
// @stuck: none — MATCH

s32 func_8016BEA0(s32 param_1)
{
    int iVar2;
    unsigned short uVar1;

    iVar2 = *(int *)(((int)param_1) + 0x20);
    ((void(*)())func_8016BF50)();
    uVar1 = *(unsigned short *)(((int)param_1) + 0x10) - 0x18;
    *(unsigned short *)(((int)param_1) + 0x10) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = *(unsigned short *)(iVar2 + 0x1a) + uVar1;
    *(unsigned short *)(iVar2 + 0x12) = (*(unsigned short *)(iVar2 + 0x12) + 0x22) & 0xfff;
    ((void (*)(int, void *, void *, int))func_8016BFA8)(((int)param_1), &(*(int *)&D_801D9BC4), &(*(int *)&D_801D9BC8), iVar2 + 0x18);
    if (*(short *)(iVar2 + 0x1a) < 0) {
        ((void (*)(int))func_80146C3C)(((int)param_1));
    }
}


DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016BF34 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016BF50);

extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D9B50;

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_8016BFD0(a0, a1, a2, a3, &D_801D9B50);
}

// @class: struct
// @stuck: none — MATCH (95 ins). Keys: (1) 4-byte unaligned copies via `struct{char b[4];}`
//   assignment -> lwl/lwr/swl/swr with reload; (2) 0x40-byte stack buffer `buf` (Mtx padded to
//   0x40, not 0x20) sets the frame to 0x70 and lands v1/v2 at sp+0x50/0x58; (3) func_80017714(a4)
//   takes param_5 as an arg -> gcc materializes `addu $a0,$s0,$zero` and stores the 4 zeros via $a0.

typedef struct { char b[4]; } W;
typedef struct { s16 x, y, z; } Vec3_8016BFD0;
typedef struct {
    s16 m[9];    /* 0x00 */
    s16 pad;     /* 0x12 */
    s32 t[3];    /* 0x14, 0x18, 0x1c */
    s32 rest[8]; /* 0x20..0x3f */
} Mtx;



void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4) {
    extern void func_80017714();
    extern s32 D_80189D64;
    extern s32 D_80189D6C;
    extern s32 D_80189D74;
    extern s32 D_80189D7C;

    Mtx buf;
    Vec3_8016BFD0 v1;
    Vec3_8016BFD0 v2;
    s32 iVar5 = *(s32 *)(a0 + 0x20);

    *(u32 *)((s32)a4 + 0x30) = 0x50000000;
    *(W *)((s32)a4 + 0x20) = *(W *)a1;
    *(W *)((s32)a4 + 0x24) = *(W *)a1;
    *(W *)((s32)a4 + 0x28) = *(W *)a2;
    *(W *)((s32)a4 + 0x2c) = *(W *)a2;

    v1.x = *(u16 *)(a0 + 6);
    v1.y = *(u16 *)(a0 + 0xa);
    v1.z = *(u16 *)(a0 + 0xe);
    ((void(*)())func_8012EFB8)(&v1, &v1);
    ((void(*)())func_80013F3C)(&buf);
    ((void(*)())func_800123F0)(&buf, (s32)*(s16 *)(iVar5 + 0x12));

    v2.x = *(u16 *)(a3 + 0);
    v2.y = *(u16 *)(a3 + 2);
    v2.z = *(u16 *)(a3 + 4);
    ((void(*)())func_80020F34)(&buf, &v2);

    buf.t[0] = v1.x;
    buf.t[1] = v1.y;
    buf.t[2] = v1.z;
    ((void(*)())func_8012F14C)(&buf, &D_80189D64, (s32)a4);
    ((void(*)())func_8012F14C)(&buf, &D_80189D6C, (s32)a4 + 8);
    ((void(*)())func_8012F14C)(&buf, &D_80189D74, (s32)a4 + 0x10);
    ((void(*)())func_8012F14C)(&buf, &D_80189D7C, (s32)a4 + 0x18);

    *(s16 *)((s32)a4 + 4) = 0;
    *(s16 *)((s32)a4 + 0xc) = 0;
    *(s16 *)((s32)a4 + 0x14) = 0;
    *(s16 *)((s32)a4 + 0x1c) = 0;
    func_80017714(a4);
}


extern void (*D_80189D84[])(void);

void func_8016C14C(void *a0) {
    D_80189D84[*(u16 *)((s32)a0 + 0x2)]();
}

void func_8016C188(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18");
    register u8 *s0 __asm__("$16");
    u16 buf[3];
    s16 *pBCC;
    s16 *pBD4;
    s32 t34;

    extern void func_80015954(s32, s32);
    extern s32 func_8016C374(s32, s32, s32, s32);
    extern void func_80146C3C(void);
    extern void func_8001CD9C(s32, void *);
    extern void func_800233CC(void *, unsigned short);
    extern u8 D_801D9B84[];
    extern s16 D_801D9BCC;
    extern s16 D_801D9BCE;
    extern s16 D_801D9BD0;
    extern s16 D_801D9BD4;
    extern s16 D_801D9BD6;
    extern s16 D_801D9BD8;

    s1 = param;
    s2 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = s2;
    if (s2 != 0) {
        *(u16 *)(s1 + 0x12) = *(u16 *)(s1 + 0x6);
        *(u16 *)(s1 + 0x16) = *(u16 *)(s1 + 0xA);
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0xE);
        t34 = *(s32 *)(s1 + 0x34);
        buf[0] = *(u16 *)(s1 + 0x12);
        buf[1] = *(u16 *)(s1 + 0x16);
        buf[2] = *(u16 *)(s1 + 0x1A);
        ((void (*)(s32, void *, void *))func_80149350)(t34, buf, buf);
        ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
        s0 = D_801D9B84;
        ((void (*)(s32, void *))func_8001CD9C)(s2, s0);
        *(s16 *)(s2 + 0x1E) = 0xCCC;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0x50000000;
        ((void (*)(void *, s32))func_800233CC)(s0, 0x80);
        *(s16 *)(s2 + 0x1A) = 0;
        *(s16 *)(s2 + 0x18) = 0;
        *(s16 *)(s1 + 0x10) = 0;
        pBCC = &D_801D9BCC;
        pBD4 = &D_801D9BD4;
        *pBCC = 0x20;
        D_801D9BCE = 0x20;
        D_801D9BD0 = 0;
        *pBD4 = 0xC0;
        D_801D9BD6 = 0xC0;
        D_801D9BD8 = 0;
        ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, pBCC, pBD4, s0);
        *(u16 *)(s1 + 2) = *(u16 *)(s1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}

// @class: schedule
// @stuck: none — MATCH (44 ins; pins $s0/$s1 + hoist call-arg into a temp so its load fills the buf-store delay slot)

extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);

extern u8 D_801D9BCC[];
extern u8 D_801D9BD4[];
extern u8 D_801D9B84[];

void func_8016C2C4(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s0 __asm__("$16");
    u16 buf[3];
    s16 v;
    s32 r;
    s32 arg;

    s1 = param;
    s0 = *(s32 *)(s1 + 0x20);
    arg = *(s32 *)(s1 + 0x34);
    buf[0] = *(u16 *)(s1 + 0x12);
    buf[1] = *(u16 *)(s1 + 0x16);
    buf[2] = *(u16 *)(s1 + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
    v = *(s16 *)(s1 + 0x10) + 0x10;
    *(s16 *)(s1 + 0x10) = v;
    v = *(s16 *)(s0 + 0x1a) + v;
    *(s16 *)(s0 + 0x1a) = v;
    *(s16 *)(s0 + 0x18) = v;
    r = ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, D_801D9BCC, D_801D9BD4, D_801D9B84);
    if (r == 0) {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}

DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016C374 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (172/172, relocation-masked)



s32 func_8016C49C(s32 param_1_arg) {
    extern s32 VectorNormalSS(void *, void *);
    extern short func_8016CF04(s32, s32);
    extern u8 D_801D9BE0[];
    extern u8 D_801D9CA0;

    register u16 *param_1 __asm__("$17") = ((u16 *)param_1_arg);
    int iVar5;
    int iVar6;
    u16 sv[4];
    s32 mat[8];
    short sVar1;

    iVar5 = *(int *)(param_1 + 0x18);
    iVar6 = *(int *)(param_1 + 0x1a);
    param_1[0x14] = *(u16 *)(iVar5 + 0x36);
    if ((*(u32 *)(param_1 + 0x16) & 0x8000) == 0) {
        short iVar4 = 0;
        u16 *psVar3 = (u16 *)&D_8011D030;
        do {
            if (psVar3 != param_1 && *psVar3 == 0x30) {
                ((void(*)(void *))func_80146C3C)(psVar3);
            }
            iVar4 = iVar4 + 1;
            psVar3 = psVar3 + 0x2c;
        } while (iVar4 < 0x1e);
        D_801D9BE0[1] = 0xff;
        D_801D9BE0[2] = 0x10;
        D_801D9BE0[0] = 0x10;
        D_801D9BE0[6] = 0;
        D_801D9BE0[5] = 0;
        D_801D9BE0[4] = 0;
        ((void(*)(void *, s32))func_800233CC)(D_801D9BE0, 10);
        sv[0] = *(u16 *)(iVar5 + 6) - *(u16 *)(iVar6 + 6);
        {
            int t = *(u16 *)(iVar6 + 0xa) + 0x28;
            sv[1] = *(u16 *)(iVar5 + 0xa) - t;
        }
        sv[2] = *(u16 *)(iVar5 + 0xe) - *(u16 *)(iVar6 + 0xe);
        VectorNormalSS(sv, sv);
        param_1[3] = *(u16 *)(iVar5 + 6) + ((s16)sv[0] >> 9);
        param_1[5] = *(u16 *)(iVar5 + 0xa) + (((s16)sv[1] >> 9) - 0x28);
        param_1[7] = *(u16 *)(iVar5 + 0xe) + ((s16)sv[2] >> 9);
        ((void(*)(void *))func_800D23D0)(sv);
        sv[0] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, param_1 + 0x1c);
        ((void(*)(void *, s32))func_80016714)(&D_801D9CA0, 0x620);
        ((s32(*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x32, param_1, 0, 0, 0, 0, *(int *)(param_1 + 0x18));
        sVar1 = 5;
    } else {
        int iVar5b = ((s32(*)())func_801465C0)();
        u32 uVar2;
        if (iVar5b == 0) {
            return;
        }
        ((void(*)(s32, void *))func_8001CD9C)(iVar5b, D_801D9BE0);
        *(u32 *)(iVar5b + 4) |= 0x50000000;
        uVar2 = rand();
        sv[0] = (uVar2 & 0x7f) * 8 - 0x80;
        sv[1] = ((uVar2 & 0x7f00) >> 4) - 0x400;
        sv[2] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, mat);
        ((void(*)(void *, void *))func_80048EAC)(param_1 + 0x1c, mat);
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0xb;
        ((void(*)(void *, void *, void *))ApplyMatrixSV)(mat, sv, sv);
        param_1[9] = sv[0];
        param_1[0xb] = sv[1];
        param_1[0xd] = sv[2];
        *(int *)(param_1 + 0x10) = iVar5b;
        *(int *)(param_1 + 0xe) = 8;
        func_8016CF04((s32)param_1, 0);
        *(int *)(param_1 + 0x16) = 0;
        sVar1 = param_1[1] + 1;
    }
    param_1[1] = sVar1;
}


DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016C74C (src/shared) */

#include "common.h"

DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016C83C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016C998);

// @class: struct
// @stuck: none — MATCH (byte-matched sibling idiom func_80131EEC, table-dispatch via jalr)
#include "common.h"

extern void (*D_80189D8C[])(void);

void func_8016CB84(void *a0) {
    D_80189D8C[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016CBC0);

/* func_8016CF04 returns short (case 2: 1 if the decremented f2 hit 0, else 0; all other
 * paths return 0 via the addu $v0,$zero,$zero at 0x8016D154). The TU/engine_core.h declare
 * it `void` in 4 DEFINE_ macros + one block-scope decl in func_8016C49C; the real apply is the
 * byte-neutral engine_core.h void->short flip (every caller discards or ptr-casts the return,
 * cf. func_8016D5EC's `(s16)(...)` cast). The //@EDIT lines above are the rtu_match proxy for
 * that flip. Body verified 166/166 in isolation AND in a whole-TU compile w/ the reconciled hdr. */
typedef struct {
    u8 f0, f1, f2, f3;
    struct { s16 a, b, c, d, e, g; } ent[16];
} Blk_8016CF04;                /* 4 + 16*12 = 0xC4 stride */

short func_8016CF04(s32 param_1, s32 param_2) {
    extern Blk_8016CF04 D_801D9CA0[];

    Blk_8016CF04 *p = &D_801D9CA0[*(short *)(((int)param_1) + 0x2a)];
    u16 rot[4];
    u16 out[4];
    s32 mtx[8];

    switch (((short)param_2)) {
    case 0:
        p->f2 = 0;
        p->f1 = 0;
        p->f3 = 0xf0;
        break;
    case 1:
        p->f1 = p->f1 + 1;
        if ((u8)p->f1 >= 0x10)
            p->f1 = 0;
        if ((u8)p->f2 < 0xf)
            p->f2 = p->f2 + 1;
        break;
    case 2: {
        u8 c = p->f2 - 1;
        p->f2 = c;
        if (c == 0) {
            p->f0 = 0;
            return 1;
        }
        p->f3 = p->f3 - 0xf;
        return 0;
    }
    }

    rot[0] = *(s32 *)(((int)param_1) + 0x10) >> 12;
    rot[1] = *(s32 *)(((int)param_1) + 0x14) >> 12;
    rot[2] = *(s32 *)(((int)param_1) + 0x18) >> 12;
    func_800D23D0(rot);
    RotMatrixYXZ(rot, mtx);
    rot[0] = 9;
    rot[1] = 0;
    rot[2] = 0;
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].a = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].b = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].c = *(u16 *)(((int)param_1) + 0xe) + out[2];
    rot[0] = -rot[0];
    rot[1] = -rot[1];
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].d = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].e = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].g = *(u16 *)(((int)param_1) + 0xe) + out[2];
    return 0;
}

extern void (*D_80189DA8[])(void);

void func_8016D19C(void *a0) {
    D_80189DA8[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016D1D8);

extern void (*D_80189DB0[])(void);

void func_8016D428(void *a0) {
    D_80189DB0[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016D464 (src/shared) */

DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016D4DC (src/shared) */

/* func_8016D5EC — bias two u16s (-0x60) in the sub-record at *(a0+0x20), then
 * func_8016CF04(a0, 2); if its (short) return is nonzero, func_80146C3C(a0).
 * func_8016CF04 canonically void in the TU but the .s reads v0 (sll16;beqz) — call via
 * a short-returning ptr cast. func_80146C3C is (void); a0 passed via ptr-cast. */

DEFINE_func_8016D5EC()  /* dedup: shared engine-core @0x8016D5EC (src/shared) */

// @class: other
// @stuck: none — MATCH (expected): short-return truthiness via sll16+bnez, param saved in $s0 across call
DEFINE_func_8016D64C()  /* dedup: shared engine-core @0x8016D64C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016D688);

DEFINE_func_8016D778()  /* dedup: shared engine-core @0x8016D778 (src/shared) */

DEFINE_func_8016D848()  /* dedup: shared engine-core @0x8016D848 (src/shared) */

DEFINE_func_8016D984()  /* dedup: shared engine-core @0x8016D984 (src/shared) */

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016DA04 (src/shared) */

// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);
extern void (*D_80189E18[])(int);

void func_8016DA30(int param_1)
{
    ((void (*)(void))func_8016DBD8)();
    D_80189E18[*(unsigned short *)(param_1 + 2)](param_1);
}

// @class: plumbing
// @stuck: none — MATCH (clean if/else, one call-crossing local; bnez polarity = if(iVar1==0) fall-through)

extern void func_801465C0(void);
extern void func_80146C3C(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

extern u8 D_80189DBC;
extern u8 D_80189DC8;

void func_8016DA7C(s32 param_1)
{
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        *(s32 *)(param_1 + 0x20) = iVar1;
        ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_80189DBC, 0x250, 0x100);
        *(u8 *)(iVar1 + 0x27) = 0x90;
        *(u16 *)(iVar1 + 0x18) = 0x3000;
        *(u16 *)(iVar1 + 0x1a) = 0x4000;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        func_80128EA8(iVar1, param_1 + 0x24, (s32)&D_80189DC8);
        *(s32 *)(param_1 + 0x10) = 0;
        *(s32 *)(param_1 + 0x14) = 0xfff40000;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}

// @class: loop-guard
// @stuck: none — MATCH (branch-polarity invert §3-T4: call on fall-through, block in else)

DEFINE_func_8016DB34()  /* dedup: shared engine-core @0x8016DB34 (src/shared) */

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016DBD8 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (161 ins, relocation-masked). Keys: (1) mirror sibling func_8017BEF8 coord-transform idiom (16-byte Work struct {in x,y,z,xpad @0x20; out vx,vy,vz,vpad @0x28} -> frame 0x48, in@sp+0x20/out@sp+0x28); (2) SHORT loop counter i shared across all 3 loops defeats shift-IV strength reduction; (3) loop-2 = check-first/increment-after (like loop-1) keeps search key 0x11 in $a0 (reused as the func_80146A6C a0 arg) instead of spilling to $a1; (4) place loop-3 counter reset i=0 AFTER func_800D23D0 (not before func_80146A6C(0x11)) so it schedules as $s1-reset last, not first; (5) inverted final branch (if r!=0 {loops} else fall to ddb0/func_80146C3C) matches beqz; node-alloc block mirrors sibling func_8016DA7C.
#include "common.h"

typedef struct {
    u16 x, y, z, xpad;      /* 0x00 : in  -> sp+0x20 */
    u16 vx, vy, vz, vpad;   /* 0x08 : out -> sp+0x28 */
} Work8016;

extern s32  D_8011D030;
extern s16  D_801DA2C0;
extern s16  D_801DA2C4;
extern s32  D_80189E20;
extern s32  D_80189E2C;
s32 func_8016DC20(s32 param_1) {
    u16 *p;
    short i;
    s32 obj;
    s32 r;
    s32 node;
    s32 e;
    Work8016 w;

    i = 0;
    p = (u16 *)&D_8011D030;
    obj = *(s32 *)(param_1 + 0x34);
    do {
        if ((p != (u16 *)param_1) && (*p == 0x34)) goto done;
        i = i + 1;
        p += 0x2c;
    } while (i < 0x1e);

    func_80149374(obj, param_1 + 4);
    r = func_801619D0((void *)obj);
    i = 0;
    if (r != 0) {
        p = (u16 *)&D_8011D030;
        do {
            if (*p == 0x11) goto ddb0;
            i = i + 1;
            p += 0x2c;
        } while (i < 0x1e);

        func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                      (s16)(*(u16 *)(param_1 + 0xA) - 8),
                      *(s16 *)(param_1 + 0xE), 0, 0);
        w.x = *(u16 *)(param_1 + 6);
        w.y = *(u16 *)(param_1 + 0xA);
        w.z = *(u16 *)(param_1 + 0xE);
        func_800D20C0(&w.x, &w.vx, 0);
        w.vy = 0;
        func_800D23D0(&w.vx);
        i = 0;
        do {
            e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                              *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE),
                              i, 0);
            if (e != 0) {
                *(s16 *)(e + 0x12) = w.vx;
                *(s16 *)(e + 0x16) = w.vy;
                *(s16 *)(e + 0x1A) = 0;
            }
            i = i + 2;
        } while (i < 3);
        goto done;
    }
ddb0:
    if (((D_801DA2C0 != *(s16 *)(obj + 6)) || (D_801DA2C4 != *(s16 *)(obj + 0xE)))
        && (node = func_800D21C4(param_1, &D_80189E20, 0x18), node != 0)) {
        D_801DA2C0 = *(u16 *)(obj + 6);
        D_801DA2C4 = *(u16 *)(obj + 0xE);
        func_800D1FC8(param_1, 7);
        *(s32 *)(param_1 + 0x20) = node;
        *(u16 *)(node + 0x1A) = 0x3000;
        *(u16 *)(node + 0x18) = 0x3000;
        *(u8 *)(node + 0x26) = 0xFF;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x50000000;
        func_80128EA8(node, param_1 + 0x24, (s32)&D_80189E2C);
        func_80128ED8(node, param_1 + 0x24);
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        return;
    }
done:
    ((void (*)(s32))func_80146C3C)(param_1);
}


extern void (*D_80189E4C[])(void);

void func_8016DEA4(void *a0) {
    D_80189E4C[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8016DEE0()  /* dedup: shared engine-core @0x8016DEE0 (src/shared) */

extern void (*D_80189E54[])(void);

void func_8016DF20(void *a0) {
    D_80189E54[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: regalloc-order
// @stuck: none — MATCH (156 ins). Split iVar8 live-range (top-load->else $s3, func_801465C0
//   result pinned $s1 for the then-branch, reusing the dead loop counter). sVar1 merge-phi
//   wanted $v0: a scheduling barrier before `sVar1=4` stops the constant hoisting into the
//   param_1[7] load-delay slot (fixes the count/nop), and pinning the then-branch 0x10 temp
//   to $v1 frees $v0 so the param_1[1]+1 load coalesces into the phi ($v0) in both branches.
//   Blk20_8016DF5C struct copies ((*(Blk20_8016DF5C*)&D_800AE620)->localMatrix 3/3 grouping; iVar8+0x38->param_1+0x38 4/4).
#include "common.h"

typedef struct { s32 w[8]; } Blk20_8016DF5C;



void func_8016DF5C(s32 param_1)
{
    extern void func_8016E3CC(void *a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern u8 D_801DA2C8;
    extern u8 D_801DA2C9;
    extern u8 D_801DA2CA;
    extern u8 D_801DA2CC;
    extern u8 D_801DA2CD;
    extern u8 D_801DA2CE;

    s32 iVar8;
    short sVar1;

    iVar8 = *(s32 *)((u8 *)((void *)param_1) + 0x34);
    if ((*(u32 *)((u8 *)((void *)param_1) + 0x2c) & 0x8000) == 0) {
        unsigned short uVar7 = 0;
        u16 *psVar6 = (u16 *)&D_8011D030;
        register s32 iNew __asm__("$17");
        s32 base;
        do {
            if (psVar6 != (u16 *)((void *)param_1) && (*psVar6 == 0x41 || *psVar6 == 0x48)) {
                ((void (*)(void *))func_80146C3C)(psVar6);
            }
            uVar7++;
            psVar6 += 0x2c;
        } while (uVar7 < 0x1e);
        iNew = ((s32(*)())func_801465C0)();
        if (iNew == 0) {
            return;
        }
        base = (s32)&D_801DA2C8;
        D_801DA2CA = 0xc0;
        *(u8 *)base = 0xc0;
        D_801DA2C9 = 0;
        D_801DA2CE = 0;
        D_801DA2CD = 0;
        D_801DA2CC = 0;
        ((void(*)(void *, unsigned short))func_800233CC)((void *)base, 0x40);
        func_8001CD50(iNew, base);
        *(s32 *)(iNew + 0x34) = (s32)((u8 *)((void *)param_1) + 0x38);
        *(s16 *)(iNew + 0x1a) = 0;
        *(s16 *)(iNew + 0x18) = 0;
        *(u32 *)(iNew + 4) = *(u32 *)(iNew + 4) | 0x50000000;
        func_8016E3CC(((void *)param_1));
        {
            register s32 t10 __asm__("$3");
            t10 = 0x10;
            *(s32 *)((u8 *)((void *)param_1) + 0x20) = iNew;
            *(s32 *)((u8 *)((void *)param_1) + 0x1c) = t10;
        }
        sVar1 = *(u16 *)((u8 *)((void *)param_1) + 2) + 1;
    } else {
        short asStack_60[20];
        Blk20_8016DF5C localMatrix;
        s32 uVar2;

        asStack_60[0] = 0;
        asStack_60[1] = 0;
        asStack_60[2] = 0x20;
        localMatrix = (*(Blk20_8016DF5C*)&D_800AE620);
        uVar2 = ((s32(*)())rand)();
        RotMatrixY((uVar2 & 0x7f00) >> 3, &localMatrix);
        ApplyMatrixSV(&localMatrix, asStack_60, asStack_60);
        *(s16 *)((u8 *)((void *)param_1) + 6) = D_80126B5E + asStack_60[0];
        *(s16 *)((u8 *)((void *)param_1) + 0xa) = D_80126B62 - ((u16)uVar2 & 0x3f);
        *(s16 *)((u8 *)((void *)param_1) + 0xe) = D_80126B66 + asStack_60[2];
        *(Blk20_8016DF5C *)((u8 *)((void *)param_1) + 0x38) = *(Blk20_8016DF5C *)((u8 *)iVar8 + 0x38);
        *(s32 *)((u8 *)((void *)param_1) + 0x2c) = 0x1000;
        *(s32 *)((u8 *)((void *)param_1) + 0x30) = 0xff;
        *(s32 *)((u8 *)((void *)param_1) + 0x1c) = 0x10;
        __asm__ __volatile__("" ::: "memory");
        sVar1 = 4;
    }
    *(s16 *)((u8 *)((void *)param_1) + 2) = sVar1;
}

DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016E1CC (src/shared) */

DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016E26C (src/shared) */

DEFINE_func_8016E2E8()  /* dedup: shared engine-core @0x8016E2E8 (src/shared) */

DEFINE_func_8016E358()  /* dedup: shared engine-core @0x8016E358 (src/shared) */

DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016E3CC (src/shared) */

DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016E460 (src/shared) */

extern void (*D_80189EA8[])(void);

void func_8016E5B8(void *a0) {
    D_80189EA8[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8016E5F4()  /* dedup: shared engine-core @0x8016E5F4 (src/shared) */

extern void func_8016E778();

void func_8016E688(void *a0) {
    u16 *p = (u16 *)a0;
    s16 v;
    p[0x10/2] += 0x200;
    v = p[0x12/2] + p[0x10/2];
    p[0x12/2] = v;
    if (v >= 0x3000) {
        *(s32 *)((u8 *)a0 + 0x1C) = 4;
        *(s16 *)((u8 *)a0 + 0x2) += 1;
    }
    func_8016E778();
}

DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016E6E4 (src/shared) */

DEFINE_func_8016E728()  /* dedup: shared engine-core @0x8016E728 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (build-word spread + 3-halfword buffer, two stack addrs passed)

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016E778 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (74 ins); register pin $s2 forces &prim into a saved reg (§17)

typedef struct { short vx, vy, vz, pad; } SVECTOR;                 /* 0x08 */
typedef struct { short m[3][3]; short pad; s32 t[3]; } MATRIX;     /* 0x20 */

typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;


void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern void func_80016ED4(void *a0);
    extern SVECTOR D_80189E68[4];
    extern s32 D_80189E88;
    extern s32 D_80189E90;
    extern s32 D_80189E98;
    extern s32 D_80189EA0;

    Prim_8016E7C8 prim;
    MATRIX m;
    SVECTOR tmp;
    register Prim_8016E7C8 *pp __asm__("$18");   /* $s2 — force &prim into a saved reg */

    ((void (*)(void *, void *))func_80017DC4)(param_2, &m);
    m.t[0] = *(short *)(param_1 + 6);
    m.t[1] = *(short *)(param_1 + 10);
    m.t[2] = *(short *)(param_1 + 14);
    func_8004914C(&m);
    func_800491AC(&m);
    pp = &prim;
    RotTransSV(&D_80189E68[0], pp, &tmp);
    RotTransSV(&D_80189E68[1], &prim.v[1], &tmp);
    RotTransSV(&D_80189E68[2], &prim.v[2], &tmp);
    RotTransSV(&D_80189E68[3], &prim.v[3], &tmp);
    prim.v[0].vz = 3;
    prim.f5 = 0x50000000;
    prim.f0 = D_80189E88;
    prim.f1 = D_80189E90;
    prim.f2 = D_80189E98;
    prim.f3 = D_80189EA0;
    prim.f4 = *param_3;
    prim.f6 = 0x27;
    func_80016ED4(pp);
}


DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016E8F0 (src/shared) */

#include "common.h"

DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016E918 (src/shared) */

// @class: struct
// @stuck: none — MATCH (36/36 ins, match_one relocation-masked)


struct Entry {
    u8 f0;
    u8 f1;
    u8 pad[0x1e];
};

typedef void (*Handler)(struct Entry *);


s32 func_8016E95C() {
    extern Handler D_80189EE8[];

    struct Entry *p;
    for (p = ((struct Entry *)&D_80115218); p < &((struct Entry *)&D_80115218)[4]; p++) {
        if (p->f0 != 0) {
            D_80189EE8[p->f1](p);
        }
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016E9EC);

// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern u16 D_80189EDC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_80189EDC[param_1->f2];
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

extern u8 D_80189ECC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_80189ECC[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}

// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_80189EDC[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.

extern u16 D_80189EDC[];

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_80189EDC[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016EC0C);

DEFINE_func_8016ED6C()  /* dedup: shared engine-core @0x8016ED6C (src/shared) */

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ED8C (src/shared) */

DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016EDBC (src/shared) */

DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016EDEC (src/shared) */

DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016EE40 (src/shared) */

DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016EE94 (src/shared) */

DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016EF78 (src/shared) */

DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016EFA8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016EFC8);

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016F094 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH

s32 func_8016F0AC()
{
    extern void func_8016F0E4(void);

    ((void (*)(void *))func_8016F0E4)(&D_80126B58);
    ((void (*)(void *))func_80165770)(&D_80126B58);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8016F0E4);

/* func_8016F14C — read a packed fn-ptr+flags word at a0+0x1F8; mask off the high byte
 * (0x80FFFFFF) to recover the fn ptr (computed BEFORE the null check so gcc hoists the
 * lui+ori into the load-delay slot — load-bearing); if the word is nonzero, optionally
 * func_80148634(a0) when bit24 is set, then call the recovered fn ptr with a0. */

DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016F14C (src/shared) */

DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016F1AC (src/shared) */

// @class: schedule
// @stuck: none — MATCH

extern s32 D_80189EF8;
extern s32 D_80126B58;
extern s16 currentLocationId;

s32 func_8016F1C4(void) {
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_80189EF8;
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

DEFINE_func_8016F250()  /* dedup: shared engine-core @0x8016F250 (src/shared) */

DEFINE_func_8016F264()  /* dedup: shared engine-core @0x8016F264 (src/shared) */

DEFINE_func_8016F288()  /* dedup: shared engine-core @0x8016F288 (src/shared) */

DEFINE_func_8016F2A8()  /* dedup: shared engine-core @0x8016F2A8 (src/shared) */

DEFINE_func_8016F2C8()  /* dedup: shared engine-core @0x8016F2C8 (src/shared) */

DEFINE_func_8016F2EC()  /* dedup: shared engine-core @0x8016F2EC (src/shared) */

DEFINE_func_8016F30C()  /* dedup: shared engine-core @0x8016F30C (src/shared) */

DEFINE_func_8016F330()  /* dedup: shared engine-core @0x8016F330 (src/shared) */

DEFINE_func_8016F350()  /* dedup: shared engine-core @0x8016F350 (src/shared) */

DEFINE_func_8016F374()  /* dedup: shared engine-core @0x8016F374 (src/shared) */

DEFINE_func_8016F388()  /* dedup: shared engine-core @0x8016F388 (src/shared) */

DEFINE_func_8016F398()  /* dedup: shared engine-core @0x8016F398 (src/shared) */

DEFINE_func_8016F410()  /* dedup: shared engine-core @0x8016F410 (src/shared) */

DEFINE_func_8016F44C()  /* dedup: shared engine-core @0x8016F44C (src/shared) */

DEFINE_func_8016F470()  /* dedup: shared engine-core @0x8016F470 (src/shared) */

DEFINE_func_8016F494()  /* dedup: shared engine-core @0x8016F494 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected (param crosses first call into $s0, passed to 2nd callee)

DEFINE_func_8016F4C4()  /* dedup: shared engine-core @0x8016F4C4 (src/shared) */

DEFINE_func_8016F4F4()  /* dedup: shared engine-core @0x8016F4F4 (src/shared) */

DEFINE_func_8016F4FC()  /* dedup: shared engine-core @0x8016F4FC (src/shared) */

struct S;
DEFINE_func_8016F540()  /* dedup: shared engine-core @0x8016F540 (src/shared) */

DEFINE_func_8016F578()  /* dedup: shared engine-core @0x8016F578 (src/shared) */

DEFINE_func_8016F5B0()  /* dedup: shared engine-core @0x8016F5B0 (src/shared) */

DEFINE_func_8016F5E0()  /* dedup: shared engine-core @0x8016F5E0 (src/shared) */

DEFINE_func_8016F610()  /* dedup: shared engine-core @0x8016F610 (src/shared) */

DEFINE_func_8016F648()  /* dedup: shared engine-core @0x8016F648 (src/shared) */

DEFINE_func_8016F680()  /* dedup: shared engine-core @0x8016F680 (src/shared) */

DEFINE_func_8016F6B0()  /* dedup: shared engine-core @0x8016F6B0 (src/shared) */

extern void (*D_80189F70[])(void);

void func_8016F6E0(void *a0) {
    D_80189F70[*(u8 *)((s32)a0 + 0x216)]();
}

DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016F71C (src/shared) */

DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016F764 (src/shared) */

extern void (*D_80189F78[])(void);

void func_8016F798(void *a0) {
    D_80189F78[*(u8 *)((s32)a0 + 0x216)]();
}

DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016F7D4 (src/shared) */

DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016F804 (src/shared) */

extern void (*D_80189F80[])(void);

void func_8016F834(void *a0) {
    D_80189F80[*(u8 *)((s32)a0 + 0x216)]();
}

DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016F870 (src/shared) */

DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016F8AC (src/shared) */

extern void (*D_80189F88[])(void);

void func_8016F8E4(void *a0) {
    D_80189F88[*(u8 *)((s32)a0 + 0x216)]();
}

DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016F920 (src/shared) */

extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern void func_80171928(void *a0);
extern u16 D_8011F73E;

void func_8016F95C(void *a0) {
    u16 *p = &D_8011F73E;
    u16 v = *p;
    s32 r;

    if (v == 0) {
        r = func_80171CC4(a0, p - 3);
    } else {
        r = func_80171D1C(a0, p - 3, v & 0xFF);
    }
    if (r != 0) {
        func_80171928(a0);
    }
}

extern void (*D_80189F90[])(void);

void func_8016F9C4(void *a0) {
    D_80189F90[*(u8 *)((s32)a0 + 0x216)]();
}

DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016FA00 (src/shared) */

DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016FA44 (src/shared) */

extern void (*D_80189F98[])(void);

void func_8016FA84(void *a0) {
    D_80189F98[*(u8 *)((s32)a0 + 0x216)]();
}

DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016FAC0 (src/shared) */

DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016FB10 (src/shared) */

DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016FB50 (src/shared) */

extern void (*D_80189FA4[])(void);

void func_8016FB7C(void *a0) {
    D_80189FA4[*(u8 *)((s32)a0 + 0x216)]();
}

DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016FBB8 (src/shared) */

DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016FC24 (src/shared) */

DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016FC64 (src/shared) */

extern void (*D_80189FB0[])(void);

void func_8016FC90(u8 *a0)
{
    D_80189FB0[a0[0x216]]();
}

DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016FCCC (src/shared) */

DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016FD08 (src/shared) */

DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016FD7C (src/shared) */

extern void (*D_80189FBC[])(void);

void func_8016FDB4(u8 *a0)
{
    D_80189FBC[a0[0x216]]();
}

DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016FDF0 (src/shared) */

DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016FE2C (src/shared) */

DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016FE78 (src/shared) */

/* func_8016FED0 — if func_80172664(a0) is true, OR-in 0x40 to the u16 at a0+0xAA;
 * then func_80171CC4(a0, &D_8011F738); on its hit, func_80171928(a0). */

DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016FED0 (src/shared) */

extern void (*D_80189FCC[])(void);

void func_8016FF30(u8 *a0)
{
    D_80189FCC[a0[0x216]]();
}

DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016FF6C (src/shared) */

DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016FFA8 (src/shared) */

extern void (*D_80189FDC[])(void);

void func_8016FFDC(u8 *a0)
{
    D_80189FDC[a0[0x216]]();
}

DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */

DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */

DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700B8 (src/shared) */

DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */

extern void (*D_80189FE4[])(void);

void func_80170150(u8 *a0)
{
    D_80189FE4[a0[0x216]]();
}

DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018C (src/shared) */

DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701C8 (src/shared) */

extern void (*D_80189FEC[])(void);

void func_80170240(u8 *a0)
{
    D_80189FEC[a0[0x216]]();
}

DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027C (src/shared) */

DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702B8 (src/shared) */

extern void (*D_80189FF4[])(void);

void func_801702FC(u8 *a0)
{
    D_80189FF4[a0[0x216]]();
}

DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */

DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */

extern void (*D_80189FFC[])(void);

void func_801703E0(u8 *a0)
{
    D_80189FFC[a0[0x216]]();
}

DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041C (src/shared) */

DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044C (src/shared) */

extern void (*D_8018A004[])(void);

void func_801704B0(u8 *a0)
{
    D_8018A004[a0[0x216]]();
}

DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704EC (src/shared) */

DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051C (src/shared) */

extern void (*D_8018A00C[])(void);

void func_80170548(u8 *a0)
{
    D_8018A00C[a0[0x216]]();
}

DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */

DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705C0 (src/shared) */

extern void (*D_8018A014[])(void);

void func_801705F8(u8 *a0)
{
    D_8018A014[a0[0x216]]();
}

DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */

DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */

extern void (*D_8018A01C[])(void);

void func_801706AC(u8 *a0)
{
    D_8018A01C[a0[0x216]]();
}

DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706E8 (src/shared) */

extern void func_80129FF4(void);
extern void func_80171928(void *a0);

void func_80170718(void *a0) {
    func_80129FF4();
    func_80171928(a0);
}

extern void (*D_8018A024[])(void *);

void func_80170748(void *a0) {
    D_8018A024[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */

DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707D4 (src/shared) */

extern void (*D_8018A02C[])(void *);

void func_80170810(void *a0) {
    D_8018A02C[*(u8 *)((s32)a0 + 0x216)](a0);
}

extern void func_801719A4(int a0, int a1);
extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern s32 func_80171990(u8 *a0);
extern void func_801708B0(void *a0);
extern u8 D_800D5DA8;

void func_8017084C(s32 a0) {
    func_801719A4(a0, 1);
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_800D5DA8);
    func_8016BADC((void *)a0, -0x40, 0x40);
    func_80171990((u8 *)a0);
    func_801708B0((void *)a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801708B0);

DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */

DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */

DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709B8 (src/shared) */

DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170A00 (src/shared) */

DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170A48 (src/shared) */

DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170A90 (src/shared) */

extern void (*D_8018A034[])(void *);

void func_80170AD8(void *a0) {
    D_8018A034[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170B14 (src/shared) */

extern void *D_8011F738;
void func_8014706C(void *a0);
void func_80154274(s32 *a0, s32 a1);
s32 func_80171990(u8 *a0);
void func_80170B90(u8 *a0);

DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170B48 (src/shared) */

DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170B90 (src/shared) */

extern void (*D_8018A03C[])(void *);

void func_80170BD8(void *a0) {
    D_8018A03C[*(u8 *)((s32)a0 + 0x216)](a0);
}

extern s32 func_80171990(u8 *a0);
extern void func_80170C44(u8 *a0);

void func_80170C14(u8 *a0) {
    func_80171990(a0);
    func_80170C44(a0);
}

DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170C44 (src/shared) */

extern void (*D_8018A044[])(void *);

void func_80170C74(void *a0) {
    D_8018A044[*(u8 *)((s32)a0 + 0x215)](a0);
}

DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170CB0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80170CF0);

extern void (*D_8018A04C[])(void *);

void func_80170D68(void *a0) {
    D_8018A04C[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170DA4 (src/shared) */

// @class: plumbing
// @stuck: none — expecting MATCH (u8 mask via andi 0xFF, if/else picks data extern)

DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170DE0 (src/shared) */

extern void (*D_8018A054[])(void *);

void func_80170E34(void *a0) {
    D_8018A054[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170E70 (src/shared) */

DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170EAC (src/shared) */

extern void (*D_8018A05C[])(void *);

void func_80170EFC(void *a0) {
    D_8018A05C[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170F38 (src/shared) */

DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170F74 (src/shared) */

extern void (*D_8018A064[])(void *);

void func_80170FB0(void *a0) {
    D_8018A064[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170FEC (src/shared) */

DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */

extern void (*D_8018A06C[])(void *);

void func_80171064(void *a0) {
    D_8018A06C[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710A0 (src/shared) */

DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710DC (src/shared) */

extern void (*D_8018A074[])(void *);

void func_80171120(void *a0) {
    D_8018A074[*(u8 *)((s32)a0 + 0x216)](a0);
}

extern s32 func_80171990(u8 *a0);
extern void func_8017118C(u8 *a0);

void func_8017115C(u8 *a0) {
    func_80171990(a0);
    func_8017118C(a0);
}

DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118C (src/shared) */

extern void (*D_8018A07C[])(void *);

void func_801711C0(void *a0) {
    D_8018A07C[*(u8 *)((s32)a0 + 0x216)](a0);
}

#include "common.h"

void func_801719A4(int a0, int a1);
s32 func_80171990(u8 *a0);
DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711FC (src/shared) */

DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */

extern s32 (*D_8018A084[])(void *);

s32 func_80171260(void *a0) {
    return D_8018A084[*(u8 *)((s32)a0 + 0x216)](a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017129C);

DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */

extern s32 (*D_8018A08C[])(void *);

s32 func_801714E4(void *a0) {
    return D_8018A08C[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */

DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162C (src/shared) */

// @class: schedule
// @stuck: none — MATCH
#include "common.h"

DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716AC (src/shared) */

DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717A0 (src/shared) */

extern void func_8013E588(void *a0);
extern void func_80171928(void *a0);

void func_801717F4(void *a0) {
    func_8013E588(a0);
    func_80171928(a0);
}

extern void func_80175414(s32);
extern void func_80171928(void *a0);

void func_80171824(void *a0) {
    func_80175414((s32)a0);
    func_80171928(a0);
}

extern void func_80175454(void);
extern void func_80171928(void *a0);

void func_80171854(void *a0) {
    func_80175454();
    func_80171928(a0);
}

DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801718AC);

DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */

// @class: struct
// @stuck: none — MATCH (expected); simple field accesses + tail call passing a0 unchanged

DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */

DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196C (src/shared) */

DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197C (src/shared) */

DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801719A4);

DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171A04 (src/shared) */

DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171A10 (src/shared) */

DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171A1C (src/shared) */

DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171A34 (src/shared) */

DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171A44 (src/shared) */

DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171A58 (src/shared) */

DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171A6C (src/shared) */

DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171A80 (src/shared) */

DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171A88 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (clean structural reconstruction; param_1 in $s0, both calls sign-extend their $v0 to s16)

DEFINE_func_80171AB0()  /* dedup: shared engine-core @0x80171AB0 (src/shared) */

DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171B10 (src/shared) */

DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171B44 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80171B4C);

// @class: regalloc-order
// @stuck: none — MATCH (param pins $s1/$s0 reversed; s32 param_2 keeps the & 0xFF as a separate andi, I2)

DEFINE_func_80171C64()  /* dedup: shared engine-core @0x80171C64 (src/shared) */

DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171CC4 (src/shared) */

DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171D1C (src/shared) */

DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171D78 (src/shared) */

DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171E08 (src/shared) */

DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171EC8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80171FFC);

extern s32 func_8017248C(s32 a0, s32 a1);
extern void func_80146D90(s32 a0);
extern s32  ratan2(s32 a0, s32 a1);   /* ratan2 */
DEFINE_func_8017209C()  /* dedup: shared engine-core @0x8017209C (src/shared) */

DEFINE_func_80172170()  /* dedup: shared engine-core @0x80172170 (src/shared) */

DEFINE_func_801722CC()  /* dedup: shared engine-core @0x801722CC (src/shared) */

DEFINE_func_80172304()  /* dedup: shared engine-core @0x80172304 (src/shared) */

DEFINE_func_80172310()  /* dedup: shared engine-core @0x80172310 (src/shared) */

DEFINE_func_80172358()  /* dedup: shared engine-core @0x80172358 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (simple stub: 3 calls, 1 store; s0/s1 hold the two call-crossing params)

DEFINE_func_801723C4()  /* dedup: shared engine-core @0x801723C4 (src/shared) */

DEFINE_func_80172414()  /* dedup: shared engine-core @0x80172414 (src/shared) */

DEFINE_func_8017248C()  /* dedup: shared engine-core @0x8017248C (src/shared) */

DEFINE_func_801724EC()  /* dedup: shared engine-core @0x801724EC (src/shared) */

DEFINE_func_8017250C()  /* dedup: shared engine-core @0x8017250C (src/shared) */

DEFINE_func_80172560()  /* dedup: shared engine-core @0x80172560 (src/shared) */

DEFINE_func_80172588()  /* dedup: shared engine-core @0x80172588 (src/shared) */

DEFINE_func_80172590()  /* dedup: shared engine-core @0x80172590 (src/shared) */

DEFINE_func_801725A4()  /* dedup: shared engine-core @0x801725A4 (src/shared) */

DEFINE_func_801725B8()  /* dedup: shared engine-core @0x801725B8 (src/shared) */

DEFINE_func_801725CC()  /* dedup: shared engine-core @0x801725CC (src/shared) */

DEFINE_func_801725E0()  /* dedup: shared engine-core @0x801725E0 (src/shared) */

DEFINE_func_801725F4()  /* dedup: shared engine-core @0x801725F4 (src/shared) */

DEFINE_func_80172608()  /* dedup: shared engine-core @0x80172608 (src/shared) */

DEFINE_func_8017261C()  /* dedup: shared engine-core @0x8017261C (src/shared) */

DEFINE_func_80172630()  /* dedup: shared engine-core @0x80172630 (src/shared) */

DEFINE_func_80172644()  /* dedup: shared engine-core @0x80172644 (src/shared) */

DEFINE_func_80172658()  /* dedup: shared engine-core @0x80172658 (src/shared) */

DEFINE_func_80172664()  /* dedup: shared engine-core @0x80172664 (src/shared) */

DEFINE_func_80172670()  /* dedup: shared engine-core @0x80172670 (src/shared) */

DEFINE_func_8017267C()  /* dedup: shared engine-core @0x8017267C (src/shared) */

DEFINE_func_80172688()  /* dedup: shared engine-core @0x80172688 (src/shared) */

DEFINE_func_80172694()  /* dedup: shared engine-core @0x80172694 (src/shared) */

DEFINE_func_801726A0()  /* dedup: shared engine-core @0x801726A0 (src/shared) */

DEFINE_func_801726AC()  /* dedup: shared engine-core @0x801726AC (src/shared) */

DEFINE_func_801726B8()  /* dedup: shared engine-core @0x801726B8 (src/shared) */

DEFINE_func_801726C4()  /* dedup: shared engine-core @0x801726C4 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected (stub: 3 global stores + tail call)

DEFINE_func_801726D0()  /* dedup: shared engine-core @0x801726D0 (src/shared) */

DEFINE_func_80172710()  /* dedup: shared engine-core @0x80172710 (src/shared) */

DEFINE_func_80172738()  /* dedup: shared engine-core @0x80172738 (src/shared) */

DEFINE_func_80172760()  /* dedup: shared engine-core @0x80172760 (src/shared) */

DEFINE_func_80172780()  /* dedup: shared engine-core @0x80172780 (src/shared) */

extern s32 (*D_8018A09C[])(void *);

s32 func_801727D0(void *a0) {
    return D_8018A09C[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280C (src/shared) */

DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */

DEFINE_func_8017288C()  /* dedup: shared engine-core @0x8017288C (src/shared) */

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */

extern s32 (*D_8018A0A8[])(void *);

s32 func_801728E4(void *a0) {
    return D_8018A0A8[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */

DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */

DEFINE_func_801729A8()  /* dedup: shared engine-core @0x801729A8 (src/shared) */

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729B0 (src/shared) */

extern s32 (*D_8018A0B4[])(void *);

s32 func_801729F0(void *a0) {
    return D_8018A0B4[*(u8 *)((s32)a0 + 0x214)](a0);
}

// @class: plumbing
// @stuck: none — MATCH expected (simple STUB: save arg across call, two halfword stores, 3 calls)

DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172A2C (src/shared) */

DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172A8C (src/shared) */

DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172ACC (src/shared) */

DEFINE_func_80172B0C()  /* dedup: shared engine-core @0x80172B0C (src/shared) */

extern s16 D_80126B32;
extern s32 func_80172B44(void *a0);
extern void func_80174684(void *);

void func_80172B14(s16 a0) {
    D_80126B32 = a0;
    func_80174684((void *)func_80172B44);
}

extern s32 (*D_8018A0C4[])(void *);

s32 func_80172B44(void *a0) {
    return D_8018A0C4[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172B80 (src/shared) */

DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172BC8 (src/shared) */

DEFINE_func_80172C48()  /* dedup: shared engine-core @0x80172C48 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80172C50);

extern s32 (*D_8018A0D0[])(void *);

s32 func_80172CA0(void *a0) {
    return D_8018A0D0[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172CDC (src/shared) */

DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172D14 (src/shared) */

DEFINE_func_80172D60()  /* dedup: shared engine-core @0x80172D60 (src/shared) */

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172D68 (src/shared) */

extern s32 (*D_8018A0DC[])(void *);

s32 func_80172DAC(void *a0) {
    return D_8018A0DC[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80172DE8()  /* dedup: shared engine-core @0x80172DE8 (src/shared) */

DEFINE_func_80172E20()  /* dedup: shared engine-core @0x80172E20 (src/shared) */

DEFINE_func_80172E8C()  /* dedup: shared engine-core @0x80172E8C (src/shared) */

DEFINE_func_80172E94()  /* dedup: shared engine-core @0x80172E94 (src/shared) */

DEFINE_func_80172ED4()  /* dedup: shared engine-core @0x80172ED4 (src/shared) */

DEFINE_func_80172EFC()  /* dedup: shared engine-core @0x80172EFC (src/shared) */

DEFINE_func_80172F24()  /* dedup: shared engine-core @0x80172F24 (src/shared) */

DEFINE_func_80172F4C()  /* dedup: shared engine-core @0x80172F4C (src/shared) */

DEFINE_func_80172F9C()  /* dedup: shared engine-core @0x80172F9C (src/shared) */

DEFINE_func_80172FEC()  /* dedup: shared engine-core @0x80172FEC (src/shared) */

DEFINE_func_8017303C()  /* dedup: shared engine-core @0x8017303C (src/shared) */

extern s32 (*D_8018A0E8[])(void *);

s32 func_80173078(void *a0) {
    return D_8018A0E8[*(u8 *)((s32)a0 + 0x214)](a0);
}

// @class: plumbing
// @stuck: none — MATCH expected (STUB: 4 sequential calls, param saved in $s0)

DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730B4 (src/shared) */

DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730FC (src/shared) */

DEFINE_func_8017316C()  /* dedup: shared engine-core @0x8017316C (src/shared) */

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */

extern s32 (*D_8018A0F4[])(void *);

s32 func_8017319C(void *a0) {
    return D_8018A0F4[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731D8 (src/shared) */

extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
extern M2C_UNK D_8018A094;

void func_80173220(void * arg0)
{
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_8018A094);
    }
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x8000) {
        func_80171A1C(arg0);
        func_80174650(arg0);
    }
}

DEFINE_func_80173294()  /* dedup: shared engine-core @0x80173294 (src/shared) */

DEFINE_func_8017329C()  /* dedup: shared engine-core @0x8017329C (src/shared) */

DEFINE_func_801732C4()  /* dedup: shared engine-core @0x801732C4 (src/shared) */

DEFINE_func_801732F4()  /* dedup: shared engine-core @0x801732F4 (src/shared) */

DEFINE_func_8017331C()  /* dedup: shared engine-core @0x8017331C (src/shared) */

DEFINE_func_8017334C()  /* dedup: shared engine-core @0x8017334C (src/shared) */

DEFINE_func_80173374()  /* dedup: shared engine-core @0x80173374 (src/shared) */

DEFINE_func_801733A4()  /* dedup: shared engine-core @0x801733A4 (src/shared) */

extern void func_8016F30C(void);
extern s32 func_80174650(s32);

void func_801733CC(s32 a0) {
    func_8016F30C();
    func_80174650(a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801733FC);

DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801734BC);

extern s32 (*D_8018A100[])(void *);

s32 func_80173544(void *a0) {
    return D_8018A100[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80173580()  /* dedup: shared engine-core @0x80173580 (src/shared) */

DEFINE_func_801735B8()  /* dedup: shared engine-core @0x801735B8 (src/shared) */

extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80171A1C(u8 *a0);
extern s16 D_80126B40;
extern s16 D_80126B32;

void func_801735EC(void *a0) {
    if (D_80126B40 != 0) {
        *(s32 *)((u8 *)a0 + 0x44) |= 0x40000;
    }
    func_801477E8((s32 *)a0, D_80126B32 << 16);
    func_80171A1C((u8 *)a0);
}

DEFINE_func_80173648()  /* dedup: shared engine-core @0x80173648 (src/shared) */

DEFINE_func_801736A8()  /* dedup: shared engine-core @0x801736A8 (src/shared) */

DEFINE_func_801736B0()  /* dedup: shared engine-core @0x801736B0 (src/shared) */

extern s32 (*D_8018A114[])(void *);

s32 func_801736FC(void *a0) {
    return D_8018A114[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80173738()  /* dedup: shared engine-core @0x80173738 (src/shared) */

DEFINE_func_80173770()  /* dedup: shared engine-core @0x80173770 (src/shared) */

DEFINE_func_801737B0()  /* dedup: shared engine-core @0x801737B0 (src/shared) */

extern s16 D_80126B30;
extern s32 func_801737E8(void *a0);
extern void func_80174684(void *);

void func_801737B8(s16 a0) {
    D_80126B30 = a0;
    func_80174684((void *)func_801737E8);
}

extern s32 (*D_8018A120[])(void *);

s32 func_801737E8(void *a0) {
    return D_8018A120[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80173824()  /* dedup: shared engine-core @0x80173824 (src/shared) */

/* func_8017385C — overlay ov_SC01_077 shared core */
DEFINE_func_8017385C()  /* dedup: shared engine-core @0x8017385C (src/shared) */

DEFINE_func_801738D4()  /* dedup: shared engine-core @0x801738D4 (src/shared) */

extern s16 D_80126B30;
extern s32 func_8017390C(void *a0);
extern void func_80174684(void *);

void func_801738DC(s16 a0) {
    D_80126B30 = a0;
    func_80174684((void *)func_8017390C);
}

extern s32 (*D_8018A12C[])(void *);

s32 func_8017390C(void *a0) {
    return D_8018A12C[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80173948()  /* dedup: shared engine-core @0x80173948 (src/shared) */

DEFINE_func_80173980()  /* dedup: shared engine-core @0x80173980 (src/shared) */

DEFINE_func_801739D8()  /* dedup: shared engine-core @0x801739D8 (src/shared) */

DEFINE_func_80173A20()  /* dedup: shared engine-core @0x80173A20 (src/shared) */

DEFINE_func_80173A28()  /* dedup: shared engine-core @0x80173A28 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80173A60);

extern s32 (*D_8018A13C[])(void *);

s32 func_80173B4C(void *a0) {
    return D_8018A13C[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80173B88()  /* dedup: shared engine-core @0x80173B88 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80173BC0);

DEFINE_func_80173C64()  /* dedup: shared engine-core @0x80173C64 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80173CB4);

// @class: schedule
// @stuck: none — MATCH (55 ins). Levers: pin param_1->$s0 ($16) + a register ptr &D_80127508->$s1 ($17)
//   kept across the first block (reused for the !=0 test and the +4 arg); func_801399F0(*(s0+0x198))
//   reuses the outer-test $a0 load as its arg; and DUPLICATE func_80154274()+func_80171A1C() into BOTH
//   if/else arms (don't factor to a shared tail) -- gcc cross-jump-merges the two jals+epilogue but keeps
//   each arm's arg-setup, because the *(s0+0x198)=0 store lands in the !=0 arm's `j` delay slot and breaks
//   the suffix identity right before the merge point.

DEFINE_func_80173E1C()  /* dedup: shared engine-core @0x80173E1C (src/shared) */

// @class: other
// @stuck: switch dispatch tree — verifying gcc -O2 emits 0x79-first balanced tree

DEFINE_func_80173EF8()  /* dedup: shared engine-core @0x80173EF8 (src/shared) */

extern s32 func_80174188(s32 a0);
extern void func_801741A8(s32 a0);

void func_80174158(s32 a0) {
    func_80174188(a0);
    func_801741A8(a0);
}

DEFINE_func_80174188()  /* dedup: shared engine-core @0x80174188 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (3 jal stubs + two 0xA00000 global stores reusing one lui)

DEFINE_func_801741A8()  /* dedup: shared engine-core @0x801741A8 (src/shared) */

DEFINE_func_801741EC()  /* dedup: shared engine-core @0x801741EC (src/shared) */

DEFINE_func_80174274()  /* dedup: shared engine-core @0x80174274 (src/shared) */

DEFINE_func_8017427C()  /* dedup: shared engine-core @0x8017427C (src/shared) */

extern s32 (*D_8018A15C[])(void *);

s32 func_801742A4(void *a0) {
    return D_8018A15C[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_801742E0()  /* dedup: shared engine-core @0x801742E0 (src/shared) */

DEFINE_func_80174318()  /* dedup: shared engine-core @0x80174318 (src/shared) */

DEFINE_func_80174354()  /* dedup: shared engine-core @0x80174354 (src/shared) */

DEFINE_func_8017435C()  /* dedup: shared engine-core @0x8017435C (src/shared) */

extern s32 (*D_8018A168[])(void *);

s32 func_80174384(void *a0) {
    return D_8018A168[*(u8 *)((s32)a0 + 0x214)](a0);
}

extern void func_80171A1C(u8 *a0);
extern void func_801743F0(u8 *a0);

void func_801743C0(u8 *a0) {
    func_80171A1C(a0);
    func_801743F0(a0);
}

DEFINE_func_801743F0()  /* dedup: shared engine-core @0x801743F0 (src/shared) */

DEFINE_func_80174430()  /* dedup: shared engine-core @0x80174430 (src/shared) */

DEFINE_func_80174438()  /* dedup: shared engine-core @0x80174438 (src/shared) */

extern s32 (*D_8018A174[])(void *);

s32 func_80174474(void *a0) {
    return D_8018A174[*(u8 *)((s32)a0 + 0x214)](a0);
}

extern void func_80171A1C(u8 *a0);
extern void func_801744E0(u8 *a0);

void func_801744B0(u8 *a0) {
    func_80171A1C(a0);
    func_801744E0(a0);
}

DEFINE_func_801744E0()  /* dedup: shared engine-core @0x801744E0 (src/shared) */

DEFINE_func_80174524()  /* dedup: shared engine-core @0x80174524 (src/shared) */

DEFINE_func_8017452C()  /* dedup: shared engine-core @0x8017452C (src/shared) */

DEFINE_func_80174554()  /* dedup: shared engine-core @0x80174554 (src/shared) */

DEFINE_func_80174584()  /* dedup: shared engine-core @0x80174584 (src/shared) */

DEFINE_func_801745AC()  /* dedup: shared engine-core @0x801745AC (src/shared) */

DEFINE_func_801745DC()  /* dedup: shared engine-core @0x801745DC (src/shared) */

DEFINE_func_80174604()  /* dedup: shared engine-core @0x80174604 (src/shared) */

DEFINE_func_80174630()  /* dedup: shared engine-core @0x80174630 (src/shared) */

extern s32 D_801270BC;
    extern s32 D_801150F8;
    s32 func_80174650(s32 _arg0)
{
        D_801270BC = D_801270BC | 1;
        D_801150F8 = 0;
    }

DEFINE_func_80174674()  /* dedup: shared engine-core @0x80174674 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80174684);

// @class: plumbing
// @stuck: none — MATCH (straight stub: two calls, fn-ptr args + 0x1000000 immediate)

DEFINE_func_801746A4()  /* dedup: shared engine-core @0x801746A4 (src/shared) */

DEFINE_func_801746DC()  /* dedup: shared engine-core @0x801746DC (src/shared) */

DEFINE_func_80174714()  /* dedup: shared engine-core @0x80174714 (src/shared) */

DEFINE_func_80174754()  /* dedup: shared engine-core @0x80174754 (src/shared) */

DEFINE_func_80174764()  /* dedup: shared engine-core @0x80174764 (src/shared) */

DEFINE_func_80174774()  /* dedup: shared engine-core @0x80174774 (src/shared) */

DEFINE_func_80174784()  /* dedup: shared engine-core @0x80174784 (src/shared) */

DEFINE_func_801747AC()  /* dedup: shared engine-core @0x801747AC (src/shared) */

extern s32 (*D_8018A180[])(void *);

s32 func_801747CC(void *a0) {
    return D_8018A180[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80174808()  /* dedup: shared engine-core @0x80174808 (src/shared) */

DEFINE_func_8017481C()  /* dedup: shared engine-core @0x8017481C (src/shared) */

DEFINE_func_80174824()  /* dedup: shared engine-core @0x80174824 (src/shared) */

DEFINE_func_8017484C()  /* dedup: shared engine-core @0x8017484C (src/shared) */

extern s32 (*D_8018A188[])(void *);

s32 func_80174888(void *a0) {
    return D_8018A188[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_801748C4()  /* dedup: shared engine-core @0x801748C4 (src/shared) */

DEFINE_func_801748E4()  /* dedup: shared engine-core @0x801748E4 (src/shared) */

DEFINE_func_801748EC()  /* dedup: shared engine-core @0x801748EC (src/shared) */

extern s32 (*D_8018A190[])(void *);

s32 func_8017496C(void *a0) {
    return D_8018A190[*(u8 *)((s32)a0 + 0x4)](a0);
}

DEFINE_func_801749A8()  /* dedup: shared engine-core @0x801749A8 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (105 ins). Keys: (1) single-buffer struct for the func_80049CAC/func_8012F14C
//   out-params (local_2c..local_14 are fields of ONE stack buffer, not separate scalars — else gcc
//   DCEs the unread ones + overlaps the buffer -> wrong 0x40 frame); (2) $s2/$s1 pins for iVar5/iVar4
//   (call-crossing saved regs); (3) load D_80126B66 as RAW u16 (lhu) with (s16) sext at each USE —
//   this defeats gcc's lhu+sext->lh combine fold so the target's lhu+sll+sra reappears; (4) inline
//   `iVar5 = (s16)D_80126B5E` into the f48 expression so the f28 operand load schedules first.

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s16 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32);

typedef struct {
    /* 0x00 */ s8  head[0x14];
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
    /* 0x1C */ s32 f1c;
    /* 0x20 */ s16 f20;
    /* 0x22 */ s16 f22;
    /* 0x24 */ s16 f24;
    /* 0x26 */ s16 pad26;
    /* 0x28 */ s16 f28;
    /* 0x2A */ s16 f2a;
    /* 0x2C */ s16 f2c;
} Buf;

s32 func_801749C8(s32 param_1)
{
    Buf buf;
    register s32 iVar5 __asm__("$18");
    register u32 iVar4 __asm__("$17");

    *(s32 *)(param_1 + 8) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 8), (s32)*(s16 *)(param_1 + 0xc), 4);
    *(s32 *)(param_1 + 0x10) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1a) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1a), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1c) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1c), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2e), 0x10);
    *(s16 *)(param_1 + 0x2a) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2a), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2c) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2c), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    iVar4 = (u16)D_80126B66;
    *(s32 *)(param_1 + 0x48) = *(s16 *)(param_1 + 0x28) + (iVar5 = (s16)D_80126B5E);
    *(s32 *)(param_1 + 0x4c) = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    *(s32 *)(param_1 + 0x50) = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    func_80049CAC(param_1 + 0x18, (s32)&buf);

    buf.f14 = *(s16 *)(param_1 + 0x28) + iVar5;
    buf.f18 = *(s16 *)(param_1 + 0x2a) + (s16)D_80126B62;
    buf.f1c = *(s16 *)(param_1 + 0x2c) + (s16)iVar4;
    buf.f20 = 0;
    buf.f22 = 0;
    buf.f24 = (s16)*(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&buf, (s32)&buf.f20, (s32)&buf.f28);

    *(s32 *)(param_1 + 0x3c) = buf.f28;
    *(s32 *)(param_1 + 0x40) = buf.f2a;
    *(s32 *)(param_1 + 0x44) = buf.f2c;
}

DEFINE_func_80174B6C()  /* dedup: shared engine-core @0x80174B6C (src/shared) */

DEFINE_func_80174BBC()  /* dedup: shared engine-core @0x80174BBC (src/shared) */

// @class: struct
// @stuck: none — MATCH (27 ins) via func-ptr array fold extern void(*D_8018A194[])()

extern void (*D_8018A194[])();

void func_80174BF4(void * arg0)
{
    M2C_FIELD(arg0, s32 *, 0xC) = 0x12C;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x12C;
    M2C_FIELD(arg0, s16 *, 0x20) = 0x155;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x800;
    M2C_FIELD(arg0, s16 *, 0x24) = 0;
    M2C_FIELD(arg0, s16 *, 0x2E) = 0;
    M2C_FIELD(arg0, s16 *, 0x30) = -0x28;
    M2C_FIELD(arg0, s16 *, 0x32) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    D_8018A194[M2C_FIELD(arg0, u8 *, 4)]();
}

DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174C60 (src/shared) */

extern s32 func_80174CB0(s32, s32);

void func_80174C80(s32 a0) {
    s32 v;
    v = (*(u16 *)(a0 + 0xA0) - 0x16) & 0xFFF;
    *(s16 *)(a0 + 0xA0) = v;
    func_80174CB0(a0, v);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80174CB0);

DEFINE_func_80174E9C()  /* dedup: shared engine-core @0x80174E9C (src/shared) */

DEFINE_func_80174ED4()  /* dedup: shared engine-core @0x80174ED4 (src/shared) */

DEFINE_func_80174EF0()  /* dedup: shared engine-core @0x80174EF0 (src/shared) */

extern s32 (*D_8018A19C[])(void *);

s32 func_80174F28(void *a0) {
    return D_8018A19C[*(u8 *)((s32)a0 + 0x4)](a0);
}

DEFINE_func_80174F64()  /* dedup: shared engine-core @0x80174F64 (src/shared) */

DEFINE_func_80174FBC()  /* dedup: shared engine-core @0x80174FBC (src/shared) */

DEFINE_func_80175014()  /* dedup: shared engine-core @0x80175014 (src/shared) */

DEFINE_func_8017509C()  /* dedup: shared engine-core @0x8017509C (src/shared) */

DEFINE_func_80175114()  /* dedup: shared engine-core @0x80175114 (src/shared) */

DEFINE_func_80175150()  /* dedup: shared engine-core @0x80175150 (src/shared) */

extern void (*D_8018A1A4[])(void*);
extern s32 func_80175268(s32);

void func_80175184(s32* arg0) {
    u16 v1 = *(u16*)((u8*)arg0 + 2);
    if (v1 < 2) {
        D_8018A1A4[v1](arg0);
    } else {
        func_80175268((s32)arg0);
    }
}

DEFINE_func_801751D8()  /* dedup: shared engine-core @0x801751D8 (src/shared) */

// @class: struct
// @stuck: none — MATCH (fn-ptr table indexed by D_80078EC0-1; param preserved in $s0 across 1st call)

extern u8 D_80078EC0;
extern void (*D_8018A1AC[])(s32);
extern void func_80146CA0(void *a0);

s32 func_80175218(void * param_1)
{
    s32 i = D_80078EC0 - 1;

    D_8018A1AC[i](param_1);
    ((void (*)(s32))func_80146CA0)(param_1);
}

// @class: struct
// @stuck: none — MATCH
//
// Indexed fn-ptr table call. Writing D_8018A1C4[D_80078EC0 - 1]() lets gcc reassociate
// (x-1)*4 -> x*4 - 4 and fold the -4 into the lw displacement (lw -4($at)), dropping the
// `addiu -1`. The target keeps `addiu $v0,$v0,-1; sll $v0,2` separate then folds %lo at
// offset 0. The fix: integer address arithmetic with an explicit << 2 on (x-1):
//   (s32)base + ((x - 1) << 2)  -> keeps (x-1) live in the index reg, folds %lo(base) into lw.

#include "common.h"

extern u8 D_80078EC0;
extern VoidFn D_8018A1C4[];

s32 func_80175268(s32 param_1)
{
    *(u32 *)(param_1 + 0x44) |= 2;
    (*(VoidFn *)((s32)D_8018A1C4 + ((D_80078EC0 - 1) << 2)))();
}

DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752BC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80175308);

// @class: remat
// @stuck: none — MATCH
DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */

DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */

DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801754A8);

// @class: struct
// @stuck: none — MATCH expected. fn-ptr-table dispatch: byte at param+1 indexes D_8018A314[] declared extern void(*[])() so %lo folds into the lw of the fn-ptr; dispatched call takes no args (no $a0 setup before jalr), then three plain jal tail calls.
#include "common.h"

extern void (*D_8018A314[])();
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_8017553C(s32 *param) {
    D_8018A314[*(u8 *)((s32)param + 1)]();
    ((void (*)(void))func_801758FC)();
    ((void (*)(void))func_80175820)();
    ((void (*)(void))func_801759D8)();
}

DEFINE_func_80175590()  /* dedup: shared engine-core @0x80175590 (src/shared) */

DEFINE_func_80175624()  /* dedup: shared engine-core @0x80175624 (src/shared) */

DEFINE_func_80175668()  /* dedup: shared engine-core @0x80175668 (src/shared) */

// @class: struct
// @stuck: none — MATCH expected (indexed fn-ptr-table call + 3 direct calls; mirrors byte-matched func_80130D0C)

extern void (*D_8018A320[])(void);
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);

void func_80175690(void *a0) {
    D_8018A320[*(u8 *)((s32)a0 + 1)]();
    func_801758FC();
    func_80175820();
    func_801759D8();
}

DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756E4 (src/shared) */

DEFINE_func_80175798()  /* dedup: shared engine-core @0x80175798 (src/shared) */

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757A0 (src/shared) */

DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757E0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80175820);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801758FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801759D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80175AB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80175DA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80176144);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80176218);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80176734);

DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176D00 (src/shared) */

/* func_80176D94 (ov_SC01_077) — 152 ins. Port of the MATCHED sibling func_801770E0
 * (src/ov_SC01_077/ov_SC01_077.c:10352, Fable5 crack): the two targets are
 * instruction-ISOMORPHIC (diff = immediates/symbols only). All levers inherited:
 *  - /s-load dep lattice: both D-globals read as struct-member-at-offset-0 (COMPONENT_REF
 *    sets MEM_IN_STRUCT_P on the LOAD) → full store↔load conflict lattice (sched.c:816-864
 *    drop clauses both fail) → tail = source statement order around the loads.
 *  - `dl` multi-set load var (reg_n_sets==2 → no birthing boost → lhu stays at source pos).
 *  - v0m-before-c6055 block: [1]-statement-first with the [0] value precomputed → mask
 *    0xffffff materializes first; c6000dcff pinned $a2 (breaks the sched2 $v1 fixed point).
 *  - head (u16)param_2 (zero_extend) vs tail param_2 & 0xffff (AND) — CSE-dodge, no
 *    cross-call CSE, no 7th callee-save.
 *  - u4/u5 fresh single-set call-result vars (S2 boost → jal delay slots);
 *    c3/cad/cff = $s5/$s4/$s3 pins. param_2/uVar5/iVar6 UNPINNED (natural $s2/$s0/$s1).
 * Constant swaps vs 770E0: 0x6e16{5010,5808,4060,3858}→0x6b56{5040,5808,4060,3858},
 * D_8011F830→D_8011F82C, D_8011F82E→D_8011F82A, 0xb8→0xad, 0x6055ff00→0x6000dcff,
 * 0x60ff3214→0x600000ff, (iVar6-4)→(iVar6+10), (iVar6-5)→(iVar6+9).
 */

DEFINE_func_80176D94()  /* dedup: shared engine-core @0x80176D94 (src/shared) */

DEFINE_func_80176FF4()  /* dedup: shared engine-core @0x80176FF4 (src/shared) */

// MATCH (152/152) — func_801770E0, Fable5 crack, Phase 24 T7 §G.
// Was: the regalloc.md §RC-6 NAMED exemplar, CLOSE=47 floor. VERDICT DOWNGRADED: not a
// pressure-lock — the 47 residual was a MISSING MEMORY-DEPENDENCE LATTICE (wrong dep graph),
// and once restored every remaining edit was local+monotone: 47 -> 12 -> 10 -> 4 -> MATCH.
//
// LEVER 1 (47->12, THE STRUCTURAL KEY — "/s-load dep lattice"):
//   gcc-2.7.2 expr.c marks INDIRECT_REF-of-PLUS as MEM_IN_STRUCT_P: `p[k]` (k!=0) stores are
//   mem/s, bare `*p` is not. sched.c:829-907 true/anti_dependence DROP the conflict when one
//   side is /s+varying(+!QI) and the other non-/s+fixed → `puVar3[k]` stores never order
//   against a plain `lhu D_global` (fixed-address, non-/s) → both tail lhu's float free and
//   ~40 insns of store/mul schedule collapse into priority soup (the old "RC-6" 47).
//   FIX (zero bytes): load the global as a struct member at offset 0 —
//   `((struct hs*)&D_8011F830)->h` — COMPONENT_REF sets /s on the LOAD; both exception
//   clauses now fail for every store↔load pair → full conflict lattice: stores before the
//   load statement hold it down (true deps), stores after stay below it (anti deps).
//   The whole tail order then equals SOURCE statement order (S1) around the two loads.
// LEVER 2 (12->10, re-validated old 49->47 lever): compute the [0]-store value into a
//   block-local `v0m` BEFORE the [1]=0x6055ff00 statement → mask 0xffffff materializes first.
//   (2-insn split consts have reg_n_sets==2 → never birthing-boosted → they place at the
//   block top in LUID order; the temp reorders the LUIDs.)
// LEVER 3 (10->4, the pin): the residual LOOKED like schedule but was ONE local-alloc
//   first-fit: 0x6055ff00 got $v1 (its window [birth..sw1] missed the $v1 v0m-chain since
//   sched1 had sw1 above the chain); c6055=$v1 then FORCES sw1 above the chain in sched2
//   (hard-reg anti-web: sw1 reads $v1, chain writes $v1) — a self-consistent wrong fixed
//   point. Block-scoped `register u32 c6055 __asm__("$6") = 0x6055ff00;` puts it in $a2
//   (target), sched2's webs relax, and sw1/lhu/retv/move all fall into place (6 insns).
//   RC-5 channels clean: narrow scope, $a2 already ever-live (arg reg), no spills.
// LEVER 4 (4->0): C89 decl-initializer order = LUID order: `u32 v0m = expr;` BEFORE the
//   pinned c6055 decl puts the mask materialization below the pinned lui/ori → the two
//   2-insn const pairs land [mask, 0x6055ff00] at the top like the target.
// Supporting structure (needed, from Ghidra's REAL variable reuse):
//   - `dl` multi-set (both D-loads through one u32 var) → no birthing boost → the lhu's
//     stay at source position (a single-set load var sinks to its consumer).
//   - head uses `(u16)param_2` (zero_extend RTL) vs tail `param_2 & 0xffff` (AND rtl) —
//     different cse hashes → no cross-call CSE → no 7th callee-save; replaces the old
//     volatile-asm barrier (which is a FULL scheduling barrier per sched.c ASM_OPERANDS
//     handling and had warped the tail).
//   - u4/u5 fresh single-set call-result vars (S2 boost → jal delay slots), c3/cb8/cff
//     $s5/$s4/$s3 pins for the 777BC extra args: unchanged from the close draft.
// Negative results (do not retry): unboosting the v0m chain (multi-set va / named+retied
//   t0c / v0m-reuse-as-mul2-t) regresses 10 -> 35..71 — the target NEEDS the inline
//   single-set birthing boosts; a retie on a shared const breaks cse-sharing with literal
//   uses elsewhere (+1 insn) unless ALL uses go through the var.
// Decl-reconcile notes (unchanged): func_80177784 canonical 4-arg called 3-arg
//   (cast_call_sites), func_801777BC INCLUDE_ASM 7-arg, D_8011F830/D_8011F82E u16.

/* /s-cast helper anonymized inline below (self-contained for ×134 propagation) */
DEFINE_func_801770E0()  /* dedup: shared engine-core @0x801770E0 (src/shared) */

DEFINE_func_80177340()  /* dedup: shared engine-core @0x80177340 (src/shared) */

DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801775E0);

DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776EC (src/shared) */

DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801777BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801778A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80177940);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80177AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80177B5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80177DA8);

// @class: regalloc-order
// @stuck: none — MATCH

uint *func_80177EA4(uint *param_1, int param_2, uint param_3, int param_4)
{
    uint uVar1;
    register int iVar2 __asm__("$4");
    register uint *p1 __asm__("$9");
    register uint *puVar3 __asm__("$8");
    register int iVar4 __asm__("$10");
    register uint uVar5 __asm__("$11");
    register uint mask __asm__("$12");
    register int nx __asm__("$2");
    register int p4s __asm__("$7");
    int cont;
    p1 = param_1; uVar5 = 0x1000000; iVar4 = 0; mask = 0xffffff;
    p4s = param_4 << 0x10;
    puVar3 = p1 + 3;
    do {
        register uint c74 __asm__("$4");
        register uint c3 __asm__("$3");
        register uint m __asm__("$2");
        c74 = 0x74808080;
        m = (uint)(p1 + -5) & mask;
        __asm__ __volatile__("" : "=r"(m) : "0"(m));
        c3 = 0x3000000;
        *p1 = m | c3;
        puVar3[-2] = c74;
        if ((short)iVar4 != 0) {
            register int six __asm__("$2");
            six = 6;
            if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
            else {
                register int t __asm__("$2");
                t = param_2 >> 0x10 & 0xf;
                iVar2 = t + 1;
                param_2 = param_2 << 4;
            }
            {
                register int iv2c __asm__("$3");
                register int one __asm__("$2");
                iv2c = iVar2;
                __asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));
                one = 1;
                if (iv2c != one) uVar5 = 0;
            }
            uVar1 = p4s | (param_3 & 0xffff) | uVar5;
        } else { iVar2 = 0; uVar1 = p4s | (param_3 & 0xffff); }
        puVar3[-1] = uVar1;
        __asm__ __volatile__("" : : "r"(iVar2) : "memory");
        {
            register uint c6b __asm__("$3");
            register uint r __asm__("$2");
            c6b = 0x6b564000;
            r = (uint)(iVar2 << 3) | c6b;
            *puVar3 = r;
        }
        puVar3 = puVar3 + 5; p1 = p1 + 5; param_3 = param_3 + 8;
        {
            register int sx __asm__("$2");
            nx = iVar4 + 1;
            iVar4 = nx;
            sx = nx << 0x10;
            cont = (sx >> 0x10) < 7;
        }
    } while (cont);
    return p1;
}

// @class: schedule
// @stuck: none — MATCH (pin hoisted consts 5/$t2 + 0xfeff/$t1 BEFORE the $a2 ptr init fixes prologue order; ==5 uses register c5, but <5 loop-back uses literal 5 -> slti)
#include "common.h"

DEFINE_func_80177F84()  /* dedup: shared engine-core @0x80177F84 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80178004);

// @class: iv-combine
// @stuck: none — MATCH (78 ins, relocation-masked)
//
// KEY LEVERS (byte-gated):
//  1. SINGLE moving pointer (param_1), write record fields as offsets off param_1
//     (NOT a second `puVar3` var — the two-pointer form leaves an unused param_1+0x12
//     init and gcc reanchors the giv anyway).
//  2. GIV ANCHOR = the LAST giv-store in PROGRAM ORDER (gcc loop.c: record_giv PREPENDS
//     to bl->giv, combine_givs makes giv_array[0]=the-last-recorded the base). The target
//     anchors its store giv at param_1+0x12 (all displacements <=0), so the +0x12 store
//     (`*(short*)(param_1+0x12)=8`) MUST be the LAST store before the pointer bump.
//     Moving it last: 15-mismatch -> 3.
//  3. switch case-BODY layout order follows source order: emit 0x1850/0x1858 (the break
//     cases) FIRST, then the 0x3870/0x3871/0x3872 continue cases, then default.
//  4. byte fields read via post-increment: `c=*p2++; ...; d=*p2++;` (target advances
//     param_2 by +1 twice, not +2 once, in the store path).
//  5. <0x861 branch-polarity: write `if (x>=0x861) +=8; else +=7;` so the +=8 (else of
//     the source intent) falls through first and gcc emits `bnez` to the +=7 body (§3-T4).

DEFINE_func_80178298()  /* dedup: shared engine-core @0x80178298 (src/shared) */

DEFINE_func_801783D0()  /* dedup: shared engine-core @0x801783D0 (src/shared) */

M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D8E08;

void func_80178438(u16 *arg0) {
    func_8001534C(2, &D_801D8E08, 0x80, 0x88, 0, 0);
    func_800153CC(3, *arg0, 0xA8, 0x88, 0x40, 0);
}

// @class: struct
// @stuck: none — MATCH (91 ins). Keys: (1) two-pointer do-while over D_801202A0
//   (base ptr p=$s1, derived q=p+0x54=$s0, counter i=$s2) all PINNED via register
//   __asm__ to get the 3-saved-reg frame (0x20) + exact alloc order; (2) the &&-chain
//   if(byte6C!=0 && byte6D!=0) func_80130D0C else fptr -> func_80130D0C is the
//   fall-through THEN block, fptr the jumped-to ELSE (matches the two-beqz target CFG);
//   (3) the indirect-call table base D_8011DB08 PINNED to $v1 ($3) so it reuses store2's
//   freed reg AND HOISTS before the byte6C branch (else block then carries load-delay
//   nops, matching target); (4) byte6C read into a temp PINNED to $v0 ($2), read EARLY
//   (between store1 and store2) so it (a) reuses store1's freed $v0 and (b) lets store3
//   (sw -0x14) become the byte6C-beqz DELAY-SLOT fill instead of a standalone+nop. The
//   reg pins for tbl/c6c are the lever that beat the gcc reorg tie-break (delay-slot
//   packing) — without them the only residual was store3 standalone (+1 nop, 92 ins).

#include "common.h"

DEFINE_func_8017849C()  /* dedup: shared engine-core @0x8017849C (src/shared) */

DEFINE_func_80178608()  /* dedup: shared engine-core @0x80178608 (src/shared) */

DEFINE_func_8017869C()  /* dedup: shared engine-core @0x8017869C (src/shared) */

DEFINE_func_80178744()  /* dedup: shared engine-core @0x80178744 (src/shared) */

DEFINE_func_801787D4()  /* dedup: shared engine-core @0x801787D4 (src/shared) */

// @class: regalloc-order
// @stuck: sll $v0,$s1,2 must be recomputed AFTER the call (target nops the delay slot)

extern void func_80019064(void *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

extern int D_8018A360;
extern int D_8018A36C[];

void func_80178840(int param_1) {
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_8018A360);
        }
        ((void (*)(int, int))func_80131E00)(p, D_8018A36C[s1byte]);
    }
}

#include "common.h"

DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788B8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (result pinned to $v0 forces call-result copy to $v1 + delay-slot zero)

extern int func_801789AC(void);
extern s16 D_801DAAB8;

int func_80178970(void)
{
    register int r __asm__("$2");
    int v;

    v = func_801789AC();
    r = 0;
    if (v != 0)
        r = D_801DAAB8 == 0;
    return r;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801789AC);

// @class: struct
// @stuck: none — MATCH (pointer var forces &(*(int *)&D_8018A458) into $s0, reused for store + arg-0xC)



s32 func_80178B18(s32 param_1, s32 param_2)
{
    extern void func_80178BF8(void);
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern u16 D_8018A458;

    int *p = &(*(int *)&D_8018A458);
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
    extern int D_8018A458;

    int *p = &D_8018A458;
    *p = ((int)param_2);
    func_80178BF8();
    func_80178CBC(((int)param_1), p - 3);
}


void func_80178BF8(s32 a0, s32 a1);
void func_80178CBC(s32 a0, s32 a1);

DEFINE_func_80178BB8()  /* dedup: shared engine-core @0x80178BB8 (src/shared) */

// @class: other
// @stuck: none — MATCH (49 ins). Key: init loop pointers via &D_SYMBOL (not (T*)0x801da788 raw int, which emits lui+ori instead of lui%hi+addiu%lo).



void func_80178BF8(s32 _unused0, s32 _unused1)
{
    extern void func_8017B1D8(void);
    extern short D_801DAB2C;
    extern int D_801DA720;
    extern short D_801DA730;
    extern short D_801DA72C;
    extern short D_801DA728;
    extern short D_801DA724;
    extern int D_801DA9B0;
    extern int D_801DA738;
    extern s16 D_801DA718;
    extern short D_801DA710;
    extern short D_801DA714;
    extern int D_801DAA88;
    extern unsigned int D_801DA788;
    extern unsigned short D_801DA70E;

    unsigned short *puVar1;
    int iVar2;
    unsigned int *puVar3;

    iVar2 = 9;
    puVar3 = &D_801DA788;
    D_801DAB2C = 0;
    D_801DA720 = 0;
    D_801DA730 = 0;
    D_801DA72C = 0;
    D_801DA728 = 0;
    D_801DA724 = 0;
    D_801DA9B0 = 1;
    D_801DA738 = 0;
    (*(short *)&D_801DA718) = 0;
    do {
        *puVar3 = 0;
        iVar2 = iVar2 + -1;
        puVar3 = puVar3 + -1;
    } while (-1 < iVar2);
    iVar2 = 0x1ff;
    puVar1 = &D_801DA70E;
    do {
        *puVar1 = 0;
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -1;
    } while (-1 < iVar2);
    D_801DA710 = 0;
    D_801DA714 = 0;
    ((void (*)(int *, int))func_80016714)(&D_801DAA88, 0x14);
    func_8017B1D8();
}


M2C_UNK func_80178D40(s32, s32);                    /* extern */
extern s32 D_801DA308;
extern short D_801DAB2C;

void func_80178CBC(s32 arg0, s32 arg1) {
    D_801DA308 = arg1;
    do {
        func_80178D40(arg0, D_801DA308);
    } while (D_801DAB2C == 3);
}

extern short D_801DAB2C;
extern void func_80174714(void);

void func_80178D18(void) {
    D_801DAB2C = 0;
    func_80174714();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80178D40);

DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179B28 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80179B74);

DEFINE_func_80179D30()  /* dedup: shared engine-core @0x80179D30 (src/shared) */

DEFINE_func_80179D78()  /* dedup: shared engine-core @0x80179D78 (src/shared) */

DEFINE_func_80179DCC()  /* dedup: shared engine-core @0x80179DCC (src/shared) */

DEFINE_func_80179DF8()  /* dedup: shared engine-core @0x80179DF8 (src/shared) */

DEFINE_func_80179E1C()  /* dedup: shared engine-core @0x80179E1C (src/shared) */

extern void func_80179B74(s16 *a0);

void func_80179E48(s16 a0) {
    s16 sp[2];
    sp[0] = 0x1F;
    sp[1] = a0;
    func_80179B74(sp);
}

extern void func_80179B74(s16 *a0);

void func_80179E74(s16 a0) {
    s16 sp[2];
    sp[0] = 0x4;
    sp[1] = a0;
    func_80179B74(sp);
}

DEFINE_func_80179EA0()  /* dedup: shared engine-core @0x80179EA0 (src/shared) */

DEFINE_func_80179EE8()  /* dedup: shared engine-core @0x80179EE8 (src/shared) */

extern void func_80179B74(s16 *a0);

void func_80179F14(s16 a0, s16 a1) {
    s16 sp[3];
    sp[0] = 0x13;
    sp[1] = a0;
    sp[2] = a1;
    func_80179B74(sp);
}

DEFINE_func_80179F44()  /* dedup: shared engine-core @0x80179F44 (src/shared) */

DEFINE_func_80179F6C()  /* dedup: shared engine-core @0x80179F6C (src/shared) */

DEFINE_func_80179F98()  /* dedup: shared engine-core @0x80179F98 (src/shared) */

DEFINE_func_80179FEC()  /* dedup: shared engine-core @0x80179FEC (src/shared) */

DEFINE_func_8017A040()  /* dedup: shared engine-core @0x8017A040 (src/shared) */

extern void func_80179B74(s16 *a0);
extern s32 D_801DA734;

void func_8017A094(s32 arg0) {
    s16 sp10;

    D_801DA734 = arg0;
    sp10 = 0x15;
    func_80179B74(&sp10);
}

extern void func_80179B74(s16 *a0);
extern s32 D_801DA734;

void func_8017A0C4(s32 arg0) {
    s16 sp10;

    D_801DA734 = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}

DEFINE_func_8017A0F4()  /* dedup: shared engine-core @0x8017A0F4 (src/shared) */

DEFINE_func_8017A11C()  /* dedup: shared engine-core @0x8017A11C (src/shared) */

extern s32 D_801DA75C;
extern void func_80179B74(s16 *a0);

void func_8017A144(s32 a0) {
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_801DA75C = a0;
}

DEFINE_func_8017A180()  /* dedup: shared engine-core @0x8017A180 (src/shared) */

DEFINE_func_8017A1A8()  /* dedup: shared engine-core @0x8017A1A8 (src/shared) */

DEFINE_func_8017A1D0()  /* dedup: shared engine-core @0x8017A1D0 (src/shared) */

DEFINE_func_8017A1F8()  /* dedup: shared engine-core @0x8017A1F8 (src/shared) */

DEFINE_func_8017A220()  /* dedup: shared engine-core @0x8017A220 (src/shared) */

DEFINE_func_8017A248()  /* dedup: shared engine-core @0x8017A248 (src/shared) */

DEFINE_func_8017A270()  /* dedup: shared engine-core @0x8017A270 (src/shared) */

DEFINE_func_8017A298()  /* dedup: shared engine-core @0x8017A298 (src/shared) */

DEFINE_func_8017A2C0()  /* dedup: shared engine-core @0x8017A2C0 (src/shared) */

DEFINE_func_8017A2E8()  /* dedup: shared engine-core @0x8017A2E8 (src/shared) */

DEFINE_func_8017A310()  /* dedup: shared engine-core @0x8017A310 (src/shared) */

DEFINE_func_8017A338()  /* dedup: shared engine-core @0x8017A338 (src/shared) */

DEFINE_func_8017A360()  /* dedup: shared engine-core @0x8017A360 (src/shared) */

DEFINE_func_8017A388()  /* dedup: shared engine-core @0x8017A388 (src/shared) */

extern s16 D_801DA718;

s32 func_8017A3B0(void) {
    switch (D_801DA718) {
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

extern short D_801DA754;
extern short D_801DA750;

extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);

int func_8017A3D8(void)
{
    switch (D_801DA754) {
    case 0:
        func_800D0CA0(1);
        D_801DA754 = D_801DA754 + 1;
        return 0;
    case 100:
    {
        register int a __asm__("$4");
        a = D_801DA750;
        if (a != -1) {
            return func_8001AAA0() != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_801DA754 = D_801DA754 + 1;
        if (D_801DA754 < 0x1E) {
            return 0;
        }
        D_801DA754 = 100;
        return 0;
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017A4AC);

/* canonical: resident engine call @ 0x80059A80 (engine_core.h) */
DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017AD0C (src/shared) */

DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ADE8 (src/shared) */

DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017AE08 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017AE2C);

// @class: plumbing
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801DA794;
    extern s16 D_801DA796;
    extern s16 D_801DA798;
    extern s16 D_801DA78C;
    extern s16 D_801DA78E;
    extern s16 D_801DA790;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801DA794, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801DA796, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801DA798, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801DA78C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801DA78E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801DA790, (s32)((s16)param_2));
}


void func_8012A418(void);                           /* extern (Phase-18 reconciled) */
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801DA71C;
extern u16 D_801DA79C;
extern u16 D_801DA79E;
extern u16 D_801DA7A0;
extern s16 D_801DAAB8;

void func_8017B1D8(void) {
    func_8012A418();
    D_801DAAB8 = 0;
    D_801DA71C = 0;
    D_801DA79C = D_80126B5E;
    D_801DA79E = D_80126B62;
    D_801DA7A0 = D_80126B66;
}

// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.

typedef struct { u8 b[8]; } Blk8_8017B238;

s32 func_8017B238(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018A45C[];
    extern s16 D_801DA794;
    extern s16 D_801DA78C;
    extern u8 D_8012694C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238 *)&buf[0] = *(Blk8_8017B238 *)src;
        *(Blk8_8017B238 *)&buf[8] = *(Blk8_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018A45C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018A45C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801DA794;
        s16 *p78C = &D_801DA78C;
        *(Blk8_8017B238 *)p794 = *(Blk8_8017B238 *)&buf[0];
        *(Blk8_8017B238 *)p78C = *(Blk8_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801DAAB8 = 1;
        D_801DA71C = 0;
    }
}

// @class: struct
// @stuck: none — MATCH (74 ins)

typedef struct { s16 a, b, c, d; } SV4_8017B368;      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
typedef struct { SV4_8017B368 x, y; } Pair16;         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801DA73C;
    extern SV4_8017B368 D_801DA744;
    extern s16 D_801DA794;
    extern s16 D_801DA78C;
    extern u16 D_8018A45C;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801DA73C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801DA744;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018A45C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018A45C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801DA794) = loc0;
    (*(SV4_8017B368 *)&D_801DA78C) = loc1;
    D_801DAAB8 = 1;
    D_801DA71C = 0;
}


s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801DA73C;
    extern SV4_8017B368 D_801DA744;
    extern s16 D_801DA794;
    extern s16 D_801DA78C;
    extern u16 D_8018A45C;
    extern s16 D_801DA71C;
    extern s16 D_801DAAB8;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801DA73C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801DA744;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018A45C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018A45C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801DA794) = loc0;
    (*(SV4_8017B368 *)&D_801DA78C) = loc1;
    D_801DAAB8 = 1;
    D_801DA71C = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801DA794).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801DA794).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801DA794).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801DA78C).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801DA78C).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801DA78C).c;
}

// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @stuck: 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.

typedef struct { u8 b[8]; } Blk8_8017B614;



s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018A45C[];
    extern s16 D_801DA794;
    extern s16 D_801DA796;
    extern s16 D_801DA798;
    extern s16 D_801DA78C;
    extern s16 D_801DA78E;
    extern s16 D_801DA790;
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
        s32 a1addr = (s32)&D_8018A45C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018A45C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801DA794;
        s16 *p78C = &D_801DA78C;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801DA796;
            v798 = D_801DA798;
            v78C = *p78C;
            v78E = D_801DA78E;
            v790 = D_801DA790;
            __asm__ __volatile__("");
            D_801DAAB8 = 1;
            D_801DA71C = 0x1E;
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

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8 D_8012694C;
extern s16 D_801DA71C;
extern s16 D_801DA794;
extern s16 D_801DA796;
extern s16 D_801DA798;
extern s16 D_801DA78C;
extern s16 D_801DA78E;
extern s16 D_801DA790;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801DA71C = 0;
    D_801DA794 = (s16) D_80114F30;
    D_801DA796 = (s16) D_80114F34;
    D_801DA798 = (s16) D_80114F38;
    D_801DA78C = (s16) D_80114F24;
    D_801DA78E = (s16) D_80114F28;
    D_801DA790 = (s16) D_80114F2C;
}

extern s32 D_801151D4;
extern s16 D_801DA7AC;
extern s16 D_801DA7AE;
extern s16 D_801DA7B0;
extern s16 D_801DA7B4;
extern s16 D_801DA7B6;
extern s16 D_801DA7B8;

void func_8017B824(void) {
    D_801DA7AC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801DA7AE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801DA7B0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801DA7B4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801DA7B6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801DA7B8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}

// @class: schedule
// @stuck: none — MATCH

extern s16 D_801DA7AC;
extern s16 D_801DA7AE;
extern s16 D_801DA7B0;
extern s16 D_801DA7B4;
extern s16 D_801DA7B6;
extern s16 D_801DA7B8;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801DA7AC;
    D_80114F34 = D_801DA7AE;
    D_80114F38 = D_801DA7B0;
    D_80114F24 = D_801DA7B4;
    D_80114F28 = D_801DA7B6;
    D_80114F2C = D_801DA7B8;
}

// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801DA794), src[8..15] -> (*(S8_8017B8E8 *)&D_801DA78C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */

typedef struct { unsigned char b[8]; } S8_8017B8E8;


s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801DA794) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801DA78C) = ((S8_8017B8E8 *)src)[1];
}


// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801DA79C;
extern u16 D_801DA79E;
extern u16 D_801DA7A0;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801DA71C;
extern short D_801DA7A4;
extern short D_801DA7A6;
extern short D_801DA7A8;
extern s16 D_801DA794;
extern s16 D_801DA796;
extern s16 D_801DA798;
extern s16 D_801DA78C;
extern s16 D_801DA78E;
extern s16 D_801DA790;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801DA79C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801DA79E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801DA7A0);
    (*(s16 *)&D_801DA7A4) = buf[0];
    (*(s16 *)&D_801DA7A6) = buf[1];
    (*(s16 *)&D_801DA7A8) = buf[2];
    D_801DA794 = D_80114F30 + buf[0];
    D_801DA71C = 0;
    D_801DA796 = D_80114F34 + buf[1];
    D_801DA798 = D_80114F38 + buf[2];
    D_801DA78C = D_80114F24 + buf[0];
    D_801DA78E = D_80114F28 + buf[1];
    D_801DA790 = D_80114F2C + buf[2];
}


// @class: struct
// @stuck: none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX: 3x3 short rotation + pad + 3 long translation (offset 0x14) */

extern SV4 D_801DA73C;
extern SV4 D_801DA744;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801DA744) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801DA73C = svec;

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
    D_801DA744 = buf1;
}

// @class: struct
// @stuck: none — MATCH (65 ins)
#include "common.h"

typedef struct { s16 a, b, c, d; } SV4_8017BB34;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017BB34;



s32 func_8017BB34(s32 param_1, s32 param_2)
{
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801DA744)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801DA73C) = svec;

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
    (*(SV4_8017BB34*)&D_801DA744) = buf1;
}


// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801DA764[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801DA764;
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
extern s16 D_801DA71C;
extern s16 D_801DAAB8;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801DA71C = D_801DA71C + 1;
    if (D_801DA71C >= 0x1F) {
        D_801DAAB8 = 2;
    }
}

// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801DA71C;
extern s16 D_801DAAB8;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801DA71C = D_801DA71C + 1;
    if (0x18 < D_801DA71C) {
        func_8012A4BC();
        D_801DAAB8 = 0;
    }
    return;
}

// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801DA71C;
extern void (*D_801DA760)(void);
extern short D_801DA7A4;
extern short D_801DA7A6;
extern short D_801DA7A8;
extern s16 D_801DAAB8;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801DA71C = D_801DA71C + 1;
    if (D_801DA71C >= 0x19) {
        if (D_801DA760 != 0) {
            (*D_801DA760)();
        } else {
            D_80114F30 = D_80114F30 + D_801DA7A4;
            D_80114F34 = D_80114F34 + D_801DA7A6;
            D_80114F38 = D_80114F38 + D_801DA7A8;
            D_80114F24 = D_80114F24 + D_801DA7A4;
            D_80114F28 = D_80114F28 + D_801DA7A6;
            D_80114F2C = D_80114F2C + D_801DA7A8;
            func_8012A4BC();
        }
        D_801DAAB8 = 0;
    }
}

extern s32 (*D_8018A4FC[])(void *);

s32 func_8017BE60(void *a0) {
    return D_8018A4FC[*(u8 *)((s32)a0 + 0x4)](a0);
}

DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */

extern s32 (*D_8018A520[])(void *);

s32 func_8017BEBC(void *a0) {
    return D_8018A520[*(u16 *)((s32)a0 + 0x2)](a0);
}

// @class: schedule
// @stuck: none — MATCH (113 ins, relocation-masked). Keys: (1) one 48-byte scratch struct {in@0x00,out@0x08,dead[8]@0x10} forces frame 0x68 with in@sp+0x20/out@sp+0x28 for free; (2) SHORT loop counter (not int) defeats gcc's shift-IV strength reduction so i increments by 1 + sll/sra per use; (3) if-body store order 0x12,0x16,0x1A puts the =0 store into the w.vy load-delay slot; (4) inverted final branch (if node!=0 {...} else func_80146C3C) makes the big block fall-through (beqz).
#include "common.h"

typedef struct {
    u16 x, y, z, xpad;      /* 0x00 : in  (Pos800D20C0, padded to 8) -> sp+0x20 */
    u16 vx, vy, vz, vpad;   /* 0x08 : out (SVECTOR)                  -> sp+0x28 */
    s32 dead[8];            /* 0x10 : reserved, unaccessed           -> sp+0x30..0x4F */
} Work8017;

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);

extern u8 D_8018A508;

void func_8017BEF8(s32 param_1) {
    s32 obj = *(s32 *)(param_1 + 0x34);
    Work8017 w;
    short i;
    s32 e;
    s32 node;

    func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                  (s16)(*(u16 *)(param_1 + 0xA) - 0x10),
                  *(s16 *)(param_1 + 0xE), 0, 0);

    w.x = *(u16 *)(param_1 + 6);
    w.y = *(u16 *)(param_1 + 0xA);
    w.z = *(u16 *)(param_1 + 0xE);
    func_800D20C0(&w.x, &w.vx, 10);
    *(s16 *)(param_1 + 6) = w.x;
    *(s16 *)(param_1 + 0xE) = w.z;
    w.vy = 0;
    func_800D23D0(&w.vx);

    i = 0;
    do {
        e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                          *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE), i, 0);
        if (e != 0) {
            *(s16 *)(e + 0x12) = w.vx;
            *(s16 *)(e + 0x16) = w.vy;
            *(s16 *)(e + 0x1A) = 0;
        }
        i = i + 1;
    } while (i < 3);

    node = func_800D222C(param_1, &D_8018A508, 0xFD);
    if (node != 0) {
        *(s32 *)(param_1 + 0x20) = node;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x5D000100;
        ((void (*)(void *))func_8001CF30)((void *)node);
        *(s16 *)(node + 0x18) = 0x4000;
        *(s16 *)(node + 0x1A) = 0x200;
        *(s16 *)(param_1 + 0x16) = 0x200;
        *(s16 *)(param_1 + 0x14) = 0x1000;
        *(s16 *)(node + 0x28) = 0x240;
        *(s16 *)(node + 0x2A) = 0x180;
        *(s16 *)(node + 0x10) = w.vx;
        *(s16 *)(node + 0x12) = w.vy;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


DEFINE_func_8017C0BC()  /* dedup: shared engine-core @0x8017C0BC (src/shared) */

extern s32 (*D_8018A528[])(void *);

s32 func_8017C150(void *a0) {
    return D_8018A528[*(u16 *)((s32)a0 + 2)](a0);
}

// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_8018A514;

void func_8017C18C(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_8018A514, 0x18);
    if (r != 0) {
        *(s32 *)(a0 + 0x20) = r;
        *(u32 *)(r + 4) = *(u32 *)(r + 4) | 0x5C000140;
        func_8001CF30((void *)r);
        *(s16 *)(r + 0x10) = 0x400;
        *(s16 *)(r + 0x18) = 0x3000;
        *(s16 *)(r + 0x1A) = 0x3000;
        *(s16 *)(r + 0x28) = 0x248;
        *(s16 *)(r + 0x2A) = 0x180;
        *(s16 *)(a0 + 2) = *(s16 *)(a0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}

DEFINE_func_8017C230()  /* dedup: shared engine-core @0x8017C230 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017C294);

DEFINE_func_8017C66C()  /* dedup: shared engine-core @0x8017C66C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (126 ins)

int func_8017C710(short *param_1, short *param_2, short *param_3, int param_4) {
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


DEFINE_func_8017C908()  /* dedup: shared engine-core @0x8017C908 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017C974);

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern s32 func_8017DA08(void *a0);
extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017D840(void) {
    D_80126954 = 0x15E;
    D_8012695C = 0x258;
    D_80126968 = 0x1C2;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0x140;
    D_80126978 = 0;
    D_8012697A = 0x140;
    func_8012A018(func_8017DA08, 0);
    func_8017DA08(&D_80126948);
    func_8012A094(&D_80126948);
}

extern u8 D_8012694C;

void func_8017D8DC(void) {
    D_8012694C = 1;
}

extern u8 D_8012694C;

void func_8017D8F0(void) {
    D_8012694C = 0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017D900);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017D98C);

extern s32 (*D_8018A530[])(void *);

s32 func_8017DA08(void *a0) {
    return D_8018A530[*(u8 *)((s32)a0 + 4)](a0);
}

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8017DAEC(s32);
extern s32 *D_80126B78;

void func_8017DA44(void *arg0) {
    s32 var_v0;
    s32 var_v0_2;

    var_v0 = -func_8004787C(M2C_FIELD(D_80126B78, s16 *, 0x12));
    if (var_v0 < 0) {
        var_v0 += 0x3F;
    }
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (var_v0 >> 6);
    var_v0_2 = -func_80047948(M2C_FIELD(D_80126B78, s16 *, 0x12));
    if (var_v0_2 < 0) {
        var_v0_2 += 0x1F;
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (var_v0_2 >> 5);
    func_8017DAEC(arg0);
}

extern s32 func_8017DAEC(s32);

s32 func_8017DACC(s32 a0) {
    return func_8017DAEC(a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017DAEC);

extern s32 (*D_8018A588[])(void *);

s32 func_8017DCB0(void *a0) {
    return D_8018A588[*(u8 *)((s32)a0 + 0x15)](a0);
}

// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017DE84(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017DCEC(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017DE84, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}

extern s32 func_800167F0(s32 a0);

s32 func_8017DD3C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}

extern s32 (*D_8018A590[])(void *);

s32 func_8017DD60(void *a0) {
    return D_8018A590[*(u8 *)((s32)a0 + 0x15)](a0);
}

// @class: plumbing
// @stuck: callee func_8016EDEC is 3-arg canonical; called 2-arg via fn-ptr cast (matches func_80174784/824 precedent)
#include "common.h"

extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8017E0EC(void *arg0);

s32 func_8017DD9C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_8017E0EC, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 10;
    return 0;
}

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017DDE8(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(2);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}

extern void func_800D1EBC(void);

void func_8017DE64(void) {
    func_800D1EBC();
}

extern void (*D_8018A740[])();

void func_8017DE84(void *arg0) {
    D_8018A740[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

extern void func_8016F398(void);
M2C_UNK func_8017D900();                            /* extern */

void func_8017DEC0(void *arg0) {
    func_8016F398();
    M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    func_8017D900();
}

extern void func_80171B44(s32 *a0);
M2C_UNK func_8017D98C();                            /* extern */
extern u16 D_80126980;

void func_8017DEFC(void *arg0) {
    u16 temp_v0;

    temp_v0 = D_80126980 | 0x8000;
    D_80126980 = temp_v0;
    if (temp_v0 & 0x8000) {
        func_8017D98C();
        func_80171B44(arg0);
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

// @class: schedule
// @stuck: none — MATCH (proxy 31/31)

extern s32 func_80171B4C(s32 a0, s32 a1);
extern s32 func_800CF854(s32);
extern s32 func_8013767C(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_8014706C(void *arg0);

extern u8 D_800D5A34[];

void func_8017DF5C(int param_1)
{
    char cVar1;

    if (func_80171B4C(param_1, 0x1E) != 0) {
        if (((int (*)(void))func_800CF854)() != 0) {
            cVar1 = 4;
        } else {
            *(int *)(param_1 + 0x198) = func_8013767C(*(int *)(param_1 + 0x198));
            ((int (*)(int, int))func_80154274)(param_1, (int)&D_800D5A34);
            ((int (*)(int))func_8014706C)(param_1);
            cVar1 = *(char *)(param_1 + 0x214) + 1;
            *(short *)(param_1 + 0x20c) = 0;
        }
        *(char *)(param_1 + 0x214) = cVar1;
    }
}

// @class: other
// @stuck: none — straightforward control flow mirroring Ghidra-C; expect MATCH

extern s32 func_8016F410(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80147060(u8 *a0);

extern unsigned char D_8018A62C[];
extern unsigned char D_8018A69C[];
extern unsigned char D_8018A6E4[];

void func_8017DFD8(int param_1) {
    if (func_8016F410(0) != 0) {
        ((void (*)(int, void *))func_80154274)(param_1, &D_8018A62C);
    }
    if (func_8016F410(1) != 0) {
        ((void (*)(int, void *))func_80154274)(param_1, &D_8018A69C);
        *(short *)(param_1 + 0x20c) = 1;
    }
    if (*(short *)(param_1 + 0x20c) == 1 && (*(unsigned short *)(param_1 + 0xb8) & 0x8000) != 0) {
        *(short *)(param_1 + 0x20c) = 2;
        ((void (*)(int, void *))func_80154274)(param_1, &D_8018A6E4);
    }
    if (func_801399F0(*(int *)(param_1 + 0x198)) != 0) {
        func_80139914(*(int *)(param_1 + 0x198));
        ((void (*)(int))func_80147060)(param_1);
        *(char *)(param_1 + 0x214) = *(char *)(param_1 + 0x214) + 1;
    }
}

// @class: plumbing
// @stuck: none — MATCH (param_1 survives across func_8016F0E4 → lands in $s0; passed to func_80165770)

extern void func_8016F0E4(void);
extern void func_80165770(void);
extern void func_80175414(s32);

void func_8017E0B4(s32 param_1)
{
    func_8016F0E4();
    ((void (*)(s32))func_80165770)(param_1);
    ((void (*)(void))func_80175414)();
}

extern void (*D_8018A754[])();

void func_8017E0EC(void *arg0) {
    D_8018A754[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

// @class: plumbing
// @stuck: none — MATCH (18/18 via match_one); a0 reused across call, sh-in-delay-slot

extern void func_80171B44(s32 *a0);
extern void func_8017E170(s32 a0);

void func_8017E128(s32 a0)
{
    *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0x800;
    func_80171B44((s32 *)a0);
    func_8017E170(a0);
}

// @class: plumbing
// @stuck: none — MATCH (expected); simple call + conditional u8 increment

extern s32 func_80171B4C(s32 a0, s32 a1);

void func_8017E170(int param_1)
{
    if (func_80171B4C(param_1, 0x1E) != 0) {
        *(unsigned char *)(param_1 + 0x214) += 1;
    }
    return;
}

extern void func_8016F0E4(void);

void func_8017E1B4(void) {
    func_8016F0E4();
}

extern void (*D_8018A760[])();

void func_8017E1D4(void *arg0) {
    D_8018A760[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

s32 func_8017E210(u8 *a0) {
    s32 v = (s32)a0[0x214] + 1;
    a0[0x214] = (u8)v;
    return v;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017E224);

// @class: schedule
// @stuck: none — MATCH. Cross-jump/tail-merge of the two `p->0x214=...` sb stores defeated by
//         reading D_8012695C into a local temp first (holds $a0, forces incr into $v1 not $v0).
#include "common.h"

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_8013767C(s32 a0);
extern void func_8017D8DC(void);
extern u8 D_80078EC1;
extern u8 D_801B1720;
extern s32 D_8012695C;

void func_8017E298(void *arg0) {
    s16 temp_v0;
    void *temp_a0;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), 0x800, 4);
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a0, s16 *, 0x12) + temp_v0) & 0xFFF);
    if (temp_v0 == 0) {
        if (D_80078EC1 == 8) {
            M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C((s32) &D_801B1720);
            M2C_FIELD(arg0, u8 *, 0x214) = 0xB;
        } else {
            s32 t;
            func_8017D8DC();
            t = D_8012695C;
            M2C_FIELD(arg0, s32 *, 0x204) = 0x20;
            M2C_FIELD(arg0, s32 *, 0x208) = t;
            M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
        }
    }
}

extern s32 func_8013767C(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 D_80126958;
extern s32 D_8012695C;
extern M2C_UNK D_8018A59C;
extern M2C_UNK D_801B17AC;

void func_8017E350(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x204) - 1;
    M2C_FIELD(arg0, s32 *, 0x204) = temp_v0;
    if (temp_v0 != -1) {
        temp_v0_2 = D_80126958 + 8;
        D_80126958 = temp_v0_2;
        D_8012695C = temp_v0_2;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x204) = 0;
    M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C(&D_801B17AC);
    func_80154274(arg0, &D_8018A59C);
    M2C_FIELD(arg0, u8 *, 0x4D) = (u8) (M2C_FIELD(arg0, u8 *, 0x4D) + 1);
    M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
}

// @class: plumbing
// @stuck: none — MATCH (early-exit guard + 2 calls + struct stores + cond byte incr)

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 D_8018A5E4;
extern s32 D_8012695C;

void func_8017E3EC(s32 param_1)
{
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        ((s32 (*)(s32))func_80139914)(*(s32 *)(param_1 + 0x198));
        ((s32 (*)(s32, s32))func_80154274)(param_1, (s32)&D_8018A5E4);
        D_8012695C = *(s32 *)(param_1 + 0x208);
        *(s32 *)(param_1 + 0x204) = 0x20;
        *(unsigned char *)(param_1 + 0x214) = *(unsigned char *)(param_1 + 0x214) + 1;
    }
}

M2C_UNK func_8017F240();                            /* extern */

void func_8017E460(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x204) - 1;
    M2C_FIELD(arg0, s32 *, 0x204) = temp_v0;
    if (temp_v0 == -1) {
        func_8017F240();
        M2C_FIELD(arg0, s32 *, 0x204) = 0x40;
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

extern s32 func_8013767C(s32 a0);
extern M2C_UNK D_801B17F0;

void func_8017E4B4(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x204) - 1;
    M2C_FIELD(arg0, s32 *, 0x204) = temp_v0;
    if (temp_v0 == -1) {
        M2C_FIELD(arg0, u8 *, 0x4D) = (u8) (M2C_FIELD(arg0, u8 *, 0x4D) - 1);
        M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C(&D_801B17F0);
        M2C_FIELD(arg0, s32 *, 0x204) = 0x20;
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern u16 D_80126970;
extern u16 D_80126974;
extern s16 D_80126976;
extern s16 D_8012697A;

void func_8017E51C(void *arg0) {
    s16 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v1;
    void *temp_a0;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), 0x400, 4);
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a0, s16 *, 0x12) + temp_v0) & 0xFFF);
    if (temp_v0 == 0) {
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x204);
    if (((temp_v0_2 == 0) || (M2C_FIELD(arg0, s32 *, 0x204) = (s32) (temp_v0_2 - 1), temp_v0_3 = D_80126970 - 4, temp_v1 = D_80126974 - 4, D_80126970 = temp_v0_3, D_80126976 = temp_v0_3, D_80126974 = temp_v1, D_8012697A = temp_v1, (M2C_FIELD(arg0, s32 *, 0x204) == 0))) && (temp_v0 == 0)) {
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

// @class: plumbing
// @stuck: none — MATCH expected; mirrors DEFINE_func_80160FE0 idiom (s0=a0 saved across 3 calls)
#include "common.h"

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern s32 func_8013767C(s32 a0);
extern u8 D_801B1848;

void func_8017E604(s32 a0) {
    s32 s0 = a0;
    if (func_801399F0(*(s32 *)(s0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(s0 + 0x198));
        *(s32 *)(s0 + 0x198) = func_8013767C((s32)&D_801B1848);
        *(u8 *)(s0 + 0x214) = *(u8 *)(s0 + 0x214) + 1;
    }
}

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);

void func_8017E668(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    }
}

// @class: plumbing
// @stuck: none — MATCH (expected)

extern void func_8017D8F0(void);
extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017E6BC(s32 param_1)
{
    ((void (*)(s32))func_8017D8F0)(param_1);
    ((void (*)(s32))func_8016F0E4)(param_1);
    ((void (*)(s32))func_80165770)(param_1);
}

// @class: plumbing
// @stuck: none — MATCH (simple stub; param_1 in $s0 across calls)

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017E6F4(s32 param_1) {
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        func_80139914(*(s32 *)(param_1 + 0x198));
        ((void (*)(s32))func_8016F0E4)(param_1);
        ((void (*)(s32))func_80165770)(param_1);
    }
    return;
}

extern void (*D_8018A790[])();

void func_8017E748(void *arg0) {
    D_8018A790[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

extern s32 func_8013767C(s32 a0);
extern void func_8017D8DC(void);
extern s16 D_80126976;
extern s16 D_8012697A;
extern M2C_UNK D_801B19C0;

void func_8017E784(void *arg0) {
    func_8017D8DC();
    D_80126976 = 0;
    D_8012697A = 0;
    M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C(&D_801B19C0);
    M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
}

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);

void func_8017E7DC(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    }
}

// @class: plumbing
// @stuck: none — MATCH (simple 3-call stub; param saved in $s0 across first call)
extern void func_8017D8F0(void);
extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017E830(s32 param_1)
{
    ((s32 (*)(void))func_8017D8F0)();
    ((s32 (*)(s32))func_8016F0E4)(param_1);
    ((s32 (*)(s32))func_80165770)(param_1);
}

extern void (*D_8018A79C[])();

void func_8017E868(void *arg0) {
    D_8018A79C[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

// @class: schedule
// @stuck: none — MATCH (32/32). Target reloads $a0 from $s0 before the first call (filling the jal
//   delay slot with `addu $a0,$s0,$zero`); gcc otherwise keeps param_1 live in $a0 and the slot stays a
//   nop. A zero-code `__asm__ __volatile__("" ::: "$4")` clobber barrier before the call forces the reload.

extern s32 D_801270D4;
extern s32 func_80172658(s32 *a0);
extern void func_80171B44(s32 *a0);

void func_8017E8A4(u16 *param_1)
{
    s32 cVar1;

    if (1 < (u16)(*param_1 - 0x19)) {
        if (D_801270D4 < 0x1e) {
            __asm__ __volatile__("" ::: "$4");
            if (((s32 (*)(u16 *))func_80172658)(param_1) == 0) {
                return;
            }
            *(u16 *)(*(s32 *)(param_1 + 0x10) + 0x12) = 0;
            ((void (*)(u16 *))func_80171B44)(param_1);
            cVar1 = *(u8 *)(param_1 + 0x10a) + 1;
        } else {
            cVar1 = 4;
        }
        *(s8 *)(param_1 + 0x10a) = cVar1;
    }
}

// @class: loose-typing
// @stuck: none — MATCH (unsigned short store forces ori vs sign-extending li for 0xc040)

extern s32 func_80171B4C(s32 a0, s32 a1);

void func_8017E924(int param_1)
{
    if (func_80171B4C(param_1, 8) != 0) {
        *(int *)(param_1 + 0x204) = 0x20;
        *(unsigned short *)(param_1 + 0xac) = 0xc040;
        *(unsigned short *)(param_1 + 0xaa) = 0xc040;
        *(unsigned char *)(param_1 + 0x214) = *(unsigned char *)(param_1 + 0x214) + 1;
    }
    return;
}

// @class: loose-typing
// @stuck: none — MATCH (u16 store forces ori/zero-extend of 0xC040; s16 gave addiu/li -16320)

extern s32 func_80172664(s32 *a0);

void func_8017E974(s32 param_1)
{
    if (((s32 (*)(void))func_80172664)() != 0) {
        *(u16 *)(param_1 + 0xac) = 0xc040;
        *(u16 *)(param_1 + 0xaa) = 0xc040;
    } else {
        *(u8 *)(param_1 + 0x214) = *(u8 *)(param_1 + 0x214) + 1;
    }
}

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);

void func_8017E9C0(void *arg0) {
    s32 temp_v0;
    void *temp_a0;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), 0x800, 4);
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a0, s16 *, 0x12) + temp_v0) & 0xFFF);
    if ((temp_v0 << 0x10) == 0) {
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

// @class: plumbing
// @stuck: none — MATCH (expected): param saved to $s0 across first call, passed to second

extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017EA2C(int param_1)
{
    ((void (*)(int))func_8016F0E4)(param_1);
    ((void (*)(int))func_80165770)(param_1);
}

extern s32 (*D_8018A7B0[])();

s32 func_8017EA5C(s16 *a0) {
    return D_8018A7B0[(u16)a0[1]]();
}

extern void func_8012AD44(s32 *a0, s16 a1);

void func_8017EA98(s32 *a0) {
    a0[7] = 0x10;
    func_8012AD44(a0, 1);
}

// @class: other
// @stuck: none — MATCH (27 ins, byte-identical via match_one relocation-masked)
extern int rand(void);
extern void func_8017EB2C(int a, int b);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8017EAC0(int param_1)
{
    int i;

    i = 0;
    do {
        i = i + 1;
        func_8017EB2C(rand(), *(int *)(param_1 + 0x1C));
    } while (i < 4);
    if (func_8012BEE8(param_1) == 1) {
        ((void (*)(int))func_8012C218)(param_1);
    }
}

// @class: regalloc-order
// @stuck: none — MATCH (69 ins, relocation-masked)

extern s32 D_80126B58;
extern u8 *func_8012913C(s32 a0);
extern int rand(void);

void func_8017EB2C(int param_1, int param_2)
{
    s32 base = (s32)&D_80126B58;
    u8 *p;
    s32 s1, v;
    if ((param_1 & 1) != 0) {
        p = func_8012913C(2);
    } else {
        p = func_8012913C(1);
    }
    if (p != 0) {
        int t;
        register s32 d __asm__("$5");
        register s32 r __asm__("$2");
        t = rand();
        s1 = t - (t / 256) * 256;
        r = rand() % 640;
        d = (s32)*(u16 *)(base + 0xe) - 0x140;
        __asm__("" : "=r"(d) : "0"(d));
        d += r;
        *(s16 *)(p + 0xe) = d;
        if ((param_2 & 1) != 0) {
            *(s16 *)(p + 6) = s1 + 0x7a;
            v = (s32)*(u16 *)(base + 0xa) - 0xe0;
        } else {
            *(s16 *)(p + 6) = s1 - 0xf8;
            v = (s32)*(u16 *)(base + 0xa) - 0xc0;
        }
        *(s16 *)(p + 0xa) = v;
        *(s16 *)(p + 0x36) = (s32)*(u16 *)(base + 0xa) - 0x50;
    }
}

extern s32 (*D_8018A7B8[])();

s32 func_8017EC40(s16 *a0) {
    return D_8018A7B8[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017EC7C);

extern s32 (*D_8018A7F0[])();

s32 func_8017ED4C(s16 *a0) {
    return D_8018A7F0[(u16)a0[1]]();
}

s32 rand();                                         /* extern */

void func_8017ED88(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (rand() + 0xC000);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (((rand() & 0x3FFF) * 2) - 0x4000);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (((rand() & 0x3FFF) * 2) - 0x4000);
}

extern s32 (*D_8018A7F8[])();

s32 func_8017EDE4(s16 *a0) {
    return D_8018A7F8[(u16)a0[1]]();
}

extern s32 func_8012AD50(void *a0);

void func_8017EE20(void *a0) {
    *(s32 *)((s32)a0 + 0x1C) = 1;
    func_8012AD50(a0);
}

// @class: other
// @stuck: none — MATCH (expect clean codegen; rand result held in $s0 across 2nd rand call)
extern int rand(void);
extern void func_8017EB2C(int a, int b);
extern s32 func_8012BEE8(s32 a0);

void func_8017EE44(int param_1)
{
    int r;

    if ((*(unsigned int *)(param_1 + 0x1c) & 0xf) == 0) {
        r = rand();
        func_8017EB2C(r, *(unsigned int *)(param_1 + 0x1c) & 1);
    }
    if (func_8012BEE8(param_1) != 0) {
        *(int *)(param_1 + 0x1c) = 0x30;
        r = rand();
        func_8017EB2C(r, rand());
    }
}

// @class: plumbing
// @stuck: none — MATCH expected; base D_8018A7C0 materialized + index*0xc added as integer arg

#include "common.h"

extern s32 rand(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8017EC7C(s32 a0);
extern u8 D_8018A7C0;

void func_8017EEC0(s32 param_1) {
    s32 iVar2 = *(s32 *)(param_1 + 0x20);

    func_8001CC3C(iVar2, (rand() & 3) * 0xc + (s32)&D_8018A7C0, 0x3F0, 0x100);
    *(u8 *)(iVar2 + 0x27) = 0x9D;
    *(u16 *)(iVar2 + 0x1A) = 0x1000;
    *(u16 *)(iVar2 + 0x18) = 0x1000;
    func_8017EC7C(param_1);
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


s32 func_8017EF50(s32 param_1)
{
    extern void func_8012931C(struct vec *a0);
    extern void func_801292C8(u8 *a0);

    register unsigned short c __asm__("$5");
    register int d __asm__("$4");
    register int g __asm__("$6");
    int a;
    int e;
    ((void (*)(int))func_8012931C)(((int)param_1));
    a = *(int *)(((int)param_1) + 0x10);
    c = *(unsigned short *)(((int)param_1) + 0x34);
    e = *(int *)(((int)param_1) + 0x2c);
    __asm__ __volatile__("" : : "r"(a));
    d = *(int *)(((int)param_1) + 0x30);
    {
        unsigned short cp1 = c + 1;
        *(int *)(((int)param_1) + 0x10) = a + e;
        *(unsigned short *)(((int)param_1) + 0x34) = cp1;
    }
    *(int *)(((int)param_1) + 8) = *(int *)(((int)param_1) + 8) + 0x10000;
    *(int *)(((int)param_1) + 0x18) = *(int *)(((int)param_1) + 0x18) + d;
    g = *(short *)(((int)param_1) + 0xa);
    if (g > *(short *)(((int)param_1) + 0x36)) {
        ((void (*)(int))func_801292C8)(((int)param_1));
    } else if (*(short *)(((int)param_1) + 0x34) == 8) {
        *(int *)(((int)param_1) + 0x2c) = -*(int *)(((int)param_1) + 0x2c);
        *(int *)(((int)param_1) + 0x30) = -*(int *)(((int)param_1) + 0x30);
        *(int *)(((int)param_1) + 0x14) = -*(int *)(((int)param_1) + 0x14);
    } else if (*(short *)(((int)param_1) + 0x34) == 0x10) {
        *(short *)(((int)param_1) + 0x34) = 0;
        *(int *)(((int)param_1) + 0x14) = -*(int *)(((int)param_1) + 0x14);
    }
}


// @class: other
// @stuck: none — MATCH expected (s0=*(p+0x20) and s1=p both call-crossing; address of D_8018A7C0 materialized + (rand()&3)*0xc)

extern int rand(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017ED88(void *arg0);

extern u8 D_8018A7C0;

void func_8017F024(int param_1)
{
    s32 p;

    p = *(s32 *)(param_1 + 0x20);
    func_8001CB6C((u8 *)p, (s32)&D_8018A7C0 + (rand() & 3) * 0xc, 0x3F0, 0x100);
    *(u8 *)(p + 0x27) = 0x9D;
    *(s16 *)(p + 0x1A) = 0x1000;
    *(s16 *)(p + 0x18) = 0x1000;
    func_8017ED88((void *)param_1);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}

struct vec;
extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_8017F0B4(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x200;
    func_8012931C((struct vec *)a0);
    if (*(s16 *)(a0 + 0xA) > *(s16 *)(a0 + 0x36)) {
        func_801292C8(a0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017F114);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017F240);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017F290);

extern s32 (*D_8018A87C[])();

s32 func_8017F3E8(s16 *a0) {
    return D_8018A87C[(u16)a0[1]]();
}

extern s32 (*D_8018A89C[])();

s32 func_8017F424(s16 *a0) {
    return D_8018A89C[(u16)a0[1]]();
}

// @class: remat
// @stuck: none — MATCH (match_one 87/87). Levers: (1) block-scoped `s32 *pCC=&D_801270CC;` INSIDE
//   the ==4 branch forces gcc to CSE/HOLD the symbol address in a reg for the load+conditional store
//   (target: lui;addiu;lw 0($v1) ... sw 0($v1)) instead of %lo-folding each access; declaring it at
//   function top materializes it too early (before the bne) — must be block-scoped so it builds lazily.
//   (2) (s16)D_80126B66 on the u16 canonical folds to lh. (3) extern short D_8018A8FC[]; D_8018A8FC[idx]
//   %lo-folds the indexed s16 load.

extern s32 D_801270CC;
extern s32 D_801270D4;
extern short D_8018A8FC[];
extern int D_8018A8F8;
extern u16 D_80126B66;

extern void func_8017F5BC(int param_1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017F460(int param_1)
{
    int iVar1;

    if (*(unsigned char *)(param_1 + 0x70) == 4) {
        s32 *pCC = &D_801270CC;
        if (*pCC == 0 && (*(unsigned short *)(param_1 + 0x5c) & 1) != 0) {
            if (D_801270D4 == 0) {
                D_801270D4 = 1;
            }
            *pCC = 3;
            *(unsigned short *)(param_1 + 0x5c) = 0;
        }
        if (1 < D_801270CC) {
            if ((*(unsigned short *)(param_1 + 0x5c) & 1) != 0 && D_801270D4 == 0) {
                D_801270D4 = 1;
            }
            if (D_8018A8FC[(int)((unsigned int)*(unsigned short *)(param_1 + 0x70) << 0x10) >> 0x18] <= D_801270D4) {
                func_8017F5BC(param_1);
                func_8002D4C8(0x495, 0);
            }
        }
    } else {
        iVar1 = (int)(s16)D_80126B66 - (int)*(short *)(param_1 + 0xe);
        if (iVar1 < 0) {
            iVar1 = -iVar1;
        }
        if (iVar1 < D_8018A8F8) {
            func_8017F5BC(param_1);
        }
    }
}

// @class: regalloc-order
// @stuck: none — MATCH (54 ins, relocation-masked)

extern s32 func_8012C51C(void *a0, s32 a1);

void func_8017F5BC(int param_1)
{
    int iVar1;
    int c70;
    register short vf4 __asm__("$3");
    register unsigned short v5c __asm__("$2");
    struct buf_8017F5BC sp;

    *(short *)(param_1 + 2) = 2;
    *(short *)(param_1 + 0x34) = 0;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    *(int *)(param_1 + 0xe0) = 0x100000;
    *(int *)(param_1 + 0xe4) = 0x40000;
    *(int *)(param_1 + 0x1c) = 0x10;
    c70 = *(char *)(param_1 + 0x70);
    *(int *)(param_1 + 0xdc) = 0;
    v5c = *(unsigned short *)(param_1 + 0x5c) & 0x73ff;
    *(unsigned short *)(param_1 + 0x5c) = v5c;
    __asm__ __volatile__("");
    if (c70 != 4) {
        sp.f0 = *(short *)(param_1 + 6) + 0xf0;
        sp.f2 = *(short *)(param_1 + 10);
        vf4 = *(short *)(param_1 + 0xe) + 0x20;
        sp.f6 = 0x2f;
        sp.f8 = 0x600;
        sp.fa = 0;
        sp.f10 = 0;
        sp.fe = 0;
        sp.f4 = vf4;
        iVar1 = ((int (*)(int, int))func_8012C51C)((int)&sp, param_1);
        if (iVar1 != 0) {
            *(short *)(*(int *)(iVar1 + 0x20) + 0x12) =
                *(short *)(*(int *)(param_1 + 0x20) + 0x12);
        }
    }
    return;
}

extern s32 func_8012C588(s32 a0, s32 a1);

void func_8017F694(void *arg0) {
    M2C_FIELD(arg0, s16 *, 2) = 3;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x10) = 0x400;
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0xCC00);
    func_8012C588(0x25, 0);
}

extern s32 (*D_8018A904[])();

s32 func_8017F6D8(s16 *a0) {
    return D_8018A904[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017F714);

// @class: struct
// @stuck: none — MATCH (26 ins)

extern void (*D_8018A934[])(void);
extern s32 func_8012B4B8(s32 a0);
extern s32 func_8012C0EC(s32 *a0);

void func_8017F780(s32 *arg0) {
    D_8018A934[*(u16 *)((s32)arg0 + 2)]();
    func_8012B4B8((s32)arg0);
    if (*(u16 *)arg0 != 0) {
        ((s32 (*)(s32))func_8012C0EC)((s32)arg0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017F7E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017FAAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8017FD14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", listCdBuffer);

// @class: struct
// @stuck: none — MATCH (73 ins). §18 array %lo-fold (u8 base[] + byte-offset cast) for the
//   D_8018A940/942/944 indexed halfword reads; two-pseudo (arg=iVar3) hoists `move a0,v0`
//   before the branch; dead int[4] local reserves the 0x28 frame (16 unused bytes).
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32, void *);
extern int rand(void);
extern void *D_801D20B4;
extern u8 D_8018A800[];
extern u8 D_8018A940[];
extern u8 D_8018A942[];
extern u8 D_8018A944[];

void func_801800F8(int param_1) {
    int iVar3;
    int arg;
    u16 tmp;
    int sp10[4]; /* 16-byte stack local (dead in final codegen) -> 0x28 frame */

    iVar3 = ((s32 (*)(void))func_8012C1B8)();
    arg = iVar3;
    *(int *)(param_1 + 0x20) = iVar3;
    if (iVar3 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001C214)(arg, &D_801D20B4);
        func_8012A828(param_1, D_8018A800);
        *(u8 *)(param_1 + 0x100) = *(u8 *)(param_1 + 0x70) & 1;
        *(u16 *)(param_1 + 0xfe) = rand() & 0x3f;
        *(u16 *)(param_1 + 0xfc) = rand() & 0x3f;
        *(u16 *)(param_1 + 6) = *(u16 *)(D_8018A940 +
            ((int)((u32)*(u16 *)(param_1 + 0x70) << 16) >> 24) * 0x10 +
            *(u8 *)(param_1 + 0x100) * 8);
        *(u16 *)(param_1 + 0xa) = *(u16 *)(D_8018A942 +
            ((int)((u32)*(u16 *)(param_1 + 0x70) << 16) >> 24) * 0x10 +
            *(u8 *)(param_1 + 0x100) * 8);
        tmp = *(u16 *)(D_8018A944 +
            ((int)((u32)*(u16 *)(param_1 + 0x70) << 16) >> 24) * 0x10 +
            *(u8 *)(param_1 + 0x100) * 8);
        *(u16 *)(param_1 + 2) = 1;
        *(int *)(param_1 + 0x1c) = 0x1e;
        *(u16 *)(param_1 + 0xe) = tmp;
    }
}

extern s32 (*D_8018AA1C[])();

s32 func_8018021C(s16 *a0) {
    return D_8018AA1C[(u16)a0[1]]();
}

extern s32 (*D_8018AA24[])();

s32 func_80180258(s16 *a0) {
    return D_8018AA24[(u16)a0[1]]();
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_80180294(void *a0) {
    u16 v0 = *(u16 *)((s32)a0 + 0x2);
    *(s32 *)((s32)a0 + 0x1C) = 0x96;
    *(u16 *)((s32)a0 + 0x2) = v0 + 1;
    func_8002D4C8(0x401, 0);
}

// @class: plumbing
// @stuck: none — MATCH (simple stub: short-circuit && guard + two tail calls)

extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017F114(void);
extern void func_8017F290(void);

void func_801802CC(s32 *param_1)
{
    if (param_1[7] != 0 && ((s32 (*)(void))func_8012BEE8)() != 0) {
        func_8002D4C8(0xD, 0x401);
    }
    func_8017F114();
    func_8017F290();
}

// @class: other
// @stuck: none — MATCH (straight reconstruction, single $s0 call-crossing local)
extern s32 func_8012CE2C(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018031C(int param_1)
{
    short sVar2;

    if (((int (*)(void))func_8012CE2C)() == 0) {
        func_8012CBCC(param_1);
    }
    sVar2 = *(short *)(param_1 + 0x84) + 1;
    *(short *)(param_1 + 0x84) = sVar2;
    if ((*(short *)(param_1 + 0xdc) != *(short *)(param_1 + 6)) ||
        (*(short *)(param_1 + 0xde) != *(short *)(param_1 + 0xe))) {
        if (0xf < sVar2) {
            func_8002D4C8(0x485, 0);
            *(short *)(param_1 + 0x84) = 0;
        }
        *(short *)(param_1 + 0xdc) = *(short *)(param_1 + 6);
        *(short *)(param_1 + 0xde) = *(short *)(param_1 + 0xe);
    }
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801803B0);

// @class: regalloc-order
// @stuck: none — MATCH

extern s32 func_8012BEE8(s32 a0);
extern int func_8012D714(int, int);
extern void func_8017F694(void *arg0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern volatile unsigned short D_80126B96;

void func_8018047C(int param_1)
{
    int iVar1;

    if ((*(char *)(param_1 + 0x70) == 4) || (iVar1 = ((int (*)(void))func_8012BEE8)(), iVar1 != 0)) {
        register int sum __asm__("$3");
        sum = *(int *)(param_1 + 0xe0);
        sum += *(int *)(param_1 + 0xe4);
        *(int *)(param_1 + 0xdc) += sum;
        *(int *)(param_1 + 0xe0) = sum;
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) = *(unsigned short *)(param_1 + 0xde);
        if (0x3ff < *(short *)(param_1 + 0xde)) {
            if (*(unsigned short *)(param_1 + 0x34) == 0 &&
                (iVar1 = func_8012D714(param_1, 2), iVar1 != 0)) {
                D_80126B96 = 0x4002;
            }
            if (2 <= *(unsigned short *)(param_1 + 0x34)) {
                ((void (*)(int))func_8017F694)(param_1);
            } else {
                register int cnt __asm__("$4");
                if (*(unsigned short *)(param_1 + 0x34) == 0) {
                    func_8002D4C8(0x487, 0);
                }
                cnt = *(unsigned short *)(param_1 + 0x34) + 1;
                *(int *)(param_1 + 0xdc) = 0x4000000;
                *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) | 0xcc00;
                *(int *)(param_1 + 0xe0) = -(*(int *)(param_1 + 0xe0) >> 1);
                *(unsigned short *)(param_1 + 0x34) = cnt;
            }
        }
    }
}

void func_80180588(void) {
}

// @class: regalloc-order
// @stuck: none — MATCH (70 ins). Twin of matched func_801807B8 + 0x70==4 branching. Two §17 levers: (1) memory barrier between the 0x5c store and the *(p+0x20+0x10)=0 store stops gcc folding the if/else 0xc800 into the bne delay slot and keeps the merged value in $v0 (the missing-instruction class); (2) pin uVar3 (the D_8018A8x symbol selected by the branch, OR'd with 0x40000000 for the 0x58 store) to $v0 so the OR is `or $v0,$v0($v0=sym),$v1(const)` — natural alloc put the symbol in $v1.

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);

extern int D_801D15C4;
extern int D_801D1CBC;
extern int D_8018A8A4;
extern int D_8018A8B4;
extern int D_8018A8C4;
extern M2C_UNK D_80186E48;

void func_80180590(int param_1)
{
    int iVar2;
    register unsigned int uVar3 __asm__("$2");
    int uVar5;
    int uVar6;
    unsigned short uVar1;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        int ppuVar4;
        ppuVar4 = (int)&D_801D15C4;
        if (*(char *)(param_1 + 0x70) == 4) {
            ppuVar4 = (int)&D_801D1CBC;
        }
        ((void (*)(int, int))func_8001C214)(iVar2, ppuVar4);
        if (*(char *)(param_1 + 0x70) != 4) {
            uVar5 = 0x168;
            uVar3 = (int)&D_8018A8A4;
            uVar6 = 0x140;
        } else {
            uVar5 = 0x7fff;
            uVar6 = 0x7fff;
            uVar3 = (int)&D_8018A8B4;
        }
        *(unsigned int *)(param_1 + 0x58) = uVar3 | 0x40000000;
        func_8001D0E8(*(int *)(param_1 + 0x20), uVar5, uVar6);
        *(int *)(param_1 + 0x78) = (int)&D_8018A8C4;
        *(char *)(param_1 + 0x75) = 4;
        func_8012A828(param_1, &D_80186E48);
        *(short *)(param_1 + 2) = 1;
        if (*(char *)(param_1 + 0x70) == 4) {
            uVar1 = *(unsigned short *)(param_1 + 0x5c) | 0x8000;
        } else {
            uVar1 = 0xc800;
        }
        *(unsigned short *)(param_1 + 0x5c) = uVar1;
        __asm__ __volatile__("" ::: "memory");
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
        func_8012B2CC(param_1);
    }
}

extern s32 D_801270C8;
extern void func_8017F714(void);

void func_801806A8(void) {
    if (D_801270C8 == 1) {
        func_8017F714();
    }
}

// @class: other
// @stuck: none — MATCH (56 ins). D_80126B96 reloaded between two stores => volatile u16; signed-short*0x10 via int temp forces lh (not lhu)

extern void func_8012CC1C(s32 arg0, s32 arg1);
extern int func_8012D714(int, int);
extern void func_8002D4C8(s32 a0, s32 a1);

extern unsigned char D_8018A92C[];
extern int D_8018A924;
extern volatile unsigned short D_80126B96;

void func_801806D8(int param_1) {
    short sVar1;
    int iVar2;

    ((int (*)(int, void *))func_8012CC1C)(param_1, &D_8018A92C);
    if (*(int *)(param_1 + 0x18) < -D_8018A924) {
        *(int *)(param_1 + 0x18) = -D_8018A924;
    }
    if (0x600000 < *(int *)(param_1 + 0x14)) {
        *(int *)(param_1 + 0x14) = 0x600000;
    }
    iVar2 = *(short *)(param_1 + 0x1a) * 0x10;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) - iVar2;
    if (func_8012D714(param_1, 1) != 0) {
        D_80126B96 = 2;
        D_80126B96 = D_80126B96 | 0x4000;
    }
    sVar1 = *(short *)(param_1 + 0x84) + 1;
    *(short *)(param_1 + 0x84) = sVar1;
    if (sVar1 < 0x10) {
        return;
    }
    func_8002D4C8(0x48a, 0);
    *(short *)(param_1 + 0x84) = 0;
}

// @class: other
// @stuck: none — straight if/else mirroring Ghidra-C; expect MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B030(u8 *a0);
extern void func_8012A828(s32 a0, void *a1);

extern int D_801D100C;
extern unsigned char D_8018A914[];
extern M2C_UNK D_80186E48;
extern s32 D_801270C8;

void func_801807B8(int param_1) {
    int iVar1;

    iVar1 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(iVar1, &D_801D100C);
        func_8001D0E8(*(int *)(param_1 + 0x20), 0x140, 0xF0);
        *(int *)(param_1 + 0x58) = (int)&D_8018A914 | 0x40000000;
        *(short *)(param_1 + 0x5C) = 0x800;
        ((int (*)(int))func_8012B030)(param_1);
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) - 0x200000;
        *(int *)(param_1 + 0xC) = *(int *)(param_1 + 0xC) - 0x200000;
        func_8012A828(param_1, &D_80186E48);
        *(short *)(param_1 + 2) = 1;
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = 0;
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) = 0;
        D_801270C8 = 0;
    }
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_80180898(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xFC);
    if (temp_v0 != 0) {
        temp_v0_2 = temp_v0 - 1;
        M2C_FIELD(arg0, s16 *, 0xFC) = temp_v0_2;
        if ((temp_v0_2 << 0x10) == 0) {
            func_8002D4C8(0xD, 0x401);
        }
    }
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_801808DC(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 1;
    *(s16 *)((s32)a0 + 0xFC) = 0x96;
    func_8002D4C8(0x401, 0);
}

extern void func_80180930(void);

void func_80180910(void) {
    func_80180930();
}

// @class: regalloc-order
// @stuck: none — MATCH

extern u32 D_801DA9AC;
extern u16 D_8018AA2C[];
extern u16 D_801DA9E8[];
extern s32 D_8018AA4C;

extern void func_800183E0(s32 a0);

void func_80180930(void)
{
    u32 i;
    u16 *p;
    u32 base;
    u16 *tbl;

    i = 0;
    tbl = D_8018AA2C;
    base = D_801DA9AC >> 8;
    p = D_801DA9E8;
    do {
        *p = tbl[(base + i) & 0xF] | 0x8000;
        i = i + 1;
        p = p + 1;
    } while (i < 0x10);
    func_800183E0((s32)&D_8018AA4C);
    D_801DA9AC = D_801DA9AC + 0x100;
}

// @class: regalloc-order
// @stuck: none — MATCH (relocation-masked, 70 ins). pins $s0/$s1 + precomputed a0v anchored in a zero-byte barrier fix the prologue schedule.

extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 ratan2(s32, s32);
extern void func_8012B0B4(SVEC *, s32, s32);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012ADE4(u8 *a0);

s32 func_801809BC(s32 param_1, s32 param_2)
{
    register s32 p1 __asm__("$16") = param_1;
    register s32 p2 __asm__("$17") = param_2;
    SVEC in;
    SVEC out;
    SVEC buf;
    s32 d;
    s32 ang;
    u16 px, pz;
    s32 a0v;

    a0v = p1 + 4;
    __asm__ __volatile__("" : : "r"(p2), "r"(a0v));
    if (((s32 (*)(s32, s32))func_8012BC60)(a0v, p2 + 4) >= 0x1000) {
        return 0;
    }
    ang = ratan2((s32)*(s16 *)(p1 + 0xe) - (s32)*(s16 *)(p2 + 0xe),
                 (s32)*(s16 *)(p2 + 6) - (s32)*(s16 *)(p1 + 6));
    func_8012B0B4(&buf, (ang - 0x400) & 0xfff, 0x41);
    d = *(s32 *)&buf;
    px = *(u16 *)(p2 + 6);
    out.vx = px;
    out.vy = *(u16 *)(p2 + 0xa);
    pz = *(u16 *)(p2 + 0xe);
    out.vz = pz;
    out.vx = px + d;
    out.vz = pz + (d >> 16);
    in.vx = *(u16 *)(p1 + 0x3a);
    in.vy = *(u16 *)(p1 + 0x3e);
    in.vz = *(u16 *)(p1 + 0x42);
    if ((((s32 (*)(SVEC *, SVEC *, s32))func_8012CEB0)(&in, &out, 0) & 0x2000) == 0) {
        ((void (*)(s32))func_8012ADE4)(p1);
        return 1;
    }
    *(s16 *)(p1 + 6) = out.vx;
    *(s16 *)(p1 + 0xa) = out.vy;
    *(s16 *)(p1 + 0xe) = out.vz;
    return 1;
}

// @class: struct
// @stuck: none — MATCH expected (modeled on byte-proven DEFINE_func_8012E504 idiom: D_801202A0 base, 0x6480 end, 0x10C stride for-loop)

extern u8 D_801202A0[];
extern s32 func_801809BC(s32 a0, s32 a1);
extern s32 func_8012AE00(s32 a0);

void func_80180AD4(s32 a0) {
    s32 p;
    s32 end;
    s32 v;
    v = *(u16 *)a0;
    p = (s32)D_801202A0;
    end = (s32)D_801202A0 + 0x6480;
    for (; p != end; p += 0x10C) {
        if (p != a0) {
            if (*(u16 *)p == v) {
                if (func_801809BC(a0, p) != 0) {
                    break;
                }
            }
        }
    }
    ((void (*)(s32))func_8012AE00)(p);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80180B64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80180C90);

extern s16 D_8018AACC;
extern s16 D_8018AAD0;
extern u16 D_80126B5E;
extern s32 func_80013478(s32 a0, s32 a1);
extern s32 ratan2(s32, s32);
s32 func_80180F10(s32 param_1, s32 param_2) {
    s32 local_20[2] = {0x3c100, 0x51000};
    s32 iVar1;
    s32 iVar2;
    if ((s32)((u32)*(u16 *)(param_1 + 0x70) << 0x10) >> 0x18 == 4) {
        iVar1 = ((s32 (*)(s32, void *))func_80013478)(param_1 + 4, &D_8018AACC);
        if (param_2 == 1) {
            iVar2 = ratan2((s32)*(s16 *)(param_1 + 0xe) - (s32)D_8018AAD0,
                           (s32)D_8018AACC - (s32)*(s16 *)(param_1 + 6));
            if ((((u32)iVar2 - 0x400U) & 0xfff) - 0x381 < 0xff && 0x2df < (*(s16 *)&D_80126B5E) &&
                0x3c100 < iVar1) { return 1; }
        }
        if (local_20[param_2] < iVar1 && *(s32 *)(param_1 + 0xe8) < iVar1) {
            *(s32 *)(param_1 + 0xe8) = iVar1; return 1;
        }
        *(s32 *)(param_1 + 0xe8) = iVar1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8018103C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80181948);

// @class: plumbing
// @stuck: none — MATCH expected; simple param-survives-call store sequence

extern void func_8012A828(s32 a0, void *a1);
extern char D_801B0118[];

void func_80181B58(int param_1)
{
    *(short *)(param_1 + 2) = 2;
    *(short *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, &D_801B0118);
    *(int *)(param_1 + 0x1c) = 0x14;
}

// @class: plumbing
// @stuck: none — MATCH expected; param_1 survives call in $s0 naturally (single global allocno)

extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801B0D50;

void func_80181B9C(s32 param_1) {
    *(s16 *)(param_1 + 2) = 2;
    *(s16 *)(param_1 + 0x34) = 3;
    func_8012A828(param_1, &D_801B0D50);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80181BE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80181F08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801820DC);

void func_80182254(s32 a0) {
    *(s16 *)(a0 + 0x2) = 4;
    *(s16 *)(a0 + 0x98) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80182268);

void func_801822E4(u8 *a0) {
    *(s16 *)(a0 + 0x2) = 0xC;
    *(s32 *)(a0 + 0x1C) = 6;
    *(s16 *)(a0 + 0x5C) = 0;
}

void func_801822FC(void *a0) {
    u16 v = *(u16 *)((s32)a0 + 0x70);
    *(s16 *)((s32)a0 + 0x2) = 5;
    *(s16 *)((s32)a0 + 0x98) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x10;
    if ((s8)(v >> 8) == 5) {
        *(u16 *)((s32)a0 + 0x70) = (v & 0xFF) | 0x100;
    }
}

// @class: other
// @stuck: none — MATCH (26 ins, match_one confirmed)
extern void func_8012A828(int, void *);
extern void func_8012B2CC(int);
extern void func_8012B23C(int);
extern void func_8012B14C(s32 a0, s32 a1);
extern unsigned char D_801B09D0;
extern unsigned char D_8018AAEC;

void func_80182338(int param_1) {
    *(short *)(param_1 + 0x5c) = 0;
    *(short *)(param_1 + 0x2) = 6;
    func_8012A828(param_1, ((unsigned char *)&D_801B09D0));
    func_8012B2CC(param_1);
    func_8012B23C(param_1);
    ((void (*)(int, void *))func_8012B14C)(param_1, ((unsigned char *)&D_8018AAEC));
    *(int *)(param_1 + 0x1c) = 0;
    *(char *)(param_1 + 0xc2) = 0;
    *(char *)(param_1 + 0xc3) = 0;
}


// @class: plumbing
// @stuck: none — MATCH expected (straight-line stores + 4 calls; delay-slot 0x2 store of 6 schedules into first jal)

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);

extern unsigned char D_801B09D0;
extern unsigned char D_8018AAEC;
extern unsigned char D_8018AAF8;

void func_801823A0(int param_1)
{
    *(unsigned char *)(param_1 + 0xc1) = 7;
    *(short *)(param_1 + 0x5c) = 0;
    *(short *)(param_1 + 2) = 6;
    func_8012A828(param_1, &D_801B09D0);
    func_8012B2CC(param_1);
    func_8012B23C(param_1);
    ((void (*)(s32, void *))func_8012B14C)(param_1, &D_8018AAEC);
    *(int *)(param_1 + 0x1c) = 0;
    *(unsigned char *)(param_1 + 0xc2) = 0;
    *(unsigned char *)(param_1 + 0xc3) = 0;
    ((void (*)(s32, void *))func_8012B14C)(param_1, &D_8018AAF8);
    return;
}

// @class: plumbing
// @stuck: none — MATCH expected (straight-line stores + 5 calls; sibling func_801823A0 is the matched twin)

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

extern unsigned char D_801B09D0;
extern unsigned char D_8018AAEC;
extern unsigned char D_8018AB04;

void func_80182420(int param_1)
{
    *(short *)(param_1 + 0x5c) = 0;
    *(short *)(param_1 + 0x76) = 0;
    *(short *)(param_1 + 0x5c) = 0;
    *(short *)(param_1 + 2) = 6;
    func_8012A828(param_1, &D_801B09D0);
    func_8012B2CC(param_1);
    func_8012B23C(param_1);
    ((void (*)(s32, void *))func_8012B14C)(param_1, &D_8018AAEC);
    *(int *)(param_1 + 0x1c) = 0;
    *(unsigned char *)(param_1 + 0xc2) = 0;
    *(unsigned char *)(param_1 + 0xc3) = 0;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0x300;
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) - 0x240000;
    ((void (*)(s32, void *))func_8012B14C)(param_1, &D_8018AB04);
    func_8012B2CC(param_1);
    func_8002D4C8(0x6aa, 0);
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801824D0);

// @class: plumbing
// @stuck: none — MATCH (30 ins)

extern unsigned char D_801B0908[];

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern void func_80143CD4(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern int func_800CB0E8(int param);

void func_801827A4(int param_1)
{
    *(short *)(param_1 + 2) = 8;
    ((int (*)(int, void *))func_8012A828)(param_1, &D_801B0908);
    ((int (*)(int))func_8012B23C)(param_1);
    *(int *)(param_1 + 0x1c) = 0x78;
    ((int (*)(int))func_80143CD4)(param_1);
    ((int (*)(int, int))func_8002D4C8)(0x47b, 0);
    ((int (*)(int, int))func_8002D4C8)(0x478, 0);
    func_800CB0E8(param_1);
    *(char *)(param_1 + 0xc1) = 6;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8018281C);

void func_8018294C(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 7;
    *(s16 *)((s32)a0 + 0x98) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x1E;
    *(s16 *)((s32)a0 + 0x5C) = 0;
}

extern void func_80182988(void);

void func_80182968(void) {
    func_80182988();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80182988);

// @class: plumbing
// @stuck: none — MATCH expected (param_1 lives in $s0 across the call; a0 reused as first arg)

extern void func_8012A828(s32 a0, void *a1);
extern unsigned char D_801B0E48[];

void func_801829E0(int param_1)
{
    *(short *)(param_1 + 2) = 0xB;
    *(short *)(param_1 + 0x34) = 2;
    func_8012A828(param_1, &D_801B0E48);
    *(char *)(param_1 + 0x102) = 0;
}

// @class: struct
// @stuck: none — MATCH (158/158). Levers: (1) switch(s32 st34) decision-tree {0,1,2} gives the
//   beq==1 / slti<2 / beq==2 dispatch (signed s32 index -> slti not sltiu); case bodies in source
//   order 0,1,2 = physical order B04<B50<C48. (2) GPU-prim struct S80143BDC shape {s16 f0..fE; s32
//   f10} -> stack layout (prim@sp+0x10, RotTrans buf s16[4]@sp+0x28) falls out byte-exact; store
//   order f6,f8,fA,f10,fE,f0,f2,f4,fC matches. (3) uninitialized $s0 flag CFG via explicit
//   compute/flag_zero labels + `if(*(u16*)(cond+2)==2) goto compute` (beq==2->compute, flag=0
//   fall-through j AB0). (4) `d=-d; flag=d<0x20` reuses d's reg ($v1) for negu. (5) u16 store of
//   0xAA10 -> ori (high bit set); s16 would give addiu/li -22000. (6) zero-byte __asm__ memory
//   barrier after the 0x102 store forces c&0xff (not the sb) into the jal rand delay slot.
#include "common.h"


struct Prim { s16 f0, f2, f4, f6, f8, fA, fC, fE; s32 f10; };

s32 func_80182A24(s32 arg0) {
    extern s32 func_8012E544(s32 a0);
    extern void func_8018301C(s32 a0);
    extern void func_80184ED8(s32 a0, s32 a1);
    extern s32 D_8018AA6C[];
    extern s32 D_801AFDD0;

    s32 cond;
    s32 flag;
    s32 d;
    u16 mode;
    s32 st34;

    mode = *(u16 *)(arg0 + 0x70);
    cond = 1;
    if ((u32)(mode - 0x505) >= 2) {
        cond = ((mode & 0xff00) == 0x700);
    }
    if (cond == 0) {
        goto flag_zero;
    }
    cond = func_8012E544(0x298);
    if (cond == 0) {
        goto lab_ab0;
    }
    if (*(u16 *)(cond + 2) == 2) {
        goto compute;
    }
flag_zero:
    flag = 0;
    goto lab_ab0;
compute:
    d = *(s16 *)(cond + 0xe) - *(s16 *)(arg0 + 0xe);
    flag = (d < 0x20);
    if (d < 0) {
        d = -d;
        flag = (d < 0x20);
    }
lab_ab0:
    if (flag != 0) {
        func_8018301C(arg0);
        return;
    }

    st34 = *(u16 *)(arg0 + 0x34);
    switch (st34) {
    case 0:
        if (*(u16 *)(arg0 + 0x72) & 0x4000) {
            s32 c = *(u8 *)(arg0 + 0x102) + 1;
            *(u8 *)(arg0 + 0x102) = c;
            __asm__ __volatile__("" ::: "memory");
            if ((((s32(*)())rand)() & 1) < (c & 0xff)) {
                ((void(*)(s32))func_80182988)(arg0);
            }
        }
        break;
    case 1: {
        s32 s1c = *(s32 *)(arg0 + 0x1c);
        if (s1c == 0xc) {
            struct Prim sp;
            s16 buf[4];
            s32 tv0;
            func_8012F214(arg0, (s32)&(*(s32 *)&D_8018AA6C), (s32)buf);
            sp.f6 = 0x20;
            sp.f8 = 2;
            sp.fA = 0;
            sp.f10 = 0;
            sp.fE = 0;
            sp.f0 = buf[0];
            sp.f2 = buf[1];
            sp.f4 = buf[2];
            sp.fC = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
            tv0 = func_8012C51C(&sp, arg0);
            if (tv0 != 0) {
                *(u16 *)(*(s32 *)(tv0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
                func_8012B2CC(tv0);
            }
        } else if (s1c == 0xf) {
            func_80184ED8(arg0, (s32)&(*(s32 *)&D_8018AA6C));
        }
        if (func_8012BEE8(arg0) != 0) {
            s32 c = *(u8 *)(arg0 + 0x102) + 1;
            *(u8 *)(arg0 + 0x102) = c;
            if ((u32)(c & 0xff) >= 3) {
                ((void(*)(s32))func_801829E0)(arg0);
                return;
            }
            *(s32 *)(arg0 + 0x1c) = 0x1e;
            return;
        }
        break;
    }
    case 2:
        if (*(u16 *)(arg0 + 0x72) & 0x4000) {
            *(s16 *)(arg0 + 2) = 0xb;
            *(u16 *)(arg0 + 0x34) = 0;
            *(s16 *)(arg0 + 0x5e) = 0;
            *(u16 *)(arg0 + 0x5c) = 0xaa10;
            func_8012A828(arg0, &D_801AFDD0);
            *(u8 *)(arg0 + 0x102) = 0;
        }
        break;
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80182C9C);

// @class: loose-typing
// @stuck: none — MATCH (unsigned short store @0x5c forces ori vs li/addiu for 0xaa10)

extern int D_801B06E8;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80182E30(short *param_1)
{
    param_1[1] = 0xe;
    *(short *)((char *)param_1 + 0x34) = 0;
    ((void (*)(void *, void *))func_8012A828)(param_1, &D_801B06E8);
    ((void (*)(void *))func_8012B23C)(param_1);
    *(unsigned short *)((char *)param_1 + 0x5c) = 0xaa10;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80182E7C);

// @class: plumbing
// @stuck: none — MATCH expected (param in $s0 across call, stores in source order)

extern void func_80130740(void *a0, u16 *a1);
extern unsigned char D_8018AB8C[];

void func_80182FD0(int param)
{
    ((int (*)(int, void *))func_80130740)(param, &D_8018AB8C);
    *(int *)(param + 0x1c) = 0x1e;
    *(int *)(param + 0x18) = 0;
    *(int *)(param + 0x10) = 0;
    *(short *)(param + 0x2) = 0xf;
    *(short *)(param + 0x5c) = 0;
}

// @class: plumbing
// @stuck: none — MATCH expected (simple struct-field init + two calls, natural schedule)

extern void func_8012A828(s32, void *);
extern void func_8002D4C8(s32, s32);
extern unsigned char D_801B09D0;

void func_8018301C(s32 param_1)
{
    *(s16 *)(param_1 + 2) = 0x10;
    *(s16 *)(param_1 + 0x34) = 0;
    *(s16 *)(param_1 + 0x5c) = 0;
    *(s32 *)(param_1 + 0x1c) = 0;
    ((void (*)(s32, u8 *))func_8012A828)(param_1, ((u8 *)&D_801B09D0));
    *(s16 *)(param_1 + 0x98) = 0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x10;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1a) = 0x100;
    func_8002D4C8(0x436, 0);
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_8018308C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183324);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183834);

extern void func_8012E364(void);

void func_80183A50(void) {
    func_8012E364();
}

extern s32 func_8012E470(s32);
extern void func_8012E4C8(s32);

void func_80183A70(s32 arg0) {
    if (func_8012E470(arg0)) {
        func_8012E4C8(arg0);
    }
}

// @class: plumbing
// @stuck: none — MATCH expected (clean structural stub)

extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern unsigned char D_801B09D0;

void func_80183AA8(int param_1)
{
    ((void (*)(void))func_8012BEE8)();
    if (*(int *)(param_1 + 0x1c) == 1) {
        func_8012A828(param_1, &D_801B09D0);
    }
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183AF0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183BAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183C50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183CF4);

void func_80183DD8(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183DE0);

// @class: plumbing
// @stuck: none — MATCH (straight-line stub; statement order + delay-slot 0x34 store match)

extern void func_8012B23C(s32 a0);

void func_80183F4C(int param_1) {
    *(short *)(param_1 + 0x2) = 2;
    *(short *)(param_1 + 0x34) = 0;
    ((void (*)(void))func_8012B23C)();
    *(short *)(param_1 + 0x5c) = 0x800;
    *(short *)(param_1 + 0x84) = 0;
    if (*(short *)(param_1 + 0xfc) < *(short *)(param_1 + 0xe)) {
        *(short *)(param_1 + 0x34) = 0;
    } else {
        *(short *)(param_1 + 0x34) = 1;
    }
    *(int *)(param_1 + 0x1c) = 0x100;
    *(int *)(param_1 + 0xdc) = 0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80183FB8);

// @class: regalloc-order
// @stuck: none — MATCH
extern s32 func_8012DE2C(s32 a0);
extern s32 func_8012DDA4(void);

void func_8018414C(short *param_1) {
    unsigned short uVar1;
    short *psVar2;
    int iVar3;
    register int k1f __asm__("$17");
    register int flag __asm__("$18");
    psVar2 = (short *)func_8012DE2C((s32)param_1);
    if (psVar2 != (short *)0) {
        k1f = 0x1f;
        flag = 1;
        do {
            if (*(unsigned short *)psVar2 == 0x2f) {
                uVar1 = psVar2[0x2e];
                if ((uVar1 & 0x8000) != 0) {
                    if ((uVar1 & 0x4000) == 0) {
                        if (*(unsigned short *)&psVar2[0x2f] != k1f) {
                            if ((psVar2[0x57] & 1) == 0) {
                                iVar3 = (int)param_1[7] - (int)psVar2[7];
                                if (iVar3 < 0) iVar3 = -iVar3;
                                if (iVar3 < 0x21 && flag) {
                                    psVar2[0x2e] = uVar1 | 1;
                                    psVar2[0x30] = 0;
                                    psVar2[0x31] = 0;
                                    psVar2[0x2f] = k1f;
                                }
                            }
                        }
                    }
                }
            }
            psVar2 = (short *)func_8012DDA4();
        } while (psVar2 != (short *)0);
    }
}

void func_80184238(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 3;
    *(s16 *)((s32)a0 + 0x34) = 0;
    *(s32 *)((s32)a0 + 0x18) = 0;
    *(s16 *)((s32)a0 + 0x5C) = 0x800;
}

void func_80184254(s32 a0) {
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x34) = 1;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0x1C) = 0x1B;
}

// @class: struct
// @stuck: none — MATCH (fn-ptr table %lo-fold via extern array of code ptrs)

extern code_fn D_8018AE88[];

extern s32 func_8012B4B8(s32 a0);

void func_80184278(int param_1)
{
    D_8018AE88[*(unsigned short *)(param_1 + 2)]();
    ((void (*)(int))func_8012B4B8)(param_1);
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801842C8);

// @class: other
// @stuck: none — MATCH expected; mirrors matched sibling func_80185814 (s0=param_1 call-crossing, sh stores via short* casts, nested second func_8012C1B8)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);

extern int D_801D100C;
extern int D_8018AE70;

void func_801843C0(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(int, int))func_8001C214)(v0, 0);
    func_8001D0E8(*(int *)(param_1 + 0x20), 0x140, 0xf0);
    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0xcc) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(int, void *))func_8001C214)(v0, &D_801D100C);
    *(int *)(param_1 + 0x58) = (int)&D_8018AE70;
    *(short *)(param_1 + 0x5c) = 0x1800;
    *(short *)(param_1 + 0x2) = 1;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) = 0;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) = 0;
    *(short *)(param_1 + 0xfc) = *(short *)(param_1 + 0xe);
    return;
}

s32 func_80184484(void) {
    return 1;
}

extern void func_8012C098(void);

void func_8018448C(void) {
    func_8012C098();
}

// @class: plumbing
// @stuck: none — MATCH (18 ins): if((b&1) && p!=&sym) call(param,&sym); $a0 live, $a1=&sym fall out
extern void func_8012A828(s32 a0, void *a1);
extern void D_80196F3C;

void func_801844AC(s32 arg0)
{
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_80196F3C)) {
        func_8012A828(arg0, &D_80196F3C);
    }
}

M2C_UNK func_8002AC00(M2C_UNK);                     /* extern */
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801844F4(void *arg0) {
    M2C_UNK var_a0;
    M2C_UNK var_a0_2;

    var_a0 = 2;
    if (M2C_FIELD(arg0, u16 *, 0x70) & 1) {
        var_a0 = 8;
    }
    func_8002AC00(var_a0);
    var_a0_2 = 0x43F;
    if (M2C_FIELD(arg0, u16 *, 0x5E) == 0x1D) {
        var_a0_2 = 0x440;
    }
    func_8002D4C8(var_a0_2, 0);
}

extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801973C4;

void func_80184554(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801973C4);
    *(s32 *)(a0 + 0x1C) = 0x14;
}

// @class: schedule
// @stuck: none — MATCH; read chained load into a temp post-call so gcc schedules lw early ($s0 holds call-crossing param naturally, no pins needed)

extern void func_8012A828(s32 a0, void *a1);
extern void D_80196F3C;

void func_80184594(s32 param) {
    u16 v;
    *(s16 *)(param + 2) = 3;
    ((void (*)(s32, s32))func_8012A828)(param, (s32)&D_80196F3C);
    v = *(u16 *)(*(s32 *)(param + 0x78) + 2);
    *(s16 *)(param + 0x5e) = 0;
    *(s16 *)(param + 0xdc) = 0;
    *(s32 *)(param + 0x1c) = 0x2d;
    *(s16 *)(param + 0x5c) = v;
}

// @class: schedule
// @stuck: none — MATCH (44 ins). Two §3-T4 branch-polarity inversions: outer if(param_2>=iVar2) makes the func_8018469C else-block fall-through; inner if(param_3>=iVar2) return 0 makes the func_8012A828 body fall-through. No pins needed — natural $s1/$s0/$s2 alloc matched.
extern s32 func_8012BCCC(s32 a0);
extern void func_8018469C(s32 param_1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_8019731C;

s32 func_801845EC(s32 param_1, s32 param_2, s32 param_3) {
    s32 iVar2;
    s16 sVar1;

    iVar2 = func_8012BCCC(param_1);
    if (param_2 >= iVar2) {
        func_8018469C(param_1);
        return 1;
    }
    sVar1 = *(s16 *)(param_1 + 0xdc) + 1;
    *(s16 *)(param_1 + 0xdc) = sVar1;
    if (sVar1 < 0x79) {
        return 0;
    }
    if (param_3 >= iVar2) {
        return 0;
    }
    *(s16 *)(param_1 + 2) = 1;
    func_8012A828(param_1, &D_8019731C);
    return 1;
}

// @class: plumbing
// @stuck: none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801970DC;

void func_8018469C(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801970DC);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}

void func_801846F8(s32 a0) {
    *(s16 *)(a0 + 0x2) = 5;
    *(s32 *)(a0 + 0x1C) = 0x14;
}

// @class: regalloc-order
// @stuck: none — MATCH (97 ins, relocation-masked); $s0=&spr (call-crossing) + $s1=param_1 fell out naturally (no pins needed); frame 0x40 from svec(8)+spr(20)

extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

extern u8 D_8018AF78;
extern u8 D_8018AF88;
extern volatile unsigned short D_80126B96;
extern void D_80196F3C;

void func_8018470C(s32 param_1)
{
    SV4U svec;            /* sp+0x10 */
    struct sprite8 spr;   /* sp+0x18 */
    s32 base;
    u16 uVar1;

    if (*(int *)(param_1 + 0x1c) == 9) {
        base = (s32)&D_8018AF78;
        if (func_8012D5E4(param_1, base, base + 8, 9) != 0
            && (*(unsigned short *)(param_1 + 0x70) & 1) != 0) {
            D_80126B96 = D_80126B96 | 0x800;
        }
        if ((*(short *)(param_1 + 0x70) & 0x8000) != 0) {
            func_8012F214(param_1, (s32)&D_8018AF88, (s32)&svec);
            spr.f6 = 0xda;
            spr.fa = 0;
            spr.fc = 0x7fff;
            spr.f0 = svec.a;
            spr.f2 = svec.b;
            spr.f4 = svec.c;
            spr.fe = *(u16 *)(*(int *)(param_1 + 0x20) + 0x12);
            func_8012C51C(&spr, param_1);
            spr.fe = *(u16 *)(*(int *)(param_1 + 0x20) + 0x12) + 0x100;
            func_8012C51C(&spr, param_1);
            spr.fe = *(u16 *)(*(int *)(param_1 + 0x20) + 0x12) - 0x100;
            func_8012C51C(&spr, param_1);
        }
        func_8002D4C8(0x43e, 0);
    }
    if (func_8012BEE8(param_1) != 0) {
        *(int *)(param_1 + 0x1c) = 0x3c;
        *(short *)(param_1 + 2) = 3;
        func_8012A828(param_1, &D_80196F3C);
        uVar1 = *(u16 *)(*(int *)(param_1 + 0x78) + 2);
        *(short *)(param_1 + 0x5e) = 0;
        *(short *)(param_1 + 0xdc) = 0;
        *(int *)(param_1 + 0x1c) = 0x2d;
        *(short *)(param_1 + 0x5c) = uVar1;
    }
}

extern s32 (*D_8018AF90[])();

s32 func_80184890(s16 *a0) {
    return D_8018AF90[(u16)a0[1]]();
}

extern s32 (*D_8018AFB8[])();

s32 func_801848CC(s16 *a0) {
    return D_8018AFB8[(u16)a0[1]]();
}

extern s32 (*D_8018B000[])();

s32 func_80184908(s16 *a0) {
    return D_8018B000[(u16)a0[1]]();
}

// @class: plumbing
// @stuck: none — MATCH (clean if/else, sh into delay slot of func_8001CA88 call)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern void func_80143994(s32 a0, s32 a1);
extern int D_8018AFC0;

void func_80184944(int param_1)
{
    int iVar1;

    iVar1 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        *(short *)(param_1 + 2) = 1;
        func_8001CA88(*(int *)(param_1 + 0x20), &D_8018AFC0);
        func_80143994(param_1, 0x1000);
    }
}

extern void func_8012B2CC(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_801849A8(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    u16 v = *(u16 *)(a0 + 0xFC);
    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 0x50;
    *(s16 *)(p + 0x12) = v;
    func_8012B2CC((s32)a0);
    func_8012B200(a0);
    func_8012B178((s32)a0, 0xFFF00000);
}

// @class: plumbing
// @stuck: none — MATCH (expected); clean stub, s0 holds param across both calls, no regalloc/schedule residual

extern void func_8012AD80(s32 a0);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012C218(void *a0);

extern s32 D_8018B00C;
extern u8 D_800D3918[];

void func_80184A00(s32 param_1) {
    ((void (*)(void))func_8012AD80)();
    if (func_8012D5E4(param_1, (s32)&D_8018B00C, (s32)&D_800D3918, 10) != 0 ||
        (*(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80184A68);

extern s32 func_8012BEE8(s32);
extern void func_80184594(s32);

void func_80184AEC(s32 arg0) {
    if (func_8012BEE8(arg0)) {
        func_80184594(arg0);
    }
}

// @class: schedule
// @stuck: none — MATCH (36 ins, relocation-masked)

extern s32 func_8012BEE8(s32 a0);
extern s32 func_801845EC(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void);

void func_80184B24(s32 param_1)
{
    s32 r, a1, a2;

    r = ((s32 (*)(void))func_8012BEE8)();
    if (r == 1) {
        s32 d = param_1;
        if (*(s16 *)(d + 0x70) & 0x8000) { a1 = 0x40000; a2 = 0xC0000; }
        else                             { a1 = 0x9000;  a2 = 0x20000; }
        /* scheduling barrier: anchors the `move a0,s0` arg setup into the
           beqz delay slot, matching the target's reorg delay-slot fill. */
        __asm__ ("" : "=r"(d) : "0"(d));
        if (func_801845EC(d, a1, a2 | 0x4000) == r) {
            return;
        }
    }
    if (func_8012C044(param_1) != 0) {
        ((void (*)(s32))func_8012C098)(param_1);
    }
}

// @class: plumbing
// @stuck: none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801846F8(s32 a0);

void func_80184BB4(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        func_801846F8(param_1);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80184C0C);

// @class: struct
// @stuck: none — MATCH expected (folded %lo via extern array decay; a0 carries iVar2 into func_8001C214)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_8018AFA8[];

void func_80184CCC(int param_1)
{
    int iVar2;
    short uVar1;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(iVar2, D_8018AFA8[*(short *)(param_1 + 0x70)]);
        uVar1 = *(short *)(*(int *)(param_1 + 100) + 0x36);
        *(short *)(param_1 + 2) = 1;
        *(short *)(param_1 + 0xfe) = 0x7fff;
        *(short *)(param_1 + 0xfc) = uVar1;
    }
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80184D50);

extern s32 D_801DA908;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80184ED8(s32 a0, s32 a1) {
    D_801DA908 = a1;
    return func_8012C588(0x85, a0);
}

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)

typedef struct { short vx, vy, vz, pad; } SVECTOR_80184F08;
typedef struct { u8 b[8]; } S8_80184F08;



s32 func_80184F08(s32 param_1) {
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_8019918C;
    extern char * D_801991C0;
    extern char D_801DA8E8[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_8019918C) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80186E48));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801DA908, &s60);
    s50 = s60;
    sStack_58.vz = 0x1800;
    sStack_58.vy = 0x1800;
    sStack_58.vx = 0x1800;
    ((void (*)(void *, void *))func_80017DC4)(&sStack_58, auStack_48);
    RotMatrixZ(rand() & 0xfff, auStack_48);
    MulMatrix0(iVar8, auStack_48, iVar5 + 0x34);
    ((void (*)(void *, s32))func_80017E68)(&s50, iVar5 + 0x34);

    /* pool-alloc: gcc routes the loaded pointer through a caller-saved reg ($v0)
       before the callee-saved home ($s1) — pin it to reproduce the extra move. */
    {
        register char *tmp __asm__("$2");
        tmp = D_801991C0;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801991C0 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801DA8E8 < puVar4) {
        D_801991C0 = D_801DA8E8 - 0x120;
    }
    func_800D20C0(&s60, &sStack_58, 7);
    func_800D23D0(&sStack_58);
    ((void(*)(void *, void *))RotMatrixYXZ)(&sStack_58, puVar2);
    ((void (*)(void *, s32))func_80017E68)(&s60, (s32)puVar2);

    uVar3 = *(u16 *)((char *)&s50 + 2);
    if (((s32 (*)(void *))func_80134510)(&s50) != 0 &&
        (s32)(s16)uVar3 - (s32)*(s16 *)((char *)&s50 + 2) < 0x80) {
        *(s16 *)((char *)&s50 + 2) = *(s16 *)((char *)&s50 + 2) - 4;
        {
            register char *tmp __asm__("$3");
            tmp = D_801991C0;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801991C0 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801DA8E8 < puVar4) {
            D_801991C0 = D_801DA8E8 - 0x120;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), puVar2);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)puVar2);
    }
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


// @class: regalloc-order
// @stuck: none — MATCH (168 ins). Keys: (1) pin param->$s1 via `register int self __asm__("$17")=param_1`
//   (natural alloc put the short loop-counter in $s1); (2) block2's guarded dest via a test-temp
//   `td=load; if(td){dest=td; ...}` forces the range-split `lw $a1; addu $s3,$a1,$0` the target has;
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).
extern signed char D_80199178[];

s32 func_8018514C(s32 param_1) {
    register int self __asm__("$17") = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    iVar1 = *(int *)(self + 0x1c);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_80199178;
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
            p = D_80199178;
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
        *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1;
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        __asm__ __volatile__("" : "=r"(self) : "0"(self));
        func_8012C218((void *)self);
    }
}


extern s32 (*D_801991C4[])();

s32 func_801853EC(s16 *a0) {
    return D_801991C4[(u16)a0[1]]();
}

// @class: struct
// @stuck: none — MATCH (94 ins). Keys: (1) cache out[0] in a local `o` before the switch so gcc
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
extern M2C_UNK D_801B1430;
extern u8   D_801B1208;
extern u8 D_80126B5C;
extern s32  D_80126B60;
extern s32  D_80126B64;

struct In { s32 w0; s16 lo; s16 hi; s32 w2; };

void func_80185428(s32 param_1) {
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
    ((void (*)(s32, void *))func_8001C214)(iVar1, &(*(u8 *)&D_801B1430));
    if ((*(u16 *)(param_1 + 0x70) & 0x1000) == 0) {
        func_8002D4C8(0x43A, 0);
    } else {
        func_8002D4C8(0x6D6, 0);
    }
    func_8012A828(param_1, &D_801B1208);
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


// @class: struct
// @stuck: none — MATCH (established no-arg function-pointer table dispatch idiom)

extern void (*D_801B12A4[])(void);

void func_801855A0(void *a0) {
    D_801B12A4[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: struct
// @stuck: none — MATCH expected (indexed function-pointer table tail-call)

extern void (*D_801B12B8[])(void);

void func_801855DC(short *param_1) {
    D_801B12B8[(unsigned short)param_1[1]]();
}

// @class: plumbing
// @stuck: none — MATCH (56 ins, relocation-masked); branch-polarity invert (§3-T4) put the func_80146A6C block as fall-through

#include "common.h"

extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_801B1290;
extern s32 D_801B129C;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_80185618(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_801B1290);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_801B129C, (s32)&D_800D3918, 0x19) == 0 &&
            (*(s16 *)(s0 + 0x70) == 2 || D_80126D50 == 0) &&
            func_8012BEE8(s0) == 0) {
            return;
        }
    }
    func_8012C218((void *)s0);
}

// @class: schedule
// @stuck: none — MATCH (71 ins). Tail schedule: read out.c into an explicit temp BEFORE the 0x5a/1 const stores so gcc hoists its lhu early (load-delay filled by li 0x5a) and stores out.c last from a held reg; without the temp gcc instead deferred out.b's store. in/out are two separate SV3{s16 a,b,c} stack slots (sp+0x10, sp+0x18) for ((void (*)(int, void *, void *))func_8012F214)(a0,&in,&out). 0x34 compare reads u16 (lhu, not lh).

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern int D_801B12AC;

void func_801856F8(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801B12AC);
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
// @stuck: none — MATCH (expected); 16-bit sh stores via short* casts, s0=param_1 call-crossing

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_801B1560;

void func_80185814(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801B1560);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}

// @class: struct
// @stuck: none — MATCH (table-dispatch idiom, twin of matched func_801425CC)
#include "common.h"

extern s32 (*D_801B1588[])();

s32 func_80185870(s16 *a0) {
    return D_801B1588[(u16)a0[1]]();
}

// @class: iv-combine
// @stuck: none — MATCH (49 ins). gcc folds (v0+0x1800)-0x1000 -> v0+0x800; re-tie barrier on the WORKING reg v0 (NOT a saved local) forces the target chain v0=base+0x1800; s2=copy; v0-=0x1000; s1=v0<<5. NO register pins (pins re-trigger the lhu/lh dual-load CSE collapse and shrink the frame; natural alloc gives s0-s3 + frame 0x38).
extern int rand(void);
extern u8 *func_8012913C(s32 a0);

extern unsigned short D_801B1568[];

void func_801858AC(s32 param_1, s32 param_2)
{
    int s3;
    unsigned short s0;
    int s2;
    int s1;
    int v0;
    int iVar3;

    s0 = D_801B1568[*(short *)(param_1 + 0xfc)];
    s3 = param_2;
    if (((short *)D_801B1568)[*(short *)(param_1 + 0xfc)] == 0) {
        *(short *)(param_1 + 0xfc) = 0;
        s0 = D_801B1568[0];
    }
    *(short *)(param_1 + 0xfc) = *(short *)(param_1 + 0xfc) + 1;
    v0 = (rand() & 3) * 0x400 + 0x1800;
    s2 = v0;
    __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
    s1 = (v0 - 0x1000) * 0x20;
    iVar3 = ((int (*)(int))func_8012913C)(4);
    if (iVar3 != 0) {
        *(short *)(iVar3 + 6) = s3;
        *(short *)(iVar3 + 0xa) = s0;
        *(short *)(iVar3 + 0xe) = 0;
        *(int *)(iVar3 + 0x10) = s1;
        *(short *)(iVar3 + 0x2c) = s2;
    }
}

// @class: struct
// @stuck: none — MATCH (mirrors matched sibling func_801853EC: table[(u16)a0[1]]())

extern s32 (*D_801B159C[])();

s32 func_80185970(s16 *a0) {
    return D_801B159C[(u16)a0[1]]();
}

// @class: regalloc-order
// @stuck: none — MATCH

extern void func_801858AC(s32, s32);
extern s32 func_8012AD50(void *a0);

void func_801859AC(int param_1) {
    short uVar1;

    *(short *)(param_1 + 0xfc) = 0;
    *(int *)(param_1 + 0x1c) = 1;
    uVar1 = *(unsigned short *)(param_1 + 0x70) & 7;
    *(short *)(param_1 + 0xfe) = (uVar1 < 2) ? 0x1e : 0xf;
    if (uVar1 != 0) {
        func_801858AC(param_1, -0x80);
        func_801858AC(param_1, -0x30);
        func_801858AC(param_1, 0x20);
        func_801858AC(param_1, 0x70);
        func_801858AC(param_1, 0xc0);
    }
    if (1 < uVar1) {
        func_801858AC(param_1, -0x58);
        func_801858AC(param_1, -0x8);
        func_801858AC(param_1, 0x48);
        func_801858AC(param_1, 0x98);
        func_801858AC(param_1, 0xe8);
    }
    ((void (*)(int))func_8012AD50)(param_1);
}

// @class: regalloc-order
// @stuck: none — MATCH (param_1 naturally lands in $s0 across the call, mirrors sibling func_80184AEC)

extern s32 func_8012BEE8(s32 a0);
extern void func_801858AC(s32, s32);

void func_80185A94(s32 arg0) {
    if (func_8012BEE8(arg0)) {
        *(s32 *)(arg0 + 0x1c) = (s32)*(s16 *)(arg0 + 0xfe);
        func_801858AC(arg0, 0x110);
    }
}

// @class: plumbing
// @stuck: none — MATCH (expected)
extern void func_8001CB00(int param_1, void *src, int len, int n);

extern unsigned char D_801B1590;

void func_80185AD4(int param_1)
{
    unsigned short uVar1;
    int iVar2;

    iVar2 = *(int *)(param_1 + 0x20);
    func_8001CB00(iVar2, &D_801B1590, 0x280, 0x100);
    *(unsigned int *)(iVar2 + 4) = *(unsigned int *)(iVar2 + 4) | 0x70000000;
    uVar1 = *(unsigned short *)(param_1 + 0x2c);
    *(unsigned char *)(iVar2 + 0x27) = 0x9e;
    *(unsigned short *)(iVar2 + 0x2c) = 4;
    *(unsigned short *)(iVar2 + 0x1c) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = uVar1;
    *(unsigned short *)(iVar2 + 0x18) = uVar1;
    *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    return;
}

extern void func_801292C8(u8 *a0);

void func_80185B5C(u8 *a0) {
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x4) - *(s32 *)(a0 + 0x10);
    if (*(s16 *)(a0 + 0x6) < -0x110) {
        func_801292C8(a0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80185BA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80185E68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_80186078);

extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern M2C_UNK D_80186E48;
extern M2C_UNK D_801D77A8;

void func_80186330(void *arg0) {
    void *temp_v1;

    func_8001C214(M2C_FIELD(arg0, void **, 0x20), &D_801D77A8);
    func_8012A828(arg0, &D_80186E48);
    M2C_FIELD(arg0, s16 *, 2) = 3;
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 0xDC);
    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(arg0, u16 *, 0xDE);
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) & 0x77FF);
    M2C_FIELD(temp_v1, u16 *, 0x2C) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x2C) & 0xFFEF);
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
}

// @class: schedule
// @stuck: none — MATCH (pending byte-gate); pure store sequence, gcc -O2 schedules a0/a1 materialization

extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80174784(void);
extern M2C_UNK D_80186E48;

void func_801863B4(int param_1) {
    unsigned short uVar1;

    func_8012A828(param_1, &D_80186E48);
    *(short *)(param_1 + 2) = 4;
    *(short *)(param_1 + 0x34) = 0;
    *(int *)(param_1 + 0x1c) = 0x1e;
    uVar1 = *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *(short *)(param_1 + 0xe8) = 0;
    *(int *)(param_1 + 0xe0) = 0x400000;
    *(int *)(param_1 + 0xe4) = 0;
    *(short *)(param_1 + 0xea) = uVar1;
    func_8002D4C8(0x49e, 0);
    func_8002D4C8(0x4a2, 0);
    func_80174784();
}

// @class: regalloc-order
// @stuck: none — MATCH (pending verify)

#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32, s32, s32);
extern void func_8012A828(s32 a0, void *a1);

extern u8 D_801D6F6C;
extern u8 D_801D55C0;
extern s32 D_801D55AC[];
extern u8 D_801D5568;
extern u8 D_801D5558;

void func_80186434(s32 arg0) {
    register s32 param_1 __asm__("$16") = arg0;
    register s32 iVar1 __asm__("$17");
    s32 ret;
    s32 iVar2;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = ret;
    iVar1 = ret;
    if (ret == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001C214)(iVar1, &D_801D6F6C);
        func_8001D0E8(iVar1, 0x104, 0x190);
        *(u16 *)(iVar1 + 0x1c) = 0x1c00;
        *(u16 *)(iVar1 + 0x1a) = 0x1c00;
        *(u16 *)(iVar1 + 0x18) = 0x1c00;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0x10;
        *(u16 *)(param_1 + 0x76) = 4;
        *(s32 *)(param_1 + 0x78) = (s32)&D_801D55C0;
        *(u16 *)(param_1 + 0xdc) = *(u16 *)(param_1 + 6);
        *(u16 *)(param_1 + 0xde) = *(u16 *)(param_1 + 0xe);
        ((void (*)(s32, s32))func_8012A828)(param_1, D_801D55AC[*(s16 *)(param_1 + 0x76)]);
        *(u16 *)(param_1 + 2) = 1;
        if (*(s16 *)(param_1 + 0x70) == 4) {
            *(s32 *)(param_1 + 0x58) = (s32)&D_801D5568;
        } else {
            *(s32 *)(param_1 + 0x58) = (s32)&D_801D5558;
        }
        iVar2 = *(s32 *)(param_1 + 0x20);
        *(u32 *)(param_1 + 0x58) = *(u32 *)(param_1 + 0x58) | 0x60000000;
        *(u16 *)(iVar2 + 0x1c) = 0x1c00;
        *(u16 *)(iVar2 + 0x1a) = 0x1c00;
        *(u16 *)(iVar2 + 0x18) = 0x1c00;
        *(u16 *)(param_1 + 0x5e) = 0;
        *(u16 *)(param_1 + 0x5c) = *(u16 *)(param_1 + 0x5c) | 0x8800;
        *(u16 *)(param_1 + 6) = *(u16 *)(param_1 + 0xdc);
        *(u16 *)(param_1 + 0xe) = *(u16 *)(param_1 + 0xde);
    }
}

// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold; (unsigned)(field-1)<2 forces sltiu not slti)

extern void func_80185E68();
extern void (*D_801D5624[])();

void func_80186574(int param_1)
{
    if (((unsigned int)(*(unsigned short *)(param_1 + 2) - 1) < 2) &&
        ((*(unsigned short *)(param_1 + 0x5c) & 1) != 0)) {
        func_80185E68();
    } else {
        D_801D5624[*(unsigned short *)(param_1 + 2)]();
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_after", func_801865EC);

// @class: struct
// @stuck: none — MATCH expected (fn-pointer-table dispatch, lhu+2 index, %lo-folded lw)

extern void (*D_801D564C[])(void);

void func_801867E0(short *arg0) {
    D_801D564C[*(unsigned short *)((char *)arg0 + 2)]();
}

extern Blk8 D_801D5610;

void func_8018681C(s32 a0) {
    if (*(s16 *)((s32)a0 + 0x70) == 4) {
        *(Blk8 *)((s32)a0 + 0x50) = D_801D5610;
    }
}

// @class: struct
// @stuck: none — MATCH; int *p=&D_801270DC + deref for both load AND store forces addiu-base in $s1 (callee-saved), reused via 0x0($s1) — direct global ref re-materializes lui per access
extern void func_8012BD14(s32 a0);
extern s32 func_8012E544(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_801863B4(int param_1);

extern int D_801270DC;
extern s32 D_80126D50;

void func_80186860(int param_1) {
    int v;
    int *p = &D_801270DC;

    if (*p == 0) {
        if (((int (*)(int))func_8012BD14)(param_1) < 0x4001) {
            v = func_8012E544(0x161);
            if (v != 0) {
                *(short *)(v + 0xfc) = 1;
                *(short *)(v + 0xfe) = 3 - *(short *)(param_1 + 0x70);
            }
            *p = 1;
            *(int *)(param_1 + 0x1c) = 0x1e;
        }
    } else {
        ((void (*)(int))func_8012BEE8)(param_1);
        if (*(int *)(param_1 + 0x1c) == 0 && D_80126D50 == 0 &&
            ((int (*)(int))func_8012BD14)(param_1) < 0x241) {
            func_801863B4(param_1);
        }
    }
}

// @class: remat
// @stuck: none — MATCH. Key idiom: D_801270C8 read+write via a pointer var (s32 *p = &D_801270C8; *p+=1; *p>=4) forces gcc to materialize the symbol address ONCE (lui+addiu %lo into one reg) and reuse it for both lw and sw, vs two separate %lo-folded lui's from `D_801270C8 += 1`. Also 0x34 field is lhu (u16) not lh.

extern s32 D_801270C8;
extern s32 D_801270CC;
extern u8 D_801D7A4C;
extern M2C_UNK D_80186E48;

extern void func_80185BA4(void *arg0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_801747AC(s32 a0);

void func_80186938(s32 arg0) {
    s32 temp;
    s32 *p;

    if (*(u16 *)(arg0 + 0x34) == 0) {
        temp = *(s32 *)(arg0 + 0xE4) + *(s32 *)(arg0 + 0xE0);
        *(s32 *)(arg0 + 0xE8) = *(s32 *)(arg0 + 0xE8) + temp;
        *(s32 *)(arg0 + 0xE4) = temp;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = *(s16 *)(arg0 + 0xEA);
        func_80185BA4((void *)arg0);
        if (((s32 (*)(void *))func_8012BEE8)((void *)arg0) != 0) {
            *(s16 *)(arg0 + 0x34) = 1;
            ((void (*)(s32, void *))func_8001C214)(*(s32 *)(arg0 + 0x20), &D_801D7A4C);
            ((void (*)(void *, void *))func_8012A828)((void *)arg0, &D_80186E48);
            ((void (*)(void))func_801747AC)();
            p = &D_801270C8;
            *p += 1;
            if (*p >= 4) {
                D_801270CC = 2;
            }
        }
    }
}

// @class: plumbing
// @stuck: none — MATCH (51 ins; key lever: §3-T4 branch-polarity invert >=0x30 → OR-block falls through, AND-block is branch target with lui hoisted to delay slot)

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80186A04(int param_1)
{
    int iVar1;

    ((void (*)(void))func_8012AD80)();
    if (*(int *)(param_1 + 0x1c) >= 0x30) {
        *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) =
            *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) | 0x80000000;
    } else {
        *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) =
            *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) & 0x7fffffff;
    }
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) + 0x17;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 0x43;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 0x58;
    iVar1 = func_8012BEE8(param_1);
    if (iVar1 != 0) {
        ((void (*)(int))func_8012C218)(param_1);
    }
    return;
}
