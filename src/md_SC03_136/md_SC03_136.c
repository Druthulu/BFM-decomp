#include "common.h"

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2610);


extern s32 func_800167F0(s32 a0);

s32 func_801E2668(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E293C(void *arg0);

s32 func_801E268C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E293C, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E26D8);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2778);



void func_801E2798(void *a0) {

    extern void (*D_801E31D4[])(void);
    D_801E31D4[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27D4(void *a0) {

    extern void (*D_801E31DC[])(void);
    D_801E31DC[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E2810(void *a0) {

    extern void (*D_801E3260[])(void);
    D_801E3260[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E284C);

INCLUDE_RODATA("asm/md_SC03_136/nonmatchings/md_SC03_136", D_801E25E8);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2874);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E28DC);

void func_801E2934(void) {
}



void func_801E293C(void *a0) {

    extern void (*D_801E3270[])(void);
    D_801E3270[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2978);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2998);

void func_801E2A00(void) {
}

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2A08);



void func_801E2ACC(void *a0) {

    extern void (*D_801E327C[])(void);
    D_801E327C[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2B08);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2B30);


s32 func_801E2CC8(void) {
    return 39;
}


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2CD0);



void func_801E2E2C(void *a0) {

    extern void (*D_801E3598[])(void);
    D_801E3598[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2E68);



void func_801E2E78(void) {

    extern s32 D_801EA5AC;
    D_801EA5AC = 1;
}




s32 func_801E2E8C(void) {

    extern s32 D_801EA5AC;
    return D_801EA5AC;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E2E9C(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2ED8);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2FB4);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2FD4);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E2FF4);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E3080);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E3098);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E30C8);

INCLUDE_ASM("asm/md_SC03_136/nonmatchings/md_SC03_136", func_801E3124);
