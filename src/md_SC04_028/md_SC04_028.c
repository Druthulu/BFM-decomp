#include "common.h"

#include "common.h"

extern u8 D_801E8798[];

void func_800167B8(int);
void func_80175414(s32 _arg0);

int func_801E7B50(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E8798;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_801E7BA8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E7C(void *arg0);

s32 func_801E7BCC(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E7C, 0x1000000);
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

s32 func_801E7C18(s32 param_1) {
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
void func_801E7CB8(void) {
    func_800D1EBC();
}




void func_801E7CD8(void *a0) {

    extern void (*D_801E873C[])(void);
    D_801E873C[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D14(void *a0) {

    extern void (*D_801E8744[])(void);
    D_801E8744[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D50(void *a0) {

    extern void (*D_801E87C8[])(void);
    D_801E87C8[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801E7D8C(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC04_028/nonmatchings/md_SC04_028", D_801E7B28);

typedef struct { u8 c[8]; } Blk8;
const Blk8 D_801E7B2C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E7DB4(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E7B2C;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E7E1C(void *arg0) {

    extern u8 D_801E8798[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E8798));
        func_80171A1C(arg0);
    }
}


void func_801E7E74(void) {
}



void func_801E7E7C(void *a0) {

    extern void (*D_801E87D8[])(void);
    D_801E87D8[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801E7EB8(void) {
    ((void (*)(void))func_80171A1C)();
}



const Blk8 D_801E7B34 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E7ED8(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E7B34;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


void func_801E7F40(void) {
}

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E800C(void *a0);

void func_801E7F48(void) {

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
    D_80126978 = -0x50;
    D_8012697A = 0;
    func_8012A018((s32)func_801E800C, 0);
    func_801E800C(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E800C(void *a0) {

    extern void (*D_801E87E4[])(void);
    D_801E87E4[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8048);

typedef struct { short vx, vy, vz, pad; } SVECTOR;
typedef struct { short m[3][3]; long t[3]; } MATRIX;
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801E8070(s32 param_1, s16 *param_2) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  0xa);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 0xa);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 0xa);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 0xa);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 0xa);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0xa);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0xa);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0xa);

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



u8 func_801E8208(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}
