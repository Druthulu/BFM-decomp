#include "common.h"

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF47C);


extern s32 func_800167F0(s32 a0);

s32 func_801EF4D4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EF798(void *arg0);

s32 func_801EF4F8(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EF798, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF544);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF5D4);



void func_801EF5F4(void *a0) {

    extern void (*D_801EFE90[])(void);
    D_801EFE90[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF630(void *a0) {

    extern void (*D_801EFE98[])(void);
    D_801EFE98[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF66C(void *a0) {

    extern void (*D_801EFF1C[])(void);
    D_801EFF1C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF6A8);

INCLUDE_RODATA("asm/md_SC03_073/nonmatchings/md_SC03_073", D_801EF468);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF6D0);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF738);

void func_801EF790(void) {
}



void func_801EF798(void *a0) {

    extern void (*D_801EFF2C[])(void);
    D_801EFF2C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF7D4);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF7F4);

void func_801EF85C(void) {
}

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF864);



void func_801EF928(void *a0) {

    extern void (*D_801EFF38[])(void);
    D_801EFF38[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF964);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EF98C);



void func_801EFB84(void *a0) {

    extern void (*D_801F0040[])(void);
    D_801F0040[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EFBC0);



void func_801EFBD0(void) {

    extern s32 D_801F661C;
    D_801F661C = 1;
}




s32 func_801EFBE4(void) {

    extern s32 D_801F661C;
    return D_801F661C;
}


INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EFBF4);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EFC94);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EFDC8);

INCLUDE_ASM("asm/md_SC03_073/nonmatchings/md_SC03_073", func_801EFE60);
