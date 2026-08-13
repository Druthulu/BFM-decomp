#include "common.h"
#include "../shared/engine_core.h"

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF47C);


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

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF6D0);


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


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF7F4);

DEFINE_func_801EF85C()  /* dedup: shared engine-core @0x801EF85C (src/shared) */


DEFINE_func_801EF864()  /* dedup: shared engine-core @0x801EF864 (src/shared) */




void func_801EF928(void *a0) {

    extern void (*D_801EFFE0[])(void);
    D_801EFFE0[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EF964);


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


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFBC0);



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


INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFC6C);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFD28);

INCLUDE_ASM("asm/md_SC03_074/nonmatchings/md_SC03_074", func_801EFE5C);


u8 func_801EFF08(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xE;
}

