#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CC160;
    func_800183E0(&D_800CC160);
}




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


extern void func_800CB4A8(void);

void func_800CB2C8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CC124[])(void);
    if (D_80078EC1 == 0xd) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC124[v0]();
    } else {
        func_800CB4A8();
    }
}


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB324);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB3FC);

extern void func_80162CCC(void);
void func_800CB4A8(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB4C8);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB578);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB9F8);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBC0C);



extern void func_80162CCC(void);

void func_800CBD0C(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CC130[])(void);
    if (D_80078EC1 == 0xd) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC130[v0]();
    } else {
        func_80162CCC();
    }
}


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBD68);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBE38);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBEC0);

extern void func_80162CCC(void);
void func_800CBF60(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBF80);
