#include "common.h"

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E25FC);


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


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E26C4);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2764);



void func_801E2784(void *a0) {

    extern void (*D_801E32F0[])(void);
    D_801E32F0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27C0(void *a0) {

    extern void (*D_801E32F8[])(void);
    D_801E32F8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27FC(void *a0) {

    extern void (*D_801E337C[])(void);
    D_801E337C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2838);

INCLUDE_RODATA("asm/md_SC03_138/nonmatchings/md_SC03_138", D_801E25E8);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2860);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E28C8);

void func_801E2920(void) {
}



void func_801E2928(void *a0) {

    extern void (*D_801E338C[])(void);
    D_801E338C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2964);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2984);

void func_801E29EC(void) {
}

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E29F4);



void func_801E2AB8(void *a0) {

    extern void (*D_801E3398[])(void);
    D_801E3398[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2AF4);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2B1C);



void func_801E2D14(void *a0) {

    extern void (*D_801E3464[])(void);
    D_801E3464[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2D50);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2D9C);



void func_801E2DE8(void) {

    extern s32 D_801EC2C4;
    extern s32 D_801E2460;
    D_801E2460 = D_801EC2C4;
}


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2E00);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2EC4);


s32 func_801E2F98(void) {
    return 39;
}


void func_801E2FA0(void) {
}

void func_801E2FA8(void) {
}

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E2FB0);



void func_801E310C(void *a0) {

    extern void (*D_801E35A8[])(void);
    D_801E35A8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E3148);



void func_801E3158(void) {

    extern s32 D_801EC2C8;
    D_801EC2C8 = 1;
}




s32 func_801E316C(void) {

    extern s32 D_801EC2C8;
    return D_801EC2C8;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E317C(void) {
        if ((func_80029178(0x112) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x112, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E31B8);

INCLUDE_ASM("asm/md_SC03_138/nonmatchings/md_SC03_138", func_801E3258);
