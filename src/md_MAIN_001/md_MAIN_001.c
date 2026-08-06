#include "common.h"



void func_800CEDFC(void) {

    extern u16 D_800B99E4;
    extern void (*D_800CF450[])(void);
    u32 v1;
    v1 = D_800B99E4;
    if (v1 < 8) {
        D_800CF450[v1]();
    }
}


INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CEE40);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CEF04);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CEF54);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CEFA8);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CEFF4);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CF038);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CF0C4);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CF114);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CF180);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CF290);

INCLUDE_RODATA("asm/md_MAIN_001/nonmatchings/md_MAIN_001", D_800CEDF8);
