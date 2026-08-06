#include "common.h"

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAE0C);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAE70);



void func_800CAEC0(void *a0) {

    extern void (*D_800CB610[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB610[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAF4C(u8 *a0);
void func_800CAF04(u8 *a0) {
    if (func_80161104()) {
        func_800CAF4C(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAF4C);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAF94);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB014);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB028);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB09C);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB150);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB2A8);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB30C);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB358);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB378);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB424);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB480);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB55C);
