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
/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
extern void func_80128288(void);
extern void func_80128158(void);
extern void func_801285E4(void);
extern void func_80128178(void);
extern void func_80128678(void);
extern void func_80128198(void);
extern void func_80128714(void);
extern void func_801281B8(void);
extern void func_8013E67C(void);
extern void func_801281D8(void);
extern void func_8013E558(void);
extern void func_801281F8(void);
extern s32 D_801D7F90;
extern s32 func_80128218(void);
extern void func_80128A28(void);
extern void func_80128228(void);
extern void func_80128AF4(void);
extern void func_80128248(void);
extern void func_801282EC(void);
extern void func_80128268(void);
extern u16 D_800B99F6;
extern void (*D_80186DB4[])(void);
extern void func_80011B7C(int);
extern void func_801282CC(void);
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_80129258(void);
extern void func_801378F0(void);
extern void func_80010E14(void);
extern s16 currentLocationId;
extern s32 func_80029504(void);
extern s32 func_800CF854(s32);
extern s32 func_80128998(void);
extern s32 func_801289F0(void);
extern s32 func_801288E8(s32);
extern s32 func_80128940(s32);
extern s32 func_80029178(s32);
extern s32 func_801288B0(void);
extern void func_80011C10(void);
extern void func_8012832C(void);
extern void func_80129220(void);
extern void func_80011E24(void);
extern void func_80128C14(void);
extern void func_8002AEF8(void);
extern void func_800CFBBC(void);
extern void SsUtReverbOff(void);
extern void func_8013C98C(void);
extern void func_80129C40(s32 a0);
extern void func_800D0630(void);
extern void func_80145CEC(void);
extern void func_80144B9C(void);
extern u8 D_800B9A17;
extern u8 D_800B9A10;
extern void func_80128420(void);
extern s32 func_800D0588(void);
extern void func_801284B8(void);
extern void func_80175308(void);
extern void func_8016E8F0(void);
extern void func_80175494(void);
extern u8 D_800B9A64;
extern void func_801284F0(void);
extern void func_80146074(void);
extern void func_8012853C(void);
extern void func_80178608(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80011A3C(void);
extern short currentLocationId;
extern short D_800B99F2;
extern void func_80128564(void);
extern u8 D_800B9A11;
extern void func_801285D4(void);
extern s32 func_800D18DC(void);
extern void func_8014607C(void);
extern void func_801287B8(void);
extern s32 D_801D9484;
extern void func_80029444(void);
extern void func_800D1754(void);
extern s32 D_80126B58;
extern s32 D_801DAAC0;
extern u16 D_800B99DA;
extern void func_80129CF8(void);
extern void func_8017849C(void);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_801505FC(s32 a0);
extern void func_801508B4(void *a0);
extern void func_80165E90(void);
extern void func_801627E8(void);
extern void func_80162B1C(void);
extern void func_80165CA0(void);
extern void func_80129010(void);
extern void func_8013CA14(void);
extern void func_800190AC(void);
extern void func_8012956C(void);
extern void func_8016E95C(void);
extern void func_801754A8(void);
extern void func_8013BC7C(void);
extern void func_8013BCDC(void);
extern void func_801379FC(void);
extern void func_8001212C(void);
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern u8 D_800AEFD0;
extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AF558;
extern int D_801D7F90;
extern int func_801288E8(int arg0);
extern u8 D_800AF560;
extern s32 func_80128940(s32 _arg0);
extern int D_800AECB0;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);
M2C_UNK func_80010DE0();                            /* extern */
extern s16 D_800B9A00;
extern M2C_UNK (*D_80186AF0)();
extern s16 (*D_80186AF4)();
s32 func_8002AF08();                                /* extern */
s32 func_800CFBE8();                                /* extern */
extern M2C_UNK (*D_80186AFC)();
extern s32 (*D_80186B00)();
extern s32 D_801D9480;
extern void func_80010AE0(s32 a0);
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D7F94;
extern void func_80128FAC(u16 *arg0);
extern s16 D_8011DB2C;
extern s16 D_8011DB30;
extern s32 D_80126AEC;
extern u8 *func_8012913C(s32 a0);
extern u8 * func_801290DC(s32 a0, u8 *a1);
extern void func_8001D074(s32 a, s32 b);
extern u8 *func_801291C0(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 * func_8012913C(s32 arg0);
extern void func_80016714(void *a0, s32 a1);
extern u8 * func_801291C0(void);
extern void func_80129248(s16 a0);
extern void func_801292C8(u8 *a0);
extern void func_8012927C(void);
extern void func_8012931C(struct vec *a0);
extern void func_80129350(s32 a0, s32 a1);
extern void func_80129374(s32 a0, s32 a1);
extern s16 D_800B9AAC[];
extern s16 D_800B9AAE[];
extern s16 D_800B9AB0[];
extern s16 D_800B9AB2[];
extern s16 D_800B9AB4[];
extern s16 D_800B9AB6[];
extern s16 D_800B9AB8[];
extern s16 D_800B9ABA[];
extern void func_80129398(void);
extern s16 D_80114EE0;
extern void func_80129428(void);
extern void func_8012943C(void);
extern s32 D_8005128C;
extern u8 D_800B9A78;
extern void func_801298F4(void *arg0);
extern void func_801299C8(s32 a, s32 b, s32 c);
extern void func_8012944C(void);
extern unsigned short D_800B99F0;
extern void func_8012A328(void);
extern void func_80053308(s32);
extern s32 func_80012F74(s32, s32, s32, s32);  /* canonical s32 (engine_core); (s16)-cast the return for the sll/sra */
extern void GsSetRefView2L(void *);
extern s8 D_801150D6;            /* canonical (engine_core macro): s8 — access via *(u8*)& for lbu */
extern u8 D_80127504;
extern s32 D_80126E60[];
extern s32 D_80126F04[];
extern u8 D_80126948[];          /* canonical (sibling): u8[] — cast (s32*) at use */
extern s32 D_80126FA8[];
extern struct BigCopy D_80126DB8;/* canonical (engine_core macro): struct BigCopy — (s32*)& at use */
extern u8 D_800AF630[];          /* canonical (sibling): u8[] — cast (s32*) at use */
extern s32 D_800AE688[];
extern s32 D_801151D4;           /* canonical (10 siblings): scalar s32 — store (s32)ptr */
extern void func_8012A018(s32 a, s32 b);
extern void func_80129FF4(void);
extern u8 D_80126948[];
void func_8012A048(void *a0, s32 a1, u8 a2);
extern void func_8012A018(s32 a0, s32 a1);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern void func_8012A048(void *a0, s32 a1, u8 a2);
extern void *memcpy(void *, const void *, unsigned int);
extern void func_8012A094(s32 a0);
extern void func_8012A100(s8 a0);
extern void func_8012A0E0(void);
extern s8 D_801150D6;
extern s32 D_80120204;
extern s32 D_80120200;
extern s32 D_8012020C;
extern s32 D_80120208;
extern s16 D_80120218;
extern s16 D_80120210;
extern s16 D_8012021A;
extern s16 D_80120212;
extern s16 D_8012021C;
extern s16 D_80120214;
extern s16 D_80120226;
extern s16 D_80120220;
extern s16 D_80120228;
extern s16 D_80120222;
extern s16 D_8012022A;
extern s16 D_80120224;
extern s32 D_80120294;
extern s16 D_80120298;
extern s16 D_8012029A;
extern void func_8012A110(void);
extern s8 D_801152C0;
extern void func_8012A2F4(void);
extern s16 D_80127080;
extern s16 D_801152C2;
extern void func_8012A304(s32 a0, s32 a1);
extern s32 D_801151D4;
extern void func_8012A418(void);
extern void func_8012A464(void);
extern struct BigCopy D_80126DB8;
extern struct BigCopy D_80114EE8;
extern void func_8012A4BC(void);
extern void func_8012A598(void *a0);
extern void func_8012A568(void (*a0)(void));
extern void func_8012A62C(s32);
extern void func_8012A5F8(void (*a0)(void), s32 a1);
extern void func_8012A62C(s32 a0);
extern void func_8012A7D4(void *a0, void *a1);
extern s32 func_8012A6D0(void *a0, void *a1);
extern s16 func_8012A68C(void);
extern s16 func_8012A79C(s16 *a0, s16 *a1);
extern s16 func_8012A758(void);
extern s32 ratan2(s32 a0, s32 a1);
extern void func_8012A7D4(void *arg0, void *arg1);
extern void func_8012AAAC();
extern void func_8012A828(s32 a0, void * a1);
extern int func_8012ACE0(void *a0);
extern void func_8012A860(void *a0, int a1);
extern void func_8012A8B0(u8 *a0, s32 a1);
extern void func_8012A8E8(void);
extern u8 D_801202A0[];
extern u16 D_801270C0;
extern void func_8012A988(u8 *a0);
extern void func_8012A908(void);
extern s32 func_8012ACE0(void *a0);
extern M2C_UNK D_80186E48;
extern void func_8012ACA0(void *arg0);
/* ==== end §8b carried decl layer ==== */


// @class: iv-combine
// @stuck: none — MATCH (25 ins). Array-subscript induction o->list[i] fixes preheader hoist order + loop-top load-delay nop; scattered case labels force the jump table (gcc merges contiguous same-target cases, so 6+ non-contiguous nodes needed for the density heuristic).
      /* 8-byte element, cmd @ +4 */
    /* list ptr @ +0x90 */

s32 func_8012ACE0(void *o) {
    int i;
    for (i = 0; ; i++) {
        switch (((Owner_8012ACE0 *)o)->list[i].cmd) {
            case -2:
            case -1:
            case 0:
                return i;
            case -50: case -45: case -40: case -35: case -30:   /* scatter -> force jump table (min=-50 sets low bound) */
            default:
                break;
        }
    }
}


DEFINE_func_8012AD44()  /* dedup: shared engine-core @0x8012AD44 (src/shared) */

DEFINE_func_8012AD50()  /* dedup: shared engine-core @0x8012AD50 (src/shared) */


void func_8012AD64(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x34) = a1;
}

DEFINE_func_8012AD6C()  /* dedup: shared engine-core @0x8012AD6C (src/shared) */

DEFINE_func_8012AD80()  /* dedup: shared engine-core @0x8012AD80 (src/shared) */

DEFINE_func_8012ADE4()  /* dedup: shared engine-core @0x8012ADE4 (src/shared) */

DEFINE_func_8012AE00()  /* dedup: shared engine-core @0x8012AE00 (src/shared) */

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_800132BC(s32 a0, s32 a1);

/* LOAD-BEARING: the 8-byte sp+0x18->sp+0x20 copy is an alignment-2 struct copy
   (3 shorts written, then copied) -> gcc emits lwl/lwr/swl/swr.  An aligned-2
   base-type typedef did NOT reproduce it; only a short-only struct (align 2) does. */

DEFINE_func_8012AF0C()  /* dedup: shared engine-core @0x8012AF0C (src/shared) */

DEFINE_func_8012B030()  /* dedup: shared engine-core @0x8012B030 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (38 ins, relocation-masked)

DEFINE_func_8012B0B4()  /* dedup: shared engine-core @0x8012B0B4 (src/shared) */


DEFINE_func_8012B14C()  /* dedup: shared engine-core @0x8012B14C (src/shared) */

DEFINE_func_8012B178()  /* dedup: shared engine-core @0x8012B178 (src/shared) */

DEFINE_func_8012B1B4()  /* dedup: shared engine-core @0x8012B1B4 (src/shared) */

DEFINE_func_8012B200()  /* dedup: shared engine-core @0x8012B200 (src/shared) */

DEFINE_func_8012B21C()  /* dedup: shared engine-core @0x8012B21C (src/shared) */

DEFINE_func_8012B23C()  /* dedup: shared engine-core @0x8012B23C (src/shared) */

DEFINE_func_8012B260()  /* dedup: shared engine-core @0x8012B260 (src/shared) */

DEFINE_func_8012B2CC()  /* dedup: shared engine-core @0x8012B2CC (src/shared) */

DEFINE_func_8012B370()  /* dedup: shared engine-core @0x8012B370 (src/shared) */

DEFINE_func_8012B414()  /* dedup: shared engine-core @0x8012B414 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (84 ins)
//
// §52b wall cracked (func_8012B4B8, "symbol-base wins-low-needs-high" + the
// movstrsi `(plus $fp const)` local-alloc theft). Recipe:
//  1. self->$s1, pre-call obj->$s0 pins; tail-reload is a SEPARATE unpinned var
//     (o2) so it lands in $a0 like the target (a pinned iVar2 would force $s0).
//  2. The copy-in from D_800AE620 must NOT be a struct-assign/movstrsi: that
//     leaves a `&m`=(plus $fp 0x10) dest pseudo that CSE shares with the 3 call
//     args -> it goes call-crossing -> stolen into a callee-saved reg ($s2)
//     (update_equiv_regs can't rematerialize a non-CONSTANT_P source). Instead:
//     load through a LAUNDERED source pointer with EXPLICIT 3-3-2 grouped temps.
//     sp-direct stores => no dest pseudo => each call rematerializes
//     `addiu $a1,$sp,0x10` in its own delay slot (matches target, 84 ins).
//  3. The laundered src is a real var, so pin it to $a1 ($5) to win the
//     symbol-base's "needs-HIGH" slot (else it first-fits $v0, the §52b wall).



DEFINE_func_8012B4B8()  /* dedup: shared engine-core @0x8012B4B8 (src/shared) */


DEFINE_func_8012B608()  /* dedup: shared engine-core @0x8012B608 (src/shared) */

DEFINE_func_8012B6D4()  /* dedup: shared engine-core @0x8012B6D4 (src/shared) */

DEFINE_func_8012B70C()  /* dedup: shared engine-core @0x8012B70C (src/shared) */

DEFINE_func_8012B744()  /* dedup: shared engine-core @0x8012B744 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0", func_8012B77C);

DEFINE_func_8012B864()  /* dedup: shared engine-core @0x8012B864 (src/shared) */

DEFINE_func_8012B8A4()  /* dedup: shared engine-core @0x8012B8A4 (src/shared) */

DEFINE_func_8012B8E4()  /* dedup: shared engine-core @0x8012B8E4 (src/shared) */



/* canonical data externs (per pre-resolved sigs); asm loads them lh -> (s16) cast at use */
extern u16 D_80126B66;
extern u16 D_80126B5E;
/* callee func_8004CFEC, linked as symbol "ratan2" (config/symbols.us.txt: 0x8004CFEC);
 * canonical s32(s32,s32) -- matches the banked sibling func_8012B8E4 in engine_core.h */
DEFINE_func_8012BA10()  /* dedup: shared engine-core @0x8012BA10 (src/shared) */



DEFINE_func_8012BB3C()  /* dedup: shared engine-core @0x8012BB3C (src/shared) */


DEFINE_func_8012BC60()  /* dedup: shared engine-core @0x8012BC60 (src/shared) */

DEFINE_func_8012BCCC()  /* dedup: shared engine-core @0x8012BCCC (src/shared) */

DEFINE_func_8012BD14()  /* dedup: shared engine-core @0x8012BD14 (src/shared) */

DEFINE_func_8012BD3C()  /* dedup: shared engine-core @0x8012BD3C (src/shared) */

DEFINE_func_8012BDBC()  /* dedup: shared engine-core @0x8012BDBC (src/shared) */

DEFINE_func_8012BE54()  /* dedup: shared engine-core @0x8012BE54 (src/shared) */

DEFINE_func_8012BE98()  /* dedup: shared engine-core @0x8012BE98 (src/shared) */


DEFINE_func_8012BEE8()  /* dedup: shared engine-core @0x8012BEE8 (src/shared) */

DEFINE_func_8012BF10()  /* dedup: shared engine-core @0x8012BF10 (src/shared) */

void func_8012BF4C(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x1C) = a1;
}

DEFINE_func_8012BF54()  /* dedup: shared engine-core @0x8012BF54 (src/shared) */

/* func_8012BF68: lhu 0x5C; andi 0x7FFF; sh 0x5C; jr (sh in delay slot)
 * void form: no return value => no extra andi v0,0xffff truncation past the mask. */
DEFINE_func_8012BF68()  /* dedup: shared engine-core @0x8012BF68 (src/shared) */

DEFINE_func_8012BF7C()  /* dedup: shared engine-core @0x8012BF7C (src/shared) */

// @class: schedule
// @stuck: none — MATCH (39/39 reloc-masked words byte-verified via objdump -s raw .text; match_one's "18 mismatched" is the objdump zero-run-elision artifact dropping the 2 cop2-latency nops, same as sibling DEFINE_func_8013E2C4 @ ov_SC01_077.c:326)
#include "common.h"

DEFINE_func_8012BFA8()  /* dedup: shared engine-core @0x8012BFA8 (src/shared) */


DEFINE_func_8012C044()  /* dedup: shared engine-core @0x8012C044 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected; tail-call passes incoming param through (nop delay slot)

DEFINE_func_8012C098()  /* dedup: shared engine-core @0x8012C098 (src/shared) */


// @class: other
// @stuck: none — MATCH (42 ins, relocation-masked); func_8012C044 dispatch idiom, if(fp==0) branch-polarity
DEFINE_func_8012C0EC()  /* dedup: shared engine-core @0x8012C0EC (src/shared) */


DEFINE_func_8012C194()  /* dedup: shared engine-core @0x8012C194 (src/shared) */

DEFINE_func_8012C1B8()  /* dedup: shared engine-core @0x8012C1B8 (src/shared) */

DEFINE_func_8012C1DC()  /* dedup: shared engine-core @0x8012C1DC (src/shared) */

DEFINE_func_8012C218()  /* dedup: shared engine-core @0x8012C218 (src/shared) */

DEFINE_func_8012C284()  /* dedup: shared engine-core @0x8012C284 (src/shared) */

// @class: schedule
// @stuck: none — MATCH expected (lifted byte-proven loop idiom from sibling func_8012C750 @0x8012C750)
#include "common.h"

DEFINE_func_8012C2D0()  /* dedup: shared engine-core @0x8012C2D0 (src/shared) */


DEFINE_func_8012C31C()  /* dedup: shared engine-core @0x8012C31C (src/shared) */

DEFINE_func_8012C354()  /* dedup: shared engine-core @0x8012C354 (src/shared) */

DEFINE_func_8012C438()  /* dedup: shared engine-core @0x8012C438 (src/shared) */

DEFINE_func_8012C51C()  /* dedup: shared engine-core @0x8012C51C (src/shared) */


DEFINE_func_8012C588()  /* dedup: shared engine-core @0x8012C588 (src/shared) */



DEFINE_func_8012C658()  /* dedup: shared engine-core @0x8012C658 (src/shared) */


DEFINE_func_8012C724()  /* dedup: shared engine-core @0x8012C724 (src/shared) */

// @class: iv-combine
// @stuck: none — MATCH (52 ins)
#include "common.h"

DEFINE_func_8012C750()  /* dedup: shared engine-core @0x8012C750 (src/shared) */


