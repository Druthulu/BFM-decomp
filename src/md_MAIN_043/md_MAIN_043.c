#include "common.h"

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCB20);

void func_800CCB8C(void *a0) {

    extern void (*D_800CD6DC[])(void);
    s32 e;

    e = *(u16 *)((s32)a0 + 0x2) - 2;
    D_800CD6DC[e]();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCBCC);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCC88);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCD04);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCDC4);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCE24);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCEA0);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCEAC);



void func_800CCF14(void *a0) {

    extern void (*D_800CD6EC[])(void);
    D_800CD6EC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCF50);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD054);

extern void func_80162CCC(void);
void func_800CD1D4(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD1F4);

s32 func_800CD258(void *a0, void *a1) {
    s32 v;
    *(u8 *)((s32)a1 + 8) = 0;
    *(u8 *)((s32)a1 + 9) = 0;
    *(u8 *)((s32)a1 + 10) = 0;
    v = (*(u32 *)((s32)a0 + 0x1C)) << 3;
    *(u8 *)((s32)a1 + 14) = 0;
    *(u8 *)((s32)a1 + 12) = v;
    *(u8 *)((s32)a1 + 13) = v;
    return v;
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD27C);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD31C);



void func_800CD3C8(void *a0) {

    extern void (*D_800CD6F8[])(void);
    D_800CD6F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD404);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD57C);

extern void func_80162CCC(void);
void func_800CD650(void) {
    func_80162CCC();
}


extern void func_800233CC(void *arg0, u16 arg1);

void func_800CD670(s32 arg0, void *arg1)
{
    s32 t;

    func_800233CC(arg1, 0x40);
    *(u8 *)(arg1 + 0) = 0;
    *(u8 *)(arg1 + 1) = 0;
    *(u8 *)(arg1 + 2) = 0;
    t = *(s16 *)(arg0 + 0x62) * 12;
    *(u8 *)(arg1 + 6) = 0;
    *(u8 *)(arg1 + 5) = t;
    *(u8 *)(arg1 + 4) = t;
}


void func_800CD6D4(void) {
}

INCLUDE_RODATA("asm/md_MAIN_043/nonmatchings/md_MAIN_043", D_800CCB1C);
