#include "common.h"

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7B3C);


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


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7C04);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7CA4);



void func_801E7CC4(void *a0) {

    extern void (*D_801E8AD0[])(void);
    D_801E8AD0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D00(void *a0) {

    extern void (*D_801E8AD8[])(void);
    D_801E8AD8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D3C(void *a0) {

    extern void (*D_801E8B5C[])(void);
    D_801E8B5C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7D78);

INCLUDE_RODATA("asm/md_SC04_026/nonmatchings/md_SC04_026", D_801E7B28);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7DA0);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7E08);

void func_801E7E60(void) {
}



void func_801E7E68(void *a0) {

    extern void (*D_801E8B6C[])(void);
    D_801E8B6C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7EA4);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7EC4);

void func_801E7F2C(void) {
}

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E7F34);



void func_801E7FF8(void *a0) {

    extern void (*D_801E8B78[])(void);
    D_801E8B78[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8034);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E805C);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8254);



void func_801E8284(void *a0) {

    extern void (*D_801E8CF0[])(void);
    D_801E8CF0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E82C0);



void func_801E830C(void) {

    extern s32 D_801EF374;
    D_801EF374 = 1;
}




s32 func_801E8320(void) {

    extern s32 D_801EF374;
    return D_801EF374;
}


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8330);




extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E8394(void) {
        if ((func_80029178(0x10f) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10f, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E83D0);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8470);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E85A4);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8654);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E87F8);



void func_801E8950(void *a0) {

    extern void (*D_801E8EEC[])(void);
    D_801E8EEC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E898C);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E89B0);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E89D4);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E89F8);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8A1C);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8A3C);

INCLUDE_ASM("asm/md_SC04_026/nonmatchings/md_SC04_026", func_801E8A64);



extern void func_80029124(s32 arg0, s32 arg1);
    void func_801E8AA0(void) {
        func_80029124(0xF5, 1);
        func_80029124(0xFB, 1);
    }