DEFINE_func_8012C820()  /* dedup: shared engine-core @0x8012C820 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (149 ins). Counter (*(u16 *)&D_801270C4): gcc CSE's the two reads (store to
//   dst+0x36 assumed non-aliasing the global) AND folds %lo per-access — target instead RELOADS
//   and keeps &(*(u16 *)&D_801270C4) in one reg. Fix = pin a `u16*` to $v1 (register asm "$3"), read via
//   `*(volatile u16*)pc` (defeats CSE -> 2 loads) but STORE via plain `*pc` (non-volatile store
//   schedules store-before-sll, no extra `move`). count is s16 so `count==0` -> `sll 16;bnez`.
//   else-block obj must be a BLOCK-LOCAL (gcc then picks $a1, not the shared if-branch $a0).

extern s32   D_8018A32C;
extern s16 D_801270C4;
extern u16   D_801274E4[];
extern s32   D_8011DB08;
extern void  func_80016714(void *a0, s32 a1);

s32 func_8012C890(s32 a0, s32 a1, s32 a2) {
    u8 *src = (u8 *)a0;
    u8 *dst = (u8 *)a1;
    u16 *d;
    s16 count;
    u16 v2, v4;
    s32 v10;
    void *obj;

    *(u16 *)(dst + 0x0)  = *(u16 *)(src + 0x6);
    v2 = *(u16 *)(src + 0x0);
    *(u16 *)(dst + 0x6)  = v2;
    *(u16 *)(dst + 0x88) = v2;
    v2 = *(u16 *)(src + 0x2);
    *(u16 *)(dst + 0xA)  = v2;
    *(u16 *)(dst + 0x8A) = v2;
    v4 = *(u16 *)(src + 0x4);
    *(u16 *)(dst + 0xC)  = 0;
    *(u16 *)(dst + 0x8)  = 0;
    *(u16 *)(dst + 0x4)  = 0;
    *(u16 *)(dst + 0xE)  = v4;
    *(u16 *)(dst + 0x8C) = v4;
    *(u16 *)(dst + 0x70) = *(u16 *)(src + 0x8);
    *(u16 *)(dst + 0x72) = *(u16 *)(src + 0xA) & 0xF7FF;
    *(u16 *)(dst + 0xFC) = *(u16 *)(src + 0xE);
    v10 = *(s32 *)(src + 0x10);
    *(s32 *)(dst + 0x78) = (s32)&D_8018A32C;
    *(s32 *)(dst + 0xDC) = v10;

    {
        register u16 *pc __asm__("$3");
        pc = &(*(u16 *)&D_801270C4);
        *(u16 *)(dst + 0x36) = *(volatile u16 *)pc;
        count = *(volatile u16 *)pc + 1;
        *pc = count;
        if (count == 0) {
            *pc = 1;
        }
    }

    if (a2 != 0) {
        *(s32 *)(dst + 0x64) = a2;
        *(s32 *)(dst + 0x68) = 0;
    } else {
        *(s32 *)(dst + 0x64) = 0;
        *(s32 *)(dst + 0x68) = (s32)src;
    }

    *(u16 *)(src + 0xA) |= 0x8000;
    *(u16 *)(dst + 0x2) = 0;
    d = D_801274E4;
    *d &= 0xFFFE;
    (*(void (**)(void *))(D_8011DB08 + *(u16 *)(dst + 0x0) * 4))(dst);

    if (*d & 1) {
        s32 a1v;
        obj = *(void **)(dst + 0x20);
        if (obj != 0) {
            s32 t = *(u16 *)obj;
            if (t != 1) {
                if (t != 2) {
                    goto done;
                }
                a1v = 0x38;
            } else {
                a1v = 0x84;
            }
            func_80016714(obj, a1v);
        done:;
        }
        func_80016714(dst, 0x10C);
        *(u16 *)(src + 0xA) &= 0x7FFF;
        return 0;
    }

    if (*(s32 *)(dst + 0x64) == 0) {
        void *o = *(void **)(dst + 0x20);
        if (o == 0) {
            return (s32)dst;
        }
        if (*(u16 *)o == 1) {
            s16 c = *(s16 *)(src + 0xC);
            if (c != 0x7FFF) {
                *(s16 *)((u8 *)o + 0x12) = c;
            }
        }
    }
    if (*(s32 *)(dst + 0x20) != 0) {
        *(u16 *)(*(s32 *)(dst + 0x20) + 0x8) = *(u16 *)(dst + 0x6) + *(u16 *)(dst + 0x50);
        *(u16 *)(*(s32 *)(dst + 0x20) + 0xA) = *(u16 *)(dst + 0xA) + *(u16 *)(dst + 0x52);
        *(u16 *)(*(s32 *)(dst + 0x20) + 0xC) = *(u16 *)(dst + 0xE) + *(u16 *)(dst + 0x54);
    }
    return (s32)dst;
}


DEFINE_func_8012CAE4()  /* dedup: shared engine-core @0x8012CAE4 (src/shared) */


DEFINE_func_8012CB64()  /* dedup: shared engine-core @0x8012CB64 (src/shared) */


extern s32 func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];

void func_8012CBA4(s32 a0) {
    func_8012CC88(a0, 0, (s32)D_800D3918);
}

extern s32 func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];

void func_8012CBCC(s32 a0) {
    func_8012CC88(a0, 1, (s32)D_800D3918);
}

DEFINE_func_8012CBF4()  /* dedup: shared engine-core @0x8012CBF4 (src/shared) */

DEFINE_func_8012CC1C()  /* dedup: shared engine-core @0x8012CC1C (src/shared) */

DEFINE_func_8012CC40()  /* dedup: shared engine-core @0x8012CC40 (src/shared) */

DEFINE_func_8012CC64()  /* dedup: shared engine-core @0x8012CC64 (src/shared) */


extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

/* a0 = actor/entity base, a1 = mode passed through to func_8012CEB0, a2 = s16[3] offset vector.
 * Two 8-byte s16 vectors live at sp+0x10 and sp+0x18 and are passed by address; the second one
 * is written back to the entity's hi-16 fixed-point position after the offset is removed. */
s32 func_8012CC88(s32 a0, s32 a1, s32 a2) {
    typedef struct { s16 vx, vy, vz, pad; } SV3_8012CC88;
    SV3_8012CC88 sp10;
    SV3_8012CC88 sp18;
    s32 v0;

    sp10.vx = *(u16*)(a0 + 0x3A);
    sp10.vy = *(u16*)(a0 + 0x3E);
    sp10.vz = *(u16*)(a0 + 0x42);
    sp10.vx += *(u16*)(a2 + 0);
    sp10.vy += *(u16*)(a2 + 2);
    sp10.vz += *(u16*)(a2 + 4);

    *(s32*)(a0 + 0x10) += *(s32*)(a0 + 0x44);
    *(s32*)(a0 + 0x14) += *(s32*)(a0 + 0x48);
    *(s32*)(a0 + 0x18) += *(s32*)(a0 + 0x4C);
    *(s32*)(a0 + 0x04) += *(s32*)(a0 + 0x10);
    *(s32*)(a0 + 0x08) += *(s32*)(a0 + 0x14);
    *(s32*)(a0 + 0x0C) += *(s32*)(a0 + 0x18);

    sp18.vx = *(u16*)(a0 + 0x06);
    sp18.vy = *(u16*)(a0 + 0x0A);
    sp18.vz = *(u16*)(a0 + 0x0E);
    sp18.vx += *(u16*)(a2 + 0);
    sp18.vy += *(u16*)(a2 + 2);
    sp18.vz += *(u16*)(a2 + 4);

    v0 = func_8012CEB0((s32)&sp10, (s32)&sp18, a1);

    sp18.vx -= *(u16*)(a2 + 0);
    sp18.vy -= *(u16*)(a2 + 2);
    sp18.vz -= *(u16*)(a2 + 4);
    *(s16*)(a0 + 0x06) = sp18.vx;
    *(s16*)(a0 + 0x0A) = sp18.vy;
    *(s16*)(a0 + 0x0E) = sp18.vz;

    if (v0 & 0x6000) {
        *(s32*)(a0 + 0x14) = 0;
    }
    return v0;
}


DEFINE_func_8012CE2C()  /* dedup: shared engine-core @0x8012CE2C (src/shared) */

DEFINE_func_8012CEB0()  /* dedup: shared engine-core @0x8012CEB0 (src/shared) */



DEFINE_func_8012CFA8()  /* dedup: shared engine-core @0x8012CFA8 (src/shared) */


/* func_8012D098 — region-a camera 8-corner/frustum builder (189 ins, reach-134).
 * STATUS: MATCH (match_one = 0, relocation-masked byte-identical). ONE-SHOT — the natural
 * Ghidra-faithful C matched with no pins, no zero-byte asm, no permuter, no Fable5 escalation.
 *
 * Why the "hardest tier / all 8 $s0-$s7 live" label did NOT translate to matching difficulty:
 *  - The two callee-saved BASES are the PARAMETERS themselves (param_1->$fp, param_2->$s7), not
 *    hoisted global arrays. §32 idiom #1's whole crux ("a base living in a $s reg across calls can
 *    only come from a source local, never a bare global") is a non-issue: params are already source
 *    locals in registers. No `p = D_xxxx;` hoist, no pins.
 *  - The body is ONE straight-line basic block (calls don't split BBs in gcc-2.7.2), so the 8 output-
 *    buffer address-pseudos are LOCAL-ALLOC territory; param_1/param_2 span BBs -> global-alloc.
 *  - Peak pressure = 10 callee-saved-worthy values (param_1, param_2, &scratch, bufA..bufG) over 9
 *    regs ($fp + $s0-$s7) -> exactly one buffer must rematerialize. local-alloc density-order (all
 *    buffers = 4 refs, equal) + first-fit naturally spills bufA (first-born, longest live range) and
 *    lays the rest out bufB->$s6 .. bufG->$s1, with &scratch->$s0 (dies at call 8) reused for bufH.
 *    That IS the target allocation, produced with zero steering.
 *
 * Loose/intended types (element type from opcode): param_1 = u16* (`*param_1` is `lhu`, unsigned;
 * an s16* would emit `lh` = 1-op miss); param_2 = u32 pointer-base (offsets 4/6/8/a/c/e emit as
 * literal immediates == target's `%lo(D_80000004..)` bytes; `| 0x80000000` -> `lui 0x8000` ==
 * target's `%hi(D_80000004)`); scratch = u16[3] (`sh` stores, `lhu` sources); the 8 output buffers
 * are 8-byte locals never dereferenced here (size only matters) declared bufA..bufH THEN scratch so
 * the ascending in-decl-order slot layout lands bufA@sp+0x10 .. bufH@sp+0x48, scratch@sp+0x50.
 * Callees kept loose (extern void func_...()); reconcile at bank time via cast_call_sites/§33.
 */
DEFINE_func_8012D098()  /* dedup: shared engine-core @0x8012D098 (src/shared) */


DEFINE_func_8012D38C()  /* dedup: shared engine-core @0x8012D38C (src/shared) */

DEFINE_func_8012D3AC()  /* dedup: shared engine-core @0x8012D3AC (src/shared) */

DEFINE_func_8012D3B4()  /* dedup: shared engine-core @0x8012D3B4 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (sibling of func_8012D3B4 + func_8012DEB8 sp10/sp18 prelude)
#include "common.h"

DEFINE_func_8012D4B4()  /* dedup: shared engine-core @0x8012D4B4 (src/shared) */


DEFINE_func_8012D5DC()  /* dedup: shared engine-core @0x8012D5DC (src/shared) */

DEFINE_func_8012D5E4()  /* dedup: shared engine-core @0x8012D5E4 (src/shared) */

DEFINE_func_8012D624()  /* dedup: shared engine-core @0x8012D624 (src/shared) */

// @class: schedule
// @stuck: none — MATCH



int func_8012D664(int arg0, int arg1, int arg2) {
    extern int func_8012F568();
    extern int D_80186E58;

    struct S8012D664_8012D664 s;
    int ret;
    int t;

    s.a = (*(unsigned short*)&D_80126B5E);
    s.b = (*(unsigned short*)&D_80126B62) - 0x40;
    s.c = (*(unsigned short*)&D_80126B66);
    ret = ((int(*)())func_800132BC)(arg0, &s);
    t = arg1 + 0x20;
    if (ret < t * t) {
        func_8012F568(1, 1, 0, arg2, arg0, &D_80186E58);
        return 1;
    }
    return 0;
}


// @class: struct
// @stuck: none — MATCH expected; base = (*(u32*)(p+0x58) & 0xFFFFFFF) | 0x80000000 held once, %lo folds via offsets
#include "common.h"

DEFINE_func_8012D714()  /* dedup: shared engine-core @0x8012D714 (src/shared) */


extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);
extern M2C_UNK D_80186E60;
extern M2C_UNK D_80186E68;

s32 func_8012DB84(void)
{
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_80186E60, &D_80186E68);
}


// @class: regalloc-order
// @stuck: none — MATCH. Pins: args $s2/$s4/$s5/$s3, loop-actor $s0, running-max/square $s1; abs load-temp pinned $v0 ($2) so abs copies $v0->$v1; re-tie barrier on iVar4 kills slt-into-bgez-delay duplication; nested ifs keep the two 0x5c bit-tests from folding to one andi 0xc000.
#include "common.h"

DEFINE_func_8012DBD0()  /* dedup: shared engine-core @0x8012DBD0 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH




s32 func_8012DDA4()
{
    extern Entry_8012DDA4 * D_801D94A4;
    extern Entry_8012DDA4 * D_801D94A0;

    Entry_8012DDA4 *p;
    Entry_8012DDA4 *end = ((Entry_8012DDA4 *)D_80126720);

    while (D_801D94A4 != end) {
        p = D_801D94A4;
        if (p->active != 0 && p != D_801D94A0) {
            D_801D94A4 = p + 1;
            return p;
        }
        D_801D94A4++;
    }
    D_801D94A4 = 0;
    return 0;
}


// @class: plumbing
// @stuck: none — MATCH (35/35 ins, relocation-masked)


s32 func_8012DE2C(s32 a0) {
    extern u8 * D_801D94A4;
    extern u8 * D_801D94A0;

    u8 *base;
    u8 *end;
    u8 *p;

    base = D_801202A0;
    end = base + 0x6480;
    D_801D94A4 = base;
    D_801D94A0 = ((u8 *)a0);

    while (D_801D94A4 != end) {
        p = D_801D94A4;
        if (*(u16 *)p != 0 && p != ((u8 *)a0)) {
            D_801D94A4 = p + 0x10C;
            return p;
        }
        D_801D94A4 += 0x10C;
    }
    D_801D94A4 = 0;
    return 0;
}


DEFINE_func_8012DEB8()  /* dedup: shared engine-core @0x8012DEB8 (src/shared) */

DEFINE_func_8012DF34()  /* dedup: shared engine-core @0x8012DF34 (src/shared) */

DEFINE_func_8012DFBC()  /* dedup: shared engine-core @0x8012DFBC (src/shared) */

DEFINE_func_8012DFCC()  /* dedup: shared engine-core @0x8012DFCC (src/shared) */

DEFINE_func_8012DFD4()  /* dedup: shared engine-core @0x8012DFD4 (src/shared) */

#include "common.h"

DEFINE_func_8012E014()  /* dedup: shared engine-core @0x8012E014 (src/shared) */


DEFINE_func_8012E138()  /* dedup: shared engine-core @0x8012E138 (src/shared) */

s32 func_8012E27C(void) {
    return 1;
}

DEFINE_func_8012E284()  /* dedup: shared engine-core @0x8012E284 (src/shared) */

// @class: struct
// @stuck: none — MATCH (modeled on DEFINE_func_8012D3B4 sibling idiom: (s8*)&D_800A651C + (u16)D_800B9A02*0x14)

DEFINE_func_8012E28C()  /* dedup: shared engine-core @0x8012E28C (src/shared) */


DEFINE_func_8012E32C()  /* dedup: shared engine-core @0x8012E32C (src/shared) */

/* func_8012E364 (ov_SC01_077_jr_8012ACE0) — MATCH, 67/67 ins, 0 mismatched (reloc-masked).
 *
 * Verified:
 *   python3 tools/match_one.py func_8012E364 --c .run/near6/wave23/func_8012E364.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0
 *   -> MATCH (67 ins)  func_8012E364
 *
 * Symbols: sig_hints listed no callees and no data decls for this fn, so the three externs below
 * are derived from the asm's %hi/%lo pairs:
 *   D_80126CE0  -> `lh`  (0x8012E370)  => s16
 *   D_801D9498  -> `lw`/`sw`           => s32
 *   D_801D949C  -> `lw`/`sw`           => s32
 * D_80126CE0 is already declared `extern s16 D_80126CE0;` inside ov_SC03_099_jr_8016AB6C.c etc.,
 * so the s16 typing is consistent with the rest of the tree.
 *
 * ---------------------------------------------------------------------------------------------
 * HOW THE LAST 7 SLOTS CAME OFF (wave22 plateaued here at closeness 7; that header's
 * "genuine regalloc hard tail / not C-expressible" verdict was WRONG on both clusters).
 *
 * CLUSTER B - idx 59-62 (`nop`/`negu $v1,$v1` vs `addu $v0,$v1,$zero`/`negu $v0,$v0`): 7 -> 3.
 *   NOT a delay-slot (dbr) residual at all. `mips.md:1526 abssi2` is a 3-instruction `multi`
 *   template that emits its OWN branch AND fills its OWN slot:
 *       REGNO(op0) == REGNO(op1):  "bgez %1,1f%#\n\tsubu %0,%z2,%0\n1:"     (slot -> maspsx nop)
 *       REGNO(op0) != REGNO(op1):  "%(bgez %1,1f\n\tmove %0,%1\n\tsubu %0,%z2,%0\n1:%)"
 *   The target IS the second form (`.set noreorder` + `move` in the slot). So the whole residual
 *   was one question: does the abs DEST get a different hard reg from its SOURCE?
 *   Two edits, both required:
 *     (a) spell the abs as `__builtin_abs(v)` so a real `(abs:SI ...)` insn exists. A hand-rolled
 *         `d = v; if (d<0) d = -d;` is equivalent (cse folds it to the same abs insn - the wave22
 *         draft was ALREADY going through abssi2, it just hit the dest==src arm), but a
 *         `(v<0) ? -v : v` ternary does NOT fold here: 68 ins, 19 off.
 *     (b) PIN the abs result to $2. Unpinned, local-alloc's combine_regs (K8) ties the abs dest
 *         into its dying input `v` -> REGNO(op0)==REGNO(op1) -> the nop form. Measured: the same
 *         file with `s32 d;` instead of the pin is 5 off; with the pin, 3 off.
 *   (Rejected on measurement: `d = v; asm("" :: "r"(v))` dead-read to break the tie = 68 ins/13;
 *    RC-12 `$0`-add opaque copy = 9; pinning d to $3 = 5.)
 *
 * CLUSTER A - idx 43-45 (the D_801D949C load vs the 0x20($a2) load, swapped): 3 -> MATCH.
 *   Pure sched1 rank, and it IS steerable (sched.md S2, the birthing boost). The `.i.sched` dump
 *   of the wave22 draft says it outright:
 *       ;; insn[ 104]: priority = 1     (prev = D_801D949C)
 *       ;; insn[ 107]: priority = 1     (a    = *(arg0+0x20))
 *       ;; ready list at T-17: 107 (1) 104 (7f000001), now 104 107
 *   Equal base priority, but 104 carries the `adjust_priority`/`birthing_insn_p` boost
 *   (sched.c:2506/2469 - `reg_n_sets[dest] == 1`) and 107 does NOT, because wave22 reused ONE
 *   variable `a` for four roles (hint value, division result, both tail entity loads) -> 4 sets.
 *   Backward scheduling means picked-first = placed-LAST, so the boosted 104 got pushed BELOW 107.
 *   Fix: give each tail entity load its own single-set local (`e1`, `e2`). Now both loads are
 *   boosted, the rank falls through to `rank_for_schedule`'s LUID tie-break (sched.c:2427,
 *   "highest LUID first" = ascending source order forward) and the two loads come out in
 *   statement order = the target order.
 *   NB the wave22 header's claim "splitting `a` regresses 2 slots" only applies to splitting the
 *   FIRST two roles (hint value / division result) - those must stay one multi-set cross-block
 *   variable. Splitting only the TAIL roles is what pays.
 *
 * LOAD-BEARING constructs (do not "simplify"):
 *  1. `spd` - a local holding 0x1000 SET BEFORE the if/else chain, so the constant lives in a
 *     pseudo across the branch: `addiu $a3,$zero,0x1000` in the `blez` slot at 0x8012E3DC and the
 *     `sw $a3` / `addu $v1,$v1,$a3` forms at L8012E410.
 *  2. `a` reused for the D_80126CE0 value AND the division result (multi-set, cross-block) - that
 *     is what puts the quotient in $a0 (`subu $a0,$v0,$v1`) instead of coalescing into $v0.
 *  3. `flags` pinned to $2 (dropping it = 13 off) and `prev` pinned to $5 (dropping it = 6 off).
 *  4. `d` pinned to $2 - see CLUSTER B(b).
 *  5. `e1`/`e2` must be SEPARATE single-set locals - see CLUSTER A.
 *  The `arg0` $6 pin is NOT load-bearing any more (verified: still MATCH without it); it is kept
 *  because it costs nothing and documents the target's `addu $a2,$a0,$zero`.
 */
