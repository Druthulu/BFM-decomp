#include "common.h"

void func_800CCB20(void) {
}

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCB28);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCB78);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCC54);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCD2C);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCDD8);

extern void func_80162CCC(void);
void func_800CCE60(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCE80);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCF28);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCF58);

extern void func_80147364(s32 a, s32 b);
void func_800CCF84(void) {
    func_80147364(0x4, 0x8E0);
}


extern s32 func_80161A00(s32 a0);
extern void (*D_800CD6B0[])(void);
extern void func_800CD1A8(void);

void func_800CCFA8(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD6B0[*(u16 *)(param_1 + 2)]();
    if (func_80161A00(iVar1) == 0) {
        ((void (*)(s32))func_800CD1A8)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD010);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD0CC);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD1A8);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD204);

extern s32 func_80161A00(s32 a0);
extern void (*D_800CD6C4[])(void);
extern void func_800CD5BC(void);

void func_800CD328(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD6C4[*(u16 *)(param_1 + 2)]();
    if (func_80161A00(iVar1) == 0) {
        ((void (*)(s32))func_800CD5BC)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD390);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD4BC);

extern void func_80162CCC(void);
void func_800CD5BC(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD5DC);

INCLUDE_RODATA("asm/md_MAIN_045/nonmatchings/md_MAIN_045", D_800CCB1C);
