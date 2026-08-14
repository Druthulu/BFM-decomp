#include "common.h"

#include "common.h"

extern u8 D_801F00E8[];

void func_800167B8(int);
void func_80175414(s32 _arg0);

int func_801EF490(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801F00E8;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_801EF4E8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EF7CC(void *arg0);

s32 func_801EF50C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EF7CC, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF558);

extern void func_800D1EBC(void);
void func_801EF608(void) {
    func_800D1EBC();
}




void func_801EF628(void *a0) {

    extern void (*D_801F008C[])(void);
    D_801F008C[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF664(void *a0) {

    extern void (*D_801F0094[])(void);
    D_801F0094[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF6A0(void *a0) {

    extern void (*D_801F0118[])(void);
    D_801F0118[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801EF6DC(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC03_077/nonmatchings/md_SC03_077", D_801EF468);

#include "common.h"

typedef struct { u8 c[8]; } Blk8;

const Blk8 D_801EF46C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};

extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void *);

void func_801EF704(u32 arg0) {
    Blk8 buffer;

    buffer = D_801EF46C;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EF76C(void *arg0) {

    extern u8 D_801F00E8[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801F00E8));
        func_80171A1C(arg0);
    }
}


void func_801EF7C4(void) {
}



void func_801EF7CC(void *a0) {

    extern void (*D_801F0128[])(void);
    D_801F0128[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801EF808(void) {
    ((void (*)(void))func_80171A1C)();
}


#include "common.h"



const Blk8 D_801EF474 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};

extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void *);

void func_801EF828(u32 arg0) {
    Blk8 buffer;

    buffer = D_801EF474;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


void func_801EF890(void) {
}

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF898);



void func_801EF95C(void *a0) {

    extern void (*D_801F0134[])(void);
    D_801F0134[*(u8 *)((s32)a0 + 0x4)]();
}


extern void func_801EF9C0(s32 param_1, s16 *param_2);

void func_801EF998(s32 param_1) {
    extern s16 D_801274E8;
    func_801EF9C0(param_1, &D_801274E8);
}


typedef struct { short vx, vy, vz, pad; } SVECTOR;
typedef struct { short m[3][3]; long t[3]; } MATRIX;
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801EF9C0(s32 param_1, s16 *param_2) {
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


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFB58);



void func_801EFCB4(void *a0) {

    extern void (*D_801F0450[])(void);
    D_801F0450[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFCF0);



void func_801EFD00(void) {

    extern s32 D_801F7464;
    D_801F7464 = 1;
}




s32 func_801EFD14(void) {

    extern s32 D_801F7464;
    return D_801F7464;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFD24(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFD60);

extern void func_80029514(int);
void func_801EFE3C(void) {
    func_80029514(0x181);
}


extern void func_8018D0E4(void);
void func_801EFE5C(void) {
    func_8018D0E4();
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFE7C);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFF08);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFF20);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFF50);

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *);
extern void func_8001C214(s32, s32);
extern void func_8012A828(s32, s32);
extern void func_8012E8E0(s32, s32);
extern void func_80178B18(s32, s32);
extern s32 func_80029504(void);

void func_801EFFAC(void *a0) {
    extern s32 D_801F742C;
    extern s32 D_801C4188;
    extern s32 D_801F0138;
    extern s32 D_801F0168;
    extern s32 D_801F7460;
    extern s32 D_801F745C;
    s32 v0;
    s32 ptr;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F742C);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s32 *)&D_801F7460 = 0;
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801C4188);
        func_8012E8E0((s32)a0, (s32)&D_801F0138);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801F0168);
        v0 = func_80029504();
        *(s32 *)&D_801F745C = v0;
    }
}



u8 func_801F005C(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}

