#include "common.h"

#include "common.h"

extern void func_800CEF50(void);
extern u16 D_800B99E4;
extern void (*D_800CF0FC[])(void);

void func_800CEDFC(void) {
    func_800CEF50();
    D_800CF0FC[D_800B99E4]();
}


INCLUDE_ASM("asm/md_MAIN_008/nonmatchings/md_MAIN_008", func_800CEE44);

void func_800CEE8C(void) {
    extern s32 func_800167F0(s32 a0);
    extern void func_800118AC(void);

    if (func_800167F0(0) & 0xFFFF) {
        func_800118AC();
    }
}


extern s32 D_800CF13C;
extern s32 func_800149E0(s32);
extern void func_800167B8(s32);
extern void func_800118AC(void);

void func_800CEEC0(void) {
    s32 ret = func_800149E0(0);
    D_800CF13C++;
    if (D_800CF13C >= 0x12D || (ret & 0x8F0)) {
        func_800167B8(4);
        func_800118AC();
    }
}


extern s32 func_800167F0(s32 a0);
extern void func_80011818(s32 arg0);

void func_800CEF1C(void) {
    if (func_800167F0(4) & 0xFFFF) {
        func_80011818(12);
    }
}


INCLUDE_ASM("asm/md_MAIN_008/nonmatchings/md_MAIN_008", func_800CEF50);

INCLUDE_RODATA("asm/md_MAIN_008/nonmatchings/md_MAIN_008", D_800CEDF8);
