/* func_8001EFE0 - src/800.c (main, -O2), 468 ins.  MATCH (match_one closeness 0,
 * rtu_match.py --tu src/800.c MATCH).
 *
 * Sprite/billboard emitter, the direct sibling of func_8001EA14 (which sits
 * immediately above it in the TU and is already banked): build a GsCOORDINATE2
 * on the stack (flg@0x58, coord@0x5C, workm@0x7C, rotate@0x9C, super@0xA0) with
 * RotMatrixZYX/ScaleMatrix/GsGetLs (func_80049CAC / func_8004901C /
 * func_800547D8), write coord+workm back to arg0+0x34/+0x54, RTPS the origin,
 * then walk a 12-byte cell list (stride 0xC, low byte 8 = skip, 0xFF = end)
 * emitting one POLY_FT4 (0x28) per cell out of the D_800A5E60 bump allocator and
 * addPrim()ing it onto D_800A6610 + (*(u16 *)(D_800AF630+0xA3D2) << 14).
 *
 * SYMBOL AUDIT (SYS law 1c, done after MATCH): the 9 external symbols in this
 * file are exactly the 9 in asm/nonmatchings/800/func_8001EFE0.s, in the same
 * order -- %hi/%lo(D_800AF630), jal func_80049CAC, jal func_8004901C,
 * jal func_800547D8, jal func_80021174, %hi/%lo(D_800A6610),
 * %hi/%lo(D_800A5E60) x2, %hi/%lo(D_80072784) x2, jal func_8001F730.
 *
 * ===========================================================================
 * HISTORY: three earlier agents left this at 172, then 89, then 14, and the
 * closeness-14 header (preserved below) declared all three remaining clusters
 * "[permuter]-class, not reachable from C".  ALL THREE WERE REACHABLE.  The
 * unlock was reading the already-MATCHED same-TU siblings func_8001DA34 and
 * func_8001EA14 instead of sweeping spellings: every lever below is a spelling
 * one of those two already uses.  14 -> 0 in three edits.
 * ===========================================================================
 *
 * N1. THE addPrim TAIL: SPLIT THE OT ADDRESS SO ONE HALF SITS BETWEEN THE TWO
 *     PINNED MASK CONSTANTS  (14 -> 12; target order is `lui a1;ori a1;
 *     sll a0,s4,2;lui a2,0xff00`, every draft emitted the two `lui`s adjacent).
 *     A pinned hard-reg SET is placed FIRST in its block (cookbook 194-A), so
 *     with `m24`/`mFF` both pinned NO source order of the two assignments can
 *     separate them -- moving `mFF = 0xFF000000;` after the `ot = ...`
 *     statement is completely inert, and a scheduling fence there (the
 *     func_8001DA34 spelling) is WORSE (+3) because this target wants
 *     `lui a2` BEFORE the `lw`/`addu` half, not after it.  The lever is to give
 *     `ot` TWO assignments and let the second mask land between them:
 *         m24 = 0xFFFFFF;
 *         ot  = (u32 *)(d * 4);
 *         mFF = 0xFF000000;
 *         ot  = (u32 *)((s32)ot + (s32)otbase);
 *     GENERAL: when two pinned constants must be separated by a third insn,
 *     do not move the constants -- SPLIT the insn that has to go between them.
 *
 * N2. A SCHEDULING FENCE AFTER THE tpage STORE  (12 -> 9).  The target issues
 *     `sh $v0,0x16($s0)` BEFORE the `andi $a0,$s6,0x40` / `lbu $v1,7($s0)` pair;
 *     every draft sank it 3 slots because gcc hoists the `q[7]` read-modify-write
 *     over it.  One `__asm__ __volatile__("");` between
 *         *(u16 *)(q + 0x16) = tpage;
 *         q[7] |= (attr & 0x40) >> 6;
 *     pins the store above the pair.  (func_8001DA34 has the identical statement
 *     pair and needs NO fence -- there `tpage` stays in a register and the store
 *     has no reload after it, so its priority is low; here the very next
 *     statement re-reads `*(u16 *)(q + 0x16)` from memory, which is what makes
 *     the store's position observable at all.)  A fence one statement LATER, or
 *     moving the `|=` after the q[0xC] statement, both explode (+19 / +158).
 *
 * N3. THE TWO-SVECTOR FILL AT sp+0x48/0x50 IS A LOCAL-ALLOC DENSITY PROBLEM,
 *     NOT A STATEMENT-ORDER ONE  (9 -> 0).  This is the block three agents
 *     filed as unreachable after sweeping all 720 statement orders; a re-sweep
 *     of all 720 x {2-operand,3-operand ldv3} x {memory clobber on/off} on the
 *     fixed base confirms the order floor is 9 and the macro arity is inert.
 *     The target holds FIVE values live here (e->u $v0, sz $v1, e->h $a0,
 *     e->v $a1, e->w $v0-after-e->u-dies) and stores e->h and e->v LAST; every
 *     C spelling coalesced e->h into $v0 and only ever kept FOUR.  The lever is
 *     cookbook 419 -- buy references instead of a register -- with ONE zero-byte
 *     asm after the group:
 *         v0.vx = *(u16 *)(p + 8);
 *         vv2   = *(u16 *)(p + 0xA);   v0.vy = vv2;
 *         v0.vz = sz;
 *         vw    = rec >> 16;           v1.vx = vw & 0xFF;
 *         vh    = rec >> 24;           v1.vy = vh;
 *         v1.vz = sz;
 *         __asm__("" : : "r"(vh), "r"(vv2), "r"(vw));
 *     Three separate facts, each measured by removing it:
 *       (a) holding e->h and e->v alone (`"r"(vh), "r"(vv2)`) is worth 9 -> 2:
 *           it buys them $a0/$a1 and the whole register assignment becomes the
 *           target's.  Holding only one of the two is worth nothing (11 / 12),
 *           and two SEPARATE one-operand asms cost 99 (each is an independent
 *           volatile barrier and they serialise the block).
 *       (b) adding `"r"(vw)` to the SAME asm lengthens the `(rec>>16)` chain by
 *           one and flips `srl $v0,$s1,16` ahead of `lhu $a1,0($s3)` -- but then
 *           the `andi` rides up with the `srl` and lands one slot too early.
 *       (c) SPLITTING the shift from its mask -- `vw = rec >> 16;` held by the
 *           asm, `v1.vx = vw & 0xFF;` as its own statement -- separates their
 *           priorities so the `lhu` fits between them.  That is the last 2.
 *     The statement ORDER that works is the plain ascending one (vx,vy,vz then
 *     vx,vy,vz), which the 720-sweep had scored 12 and thereby hidden: the
 *     sweep was over the wrong axis, so its flat plateau proved only that the
 *     residual was an ALLOCATION fact (func_8001EA14's own METHOD NOTE says
 *     exactly this).  Placement of the `vw`/`vh` statements inside the group is
 *     inert once (a)-(c) hold (6 placements measured, all 0 or all 2).
 *
 * ===========================================================================
 * LEVERS INHERITED FROM THE 89 -> 14 PASS (all re-measured, all still load-bearing)
 * ===========================================================================
 *  - POLY_FT4 vertex stores go per-VERTEX (x1=x0+w; y1=y0; x2=x0; y2=y0+h),
 *    not in copy groups: that is the -1 length drift and the 42-ins tail.
 *  - `u16 tpage` (NOT u32): a single-bit mask-shift `(sy & 0x100) >> 4` is
 *    fixed by the DESTINATION'S WIDTH, not by the expression.  Ten spellings
 *    (incl. 432's shift-pair) all converge on srl;andi with a 32-bit temp;
 *    narrowing the accumulator carries a 0xFFFF mask into the IOR tree and the
 *    single-bit term stops folding.  This is why two agents filed it [permuter].
 *  - UV copies in ascending offset order (0x14,0x15,0x1C,0x1D,0x24,0x25).
 *  - SetRotMatrix/SetTransMatrix as TWO asm blocks clobbering only $12/$13/$14
 *    (a phantom "$2" clobber evicts `abr` from $v0).
 *  - The sp+0x10 unit matrix initialised in plain field order.
 *  - tpBb,tpAb,tpA,tpB DECLARED in that order but ASSIGNED tpA..tpBb: the
 *    global-alloc tie between four equal allocnos breaks on pseudo number, and
 *    it decides whether jump2 cross-jumps the two tails.
 *  - `t14` as an s32 temp so convert_to_integer does not shorten
 *    q[0x14] = q[0x0C] + ((rec>>16)&0xFF) into QImode and drop its `andi`.
 *  - ot pinned to $4 (invariant_p refuses to hoist &otbase[d] out of a loop with
 *    a call while the address holds a call-used hard reg), m24 to $5, mFF to $6.
 *    Unpinning any of the three costs 200+ instructions (re-measured: mFF alone
 *    -> 238, m24 alone -> 245, both -> 242, ot alone -> 15).
 *  - A 4-byte struct local is BLKmode, so assign_stack_local gives it 8-byte
 *    BIGGEST_ALIGNMENT: xy0/xy1 must be s32 or the frame goes 0x130 -> 0x138.
 *  - fold reassociates `(x<<9)|CONST|var`, so the four getTPage bases must be
 *    explicit pre-loop vars or loop.c hoists only the shift.
 *  - `(u8)` casts on the s32 mode/abr keep the two `andi 0xFF` zero-extends.
 *
 * BANK NOTE: src/800.c's neighbouring func_8001EA14 already defines its own
 * suffixed SV_/MT_/Ft4_ typedefs and gte_* macros, so the _8001EFE0-suffixed
 * ones below do not collide; rtu_match.py --tu src/800.c compiles clean.
 */
