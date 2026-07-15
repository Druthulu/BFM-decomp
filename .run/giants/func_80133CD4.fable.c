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
    typedef struct { s16 e[4]; } ElemK;

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
        typedef struct { u16 h; } H16;
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
