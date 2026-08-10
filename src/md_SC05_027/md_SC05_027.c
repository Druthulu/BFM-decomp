#include "common.h"

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801ED9B0);


extern s32 func_800167F0(s32 a0);

s32 func_801EDA08(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCF4(void *arg0);

s32 func_801EDA2C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EDCF4, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDA78);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDB30);



void func_801EDB50(void *a0) {

    extern void (*D_801EE5C4[])(void);
    D_801EE5C4[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDB8C(void *a0) {

    extern void (*D_801EE5CC[])(void);
    D_801EE5CC[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDBC8(void *a0) {

    extern void (*D_801EE650[])(void);
    D_801EE650[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDC04);

INCLUDE_RODATA("asm/md_SC05_027/nonmatchings/md_SC05_027", D_801ED988);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDC2C);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDC94);

void func_801EDCEC(void) {
}



void func_801EDCF4(void *a0) {

    extern void (*D_801EE660[])(void);
    D_801EE660[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDD30);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDD50);

void func_801EDDB8(void) {
}

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDDC0);



void func_801EDE84(void *a0) {

    extern void (*D_801EE66C[])(void);
    D_801EE66C[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDEC0);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDEE8);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE080);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE0C0);



void func_801EE21C(void *a0) {

    extern void (*D_801EE988[])(void);
    D_801EE988[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE258);



void func_801EE268(void) {

    extern s32 D_801F599C;
    D_801F599C = 1;
}




s32 func_801EE27C(void) {

    extern s32 D_801F599C;
    return D_801F599C;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EE28C(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE2C8);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE3A4);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE3C4);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE3E4);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE470);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE488);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE4B8);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE514);
