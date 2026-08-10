#include "common.h"

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7B3C);


extern s32 func_800167F0(s32 a0);

s32 func_801E7B94(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E68(void *arg0);

s32 func_801E7BB8(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E68, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7C04);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7CA4);



void func_801E7CC4(void *a0) {

    extern void (*D_801E84B0[])(void);
    D_801E84B0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D00(void *a0) {

    extern void (*D_801E84B8[])(void);
    D_801E84B8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D3C(void *a0) {

    extern void (*D_801E853C[])(void);
    D_801E853C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7D78);

INCLUDE_RODATA("asm/md_SC04_029/nonmatchings/md_SC04_029", D_801E7B28);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7DA0);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7E08);

void func_801E7E60(void) {
}



void func_801E7E68(void *a0) {

    extern void (*D_801E854C[])(void);
    D_801E854C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7EA4);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7EC4);

void func_801E7F2C(void) {
}

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E7F34);



void func_801E7FF8(void *a0) {

    extern void (*D_801E8558[])(void);
    D_801E8558[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E8034);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E805C);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E8254);



void func_801E8284(void *a0) {

    extern void (*D_801E8664[])(void);
    D_801E8664[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E82C0);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E8360);




extern void func_8014B2A8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801E8380(void) {
    func_8014B2A8();
    ((s32 (*)(s32, s32))func_8002D4C8)(0x464, 0);
}


INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E83AC);

INCLUDE_ASM("asm/md_SC04_029/nonmatchings/md_SC04_029", func_801E8440);
