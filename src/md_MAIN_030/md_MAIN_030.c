#include "common.h"

INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB458[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB458[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAEC0);

extern s32 D_80078EC8;
extern void func_80165840(void);
extern s32 func_80165A20(s32 a0);

void func_800CAF44(s32 a0) {
    if (D_80078EC8 == 0) {
        func_80165840();
        func_80165A20(a0);
    }
}


extern void func_80147364(s32 a, s32 b);
void func_800CAF84(void) {
    func_80147364(0x4, 0x83F);
}


INCLUDE_ASM("asm/md_MAIN_030/nonmatchings/md_MAIN_030", func_800CAFA8);

void func_800CB158(void *a0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB51C[])(void);
    extern u8 D_800CB51D;
    extern u8 D_800CB51E;
    extern void func_800233CC(void *, u16);
    extern void func_80146C3C(void *);

    if (D_80078EC1 == 0x13) {
        if (*(s32 *)((s32)a0 + 0x1c) < 0x10) {
            u8 v = D_800CB51E + 8;
            D_800CB51E = v;
            D_800CB51D = v;
            *(u8 *)D_800CB51C = v;
            func_800233CC((void *)D_800CB51C, 0x24);
        }
        *(s32 *)((s32)a0 + 0x1c) = *(s32 *)((s32)a0 + 0x1c) + 1;
    } else {
        func_80146C3C(a0);
    }
}


typedef struct { s32 w[8]; } Blk32_CB1EC;

void func_800CB1EC(void *a0) {
    extern u8 D_80078EC1;
    extern Blk32_CB1EC D_800AE620;
    extern s16 D_80126B5E;
    extern s16 D_80126B62;
    extern s16 D_80126B66;
    extern void func_80016714(void *a0, s32 a1);
    extern s32 func_80128ED8(s32 a0, s32 *a1);
    extern void RotMatrixY(s32 a0, void *a1);
    extern s32 func_80047948(s32 a0);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_80146C3C();

    s16 out[3];
    Blk32_CB1EC buf;
    s32 *s3;
    s32 *s4;
    s32 s5;
    s32 v1;
    s32 mask;

    s3 = *(s32 **)((s32)a0 + 0x20);
    s4 = *(s32 **)((s32)a0 + 0x34);

    if (D_80078EC1 == 0x13) {
        v1 = *(s32 *)((s32)a0 + 0x1C);
        s5 = 0;
        if (v1 < 0x10) {
            *(u8 *)((s32)s3 + 0x24) = *(u8 *)((s32)s3 + 0x25) = *(u8 *)((s32)s3 + 0x26) = *(u8 *)((s32)s3 + 0x26) + 4;
            *(u16 *)((s32)s3 + 0x18) -= 0x400;
            *(u16 *)((s32)s3 + 0x1A) -= 0x400;
        } else {
            s5 = v1 - 0x10;
            func_80128ED8((s32)s3, (s32 *)((s32)a0 + 0x24));
        }

        mask = 0x7FFFFFFF;
        *(s32 *)((s32)s3 + 4) &= mask;

        buf = D_800AE620;

        RotMatrixY(((s5 << 16) >> 11) + *(s32 *)((s32)a0 + 0x2C), &buf);

        out[0] = 0;
        buf.w[5] = D_80126B5E;
        buf.w[6] = D_80126B62;
        buf.w[7] = D_80126B66;

        v1 = func_80047948(((s5 & 0xF) << 8) + *(s32 *)((s32)a0 + 0x2C));
        out[1] = (v1 >> 9) - 0x30;
        out[2] = -0x50;

        func_8012F14C((s32)&buf, (s32)out, (s32)out);

        *(u16 *)((s32)a0 + 0x6) = out[0];
        *(u16 *)((s32)a0 + 0xA) = out[1];
        *(u16 *)((s32)a0 + 0xE) = out[2];

        *(s32 *)((s32)s4 + 4) &= mask;
        *(u16 *)((s32)s4 + 0x18) = *(u16 *)((s32)s3 + 0x18);
        *(u16 *)((s32)s4 + 0x1A) = *(u16 *)((s32)s3 + 0x1A);
        *(u16 *)((s32)s4 + 0x8) = *(u16 *)((s32)a0 + 0x6);
        *(u16 *)((s32)s4 + 0xA) = *(u16 *)((s32)a0 + 0xA);
        *(u16 *)((s32)s4 + 0xC) = *(u16 *)((s32)a0 + 0xE);
        *(s32 *)((s32)a0 + 0x1C) += 1;
    } else {
        if (s4 != NULL) {
            func_80016714((void *)s4, 0x38);
        }
        func_80146C3C(a0);
    }
}




void func_800CB41C(void *a0) {

    extern void (*D_800CB490[])(void);
    D_800CB490[*(u16 *)((s32)a0 + 0x2)]();
}

