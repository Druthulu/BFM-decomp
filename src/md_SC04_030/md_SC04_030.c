#include "common.h"

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7B3C);


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


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7C04);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7CA4);



void func_801E7CC4(void *a0) {

    extern void (*D_801E85D4[])(void);
    D_801E85D4[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D00(void *a0) {

    extern void (*D_801E85DC[])(void);
    D_801E85DC[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D3C(void *a0) {

    extern void (*D_801E8660[])(void);
    D_801E8660[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7D78);

INCLUDE_RODATA("asm/md_SC04_030/nonmatchings/md_SC04_030", D_801E7B28);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7DA0);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7E08);

void func_801E7E60(void) {
}



void func_801E7E68(void *a0) {

    extern void (*D_801E8670[])(void);
    D_801E8670[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7EA4);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7EC4);

void func_801E7F2C(void) {
}

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7F34);



void func_801E7FF8(void *a0) {

    extern void (*D_801E867C[])(void);
    D_801E867C[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E8034);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E805C);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E8254);

void func_801E8284(void) {
}

void func_801E828C(void) {
}

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E8294);



void func_801E83F0(void *a0) {

    extern void (*D_801E87C4[])(void);
    D_801E87C4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E842C);



void func_801E843C(void) {

    extern s32 D_801F14E0;
    D_801F14E0 = 1;
}




s32 func_801E8450(void) {

    extern s32 D_801F14E0;
    return D_801F14E0;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E8460(void) {
        if ((func_80029178(0x112) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x112, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E849C);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E853C);
