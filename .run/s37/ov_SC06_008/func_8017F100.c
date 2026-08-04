#include "common.h"

extern s32  D_801151D4;
extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C588(s32 a0, s32 a1);
extern u8  *func_8012913C();
extern void func_8017ED80(void);

void func_8017F100(s32 a0)
{
    u16 nv[4];
    s32 g;
    s32 s0;
    s32 idx;

    g = D_801151D4;

    if (*(u16 *)a0 != 0) {
        idx = *(s32 *)(a0 + 0x1C) & 3;
        switch (idx) {
        case 0:
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            break;
        case 1:
            break;
        case 2:
        case 3:
            s0 = (s32)func_8012913C(0x23);
            if (s0 != 0) {
                *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x3F) - 0x20;
                *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x3F) - 0x30;
                {
                    s32 r = rand();
                    s32 t = *(u16 *)(a0 + 0xE);
                    *(s32 *)(s0 + 0x18) = 0;
                    *(s32 *)(s0 + 0x14) = 0;
                    *(s32 *)(s0 + 0x10) = 0;
                    *(s16 *)(s0 + 0xE) = t + (r & 0x3F) - 0x20;
                }
                *(s16 *)(s0 + 0x34) = (rand() & 0x17FF) + 0x800;
                nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
                nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
                nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
                VectorNormalSS(nv, nv);
                *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)nv[0] >> 6);
                *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)nv[1] >> 6);
                *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)nv[2] >> 6);
            }
            break;
        }
        ((void (*)(s32))func_8017ED80)(a0);
    }
}
