#include "common.h"

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E25FC);


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


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E26C4);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2764);



void func_801E2784(void *a0) {

    extern void (*D_801E3568[])(void);
    D_801E3568[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27C0(void *a0) {

    extern void (*D_801E3570[])(void);
    D_801E3570[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27FC(void *a0) {

    extern void (*D_801E361C[])(void);
    D_801E361C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2838);

INCLUDE_RODATA("asm/md_SC03_134/nonmatchings/md_SC03_134", D_801E25E8);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2860);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E28C8);

void func_801E2920(void) {
}



void func_801E2928(void *a0) {

    extern void (*D_801E362C[])(void);
    D_801E362C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2964);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2984);

void func_801E29EC(void) {
}

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E29F4);



void func_801E2AB8(void *a0) {

    extern void (*D_801E3638[])(void);
    D_801E3638[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2AF4);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2B1C);


s32 func_801E2D14(void) {
    return 39;
}




void func_801E2D1C(void *a0) {

    extern void (*D_801E37B0[])(void);
    D_801E37B0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2D58);



void func_801E2DA4(void) {

    extern s32 D_801E9E34;
    D_801E9E34 = 1;
}




s32 func_801E2DB8(void) {

    extern s32 D_801E9E34;
    return D_801E9E34;
}


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2DC8);




extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E2E2C(void) {
        if ((func_80029178(0x10f) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10f, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2E68);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E2F08);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E303C);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E30EC);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E3290);



void func_801E33E8(void *a0) {

    extern void (*D_801E39AC[])(void);
    D_801E39AC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E3424);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E3448);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E346C);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E3490);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E34B4);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E34D4);

INCLUDE_ASM("asm/md_SC03_134/nonmatchings/md_SC03_134", func_801E34FC);



extern void func_80029124(s32 arg0, s32 arg1);
    void func_801E3538(void) {
        func_80029124(0xF5, 1);
        func_80029124(0xFB, 1);
    }

