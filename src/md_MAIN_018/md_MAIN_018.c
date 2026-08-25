#include "common.h"

INCLUDE_ASM("asm/md_MAIN_018/nonmatchings/md_MAIN_018", func_800CAE0C);



void func_800CAEB4(void *a0) {

    extern void (*D_800CB5E8[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB5E8[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAF30();
void func_800CAEF8(void *a0) {
    func_800CAF30(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern s32 func_80165910(void);
extern void func_801655E4(s32 a0);
extern void func_800CAFB4();

void func_800CAF30(u8 *a0) {
    if (func_80165910() == 0) {
        func_801655E4((s32)a0);
    }
    func_800CAFB4(a0);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


INCLUDE_ASM("asm/md_MAIN_018/nonmatchings/md_MAIN_018", func_800CAF80);

void func_800CAFAC(void) {
}

void func_800CAFB4(void *arg) {
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    func_80146994(0x23, (s32)arg, 0x8000, 0);
}


INCLUDE_ASM("asm/md_MAIN_018/nonmatchings/md_MAIN_018", func_800CAFE0);

INCLUDE_ASM("asm/md_MAIN_018/nonmatchings/md_MAIN_018", func_800CB168);

INCLUDE_ASM("asm/md_MAIN_018/nonmatchings/md_MAIN_018", func_800CB328);



void func_800CB5AC(void *a0) {

    extern void (*D_800CB614[])(void);
    D_800CB614[*(u16 *)((s32)a0 + 0x2)]();
}

