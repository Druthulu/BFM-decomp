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


extern u16 D_801270C0;
extern void func_80154150(s32 a0, s32 a1);
extern void func_801655E4(s32 a0);
extern void func_800183E0(s32 a0);
extern void func_800CAE74(void *a0, void *a1, void *a2);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern u8 D_800CC09C[];
extern u8 D_800CBF3C[];
extern u8 D_800CBF7C[];
extern u8 D_800CC0DC[];
extern u8 D_800CBF5C[];
extern u8 D_800CBFA8[];
extern u8 D_800CC05C[];

void func_800CAFE4(u8 *a0) {
    D_801270C0 = 2;
    func_80154150((s32)a0, 3);
    func_801655E4((s32)a0);
    func_800CAE74((void *)&D_800CC09C, (void *)&D_800CBF3C, (void *)&D_800CBF7C);
    func_800CAE74((void *)&D_800CC0DC, (void *)&D_800CBF5C, (void *)&D_800CBFA8);
    func_800183E0((s32)&D_800CC05C);
    *(u16 *)(a0 + 0x234) = 0;
    *(u16 *)(a0 + 0x236) = 0x10;
    *(u32 *)(a0 + 0x238) = 0;
    *(u8 *)(a0 + 0xBE) = 0;
    *(u8 *)(a0 + 0xBF) = 0;
    func_80146E90((s32 *)a0, 0x10);
    func_80147324(0x8EA);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


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

void func_800CB288(s32 arg0)
{
    s16 sp10[3];
    s16 sp18[3];
    u16 temp;
    u16 cur;
    register u16 temp2 __asm__("$2");
    register u16 cur2 __asm__("$3");

    if ((func_80146E98(arg0) == 0) || (!(func_80148800((s32 *) arg0) & 0x20))) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = 0;
        sp18[0] = *(u16 *) (arg0 + 0x234);
        sp18[2] = *(u16 *) (arg0 + 0x236);
        sp18[1] = sp18[2];
        func_800CB428(arg0, sp10, sp18);
        func_800CB6A0(arg0, sp10, sp18, 1);
        func_800CB6A0(arg0, sp10, sp18, 0);
        func_800CB964(arg0, sp10, sp18);
        if (*(s16 *) (arg0 + 0x236) != 0x10) {
            temp = *(volatile u16 *) (arg0 + 0x23A) + 0x100;
            cur = *(volatile u16 *) (arg0 + 0x236) - temp;
            *(u16 *) (arg0 + 0x236) = cur;
            *(u16 *) (arg0 + 0x23A) = temp;
            if ((s16) cur < 0x10) {
                *(u16 *) (arg0 + 0x236) = 0x10;
            }
            return;
        }
        temp2 = *(volatile u16 *) (arg0 + 0x238) + 0x200;
        cur2 = *(volatile u16 *) (arg0 + 0x234) - temp2;
        *(u16 *) (arg0 + 0x234) = cur2;
        *(u16 *) (arg0 + 0x238) = temp2;
        if ((s16) cur2 >= 0) {
            return;
        }
        *(u16 *) (arg0 + 0x234) = 0;
    }
    func_80165A78(arg0);
    func_80159B3C((void *) arg0);
}


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
