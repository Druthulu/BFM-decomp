/*
 * func_8017C294 -- ov_SC01_077 (exemplar of a 16-member structural cluster), 246 ins.
 * STATUS: NEAR -- 246/246 ins, 12 mismatched (95.1% index-wise exact), ZERO structural
 * divergence (no opcode/length drift; every residual is a register grant or a stack-slot
 * offset).  Session S42.
 *
 * WHAT THE FUNCTION IS
 *   Screen-space AABB of a world rect: build 4 corner points from (x,y,w,h), rotate/project
 *   each through func_8017C66C/func_8017C710/func_8017C908, clamp each projected corner to
 *   +/- (min(w,h)/20) of the rect, then min/max the 4 results (plus the origin `base`) into
 *   out[0..3] = {minx, minz, width, depth}.
 *
 * THE 12 RESIDUALS (all measured, none guessed)
 *   idx 12,226  a1's spill slot: mine 0xA8, target 0x80          (offset only, reg correct)
 *   idx 14,15,18,19,23  head reg grant: `mh` lands in $a2, target $a0; and the `lh 0x6($a0)`
 *               / `lh 0x0($a0)` pair is emitted in the other order.  See NOTE 2.
 *   idx 31,33,34,106,108  pEnd's storage: mine 0xA0 in $v0, target 0x108 in $t8.  See NOTE 1.
 *
 * NOTE 1 -- THE 0x108 SLOT IS *NOT* REACHABLE FROM A DECLARED LOCAL (byte-measured, S42)
 *   Frame map of the target (vars=256, 0x10..0x10F):
 *     0x10 pos[4][4] | 0x30 mat[4][4] | 0x50 outp[4][4] | 0x70 zero[4] | 0x78 base[4]
 *     0x80 = the spilled `a1` parameter | 0x88..0x107 = 128 B never referenced
 *     0x108 = the loop-start pointer (stored once, reloaded for `p < pStart+0x20`)
 *   gcc-2.7.2 lays the frame out in three strata, in this order:
 *     (1) every DECLARED local, in declaration order, ascending from 0x10;
 *     (2) reload spill slots;
 *     (3) a trailing ~96 B block that the tail's `?:` chain allocates and never touches.
 *   Proven by ablation: deleting the min/max tail drops vars by exactly 96 while leaving the
 *   spill slot where it was; `volatile`, plain, and inner-block declarations of pEnd ALL land
 *   in stratum (1)/(2) and therefore always BELOW the block.  The target's 0x108 sits at the
 *   TOP of the block, so its storage is allocated after everything -- i.e. it is not a C local
 *   in the original at all.  Every source-level lever for it was byte-refuted:
 *     - `volatile` local + filler array   -> slot tracks the filler linearly, frame grows too
 *     - plain local, natural reload spill -> right slot stratum, WRONG code shape (76-97 diffs)
 *     - `__asm__` opacity on the pointer  -> 184 diffs
 *     - inner-block declaration            -> slot unchanged (gcc walks the whole BLOCK tree in
 *                                            expand_function_start, so nesting does NOT delay it)
 *     - zero-temp tail (if/else or operands bound to locals) -> kills the 96 B block, but the
 *       tail's shape DEPENDS on the memory operands (each MIN re-reads outp[i][j]: lhu+lh),
 *       so a zero-temp tail is 219/234 ins, not 246.  The block and the code are the same fact.
 *   `s32 dead[7]` below is therefore a DELIBERATE frame-size dial, not a real variable -- it is
 *   the 32 B that makes vars come out at 256.  (Cookbook 83c warns this may be gcc's own spill
 *   area; here the measurement says stratum (1) is genuinely 32 B larger than the arrays.)
 *
 * NOTE 2 -- THE HEAD IS A qty_compare TIE (local-alloc.c), not a spelling problem
 *   Target: lh 0x4 -> $v0 (w), lh 0x0 -> $s5 (x), lh 0x6 -> $v1 (h), lh 0x2 -> $s4 (y);
 *           then  mw=w ($a1), xw=x+w ($s7), mh=h ($a0), slt w,h.
 *   Writing the body in that order (mw; xw; mh; yh) reproduces the ORDER and puts mh in $a0
 *   correctly, but flips w/h to $v1/$v0 -- because QTY_CMP_PRI = log2(nrefs)*nrefs*size /
 *   (death-birth) and with that order w's live range is one insn LONGER than h's, so h wins
 *   $v0.  Writing it as (mw; mh; xw; yh) -- the form below -- keeps w in $v0 but costs the
 *   emission order and puts mh in $a2.  Both cost exactly 5 diffs; 72 statement permutations,
 *   24 declaration orders, s16/s32 retypings, `?:`-MAX spellings, ref-count shifts
 *   (`yh = y + mh`), and $v0/$v1 pins were all swept -- the floor is 12 in every direction.
 *   tools/permuter_ils.py (REGALLOC profile, 5 warm restarts x 220 s x -j10) also plateaus
 *   at exactly 12.  This is a genuine local optimum for source-level mutation.
 *
 * VERIFY:
 *   .venv/bin/python tools/match_one.py func_8017C294 --c <this file>  *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_8017AE2C
 */
