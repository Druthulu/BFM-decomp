#include "common.h"

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF47C);


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


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF544);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF5D4);



void func_801EF5F4(void *a0) {

    extern void (*D_801EFF38[])(void);
    D_801EFF38[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF630(void *a0) {

    extern void (*D_801EFF40[])(void);
    D_801EFF40[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF66C(void *a0) {

    extern void (*D_801EFFC4[])(void);
    D_801EFFC4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF6A8);

INCLUDE_RODATA("asm/md_SC03_074/nonmatchings/md_SC03_074", D_801EF468);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF6D0);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF738);

void func_801EF790(void) {
}



void func_801EF798(void *a0) {

    extern void (*D_801EFFD4[])(void);
    D_801EFFD4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF7D4);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF7F4);

void func_801EF85C(void) {
}

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF864);



void func_801EF928(void *a0) {

    extern void (*D_801EFFE0[])(void);
    D_801EFFE0[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF964);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF98C);



void func_801EFB84(void *a0) {

    extern void (*D_801F0120[])(void);
    D_801F0120[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFBC0);



void func_801EFC0C(void) {

    extern s32 D_801F5F04;
    D_801F5F04 = 1;
}




s32 func_801EFC20(void) {

    extern s32 D_801F5F04;
    return D_801F5F04;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFC30(void) {
        if ((func_80029178(0x10e) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10e, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFC6C);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFD28);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFE5C);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFF08);
