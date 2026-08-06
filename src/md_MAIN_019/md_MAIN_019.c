#include "common.h"

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CC104[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CC104[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CAF08);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB0C8);

extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB170(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB1A0);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB2C8);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB324);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB3FC);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB4A8);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB4C8);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB578);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB9F8);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBC0C);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBD0C);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBD68);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBE38);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBEC0);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBF60);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBF80);
