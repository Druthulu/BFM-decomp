#include "common.h"
#include "../shared/engine_core.h"

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF47C);


DEFINE_func_801EF4D4()  /* dedup: shared engine-core @0x801EF4D4 (src/shared) */



DEFINE_func_801EF4F8()  /* dedup: shared engine-core @0x801EF4F8 (src/shared) */


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF544);

DEFINE_func_801EF5D4()  /* dedup: shared engine-core @0x801EF5D4 (src/shared) */




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


DEFINE_func_801EF6A8()  /* dedup: shared engine-core @0x801EF6A8 (src/shared) */


INCLUDE_RODATA("asm/md_SC03_078/nonmatchings/md_SC03_078", D_801EF468);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF6D0);


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


DEFINE_func_801EF790()  /* dedup: shared engine-core @0x801EF790 (src/shared) */



void func_801EF798(void *a0) {

    extern void (*D_801EFE7C[])(void);
    D_801EFE7C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801EF7D4()  /* dedup: shared engine-core @0x801EF7D4 (src/shared) */


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF7F4);

DEFINE_func_801EF85C()  /* dedup: shared engine-core @0x801EF85C (src/shared) */


DEFINE_func_801EF864()  /* dedup: shared engine-core @0x801EF864 (src/shared) */




void func_801EF928(void *a0) {

    extern void (*D_801EFE88[])(void);
    D_801EFE88[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EF964);


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


INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EFCAC);

INCLUDE_ASM("asm/md_SC03_078/nonmatchings/md_SC03_078", func_801EFD40);


u8 func_801EFDB0(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0x17;
}