#include "common.h"

/* ---- local PsyQ-shaped types (suffixed: src/800.c has no file-scope MATRIX) ---- */
typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX_8001EFE0;       /* 0x20 */
typedef struct { s16 vx, vy, vz, pad; } SVEC_8001EFE0;           /* 0x08 */
typedef struct { s32 vx, vy, vz, pad; } VEC_8001EFE0;            /* 0x10 */
typedef struct {                                                 /* 0x50 */
    u32 flg;
    MATRIX_8001EFE0 coord;
    MATRIX_8001EFE0 workm;
    void *rotate;
    void *super;
    void *sub;
} COORD2_8001EFE0;
typedef struct { u16 x, y, z, w; } COL_8001EFE0;                 /* align 2 -> lwl/lwr (§48-C2) */
typedef struct { u16 vx, vy; } XY_8001EFE0;                      /* 0x04 */

/* ---- GTE inline macros (house spelling, suffixed to avoid TU collisions) ---- */
#define SRM_8001EFE0(r0) __asm__ volatile (      \
    "lw $12, 0( %0 );"  "lw $13, 4( %0 );"       \
    "ctc2 $12, $0;"     "ctc2 $13, $1;"          \
    "lw $12, 8( %0 );"  "lw $13, 12( %0 );"      \
    "lw $14, 16( %0 );"                          \
    "ctc2 $12, $2;"     "ctc2 $13, $3;" "ctc2 $14, $4"   \
    : : "r"( r0 ) : "$12", "$13", "$14" )

