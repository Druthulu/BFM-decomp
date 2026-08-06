#include "common.h"

INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CAE0C);



void func_800CAE34(void *a0) {

    extern void (*D_800CB278[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB278[*(u8 *)((s32)a0 + 0x197)]();
}


INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CAE78);

s32 func_800CAEB0(u8 *a0)
{
    s32 v = a0[407] + 1;
    a0[407] = v;
    return v;
}




void func_800CAEC4(void) {

    extern s32 D_80078EC8;
    D_80078EC8 = 1;
}


void func_800CAED8(void) {
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFBC(void *a0);
void func_800CAEE0(s32 *a0) {
    func_80147078(a0, 35);
    func_800CAFBC(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAF48(void *a0);
void func_800CAF14(s32 *a0) {
    func_80147078(a0, 35);
    func_800CAF48(a0);
}




void func_800CAF48(void *a0) {

    extern void (*D_800CB284[])(void);
    D_800CB284[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CAF84);

INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CAFBC);

INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CAFEC);

INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CB080);

INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CB108);


// @class: other
// @stuck: none — MATCH (proxy gate)

extern void func_80149374(s32 a0, s32 a1);

void func_800CB13C(s32 param_1) {

    extern s8 D_800CB290[];
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_800CB290[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_800CB290[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_800CB290[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


INCLUDE_ASM("asm/md_MAIN_035/nonmatchings/md_MAIN_035", func_800CB1F8);
