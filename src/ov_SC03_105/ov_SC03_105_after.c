#include "common.h"
#include "../shared/engine_prelude.h"


/* func_801457A4 (@0x801457A4) is an -O0 function; its definition lives in ov_SC03_105_o0b.c (the -O0
 * whale object, whose .text ends exactly at this address). Mirrors ov_SC01_077. §116 */
#include "../shared/ov/func_801458E0.h"

#include "../shared/ov/func_801458E8.h"


// @class: schedule
// @unstuck(P36): none — MATCH (else-if >= ladder + §5a cross-jump barrier in the first D_8018C880 block defeats the tail-merge of the two identical D_8018C880 loads; barrier emits zero bytes, load-bearing)

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);

extern u8 D_8018C880;
extern u8 D_8018C7F0;
extern u8 D_8018C7CC;
extern u8 D_8018C7A8;
extern u8 D_8018C85C;
extern u8 D_8018C838;
extern u8 D_8018C814;
extern u8 D_8018C784;

void func_80145934(void) {
    /* §5a cross-jump alias (replaces the memory barrier that used to sit in the >=0x6A4 arm).
     * Both the >=0x6A4 and the >=0x384 arm take the address of D_8018C880, so their blocks are the
     * identical pair `la a0,D_8018C880 / j <call>` and jump2's cross-jumper merges them (jump.c:1969).
     * find_cross_jump compares the two SYMBOL_REFs with rtx_renumbered_equal_p, which tests the name
     * STRING POINTERS (jump.c:2440 `case SYMBOL_REF: return XSTR (x, 0) == XSTR (y, 0);`), so a second
     * declaration of the same symbol under its own asm label gives the first arm a distinct string and
     * the two blocks stay separate.  Same bytes, same R_MIPS_HI16/LO16 D_8018C880 relocations. */
    extern u8 aD80192964 __asm__("D_8018C880");
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &aD80192964;
    } else if (v >= 0x5DC) {
        p = &D_8018C7F0;
    } else if (v >= 0x578) {
        p = &D_8018C7CC;
    } else if (v >= 0x514) {
        p = &D_8018C7A8;
    } else if (v >= 0x384) {
        p = &D_8018C880;
    } else if (v >= 0x258) {
        p = &D_8018C85C;
    } else if (v >= 0xC8) {
        p = &D_8018C838;
    } else if (v >= 0xA) {
        p = &D_8018C814;
    } else {
        p = &D_8018C784;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}




// @class: other
// @unstuck(P36): none — MATCH (62 ins). Sibling func_80145934 (byte-matched, same shape) is the template. Tail is default-then-conditional-override (matches asm .L80145AEC), and a §5a cross-jump barrier prevents the two identical D_8018C910 loads (>=0x6A4 and >=0x384) from being tail-merged.

extern s32 func_80029504(void);
extern void func_800D185C(u8 *a0);
extern void func_80145B24(void);

extern u8 D_8018C910;
extern u8 D_8018C7F0;
extern u8 D_8018C7CC;
extern u8 D_8018C7A8;
extern u8 D_8018C8EC;
extern u8 D_8018C8C8;
extern u8 D_8018C784;
extern u8 D_8018C8A4;

void func_80145A2C(void) {
    extern u8 aD801929F4 __asm__("D_8018C910");
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &aD801929F4;
    } else if (v >= 0x5DC) {
        p = &D_8018C7F0;
    } else if (v >= 0x578) {
        p = &D_8018C7CC;
    } else if (v >= 0x514) {
        p = &D_8018C7A8;
    } else if (v >= 0x384) {
        p = &D_8018C910;
    } else if (v >= 0x258) {
        p = &D_8018C8EC;
    } else if (v >= 0xC8) {
        p = &D_8018C8C8;
    } else {
        p = &D_8018C784;
        if (v >= 0xA) {
            p = &D_8018C8A4;
        }
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}


#include "../shared/ov/func_80145B24.h"

#include "../shared/ov/func_80145BF8.h"

#include "../shared/ov/func_80145C54.h"

