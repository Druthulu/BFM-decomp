#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB538;
    func_800183E0(&D_800CB538);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB4FC[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB4FC[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CAEB0);

INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CAF38);

void func_800CAF8C(void) {
}

INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CAF94);

INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CB0C8);



void func_800CB33C(void *a0) {

    extern void (*D_800CB508[])(void);
    D_800CB508[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CB378);

INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CB478);
