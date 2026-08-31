#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB570;
    func_800183E0(&D_800CB570);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB51C[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB51C[*(u8 *)((s32)a0 + 0x197)]();
}


s32 func_800CAE78(u8 *a0)
{
    s32 v = a0[407] + 1;
    a0[407] = v;
    return v;
}


extern s32 func_80165910(void);
extern void func_801655E4(s32 a0);
extern s32 func_80146A6C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

s32 func_800CAE8C(s32 arg0)
{
    s32 v;
    if (func_80165910() == 0) {
        func_801655E4(arg0);
    }
    func_80146A6C(0x4B, arg0, 0, 0, 0, 0, 0);
    v = *(u8 *)((s32)arg0 + 0x197) + 1;
    *(u8 *)((s32)arg0 + 0x197) = v;
    return v;
}


extern s32 D_80078EC8;
extern void func_80165A20(void);

void func_800CAEF4(void) {
    if (D_80078EC8 == 0) {
        func_80165A20();
    }
}


void func_800CAF20(void) {
}


extern void func_80146C3C(void);

void func_800CAF28(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB53C[])(void);
    if (D_80078EC1 == 0x1) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB53C[v0]();
    } else {
        func_80146C3C();
    }
}


#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } SVecX;
typedef struct { u8 r, g, b, cd; } CVecX;
typedef struct { SVecX v[4]; CVecX c[4]; s32 code; s32 pad2; } PrimX;
typedef struct { s16 m[3][3]; s32 t[3]; } MtxX;

