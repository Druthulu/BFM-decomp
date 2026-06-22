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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013CA14);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D064);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D330);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D3D4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D53C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D8FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013D9B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013DBE4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E2C4);

DEFINE_func_8013E370()  /* dedup: shared engine-core @0x8013E370 (src/shared) */

DEFINE_func_8013E410()  /* dedup: shared engine-core @0x8013E410 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (27 ins)

DEFINE_func_8013E448()  /* dedup: shared engine-core @0x8013E448 (src/shared) */


DEFINE_func_8013E4B4()  /* dedup: shared engine-core @0x8013E4B4 (src/shared) */

DEFINE_func_8013E558()  /* dedup: shared engine-core @0x8013E558 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E588);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E5E8);

DEFINE_func_8013E67C()  /* dedup: shared engine-core @0x8013E67C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013E6AC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013F138);

DEFINE_func_8013F1BC()  /* dedup: shared engine-core @0x8013F1BC (src/shared) */

// @class: other
// @stuck: none — MATCH (cached &D_8011511A pointer for the $a1 accesses; test (iVar2<<16) without storing back so $v1 stays live)


DEFINE_func_8013F244()  /* dedup: shared engine-core @0x8013F244 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013F350);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013FAF8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8013FFD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014032C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140608);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801407F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140958);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140D68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140E6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80140F00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141100);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141874);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801418F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141A60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141B90);

DEFINE_func_80141C04()  /* dedup: shared engine-core @0x80141C04 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141C0C);

DEFINE_func_80141C50()  /* dedup: shared engine-core @0x80141C50 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80141CA4);

DEFINE_func_80142414()  /* dedup: shared engine-core @0x80142414 (src/shared) */

DEFINE_func_80142454()  /* dedup: shared engine-core @0x80142454 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801424E4);

extern s32 (*D_80187F50[])();

s32 func_801425CC(s16 *a0) {
    return D_80187F50[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142608);

DEFINE_func_801426D4()  /* dedup: shared engine-core @0x801426D4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142740);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801427EC);

DEFINE_func_80142838()  /* dedup: shared engine-core @0x80142838 (src/shared) */

DEFINE_func_801428CC()  /* dedup: shared engine-core @0x801428CC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014292C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142978);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801429C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142A10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142A80);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142BB4);

DEFINE_func_80142C7C()  /* dedup: shared engine-core @0x80142C7C (src/shared) */

DEFINE_func_80142C84()  /* dedup: shared engine-core @0x80142C84 (src/shared) */

DEFINE_func_80142C9C()  /* dedup: shared engine-core @0x80142C9C (src/shared) */

DEFINE_func_80142D38()  /* dedup: shared engine-core @0x80142D38 (src/shared) */

DEFINE_func_80142DB8()  /* dedup: shared engine-core @0x80142DB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142DC4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142E38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80142EC0);

DEFINE_func_80142F68()  /* dedup: shared engine-core @0x80142F68 (src/shared) */

DEFINE_func_80142FFC()  /* dedup: shared engine-core @0x80142FFC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014305C);

DEFINE_func_801430F4()  /* dedup: shared engine-core @0x801430F4 (src/shared) */

DEFINE_func_80143188()  /* dedup: shared engine-core @0x80143188 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801431E8);

DEFINE_func_801432FC()  /* dedup: shared engine-core @0x801432FC (src/shared) */

DEFINE_func_80143390()  /* dedup: shared engine-core @0x80143390 (src/shared) */

struct vec;
DEFINE_func_801433F0()  /* dedup: shared engine-core @0x801433F0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143458);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80143D28);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144090);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801442F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144364);

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


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014477C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144880);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80144B9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801457A4);

DEFINE_func_801458E0()  /* dedup: shared engine-core @0x801458E0 (src/shared) */

DEFINE_func_801458E8()  /* dedup: shared engine-core @0x801458E8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145934);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145A2C);

// @class: regalloc-order
// @stuck: none — MATCH (53 ins). Key: pin register u8 *p __asm__("$17") = &D_800AF630 (forces $s1 live across all calls + the -0x20 frame with $s1 saved), store *(s16*)(p+0xA3DA)=0x3000 at the end. Offset 0xA3DA = 0x800B9A0A - 0x800AF630.

DEFINE_func_80145B24()  /* dedup: shared engine-core @0x80145B24 (src/shared) */


DEFINE_func_80145BF8()  /* dedup: shared engine-core @0x80145BF8 (src/shared) */

DEFINE_func_80145C54()  /* dedup: shared engine-core @0x80145C54 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145CEC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80145EE8);

DEFINE_func_80146014()  /* dedup: shared engine-core @0x80146014 (src/shared) */

DEFINE_func_80146074()  /* dedup: shared engine-core @0x80146074 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014607C);

// @class: regalloc-order
// @stuck: none — MATCH (142 ins). Keys: pin $s0=&D_80126B58/$s1=D_80126B78; memcpy on u8[] symbols (unaligned lwl/lwr/swl/swr); if-branch uses D_80126B9C symbol, else-branch uses base+0x44; load p=D_80126B78 BEFORE setting base

#include "common.h"

DEFINE_func_80146128()  /* dedup: shared engine-core @0x80146128 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146360);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801463A0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801466F0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146750);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014680C);

/* canonical-sig: engine_core.h declares `extern s32 D_8011F750;` */
DEFINE_func_801468C8()  /* dedup: shared engine-core @0x801468C8 (src/shared) */

DEFINE_func_80146924()  /* dedup: shared engine-core @0x80146924 (src/shared) */

DEFINE_func_80146994()  /* dedup: shared engine-core @0x80146994 (src/shared) */

DEFINE_func_801469C8()  /* dedup: shared engine-core @0x801469C8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146A6C);

DEFINE_func_80146AB4()  /* dedup: shared engine-core @0x80146AB4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146AFC);

DEFINE_func_80146B9C()  /* dedup: shared engine-core @0x80146B9C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80146C3C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147364);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147E44);

DEFINE_func_80147F50()  /* dedup: shared engine-core @0x80147F50 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80147F78);

DEFINE_func_80148038()  /* dedup: shared engine-core @0x80148038 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148094);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801483E8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148AFC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148D44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80148E54);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149374);


DEFINE_func_801493D0()  /* dedup: shared engine-core @0x801493D0 (src/shared) */

DEFINE_func_8014942C()  /* dedup: shared engine-core @0x8014942C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149450);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801494CC);

DEFINE_func_80149544()  /* dedup: shared engine-core @0x80149544 (src/shared) */

/* arg-forwarding wrapper: stack buffer passed to two callees.
 * §17 array-decay — buf declared as a local array and passed bare so gcc
 * rematerializes addiu $sp,0x10 per use instead of hoisting into a
 * callee-saved reg (frame 0x20, only $s0 saved — matches target). */
DEFINE_func_80149584()  /* dedup: shared engine-core @0x80149584 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801495C4);

// @class: regalloc-order
// @stuck: none — MATCH (34 ins). param_2 pinned to $s0; the two stack out-bufs (in@0x10,
//   mid@0x20,out@0x18) would be HOISTED into $s1 across call1 (frame 0x38, +s1 save) — break
//   that with a per-use CSE-break barrier (`__asm__("":"=r"(p):"0"(p))`) on &in, mid(call1),
//   mid(call2) so each rematerializes `addiu reg,$sp,off` (frame 0x30, only $s0 saved). The
//   two independent arg setups (`lw $a0,0x20($a0)` vs `addiu $a2,$sp,0x20`) tie in sched2 —
//   force target order with VOLATILE barriers in textual order pin(&in)->mtx-load->mid.

typedef struct {
    /* 0x00 */ s16 f0;
    /* 0x02 */ s16 f2;
    /* 0x04 */ s16 f4;
    /* 0x06 */ s16 pad6;
} Vec3;

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801497A8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149F2C);

