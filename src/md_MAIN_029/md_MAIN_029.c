#include "common.h"

extern void func_800183E0(s32 a0);

extern s32 D_800CB528;
extern s32 D_800CB568;
extern s32 D_800CB5A8;
extern s32 D_800CB4E8;

void func_800CAE0C(void) {
    func_800183E0((s32) &D_800CB528);
    func_800183E0((s32) &D_800CB568);
    func_800183E0((s32) &D_800CB5A8);
    func_800183E0((s32) &D_800CB4E8);
}




void func_800CAE64(void *a0) {

    extern void (*D_800CB49C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB49C[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEE0();
void func_800CAEA8(void *a0) {
    func_800CAEE0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


extern s32 func_80165910(void);
extern void func_801655E4(s32 a0);
extern void func_800CAF64(s32 a0);

void func_800CAEE0(void *a0) {
    if (func_80165910() == 0) {
        func_801655E4((s32) a0);
    }
    func_800CAF64((s32) a0);
    *(u8 *)((s32) a0 + 0x197) += 1;
}


extern s32 D_80078EC8;
extern s32 func_80165A20(s32 a0);

void func_800CAF30(s32 a0) {
    if (D_80078EC8 == 0) {
        func_80165A20(a0);
    }
}


void func_800CAF5C(void) {
}

extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);

void func_800CAF64(s32 a0) {
    func_80146994(0x38, a0, 0x8000, 0);
}


void func_800CAF90(s32 a0) {
    extern u8 D_800CB4A8[];
    extern u8 D_800CB4AA[];
    extern u8 D_800D387C[];
    extern u16 D_80126BC8;
    extern u16 D_80126BCA;
    extern u16 D_80126BCC;
    extern s32 func_801465C0();
    extern void func_800CB2AC(s32 a0);
    extern void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_80147324(s32 a0);
    s32 pad[2];
    s32 t;
    s32 angle;
    s32 prim;

    if (*(s32 *)(a0 + 0x2C) & 0x8000) {
        *(s16 *)(a0 + 0x12) = 0x14;
        *(s16 *)(a0 + 2) = 1;
        return;
    }
    t = *(u32 *)(a0 + 0x30) >> 15;
    prim = func_801465C0();
    if (prim == 0) {
        return;
    }
    angle = t << 16;
    func_8001CC3C(prim, D_800D387C, *(s16 *)(D_800CB4A8 + (angle >> 15)), *(s16 *)(D_800CB4AA + (angle >> 15)));
    *(u8 *)(prim + 0x27) = (angle >> 17) + 0x19;
    *(s32 *)(prim + 4) |= 0x50000000;
    *(u32 *)(a0 + 0x30) = *(u16 *)(a0 + 0x30);
    *(s32 *)(a0 + 0x20) = prim;
    *(s16 *)(a0 + 2) = 2;
    func_800CB2AC(a0);
    func_80146A6C(3, (void *)a0, *(s16 *)(a0 + 6), *(s16 *)(a0 + 0xA), *(s16 *)(a0 + 0xE), 0xCCCFFFC, 0xE0009C00);
    D_80126BCC = D_80126BCC - 0x300;
    D_80126BC8 = D_80126BCC;
    D_80126BCA = D_80126BCA + 0xC0;
    func_80147324(0x8E9);
}


typedef struct {
    s8 pad00[0x12];
    s16 f12;
    s8 pad14[6];
    s16 f1A;
    s32 f1C;
    s8 pad20[8];
    u16 f28;
    u16 f2A;
    s8 pad2C[4];
    u32 f30;
} St;

extern u8 D_80078EC1;
extern s16 D_80126BCC;
extern u16 D_80126BCA;
extern s16 D_80126BC8;
extern u16 D_800B99DA;

s32 func_80146AB4(s32, void *, s32, s32, s32, s32, s32);
void func_80146C3C(void *);
void func_8002D4C8(s32, s32);

void func_800CB0D0(St *arg0) {
    s16 *p;
    s32 r;
    if (D_80078EC1 == 0x14) {
        switch (arg0->f30) {
        case 0:
            r = rand();
            arg0->f1A = r & 0xFFF;
            arg0->f2A = (r & 1) + 2;
            arg0->f30 = arg0->f30 + 1;
            break;
        case 1:
            if ((arg0->f1C++ & 1) == 0) {
                if (func_80146AB4(0x38, arg0, 0, 0, 0, arg0->f12,
                                  arg0->f1A | ((s16)arg0->f28 << 16)) == 0) {
                    arg0->f2A = 0;
                }
                arg0->f28++;
                if ((s16)arg0->f28 >= 3) {
                    arg0->f28 = 0;
                }
                arg0->f2A--;
                if ((s16)arg0->f2A <= 0) {
                    arg0->f1C = 0xE;
                    arg0->f30 = arg0->f30 + 1;
                }
            }
            break;
        case 2:
            if (--arg0->f1C == 0) {
                arg0->f30 = 0;
            }
            break;
        }
        p = &D_80126BCC;
        if (*p < 0x1000) {
            D_80126BCA -= 0x38;
            *p += 0xE0;
            D_80126BC8 = *p;
        }
        if ((D_800B99DA & 0xF) == 0) {
            func_8002D4C8(0x5FB, 0);
        }
    } else {
        D_80126BCC = 0x1000;
        D_80126BCA = 0x1000;
        D_80126BC8 = 0x1000;
        func_80146C3C(arg0);
    }
}


typedef struct { s32 w[8]; } Blk20;

void func_800CB2AC(void *a0)
{
    extern u8 D_80078EC1;
    extern u16 D_800CB4B4[];
    extern Blk20 D_800AE620;
    extern s16 D_80126B5E;
    extern s16 D_80126B62;
    extern s16 D_80126B66;
    extern void RotMatrixY(s32, void *);
    extern void func_8012F14C(s32, s32, s32);
    extern void func_80146C3C();

    u8 *s1;
    u8 *p;
    struct { s16 x, y, z; } vec;
    Blk20 m;
    u32 t;

    s1 = (u8 *)a0;
    p = *(u8 **)(s1 + 0x20);
    if (D_80078EC1 == 0x14) {
        *(u32 *)(s1 + 0x2C) += 4;
        if (*(u32 *)(s1 + 0x2C) < 0x1C1) {
            t = (*(u32 *)(s1 + 0x1C))++;
            *(u16 *)(p + 0x18) = *(u16 *)(p + 0x1A) = D_800CB4B4[t & 3];
            *(u32 *)(s1 + 0x30) += 0xA00000 / (*(u32 *)(s1 + 0x2C) * 804);
            m = D_800AE620;
            RotMatrixY(*(u32 *)(s1 + 0x30), &m);
            vec.x = 0;
            vec.y = -*(u32 *)(s1 + 0x2C);
            t = *(u32 *)(s1 + 0x2C);
            m.w[5] = D_80126B5E;
            m.w[6] = D_80126B62 - 0x1C;
            m.w[7] = D_80126B66;
            vec.z = t - (t >> 2);
            func_8012F14C((s32)&m, (s32)&vec, (s32)&vec);
            *(u16 *)(s1 + 6) = vec.x;
            *(u16 *)(s1 + 0xA) = vec.y;
            *(u16 *)(s1 + 0xE) = vec.z;
            return;
        }
    }
    func_80146C3C(s1);
}




void func_800CB460(void *a0) {

    extern void (*D_800CB4BC[])(void);
    D_800CB4BC[*(u16 *)((s32)a0 + 0x2)]();
}

