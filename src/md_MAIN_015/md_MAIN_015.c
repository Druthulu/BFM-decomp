#include "common.h"

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CBB24[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBB24[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAF0C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAF9C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB140);

extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB190(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB1C0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB21C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB2E0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB474);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB494);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB4F0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB6A4);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB6FC);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB830);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB88C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB930);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB988);
