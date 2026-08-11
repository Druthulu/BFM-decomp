#include "common.h"

INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7B34);


extern s32 func_800167F0(s32 a0);

s32 func_801E7B8C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E60(void *arg0);

s32 func_801E7BB0(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E60, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}




extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);

s32 func_801E7BFC(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801E7C9C(void) {
    func_800D1EBC();
}




void func_801E7CBC(void *a0) {

    extern void (*D_801E8558[])(void);
    D_801E8558[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7CF8(void *a0) {

    extern void (*D_801E8560[])(void);
    D_801E8560[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D34(void *a0) {

    extern void (*D_801E85E4[])(void);
    D_801E85E4[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(void);
void func_801E7D70(void) {
    ((void (*)(void))func_80171A1C)();
    func_80175414();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7D98);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E7E00(void *arg0) {

    extern u8 D_801E85B4[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E85B4));
        func_80171A1C(arg0);
    }
}


void func_801E7E58(void) {
}



void func_801E7E60(void *a0) {

    extern void (*D_801E85F4[])(void);
    D_801E85F4[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801E7E9C(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E7EBC);

void func_801E7F24(void) {
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E7FF0(void *a0);

void func_801E7F2C(void) {

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
    func_8012A018((s32)func_801E7FF0, 0);
    func_801E7FF0(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E7FF0(void *a0) {

    extern void (*D_801E8600[])(void);
    D_801E8600[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E802C);


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801E8054;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801E8054;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801E8054(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801E8604[];
    extern u16 D_801E8608[];

    MATRIX_801EDED4_801E8054  m1;
    SVECTOR_801EDED4_801E8054 svec_in;
    SVECTOR_801EDED4_801E8054 svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E8604[t];
        *(s16 *)(param_1 + 0x2E) = D_801E8608[*(u8 *)(param_1 + 5)];
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



u8 func_801E824C(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}




void func_801E827C(void *a0) {

    extern void (*D_801E8708[])(void);
    D_801E8708[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E82B8);



void func_801E82C8(void) {

    extern s32 D_801EECE4;
    D_801EECE4 = 1;
}




s32 func_801E82DC(void) {

    extern s32 D_801EECE4;
    return D_801EECE4;
}




extern s32 func_80029504(void);
extern s32 func_80184D00(s32);
extern s32 func_80184DD0(void);
extern s32 func_80184E44(void);
extern void func_80184EA0(void);

void func_801E82EC(s32 a0) {

    extern s32 D_801E867C[];
    extern s32 D_801E8690[];
    extern s32 D_801E86AC[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184D00)();
        *(s32 *)(a0 + 0xE4) = D_801E867C[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184DD0();
        *(s32 *)(a0 + 0xE4) = D_801E8690[v0];
    } else {
        s32 v0 = func_80184E44();
        *(s32 *)(a0 + 0xE4) = D_801E86AC[v0];
        func_80184EA0();
    }
}


INCLUDE_ASM("asm/md_SC04_024/nonmatchings/md_SC04_024", func_801E838C);


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E84C0(void *a0) {
    extern s32 D_801EECB8;
    extern s32 D_801B9A50;
    extern s32 D_801E860C;
    extern s32 D_801E8614;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801EECB8);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801B9A50);
        func_8012E8E0((s32)a0, (s32)&D_801E860C);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801E8614);
    }
}


INCLUDE_RODATA("asm/md_SC04_024/nonmatchings/md_SC04_024", D_801E7B28);

INCLUDE_RODATA("asm/md_SC04_024/nonmatchings/md_SC04_024", D_801E7B2C);
