#include "common.h"

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7B34);


extern s32 func_800167F0(s32 a0);

s32 func_801E7B8C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E60(void *arg0);

s32 func_801E7BB0(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E60, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7BFC);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7C9C);



void func_801E7CBC(void *a0) {

    extern void (*D_801E8558[])(void);
    D_801E8558[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7CF8(void *a0) {

    extern void (*D_801E8560[])(void);
    D_801E8560[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D34(void *a0) {

    extern void (*D_801E85E4[])(void);
    D_801E85E4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7D70);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7D98);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7E00);

void func_801E7E58(void) {
}



void func_801E7E60(void *a0) {

    extern void (*D_801E85F4[])(void);
    D_801E85F4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7E9C);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7EBC);

void func_801E7F24(void) {
}

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7F2C);



void func_801E7FF0(void *a0) {

    extern void (*D_801E8600[])(void);
    D_801E8600[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E802C);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E8054);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E824C);



void func_801E827C(void *a0) {

    extern void (*D_801E8708[])(void);
    D_801E8708[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E82B8);



void func_801E82C8(void) {

    extern s32 D_801EECE4;
    D_801EECE4 = 1;
}




s32 func_801E82DC(void) {

    extern s32 D_801EECE4;
    return D_801EECE4;
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E82EC);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E838C);

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E84C0);

INCLUDE_RODATA("asm/md_SC04_024/nonmatchings/md_SC04_024", D_801E7B28);

INCLUDE_RODATA("asm/md_SC04_024/nonmatchings/md_SC04_024", D_801E7B2C);
