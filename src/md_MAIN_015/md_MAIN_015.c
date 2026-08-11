#include "common.h"

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CBB24[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBB24[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAF0C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CAF9C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB140);

extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB190(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}



extern void func_800CB474(void);

void func_800CB1C0(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB38[])(void);
    if (D_80078EC1 == 0x8) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB38[v0]();
    } else {
        func_800CB474();
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB21C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB2E0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB474);


extern void func_80146C3C(void);

void func_800CB494(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB58[])(void);
    if (D_80078EC1 == 0x8) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB58[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB4F0);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB6A4);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB6FC);


extern void func_80146C3C(void);

void func_800CB830(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB60[])(void);
    if (D_80078EC1 == 0x8) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB60[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB88C);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB930);

INCLUDE_ASM("asm/md_MAIN_015/nonmatchings/md_MAIN_015", func_800CB988);
