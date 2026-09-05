#include "common.h"

INCLUDE_ASM("asm/md_SC03_054/nonmatchings/md_SC03_054", func_801EF558);

INCLUDE_RODATA("asm/md_SC03_054/nonmatchings/md_SC03_054", D_801EF468);

INCLUDE_ASM("asm/md_SC03_054/nonmatchings/md_SC03_054", func_801EF6D8);

INCLUDE_ASM("asm/md_SC03_054/nonmatchings/md_SC03_054", func_801F0048);



extern s32 func_8012E544(s32 a0);

void func_801F0098(void) {
    s32 v0 = func_8012E544(0x11A);
    if (v0 != 0) {
        *(s16*)(v0 + 0xfc) = 1;
    }
}


INCLUDE_ASM("asm/md_SC03_054/nonmatchings/md_SC03_054", func_801F00C8);



extern s32 func_8012E544(s32 a0);

void func_801F0104(void) {
    s32 v0 = func_8012E544(0x11A);
    if (v0 != 0) {
        *(s16*)(v0 + 0xfc) = 3;
    }
}



extern s16 D_801F1480;
void func_801F0134(void) {
    D_801F1480 = 1;
}

