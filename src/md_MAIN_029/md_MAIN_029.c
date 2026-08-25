#include "common.h"

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAE0C);



void func_800CAE64(void *a0) {

    extern void (*D_800CB49C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB49C[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEE0();
void func_800CAEA8(void *a0) {
    func_800CAEE0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAEE0);

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CAF30);

void func_800CAF5C(void) {
}

extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);

void func_800CAF64(s32 a0) {
    func_80146994(0x38, a0, 0x8000, 0);
}


void func_800CAF90(s32 a0) {
    extern u8 D_800CB4A8[];
    extern u8 D_800CB4AA[];
    extern u8 D_800D387C[];
    extern u16 D_80126BC8;
    extern u16 D_80126BCA;
    extern u16 D_80126BCC;
    extern s32 func_801465C0();
    extern void func_800CB2AC(s32 a0);
    extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80147324(s32 a0);
    s32 pad[2];
    s32 t;
    s32 angle;
    s32 prim;

    if (*(s32 *)(a0 + 0x2C) & 0x8000) {
        *(s16 *)(a0 + 0x12) = 0x14;
        *(s16 *)(a0 + 2) = 1;
        return;
    }
    t = *(u32 *)(a0 + 0x30) >> 15;
    prim = func_801465C0();
    if (prim == 0) {
        return;
    }
    angle = t << 16;
    func_8001CC3C(prim, D_800D387C, *(s16 *)(D_800CB4A8 + (angle >> 15)), *(s16 *)(D_800CB4AA + (angle >> 15)));
    *(u8 *)(prim + 0x27) = (angle >> 17) + 0x19;
    *(s32 *)(prim + 4) |= 0x50000000;
    *(u32 *)(a0 + 0x30) = *(u16 *)(a0 + 0x30);
    *(s32 *)(a0 + 0x20) = prim;
    *(s16 *)(a0 + 2) = 2;
    func_800CB2AC(a0);
    func_80146A6C(3, (void *)a0, *(s16 *)(a0 + 6), *(s16 *)(a0 + 0xA), *(s16 *)(a0 + 0xE), 0xCCCFFFC, 0xE0009C00);
    D_80126BCC = D_80126BCC - 0x300;
    D_80126BC8 = D_80126BCC;
    D_80126BCA = D_80126BCA + 0xC0;
    func_80147324(0x8E9);
}


INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CB0D0);

INCLUDE_ASM("asm/md_MAIN_029/nonmatchings/md_MAIN_029", func_800CB2AC);



void func_800CB460(void *a0) {

    extern void (*D_800CB4BC[])(void);
    D_800CB4BC[*(u16 *)((s32)a0 + 0x2)]();
}

