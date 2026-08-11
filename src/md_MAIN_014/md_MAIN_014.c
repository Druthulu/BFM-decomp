#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB610;
    func_800183E0(&D_800CB610);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB5BC[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB5BC[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CAEB0);

INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CAF20);

void func_800CAF4C(void) {
}



void func_800CAF54(void *a0) {

    extern void (*D_800CB5DC[])(void);
    D_800CB5DC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CAF90);

INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CB164);

INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CB254);

INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CB358);

INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CB470);

INCLUDE_ASM("asm/md_MAIN_014/nonmatchings/md_MAIN_014", func_800CB4D8);
