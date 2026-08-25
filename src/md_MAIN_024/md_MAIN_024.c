#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CAF34;
    func_800183E0(&D_800CAF34);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CAF08[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CAF08[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern s32 func_80165910();
extern void func_801655E4(s32 a0);

void func_800CAEB0(void *a0) {
    if (func_80165910(a0) == 0) {
        func_801655E4((s32)a0);
    }
    *(u8 *)((s32)a0 + 0x197) += 1;
}


void func_800CAEF8(void) {
}

void func_800CAF00(void) {
}
