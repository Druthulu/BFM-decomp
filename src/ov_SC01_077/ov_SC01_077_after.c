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


struct Ent_801506A4 {
    unsigned short unk0;    /* 0x0 */
    char pad[0x5A];
    unsigned short unk5C;   /* 0x5C */
    char pad2[0x12];
    short unk70;            /* 0x70 */
};

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

#include "common.h"

typedef struct {
    u8   pad00[0x12];
    u16  unk12;              /* 0x12 */
} Sub_80155800_80155800;

typedef struct {
    u8            pad00[0x20];
    Sub_80155800_80155800 *unk20;     /* 0x20 */
    u8            pad24[0x44 - 0x24];
    s32           unk44;     /* 0x44 */
    u8            pad48[0xB8 - 0x48];
    u16           unkB8;     /* 0xB8 */
    u8            padBA[0x1A8 - 0xBA];
    u8            unk1A8;    /* 0x1A8 */
    u8            unk1A9;    /* 0x1A9 */
    u8            unk1AA;    /* 0x1AA */
    u8            pad1AB[0x1C0 - 0x1AB];
    u8            unk1C0;    /* 0x1C0 */
    u8            pad1C1[0x234 - 0x1C1];
    u8            unk234;    /* 0x234 */
} Ent_80155800_80155800;


s32 func_80155800(s32 arg0) {
    extern void func_80155A44(void *);
    extern void func_80155F80(void *);
    extern void func_80155FF8(void *, u8);
    extern void func_8015A230(void *);
    extern s32 func_80161208(void *);

    struct { s16 a, b, c, d, e, f, g, h, i, j, k, l; } sp10;
    u8 temp_v0;
    u8 temp_v1;
    s32 var_v1;

    ((Ent_80155800_80155800 *)arg0)->unk44 |= 2;
    if (((Ent_80155800_80155800 *)arg0)->unkB8 == 0x8000) {
        ((void(*)(void *))func_801599A4)(((Ent_80155800_80155800 *)arg0));
        ((void(*)(void *))func_80159B3C)(((Ent_80155800_80155800 *)arg0));
        return;
    }
    func_80155A44(((Ent_80155800_80155800 *)arg0));
    if (((s32(*)(void *))func_80148800)(((Ent_80155800_80155800 *)arg0)) & 0x80) {
        temp_v1 = ((Ent_80155800_80155800 *)arg0)->unk1A9;
        if (temp_v1 >= 4U) {
            if (((Ent_80155800_80155800 *)arg0)->unk1C0 != 0) {
                ((void(*)(void *))func_80148AFC)(((Ent_80155800_80155800 *)arg0));
                func_80155F80(((Ent_80155800_80155800 *)arg0));
                ((void(*)(void *))func_80154134)(((Ent_80155800_80155800 *)arg0));
                temp_v0 = ((Ent_80155800_80155800 *)arg0)->unk1AA;
                var_v1 = temp_v0 + 1;
                if (temp_v0 == 0) {
                    var_v1 = 2;
                } else if (var_v1 >= 5U) {
                    var_v1 = 1;
                }
                ((Ent_80155800_80155800 *)arg0)->unk1AA = var_v1;
                ((void(*)(void *))func_80149B14)(((Ent_80155800_80155800 *)arg0));
                return;
            }
            if (((Ent_80155800_80155800 *)arg0)->unk1AA >= 2U) {
                if (((Ent_80155800_80155800 *)arg0)->unk1A8 == 0) {
                    if (temp_v1 != 0) {
                        goto block_13;
                    }
                    goto block_15;
                }
                goto block_22;
            }
block_13:
            ((void(*)(void *))func_80148AFC)(((Ent_80155800_80155800 *)arg0));
            func_80155F80(((Ent_80155800_80155800 *)arg0));
            ((void(*)(void *))func_80154134)(((Ent_80155800_80155800 *)arg0));
            ((void(*)(void *))func_80149AD4)(((Ent_80155800_80155800 *)arg0));
            D_8011F730 |= 3;
            return;
        }
    }
block_15:
    if ((((Ent_80155800_80155800 *)arg0)->unk1A8 == 0) && (((Ent_80155800_80155800 *)arg0)->unk1A9 != 0)) {
        if (((s32(*)(void *))func_801496D4)(((Ent_80155800_80155800 *)arg0)) != 0) {
            ((void(*)(void *))func_801599A4)(((Ent_80155800_80155800 *)arg0));
            ((void(*)(void *))func_80149704)(((Ent_80155800_80155800 *)arg0));
            return;
        }
        if (!(((s32(*)(void *))func_801487F4)(((Ent_80155800_80155800 *)arg0)) & 8) && (((s32(*)(void *))func_801488A8)(((Ent_80155800_80155800 *)arg0)) != 0)) {
            ((void(*)(void *))func_801599A4)(((Ent_80155800_80155800 *)arg0));
            func_8015A230(((Ent_80155800_80155800 *)arg0));
            return;
        }
        goto block_22;
    }
block_22:
    if (((s32(*)(void *))func_80146E98)(((Ent_80155800_80155800 *)arg0)) == 0) {
        ((void(*)(s16, void *, void *))func_8001382C)((s16) -(s32) ((Ent_80155800_80155800 *)arg0)->unk20->unk12, &((Ent_80155800_80155800 *)arg0)->unk234, &sp10);
        ((void(*)(void *, void *))func_80146DB8)(((Ent_80155800_80155800 *)arg0), &sp10);
        ((void(*)(void *))func_80147A84)(((Ent_80155800_80155800 *)arg0));
        ((void(*)(void *))func_801473EC)(((Ent_80155800_80155800 *)arg0));
    }
    if (func_80161208(((Ent_80155800_80155800 *)arg0)) == 0) {
        func_80155FF8(((Ent_80155800_80155800 *)arg0), ((Ent_80155800_80155800 *)arg0)->unk1AA);
    }
}


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

