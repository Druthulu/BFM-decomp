#include "common.h"

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CBE94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE94[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB0D8);

extern void func_80147364(s32 a, s32 b);
void func_800CB32C(void) {
    func_80147364(0x4, 0x838);
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB350);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB3AC);

extern u16 D_800B99DA;
extern s32 func_800CB6D4(s32 a0);
extern void func_800CB684(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 rand(void);

void func_800CB484(s32 *a0) {
    u16 *p = *(u16 **)((u8 *)a0 + 0x20);
    if (*(s32 *)((u8 *)a0 + 0x54) != 0) {
        if (D_800B99DA & 1) {
            p[0x15] = 0x100;
        } else {
            p[0x15] = 0x120;
        }
    }
    if (func_800CB6D4((s32)a0) != 0) {
        s16 v = *(u16 *)((u8 *)a0 + 0x18);
        *(u16 *)((u8 *)a0 + 0x18) = v + 1;
        if (v >= 4) {
            func_800CB684((s32)a0, 0x200);
            func_80146CA0(a0);
            return;
        }
        if (*(s32 *)((u8 *)a0 + 0x54) != 0 && (rand() & 3) == 0) {
            func_80146E90(a0, 0x20);
            *(u16 *)((u8 *)a0 + 2) = 3;
        } else {
            func_800CB684((s32)a0, 0x80);
        }
    }
}


extern s32 func_800CB6D4(s32 a0);
extern s32 func_800CB600();
void func_800CB564(int param_1)
{
    if (((int (*)(void))func_800CB6D4)() != 0) {
        ((void (*)(int))func_800CB600)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB59C);

    extern void func_80162CCC(void);
    s32 func_800CB600(void)
{
        func_80162CCC();
    }


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB620);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB684);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB6D4);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CB8A0);

extern u8 D_80078EC1;
extern void (*D_800CBEE0[])();
extern void func_80146C3C();

void func_800CBA74(int param_1)
{
    if (D_80078EC1 != 21) {
        func_80146C3C();
    } else {
        D_800CBEE0[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBAD0);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBBA0);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBC7C);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBD78);

INCLUDE_ASM("asm/md_MAIN_028/nonmatchings/md_MAIN_028", func_800CBDD0);
