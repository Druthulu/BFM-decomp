#include "common.h"

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CB7D4[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB7D4[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CAF08);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CAF88);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CAF9C);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB028);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB118);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB2B4);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB338);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB358);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB3BC);

void func_800CB634(s32 a0) {
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(u16 *)(a0 + 0x12) = 0;
    *(u16 *)(a0 + 0x10) = 0x80;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB658);
