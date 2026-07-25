#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_types.h"

/* ===========================================================================
 * func_8017F510 -- 1,511 ins, ov_SC03_006 (behemoth #3).
 *
 * WHAT IT IS: the SINGLE-point-light variant of the mesh renderer family.
 *   base   = func_8017CA80  (952 ins, MATCHED, src/ov_SC03_090/...)
 *   lit x3 = func_8017D960  (3,338 ins, 98.8% draft, .run/giants/)
 *   this   = func_8017F510  (1,511 ins) -- ONE light box, plus an ambient
 *            term added to every vertex and an "unlit" flat colour derived
 *            from that same ambient.
 *
 * Differences vs the 3-light variant:
 *   - 3 args (arg0 = actor, arg1 = model = *(arg0+8), arg2 = arg0+0x10).
 *   - early-out `if (*(s32 *)arg0) return;` BEFORE the 3-call prologue.
 *   - Part[] lives INLINE at arg1 + 0x14 (not *(arg0+0xC)).
 *   - ONE light descriptor at D_801F7790 {s32 enable; u16 cx,cy,cz; pad;
 *     s32 range; ...; s32 ambient@+0x18}; defaults cx=cy=cz=0x6000,
 *     r=0x100, rlo=0x80, amb=0, col=0 when disabled.
 *   - per vertex: atten (x,z,y separable falloff) + amb, clamped to 0x80.
 *   - lit   -> POLY_GT3 (0x28, OT 0x9000000, GPU 0x34) /
 *              POLY_GT4 (0x34, OT 0xC000000, GPU 0x3C)
 *              rgb = cbase | c | (c<<8) | 0x800000  (blue fixed at 0x80),
 *              cbase = (tp[0] & 0x2000000) | GPUCODE.
 *     unlit -> POLY_FT3 (0x20, OT 0x7000000) / POLY_FT4 (0x28, OT 0x9000000)
 *              rgbc = (tp[0] & 0xFF000000) | col.
 *
 * Frame (measured from the .s): 0x258 =
 *   0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] | 0xA0 mtx |
 *   0xC0 g{otz,flag,opz,sz0..sz3} | 0xE0..0x22F = 42 EIGHT-BYTE spill slots |
 *   0x230..0x257 = 10 saved regs (s0-s7, fp, ra).
 *
 * MEASURED (2026-07-25, gcc-2.7.2 pinned triple):
 *   tools/match_one.py    mine=1511 ins  target=1511 ins  **97 mismatched**
 *                         class ADDRESSING [permuter] sig=ADDRESSING/srl!=addu
 *   .run/drafts-behemoth3/b3_align.py (shape-agnostic aligners):
 *     REGISTER-MASKED (structural)  1503 / 1511 = **99.5%**  (8 divergent ins,
 *                                   8 hunks)
 *     FULL (registers KEPT)         1410 / 1511 = **93.3%**  (101 divergent)
 *   tools/symcheck.py     SYMS-OK, 12 symbols agree (no invented symbols)
 *   Frame 0x258 EXACT; prologue + epilogue byte-exact; the same 10 saved regs
 *   at the same offsets; the SET of sp slots used is IDENTICAL to the target.
 *   NOT A MATCH. Only a byte-identical whole-binary rebuild is a match (G3/P9).
 *
 * THE THREE LEVERS THAT GOT IT HERE (all byte-measured, each one a step):
 *   1. The already-MATCHED 952-ins sibling func_8017CA80 + the 3,338-ins
 *      func_8017D960 draft supplied ~90% of the C. First compile: 1528 ins,
 *      88.0% structural, exact 10-saved-reg set, frame off by one spill slot.
 *   2. **Dedicated temps for the vertex-word loads.** Reusing the `w`/`wz`
 *      temps (which also carry prim->w1/w2 and part->zz) for
 *      `vw = *(u32*)va; vzw = *(u32*)(va+4);` extended two live ranges enough
 *      that `amb` lost its callee-saved register and got spilled -- 7 extra
 *      `lw amb`+`nop` pairs = the whole +17-instruction drift. Separate
 *      `vw`/`vzw` -> 1511/1511 ins, 99.6% structural, 131 mismatched.
 *      (A `register s32 amb __asm__("$30")` pin ALSO produced 1511 ins, but it
 *      MISCOMPILES: gcc-2.7.2 gave $s8 to `hi_z` as well -- the same hard reg
 *      held two live values. Local register pins are a preference, not a
 *      reservation; never ship one without checking the pinned reg's defs.)
 *   3. `part->prim` read BEFORE `part->nprim` (cookbook §70 family): loop.c's
 *      combine_givs walks bl->giv in reverse record order, so the LAST-recorded
 *      giv becomes the combined base. prim-then-nprim -> base = part+0xC (the
 *      target); nprim-then-prim -> base = part+0x10. Worth ~7 ins + the whole
 *      $s6/$s7 naming cascade.
 *   4. `my = wy >> 16;` BEFORE `mny = wy;` in the box[] build (the matched
 *      952 sibling has the opposite order): flipped the $a2/$a3 global-alloc
 *      decision for the my/mny pair, 131 -> 97 mismatched.
 *
 * REMAINING DIVERGENCE (all measured, all localised, 97 ins):
 *   A. 2 ins, tgt[118..120]: the box-build `addu $a2,$v1` (mny) and
 *      `srl $a3,$v1,16` (my) are TRANSPOSED. Source order sets BOTH the
 *      emission order (sched.c rank_for_schedule ties break on insn UID) and
 *      the allocation order (global.c allocno_compare ties break on allocno
 *      number). `mny;my` gives the right emission + wrong regs; `my;mny`
 *      (shipped) the right regs + wrong emission. Needs a third form.
 *   B. 3 ins x 2, tgt[864..870] and tgt[1454]: in the two UNLIT tails the
 *      target materialises the single-`lui` OT tag (0x7000000 / 0x9000000)
 *      BEFORE the two-insn 0xFFFFFF constant; mine does the reverse. Pure
 *      sched.c ordering; the LIT tails (which lack the third 0xFF000000
 *      constant) already agree.
 *   C. ~93 ins of pure REGISTER NAMING, and they all trace to ONE seed:
 *      `c3` (the 4th quad vertex colour). The target gives it $a2 (reusing the
 *      dead flag `f0`); mine gives it $a3. `tp` is one pseudo across all four
 *      emit tails and CONFLICTS with c3 in the quad-lit tail, so it takes
 *      whichever of $a2/$a3 c3 did not -- target $a3, mine $a2 -- and the whole
 *      4-tail block (tp / 0xFFFFFF / 0xFF000000 / otp / the rgb OR-chain
 *      accumulator) renames off that. Fix c3 -> $a2 and ~93 of the 97 should
 *      fall together.
 *
 * TRIED AND REJECTED (byte-measured, do not re-buy):
 *   decl-order permutations of amb / my,mny,mx,mn (no effect - gcc numbers
 *   pseudos by first USE, not declaration); block-scoping otp/tp/cb/uvw per
 *   emit branch (1509 ins); dedicated box-build min/max vars (1510 ins);
 *   splitting `tp` per branch (147); inlining `tp` as `((u32*)prim->w0)[k]`
 *   (1535 ins - no CSE); reusing `f0` as c3 (176); vertex x/z/y and y/x/z
 *   orders (99-146); `otp = (u32*)(ot + ...)` operand swap (no change);
 *   `0x800000 | cb | c | (c<<8)` (1526 ins).
 *   decomp-permuter (tools/permuter/run_masked.py, klass=ADDRESSING, -j 10):
 *   3,663 candidates, base 97, **no improvement** -> cookbook §3 hard tail,
 *   this residual is not in the C-randomisation search space.
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

/* ---- the single light-volume descriptor ---------------------------------- */
extern s32 D_801F7790;
extern u16 D_801F7794, D_801F7796, D_801F7798;
extern s32 D_801F779C;
extern s32 D_801F77A8;

