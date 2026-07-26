#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"

/* ===========================================================================
 * func_8017BF14 -- 4,763 ins, ov_SC03_116 (behemoth #4).   *** MATCH ***
 *
 * STATUS (2026-07-25, session 20 round 2, gcc-2.7.2 pinned triple):
 *   python3 tools/match_one.py func_8017BF14 --c <this file> \
 *     --asm-subdir asm/ov_SC03_116/nonmatchings/ov_SC03_116_jr_8017AE2C
 *   -> MATCH (4763 ins)  func_8017BF14      [reproduced 3x, private work dirs]
 *      LENGTH EXACT | OPCODE HISTOGRAM EXACT (L1 = 0) | STACK FRAME EXACT
 *      (all 127 slots at the target's offsets, frame 0x360)
 *      masked index-wise diff: 0 / 4763 mismatched.
 *   `match_one` is the CANDIDATE gate.  The whole-binary SHA1 arbiter (G3/P9)
 *   is run by the coordinator and is the only thing that makes this final.
 *
 *   Round 1 closed at 45/4763 mismatched.  Round 2 took 45 -> 37 -> 33 -> 21
 *   -> 11 -> 3 -> 2 -> 0.  See .run/giants/s19_bf14_report2.md.
 *
 * WHAT IT IS
 *   The *four*-light-box variant of the volumetric-light renderer whose
 *   3-box sibling func_8017D960 (3,338 ins, ov_SC03_090) is MATCHED, and whose
 *   unlit ancestor func_8017BEBC (ov_SC03_099) is MATCHED.  Same family, same
 *   skeleton; this is the biggest member.
 *
 *   Signature: func_8017BF14(s32 arg0, s32 lim).  Unlike every other member of
 *   the family this one is a LEAF -- 0 callees.  The 3-call prologue
 *   (func_800491EC / func_800547D8 / func_80052E38) of the siblings is gone;
 *   `lim` arrives as arg1 (spilled to 0xB0).  That is why the frame has no
 *   0x10 argument area (tmpxy[] starts at sp+0x00) and no $ra save.
 *
 *   Per part (stride 0x14, outer loop): build the 8-corner AABB in box[],
 *   rtpt/rtpt + rtps/rtps -> sxy[8], stszotz -> g.otz, reject on
 *   `lim >= g.otz`, then screen-space bbox reject on X (-0xA0..0xA1) and
 *   Y (-0x6E..0x6F).
 *   Per prim (stride 0xC, inner loop): rtpt the 3 vertices, stflg mask
 *   0x7F85E000, nclip, stopz > 0, then a 4-way range tree on `code = w & 7`
 *   that keeps ONLY codes 6,7 (tri) and 2,3 (quad); 0,1,4,5 fall through to
 *   the loop tail.
 *   Per drawn poly: screen bbox reject, then each vertex is tested against
 *   FOUR axis-aligned light boxes (flags f0..f3), and if any is lit a
 *   0x00..0x80 attenuation per active box is computed, summed, biased +0x10
 *   and clamped to 0x80 -> a grey gouraud vertex colour.
 *     lit   -> POLY_GT3 (0x28, tag 0x34000000, OT 0x9000000)
 *              POLY_GT4 (0x34, tag 0x3C000000, OT 0xC000000)
 *     unlit -> POLY_FT3 (0x20, OT 0x7000000) / POLY_FT4 (0x28, OT 0x9000000)
 *              with rgbc = (tp[0] & 0xFF000000) | 0x101010   <-- NOT black,
 *              unlike func_8017D960 where the unlit colour is plain black.
 *
 * THE FOUR LIGHT BOXES  (stride 0x1C, {s32 enable; u16 cx,cy,cz; s32 range})
 *   D_80197C28 / D_80197C44 / D_80197C60 / D_80197C7C.
 *   Falloff geometry differs from the 3-box sibling: RLO = R - 0x200 (not
 *   -0x80) and the ramp is ((R - d) / 4) (not (R - d)), so the 0x80 ceiling is
 *   reached over a 0x200-wide band instead of 0x80.  The `/ 4` is a SIGNED
 *   divide -- `bgez / addiu 3 / sra 2` -- not a shift.
 *
 * FIVE ORIGINAL-SOURCE COPY-PASTE ARTEFACTS, all byte-proven
 *   The 4th light box was bolted onto a copy of the 3-box source BY HAND and
 *   the hand edit was incomplete in five places.  Each was read off the target
 *   and each removed a measured delta.
 *   (1) `r3lo = r2 - 0x200;` -- box 3's low radius is derived from box 2's
 *       RANGE VARIABLE, not from its own D_80197C88.  Proven by the target's
 *       `addiu $t6, $s0, -0x200` reusing the register that box 2's `lw` filled;
 *       spelling it `D_80197C6C - 0x200` re-loads the global (+2 ins).
 *   (2) Only SIX of the eight radius variables are zero-initialised
 *       (r0,r1,r2,r0lo,r1lo,r2lo) -- r3/r3lo are left uninitialised, exactly
 *       the init list the 3-box version needed.
 *   (3) The ATTEN body is written out LONGHAND 7 times (3 tri vertices +
 *       4 quad vertices).  When box 3 was bolted on, the `R` of the z- and
 *       y-axis KILL tests was left as r2 in three of those copies:
 *         tri v0: z and y use r2   tri v2: z uses r2   all others use r3.
 *       Proven by the 24 `sll $v0,$s0,16` sites: 3 per group in box 2 plus
 *       exactly three extra at idx 1471, 1504 (tri v0) and 2178 (tri v2).
 *   (4) In the QUAD lit arm only, rgb2 and rgb3 take their `<< 16` term from
 *       c1, not from c2/c3.  Proven by the target CSE-ing ONE
 *       `sll $a0, $a0, 16` and re-using $a0 for all three stores.
 *   (5) *** ROUND 2 *** In the QUAD arm's VERTEX-1 group only, the box-3
 *       ATTEN's Y-axis `else if` branch accumulates into a2v instead of a3v,
 *       while that same test's KILL branch still says a3v.  Modelled by the
 *       ATTEN3W macro below (`AW` = the y-else destination).  Byte-proof:
 *         idx 3875  addu $a2,$zero,$zero   kill branch -> a3v ($a2)  [agreed]
 *         idx 3889  sra  $a3,$s2,7         else branch -> a2v ($a3)  [was the
 *                                          last structural residual]
 *       Costs zero instructions; the four other quad/tri sites are NOT like
 *       this (each was measured -- putting the artefact anywhere else is +2).
 *
 * FRAME (0x360, leaf -- no $ra, no argument area)
 *   0x000 tmpxy[4] | 0x010 box[8] | 0x050 sxy[8] |
 *   0x090 g{otz,flag,opz,sz0..sz3} | 0x0B0 lim | 0x0B8 j | 0x0C0 i |
 *   0x0C8 vd | 0x0D0 ot | 0x0D8 pkt | 0x0E0 f2 | 0x0E8 f3 |
 *   0x0F0/0x0F8/0x100 x3,z3,y3 | 0x108 prim | 0x110 nprim | 0x118 vtx |
 *   0x120 nparts | 0x128 part | 0x130..0x1D0 lo/hi bounds (21 s16 slots) |
 *   0x1D8..0x230 cx0..cz3 (12) | 0x238 r0 | 0x240 r1lo | 0x248 r2lo |
 *   0x250 r3lo | 0x288..0x2D0 the LICM-hoisted sign-extended bounds |
 *   0x328/0x330 spilled vertex coords | 0x338..0x358 s0-s7,fp.
 *   *** THE SLOT ORDER IS THE DECLARATION-ORDER ORACLE (see L5). ***
 *
 * ---------------------------------------------------------------------------
 * ROUND-1 LEVERS (kept; measured effect is byte-identical %, anchored)
 *
 * L1  `cb = (tp[0] & 0xFF000000) | 0x101010;` in both UNLIT arms.
 * L2  box-3 ATTEN kill-register per copy (artefact 3) + `r3lo = r2 - 0x200`
 *     (artefact 1).  89.15% -> 96.96% shape; killed sra+11 / sll+9.
 * L3  quad-lit rgb2/rgb3 use `c1 << 16` (artefact 4).  Killed the last sll+2.
 * L4  [SUPERSEDED BY R3] `s32 c0..c3` declared inside the two CULL blocks.
 * L5  `s32 f0, f1, f2, f3;` MOVED TO IMMEDIATELY AFTER `u8 *pkt;`.
 *     Spilled pseudos get stack slots in PSEUDO-NUMBER order and pseudo
 *     numbers are handed out in DECLARATION order, so the target's stack
 *     layout is a direct read-out of its declaration order.  After this one
 *     move ALL 127 stack slots agree with the target exactly.
 * L6  `u32 rgbw;` per emit arm.
 * L7  RC-15 zero-byte ref dial on `mny`, first statement of the TRI cull
 *     block -- flips my->$a3 / mny->$a2 to the target's grant.
 * L8  `cb` 2-statement accumulator [SUPERSEDED BY R2]; quad-lit rgb word as a
 *     3-statement accumulator [kept for rgb0/rgb1, SUPERSEDED for rgb2/rgb3
 *     by R5].
 * L9  FOUR REGISTER PINS: va->$t2, w->$a1, f0->$s3, c1->$a0.
 *     Round 2 removed va and w (see R4); f0 and c1 REMAIN and are both
 *     load-bearing.  This function has NO `jal`, so Sec.74's caller-saved
 *     pin-spanning-a-call hazard cannot arise -- that is why pins are usable
 *     on this family member and were a trap on the others.
 *
 * ---------------------------------------------------------------------------
 * ROUND-2 LEVERS -- 45 -> 0.  Metric is `match_one` MISMATCH COUNT (length is
 * exact throughout, so the raw count is honest).  Every number is measured.
 *
 * THE ONE MECHANISM BEHIND R1/R2/R4/R7.  A `register __asm__` pin makes the
 * variable a HARD REG in the RTL from the start.  When a 1-death local temp is
 * produced from, or consumed into, that hard reg, local-alloc.c's
 * `combine_regs` takes its hard-register branch (local-alloc.c:1795-1820) and
 * records the pinned register in `qty_phys_sugg` for the temp's quantity --
 * UNCONDITIONALLY, there is no death guard on that path.  The temp then lands
 * in the pinned register and the operation is done IN PLACE.  The target,
 * whose variable is an ordinary pseudo (reg_qty == -1 for anything crossing a
 * block), never gets that suggestion and keeps the temp in $v0/$v1.
 * Three independent cures, all used here:
 *   (i)  give the temp a NAMED variable with >1 death, so local-alloc.c:472
 *        (`reg_basic_block >= 0 && reg_n_deaths == 1`) refuses it a quantity
 *        and combine_regs bails at its very first test          -> R1
 *   (ii) drop the pin, if the pin is not load-bearing            -> R4
 *   (iii) keep the pinned value LIVE past the temp, so that
 *        find_free_reg cannot honour the suggestion              -> R7
 *
 * R1  `CLAMP80S` -- the four-way attenuation sum gets its own named variable
 *     `sv`, used at BOTH c1 sites (2 deaths).  Cure (i).       45 -> 37
 *     Target: `addu $v0,..; addu $v0,..; addu $v0,..; addiu <c>,$v0,0x10`.
 *     Without it the whole chain is tied into the pinned c1 ($a0).
 *     Only the two c1 sites: `sv` on all 7 sites collapses the frame (-64).
 * R2  UNLIT arms store `cb | 0x101010` as an expression instead of doing
 *     `cb |= 0x101010` in place.  `cb` is a function-scope global allocno, so
 *     the in-place form writes $a1; the expression form is a 1-death local
 *     that combine_regs ties to the DYING constant register $v1, which is
 *     what the target does.                                     37 -> 33
 * R3  *** `s32 c0, c1, c2, c3;` AT FUNCTION SCOPE, not per cull block. ***
 *     Read straight off the two MATCHED relatives (func_8017D960 line 310,
 *     func_8017F510 line 338), and confirmed by the target itself: its TRI
 *     grants (c0=$t4, c1=$a0, c2=$t2) are IDENTICAL to its QUAD grants, which
 *     is only possible if both arms share one set of allocnos.  Per-cull-block
 *     scope splits them into two independent allocno sets and the TRI set
 *     drifts.                                                   33 -> 21
 *     Declaration POSITION is neutral (5 anchors swept, all 21).
 *     NOTE this REVERSES round-1's L4.  L4 was correct on the round-1 base --
 *     it was supplying the extra local allocno that spills r1lo -- but R1+R2
 *     supply that pressure now, and the c1 pin does the rest.
 * R4  DROP the `va->$t2` and `w->$a1` pins.  With c0..c3 at function scope
 *     they are no longer load-bearing, and they were the sole cause of the
 *     prim-word producer ties (`andi`/`srl` written straight into $t2/$a1).
 *     Cure (ii).                                    21 -> 17 -> 13 (pair)
 *     Round 1 measured these as worth 4%; that was true of the round-1 base
 *     and is FALSE here.  Base-dependence, not a contradiction.
 * R5  QUAD lit rgb2/rgb3 revert to the SINGLE-EXPRESSION form (rgb0/rgb1 keep
 *     the 3-statement accumulator).  The intermediates then become 1-death
 *     local temps that alternate $v0/$v1, which is what lets the target's
 *     store of the previous rgb word sit one slot LATER.        21 -> 11
 *     Doing it to all four, or to rgb0/rgb1 only, is worse (23 / 21).
 * R6  Artefact 5 -- `ATTEN3W(a3v, a2v, ...)` at the QUAD vertex-1 site.  3 -> 2
 * R7  RC-15 zero-byte ref `__asm__ __volatile__ ("" :: "r" (c1));` placed
 *     immediately after the TRI arm's rgb1 store.  Cure (iii): it keeps the
 *     pinned c1 ($a0) live past `c1 << 16`, so find_free_reg cannot honour
 *     combine_regs' $a0 suggestion and the shift goes to $v0.       2 -> 0
 *     The c1 pin CANNOT simply be removed: it is what spills r1lo (dropping
 *     it, or moving it to any other colour, costs -64 length).  Measured.
 *
 * SCHEDULER ATTRIBUTION (Sec.76 primitive, run in round 2, never run before on
 * this function).  Compiled with -fno-schedule-insns, with
 * -fno-schedule-insns2, and with both.  The store/shift transposition at
 * idx 4643-4652 kept MY source order under all three.  It was therefore never
 * a `sched.c` decision: the ordering is a CONSEQUENCE of the register grant
 * (a 3-statement accumulator pins the value in one register, so no scheduler
 * could hoist the next `or` above the `sw`).  R5 fixed it by changing the
 * grant, exactly as Sec.78 predicts.
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

/* ---- the two gouraud-textured packet layouts this function emits ---------- */
typedef struct {
    u32 tag;
    u32 rgb0; s16 x0, y0; u32 uv0;
    u32 rgb1; s16 x1, y1; u32 uv1;
    u32 rgb2; s16 x2, y2; u16 uv2, p2;
} PolyGT3;                                      /* 0x28 */

