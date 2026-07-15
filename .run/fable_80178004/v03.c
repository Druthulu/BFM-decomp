#include "common.h"

s32 func_80178004(u32 *p, s32 param_2, s32 a2)
{
    extern u32 func_801783D0(s32 a0, s32 a1);
    extern s16 D_8011F81E;
    u32 *w;
    u32 uVar1;
    u32 uVar2;
    u32 uVar5;
    u32 c;
    u32 t;
    s32 n;
    s32 iVar4;

    w = p;
    a2 <<= 0x10;

    *w = ((u32)(w - 5) & 0xffffff) | 0x3000000;
    w[1] = 0x74808080;
    w[2] = a2 | (param_2 & 0xffff);
    w[3] = 0x6d165828;
    w += 5;
    *w = ((u32)(w - 5) & 0xffffff) | 0x3000000;
    w[1] = 0x74808080;
    w[2] = a2 | ((param_2 + 7) & 0xffff);
    w[3] = 0x6d160048;
    w += 5;
    *w = ((u32)(w - 5) & 0xffffff) | 0x3000000;
    w[1] = 0x74808080;
    w[2] = a2 | ((param_2 + 0xd) & 0xffff);
    w[3] = 0x6d160818;
    w += 5;
    *w = ((u32)(w - 5) & 0xffffff) | 0x3000000;
    w[1] = 0x74808080;
    w[2] = a2 | ((param_2 + 0x13) & 0xffff);
    w[3] = 0x6d160028;
    w += 5;
    *w = ((u32)(w - 5) & 0xffffff) | 0x3000000;
    w[1] = 0x74808080;
    w[2] = a2 | ((param_2 + 0x19) & 0xffff);
    w[3] = 0x6d160020;
    w += 5;
    *w = ((u32)(w - 5) & 0xffffff) | 0x3000000;
    w[1] = 0x74808080;
    w[2] = a2 | ((param_2 + 0x3a) & 0xffff);
    w[3] = 0x6d164058;
    w += 5;

    uVar1 = func_801783D0(100 - (D_8011F81E * 0xa198 >> 0x10), 4);
    p = w;
    param_2 += 0x22;
    uVar5 = 0x1000000;
    iVar4 = 0;
    do {
        uVar2 = (uVar1 & 0xffff) >> 0xc;
        if ((uVar2 != 0) || ((s16)iVar4 == 2) || ((s16)iVar4 == 0xff)) {
            uVar5 = 0;
            c = 0x74808080;
        } else {
            c = 0x74808080;
        }
        *p = ((u32)(p - 5) & 0xffffff) | 0x3000000;
        p[2] = a2 | (param_2 & 0xffff) | uVar5;
        p[1] = c;
        t = uVar2 * 8 + 8 | 0x4000;
        p[3] = t | 0x6d160000;
        p += 5;
        param_2 += 8;
        n = iVar4 + 1;
        uVar1 <<= 4;
        iVar4 = n;
    } while ((s16)n < 3);

    return (s32)p;
}
