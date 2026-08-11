#include "common.h"

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CAE0C);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CAE74);



void func_800CAF58(void *a0) {

    extern void (*D_800CBFE4[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBFE4[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAFE4(u8 *a0);
void func_800CAF9C(u8 *a0) {
    if (func_80161104()) {
        func_800CAFE4(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CAFE4);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB0B0);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB1CC);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB288);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB3B4);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB428);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB5C8);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB6A0);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CB964);


extern void func_800CBEB8(void);

void func_800CBBB8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CC030[])(void);
    if (D_80078EC1 == 0x1a) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC030[v0]();
    } else {
        func_800CBEB8();
    }
}


INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CBC14);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CBCD4);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CBEB8);

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CBED8);
