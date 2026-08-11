#include "common.h"

INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CB29C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB29C[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CAF60);

INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CAFD0);


extern void func_800CB24C(void);

void func_800CB054(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB2A8[])(void);
    if (D_80078EC1 == 0x9) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB2A8[v0]();
    } else {
        func_800CB24C();
    }
}


INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CB0B0);

INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CB188);

INCLUDE_ASM("asm/md_MAIN_032/nonmatchings/md_MAIN_032", func_800CB24C);
