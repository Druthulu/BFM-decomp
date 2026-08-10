#include "common.h"

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF47C);


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


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF544);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF5D4);



void func_801EF5F4(void *a0) {

    extern void (*D_801F0400[])(void);
    D_801F0400[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF630(void *a0) {

    extern void (*D_801F0408[])(void);
    D_801F0408[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF66C(void *a0) {

    extern void (*D_801F048C[])(void);
    D_801F048C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF6A8);

INCLUDE_RODATA("asm/md_SC03_075/nonmatchings/md_SC03_075", D_801EF468);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF6D0);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF738);

void func_801EF790(void) {
}



void func_801EF798(void *a0) {

    extern void (*D_801F049C[])(void);
    D_801F049C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF7D4);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF7F4);

void func_801EF85C(void) {
}

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF864);



void func_801EF928(void *a0) {

    extern void (*D_801F04A8[])(void);
    D_801F04A8[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF964);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF98C);



void func_801EFB84(void *a0) {

    extern void (*D_801F0620[])(void);
    D_801F0620[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFBC0);



void func_801EFC0C(void) {

    extern s32 D_801F6CA4;
    D_801F6CA4 = 1;
}




s32 func_801EFC20(void) {

    extern s32 D_801F6CA4;
    return D_801F6CA4;
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFC30);




extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFC94(void) {
        if ((func_80029178(0x10f) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10f, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFCD0);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFD70);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFEA4);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFF54);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F00F8);



void func_801F0250(void *a0) {

    extern void (*D_801F081C[])(void);
    D_801F081C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F028C);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F02B0);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F02D4);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F02F8);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F031C);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F033C);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F0364);



extern void func_80029124(s32 arg0, s32 arg1);
    void func_801F03A0(void) {
        func_80029124(0xF5, 1);
        func_80029124(0xFB, 1);
    }


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F03D0);
