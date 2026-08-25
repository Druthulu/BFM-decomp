#include "common.h"

void func_800CCB20(void) {
}

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCB28);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCB78);

extern void (*D_800CD684[])(void);
extern s16 D_800CE050;
extern s32 func_80012ABC(s32, s32, s32);
extern void func_8014ACC0(s32, s32);
extern s32 func_80161A00(s32 a0);
extern void func_80147364(s32 a, s32 b);
extern void func_800CCE60();

void func_800CCC54(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD684[*(u16 *)(param_1 + 2)]();
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= *(s32 *)(*(s32 *)(iVar1 + 0x20) + 4) & 0x80000000;
    *(u16 *)(param_1 + 0x60) = 0;
    D_800CE050 = func_80012ABC(D_800CE050, *(s16 *)(*(s32 *)(iVar1 + 0x20) + 0x12), 10);
    func_8014ACC0(iVar1, 1);
    if (func_80161A00(iVar1) == 0) {
        func_80147364(0x4, 0x8E0);
        ((void (*)(s32))func_800CCE60)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCD2C);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCDD8);

extern void func_80162CCC(void);
void func_800CCE60(void) {
    func_80162CCC();
}


extern void func_80013F3C(void *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_80048D9C(void *a0, void *a1);
extern void func_80020F34(s32 a0, s32 a1);

void func_800CCE80(void *arg0) {
    void *s2;
    void *s1;
    void *s0;
    void *p;

    s2 = *(void **)((u8 *)arg0 + 0x4C);
    p = *(void **)((u8 *)s2 + 0x20);
    s1 = *(void **)((u8 *)arg0 + 0x20);
    *(s16 *)((u8 *)arg0 + 0x06) = *(s32 *)((u8 *)p + 0x48);
    *(s16 *)((u8 *)arg0 + 0x0A) = *(s32 *)((u8 *)p + 0x4C) - 0x20;
    s0 = (void *)((u8 *)s1 + 0x34);
    *(s16 *)((u8 *)arg0 + 0x0E) = *(s32 *)((u8 *)p + 0x50);
    func_80013F3C(s0);
    RotMatrixY(*(s16 *)((u8 *)s1 + 0x12), s0);
    func_80048D9C(s0, (void *)((u8 *)*(void **)((u8 *)s2 + 0x20) + 0x34));
    func_80020F34((s32)s0, (s32)((u8 *)s1 + 0x18));
    *(u16 *)((u8 *)s1 + 0x2C) |= 1;
}


extern s32 func_8014C088(s32 a0, s32 a1);

void func_800CCF28(s32 a0) {
    s32 v1 = func_8014C088(a0, 0x10);
    if (v1 != 0) {
        *(s16 *)(v1 + 0x60) = 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CCF58);

extern void func_80147364(s32 a, s32 b);
void func_800CCF84(void) {
    func_80147364(0x4, 0x8E0);
}


extern s32 func_80161A00(s32 a0);
extern void (*D_800CD6B0[])(void);
extern void func_800CD1A8(void);

void func_800CCFA8(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD6B0[*(u16 *)(param_1 + 2)]();
    if (func_80161A00(iVar1) == 0) {
        ((void (*)(s32))func_800CD1A8)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD010);

INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD0CC);

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80162CCC(void);

void func_800CD1A8(void) {
    register void *a0r __asm__("$4");
    void *arg0 = a0r;

    func_80146A6C(3, arg0,
                  *(s16 *)((u8 *)arg0 + 6),
                  *(s16 *)((u8 *)arg0 + 0xA),
                  *(s16 *)((u8 *)arg0 + 0xE),
                  0x8880000, 0x1800A000);
    ((void (*)(void *))func_80162CCC)(arg0);
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD204);

extern s32 func_80161A00(s32 a0);
extern void (*D_800CD6C4[])(void);
extern void func_800CD5BC(void);

void func_800CD328(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD6C4[*(u16 *)(param_1 + 2)]();
    if (func_80161A00(iVar1) == 0) {
        ((void (*)(s32))func_800CD5BC)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_045/nonmatchings/md_MAIN_045", func_800CD390);

extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CD5DC();
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80162FC0(s32 *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328();
extern s32 func_801632F0();
extern u16 D_800CD690[];
extern u16 D_800CD692[];

void func_800CD4BC(s32 arg0) {
    s32 sp18[8];
    s32 temp_s2 = *(s32 *)(arg0 + 0x4C);
    s32 temp_s1 = *(s32 *)(arg0 + 0x20);

    if (func_80146E98(arg0) != 0) {
        func_80146CA0((void *)arg0);
        return;
    }
    *(u16 *)(temp_s1 + 0x28) = D_800CD690[(*(u16 *)(temp_s2 + 0x1C8) & 7) * 2];
    *(u16 *)(temp_s1 + 0x2A) = D_800CD692[(*(u16 *)(temp_s2 + 0x1C8) & 7) * 2];
    func_800CD5DC(arg0, sp18);
    func_80163194(arg0, 0, -0x10000, 0, (s32)sp18);
    func_80162FC0((s32 *)arg0);
    *(u16 *)(temp_s1 + 0x18) = *(u16 *)(temp_s1 + 0x1A) =
        *(u16 *)(temp_s1 + 0x1A) + 0x200;
    func_80163408(arg0, 0x24, 0x80, 4);
    func_80163328(arg0);
    func_801632F0(arg0);
}


extern void func_80162CCC(void);
void func_800CD5BC(void) {
    func_80162CCC();
}


extern void func_80013F3C(void *a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);

void func_800CD5DC(s32 a0, s32 a1) {
    s32 q = *(s32 *)(a0 + 0x20);
    func_80013F3C((void *)a1);
    func_800126C4((s32)a1, *(s16 *)(a0 + 0x60));
    func_800123F0((s32)a1, *(s16 *)(a0 + 0x64));
    func_80012558((s32)a1, *(s16 *)(a0 + 0x62));
    func_80012558((s32)a1, *(s16 *)(q + 0x12));
    func_800126C4((s32)a1, *(s16 *)(q + 0x10));
    func_800123F0((s32)a1, *(s16 *)(q + 0x14));
}


INCLUDE_RODATA("asm/md_MAIN_045/nonmatchings/md_MAIN_045", D_800CCB1C);
