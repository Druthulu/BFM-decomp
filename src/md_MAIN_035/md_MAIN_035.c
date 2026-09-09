#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB2C8;
    func_800183E0(&D_800CB2C8);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB278[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB278[*(u8 *)((s32)a0 + 0x197)]();
}


#include "../shared/slot_800CAE08/func_800CAE78__3873a7ac.h"


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
extern void func_800CAFBC();
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


extern s32 func_80161104(s32 a0);
extern void func_800CAFBC();
void func_800CAF84(int param_1)
{
    if (((int (*)(void))func_80161104)() != 0) {
        ((void (*)(int))func_800CAFBC)(param_1);
    }
}


    extern void func_801655E4(void);
    extern void func_80146CA0(void);
    void func_800CAFBC(s32 a0) {
        func_801655E4();
        ((void (*)(s32))func_80146CA0)(a0);
    }


void func_800CAFEC(s32 *a0) {
    extern s32 D_801151D4;
    extern s16 func_80171AB0(s32 a0, void *a1);
    extern void func_80154150(s32 a0, s32 a1);
    extern void func_80154A74(s32 *a0, s16 a1);
    extern void func_800CB13C(s32 param_1);
    extern void func_80147324(s32 a0);
    extern void func_801553A8(s32 *a0);
    extern void func_80146CA0(void);

    s16 buf[3];
    s32 *p;

    p = (s32 *)D_801151D4;
    buf[0] = (s16)p[0xF];
    buf[1] = (s16)p[0x10];
    buf[2] = (s16)p[0x11];
    if (func_80171AB0((s32)a0, buf) != 0) {
        return;
    }
    func_80154150((s32)a0, 0x1C);
    func_80154A74(a0, 0x19);
    a0[0x234 / 4] = 0;
    func_800CB13C((s32)a0);
    func_80147324(0x8F1);
    func_801553A8(a0);
    ((void (*)(s32))func_80146CA0)((s32)a0);
}


extern void func_800CB1F8(void *a0);
extern void func_800CB13C(s32 param_1);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208();

void func_800CB080(void *arg0) {
    if (*(u16 *)((u8 *)arg0 + 0xB8) & 0x4000) {
        ((void (*)(void))func_800CB1F8)();
    }
    if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) {
        func_801599A4(arg0);
        func_80159B3C(arg0);
    } else {
        if (*(s32 *)((u8 *)arg0 + 0x178) != 0) {
            func_800CB13C(arg0);
        }
        func_80161208(arg0);
    }
}


extern void func_80154A74(s32 *a0, s16 a1);
extern void func_800CB1F8(void *a0);
void func_800CB108(s32 *a0) {
    func_80154A74(a0, 17);
    func_800CB1F8(a0);
}



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


void func_800CB1F8(void *a0) {

    extern void func_8014C1A0(s32 arg0, s32 arg1);
    extern void func_80015978(s32 a0, s32 *a1);
    extern u16 func_80156370(u16 a0);
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);

    s32 iVar1;
    u16 uVar2;
    s16 buf[4];

    iVar1 = *(s32 *)((u8 *)a0 + 0x178);
    if (iVar1 != 0) {
        func_8014C1A0((s32)a0, iVar1);
        func_80015978(iVar1 + 4, (s32 *)buf);
        buf[3] = 0;
        uVar2 = func_80156370(0x29);
        func_8014C4AC(iVar1, 0x29, uVar2, buf, *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12));
        *(s32 *)((u8 *)a0 + 0x178) = 0;
    }
}