extern void func_80017DC4(void *a0, void *a1);
extern void func_8012F14C(void *a0, void *a1, void *a2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_80017E68(void *a0, void *a1);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048D9C(void *a0, void *a1);
extern void func_80017758(void *a0, void *a1);
extern u8 D_800CB528[];

void func_800CAF84(arg0) void *arg0; {
    SVecX sv;
    SVecX rot;
    PrimX prim;
    MtxX m1;
    MtxX m2;
    u8 *p;
    s16 i;

    sv.vx = sv.vy = sv.vz = *(u16 *)((u8 *)arg0 + 0x28);
    func_80017DC4(&sv, &m1);

    sv.vx = sv.vz = 0;
    sv.vy = -0x2C;
    func_8012F14C((u8 *)arg0 + 0x38, &sv, &sv);

    func_800D20C0(&sv, &rot, 5);
    func_800D23D0(&rot);

    prim.v[1].vx = prim.v[1].vy = prim.v[1].vz = 0;
    prim.v[0].vz = prim.v[2].vz = prim.v[3].vz = 0;
    prim.c[1].b = ((s16)*(u16 *)((u8 *)arg0 + 0x28) >> 6) + 0x70;
    prim.c[1].r = prim.c[1].g = 0;
    prim.c[0].r = prim.c[0].g = prim.c[0].b = 0;
    prim.c[2].r = prim.c[2].g = prim.c[2].b = 0;
    prim.c[3].r = prim.c[3].g = prim.c[3].b = 0;
    prim.code = 0x50000000;
    func_80017E68(&sv, &m1);

    RotMatrixYXZ(&rot, &m2);
    func_80048D9C(&m1, &m2);

    p = D_800CB528;
    for (i = 0; i < 4; i++) {
        prim.v[0].vx = (s8)*p++;
        prim.v[0].vy = (s8)*p++;
        prim.v[2].vx = (s8)*p++;
        prim.v[2].vy = (s8)*p++;
        prim.v[3].vx = (s8)*p++;
        prim.v[3].vy = (s8)*p++;
        p -= 2;
        func_80017758(&prim, &m1);
    }
}


extern void func_800CAF84();

void func_800CB158(s32 arg0) {
    typedef struct { s32 w[4]; } Struct16;
    s32 a0;
    s32 v0;

    s32 cnt;

    a0 = *(s32 *)(arg0 + 0x34);

    if ((*(s32 *)(arg0 + 0x2C) & 0x8000) == 0) {
        cnt = *(s32 *)(arg0 + 0x1C);
        *(s32 *)(arg0 + 0x1C) = cnt + 1;

        if (cnt < 8) {
            *(u16 *)(arg0 + 0x28) += 0x120;
        } else {
            *(s32 *)(arg0 + 0x1C) = 0;
            *(u16 *)(arg0 + 0x2) = 4;
        }

        v0 = *(s32 *)(a0 + 0x20);
        *(Struct16 *)(arg0 + 0x38) = *(Struct16 *)(v0 + 0x34);
        *(Struct16 *)(arg0 + 0x48) = *(Struct16 *)(v0 + 0x44);

        func_800CAF84(arg0);
    } else {
        *(u16 *)(arg0 + 0x2) += 1;
    }
}


typedef struct {
    s32 a, b, c, d;
} Blk16;

void func_800CB228(s32 arg0) {
    register s32 ent __asm__("$7");
    register s32 oth __asm__("$5");
    s32 cnt;
    s32 p;
    u16 t0;
    u16 t1;

    ent = arg0;
    cnt = *(s32 *)(ent + 0x1C);
    oth = *(s32 *)(ent + 0x34);
    *(s32 *)(ent + 0x1C) = cnt + 1;
    if (cnt < 10) {
        *(u16 *)(ent + 0x28) = *(u16 *)(ent + 0x28) + 0x120;
    } else {
        t0 = *(u16 *)(ent + 2);
        *(s16 *)(ent + 0x12) = (*(u16 *)(oth + 0x12) << 16) >> 17;
        t1 = *(u16 *)(oth + 0x1A);
        t0 += 1;
        *(s32 *)(ent + 0x30) = 0x20;
        *(s32 *)(ent + 0x1C) = -0xC0;
        *(u16 *)(ent + 0x2A) = 0x500;
        *(u16 *)(ent + 2) = t0;
        *(s16 *)(ent + 0x1A) = (t1 << 16) >> 17;
    }
    p = *(s32 *)(oth + 0x20);
    *(Blk16 *)(ent + 0x38) = *(Blk16 *)(p + 0x34);
    *(Blk16 *)(ent + 0x48) = *(Blk16 *)(p + 0x44);
    func_800CAF84(ent);
}


void func_800CB304(s32 arg0) {
    extern void func_800CAF84();
    extern s32 rand(void);
    s32 s0 = arg0;
    s32 v0;
    s32 t;
    if (*(s16 *)(s0 + 0x28) > *(s16 *)(s0 + 0x2A)) {
        v0 = *(s32 *)(s0 + 0x1C);
        if (v0 > 0) {
            v0 = (rand() & 0x180) + 0x500;
            *(s16 *)(s0 + 0x2A) = v0;
            *(s32 *)(s0 + 0x1C) = -0xA0;
        }
    } else {
        v0 = *(s32 *)(s0 + 0x1C);
        if (v0 < 0) {
            v0 = (rand() & 0x180) + 0x800;
            *(s16 *)(s0 + 0x2A) = v0;
            *(s32 *)(s0 + 0x1C) = 0xA0;
        }
    }

    *(s16 *)(s0 + 0x28) = *(u16 *)(s0 + 0x28) + *(s32 *)(s0 + 0x1C);
    *(s32 *)(s0 + 0x4C) += *(s16 *)(s0 + 0x12);
    *(s32 *)(s0 + 0x50) -= 2;
    *(s32 *)(s0 + 0x54) += *(s16 *)(s0 + 0x1A);

    func_800CAF84(s0);

    t = *(s32 *)(s0 + 0x30);
    *(s32 *)(s0 + 0x30) = t - 1;
    if (t == 0) {
        *(u16 *)(s0 + 0x2) += 1;
    }
}


void func_800CB400(void *a0)
{
    extern void func_800CAF84(void);
    s16 var;

    var = *(u16 *)((u8 *)a0 + 0x28) - 0x100;
    *(u16 *)((u8 *)a0 + 0x28) = var;
    if (var > 0) {
        *(s32 *)((u8 *)a0 + 0x50) -= 2;
        func_800CAF84();
    } else {
        func_80146C3C();
    }
}


void func_800CB458(s32 arg0) {
    extern void func_800CAF84(void);
    extern s32 func_80146A6C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    typedef struct { s32 w[4]; } Struct16;
    register s32 keep_a0 __asm__("$4");
    s32 s0 = arg0;
    s32 s1;
    s32 v0;
    s32 id;

    keep_a0 = arg0;
    s1 = *(s32 *)(s0 + 0x34);
    v0 = *(s32 *)(s1 + 0x20);

    *(Struct16 *)(s0 + 0x38) = *(Struct16 *)(v0 + 0x34);
    *(Struct16 *)(s0 + 0x48) = *(Struct16 *)(v0 + 0x44);
    __asm__ __volatile__("" :: "r"(keep_a0));

    func_800CAF84();

    if ((*(s32 *)(s0 + 0x1C) -= 1) == -1) {
        id = 0x4B;
        func_80146A6C(id, s1, 0, 0, 0, 0x8000, 0);
        *(s32 *)(s0 + 0x1C) = 0x18;
    }
}

