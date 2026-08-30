#include "common.h"

extern u8 D_801E8B2C[];
extern void func_80175414(s32 _arg0);
void func_800167B8(int);

int func_801E7B3C(u8 *arg) {
    extern u8 *D_80126B10;
    D_80126B10 = D_801E8B2C;
    func_800167B8(0);
    ((void (*)(void))func_80175414)();
    arg[0x15]++;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_801E7B94(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E68(void *arg0);

s32 func_801E7BB8(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E68, 0x1000000);
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

s32 func_801E7C04(s32 param_1) {
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
void func_801E7CA4(void) {
    func_800D1EBC();
}




void func_801E7CC4(void *a0) {

    extern void (*D_801E8AD0[])(void);
    D_801E8AD0[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D00(void *a0) {

    extern void (*D_801E8AD8[])(void);
    D_801E8AD8[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D3C(void *a0) {

    extern void (*D_801E8B5C[])(void);
    D_801E8B5C[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801E7D78(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC04_026/nonmatchings/md_SC04_026", D_801E7B28);

typedef struct { u8 c[8]; } Blk8;
const Blk8 D_801E7B2C = {{0x00, 0x00, 0x7E, 0xFF, 0xB0, 0x00, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E7DA0(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E7B2C;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}



extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E7E08(void *arg0) {

    extern u8 D_801E8B2C[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E8B2C));
        func_80171A1C(arg0);
    }
}


void func_801E7E60(void) {
}



void func_801E7E68(void *a0) {

    extern void (*D_801E8B6C[])(void);
    D_801E8B6C[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801E7EA4(void) {
    ((void (*)(void))func_80171A1C)();
}



const Blk8 D_801E7B34 = {{0xD5, 0xFF, 0x7E, 0xFF, 0xF5, 0xFE, 0x00, 0x00}};
extern s32 func_80171D78(u32, void *);
extern void func_80171A1C(void*);

void func_801E7EC4(u32 arg0) {
    Blk8 buffer;

    buffer = D_801E7B34;

    if (func_80171D78(arg0, &buffer)) {
        ((void (*)(u32))func_80171A1C)(arg0);
    }
}


void func_801E7F2C(void) {
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_801E7FF8(void *a0);

void func_801E7F34(void) {

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
    func_8012A018((s32)func_801E7FF8, 0);
    func_801E7FF8(D_80126948);
    func_8012A094((s32)D_80126948);
    D_801274EA = -0x82;
    D_801274E8 = 0;
    D_801274EC = -0x1B0;
}




void func_801E7FF8(void *a0) {

    extern void (*D_801E8B78[])(void);
    D_801E8B78[*(u8 *)((s32)a0 + 0x4)]();
}


void func_801E8034(void *a0) {
    extern s16 D_801274E8;
    extern void func_801E805C(s32 a0, s16 *a1);
    func_801E805C((s32)a0, &D_801274E8);
}



/* MATRIX 0x20: short m[3][3] @0x00 (18B) + 2B pad, long t[3] @0x14  (PsyQ layout) */
typedef struct { short m[3][3]; long t[3]; } MATRIX_801EDED4_801E805C;
typedef struct { short vx, vy, vz, pad; } SVECTOR_801EDED4_801E805C;

extern u16  func_80148800(s32 *a0);
extern s32  func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32  func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_801E805C(s32 param_1, s16 *param_2) {

    extern s32 D_80126B58;
    extern s16 D_801E8B7C[];
    extern u16 D_801E8B80[];

    MATRIX_801EDED4_801E805C  m1;
    SVECTOR_801EDED4_801E805C svec_in;
    SVECTOR_801EDED4_801E805C svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E8B7C[t];
        *(s16 *)(param_1 + 0x2E) = D_801E8B80[*(u8 *)(param_1 + 5)];
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



u8 func_801E8254(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xE;
}




void func_801E8284(void *a0) {

    extern void (*D_801E8CF0[])(void);
    D_801E8CF0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801E82C0(void) {
    extern u8 D_80078EBA;
    extern s32 D_801E7AAC;
    extern u8 *D_801E8EF4[];
    extern u8 *D_801E8F34[];
    extern s32 D_801EF374;

    D_801EF374 = 0;
    if (D_80078EBA == 4) {
        *(s32 *)(D_801E7AAC + 4) = (s32)D_801E8F34;
    } else {
        *(s32 *)(D_801E7AAC + 4) = (s32)D_801E8EF4;
    }
}




void func_801E830C(void) {

    extern s32 D_801EF374;
    D_801EF374 = 1;
}




s32 func_801E8320(void) {

    extern s32 D_801EF374;
    return D_801EF374;
}


s32 func_801E8330(void) {
    extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    extern s32 func_80029504(void);

    if ((func_80029178(0xF5) & 0xFF) != 0) {
        return 0;
    }
    if ((u32)(func_80029504() - 0xC8) < 0x190) {
        func_80029124(0xF5, 1);
        func_80029124(0x10F, 1);
        return 1;
    }
    return 0;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E8394(void) {
        if ((func_80029178(0x10f) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10f, 1);
            return 1;
        }
        return 0;
    }




extern s32 func_80029504(void);
extern s32 func_80184D00(s32);
extern s32 func_80184DD0(void);
extern s32 func_80184E44(void);
extern void func_80184EA0(void);

void func_801E83D0(s32 a0) {

    extern s32 D_801E8C64[];
    extern s32 D_801E8C78[];
    extern s32 D_801E8C94[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184D00)();
        *(s32 *)(a0 + 0xE4) = D_801E8C64[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184DD0();
        *(s32 *)(a0 + 0xE4) = D_801E8C78[v0];
    } else {
        s32 v0 = func_80184E44();
        *(s32 *)(a0 + 0xE4) = D_801E8C94[v0];
        func_80184EA0();
    }
}



extern s32 func_801789AC(s32 a0);
extern void func_80186460(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_80174438(s32 a0);

void func_801E8470(void *param_1) {

    extern u8 *D_80126B10;

    extern s32 D_801E8CA8;
    extern s32 D_801E8CC0;
    extern s32 D_801E8C44;

    switch (*(u16 *)((s32)param_1 + 0x34)) {
    case 0: {
        s32 v0 = func_801789AC((s32)param_1);
        switch (v0) {
        case 1:
            *(u16 *)((s32)param_1 + 0x34) = 2;
            func_80186460(0);
            break;
        case 2:
            func_80178CBC((s32)param_1, (s32)&D_801E8CA8);
            *(u16 *)((s32)param_1 + 0x34) = 0;
            break;
        case 3:
            func_80178CBC((s32)param_1, (s32)&D_801E8CC0);
            *(u16 *)((s32)param_1 + 0x34) = 3;
            break;
        }
        break;
    }
    case 1:
        break;
    case 2:
        func_80178CBC((s32)param_1, (s32)&D_801E8C44);
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

void func_801E85A4(void *a0) {
    extern s32 D_801EEDCC;
    extern s32 D_801E8B84;
    extern s16 D_801B9B50;
    extern s32 D_801E8BDC;
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
        func_8001C214(v0, (s32)&D_801EEDCC);
        *(s16 *)(*(s32 *)((s32)a0 + 0x68) + 0xC) = 0x7FFF;
        func_8012E8E0((s32)a0, (s32)&D_801E8B84);
        *(s16 *)((s32)a0 + 0x2) = 1;
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_8012A828((s32)a0, (s32)&D_801B9B50);
        func_80178B18((s32)a0, (s32)&D_801E8BDC);
    }
}



extern s32 func_8012BA10(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_801789AC(s32 a0);
extern void func_80178D18(s32 a0);

void func_801E8654(void *param_1) {

    extern s32 D_801E8D28[];
    extern s32 D_801E8D1C[];
    extern s32 D_801E8D34[];

    switch (*(s16 *)((s32)param_1 + 0xFC)) {
    case 0: {
        s32 v0 = func_8012BA10((s32)param_1, 0x10);
        s32 cur;
        s32 target;
        *(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) =
            (*(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) + v0) & 0xFFF;
        cur = *(s32 *)((s32)param_1 + 0x90);
        target = D_801E8D28[*(s16 *)((s32)param_1 + 0x70)];
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
        target = D_801E8D1C[*(s16 *)((s32)param_1 + 0x70)];
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
        target = D_801E8D1C[*(s16 *)((s32)param_1 + 0x70)];
        if (cur != target) {
            func_8012A828((s32)param_1, target);
        }
        break;
    }
    case 3: {
        s32 cur = *(s32 *)((s32)param_1 + 0x90);
        s32 target = D_801E8D34[*(s16 *)((s32)param_1 + 0x70)];
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



extern s32 func_80029504(void);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(u8 *a0);
extern s32 func_80178B18(s32 a0, s32 a1);


void func_801E87F8(void *a0) {

    extern s32 D_801EF37C;
    extern s32 D_801EF378;
    extern s32 D_801E8D10[];
    extern s32 D_801E8CF8[][2];
    extern s32 D_801E8D28[];
    extern s32 D_801E8DDC;
    s32 v0;
    s32 cur;
    s32 target;

    if ((u32)(func_80029504() - 0x122) >= 0xA) {
        func_8012CAE4(a0);
        return;
    }

    if (*(s16 *)((s32)a0 + 0x70) == 0) {
        D_801EF37C = func_8012C658(0x1C1, 1, 0);
        D_801EF378 = func_8012C658(0x1C1, 2, 0);
    }

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, D_801E8D10[*(s16 *)((s32)a0 + 0x70)]);
    *(s16 *)(*(s32 *)((s32)a0 + 0x68) + 0xC) = 0x7FFF;
    func_8012E8E0((s32)a0, (s32)&D_801E8CF8[*(s16 *)((s32)a0 + 0x70)]);
    *(s16 *)((s32)a0 + 0x2) = 1;
    func_8012E8E0((s32)a0, (s32)&D_801E8CF8[*(s16 *)((s32)a0 + 0x70)]);
    func_8012E88C((u8 *)a0);

    cur = *(s32 *)((s32)a0 + 0x90);
    target = D_801E8D28[*(s16 *)((s32)a0 + 0x70)];
    if (cur != target) {
        func_8012A828((s32)a0, target);
    }

    if (*(s16 *)((s32)a0 + 0x70) != 0) {
        func_80178B18((s32)a0, (s32)&D_801E8DDC);
    }
}




void func_801E8950(void *a0) {

    extern void (*D_801E8EEC[])(void);
    D_801E8EEC[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801E898C(void *param_1) {

    extern s32 D_801EF378;
    extern s32 D_801EF37C;
    s32 ptr1;
    s32 ptr2;

    ptr1 = D_801EF378;
    ptr2 = D_801EF37C;
    *(s16 *)((s32)param_1 + 0xFC) = 1;
    *(s16 *)(ptr1 + 0xFC) = 0;
    *(s16 *)(ptr2 + 0xFC) = 0;
}


void func_801E89B0(void *arg0) {

    extern s32 D_801EF378;
    extern s32 D_801EF37C;
    register s32 var __asm__("$2");
    register s32 var2 __asm__("$4");

    var = D_801EF378;
    *(s16 *)((s32)arg0 + 0xFC) = 0;
    var2 = D_801EF37C;
    *(s16 *)(var + 0xFC) = 1;
    *(s16 *)(var2 + 0xFC) = 0;
}


void func_801E89D4(void *arg0) {

    extern s32 D_801EF378;
    extern s32 D_801EF37C;
    register s32 var __asm__("$2");
    register s32 var2 __asm__("$4");

    var = D_801EF378;
    *(s16 *)((s32)arg0 + 0xFC) = 0;
    var2 = D_801EF37C;
    *(s16 *)(var + 0xFC) = 2;
    *(s16 *)(var2 + 0xFC) = 0;
}


void func_801E89F8(void *a0) {
    extern s32 D_801EF378;
    extern s32 D_801EF37C;
    s32 v0;
    s32 v1;

    v0 = D_801EF378;
    v1 = D_801EF37C;
    *(s16 *)((s32)a0 + 0xFC) = 0;
    *(s16 *)(v0 + 0xFC) = 0;
    *(s16 *)(v1 + 0xFC) = 1;
}


void func_801E8A1C(void *a0) {

    extern s32 D_801EF37C;
    extern s32 D_801EF378;
    s32 v0;
    s32 v1;

    v0 = D_801EF378;
    v1 = D_801EF37C;
    *(s16 *)((s32)a0 + 0xFC) = 0;
    *(s16 *)(v0 + 0xFC) = 0;
    *(s16 *)(v1 + 0xFC) = 0;
}


void func_801E8A3C(void *a0) {
    extern s32 D_801EF37C;
    extern s32 D_801EF378;
    register s32 p __asm__("$3");
    register s32 q __asm__("$4");

    p = D_801EF378;
    *(s16 *)((s32)a0 + 0xFC) = 1;
    q = D_801EF37C;
    *(s16 *)(p + 0xFC) = 3;
    *(s16 *)(q + 0xFC) = 3;
}


void func_801E8A64(void) {
    extern u8 *D_80126B10;
    extern void func_80029514(s32 a0);
    extern void func_80174438(s32 a0);
    extern void func_80029124(s32 a0, s32 a1);

    func_80029514(0x12C);
    func_80174438((s32)D_80126B10);
    func_80029124(0x10F, 1);
}




extern void func_80029124(s32 arg0, s32 arg1);
    void func_801E8AA0(void) {
        func_80029124(0xF5, 1);
        func_80029124(0xFB, 1);
    }