extern s16 D_80126CE0;
extern s32 D_801D9498;
extern s32 D_801D949C;

void func_8012E364(s32 arg0_)
{
    register s32 arg0 __asm__("$6");
    register s32 prev __asm__("$5");
    register u16 flags __asm__("$2");
    s32 a;
    s32 diff;
    s32 v;
    register s32 d __asm__("$2");
    s32 spd;
    s32 e1;
    s32 e2;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    a = D_80126CE0;
    if (a == 0) {
        D_801D9498 = 0x1000;
        D_801D949C = 0x1000;
    }
    a = ((0x90 - a) << 12) / 0x90;
    *(s32 *)(arg0 + 0x1C) += 1;
    spd = 0x1000;

    diff = D_801D9498 - a;
    if (diff > 0) {
        D_801D9498 -= diff >> 2;
    } else if (diff < 0) {
        D_801D9498 += (-diff) / 4;
    }

    prev = D_801D949C;
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_801D9498 - prev + spd;
    D_801D949C = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801D9498 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1000;
}


DEFINE_func_8012E470()  /* dedup: shared engine-core @0x8012E470 (src/shared) */

DEFINE_func_8012E4C8()  /* dedup: shared engine-core @0x8012E4C8 (src/shared) */

DEFINE_func_8012E504()  /* dedup: shared engine-core @0x8012E504 (src/shared) */

DEFINE_func_8012E544()  /* dedup: shared engine-core @0x8012E544 (src/shared) */

DEFINE_func_8012E57C()  /* dedup: shared engine-core @0x8012E57C (src/shared) */

// @class: schedule
// @stuck: none — MATCH
DEFINE_func_8012E5CC()  /* dedup: shared engine-core @0x8012E5CC (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (60/60). Pins: $4 defeats &D_800AF648 CSE; $16/$17 force param_2/param_3 saved-reg order vs the guard-branch reversal
#include "common.h"

DEFINE_func_8012E688()  /* dedup: shared engine-core @0x8012E688 (src/shared) */


// @class: other
// @stuck: none — MATCH (69/69 ins, relocation-masked 0 diffs via tools/match_one precise check)
#include "common.h"

/* GTE inline-asm sequences (psyq inline_c.h bodies). rtps uses the project's
 * `rtps` assembler macro (include/gte_macros.inc, pulled in by common.h ->
 * include_asm.h -> labels.inc) which encodes 0x4A180001 — NOT the psyq
 * `.word 0x0000007f`, which assembles to the wrong word for this target. */
#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldlv0(r0) __asm__ volatile (                 \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13" )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )


DEFINE_func_8012E778()  /* dedup: shared engine-core @0x8012E778 (src/shared) */


DEFINE_func_8012E88C()  /* dedup: shared engine-core @0x8012E88C (src/shared) */

DEFINE_func_8012E8A8()  /* dedup: shared engine-core @0x8012E8A8 (src/shared) */

DEFINE_func_8012E8C4()  /* dedup: shared engine-core @0x8012E8C4 (src/shared) */

DEFINE_func_8012E8E0()  /* dedup: shared engine-core @0x8012E8E0 (src/shared) */


// @class: other
// @stuck: none — MATCH (branch-polarity invert: `0x78 != 0` puts compute block as fall-through)

extern void func_8016AA50(int, int);
extern void func_8016B428(int);
extern void func_80019064(void *);
extern int D_80186E70;

void func_8012E9C0(int param_1)
{
    int iVar1;

    if (*(short *)(param_1 + 0x60) != 0) {
        if (*(unsigned char *)(param_1 + 0x5e) == 0x1d) {
            *(short *)(param_1 + 0x82) = 0;
            *(short *)(param_1 + 0x7c) = *(unsigned short *)(param_1 + 6);
            *(short *)(param_1 + 0x7e) = *(unsigned short *)(param_1 + 0xa);
            *(short *)(param_1 + 0x80) = *(unsigned short *)(param_1 + 0xe);
        }
        if (*(int *)(param_1 + 0x78) != 0) {
            iVar1 = *(short *)(param_1 + 0x60) *
                        *(short *)(*(int *)(param_1 + 0x78) + 0x30) >> 0xc;
            if (iVar1 < 1) {
                iVar1 = 1;
            }
        } else {
            iVar1 = *(short *)(param_1 + 0x60);
        }
        func_8016AA50(param_1, iVar1);
        if ((*(unsigned short *)(param_1 + 0x82) & 1) != 0) {
            func_8016B428(param_1);
            func_80019064(&D_80186E70);
        }
    }
    return;
}


// @class: regalloc-order
// @stuck: none — MATCH (93 ins)


extern void func_80049CAC(s32 a0, s32 a1);

/* Blk16 lifted to src/shared/engine_types.h (Phase 22). */

DEFINE_func_8012EA90()  /* dedup: shared engine-core @0x8012EA90 (src/shared) */


/* func_8012EC04 — region-a giant (T7).
 * Body = sibling func_8012EA90 (proven MATCH, 3-branch select) verbatim;
 * tail = GTE MulRotMatrix(in place)/SetTrans/ldlv0-rt-stlvnl lifted from
 * DEFINE_func_80132784 (engine_core.h), base ptrs remapped:
 *   rot/trans src M = *(param_1+0x20)+0x34 ;  vector matrix = param_3 (in place). */

DEFINE_func_8012EC04()  /* dedup: shared engine-core @0x8012EC04 (src/shared) */


DEFINE_func_8012EECC()  /* dedup: shared engine-core @0x8012EECC (src/shared) */

DEFINE_func_8012EF34()  /* dedup: shared engine-core @0x8012EF34 (src/shared) */

DEFINE_func_8012EF70()  /* dedup: shared engine-core @0x8012EF70 (src/shared) */

/* func_8012EFB8 — "Handwritten function" (GTE): RotTrans of one SVECTOR.
 * Verbatim PsyQ inline_c.h macro bodies (same set already byte-proven in
 * ov_SC03_099_jr_8012ACE0.c func_801330E0). SetRotMatrix + SetTransMatrix both
 * take the same &D_800AF648 -> gcc CSEs the address into $v0. `flag` has its
 * address taken by a "memory"-clobbering asm, so it lives at 0($sp) and the
 * `return flag` reloads it -> lw $v0, 0($sp) in the epilogue. */

#define gte_SetRotMatrix(r0) __asm__ volatile (          \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldv0(r0) __asm__ volatile (                  \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (                 \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )

/* §37/§124 asm-label alias: the fleet canon declares this `extern void
 * func_8012EFB8(s32 a0);` inside the DEFINE_func_* macros in
 * src/shared/engine_core.h (the one at src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c:1169
 * comes from DEFINE_func_8012EF70()).  The byte-true body returns s32 and takes
 * TWO pointers, so it conflicts on BOTH the return axis and the arity axis.
 * Aliasing the C name sidesteps both with no header edit and no codegen change.
 * This declaration MUST travel with the body. */
s32 aF8012EFB8(void *param_1, void *param_2) __asm__("func_8012EFB8");

s32 aF8012EFB8(param_1, param_2)
    void *param_1;
    void *param_2;
{
    extern u8 D_800AF648;
    s32 *m;
    s32 flag;

    m = (s32 *)&D_800AF648;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
    gte_ldv0(param_1);
    gte_rtps();
    gte_stsxy(param_2);
    gte_stflg(&flag);
    return flag;
}


// @class: other
// @stuck: none — MATCH (33 ins, match_one verified)

DEFINE_func_8012F038()  /* dedup: shared engine-core @0x8012F038 (src/shared) */


DEFINE_func_8012F0BC()  /* dedup: shared engine-core @0x8012F0BC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (clone of confirmed func_8012F214 template; passthrough a0)
DEFINE_func_8012F14C()  /* dedup: shared engine-core @0x8012F14C (src/shared) */


DEFINE_func_8012F1A4()  /* dedup: shared engine-core @0x8012F1A4 (src/shared) */

DEFINE_func_8012F214()  /* dedup: shared engine-core @0x8012F214 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0", func_8012F274);

DEFINE_func_8012F2E8()  /* dedup: shared engine-core @0x8012F2E8 (src/shared) */

DEFINE_func_8012F374()  /* dedup: shared engine-core @0x8012F374 (src/shared) */



// @class: remat
// @stuck: none — MATCH

extern void func_8004914C();
extern void func_800491AC();
extern s32 RotTransPers(s32, s32, s32*, s32*);

s32 *func_8012F40C(s32 *param_1, s32 param_2) {

    extern u8 D_800AF648;
    s32 sxy, p, flag;

    sxy = 0;
    /* $a0-pinned scopes force the &D_800AF648 constant to be rematerialized
       (lui/addiu) before each call instead of CSE-hoisting it into a third
       callee-saved register. */
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
    ((s32 (*)(s32, s32 *, s32 *, s32 *))RotTransPers)(param_2, &sxy, &p, &flag);
    if (flag < 0) {
        *param_1 = sxy = 0;
    } else {
        *param_1 = sxy;
    }
    return param_1;
}


#include "common.h"

/* func_8012F49C — the 3-arg superset of the byte-proven near-twin
 * func_8012F40C (src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c:1202): same
 * $a0-pinned &D_800AF648 remat pair + RotTransPers/flag guard tail, with an
 * extra head that runs func_8004914C/func_800491AC on (param_2->0x20 + 0x34)
 * and a RotTransSV into a local SVECTOR. */

DEFINE_func_8012F49C()  /* dedup: shared engine-core @0x8012F49C (src/shared) */


// @class: schedule
// @stuck: none — MATCH (35 ins). Two unaligned 8-byte memcpy to globals then sh a1/a2/a3 + lhu/or/sh RMW on D_80126B94. KEY: an `__asm__ __volatile__("":::"memory")` barrier between the 2nd memcpy and the halfword section pins the D_80126B94 RMW *read* AFTER both memcpys (without it gcc hoists the lhu between the two memcpy blocks; volatile globals over-anchors it to the END).

DEFINE_func_8012F568()  /* dedup: shared engine-core @0x8012F568 (src/shared) */


DEFINE_func_8012F5F4()  /* dedup: shared engine-core @0x8012F5F4 (src/shared) */



struct S80131E00;
DEFINE_func_8012F68C()  /* dedup: shared engine-core @0x8012F68C (src/shared) */


extern void func_80131B14(void);
extern void func_80131CA8(int a0, int a1);

void func_8012F75C(s32 a0) {
    *(u8 *)(a0 + 0xC1) = 3;
    if (*(s32 *)(a0 + 0xB4) & 0x4) {
        func_80131B14();
        *(s32 *)(a0 + 0x1C) = 0x10;
        *(s16 *)(a0 + 0x98) = 0;
    }
    func_80131CA8(a0, 6);
}

DEFINE_func_8012F7B4()  /* dedup: shared engine-core @0x8012F7B4 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (pending gate)
extern void func_80131170();
extern void func_80131CA8();
extern unsigned char D_80186E8C[];

void func_8012F828(int param_1)
{
    *(unsigned char *)(param_1 + 0xC1) = 4;
    if (*(unsigned int *)(param_1 + 0xB4) & 8) {
        func_80131170(param_1, D_80186E8C, 0xB);
    }
    func_80131CA8(param_1, 9);
}


DEFINE_func_8012F87C()  /* dedup: shared engine-core @0x8012F87C (src/shared) */

extern void func_80131170(s32 a0, s32 a1, s32 a2);
extern void func_80131CA8(int a0, int a1);
extern u8 D_80186E98[];

void func_8012F8C8(u8* arg0) {
    *(u8*)(arg0 + 0xC1) = 7;
    if (*(u32*)(arg0 + 0xB4) & 0x80) {
        ((void (*)(void*, void*, s32))func_80131170)(arg0, D_80186E98, 0xB);
    }
    ((void (*)(void*, s32))func_80131CA8)(arg0, 0x16);
}


DEFINE_func_8012F91C()  /* dedup: shared engine-core @0x8012F91C (src/shared) */

// @class: struct
// @stuck: none — MATCH (123 ins). Keys: 3 stack out-params as ONE struct (kept all live + word-load),
//         branch-polarity inverts on the two if/else, and the 0x98=0 store moved AFTER the 3rd division.
#include "common.h"

DEFINE_func_8012F968()  /* dedup: shared engine-core @0x8012F968 (src/shared) */


DEFINE_func_8012FB54()  /* dedup: shared engine-core @0x8012FB54 (src/shared) */

DEFINE_func_8012FC30()  /* dedup: shared engine-core @0x8012FC30 (src/shared) */

DEFINE_func_8012FCA4()  /* dedup: shared engine-core @0x8012FCA4 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (57 ins), byte-exact via rtu_match on the real TU.
// ROOT CAUSE of the prior 3-off "irreducible schedule-steal": the wave-2 draft had the WRONG ARITY for
//   func_80131B14. It cast the call to (int,int) and passed (param_1, 0x1C), which forced `li a1,0x1C` to be
//   func_80131B14's OWN arg. That premise made the beqz-delay `li a1,0x1C` / jal-delay `move a0,s0` look like an
//   un-reorderable {li,move} schedule-steal (calls.c emits a0 first; sched2 keeps LUID; reorg swaps them).
//   THE FIX: func_80131B14 takes ONE arg — ((void(*)(int))func_80131B14)(param_1). Then:
//     - func_80131B14's own delay slot = `move a0,s0` (its a0 arg), and a1 is NOT live across it.
//     - the `li a1,0x1C` in the beqz(0x100) delay slot is the TERMINAL func_80131CA8(param_1,0x1C)'s arg, which
//       reorg fill_slots_from_thread shares into the delay slot for the beqz-taken (else) edge FOR FREE, because
//       a1 is dead on the fall-through (1-arg func_80131B14 never reads a1) so there is no resource conflict.
//   No barrier, no register pin, no schedule mutation — the correct arity makes the target schedule fall out
//   of stock gcc-2.7.2 reorg. (Lesson for the cookbook: before conceding a delay-slot "steal" as irreducible,
//   re-derive the CALLEE ARITY from the asm — a spurious extra register arg that is live across the call is what
//   blocks reorg from sharing a downstream constant into a branch delay slot.)

extern void func_80131CA8(int a0, int a1);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_80131B14(void);
extern s32 func_80131A34(s32, s32);
extern void func_8012B14C(s32 a0, s32 a1);
extern int  D_80186EA4;

void func_8012FCC4(int param_1) {
    int v1 = *(int *)(param_1 + 0xC4);
    *(char *)(param_1 + 0xC1) = 8;
    if (v1 & 2) {
        *(char *)(param_1 + 0xC1) = 1;
        func_80131CA8(param_1, 3);
        return;
    }
    if (v1 & 1) {
        ((void (*)(int, int))func_80131E00)(param_1, 1);
        return;
    }
    if (*(int *)(param_1 + 0xB4) & 0x100) {
        ((void (*)(int))func_80131B14)(param_1);
        if (*(short *)(param_1 + 0x76) <= 0) {
            ((void (*)(int, int))func_80131E00)(param_1, 0xC);
            return;
        }
        if (func_80131A34(param_1, 4) != 0) {
            *(char *)(param_1 + 0xC2) = 0;
        } else {
            *(short *)(param_1 + 0x98) = 0;
            *(char *)(param_1 + 0xC2) = 1;
        }
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_80186EA4);
        *(int *)(param_1 + 0x1C) = 0;
        func_80131CA8(param_1, 0x1C);
        return;
    }
    func_80131CA8(param_1, 0x1C);
}

// @class: other
// @stuck: clean control-flow fn; expecting MATCH from direct structural reconstruction

extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012CBF4(s32 a0);
void func_801319E0(int);
void func_80131C78(int);
void func_80131CA8(int, int);

DEFINE_func_8012FDA8()  /* dedup: shared engine-core @0x8012FDA8 (src/shared) */


struct S80131E00;
DEFINE_func_8012FE70()  /* dedup: shared engine-core @0x8012FE70 (src/shared) */

DEFINE_func_8012FF00()  /* dedup: shared engine-core @0x8012FF00 (src/shared) */

DEFINE_func_8012FF4C()  /* dedup: shared engine-core @0x8012FF4C (src/shared) */

DEFINE_func_8012FF98()  /* dedup: shared engine-core @0x8012FF98 (src/shared) */

DEFINE_func_8013001C()  /* dedup: shared engine-core @0x8013001C (src/shared) */

DEFINE_func_80130088()  /* dedup: shared engine-core @0x80130088 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (61 ins); shared-tail done=1 at the post-if/else merge point fills the shared jal's delay slot
#include "common.h"

DEFINE_func_801300F4()  /* dedup: shared engine-core @0x801300F4 (src/shared) */


DEFINE_func_801301E8()  /* dedup: shared engine-core @0x801301E8 (src/shared) */



struct S80131E00;

DEFINE_func_80130278()  /* dedup: shared engine-core @0x80130278 (src/shared) */


DEFINE_func_80130314()  /* dedup: shared engine-core @0x80130314 (src/shared) */

DEFINE_func_80130360()  /* dedup: shared engine-core @0x80130360 (src/shared) */

DEFINE_func_801303A0()  /* dedup: shared engine-core @0x801303A0 (src/shared) */


DEFINE_func_801303EC()  /* dedup: shared engine-core @0x801303EC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (55 ins, match_one relocation-masked)

DEFINE_func_80130438()  /* dedup: shared engine-core @0x80130438 (src/shared) */


// @class: schedule
// @stuck: none — MATCH
DEFINE_func_80130514()  /* dedup: shared engine-core @0x80130514 (src/shared) */


DEFINE_func_801305CC()  /* dedup: shared engine-core @0x801305CC (src/shared) */

DEFINE_func_80130650()  /* dedup: shared engine-core @0x80130650 (src/shared) */