typedef struct {
    u32 tag;
    u32 rgb0; s16 x0, y0; u32 uv0;
    u32 rgb1; s16 x1, y1; u32 uv1;
    u32 rgb2; s16 x2, y2; u16 uv2, p2;
    u32 rgb3; s16 x3, y3; u16 uv3, p3;
} PolyGT4;                                      /* 0x34 */


/* ---- the four light-volume descriptors (stride 0x1C) --------------------- */
extern s32 D_80197C28;
extern u16 D_80197C2C, D_80197C2E, D_80197C30;
extern s32 D_80197C34;
extern s32 D_80197C44;
extern u16 D_80197C48, D_80197C4A, D_80197C4C;
extern s32 D_80197C50;
extern s32 D_80197C60;
extern u16 D_80197C64, D_80197C66, D_80197C68;
extern s32 D_80197C6C;
extern s32 D_80197C7C;
extern u16 D_80197C80, D_80197C82, D_80197C84;
extern u16 D_80197C88;

/* ---- the box-containment test for one vertex against one light box ------- */
#define BOXTEST(F, X, Y, Z, LX, HX, LY, HY, LZ, HZ) \
    if ((LX) < (X) && (X) < (HX) && (LY) < (Y) && (Y) < (HY) && (LZ) < (Z) && (Z) < (HZ)) F = 1

