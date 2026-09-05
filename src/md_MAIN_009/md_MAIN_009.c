#include "common.h"


extern void (*D_800CDD08[])(void);

void func_800CD384(void) {
    register s32 idx __asm__("$2");
    __asm__ __volatile__("" : : "r"(idx));
    D_800CDD08[idx]();
}


INCLUDE_RODATA("asm/md_MAIN_009/nonmatchings/md_MAIN_009", D_800CD348);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD3B8);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD408);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD464);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD4C8);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD520);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD558);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD5B8);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD614);

void func_800CD66C(void) {
}

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD674);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD92C);
