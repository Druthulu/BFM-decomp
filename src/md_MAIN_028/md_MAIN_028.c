#include "common.h"

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CBE94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE94[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB0D8);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB32C);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB350);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB3AC);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB484);

extern s32 func_800CB6D4(s32 a0);
extern s32 func_800CB600(void *a0);
void func_800CB564(int param_1)
{
    if (((int (*)(void))func_800CB6D4)() != 0) {
        ((void (*)(int))func_800CB600)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB59C);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB600);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB620);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB684);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB6D4);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB8A0);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBA74);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBAD0);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBBA0);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBC7C);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBD78);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBDD0);
