#include "common.h"

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF48C);


extern s32 func_800167F0(s32 a0);

s32 func_801EF4E4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EF7A8(void *arg0);

s32 func_801EF508(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EF7A8, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF554);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF5E4);



void func_801EF604(void *a0) {

    extern void (*D_801EFF04[])(void);
    D_801EFF04[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF640(void *a0) {

    extern void (*D_801EFF0C[])(void);
    D_801EFF0C[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF67C(void *a0) {

    extern void (*D_801EFF90[])(void);
    D_801EFF90[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF6B8);

INCLUDE_RODATA("asm/md_SC03_079/nonmatchings/md_SC03_079", D_801EF468);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF6E0);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF748);

void func_801EF7A0(void) {
}



void func_801EF7A8(void *a0) {

    extern void (*D_801EFFA0[])(void);
    D_801EFFA0[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF7E4);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF804);

void func_801EF86C(void) {
}

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF874);



void func_801EF938(void *a0) {

    extern void (*D_801EFFAC[])(void);
    D_801EFFAC[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF974);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EF99C);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EFB94);



void func_801EFCF0(void *a0) {

    extern void (*D_801F00F4[])(void);
    D_801F00F4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EFD2C);



void func_801EFD3C(void) {

    extern s32 D_801F8E10;
    D_801F8E10 = 1;
}




s32 func_801EFD50(void) {

    extern s32 D_801F8E10;
    return D_801F8E10;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFD60(void) {
        if ((func_80029178(0x112) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x112, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EFD9C);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EFE3C);

INCLUDE_ASM("asm/md_SC03_079/nonmatchings/md_SC03_079", func_801EFED4);
