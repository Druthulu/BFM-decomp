#include "common.h"
#include "../shared/engine_prelude.h"


typedef void (*Handler)(struct Entry_8016E95C *);
extern s32 func_801506A4(s32 a0, s32 a1);
extern s32 func_80161CD0(s32 a0, s32 a1);
#include "../shared/ov/func_80181538__27797037.h"


extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void *param_1);
extern void func_8012C218(void *a0);
extern s32 D_801270CC;

void func_801815F4(s32 param_1) {
    ((s32 (*)(s32))func_8012AD80)(param_1);
    if (func_8012BEE8(param_1) == 0) {
        return;
    }
    switch ((s32)((u32)CAST_SIGN(u16, param_1, 0x70) << 0x10) >> 0x18) {
    case 0:
    case 1:
    case 2:
    case 5:
    case 6:
        ((s32 (*)(s32))func_8012C098)(param_1);
        return;
    case 3:
    case 7:
        ((s32 (*)(s32))func_8012C218)(param_1);
        return;
    case 4:
        D_801270CC = D_801270CC + -1;
        ((s32 (*)(s32))func_8012C218)(param_1);
        return;
    default:
        return;
    }
}
