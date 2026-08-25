#include "common.h"
#include "../shared/engine_core.h"

extern u8 *D_80126B10;
extern u8 D_801F045C[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801EF47C(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801F045C;
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


#include "common.h"

extern s32 func_801789AC(s32 a0);
extern void func_80188F20(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);
extern u8 *D_80126B10;

void func_801EFD70(void *param_1) {

    extern s32 D_801F05D8;
    extern s32 D_801F05F0;
    extern s32 D_801F0574;

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80188F20(0);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801F05D8);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801F05F0);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        func_80178CBC((s32)param_1, (s32)&D_801F0574);
        *(u16 *)((s32)param_1 + 0x34) = 0;
        break;
    case 3:
        if (func_801789AC((s32)param_1) != 0) {
            func_80174438((s32)D_80126B10);
            *(u16 *)((s32)param_1 + 0x34) = 1;
        }
        break;
    }
}


extern s32 func_80029504(void);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801EFEA4(void *a0) {
    extern s32 D_801F66FC;
    extern s32 D_801F04B4;
    extern s16 D_801C3890;
    extern s32 D_801F050C;
    s32 v0;

    if ((u32)(func_80029504() - 0x122) < 0xA) {
        func_8012CAE4(a0);
        return;
    }

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F66FC);
        *(s16 *)(*(s32 *)((s32)a0 + 0x68) + 0xC) = 0x7FFF;
        func_8012E8E0((s32)a0, (s32)&D_801F04B4);
        *(s16 *)((s32)a0 + 0x2) = 1;
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_8012A828((s32)a0, (s32)&D_801C3890);
        func_80178B18((s32)a0, (s32)&D_801F050C);
    }
}


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


#include "common.h"

extern s32 func_80029504(void);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(u8 *a0);
extern s32 func_80178B18(s32 a0, s32 a1);

extern s32 D_801F6CAC;
extern s32 D_801F6CA8;
extern s32 D_801F0640[];
extern s32 D_801F0628[][2];
extern s32 D_801F0658[];
extern s32 D_801F070C;

void func_801F00F8(void *a0) {
    s32 v0;
    s32 cur;
    s32 target;

    if ((u32)(func_80029504() - 0x122) >= 0xA) {
        func_8012CAE4(a0);
        return;
    }

    if (*(s16 *)((s32)a0 + 0x70) == 0) {
        D_801F6CAC = func_8012C658(0x1C1, 1, 0);
        D_801F6CA8 = func_8012C658(0x1C1, 2, 0);
    }

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, D_801F0640[*(s16 *)((s32)a0 + 0x70)]);
    *(s16 *)(*(s32 *)((s32)a0 + 0x68) + 0xC) = 0x7FFF;
    func_8012E8E0((s32)a0, (s32)&D_801F0628[*(s16 *)((s32)a0 + 0x70)]);
    *(s16 *)((s32)a0 + 0x2) = 1;
    func_8012E8E0((s32)a0, (s32)&D_801F0628[*(s16 *)((s32)a0 + 0x70)]);
    func_8012E88C((u8 *)a0);

    cur = *(s32 *)((s32)a0 + 0x90);
    target = D_801F0658[*(s16 *)((s32)a0 + 0x70)];
    if (cur != target) {
        func_8012A828((s32)a0, target);
    }

    if (*(s16 *)((s32)a0 + 0x70) != 0) {
        func_80178B18((s32)a0, (s32)&D_801F070C);
    }
}




void func_801F0250(void *a0) {

    extern void (*D_801F081C[])(void);
    D_801F081C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801F6CA8;
extern s32 D_801F6CAC;

void func_801F028C(s32 arg0) {
    s32 a = D_801F6CA8;
    s32 b = D_801F6CAC;
    *(s16 *)(arg0 + 0xFC) = 1;
    *(s16 *)(a + 0xFC) = 0;
    *(s16 *)(b + 0xFC) = 0;
}


INCLUDE_ASM("asm/md_SC03_075/nonmatchings/md_SC03_075", func_801F02B0);

void func_801F02D4(void *a0) {
    extern s32 D_801F6CA8;
    extern s32 D_801F6CAC;
    register s32 v0 __asm__("$2");
    register s32 p __asm__("$4");
    v0 = D_801F6CA8;
    *(s16 *)((s32)a0 + 0xFC) = 0;
    p = D_801F6CAC;
    *(s16 *)(v0 + 0xFC) = 2;
    *(s16 *)(p + 0xFC) = 0;
}


void func_801F02F8(void *a0) {
    extern s32 D_801F6CA8;
    extern s32 D_801F6CAC;

    s32 var_v0 = D_801F6CA8;
    s32 var_v1 = D_801F6CAC;

    *(s16 *)((s32)a0 + 0xFC) = 0;
    *(s16 *)(var_v0 + 0xFC) = 0;
    *(s16 *)(var_v1 + 0xFC) = 1;
}


void func_801F031C(void *arg0) {
    extern s32 D_801F6CA8;
    extern s32 D_801F6CAC;
    s32 a = D_801F6CA8;
    s32 b = D_801F6CAC;
    *(s16 *)((s32)arg0 + 0xFC) = 0;
    *(s16 *)(a + 0xFC) = 0;
    *(s16 *)(b + 0xFC) = 0;
}


extern s32 D_801F6CAC;
extern s32 D_801F6CA8;

void func_801F033C(void *a0) {
    register s32 a __asm__("$3");
    s32 b;

    a = D_801F6CA8;
    *(s16 *)((s32)a0 + 0xFC) = 1;
    b = D_801F6CAC;
    *(s16 *)(a + 0xFC) = 3;
    *(s16 *)(b + 0xFC) = 3;
}


extern void func_80029514(s32 a0);
extern void func_80174438(s32 a0);
extern void func_80029124(s32 arg0, s32 arg1);
extern u8 *D_80126B10;

void func_801F0364(void) {
    func_80029514(0x12C);
    func_80174438((s32)D_80126B10);
    func_80029124(0x10F, 1);
}




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

