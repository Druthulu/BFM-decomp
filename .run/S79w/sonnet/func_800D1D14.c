#include "common.h"

extern s32 D_800D3630[];
extern u8  D_800D3618[];
extern u8  D_800D3620[];
extern s32 D_800D3624[];

extern void func_8001534C(s32 idx, s32 a1, s16 x, s16 y, u8 arg4, u8 arg5);

void func_800D1D14(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        func_8001534C(*(s16 *) &D_800D3630[arg0], (s32) D_800D3618, 0, 0, 0, 0);
    } else {
        func_8001534C(*(s16 *) &D_800D3630[arg0], D_800D3624[arg0], 0x50, D_800D3620[arg0], 0, 0);
    }
}
