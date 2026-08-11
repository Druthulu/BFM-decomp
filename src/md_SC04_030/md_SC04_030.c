#include "common.h"

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7B3C);


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

    extern void (*D_801E85D4[])(void);
    D_801E85D4[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D00(void *a0) {

    extern void (*D_801E85DC[])(void);
    D_801E85DC[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D3C(void *a0) {

    extern void (*D_801E8660[])(void);
    D_801E8660[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801E7D78(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC04_030/nonmatchings/md_SC04_030", D_801E7B28);

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7DA0);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E7E08(void *arg0) {

    extern u8 D_801E8630[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E8630));
        func_80171A1C(arg0);
    }
}


void func_801E7E60(void) {
}



void func_801E7E68(void *a0) {

    extern void (*D_801E8670[])(void);
    D_801E8670[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801E7EA4(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E7EC4);

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

    extern void (*D_801E867C[])(void);
    D_801E867C[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E8034);


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
    extern s16 D_801E8680[];
    extern u16 D_801E8684[];

    MATRIX_801EDED4_801E805C  m1;
    SVECTOR_801EDED4_801E805C svec_in;
    SVECTOR_801EDED4_801E805C svec_out;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(param_1 + 5) + 1) & 1;
        *(u8 *)(param_1 + 5) = t;
        *(s32 *)(param_1 + 0xC)  = D_801E8680[t];
        *(s16 *)(param_1 + 0x2E) = D_801E8684[*(u8 *)(param_1 + 5)];
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
    return 0x29;
}


void func_801E8284(void) {
}

void func_801E828C(void) {
}

INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E8294);



void func_801E83F0(void *a0) {

    extern void (*D_801E87C4[])(void);
    D_801E87C4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_030/nonmatchings/md_SC04_030", func_801E842C);



void func_801E843C(void) {

    extern s32 D_801F14E0;
    D_801F14E0 = 1;
}




s32 func_801E8450(void) {

    extern s32 D_801F14E0;
    return D_801F14E0;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E8460(void) {
        if ((func_80029178(0x112) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x112, 1);
            return 1;
        }
        return 0;
    }




extern s32 func_80029504(void);
extern s32 func_80184D00(s32);
extern s32 func_80184DD0(void);
extern s32 func_80184E44(void);
extern void func_80184EA0(void);

void func_801E849C(s32 a0) {

    extern s32 D_801E8738[];
    extern s32 D_801E874C[];
    extern s32 D_801E8768[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = ((s32 (*)(void))func_80184D00)();
        *(s32 *)(a0 + 0xE4) = D_801E8738[v0];
    } else if (v1 < 0x384) {
        s32 v0 = func_80184DD0();
        *(s32 *)(a0 + 0xE4) = D_801E874C[v0];
    } else {
        s32 v0 = func_80184E44();
        *(s32 *)(a0 + 0xE4) = D_801E8768[v0];
        func_80184EA0();
    }
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80178B18(s32 a0, s32 a1);

void func_801E853C(void *a0) {
    extern s32 D_801F06DC;
    extern s32 D_801F1488;
    extern s32 D_801E8688;
    extern s32 D_801E86B8;
    s32 v0;
    s32 ptr;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801F06DC);
        ptr = *(s32 *)((s32)a0 + 0x68);
        *(s16 *)(ptr + 0xC) = 0x7FFF;
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012A828((s32)a0, (s32)&D_801F1488);
        func_8012E8E0((s32)a0, (s32)&D_801E8688);
        *(s16 *)((s32)a0 + 0x34) = 0;
        func_80178B18((s32)a0, (s32)&D_801E86B8);
    }
}