DEFINE_func_80149FA8()  /* dedup: shared engine-core @0x80149FA8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80149FB0);

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

typedef struct {
    /* 0x00 */ s16 a30;
    /* 0x02 */ s16 a2e;
    /* 0x04 */ s16 a2c;
    /* 0x06 */ s16 pad06;
    /* 0x08 */ s32 buf[2];
    /* 0x10 */ s16 a20;
    /* 0x12 */ s16 a1e;
    /* 0x14 */ s16 a1c;
} Loc;

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A51C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014A738);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014ADE0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C1C8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C4AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C568);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014C6F4);

DEFINE_func_8014C860()  /* dedup: shared engine-core @0x8014C860 (src/shared) */

DEFINE_func_8014C88C()  /* dedup: shared engine-core @0x8014C88C (src/shared) */

#include "common.h"

struct up { int a; int b; } __attribute__((packed));

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CCB4);

/* func_8014CD0C — overlay ov_SC01_077 shared core */
DEFINE_func_8014CD0C()  /* dedup: shared engine-core @0x8014CD0C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CD80);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014CF04);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D04C);

DEFINE_func_8014D0A4()  /* dedup: shared engine-core @0x8014D0A4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D12C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D2A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D3E0);

DEFINE_func_8014D438()  /* dedup: shared engine-core @0x8014D438 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D4C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D610);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D738);

DEFINE_func_8014D790()  /* dedup: shared engine-core @0x8014D790 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014D820);

#include "common.h"

DEFINE_func_8014DCE0()  /* dedup: shared engine-core @0x8014DCE0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014DD8C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014DF3C);

#include "common.h"

DEFINE_func_8014DF94()  /* dedup: shared engine-core @0x8014DF94 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E048);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E284);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E434);

DEFINE_func_8014E48C()  /* dedup: shared engine-core @0x8014E48C (src/shared) */

DEFINE_func_8014E514()  /* dedup: shared engine-core @0x8014E514 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E5B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E6A0);

DEFINE_func_8014E6F8()  /* dedup: shared engine-core @0x8014E6F8 (src/shared) */

s32 func_80135888(s32, s32, M2C_UNK, M2C_UNK);      /* extern */

DEFINE_func_8014E790()  /* dedup: shared engine-core @0x8014E790 (src/shared) */

DEFINE_func_8014E83C()  /* dedup: shared engine-core @0x8014E83C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014E934);

DEFINE_func_8014E98C()  /* dedup: shared engine-core @0x8014E98C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014EA4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014ED28);

DEFINE_func_8014ED80()  /* dedup: shared engine-core @0x8014ED80 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014EE14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F1F4);

DEFINE_func_8014F24C()  /* dedup: shared engine-core @0x8014F24C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F2E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F3E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F468);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F4C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F6F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014F74C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FA04);

DEFINE_func_8014FA70()  /* dedup: shared engine-core @0x8014FA70 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FBC0);

DEFINE_func_8014FC18()  /* dedup: shared engine-core @0x8014FC18 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FCFC);

// @class: regalloc-order
// @stuck: none — MATCH; pinned result to $v0 so ret lands in $v1 (target's alloc); func_80149290 3-arg via call-site cast

DEFINE_func_8014FD54()  /* dedup: shared engine-core @0x8014FD54 (src/shared) */


DEFINE_func_8014FDF4()  /* dedup: shared engine-core @0x8014FDF4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FE60);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8014FFDC);

DEFINE_func_80150150()  /* dedup: shared engine-core @0x80150150 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150170);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801502EC);

DEFINE_func_80150460()  /* dedup: shared engine-core @0x80150460 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150480);

DEFINE_func_801504D8()  /* dedup: shared engine-core @0x801504D8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150528);

DEFINE_func_801505FC()  /* dedup: shared engine-core @0x801505FC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801506A4);

DEFINE_func_80150820()  /* dedup: shared engine-core @0x80150820 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015086C);

DEFINE_func_801508B4()  /* dedup: shared engine-core @0x801508B4 (src/shared) */

DEFINE_func_801508F8()  /* dedup: shared engine-core @0x801508F8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015094C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150A70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80150B28);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015126C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151664);

DEFINE_func_801516F0()  /* dedup: shared engine-core @0x801516F0 (src/shared) */

DEFINE_func_8015173C()  /* dedup: shared engine-core @0x8015173C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151780);

DEFINE_func_80151878()  /* dedup: shared engine-core @0x80151878 (src/shared) */

DEFINE_func_80151880()  /* dedup: shared engine-core @0x80151880 (src/shared) */

DEFINE_func_801518D8()  /* dedup: shared engine-core @0x801518D8 (src/shared) */

DEFINE_func_80151924()  /* dedup: shared engine-core @0x80151924 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151944);

DEFINE_func_80151980()  /* dedup: shared engine-core @0x80151980 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (71 ins, relocation-masked)
#include "common.h"

DEFINE_func_801519C8()  /* dedup: shared engine-core @0x801519C8 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH expected; func_801542DC called 3-arg vs 2-arg canonical needs call-site cast

#include "common.h"

DEFINE_func_80151AE4()  /* dedup: shared engine-core @0x80151AE4 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151B98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80151C54);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801522CC);

extern void (*D_80188874[])(void *);

void func_80152370(void *a0)
{
    D_80188874[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_801523AC()  /* dedup: shared engine-core @0x801523AC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801523F4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80152C80);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153CCC);

DEFINE_func_80153D34()  /* dedup: shared engine-core @0x80153D34 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153D7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80153E00);

DEFINE_func_8015410C()  /* dedup: shared engine-core @0x8015410C (src/shared) */

DEFINE_func_80154134()  /* dedup: shared engine-core @0x80154134 (src/shared) */

DEFINE_func_80154150()  /* dedup: shared engine-core @0x80154150 (src/shared) */

DEFINE_func_80154190()  /* dedup: shared engine-core @0x80154190 (src/shared) */

DEFINE_func_801541D8()  /* dedup: shared engine-core @0x801541D8 (src/shared) */

DEFINE_func_80154218()  /* dedup: shared engine-core @0x80154218 (src/shared) */

DEFINE_func_80154274()  /* dedup: shared engine-core @0x80154274 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801542A4);

DEFINE_func_801542DC()  /* dedup: shared engine-core @0x801542DC (src/shared) */

#include "common.h"

DEFINE_func_8015430C()  /* dedup: shared engine-core @0x8015430C (src/shared) */

#include "common.h"

DEFINE_func_80154358()  /* dedup: shared engine-core @0x80154358 (src/shared) */

DEFINE_func_80154418()  /* dedup: shared engine-core @0x80154418 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015444C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801549F8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80154C24);

DEFINE_func_80154ED8()  /* dedup: shared engine-core @0x80154ED8 (src/shared) */

DEFINE_func_80154F9C()  /* dedup: shared engine-core @0x80154F9C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801550FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155150);

DEFINE_func_801552F4()  /* dedup: shared engine-core @0x801552F4 (src/shared) */

DEFINE_func_80155344()  /* dedup: shared engine-core @0x80155344 (src/shared) */

DEFINE_func_80155394()  /* dedup: shared engine-core @0x80155394 (src/shared) */

DEFINE_func_801553A8()  /* dedup: shared engine-core @0x801553A8 (src/shared) */

DEFINE_func_801553C0()  /* dedup: shared engine-core @0x801553C0 (src/shared) */

DEFINE_func_80155440()  /* dedup: shared engine-core @0x80155440 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155458);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801555F4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80155800);

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

void func_80155E30(void *a0) {
    volatile s32 spill[4];
    *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2;
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
        return;
    }
    if (((s32 (*)(s32 *))func_80161208)(a0) != 0) {
        return;
    }
    func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA));
}

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
DEFINE_func_80155FF8()  /* dedup: shared engine-core @0x80155FF8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156044);

#include "common.h"

DEFINE_func_8015616C()  /* dedup: shared engine-core @0x8015616C (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156370);

extern S801563EC D_80188B80[];

S801563EC *func_801563EC(u16 idx) {
    return &D_80188B80[idx];
}

DEFINE_func_8015640C()  /* dedup: shared engine-core @0x8015640C (src/shared) */

DEFINE_func_801564B0()  /* dedup: shared engine-core @0x801564B0 (src/shared) */