DEFINE_func_80130740()  /* dedup: shared engine-core @0x80130740 (src/shared) */

DEFINE_func_801307B0()  /* dedup: shared engine-core @0x801307B0 (src/shared) */

DEFINE_func_80130858()  /* dedup: shared engine-core @0x80130858 (src/shared) */

DEFINE_func_80130898()  /* dedup: shared engine-core @0x80130898 (src/shared) */

DEFINE_func_801308DC()  /* dedup: shared engine-core @0x801308DC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (41 ins, match_one verified; lh@0x18 / lhu@0x1c, andi 0x8000 on uint field)

DEFINE_func_80130974()  /* dedup: shared engine-core @0x80130974 (src/shared) */


DEFINE_func_80130A18()  /* dedup: shared engine-core @0x80130A18 (src/shared) */


DEFINE_func_80130AC4()  /* dedup: shared engine-core @0x80130AC4 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (70 ins). Early-returns (not a shared `mode` var) keep $a0 live on the first path; main-block path reloads $a0 from $s0 at the tail, giving the move+nop delay-slot the target uses.

DEFINE_func_80130AF0()  /* dedup: shared engine-core @0x80130AF0 (src/shared) */


DEFINE_func_80130C08()  /* dedup: shared engine-core @0x80130C08 (src/shared) */

extern void (*D_80186EAC[])(void);

void func_80130D0C(void *a0) {
    D_80186EAC[*(u8 *)((s32)a0 + 0xC1)]();
}

// @class: regalloc-order
// @stuck: none — MATCH (266/266). Levers: pin pa=$s2 p=$s3, tbl=$s0 (NOT s1v — leave natural so switch-mask lands in $v1); tight-block pins for the table-addr temps `register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2")` force offset=$v1/base=$v0 (else compute-into-dest $s0); inline offset `TABLE + s1v*2` (late) keeps the 2-sll delay-slot dup; 0x60000 reuses `tbl` (not a fresh `e`) so it stays $s0 and materializes after rand().
extern s32 rand(void);
extern u8 D_80078E78[];
extern u16 D_80078EB2;
extern u16 D_80078EB4;
extern s16 D_80186EFC[];
extern s16 D_80186F2C[];
extern s16 D_80186F8C[];
extern s16 D_80186F94[];
extern s16 D_80186FB4[];

void func_80130D48(s32 arg0)
{
    register s16 *tbl __asm__("$16");
    register s32 pa __asm__("$18") = arg0;
    register u8 *p  __asm__("$19") = D_80078E78;
    s32 s1v;
    s32 call_a0;
    s32 call_a1;
    s32 cnt;
    s32 r;
    void *ret;

    s1v = func_80131CF4(*(s32 *)((s8 *)pa + 0xBC), 0x15);
    if (s1v == 0) {
        return;
    }

    if (*(u8 *)((s8 *)pa + 0x5E) == 0xB) {
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    }

    switch (s1v & 0xFFFF0000) {
    case 0x10000: {
        u32 x = D_80078EB4;
        u32 y = D_80078EB2;
        u32 b;
        u32 a;

        s1v = 0;
        if (x == y) {
            s1v = 0xC;
        } else if ((y >> 1) >= x) {
            s1v = 3;
        }

        b = *(u16 *)(p + 0x40);
        a = *(u16 *)(p + 0x3E);
        if (b == a) {
            s1v += 0x18;
        } else if ((a >> 1) >= b) {
            s1v += 6;
        }
        { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_80186F2C; tbl = (s16 *)(bp + v1); }

        r = rand() % 100;
        cnt = 0;
    loop27:
        if (r >= *tbl) {
            cnt += 1;
            tbl += 1;
            if (cnt < 3) {
                goto loop27;
            }
        }

        s1v = 0;
        switch (cnt) {
        case 0:
            tbl = D_80186F8C;
            s1v = 0x31;
            break;
        case 1: {
            s32 mx = *(u16 *)(p + 0x3A);
            s32 cur = *(u16 *)(p + 0x3C);
            if (((mx * 7) / 10) >= cur) {
                s1v = 4;
                if ((mx / 2) >= cur) {
                    s1v = 8;
                    if ((mx / 5) >= cur) {
                        s1v = 0xC;
                    }
                }
            }
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_80186F94; tbl = (s16 *)(bp + v1); }
            s1v = 0x32;
            break;
        }
        case 2: {
            s32 mx = *(u16 *)(p + 0x3E);
            s32 cur = *(u16 *)(p + 0x40);
            if (((mx * 7) / 10) >= cur) {
                s1v = 4;
                if ((mx / 2) >= cur) {
                    s1v = 8;
                    if ((mx / 5) >= cur) {
                        s1v = 0xC;
                    }
                }
            }
            { register s32 v1 __asm__("$3"); register s8 *bp __asm__("$2"); v1 = s1v * 2; bp = (s8 *)D_80186FB4; tbl = (s16 *)(bp + v1); }
            s1v = 0x33;
            break;
        }
        }

        r = rand() % 100;
        call_a1 = 0;
    loop50:
        if (r >= *tbl) {
            call_a1 += 1;
            tbl += 1;
            if (call_a1 < 4) {
                goto loop50;
            }
        }
        call_a0 = s1v;
        goto do_call;
    }
    case 0x20000:
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    case 0x30000:
        call_a0 = 0x31;
        call_a1 = 0;
        goto do_call;
    case 0x40000:
        call_a0 = 0x32;
        call_a1 = 0;
        goto do_call;
    case 0x50000:
        call_a0 = 0x33;
        call_a1 = 0;
        goto do_call;
    case 0x60000: {
        s32 rr = rand() & 0xFF;
        tbl = D_80186EFC;
        if (rr >= *tbl) {
            do {
                tbl += 3;
            } while (rr >= *tbl);
        }
        call_a0 = tbl[1];
        if (*(u16 *)(p + 0x40) < 4U) {
            call_a0 = 0x33;
        }
        call_a1 = tbl[2];
        goto do_call;
    }
    case 0x70000:
        call_a0 = 0x27B;
        call_a1 = 0;
        goto do_call;
    default:
        return;
    }

do_call:
    ret = func_8012C658(call_a0, call_a1, pa);
    if (ret != 0) {
        *(u16 *)((s8 *)ret + 0xA) -= 0x20;
    }
}


// @class: loop-guard
// @stuck: none — MATCH (88 ins). Keys: duplicate the c!=0/c==0 bodies verbatim (gcc cross-jumps
//   the shared "|=4;goto tail" into L240 on its own); tail dispatch as `if (((s32(*)(s32))func_8012BCCC)(p) <= 0x8FFF)`
//   (the <= polarity makes the >0x8FFF/0x33-first block the bnez'd else=L298, fall-through = 0x32-first);
//   both AC8 tails cross-jump-merge into the shared L2AC final call. Externs aligned to the file's
//   existing decls for gate-safety: func_80131B14(void) [file line 1486], func_8012B14C/func_8012BCCC
//   canonical (s32) [DEFINE macros], ((s32(*)())func_80131AC8)() no-proto (compatible w/ later 1-arg DEFINE, 2-arg call).


void func_80131170(s32 p, s32 b, s32 c) {
    extern u8 D_80186E80[];

    func_80131B14();
    *(u8 *)(((u8 *)p) + 0xC2) = 0;
    *(u8 *)(((u8 *)p) + 0xC3) = 0;
    *(s16 *)(((u8 *)p) + 0x98) = 0;
    if (((u8 *)b) == 0) {
        ((u8 *)b) = D_80186E80;
    }
    func_8012B14C((s32)((u8 *)p), (s32)((u8 *)b));
    *(s32 *)(((u8 *)p) + 0x1C) = 0;
    if (c != 0) {
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), c) != 0) goto tail;
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x24) != 0) goto tail;
        *(s32 *)(((u8 *)p) + 0xC4) &= ~4;
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x20) != 0) {
            *(s32 *)(((u8 *)p) + 0xC4) |= 4;
        } else {
            *(s16 *)(((u8 *)p) + 0x98) = 0;
        }
    } else {
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x24) != 0) goto tail;
        *(s32 *)(((u8 *)p) + 0xC4) &= ~4;
        if (((s32(*)(s32, s32))func_80131A34)((s32)((u8 *)p), 0x20) != 0) {
            *(s32 *)(((u8 *)p) + 0xC4) |= 4;
        } else {
            *(s16 *)(((u8 *)p) + 0x98) = 0;
        }
    }
tail:
    if (*(s16 *)(((u8 *)p) + 0x76) > 0) {
        return;
    }
    if (((s32(*)(s32))func_8012BCCC)((s32)((u8 *)p)) <= 0x8FFF) {
        if (((s32(*)())func_80131AC8)(((u8 *)p), 0x32) != 0) return;
        ((s32(*)())func_80131AC8)(((u8 *)p), 0x33);
    } else {
        if (((s32(*)())func_80131AC8)(((u8 *)p), 0x33) != 0) return;
        ((s32(*)())func_80131AC8)(((u8 *)p), 0x32);
    }
}


// @class: struct
// @stuck: none — MATCH (8-byte alignment-1 struct copy → lwl/lwr/swl/swr)

   /* size 8, alignment 1 -> unaligned copy */


s32 func_801312D0(s32 param_1, void *param_2)
{
    extern int func_80131CF4(int, int);
    extern M8 D_80186FD4;

    int iVar5;

    iVar5 = func_80131CF4(*(int *)(((int)param_1) + 0xBC), 0x2E);
    if (iVar5 != 0) {
        ((short *)param_2)[2] = 0;
        ((short *)param_2)[0] = 0;
        ((short *)param_2)[1] = (short)iVar5;
    } else {
        *(M8 *)((short *)param_2) = D_80186FD4;
    }
}


// @class: plumbing
// @stuck: none — MATCH (424/424). Verified TWICE: match_one 424/424 standalone AND 424/424
//   relocation-masked through the REAL src/ov_SC01_077/ov_SC01_077_jr_8012ACE0.c at the
//   func_80131340 slot (L1635) with every DEFINE_ macro expanded (cpp -> cc1 -> maspsx
//   --expand-div -> as, exit 0, zero `conflicting types`).
//
// ---------------------------------------------------------------------------------------
// THE TWO LEVERS THAT CRACKED IT (both byte-proven; do not "clean up"):
//
// (1) `case 0: case 1:` SHARE one block. jtbl_801D8144 (read from the sibling overlay data,
//     asm/ov_SC03_099/data/tail2.data.s @801BCE68) is
//       [0]=0x80131440 [1]=0x80131440 [2]=0x80131634 [3]=0x8013174C [4]=0x801318F4
//     — two entries point at the SAME block. That is the ONLY reason the shared block
//     re-tests `*(u8*)(a0+0xC2) == 0` to gate its vector-init half (gcc-2.7.2 has no VRP,
//     so the switch value is not propagated into the case body).
//
// (2) CROSS-JUMP POLARITY (§5a, the 4-instruction shortfall). The `lh 0x76` / E00-vs-C78
//     if-else appears TWICE (case 3's tail @801318DC and case 4 @80131944). Both arms must
//     be written `if (x <= 0) E00(a0,6); else C78(a0);` — the SAME polarity in BOTH sites.
//     Writing case 3 as the "natural" `if (x > 0) C78 else E00` compiles 4 ins SHORT: gcc
//     merges case 3's ENTIRE tail into case 4's (`j` straight to the shared `lh`).
//     Why (ground-truthed against tools/reference/gcc-2.7.2/jump.c):
//       - jump.c:1969 `find_cross_jump(insn, target, 2, ...)` pairs each `j Lend` with every
//         OTHER jump to Lend (the jump_chain) and merges BACKWARD while
//         `rtx_renumbered_equal_p` holds. The forward walk hits the LOWER address first, so
//         case 3 is always e1 (deleted/redirected) and case 4 is e2 (kept) — hence the
//         surviving .L80131954/.L80131964 bodies physically live in case 4.
//       - With the matching polarity, case 3's FIRST `j` is the E00 body -> it merges into
//         .L80131954, leaving `bgtz -> Lelse; j .L80131954; Lelse:`. Lelse now sits directly
//         after the `j`, so jump.c's conditional-jump-around-an-unconditional-jump transform
//         fires and INVERTS it to `blez -> .L80131954`; the C78 body then merges into
//         .L80131964, giving exactly `blez .L80131954 / j .L80131964`. The two sites are now
//         textually different (blez+j vs bgtz+fallthru), so find_cross_jump stops at the
//         branch and both `lh` blocks survive. That asymmetric-looking output is EMITTED BY
//         symmetric source — the inversion is what creates the asymmetry.
//       - With the opposite polarity in case 3, the C78 body merges FIRST, the inversion
//         fires the other way, and case 3 becomes byte-identical to case 4 -> fully merged.
//     NOTE: the §5a volatile-asm barrier is the WRONG tool here — it would also un-merge the
//     .L80131954/.L80131964 call bodies (+8 ins). The fix is polarity, not a barrier.
//
// OTHER BYTE-PROVEN KEYS:
//   - Two SEPARATE locals for the two func_80131CF4 results. Reusing one `temp` lets gcc
//     coalesce it into $a1 for the second call and emits an extra `move a1,v0` up at the
//     FIRST call site (+1 ins, whole-function cascade).
//   - The /3 store block: `*(s32*)(a0+0x14) = (-D_801D94AC)/3;` must come FIRST (before the
//     0x1C/0xC2 stores). Written after them, gcc will not hoist the D_801D94AC load above
//     `sw zero,0x1C($s0)` and the mult-latency slots fill differently (9 ins reordered).
//   - sp10/18/20/28 are four 8-byte, 2-byte-aligned vectors. `sp28 = sp20` is a DEAD
//     aggregate copy that gcc-2.7.2 KEEPS (no aggregate DSE) — it is load-bearing, not dead
//     code. align(2) < 4 is what makes the copies lwl/lwr + swl/swr (cf. the TU's own `M8`
//     align-1 idiom at L1614, used by func_801312D0 directly above this slot).
//   - Every vector field read is `lhu` -> the fields are u16. Contrast `lh 0xA($s0)`,
//     `lh 0x76($s0)`, `lh 0x12($v0)`, which are genuinely signed (s16 casts).
//   - `func_801319E0(a0)` gets a NOP delay slot, not `addu $a0,$s0,$zero`: cse-2.7.2 deletes
//     the redundant arg copy because $a0 still holds the param at the first call. Declaring
//     it 0-arg to "explain" the nop would be wrong (canonical is 1-arg) — just call it.
//   - `*(s32*)(a0+0x10) = *(s32*)(a0+0x10) * 15 / 16;` -> (x<<4)-x then the bgez/+0xF/sra-4
//     signed-div-by-16 fixup. `>>4` would drop the fixup.
//   - func_80131D68 is 2-arg here — (a0, D_801D94A8); a1 is reloaded from the global before
//     all 5 of its call sites (the value is NOT cached in a callee reg: gcc-2.7.2's cse is
//     extended-basic-block-local, so each join point reloads).
//
// DECL RECONCILE (§17a-1) — the TU declares these at FILE scope BEFORE this slot (L1635),
// so they are HARD `conflicting types` if redeclared differently. Sigs below are byte-copies
// of the canonical set; where the canonical return is `void` but the asm USES $v0, the read
// is done with a call-site cast (the codebase's own idiom, engine_core.h L17026) — which is
// codegen-neutral:
//   - func_8012CBF4 / func_8012CBA4 / func_8012CC64: canonical `void`, $v0 used -> cast.
//   - func_80131E00: canonical takes `struct S80131E00 *` -> declared K&R no-proto here
//     (compatible with the prototyped decl at L1250; params are promotion-safe: ptr + s32),
//     matching the TU's own precedent `extern void func_80131CA8();` at L1189.
//   - func_8012B23C / func_8012CC64 / func_8012CEB0 / func_8012DBD0 / func_8012CBF4 are
//     DEFINE_-instantiated ABOVE this slot — the decls here are exact-identical
//     redeclarations (legal C), not new sigs.
//   - func_80131CF4 is declared 2-arg `(int,int)`, mirroring func_801312D0's already-matched
//     block-scope decl at L1619 (the engine_core canonical 1-arg form is the stale one).

extern void func_801319E0(s32 a0);
extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012CC64(s32 a0, s32 a1);
extern int func_80131D68(int, int);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_80131E00();
extern void func_80131C78(s32 a0);
extern void func_80131CA8(int a0, int a1);

extern s32 D_801D94A8;
extern s32 D_801D94AC;

void func_80131340(s32 a0)
{
    /* 8-byte, align-2 vector: align < 4 is what makes the assignments unaligned
     * (lwl/lwr + swl/swr) block moves. Block-scope so the body stays self-contained
     * for the dedup_propagate lift (§28-#1) and cannot collide with the TU's `M8`. */
    struct V8 {
        u16 vx, vy, vz, pad;
    };
    extern struct V8 D_80186FD4;
    /* BLOCK-scope, mirroring the already-matched func_801312D0's decl at TU L1619: the
     * later DEFINE_func_80131AC8() (TU L1964, AFTER this slot) redeclares func_80131CF4
     * with the stale 1-arg engine_core canonical. A file-scope `extern int
     * func_80131CF4(int,int);` here is a HARD `conflicting types` against it (cc1 rc=33,
     * measured); block-scope goes out of scope before that macro and compiles clean. */
    extern int func_80131CF4(int, int);

    struct V8 sp10;
    struct V8 sp18;
    struct V8 sp20;
    struct V8 sp28;
    s32 temp;
    s32 var_a1;

    if (*(s16 *)(a0 + 0xA) >= 0x10) {
        func_801319E0(a0);
        return;
    }

    temp = func_80131CF4(*(s32 *)(a0 + 0xBC), 0x2E);
    if (temp != 0) {
        sp10.vz = 0;
        sp10.vx = 0;
        sp10.vy = temp;
    } else {
        sp10 = D_80186FD4;
    }

    if (*(s32 *)(a0 + 0x10) != 0 || *(s32 *)(a0 + 0x18) != 0) {
        var_a1 = func_80131CF4(*(s32 *)(a0 + 0xBC), 0x19);
        if (var_a1 == 0) {
            var_a1 = 0x50;
        }
        func_8012DBD0(a0, var_a1,
                      *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
    case 1:
        if (*(s32 *)(a0 + 0xC4) & 4) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
            func_80131E00(a0, 0xD);
            return;
        }
        if (*(u8 *)(a0 + 0xC2) == 0) {
            *(u8 *)(a0 + 0xC2) = 1;
            sp18.vx = *(u16 *)(a0 + 0x3A);
            sp18.vy = *(u16 *)(a0 + 0x3E);
            sp18.vz = *(u16 *)(a0 + 0x42);
            sp20 = sp18;
            sp20.vx += sp10.vx;
            sp20.vy += sp10.vy;
            sp20.vz += sp10.vz;
            sp28 = sp20; /* load-bearing dead aggregate copy — gcc-2.7.2 has no aggregate DSE */
            func_8012CEB0((s32)&sp18, (s32)&sp20, 1);
            sp20.vx -= sp10.vx;
            sp20.vy -= sp10.vy;
            sp20.vz -= sp10.vz;
            *(u16 *)(a0 + 0x3A) = sp20.vx;
            *(u16 *)(a0 + 0x3E) = sp20.vy;
            *(u16 *)(a0 + 0x42) = sp20.vz;
            *(u16 *)(a0 + 0x6) = sp20.vx;
            *(u16 *)(a0 + 0xA) = sp20.vy;
            *(u16 *)(a0 + 0xE) = sp20.vz;
        }
        D_801D94A8 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801D94A8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801D94A8 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (D_801D94A8 & 0x2000) {
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            *(u8 *)(a0 + 0xC2) = 2;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
        } else if (D_801D94A8 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 2;
            *(s32 *)(a0 + 0x1C) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 2:
        if (*(s32 *)(a0 + 0xC4) & 4) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
            func_80131E00(a0, 0xD);
            return;
        }
        D_801D94AC = *(s32 *)(a0 + 0x14);
        D_801D94A8 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801D94A8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801D94A8 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (D_801D94A8 & 0x2000) {
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            func_80143B6C(a0, 1);
            /* MUST precede the 0x1C/0xC2 stores — see the header note on the /3 block. */
            *(s32 *)(a0 + 0x14) = (-D_801D94AC) / 3;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u8 *)(a0 + 0xC2) = 3;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        } else if (D_801D94A8 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 3;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 3:
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        if (*(u8 *)(a0 + 0xC3) & 1) {
            D_801D94A8 = ((s32 (*)(s32))func_8012CBA4)(a0);
            if (D_801D94A8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            if (!(D_801D94A8 & 0x6000)) {
                func_80131E00(a0, 0xD);
                return;
            }
        } else {
            D_801D94A8 = ((s32 (*)(s32))func_8012CBF4)(a0);
            if (D_801D94A8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (D_801D94A8 & 0x4000) {
                func_8012B23C(a0);
                *(u8 *)(a0 + 0xC2) = 4;
                break;
            } else if (D_801D94A8 & 0x2000) {
                if (func_80131D68(a0, D_801D94A8) == 1) {
                    return;
                }
                *(u8 *)(a0 + 0xC3) |= 1;
            } else if (D_801D94A8 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
        }
        if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
            func_80143B6C(a0, 1);
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) < 0x11) {
            break;
        }
        if (!(D_801D94A8 & 0x6000)) {
            func_80131E00(a0, 0xD);
            return;
        }
        /* polarity MUST match case 4's — see the cross-jump note in the header. */
        if (*(s16 *)(a0 + 0x76) <= 0) {
            func_80131E00(a0, 6);
        } else {
            func_80131C78(a0);
        }
        break;

    case 4:
        D_801D94A8 = ((s32 (*)(s32))func_8012CBA4)(a0);
        if (D_801D94A8 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (D_801D94A8 & 0x2000) {
            if (func_80131D68(a0, D_801D94A8) == 1) {
                return;
            }
            if (*(s16 *)(a0 + 0x76) <= 0) {
                func_80131E00(a0, 6);
            } else {
                func_80131C78(a0);
            }
        } else {
            if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
                func_80143B6C(a0, 1);
            }
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
                func_80131E00(a0, 0xD);
                return;
            }
        }
        break;
    }

    func_80131CA8(a0, 0x2F);
}



