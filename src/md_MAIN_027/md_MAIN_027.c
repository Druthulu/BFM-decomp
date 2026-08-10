#include "common.h"

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CC134[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CC134[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CAEC0);

void func_800CAF18(void) {
}

void func_800CAF20(void) {
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFEC(void);
void func_800CAF28(s32 *a0) {
    func_80147078(a0, 32);
    ((void (*)(void *))func_800CAFEC)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAF90(void *a0);
void func_800CAF5C(s32 *a0) {
    func_80147078(a0, 32);
    func_800CAF90(a0);
}




void func_800CAF90(void *a0) {

    extern void (*D_800CC140[])(void);
    D_800CC140[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CAFEC(void);
void func_800CAFCC(void) {
    func_800CAFEC();
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CAFEC);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB06C);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB108);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB1A0);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB234);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB270);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB2CC);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB3E0);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB4A4);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB7FC);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB82C);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CBA44);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CBBF8);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CBCB4);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CBECC);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CBF28);

extern void func_800CC024(void);
void func_800CBFE4(void) {
    func_800CC024();
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CC004);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CC024);
