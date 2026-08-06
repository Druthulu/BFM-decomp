#include "common.h"

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB8C8[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB8C8[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
void func_800CAE88(u8 *a0) {
    if (func_80161104()) {
        func_800CAED0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CAED0);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CAF18);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CAFB0);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CAFC4);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB038);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB114);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB304);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB3BC);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB3DC);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB488);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB4E4);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB710);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB7B8);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB840);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB874);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB8A8);
