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

extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CD5DC();
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80162FC0(s32 *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328();
extern s32 func_801632F0();
extern u16 D_800CD690[];
extern u16 D_800CD692[];

void func_800CD4BC(s32 arg0) {
    s32 sp18[8];
    s32 temp_s2 = *(s32 *)(arg0 + 0x4C);
    s32 temp_s1 = *(s32 *)(arg0 + 0x20);

    if (func_80146E98(arg0) != 0) {
        func_80146CA0((void *)arg0);
        return;
    }
    *(u16 *)(temp_s1 + 0x28) = D_800CD690[(*(u16 *)(temp_s2 + 0x1C8) & 7) * 2];
    *(u16 *)(temp_s1 + 0x2A) = D_800CD692[(*(u16 *)(temp_s2 + 0x1C8) & 7) * 2];
    func_800CD5DC(arg0, sp18);
    func_80163194(arg0, 0, -0x10000, 0, (s32)sp18);
    func_80162FC0((s32 *)arg0);
    *(u16 *)(temp_s1 + 0x18) = *(u16 *)(temp_s1 + 0x1A) =
        *(u16 *)(temp_s1 + 0x1A) + 0x200;
    func_80163408(arg0, 0x24, 0x80, 4);
    func_80163328(arg0);
    func_801632F0(arg0);
}


extern void func_80162CCC(void);
void func_800CD5BC(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD5DC);

INCLUDE_RODATA("asm/md_MAIN_045/nonmatchings/md_MAIN_045", D_800CCB1C);
