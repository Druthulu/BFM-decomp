#include "common.h"

extern u8 *D_80126B10;
extern u8 D_801EE9B4[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801ED99C(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801EE9B4;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_801ED9F4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCE0(void *arg0);

s32 func_801EDA18(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EDCE0, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029504(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_800D0C48(s32);
extern s32 func_800D1E28(void);

s32 func_801EDA64(s32 param_1) {
    u32 s1 = func_80029504();

    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 &&
            (s1 - 0x384) >= 0x6E && (s1 - 0x460) >= 0x32) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801EDB1C(void) {
    func_800D1EBC();
}




void func_801EDB3C(void *a0) {

    extern void (*D_801EE958[])(void);
    D_801EE958[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDB78(void *a0) {

    extern void (*D_801EE960[])(void);
    D_801EE960[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDBB4(void *a0) {

    extern void (*D_801EE9E4[])(void);
    D_801EE9E4[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801EDBF0(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC05_025/nonmatchings/md_SC05_025", D_801ED988);

typedef struct { u8 c[8]; } Blk8;

const Blk8 D_801ED98C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};

extern int func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801EDC18(u32 arg0) {
    Blk8 buffer;

    buffer = D_801ED98C;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EDC80(void *arg0) {

    extern u8 D_801EE9B4[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EE9B4));
        func_80171A1C(arg0);
    }
}


void func_801EDCD8(void) {
}



void func_801EDCE0(void *a0) {

    extern void (*D_801EE9F4[])(void);
    D_801EE9F4[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801EDD1C(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDD3C);

void func_801EDDA4(void) {
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801EDE70(void *a0);

void func_801EDDAC(void) {

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
    func_8012A018((s32)func_801EDE70, 0);
    func_801EDE70(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801EDE70(void *a0) {

    extern void (*D_801EEA00[])(void);
    D_801EEA00[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EDEAC);


/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801EDED4;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801EDED4;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801EDED4(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801EEA04[];
    extern u16 D_801EEA08[];

    MATRIX_801EDED4_801EDED4  m1;
    SVECTOR_801EDED4_801EDED4 svec_in;
    SVECTOR_801EDED4_801EDED4 svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801EEA04[t];
        *(s16 *)(param_1 + 0x2E) = D_801EEA08[*(u8 *)(param_1 + 5)];
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


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE0CC);



void func_801EE10C(void *a0) {

    extern void (*D_801EEB78[])(void);
    D_801EEB78[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE148);



void func_801EE194(void) {

    extern s32 D_801F51FC;
    D_801F51FC = 1;
}




s32 func_801EE1A8(void) {

    extern s32 D_801F51FC;
    return D_801F51FC;
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE1B8);




extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EE21C(void) {
        if ((func_80029178(0x10f) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10f, 1);
            return 1;
        }
        return 0;
    }




extern s32 func_80029504(void);
extern s32 func_80184A00(s32);
extern s32 func_80184AD0(void);
extern s32 func_80184B44(void);
extern void func_80184BA0(void);

void func_801EE258(s32 a0) {

    extern s32 D_801EEAEC[];
    extern s32 D_801EEB00[];
    extern s32 D_801EEB1C[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184A00)();
        *(s32 *)(a0 + 0xE4) = D_801EEAEC[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184AD0();
        *(s32 *)(a0 + 0xE4) = D_801EEB00[v0];
    } else {
        s32 v0 = func_80184B44();
        *(s32 *)(a0 + 0xE4) = D_801EEB1C[v0];
        func_80184BA0();
    }
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE2F8);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE42C);


extern s32 func_8012BA10(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_801789AC(s32 a0);
extern void func_80178D18(s32 a0);

void func_801EE4DC(void *param_1) {

    extern s32 D_801EEBB0[];
    extern s32 D_801EEBA4[];
    extern s32 D_801EEBBC[];

    switch (*(s16 *)((s32)param_1 + 0xFC)) {
    case 0: {
        s32 v0 = func_8012BA10((s32)param_1, 0x10);
        s32 cur;
        s32 target;
        *(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) =
            (*(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) + v0) & 0xFFF;
        cur = *(s32 *)((s32)param_1 + 0x90);
        target = D_801EEBB0[*(s16 *)((s32)param_1 + 0x70)];
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
        target = D_801EEBA4[*(s16 *)((s32)param_1 + 0x70)];
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
        target = D_801EEBA4[*(s16 *)((s32)param_1 + 0x70)];
        if (cur != target) {
            func_8012A828((s32)param_1, target);
        }
        break;
    }
    case 3: {
        s32 cur = *(s32 *)((s32)param_1 + 0x90);
        s32 target = D_801EEBBC[*(s16 *)((s32)param_1 + 0x70)];
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


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE680);



void func_801EE7D8(void *a0) {

    extern void (*D_801EED74[])(void);
    D_801EED74[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE814);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE838);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE85C);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE880);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE8A4);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE8C4);

INCLUDE_ASM("asm/md_SC05_025/nonmatchings/md_SC05_025", func_801EE8EC);



extern void func_80029124(s32 arg0, s32 arg1);
    void func_801EE928(void) {
        func_80029124(0xF5, 1);
        func_80029124(0xFB, 1);
    }

