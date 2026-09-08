#include "common.h"
#include "../shared/engine_prelude.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB85C;
    func_800183E0(&D_800CB85C);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB7D4[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB7D4[*(u8 *)((s32)a0 + 0x197)]();
}


#include "../shared/slot_800CAE08/func_800CAE78__a79b87ee.h"


extern void func_80154274(s32 *a0, s32 a1);
extern void func_801655E4(s32 a0);

void func_800CAEC0(u8 *a0) {
    extern M2C_UNK D_800D57F4;

    func_80154274((s32 *)a0, &D_800D57F4);
    func_801655E4((s32)a0);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


#include "common.h"

extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern s32 func_80161208();

void func_800CAF08(void *a0) {
    u16 flags;

    flags = *(u16 *)((s32)a0 + 0xB8);
    if (flags == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flags & 0x4000) {
            func_801466F0(0x26, (s32)a0, 0, -0x40, 0, 0, 0, 0);
        }
        func_80161208(a0);
    }
}


void func_800CAF88(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


extern u8 D_80078EC1;
extern void (*D_800CB7EC[])(void);
extern void func_80162D28(s32 *a0);
extern void func_800CB338(void);

void func_800CAF9C(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1E) {
        index = *(u16 *)(a0 + 2);
        D_800CB7EC[index]();

        if (*(s32 *)(a0 + 0x20) != 0) {
            func_80162D28((s32 *)a0);
        }

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB338)(a0);
    } else {
        ((void (*)(s32))func_800CB338)(a0);
    }
}


#include "common.h"

extern void func_8014659C(void);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 D_800CBE04;
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CB338(void);

void func_800CB028(s32 a0) {
    s32 s2;
    s32 s0;

    s2 = *(s32 *)(a0 + 0x4C);
    s0 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(a0 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C214(s0, (s32)&D_800CBE04);
        *(u16 *)(s0 + 0x2C) = *(u16 *)(s0 + 0x2C) | 0x10;
        *(u16 *)(s0 + 0x1C) = 0x2000;
        *(u16 *)(s0 + 0x1A) = 0x2000;
        *(u16 *)(s0 + 0x18) = 0x2000;
        *(u16 *)(s0 + 0x12) = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x12);
        func_80149374(s2, a0 + 4);
        func_80146DE8((s32 *)a0, 0, 0, 0xFFE80000);
        func_80146E90((s32 *)a0, 0x3C);
        func_80146A6C(0x4F, (void *)a0, 0, 0, 0, 0, 0);
        func_80147324(0x8E5);
        func_80146CA0((void *)a0);
    } else {
        ((void (*)(s32))func_800CB338)(a0);
    }
}


extern void func_80162FF4();
extern void func_80162FC0(s32 *a0);
extern s32 func_80146E98(s32 a0);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328();
extern s32 func_801632F0();
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 a0);
extern u8 D_80114EB0[];
extern u8 D_80114EC8[];
extern s16 D_80126B18;
extern s16 D_80126B1A;
extern s16 D_80126B1C;

