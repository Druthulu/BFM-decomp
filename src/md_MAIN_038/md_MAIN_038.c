#include "common.h"

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CBBA8[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBBA8[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
void func_800CAE88(u8 *a0) {
    if (func_80161104()) {
        func_800CAED0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAED0);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAF1C);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAFAC);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB194);

extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB1E4(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}


INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB214);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB270);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB360);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB4F8);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB518);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB574);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB728);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB780);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB8B4);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB910);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB9B4);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CBA0C);
