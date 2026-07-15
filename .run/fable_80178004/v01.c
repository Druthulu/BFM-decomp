#include "common.h"

s32 func_80178004(u32 *p, s32 param_2, s32 a2)
{
    extern u32 func_801783D0(s32 a0, s32 a1);
    extern s16 D_8011F81E;
    u32 *puVar3;
    u32 *q;
    u32 uVar1;
    u32 uVar2;
    u32 uVar5;
    s32 iVar4;

    a2 <<= 0x10;

    *p = ((u32)(p - 5) & 0xffffff) | 0x3000000;
    p[1] = 0x74808080;
    p[2] = a2 | (param_2 & 0xffff);
    p[3] = 0x6d165828;
    p += 5;
    *p = ((u32)(p - 5) & 0xffffff) | 0x3000000;
    p[1] = 0x74808080;
    p[2] = a2 | ((param_2 + 7) & 0xffff);
    p[3] = 0x6d160048;
    p += 5;
    *p = ((u32)(p - 5) & 0xffffff) | 0x3000000;
    p[1] = 0x74808080;
    p[2] = a2 | ((param_2 + 0xd) & 0xffff);
    p[3] = 0x6d160818;
    p += 5;
    *p = ((u32)(p - 5) & 0xffffff) | 0x3000000;
    p[1] = 0x74808080;
    p[2] = a2 | ((param_2 + 0x13) & 0xffff);
    p[3] = 0x6d160028;
    p += 5;
    *p = ((u32)(p - 5) & 0xffffff) | 0x3000000;
    p[1] = 0x74808080;
    p[2] = a2 | ((param_2 + 0x19) & 0xffff);
    p[3] = 0x6d160020;
    p += 5;
    *p = ((u32)(p - 5) & 0xffffff) | 0x3000000;
    p[1] = 0x74808080;
    p[2] = a2 | ((param_2 + 0x3a) & 0xffff);
    p[3] = 0x6d164058;
    p += 5;

    uVar1 = func_801783D0(100 - (D_8011F81E * 0xa198 >> 0x10), 4);
    puVar3 = p;
    param_2 += 0x22;
    uVar5 = 0x1000000;
    iVar4 = 0;
    q = puVar3 + 3;
    do {
        uVar2 = (uVar1 & 0xffff) >> 0xc;
        if ((uVar2 != 0) || ((s16)iVar4 == 2) || ((s16)iVar4 == 0xff)) {
            uVar5 = 0;
        }
        *puVar3 = ((u32)(puVar3 - 5) & 0xffffff) | 0x3000000;
        q[-1] = a2 | (param_2 & 0xffff) | uVar5;
        q[-2] = 0x74808080;
        *q = uVar2 * 8 + 8 | 0x6d164000;
        q += 5;
        puVar3 += 5;
        param_2 += 8;
        iVar4 += 1;
        uVar1 <<= 4;
    } while ((s16)iVar4 < 3);

    return (s32)puVar3;
}