#include "common.h"

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

extern s32 func_800491EC(void);
extern void func_8017C66C(u16 *a0, void *a1);
extern int func_8017C710(short *param_1, short *param_2, short *param_3, int param_4);
extern void func_8017C908(s32 a0, s32 a1);

void func_8017C294(short *a0, short *a1, s32 a2)
{
    short pos[4][4];
    short mat[4][4];
    short outp[4][4];
    short zero[4];
    short base[4];
    s32 dead[7];
    short *volatile pEnd;
    short *p;
    short *m;
    short *o;
    short *e;
    short *dst;
    s32 x, y, w, h, xw, yh, d, z;
    s16 mw, mh;
    s32 t, r;
    register s32 n __asm__("$4");
    register s32 hi __asm__("$2");
    s32 bx, bz;
    s32 minx, minz, maxx, maxz;

    (void)&dead;
    w = a0[2];
    x = a0[0];
    h = a0[3];
    y = a0[1];
    mw = w;
    mh = h;
    xw = x + w;
    yh = y + h;
    if (w < h) {
        mw = mh;
    }
    o = outp[0];
    m = mat[0];
    pEnd = pos[0];
    p = pEnd;
    d = (s16)(mw / 20);
    z = func_800491EC();
    pos[0][0] = x;
    pos[0][1] = y;
    pos[0][2] = z;
    pos[1][0] = xw;
    pos[1][1] = y;
    pos[1][2] = z;
    pos[2][0] = x;
    pos[2][1] = yh;
    pos[2][2] = z;
    pos[3][0] = xw;
    pos[3][1] = yh;
    pos[3][2] = z;
    zero[0] = 0;
    zero[1] = 0;
    zero[2] = 0;
    func_8017C66C((u16 *)zero, base);
    do {
        func_8017C66C((u16 *)p, m);
        if (func_8017C710(base, m, o, a2) != 0) {
            func_8017C908((s32)o, (s32)p);
            t = p[0];
            dst = p;
            n = t;
            r = x - d;
            if (t >= r) {
                hi = xw + d;
                r = hi;
                __asm__ __volatile__("" : "=r"(r) : "0"(r));
                if (t <= hi) {
                    r = n;
                }
            }
            *dst = (short)r;
            t = p[1];
            dst = p;
            n = t;
            r = y - d;
            if (t >= r) {
                hi = yh + d;
                r = hi;
                __asm__ __volatile__("" : "=r"(r) : "0"(r));
                if (t <= hi) {
                    r = n;
                }
            }
            dst[1] = (short)r;
            func_8017C66C((u16 *)p, m);
            func_8017C710(base, m, o, a2);
        }
        o += 4;
        e = pEnd;
        __asm__ __volatile__("");
        p += 4;
        m += 4;
    } while ((s32)p < (s32)(e + 0x10));

    minx = MIN(MIN(outp[0][0], outp[1][0]), MIN(outp[2][0], outp[3][0]));
    bx = base[0];
    if (bx < minx) {
        minx = bx;
    }
    minz = MIN(MIN(outp[0][2], outp[1][2]), MIN(outp[2][2], outp[3][2]));
    bz = base[2];
    if (bz < minz) {
        minz = bz;
    }
    maxx = MAX(MAX(outp[0][0], outp[1][0]), MAX(outp[2][0], outp[3][0]));
    if (maxx < bx) {
        maxx = bx;
    }
    maxz = MAX(MAX(outp[0][2], outp[1][2]), MAX(outp[2][2], outp[3][2]));
    if (maxz < bz) {
        maxz = bz;
    }

    a1[2] = maxx - minx;
    a1[0] = minx;
    a1[1] = minz;
    a1[3] = maxz - minz;
}
