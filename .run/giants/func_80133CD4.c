/* func_80133CD4 (ov_SC01_077_a, 399 ins) — camera-collision solver.
 *
 * STATUS: PIN-FREE structural draft (×134-clean). rtu_match: mine=397 / target=399,
 * positional=378 (index-diff; heavily inflated by a whole-function register PERMUTATION).
 * All semantics/calls/constants/control-flow/GTE-SQR/loop/tail are byte-correct in content
 * and order. §43 (K&R s16 param) IS the crack for the arg0 double-copy: the target holds
 * arg0 in TWO callee regs ($s7 sign-test + $fp mask-test); the K&R `s16 arg0;` form
 * reproduces that duplication with NO register pins (verified: `move s6,a0; move s7,s6`).
 *
 * RESIDUAL = the giant regalloc wall (§31 RC-class / §37 allocno-tie), NOT a new quirk:
 * gcc allocates my body to 8 callee regs (s0v divisor -> caller-saved $v0), the target uses
 * 9 (s0v -> callee $s0, forcing the arg0 double-copy up to $s7/$fp). The whole callee
 * assignment is a coupled permutation:
 *   target: s0v->s0 s1v->s1 arr->s2 elemptr->s3 cmd->s4 base->s5 s6val->s6 arg0->s7 copy->fp
 *   mine:   s1v->s0 arr->s1 base->s2 elemptr->s3 cmd->s4 s6val->s5 arg0->s6 copy->s7  (s0v->v0)
 * Fixing s0v alone does not cascade (single $s0 pin rebalanced to 8; the assignment stays
 * permuted). The prior 9-callee-pin draft (.run/match/, .run/drafts-t5-batch2/) forces the
 * exact layout -> positional ~274 / true ~30 sched2 residual, but its 9 $s-pins SIGABRT
 * sibling TUs (×134-unsafe, the reason this pin-free rewrite exists).
 *
 * Levers tried for the s0v caller->callee flip (all no-op / rebalanced): pointer-var decls
 * (fixed the &D_xxx address-CSE hoist, kept), K&R double-copy (kept), asm("":: "r"(s0v))
 * priority boost, division decl reorder, single s0v->$s0 callee pin, 4 caller-saved division
 * pins ($a0-$a3), $0-add opaque divisor copy (folds, $0==0).
 * ESCALATE: Fable5 gdb-on-cc1 (§34 method) on find_reg/post_mark_life to break the s0v
 * global-vs-local allocno tie; then the ~30-ins sched2 residual is permuter-finishable.
 * No //@EDIT / no ec_edit needed (split decl is already `s32 func_80133CD4()`; caller no-proto).
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
    s32 s1v, s0v;
    s32 s1a, s0a, s2a;
    s16 y;

    if (func_80134310(s3, D_801870B0, s6) >= 0)
        return 0;

    s1v = func_80134310(s3, D_801870AC, s6);
    if (s1v < 0)
        return 0;

    s0v = func_80134310(s3, D_801870B8, 0);
    {
        u16 *pac = D_801870AC;
        s16 *pb8 = D_801870B8;
        s16 *pb4 = D_801870B4;
        s32 neg = -s1v;
        pb4[0] = pac[0] + neg * pb8[0] / s0v;
        pb4[1] = pac[1] + neg * pb8[1] / s0v;
        pb4[2] = pac[2] + neg * pb8[2] / s0v;
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
        s32 neg = -ret;
        s32 *pc0 = D_801870C0;
        s32 *pc4;
        u16 *pb0;
        s32 denom;
        s32 t, o2;

        pc0[0] = s3[0];
        pc0[1] = s3[1];
        pc0[2] = s3[2];

        __asm__ __volatile__(
            "lwc2 $9, 0(%0)\n"
            "lwc2 $10, 4(%0)\n"
            "lwc2 $11, 8(%0)\n"
            "nop\n"
            "nop\n"
            "sqr 0\n"
            : : "r"(D_801870C0) : "$9", "$10", "$11", "memory");
        {
            s32 *dst = D_801870C4;
            __asm__ __volatile__(
                "swc2 $25, 0(%0)\n"
                "swc2 $26, 4(%0)\n"
                "swc2 $27, 8(%0)\n"
                : : "r"(dst) : "memory");
        }

        pc0 = D_801870C0;
        pc4 = D_801870C4;
        denom = pc4[0] + pc4[1] + pc4[2];
        pb0 = D_801870B0;
        pb0[0] += neg * pc0[0] / denom;
        pb0[1] += neg * pc0[1] / denom;
        pb0[2] += neg * pc0[2] / denom;

        s1a = (s16)pb0[0] << 16;
        s0a = (s16)pb0[1] << 16;
        s2a = (s16)pb0[2] << 16;

        t = pc0[0] << 4;
        pc0[0] = t;
        if (t < 0) s1a |= 0xFFFF;
        t = pc0[1] << 4;
        pc0[1] = t;
        if (t < 0) s0a |= 0xFFFF;
        o2 = pc0[2];
        t = o2 << 4;
        pc0[2] = t;
        if (t < 0) s2a |= 0xFFFF;
        s2a += o2 << 5;
        s1a += pc0[0] << 1;
        s0a += pc0[1] << 1;

        do {
            pc0 = D_801870C0;
            s1a += pc0[0];
            s0a += pc0[1];
            s2a += pc0[2];
            pb0 = D_801870B0;
            pb0[0] = s1a >> 16;
            pb0[1] = s0a >> 16;
            pb0[2] = s2a >> 16;
            ret = func_80134310(s3, pb0, s6);
        } while (ret < ((s3[1] < -0xE00) ? 0x1800 : 0x2F00));
    }

    y = s3[1];
    if (y < -0xBCB) {
        u16 *s3u = (u16 *)s3;
        u16 *pb0 = D_801870B0;
        *(u16 *)D_801152A8 = s3u[0];
        pb0[3] = s3u[1];
        D_801152AA = s3u[1];
        D_801152AC = s3u[2];
        D_801152AE = s3u[3];
        return 1;
    }
    D_801870AC[3] = y;
    {
        typedef struct { s8 c[8]; } Blk8;
        *(Blk8 *)&D_801152B0 = *(Blk8 *)s3;
    }
    if (*(u8 *)cmd != 0)
        return 1;
    return -1;
}
