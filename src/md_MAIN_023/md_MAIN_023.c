#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CAF6C;
    func_800183E0(&D_800CAF6C);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CAF40[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CAF40[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_023/nonmatchings/md_MAIN_023", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_023/nonmatchings/md_MAIN_023", func_800CAEF8);

void func_800CAF38(void) {
}
