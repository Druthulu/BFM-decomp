#include "common.h"
#include "../shared/engine_core.h"

extern u8 *D_80126B10;
extern u8 D_801E2FA4[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801E25FC(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E2FA4;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_801E2654(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E2928(void *arg0);

s32 func_801E2678(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E2928, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}




extern s32 func_800D1E28(void);
extern void func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);

s32 func_801E26C4(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        ((s32 (*)(s32, s32))func_8002D4C8)(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
            ((s32 (*)(s32, s32))func_8002D4C8)(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801E2764(void) {
    func_800D1EBC();
}




void func_801E2784(void *a0) {

    extern void (*D_801E2F48[])(void);
    D_801E2F48[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27C0(void *a0) {

    extern void (*D_801E2F50[])(void);
    D_801E2F50[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27FC(void *a0) {

    extern void (*D_801E2FD4[])(void);
    D_801E2FD4[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801E2838(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC03_137/nonmatchings/md_SC03_137", D_801E25E8);


const Blk8 D_801E25EC = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E2860(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E25EC;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E28C8(void *arg0) {

    extern u8 D_801E2FA4[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E2FA4));
        func_80171A1C(arg0);
    }
}


void func_801E2920(void) {
}



void func_801E2928(void *a0) {

    extern void (*D_801E2FE4[])(void);
    D_801E2FE4[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801E2964(void) {
    ((void (*)(void))func_80171A1C)();
}



const Blk8 D_801E25F4 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E2984(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E25F4;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


void func_801E29EC(void) {
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E2AB8(void *a0);

void func_801E29F4(void) {

    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;

    D_80126954 = 0x190;
    D_80126950 = 0x190;
    D_8012695C = 0x82;
    D_80126968 = 0xFB1;
    D_8012696A = 0x7C7;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x36;
    D_8012697A = 0;
    func_8012A018((s32)func_801E2AB8, 0);
    func_801E2AB8(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E2AB8(void *a0) {

    extern void (*D_801E2FF0[])(void);
    D_801E2FF0[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_801E2AF4()  /* dedup: shared engine-core @0x801E2AF4 (src/shared) */


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801E2B1C;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801E2B1C;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801E2B1C(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801E2FF4[];
    extern u16 D_801E2FF8[];

    MATRIX_801EDED4_801E2B1C  m1;
    SVECTOR_801EDED4_801E2B1C svec_in;
    SVECTOR_801EDED4_801E2B1C svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E2FF4[t];
        *(s16 *)(param_1 + 0x2E) = D_801E2FF8[*(u8 *)(param_1 + 5)];
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



s32 func_801E2D14(void) {
    return 39;
}




void func_801E2D1C(void *a0) {

    extern void (*D_801E30FC[])(void);
    D_801E30FC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801E3018[];
extern s32 D_801E302C[];
extern s32 D_801E3048[];
extern s32 func_80029504(void);
extern s32 func_80184428(s32);
extern s32 func_801844F8(void);
extern s32 func_8018456C(void);

void func_801E2D58(s32 a0) {

    extern s32 D_801E3018[];
    extern s32 D_801E302C[];
    extern s32 D_801E3048[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184428)();
        *(s32 *)(a0 + 0xE4) = D_801E3018[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_801844F8();
        *(s32 *)(a0 + 0xE4) = D_801E302C[v0];
    } else {
        s32 v0 = func_8018456C();
        *(s32 *)(a0 + 0xE4) = D_801E3048[v0];
    }
}




extern s32 func_8014CB1C(void);

s32 func_801E2DF8(void) {
    return (u32)func_8014CB1C() != 0;
}





extern void func_8014B2A8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801E2E18(void) {
    func_8014B2A8();
    ((s32 (*)(s32, s32))func_8002D4C8)(0x464, 0);
}


void func_801E2E44(void *param_1) {

    extern u8 *D_80126B10;
    extern s32 D_801E30EC;
    extern s32 func_801789AC(s32 a0);
    extern void func_80178CBC(s32 a0, s32 a1);
    extern void func_80174438(s32 a0);

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0:
        if (func_801789AC((s32)param_1) != 0) {
            func_80178CBC((s32)param_1, (s32)&D_801E30EC);
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


extern s32 D_801E3004[];
extern s32 func_80183EE4(void *a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801BF330;
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 D_801E2FFC;
extern s32 func_80178B18(s32 a0, s32 a1);
extern void *D_801E3084;

void func_801E2ED8(void *param_1) {
    if (func_80183EE4(param_1, D_801E3004) != 0) {
        *(s16 *)((s32)param_1 + 0x2) = 1;
        func_8012A828((s32)param_1, &D_801BF330);
        func_8012E8E0((s32)param_1, (s32)&D_801E2FFC);
        *(u16 *)((s32)param_1 + 0x34) = 0;
        func_80178B18((s32)param_1, (s32)&D_801E3084);
    }
}