DEFINE_func_801565C0()  /* dedup: shared engine-core @0x801565C0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156600);

DEFINE_func_80156648()  /* dedup: shared engine-core @0x80156648 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156670);

DEFINE_func_801567BC()  /* dedup: shared engine-core @0x801567BC (src/shared) */

#include "common.h"

extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8);
extern void func_80156A1C(s32 a0, s32 a1);

typedef struct { s16 a; s16 b; s16 c; s16 d; } S8;
typedef struct { u8 b[8]; } B8;

extern s32 D_801151E0[];
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];

void func_80156848(s32 param_1, s32 param_2) {
    u32 uVar1;
    s32 i;
    u32 uVar3;
    u32 local_20[2];

    uVar3 = 0;
    i = 0;
    do {
        uVar1 = D_801151E0[uVar3];
        if (uVar1 & 1) {
            func_80013E94(&D_80128120[i], local_20);
            ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(*(u8 *)(param_2 + 8), param_1, (s32)D_80126AF0[i].a,
                          (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0],
                          *(u8 *)(param_2 + 9));
        } else if (uVar1 & 6) {
            func_80156A1C(param_1, uVar3);
            func_80013E94(&D_80128138[i], local_20);
            if ((D_801151E0[uVar3] & 6) == 4) {
                local_20[0] = local_20[0] | 0x80000000;
            }
            ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(6, param_1, (s32)D_80126AF0[i].a,
                          (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0], 0);
            if (D_80126730[uVar3] == 0x24) {
                ((void (*)(s32, s32, s32, s32, s32, s32, s32, s32))func_801469C8)(0x53, param_1, (s32)D_80126AF0[i].a,
                              (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0], 0, 0x14);
            }
        }
        uVar3 = uVar3 + 1;
        i = i + 1;
    } while (uVar3 < 3);
}


DEFINE_func_80156A14()  /* dedup: shared engine-core @0x80156A14 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156A1C);

DEFINE_func_80156A88()  /* dedup: shared engine-core @0x80156A88 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156B74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80156ECC);

#include "common.h"

DEFINE_func_80156FA8()  /* dedup: shared engine-core @0x80156FA8 (src/shared) */


extern void func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3,
                           s32 a4, s32 a5, s32 a6, s32 a7,
                           s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);

void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3,
                   s32 a4, s32 a5, s32 a6, s32 a7,
                   s32 a8, s32 a9, u16 a10, s32 a11, s32 a12) {
    func_801571C4(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801571C4);

DEFINE_func_801574DC()  /* dedup: shared engine-core @0x801574DC (src/shared) */

DEFINE_func_80157510()  /* dedup: shared engine-core @0x80157510 (src/shared) */

extern void (*D_80188E00[])(void *);

void func_80157544(void *a0)
{
    D_80188E00[*(u16 *)((s32)a0 + 0x2)](a0);
}

/* Canonical callee signatures (shared set; call-site casts where the byte-match
 * needs the $v0 return of a void-canonical callee). */
extern void func_8014CC28(s32 a0);      /* defined  */
extern void func_8014F3E8(s32 a0);      /* declared */
extern void func_8015BDD0(s32 *a0);     /* defined  */
extern void func_801575E4(void *a0);    /* defined  */

void func_80157580(s32 arg0) {
    s32 temp_s1;

    /* return-cast: canonical func_8014CC28 is void, but its $v0 is used here */
    temp_s1 = ((s32 (*)(s32))func_8014CC28)(arg0);
    /* return-cast: canonical func_8014F3E8 is void, but its $v0 is tested here */
    if ((((s32 (*)(s32))func_8014F3E8)(arg0) == 0) && (temp_s1 == 0)) {
        func_8015BDD0((s32 *)arg0);
        return;
    }
    func_801575E4((void *)arg0);
}

DEFINE_func_801575E4()  /* dedup: shared engine-core @0x801575E4 (src/shared) */

extern void func_801599A4(void *a0);   /* canonical: void(*)(void *) */
extern void func_80159B3C(void *a0);   /* canonical: void(*)(void *) */
extern s32 func_80161208(void);        /* canonical: s32(*)(void) — call-site cast to pass arg0 */
extern int func_80155FF8(int arg, int a1);

void func_801576A8(void *arg0) {
    volatile s32 spill[4];  /* forces the 0x28 frame the target reserves */
    *(s32 *)((u8 *)arg0 + 0x44) |= 2;
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        func_801599A4(arg0);
        func_80159B3C(arg0);
    } else if (((s32 (*)(void *))func_80161208)(arg0) == 0) {
        func_80155FF8((int)arg0, *(u8 *)((u8 *)arg0 + 0x1AA));
    }
}

DEFINE_func_8015771C()  /* dedup: shared engine-core @0x8015771C (src/shared) */

DEFINE_func_8015773C()  /* dedup: shared engine-core @0x8015773C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157788);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801577C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157808);

DEFINE_func_80157880()  /* dedup: shared engine-core @0x80157880 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801578C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015795C);

DEFINE_func_80157A8C()  /* dedup: shared engine-core @0x80157A8C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (43 ins). Fixed via §3-T4 branch-polarity: target fall-through is the (val>0) func_8016706C block, so put it in the `if` and the (val<=0) block in the `else` → blez to else, blocks in target order.

#include "common.h"

DEFINE_func_80157AC8()  /* dedup: shared engine-core @0x80157AC8 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157B74);

DEFINE_func_80157BC8()  /* dedup: shared engine-core @0x80157BC8 (src/shared) */

DEFINE_func_80157CCC()  /* dedup: shared engine-core @0x80157CCC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80157D20);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158038);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158434);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158548);

DEFINE_func_801585A4()  /* dedup: shared engine-core @0x801585A4 (src/shared) */

DEFINE_func_801585AC()  /* dedup: shared engine-core @0x801585AC (src/shared) */

DEFINE_func_801585EC()  /* dedup: shared engine-core @0x801585EC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158638);

DEFINE_func_80158794()  /* dedup: shared engine-core @0x80158794 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015879C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158814);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801588CC);

DEFINE_func_80158AB4()  /* dedup: shared engine-core @0x80158AB4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158AE4);

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


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158F00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80158FA4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159464);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801594E8);

extern void (*D_80189108[])(void *);

void func_80159698(void *a0)
{
    D_80189108[*(u8 *)((s32)a0 + 0x15)](a0);
}

DEFINE_func_801596D4()  /* dedup: shared engine-core @0x801596D4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801596F0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159A20);

DEFINE_func_80159B08()  /* dedup: shared engine-core @0x80159B08 (src/shared) */

DEFINE_func_80159B3C()  /* dedup: shared engine-core @0x80159B3C (src/shared) */

extern void (*D_80189300[])(void *);

