#include "common.h"

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CAE0C);



void func_800CAE54(void *a0) {

    extern void (*D_800CBF94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBF94[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEE0(u8 *a0);
void func_800CAE98(u8 *a0) {
    if (func_80161104()) {
        func_800CAEE0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CAEE0);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CAF4C);

void func_800CAFCC(void) {
}


extern void func_800CB5A8(void);

void func_800CAFD4(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBFB8[])(void);
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBFB8[v0]();
    } else {
        func_800CB5A8();
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB030);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB11C);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB1CC);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB218);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB3B4);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB570);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB5A8);


extern void func_800CB774(void);

void func_800CB5D8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBFD4[])(void);
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBFD4[v0]();
    } else {
        func_800CB774();
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB634);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB708);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB774);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB794);

extern u8 D_80078EC1;
extern void (*D_800CC01C[])(void);
extern void func_80146C3C(void);

void func_800CB8B4(void *arg0) {
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC01C[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB910);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBC14);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBC90);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBD2C);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBD54);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBEB0);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBF24);

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CBF3C);
