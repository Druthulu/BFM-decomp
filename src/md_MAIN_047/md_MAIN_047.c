#include "common.h"

void func_800CCB20(void) {
}

#include "common.h"

extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CCB28(void *a0) {
    void *s0 = a0;

    func_80146994(0x3B, (s32)s0, 0, 0);
    *(s16 *)((s32)s0 + 0x1C8) = 0xBA;
    func_801599A4(s0);
    func_80159B3C(s0);
}




s32 func_800CCB78(a0)
void *a0;
{
    *(s32 *)((s32)a0 + 0x2c) = 1;
    return 1;
}




void func_800CCB84(void *a0) {

    extern void (*D_800CD6C8[])(void);
    D_800CD6C8[((Unkstruct_80126B58 *)a0)->unk2]();
}


/* DEF-SIDE-RETURN wall (cookbook §202): the destination TU declares this
 * symbol `extern void func_800CCBC0(void);` at src/md_MAIN_047/md_MAIN_047.c
 * (its sole caller in func_800CD58C discards the value), but the asm proves
 * an s32 return (sll/sra into $v0 at .L800CCDB8/.L800CCDC0 before the
 * epilogue). Bind the real body to a private C name aliased to the same
 * link symbol so the TU's void declaration never conflicts with this
 * definition's true s32 return type. */

s32 func_800CCBC0(void)
{

    extern Blk20 D_800AE620;
    extern u8 D_800CD6E0[];
    extern u8 D_800CD6E1;
    extern u8 D_800CD6E2;
    extern u8 D_800CD6E3;
    extern s32 func_80017758(void *a0, void *a1);

    Prim_md_MAIN_047_800CCBC0 prim;
    Blk20 blk;
    Trail_md_MAIN_047_800CCBC0 *p;
    Rec_md_MAIN_047_800CCBC0 *e;
    Rec_md_MAIN_047_800CCBC0 *q;
    short idx;
    short cnt;
    unsigned int tim;
    short half;
    short n;

    blk = D_800AE620;
    prim.tag = 0x50000000;
    p = (Trail_md_MAIN_047_800CCBC0 *)D_800CD6E0;
    if (p->flag == 0) {
        return 0;
    }
    n = 0;
    e = p->e;
    idx = D_800CD6E1;
    tim = D_800CD6E3;
    cnt = D_800CD6E2;
    half = tim >> 1;
    cnt = cnt - 1;
    if (cnt != -1) {
        do {
            q = &e[idx];
            prim.v0.vx = q->f0;
            prim.v0.vy = q->f1;
            prim.v0.vz = q->f2;
            prim.v1.vx = q->f3;
            prim.v1.vy = q->f4;
            prim.v1.vz = q->f5;
            n = n + 1;
            idx = idx - 1;
            prim.c0.r = prim.c1.r = tim;
            prim.c0.g = prim.c1.g = prim.c0.b = prim.c1.b = half;
            if (idx < 0) {
                idx = 15;
            }
            q = &e[idx];
            prim.v2.vx = q->f0;
            prim.v2.vy = q->f1;
            prim.v2.vz = q->f2;
            prim.v3.vx = q->f3;
            prim.v3.vy = q->f4;
            prim.v3.vz = q->f5;
            tim = tim - 0x10;
            half = half - 0x10;
            if (half < 0) {
                half = 0;
            }
            prim.c2.r = prim.c3.r = tim;
            prim.c2.g = prim.c3.g = prim.c2.b = prim.c3.b = half;
            func_80017758(&prim, &blk);
            cnt = cnt - 1;
        } while (cnt != -1);
    }
    return n;
}


