#include "common.h"

INCLUDE_ASM("asm/md_MAIN_020/nonmatchings/md_MAIN_020", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CB260[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB260[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_020/nonmatchings/md_MAIN_020", func_800CAEB0);

void func_800CAF10(void) {
}

INCLUDE_ASM("asm/md_MAIN_020/nonmatchings/md_MAIN_020", func_800CAF18);

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFFC(void);
void func_800CAF38(s32 *a0) {
    func_80147078(a0, 31);
    ((void (*)(void *))func_800CAFFC)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFA0(void *a0);
void func_800CAF6C(s32 *a0) {
    func_80147078(a0, 31);
    func_800CAFA0(a0);
}




void func_800CAFA0(void *a0) {

    extern void (*D_800CB26C[])(void);
    D_800CB26C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CAFFC(void);
void func_800CAFDC(void) {
    func_800CAFFC();
}


INCLUDE_ASM("asm/md_MAIN_020/nonmatchings/md_MAIN_020", func_800CAFFC);

INCLUDE_ASM("asm/md_MAIN_020/nonmatchings/md_MAIN_020", func_800CB034);

INCLUDE_ASM("asm/md_MAIN_020/nonmatchings/md_MAIN_020", func_800CB148);

INCLUDE_ASM("asm/md_MAIN_020/nonmatchings/md_MAIN_020", func_800CB17C);
