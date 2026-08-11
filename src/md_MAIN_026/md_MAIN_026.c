#include "common.h"

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CBB10[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBB10[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAF10);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CAF68);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB010);

extern void func_800CB108(void);
void func_800CB078(void) {
    func_800CB108();
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB098);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB108);


extern void func_800CB5D4(void);

void func_800CB134(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB24[])(void);
    if (D_80078EC1 == 0x16) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB24[v0]();
    } else {
        func_800CB5D4();
    }
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB190);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB278);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB3C0);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB470);

extern void func_80162CCC(void);
void func_800CB5D4(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB5F4);


extern void func_800CB8A4(void);

void func_800CB62C(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB48[])(void);
    if (D_80078EC1 == 0x16) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB48[v0]();
    } else {
        func_800CB8A4();
    }
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB688);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB6E8);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB77C);

extern void func_80162CCC(void);
void func_800CB8A4(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB8C4);

INCLUDE_ASM("asm/md_MAIN_026/nonmatchings/md_MAIN_026", func_800CB900);
