#include "common.h"

extern s32 D_800B9B50;

s32 DsSyncCallback(s32 arg0) {
    s32 *p = &D_800B9B50;
    s32 old = *p;

    *p = arg0;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/gap", DsReadyCallback);


extern void DMACallback(s32 chan, s32 addr);

void DsDataCallback(s32 arg0, s32 arg1) {
    DMACallback(3, arg0);
}
