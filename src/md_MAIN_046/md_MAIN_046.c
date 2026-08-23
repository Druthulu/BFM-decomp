#include "common.h"

void func_800CCB20(void) {
}

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CCB28);

extern void func_80147324(s32 a0);
extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CCB78(void *a0) {
    func_80147324(0x8E3);
    func_8014B5C4((s32 *)a0, 5, 0);
    func_801466F0(0x13, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 1, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 2, 0, 0);
    func_801466F0(0x14, (s32)a0, 0, 0, 0, 3, 0, 0);
    *(s16 *)((s32)a0 + 0x1C8) = 0xFF;
    func_801599A4(a0);
    func_80159B3C(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CCD50(void);
void func_800CCC8C(s32 *a0) {
    func_80147078(a0, 33);
    ((void (*)(void *))func_800CCD50)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CCCF4(void *a0);
void func_800CCCC0(s32 *a0) {
    func_80147078(a0, 33);
    func_800CCCF4(a0);
}




void func_800CCCF4(void *a0) {

    extern void (*D_800CE044[])(void);
    D_800CE044[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CCD50(void);
void func_800CCD30(void) {
    func_800CCD50();
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CCD50);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CCDB0);

void func_800CCDC8(s32 *param_1)
{
    s32 v1;
    s32 v0;

    if (func_800CD240() != 0) return;
    func_800CD288(param_1);
    if (func_800CD494(param_1) != 0) return;
    v0 = func_800CD5CC(param_1);
    if (v0 != 0)
        func_800CD6A4(param_1, v0);
    v1 = func_801612B8(param_1, 0);
    if ((v1 & 0x4000) != 0) {
        func_800CCFA8(param_1);
        return;
    }
    if (v1 == 0 || v1 == 0x8000) {
        func_801477E8(param_1, 0);
        func_80146CA0(param_1);
        return;
    }
    if (func_801496D4(param_1) != 0) {
        func_800CCEB8(param_1);
        return;
    }
    func_801483E8(param_1);
    *(s32 *)((u8 *)param_1 + 0x44) |= 0x1000;
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CCEB8);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CCEEC);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CCFA8);

extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F50(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_800CD494(void *a0);
extern void func_800CD5CC(void *a0);
extern void func_8016151C(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern s16 D_801152B0;
extern s16 D_801152B4;

void func_800CCFDC(void *arg0) {
    s32 ret;

    if (func_800CD240(arg0) != 0) {
        return;
    }
    func_80146DE8((s32 *)arg0, *(s32 *)((s32)arg0 + 0x234), *(s32 *)((s32)arg0 + 0x238), *(s32 *)((s32)arg0 + 0x23C));
    func_80147F50((s32)arg0);
    func_801473EC((s32 *)arg0);
    func_80148038((s32)arg0, 0x1A000);
    func_80147460((s32)arg0);
    if (((s32 (*)(void *))func_800CD494)(arg0) != 0) {
        return;
    }
    func_800CD5CC(arg0);
    ret = ((s32 (*)(void *))func_8016151C)(arg0);
    if (ret & 0x4000) {
        *(s32 *)((s32)arg0 + 0x234) = D_801152B0 << 6;
        *(s32 *)((s32)arg0 + 0x238) = 0x80000;
        *(s32 *)((s32)arg0 + 0x23C) = D_801152B4 << 6;
        *(s16 *)((s32)arg0 + 2) = 3;
    } else if (ret != 0) {
        func_80146E90((s32 *)arg0, 8);
        func_80146CA0(arg0);
    } else {
        *(s32 *)((s32)arg0 + 0x44) |= 0x1000;
    }
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD0DC);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD1F4);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD240);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD288);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD494);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD5CC);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD6A4);

extern s16 D_800CE8D4;
extern void (*D_800CE080[])(void);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8014ACC0(s32 a0, s32 a1);
extern s32 func_80161A30(s32 a0);
extern void func_800CD94C(void);

void func_800CD708(s32 param_1)
{
    s32 s0;
    s32 iVar1;
    s0 = *(s32 *)(param_1 + 0x4C);
    D_800CE080[*(u16 *)(param_1 + 2)]();

    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= (*(s32 *)(*(s32 *)(s0 + 0x20) + 4)) & 0x80000000;

    *(s16 *)(param_1 + 0x60) = 0;

    iVar1 = *(s32 *)(s0 + 0x20);
    D_800CE8D4 = func_80012ABC(D_800CE8D4, *(s16 *)(iVar1 + 0x12), 0xA);

    func_8014ACC0(s0, 1);
    if (func_80161A30(s0) != 0) {
        return;
    }
    ((void (*)(s32))func_800CD94C)(param_1);
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD7D8);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD884);

extern void func_80162CCC(void);
void func_800CD94C(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CD96C);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDA14);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDA44);

extern s32 func_80161A30(s32 a0);
extern void (*D_800CE0AC[])(void);
extern void func_800CDBD4(void);

void func_800CDA4C(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CE0AC[*(u16 *)(param_1 + 2)]();
    if (func_80161A30(iVar1) == 0) {
        ((void (*)(s32))func_800CDBD4)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDAB4);

extern void func_800CDBF4(void);
extern void func_800CDCA8(void);
void func_800CDBA4(s32 a0) {
    func_800CDBF4();
    ((void (*)(s32))func_800CDCA8)(a0);
}


extern void func_80162CCC(void);
void func_800CDBD4(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDBF4);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDCA8);

extern s32 func_80161A30(s32 a0);
extern void (*D_800CE0C0[])(void);
extern void func_800CDF64(void);

void func_800CDD34(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CE0C0[*(u16 *)(param_1 + 2)]();
    if (func_80161A30(iVar1) == 0) {
        ((void (*)(s32))func_800CDF64)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDD9C);

INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDEB4);

extern void func_80162CCC(void);
void func_800CDF64(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_046/nonmatchings/md_MAIN_046", func_800CDF84);

INCLUDE_RODATA("asm/md_MAIN_046/nonmatchings/md_MAIN_046", D_800CCB1C);
