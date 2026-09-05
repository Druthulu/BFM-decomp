#include "common.h"




extern void func_80178CBC(s32*, s32);
    extern short D_801CC890;
    void func_801CBB54(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 10;
        ((void (*)(s32, s32))func_80178CBC)((int)arg0, (int)&D_801CC890);
    }


INCLUDE_ASM("asm/md_SC03_056/nonmatchings/md_SC03_056", func_801CBB80);

INCLUDE_ASM("asm/md_SC03_056/nonmatchings/md_SC03_056", func_801CBBDC);

extern s32 func_80178970(s32 *a0);
extern void func_80178D18(u8 *a0);
extern s32 func_8018151C(s32);
void func_801CBC08(u8 * a0)
{
    if (func_80178970(a0)) {
        func_80178D18((u8 *)a0);
        func_8018151C((s32)a0);
    }
}


INCLUDE_RODATA("asm/md_SC03_056/nonmatchings/md_SC03_056", D_801CBB50);
