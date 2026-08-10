#include "common.h"

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF47C);


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


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF544);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF5D4);



void func_801EF5F4(void *a0) {

    extern void (*D_801EFDE0[])(void);
    D_801EFDE0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF630(void *a0) {

    extern void (*D_801EFDE8[])(void);
    D_801EFDE8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF66C(void *a0) {

    extern void (*D_801EFE6C[])(void);
    D_801EFE6C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF6A8);

INCLUDE_RODATA("asm/md_SC03_078/nonmatchings/md_SC03_078", D_801EF468);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF6D0);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF738);

void func_801EF790(void) {
}



void func_801EF798(void *a0) {

    extern void (*D_801EFE7C[])(void);
    D_801EFE7C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF7D4);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF7F4);

void func_801EF85C(void) {
}

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF864);



void func_801EF928(void *a0) {

    extern void (*D_801EFE88[])(void);
    D_801EFE88[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF964);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF98C);



void func_801EFB84(void *a0) {

    extern void (*D_801EFF94[])(void);
    D_801EFF94[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EFBC0);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EFC60);




extern void func_8014B2A8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801EFC80(void) {
    func_8014B2A8();
    ((s32 (*)(s32, s32))func_8002D4C8)(0x464, 0);
}


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EFCAC);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EFD40);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EFDB0);