void func_80159B70(void *a0)
{
    D_80189300[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_80159BAC()  /* dedup: shared engine-core @0x80159BAC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159BE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80159C84);

DEFINE_func_8015A1C8()  /* dedup: shared engine-core @0x8015A1C8 (src/shared) */

DEFINE_func_8015A1FC()  /* dedup: shared engine-core @0x8015A1FC (src/shared) */

DEFINE_func_8015A230()  /* dedup: shared engine-core @0x8015A230 (src/shared) */

extern void (*D_80189308[])(void *);

void func_8015A264(void *a0)
{
    D_80189308[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_8015A2A0()  /* dedup: shared engine-core @0x8015A2A0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A2D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015A3C8);

DEFINE_func_8015AB7C()  /* dedup: shared engine-core @0x8015AB7C (src/shared) */

/* func_8015ABD4 — overlay ov_SC01_077 shared core */
DEFINE_func_8015ABD4()  /* dedup: shared engine-core @0x8015ABD4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AC48);

DEFINE_func_8015AC90()  /* dedup: shared engine-core @0x8015AC90 (src/shared) */

DEFINE_func_8015ACC4()  /* dedup: shared engine-core @0x8015ACC4 (src/shared) */

DEFINE_func_8015AD08()  /* dedup: shared engine-core @0x8015AD08 (src/shared) */

extern void (*D_80189310[])(void *);

void func_8015AD3C(void *a0)
{
    D_80189310[*(u16 *)((s32)a0 + 0x2)](a0);
}

DEFINE_func_8015AD78()  /* dedup: shared engine-core @0x8015AD78 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015ADB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015AE2C);

// @class: regalloc-order
// @stuck: none — MATCH (48 ins)

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015B6F4 (src/shared) */


DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015B7B4 (src/shared) */

DEFINE_func_8015B858()  /* dedup: shared engine-core @0x8015B858 (src/shared) */

DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015B8F8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015B950);

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015BD8C (src/shared) */

DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015BDD0 (src/shared) */

struct Obj;
DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015BE04 (src/shared) */

extern void (*D_8018932C[])(void);

void func_8015BE38(struct Obj *a0) {
    D_8018932C[a0->idx]();
}

DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015BE74 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015BE94);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C030);

DEFINE_func_8015C08C()  /* dedup: shared engine-core @0x8015C08C (src/shared) */

DEFINE_func_8015C0C4()  /* dedup: shared engine-core @0x8015C0C4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C128);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C32C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C7E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015C944);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CA28);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CC74);

DEFINE_func_8015CCB0()  /* dedup: shared engine-core @0x8015CCB0 (src/shared) */

#include "common.h"

DEFINE_func_8015CCD0()  /* dedup: shared engine-core @0x8015CCD0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CD20);

DEFINE_func_8015CF24()  /* dedup: shared engine-core @0x8015CF24 (src/shared) */

#include "common.h"

void func_80147078(s32 *a0, s16 a1);
DEFINE_func_8015CF58()  /* dedup: shared engine-core @0x8015CF58 (src/shared) */


DEFINE_func_8015CF8C()  /* dedup: shared engine-core @0x8015CF8C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015CFC0);

DEFINE_func_8015CFFC()  /* dedup: shared engine-core @0x8015CFFC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D01C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D104);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D1B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D380);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D414);

DEFINE_func_8015D480()  /* dedup: shared engine-core @0x8015D480 (src/shared) */

DEFINE_func_8015D4B4()  /* dedup: shared engine-core @0x8015D4B4 (src/shared) */

extern s32 (*D_801893F0[])();

s32 func_8015D4E8(s16 *a0) {
    return D_801893F0[(u16)a0[1]]();
}

DEFINE_func_8015D524()  /* dedup: shared engine-core @0x8015D524 (src/shared) */

DEFINE_func_8015D544()  /* dedup: shared engine-core @0x8015D544 (src/shared) */

DEFINE_func_8015D57C()  /* dedup: shared engine-core @0x8015D57C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D5E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015D738);

DEFINE_func_8015DA5C()  /* dedup: shared engine-core @0x8015DA5C (src/shared) */

DEFINE_func_8015DA90()  /* dedup: shared engine-core @0x8015DA90 (src/shared) */

DEFINE_func_8015DAC4()  /* dedup: shared engine-core @0x8015DAC4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DAF8);

DEFINE_func_8015DB34()  /* dedup: shared engine-core @0x8015DB34 (src/shared) */

DEFINE_func_8015DB6C()  /* dedup: shared engine-core @0x8015DB6C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DBD4);

DEFINE_func_8015DC84()  /* dedup: shared engine-core @0x8015DC84 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DCB8);

extern void func_8014C1A0(s32 arg0, s32 arg1);
extern void func_80015978(s32 a0, s32 *a1);
s32 func_80029AAC();
DEFINE_func_8015DD74()  /* dedup: shared engine-core @0x8015DD74 (src/shared) */

DEFINE_func_8015DDF0()  /* dedup: shared engine-core @0x8015DDF0 (src/shared) */

DEFINE_func_8015DE24()  /* dedup: shared engine-core @0x8015DE24 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DE58);

DEFINE_func_8015DE94()  /* dedup: shared engine-core @0x8015DE94 (src/shared) */

DEFINE_func_8015DECC()  /* dedup: shared engine-core @0x8015DECC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015DF34);

DEFINE_func_8015DFE4()  /* dedup: shared engine-core @0x8015DFE4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E018);

void func_8014C1A0(s32 arg0, s32 arg1);
void func_80015978(s32 a0, s32 *a1);
s32 func_80029AAC(void);
void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

DEFINE_func_8015E0D4()  /* dedup: shared engine-core @0x8015E0D4 (src/shared) */

DEFINE_func_8015E150()  /* dedup: shared engine-core @0x8015E150 (src/shared) */

DEFINE_func_8015E184()  /* dedup: shared engine-core @0x8015E184 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E1B8);

DEFINE_func_8015E1F4()  /* dedup: shared engine-core @0x8015E1F4 (src/shared) */

DEFINE_func_8015E22C()  /* dedup: shared engine-core @0x8015E22C (src/shared) */

DEFINE_func_8015E288()  /* dedup: shared engine-core @0x8015E288 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E344);

DEFINE_func_8015E40C()  /* dedup: shared engine-core @0x8015E40C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E4B0);

extern void func_8013C9C4(void *a0);
extern s32 D_80189490;

void func_8015E588(void) {
    func_8013C9C4(&D_80189490);
}

DEFINE_func_8015E5B0()  /* dedup: shared engine-core @0x8015E5B0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E698);

DEFINE_func_8015E714()  /* dedup: shared engine-core @0x8015E714 (src/shared) */

DEFINE_func_8015E84C()  /* dedup: shared engine-core @0x8015E84C (src/shared) */

DEFINE_func_8015E880()  /* dedup: shared engine-core @0x8015E880 (src/shared) */

DEFINE_func_8015E8B4()  /* dedup: shared engine-core @0x8015E8B4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015E8E8);

DEFINE_func_8015E924()  /* dedup: shared engine-core @0x8015E924 (src/shared) */

DEFINE_func_8015E95C()  /* dedup: shared engine-core @0x8015E95C (src/shared) */

DEFINE_func_8015E9B8()  /* dedup: shared engine-core @0x8015E9B8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EA3C);

DEFINE_func_8015ED6C()  /* dedup: shared engine-core @0x8015ED6C (src/shared) */

DEFINE_func_8015EDA0()  /* dedup: shared engine-core @0x8015EDA0 (src/shared) */

DEFINE_func_8015EDD4()  /* dedup: shared engine-core @0x8015EDD4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EE08);

DEFINE_func_8015EE44()  /* dedup: shared engine-core @0x8015EE44 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EE7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015EEE0);

DEFINE_func_8015EF9C()  /* dedup: shared engine-core @0x8015EF9C (src/shared) */

DEFINE_func_8015EFA4()  /* dedup: shared engine-core @0x8015EFA4 (src/shared) */

DEFINE_func_8015EFD8()  /* dedup: shared engine-core @0x8015EFD8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F00C);

DEFINE_func_8015F048()  /* dedup: shared engine-core @0x8015F048 (src/shared) */

DEFINE_func_8015F080()  /* dedup: shared engine-core @0x8015F080 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F118);

DEFINE_func_8015F260()  /* dedup: shared engine-core @0x8015F260 (src/shared) */

DEFINE_func_8015F2BC()  /* dedup: shared engine-core @0x8015F2BC (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015F324(s32 *a0);

void func_8015F2F0(s32 *a0) {
    func_80147078(a0, 0x14);
    func_8015F324(a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F324);

DEFINE_func_8015F360()  /* dedup: shared engine-core @0x8015F360 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F380);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F448);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015F7D4);

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

void func_8015F948(s32 *param_1) {
    func_80147078(param_1, 0x15);
    if (((s32 (*)(s32 *))func_80161104)(param_1) != 0) {
        func_80154150((s32)param_1, 0x22);
        func_80154A74((s32)param_1, 0x1A);
        func_80146C98(param_1, 2);
    }
}


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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FAAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FAE8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FBE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FCC8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FD74);

DEFINE_func_8015FDCC()  /* dedup: shared engine-core @0x8015FDCC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FE70);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8015FF20);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160138);

DEFINE_func_80160174()  /* dedup: shared engine-core @0x80160174 (src/shared) */

DEFINE_func_801601AC()  /* dedup: shared engine-core @0x801601AC (src/shared) */

/* func_801601E4 — if *(u16*)(a0+0xB8) == 0x8000 run the 3-call setup sequence,
 * else dispatch func_80161208 (canonically (void); a0 passed via ptr-cast). */

DEFINE_func_801601E4()  /* dedup: shared engine-core @0x801601E4 (src/shared) */

/* func_80160244 — twin of func_801601E4 with constants 0x23/0x1B.
 * if *(u16*)(a0+0xB8) == 0x8000 run the 3-call setup, else dispatch func_80161208. */

DEFINE_func_80160244()  /* dedup: shared engine-core @0x80160244 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801602A4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016039C);

DEFINE_func_801603D8()  /* dedup: shared engine-core @0x801603D8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH

DEFINE_func_80160410()  /* dedup: shared engine-core @0x80160410 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160534);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016084C);

DEFINE_func_80160888()  /* dedup: shared engine-core @0x80160888 (src/shared) */

DEFINE_func_801608C0()  /* dedup: shared engine-core @0x801608C0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160920);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801609B8);

DEFINE_func_80160A28()  /* dedup: shared engine-core @0x80160A28 (src/shared) */

DEFINE_func_80160A74()  /* dedup: shared engine-core @0x80160A74 (src/shared) */

extern void func_80147078(s32 *a0, s16 a1);
extern void func_80160BB4(s32 *a0);

void func_80160ACC(s32 *a0) {
    func_80147078(a0, 0x1D);
    func_80160BB4(a0);
}

DEFINE_func_80160B00()  /* dedup: shared engine-core @0x80160B00 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160B34);

DEFINE_func_80160B70()  /* dedup: shared engine-core @0x80160B70 (src/shared) */

DEFINE_func_80160BB4()  /* dedup: shared engine-core @0x80160BB4 (src/shared) */

DEFINE_func_80160C28()  /* dedup: shared engine-core @0x80160C28 (src/shared) */

DEFINE_func_80160CB4()  /* dedup: shared engine-core @0x80160CB4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160D10);

DEFINE_func_80160DEC()  /* dedup: shared engine-core @0x80160DEC (src/shared) */

DEFINE_func_80160E3C()  /* dedup: shared engine-core @0x80160E3C (src/shared) */

DEFINE_func_80160E70()  /* dedup: shared engine-core @0x80160E70 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160EA4);

DEFINE_func_80160EE0()  /* dedup: shared engine-core @0x80160EE0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80160F00);

DEFINE_func_80160F70()  /* dedup: shared engine-core @0x80160F70 (src/shared) */

DEFINE_func_80160FE0()  /* dedup: shared engine-core @0x80160FE0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161034);

DEFINE_func_80161094()  /* dedup: shared engine-core @0x80161094 (src/shared) */

DEFINE_func_801610FC()  /* dedup: shared engine-core @0x801610FC (src/shared) */

DEFINE_func_80161104()  /* dedup: shared engine-core @0x80161104 (src/shared) */

DEFINE_func_80161124()  /* dedup: shared engine-core @0x80161124 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161208);

DEFINE_func_80161240()  /* dedup: shared engine-core @0x80161240 (src/shared) */

DEFINE_func_80161278()  /* dedup: shared engine-core @0x80161278 (src/shared) */

#include "common.h"

DEFINE_func_801612B8()  /* dedup: shared engine-core @0x801612B8 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016130C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161374);

DEFINE_func_80161418()  /* dedup: shared engine-core @0x80161418 (src/shared) */

DEFINE_func_80161450()  /* dedup: shared engine-core @0x80161450 (src/shared) */

DEFINE_func_80161488()  /* dedup: shared engine-core @0x80161488 (src/shared) */

DEFINE_func_801614E4()  /* dedup: shared engine-core @0x801614E4 (src/shared) */

DEFINE_func_8016151C()  /* dedup: shared engine-core @0x8016151C (src/shared) */

DEFINE_func_80161554()  /* dedup: shared engine-core @0x80161554 (src/shared) */

DEFINE_func_8016158C()  /* dedup: shared engine-core @0x8016158C (src/shared) */

DEFINE_func_801615C4()  /* dedup: shared engine-core @0x801615C4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016163C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161774);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161888);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016191C);

DEFINE_func_8016197C()  /* dedup: shared engine-core @0x8016197C (src/shared) */

DEFINE_func_801619A4()  /* dedup: shared engine-core @0x801619A4 (src/shared) */

DEFINE_func_801619D0()  /* dedup: shared engine-core @0x801619D0 (src/shared) */

DEFINE_func_80161A00()  /* dedup: shared engine-core @0x80161A00 (src/shared) */

DEFINE_func_80161A30()  /* dedup: shared engine-core @0x80161A30 (src/shared) */

DEFINE_func_80161A60()  /* dedup: shared engine-core @0x80161A60 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161A90);

DEFINE_func_80161B18()  /* dedup: shared engine-core @0x80161B18 (src/shared) */

DEFINE_func_80161B84()  /* dedup: shared engine-core @0x80161B84 (src/shared) */

#include "common.h"

DEFINE_func_80161BE0()  /* dedup: shared engine-core @0x80161BE0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161C24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161C98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161CD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161D20);

DEFINE_func_80161D58()  /* dedup: shared engine-core @0x80161D58 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161D88);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80161E08);

DEFINE_func_801620C4()  /* dedup: shared engine-core @0x801620C4 (src/shared) */

DEFINE_func_80162120()  /* dedup: shared engine-core @0x80162120 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016216C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801621CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801622C4);

extern void (*D_8018967C[])(void);

void func_80162330(void *a0) {
    D_8018967C[*(u8 *)((s32)a0 + 0x15)]();
}

DEFINE_func_8016236C()  /* dedup: shared engine-core @0x8016236C (src/shared) */

DEFINE_func_801623B8()  /* dedup: shared engine-core @0x801623B8 (src/shared) */

DEFINE_func_80162414()  /* dedup: shared engine-core @0x80162414 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162438);

DEFINE_func_801626B8()  /* dedup: shared engine-core @0x801626B8 (src/shared) */

DEFINE_func_80162714()  /* dedup: shared engine-core @0x80162714 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162760);

DEFINE_func_801627C0()  /* dedup: shared engine-core @0x801627C0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801627E8);

extern void (*D_801896C4[])(void);

void func_80162834(void *a0) {
    D_801896C4[*(u8 *)((s32)a0 + 0x1)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162870);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80162CCC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163408);

DEFINE_func_8016345C()  /* dedup: shared engine-core @0x8016345C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801634D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163534);

DEFINE_func_80163664()  /* dedup: shared engine-core @0x80163664 (src/shared) */

DEFINE_func_801636D0()  /* dedup: shared engine-core @0x801636D0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163764);

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

typedef struct { u32 a, b, c, d; } Blk16;

void func_80163A94(s32 param_1) {
    s32 iVar7;
    s32 iVar1;
    s32 iVar2;
    s32 iVar3;

    iVar7 = *(s32 *)(param_1 + 0x4c);
    *(u32 *)(iVar7 + 0x44) = *(u32 *)(iVar7 + 0x44) | 4;
    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001C214(iVar1, (s32)&D_800DE5A0);
        *(s32 *)(iVar1 + 0x20) = (s32)&D_800636C8;
        *(s16 *)(iVar1 + 0x1c) = 0x1800;
        *(s16 *)(iVar1 + 0x1a) = 0x1800;
        *(s16 *)(iVar1 + 0x18) = 0x1800;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0x10;
        func_80149374(iVar7, param_1 + 4);
        iVar3 = *(s32 *)(param_1 + 0x20);
        iVar2 = *(s32 *)(iVar7 + 0x20);
        *(Blk16 *)(iVar3 + 0x34) = *(Blk16 *)(iVar2 + 0x34);
        *(Blk16 *)(iVar3 + 0x44) = *(Blk16 *)(iVar2 + 0x44);
        *(s16 *)(iVar1 + 0x10) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x10);
        *(s16 *)(iVar1 + 0x12) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x12);
        *(s16 *)(iVar1 + 0x14) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x14);
        *(s16 *)(param_1 + 0x60) = *(s16 *)(iVar7 + 0x100);
        *(s16 *)(param_1 + 0x62) = *(s16 *)(iVar7 + 0x102);
        *(s16 *)(param_1 + 0x64) = *(s16 *)(iVar7 + 0x104);
        func_80147324(0x448);
        func_80146E90((s32 *)param_1, 0x10);
        func_80146A6C(0xd, (void *)param_1, 0, 0, 0, 0, 0);
        func_80146DE8((s32 *)param_1, 0, 0, 0xffe00000);
        func_80146CA0((void *)param_1);
    }
    return;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163C2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80163EC8);

DEFINE_func_80164270()  /* dedup: shared engine-core @0x80164270 (src/shared) */

DEFINE_func_801642AC()  /* dedup: shared engine-core @0x801642AC (src/shared) */

// @class: schedule
// @stuck: none — MATCH (match_one 57/57). Levers: decl-order regalloc (s1=a0, s0=*(s1+0x4c) like sibling func_801642AC) + branch-polarity invert on the A||B||C guard (THEN-block placed last, 17->4) + cached v44=*(s0+0x44) reused for &0x400 test and |0x10 + volatile barrier on s0 to anchor sh 0x188 before $a0 materialization (4->0).

DEFINE_func_8016432C()  /* dedup: shared engine-core @0x8016432C (src/shared) */


DEFINE_func_80164410()  /* dedup: shared engine-core @0x80164410 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164418);

#include "common.h"

DEFINE_func_80164530()  /* dedup: shared engine-core @0x80164530 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164744);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801647A4);

DEFINE_func_80164864()  /* dedup: shared engine-core @0x80164864 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164930);

DEFINE_func_80164A74()  /* dedup: shared engine-core @0x80164A74 (src/shared) */

DEFINE_func_80164ACC()  /* dedup: shared engine-core @0x80164ACC (src/shared) */

extern void (*D_8018972C[])(void);

void func_80164BA0(void *a0) {
    D_8018972C[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164BDC);

DEFINE_func_80164CD4()  /* dedup: shared engine-core @0x80164CD4 (src/shared) */

DEFINE_func_80164D4C()  /* dedup: shared engine-core @0x80164D4C (src/shared) */

DEFINE_func_80164DB0()  /* dedup: shared engine-core @0x80164DB0 (src/shared) */

DEFINE_func_80164DD0()  /* dedup: shared engine-core @0x80164DD0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164E40);

extern s32 (*D_8018973C[])();

s32 func_80164EA4(s16 *a0) {
    return D_8018973C[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80164EE0);

DEFINE_func_80164F44()  /* dedup: shared engine-core @0x80164F44 (src/shared) */

DEFINE_func_80165024()  /* dedup: shared engine-core @0x80165024 (src/shared) */

DEFINE_func_80165064()  /* dedup: shared engine-core @0x80165064 (src/shared) */

DEFINE_func_801650C4()  /* dedup: shared engine-core @0x801650C4 (src/shared) */

DEFINE_func_80165124()  /* dedup: shared engine-core @0x80165124 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165140);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801651B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165240);

DEFINE_func_8016533C()  /* dedup: shared engine-core @0x8016533C (src/shared) */

DEFINE_func_80165374()  /* dedup: shared engine-core @0x80165374 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801653B8);

DEFINE_func_801653F4()  /* dedup: shared engine-core @0x801653F4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801654A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165580);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80165A50);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166054);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801661CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166244);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166690);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166994);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80166F58);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016706C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801670E4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167540);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167714);

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

typedef struct { s32 w[8]; } Blk32;

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167AE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80167DBC);

// @class: struct
// @stuck: none — MATCH (99 ins, relocation-masked); array-decay (§18) kept mid/dir/pos stack-resident

DEFINE_func_80168070()  /* dedup: shared engine-core @0x80168070 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801681FC);

DEFINE_func_8016829C()  /* dedup: shared engine-core @0x8016829C (src/shared) */

DEFINE_func_80168328()  /* dedup: shared engine-core @0x80168328 (src/shared) */

#include "common.h"

void func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_80166690(s32 a0, s32 a1);
DEFINE_func_801683D8()  /* dedup: shared engine-core @0x801683D8 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168430);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801687CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168828);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80168B70);

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

void func_80168F40(void *arg0) {
    struct A a;
    struct B b;

    a.unk00 = *(u16 *)((u8 *)arg0 + 0x10);
    a.unk02 = *(u16 *)((u8 *)arg0 + 0x14);
    a.unk04 = *(u16 *)((u8 *)arg0 + 0x18);
    a.unk08 = *(u16 *)((u8 *)arg0 + 0x6);
    a.unk0A = *(u16 *)((u8 *)arg0 + 0xA);
    a.unk0C = *(u16 *)((u8 *)arg0 + 0xE);
    a.unk10 = 8;
    a.unk14 = 0xC0;
    a.unk12 = 0;
    a.unk11 = 0;
    a.unk16 = 0x80;
    a.unk15 = 0x80;
    *(struct Bv *)&b = *(struct Bv *)&D_800AE620;
    a.unk18 = 0x50000000;
    func_80016A5C(&a, &b);
}

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169228);

extern void (*D_80189B38[])(void);

void func_801693CC(void *a0) {
    D_80189B38[*(u16 *)((s32)a0 + 0x2)]();
}

// @class: regalloc-order
// @stuck: none — MATCH (proxy); s2/s1/s0 pins + array-decay reproduce the call-crossing regalloc

DEFINE_func_80169408()  /* dedup: shared engine-core @0x80169408 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016951C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169BBC);

DEFINE_func_80169E44()  /* dedup: shared engine-core @0x80169E44 (src/shared) */

extern void (*D_80189BFC[])(void);

void func_80169F00(void *a0) {
    D_80189BFC[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80169F3C);

DEFINE_func_80169FE0()  /* dedup: shared engine-core @0x80169FE0 (src/shared) */

extern void (*D_80189C34[])(void);

void func_8016A020(void *a0) {
    D_80189C34[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8016A05C()  /* dedup: shared engine-core @0x8016A05C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH

DEFINE_func_8016A08C()  /* dedup: shared engine-core @0x8016A08C (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A1CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A290);

extern void (*D_80189C40[])(void);

void func_8016A700(void *a0) {
    D_80189C40[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016A73C);

DEFINE_func_8016A890()  /* dedup: shared engine-core @0x8016A890 (src/shared) */

// @class: struct
// @stuck: none — expect MATCH (single-call leaf, stack-struct prim build + averaging writeback)

extern s32 func_80016A5C();
extern Blk20 D_800AE620;

typedef struct {
    short v0;   /* 0x00 */
    short v1;   /* 0x02 */
    short v2;   /* 0x04 */
    short pad6; /* 0x06 */
    short w0;   /* 0x08 */
    short w1;   /* 0x0A */
    short w2;   /* 0x0C */
    short padE; /* 0x0E */
    unsigned char b10; /* 0x10 */
    unsigned char b11; /* 0x11 */
    unsigned char b12; /* 0x12 */
    unsigned char b13; /* 0x13 */
    unsigned char b14; /* 0x14 */
    unsigned char b15; /* 0x15 */
    unsigned char b16; /* 0x16 */
    unsigned char b17; /* 0x17 */
    int   w18; /* 0x18 */
} Prim;

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016AB6C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016AFB0 (src/shared) */

#include "common.h"

DEFINE_func_8016B114()  /* dedup: shared engine-core @0x8016B114 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B234);

DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016B3F4 (src/shared) */

DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016B428 (src/shared) */

DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016B448 (src/shared) */

extern void (*D_80189D04[])(void);

void func_8016B4BC(void *a0) {
    D_80189D04[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B4F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B5C0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B6BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B834);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B91C);

DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016B964 (src/shared) */

DEFINE_func_8016B984()  /* dedup: shared engine-core @0x8016B984 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016B9F8);

DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016BA48 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BA68);

DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016BADC (src/shared) */

extern void (*D_80189D54[])(void);

void func_8016BBA4(void *a0) {
    D_80189D54[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BBE0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BD78);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BEA0);

DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016BF34 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BF50);

extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D9B50;

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_8016BFD0(a0, a1, a2, a3, &D_801D9B50);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016BFD0);

extern void (*D_80189D84[])(void);

void func_8016C14C(void *a0) {
    D_80189D84[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C188);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C2C4);

DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016C374 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C49C);

DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016C74C (src/shared) */

#include "common.h"

DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016C83C (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016C998);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016CB84);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016CBC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016CF04);