/* ---- the separable per-axis falloff, visited in x, z, y order ------------ */
#define ATTEN(A, F, X, Y, Z, CX, CY, CZ, R, RLO)                        \
    A = 0;                                                              \
    if (F) {                                                            \
        d = (X) - (CX);   if (d < 0) d = (CX) - (X);                    \
        if (d < (R)) { A = 0x80; if (d >= (RLO)) A = ((R) - d) / 4; }   \
        d = (Z) - (CZ);   if (d < 0) d = (CZ) - (Z);                    \
        if ((R) < d) A = 0;                                             \
        else if ((RLO) < d) A = (A * (((R) - d) / 4)) >> 7;             \
        d = (Y) - (CY);   if (d < 0) d = (CY) - (Y);                    \
        if ((R) < d) A = 0;                                             \
        else if ((RLO) < d) A = (A * (((R) - d) / 4)) >> 7;             \
    }

#define ATTEN3W(A, AW, F, X, Y, Z, CX, CY, CZ, R, RLO, RZ, RY)          \
    A = 0;                                                              \
    if (F) {                                                            \
        d = (X) - (CX);   if (d < 0) d = (CX) - (X);                    \
        if (d < (R)) { A = 0x80; if (d >= (RLO)) A = ((R) - d) / 4; }   \
        d = (Z) - (CZ);   if (d < 0) d = (CZ) - (Z);                    \
        if ((RZ) < d) A = 0;                                            \
        else if ((RLO) < d) A = (A * (((R) - d) / 4)) >> 7;             \
        d = (Y) - (CY);   if (d < 0) d = (CY) - (Y);                    \
        if ((RY) < d) A = 0;                                            \
        else if ((RLO) < d) AW = (A * (((R) - d) / 4)) >> 7;            \
    }