/* Canonical sigs (consistent with src/ov_SC01_077/ov_SC01_077.c + engine_core.h):
 *  - func_80131CA8: canonical 'extern void func_80131CA8(int, int)' (overlay .c L742,
 *    engine_core.h). Its $v0 return IS used here (asm: jal ...; bnez $v0), so cast at the
 *    call site to read it -- the codebase's own idiom (engine_core.h L17026:
 *    ((s32 (*)(int, int))func_80131CA8)(arg0, 0x2C)). Byte-neutral, no sig conflict.
 *  - func_8012C218: canonical 'void func_8012C218(void *a0)' (DEFINE_func_8012C218).
 *  - func_8002A04C: main-EXE callee (src/800.c), undeclared in this TU -> declare locally,
 *    arity 1 (asm: jal func_8002A04C; delay-slot a0=s0). No conflict.
 */
DEFINE_func_801319E0()  /* dedup: shared engine-core @0x801319E0 (src/shared) */


/* func_80131A34 — MATCH (37/37).
 * Keys:
 *  - func_80131CF4 is the TU's 2-arg canonical `(int,int)` and the SECOND arg is the
 *    incoming `a1` (kind). $a1 already holds it, so the call costs no arg-setup insn --
 *    but the extra arg ref is what breaks the sched2 prologue save-order tie so
 *    `sw $s0` schedules before `sw $ra` (cookbook §52a RC-3 / sched.md S7). Without it
 *    the pair comes out ra-then-s0 (2 mismatches); the `const`-load form of RC-3 fixes
 *    the tie but OVER-frees (the `lw $a0` hoists above both saves, 3 mismatches).
 *  - Declaration is BLOCK-SCOPE on purpose, mirroring func_801312D0 (TU L1619) and
 *    func_80131340 (TU L1822): the later DEFINE_func_80131AC8() re-declares
 *    func_80131CF4 with the stale 1-arg engine_core canonical, so a file-scope 2-arg
 *    decl here is a hard `conflicting types` (cc1 rc=33).
 *  - func_8012A828 is the TU's file-scope canonical (L280) `(s32, void *)`; `p` rides in
 *    $a1 from the return of func_80131CF4, so no move is emitted.
 */
extern void func_8012A828(s32 a0, void *a1);

s32 func_80131A34(s32 a0, s32 a1)
{
    extern int func_80131CF4(int, int);
    void *p;

    p = (void *)func_80131CF4(*(s32 *)(a0 + 0xBC), a1);
    if (p != 0) {
        if (a1 == 0xB || a1 == 8 || a1 == 0x20) {
            *(s32 *)(a0 + 0xC4) |= 4;
        } else {
            *(s32 *)(a0 + 0xC4) &= -5;
        }
        func_8012A828(a0, p);
        return 1;
    }
    return 0;
}


DEFINE_func_80131AC8()  /* dedup: shared engine-core @0x80131AC8 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (89 ins). Reconcile: TU canonical decl is `void func_80131B14(void)`
//   (ov_SC01_077_a.c L1676/L1756; callers cast to (void(*)(int)) when passing p), so the def MUST be
//   (void) or cc1 hard-errors `conflicting types` (exit 33). §42c lever #6: capture incoming $a0 into a
//   NORMAL pseudo (`register u8 *a0v __asm__("$4"); u8 *p = a0v;`) so p gets a callee-saved home ($s0).
//   func_8012B2CC/func_8012B23C are file-scope DEFINE'd here (split L740/L744) as void(s32) — do NOT redeclare;
//   the (void(*)(void*)) cast on the bare name is byte-neutral. Body keys: e(0x5E) as s32 not u8 (kills the
//   compare-time andi 0xff); f76 dual-width via per-access casts (lhu in the decrement, lh in the <=0 compare);
//   the p->f20 reload split into TWO separate temps so the 2nd load takes $v0 not $v1.

void func_80131B14(void) {
    register u8 *a0v __asm__("$4");
    u8 *p = a0v;

    extern void func_8002A520(void *);
    extern void func_8002A790(void *);
    extern u8 D_80186FDC;

    s32 e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(s16 *)(p + 0x82) = 0;
            *(s16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(s16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(s16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec <= 0) dec = 1;
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
        }
        ((void (*)(void *))func_8016AA50)(p);
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            ((void(*)(void *))func_80019064)(&D_80186FDC);
        }
    }

    *(u16 *)(p + 0x5C) = *(u16 *)(p + 0x5C) & 0xFFFE;

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) <= 0) *(s16 *)(p + 0x5C) = 0;

    {
        s32 r = *(s32 *)(p + 0x20);
        *(s16 *)(r + 0x12) = (*(u16 *)(p + 0x62) + 0x800) & 0xFFF;
        {
            s32 r2 = *(s32 *)(p + 0x20);
            *(s16 *)(r2 + 0x14) = 0;
            *(s16 *)(r2 + 0x10) = 0;
        }
    }

    ((void (*)(void *))func_8012B2CC)(p);
    ((void (*)(void *))func_8012B23C)(p);
}

DEFINE_func_80131C78()  /* dedup: shared engine-core @0x80131C78 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0", func_80131CA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0", func_80131CF4);

struct S80131E00;
DEFINE_func_80131D68()  /* dedup: shared engine-core @0x80131D68 (src/shared) */


extern void (*D_80186FEC[])(struct S80131E00 *a0);

void func_80131E00(struct S80131E00 *a0, s32 a1) {
    a0->field_B0 = a1;
    D_80186FEC[a1](a0);
}

DEFINE_func_80131E38()  /* dedup: shared engine-core @0x80131E38 (src/shared) */

struct S80131E00;
DEFINE_func_80131E7C()  /* dedup: shared engine-core @0x80131E7C (src/shared) */

DEFINE_func_80131EE4()  /* dedup: shared engine-core @0x80131EE4 (src/shared) */

extern void (*D_80187044[])(void);

void func_80131EEC(void *a0) {
    D_80187044[*(u16 *)((s32)a0 + 0x2)]();
}

extern void (*D_8018708C[])(void);

void func_80131F28(void *a0) {
    D_8018708C[*(u16 *)((s32)a0 + 0x2)]();
}

extern void (*D_80187094[])(void);

void func_80131F64(s32 *a0) {
    D_80187094[*(u16 *)((s32)a0 + 2)]();
}

extern s32 (*D_8018709C[])();

s32 func_80131FA0(s16 *a0) {
    return D_8018709C[(u16)a0[1]]();
}

extern s32 (*D_801870A4[])();

s32 func_80131FDC(s16 *a0) {
    return D_801870A4[(u16)a0[1]]();
}

#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);

/* §37 asm-label aliases: D_80187044 is declared in this TU as `void (*[])(void)`
 * (func_80131EEC's dispatch table) — a conflicting type. The 20-byte-stride view
 * below is this function's own. D_80187048 == D_80187044 + 4 is a SEPARATE
 * per-overlay symbol and is referenced BY NAME, never as base+literal (§84). */
extern int tbl_D_80187044[][5] __asm__("D_80187044");
extern int tbl_D_80187048[][5] __asm__("D_80187048");

void func_80132018(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
        *(int *)(param_1 + 0x58) = (int)&tbl_D_80187048[*(unsigned short *)(param_1 + 0x70) & 0xfff];
        *(int *)(param_1 + 0xdc) = tbl_D_80187044[*(unsigned short *)(param_1 + 0x70) & 0xfff][0];
        *(short *)(param_1 + 0xfc) = (*(unsigned short *)(param_1 + 0x70) >> 12) << 9;
    }
}


DEFINE_func_801320D0()  /* dedup: shared engine-core @0x801320D0 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018704C;

void func_801320D8(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018704C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018705C;

void func_80132144(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018705C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018706C;

void func_801321B0(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018706C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}



// @class: plumbing
// @stuck: none — MATCH expected; simple if/else, param saved in $s0 across call

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018707C;

void func_8013221C(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        func_8001C214(v0, 0);
        *(int *)(param_1 + 0x58) = (int)&D_8018707C;
        *(short *)(param_1 + 0x5c) = 0x80;
        *(unsigned short *)(param_1 + 2) += 1;
    }
}


// @class: regalloc-order
// @stuck: none — MATCH (97 ins, relocation-masked)
DEFINE_func_80132288()  /* dedup: shared engine-core @0x80132288 (src/shared) */


DEFINE_func_8013240C()  /* dedup: shared engine-core @0x8013240C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH

/* func_801325B8 — TMD-shaped MIMe apply (ov_SC01_077).
 *
 * Levers used (all §17/§49):
 *  1. $a0 PIN on the rolling TMD base `p` (§17). The target re-materialises
 *     `addu $a0,$s4/$s5,$zero` before each flags test; a plain `int p` is
 *     copy-propagated away, so the copy must be forced with a hard-reg pin.
 *  2. $s0/$s1/$s2 PINS on m/n/dv (§17 regalloc-ORDER). Unpinned, global.c's
 *     density sort hands m=$s1, dv=$s0, n=$s2 — the exact inverse of the target.
 *  3. Two-statement `ofs = ((x>>2)<<2) + 0xC; p + ofs;` — fold's `associate`
 *     rewrites the single expression `p + t + 12` to `(p+t)+12` (addu;addiu);
 *     splitting the statement keeps the target's `addiu $v0,$v0,0xC; addu`.
 *  4. THE CLOSER (§49 birthing boost): `c = *(int*)(m+8); dv += c*8;` instead of
 *     `dv += *(int*)(m+8)*8;`. As a fresh compiler temp the load's dest has
 *     reg_n_sets==1, so sched1's birthing_insn_p hands it LAUNCH_PRIORITY
 *     0x7f000001 and — scheduling BACKWARD — sinks it past the un-boosted
 *     `lw $s1,0xC($s0)`, which then floats ahead of it in the .greg stream and
 *     sched2's LUID tiebreak preserves the inversion. Routing the load through a
 *     `c` that is assigned in BOTH halves makes reg_n_sets==2, the boost never
 *     fires, both loads tie at priority 1, and the LUID tiebreak emits them in
 *     source order. Zero-byte dial: same instructions, correct order.
 */

DEFINE_func_801325B8()  /* dedup: shared engine-core @0x801325B8 (src/shared) */


DEFINE_func_8013277C()  /* dedup: shared engine-core @0x8013277C (src/shared) */


DEFINE_func_80132784()  /* dedup: shared engine-core @0x80132784 (src/shared) */

DEFINE_func_80132DC4()  /* dedup: shared engine-core @0x80132DC4 (src/shared) */

extern void Square0(s32 *a0, s32 *a1);
extern s16 D_80126CAC;
extern s16 D_80126CB0;

s32 func_80132E6C(s16 *a0) {
    s32 in[3];
    s32 out[3];
    in[0] = a0[3] - D_80126CAC;
    in[1] = 0;
    in[2] = a0[7] - D_80126CB0;
    Square0(in, out);
    return out[0] + out[2];
}

DEFINE_func_80132EC4()  /* dedup: shared engine-core @0x80132EC4 (src/shared) */

DEFINE_func_80132EF4()  /* dedup: shared engine-core @0x80132EF4 (src/shared) */

/* func_80132F40 — ov_SC01_077 (jr_8012ACE0 region), 72 ins, -O2.  *** MATCH ***
 *
 * Verified:
 *   python3 tools/match_one.py func_80132F40 --c .run/near6/wave23/func_80132F40.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8012ACE0
 *   -> MATCH (72 ins)
 *
 * ---------------------------------------------------------------------------
 * WHAT THE WAVE-22 SEED GOT WRONG (the 6-mismatch plateau, and why s32 "cost 3")
 * ---------------------------------------------------------------------------
 * The seed's note blamed the `addiu $s3,$sp,0x10` hoist on a *whole-function CSE
 * fork keyed on s16-vs-s32 w/h*, and concluded the s32 world was unreachable.
 * Both halves of that are wrong, and the real mechanism is a reusable idiom.
 *
 * The hoisted register is the block-move source-address pseudo (reg 83 =
 * `(plus fp 16)`, created by expand for `v[1] = v[0]`).  Whether it survives is
 * decided by ONE thing: does CSE's *extended basic block* still contain it when
 * CSE reaches the two `&v[0]` call arguments?
 *
 *   cse.c:cse_end_of_basic_block scans `while (p && GET_CODE (p) != CODE_LABEL)`.
 *   It can walk PAST a conditional jump only via
 *     - follow_jumps  : target label preceded by a BARRIER, LABEL_NUSES == 1, or
 *     - skip_blocks   : "branch around a block", no labels inside  (-O2 sets both)
 *   and it BREAKS EARLY on
 *     `if (! after_loop && NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_END) break;`
 *
 * With s16 w the min block stayed a *diamond* (jump.c's `if(..) x=a; else x=b;`
 * -> `x=b; if(..) x=a;` at jump.c:699 is blocked when the moved insn carries a
 * REG_EQUAL note — the sign_extend note from the sll/sra pair).  The diamond's
 * BARRIER + join label ended CSE's block before the calls, so `&v[0]` was
 * recomputed at each site.  With s32 w the diamond was flattened in jump1, and
 * skip_blocks then walked CSE straight through to both call sites -> reg 83 was
 * substituted, went live across a call, and took a 5th callee-saved register.
 * So the fork was never about the *type* — it was about the CFG shape at CSE.
 *
 * ---------------------------------------------------------------------------
 * THE NEW LEVER  (cookbook candidate: "zero-instruction CSE path cut")
 * ---------------------------------------------------------------------------
 * `do { } while (0);` emits NOTE_INSN_LOOP_BEG/CONT/END and ZERO instructions.
 * A NOTE_INSN_LOOP_END is exactly what cse1 (after_loop == 0) breaks its
 * extended basic block on.  Dropping one between the struct copy and the call
 * sites cuts the path, kills the hoist, and costs nothing:  73 ins -> 70 ins.
 * (Measured: without it this same file is 75 ins / 58 mismatched.)
 * It is *not* an ordering/pressure hack — 1..8 empty `__asm__ __volatile__("")`
 * barriers, which lengthen live ranges but emit no LOOP notes, changed the hoist
 * by exactly nothing, which refutes the global.c allocno-priority explanation.
 *
 * ---------------------------------------------------------------------------
 * THE MIN BLOCK (idx 37..44)
 * ---------------------------------------------------------------------------
 *      lh   $v1,8($v0)      w        (both loads are SImode sign_extend -> `lh`)
 *      lh   $v0,0xA($v0)    h        (reuses the dying pointer's $v0)
 *      nop                           (load-delay; nothing schedulable)
 *      addu $a0,$v0,$zero   hh = h   (a REAL source-level carrier)
 *      slt  $v0,$v0,$v1     c = h<w  (reuses $v0 because hh now carries h)
 *      beqz $v0,.L80132FF4
 *       addu $s2,$v1,$zero  m = w    (else-arm, moved by jump.c:699 in jump2)
 *      addu $s2,$a0,$zero   m = hh
 *
 * Three locals legitimately share $v0 back-to-back — p dies at h's load, h dies
 * at the slt (hh carries its value), c is born there.  That chain is what makes
 * `slt $v0,$v0,$v1` possible and is why the carrier is mandatory: with h and c
 * on $2 but NO carrier, gcc emits `addu $s2,$v0,$zero` after the slt has already
 * clobbered $v0 — silently wrong code.  Do not remove `hh`.
 *
 * The carrier must be a *pinned* hard register: as a plain pseudo, cse2 (which
 * runs with after_loop == 1 and therefore ignores the LOOP_END) canonicalises it
 * back to h via canon_reg and flow deletes the copy (measured: 71 ins).
 *
 * Ablations (each measured with match_one):
 *   drop the do{}while(0) -> 75 ins / 58     drop `p`  pin -> 71 ins / 40
 *   drop `h`  pin         -> 71 ins / 33     drop `c`  pin -> 70 ins / 36
 *   drop `hh` pin         -> 71 ins / 32     drop `q`  pin -> 72 ins / 12
 *   adding a `w`->$3 pin or an `m`->$18 pin -> still MATCH (so both are omitted)
 *
 * Canonical decls (wave22_targets.json sig_hints) verbatim; D_80126BE0 is
 * declared exactly as the 20+ sibling TUs already declare it.
 */
extern void func_8012F038();
extern void func_8012F14C();
extern s32 func_80135888(s32, s32, s32, s32);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_80126BE0[];

