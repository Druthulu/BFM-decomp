#include "common.h"

INCLUDE_ASM("asm/md_MAIN_024/nonmatchings/md_MAIN_024", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CAF08[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CAF08[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_024/nonmatchings/md_MAIN_024", func_800CAEB0);

void func_800CAEF8(void) {
}

void func_800CAF00(void) {
}
