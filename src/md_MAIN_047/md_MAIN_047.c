#include "common.h"

void func_800CCB20(void) {
}

INCLUDE_ASM("asm/md_MAIN_047/nonmatchings/md_MAIN_047", func_800CCB28);

INCLUDE_ASM("asm/md_MAIN_047/nonmatchings/md_MAIN_047", func_800CCB78);



void func_800CCB84(void *a0) {

    extern void (*D_800CD6C8[])(void);
    D_800CD6C8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_047/nonmatchings/md_MAIN_047", func_800CCBC0);

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

    typedef struct { u16 f0; u16 f1; u16 f2; u16 f3; u16 f4; u16 f5; } Rec;
    typedef struct { u8 flag; u8 idx; u8 cnt; u8 tim; Rec e[16]; } Trail;

    Trail *p = (Trail *)D_800CD6E0;
    s32 node = *(s32 *)(param_1 + 0x34);
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


INCLUDE_ASM("asm/md_MAIN_047/nonmatchings/md_MAIN_047", func_800CD314);



void func_800CD458(void *a0) {

    extern void (*D_800CD6D0[])(void);
    D_800CD6D0[*(u16 *)((s32)a0 + 0x2)]();
}




void func_800CD494(void *a0) {

    extern void (*D_800CD6D8[])(void);
    D_800CD6D8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_800CD4D0(void *arg0) {
    extern s32 D_8011D030;
    extern u8 D_800CD6E0[];
    extern void func_80146C3C(void);
    extern void func_80016714(void *a0, s32 a1);

    unsigned short *p;
    short i;
    s32 k;

    *(s32 *)((s32)arg0 + 0x2C) = 0;
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
    *(u16 *)((s32)arg0 + 2) = *(u16 *)((s32)arg0 + 2) + 1;
}


INCLUDE_ASM("asm/md_MAIN_047/nonmatchings/md_MAIN_047", func_800CD58C);

INCLUDE_ASM("asm/md_MAIN_047/nonmatchings/md_MAIN_047", func_800CD5F8);

INCLUDE_RODATA("asm/md_MAIN_047/nonmatchings/md_MAIN_047", D_800CCB1C);
