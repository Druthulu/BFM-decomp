#include "common.h"

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CAE0C);



void func_800CAE54(void *a0) {

    extern void (*D_800CB880[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB880[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEE0(u8 *a0);
void func_800CAE98(u8 *a0) {
    if (func_80161104()) {
        func_800CAEE0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


extern void func_80154274(void *a0, void *a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_801655E4(void *a0);
extern void func_80156648(s32 *a0);
extern void func_800CB054(void *a0);
extern void func_80019064(void *a0);

void func_800CAEE0(u8 *a0) {
    extern u8 D_800CB830[];
    extern u8 D_80062BD0;

    func_80154274(a0, D_800CB830);
    func_80154A74((s32)a0, 0x15);
    func_80147324(0x477);
    func_801655E4(a0);
    *(u8 *)(a0 + 0xBE) = 0;
    *(u8 *)(a0 + 0xBF) = 0;
    func_80156648((s32 *)a0);
    *(u8 *)(a0 + 0x1AA) = 0;
    func_800CB054(a0);
    func_80019064(&D_80062BD0);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CAF68);

void func_800CB018(s32 a0) {
    extern void func_80154A74(s32 a0, s32 a1);
    *(u16 *)(a0 + 0x1BA) = 0x1000;
    *(u16 *)(a0 + 0x1B8) = 0x1000;
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}


void func_800CB054(void *a0) {
    *(s32 *)((s32)a0 + 0xC0) = 0;
}


void func_800CB05C(s32 a0, s32 a1) {
    s32 v; s16 x; s16 y;
    a1 &= 0xFF;
    switch (a1) {
    case 1:
        v = *(s32 *)(a0 + 0xC0) + 0x800;
        *(s32 *)(a0 + 0xC0) = v;
        if (v >= 0x2001) { *(s32 *)(a0 + 0xC0) = 0x2000; }
        x = *(u16 *)(a0 + 0x1B8) + 0x800;
        y = *(u16 *)(a0 + 0x1BA) + 0x800;
        *(u16 *)(a0 + 0x1B8) = x;
        *(u16 *)(a0 + 0x1BA) = y;
        break;
    case 2:
        v = *(s32 *)(a0 + 0xC0) - 0x800;
        *(s32 *)(a0 + 0xC0) = v;
        if (v < 0) { *(s32 *)(a0 + 0xC0) = 0; }
        x = *(u16 *)(a0 + 0x1B8) - 0x800;
        y = *(u16 *)(a0 + 0x1BA) - 0x800;
        *(u16 *)(a0 + 0x1B8) = x;
        *(u16 *)(a0 + 0x1BA) = y;
        break;
    }
}


void func_800CB0E8(void *a0) {
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    s32 v1;

    v1 = func_80146994(0x15, (s32)a0, 0, 0);
    if (v1 != 0) {
        *(s32 *)(v1 + 0x30) = *(s16 *)((u8 *)a0 + 0x36);
    }
}


INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB138);


extern void func_80146C3C(void);

void func_800CB370(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB908[])(void);
    if (D_80078EC1 == 0x7) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB908[v0]();
    } else {
        func_80146C3C();
    }
}


void func_800CB3CC(void *arg0) {
    extern void func_800D2318(void);
    extern void RotMatrixYXZ();
    extern void ApplyMatrixSV();
    extern void func_800D1FC8();
    extern s32 func_800D21C4();
    extern void func_80128EA8();
    extern void func_80146C3C();
    extern u8 D_800CB8FC[];
    extern u8 D_800CB8BC[];
    s16 sp10[8];
    s16 sp20[16];
    s32 p;

    func_800D2318();
    sp10[0] = *(u16 *)((s32)arg0 + 0x12);
    sp10[1] = *(u16 *)((s32)arg0 + 0x16);
    sp10[2] = 0;
    RotMatrixYXZ(sp10, sp20);
    sp10[1] = -8;
    sp10[0] = 0;
    sp10[2] = -0x10;
    ApplyMatrixSV(sp20, sp10, sp10);
    *(s32 *)((s32)arg0 + 0x4C) = (s16)(*(u16 *)((s32)arg0 + 6) = *(u16 *)((s32)arg0 + 6) + (u16)sp10[0]);
    *(s32 *)((s32)arg0 + 0x50) = (s16)(*(u16 *)((s32)arg0 + 0xA) = *(u16 *)((s32)arg0 + 0xA) + (u16)sp10[1]);
    *(s32 *)((s32)arg0 + 0x54) = (s16)(*(u16 *)((s32)arg0 + 0xE) = *(u16 *)((s32)arg0 + 0xE) + (u16)sp10[2]);
    func_800D1FC8(arg0, 6);
    p = func_800D21C4(arg0, D_800CB8FC, 0x19);
    if (p != 0) {
        *(s32 *)((s32)arg0 + 0x20) = p;
        *(u16 *)(p + 0x1A) = 0x3000;
        *(u16 *)(p + 0x18) = 0x3000;
        *(s32 *)(p + 4) |= 0x50000000;
        func_80128EA8(p, (s32)arg0 + 0x24, D_800CB8BC);
        *(u16 *)((s32)arg0 + 2) = *(u16 *)((s32)arg0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}



extern void func_80146C3C(void);

void func_800CB510(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB914[])(void);
    if (D_80078EC1 == 0x7) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB914[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB56C);

INCLUDE_ASM("asm/md_MAIN_013/nonmatchings/md_MAIN_013", func_800CB6E4);

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_800CB7F0(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}

