/* func_80133CD4 — merged-variable form: V0={s0v,denom,s0a}, V1={s1v,neg2,s1a}.
 * Hypothesis: original source reused one variable per accumulator chain, making the
 * allocno call-crossing (K4) + top-density (K2) => s0var->$s0, s1var->$s1 first-fit,
 * cascading the whole callee assignment to the target permutation. Pin-free. */
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

        {
            s32 *pw = D_801870C0;
            pw[0] = s3[0];
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
        pb0[2] += s1var * pc0[2] / s0var;

        {
            s32 h;
            h = ((s16 *)pb0)[0];
            s1var = h << 16;
            __asm__("lh %0, 2(%2)" : "=r"(h) : "0"(h), "r"(pb0));
            s0var = h << 16;
        }
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
        if (*(u8 *)cmd == 0)
            return -1;
        return 1;
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
    return 1;
}
