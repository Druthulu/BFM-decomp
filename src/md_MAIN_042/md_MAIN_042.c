#include "common.h"

extern u8 D_800D5360[];
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80156648(s32 *a0);
extern void func_80147324(s32 a0);
extern void func_80149020(s32 *a0);

void func_800CCB20(s32 a0)
{
    s32 s0;
    s32 v0;
    u16 v1;

    s0 = a0;
    func_80154274((s32 *)s0, (s32)&D_800D5360);
    v0 = *(s32 *)(s0 + 0x20);
    *(s32 *)(s0 + 0x234) = 0;
    *(s32 *)(s0 + 0x238) = 0;
    v1 = *(u16 *)(v0 + 0x12);
    *(s16 *)(s0 + 0x246) = 0;
    *(s16 *)(s0 + 0x248) = 0x100;
    *(s32 *)(s0 + 0x23C) = 0;
    *(s16 *)(s0 + 0x244) = v1;
    func_80146994(5, s0, 8, 0);
    func_80156648((s32 *)s0);
    func_80147324(0x450);
    func_80149020((s32 *)s0);
}


extern void (*D_800CCD94[])(s32);
extern void func_80149020(s32 *a0);

void func_800CCBA0(param_1)
s32 param_1;
{
    s32 s0 = param_1;
    s32 idx;
    func_80149020(s0);
    idx = *(u16 *)(s0 + 2) - 2;
    D_800CCD94[idx](s0);
}


#include "common.h"

extern u8 D_80078E78[];
extern void func_800CCD60(s32);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208();
extern s32 func_80155FB0(s32 a0, s32 a1);

void func_800CCBF0(u8 *a0) {
    s32 dead[12];
    u8 *p = D_80078E78;
    s32 var = ((Unkstruct_80126B58 *)a0)->unk23C;

    if (var == 0) {
        if (((Unkstruct_80126B58 *)a0)->unkB8 & 0x4000) {
            ((Unkstruct_80126B58 *)a0)->unk23C = 1;
            ((void (*)(void *))func_800CCD60)(a0);
        }
    } else {
        if (var >= 0) {
            if (var < 7) {
                ((Unkstruct_80126B58 *)a0)->unk23C = var + 1;
                ((void (*)(void *))func_800CCD60)(a0);
            }
        }
    }

    switch (((Unkstruct_80126B58 *)a0)->unk234) {
    case 0:
        if (((Unkstruct_80126B58 *)a0)->unkB8 & 0x8000) {
            if (CAST_SIGN(s16, a0, 0x246) < 0x1000) {
                ((Unkstruct_80126B58 *)a0)->unk248 += 30;
                ((Unkstruct_80126B58 *)a0)->unk246 += ((Unkstruct_80126B58 *)a0)->unk248;
                ((Unkstruct_80126B58 *)a0)->unk24A = *(u16 *)(((Unkstruct_80126B58 *)a0)->unk20 + 0x12);
                *(u16 *)(((Unkstruct_80126B58 *)a0)->unk20 + 0x12) =
                    ((Unkstruct_80126B58 *)a0)->unk244 + ((Unkstruct_80126B58 *)a0)->unk246;
                func_80155FB0((s32)a0, (p[0x48] & 0x7F) - 1);
            } else {
                ((Unkstruct_80126B58 *)a0)->unkB8 = 1;
                *(u16 *)(((Unkstruct_80126B58 *)a0)->unk20 + 0x12) = ((Unkstruct_80126B58 *)a0)->unk244;
                ((Unkstruct_80126B58 *)a0)->unk234 += 1;
            }
        }
        break;
    case 1:
        if (((Unkstruct_80126B58 *)a0)->unkB8 & 0x8000) {
            func_801599A4(a0);
            func_80159B3C(a0);
            return;
        }
        break;
    }
    func_80161208(a0);
}


void func_800CCD60(s32 arg0) {
    *(s16 *)(arg0 + 0xF6) = (*(s32 *)(arg0 + 0x23C) << 10) / 7 + 0x1000;
}


INCLUDE_RODATA("asm/md_MAIN_042/nonmatchings/md_MAIN_042", D_800CCB1C);
