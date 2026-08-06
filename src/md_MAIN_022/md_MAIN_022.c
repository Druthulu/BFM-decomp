#include "common.h"

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CBC90[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBC90[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEB0();
void func_800CAE78(void *a0) {
    func_800CAEB0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAEB0);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAEE8);

void func_800CAF3C(void) {
}

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CAF44);

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFAC(void *a0);
void func_800CAF78(s32 *a0) {
    func_80147078(a0, 34);
    func_800CAFAC(a0);
}




void func_800CAFAC(void *a0) {

    extern void (*D_800CBC9C[])(void);
    D_800CBC9C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CB008(void);
void func_800CAFE8(void) {
    func_800CB008();
}


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB008);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB03C);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB0B8);

void func_800CB104(void) {
}

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB10C);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB184);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB1BC);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB2F4);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB354);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB3D0);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB3F0);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB4AC);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB4F4);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB550);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB5E4);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB630);

INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CB68C);

extern void func_800CBAA4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_800CB8A4(s32 a0) {
    s32 s1;
    s32 v;
    s1 = *(s32 *)(a0 + 0x20);
    func_800CBAA4(a0);
    v = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v;
    if (v != 0) {
        func_80146A6C(0x41, (void *)a0, 0, 0, 0, 0x8000, 0);
        *(s16 *)(s1 + 0x18) = *(u16 *)(s1 + 0x18) + 0x100;
        *(s16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0x1A) + 0x140;
        return;
    }
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


extern void func_800CBAA4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_800CB944(s32 *a0) {
    func_800CBAA4((s32)a0);
    if (--a0[0x1C / 4] != 0) {
        func_80146A6C(0x41, a0, 0, 0, 0, 0x8000, 0);
    } else {
        a0[0x1C / 4] = 0x10;
        *(u16 *)((char *)a0 + 2) += 1;
    }
}


extern void func_800CBAA4(s32 a0);
extern void func_80146C3C();
void func_800CB9C0(void *a0) {
    s32 *s1 = *(s32 **)((s32)a0 + 0x20);
    func_800CBAA4((s32)a0);
    if (--*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(u16 *)((s32)s1 + 0x18) -= 0x100;
        *(u16 *)((s32)s1 + 0x1A) -= 0x120;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}


extern void func_800D22E4(s32 a0);
extern void func_800CBB38(void *a0, void *a1);
extern void func_80146C3C();
void func_800CBA30(void *a0) {
    s32 v0;
    v0 = *(s32*)((s32)a0 + 0x1C) - 1;
    *(s32*)((s32)a0 + 0x1C) = v0;
    if (v0 != 0) {
        func_800D22E4((s32)a0);
        *(s16*)((s32)a0 + 0x16) = *(u16*)((s32)a0 + 0x16) - 3;
        *(s32*)((s32)a0 + 0x30) = *(s32*)((s32)a0 + 0x30) - 0xE;
        func_800CBB38(a0, (void*)((s32)a0 + 0x38));
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
void func_800CBAA4(s32 a0) {
    s16 src[4];
    u8 mtx[8];
    s32 p;
    p = *(s32 *)(a0 + 0x34);
    src[0] = *(u16 *)(p + 0x6);
    src[1] = *(u16 *)(p + 0xA) - 0x28;
    src[2] = *(u16 *)(p + 0xE);
    func_800D20C0((void *)src, (void *)mtx, 6);
    *(s16 *)(a0 + 0x6) = src[0];
    *(s16 *)(a0 + 0xA) = src[1];
    *(s16 *)(a0 + 0xE) = src[2];
    func_800D23D0((void *)mtx);
    RotMatrixYXZ((void *)mtx, (void *)(a0 + 0x38));
}


INCLUDE_ASM("asm/md_MAIN_022/nonmatchings/md_MAIN_022", func_800CBB38);