/* ---- the box-containment test for one vertex ----------------------------- */
#define BOXTEST(F, X, Y, Z) \
    if (lo_x < (X) && (X) < hi_x && lo_y < (Y) && (Y) < hi_y && lo_z < (Z) && (Z) < hi_z) F = 1

/* ---- the separable per-axis falloff, visited in x, z, y order ------------ */
#define ATTEN(A, X, Y, Z)                                       \
    A = 0;                                                      \
    d = (X) - cx;   if (d < 0) d = cx - (X);                    \
    if (d < r) { A = 0x80; if (d >= rlo) A = r - d; }           \
    d = (Z) - cz;   if (d < 0) d = cz - (Z);                    \
    if (r < d) A = 0;                                           \
    else if (rlo < d) A = (A * (r - d)) >> 7;                   \
    d = (Y) - cy;   if (d < 0) d = cy - (Y);                    \
    if (r < d) A = 0;                                           \
    else if (rlo < d) A = (A * (r - d)) >> 7;                   \
    A = A + amb;                                                \
    if (A > 0x80) A = 0x80

void func_8017F510(s32 arg0, s32 arg1, s32 arg2)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern u8 D_800AF630[];

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 j;
    u32 i;
    u8 *vd;
    u32 ot;
    u8 *pkt;
    s16 x3, z3, y3;
    Prim *prim;
    u32 nprim;
    u8 *vtx;
    s32 nparts;
    Part *part;
    s16 lo_x, hi_x, lo_y, hi_y, lo_z, hi_z;
    s16 cx, cy, cz;
    s32 r, rlo;
    u32 col;
    u8 *va, *vb, *vc;
    u32 w; s32 code;
    u32 vw, vzw;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    u8 *base;
    s32 f0;
    s16 x0, y0, z0, x1, y1, z1, x2, y2, z2;
    s32 d;
    s32 c0, c1, c2, c3;
    s32 za, zb;
    u32 *otp;
    u32 *tp;
    u32 cb;
    u32 uvw;
    s32 amb;

    base = D_800AF630;

    if (*(s32 *)arg0 != 0) {
        return;
    }

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg2, &mtx);
    func_80052E38(&mtx);

    if (D_801F7790) {
        cx = D_801F7794;
        cy = D_801F7796;
        r = D_801F779C;
        rlo = r - 0x80;
        amb = D_801F77A8;
        cz = D_801F7798;
        if (amb < 0x60) {
            col = amb | 0x600000 | (amb << 8);
        } else {
            col = amb | (amb << 8) | (amb << 16);
        }
    } else {
        cz = 0x6000;
        cy = 0x6000;
        cx = 0x6000;
        r = 0x100;
        rlo = 0x80;
        amb = 0;
        col = 0;
    }

    lo_x = cx - r;  hi_x = cx + r;
    lo_y = cy - r;  hi_y = cy + r;
    lo_z = cz - r;  hi_z = cz + r;

    pkt = D_800A5E60;
    part = (Part *)(arg1 + 0x14);
    nparts = *(s32 *)(arg1 + 8);
    vtx = *(u8 **)(arg1 + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)(base + 0xA3D2)) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        my = wy >> 16;
        mny = wy;
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
                                            if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; }
                                            else { za = g.sz1; if (za < g.sz2) za = g.sz2; }
                                            g.opz = za;

                                            f0 = 0;

                                            vw = *(u32 *)va;
                                            vzw = *(u32 *)(va + 4);
                                            x0 = vw; y0 = vw >> 16; z0 = vzw;
                                            BOXTEST(f0, x0, y0, z0);
                                            vw = *(u32 *)vb;
                                            vzw = *(u32 *)(vb + 4);
                                            x1 = vw; y1 = vw >> 16; z1 = vzw;
                                            BOXTEST(f0, x1, y1, z1);
                                            vw = *(u32 *)vc;
                                            vzw = *(u32 *)(vc + 4);
                                            x2 = vw; y2 = vw >> 16; z2 = vzw;
                                            BOXTEST(f0, x2, y2, z2);

                                            if (f0) {
                                                ATTEN(c0, x0, y0, z0);
                                                ATTEN(c1, x1, y1, z1);
                                                ATTEN(c2, x2, y2, z2);

                                                *(u32 *)&((PolyGT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyGT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyGT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = (tp[0] & 0x2000000) | 0x34000000;
                                                ((PolyGT3 *)pkt)->rgb0 = cb | c0 | (c0 << 8) | 0x800000;
                                                ((PolyGT3 *)pkt)->rgb1 = cb | c1 | (c1 << 8) | 0x800000;
                                                ((PolyGT3 *)pkt)->rgb2 = cb | c2 | (c2 << 8) | 0x800000;
                                                ((PolyGT3 *)pkt)->uv0 = tp[1];
                                                ((PolyGT3 *)pkt)->uv1 = tp[2];
                                                ((PolyGT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            } else {
                                                *(u32 *)&((PolyFT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT3 *)pkt)->rgbc = (tp[0] & 0xFF000000) | col;
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
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;

                                                f0 = 0;

                                                vw = *(u32 *)va;
                                                vzw = *(u32 *)(va + 4);
                                                x0 = vw; y0 = vw >> 16; z0 = vzw;
                                                BOXTEST(f0, x0, y0, z0);
                                                vw = *(u32 *)vb;
                                                vzw = *(u32 *)(vb + 4);
                                                x1 = vw; y1 = vw >> 16; z1 = vzw;
                                                BOXTEST(f0, x1, y1, z1);
                                                vw = *(u32 *)vc;
                                                vzw = *(u32 *)(vc + 4);
                                                x2 = vw; y2 = vw >> 16; z2 = vzw;
                                                BOXTEST(f0, x2, y2, z2);
                                                vw = *(u32 *)vd;
                                                vzw = *(u32 *)(vd + 4);
                                                x3 = vw; y3 = vw >> 16; z3 = vzw;
                                                BOXTEST(f0, x3, y3, z3);

                                                if (f0) {
                                                    ATTEN(c0, x0, y0, z0);
                                                    ATTEN(c1, x1, y1, z1);
                                                    ATTEN(c2, x2, y2, z2);
                                                    ATTEN(c3, x3, y3, z3);

                                                    *(u32 *)&((PolyGT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    gte_stsxy((long *)&((PolyGT4 *)pkt)->x3);
                                                    tp = (u32 *)prim->w0;
                                                    cb = (tp[0] & 0x2000000) | 0x3C000000;
                                                    ((PolyGT4 *)pkt)->rgb0 = cb | c0 | (c0 << 8) | 0x800000;
                                                    ((PolyGT4 *)pkt)->rgb1 = cb | c1 | (c1 << 8) | 0x800000;
                                                    ((PolyGT4 *)pkt)->rgb2 = cb | c2 | (c2 << 8) | 0x800000;
                                                    ((PolyGT4 *)pkt)->rgb3 = cb | c3 | (c3 << 8) | 0x800000;
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
                                                    *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    tp = (u32 *)prim->w0;
                                                    ((PolyFT4 *)pkt)->rgbc = (tp[0] & 0xFF000000) | col;
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
