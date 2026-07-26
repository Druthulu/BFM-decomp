#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"

/* ===========================================================================
 * func_8017C954 -- 1,194 ins, ov_SC06_029 (behemoth #5).   *** MATCH ***
 *
 * STATUS (2026-07-25, session 20, gcc-2.7.2 pinned triple):
 *   python3 tools/match_one.py func_8017C954 --c <this file> \
 *     --asm-subdir asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017AE2C
 *   -> MATCH (1194 ins)
 *   Independent re-check (private pipeline .run/giants/c954_cc.sh + c954_full.py):
 *     mine=1194 target=1194  0 mismatched
 *   b3_align: register-MASKED 1194/1194 = 100.0%, register-KEPT 1194/1194 = 100.0%
 *   The compiler-generated .rodata jump table is byte-correct too:
 *     offsets 0x980 0x980 0xBE4 0xEB8 0x5D4 0x5D4 0x794 0x794
 *     == target jtbl_801DB70C  (symcheck's only diff is the jtbl NAME, which is a
 *     splat rodata-carve integration item, not a code difference).
 *   match_one is the CANDIDATE gate; the whole-binary SHA1 rebuild (G3/P9) is the
 *   arbiter and has NOT been run here (the task forbade touching the build tree).
 *   ONE register pin-equivalent survives: a single zero-byte
 *   `__asm__ __volatile__ ("" ::: "$3")` -- see L1 below.  It emits
 *   `#APP / <empty> / #NO_APP`, i.e. NO instruction; the compile is 1194 EXACT.
 *
 * WHAT IT IS: the "constant-colour + subtractive overlay quad" variant of the
 *   mesh-renderer family.  Skeleton is byte-for-byte the MATCHED unlit base
 *   func_8017CA80 (952 ins, src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c):
 *   same 3-call prologue (func_800491EC / func_800547D8 / func_80052E38), same
 *   Part[] outer loop (stride 0x14) with the 8-corner AABB rtpt/rtps + otz +
 *   screen-bbox reject, same Prim[] inner loop (stride 0xC) with
 *   rtpt/stflg/nclip/stopz, same OT insert, same `D_800A5E60 = pkt`.
 *
 *   THE TWO DELTAS vs the base (952 -> 1194 = +242 ins):
 *
 *   (1) PROLOGUE, +14 ins: two replicated grey colour words derived from the
 *       global s32 D_801DCCA0 (a fade/flash level, 0..0x80):
 *           d    = D_801DCCA0;
 *           colA = (d << 16) | (d << 8) | d;          -> stack slot 0x108
 *           e    = d * 2;  if (e > 0xFF) e = 0xFF;    (UNSIGNED: `sltiu ,0x100`)
 *           colB = (e << 16) | (e << 8) | e;          -> stack slot 0x110
 *       Placement is load-bearing: `pkt`, `ot`, `d`, `colA`, `e` and the clamp
 *       `if` are all in basic block 1; `part`, `nparts`, `vtx` are read AFTER
 *       the clamp branch (gcc's sched cannot cross the branch, so the emission
 *       order reads the source order back directly).
 *
 *   (2) THE SWITCH GAINS A FIFTH ARM, +228 ins.  The base maps
 *       {4,5}->POLY_F3 {6,7}->POLY_FT3 {0,1}->POLY_F4 {2,3}->POLY_FT4.
 *       Here `case 2` and `case 3` SPLIT (verified against the real
 *       jtbl_801DB70C in asm/ov_SC06_029/data/tail21.data.s):
 *         [0][1] -> arm C  POLY_F4   (unchanged)
 *         [2]    -> arm D  POLY_FT4  (unchanged -- it even KEEPS the now-dead
 *                                     `if (code == 3) g.opz = za + 0x200;`)
 *         [3]    -> arm E  NEW
 *         [4][5] -> arm A  POLY_F3   (unchanged)
 *         [6][7] -> arm B  POLY_FT3  (unchanged)
 *       Arm E emits TWO packets per primitive:
 *         P1 = POLY_FT4 (0x28, OT tag 0x9000000) -- same geometry/UVs as arm D
 *              but `rgbc = colA | 0x2E000000` (GPU code 0x2E = textured quad,
 *              semi-transparent) INSTEAD of tp[0], so tp[0] is never read;
 *         P2 = a 7-word (0x1C, OT tag 0x6000000) overlay:
 *              +0x00 tag, +0x04 0xE1000040 (GPU E1 draw-mode: semi-transparency
 *              mode 2 = B-F, subtractive), +0x08 `colB | 0x2A000000`
 *              (GPU 0x2A = flat quad, semi-transparent), +0x0C..+0x18 the four
 *              screen xy words.  `pkt[3] = 6;` writes the P_TAG len byte by hand
 *              before the tag word overwrites it (a PsyQ `setlen()` habit).
 *       Arm E also differs from arm D in HOW it gets the 4th vertex:
 *         `vv[3] = *(SVECTOR2 *)vd;  gte_ldv0(&vv[3]);`
 *       (SVECTOR2 has 2-byte alignment, so mips.c's `output_block_move`
 *       (align < 4) emits the lwl/lwr + swl/swr pair the target has), and it
 *       stsxy's the 4th projected vertex into `tmpxy[3]` rather than straight
 *       into the packet, because both packets need all four xy words.
 *
 * FRAME (0x298, measured, matches exactly):
 *   0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 vv[4] |
 *   0xC0 mtx | 0xE0 g{otz,flag,opz,sz0..sz3} | 0x100..0x26F = 46 EIGHT-BYTE
 *   spill slots | 0x270..0x294 saved regs (s0-s7, fp, ra).
 *   The 0xA0 block is a NEW 0x20-byte local declared between `sxy` and `mtx`;
 *   only vv[3] (0xB8) is ever touched -- an array element, so gcc allocates the
 *   whole 0x20 (Sec.79 frame-slot oracle: this is what puts mtx at 0xC0 and g at
 *   0xE0 instead of the base's 0xA0/0xC0).
 *   Spill order (Sec.79 = declaration order): lim 0x100, colA 0x108, colB 0x110,
 *   nprim 0x118, nparts 0x120, part 0x128, i 0x260, (part+0xC giv) 0x268.
 *   NOTE nprim BEFORE nparts -- that is why `u32 nprim;` is declared ahead of
 *   `s32 nparts;` here, unlike the base.  (Measured: +3 structural ins.)
 *
 * ---------------------------------------------------------------------------
 * THE FIVE LEVERS THAT TOOK 1129 mismatched -> MATCH.  Each byte-measured.
 * Metric quoted is `c954_reg.py` register-KEPT aligned-identical %, which is
 * length-drift-proof (match_one's index-wise count is useless while len != 1194).
 *
 * L1  ONE ZERO-BYTE $v1 CONFLICT DIAL, first statement after arm E's y min/max:
 *         __asm__ __volatile__ ("" ::: "$3");
 *     62.6% -> 94.9% kept.  THE dominant lever; everything else is small.
 *     WHY (this is the reusable finding):
 *       my/mny/mx/mn are four s16 GLOBAL allocnos (pseudos 103..106, refs 103,
 *       live length 245..282).  In the target they are granted
 *       my=$a2 mny=$a3 mx=$t0 mn=$t1 -- exactly what the MATCHED 952-ins base
 *       compiles to.  Adding the 5th arm makes `my` and `mny` LOSE their hard-reg
 *       conflict with $v1 and instead acquire a COPY PREFERENCE for it
 *       (`;; 103 conflicts: ... 2 12 29` / `;; 103 preferences: 3`, greg dump),
 *       so `my` takes $v1 and the whole quad slides one slot down the
 *       reg_alloc_order (v1,a2,a3,t0 instead of a2,a3,t0,t1).  That single slide
 *       renames ~40% of every switch arm.
 *       Bisected to the instruction: with arm E truncated after its y min/max
 *       the conflict is present; adding ANY block after it (even
 *       `if (!(g.flag & 0x7F85E000)) pkt += 4;`) removes it.  A 5th arm that is
 *       *small* (or a verbatim duplicate of arm D) does not break it -- so it is
 *       the SIZE/shape of arm E, not the arm count.
 *       Only "$3" works: a bare `__asm__ volatile("")`, a "$2"/"$4" clobber or a
 *       "memory" clobber are all no-ops here (measured).  Six "natural" spellings
 *       were tried and all failed (see the report's do-not-re-buy list), so this
 *       dial stands in for whatever the original source did to keep $v1 busy.
 *
 * L2  `u32 nprim;` DECLARED BEFORE `s32 nparts;`   -> +3 structural ins,
 *     94.9% -> 95.2% kept.  Sec.79: spill slots are handed out in pseudo-number
 *     (= declaration) order, and the target has nprim at 0x118, nparts at 0x120.
 *
 * L3  ARM E's PACKET-1 STORE ORDER: the four xy words, then `tp`, then rgbc,
 *     then the three uv words.   95.2% -> 95.5% kept.
 *
 * L4  TWO SEPARATELY-SCOPED `otp`s IN ARM E (one per OT insert), not one
 *     function-scope-style `otp` assigned twice.        95.5% -> 97.3% kept AND
 *     1202 -> 1194 ins (the whole remaining LENGTH DRIFT).
 *     This is the family's L1 lever (Sec.76) applied inside one arm:
 *     `local-alloc.c:472` accepts an allocno only if REG_BASIC_BLOCK >= 0 &&
 *     REG_N_DEATHS == 1.  One `otp` with two OT inserts has 2 deaths -> GLOBAL
 *     allocno -> `combine_regs` (local-alloc.c:1825) cannot tie the
 *     `(za>>2)<<2` shift chain into it, so the chain needs a separate $v0 scratch
 *     -- and $v0 is exactly the register the four `lw/sw` xy pairs are using, so
 *     the scheduler can no longer slot `sra/sll/addu` into their load-delay slots
 *     and maspsx emits three `nop`s instead.  Per-insert scoping makes each a
 *     1-death, 1-block pseudo, the chain ties in place in $a0, and the three nops
 *     turn back into the target's `sra $a0 / sll $a0 / addu $a0,$a0,$s0`.
 *     (The first insert also has to read `za`, not `g.opz`: `g` has its address
 *     taken by the gte macros, so `g.opz` would have to be RE-LOADED after the
 *     aliasing `pkt` stores and could not be hoisted at all.)
 *
 * L5  ARM E's PACKET-2 STORE ORDER: len byte, +0x08 colour word, +0x0C xy0,
 *     +0x04 0xE1000040, then +0x10/+0x14/+0x18.        37 -> 28 mismatched.
 *     The odd interleave is what keeps the two-insn 0xE1000040 constant from
 *     being materialised early: with the store any earlier, `lui $a1` gets
 *     scheduled into the packet-1 load-delay slot at tgt[1093] where the target
 *     has a real `nop` (Sec.78 -- a nop the target has and you lack is a
 *     register-liveness fact).
 *
 * L6  ZERO `__asm__ volatile ("")` LIVE-LENGTH SLIDERS.  The matched 952-ins base
 *     ships ONE (Sec.47, to split the &g.sz1 / &g.sz2 allocno tie).  Here the
 *     correct count is NONE: 0 -> MATCH, 2 -> 28, 3 -> 10, 1 and 5 -> length -1.
 *     Same mechanism, opposite sign: `allocno_compare` (global.c:594) gives the
 *     three &g.szN pointers refs 16 and lengths within 2 of each other, so
 *     int(4*16*10000/L) puts them 1 apart and every static instruction added
 *     anywhere in the outer loop re-ranks them.  The last 28 mismatched
 *     instructions were exactly this: a 3-cycle on {vtx, &g.flag, 0x7F85E000}
 *     ($s7/$s5/$s6 -> $s6/$s7/$s5) plus a swap on {&g.sz1, &g.sz2} ($s1/$t8).
 *
 * ===== TRIED AND REJECTED (byte-measured; scoped to the base named) =====
 *   On the 1129 base: all 24 permutations of `s16 my, mny, mx, mn` (ALL exactly
 *   neutral -- the four are not tied); 9 positions for that declaration in the
 *   decl list (all neutral); colA/colB declared first / last / next to d,e;
 *   `ot` hoisted before the 3 calls (worse) or moved after the clamp (-1 ins,
 *   much worse); `e = d << 1`; reading nprim before prim; dedicated arm-E
 *   min/max variables (function-scope, block-scope, x-only, y-only -- all
 *   neutral or worse); a reversed y comparison; a `t32` temp for tmpxy[2];
 *   `gte_ldv0(vd)` instead of the vv[3] block copy (much worse -- and it loses
 *   the target's lwl/lwr).  Arm E's y-block BEFORE its x-block reaches the right
 *   REGISTERS (a2,a3,t0,t1) but with x and y swapped, and costs +7 ins: it was
 *   the diagnostic that proved the residual was one allocno-slide, not 40 bugs.
 *   On the MATCH base: removing the "$3" dial, or replacing it with "" / "$2" /
 *   "memory", drops to 1182 ins / ~1085 mismatched.
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

void func_8017C954(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;   /* TU-visible spelling (engine_core.h + ov_SC01_000.c col-0); unsigned access forced at use — §8d sub-class (b) */
    extern s32 D_801DCCA0;     /* fade/flash level driving both overlay colours */

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    SVECTOR2 vv[4];            /* 0xA0..0xBF; only vv[3] is used (arm E vertex copy) */
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    u32 colA;
    u32 colB;
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
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    s32 d;
    u32 e;

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    d = D_801DCCA0;
    colA = (d << 16) | (d << 8) | d;
    e = d * 2;
    if (e > 0xFF) e = 0xFF;
    colB = (e << 16) | (e << 8) | e;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);

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
                if ((s16)mxc >= -0x78 && (s16)mnc < 0x79) {
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
                        gte_stflg(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip();
                            code = w & 7;
                            vd = vtx + (w & 0xFFF8);
                            gte_stopz(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
                                case 4:
                                case 5:
                                    gte_stsxy3_f3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
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
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code != 4) g.opz = za + 0x200;
                                            ((PolyF3 *)pkt)->rgbc = prim->w0;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x14;
                                        }
                                    }
                                    break;
                                case 6:
                                case 7:
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
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
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            u32 *tp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code == 7) g.opz = za + 0x200;
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT3 *)pkt)->rgbc = tp[0];
                                            ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
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
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyF4 *)pkt)->x3);
                                        if (((PolyF4 *)pkt)->x3 < mn) mn = ((PolyF4 *)pkt)->x3;
                                        else if (mx < ((PolyF4 *)pkt)->x3) mx = ((PolyF4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyF4 *)pkt)->y3 < mny) mny = ((PolyF4 *)pkt)->y3;
                                            else if (my < ((PolyF4 *)pkt)->y3) my = ((PolyF4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                ((PolyF4 *)pkt)->rgbc = prim->w0;
                                                otp = (u32 *)(((za >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x5000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x18;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
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
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                        if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x200;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = tp[0];
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
                                    break;
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    vv[3] = *(SVECTOR2 *)vd;
                                    gte_ldv0(&vv[3]);
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
                                    /* L1: zero-byte $v1 conflict dial -- keeps my/mny off $v1 so the
                                     * my/mny/mx/mn quad lands on $a2/$a3/$t0/$t1 (see header). */
                                    __asm__ __volatile__ ("" ::: "$3");
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&tmpxy[3]);
                                        if (tmpxy[3].vx < mn) mn = tmpxy[3].vx;
                                        else if (mx < tmpxy[3].vx) mx = tmpxy[3].vx;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (tmpxy[3].vy < mny) mny = tmpxy[3].vy;
                                            else if (my < tmpxy[3].vy) my = tmpxy[3].vy;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                *(u32 *)&((PolyFT4 *)pkt)->x3 = *(u32 *)&tmpxy[3];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = colA | 0x2E000000;
                                                ((PolyFT4 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                {
                                                u32 *op1 = (u32 *)(((za >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*op1 & 0xFFFFFF) | 0x9000000;
                                                *op1 = (*op1 & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                }
                                                pkt += 0x28;
                                                pkt[3] = 6;
                                                *(u32 *)(pkt + 8) = colB | 0x2A000000;
                                                *(u32 *)(pkt + 0xC) = *(u32 *)&tmpxy[0];
                                                *(u32 *)(pkt + 4) = 0xE1000040;
                                                *(u32 *)(pkt + 0x10) = *(u32 *)&tmpxy[1];
                                                *(u32 *)(pkt + 0x14) = *(u32 *)&tmpxy[2];
                                                *(u32 *)(pkt + 0x18) = *(u32 *)&tmpxy[3];
                                                {
                                                u32 *op2 = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*op2 & 0xFFFFFF) | 0x6000000;
                                                *op2 = (*op2 & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                }
                                                pkt += 0x1C;
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

