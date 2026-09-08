#include "common.h"
#include "../shared/engine_prelude.h"

extern u8 *D_80126B10;
extern u8 D_801EFE3C[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801EF47C(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801EFE3C;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



#include "../shared/slot_801EF468/func_801EF4D4.h"



#include "../shared/slot_801EF468/func_801EF4F8.h"


    extern s32 func_800D1E28(void);
    extern void func_8002D4C8(s32, s32);
    extern s32 func_8001BFD0(void);
    extern s32 func_800291B4(s32);
    extern s32 func_800D0C48(s32);
    s32 func_801EF544(s32 param_1) {
        if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
            func_800D1E28();
            ((s32 (*)(s32, s32))func_8002D4C8)(0x1C, 0);
            func_8001BFD0();
            if ((func_800291B4(0xCE) & 0xFF) == 0) {
                ((s32 (*)(s32, s32))func_8002D4C8)(0x1D, 0);
                func_800D0C48(1);
            }
            *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
        }
        return 0;
    }


#include "../shared/slot_801EF468/func_801EF5D4.h"




void func_801EF5F4(void *a0) {

    extern void (*D_801EFDE0[])(void);
    D_801EFDE0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF630(void *a0) {

    extern void (*D_801EFDE8[])(void);
    D_801EFDE8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF66C(void *a0) {

    extern void (*D_801EFE6C[])(void);
    D_801EFE6C[*(u8 *)((s32)a0 + 0x214)]();
}


#include "../shared/slot_801EF468/func_801EF6A8.h"


INCLUDE_RODATA("asm/md_SC03_078/nonmatchings/md_SC03_078", D_801EF468);

#include "common.h"



const Blk8 D_801EF46C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};

extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void *);

void func_801EF6D0(u32 arg0) {
    Blk8 buffer;

    buffer = D_801EF46C;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EF738(void *arg0) {

    extern u8 D_801EFE3C[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EFE3C));
        func_80171A1C(arg0);
    }
}


#include "../shared/slot_801EF468/func_801EF790.h"



void func_801EF798(void *a0) {

    extern void (*D_801EFE7C[])(void);
    D_801EFE7C[*(u8 *)((s32)a0 + 0x214)]();
}


#include "../shared/slot_801EF468/func_801EF7D4.h"



const Blk8 D_801EF474 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801EF7F4(u32 arg0) {
    Blk8 buffer;

    buffer = D_801EF474;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


#include "../shared/slot_801EF468/func_801EF85C.h"


#include "../shared/slot_801EF468/func_801EF864.h"




void func_801EF928(void *a0) {

    extern void (*D_801EFE88[])(void);
    D_801EFE88[*(u8 *)((s32)a0 + 0x4)]();
}


#include "../shared/slot_801EF468/func_801EF964.h"



/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801EF98C;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801EF98C;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801EF98C(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801EFE8C[];
    extern u16 D_801EFE90[];

    MATRIX_801EDED4_801EF98C  m1;
    SVECTOR_801EDED4_801EF98C svec_in;
    SVECTOR_801EDED4_801EF98C svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801EFE8C[t];
        *(s16 *)(param_1 + 0x2E) = D_801EFE90[*(u8 *)(param_1 + 5)];
    }

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  0xA);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 0xA);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 0xA);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 0xA);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 0xA);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0xA);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0xA);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0xA);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_2[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_2[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}




void func_801EFB84(void *a0) {

    extern void (*D_801EFF94[])(void);
    D_801EFF94[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80029504(void);
extern s32 func_801877C0(s32);
extern s32 func_80187890(void);
extern s32 func_80187904(void);

void func_801EFBC0(s32 a0) {

    extern s32 D_801EFEB0[];
    extern s32 D_801EFEC4[];
    extern s32 D_801EFEE0[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_801877C0)();
        *(s32 *)(a0 + 0xE4) = D_801EFEB0[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80187890();
        *(s32 *)(a0 + 0xE4) = D_801EFEC4[v0];
    } else {
        s32 v0 = func_80187904();
        *(s32 *)(a0 + 0xE4) = D_801EFEE0[v0];
    }
}




extern s32 func_8014CB1C(void);

s32 func_801EFC60(void) {
    return (u32)func_8014CB1C() != 0;
}





extern void func_8014B2A8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801EFC80(void) {
    func_8014B2A8();
    ((s32 (*)(s32, s32))func_8002D4C8)(0x464, 0);
}


extern u8 *D_80126B10;
extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);

void func_801EFCAC(void *param_1) {

    extern s32 D_801EFF84;

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0:
        if (func_801789AC((s32)param_1) != 0) {
            func_80178CBC((s32)param_1, (s32)&D_801EFF84);
            *(u16 *)((s32)param_1 + 0x34) = 1;
        }
        break;
    case 1:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)param_1 + 0x34) = 2;
        }
        break;
    case 2:
        break;
    }
}


void func_801EFD40(void *a0) {
    extern s32 func_8018727C(void *a0, void *a1);
    extern u8 D_801EFE9C[];
    extern u8 D_801C3FC8[];
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern u8 D_801EFE94[];
    extern void (*D_801EFF1C[])(void);
    extern s32 func_80178B18(s32 a0, s32 a1);

    s32 s0 = (s32)a0;

    if (func_8018727C(a0, D_801EFE9C)) {
        *(u16 *)(s0 + 2) = 1;
        func_8012A828(s0, D_801C3FC8);
        func_8012E8E0(s0, (s32)D_801EFE94);
        *(u16 *)(s0 + 0x34) = 0;
        func_80178B18(s0, (s32)D_801EFF1C);
    }
}



u8 func_801EFDB0(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0x17;
}

