// func_8014D820 -- "attach/track to parent entity" mover (304 ins, ov_SC01_077_after).
// param_1 = self entity (s32 base), param_2/param_3 = u16[] pos snapshots (prev/cur).
// Delta -> validate tracked parent (e=*(self+0x170)) -> ratan2/func_80012A60 heading gate
// (<0x400) -> either the 0x3008 special case (func_800139C8 fan-of-3 + func_8014DCE0 collide
// loop) or the generic func_80135888 loop -> func_80133784 -> write back the pose.
// Returns s32 (1 = applied, 0 = detach: *(self+0x170)=0).
//
//   EC_EDIT (src/shared/engine_core.h line 9752, DEFINE_func_8014D790 body): void->s32 return
//   flip (unchanged from the opus seed; byte-neutral, the sole caller discards the result).
//
// PINS? NO. Fully block-scoped; the only asm is ABSENT (this draft is asm-free). `self`/`t0`/`t1`
// are plain s32 locals; no `register __asm__("$N")`, no generic-constraint asm, zero file-scope
// footprint -> ×134-clean via family_sweep --edit-remap.
//
// ============================================================================================
// FABLE5 gdb-on-cc1 PASS (2026-07-15) -- match_one 261 -> **110 positional** (mine=305/target=304).
// The opus "RC-6 whole-function permutation, pin-blocked" verdict is REFUTED at the mechanism
// level; the block-0 residual is CRACKED pin-free. Details in func_8014D820.fable.md.
//
//   ROOT-CAUSE CORRECTION (gdb oracle, .run/giants/fable_d820/nopin.gdb):
//     The opus blamed the sched.c:3199 "don't delay getting parameters" pin (INSN_REF_COUNT=1 on
//     the leading param copy). FALSE. Patching cc1 to skip BOTH the pin store AND the head-advance
//     (so insn 4 = `reg72=a0` re-enters the schedulable range) leaves the schedule BYTE-IDENTICAL:
//     the copy still lands at the block head, the 4 loads still PARALLELIZE. The pin is a red herring.
//     The real block-0 divergence: the target SERIALIZES the dx/dz load temps (load-pair -> subu ->
//     load-pair -> subu, reusing $v1/$v0), which opens the load-delay slot the param_1->$s4 copy
//     fills. A direct-expression draft (`dx = p3[0]-p2[0]`) gives 4 DISTINCT load pseudos -> the
//     scheduler batches them (parallel, 4 scratch regs) -> no slot for the copy.
//
//   THE CRACK (261 -> 110, PIN-FREE):
//     (1) SERIALIZE via reused load-temps -- the `{ s32 t0,t1; t0=p3[0]; t1=p2[0]; dx=t0-t1;
//         t0=p3[2]; t1=p2[2]; dz=t0-t1; }` block. K8/no-coalescing: reusing ONE pair of temp
//         VARIABLES forces one pseudo each -> the read-before-2nd-write anti-dependence forces the
//         serial schedule AND the $v1/$v0 reuse -- an exact block-0 load structure + temp regs.
//         (This is §45 Lever A / the func_801670E4 SPLIT<->MERGE duality applied to LOAD TEMPS.)
//     (2) ROUTE param_1 through `self` -- `self=param_1;` then all base accesses via `self`. This
//         moves param_1's callee-saved copy INTO block 0 (it participates in scheduling) instead of
//         the copy-at-head that param_1-direct produces. (param_1-direct + serial = 287; this = 110.)
//
//   RESIDUAL 110 = ~5 LOCALIZED knife-edges (NOT a whole-function permutation -- see fable.md):
//     (a) the `self` copy sinks (S2 birthing boost) to block-0 slot2 (dz-delay); target has it in
//         slot1 (dx-delay). Source position is invariant (sinks to the lowest slot with a live
//         successor use; both branch-successors use self). 2-set re-tie to stop the sink
//         MATERIALIZES a move (307/266). INTRINSIC -> permuter.
//     (b) beqz-delay dvec.x temp reg (a0 vs v1) -- CASCADES from (a): a0 is freed for the temp only
//         if the copy took slot1.
//     (c) ratan2 d1/dzz callee-saved reuse ($s0/$s1 order) -- RC-3/Lever-A callee tie; the reuse
//         form cascaded (129). INTRINSIC -> permuter.
//     (d) e3/e5/e7 + out0/1/2 combine + writeback store/load ORDER -- coupled schedule (source
//         reorder cascaded 231).
//     (e) return-1 const: mine materializes `li v0,1` standalone (the +1 ins); target CROSS-JUMPS
//         the `sh 0xE(s4); j; li v0,1` tail (§5a). goto-ret1 ADDS an insn (134). Cross-jump-shaped.
//
//   ROUTE: this pin-free 110 seed -> decomp-permuter. Block 0 is now STRUCTURALLY EXACT (serial
//   loads + correct temp regs), which the old opus seed was not; the prior ILS walled at masked-38
//   from the worse (parallel-block-0) seed, so a warm restart from here should go lower.
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
    s32 self;
    u16 *p2 = param_2;
    u16 *p3 = param_3;
    s32 dx, dz, d1;
    s32 a, b;
    s32 e3, e5, e7;
    s32 ang, r;

    {
        s32 t0, t1;
        self = param_1;
        t0 = p3[0]; t1 = p2[0]; dx = t0 - t1;
        t0 = p3[2]; t1 = p2[2]; dz = t0 - t1;
    }
    if ((s16)(dx | dz) == 0) goto fail;

    f.dvec.x = dx;
    f.dvec.y = p3[1] - p2[1];
    f.dvec.z = p3[2] - p2[2];

    e = *(u8 **)(self + 0x170);
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
        *(u16 *)(self + 0x6) = p2[0] + f.dvec.x;
        *(u16 *)(self + 0xA) = p2[1] + f.dvec.y + 0x10;
        *(u16 *)(self + 0xE) = p2[2] + f.dvec.z;
    } else {
        *(u16 *)(self + 0x6) = p2[0];
        *(u16 *)(self + 0xA) = p2[1] + 0x10;
        *(u16 *)(self + 0xE) = p2[2];
    }
    return 1;

fail:
    *(s32 *)(self + 0x170) = 0;
    return 0;
}
