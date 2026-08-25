#include "common.h"

#include "common.h"

extern u8 D_800AF630[];

typedef struct { void (*fn)(void); } FnEntry;
extern FnEntry D_800D4C54[];

void func_800CEE74(void) {
    register u8 *base = (u8 *)D_800AF630;
    if (*(u16 *)(base + 0xA3B4) < 5u) {
        D_800D4C54[*(u16 *)(base + 0xA3B4)].fn();
    }
}


INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CEF00);

INCLUDE_RODATA("asm/md_MAIN_011/nonmatchings/md_MAIN_011", D_800CEDF8);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CF28C);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFB88);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFBF0);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFC58);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFCBC);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFDB4);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D03F8);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0430);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0450);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D04C4);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D04F4);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0828);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0858);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0964);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0BDC);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D1254);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D1B00);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D235C);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D2BC4);
