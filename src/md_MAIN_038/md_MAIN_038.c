#include "common.h"

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CBBA8[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBBA8[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
void func_800CAE88(u8 *a0) {
    if (func_80161104()) {
        func_800CAED0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAED0);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAF1C);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CAFAC);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB194);

extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB1E4(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}



extern void func_800CB4F8(void);

void func_800CB214(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBBC8[])(void);
    if (D_80078EC1 == 0x1b) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBBC8[v0]();
    } else {
        func_800CB4F8();
    }
}


INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB270);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB360);

extern void func_80162CCC(void);
void func_800CB4F8(void) {
    func_80162CCC();
}



extern void func_80146C3C(void);

void func_800CB518(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBBE8[])(void);
    if (D_80078EC1 == 0x1b) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBBE8[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB574);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB728);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB780);


extern void func_80146C3C(void);

void func_800CB8B4(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBBF0[])(void);
    if (D_80078EC1 == 0x1b) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBBF0[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB910);

INCLUDE_ASM("asm/md_MAIN_038/nonmatchings/md_MAIN_038", func_800CB9B4);

extern signed char D_800CBBD4[];

void func_800CBA0C(s32 param_1) {
    unsigned char buf[0x34];
    signed char *p;
    short i;
    u8 t;

    p = D_800CBBD4;
    i = 0;
    *(short *)(buf + 0x0c) = 0;
    *(short *)(buf + 0x0a) = 0;
    *(short *)(buf + 0x08) = 0;
    *(short *)(buf + 0x1c) = 0;
    *(short *)(buf + 0x14) = 0;
    *(short *)(buf + 0x04) = 0;
    t = *(u8 *)(param_1 + 0x30);
    buf[0x22] = 0;
    buf[0x21] = 0;
    buf[0x20] = 0;
    buf[0x2a] = 0;
    buf[0x29] = 0;
    buf[0x28] = 0;
    buf[0x2e] = 0;
    buf[0x2d] = 0;
    buf[0x2c] = 0;
    *(s32 *)(buf + 0x30) = 0x50000000;
    buf[0x25] = t;
    buf[0x24] = t;
    buf[0x26] = t >> 1;
    do {
        *(short *)(buf + 0x00) = *p++;
        *(short *)(buf + 0x02) = *p++;
        *(short *)(buf + 0x10) = *p++;
        *(short *)(buf + 0x12) = *p++;
        *(short *)(buf + 0x18) = *p++;
        *(short *)(buf + 0x1a) = *p--;
        func_80017758(buf, (void *)(param_1 + 0x38));
        i++;
    } while (i < 4);
}