void func_800CB118(s32 a0) {
    s32 sp20[2];
    s32 sp28;
    register s32 ret __asm__("$3");
    register s32 m __asm__("$2");

    func_80162FF4(a0, 0, 0x4000, 0);
    func_80162FC0((s32 *) a0);
    if (func_80146E98(a0) != 0) {
        func_80146CA0((void *) a0);
        return;
    }
    ret = func_801638A0((u8 *) a0, (s32) sp20);
    if (ret == 0) {
    } else if ((m = ret & 0x8000) != 0) {
        *(s32 *)(a0 + 0x2C) = 0;
        *(s32 *)(a0 + 0x24) = 0;
    } else {
        func_80146E90((s32 *) a0, 0x20);
        func_80146CA0((void *) a0);
        return;
    }
    func_80163408(a0, 0x2C, 0x80, 0x200);
    func_80163328(a0);
    switch ((u32) func_801632F0(a0)) {
    case 1:
        func_80013E94(D_80114EB0, &sp28);
        sp28 |= 0x80000000;
        func_80146A6C(0x1F, (void *) a0, D_80126B18, D_80126B1A, D_80126B1C, sp28, 0);
        func_80147324(0x8E6);
        break;
    case 2:
    case 4:
        func_80013E94(D_80114EC8, &sp28);
        sp28 |= 0x80000000;
        func_80146A6C(7, (void *) a0, D_80126B18, D_80126B1A, D_80126B1C, sp28, 0);
        break;
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB2B4(s32 *a0) {
    s32 *s1;

    s1 = (s32 *)a0[0x20 / 4];
    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
    } else if (a0[0x1C / 4] & 1) {
        s1[1] |= 0x80000000;
    } else {
        s1[1] &= 0x7FFFFFFF;
    }
}


extern void func_80162CCC(void);
void func_800CB338(void) {
    func_80162CCC();
}


#include "common.h"

void func_800CB358(void *param_1) {
    extern void (*D_800CB834[])(void);
    extern void func_80146C3C();

    if (*(u16 *)(*(s32 *)((s32)param_1 + 0x34)) == 0x26) {
        D_800CB834[*(u16 *)((s32)param_1 + 2)]();
    } else {
        func_80146C3C(param_1);
    }
}


extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);

typedef struct { s16 x, y, z, pad; } SVec_800CB3BC;   /* 8 bytes */
typedef struct {
    /* 0x00 */ u16 cx, cy, cz;
    /* 0x06 */ u16 _p06;
    /* 0x08 */ u16 a8[4];
    /* 0x10 */ s32 pos[3];
    /* 0x1C */ s32 _p1C;
    /* 0x20 */ SVec_800CB3BC v[4];
    /* 0x40 */ struct { u8 r, g, b, cd; } col[4];
    /* 0x50 */ u32 code;
    /* 0x54 */ s32 _p54;
    /* 0x58 */ u8 m1[0x20];
    /* 0x78 */ u8 m2[0x20];
} Fr_800CB3BC;   /* 0x98 bytes -> sp+0x10 .. sp+0xA8 */

void func_800CB3BC(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {

    extern u8  D_800CB820[];
    extern u16 D_800CB7FC[];
    Fr_800CB3BC f;
    register u8  *p   __asm__("$18");   /* $s2 */
    register s32  ent __asm__("$20");   /* $s4 */
    s16 i;
    s32 node;
    u16 c;
    u8  cv;
    u8  *va;
    u8  *vb;
    u16 *q;

    ent = arg0;
    node = *(s32 *)(ent + 0x34);
    f.v[1].z = 0;
    f.v[1].y = 0;
    f.v[1].x = 0;
    f.v[3].z = 0;
    f.v[2].z = 0;
    f.v[0].z = 0;
    f.col[1].b = 0x70;
    cv = *(u8 *)(ent + 0x12);
    f.cx = arg1;
    __asm__ __volatile__("");
    va = (u8 *)&f.cx;
    __asm__ __volatile__("" : "=r"(va) : "0"(va));
    f.cy = arg2;
    vb = va;
    __asm__ __volatile__("" : "=r"(vb) : "0"(vb));
    p = D_800CB820;
    i = 0;
    f.col[0].b = 0;
    f.col[0].g = 0;
    f.col[0].r = 0;
    f.col[2].b = 0;
    f.col[2].g = 0;
    f.col[2].r = 0;
    f.col[3].b = 0;
    f.col[3].g = 0;
    f.col[3].r = 0;
    f.code = 0x50000000;
    f.cz = arg3;
    f.col[1].r = cv;
    f.col[1].g = cv;
    ((void (*)(s32, void *, void *))func_80149350)(node, va, vb);

    c = f.cx;
    *(s16 *)(ent + 0x06) = c;
    *(s32 *)(ent + 0x4C) = (s16)c;
    c = f.cy;
    *(s16 *)(ent + 0x0A) = c;
    *(s32 *)(ent + 0x50) = (s16)c;
    c = f.cz;
    *(s16 *)(ent + 0x0E) = c;
    *(s32 *)(ent + 0x54) = (s16)c;
    func_800D20C0(&f.cx, f.a8, 8);
    func_80017E68(&f.cx, f.m1);
    func_800D23D0(f.a8);
    RotMatrixYXZ(f.a8, f.m1);

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].y = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].y = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].y = (s8)*p--;
        func_80017758(f.v, f.m1);
    } while ((i = i + 1) < 4);

    q = D_800CB7FC;
    i = 0;
    f.v[1].z = 0x50;
    f.col[1].b = 0xA0;
    f.v[3].y = 0;
    f.v[2].y = 0;
    f.v[0].y = 0;
    f.col[1].g = 0x10;
    f.col[1].r = 0x10;

    do {
        f.v[0].x = *q++;
        f.v[0].z = *q++;
        f.v[2].x = *q++;
        f.v[2].z = *q++;
        f.v[3].x = *q++;
        f.v[3].z = *q--;
        func_80017758(f.v, (void *)(ent + 0x38));
    } while ((i = i + 1) < 4);
}


