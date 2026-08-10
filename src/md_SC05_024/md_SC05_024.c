#include "common.h"

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801ED99C);


extern s32 func_800167F0(s32 a0);

s32 func_801ED9F4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCE0(void *arg0);

s32 func_801EDA18(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EDCE0, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDA64);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDB1C);



void func_801EDB3C(void *a0) {

    extern void (*D_801EE490[])(void);
    D_801EE490[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDB78(void *a0) {

    extern void (*D_801EE498[])(void);
    D_801EE498[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDBB4(void *a0) {

    extern void (*D_801EE51C[])(void);
    D_801EE51C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDBF0);

INCLUDE_RODATA("asm/md_SC05_024/nonmatchings/md_SC05_024", D_801ED988);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDC18);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDC80);

void func_801EDCD8(void) {
}



void func_801EDCE0(void *a0) {

    extern void (*D_801EE52C[])(void);
    D_801EE52C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDD1C);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDD3C);

void func_801EDDA4(void) {
}

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDDAC);



void func_801EDE70(void *a0) {

    extern void (*D_801EE538[])(void);
    D_801EE538[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDEAC);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EDED4);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EE0CC);



void func_801EE10C(void *a0) {

    extern void (*D_801EE678[])(void);
    D_801EE678[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EE148);



void func_801EE194(void) {

    extern s32 D_801F445C;
    D_801F445C = 1;
}




s32 func_801EE1A8(void) {

    extern s32 D_801F445C;
    return D_801F445C;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EE1B8(void) {
        if ((func_80029178(0x10e) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10e, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EE1F4);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EE2B0);

INCLUDE_ASM("asm/md_SC05_024/nonmatchings/md_SC05_024", func_801EE3E4);
