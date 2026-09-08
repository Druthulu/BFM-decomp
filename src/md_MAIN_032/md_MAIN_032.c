#include "common.h"
#include "../shared/engine_prelude.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB2D4;
    func_800183E0(&D_800CB2D4);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB29C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB29C[*(u8 *)((s32)a0 + 0x197)]();
}


#include "../shared/slot_800CAE08/func_800CAE78__a79b87ee.h"


extern M2C_UNK D_800CB26C;
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_801655E4(s32 a0);
extern void func_80156648(s32 *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);

void func_800CAEC0(u8 *a0) {
    func_80154274((s32 *)a0, (s32)&D_800CB26C);
    func_80146DE8((s32 *)a0, 0, 0, 0xFFEE0000);
    func_801477E8((s32 *)a0, 0xFFF40000);
    func_801655E4((s32)a0);
    func_80156648((s32 *)a0);
    a0[0x1AA] = 1;
    func_801466F0(0x18, (s32)a0, 0, 0, 0, 0, 0, 1);
    a0[0x197] = a0[0x197] + 1;
}


void func_800CAF60(void *a0) {
    extern void func_80147A84(s32 a0);
    extern void func_801473EC(s32 *a0);
    extern void func_80148038(s32 a0, s32 a1);
    extern void func_80147460(s32 a0);
    extern s32  func_80161418(void *a0);
    extern s32  func_80155FD4(s32 a0, s32 a1);

    *(u32 *)((u8 *)a0 + 0x44) |= 2;
    func_80147A84((s32)a0);
    func_801473EC((s32 *)a0);
    func_80148038((s32)a0, 0x20000);
    func_80147460((s32)a0);
    if (func_80161418(a0) == 0) {
        func_80155FD4((s32)a0, *(u8 *)((u8 *)a0 + 0x1AA));
    }
}


void func_800CAFD0(void *a0) {
    extern u8 D_8011F9D0[];
    extern void func_80162CCC();
    s32 i;
    u8 *ptr;

    for (i = 0; i < 0x14; i++) {
        ptr = D_8011F9D0 + (i * 0x68);
        if (*(u16 *)ptr == 0x18) {
            func_80162CCC(ptr);
        }
    }

    *(u32 *)((s32)a0 + 0x44) &= ~2;
}



extern void func_800CB24C(void);

void func_800CB054(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB2A8[])(void);
    if (D_80078EC1 == 0x9) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB2A8[v0]();
    } else {
        func_800CB24C();
    }
}


#include "common.h"

typedef struct { s32 w[4]; } func_800CB0B0_Blk16;

extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_800CB24C(void);

void func_800CB0B0(void *arg0) {
    extern u16 D_800CC3C4;
    s32 s0;
    s32 s2;
    s32 flag;
    s32 src;

    s2 = *(s32 *)((s32)arg0 + 0x4C);
    s0 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)((s32)arg0 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C810(s0, (s32)&D_800CC3C4);
        flag = *(s32 *)(s0 + 4);
        flag |= 0x50000000;
        *(s32 *)(s0 + 4) = flag;
        func_80149374(s2, (s32)arg0 + 4);
        src = *(s32 *)(s2 + 0x20);
        *(func_800CB0B0_Blk16 *)(s0 + 0x34) = *(func_800CB0B0_Blk16 *)(src + 0x34);
        *(func_800CB0B0_Blk16 *)(s0 + 0x44) = *(func_800CB0B0_Blk16 *)(src + 0x44);
        func_80146CA0(arg0);
    } else {
        ((void (*)(void *))func_800CB24C)(arg0);
    }
}


#include "common.h"

typedef struct { s32 w[4]; } func_800CB188_Blk16;

extern void func_80149374(s32 a0, s32 a1);

void func_800CB188(void *arg0) {
    extern u16 D_800B99DA;
    s32 s0;
    s32 s1;
    s32 v0;
    s32 v1;

    s0 = *(s32 *)((s32)arg0 + 0x4C);
    s1 = *(s32 *)((s32)arg0 + 0x20);
    *(s32 *)((s32)arg0 + 0xC) = 0;
    *(s32 *)((s32)arg0 + 0x8) = 0;
    *(s32 *)((s32)arg0 + 0x4) = 0;
    func_80149374(s0, (s32)arg0 + 4);
    v0 = *(s32 *)(s0 + 0x20);
    *(func_800CB188_Blk16 *)(s1 + 0x34) = *(func_800CB188_Blk16 *)(v0 + 0x34);
    *(func_800CB188_Blk16 *)(s1 + 0x44) = *(func_800CB188_Blk16 *)(v0 + 0x44);
    v1 = *(s32 *)(s1 + 4) & 0x7FFFFFFF;
    *(s32 *)(s1 + 4) = v1;
    if (D_800B99DA & 1) {
        *(s32 *)(s1 + 4) = v1 | 0x80000000;
    }
}


extern void func_80162CCC(void);
void func_800CB24C(void) {
    func_80162CCC();
}