// @class: struct
// @unstuck(P36): 2 residuals — (1) target RELOADS global ptr D_80126B78 before each of its 5 field accesses (f28/f18/f1a/f1c/f2c); gcc-2.7.2 CSEs the single pointer load in every clean-C form I tried (int-cast, (s8*)/(s32) M2C_FIELD, struct*), keeping ONE load. volatile forces reloads but hoists them + leaves delay-slot nops the target fills (target is NOT volatile). (2) frame 0x20 not 0x18: target reserves an unused 8-byte stack local @0x10 (address-taken local — reproduced, but every code-free escape optimizes away and a visible escape corrupts the func_80145EE8(0) arg). Structure/order/values/callees all match; only the alias-driven reload chain + the phantom frame local remain. Family exemplar (~130 overlays).



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
    extern s32 D_8018BCF8;
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
    D_80126B90 = (s32 *)&D_8018BCF8;
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
// @unstuck(P36): branch layout — 3-way dispatch on param_1; trying switch form

extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);

extern unsigned char D_8018BD08[];
extern unsigned char D_8018BD38[];
extern unsigned char D_8018BD88[];
extern unsigned char D_8018BDB8[];
extern unsigned char D_8018BDE8[];

void func_80145EE8(s32 param_1)
{
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))func_80029178)(0x1F) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BD08);
        }
        if (((unsigned char (*)(int))func_80029178)(0x21) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BD38);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1E) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BD88);
        }
        if (((unsigned char (*)(int))func_80029178)(0x1D) != 0) {
            ((void (*)(void *))func_80146014)(D_8018BDB8);
        }
        if (((unsigned char (*)(int))func_80029178)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))func_80146014)(D_8018BDE8);
        break;
    case 1:
        ((void (*)(void *))func_80146014)(D_8018BD08);
        ((void (*)(void *))func_80146014)(D_8018BD38);
        ((void (*)(void *))func_80146014)(D_8018BD88);
        ((void (*)(void *))func_80146014)(D_8018BDB8);
        ((void (*)(void *))func_80146014)(D_8018BDE8);
        break;
    }
}


#include "../shared/ov/func_80146014.h"

#include "../shared/ov/func_80146074.h"


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
        "lui   $at, %%hi(D_801B8490)\n"
        "sw    $v0, %%lo(D_801B8490)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8490)\n"
        "lw    $v0, %%lo(D_801B8490)($v0)\n"
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


#include "../shared/ov/func_80146128.h"


// @class: struct
// @unstuck(P36): none — MATCH (fnptr-table idiom: D_8018BE38[u8 idx](&arg))
extern void (*D_8018BE38[])(void *);
extern u8 D_80126BA4;

void func_80146360(void)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_80126B58;
    D_8018BE38[D_80126BA4](&D_80126B58);
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

#include "../shared/ov/func_801466B4.h"

#include "../shared/ov/func_801466F0.h"



#include "../shared/ov/func_80146750.h"


#include "../shared/ov/func_8014680C.h"

#include "../shared/ov/func_801468C8.h"

#include "../shared/ov/func_80146924.h"

#include "../shared/ov/func_80146994.h"

#include "../shared/ov/func_801469C8.h"

extern s32 func_80146AFC(void *arg0);
void aF80146A6C(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6) __asm__("func_80146A6C");
#include "../shared/ov/func_80146A6C.h"


#include "../shared/ov/func_80146AB4.h"

extern s32 func_80146B9C(void * arg0);

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

    extern s32 D_8011D030;
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



#include "../shared/ov/func_80146AFC.h"


#include "../shared/ov/func_80146B9C.h"

#include "../shared/ov/func_80146C3C.h"

#include "../shared/ov/func_80146C98.h"

#include "../shared/ov/func_80146CA0.h"

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

#include "../shared/ov/func_80147514.h"

#include "../shared/ov/func_80147628.h"

#include "../shared/ov/func_80147718.h"

#include "../shared/ov/func_80147788.h"

#include "../shared/ov/func_801477A8.h"

#include "../shared/ov/func_801477C8.h"

#include "../shared/ov/func_801477E8.h"

#include "../shared/ov/func_80147814.h"

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

#include "../shared/ov/func_80147C30.h"

#include "../shared/ov/func_80147CC8.h"

#include "../shared/ov/func_80147D38.h"

#include "../shared/ov/func_80147DC0.h"

#include "../shared/ov/func_80147E44.h"

#include "../shared/ov/func_80147F50.h"

#include "../shared/ov/func_80147F78.h"

#include "../shared/ov/func_80148038.h"

#include "../shared/ov/func_80148094.h"

#include "../shared/ov/func_801483E8.h"