/* func_8015A3C8 (ov_SC01_077_after, 493 ins, jtbl_801D8B34) — Phase 26 crack
 * Entity air/fall update: 7-case switch (0/1/2/6 shared, 3/4/5 own, no default block),
 * then a big velocity-clamp tail with a nested char switch (0x41 / 0x53+0x73).
 * PIN-FREE. Offset-pure (s32 arg0 + raw offsets) — x134 template-safe.
 */
extern void (*D_801891B8[])(void *);
extern u8 D_80078E78[];
extern s16 currentLocationId;

extern s32 func_80149D9C(s32 a0);
extern void func_80149FA8(void);
extern s32 func_80149FB0(s32 a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161B18(void *a0);
extern s32 func_8014A048(s32 a0);
extern void func_8014A218(void);
extern int func_80161BE0(void *param_1);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80149AA8(s32 *a0);
extern void func_80149AD4(s32 *a0);
extern s32 func_80149B54(s32 * arg0);
extern void func_80149BAC(s32 *a0);
extern s32 func_801498E0(s32 *a0);
extern s32 func_80149954(s32 s0);
extern s32 func_80149A64(s32 *a0);
extern void func_800CCCC0(s32 a0);
extern s32 func_80149CD4(s32 a0);
extern void func_8015E880(s32 *a0);
extern s32 func_801496D4(void *a0);
extern void func_80149704(void);
extern s32 func_801488A8(u8 *a0);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern void func_8015AC48(s32 a0);
extern int func_80148AFC(void *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern u16 func_801487F4(s32 *a0);
extern s32 func_8016F1C4(void);
extern s32 func_8015AB7C(s32 a0);
extern void func_801541D8(u8 *a0, s32 a1, s32 a2);
extern s32 func_80148824(void *arg0);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_8015C6E0(s32 *a0);
extern void func_8014E934(s32 _arg0);
extern void func_80155440(s32 *a0);
extern void func_801553C0(s32 a0);
extern void func_80161278(void *a0);
extern void func_80161C24(s32 a0, s32 a1);
extern s32 func_80172608(u8 *a0);
extern void func_801483E8(void);

s32 func_8015A3C8(arg0)
s32 arg0;
{

    extern u16 D_800B99DA;
    extern s32 D_800D5428;
    extern u8 D_8018913C[];
    s32 min;
    s32 grav;
    s32 hi;
    s32 t;
    s32 lo1;
    s32 lo2;
    s32 sv;
    u8 *p;

    p = D_80078E78;
    if (currentLocationId == 0x302A) {
        min = -0xC0000;
        grav = -0x4000;
        hi = 0;
    } else {
        min = -0xB0000;
        grav = -0x1000;
        hi = 0;
    }

    if (func_80149D9C(arg0) != 0) {
        D_801891B8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149FA8)(arg0);
        return;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (((s32 (*)(s32))func_80161B84)(arg0) != 0) {
        return;
    }
    if (((s32 (*)(s32))func_80161B18)(arg0) != 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D5428) {
        if (func_8014A048(arg0) != 0) {
            D_801891B8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8014A218)(arg0);
            return;
        }
    }
    if (((s32 (*)(s32))func_80161BE0)(arg0) != 0) {
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 2:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_801891B8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_801891B8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
            return;
        }
        break;
    case 3:
        ((void (*)(s32))func_801498E0)(arg0);
        break;
    case 4:
        ((void (*)(s32))func_80149954)(arg0);
        break;
    case 5:
        if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
            D_801891B8[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
        break;
    }

    if (func_80149CD4(arg0) != 0) {
        D_801891B8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015E880)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_801891B8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801488A8)(arg0) == 0) {
        sv = *(s32 *)(arg0 + 0x2C);
        D_801891B8[*(u16 *)arg0]((void *)arg0);
        func_8014C010(arg0, 1);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        if (func_8015ABD4(arg0, sv, min) != 0) {
            func_8015AC48(arg0);
        }
        return;
    }

    ((void (*)(s32))func_80148AFC)(arg0);
    if (*(u32 *)(arg0 + 0x44) & 0x200) {
        if (*(s32 *)(arg0 + 0x23C) == 0) {
            func_80154150(arg0, 0xA);
            func_80154A74(arg0, 0x1C);
        }
        ((void (*)(s32, s32))func_80146DB8)(arg0, (s32)&(*(s32 *)&D_8018913C));
        func_80147AD4(arg0, 0, 0, 0);
    } else {
        switch (*(u8 *)(arg0 + 0xA9)) {
        case 0x41:
            func_80147AD4(arg0, 0, 0, grav);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                if (((s32 (*)(s32))func_801487F4)(arg0) & 4) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                } else if (func_8016F1C4() == 0) {
                    if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                            *(s32 *)(arg0 + 0x2C) = -0x40000;
                        }
                    } else if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                        if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                            *(s32 *)(arg0 + 0x2C) = -0x80000;
                        }
                    }
                }
                if (*(s32 *)(arg0 + 0x2C) < min) {
                    *(s32 *)(arg0 + 0x2C) = min;
                }
                if (*(s32 *)(arg0 + 0x2C) >= hi) {
                    *(s32 *)(arg0 + 0x2C) = hi;
                }
                lo1 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo1) {
                    func_80154150(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))func_801541D8)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    func_80154150(arg0, 6);
                }
            }
            break;
        case 0x53:
        case 0x73:
            *(s32 *)(arg0 + 0x2C) = (min * (((s32 (*)(s32))func_80148824)(arg0) & 0xFF)) / 127;
            if (func_8016F1C4() == 0) {
                if ((*(s16 *)(p + 0x26) < 0x40) || (*(s16 *)(p + 0x2E) < 0x30)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x80000) {
                        *(s32 *)(arg0 + 0x2C) = -0x80000;
                    }
                }
                if ((*(s16 *)(p + 0x26) < 0x20) || (*(s16 *)(p + 0x2E) < 0x20)) {
                    if (*(s32 *)(arg0 + 0x2C) < -0x40000) {
                        *(s32 *)(arg0 + 0x2C) = -0x40000;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x2C) < min) {
                *(s32 *)(arg0 + 0x2C) = min;
            }
            if (*(s32 *)(arg0 + 0x2C) >= hi) {
                *(s32 *)(arg0 + 0x2C) = hi;
            }
            func_80147A84(arg0);
            if (*(s32 *)(arg0 + 0x23C) == 0) {
                lo2 = -0x94000;
                t = *(s32 *)(arg0 + 0x2C);
                if (t < lo2) {
                    func_80154150(arg0, 8);
                } else if (t < -0x70000) {
                    ((void (*)(s32, s32, s32))func_801541D8)(arg0, 7, func_8015AB7C(arg0) & 0xFFFF);
                } else {
                    func_80154150(arg0, 6);
                }
            }
            break;
        }
    }

    ((void (*)(s32))func_801473EC)(arg0);
    if ((min >= *(s32 *)(arg0 + 0x2C)) && !(D_800B99DA & 7)) {
        func_8014C010(arg0, 2);
    }
    if (((s32 (*)(s32))func_8014D738)(arg0) != 0) {
        D_801891B8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015C6E0)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_8014E934)(arg0) != 0) {
        ((void (*)(s32))func_80155440)(arg0);
        func_80154150(arg0, 0x12);
        func_80154A74(arg0, 0x17);
        *(s32 *)(arg0 + 0x23C) = 1;
    } else {
        if (*(s32 *)(arg0 + 0x23C) != 0) {
            func_801553C0(arg0);
            func_80154150(arg0, 6);
            func_80154A74(arg0, 0x21);
        }
        *(s32 *)(arg0 + 0x23C) = 0;
    }
    if (((s32 (*)(s32))func_80161278)(arg0) == 0) {
        if (*(u16 *)(arg0 + 0xB8) & 0x2000) {
            func_80161C24(arg0, *(u16 *)(arg0 + 0x16E));
        }
        ((void (*)(s32))func_80172608)(arg0);
        ((void (*)(s32))func_801483E8)(arg0);
    }
}


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