#define STM_8001EFE0(r0) __asm__ volatile (      \
    "lw $12, 20( %0 );" "lw $13, 24( %0 );"      \
    "ctc2 $12, $5;"     "lw $14, 28( %0 );"      \
    "ctc2 $13, $6;"     "ctc2 $14, $7"           \
    : : "r"( r0 ) : "$12", "$13", "$14" )

#define ldv0_8001EFE0(r0) __asm__ volatile (     \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    : : "r"( r0 ) )

#define ldv3_8001EFE0(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define rtps_8001EFE0()  __asm__ volatile ("nop;nop;rtps")
#define rtpt_8001EFE0()  __asm__ volatile ("nop;nop;rtpt")

#define stsxy_8001EFE0(r0) __asm__ volatile (    \
    "swc2 $14, 0( %0 )"                          \
    : : "r"( r0 ) : "memory" )

#define stsxy0_8001EFE0(r0) __asm__ volatile (   \
    "swc2 $12, 0( %0 )"                          \
    : : "r"( r0 ) : "memory" )

#define stsxy1_8001EFE0(r0) __asm__ volatile (   \
    "swc2 $13, 0( %0 )"                          \
    : : "r"( r0 ) : "memory" )

#define stflg_8001EFE0(r0) __asm__ volatile (    \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    : : "r"( r0 ) : "$12", "memory" )

#define stsz_8001EFE0(r0) __asm__ volatile (     \
    "swc2 $19, 0( %0 )"                          \
    : : "r"( r0 ) : "memory" )

#define stszotz_8001EFE0(r0) __asm__ volatile (  \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    : : "r"( r0 ) : "$12", "memory" )

extern u8 D_800AF630[];
extern u8 D_800A6610[];
extern u8 *D_800A5E60;
extern u32 D_80072784;
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004901C(void *a0, void *a1);
extern void func_800547D8(s32 a0, void *a1);
extern s32 func_80021174(s32 a0, s32 a1);
extern void func_8001F730(s32 a0, void *a1, void *a2);

