#include "common.h"

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CAE14);



void func_800CAE4C(void *a0) {

    extern void (*D_800CBE34[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE34[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED8(u8 *a0);
void func_800CAE90(u8 *a0) {
    if (func_80161104()) {
        func_800CAED8(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CAED8);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CAF80);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB02C);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB040);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB0B4);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB228);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB424);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB4AC);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB4CC);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB4D4);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB5CC);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB61C);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB6F4);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB804);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB860);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBAAC);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBB54);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBBDC);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBC10);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBC40);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBC60);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBCBC);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBD90);