#include "../shared/ov/func_801484B0.h"

#include "../shared/ov/func_801484E8.h"

#include "../shared/ov/func_80148534.h"

#include "../shared/ov/func_8014856C.h"

#include "../shared/ov/func_801485B8.h"

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
// @unstuck(P36): none — MATCH (71 ins). switch binary-tree; s1 angle = pin-source-of-copy ($5 temp + retie); 2nd-block double-load + 0x80-clobber via $v1/$v0/$a0 pins + lazy hi-pin reusing dead c80 reg

extern s32 ratan2(s32 a0, s32 a1);

int func_80148AFC(void *a0) {

    extern s32 D_801151D4;
    extern s32 (*D_8018BE40[])(void *, s32);
    s32 p = (s32)a0;
    s32 iVar5 = *(s32 *)(p + 0x20);
    s32 tmp = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                      *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 ang = tmp;

    switch (*(u8 *)(p + 0xA9)) {
    case 0x41:
        return D_8018BE40[*(u16 *)(p + 0xAA) >> 12](a0, tmp) & 0xFF;
    case 0x53:
    case 0x73:
        if ((*(u16 *)(p + 0xAE) & 0xFF) == 0x80 && (*(u16 *)(p + 0xAE) >> 8) == 0x80) {
            return 0;
        }
        tmp = ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8));
        *(u16 *)(iVar5 + 0x12) = (ang + tmp) & 0xFFF;
        return 1;
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

#include "../shared/ov/func_80148CB4.h"

#include "../shared/ov/func_80148CCC.h"

#include "../shared/ov/func_80148CE4.h"

#include "../shared/ov/func_80148CEC.h"

#include "../shared/ov/func_80148CF4.h"

#include "../shared/ov/func_80148D0C.h"

#include "../shared/ov/func_80148D24.h"

#include "../shared/ov/func_80148D3C.h"


// @class: schedule
// @unstuck(P36): none — MATCH (68 ins)
extern s32 ratan2(s32 a0, s32 a1);

s32 func_80148D44(void) {

    extern s32 D_801151D4;
    extern u8 D_80126C01;
    extern u16 D_80126C02;
    extern u16 D_80126C06;
    extern s16 (*D_8018BE80[])(s32);
    s32 p = D_801151D4;
    s32 tmp = (ratan2(*(s32 *)(p + 0x44) - *(s32 *)(p + 0x50),
                      *(s32 *)(p + 0x48) - *(s32 *)(p + 0x3C)) - 0x400) & 0xFFF;
    s32 ang = tmp;

    switch (D_80126C01) {
    case 0x41:
        return D_8018BE80[D_80126C02 >> 12](tmp);
    case 0x53:
    case 0x73:
        if ((D_80126C06 & 0xFF) == 0x80 && (D_80126C06 >> 8) == 0x80) {
            return -1;
        }
        tmp = ratan2((D_80126C06 & 0xFF) - 0x80, 0x80 - (D_80126C06 >> 8));
        return (ang + tmp) & 0xFFF;
    }
}



extern s32 ratan2(s32, s32);
/* derived from asm: lui/addu/lw %lo(D_8018BEC0) indexed by (u16>>12)*4, then jalr, the handler taking the angle in $a0 as its first argument (P36 S103 agent c12: the missing copy was that argument);
 * the result is sign-extended from 16 bits => the table's functions return s16. */

