#include "common.h"

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E25F4);


extern s32 func_800167F0(s32 a0);

s32 func_801E264C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E2920(void *arg0);

s32 func_801E2670(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E2920, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E26BC);

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E275C);



void func_801E277C(void *a0) {

    extern void (*D_801E2FF0[])(void);
    D_801E2FF0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27B8(void *a0) {

    extern void (*D_801E2FF8[])(void);
    D_801E2FF8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27F4(void *a0) {

    extern void (*D_801E307C[])(void);
    D_801E307C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2830);

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2858);

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E28C0);

void func_801E2918(void) {
}



void func_801E2920(void *a0) {

    extern void (*D_801E308C[])(void);
    D_801E308C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E295C);

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E297C);

void func_801E29E4(void) {
}

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E29EC);



void func_801E2AB0(void *a0) {

    extern void (*D_801E3098[])(void);
    D_801E3098[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2AEC);

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2B14);


s32 func_801E2D0C(void) {
    return 39;
}




void func_801E2D14(void *a0) {

    extern void (*D_801E31A0[])(void);
    D_801E31A0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2D50);



void func_801E2D60(void) {

    extern s32 D_801E977C;
    D_801E977C = 1;
}




s32 func_801E2D74(void) {

    extern s32 D_801E977C;
    return D_801E977C;
}


INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2D84);

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2E24);

INCLUDE_ASM("asm/md_SC03_132/nonmatchings/md_SC03_132", func_801E2F58);

INCLUDE_RODATA("asm/md_SC03_132/nonmatchings/md_SC03_132", D_801E25E8);

INCLUDE_RODATA("asm/md_SC03_132/nonmatchings/md_SC03_132", D_801E25EC);