s32 func_800CCDE8(param_1, param_2, param_3, param_4)
    s32 param_1;
    s16 param_2;
    s16 param_3;
    s16 param_4;
{
    extern u8 D_800CD6E0[];
    extern void func_80148534(s32 a0, s32 a1);
    extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
    extern void func_80149350(s32 a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern s32 VectorNormalSS(void *a0, void *a1);


    Trail_md_MAIN_047_800CCDE8 *p = (Trail_md_MAIN_047_800CCDE8 *)D_800CD6E0;
    s32 node = ((Unkstruct_800CCDE8 *)param_1)->unk34;
    s16 v10[4];
    s16 v18[4];
    s16 v20[4];
    s16 v28[4];
    s16 out[4];
    s32 c;

    switch (param_2) {
    case 0:
        p->flag = 1;
        p->cnt = 0;
        p->idx = 0;
        p->tim = 0xf4;
        break;
    case 1:
        v20[0] = p->e[p->idx].f0;
        v20[1] = p->e[p->idx].f1;
        v20[2] = p->e[p->idx].f2;
        v28[0] = p->e[p->idx].f3;
        v28[1] = p->e[p->idx].f4;
        v28[2] = p->e[p->idx].f5;
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->cnt < 0xf) {
            p->cnt = p->cnt + 1;
        }
        break;
    case 2: {
        u8 t = p->tim - 0x10;
        p->tim = t;
        if (t < 0x10) {
            p->flag = 0;
            return 1;
        }
        {
            u8 n = p->cnt;
            if (n >= 2 && (t >> 4) < n) {
                p->cnt = n - 1;
            }
        }
        return 0;
    }
    }

    func_80148534((s32)v10, (s32)v18);
    func_80165FA4(node, (s32)v10, (s32)v18);
    ((void (*)(s32, s32, s32))func_80149350)(node, (s32)v10, (s32)v10);
    RotTransSV(v18, v18, out);

    if (param_2 != 0) {
        v20[0] = (v10[0] + v20[0]) >> 1;
        v20[1] = (v10[1] + v20[1]) >> 1;
        v20[2] = (v10[2] + v20[2]) >> 1;
        v28[0] = (v18[0] + v28[0]) >> 1;
        v28[1] = (v18[1] + v28[1]) >> 1;
        v28[2] = (v18[2] + v28[2]) >> 1;
        v20[0] = v20[0] - v28[0];
        v20[1] = v20[1] - v28[1];
        v20[2] = v20[2] - v28[2];
        VectorNormalSS(v20, v20);
        v20[0] = v28[0] + v20[0] / param_3;
        v20[1] = v28[1] + v20[1] / param_3;
        v20[2] = v28[2] + v20[2] / param_3;
        p->e[p->idx].f0 = v20[0];
        p->e[p->idx].f1 = v20[1];
        p->e[p->idx].f2 = v20[2];
        p->e[p->idx].f3 = v28[0];
        p->e[p->idx].f4 = v28[1];
        p->e[p->idx].f5 = v28[2];
        c = p->idx;
        p->idx = c + 1;
        if ((u8)(c + 1) > 0xf) {
            p->idx = 0;
        }
        if (p->cnt < 0xf) {
            p->cnt = p->cnt + 1;
        }
    }

    p->e[p->idx].f0 = v10[0];
    p->e[p->idx].f1 = v10[1];
    p->e[p->idx].f2 = v10[2];
    p->e[p->idx].f3 = v18[0];
    p->e[p->idx].f4 = v18[1];
    p->e[p->idx].f5 = v18[2];
    return 0;
}


void func_800CD314(void *arg0) {
    extern u8 D_8011F75C[];
    extern volatile s32 D_8011F758;
    extern u8 D_800CD7A4;
    extern void func_80147324(s32 a0);
    extern void func_800233CC(void *a0, u16 a1);
    extern void func_80146C3C(u8 *a0);


    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t8_tus2)
    s32 t;
    register s32 tb __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t8_tus2)
    s32 cnt;
    s32 p;
    s32 idx;

    s0 = (s32)arg0;
    cnt = ((Unkstruct_800CD314 *)s0)->unk1C;
    p = ((Unkstruct_800CD314 *)s0)->unk20;

    if (cnt < 0x20) {
        if ((cnt & 7) == 0) {
            *(Blk32 *)(s0 + 0x38) = *(Blk32 *)D_8011F75C;
            CAST_ALIAS(s32, p, 4) = (((Unkstruct_800CD314_2 *)p)->unk4 & 0x7FFFFFFF) | (((Unkstruct_800CD314_3 *)D_8011F758)->unk4 & (s32)0x80000000);
            CAST_ALIAS(u16, p, 0x18) = ((Unkstruct_800CD314_3 *)D_8011F758)->unk18;
            ((Unkstruct_800CD314_2 *)p)->unk1A = ((Unkstruct_800CD314_3 *)D_8011F758)->unk1A;
            t = ((Unkstruct_800CD314 *)s0)->unk4C;
            ((Unkstruct_800CD314 *)s0)->unk6 = t;
            tb = ((Unkstruct_800CD314 *)s0)->unk54;
            ((Unkstruct_800CD314 *)s0)->unkE = tb;
            ((Unkstruct_800CD314 *)s0)->unk30 = 0;
            t = ((Unkstruct_800CD314 *)s0)->unk50;
            ((Unkstruct_800CD314 *)s0)->unkA = t - 8;
            func_80147324(0x8E2);
        }
        idx = ((Unkstruct_800CD314 *)s0)->unk30;
        idx += 0x10;
        ((Unkstruct_800CD314 *)s0)->unk30 = idx;
        func_800233CC((void *)&D_800CD7A4, idx);
        ((Unkstruct_800CD314 *)s0)->unk1C = ((Unkstruct_800CD314 *)s0)->unk1C + 1;
        return;
    }
    __asm__ __volatile__("" ::: "a0");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t8_tus2)
    ((void (*)(s32))func_80146C3C)(s0);
}




