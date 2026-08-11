#include "common.h"

INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB318[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB318[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CAF2C);

extern void func_80147364(s32 a, s32 b);
void func_800CAF7C(void) {
    func_80147364(0x4, 0x47C);
}


INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CAFA0);



void func_800CB190(void *a0) {

    extern void (*D_800CB350[])(void);
    D_800CB350[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CB1CC);

INCLUDE_ASM("asm/md_MAIN_017/nonmatchings/md_MAIN_017", func_800CB2CC);