void func_80132F40(s32 arg0)
{
    typedef struct { u16 vx, vy, vz, pad; } Svec_80132F40;

    Svec_80132F40 v[4];
    register Svec_80132F40 *q __asm__("$17");
    register s16 *p __asm__("$2");
    register s32 h __asm__("$2");
    register s32 c __asm__("$2");
    register s32 hh __asm__("$4");
    s32 w;
    s32 m;

    q = &v[1];
    v[0].vx = D_80126B5E;
    v[0].vy = D_80126B62;
    v[0].vz = D_80126B66;
    v[1] = v[0];

    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58),
                      (s32)D_80126BE0, (s32)q) != 0) {
        /* zero-instruction NOTE_INSN_LOOP_END: cuts cse1's extended basic block
         * so the block-move address pseudo cannot reach the two &v[0] args. */
        do { } while (0);

        p = (s16 *)((*(s32 *)(arg0 + 0x58) & 0x0FFFFFFF) | 0x80000000);
        w = p[4];
        h = p[5];
        hh = h;
        c = (h < w);
        if (c) { m = hh; } else { m = w; }

        func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34, &v[0], q);
        v[1].vy = m;
        func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34, q, &v[0]);
        D_80126B5E = v[0].vx;
        D_80126B62 = v[0].vy;
        D_80126B66 = v[0].vz;
    }
}


DEFINE_func_80133060()  /* dedup: shared engine-core @0x80133060 (src/shared) */

// @class: other
// @stuck: none — MATCH (110/110 ins, symcheck SYMS-OK). PsyQ GTE inline-asm block (SetTransMatrix before SetRotMatrix, ldv0/rtv0tr/stlvnl/stflg) + §43 K&R s16 param_3 (in-place `sll $a2,$a2,16` tell) + 16-byte s32[4] locals for the 0x10/0x20/0x30 slot order.
#include "common.h"

#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldv0(r0) __asm__ volatile (                  \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )

#define gte_rtv0tr() __asm__ volatile (                  \
    "nop;"                                               \
    "nop;"                                               \
    "mvmva 1, 0, 0, 0, 0"                                \
    :                                                    \
    :                                                    \
    : "memory" )

#define gte_stlvnl(r0) __asm__ volatile (                \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (                 \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )

extern u8 D_800AF648;
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);

void func_801330E0(param_1, param_2, param_3)
    void *param_1;
    s16 *param_2;
    s16 param_3;
{
    s32 *m;
    s32 sxyz[4];
    s32 pos[4];
    s32 flag;
    s32 z;

    m = (s32 *)&D_800AF648;
    gte_SetTransMatrix(m);
    gte_SetRotMatrix(m);
    gte_ldv0(param_1);
    gte_rtv0tr();
    gte_stlvnl(sxyz);
    gte_stflg(&flag);

    z = sxyz[2];
    pos[2] = z + param_3;
    if (z != 0) {
        pos[0] = sxyz[0] * pos[2] / z;
        pos[1] = sxyz[1] * pos[2] / z;
    } else {
        pos[1] = 0;
        pos[0] = 0;
    }
    pos[0] -= m[5];
    pos[1] -= m[6];
    pos[2] -= m[7];
    ApplyTransposeMatrixLV(m, pos, sxyz);
    param_2[0] = sxyz[0];
    param_2[1] = sxyz[1];
    param_2[2] = sxyz[2];
}


#include "common.h"

/* 32-byte opaque block: drives gcc's movstrsi block-move (4x lw / 4x sw, cookbook
 * struct-fold) instead of 8 serial lw/sw pairs. Locally named (engine_types.h's
 * identical `Blk32` is an anonymous-tag typedef -> a same-name redefinition here
 * is a C89 error in the real TU). */
typedef struct { s32 w[8]; } Blk32L;

extern u8 D_80126B5C; /* canonical decl (engine_core.h DEFINE_func_8012BD14) */
extern s32 D_80126B5C_w __asm__("D_80126B5C"); /* same symbol, s32 view */
extern s32 D_80126B60;
extern s32 D_80126B64;

extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
extern void func_8012B2CC(s32 a0);
extern void func_8013339C(s16 *a0, s16 *a1);
extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);

void func_80133298(s32 *a0)
{
    s32 in[3];
    s32 out[3];
    s32 tmp[3];
    Blk32L m;

    in[0] = D_80126B5C_w;
    in[1] = D_80126B60;
    in[2] = D_80126B64;
    func_8012F0BC((s32 *)(a0[8] + 0x34), in, tmp);
    func_8012B2CC((s32)a0);
    m = *(Blk32L *)(a0[8] + 0x34);
    func_8013339C((s16 *)&m, (s16 *)(a0[8] + 0x18));
    func_8012F1A4((s32 *)&m, (s32)tmp, out);
    D_80126B5C_w = out[0];
    D_80126B60 = out[1];
    D_80126B64 = out[2];
}


// @class: schedule
// @stuck: none — MATCH
DEFINE_func_8013339C()  /* dedup: shared engine-core @0x8013339C (src/shared) */


DEFINE_func_8013361C()  /* dedup: shared engine-core @0x8013361C (src/shared) */

// @class: plumbing
// @stuck: none — MATCH

extern s32 D_801D94F0;
extern s32 D_801D94F4[];
extern int D_801D94F8;
extern void func_80136BC4(s32 a0);

void func_801336E8(void *a0, int a1, int a2) {
    if (a0 != 0) {
        (*(void * *)&D_801D94F0) = a0;
        ((void (*)(void))func_80136BC4)();
    }
    (*(int *)&D_801D94F4) = a1;
    D_801D94F8 = a2;
}


extern s32 D_801D94F4[];
extern s32 D_801D94F0;
extern void func_80136BC4(s32);

void func_8013373C(s16 arg0) {
    s32 temp = D_801D94F4[arg0];
    if (temp != 0) {
        D_801D94F0 = temp;
        func_80136BC4(temp);
    }
}


// @class: regalloc-order
#include "common.h"



s32 func_80133784(s32 arg0, void *arg1, s32 arg2) {
    extern s32 func_80047D3C(s32);
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern Box_80133784 * D_801870AC;
    extern Box_80133784 * D_801870B0;
    extern s16 D_801D94FC;
    extern u16 D_801D9500;

    register s32 s1 __asm__("$17");
    s32 s2;
    register s16 s3 __asm__("$19");
    register s32 s4 __asm__("$20");
    register s16 a0v __asm__("$4");
    register s16 arg0s __asm__("$21");
    s32 dx, dy, dz;
    s32 r, ret;

    a0v = ((s16)arg0);
    s1 = 0;
    s3 = 0;
    s4 = 0;
    s2 = 0;
    arg0s = a0v;
    D_801870AC->f6 = -0x7FFF;
    D_801870B0->f6 = 0x7FFF;
    D_801870AC->f0 = ((Box_80133784 *)arg1)->f0;
    D_801870AC->f4 = ((Box_80133784 *)arg1)->f4;
    D_801870B0->f0 = ((Box_80133784 *)arg2)->f0;
    D_801870B0->f4 = ((Box_80133784 *)arg2)->f4;
    D_801D9500 = 0;
    D_801D94FC = 0;

    if ((s16)a0v == 0) {
        s16 sx = ((Box_80133784 *)arg2)->f0 - ((Box_80133784 *)arg1)->f0;
        s16 sy = ((Box_80133784 *)arg2)->f2 - ((Box_80133784 *)arg1)->f2;
        s16 sz = ((Box_80133784 *)arg2)->f4 - ((Box_80133784 *)arg1)->f4;
        if (sx == 0 && sy == 0) {
            s32 zt = (sz == 0);
            __asm__("addu %0,%1,$zero" : "=r"(s2) : "r"(zt));
        }
        D_801870AC->f2 = ((Box_80133784 *)arg1)->f2 - 4;
        r = func_80047D3C(sx * sx + sz * sz);
        if (r < 3) {
            r = 4;
        } else if (r < 5) {
            r += 1;
        }
        D_801870B0->f2 = ((Box_80133784 *)arg2)->f2 + r + 1;
    } else {
        D_801870AC->f2 = ((Box_80133784 *)arg1)->f2;
        if ((s16)a0v == 2) {
            D_801870B0->f0 = D_801870AC->f0;
            D_801870B0->f2 = D_801870AC->f2 + 6;
            s2 = 1;
            D_801870B0->f4 = D_801870AC->f4;
        } else {
            D_801870B0->f2 = ((Box_80133784 *)arg2)->f2;
        }
    }

    while (1) {
        s32 ret0;
        register s32 retc __asm__("$3");
        __asm__ __volatile__("");
        ret0 = func_80133AB0(arg0s, (s16)D_801870AC->f0, (s16)D_801870AC->f4, (*(s32*)&D_801D94F0));
        __asm__("addu %0,%1,$zero" : "=r"(retc) : "r"(ret0));
        ret = retc;
        if (ret == 0) goto after;
        s4 |= ret;
        if (s2 != 0) goto after;
        {
            s16 oldc = s3;
            s3 = s3 + 1;
            if (oldc >= 5) break;
        }
    }

    D_801870B0->f0 = D_801870AC->f0;
    D_801870B0->f2 = D_801870AC->f2;
    s1 = 0x2000;
    D_801870B0->f4 = D_801870AC->f4;
    goto store_out;

after:
    if ((s16)s4 != 0 || D_801D94FC != 0) {
        s16 t;
        __asm__ __volatile__("" :: "r"(s4));
        t = D_801870AC->f6;
        if (t >= -0xBCB) {
            if (t < -0x578) {
                s1 |= 0x4000;
            } else {
                s1 |= 0x8000;
            }
        }
        if ((s16)D_801870B0->f6 < -0xBCB) {
            s1 |= 0x2000;
        }
    store_out:
        ((Box_80133784 *)arg2)->f0 = D_801870B0->f0;
        ((Box_80133784 *)arg2)->f2 = D_801870B0->f2;
        ((Box_80133784 *)arg2)->f4 = D_801870B0->f4;
        ((Box_80133784 *)arg2)->f6 = D_801D9500;
        return s1 & 0xFFFF;
    }
    ((Box_80133784 *)arg2)->f6 = D_801D9500;
    return 0;
}


// @class: regalloc-order/schedule  @status: MATCH (137 ins, real-TU rtu_match byte-identical)
// Cracked from the wave-2 91-off draft. Winning levers (each byte-gated, ~137→0):
//  1. RECONCILE: the TU has TWO conflicting block-scope externs for this fn (s32(s16,s16,s16,s32)
//     @func_80133784 and int(int,s16,s16,int)@func_801343C4); a DEFINITION hard-errors against the
//     mismatched one. Match the first (s16 arg0) + //@EDIT the second to it (byte-neutral for
//     func_801343C4: sangle is already s16-valued in-reg; verified words-identical). arg3 s32→(Map*).
//  2. LOOP FORM (46→20→10): the target is a for-style jump-to-bottom-test with the decrement in the
//     test's delay slot. A plain `while((u16)cnt!=0){cnt--;...}` gets rotated+exit-test-DUPLICATED
//     into a guarded do-while (§ jump.c:duplicate_loop_exit_test). Sibling idiom kills the guard:
//     `while(((cnt-- + zr) & 0xffff) != 0)` — the post-decrement side-effect + `+zr` ($0) forces the
//     `addu v0,s1,$0; andi; ...; addiu s1,-1(delay)` shape and blocks the guard duplication.
//  3. cp REGISTER (10→6): write `&cells[k]` as `k*2 + (u32)cells` (index first, base added LAST) so the
//     running accumulator stays in $v0 (target: `addu v0,v0,v1`), not the cells reg $v1.
//  4. NO pin on pA (6→1): the wave-2 `register u16 *pA __asm__("$7")` pin was UNNEEDED (gcc allocs pA
//     to $a3 naturally) AND poisoned the tail — the dead $7 anti-dep let sched2 hoist `move a3,p0C`
//     out of the jal delay slot. Dropping the pin fixed the whole call-arg schedule. (§42: pins backfire.)
//  5. harg→$4 pin (1→0): `register int harg __asm__("$4")` makes the flag OR in-place `or a0,a0,s7`
//     (harg first) instead of `or a0,s7,a0`; a0 is harg's natural uncontested home (clean pin, §42).
//  hib→a0 copy comes from `harg = hib + zr` (sibling idiom); Xc/Yc live-range splits via the $0-add asm.
#include "common.h"


s32 func_80133AB0(s16 flag, s16 x, s16 y, s32 arg3)
{
    extern u8 D_801870B0;
    extern u8 D_801870AC;
    extern u8 D_801870B8;
    extern u16 D_801D9500;
    extern s16 D_801D94FC;
    extern s32 func_80133CD4();

    Map_80133AB0 *map = (Map_80133AB0 *)arg3;
    u16 *pA = (*(u16 * *)&D_801870B0);
    u16 *pB = (*(u16 * *)&D_801870AC);
    u16 *pC = (*(u16 * *)&D_801870B8);
    register int zr __asm__("$0");
    u32 X, Y, cell, Xc, Yc;
    u16 k, off;
    int cnt;
    u16 *cp, *lst;
    u8 *s0;
    u16 raw;
    u32 hib;
    register int harg __asm__("$4");
    s32 ret;
    void *p0C, *p10;
    u8 *p14, *p18, *p1C;
    u16 *cells;

    pC[0] = pA[0] - pB[0];
    pC[1] = pA[1] - pB[1];
    pC[2] = pA[2] - pB[2];

    X = ((((u16)x + 0x8000) >> 7) & 0x1ff) - map->ox;
    __asm__("addu %0,%1,$zero" : "=r"(Xc) : "r"(X));
    if (!((X & 0xffff) < map->w))
        return 0;
    Y = ((((u16)y + 0x8000) >> 7) & 0x1ff) - map->oy;
    __asm__("addu %0,%1,$zero" : "=r"(Yc) : "r"(Y));
    if (!((Y & 0xffff) < map->h))
        return 0;

    cell = (Yc & 0xffff) * map->w + (Xc & 0xffff);
    cells = map->cells;
    p14 = map->p14;
    p0C = map->p0C;
    p10 = map->p10;
    p18 = map->p18;
    p1C = map->p1C;
    k = cell * 2;
    cp = (u16 *)(k * 2 + (u32)cells);
    off = cp[0];
    cnt = cp[1];
    lst = (u16 *)(p14 + off);

    while (((cnt-- + zr) & 0xffff) != 0) {
        raw = *lst;
        hib = raw & 0x8000;
        harg = hib + zr;
        if (hib == 0) {
            s0 = p18 + raw * 18;
        } else {
            s0 = p1C + (raw & 0x7fff) * 22;
        }
        ret = (s16)func_80133CD4((s16)(harg | flag), s0, p10, p0C);
        if (ret != 0) {
            if (ret > 0)
                D_801D9500 = *(u16 *)s0;
            return 1;
        }
        lst++;
        if (D_801D94FC != 0) {
            D_801D9500 = *(u16 *)s0;
            return 0;
        }
    }
    return 0;
}

/* func_80133CD4 (ov_SC01_077_a, 399 ins) — camera-collision solver. MATCH (byte-identical),
 * match_one + rtu_match both green, 2026-07-11 (Fable5 crack, gdb-on-cc1 §34 method).
 *
 * PIN-FREE (x134-safe): no register-asm pins; the only asm are the two blessed GTE blocks
 * plus ONE generic-constraint in-out lh (real opcode, no hard-reg names). Zero file-scope
 * footprint (all externs/typedefs in-body). No //@EDIT needed (caller extern is no-proto).
 *
 * THE CRACK (in order of byte-weight):
 * 1. MERGED ACCUMULATOR VARIABLES (378->147): the target reuses $s0 for {call3-result,
 *    denom, s0-loop-accum} and $s1 for {call2-result, -ret, s1-loop-accum}. global-alloc
 *    NEVER coalesces (K8), so one reg across disjoint regions = ONE source variable.
 *    Merging {s0v,denom,s0a}->s0var and {s1v,neg2,s1a}->s1var makes both allocnos
 *    call-crossing (K4, global.c:917) + top-density (K2, global.c:594 allocno_compare)
 *    -> they allocate FIRST -> plain first-fit (K3) reproduces the ENTIRE 9-callee
 *    permutation incl. arg0->s7/fp (the K&R s16 double-copy, kept from the seed).
 * 2. BLOCK-SCOPED POINTER SPLITS (147->141, cookbook 44-3): pc0's three regions live in
 *    $a0/$a2/$v0 in the target = three source pointers (pw / pc0 / loop-local pl); same
 *    for pb0 (division-region pb0 / loop-local pb).
 * 3. THE 1-DEATH SHARED READ TEMP (67->13, THE gdb-oracle find): the accumulator-init
 *    reads pb0[0]/pb0[1] through ONE temp h serialized by an anti-dep (the byte-visible
 *    nop + lh/lh into the same reg). A plain 2-set h has TWO REG_DEADs -> fails
 *    local-alloc.c:472's reg_n_deaths==1 gate -> GLOBAL -> loses $v0 to the upd2-chain
 *    local qty and the whole caller-saved block permutes (q1/q2/q3, pb0, chain, lw-t).
 *    gdb-patching reg_n_deaths[h]=1 at local_alloc proved the single flip yields the
 *    exact target allocation. No pure-C spelling gives 2 sets + 1 death (flow.c REG_DEAD
 *    is per-region; combine's 2-insn merges undo cleanly, the split path needs i1,
 *    combine.c:1737). The in-out asm makes read2 USE+SET h in one insn ->
 *    dead_or_set_p suppresses region-1's death note (flow.c:2511) -> 1 death -> LOCAL
 *    -> wins $v0 (pri-10000 tie, earlier qty birth) -> chain->$v1, pb0->$a0,
 *    q1/q2->$v1, q3->$a1 all fall out by first-fit.
 * 4. upd2 MOVED BELOW THE READS via named q3v + "memory" clobber on the in-out asm
 *    (13->{chain-lhu fills read2's delay slot, not read1's}).
 * 5. TAIL: branch-polarity off the opcode (32-2), per-element serialized store groups
 *    with /s struct-member stores (H16) + single w local for the s3u[1] pair + early bp
 *    pointer + goto-shared-ret1 (own-BB return-1 stops the li hoisting cross-BB and
 *    frees $v0 for the last lhu temp; dbr still steals the li into the bnez slot).
 * 6. THE OFFSET-0 /s STORE ASYMMETRY (5->0): p[0]=x expands NON-/s (mem (reg)) while
 *    p[1]/p[2] are mem/s -> the reload-born $t0 operand load (insn 763) keeps a true-dep
 *    on S0 ONLY (sched.c:820 drop needs /s+varying vs non-/s+fixed) and parks in the
 *    SECOND lh delay gap. ((struct { s32 w; } *)pw)->w = s3[0]; forces /s at offset 0
 *    -> dep dropped -> the pair floats to the FIRST gap = target.
 */
#include "common.h"

