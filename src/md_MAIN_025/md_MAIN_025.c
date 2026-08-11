#include "common.h"

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CAE14);



void func_800CAE5C(void *a0) {

    extern void (*D_800CBE7C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE7C[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAED8();
void func_800CAEA0(void *a0) {
    func_800CAED8(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CAED8);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CAF3C);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CAF7C);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB028);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB068);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB0E4);

extern void func_801599A4(u8 *a0);
extern void func_80159B3C(void *a0);
void func_800CB138(u8 *a0) {
    if (*(u16 *)(a0 + 0xB8) & 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    }
}


extern void func_800CBBF8(void);
void func_800CB180(void) {
    func_800CBBF8();
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB1A0);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB23C);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB300);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB6CC);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB708);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB758);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB760);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB7B0);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB848);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB8A4);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CB968);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBA14);

extern void func_80146E90(s32 *a0, s16 a1);
extern void func_80146CA0(void *a0);
void func_800CBA2C(s32 *a0) {
    func_80146E90(a0, 8);
    func_80146CA0(a0);
}


INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBA60);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBAF4);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBB50);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBB70);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBBA0);

INCLUDE_ASM("asm/md_MAIN_025/nonmatchings/md_MAIN_025", func_800CBBF8);