s32 func_80148E54(s32 arg0) {

    extern s32 D_801151D4;
    extern s16 (*D_8018BEC0[])(s32);
    s32 tmp = (ratan2(*(s32 *)(D_801151D4 + 0x44) - *(s32 *)(D_801151D4 + 0x50),
                      *(s32 *)(D_801151D4 + 0x48) - *(s32 *)(D_801151D4 + 0x3C)) - 0x400) & 0xFFF;
    s32 ang = tmp;

    switch (*(u8 *)(arg0 + 0xA9)) {
    case 0x41:
        return D_8018BEC0[*(u16 *)(arg0 + 0xAA) >> 12](tmp);
    case 0x53:
    case 0x73:
        if ((*(u16 *)(arg0 + 0xAE) & 0xFF) == 0x80 && (*(u16 *)(arg0 + 0xAE) >> 8) == 0x80) {
            return -1;
        }
        tmp = ratan2((*(u16 *)(arg0 + 0xAE) & 0xFF) - 0x80,
                             0x80 - (*(u16 *)(arg0 + 0xAE) >> 8));
        return (ang + tmp) & 0xFFF;
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

#include "../shared/ov/func_80149374.h"

#include "../shared/ov/func_801493D0.h"

#include "../shared/ov/func_8014942C.h"

#include "../shared/ov/func_80149450.h"

#include "../shared/ov/func_801494CC.h"

#include "../shared/ov/func_80149544.h"

#include "../shared/ov/func_80149584.h"

#include "../shared/ov/func_801495C4.h"



// @class: regalloc-order
// @unstuck(P36): none — MATCH (34 ins). param_2 pinned to $s0; the two stack out-bufs (in@0x10,
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

#include "../shared/ov/func_801498E0.h"

#include "../shared/ov/func_80149954.h"

#include "../shared/ov/func_80149A64.h"

#include "../shared/ov/func_80149AA8.h"

#include "../shared/ov/func_80149AD4.h"

#include "../shared/ov/func_80149B14.h"

#include "../shared/ov/func_80149B54.h"

#include "../shared/ov/func_80149BAC.h"

#include "../shared/ov/func_80149BEC.h"

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
// @unstuck(P36): none — MATCH (38 ins)
extern s32 D_8018BF00[];
extern u8 D_80078E78[];
extern s16 currentLocationId;

s32 func_80149FB0(s32 a0) {
    s32 *p = &D_8018BF00[0];
    s32 v = *p;
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
// @unstuck(P36): none — MATCH (90 ins). Keys: (1) single Loc struct pins the 0x10..0x25 stack
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

#include "../shared/ov/func_8014B7A4.h"

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

#include "../shared/ov/func_8014C168.h"



extern void func_8014C1C8(s32 arg0, s32 arg1, void *arg2);
extern u8 D_8018BF88[];

void func_8014C1A0(s32 arg0, s32 arg1) {
    func_8014C1C8(arg0, arg1, D_8018BF88);
}


#include "../shared/ov/func_8014C1C8.h"

#include "../shared/ov/func_8014C278.h"

#include "../shared/ov/func_8014C2B0.h"

#include "../shared/ov/func_8014C308.h"

#include "../shared/ov/func_8014C3A4.h"

#include "../shared/ov/func_8014C3D0.h"

#include "../shared/ov/func_8014C43C.h"


/* §37/§73/§124 asm-label alias: the fleet canon declares this `extern void` (engine_core.h, inside 8
 * DEFINE_func_* macros); the byte-true body must return s32.  Aliasing the C name sidesteps the
 * RETURN-axis conflict with no header edit.  This line MUST travel with the body. */
s32 aF8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4) __asm__("func_8014C4AC");

#include "../shared/ov/func_8014C4AC.h"



#include "../shared/ov/func_8014C568.h"


#include "../shared/ov/func_8014C59C.h"


extern u8 D_8018BF90;
extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);

s16 func_8014C5D0(s32 a0, s32 a1) {
    return func_8014C5FC(a0, a1, &D_8018BF90);
}


#include "../shared/ov/func_8014C5FC.h"

#include "../shared/ov/func_8014C6AC.h"

#include "../shared/ov/func_8014C6C0.h"

#include "../shared/ov/func_8014C6D0.h"

#include "../shared/ov/func_8014C6E0.h"



// @class: schedule
// @unstuck(P36): none — MATCH (match_one 91/91)
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


#include "../shared/ov/func_8014C8C8.h"


#include "../shared/ov/func_8014C8F0.h"

#include "../shared/ov/func_8014C918.h"

#include "../shared/ov/func_8014C968.h"

#include "../shared/ov/func_8014C978.h"

#include "../shared/ov/func_8014C98C.h"

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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014CD0C.h"

#include "../shared/ov/func_8014CD80.h"

#include "../shared/ov/func_8014CF04.h"



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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014D0A4.h"


#include "../shared/ov/func_8014D12C.h"



#include "../shared/ov/func_8014D2A0.h"



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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014D438.h"

#include "../shared/ov/func_8014D4C0.h"


#include "../shared/ov/func_8014D610.h"



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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014D790.h"

extern void func_8012AAAC(void *arg0);

// @class: schedule
// @unstuck(P36): none — MATCH (304/304), symcheck SYMS-OK 12/12, and the whole-TU cc1 stage now compiles CLEAN
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
// `u8 D_8018BF98[]`, `s16 currentLocationId`. symcheck: SYMS-OK, 12 symbols agree.
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
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 a0, s32 a1, s32 a2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
s32 func_8014D820(s32 a0, u16 *a1, u16 *a2)
{

    extern u8 D_801202A0[];
    extern u8 D_8018BF98[];
    extern u8 D_801152A8[];
    extern s16 D_801152AC;
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
  t = a2[0];
  u = a1[0];
  dx = t - u;
a0v = a0;
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
  if (func_80135A4C(ent->f20, ent->f58, (s32 *) a1, (s32) a2) == 0)
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
    func_800139C8(ang, D_8018BF98, &out[0]);
    func_800139C8((s16) (ang - 0x155), D_8018BF98, &out[1]);
    func_800139C8((s16) (ang + 0x155), D_8018BF98, &out[2]);
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


#include "../shared/ov/func_8014DCE0.h"


#include "../shared/ov/func_8014DD8C.h"



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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014DF94.h"

#include "../shared/ov/func_8014E048.h"

#include "../shared/ov/func_8014E284.h"


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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014E48C.h"

#include "../shared/ov/func_8014E514.h"

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
extern s32 func_8014E5B4(s32 a0, void *a1, void *a2);

#include "../shared/ov/func_8014E5B4.h"



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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014E6F8.h"

#include "../shared/ov/func_8014E790.h"

#include "../shared/ov/func_8014E83C.h"


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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014E98C.h"

#include "../shared/ov/func_8014EA4C.h"



// @class: other
// @unstuck(P36): none — MATCH (handwritten full inline-asm scratchpad-stack-switch wrapper; no trailing .set reorder — that adds a stray epilogue nop)
/*
 * HANDWRITTEN scratchpad-stack-switch wrapper: temporarily repoints $sp into the
 * D-cache scratchpad stack held at *(0x1F8003FC), calls func_8014ED80, stashes the
 * return value through D_801B8498, restores $sp and returns it.
 * Manipulating $sp is not expressible in C; full inline asm (manages its own frame).
 */
extern s32 func_8014ED80(struct SubED80 *a0);
extern int D_801B8498;

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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014ED80.h"

#include "../shared/ov/func_8014EE14.h"


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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014F24C.h"

#include "../shared/ov/func_8014F2E0.h"

#include "../shared/ov/func_8014F3E8.h"



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
        "lui   $at, %%hi(D_801B849C)\n"
        "sw    $v0, %%lo(D_801B849C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B849C)\n"
        "lw    $v0, %%lo(D_801B849C)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014F4C0.h"


// @class: plumbing
// @unstuck(P36): none — MATCH (22 ins, relocation-masked). Handwritten scratchpad-stack-switch
//         wrapper, full inline asm like DEFINE_func_80155FF8. NOTE: do NOT write an explicit
//         "nop" after "jal func_8014F74C" — maspsx --aspsx-version=2.56 auto-fills the jal
//         delay slot with a nop; an explicit one yields a double-nop (+1 ins). %hi/%lo must be
//         escaped as %%hi/%%lo inside __asm__ (bare % is read as an operand placeholder).

/* HANDWRITTEN scratchpad-stack-switch wrapper (same idiom as func_80155FF8 /
 * func_80128564): temporarily repoints $sp into the D-cache scratchpad stack held
 * at *(0x1F8003FC), calls func_8014F74C, stores its $v0 result to D_801B849C, then
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
        "lui   $at, %%hi(D_801B849C)\n"
        "sw    $v0, %%lo(D_801B849C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B849C)\n"
        "lw    $v0, %%lo(D_801B849C)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014F74C.h"



// @class: other
// @unstuck(P36): none — MATCH (full inline-asm $sp-switch trampoline w/ 0x40000 guard, jal func_8014FA70, stash D_801B849C; maspsx auto-fills jal delay slot)

extern s32 func_8014FA70(s32 a0);
extern s32 D_801B849C;

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
        "lui   $at, %%hi(D_801B849C)\n"
        "sw    $v0, %%lo(D_801B849C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B849C)\n"
        "lw    $v0, %%lo(D_801B849C)($v0)\n"
        "1:\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014FA70.h"

// @class: other
// @unstuck(P36): none — MATCH (22 ins, relocation-masked). Handwritten scratchpad-stack-switch
//   trampoline: byte-identical to the matched in-TU sibling func_8014F6F4 (line ~2005),
//   differing ONLY in the callee (func_8014FC18 vs func_8014F74C). Full inline asm manages
//   its own frame; both the callee and the D_801B849C global live inside the asm, so NO C
//   externs are declared — this sidesteps the canonical-sig-layer reconcile that CC1_FAILed
//   the register-asm draft (func_8014FC18/D_801B849C are declared elsewhere in the TU).
//   maspsx --aspsx-version=2.56 auto-fills the jal delay slot with a nop, so do NOT write an
//   explicit nop after `jal` (double-nop = +1 ins); %hi/%lo escaped as %% inside __asm__.
//   gcc emits only the `jr $ra; nop` epilogue (leaf, no locals it can see) → exactly 22 ins.
s32 func_8014FBC0() {
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
        "lui   $at, %%hi(D_801B849C)\n"
        "sw    $v0, %%lo(D_801B849C)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B849C)\n"
        "lw    $v0, %%lo(D_801B849C)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}



#include "../shared/ov/func_8014FC18.h"


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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_8014FD54.h"

#include "../shared/ov/func_8014FDF4.h"

#include "../shared/ov/func_8014FE60.h"




#include "../shared/ov/func_8014FFDC.h"


#include "../shared/ov/func_80150150.h"

#include "../shared/ov/func_80150170.h"


#include "../shared/ov/func_801502EC.h"


#include "../shared/ov/func_80150460.h"


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
        "lui   $at, %%hi(D_801B8498)\n"
        "sw    $v0, %%lo(D_801B8498)($at)\n"
        "addiu $sp, $sp, 4\n"
        "lw    $sp, 0($sp)\n"
        "lui   $v0, %%hi(D_801B8498)\n"
        "lw    $v0, %%lo(D_801B8498)($v0)\n"
        "lw    $ra, 16($sp)\n"
        "addiu $sp, $sp, 24\n"
        : : : "memory");
}


#include "../shared/ov/func_801504D8.h"

#include "../shared/ov/func_80150528.h"

extern s32 func_801506A4();
#include "../shared/ov/func_801505FC.h"



s32 func_801506A4(s32 arg0, s32 arg1) {
    extern void func_80150820(int, unsigned short);
    extern void func_8015086C(int);
    extern unsigned short D_8018BFA8[];
    extern unsigned short D_8018BFB0[];
    extern unsigned short D_8018BFB8[];

    int mode;

    mode = ((struct Ent_801506A4 *)arg1)->unk0;
    ((struct Ent_801506A4 *)arg1)->unk5C |= 1;
    switch (mode) {
    case 0x31:
        ((void(*)(int))func_80147324)(0x452);
        ((void(*)(int, unsigned))func_8014ADA8)(((int)arg0), D_8018BFA8[((struct Ent_801506A4 *)arg1)->unk70]);
        ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 3, D_8018BFA8[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0x32:
        if ((*(unsigned short*)&D_80078EB4) != 0) {
            ((void(*)(int))func_80147324)(0x452);
            ((void(*)(int, unsigned, int))func_8014BB24)(((int)arg0), D_8018BFB0[((struct Ent_801506A4 *)arg1)->unk70], 1);
            ((void(*)(int, int, unsigned))func_8014ACE8)(((int)arg0), 2, D_8018BFB0[((struct Ent_801506A4 *)arg1)->unk70]);
        }
        break;
    case 0x33:
        ((void(*)(int))func_80147324)(0x452);
        func_80150820(((int)arg0), D_8018BFB8[((struct Ent_801506A4 *)arg1)->unk70]);
        break;
    case 0xC5:
    case 0x27B:
        ((void(*)(int))func_80147324)(0x452);
        func_8015086C(((int)arg0));
        break;
    }
}



#include "../shared/ov/func_80150820.h"

#include "../shared/ov/func_8015086C.h"

#include "../shared/ov/func_801508B4.h"

#include "../shared/ov/func_801508F8.h"


extern S16 D_801B781C;
extern s32 D_8018BFC0;
extern s32 D_80126990;
extern s32 D_80126994;
extern u8 D_80126948[];
extern s32 func_80021174(s32 a0, s32 a1);

s32 func_8015094C(s32 param_1) {
    struct { s32 x, mid, y; s32 _pad[9]; } arg;   /* 0x30 @ 0x10 */
    S16 local;                                     /* 0x10 @ 0x40 */
    s32 pad1[4];                                    /* 0x10 @ 0x50 */
    u8 *cam = D_80126948;
    s32 ret;

    local = D_801B781C;
    arg.x = *(short *)(param_1 + 6);
    arg.mid = D_80126994;
    arg.y = *(short *)(param_1 + 0xe);
    ret = func_80021174(D_8018BFC0, (s32)&arg);
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
extern s32 D_801B849C;

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
        "lui   $at, %%hi(D_801B849C)\n"
        "sw    $v0, %%lo(D_801B849C)($at)\n"
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
// @unstuck(P36): none — MATCH (fn-ptr table; split idx-1 into a $v0-pinned temp to stop (idx-1)*4 strength-reducing into a -4 load offset AND land the subtract in $v0)


void func_80150B28(int param_1) {

    extern s32 D_800AE6B0;
    extern void (*D_8018BFC4[])(void);
    u32 idx;
    u32 sub;

    if ((D_800AE6B0 & 0x80FFFFFF) == 0) {
        idx = *(u16 *)(param_1 + 0x16C);
        if (idx != 0 && idx < 0x26) {
            sub = idx - 1;
            D_8018BFC4[sub]();
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

#include "../shared/ov/func_80151780.h"

#include "../shared/ov/func_80151878.h"

#include "../shared/ov/func_80151880.h"

#include "../shared/ov/func_801518D8.h"

#include "../shared/ov/func_80151924.h"



void func_80151944(void *a0) {

    extern void (*D_8018C058[])(void);
    D_8018C058[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80151980.h"

#include "../shared/ov/func_801519C8.h"

#include "../shared/ov/func_80151AE4.h"

#include "../shared/ov/func_80151B98.h"

#include "../shared/ov/func_80151C54.h"


extern void (*D_8018C068[])(void);

void func_80151D24(void *a0) {
    D_8018C068[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80151D60.h"

#include "../shared/ov/func_80151DB0.h"

#include "../shared/ov/func_80151E78.h"

#include "../shared/ov/func_80151ECC.h"

#include "../shared/ov/func_80151F38.h"

#include "../shared/ov/func_80151FB4.h"


extern void (*D_8018C08C[])(void);

void func_80152058(void *a0) {
    D_8018C08C[*(u16 *)((s32)a0 + 0x2)]();
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
extern M2C_UNK D_8018C07C;

void func_801520DC(s32 arg0)
{
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_801472C8(arg0);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_8018C07C);
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



extern void (*D_8018C0A0[])(void);

void func_80152370(void *a0) {
    D_8018C0A0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_801523AC.h"


// @class: regalloc-order
// @unstuck(P36): none — MATCH (67 ins)


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
extern u8 D_8018C0AC[];

void func_801523F4(s32 arg0)
{
    s32 pad[4];
    s32 buf[4];
    s32 s0a;                    /* $s0 = buf */
    s32 s2a = (s32)&D_8018C0AC; /* $s2 = &D_8018C0AC */

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


#include "../shared/ov/func_80152500.h"

#include "../shared/ov/func_801525F4.h"


extern void (*D_8018C0BC[])(void);

void func_80152698(void *a0) {
    D_8018C0BC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_801526D4.h"

#include "../shared/ov/func_80152714.h"

#include "../shared/ov/func_80152790.h"


extern void (*D_8018C0D4[])(void);

void func_8015282C(void *a0) {
    D_8018C0D4[*(u16 *)((s32)a0 + 0x2)]();
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
extern M2C_UNK D_8018C0C4;

void func_801528B0(s32 arg0)
{
    func_80019064(&D_80062C04);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    func_80146DB8(arg0, &D_8018C0C4);
    func_801477E8(arg0, 0xFFF00000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


#include "../shared/ov/func_8015294C.h"

#include "../shared/ov/func_80152A08.h"

#include "../shared/ov/func_80152A50.h"

#include "../shared/ov/func_80152AC8.h"


extern void (*D_8018C0E8[])(void);

void func_80152B6C(void *a0) {
    D_8018C0E8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80152BA8.h"

#include "../shared/ov/func_80152BF0.h"

#include "../shared/ov/func_80152C40.h"

#include "../shared/ov/func_80152C80.h"


extern void (*D_8018C104[])(void);

void func_80152D24(void *a0) {
    D_8018C104[*(u16 *)((s32)a0 + 0x2)]();
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
extern M2C_UNK D_8018C0F4;

void func_80152DA8(s32 arg0)
{
    func_80019064(&D_80062C14);
    func_80151204(arg0, M2C_FIELD(arg0, s16 *, 0xF2));
    func_80149020(arg0);
    func_80154274(arg0, &D_800D5880);
    func_80147324(0x451);
    M2C_FIELD(arg0, s8 *, 0xDE) = 0x10;
    M2C_FIELD(arg0, s8 *, 0xDF) = 8;
    func_80146DB8(arg0, &D_8018C0F4);
    func_801477E8(arg0, 0xFFE40000);
    func_8014CBF8(arg0);
    func_801474EC(arg0);
    func_80146CA0(arg0);
}


#include "../shared/ov/func_80152E4C.h"

#include "../shared/ov/func_80152EFC.h"

#include "../shared/ov/func_80152F44.h"

#include "../shared/ov/func_80152FBC.h"


extern void (*D_8018C118[])(void);

void func_80153060(void *a0) {
    D_8018C118[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015309C.h"

#include "../shared/ov/func_801530E4.h"

#include "../shared/ov/func_80153150.h"

#include "../shared/ov/func_801531BC.h"

#include "../shared/ov/func_80153204.h"

#include "../shared/ov/func_8015327C.h"


extern void (*D_8018C12C[])(void);

void func_80153320(void *a0) {
    D_8018C12C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015335C.h"

#include "../shared/ov/func_801533A4.h"

#include "../shared/ov/func_80153410.h"

#include "../shared/ov/func_80153490.h"

#include "../shared/ov/func_801534D8.h"

#include "../shared/ov/func_80153550.h"


#include "../shared/ov/func_801535F4.h"


#include "../shared/ov/func_8015369C.h"

#include "../shared/ov/func_801536DC.h"

#include "../shared/ov/func_80153800.h"

#include "../shared/ov/func_80153978.h"

#include "../shared/ov/func_801539F8.h"

#include "../shared/ov/func_80153B58.h"

#include "../shared/ov/func_80153BD8.h"

#include "../shared/ov/func_80153BF0.h"

#include "../shared/ov/func_80153C18.h"

#include "../shared/ov/func_80153C30.h"

#include "../shared/ov/func_80153C44.h"

#include "../shared/ov/func_80153C74.h"

#include "../shared/ov/func_80153C8C.h"

#include "../shared/ov/func_80153C9C.h"

#include "../shared/ov/func_80153CBC.h"


// @class: struct
// @unstuck(P36): none — MATCH (expected); dispatch-table %lo-fold via extern fn-ptr array, s0 holds param across both calls
extern void func_80019064(void *a0);
extern s32 D_8018C140;
extern void (*D_8018C168[])(void *a0);
extern s16 D_8011DB0C;
extern u16 D_8011F748;

void func_80153CCC(S80153CCC *a0) {
    ((s32 (*)(s32))func_80019064)((s32)&D_8018C140);
    D_8018C168[a0->idx](a0);
    D_8011DB0C = 0;
    D_8011F748 = 0;
}


#include "../shared/ov/func_80153D34.h"


// @class: regalloc-order
// @unstuck(P36): none — MATCH (33/33)

extern void func_80147324(s32 arg0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern s16 currentLocationId;
extern u8 D_8018C148;

void func_80153D7C(s32 param_1)
{
    func_80147324(0x451);
    func_80154274((s32 *)param_1, (s32)&D_8018C148);
    func_80149020((s32 *)param_1);
    *(u16 *)(param_1 + 0x244) = *(u16 *)(param_1 + 6);
    *(u16 *)(param_1 + 0x246) = *(u16 *)(param_1 + 10);
    *(u16 *)(param_1 + 0x248) = *(u16 *)(param_1 + 0xe);
    if (currentLocationId == 0x3075) *(u8 *)(param_1 + 0xde) = 0x14;
    else *(u8 *)(param_1 + 0xde) = 10;
    *(u8 *)(param_1 + 0xdf) = 0;
    func_80146CA0((void *)param_1);
}


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

#include "../shared/ov/func_8015430C.h"

#include "../shared/ov/func_80154358.h"

#include "../shared/ov/func_80154418.h"