extern void (*D_80189DA8[])(void);

void func_8016D19C(void *a0) {
    D_80189DA8[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D1D8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D64C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016D688);

DEFINE_func_8016D778()  /* dedup: shared engine-core @0x8016D778 (src/shared) */

DEFINE_func_8016D848()  /* dedup: shared engine-core @0x8016D848 (src/shared) */

DEFINE_func_8016D984()  /* dedup: shared engine-core @0x8016D984 (src/shared) */

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016DA04 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DA30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DA7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DB34);

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016DBD8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DC20);

extern void (*D_80189E4C[])(void);

void func_8016DEA4(void *a0) {
    D_80189E4C[*(u16 *)((s32)a0 + 0x2)]();
}

DEFINE_func_8016DEE0()  /* dedup: shared engine-core @0x8016DEE0 (src/shared) */

extern void (*D_80189E54[])(void);

void func_8016DF20(void *a0) {
    D_80189E54[*(u16 *)((s32)a0 + 0x2)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016DF5C);

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

extern void func_8016E778(void);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E778);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E7C8);

DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016E8F0 (src/shared) */

#include "common.h"

DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016E918 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E95C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016E9EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EAC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EB3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EBA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EC0C);

DEFINE_func_8016ED6C()  /* dedup: shared engine-core @0x8016ED6C (src/shared) */

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ED8C (src/shared) */

DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016EDBC (src/shared) */


DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016EDEC (src/shared) */


DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016EE40 (src/shared) */

DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016EE94 (src/shared) */

DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016EF78 (src/shared) */

DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016EFA8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016EFC8);

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016F094 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F0AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F0E4);

/* func_8016F14C — read a packed fn-ptr+flags word at a0+0x1F8; mask off the high byte
 * (0x80FFFFFF) to recover the fn ptr (computed BEFORE the null check so gcc hoists the
 * lui+ori into the load-delay slot — load-bearing); if the word is nonzero, optionally
 * func_80148634(a0) when bit24 is set, then call the recovered fn ptr with a0. */

DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016F14C (src/shared) */

DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016F1AC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F1C4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8016F4C4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801705C0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801708B0);

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

void func_80170B48(int a0)
{
    func_8014706C(a0);
    func_80154274((s32 *)a0, (s32)D_8011F738);
    func_80171990((u8 *)a0);
    func_80170B90((u8 *)a0);
}

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170CF0);

extern void (*D_8018A04C[])(void *);

void func_80170D68(void *a0) {
    D_8018A04C[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170DA4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170DE0);

extern void (*D_8018A054[])(void *);

void func_80170E34(void *a0) {
    D_8018A054[*(u8 *)((s32)a0 + 0x216)](a0);
}

DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170E70 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80170EAC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017129C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801718AC);

DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */

// @class: struct
// @stuck: none — MATCH (expected); simple field accesses + tail call passing a0 unchanged

DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */


DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196C (src/shared) */

DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197C (src/shared) */

DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801719A4);

DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171A04 (src/shared) */

DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171A10 (src/shared) */

DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171A1C (src/shared) */

DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171A34 (src/shared) */

DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171A44 (src/shared) */

DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171A58 (src/shared) */

DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171A6C (src/shared) */

DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171A80 (src/shared) */

DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171A88 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171AB0);

DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171B10 (src/shared) */

DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171B44 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171B4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171C64);

DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171CC4 (src/shared) */

DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171D1C (src/shared) */

DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171D78 (src/shared) */

DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171E08 (src/shared) */

DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171EC8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80171FFC);

extern s32 func_8017248C(s32 a0, s32 a1);
extern void func_80146D90(s32 a0);
extern s32  ratan2(s32 a0, s32 a1);   /* ratan2 */
DEFINE_func_8017209C()  /* dedup: shared engine-core @0x8017209C (src/shared) */

DEFINE_func_80172170()  /* dedup: shared engine-core @0x80172170 (src/shared) */

DEFINE_func_801722CC()  /* dedup: shared engine-core @0x801722CC (src/shared) */

DEFINE_func_80172304()  /* dedup: shared engine-core @0x80172304 (src/shared) */

DEFINE_func_80172310()  /* dedup: shared engine-core @0x80172310 (src/shared) */

DEFINE_func_80172358()  /* dedup: shared engine-core @0x80172358 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801723C4);

DEFINE_func_80172414()  /* dedup: shared engine-core @0x80172414 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017248C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801726D0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172A2C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80172C50);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801730B4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801732C4);

DEFINE_func_801732F4()  /* dedup: shared engine-core @0x801732F4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017331C);

DEFINE_func_8017334C()  /* dedup: shared engine-core @0x8017334C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173374);

DEFINE_func_801733A4()  /* dedup: shared engine-core @0x801733A4 (src/shared) */

extern void func_8016F30C(void);
extern s32 func_80174650(s32);

void func_801733CC(s32 a0) {
    func_8016F30C();
    func_80174650(a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801733FC);

DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801734BC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173A60);

extern s32 (*D_8018A13C[])(void *);

s32 func_80173B4C(void *a0) {
    return D_8018A13C[*(u8 *)((s32)a0 + 0x214)](a0);
}

DEFINE_func_80173B88()  /* dedup: shared engine-core @0x80173B88 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173BC0);

DEFINE_func_80173C64()  /* dedup: shared engine-core @0x80173C64 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173CB4);

// @class: schedule
// @stuck: none — MATCH (55 ins). Levers: pin param_1->$s0 ($16) + a register ptr &D_80127508->$s1 ($17)
//   kept across the first block (reused for the !=0 test and the +4 arg); func_801399F0(*(s0+0x198))
//   reuses the outer-test $a0 load as its arg; and DUPLICATE func_80154274()+func_80171A1C() into BOTH
//   if/else arms (don't factor to a shared tail) -- gcc cross-jump-merges the two jals+epilogue but keeps
//   each arm's arg-setup, because the *(s0+0x198)=0 store lands in the !=0 arm's `j` delay slot and breaks
//   the suffix identity right before the merge point.

DEFINE_func_80173E1C()  /* dedup: shared engine-core @0x80173E1C (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80173EF8);

extern s32 func_80174188(s32 a0);
extern void func_801741A8(s32 a0);

void func_80174158(s32 a0) {
    func_80174188(a0);
    func_801741A8(a0);
}

DEFINE_func_80174188()  /* dedup: shared engine-core @0x80174188 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801741A8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174554);

DEFINE_func_80174584()  /* dedup: shared engine-core @0x80174584 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801745AC);

DEFINE_func_801745DC()  /* dedup: shared engine-core @0x801745DC (src/shared) */

DEFINE_func_80174604()  /* dedup: shared engine-core @0x80174604 (src/shared) */

DEFINE_func_80174630()  /* dedup: shared engine-core @0x80174630 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174650);

DEFINE_func_80174674()  /* dedup: shared engine-core @0x80174674 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174684);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801746A4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174BF4);

DEFINE_func_80174C60()  /* dedup: shared engine-core @0x80174C60 (src/shared) */

extern s32 func_80174CB0(s32, s32);

void func_80174C80(s32 a0) {
    s32 v;
    v = (*(u16 *)(a0 + 0xA0) - 0x16) & 0xFFF;
    *(s16 *)(a0 + 0xA0) = v;
    func_80174CB0(a0, v);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80174CB0);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175184);