void func_800CD458(void *a0) {

    extern void (*D_800CD6D0[])(void);
    D_800CD6D0[((Unkstruct_80126B58 *)a0)->unk2]();
}




void func_800CD494(void *a0) {

    extern void (*D_800CD6D8[])(void);
    D_800CD6D8[((Unkstruct_80126B58 *)a0)->unk2]();
}


void func_800CD4D0(void *arg0) {
    extern s32 D_8011D030;
    extern u8 D_800CD6E0[];
    extern void func_80146C3C(u8 *a0);
    extern void func_80016714(void *a0, s32 a1);

    unsigned short *p;
    short i;
    s32 k;

    ((Unkstruct_800CCDE8 *)arg0)->unk2C = 0;
    i = 0;
    p = (unsigned short *)&D_8011D030;
    k = 0x3B;
    do {
        if (p != (unsigned short *)arg0) {
            if (*p == k) {
                ((void (*)(unsigned short *))func_80146C3C)(p);
            }
        }
        i = i + 1;
        p = p + 0x2C;
    } while (i < 0x1E);

    func_80016714(D_800CD6E0, 0xC4);
    func_800CCDE8(arg0, 0, 0);
    ((Unkstruct_800CCDE8 *)arg0)->unk2 = ((Unkstruct_800CCDE8 *)arg0)->unk2 + 1;
}


void func_800CD58C(void *arg0) {
    extern u8 D_800CD6E0[];
    extern void func_80016714(void *a0, s32 a1);
    extern s32 func_800CCBC0(void);

    if (((Unkstruct_800CCDE8 *)arg0)->unk2C != 0) {
        func_800CCDE8(arg0, 1, 0x37);
        func_800CCBC0();
        ((Unkstruct_800CCDE8 *)arg0)->unk2C = 0;
    } else {
        func_80016714(D_800CD6E0, 0xC4);
        func_800CCDE8(arg0, 0, 0);
    }
}


void func_800CD5F8(void *arg0) {
    extern void func_801465C0(void);
    extern void func_8001CD50(s32 a0, s32 a1);
    extern void func_800CD314(void *a0);
    extern void func_80146C3C(u8 *a0);
    extern u8 D_800CD7A4;
    extern u8 D_800CD7A5;
    extern u8 D_800CD7A6;
    extern u8 D_800CD7A8;
    extern u8 D_800CD7A9;
    extern u8 D_800CD7AA;

    s32 s1;
    s32 s0;

    s1 = ((s32 (*)(void))func_801465C0)();
    if (s1 != 0) {
        s0 = (s32)&D_800CD7A4;
        func_8001CD50(s1, s0);
        ((Unkstruct_800CD5F8_2 *)arg0)->unk20 = s1;
        ((Unkstruct_800CD5F8 *)s1)->unk34 = (s32)arg0 + 0x38;
        ((Unkstruct_800CD5F8 *)s1)->unk1E = -0x7400;
        CAST_ALIAS(s32, s1, 4) |= 0x50000000;
        D_800CD7A5 = 0;
        *(u8 *)s0 = 0;
        D_800CD7A9 = 0x40;
        D_800CD7A8 = 0x40;
        D_800CD7A6 = 0;
        D_800CD7AA = 0x50;
        func_800CD314(arg0);
        ((Unkstruct_800CD5F8_2 *)arg0)->unk2 = ((Unkstruct_800CD5F8_2 *)arg0)->unk2 + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(arg0);
    }
}


INCLUDE_RODATA("asm/md_MAIN_047/nonmatchings/md_MAIN_047", D_800CCB1C);
