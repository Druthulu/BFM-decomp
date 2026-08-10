#include "common.h"

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801ED99C);


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


INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDA64);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDB1C);



void func_801EDB3C(void *a0) {

    extern void (*D_801EE3E8[])(void);
    D_801EE3E8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDB78(void *a0) {

    extern void (*D_801EE3F0[])(void);
    D_801EE3F0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDBB4(void *a0) {

    extern void (*D_801EE474[])(void);
    D_801EE474[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDBF0);

INCLUDE_RODATA("asm/md_SC05_023/nonmatchings/md_SC05_023", D_801ED988);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDC18);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDC80);

void func_801EDCD8(void) {
}



void func_801EDCE0(void *a0) {

    extern void (*D_801EE484[])(void);
    D_801EE484[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDD1C);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDD3C);

void func_801EDDA4(void) {
}

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDDAC);



void func_801EDE70(void *a0) {

    extern void (*D_801EE490[])(void);
    D_801EE490[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDEAC);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EDED4);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EE0CC);



void func_801EE10C(void *a0) {

    extern void (*D_801EE598[])(void);
    D_801EE598[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EE148);



void func_801EE158(void) {

    extern s32 D_801F4B74;
    D_801F4B74 = 1;
}




s32 func_801EE16C(void) {

    extern s32 D_801F4B74;
    return D_801F4B74;
}


INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EE17C);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EE21C);

INCLUDE_ASM("asm/md_SC05_023/nonmatchings/md_SC05_023", func_801EE350);