void func_8001EFE0(s32 arg0)
{
    MATRIX_8001EFE0 um;       /* sp+0x10 */
    SVEC_8001EFE0 sv;         /* sp+0x30 */
    VEC_8001EFE0 scale;       /* sp+0x38 */
    SVEC_8001EFE0 v0;         /* sp+0x48 */
    SVEC_8001EFE0 v1;         /* sp+0x50 */
    COORD2_8001EFE0 c2;       /* sp+0x58 */
    MATRIX_8001EFE0 ls;       /* sp+0xA8 */
    COL_8001EFE0 col;         /* sp+0xC8 */
    s32 flag;                 /* sp+0xD0 */
    s32 sz;                   /* sp+0xD4 */
    s32 otz;                  /* sp+0xD8 */
    MATRIX_8001EFE0 *mp;
    s32 xy0;                  /* sp+0xDC */
    s32 xy1;                  /* sp+0xE0 */
    u32 attr;
    u8 *base;
    u8 *p;
    u8 *q;
    s32 shift;
    u32 *otbase;
    u32 tpBb;
    u32 tpAb;
    u32 tpA;
    u32 tpB;
    s32 d;
    u32 pri;
    s32 mode;
    s32 abr;
    u32 rec;
    u16 sx, sy;
    u16 tpage;
    s32 vv;
    u16 tv;
    u32 cy, cbase;
    u32 tag;
    s32 t14;
    u16 vv2;
    s32 vh;
    s32 vw;
    register u32 *ot __asm__("$4");
    register u32 m24 __asm__("$5");
    register u32 mFF __asm__("$6");

    attr = *(u32 *)(arg0 + 4);
    c2.super = *(void **)(arg0 + 0x78);
    c2.flg = 0;
    base = D_800AF630;
    if (*(u16 *)(arg0 + 0x2C) & 1) {
        *(u16 *)(arg0 + 0x2C) &= 0xFFFE;
        c2.coord = *(MATRIX_8001EFE0 *)(arg0 + 0x34);
    } else {
        func_80049CAC(arg0 + 0x10, (s32)&c2.coord);
        c2.coord.t[0] = *(s16 *)(arg0 + 8);
        c2.coord.t[1] = *(s16 *)(arg0 + 0xA);
        c2.coord.t[2] = *(s16 *)(arg0 + 0xC);
    }
    scale.vx = *(s16 *)(arg0 + 0x18);
    scale.vy = *(s16 *)(arg0 + 0x1A);
    scale.vz = *(s16 *)(arg0 + 0x1C);
    func_8004901C(&c2.coord, &scale);
    mp = &ls;
    func_800547D8((s32)&c2, mp);
    *(MATRIX_8001EFE0 *)(arg0 + 0x34) = c2.coord;
    *(MATRIX_8001EFE0 *)(arg0 + 0x54) = c2.workm;

    p = *(u8 **)(arg0 + 0x20);
    if (p != NULL && func_80021174(*(s32 *)(arg0 + 0x28), (s32)&c2.workm.t[0]) != 0) {
        SRM_8001EFE0(mp);
        STM_8001EFE0(mp);
        sv.vx = sv.vy = sv.vz = 0;
        ldv0_8001EFE0(&sv);
        rtps_8001EFE0();
        stsxy_8001EFE0(&sv);
        stflg_8001EFE0(&flag);
        stsz_8001EFE0(&sz);
        stszotz_8001EFE0(&otz);
        if ((flag & ~0x1000) == 0) {
            d = otz + 1;
            otbase = (u32 *)&D_800A6610[*(u16 *)(base + 0xA3D2) << 14];
            pri = *(u16 *)(arg0 + 0x2E);
            if (pri & 0xC000) {
                if ((pri & 0xC000) == 0xC000) {
                    d -= (pri & 0xFFF);
                    if (d < 0) {
                        d = 0;
                    }
                } else {
                    d += (pri & 0xFFF);
                }
            }
            if ((u32)d < 0x1000) {
                if (*(u16 *)(arg0 + 0x2C) & 0x80) {
                    col = *(COL_8001EFE0 *)(*(u8 **)(arg0 + 0x80));
                } else {
                    col.x = col.y = col.z = 0x80;
                }
                mode = (attr >> 24) & 3;
                um.m[0][0] = *(u16 *)(arg0 + 0x18);
                um.m[0][1] = 0;
                um.m[0][2] = 0;
                um.m[1][0] = 0;
                um.m[1][1] = *(u16 *)(arg0 + 0x1A);
                um.m[1][2] = 0;
                um.m[2][0] = 0;
                um.m[2][1] = 0;
                um.m[2][2] = 0x1000;
                um.t[2] = 0;
                um.t[1] = 0;
                um.t[0] = 0;
                shift = 2 - mode;
                abr = (attr >> 28) & 3;
                SRM_8001EFE0(&um);
                STM_8001EFE0(&um);
                tpA = ((u8)mode << 9) | ((u8)abr << 7);
                tpB = ((u8)mode << 7) | ((u8)abr << 5);
                tpAb = ((u8)mode << 9) | 0x80;
                tpBb = ((u8)mode << 7) | 0x20;
                do {
                    rec = *(u32 *)p;
                    if ((rec & 0xFF) != 8) {
                        q = D_800A5E60;
                        sx = *(u16 *)(p + 4);
                        sy = *(u16 *)(p + 6);
                        D_800A5E60 = q + 0x28;
                        q[3] = 9;
                        q[7] = 0x2C;
                        if (attr & 0x40000000) {
                            q[7] = 0x2E;
                            if ((u32)(*(u8 *)(D_80072784 + 4) - 1) < 2) {
                                tpage = (tpA | ((sy & 0x300) >> 3)) | ((sx & 0x3C0) >> 6);
                            } else {
                                tpage = (tpB | ((sy & 0x100) >> 4)) | ((sx & 0x3C0) >> 6) |
                                        ((sy & 0x200) << 2);
                            }
                        } else {
                            if ((u32)(*(u8 *)(D_80072784 + 4) - 1) < 2) {
                                tpage = (tpAb | ((sy & 0x300) >> 3)) | ((sx & 0x3C0) >> 6);
                            } else {
                                tpage = (tpBb | ((sy & 0x100) >> 4)) | ((sx & 0x3C0) >> 6) |
                                        ((sy & 0x200) << 2);
                            }
                        }
                        *(u16 *)(q + 0x16) = tpage;
                        __asm__ __volatile__("");
                        q[7] |= (attr & 0x40) >> 6;
                        q[0x0C] = (sx - ((*(u16 *)(q + 0x16) & 0xF) << 6)) << shift;
                        vv = sy;
                        if (*(u16 *)(q + 0x16) & 0x10) {
                            tv = vv - 0x100;
                        } else {
                            tv = vv;
                        }
                        q[0x0D] = tv;
                        t14 = q[0x0C] + ((rec >> 16) & 0xFF);
                        q[0x14] = t14;
                        q[0x15] = q[0x0D];
                        q[0x1C] = q[0x0C];
                        q[0x1D] = q[0x0D] + (rec >> 24);
                        q[0x24] = q[0x14];
                        q[0x25] = q[0x1D];
                        cy = (rec >> 8) & 0xFF;
                        cbase = (cy + 0x100) << 6;
                        if (cy < 0xE0) {
                            *(u16 *)(q + 0xE) = cbase | 0x16;
                        } else {
                            *(u16 *)(q + 0xE) = cbase | 0x10;
                        }
                        q[4] = col.x;
                        q[5] = col.y;
                        q[6] = col.z;
                        v0.vx = *(u16 *)(p + 8);
                        vv2 = *(u16 *)(p + 0xA);
                        v0.vy = vv2;
                        v0.vz = sz;
                        vw = rec >> 16;
                        v1.vx = vw & 0xFF;
                        vh = rec >> 24;
                        v1.vy = vh;
                        v1.vz = sz;
                        __asm__("" : : "r"(vh), "r"(vv2), "r"(vw));
                        ldv3_8001EFE0(&v0, &v1, &v1);
                        rtpt_8001EFE0();
                        stsxy0_8001EFE0(&xy0);
                        stsxy1_8001EFE0(&xy1);
                        *(u16 *)(q + 8) = *(u16 *)&xy0 + sv.vx;
                        *(u16 *)(q + 0xA) = *((u16 *)&xy0 + 1) + sv.vy;
                        *(u16 *)(q + 0x10) = *(u16 *)(q + 8) + *(u16 *)&xy1;
                        *(u16 *)(q + 0x12) = *(u16 *)(q + 0xA);
                        *(u16 *)(q + 0x18) = *(u16 *)(q + 8);
                        *(u16 *)(q + 0x1A) = *(u16 *)(q + 0xA) + *((u16 *)&xy1 + 1);
                        *(u16 *)(q + 0x20) = *(u16 *)(q + 0x10);
                        *(u16 *)(q + 0x22) = *(u16 *)(q + 0x1A);
                        if (*(u32 *)(arg0 + 4) & 0x8000000) {
                            func_8001F730(arg0 + 0x10, &sv, q);
                        }
                        m24 = 0xFFFFFF;
                        ot = (u32 *)(d * 4);
                        mFF = 0xFF000000;
                        ot = (u32 *)((s32)ot + (s32)otbase);
                        tag = *(u32 *)q;
                        *(u32 *)q = (tag & mFF) | (*ot & m24);
                        *ot = (*ot & mFF) | ((u32)q & m24);
                    }
                    p += 12;
                } while ((rec & 0xFF) != 0xFF);
            }
        }
    }
}
