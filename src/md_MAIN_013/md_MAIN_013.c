#include "common.h"

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CAE0C);



void func_800CAE54(void *a0) {

    extern void (*D_800CB880[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB880[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEE0(u8 *a0);
void func_800CAE98(u8 *a0) {
    if (func_80161104()) {
        func_800CAEE0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CAEE0);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CAF68);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB018);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB054);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB05C);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB0E8);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB138);


extern void func_80146C3C(void);

void func_800CB370(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB908[])(void);
    if (D_80078EC1 == 0x7) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB908[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB3CC);


extern void func_80146C3C(void);

void func_800CB510(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB914[])(void);
    if (D_80078EC1 == 0x7) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB914[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB56C);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB6E4);

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_800CB7F0(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}

