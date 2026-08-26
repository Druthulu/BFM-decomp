#include "common.h"

void func_8003FA54(void) {
    extern u16 D_800A5F60;
    D_800A5F60 = 0;
}

INCLUDE_ASM("asm/nonmatchings/sgap_6", func_8003FA64);
