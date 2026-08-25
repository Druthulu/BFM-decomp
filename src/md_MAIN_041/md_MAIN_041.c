#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB85C;
    func_800183E0(&D_800CB85C);
}




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

void func_800CAF88(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


extern u8 D_80078EC1;
extern void (*D_800CB7EC[])(void);
extern void func_80162D28(s32 *a0);
extern void func_800CB338(void);

void func_800CAF9C(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1E) {
        index = *(u16 *)(a0 + 2);
        D_800CB7EC[index]();

        if (*(s32 *)(a0 + 0x20) != 0) {
            func_80162D28((s32 *)a0);
        }

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB338)(a0);
    } else {
        ((void (*)(s32))func_800CB338)(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB028);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB118);

extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB2B4(s32 *a0) {
    s32 *s1;

    s1 = (s32 *)a0[0x20 / 4];
    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
    } else if (a0[0x1C / 4] & 1) {
        s1[1] |= 0x80000000;
    } else {
        s1[1] &= 0x7FFFFFFF;
    }
}


extern void func_80162CCC(void);
void func_800CB338(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB358);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB3BC);

void func_800CB634(s32 a0) {
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(u16 *)(a0 + 0x12) = 0;
    *(u16 *)(a0 + 0x10) = 0x80;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB658);
