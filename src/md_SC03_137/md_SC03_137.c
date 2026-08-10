#include "common.h"

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E25FC);


extern s32 func_800167F0(s32 a0);

s32 func_801E2654(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E2928(void *arg0);

s32 func_801E2678(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E2928, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E26C4);

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2764);



void func_801E2784(void *a0) {

    extern void (*D_801E2F48[])(void);
    D_801E2F48[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27C0(void *a0) {

    extern void (*D_801E2F50[])(void);
    D_801E2F50[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27FC(void *a0) {

    extern void (*D_801E2FD4[])(void);
    D_801E2FD4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2838);

INCLUDE_RODATA("asm/md_SC03_137/nonmatchings/md_SC03_137", D_801E25E8);

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2860);

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E28C8);

void func_801E2920(void) {
}



void func_801E2928(void *a0) {

    extern void (*D_801E2FE4[])(void);
    D_801E2FE4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2964);

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2984);

void func_801E29EC(void) {
}

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E29F4);



void func_801E2AB8(void *a0) {

    extern void (*D_801E2FF0[])(void);
    D_801E2FF0[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2AF4);

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2B1C);


s32 func_801E2D14(void) {
    return 39;
}




void func_801E2D1C(void *a0) {

    extern void (*D_801E30FC[])(void);
    D_801E30FC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2D58);

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2DF8);




extern void func_8014B2A8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801E2E18(void) {
    func_8014B2A8();
    ((s32 (*)(s32, s32))func_8002D4C8)(0x464, 0);
}


INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2E44);

INCLUDE_ASM("asm/md_SC03_137/nonmatchings/md_SC03_137", func_801E2ED8);
