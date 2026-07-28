/* func_80132F40 — ov_SC01_077 (jr_8012ACE0 region), 72 ins, -O2.
 *
 * STATUS: NEAR — 72/72 instructions, closeness 6, klass OPCODE-MIXED(branch,width).
 * Instructions 0..36 and 44..71 are byte-identical (relocation-masked); the whole residual
 * is the 6-instruction min(w,h) block at idx 37..43.
 *
 * Canonical decls (wave22_targets.json sig_hints) verbatim. D_80126BE0 is NOT in sig_hints —
 * it is derived from the asm (`lui/addiu %hi/%lo` passed as arg 3) and declared exactly as the
 * 20+ sibling TUs already declare it: `extern u8 D_80126BE0[];`.
 *
 * Structure facts that were byte-forced (each verified by a compile):
 *  - locals are an SVECTOR-ish ARRAY of 4 (vars=32 in the target frame 0x40 with only 4 saved
 *    regs; v[0]@sp+0x10 and v[1]@sp+0x18 are used, v[2]/v[3] are dead but hold the frame).
 *  - `q` is a SOURCE-LEVEL pointer local for v[1] (cookbook §32#1): a base living in a
 *    callee-saved reg across calls/branches can only come from a source local. Pinning it to
 *    $17 pushes arg0 into $16, which reproduces the target's $s0=arg0 / $s1=&v[1] exactly.
 *  - `&v[0]` must be REMATERIALIZED at both call sites (`addiu $aN,$sp,0x10`). That only
 *    happens in a narrow whole-function CSE fork (§83d): w/h declared s16 (not s32). With
 *    s32 w/h, gcc's CSE commons the struct-copy's source-address pseudo (created by
 *    mips.c's block-move `copy_addr_to_reg`) into both call sites, hoisting sp+0x10 into a
 *    FIFTH callee-saved register (frame 0x48, +3 ins = 73). Verified across ~120 spellings:
 *    CFG shape, inline helpers, nested-block ptr + §2 output-only volatile kill, reg-tie
 *    barriers, packed/aligned copies and array/struct/pair layouts all leave the fork alone.
 *
 * REMAINING BLOCKER (idx 37..43): the target's min block is
 *      lh $v1,8($v0) / lh $v0,0xA($v0) / nop / addu $a0,$v0,$zero /
 *      slt $v0,$v0,$v1 / beqz / (delay) addu $s2,$v1,$zero / addu $s2,$a0,$zero
 *  i.e. form-b (`m = w; if (h < w) m = h;`) with (a) NO coalescing of m into w's register and
 *  (b) an explicit copy of h into $a0 because the slt overwrites h's $v0. Every C spelling
 *  that yields form-b semantics without the m/w coalescing also flips the CSE fork above and
 *  costs 3 instructions elsewhere; the only 72-ins state found keeps form-a and pins w to $3
 *  as s16, whose HImode load is `lhu` + `sll/sra` (3 ins) instead of `lh` + `nop`/`addu` (3).
 *  Net: same length, 6 opcode/register mismatches.
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
    s16 *p;
    register s16 w __asm__("$3");
    register s32 h __asm__("$2");
    s32 m;

    q = &v[1];
    v[0].vx = D_80126B5E;
    v[0].vy = D_80126B62;
    v[0].vz = D_80126B66;
    v[1] = v[0];

    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58),
                      (s32)D_80126BE0, (s32)q) != 0) {
        p = (s16 *)((*(s32 *)(arg0 + 0x58) & 0x0FFFFFFF) | 0x80000000);
        w = p[4];
        h = p[5];
        if (h < w) { m = h; } else { m = w; }
        func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34, &v[0], q);
        v[1].vy = m;
        func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34, q, &v[0]);
        D_80126B5E = v[0].vx;
        D_80126B62 = v[0].vy;
        D_80126B66 = v[0].vz;
    }
}
