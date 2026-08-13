#include "common.h"
#include "../shared/engine_core.h"

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF47C);


DEFINE_func_801EF4D4()  /* dedup: shared engine-core @0x801EF4D4 (src/shared) */



DEFINE_func_801EF4F8()  /* dedup: shared engine-core @0x801EF4F8 (src/shared) */


DEFINE_func_801EF544()  /* dedup: shared engine-core @0x801EF544 (src/shared) */

DEFINE_func_801EF5D4()  /* dedup: shared engine-core @0x801EF5D4 (src/shared) */




void func_801EF5F4(void *a0) {

    extern void (*D_801F0400[])(void);
    D_801F0400[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF630(void *a0) {

    extern void (*D_801F0408[])(void);
    D_801F0408[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF66C(void *a0) {

    extern void (*D_801F048C[])(void);
    D_801F048C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801EF6A8()  /* dedup: shared engine-core @0x801EF6A8 (src/shared) */


INCLUDE_RODATA("asm/md_SC03_075/nonmatchings/md_SC03_075", D_801EF468);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF6D0);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EF738(void *arg0) {

    extern u8 D_801F045C[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801F045C));
        func_80171A1C(arg0);
    }
}


DEFINE_func_801EF790()  /* dedup: shared engine-core @0x801EF790 (src/shared) */



void func_801EF798(void *a0) {

    extern void (*D_801F049C[])(void);
    D_801F049C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801EF7D4()  /* dedup: shared engine-core @0x801EF7D4 (src/shared) */


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EF7F4);

DEFINE_func_801EF85C()  /* dedup: shared engine-core @0x801EF85C (src/shared) */


DEFINE_func_801EF864()  /* dedup: shared engine-core @0x801EF864 (src/shared) */




void func_801EF928(void *a0) {

    extern void (*D_801F04A8[])(void);
    D_801F04A8[*(u8 *)((s32)a0 + 0x4)]();
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
    extern s16 D_801F04AC[];
    extern u16 D_801F04B0[];

    MATRIX_801EDED4_801EF98C  m1;
    SVECTOR_801EDED4_801EF98C svec_in;
    SVECTOR_801EDED4_801EF98C svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801F04AC[t];
        *(s16 *)(param_1 + 0x2E) = D_801F04B0[*(u8 *)(param_1 + 5)];
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

    extern void (*D_801F0620[])(void);
    D_801F0620[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFBC0);



void func_801EFC0C(void) {

    extern s32 D_801F6CA4;
    D_801F6CA4 = 1;
}




s32 func_801EFC20(void) {

    extern s32 D_801F6CA4;
    return D_801F6CA4;
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFC30);




extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFC94(void) {
        if ((func_80029178(0x10f) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10f, 1);
            return 1;
        }
        return 0;
    }




extern s32 func_80029504(void);
extern s32 func_801877C0(s32);
extern s32 func_80187890(void);
extern s32 func_80187904(void);
extern void func_80187960(void);

void func_801EFCD0(s32 a0) {

    extern s32 D_801F0594[];
    extern s32 D_801F05A8[];
    extern s32 D_801F05C4[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_801877C0)();
        *(s32 *)(a0 + 0xE4) = D_801F0594[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80187890();
        *(s32 *)(a0 + 0xE4) = D_801F05A8[v0];
    } else {
        s32 v0 = func_80187904();
        *(s32 *)(a0 + 0xE4) = D_801F05C4[v0];
        func_80187960();
    }
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFD70);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801EFEA4);

extern s32 func_8012BA10(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_801789AC(s32 a0);
extern void func_80178D18(s32 a0);

void func_801EFF54(void *param_1) {

    extern s32 D_801F0658[];
    extern s32 D_801F064C[];
    extern s32 D_801F0664[];

    switch (*(s16 *)((s32)param_1 + 0xFC)) {
    case 0: {
        s32 v0 = func_8012BA10((s32)param_1, 0x10);
        s32 cur;
        s32 target;
        *(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) =
            (*(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) + v0) & 0xFFF;
        cur = *(s32 *)((s32)param_1 + 0x90);
        target = D_801F0658[*(s16 *)((s32)param_1 + 0x70)];
        if (cur != target) {
            func_8012A828((s32)param_1, target);
        }
        break;
    }
    case 1: {
        s32 v0 = func_8012BA10((s32)param_1, 0x10);
        s32 cur;
        s32 target;
        *(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) =
            (*(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) + v0) & 0xFFF;
        cur = *(s32 *)((s32)param_1 + 0x90);
        target = D_801F064C[*(s16 *)((s32)param_1 + 0x70)];
        if (cur != target) {
            func_8012A828((s32)param_1, target);
        }
        break;
    }
    case 2: {
        s32 v0 = func_8012B608(*(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12), 0x600, 8);
        s32 cur;
        s32 target;
        *(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) =
            (*(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) + v0) & 0xFFF;
        cur = *(s32 *)((s32)param_1 + 0x90);
        target = D_801F064C[*(s16 *)((s32)param_1 + 0x70)];
        if (cur != target) {
            func_8012A828((s32)param_1, target);
        }
        break;
    }
    case 3: {
        s32 cur = *(s32 *)((s32)param_1 + 0x90);
        s32 target = D_801F0664[*(s16 *)((s32)param_1 + 0x70)];
        if (cur != target) {
            func_8012A828((s32)param_1, target);
        }
        break;
    }
    }

    if (*(s16 *)((s32)param_1 + 0x70) == 0) {
        if (func_801789AC((s32)param_1) != 0) {
            func_80178D18((s32)param_1);
            *(s16 *)((s32)param_1 + 0x70) = 2;
        }
    }
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F00F8);



void func_801F0250(void *a0) {

    extern void (*D_801F081C[])(void);
    D_801F081C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F028C);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F02B0);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F02D4);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F02F8);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F031C);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F033C);

INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F0364);



extern void func_80029124(s32 arg0, s32 arg1);
    void func_801F03A0(void) {
        func_80029124(0xF5, 1);
        func_80029124(0xFB, 1);
    }



u8 func_801F03D0(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xE;
}