void func_800CB634(s32 a0) {
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(u16 *)(a0 + 0x12) = 0;
    *(u16 *)(a0 + 0x10) = 0x80;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


#include "common.h"

typedef struct { s32 m[8]; } Mat_800CB658;
struct Src_800CB658 {
    u8 pad0[0x34];
    Mat_800CB658 mat;
};
struct Node_800CB658 {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x2];
    s16 unkA;
    u8 padC[0x2];
    s16 unkE;
    u8 pad10[0x10];
    struct Src_800CB658 *unk20;
};
struct Entity_800CB658 {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x2];
    s16 unkA;
    u8 padC[0x2];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    u8 pad14[0x8];
    s32 unk1C;
    u8 pad20[0x14];
    struct Node_800CB658 *unk34;
    Mat_800CB658 mat;
};

extern s32 rand(void);
extern void func_800CB3BC();
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

s32 func_800CB658(s32 arg0) {
    struct Node_800CB658 *node;
    struct Entity_800CB658 *ent;
    s32 v;

    node = ((struct Entity_800CB658 *)arg0)->unk34;
    if (((struct Entity_800CB658 *)arg0)->unk12 > ((struct Entity_800CB658 *)arg0)->unk10) {
        if (((struct Entity_800CB658 *)arg0)->unk1C > 0) {
            ((struct Entity_800CB658 *)arg0)->unk10 = (s16)(rand() & 0x30);
            v = -0x30;
            goto shared;
        }
    } else if (((struct Entity_800CB658 *)arg0)->unk1C < 0) {
        ((struct Entity_800CB658 *)arg0)->unk10 = (s16)((rand() & 0x30) + 0x40);
        v = 0x30;
    shared:
        ((struct Entity_800CB658 *)arg0)->unk1C = v;
    }
    ((struct Entity_800CB658 *)arg0)->unk12 = (s16)(((struct Entity_800CB658 *)arg0)->unk12 + ((struct Entity_800CB658 *)arg0)->unk1C);
    ((struct Entity_800CB658 *)arg0)->mat = node->unk20->mat;
    func_800CB3BC(arg0, 0, 0, -0x50);
    ent = ((struct Entity_800CB658 *(*)(s32, void *, s16, s16, s32, s32, s32))func_80146A6C)(0xE, (void *)arg0, ((struct Entity_800CB658 *)arg0)->unk6, ((struct Entity_800CB658 *)arg0)->unkA, ((struct Entity_800CB658 *)arg0)->unkE, 0, 0);
    if (ent != 0) {
        ent->mat = node->unk20->mat;
    }
}