DEFINE_func_801751D8()  /* dedup: shared engine-core @0x801751D8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175218);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175268);

DEFINE_func_801752BC()  /* dedup: shared engine-core @0x801752BC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175308);

// @class: remat
// @stuck: none — MATCH
DEFINE_func_80175414()  /* dedup: shared engine-core @0x80175414 (src/shared) */


DEFINE_func_80175454()  /* dedup: shared engine-core @0x80175454 (src/shared) */

DEFINE_func_80175494()  /* dedup: shared engine-core @0x80175494 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801754A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017553C);

DEFINE_func_80175590()  /* dedup: shared engine-core @0x80175590 (src/shared) */

DEFINE_func_80175624()  /* dedup: shared engine-core @0x80175624 (src/shared) */

DEFINE_func_80175668()  /* dedup: shared engine-core @0x80175668 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175690);

DEFINE_func_801756E4()  /* dedup: shared engine-core @0x801756E4 (src/shared) */

DEFINE_func_80175798()  /* dedup: shared engine-core @0x80175798 (src/shared) */

DEFINE_func_801757A0()  /* dedup: shared engine-core @0x801757A0 (src/shared) */

DEFINE_func_801757E0()  /* dedup: shared engine-core @0x801757E0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175820);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801758FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801759D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175AB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80175DA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176144);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176218);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176734);

DEFINE_func_80176D00()  /* dedup: shared engine-core @0x80176D00 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80176D94);

DEFINE_func_80176FF4()  /* dedup: shared engine-core @0x80176FF4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801770E0);

DEFINE_func_80177340()  /* dedup: shared engine-core @0x80177340 (src/shared) */

DEFINE_func_8017742C()  /* dedup: shared engine-core @0x8017742C (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801775E0);

DEFINE_func_801776EC()  /* dedup: shared engine-core @0x801776EC (src/shared) */

DEFINE_func_80177784()  /* dedup: shared engine-core @0x80177784 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801777BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801778A8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177940);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177B5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80177DA8);

// @class: regalloc-order
// @stuck: none — MATCH
typedef unsigned int uint;
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


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178004);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178840);

#include "common.h"

DEFINE_func_801788B8()  /* dedup: shared engine-core @0x801788B8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178970);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801789AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178B18);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178B70);

void func_80178BF8(s32 a0, s32 a1);
void func_80178CBC(s32 a0, s32 a1);

DEFINE_func_80178BB8()  /* dedup: shared engine-core @0x80178BB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178BF8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80178D40);

DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179B28 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80179B74);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A3D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017A4AC);

/* canonical: resident engine call @ 0x80059A80 (engine_core.h) */
DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017AD0C (src/shared) */

DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ADE8 (src/shared) */

DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017AE08 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017AE2C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B0E4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B238);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B368);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B490);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B614);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B7A8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B880);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B8E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017B940);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BA3C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BB34);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BC38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BCA0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BCF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BD50);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017BEF8);

DEFINE_func_8017C0BC()  /* dedup: shared engine-core @0x8017C0BC (src/shared) */

extern s32 (*D_8018A528[])(void *);

s32 func_8017C150(void *a0) {
    return D_8018A528[*(u16 *)((s32)a0 + 2)](a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C18C);

DEFINE_func_8017C230()  /* dedup: shared engine-core @0x8017C230 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C294);

DEFINE_func_8017C66C()  /* dedup: shared engine-core @0x8017C66C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C710);

DEFINE_func_8017C908()  /* dedup: shared engine-core @0x8017C908 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017C974);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017D900);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017D98C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DAEC);

extern s32 (*D_8018A588[])(void *);

s32 func_8017DCB0(void *a0) {
    return D_8018A588[*(u8 *)((s32)a0 + 0x15)](a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DCEC);

extern s32 func_800167F0(s32 a0);

s32 func_8017DD3C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}

extern s32 (*D_8018A590[])(void *);

s32 func_8017DD60(void *a0) {
    return D_8018A590[*(u8 *)((s32)a0 + 0x15)](a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DD9C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DF5C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017DFD8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E0B4);

extern void (*D_8018A754[])();

void func_8017E0EC(void *arg0) {
    D_8018A754[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E128);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E170);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E224);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E298);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E3EC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E604);

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);

void func_8017E668(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E6BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E6F4);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E830);

extern void (*D_8018A79C[])();

void func_8017E868(void *arg0) {
    D_8018A79C[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E8A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E924);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017E974);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EA2C);

extern s32 (*D_8018A7B0[])();

s32 func_8017EA5C(s16 *a0) {
    return D_8018A7B0[(u16)a0[1]]();
}

extern void func_8012AD44(s32 *a0, s16 a1);

void func_8017EA98(s32 *a0) {
    a0[7] = 0x10;
    func_8012AD44(a0, 1);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EAC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EB2C);

extern s32 (*D_8018A7B8[])();

s32 func_8017EC40(s16 *a0) {
    return D_8018A7B8[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EC7C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EE44);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EEC0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017EF50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F024);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F114);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F240);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F290);

extern s32 (*D_8018A87C[])();

s32 func_8017F3E8(s16 *a0) {
    return D_8018A87C[(u16)a0[1]]();
}

extern s32 (*D_8018A89C[])();

s32 func_8017F424(s16 *a0) {
    return D_8018A89C[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F460);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F5BC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F780);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017F7E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017FAAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8017FD14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", listCdBuffer);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801800F8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801802CC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018031C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801803B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018047C);

void func_80180588(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180590);

extern s32 D_801270C8;
extern void func_8017F714(void);

void func_801806A8(void) {
    if (D_801270C8 == 1) {
        func_8017F714();
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801806D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801807B8);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180930);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801809BC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180AD4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180B64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180C90);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80180F10);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018103C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181948);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181B58);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181B9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181BE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80181F08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801820DC);

void func_80182254(s32 a0) {
    *(s16 *)(a0 + 0x2) = 4;
    *(s16 *)(a0 + 0x98) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182268);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182338);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801823A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182420);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801824D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801827A4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018281C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182988);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801829E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182A24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182C9C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182E30);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182E7C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80182FD0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018301C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018308C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183324);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183834);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183AA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183AF0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183BAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183C50);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183CF4);

void func_80183DD8(void) {
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183DE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183F4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80183FB8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018414C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184278);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801842C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801843C0);

s32 func_80184484(void) {
    return 1;
}

extern void func_8012C098(void);

void func_8018448C(void) {
    func_8012C098();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801844AC);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184594);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801845EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018469C);

void func_801846F8(s32 a0) {
    *(s16 *)(a0 + 0x2) = 5;
    *(s32 *)(a0 + 0x1C) = 0x14;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018470C);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184944);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184A00);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184A68);

extern s32 func_8012BEE8(s32);
extern void func_80184594(s32);

void func_80184AEC(s32 arg0) {
    if (func_8012BEE8(arg0)) {
        func_80184594(arg0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184B24);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184BB4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184C0C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184CCC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184D50);

extern s32 D_801DA908;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80184ED8(s32 a0, s32 a1) {
    D_801DA908 = a1;
    return func_8012C588(0x85, a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80184F08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_8018514C);

extern s32 (*D_801991C4[])();

s32 func_801853EC(s16 *a0) {
    return D_801991C4[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185428);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801855A0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801855DC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185618);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801856F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185814);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185870);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801858AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185970);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801859AC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185A94);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185AD4);

extern void func_801292C8(u8 *a0);

void func_80185B5C(u8 *a0) {
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x4) - *(s32 *)(a0 + 0x10);
    if (*(s16 *)(a0 + 0x6) < -0x110) {
        func_801292C8(a0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185BA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80185E68);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186078);

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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801863B4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186434);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186574);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801865EC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_801867E0);

extern Blk8 D_801D5610;

void func_8018681C(s32 a0) {
    if (*(s16 *)((s32)a0 + 0x70) == 4) {
        *(Blk8 *)((s32)a0 + 0x50) = D_801D5610;
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186860);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186938);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077", func_80186A04);
