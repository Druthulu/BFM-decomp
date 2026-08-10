#include "common.h"

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801ED99C);


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


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDA64);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDB1C);



void func_801EDB3C(void *a0) {

    extern void (*D_801EE958[])(void);
    D_801EE958[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDB78(void *a0) {

    extern void (*D_801EE960[])(void);
    D_801EE960[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDBB4(void *a0) {

    extern void (*D_801EE9E4[])(void);
    D_801EE9E4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDBF0);

INCLUDE_RODATA("asm/md_SC05_025/nonmatchings/md_SC05_025", D_801ED988);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDC18);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDC80);

void func_801EDCD8(void) {
}



void func_801EDCE0(void *a0) {

    extern void (*D_801EE9F4[])(void);
    D_801EE9F4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDD1C);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDD3C);

void func_801EDDA4(void) {
}

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDDAC);



void func_801EDE70(void *a0) {

    extern void (*D_801EEA00[])(void);
    D_801EEA00[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDEAC);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDED4);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE0CC);



void func_801EE10C(void *a0) {

    extern void (*D_801EEB78[])(void);
    D_801EEB78[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE148);



void func_801EE194(void) {

    extern s32 D_801F51FC;
    D_801F51FC = 1;
}




s32 func_801EE1A8(void) {

    extern s32 D_801F51FC;
    return D_801F51FC;
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE1B8);




extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EE21C(void) {
        if ((func_80029178(0x10f) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10f, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE258);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE2F8);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE42C);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE4DC);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE680);



void func_801EE7D8(void *a0) {

    extern void (*D_801EED74[])(void);
    D_801EED74[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE814);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE838);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE85C);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE880);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE8A4);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE8C4);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE8EC);



extern void func_80029124(s32 arg0, s32 arg1);
    void func_801EE928(void) {
        func_80029124(0xF5, 1);
        func_80029124(0xFB, 1);
    }

