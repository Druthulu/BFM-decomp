#include "common.h"

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAE0C);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAE70);



void func_800CAEC0(void *a0) {

    extern void (*D_800CB610[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB610[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAF4C(u8 *a0);
void func_800CAF04(u8 *a0) {
    if (func_80161104()) {
        func_800CAF4C(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAF4C);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CAF94);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB014);

#include "common.h"

extern u8 D_80078EC1;
extern void (*D_800CB634[])(void);
extern void func_800CB358(void);

void func_800CB028(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x19) {
        index = *(u16 *)(a0 + 2);
        D_800CB634[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB358)(a0);
    } else {
        ((void (*)(s32))func_800CB358)(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB09C);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB150);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB2A8);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB30C);

extern void func_80162CCC(void);
void func_800CB358(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB378);


extern void func_80146C3C(void);

void func_800CB424(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB654[])(void);
    if (D_80078EC1 == 0x19) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB654[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB480);

INCLUDE_ASM("asm/md_MAIN_037/nonmatchings/md_MAIN_037", func_800CB55C);
