#include "common.h"

INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CB51C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB51C[*(u8 *)((s32)a0 + 0x197)]();
}


s32 func_800CAE78(u8 *a0)
{
    s32 v = a0[407] + 1;
    a0[407] = v;
    return v;
}


INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CAE8C);

INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CAEF4);

void func_800CAF20(void) {
}


extern void func_80146C3C(void);

void func_800CAF28(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB53C[])(void);
    if (D_80078EC1 == 0x1) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB53C[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CAF84);

INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CB158);

INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CB228);

INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CB304);

INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CB400);

INCLUDE_ASM("asm/md_MAIN_016/nonmatchings/md_MAIN_016", func_800CB458);
