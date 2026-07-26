#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"

/* ===========================================================================
 * func_8017C730 -- 1,061 ins, ov_SC03_010 (behemoth #6).   *** MATCH ***
 *
 * STATUS (2026-07-25, session 21, gcc-2.7.2 pinned triple):
 *   python3 tools/match_one.py func_8017C730 --c <this file> \
 *     --asm-subdir asm/ov_SC03_010/nonmatchings/ov_SC03_010_jr_8017AE2C
 *   -> MATCH (1061 ins)
 *   Independent re-check (private pipeline .run/giants/c730_cc.sh + b3_align.py):
 *     mine 1061 target 1061
 *     register-MASKED 1061/1061 = 100.0%   register-KEPT 1061/1061 = 100.0%
 *   Per-region (c730_reg.py), all register-KEPT 100%:
 *     pro 80  part 55  proj 47  bbox 165  prim 56  A:F3 127  B:FT3 131
 *     C:F4 180  D:FT4 187  tail 33
 *   Frame 0x270 exact; every sp offset agrees with the target.
 *   Undefined symbols: exactly the target's 11 externals, no more, no fewer.
 *   The compiler-emitted .rodata jump table is byte-correct too:
 *     offsets 0xA54 0xA54 0xD24 0xD24 0x64C 0x64C 0x848 0x848
 *     == target jtbl_8019EBA4 (asm/ov_SC03_010/data/tail21.data.s) relative to
 *     the function base.  {0,1}->C:F4 {2,3}->D:FT4 {4,5}->A:F3 {6,7}->B:FT3.
 *
 *   match_one is the CANDIDATE gate; the whole-binary SHA1 rebuild (G3/P9) is the
 *   arbiter and has NOT been run here (the task forbade touching src/, config/ or
 *   the build tree).  THIS IS A jr FUNCTION -- cookbook Sec.81's 3-step carve
 *   chain is REQUIRED before banking:
 *     1. tools/jr_isolate_all.py ov_SC03_010 --only func_8017C730   (gate)
 *     2. tools/jtbl_carve.py     ov_SC03_010 --func func_8017C730   (gate)
 *     3. tools/harvest_verify.py --binary ov_SC03_010 --drafts <dir> --chunk 1
 *   then a FULL R22 (config changed => T2).
 *
 * WHAT IT IS: the "camera height-band cull + distance-CLUT fade" variant of the
 *   TMD mesh-renderer family.  Skeleton = the MATCHED unlit base func_8017CA80
 *   (952 ins, src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c): same 3-call prologue,
 *   same Part[] outer loop (stride 0x14) with the 8-corner AABB rtpt/rtps and
 *   the screen-bbox reject, same Prim[] inner loop (stride 0xC) with
 *   rtpt/stflg/nclip/stopz, same 4-arm switch, same OT insert, same
 *   `D_800A5E60 = pkt`.  +109 instructions in SEVEN places:
 *
 *   (1) PROLOGUE, +36 ins -- the func_8004974C feature (the one extra shared
 *       callee).  Computes the camera position in WORLD space and derives a
 *       height band from its Y:
 *           lim = func_800491EC();            -- NOT `+ *(s32*)(arg0+0x64)`
 *           org = {0,0,0};  bandsetup(&org, &hv);
 *           hmid = hv.vy + 0x100;  hhi = hv.vy + 0x280;  hv.vy -= 0x180;
 *       bandsetup() is a `static inline` helper -- see L1 below; that is what
 *       makes gcc re-materialise `addiu $a0,$sp,0xD0` at BOTH call sites
 *       instead of parking &rot in $s0.  Its body is the byte-identical twin of
 *       the MATCHED standalone func_8017C294
 *       (src/ov_SC02_004/ov_SC02_004_jr_8017AE2C.c:3285), which is presumably
 *       the same source helper compiled un-inlined in that overlay.
 *   (2) PART LOOP, +19 ins -- a per-part mid-height cull BEFORE the AABB is
 *       built:  mid = (mny + my) / 2;  if (mid < hv.vy) continue;
 *                                     if (hhi < mid) continue;
 *       (`mid` is s16, hence the sll/sra sign-extend at each use.)
 *   (3) THE PART-LEVEL `lim >= g.otz` CULL IS GONE, -11 ins.  There is no
 *       gte_stszotz in this variant at all, so the GTE result block loses its
 *       `otz` member: only flag, opz, sz0..sz3 exist.
 *   (4) The per-prim SCREEN-Y bounds tighten from +-0x78/0x79 to +-0x6E/0x6F
 *       (all 5 sites); the X bounds stay +-0xA0/0xA1.
 *   (5) A REDUNDANT re-test of the band after the bbox cull, +10 ins:
 *           t32 = mid;  if (!(hhi < t32)) mnc = hmid;
 *       `mnc` is dead afterwards and `hmid` has no other reader -- vestigial
 *       source.  See L4/L5.
 *   (6) A per-prim NEAR-PLANE cull in the FLAT arms only:
 *           A:F3  if (gsz0 < lim && gsz1 < lim && gsz2 < lim) break;      +15
 *           C:F4  if (gsz0 < lim && ... && gsz3 < lim) break;             +20
 *       (the textured arms B/FT3 and D/FT4 do NOT have it), and arm C gains the
 *       `if (code != 0) gopz = za + 0x200;` half-step the base lacks.
 *   (7) The TEXTURED arms gain a DISTANCE-DRIVEN CLUT, +10 ins each:
 *           uvw = tp[1] & 0x3FC0FFFF;          -- clear the CLUT-x field
 *           cd  = gopz - 0x174;
 *           if (cd < 0) cd = gopz - 0xF5;
 *           pkt->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);
 *       plus a stray `gte_avsz3()` in arm B ONLY (its OTZ result is never read;
 *       it is in the target, so it ships -- ablation L11 = -3 ins).
 *       Arm B's half-step test is spelled `if (code != 6)` (a `beq`), NOT the
 *       base's `if (code == 7)` (a `bne`).
 *
 * FRAME (0x270, exact -- every offset agrees with the target):
 *   0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 mtx |
 *   0xC0 org | 0xC8 hv | 0xD0 rot | 0xF0 inv | 0x110 dv |
 *   0x118 gflag 0x11C gopz 0x120 gsz0 0x124 gsz1 0x128 gsz2 0x12C gsz3 |
 *   0x130 hmid (HImode spill) | 0x138 nprim | 0x140 nparts |
 *   0x148 loop.c's hoisted (s16)hhi | 0x240 the part loop pseudo |
 *   0x248..0x26C saved regs (s0-s7, fp, ra).
 *   rot/inv/dv are the INLINED HELPER's locals -- they are stack TEMPS, which is
 *   why they sit after hv and before the GTE result words.
 *   Sec.79: the three DECLARED spilled scalars take slots 0/1/2, so
 *   `s16 hmid;` must precede `u32 nprim;` which must precede `s32 nparts;`
 *   (ablation L12 = 4 mismatched).  0x148 is not a declared variable.
 *
 * ---------------------------------------------------------------------------
 * THE LEVERS.  Every one below is proven NECESSARY by drop-one ablation against
 * this exact draft (.run/giants/c730_abl.py); the number is that ablation's
 * `match_one` result.
 *
 * L1  bandsetup() IS A `static inline` HELPER, not straight-line code.
 *     ABLATION: inline it by hand -> 1063 ins, 973 mismatched.
 *     WHY (the reusable finding): `expand_expr`'s ADDR_EXPR case
 *     (expr.c:6260) ends in `force_operand (XEXP (op0, 0), target)` with
 *     target == NULL, and force_operand on `(plus virtual-stack-vars K)` always
 *     emits a NEW PSEUDO -- unless K == 0, i.e. the object is the FIRST local.
 *     Two `&rot` therefore become one pseudo (cse merges them; nothing in cse.c
 *     invalidates an expression built on a callee-saved base at a call), that
 *     pseudo is live across a call, so it costs `addiu $s0,$sp,0xD0` + two
 *     `move`s.  Inside an INLINED function, `&rot` (the helper's first local)
 *     is the bare virtual-stack-vars REG, so integrate.c substitutes
 *     `(plus fp K)` INDEPENDENTLY at each occurrence -> `addiu $a0,$sp,0xD0`
 *     twice, exactly like the target.  A 10-case bisect (.run/c730/f*.c) pinned
 *     the "first local" rule; 17 non-inline spellings all failed.
 * L2  THE SIX GTE RESULT WORDS ARE SIX SEPARATE `long` SCALARS, not a struct.
 *     ABLATION: make them a struct -> 61 mismatched (every g offset wrong).
 *     WHY: `expand_decl` (stmt.c:3412) gives an aggregate a stack slot
 *     IMMEDIATELY (assign_stack_temp), which would put it at 0xD0, ahead of the
 *     inlined helper's temps.  A SCALAR gets a pseudo at declaration time and is
 *     only moved to the stack by `put_var_into_stack` when its address is first
 *     taken -- which happens INSIDE the loop, after the helper's temps, so the
 *     six land at 0x118..0x12F in first-`&` order (flag, opz, sz0, sz1, sz2,
 *     sz3) and the spill area starts at 0x130.
 * L3  ARMS A AND C STORE rgbc AS `*(u32 *)(pkt + 4)`, not `((PolyF3*)pkt)->rgbc`.
 *     ABLATION (arm C only) -> 1060 ins, 255 mismatched.
 *     WHY: gcc-2.7.2's `true_dependence` says a VARYING-address in-struct ref
 *     cannot conflict with a FIXED-address scalar ref.  With L2 in force `gopz`
 *     is a fixed-address SCALAR, so a `((PolyF3*)pkt)->rgbc` store (in-struct,
 *     varying) is assumed not to alias it and the scheduler hoists the `gopz`
 *     load into the rgbc load-delay slot -- killing the `nop` the target has
 *     there.  Spelling the store as a scalar deref restores the conflict.
 *     (Arms B and D do not need it: there the delay slot is filled by tp[1].)
 * L4  `t32 = mid;` BEFORE the redundant band re-test -- reuse of an EXISTING
 *     busy variable, not a fresh temp.   ABLATION -> 2 mismatched
 *     (`sra $v0` where the target has `sra $v1`).  A fresh `s32 _m2 = mid;`
 *     also measured 2 -- Sec.78: reuse an already-busy variable.  Laundering
 *     `mid` through t32 gives the sign-extension its own allocno so local-alloc
 *     cannot tie the sll->sra producer chain into $v0.
 * L5  ONE ZERO-BYTE `__asm__ volatile ("" : : "r" (mnc))` after `mnc = hmid`.
 *     ABLATION -> 1051 ins, 951 mismatched.  The assignment is DEAD, so
 *     gcc-2.7.2's flow.c deletes it and takes `hmid`, its 0x130 spill slot and
 *     10 instructions with it.  The dial emits `#APP/#NO_APP` only.  It is a
 *     documented STAND-IN for whatever real (later-removed) reader `mnc` had;
 *     twelve natural spellings were measured and all were DCE'd (report table).
 * L6  `wv = wz >> 16;` COMPUTED BEFORE the two band `continue`s, in a DEDICATED
 *     variable (the base reuses `wy`).  ABLATION (compute it after) -> 51
 *     mismatched.  It has to live in the same basic block as the culls so dbr
 *     can put it in the first cull's delay slot, which is what the target does;
 *     it also fixes the whole part-loop head's register assignment.
 * L7  Arm B's `otp = ...` hoisted above the uv stores.  ABLATION -> still MATCH
 *     on THIS base (it was worth -8 instructions at an earlier base -- Sec.80(i)
 *     in action).  Kept because it is the natural reading: one `lw 0x11C($sp)`
 *     then serves both the CLUT and the OT index.
 * L8  Arm D uses a SEPARATE temp (`uvm`) for the CLUT mask; `uvw` still carries
 *     tp[3] for uv2/uv3.   ABLATION (share one) -> 11 mismatched.  Sharing gives
 *     the variable 2 deaths, so local-alloc.c:472 refuses it a local allocno and
 *     `combine_regs` can no longer tie its producer chain (Sec.76).
 * L9  Arm B masks tp[1] into `uvw` as a SEPARATE STATEMENT before the `cd` if.
 *     ABLATION (inline it into the uvc0 expression) -> 17 mismatched.  It has to
 *     be in the same basic block as the branch so the lui/ori/lw/and fill three
 *     load-delay slots and dbr can put the `and` in the bgez slot.
 * L10 ZERO Sec.47 `__asm__ volatile ("")` sliders.  The matched 952-ins base
 *     ships ONE (to split the &g.sz1/&g.sz2 allocno tie); here the right count
 *     is NONE.   ABLATION (add one) -> 15 mismatched.  Same sign as func_8017C954.
 * L11 `gte_avsz3()` in arm B.   ABLATION -> 1058 ins, 457 mismatched.
 * L12 `u32 nprim;` declared BEFORE `s32 nparts;` (Sec.79 frame-slot oracle).
 *     ABLATION (swap) -> 4 mismatched.
 * =========================================================================== */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv3c(r0) __asm__ volatile (         \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 8( %0 );"                          \
    "lwc2 $3, 12( %0 );"                         \
    "lwc2 $4, 16( %0 );"                         \
    "lwc2 $5, 20( %0 )"                          \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3c(r0) __asm__ volatile (       \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 4( %0 );"                         \
    "swc2 $14, 8( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_f3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_ft3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                         \
    "swc2 $17, 0( %1 );"                         \
    "swc2 $18, 0( %2 );"                         \
    "swc2 $19, 0( %3 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )


#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")

extern void ReadRotMatrix(MATRIX2 *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void func_8004974C(MATRIX2 *, MATRIX2 *);
extern void ApplyMatrixSV(MATRIX2 *, SVECTOR2 *, SVECTOR2 *);

static inline void bandsetup(SVECTOR2 *o, SVECTOR2 *out)
{
    MATRIX2 rot;
    MATRIX2 inv;
    SVECTOR2 dv;

    ReadRotMatrix(&rot);
    PushMatrix();
    dv.vx = o->vx - rot.t[0];
    dv.vy = o->vy - rot.t[1];
    dv.vz = o->vz - rot.t[2];
    func_8004974C(&rot, &inv);
    ApplyMatrixSV(&inv, &dv, out);
    PopMatrix();
}

void func_8017C730(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    SVECTOR2 org;
    SVECTOR2 hv;
    long gflag, gopz, gsz0, gsz1, gsz2, gsz3;

    s32 lim;
    s16 hmid;
    s16 hhi;
    u32 nprim;
    s32 nparts;
    s32 j;
    u32 i;
    Part *part;
    Prim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz, wv;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    s16 mid;
    s32 cd;

    lim = func_800491EC();
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    org.vx = 0;
    org.vy = 0;
    org.vz = 0;
    bandsetup(&org, &hv);

    hmid = hv.vy + 0x100;
    hhi = hv.vy + 0x280;
    hv.vy = hv.vy - 0x180;

    pkt = D_800A5E60;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        wv = wz >> 16;
        mid = (mny + my) / 2;
        if (mid < hv.vy) continue;
        if (hhi < mid) continue;
        box[0].vx = mn; box[0].vy = mny; box[0].vz = wz;
        box[1].vx = mx; box[1].vy = mny; box[1].vz = wz;
        box[2].vx = mn; box[2].vy = mny; box[2].vz = wv;
        box[3].vx = mx; box[3].vy = mny; box[3].vz = wv;
        box[4].vx = mn; box[4].vy = my;  box[4].vz = wz;
        box[5].vx = mx; box[5].vy = my;  box[5].vz = wz;
        box[6].vx = mn; box[6].vy = my;  box[6].vz = wv;
        box[7].vx = mx; box[7].vy = my;  box[7].vz = wv;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        gte_stsxy(&sxy[3]);
        gte_ldv3c(&box[4]);
        gte_rtpt();
        gte_stsxy3(&sxy[4], &sxy[5], &sxy[6]);
        gte_ldv0(&box[7]);
        gte_rtps();
        gte_stsxy(&sxy[7]);

        xa32 = sxy[0].vx;
        xb32 = sxy[1].vx;
        if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
        t32 = sxy[2].vx;
        if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
        t32 = sxy[3].vx;
        if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
        xa32 = sxy[4].vx;
        xb32 = sxy[5].vx;
        if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
        t32 = sxy[6].vx;
        if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
        t32 = sxy[7].vx;
        if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
        mnc = xmn1;
        if (xmn2 < xmn1) mnc = xmn2;
        mxc = xmx1;
        if (mxc < xmx2) mxc = xmx2;
        if ((s16)mxc >= -0xA0 && (s16)mnc < 0xA1) {
            xa32 = sxy[0].vy;
            xb32 = sxy[1].vy;
            if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
            t32 = sxy[2].vy;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            t32 = sxy[3].vy;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            xa32 = sxy[4].vy;
            xb32 = sxy[5].vy;
            if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
            t32 = sxy[6].vy;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            t32 = sxy[7].vy;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            mnc = xmn1;
            if (xmn2 < xmn1) mnc = xmn2;
            mxc = xmx1;
            if (mxc < xmx2) mxc = xmx2;
            if ((s16)mxc >= -0x6E && (s16)mnc < 0x6F) {
                t32 = mid;
                if (!(hhi < t32)) { mnc = hmid; __asm__ volatile ("" : : "r" (mnc)); }
                prim = (Prim *)part->prim;
                nprim = part->nprim;
                for (i = 0; i < nprim; i++, prim++) {
                    w = prim->w1;
                    va = vtx + (w & 0xFFFF);
                    vb = vtx + (w >> 16);
                    w = prim->w2;
                    vc = vtx + (w & 0xFFFF);
                    w = w >> 16;
                    gte_ldv3(va, vb, vc);
                    gte_rtpt();
                    gte_stflg(&gflag);
                    if (!(gflag & 0x7F85E000)) {
                        gte_nclip();
                        code = w & 7;
                        vd = vtx + (w & 0xFFF8);
                        gte_stopz(&gopz);
                        if (gopz > 0) {
                            switch (code) {
                            case 4:
                            case 5:
                                gte_stsxy3_f3(pkt);
                                gte_stsz3(&gsz0, &gsz1, &gsz2);
                                if (((PolyF3 *)pkt)->x0 > ((PolyF3 *)pkt)->x1) {
                                    mx = ((PolyF3 *)pkt)->x0;
                                    mn = ((PolyF3 *)pkt)->x1;
                                } else {
                                    mn = ((PolyF3 *)pkt)->x0;
                                    mx = ((PolyF3 *)pkt)->x1;
                                }
                                if (((PolyF3 *)pkt)->x2 > mx) mx = ((PolyF3 *)pkt)->x2;
                                else if (((PolyF3 *)pkt)->x2 < mn) mn = ((PolyF3 *)pkt)->x2;
                                if (mx >= -0xA0 && mn < 0xA1) {
                                    if (((PolyF3 *)pkt)->y0 > ((PolyF3 *)pkt)->y1) {
                                        my = ((PolyF3 *)pkt)->y0;
                                        mny = ((PolyF3 *)pkt)->y1;
                                    } else {
                                        mny = ((PolyF3 *)pkt)->y0;
                                        my = ((PolyF3 *)pkt)->y1;
                                    }
                                    if (((PolyF3 *)pkt)->y2 > my) my = ((PolyF3 *)pkt)->y2;
                                    else if (((PolyF3 *)pkt)->y2 < mny) mny = ((PolyF3 *)pkt)->y2;
                                    if (my >= -0x6E && mny < 0x6F) {
                                        s32 za, zb;
                                        u32 *otp;
                                        if (gsz0 < lim && gsz1 < lim && gsz2 < lim) break;
                                        if (gsz0 > gsz1) {
                                            za = gsz0;
                                            if (za < gsz2) za = gsz2;
                                        } else {
                                            za = gsz1;
                                            if (za < gsz2) za = gsz2;
                                        }
                                        gopz = za;
                                        if (code != 4) gopz = za + 0x200;
                                        *(u32 *)(pkt + 4) = prim->w0;
                                        otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                        *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                        *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                        pkt += 0x14;
                                    }
                                }
                                break;
                            case 6:
                            case 7:
                                gte_stsxy3_ft3(pkt);
                                gte_stsz3(&gsz0, &gsz1, &gsz2);
                                if (((PolyFT3 *)pkt)->x0 > ((PolyFT3 *)pkt)->x1) {
                                    mx = ((PolyFT3 *)pkt)->x0;
                                    mn = ((PolyFT3 *)pkt)->x1;
                                } else {
                                    mn = ((PolyFT3 *)pkt)->x0;
                                    mx = ((PolyFT3 *)pkt)->x1;
                                }
                                if (((PolyFT3 *)pkt)->x2 > mx) mx = ((PolyFT3 *)pkt)->x2;
                                else if (((PolyFT3 *)pkt)->x2 < mn) mn = ((PolyFT3 *)pkt)->x2;
                                if (mx >= -0xA0 && mn < 0xA1) {
                                    if (((PolyFT3 *)pkt)->y0 > ((PolyFT3 *)pkt)->y1) {
                                        my = ((PolyFT3 *)pkt)->y0;
                                        mny = ((PolyFT3 *)pkt)->y1;
                                    } else {
                                        mny = ((PolyFT3 *)pkt)->y0;
                                        my = ((PolyFT3 *)pkt)->y1;
                                    }
                                    if (((PolyFT3 *)pkt)->y2 > my) my = ((PolyFT3 *)pkt)->y2;
                                    else if (((PolyFT3 *)pkt)->y2 < mny) mny = ((PolyFT3 *)pkt)->y2;
                                    if (my >= -0x6E && mny < 0x6F) {
                                        s32 za, zb;
                                        u32 *otp;
                                        u32 *tp;
                                        u32 uvw;
                                        gte_avsz3();
                                        if (gsz0 > gsz1) {
                                            za = gsz0;
                                            if (za < gsz2) za = gsz2;
                                        } else {
                                            za = gsz1;
                                            if (za < gsz2) za = gsz2;
                                        }
                                        gopz = za;
                                        if (code != 6) gopz = za + 0x200;
                                        tp = (u32 *)prim->w0;
                                        ((PolyFT3 *)pkt)->rgbc = tp[0];
                                        uvw = tp[1] & 0x3FC0FFFF;
                                        cd = gopz - 0x174;
                                        if (cd < 0) cd = gopz - 0xF5;
                                        otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                        ((PolyFT3 *)pkt)->uvc0 = uvw | (((cd >> 7) + 0x30) << 16);
                                        ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                        ((PolyFT3 *)pkt)->uv2 = tp[3];
                                        *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                        *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                        pkt += 0x20;
                                    }
                                }
                                break;
                            case 0:
                            case 1:
                                gte_stsxy3_f4(pkt);
                                gte_ldv0(vd);
                                gte_rtps();
                                if (((PolyF4 *)pkt)->x0 > ((PolyF4 *)pkt)->x1) {
                                    mx = ((PolyF4 *)pkt)->x0;
                                    mn = ((PolyF4 *)pkt)->x1;
                                } else {
                                    mn = ((PolyF4 *)pkt)->x0;
                                    mx = ((PolyF4 *)pkt)->x1;
                                }
                                if (((PolyF4 *)pkt)->x2 > mx) mx = ((PolyF4 *)pkt)->x2;
                                else if (((PolyF4 *)pkt)->x2 < mn) mn = ((PolyF4 *)pkt)->x2;
                                if (((PolyF4 *)pkt)->y0 > ((PolyF4 *)pkt)->y1) {
                                    my = ((PolyF4 *)pkt)->y0;
                                    mny = ((PolyF4 *)pkt)->y1;
                                } else {
                                    mny = ((PolyF4 *)pkt)->y0;
                                    my = ((PolyF4 *)pkt)->y1;
                                }
                                if (((PolyF4 *)pkt)->y2 > my) my = ((PolyF4 *)pkt)->y2;
                                else if (((PolyF4 *)pkt)->y2 < mny) mny = ((PolyF4 *)pkt)->y2;
                                gte_stflg(&gflag);
                                if (!(gflag & 0x7F85E000)) {
                                    gte_stsz4(&gsz0, &gsz1, &gsz2, &gsz3);
                                    gte_stsxy((long *)&((PolyF4 *)pkt)->x3);
                                    if (((PolyF4 *)pkt)->x3 < mn) mn = ((PolyF4 *)pkt)->x3;
                                    else if (mx < ((PolyF4 *)pkt)->x3) mx = ((PolyF4 *)pkt)->x3;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyF4 *)pkt)->y3 < mny) mny = ((PolyF4 *)pkt)->y3;
                                        else if (my < ((PolyF4 *)pkt)->y3) my = ((PolyF4 *)pkt)->y3;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, zb;
                                            u32 *otp;
                                            if (gsz0 < lim && gsz1 < lim && gsz2 < lim && gsz3 < lim) break;
                                            zb = gsz2;
                                            if (zb < gsz3) zb = gsz3;
                                            za = gsz0;
                                            if (za < gsz1) za = gsz1;
                                            if (za < zb) za = zb;
                                            gopz = za;
                                            if (code != 0) gopz = za + 0x200;
                                            *(u32 *)(pkt + 4) = prim->w0;
                                            otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x5000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x18;
                                        }
                                    }
                                }
                                break;
                            case 2:
                            case 3:
                                gte_stsxy3c(&tmpxy[0]);
                                gte_ldv0(vd);
                                gte_rtps();
                                if (tmpxy[0].vx > tmpxy[1].vx) {
                                    mx = tmpxy[0].vx;
                                    mn = tmpxy[1].vx;
                                } else {
                                    mn = tmpxy[0].vx;
                                    mx = tmpxy[1].vx;
                                }
                                if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                if (tmpxy[0].vy > tmpxy[1].vy) {
                                    my = tmpxy[0].vy;
                                    mny = tmpxy[1].vy;
                                } else {
                                    mny = tmpxy[0].vy;
                                    my = tmpxy[1].vy;
                                }
                                if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                gte_stflg(&gflag);
                                if (!(gflag & 0x7F85E000)) {
                                    gte_stsz4(&gsz0, &gsz1, &gsz2, &gsz3);
                                    gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                    if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                    else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                        else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, zb;
                                            u32 *otp;
                                            u32 *tp;
                                            u32 uvw;
                                            u32 uvm;
                                            zb = gsz2;
                                            if (zb < gsz3) zb = gsz3;
                                            za = gsz0;
                                            if (za < gsz1) za = gsz1;
                                            if (za < zb) za = zb;
                                            gopz = za;
                                            if (code != 2) gopz = za + 0x200;
                                            *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                            *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                            *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT4 *)pkt)->rgbc = tp[0];
                                            uvm = tp[1] & 0x3FC0FFFF;
                                            cd = gopz - 0x174;
                                            if (cd < 0) cd = gopz - 0xF5;
                                            otp = (u32 *)(((gopz >> 2) << 2) + ot);
                                            ((PolyFT4 *)pkt)->uvc0 = uvm | (((cd >> 7) + 0x30) << 16);
                                            ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                            uvw = tp[3];
                                            ((PolyFT4 *)pkt)->uv2 = uvw;
                                            ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x28;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    D_800A5E60 = pkt;
}
