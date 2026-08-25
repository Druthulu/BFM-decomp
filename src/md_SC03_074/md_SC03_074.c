#include "common.h"
#include "../shared/engine_core.h"

extern u8 *D_80126B10;
extern u8 D_801EFF94[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801EF47C(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801EFF94;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



DEFINE_func_801EF4D4()  /* dedup: shared engine-core @0x801EF4D4 (src/shared) */



DEFINE_func_801EF4F8()  /* dedup: shared engine-core @0x801EF4F8 (src/shared) */


DEFINE_func_801EF544()  /* dedup: shared engine-core @0x801EF544 (src/shared) */

DEFINE_func_801EF5D4()  /* dedup: shared engine-core @0x801EF5D4 (src/shared) */




void func_801EF5F4(void *a0) {

    extern void (*D_801EFF38[])(void);
    D_801EFF38[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF630(void *a0) {

    extern void (*D_801EFF40[])(void);
    D_801EFF40[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF66C(void *a0) {

    extern void (*D_801EFFC4[])(void);
    D_801EFFC4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801EF6A8()  /* dedup: shared engine-core @0x801EF6A8 (src/shared) */


INCLUDE_RODATA("asm/md_SC03_074/nonmatchings/md_SC03_074", D_801EF468);


const Blk8 D_801EF46C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

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

    extern u8 D_801EFF94[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EFF94));
        func_80171A1C(arg0);
    }
}


DEFINE_func_801EF790()  /* dedup: shared engine-core @0x801EF790 (src/shared) */



void func_801EF798(void *a0) {

    extern void (*D_801EFFD4[])(void);
    D_801EFFD4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801EF7D4()  /* dedup: shared engine-core @0x801EF7D4 (src/shared) */



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


DEFINE_func_801EF85C()  /* dedup: shared engine-core @0x801EF85C (src/shared) */


DEFINE_func_801EF864()  /* dedup: shared engine-core @0x801EF864 (src/shared) */




void func_801EF928(void *a0) {

    extern void (*D_801EFFE0[])(void);
    D_801EFFE0[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_801EF964()  /* dedup: shared engine-core @0x801EF964 (src/shared) */


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
    extern s16 D_801EFFE4[];
    extern u16 D_801EFFE8[];

    MATRIX_801EDED4_801EF98C  m1;
    SVECTOR_801EDED4_801EF98C svec_in;
    SVECTOR_801EDED4_801EF98C svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801EFFE4[t];
        *(s16 *)(param_1 + 0x2E) = D_801EFFE8[*(u8 *)(param_1 + 5)];
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

    extern void (*D_801F0120[])(void);
    D_801F0120[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801EFBC0(void) {

    extern u8 D_80078EB1;
    extern s32 D_801EF3EC;
    extern s32 D_801F5F04;
    extern s32 D_801F0234[];
    extern s32 D_801F0204[];

    D_801F5F04 = 0;
    if ((u32)D_80078EB1 >= 0x12) {
        *(s32 *)(D_801EF3EC + 4) = (s32)D_801F0234;
    } else {
        *(s32 *)(D_801EF3EC + 4) = (s32)D_801F0204;
    }
}




void func_801EFC0C(void) {

    extern s32 D_801F5F04;
    D_801F5F04 = 1;
}




s32 func_801EFC20(void) {

    extern s32 D_801F5F04;
    return D_801F5F04;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFC30(void) {
        if ((func_80029178(0x10e) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10e, 1);
            return 1;
        }
        return 0;
    }


extern s32 func_80029504(void);
extern s32 func_801877C0(void);
extern s32 func_80187890(void);
extern s32 func_80187904(void);
extern void func_80187960(void);

void func_801EFC6C(s32 a0) {
    extern s32 D_801F0094[];
    extern s32 D_801F0734;
    extern s32 D_801F00A8[];
    extern s32 D_801F00C4[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = func_801877C0();
        *(s32 *)(a0 + 0xE4) = D_801F0094[v0];
    } else if (v1 < 0x384) {
        if ((u32)(v1 - 0x136) < 0x122) {
            *(s32 *)(a0 + 0xE4) = (s32)&D_801F0734;
        } else {
            s32 v0 = func_80187890();
            *(s32 *)(a0 + 0xE4) = D_801F00A8[v0];
        }
    } else {
        s32 v0 = func_80187904();
        *(s32 *)(a0 + 0xE4) = D_801F00C4[v0];
        func_80187960();
    }
}


extern s32 func_801789AC(s32 arg0);
extern void func_80188F20(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern u8 *D_80126B10;

void func_801EFD28(void *a0) {

    extern s32 D_801F00D8;
    extern s32 D_801F00F0;
    extern s32 D_801F0074;

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0: {
        s32 v0 = func_801789AC((s32)a0);
        switch (v0) {
        case 1:
            *(u16 *)((s32)a0 + 0x34) = 2;
            func_80188F20(1);
            break;
        case 2:
            func_80178CBC((s32)a0, (s32)&D_801F00D8);
            *(u16 *)((s32)a0 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)a0, (s32)&D_801F00F0);
            *(u16 *)((s32)a0 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        func_80178CBC((s32)a0, (s32)&D_801F0074);
        *(u16 *)((s32)a0 + 0x34) = 0;
        break;
    case 3:
        if (func_801789AC((s32)a0) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)a0 + 0x34) = 1;
        }
        break;
    }
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801EFE5C(void *a0) {
    extern s32 D_801F5EE4;
    extern s32 D_801C3890;
    extern s32 D_801F001C;
    extern u16 D_801EFFEC;
    extern u16 D_801EFFEE;
    extern u16 D_801EFFF0;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F5EE4);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(u16 *)((s32)a0 + 0x6) = D_801EFFEC;
        *(u16 *)((s32)a0 + 0xA) = D_801EFFEE;
        *(u16 *)((s32)a0 + 0xE) = D_801EFFF0;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(u16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801C3890);
        *(u16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801F001C);
    }
}



u8 func_801EFF08(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xE;
}

