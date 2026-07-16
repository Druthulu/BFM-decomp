#include "common.h"
// func_8014D820 -- "attach/track to parent entity" mover (304 ins, ov_SC01_077_after).
// param_1 = self entity (s32 base), param_2/param_3 = u16[] pos snapshots (prev/cur).
// Delta -> validate tracked parent (e=*(param_1+0x170)) -> ratan2/func_80012A60 heading
// gate (<0x400) -> either the 0x3008 special case (func_800139C8 fan-of-3 + func_8014DCE0
// collide loop) or the generic func_80135888 loop -> func_80133784 -> write back the pose.
// Returns s32 (1 = applied, 0 = detach: *(param_1+0x170)=0).
//
// §43 return-type-flip pair: the target materializes v0=1 / v0=0 at the two exits, so the
// def MUST be s32. engine_core.h declares it void (via DEFINE_func_8014D790, invoked at
// split line 1572 -> in scope), so cc1 hard-errors "conflicting types" unless flipped.
// Byte-neutral: the sole caller (func_8014D790, engine_core.h:9765) discards the result.
// There is NO split-scope self-decl to //@EDIT (func_8014D820 is INCLUDE_ASM'd; the ov077
// canon-sig layer lists only its callees). So the ONLY pre-edit is the engine_core.h flip:
//
//   EC_EDIT (src/shared/engine_core.h line 9752, in the DEFINE_func_8014D790 body):
//     old:  extern void func_8014D820(s32 a0, void *a1, void *a2);
//     new:  extern s32  func_8014D820(s32 a0, void *a1, void *a2);
//
// PINS? NO. Fully block-scoped (typedefs + externs in-body), void*/s32 params (no
// s16-by-value -> no K&R param form, no param //@EDIT) -> ×134-clean via family_sweep
// --edit-remap (contrast the old pinned seed, which cc1-SIGABRTs in sibling TUs).
//
// STATUS: STRUCTURALLY COMPLETE, NOT byte-identical. rtu_match: 304/304 ins, all calls/
// constants/control-flow/two-pointer loops/unaligned Blk8 copy/apply+detach branches
// byte-correct; LCS 237/304 (close=67), pin-free -> beats the prior pinned seed (LCS 228).
// Residual = gcc-2.7.2 INTRINSIC sched1/regalloc knife-edge (§31 RC-6 / S3): prologue
// deferred param_1->$s4 copy + serialized-vs-parallel dx/dz load temps; sched1 store/load
// ORDER in the e3/e5/e7 setup, the func_800139C8 out0/1/2 combine, and the apply block;
// dead-dx/dz $s0/$s1 reuse for the ratan2#2 operands. 4 structural probes (reused-t temp,
// d2 hoist, alias-removal, out2 store-swap) each cascaded 20+ ins (the RC-6 tell) -> NOT
// hand-steerable. Route: permuter (this pin-free seed is permuter-viable) / Fable5.
//
// OPUS INVESTIGATION (2026-07-11, cheap-Opus giant-cracker, Lever A/B pass): CONFIRMED RC-6.
// This IS the best pin-free seed (match_one 261 positional / masked-LCS 226/304; every probe <=226).
// Uses the EXACT target hard-reg set ($v0,$v1,$a0-$a3,$t0,$s0-$s5,$ra) + all 304 correct opcodes ->
// pure schedule/alloc-ORDER permutation (§31 RC-6 tell: "regs+opcodes exact, placement off, edits explode").
//   * PROLOGUE ROOT CAUSE (new): the deferred param_1->$s4 copy is PINNED early by sched.c:3199
//     ("don't delay getting parameters" -> INSN_REF_COUNT=1 on the leading (set pseudo hardreg) run).
//     The target UN-pins it because it SERIALIZES the dx/dz loads (2-at-a-time thru $v0/$v1), opening
//     a load-delay slot the copy fills (t12). The serialize-vs-parallel choice is sched1's list-sched
//     tie-break (rank_for_schedule sched.c:2385/2414) -> NO clean C-lever. Probes: s32 `self=param_1`
//     copy FOLDS (cse) back into the pin (neutral); `u8* self=(u8*)param_1` cast still lands early.
//   * LEVER A PARTIALLY VALID but pressure-blocked: merging dz->d1 / dx->dzz is right in spirit
//     (v2 d2-hoist DID land d1->$s1, t60 exact), but a long-lived dzz allocno then EVICTS e->$s2 and
//     param_1->$s4 to $s3/$s5 (K4/K2 cascade). The target keeps dzz SHORT-lived by computing it in
//     ratan2#1's DELAY SLOT (t62) -> not C-expressible w/o disturbing the 6-callee-saved balance.
//     Source-reorder merge (v1) cascades 226->199. K8: global.c has no coalescing, so the $s0/$s1
//     reuse must come from sched1 placement, not a C variable.  Full evidence: func_8014D820.opus.md.
s32 func_8014D820(s32 param_1, void *param_2, void *param_3)
{
    typedef struct { u16 x, y, z, w; } V8;
    typedef struct { u8 b[8]; } Blk8;   /* align-1 -> unaligned lwl/lwr/swl/swr block copy */
    typedef struct {
        V8 out0; V8 out1; V8 out2; V8 pvec; V8 dvec;
        u8 gap[0x10];
        s32 z0; s32 z1; s32 z2;
    } Ctx;
    extern s16 currentLocationId;
    extern u8 D_801202A0[];
    extern u8 D_8018876C[];
    extern u16 D_801152A8, D_801152AC;
    extern s32 ratan2(s32 a0, s32 a1);
    extern s32 func_80012A60(s32 a0, s32 a1);
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_800139C8(s32 a0, void *a1, void *a2);
    extern s32 func_8014DCE0(s32 arg0, s32 arg1, s32 arg2);
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);

    Ctx f;
    u8 *e;
    u8 *p;
    u16 *p2 = param_2;
    u16 *p3 = param_3;
    s32 dx, dz, d1;
    s32 a, b;
    s32 e3, e5, e7;
    s32 ang, r;

    dx = p3[0] - p2[0];
    dz = p3[2] - p2[2];
    if ((s16)(dx | dz) == 0) goto fail;

    f.dvec.x = dx;
    f.dvec.y = p3[1] - p2[1];
    f.dvec.z = p3[2] - p2[2];

    e = *(u8 **)(param_1 + 0x170);
    if (*(u16 *)e == 0) goto fail;
    if ((*(u16 *)(e + 0x5C) & 0x1000) == 0) goto fail;
    if (*(s32 *)(e + 0x58) == 0) goto fail;
    if (func_80135A4C(*(s32 *)(e + 0x20), *(s32 *)(e + 0x58), (s32 *)param_2, (s32)param_3) == 0) goto fail;

    d1 = *(u16 *)(e + 0x6) - *(u16 *)(param_1 + 0x6);
    a = ratan2((s16)dz, (s16)dx);
    b = ratan2((s16)(*(u16 *)(e + 0xE) - *(u16 *)(param_1 + 0xE)), (s16)d1);
    a = (s16)func_80012A60((s16)a, (s16)b);
    if (a >= 0x400) goto fail;

    f.z2 = 0;
    f.z1 = 0;
    f.z0 = 0;

    e3 = *(u16 *)(e + 0x6);
    e5 = *(u16 *)(e + 0xA);
    e7 = *(u16 *)(e + 0xE);
    f.dvec.x = e3 + f.dvec.x;
    f.pvec.x = e3;
    f.dvec.y = e5 + f.dvec.y + 8;
    f.pvec.y = e5;
    f.dvec.z = e7 + f.dvec.z;
    f.pvec.z = e7;

    if (currentLocationId != 0x3008) {
        for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) {
            if (p == e) continue;
            if (*(u16 *)p == 0) continue;
            if (*(u16 *)(p + 0x5C) == 0) continue;
            if (*(s32 *)(p + 0x58) == 0) continue;
            func_80135888(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), (s32)&f.pvec, (s32)&f.dvec);
        }
    } else {
        ang = ratan2((s16)f.pvec.x - (s16)f.dvec.x, (s16)f.pvec.z - (s16)f.dvec.z) & 0xFFF;
        func_800139C8(ang, D_8018876C, &f.out0);
        func_800139C8((s16)(ang - 0x155), D_8018876C, &f.out1);
        func_800139C8(ang + 0x155, D_8018876C, &f.out2);
        f.out0.x += f.pvec.x;
        f.out0.z += f.pvec.z;
        f.out0.y = f.pvec.y;
        f.out1.y = f.pvec.y;
        f.out2.y = f.pvec.y;
        f.out1.x += f.pvec.x;
        f.out1.z += f.pvec.z;
        f.out2.x += f.pvec.x;
        f.out2.z += f.pvec.z;
        for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) {
            if (p == e) continue;
            if (*(u16 *)p == 0) continue;
            if (*(u16 *)(p + 0x5C) == 0) continue;
            if (*(s32 *)(p + 0x58) == 0) continue;
            if (func_8014DCE0((s32)p, (s32)&f.pvec, (s32)&f.out0) != 0) {
                *(Blk8 *)&f.dvec = *(Blk8 *)&f.pvec;
            }
        }
    }

    r = func_80133784(0, &f.pvec, (s32)&f.dvec);
    if (r == 0 || (r == 0x2000 && (D_801152A8 | D_801152AC) == 0)) {
        *(u16 *)(e + 0x6) = f.dvec.x - f.z0;
        *(u16 *)(e + 0xA) = f.dvec.y;
        *(u16 *)(e + 0xE) = f.dvec.z - f.z2;
        f.dvec.x = f.dvec.x - f.pvec.x;
        f.dvec.z = f.dvec.z - f.pvec.z;
        f.dvec.y = f.dvec.y - f.pvec.y;
        *(u16 *)(param_1 + 0x6) = p2[0] + f.dvec.x;
        *(u16 *)(param_1 + 0xA) = p2[1] + f.dvec.y + 0x10;
        *(u16 *)(param_1 + 0xE) = p2[2] + f.dvec.z;
    } else {
        *(u16 *)(param_1 + 0x6) = p2[0];
        *(u16 *)(param_1 + 0xA) = p2[1] + 0x10;
        *(u16 *)(param_1 + 0xE) = p2[2];
    }
    return 1;

fail:
    *(s32 *)(param_1 + 0x170) = 0;
    return 0;
}