s32 func_80133CD4(arg0, cmd, base, arr)
    s16 arg0;
    s16 *cmd;
    s16 *base;
    s32 *arr;
{

    extern u16 *D_801870B0;
    extern u16 *D_801870AC;
    extern s16 *D_801870B8;
    extern s16 *D_801870B4;
    extern s32 *D_801870C0;
    extern s32 *D_801870C4;
    extern u16 D_801D9500;
    extern u8  D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern u16 D_801152AE;
    extern u8  D_801152B0;
    extern s32 func_80134310();
    extern s32 func_8013435C();

    s16 *s3 = ((ElemK *)base)[cmd[1]].e;
    s32 s6 = arr[cmd[2]];
    s32 s0var, s1var;
    s32 s2a;
    s16 y;

    if (func_80134310(s3, D_801870B0, s6) >= 0)
        return 0;

    s1var = func_80134310(s3, D_801870AC, s6);
    if (s1var < 0)
        return 0;

    s0var = func_80134310(s3, D_801870B8, 0);
    {
        u16 *pac = D_801870AC;
        s16 *pb8 = D_801870B8;
        s16 *pb4 = D_801870B4;
        s32 neg = -s1var;
        pb4[0] = pac[0] + neg * pb8[0] / s0var;
        pb4[1] = pac[1] + neg * pb8[1] / s0var;
        pb4[2] = pac[2] + neg * pb8[2] / s0var;
        if (func_8013435C(((ElemK *)base)[cmd[3]].e, pb4, arr[cmd[4]], s3))
            return 0;
    }
    if (func_8013435C(((ElemK *)base)[cmd[5]].e, D_801870B4, arr[cmd[6]], s3))
        return 0;
    if (func_8013435C(((ElemK *)base)[cmd[7]].e, D_801870B4, arr[cmd[8]], s3))
        return 0;
    if (arg0 < 0) {
        if (func_8013435C(((ElemK *)base)[cmd[9]].e, D_801870B4, arr[cmd[10]], s3))
            return 0;
    }
    if (arg0 & 0x10) {
        if (*(u16 *)cmd & 0x100)
            return 0;
    }
    if (*(u16 *)cmd & 0x200) {
        D_801D9500 = *(u16 *)cmd;
        return 0;
    }

    {
        s32 ret = func_80134310(s3, D_801870B0, s6);
        s32 *pc0;
        s32 *pc4;
        u16 *pb0;
        s32 t, o2;
        s32 q3v;

        {
            s32 *pw = D_801870C0;
            ((struct { s32 w; } *)pw)->w = s3[0];
            pw[1] = s3[1];
            pw[2] = s3[2];
        }
        s1var = -ret;

        __asm__ __volatile__(
            "lwc2 $9, 0(%0)\n"
            "lwc2 $10, 4(%0)\n"
            "lwc2 $11, 8(%0)\n"
            "nop\n"
            "nop\n"
            "sqr 0\n"
            : : "r"(D_801870C0) : "$9", "$10", "$11", "memory");
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n"
            "swc2 $26, 4(%0)\n"
            "swc2 $27, 8(%0)\n"
            : : "r"(D_801870C4) : "memory");

        pc0 = D_801870C0;
        pc4 = D_801870C4;
        s0var = pc4[0] + pc4[1] + pc4[2];
        pb0 = D_801870B0;
        pb0[0] += s1var * pc0[0] / s0var;
        pb0[1] += s1var * pc0[1] / s0var;
        q3v = s1var * pc0[2] / s0var;

        {
            s32 h;
            h = ((s16 *)pb0)[0];
            s1var = h << 16;
            __asm__("lh %0, 2(%2)" : "=r"(h) : "0"(h), "r"(pb0) : "memory");
            s0var = h << 16;
        }
        pb0[2] += q3v;
        s2a = (s16)pb0[2] << 16;

        t = pc0[0] << 4;
        pc0[0] = t;
        if (t < 0) s1var |= 0xFFFF;
        t = pc0[1] << 4;
        pc0[1] = t;
        if (t < 0) s0var |= 0xFFFF;
        o2 = pc0[2];
        t = o2 << 4;
        pc0[2] = t;
        if (t < 0) s2a |= 0xFFFF;
        s2a += o2 << 5;
        s1var += pc0[0] << 1;
        s0var += pc0[1] << 1;

        do {
            s32 *pl = D_801870C0;
            u16 *pb;
            s1var += pl[0];
            s0var += pl[1];
            s2a += pl[2];
            pb = D_801870B0;
            pb[0] = s1var >> 16;
            pb[1] = s0var >> 16;
            pb[2] = s2a >> 16;
            ret = func_80134310(s3, pb, s6);
        } while (ret < ((s3[1] < -0xE00) ? 0x1800 : 0x2F00));
    }

    y = s3[1];
    if (y >= -0xBCB) {
        D_801870AC[3] = y;
        {
            typedef struct { s8 c[8]; } Blk8;
            *(Blk8 *)&D_801152B0 = *(Blk8 *)s3;
        }
        if (*(u8 *)cmd != 0)
            goto ret1;
        return -1;
    }
    {
        u16 *s3u = (u16 *)s3;
        u16 *bp = D_801870B0;
        u16 w;
        ((H16 *)D_801152A8)->h = s3u[0];
        w = s3u[1];
        bp[3] = w;
        ((H16 *)&D_801152AA)->h = w;
        ((H16 *)&D_801152AC)->h = s3u[2];
        ((H16 *)&D_801152AE)->h = s3u[3];
    }
ret1:
    return 1;
}



DEFINE_func_80134310()  /* dedup: shared engine-core @0x80134310 (src/shared) */

DEFINE_func_8013435C()  /* dedup: shared engine-core @0x8013435C (src/shared) */

// @class: schedule
// @stuck: none — MATCH (83 ins, relocation-masked)



s32 func_801343C4(s32 angle, s32 p1, s32 p2)
{
    extern s32 func_80133AB0(s16, s16, s16, s32);
    extern s16 * D_801870AC;
    extern s16 * D_801870B0;
    extern u16 D_801D9500;
    extern u16 D_801D94FC;

    s16 *pac;
    s16 *pb0;
    s16 *pacs, *pb0s;
    u16 *pb0u;
    int a1v, a2v, d94, b0;
    int sangle = ((s16)angle);

    pac = D_801870AC;
    d94 = D_801D94F0;
    pb0 = D_801870B0;
    pac[0] = ((u16 *)p1)[0];
    pac[1] = ((u16 *)p1)[1];
    pac[2] = ((u16 *)p1)[2];
    pb0[0] = ((u16 *)p2)[0];
    pb0[1] = ((u16 *)p2)[1];
    pb0[2] = ((u16 *)p2)[2];

    a1v = pac[0]; a2v = pac[2];
    __asm__ __volatile__("" ::: "memory");
    D_801D9500 = 0;
    D_801D94FC = 0;
    if (func_80133AB0(sangle, a1v, a2v, d94)) {
    setdst:
        pb0u = (u16 *)D_801870B0;
        ((u16 *)p2)[0] = pb0u[0];
        ((u16 *)p2)[1] = pb0u[1];
        ((u16 *)p2)[2] = pb0u[2];
        ((u16 *)p2)[3] = D_801D9500;
        return 1;
    }

    pacs = D_801870AC;
    pb0s = D_801870B0;
    b0 = pb0s[0];
    if ((pacs[0] & 0xFF80) == (b0 & 0xFF80) &&
        (pacs[2] & 0xFF80) == (pb0s[2] & 0xFF80)) {
        return 0;
    }
    if (func_80133AB0(sangle, b0, pb0s[2], D_801D94F0)) {
        goto setdst;
    }
    return 0;
}


// @class: schedule


s32 func_80134510(s32 param) {
    extern s32 func_801345F8(s32);
    extern Foo_80134510 * D_801870AC;
    extern Foo_80134510 * D_801870B0;
    extern Foo_80134510 * D_801870B4;
    extern s32 D_801D94F0;
    extern u16 D_801D9500;

    s32 ret = 0;
    Foo_80134510 *b0 = D_801870B0;
    Foo_80134510 *ac = D_801870AC;
    u16 t0 = ((Foo_80134510 *)param)->f0;
    u16 t2, t4;

    ((Foo_80134510 *)param)->f6 = 0;
    ac->f0 = t0;
    b0->f0 = t0;
    t2 = ((Foo_80134510 *)param)->f2;
    ac->f2 = t2 - 4;
    b0->f2 = t2 + 0x2FC;
    t4 = ((Foo_80134510 *)param)->f4;
    ac->f4 = t4;
    b0->f4 = t4;

    if (func_801345F8(D_801D94F0) != 0) {
        s16 x;
        ((Foo_80134510 *)param)->f2 = D_801870B4->f2 - 2;
        x = D_801870AC->f6;
        if (x >= -3019) {
            if (x < -1400) {
                ret = 0x4000;
            } else {
                ret = 0x8000;
            }
        } else {
            ret = 0x2000;
        }
        D_801870AC->f6 = D_801D9500;
    }
    return ret;
}

// @class: regalloc-order
// @stuck: 26-mismatch near-miss (structure fully matches: while-loop test-first via j-to-bottom-test, s0=puVar7/s1=cnt/s2=scan/s3=iVar8/s4=iVar9/s5=uVar3/s6=uVar10, a1=param/a0=cc/a3=0x8000 pinned, both range-persist copies present, mult+GPU-index+call all byte-correct). Residual = 4 instances of ONE gcc-2.7.2 regalloc/copy-prop tie-break: target computes a preserved-then-masked value in $v0 and reads $v0 for the mask (`subu $v0; addu $persist,$v0; andi $v0,$v0`), gcc here reads the persist reg (`andi $v0,$t0`). (1) range-check-1 andi reads $t0 not $v0; (2) range-check-2 andi reads $a0 not $v0; (3) `hi=uVar1&0x8000` folds into $a0 — target computes in $v0 + copies to $a0 in the branch-delay (same-block copy, gcc coalesces mine); (4) loop-test `cnt&0xffff` folds to direct `andi $v0,$s1` — target copies `addu $v0,$s1` first. Splitting the value into compare-temp + persist-var produces the copy but gcc forward-propagates the copy DEST into the mask; persist-after-compare kills the copy; explicit `register __asm__` pins fold the whole expr chain into the pinned reg; `=r/0` barriers force bad materialization. Also minor: while-loop header-copy adds a `beqz s1` entry guard vs target `j`, and a2/a3 call-arg setup order. Permuter can't run (register __asm__ pins rejected by pycparser). Genuinely compiler-internal — hand-finish or accept as ceiling.


s32 func_801345F8(s32 arg)
{
    extern int func_801347A0(short, u16 *, int, int);
    extern u16 * D_801870AC;
    extern u16 D_801D9500;

    register u16 *param_1 __asm__("$5") = ((u16 *)arg);
    register u16 *cc __asm__("$4") = D_801870AC;
    int c8000 = 0x8000;
    register int zr __asm__("$0");
    u32 c1, c2, uVar6, uVar2, cnt, v14;
    u16 *ptmp, *puVar4, *puVar7, uVar1;
    int hi, harg, iVar9, iVar8, uVar3, uVar10, tbl;

    c1 = ((int)(cc[0] + c8000) >> 7 & 0x1ff) - (u32)param_1[0];
    uVar6 = c1 + zr;
    if ((c1 & 0xffff) < (u32)param_1[2]) {
        c2 = ((int)(cc[2] + c8000) >> 7 & 0x1ff) - (u32)param_1[1];
        uVar2 = c2 + zr;
        if ((c2 & 0xffff) < (u32)param_1[3])
            goto do_mult;
        return 0;
      found:
        D_801D9500 = *puVar7;
        return 1;
      do_mult:
        tbl = *(int *)(param_1 + 4);
        uVar10 = *(int *)(param_1 + 6);
        uVar3 = *(int *)(param_1 + 8);
        iVar9 = *(int *)(param_1 + 0xc);
        iVar8 = *(int *)(param_1 + 0xe);
        ptmp = (u16 *)((((u32)(u16)uVar2 * (u32)param_1[2] + (u32)(u16)uVar6) * 2 & 0xffff) * 2 + tbl);
        cnt = (u32)ptmp[1];
        v14 = *(int *)(param_1 + 10);
        puVar4 = (u16 *)(v14 + (u32)*ptmp + cnt * 2) - 1;
        while (((cnt-- + zr) & 0xffff) != 0) {
            uVar1 = *puVar4;
            hi = uVar1 & 0x8000;
            harg = hi + zr;
            if (hi == 0)
                puVar7 = (u16 *)(iVar9 + (u32)uVar1 * 0x12);
            else
                puVar7 = (u16 *)(iVar8 + (uVar1 & 0x7fff) * 0x16);
            if (func_801347A0((short)harg, puVar7, uVar3, uVar10) != 0)
                goto found;
            puVar4 = puVar4 - 1;
        }
    }
    return 0;
}


// @class: regalloc-order
// @stuck: none — MATCH (162 ins). iv pinned to $4 (a0) forces move+delay-slot negu; divisor-temp forces divisor-first schedule (load-delay nop). Globals declared pointer-typed (SVec*/s16*) so %lo folds per-use instead of &sym address-CSE into callee regs.
#include "common.h"






s32 func_801347A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_80134A28(s32 a0, s32 a1, s32 a2);
    extern s16 * D_801870B0;
    extern SVec * D_801870AC;
    extern SVec * D_801870B4;

    Elem *pElem;
    s32 val;
    register s32 iv __asm__("$4");
    s32 q;
    s32 dvsr;

    pElem = &((Elem *)arg2)[((S0 *)arg1)->f2];
    val = ((s32 *)arg3)[((S0 *)arg1)->f4];
    if (func_80134A28((s32)pElem, (s32)D_801870B0, val) >= 0) {
        return 0;
    }
    iv = func_80134A28((s32)pElem, (s32)D_801870AC, val);
    if (iv < 0) {
        return 0;
    }
    iv = -iv;
    dvsr = pElem->f2 * 48;
    q = (iv * 48) / dvsr;
    D_801870B4->f0 = D_801870AC->f0;
    D_801870B4->f2 = D_801870AC->f2 + q;
    D_801870B4->f4 = D_801870AC->f4;
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->f6], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->f8]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->fa], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->fc]) < -0x2F00) {
        return 0;
    }
    if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->fe], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->f10]) < -0x2F00) {
        return 0;
    }
    if ((s16)arg0) {
        if (func_80134A28((s32)&((Elem *)arg2)[((S0 *)arg1)->f12], (s32)D_801870B4, ((s32 *)arg3)[((S0 *)arg1)->f14]) < -0x2F00) {
            return 0;
        }
    }
    if ((((S0 *)arg1)->f0 & 0x300) != 0) {
        return 0;
    }
    D_801870B4->f0 = D_801870AC->f0;
    D_801870B4->f4 = D_801870AC->f4;
    (*(Elem*)D_801152A8) = *pElem;
    D_801870AC->f6 = pElem->f2;
    return 1;
}


DEFINE_func_80134A28()  /* dedup: shared engine-core @0x80134A28 (src/shared) */

int func_80134A74(int param_1, s16 param_2, s16 param_3, int param_4)
{
    extern u16 D_801D9500;
    extern s32 func_80134C20(s32, s32, s32, s32);

    u16 *param_4p = (u16 *)param_4;
    register u32 zr __asm__("$0");
    u32 uVar6, uVar2, uVar2c;
    register u32 uVar6c __asm__("$9");
    u16 *puVar4, *ptmp;
    register u32 n __asm__("$18");
    register u32 p0 __asm__("$4");
    register int v14 __asm__("$3");
    u16 *puVar7, uVar1;
    u32 hi, hic;
    int iVar5, iVar9, iVar8, uVar3, uVar10;

    uVar6 = ((int)((param_2 & 0xffff) + 0x8000) >> 7 & 0x1ff) - (u32)param_4p[0];
    uVar6c = uVar6 + zr;
    if ((uVar6 & 0xffff) < (u32)param_4p[2]) {
        uVar2 = ((int)((param_3 & 0xffff) + 0x8000) >> 7 & 0x1ff) - (u32)param_4p[1];
        __asm__("addu %0,%1,$zero" : "=r"(uVar2c) : "r"(uVar2));
        if ((uVar2 & 0xffff) < (u32)param_4p[3]) goto work;
        return 0;
    found:
        D_801D9500 = *puVar7;
        return 1;
    work:
        uVar10 = *(int *)(param_4p + 6);
        uVar3 = *(int *)(param_4p + 8);
        iVar9 = *(int *)(param_4p + 0xc);
        iVar8 = *(int *)(param_4p + 0xe);
        ptmp = (u16 *)((((uVar2c & 0xffff) * (u32)param_4p[2] + (uVar6c & 0xffff)) * 2 & 0xffff) * 2 + *(int *)(param_4p + 4));
        v14 = *(int *)(param_4p + 10);
        __asm__ __volatile__("" :: "r"(uVar6c));
        p0 = (u32)*ptmp;
        n = (u32)ptmp[1];
        puVar4 = (u16 *)(v14 + p0 + n * 2) - 1;
        goto test;
    body:
        uVar1 = *puVar4;
        hi = uVar1 & 0x8000;
        hic = hi + zr;
        if (hi == 0)
            puVar7 = (u16 *)(iVar9 + (u32)uVar1 * 0x12);
        else
            puVar7 = (u16 *)(iVar8 + (uVar1 & 0x7fff) * 0x16);
        puVar4 = puVar4 - 1;
        iVar5 = func_80134C20((short)(hic | param_1), (s32)puVar7, uVar3, uVar10);
        if (iVar5 != 0) goto found;
    test:
        {
            u32 m;
            __asm__("addu %0,%1,$zero" : "=r"(m) : "r"(n));
            n--;
            if ((m & 0xffff) != 0) goto body;
        }
    }
    return 0;
}

// @class: regalloc-order
// @try: variant B — direct pins m=$s5($21), c=$s6($22)


s32 func_80134C20(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    extern s32 func_80134FB8(s32 a0, s32 a1, s32 a2);
    extern void * D_801870AC;
    extern void * D_801870B0;
    extern void * D_801870B4;
    extern void * D_801870B8;
    extern u16 D_801D9500;

    s32 temp_a3;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;
    u16 temp_a1;
    s32 temp_s4;
    s32 c = arg0;
    __asm__ __volatile__("" : "=r"(c) : "0"(c));
    __asm__ __volatile__("" : : "r"(arg0));

    temp_s4 = arg2 + (M2C_FIELD(((void *)arg1), s16 *, 2) * 8);
    temp_s1 = *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 4) * 4));
    var_v0 = 0;
    if (func_80134FB8(temp_s4, (s32) D_801870B0, temp_s1) >= 0) {
        return var_v0;
    }
    temp_v0 = func_80134FB8(temp_s4, (s32) D_801870AC, temp_s1);
    if (temp_v0 < 0) {
        goto block_13;
    }
    temp_v0_2 = func_80134FB8(temp_s4, (s32) D_801870B8, 0);
    temp_a3 = -temp_v0;
    {
        u16 *pB4 = (u16 *)D_801870B4;
        u16 *pAC = (u16 *)D_801870AC;
        s16 *pB8 = (s16 *)D_801870B8;
        pB4[0] = pAC[0] + (temp_a3 * pB8[0]) / temp_v0_2;
        pB4[1] = pAC[1] + (temp_a3 * pB8[1]) / temp_v0_2;
        pB4[2] = pAC[2] + (temp_a3 * pB8[2]) / temp_v0_2;
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 6) * 8), (s32) pB4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 8) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xA) * 8), (s32) D_801870B4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0xC) * 4))) < -0x2F00) {
        return var_v0;
    }
    var_v0 = 0;
    if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0xE) * 8), (s32) D_801870B4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x10) * 4))) < -0x2F00) {
        return var_v0;
    }
    if ((arg0 << 16) < 0) {
        var_v0 = 0;
        if (func_80134FB8(arg2 + (M2C_FIELD(((void *)arg1), s16 *, 0x12) * 8), (s32) D_801870B4, *(s32 *)(arg3 + (M2C_FIELD(((void *)arg1), s16 *, 0x14) * 4))) < -0x2F00) {
            return var_v0;
        }
    }
    if (c & 1) {
        if (!(M2C_FIELD(((void *)arg1), u16 *, 0) & 0x300)) {
            goto block_14;
        }
        return 0;
    }
    temp_a1 = M2C_FIELD(((void *)arg1), u16 *, 0);
    if (!(temp_a1 & 0x200)) {
        goto block_14;
    }
    D_801D9500 = temp_a1;
