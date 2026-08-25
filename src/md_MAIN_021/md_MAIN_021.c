#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB538;
    func_800183E0(&D_800CB538);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB4FC[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB4FC[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CAEB0);

void func_800CAF38(void *a0) {

    extern s32 D_80078EC8;
    extern s32 D_80078EA4;
    extern void func_80165840(void);
    extern s32 func_80165A20(s32);

    if (D_80078EC8 == 0) {
        func_80165840();
        func_80165A20((s32)a0);
    } else {
        D_80078EA4 = 0xA00000;
    }
}


void func_800CAF8C(void) {
}

INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CAF94);

INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CB0C8);



void func_800CB33C(void *a0) {

    extern void (*D_800CB508[])(void);
    D_800CB508[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_021/nonmatchings/md_MAIN_021", func_800CB378);

void func_800CB478(s32 param_1)
{
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80146C3C();
    extern u8 D_80078EC1;
    s32 a1;
    s32 counter;

    a1 = *(s32 *)(param_1 + 0x34);
    if (D_80078EC1 == 2) {
        counter = *(s32 *)(param_1 + 0x1c) - 1;
        *(s32 *)(param_1 + 0x1c) = counter;
        if (counter == -1) {
            func_80146A6C(0x21, (void *)a1, 0, 0, 0, 0x8000, 0);
            *(s32 *)(param_1 + 0x1c) = 0x20;
        }
    } else {
        func_80146C3C(param_1);
    }
}

