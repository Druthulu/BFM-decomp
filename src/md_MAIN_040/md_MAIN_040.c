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

extern void func_80162CCC(void);
void func_800CB3BC(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB3DC);


extern void func_80146C3C(void);

void func_800CB488(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB948[])(void);
    if (D_80078EC1 == 0x1d) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB948[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB4E4);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB710);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB7B8);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB840);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB874);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB8A8);
