#include "common.h"

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAE0C);



void func_800CAE64(void *a0) {

    extern void (*D_800CB49C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB49C[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEE0();
void func_800CAEA8(void *a0) {
    func_800CAEE0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAEE0);

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAF30);

void func_800CAF5C(void) {
}

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAF64);

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAF90);

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CB0D0);

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CB2AC);



void func_800CB460(void *a0) {

    extern void (*D_800CB4BC[])(void);
    D_800CB4BC[*(u16 *)((s32)a0 + 0x2)]();
}