#define ATTEN3(A, F, X, Y, Z, CX, CY, CZ, R, RLO, RZ, RY)               \
    A = 0;                                                              \
    if (F) {                                                            \
        d = (X) - (CX);   if (d < 0) d = (CX) - (X);                    \
        if (d < (R)) { A = 0x80; if (d >= (RLO)) A = ((R) - d) / 4; }   \
        d = (Z) - (CZ);   if (d < 0) d = (CZ) - (Z);                    \
        if ((RZ) < d) A = 0;                                            \
        else if ((RLO) < d) A = (A * (((R) - d) / 4)) >> 7;             \
        d = (Y) - (CY);   if (d < 0) d = (CY) - (Y);                    \
        if ((RY) < d) A = 0;                                            \
        else if ((RLO) < d) A = (A * (((R) - d) / 4)) >> 7;             \
    }

#define CLAMP80(C, A0, A1, A2, A3)  C = (A0) + (A1) + (A2) + (A3) + 0x10; if ((C) > 0x80) C = 0x80
#define CLAMP80S(C, A0, A1, A2, A3)  sv = (A0) + (A1) + (A2) + (A3); C = sv + 0x10; if ((C) > 0x80) C = 0x80


void func_8017BF14(s32 arg0, s32 lim)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern u8 D_800AF630[];

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 j;
    u32 i;
    u8 *vd;
    u32 ot;
    u8 *pkt;
    register s32 f0 __asm__("$19");
    s32 f1, f2, f3;
    s16 x3, z3, y3;
    Prim *prim;
    u32 nprim;
    u8 *vtx;
    s32 nparts;
    Part *part;
    s16 lo0x, hi0x, lo0y, hi0y, lo0z, hi0z;
    s16 lo1x, hi1x, lo1y, hi1y, lo1z, hi1z;
    s16 lo2x, hi2x, lo2y, hi2y, lo2z, hi2z;
    s16 lo3x, hi3x, lo3y, hi3y, lo3z, hi3z;
    s16 cx0, cy0, cz0, cx1, cy1, cz1, cx2, cy2, cz2, cx3, cy3, cz3;
    s16 r0;
    s16 r1;
    s16 r2;
    s16 r3;
    s16 r0lo;
    s16 r1lo;
    s16 r2lo;
    s16 r3lo;
    u8 *va, *vb, *vc;
    u32 w;
    s32 code;
    u32 vw, vzw;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    u8 *base;
    s16 x0, y0, z0, x1, y1, z1, x2, y2, z2;
    s32 a0v, a1v, a2v, a3v;
    register s32 c1 __asm__("$4"); s32 c0, c2, c3;
    s32 d;
    u32 *tp;
    u32 uvw;
    u32 cb;
    s32 sv;

    base = D_800AF630;

    r2lo = 0;
    r1lo = 0;
    r0lo = 0;
    r2 = 0;
    r1 = 0;
    r0 = 0;

    if (D_80197C28) {
        cx0 = D_80197C2C;
        cy0 = D_80197C2E;
        r0lo = D_80197C34 - 0x200;
        r0 = D_80197C34;
        cz0 = D_80197C30;
    } else {
        cz0 = 0x6000;
        cy0 = 0x6000;
        cx0 = 0x6000;
    }
    if (D_80197C44) {
        cx1 = D_80197C48;
        cy1 = D_80197C4A;
        r1 = D_80197C50;
        r1lo = D_80197C50 - 0x200;
        cz1 = D_80197C4C;
    } else {
        cz1 = 0x6000;
        cy1 = 0x6000;
        cx1 = 0x6000;
    }
    if (D_80197C60) {
        cx2 = D_80197C64;
        cy2 = D_80197C66;
        r2 = D_80197C6C;
        r2lo = D_80197C6C - 0x200;
        cz2 = D_80197C68;
    } else {
        cz2 = 0x6000;
        cy2 = 0x6000;
        cx2 = 0x6000;
    }
    if (D_80197C7C) {
        cx3 = D_80197C80;
        cy3 = D_80197C82;
        r3lo = r2 - 0x200;
        r3 = D_80197C88;
        cz3 = D_80197C84;
    } else {
        cz3 = 0x6000;
        cy3 = 0x6000;
        cx3 = 0x6000;
    }

    lo0x = cx0 - r0;  hi0x = cx0 + r0;
    lo0y = cy0 - r0;  hi0y = cy0 + r0;
    lo0z = cz0 - r0;  hi0z = cz0 + r0;
    lo1x = cx1 - r1;  hi1x = cx1 + r1;
    lo1y = cy1 - r1;  hi1y = cy1 + r1;
    lo1z = cz1 - r1;  hi1z = cz1 + r1;
    lo2x = cx2 - r2;  hi2x = cx2 + r2;
    lo2y = cy2 - r2;  hi2y = cy2 + r2;
    lo2z = cz2 - r2;  hi2z = cz2 + r2;
    lo3x = cx3 - r3;  hi3x = cx3 + r3;
    lo3y = cy3 - r3;  hi3y = cy3 + r3;
    lo3z = cz3 - r3;  hi3z = cz3 + r3;

    pkt = D_800A5E60;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)(base + 0xA3D2)) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        box[0].vx = mn; box[0].vy = mny;
        box[1].vx = mx; box[1].vy = mny;
        box[2].vx = mn; box[2].vy = mny;
        box[3].vx = mx; box[3].vy = mny;
        box[4].vx = mn; box[4].vy = my;
        box[5].vx = mx; box[5].vy = my;
        box[6].vx = mn; box[6].vy = my;
        box[7].vx = mx; box[7].vy = my;
        wy = wz >> 16;
        box[0].vz = wz;
        box[1].vz = wz;
        box[4].vz = wz;
        box[5].vz = wz;
        box[2].vz = wy;
        box[3].vz = wy;
        box[6].vz = wy;
        box[7].vz = wy;

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
        gte_stszotz(&g.otz);

        if (lim >= g.otz) {
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
                    nprim = part->nprim;
                    prim = (Prim *)part->prim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        gte_ldv3(va, vb, vc);
                        gte_rtpt();
                        gte_stflg(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip();
                            code = w & 7;
                            vd = vtx + (w & 0xFFF8);
                            gte_stopz(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
                                case 6:
                                case 7:
                                    /* ---------------- TRI (FT3 / GT3) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                        else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
                                        if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                        else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, zb;
                                            __asm__ __volatile__ ("" :: "r" (mny));
                                            if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; }
                                            else { za = g.sz1; if (za < g.sz2) za = g.sz2; }
                                            g.opz = za;

                                            f3 = 0; f2 = 0; f1 = 0; f0 = 0;

                                            vw = *(u32 *)va;
                                            vzw = *(u32 *)(va + 4);
                                            x0 = vw; y0 = vw >> 16; z0 = vzw;
                                            BOXTEST(f0, x0, y0, z0, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x0, y0, z0, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x0, y0, z0, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                            BOXTEST(f3, x0, y0, z0, lo3x, hi3x, lo3y, hi3y, lo3z, hi3z);
                                            vw = *(u32 *)vb;
                                            vzw = *(u32 *)(vb + 4);
                                            x1 = vw; y1 = vw >> 16; z1 = vzw;
                                            BOXTEST(f0, x1, y1, z1, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x1, y1, z1, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x1, y1, z1, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                            BOXTEST(f3, x1, y1, z1, lo3x, hi3x, lo3y, hi3y, lo3z, hi3z);
                                            vw = *(u32 *)vc;
                                            vzw = *(u32 *)(vc + 4);
                                            x2 = vw; y2 = vw >> 16; z2 = vzw;
                                            BOXTEST(f0, x2, y2, z2, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x2, y2, z2, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x2, y2, z2, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                            BOXTEST(f3, x2, y2, z2, lo3x, hi3x, lo3y, hi3y, lo3z, hi3z);

                                            if (f0 | f1 | f2 | f3) {
                                            u32 *otp;
                                            u32 rgbw;
                                                ATTEN(a0v, f0, x0, y0, z0, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x0, y0, z0, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x0, y0, z0, cx2, cy2, cz2, r2, r2lo);
                                                ATTEN3(a3v, f3, x0, y0, z0, cx3, cy3, cz3, r3, r3lo, r2, r2);
                                                CLAMP80(c0, a0v, a1v, a2v, a3v);
                                                ATTEN(a0v, f0, x1, y1, z1, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x1, y1, z1, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x1, y1, z1, cx2, cy2, cz2, r2, r2lo);
                                                ATTEN3(a3v, f3, x1, y1, z1, cx3, cy3, cz3, r3, r3lo, r3, r3);
                                                CLAMP80S(c1, a0v, a1v, a2v, a3v);
                                                ATTEN(a0v, f0, x2, y2, z2, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x2, y2, z2, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x2, y2, z2, cx2, cy2, cz2, r2, r2lo);
                                                ATTEN3(a3v, f3, x2, y2, z2, cx3, cy3, cz3, r3, r3lo, r2, r3);
                                                CLAMP80(c2, a0v, a1v, a2v, a3v);

                                                *(u32 *)&((PolyGT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyGT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyGT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = 0x34000000;
                                                rgbw = (c0 | cb) | (c0 << 8) | (c0 << 16);
                                                ((PolyGT3 *)pkt)->rgb0 = rgbw;
                                                rgbw = (c1 | cb) | (c1 << 8) | (c1 << 16);
                                                ((PolyGT3 *)pkt)->rgb1 = rgbw;
                                                __asm__ __volatile__ ("" :: "r" (c1));
                                                rgbw = (c2 | cb) | (c2 << 8) | (c2 << 16);
                                                ((PolyGT3 *)pkt)->rgb2 = rgbw;
                                                ((PolyGT3 *)pkt)->uv0 = tp[1];
                                                ((PolyGT3 *)pkt)->uv1 = tp[2];
                                                ((PolyGT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            } else {
                                            u32 *otp;
                                            u32 rgbw;
                                                *(u32 *)&((PolyFT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = tp[0] & 0xFF000000;
                                                ((PolyFT3 *)pkt)->rgbc = cb | 0x101010;
                                                ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                                ((PolyFT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x20;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    /* ---------------- QUAD (FT4 / GT4) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                    else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                        if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;

                                                f3 = 0; f2 = 0; f1 = 0; f0 = 0;

                                                vw = *(u32 *)va;
                                                vzw = *(u32 *)(va + 4);
                                                x0 = vw; y0 = vw >> 16; z0 = vzw;
                                                BOXTEST(f0, x0, y0, z0, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x0, y0, z0, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x0, y0, z0, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                BOXTEST(f3, x0, y0, z0, lo3x, hi3x, lo3y, hi3y, lo3z, hi3z);
                                                vw = *(u32 *)vb;
                                                vzw = *(u32 *)(vb + 4);
                                                x1 = vw; y1 = vw >> 16; z1 = vzw;
                                                BOXTEST(f0, x1, y1, z1, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x1, y1, z1, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x1, y1, z1, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                BOXTEST(f3, x1, y1, z1, lo3x, hi3x, lo3y, hi3y, lo3z, hi3z);
                                                vw = *(u32 *)vc;
                                                vzw = *(u32 *)(vc + 4);
                                                x2 = vw; y2 = vw >> 16; z2 = vzw;
                                                BOXTEST(f0, x2, y2, z2, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x2, y2, z2, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x2, y2, z2, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                BOXTEST(f3, x2, y2, z2, lo3x, hi3x, lo3y, hi3y, lo3z, hi3z);
                                                vw = *(u32 *)vd;
                                                vzw = *(u32 *)(vd + 4);
                                                x3 = vw; y3 = vw >> 16; z3 = vzw;
                                                BOXTEST(f0, x3, y3, z3, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x3, y3, z3, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x3, y3, z3, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                BOXTEST(f3, x3, y3, z3, lo3x, hi3x, lo3y, hi3y, lo3z, hi3z);

                                                if (f0 | f1 | f2 | f3) {
                                                u32 *otp;
                                                u32 rgbw;
                                                    ATTEN(a0v, f0, x0, y0, z0, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x0, y0, z0, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x0, y0, z0, cx2, cy2, cz2, r2, r2lo);
                                                    ATTEN3(a3v, f3, x0, y0, z0, cx3, cy3, cz3, r3, r3lo, r3, r3);
                                                    CLAMP80(c0, a0v, a1v, a2v, a3v);
                                                    ATTEN(a0v, f0, x1, y1, z1, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x1, y1, z1, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x1, y1, z1, cx2, cy2, cz2, r2, r2lo);
                                                    ATTEN3W(a3v, a2v, f3, x1, y1, z1, cx3, cy3, cz3, r3, r3lo, r3, r3);
                                                    CLAMP80S(c1, a0v, a1v, a2v, a3v);
                                                    ATTEN(a0v, f0, x2, y2, z2, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x2, y2, z2, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x2, y2, z2, cx2, cy2, cz2, r2, r2lo);
                                                    ATTEN3(a3v, f3, x2, y2, z2, cx3, cy3, cz3, r3, r3lo, r3, r3);
                                                    CLAMP80(c2, a0v, a1v, a2v, a3v);
                                                    ATTEN(a0v, f0, x3, y3, z3, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x3, y3, z3, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x3, y3, z3, cx2, cy2, cz2, r2, r2lo);
                                                    ATTEN3(a3v, f3, x3, y3, z3, cx3, cy3, cz3, r3, r3lo, r3, r3);
                                                    CLAMP80(c3, a0v, a1v, a2v, a3v);

                                                    *(u32 *)&((PolyGT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    gte_stsxy((long *)&((PolyGT4 *)pkt)->x3);
                                                    tp = (u32 *)prim->w0;
                                                    cb = 0x3C000000;
                                                    rgbw = c0 | cb; rgbw |= c0 << 8; rgbw |= c0 << 16;
                                                    ((PolyGT4 *)pkt)->rgb0 = rgbw;
                                                    rgbw = c1 | cb; rgbw |= c1 << 8; rgbw |= c1 << 16;
                                                    ((PolyGT4 *)pkt)->rgb1 = rgbw;
                                                    rgbw = (c2 | cb) | (c2 << 8) | (c1 << 16);
                                                    ((PolyGT4 *)pkt)->rgb2 = rgbw;
                                                    rgbw = (c3 | cb) | (c3 << 8) | (c1 << 16);
                                                    ((PolyGT4 *)pkt)->rgb3 = rgbw;
                                                    ((PolyGT4 *)pkt)->uv0 = tp[1];
                                                    ((PolyGT4 *)pkt)->uv1 = tp[2];
                                                    uvw = tp[3];
                                                    ((PolyGT4 *)pkt)->uv2 = uvw;
                                                    ((PolyGT4 *)pkt)->uv3 = uvw >> 16;
                                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0xC000000;
                                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                    pkt += 0x34;
                                                } else {
                                                u32 *otp;
                                                u32 rgbw;
                                                    *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    tp = (u32 *)prim->w0;
                                                    cb = tp[0] & 0xFF000000;
                                                    ((PolyFT4 *)pkt)->rgbc = cb | 0x101010;
                                                    ((PolyFT4 *)pkt)->uvc0 = tp[1];
                                                    ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                    uvw = tp[3];
                                                    ((PolyFT4 *)pkt)->uv2 = uvw;
                                                    ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                    pkt += 0x28;
                                                }
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
    }
    D_800A5E60 = pkt;
}
