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

extern void func_800CB428(void *a0, void *a1, void *a2);
extern void func_800CB6A0(void *a0, void *a1, void *a2, s32 a3);
extern void func_800CB964(void *a0, void *a1, void *a2);
extern void func_80147324(s32 a0);

void func_800CB0B0(void *arg) {
    u16 sp10[3];
    u16 sp18[3];
    u16 temp;
    u16 cur;
    u8 b;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = 0;
    sp18[0] = *(u16 *)((u8 *)arg + 0x234);
    sp18[2] = *(u16 *)((u8 *)arg + 0x236);
    sp18[1] = sp18[2];
    func_800CB428(arg, sp10, sp18);
    func_800CB6A0(arg, sp10, sp18, 1);
    func_800CB6A0(arg, sp10, sp18, 0);
    func_800CB964(arg, sp10, sp18);
    if (*(s16 *)((u8 *)arg + 0x234) != 0x2000) {
        temp = *(volatile u16 *)((u8 *)arg + 0x238) + 0x100;
        cur = *(volatile u16 *)((u8 *)arg + 0x234) + temp;
        *(u16 *)((u8 *)arg + 0x234) = cur;
        *(u16 *)((u8 *)arg + 0x238) = temp;
        if ((s16)cur >= 0x2001) {
            func_80147324(0x8EB);
            *(u16 *)((u8 *)arg + 0x234) = 0x2000;
        }
    } else {
        temp = *(volatile u16 *)((u8 *)arg + 0x23A) + 0x200;
        cur = *(volatile u16 *)((u8 *)arg + 0x236) + temp;
        *(u16 *)((u8 *)arg + 0x236) = cur;
        *(u16 *)((u8 *)arg + 0x23A) = temp;
        if ((s16)cur >= 0x2001) {
            b = *(u8 *)((u8 *)arg + 0x197);
            *(u16 *)((u8 *)arg + 0x236) = 0x2000;
            *(u8 *)((u8 *)arg + 0x197) = b + 1;
        }
    }
}


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

extern void func_80162CCC(void);
void func_800CBEB8(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CBED8);
