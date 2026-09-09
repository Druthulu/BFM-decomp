#include "common.h"
#include "../shared/engine_prelude.h"

extern u8 *D_80126B10;
extern u8 D_801E334C[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801E25FC(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E334C;
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

#include "../shared/slot_801E25E8/func_801E2678.h"


extern void func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern void func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern void func_800D0C48(s32);

s32 func_801E26C4(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
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

    extern void (*D_801E32F0[])(void);
    D_801E32F0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27C0(void *a0) {

    extern void (*D_801E32F8[])(void);
    D_801E32F8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E27FC(void *a0) {

    extern void (*D_801E337C[])(void);
    D_801E337C[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801E2838(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC03_138/nonmatchings/md_SC03_138", D_801E25E8);


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

    extern u8 D_801E334C[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E334C));
        func_80171A1C(arg0);
    }
}


void func_801E2920(void) {
}



void func_801E2928(void *a0) {

    extern void (*D_801E338C[])(void);
    D_801E338C[*(u8 *)((s32)a0 + 0x214)]();
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

#include "../shared/slot_801E25E8/func_801E29F4.h"




void func_801E2AB8(void *a0) {

    extern void (*D_801E3398[])(void);
    D_801E3398[*(u8 *)((s32)a0 + 0x4)]();
}


#include "../shared/slot_801E25E8/func_801E2AF4.h"



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
    extern s16 D_801E339C[];
    extern u16 D_801E33A0[];

    MATRIX_801EDED4_801E2B1C  m1;
    SVECTOR_801EDED4_801E2B1C svec_in;
    SVECTOR_801EDED4_801E2B1C svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E339C[t];
        *(s16 *)(param_1 + 0x2E) = D_801E33A0[*(u8 *)(param_1 + 5)];
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




void func_801E2D14(void *a0) {

    extern void (*D_801E3464[])(void);
    D_801E3464[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801E2D50(void) {
    extern s32 D_801E2460;
    extern s32 D_801EC2C4;
    extern s32 D_801E256C;
    extern s32 D_801E3904[];
    extern s32 D_801E3920[];

    s32 var;

    var = D_801E2460;
    D_801EC2C4 = var;
    if (var == 1) {
        *(s32 *)(D_801E256C + 4) = (s32)D_801E3904;
    } else {
        *(s32 *)(D_801E256C + 4) = (s32)D_801E3920;
    }
}


void func_801E2D9C(void) {
    extern s32 D_801E2460;
    extern s32 D_801EC2C4;
    extern s32 D_801E256C;
    extern s32 D_801E3904[];
    extern s32 D_801E394C[];

    s32 var;

    var = D_801E2460;
    D_801EC2C4 = var;
    if (var == 1) {
        *(s32 *)(D_801E256C + 4) = (s32)D_801E3904;
    } else {
        *(s32 *)(D_801E256C + 4) = (s32)D_801E394C;
    }
}




void func_801E2DE8(void) {

    extern s32 D_801EC2C4;
    extern s32 D_801E2460;
    D_801E2460 = D_801EC2C4;
}


extern u8 *D_80126B10;
extern s32 func_801789AC(s32 a0);
extern void func_80174438(s32 a0);

void func_801E2E00(void *param_1) {

    extern u8 D_800D39CC[];
    extern void func_800D1724(void *);
    extern void func_80029124(s32, s32);
    s32 st;

    st = *(u16 *)((s32)param_1 + 0x34);
    switch (st) {
    case 0:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)param_1 + 0x34) = 2;
        }
        break;
    case 1:
        switch (func_801789AC((s32)param_1)) {
        case 1:
            func_800D1724(D_800D39CC);
            func_80029124(0xFF, 1);
            *(u16 *)((s32)param_1 + 0x34) = 2;
            break;
        case 2:
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)param_1 + 0x34) = 2;
            break;
        }
        break;
    case 2:
        break;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_80029504(void);

void func_801E2EC4(s32 a0) {
    extern s32 D_801E33A4;
    extern s32 D_801E33DC;
    extern s32 D_801E33F4;
    extern s32 D_801E342C;
    s32 v0;
    s32 ptr;
    s32 flag;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C214(v0, 0);
    ptr = *(s32 *)(a0 + 0x68);
    *(s16 *)(ptr + 0xC) = 0x7FFF;
    flag = 1;
    *(s16 *)(a0 + 0x2) = flag;
    func_8012E8E0(a0, (s32)&D_801E33A4);
    if (func_80029504() < 0x140) {
        *(s16 *)(a0 + 0x34) = 0;
        func_80178B18(a0, (s32)&D_801E33DC);
    } else {
        if ((func_80029178(0xFF) & 0xFF) != 0) {
            *(s16 *)(a0 + 0x34) = flag;
            func_80178B18(a0, (s32)&D_801E342C);
        } else {
            *(s16 *)(a0 + 0x34) = flag;
            func_80178B18(a0, (s32)&D_801E33F4);
        }
    }
}



s32 func_801E2F98(void) {
    return 39;
}


void func_801E2FA0(void) {
}

void func_801E2FA8(void) {
}

extern u8 *D_80126B10;
extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern void func_80185B88(s32 a0);
extern s16 func_80185B78(void);
extern void func_800D1724(void *);

void func_801E2FB0(void *param_1) {

    extern s32 D_801E34FC;
    extern s32 D_801E3560;
    extern s32 D_801E3578;
    extern s32 D_800D39CC;

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v1 = func_801789AC((s32)param_1);
        switch (v1) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80185B88(5);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801E3560);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801E3578);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2: {
        s32 v0 = func_80185B78();
        if (v0 != 0) {
            func_800D1724((void *)&D_800D39CC);
            *(u16 *)((s32)param_1 + 0x34) = 1;
        } else {
            func_80178CBC((s32)param_1, (s32)&D_801E34FC);
            *(u16 *)((s32)param_1 + 0x34) = 0;
        }
        break;
    }
    case 3:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)param_1 + 0x34) = 1;
        }
        break;
    }
}




void func_801E310C(void *a0) {

    extern void (*D_801E35A8[])(void);
    D_801E35A8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801E3148(void) {

    extern s32 D_801EC2C8;
    D_801EC2C8 = 0;
}




void func_801E3158(void) {

    extern s32 D_801EC2C8;
    D_801EC2C8 = 1;
}




s32 func_801E316C(void) {

    extern s32 D_801EC2C8;
    return D_801EC2C8;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E317C(void) {
        if ((func_80029178(0x112) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x112, 1);
            return 1;
        }
        return 0;
    }




extern s32 func_80029504(void);
extern s32 func_80184428(s32);
extern s32 func_801844F8(void);
extern s32 func_8018456C(void);
extern void func_801845C8(void);

void func_801E31B8(s32 a0) {

    extern s32 D_801E351C[];
    extern s32 D_801E3530[];
    extern s32 D_801E354C[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184428)();
        *(s32 *)(a0 + 0xE4) = D_801E351C[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_801844F8();
        *(s32 *)(a0 + 0xE4) = D_801E3530[v0];
    } else {
        s32 v0 = func_8018456C();
        *(s32 *)(a0 + 0xE4) = D_801E354C[v0];
        func_801845C8();
    }
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E3258(void *a0) {
    extern s32 D_801EB4C0;
    extern s32 D_801EC26C;
    extern s32 D_801E346C;
    extern s32 D_801E349C;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801EB4C0);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801EC26C);
        func_8012E8E0((s32)a0, (s32)&D_801E346C);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801E349C);
    }
}

