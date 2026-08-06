#include "common.h"

INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB458[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB458[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAF44);

INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAF84);

INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAFA8);

INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CB158);

INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CB1EC);



void func_800CB41C(void *a0) {

    extern void (*D_800CB490[])(void);
    D_800CB490[*(u16 *)((s32)a0 + 0x2)]();
}

