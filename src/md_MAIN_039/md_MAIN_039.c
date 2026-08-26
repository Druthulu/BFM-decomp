#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE14(void) {

    extern s32 D_800CBF60;
    extern s32 D_800CBF20;
    func_800183E0(&D_800CBF60);
    func_800183E0(&D_800CBF20);
}




void func_800CAE4C(void *a0) {

    extern void (*D_800CBE34[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE34[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED8(u8 *a0);
void func_800CAE90(u8 *a0) {
    if (func_80161104()) {
        func_800CAED8(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


void func_800CAED8(u8 *a0) {
    extern s32 D_8011F9D0;
    extern M2C_UNK D_800D57F4;
    extern void func_80154274(s32 *a0, s32 a1);
    extern void func_801655E4(void *a0);
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    s32 count = 0;
    s32 i;

    for (i = 0; i < 0x14; i++) {
        if (*(u16 *)((s32)&D_8011F9D0 + i * 0x68) == 0x25) {
            count++;
        }
    }

    if (count >= 6) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        func_80154274((s32 *)a0, &D_800D57F4);
        func_801655E4(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


extern s32 D_80062BE8;
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80019064(void *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208();

void func_800CAF80(void *a0) {
    u16 flag;

    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flag & 0x4000) {
            func_801466F0(0x25, (s32)a0, 0, -0x40, 0, 1, 0, 0);
            func_80019064(&D_80062BE8);
        }
        if (func_80161208(a0) == 0) {
            *(s32 *)((u8 *)a0 + 0x44) |= 2;
        }
    }
}


void func_800CB02C(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


extern u8 D_80078EC1;
extern void (*D_800CBE40[])(void);
extern void func_800CB4AC(void);

void func_800CB040(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1C) {
        index = *(u16 *)(a0 + 2);
        D_800CBE40[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB4AC)(a0);
    } else {
        ((void (*)(s32))func_800CB4AC)(a0);
    }
}


extern void func_8014659C(void);
extern void func_80146CA0(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_800CB4AC();

typedef struct { s32 w0, w1, w2, w3; } Blk16X;

void func_800CB0B4(s32 param_1) {
    extern void func_8001C214(s32 a0, s32 a1);
    extern s32 D_800CC444;

    s32 iVar2 = *(s32 *)(param_1 + 0x4c);
    s32 obj;

    obj = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = obj;
    if (obj != 0) {
        func_8001C214(obj, (s32)&D_800CC444);
        *(u16 *)(obj + 0x10) = *(u16 *)(*(s32 *)(iVar2 + 0x20) + 0x10);
        {
            register s32 prod __asm__("$2");
            prod = (*(s32 *)(param_1 + 0x50) - 1) * 0x155;
            *(u16 *)(obj + 0x12) =
                (*(u16 *)(*(s32 *)(iVar2 + 0x20) + 0x12) + prod) & 0xFFF;
        }
        *(u16 *)(obj + 0x14) = *(u16 *)(*(s32 *)(iVar2 + 0x20) + 0x14);
        *(u16 *)(param_1 + 0x58) = *(u16 *)(iVar2 + 0x100);
        *(u16 *)(param_1 + 0x5A) = *(u16 *)(iVar2 + 0x102);
        *(u16 *)(param_1 + 0x5C) = *(u16 *)(iVar2 + 0x104);
        func_80149374(iVar2, param_1 + 4);
        {
            register s32 dstp __asm__("$3");
            register s32 srcp __asm__("$2");
            dstp = *(volatile s32 *)(param_1 + 0x20);
            srcp = *(volatile s32 *)(iVar2 + 0x20);
            *(Blk16X *)(dstp + 0x34) = *(Blk16X *)(srcp + 0x34);
            *(Blk16X *)(dstp + 0x44) = *(Blk16X *)(srcp + 0x44);
        }
        func_80146DE8(param_1, 0, 0, 0xFFF00000);
        func_800CB4CC((void *)param_1);
        func_80146E90((s32 *)param_1, 0x28);
        func_80147324(0x8E8);
        func_80146CA0((void *)param_1);
    } else {
        ((void (*)(s32))func_800CB4AC)(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB228);

extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_800CB424(void *a0)
{
    s32 i;

    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
        return;
    }
    for (i = 0; i < 4; i++) {
        func_80146A6C(0x4E, a0, *(s16 *)((s32)a0 + 6), *(s16 *)((s32)a0 + 0xA),
                      *(s16 *)((s32)a0 + 0xE), i, 1);
    }
}


extern void func_80162CCC(void);
void func_800CB4AC(void) {
    func_80162CCC();
}


void func_800CB4CC(void *a0)
{
    *(s32 *)((s32)a0 + 0x54) = 0;
}


#include "common.h"

s32 func_800CB4D4(s32 a0) {
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 func_8012E778(s32 a0, s32 a1);
    extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_80013328(s32 *a0, s32 *a1);

    u8 *p;
    u8 *q;
    s32 buf[2];
    s32 best;
    u8 *bestp;
    s16 r;

    bestp = 0;
    best = 0x7FFFFFFF;
    p = D_801202A0;
    while (p < D_801202A0 + 0x6480) {
        if (*(u16 *)(p + 0) != 0x282) {
            q = p + 4;
            func_80015978((s32)q, buf);
            if (func_8012E778((s32)p, 0x8C00B4) == 1) {
                if (func_8014C308(a0, (s32)p, 0x2B, 0x40) != 0) {
                    r = func_80013328((s32 *)(a0 + 4), (s32 *)q);
                    if (r < best) {
                        best = r;
                        bestp = p;
                    }
                }
            }
        }
        p += 0x10C;
    }
    return (s32)bestp;
}


void func_800CB5CC(void *a0) {
    if (*(s32 *)((s32)a0 + 0x54) != 0) {
        if (func_8014C308((s32)a0, *(s32 *)((s32)a0 + 0x54), 0x2B, 0x40) != 0) {
            func_800CB61C(a0, *(s32 *)((s32)a0 + 0x54));
        }
    }
}


s32 func_800CB61C(s32 a0, s32 a1)
{
    typedef struct { u8 b[8]; } Blk8;
    extern u8 D_800CAE0C[8];
    extern s32 func_8014C5FC(s32, s32, void *);
    extern s32 func_8014C59C(void *, void *);
    extern s32 func_80012DBC(s32, s32, s32, s32);

    s32 s2 = *(s32 *)(a0 + 0x20);
    Blk8 buf;
    s32 r1, r2, x, y;

    buf = *(Blk8 *)D_800CAE0C;
    if (*(u16 *)a1 == 0x2CE) {
        *(s16 *)&buf.b[2] = -0x1AB;
    }
    r1 = func_8014C59C((void *)a0, (void *)a1);
    x = func_80012DBC(*(s16 *)(s2 + 0x12), (s16)r1, 0x10, 1);
    *(s16 *)(s2 + 0x12) = x;
    r2 = func_8014C5FC(a0, a1, &buf);
    y = func_80012DBC(*(s16 *)(s2 + 0x10), (s16)r2, 0x10, 1);
    *(s16 *)(s2 + 0x10) = y;
}


#define gte_SetRotMatrix(r0) __asm__ volatile (          \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldlv0(r0) __asm__ volatile (                 \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13" )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

extern u8 D_800AF648;

s32 func_800CB6F4(int param_1, int param_2)
{
    u8 *r0;
    int iVarX;
    int iVarY;
    int sp[6];
    sp[0] = (int)*(short *)(param_1 + 6);
    sp[1] = (int)*(short *)(param_1 + 10);
    sp[2] = (int)*(short *)(param_1 + 0xe);
    r0 = &D_800AF648;
    gte_SetRotMatrix(r0);
    gte_SetTransMatrix(r0);
    gte_ldlv0(sp);
    gte_rtps();
    gte_stsxy((int *)sp + 4);
    iVarX = *(short *)((int)sp + 0x10);
    if (iVarX >= 0) {
        if (iVarX < 0xAB) goto cy;
        goto ret0;
    }
    if (-iVarX >= 0xAB) goto ret0;
cy:
    iVarY = *(short *)((int)sp + 0x12);
    if (iVarY >= 0) {
        if (iVarY < 0x81) goto c1;
        goto ret0;
    }
    if (-iVarY >= 0x81) goto ret0;
c1:
    return 1;
ret0:
    return 0;
}



extern void func_80146C3C(void);

void func_800CB804(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBEAC[])(void);
    if (D_80078EC1 == 0x1c) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBEAC[v0]();
    } else {
        func_80146C3C();
    }
}


typedef struct { s16 vx, vy, vz, pad; } SV;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX;
typedef struct { s32 vx, vy, vz, pad; } V32;

extern void func_801465C0();
extern s32 func_8001CC3C(s32, s32, s32, s32);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C();
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern int rand(void);

extern SV D_800CBE50[];
extern u8 D_800CBE5C[];
extern V32 D_800CBEE8;
extern SV D_800CBEB8[];

void func_800CB860(s32 param_1) {
    SV rot;
    MTX m;
    V32 vel;
    s32 p;
    s32 pb;

    p = ((s32 (*)(void))func_801465C0)();
    pb = p;
    *(s32 *)(param_1 + 0x20) = p;

    if (p != 0) {
        ((void (*)(s32, void *, s32, s32))func_8001CC3C)(p, D_800CBE50, 0, 0);
        *(u8 *)(p + 0x27) = 0x90;
        *(s16 *)(p + 0x18) = *(s16 *)(p + 0x1a) = 0x2000;
        *(s32 *)(p + 4) |= 0x50000000;
        func_80128EA8(p, param_1 + 0x24, D_800CBE5C);

        vel = D_800CBEE8;
        rot = D_800CBEB8[*(s32 *)(param_1 + 0x2c)];

        if (*(s32 *)(param_1 + 0x30) != 0) {
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.vx = ((rand() & 0x1f) - 0x10) * 0x18000;
            vel.vy = ((rand() & 0x1f) - 0x10) * 0x18000;
            vel.vz = ((rand() & 0x1f) - 0x10) * 0x18000;
        }

        func_80049CAC((s32)&rot, (s32)&m);
        func_800484EC((s32)&m, (s32)&vel, (s32)&vel);

        *(s32 *)(param_1 + 0x10) = vel.vx;
        *(s32 *)(param_1 + 0x14) = vel.vy;
        *(s32 *)(param_1 + 0x18) = vel.vz;

        *(u8 *)(pb + 0x24) = 0xC0;
        *(u8 *)(pb + 0x25) = 0xC0;
        *(u8 *)(pb + 0x26) = 0x40;

        func_80146E90((s32 *)param_1, 4);
        *(s16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


extern void func_800CBBDC(s32 a0);
extern void func_800CBC40(void*, s32);
extern s32 func_80146E98(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);

void func_800CBAAC(s32 param_1)
{
    s32 s0;

    s0 = *(s32 *)(param_1 + 0x20);
    func_80128ED8(s0, (s32 *)(param_1 + 0x24));
    *(s8 *)(s0 + 0x27) = *(u8 *)(param_1 + 0x28) - 0x70;
    func_800CBBDC(param_1);
    ((void (*)(s32, s32))func_800CBC40)(param_1, 0x30);
    if (func_80146E98(param_1) != 0) {
        *(s32 *)(param_1 + 0x10) >>= 2;
        *(s32 *)(param_1 + 0x14) >>= 2;
        *(s32 *)(param_1 + 0x18) >>= 2;
        func_80146E90((s32 *)param_1, 8);
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80146E98(s32 a0);
extern void func_800CBBDC(s32 a0);
extern void func_800CBC10(void*);
extern void func_800CBC40(void*, s32);
extern void func_80146C3C(void);

void func_800CBB54(param_1)
s32 param_1;
{
    s32 p;
    s32 node;

    p = param_1;
    node = *(s32 *)(p + 0x20);
    ((void (*)(s32))func_800CBC10)(param_1);
    func_80128ED8(node, (s32 *)(p + 0x24));
    *(u8 *)(node + 0x27) = *(u8 *)(p + 0x28) - 0x70;
    ((void (*)(s32, s32))func_800CBC40)((void *)p, 0x40);
    *(s32 *)(p + 0x14) -= 0x4000;
    func_800CBBDC(p);
    if (func_80146E98(p) != 0) {
        ((void (*)(s32))func_80146C3C)(p);
    }
}


void func_800CBBDC(s32 a0) {
    *(s32 *)(a0 + 4) += *(s32 *)(a0 + 0x10);
    *(s32 *)(a0 + 8) += *(s32 *)(a0 + 0x14);
    *(s32 *)(a0 + 0xC) += *(s32 *)(a0 + 0x18);
}


void func_800CBC10(void *arg0) {
    u8 *a0 = (u8 *)arg0;
    a0 = *(u8 **)(a0 + 0x20);
    a0[0x24] -= 4;
    a0[0x25] -= 4;
    a0[0x26] -= 4;
}


void func_800CBC40(void *arg0, s32 arg1) {
    void *v1 = *(void **)((s32)arg0 + 0x20);
    u16 v0 = *(u16 *)((s32)v1 + 0x1A) - arg1;
    *(u16 *)((s32)v1 + 0x1A) = v0;
    *(u16 *)((s32)v1 + 0x18) = v0;
}



extern void func_80146C3C(void);

void func_800CBC60(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBEF8[])(void);
    if (D_80078EC1 == 0x1c) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBEF8[v0]();
    } else {
        func_80146C3C();
    }
}


extern void func_801465C0(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(void);

void func_800CBCBC(void *a0)
{
    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    void *s1;
    void *s0;
    s32 pad[14];

    s1 = *(void **)((u8 *)a0 + 0x34);
    s0 = ((void *(*)(void))func_801465C0)();
    *(void **)((u8 *)a0 + 0x20) = s0;

    if (s0 != NULL) {
        func_8001CC3C((s32)s0, (s32)&D_800D387C, 0, 0);

        *(u8 *)((u8 *)s0 + 0x27) = 0x9C;
        *(u16 *)((u8 *)s0 + 0x1A) = 0x2000;
        *(u16 *)((u8 *)s0 + 0x18) = 0x2000;
        *(u8 *)((u8 *)s0 + 0x24) = 0xFF;
        *(u8 *)((u8 *)s0 + 0x25) = 0;
        *(u8 *)((u8 *)s0 + 0x26) = 0;
        *(s32 *)((u8 *)s0 + 4) |= 0x50000000;

        func_80149374((s32)s1, (s32)((u8 *)a0 + 4));
        func_80128EA8((s32)s0, (s32)((u8 *)a0 + 0x24), (s32)&D_800D3888);

        *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


extern void func_80146C3C(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);

void func_800CBD90(void *arg0) {
    s32 q;
    u8 a;
    u8 b;
    u16 h;

    q = *(s32 *)((s32)arg0 + 0x20);

    a = *(u8 *)(q + 0x24) - 0x20;
    *(u8 *)(q + 0x24) = a;
    if (a < 0x80) {
        *(u8 *)(q + 0x24) = 0x80;
    }

    b = *(u8 *)(q + 0x25) + 0x20;
    *(u8 *)(q + 0x25) = b;
    if (b > 0x80) {
        *(u8 *)(q + 0x25) = 0x80;
    }

    h = *(u16 *)(q + 0x1A) + 0x400;
    *(u8 *)(q + 0x26) = *(u8 *)(q + 0x25);
    *(u16 *)(q + 0x1A) = h;
    *(u16 *)(q + 0x18) = h;

    if (func_80128ED8(q, (s32 *)((s32)arg0 + 0x24)) != 0) {
        ((void (*)(void *))func_80146C3C)(arg0);
    }
}