block_13:
    return 0;
block_14:
    __builtin_memcpy(D_801152A8, (void *)temp_s4, 8);
    VectorNormalSS(D_801870B8, D_801870B8);
    {
        u16 *pB8 = (u16 *)D_801870B8;
        u16 *pB4b = (u16 *)D_801870B4;
        pB4b[0] = pB4b[0] - ((pB8[0] << 0x10) >> 0x1B);
        var_v0 = 1;
        pB4b[1] = pB4b[1] - ((pB8[1] << 0x10) >> 0x1B);
        pB4b[2] = pB4b[2] - ((pB8[2] << 0x10) >> 0x1B);
    }
    return var_v0;
}


DEFINE_func_80134FB8()  /* dedup: shared engine-core @0x80134FB8 (src/shared) */

// @class: plumbing
// @stuck: MATCH (89 ins). To BANK: retype D_801870B0 + D_801870AC (u8 -> s16*) in sibling func_80135168's externs (src/ov_SC01_077/ov_SC01_077_a.c ~L1879); they hold pointers double-referenced across a call, so only a 4-byte/pointer decl folds %lo (u8 &-cast CSE's the address into a saved reg). Retype is byte-NEUTRAL for the sibling (verified: identical objdump bytes u8 vs s16*).




s32 func_80135004(s32 arg0, s32 p1, s32 p2)
{
    extern int func_80134A74(int, s16, s16, int);
    extern s16 * D_801870B0;
    extern s16 * D_801870AC;
    extern u8 D_801870B8;
    extern s16 *D_801870B4;
    extern u16 D_801D9500;

    register s16 *pb0 __asm__("$9");   /* D_801870B0 -> $t1 */
    register s16 *pac __asm__("$6");   /* D_801870AC -> $a2 */
    register s16 *pb8 __asm__("$8");   /* D_801870B8 -> $t0 */
    u16 *pb4;
    u16 a, b;
    int id;
    int a1v, a2v, d94;

    pb0 = D_801870B0;
    __asm__ __volatile__("" : : "r"(pb0));

    a = ((u16 *)p2)[0]; pac = D_801870AC; pb0[0] = a; b = ((u16 *)p1)[0]; pb8 = (*(s16 * *)&D_801870B8); pac[0] = b; pb8[0] = a - b;
    a = ((u16 *)p2)[1]; pb0[1] = a; b = ((u16 *)p1)[1]; pac[1] = b; pb8[1] = a - b;
    a = ((u16 *)p2)[2]; pb0[2] = a; b = ((u16 *)p1)[2]; pac[2] = b; pb8[2] = a - b;

    id = ((int)arg0) & 0xFFFF;
    a1v = pac[0]; a2v = pac[2]; d94 = D_801D94F0;
    __asm__ __volatile__("" ::: "memory");
    D_801D9500 = 0;

    if (func_80134A74(id, a1v, a2v, d94)) {
    found:
        pb4 = (*(u16 * *)&D_801870B4);
        ((u16 *)p2)[0] = pb4[0];
        ((u16 *)p2)[1] = pb4[1];
        ((u16 *)p2)[2] = pb4[2];
        ((u16 *)p2)[3] = D_801D9500;
        return 1;
    }
    {
        register u16 *qb __asm__("$4");   /* D_801870AC -> $a0 (reloaded) */
        register int qa0 __asm__("$5");   /* D_801870B0[0], kept in $a1 for the 2nd-call arg */
        register u16 *qa __asm__("$6");   /* D_801870B0 -> $a2 (reloaded) */
        qb = (u16 *)D_801870AC;
        qa = (u16 *)D_801870B0;
        qa0 = qa[0];
        if (((qb[0] & 0xFF80) == (qa0 & 0xFF80)) &&
            ((qb[2] & 0xFF80) == (qa[2] & 0xFF80)))
            return 0;
        if (func_80134A74(id, (s16)qa0, (s16)qa[2], D_801D94F0))
            goto found;
        return 0;
    }
}


// @class: schedule
// @stuck: none — MATCH (62 ins, relocation-masked)


extern int D_801D94F0;
extern u16 D_801D9500;

extern int func_80134A74(int, s16, s16, int);

int func_80135168(u16 arg0, u16 *p1, u16 *p2)
{
    /* [T48] moved from FILE scope into the two consumers: a file-scope decl of these symbols
       forces every LATER function in this TU to agree with it, which blocks a byte-true
       pointer-typed decl in func_80135260. Declaration-only move; R22 is the arbiter. */
    extern u8 D_801870B0;
    extern u8 D_801870AC;
    extern s16 *D_801870B4;
    extern u8 D_801870B8;
    register s16 *pb0 __asm__("$8");
    register s16 *pac __asm__("$6");
    register s16 *pb8 __asm__("$7");
    u16 *pb4;
    u16 a, b;
    int a1v, a2v, d94;

    pb0 = (*(s16 * *)&D_801870B0);
    __asm__ __volatile__("" : : "r"(pb0));

    a = p2[0]; pac = (*(s16 * *)&D_801870AC); pb0[0] = a; b = p1[0]; pb8 = (*(s16 * *)&D_801870B8); pac[0] = b; pb8[0] = a - b;
    a = p2[1]; pb0[1] = a; b = p1[1]; pac[1] = b; pb8[1] = a - b;
    a = p2[2]; pb0[2] = a; b = p1[2]; pac[2] = b; pb8[2] = a - b;

    a1v = pac[0]; a2v = pac[2]; d94 = D_801D94F0;
    __asm__ __volatile__("" ::: "memory");
    D_801D9500 = 0;
    if (func_80134A74(arg0, a1v, a2v, d94)) {
        pb4 = (*(u16 * *)&D_801870B4);
        p2[0] = pb4[0];
        p2[1] = pb4[1];
        p2[2] = pb4[2];
        p2[3] = D_801D9500;
        return 1;
    }
    return 0;
}


/* func_80135260 — "is <target> reachable/hittable" gate (136 ins, ov_SC01_077 jr_8012ACE0).
 *
 * Sibling of the already-banked func_80135D20 (src/ov_SC03_099/ov_SC03_099_jr_80135D20.c L659+):
 * same func_80135480 switch (jtbl_801D8158, cases 0..4, default falls through with p/flag/q
 * UNINITIALISED — reproduced by leaving the switch without a default), same peeled-probe +
 * rotated list loop, different `elsepath`.
 *
 * Load-bearing details (all byte-proven by ablation against match_one):
 *  - func_80135480 is DEFINED later in this same TU (L3261) returning s16. Calling it through an
 *    `s32 (*)(...)` cast is REQUIRED: the target does NOT re-extend the callee result before the
 *    switch (`addu $v1,$v0,$zero` only); a plain s16-returning call costs an extra `sll/sra 16`.
 *    The cast is call-site-local, so func_80135480's own definition is untouched (no //@EDIT).
 *  - D_801870AC / D_801870B0 / D_801870B8 MUST be declared as 4-byte POINTERS
 *    (`extern u16 *D_801870Bx;`), not the canonical `extern u8` + `(*(u16**)&sym)` cast. With the
 *    u8 form gcc CSEs `&sym` into two callee-saved regs ($s1/$s5), which costs a 7th saved
 *    register ($s6 for arg3) and 3 extra instructions. This is exactly the retype already
 *    documented in this TU's @stuck note at L3127. The decls are BLOCK-SCOPE-compatible with the
 *    TU's other `extern u8 D_801870AC;` bodies (the TU already mixes both forms: L2461 vs L2587).
 *  - `u8 dead[56];` is a DEAD local that only sets the frame: without it the frame is 0x30, the
 *    target's is 0x68 (gcc-2.7.2 assign_stack_local runs at expand time, so an unreferenced
 *    aggregate still owns its slot). Body bytes are already exact at 136/136 without it — the 16
 *    residual diffs are purely the sp/save-slot immediates.
 *  - explicit goto layout (loop / hit / body / elsepath) reproduces the target's block ORDER: the
 *    `hit` block sits physically between the loop test and the loop body, and its leading
 *    `move a0,flag` gets copied into all four branch delay slots.
 *  - the two D_801870xx compare fields are read `lhu` -> u16; the func_80134A74 args are `(s16)`
 *    casts of those u16 lvalues (combine folds the fresh ones into `lh`, and sll/sra the one that
 *    is still live in $a1 from the 0xFF80 compare).
 *  - func_80135D20's §5a cross-jump barrier is NOT needed here (ablated: MATCH either way).
 */
extern s16 func_80135480(void*, s32, s16*, s16*);
extern s32 func_80135EB0(void *arg0, s32 arg1_);
extern s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3);
extern int func_80134A74(int, s16, s16, int);

s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3)
{
    /* BLOCK scope on purpose: this TU already declares D_801870AC/B0/B8 as `extern u8` inside
     * other function bodies (L2461-2463) and as `extern u16 *` inside others (L2587-2589).
     * A FILE-scope pointer decl here would make those inner `extern u8` decls conflicting-types.
     * The same reason keeps D_801D9504/D_801D9524 local (cf. the TU's own L3268-3270). */
    extern u16 *D_801870AC;
    extern u16 *D_801870B0;
    extern u16 *D_801870B8;
    extern s32 D_801D9504;
    extern s32 D_801D9524;

    u8 dead[56];
    s32 *p;
    s32 flag;
    s32 q;
    u16 *pa;
    u16 *pb;
    u16 *pc;
    u16 *pd;
    u16 *pe;
    u16 t;

    switch (((s32 (*)(void *, s32, s16 *, s16 *))func_80135480)((void *)arg0, arg1, arg2, arg3)) {
    case 0:
        return 0;
    case 1:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 0;
        break;
    case 2:
        q = arg0 + 0x34;
        p = (s32 *)((arg1 & 0xFFFFFFF) | 0x80000000);
        flag = 1;
        break;
    case 3:
        q = arg0 + 0x34;
        p = &D_801D9524;
        flag = 0;
        break;
    case 4:
        q = (s32)&D_801D9504;
        p = &D_801D9524;
        flag = 1;
        break;
    }
    if (arg1 >= 0) {
        goto elsepath;
    }
    if (func_80135EB0(p, 0) != 0) {
        goto hit;
    }
    p = (s32 *)*p;
    if (p == 0) {
        return 0;
    }
loop:
    if (func_80135EB0(p, 0) == 0) {
        goto body;
    }
hit:
    func_80136A94(flag, arg0, (s32)arg3, q);
    return 1;
body:
    p = (s32 *)*p;
    if (p != 0) {
        goto loop;
    }
    return 0;
elsepath:
    pa = D_801870B0;
    pb = D_801870AC;
    pc = D_801870B8;
    pc[0] = pa[0] - pb[0];
    pc[1] = pa[1] - pb[1];
    pc[2] = pa[2] - pb[2];
    if (func_80134A74(0, (s16)pb[0], (s16)pb[2], (int)p) != 0) {
        goto hit;
    }
    pd = D_801870AC;
    pe = D_801870B0;
    t = pe[0];
    if (((pd[0] & 0xFF80) == (t & 0xFF80)) && ((pd[2] & 0xFF80) == (pe[2] & 0xFF80))) {
        return 0;
    }
    if (func_80134A74(0, (s16)t, (s16)pe[2], (int)p) != 0) {
        goto hit;
    }
    return 0;
}


/* func_80135480 — cull + coordinate-transform emitter (258 ins, ov_SC01_077 split _a, ×134 family).
 *
 * NOT a §43 s16-param giant. Params are (void*, s32, s16*, s16*); the sole `sll/sra 16` is the s16
 * RETURN narrowing on $s3 (result), not an in-place arg-reg narrow. So §43's K&R-s16-param map does
 * not apply here — no //@EDIT, no ec_edit. func_80135480 has NO ambient prototype/caller anywhere in
 * src/include, so the s16 return type is free (no void->s32 flip, no engine_core.h edit).
 *
 * THE CRACK (residual class = §31 regalloc/schedule, RC-4/RC-2 in gcc-2.7.2-map/regalloc.md):
 * the two output buffers D_801870AC / D_801870B0 are written through a pointer in each of the two
 * return tails (mode!=0 and mode==0). A single function-scope `s16 *tmp` reused across both tails is a
 * GLOBAL allocno (used in 2 blocks, dies 4x) -> forced onto one hard reg ($a1), which is WRONG and also
 * perturbs the switch's first-`beq` delay-slot fill (extra nop). The target instead allocates each
 * store-group's pointer as a LOCAL-ALLOC pseudo (set once, used 3x, dies once, single block) that picks
 * the lowest-free scratch over its OWN window:
 *     mode!=0 tail:  p_AC -> $v1,  p_B0 -> $v1 (reused, $v0 = the load temp)
 *     mode==0 tail:  p_AC -> $v1,  p_B0 -> $a0 (the sub-scratch occupies $v1, so $v1 is unavailable)
 * Reproduced by giving each of the four store-groups its OWN block-scoped pointer. With the tail
 * allocation correct, the whole schedule (incl. the beq delay slot) re-derives to byte-identical.
 * No register pins (§17 caveat: don't pin $v1 — the target reuses it for the cull; a pin cascades
 * per RC-5). NOTE: the block-scope `s16 *p` intentionally shadows the function-scope `s32 p` (the
 * case-0x20000000 pointer base); scopes never overlap — legal and byte-verified.
 *
 * Zero file-scope footprint (block-scoped typedefs + externs; D_801870AC/B0 read via the ambient
 * `extern u8` + `*(s16**)&` §30 anon-cast, matching neighbor func_80135168) -> ×134-clean for
 * family_sweep --edit-remap with no cc1 crash.
 *
 * VERIFIED: tools/rtu_match.py func_80135480 --split ov_SC01_077_a  ->  MATCH (258 ins), 3x stable.
 */
s16 func_80135480(void *param_1, s32 param_2, s16 *param_3, s16 *param_4)
{
    /* [T48] moved from FILE scope into the two consumers: a file-scope decl of these symbols
       forces every LATER function in this TU to agree with it, which blocks a byte-true
       pointer-typed decl in func_80135260. Declaration-only move; R22 is the arbiter. */
    extern u8 D_801870B0;
    extern u8 D_801870AC;
    extern s16 *D_801870B4;
    extern u8 D_801870B8;
        extern void func_80048EAC(void *m0, void *m1);
    extern void func_8004914C(void *m);
    extern void ApplyTransposeMatrixLV(void *m, void *in, void *out);
    extern void ApplyRotMatrixLV(void *in, void *out);
    extern void ApplyRotMatrix(void *in, void *out);
    extern s32 D_801D9504, D_801D9508, D_801D950C, D_801D9510;
    extern s16 D_801D9514;
    extern s32 D_801D9524;
    extern s16 D_801D9528, D_801D952A, D_801D952C, D_801D952E, D_801D9530, D_801D9532;

    Vec32 in0, in1, rotout;
    Mat32 mat2;
    Vec16 vecin;
    s32 result;
    s32 mode;
    s32 q1, q2;
    s32 p;
    s32 t18, t1A, t1C;
    s32 *m;

    in0.vx = param_3[0] - *(s32 *)((s32)param_1 + 0x48);
    in0.vz = param_3[2] - *(s32 *)((s32)param_1 + 0x50);
    if ((param_2 & 0x10000000) == 0) {
        if (in0.vx * in0.vx + in0.vz * in0.vz > 0x40000) {
            return 0;
        }
    }
    mode = param_2 & 0x60000000;
    if (mode != 0) {
        result = 1;
        if (param_2 >= 0) {
            mode &= 0x40000000;
        }
        in0.vy = param_3[1] - *(s32 *)((s32)param_1 + 0x4C);
        in1.vx = param_4[0] - *(s32 *)((s32)param_1 + 0x48);
        in1.vy = param_4[1] - *(s32 *)((s32)param_1 + 0x4C);
        in1.vz = param_4[2] - *(s32 *)((s32)param_1 + 0x50);
        switch (mode) {
        case 0x60000000:
            m = &D_801D9504;
            *m = 0x1000000 / *(s16 *)((s32)param_1 + 0x18);
            q1 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1A);
            q2 = 0x1000000 / *(s16 *)((s32)param_1 + 0x1C);
            D_801D9508 = 0;
            D_801D9510 = 0;
            D_801D950C = q1;
            D_801D9514 = q2;
            func_80048EAC((void *)((s32)param_1 + 0x34), m);
            ApplyTransposeMatrixLV(m, &in0, &in0);
            ApplyRotMatrixLV(&in1, &in1);
            result = 2;
            /* fallthrough */
        case 0x20000000:
            p = (param_2 & 0xFFFFFFF) | 0x80000000;
            t18 = *(s16 *)((s32)param_1 + 0x18);
            t1A = *(s16 *)((s32)param_1 + 0x1A);
            t1C = *(u16 *)((s32)param_1 + 0x1C);
            mat2.w4 = 0;
            mat2.wC = 0;
            mat2.w0 = t18;
            mat2.w8 = t1A;
            mat2.h10 = t1C;
            func_8004914C(&mat2);
            vecin.vx = *(u16 *)(p + 4);
            vecin.vy = *(u16 *)(p + 8);
            vecin.vz = *(u16 *)(p + 0xC);
            ApplyRotMatrix(&vecin, &rotout);
            D_801D9528 = rotout.vx;
            D_801D952C = rotout.vy;
            D_801D9530 = rotout.vz;
            vecin.vx = *(u16 *)(p + 6);
            vecin.vy = *(u16 *)(p + 0xA);
            vecin.vz = *(u16 *)(p + 0xE);
            ApplyRotMatrix(&vecin, &rotout);
            D_801D9524 = 0;
            D_801D952A = rotout.vx;
            D_801D952E = rotout.vy;
            D_801D9532 = rotout.vz;
            result += 2;
            break;
        case 0x40000000:
            ApplyTransposeMatrixLV((void *)((s32)param_1 + 0x34), &in0, &in0);
            ApplyRotMatrixLV(&in1, &in1);
            result = 2;
            break;
        }
        {
            s16 *p = *(s16 **)&D_801870AC;
            p[0] = in0.vx;
            p[1] = in0.vy;
            p[2] = in0.vz;
        }
        {
            s16 *p = *(s16 **)&D_801870B0;
            p[0] = in1.vx;
            p[1] = in1.vy;
            p[2] = in1.vz;
        }
        return result;
    }
    {
        s16 *p = *(s16 **)&D_801870AC;
        p[0] = in0.vx;
        p[1] = ((u16 *)param_3)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = in0.vz;
    }
    {
        s16 *p = *(s16 **)&D_801870B0;
        p[0] = ((u16 *)param_4)[0] - *(s32 *)((s32)param_1 + 0x48);
        p[1] = ((u16 *)param_4)[1] - *(s32 *)((s32)param_1 + 0x4C);
        p[2] = ((u16 *)param_4)[2] - *(s32 *)((s32)param_1 + 0x50);
    }
    return 1;
}
