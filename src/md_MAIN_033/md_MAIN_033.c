#include "common.h"

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB8A4[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB8A4[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
void func_800CAE88(u8 *a0) {
    if (func_80161104()) {
        func_800CAED0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CAED0);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CAF24);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CAFD4);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CAFE8);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB058);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB190);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB2C8);

extern void func_80162CCC(void);
void func_800CB384(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB3A4);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB3D8);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB4EC);


extern void func_80146C3C(void);

void func_800CB580(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB8F0[])(void);
    if (D_80078EC1 == 0xb) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB8F0[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB5DC);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB6D4);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB720);

INCLUDE_ASM("asm/md_MAIN_033/nonmatchings/md_MAIN_033", func_800CB76C);
