#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CC160;
    func_800183E0(&D_800CC160);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CC104[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CC104[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
#include "../shared/slot_800CAE08/func_800CAE78__a79b87ee.h"


extern u8 D_800CC01C[];
extern void func_80154274(void *a0, void *a1);
extern void func_801655E4(void *a0);

void func_800CAEC0(u8 *a0) {
    func_80154274(a0, D_800CC01C);
    func_801655E4(a0);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


extern s32 func_80161208();
extern s32 func_800CB170(s32 a0);
extern void func_80147324(s32 a0);
extern void func_80162CCC();
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern u8 D_800CC0D8[];
extern s32 D_8011F9D0;

void func_800CAF08(u8 *arg0) {
    u16 *p;

    if (func_80161208() != 0) {
        func_800CB170((s32)arg0);
        return;
    }
    if (*(u16 *)(arg0 + 0xB8) != 0x8000) {
        return;
    }
    func_80147324(0x479);
    func_80154274(arg0, D_800CC0D8);
    *(u8 *)(arg0 + 0xBE) = 0x10;
    *(u8 *)(arg0 + 0x197) = *(u8 *)(arg0 + 0x197) + 1;
    p = (u16 *)&D_8011F9D0;
    if (p < (u16 *)((s32)&D_8011F9D0 + 0x820)) {
        do {
            if (*p == 4) {
                func_80162CCC(p);
            }
            if (*p == 0xF) {
                func_80162CCC(p);
            }
            p += 0x34;
        } while (p < (u16 *)((s32)&D_8011F9D0 + 0x820));
    }
    func_801466F0(4, (s32)arg0, 0, -0x18, -0xF, 0, 0, 1);
    func_801466F0(4, (s32)arg0, 0, -0x18, -0xF, 1, 0, 1);
    func_801466F0(4, (s32)arg0, 0, -0x18, -0xF, 2, 0, 1);
    func_801466F0(4, (s32)arg0, 0, -0x18, -0xF, 3, 0, 1);
    func_801466F0(0xF, (s32)arg0, 0, -0x18, -0xF, 0, 0, 0);
}


void func_800CB0C8(void *a0) {
    extern s32 D_800CC580;
    extern void func_800CB1A0(void);
    extern s32 func_80161208();
    extern void func_80165A78(s32 a0);
    extern void func_80159B3C(void *a0);
    extern s32 func_800CB170(s32 a0);
    s32 v0;
    s32 p;

    p = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(p + 0x2C) |= 0x20;
    p = *(s32 *)((s32)a0 + 0x20);
    *(s32 *)(p + 0x80) = (s32)&D_800CC580;
    func_800CB1A0();
    *(u32 *)((s32)a0 + 0x44) |= 2;
    v0 = func_80161208((s32)a0);
    if (v0 != 0) {
        func_800CB170((s32)a0);
        return;
    }
    p = *(u8 *)((s32)a0 + 0xBE);
    v0 = p + 0xFF;
    *(u8 *)((s32)a0 + 0xBE) = v0;
    if (p == 0) {
        func_800CB170((s32)a0);
        func_80165A78((s32)a0);
        func_80159B3C(a0);
    }
}


extern void func_80154A74(s32 a0, s32 a1);
s32 func_800CB170(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}


#include "common.h"

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_800CB1A0(void) {
    extern u16 D_800B99DA;
    extern s32 D_800CC580;
    extern s32 D_800CC584;
    extern s32 D_800CC588;
    extern u8 D_800CC58C;
    extern u8 D_800CC58D;
    extern u8 D_800CC58E;
    extern s32 D_800CC590;
    extern s32 D_800CC594;
    extern s32 D_800CC598;
    extern u8 D_800CC59C;
    extern u8 D_800CC59D;
    extern u8 D_800CC59E;
    extern s32 D_800CC5A0;
    extern s32 D_800CC5A4;
    extern s32 D_800CC5A8;
    extern u8 D_800CC5AC;
    extern u8 D_800CC5AD;
    extern u8 D_800CC5AE;
    u16 *p;
    s32 ff;

    p = &D_800B99DA;
    D_800CC580 = func_8004787C((p[0] & 7) << 9);
    D_800CC584 = 0;
    D_800CC588 = func_80047948((p[0] & 7) << 9);
    ff = 0xFF;
    D_800CC58C = ff;
    D_800CC58D = 0;
    D_800CC58E = 0;
    D_800CC590 = func_8004787C((p[0] & 7) << 9);
    D_800CC594 = func_80047948((p[0] & 7) << 9);
    D_800CC598 = 0;
    D_800CC59C = 0;
    D_800CC59D = 0;
    D_800CC59E = ff;
    D_800CC5A0 = 0;
    D_800CC5A4 = func_8004787C((p[0] & 7) << 9);
    D_800CC5A8 = func_80047948((p[0] & 7) << 9);
    D_800CC5AC = ff;
    D_800CC5AD = ff;
    D_800CC5AE = ff;
}



extern void func_800CB4A8(void);

void func_800CB2C8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CC124[])(void);
    if (D_80078EC1 == 0xd) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC124[v0]();
    } else {
        func_800CB4A8();
    }
}


void func_800CB324(s32 a0) {
    extern void func_8014659C(void);
    extern void func_8001C2C4(s32 a0);
    extern void func_800CB4C8(void *a0);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80146CA0(void *a0);
    extern void func_800CB4A8(void);

    typedef struct { u32 a, b, c, d; } Blk16;

    s32 iVar1;
    s32 iVar2;
    s32 iVar4;

    iVar2 = *(s32 *)(a0 + 0x4C);
    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(a0 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001C2C4(iVar1);
        *(u32 *)(iVar1 + 4) |= 0x80000000;
        iVar4 = *(s32 *)(iVar2 + 0x20);
        *(Blk16 *)(iVar1 + 0x34) = *(Blk16 *)(iVar4 + 0x34);
        *(Blk16 *)(iVar1 + 0x44) = *(Blk16 *)(iVar4 + 0x44);
        func_800CB4C8((void *)a0);
        func_80146E90((s32 *)a0, 0x40);
        func_80146CA0((void *)a0);
    } else {
        ((void (*)(s32))func_800CB4A8)(a0);
    }
}


typedef struct { s32 vpx, vpy, vpz, vrx, vry, vrz, rz, super; } RView;

extern void func_800CB578(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80015954(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80146CA0(void *a0);
extern void func_800CBC0C(void *a0);

void func_800CB3FC(void *arg0)
{
    RView view; /* unused: reserves the extra 0x20 frame bytes the target has */
    *(u16 *)((s32)arg0 + 0x14) -= 6;
    func_800CB578(arg0);
    if (func_80146E98((s32)arg0) != 0) {
        func_80015954((s32)arg0 + 0x10, (s32)arg0 + 4);
        func_80149374((s32)arg0, (s32)arg0 + 4);
        func_80146A6C(3, arg0,
                      *(s16 *)((s32)arg0 + 6),
                      *(s16 *)((s32)arg0 + 0xA),
                      *(s16 *)((s32)arg0 + 0xE),
                      0,
                      0x80001C00);
        func_80146CA0(arg0);
    } else {
        func_800CBC0C(arg0);
    }
}


extern void func_80162CCC(void);
void func_800CB4A8(void) {
    func_80162CCC();
}


typedef struct { u8 b[8]; } Blk8;

extern void func_80015978(s32 a0, s32 *a1);
extern void func_80149374(s32 a0, s32 a1);
extern u8 D_800CC5B0[];

void func_800CB4C8(void *arg0) {
    s32 s1 = (s32)arg0;
    s32 off;
    s32 t;
    s32 s2;
    u8 *dst;
    s32 i;

    s2 = *(s32 *)(s1 + 0x4C);
    off = *(s32 *)(s1 + 0x50) * 160;
    dst = D_800CC5B0 + off;
    func_80015978(s1 + 4, (s32 *)(s1 + 0x10));
    for (i = 0; i < 20; i++) {
        *(Blk8 *)dst = *(Blk8 *)(s1 + 0x10);
        dst += 8;
    }
    func_80149374(s2, s1 + 4);
    t = *(s32 *)(s1 + 0x50);
    *(u16 *)(s1 + 0x60) = 0;
    *(u16 *)(s1 + 0x64) = t << 10;
}


#include "common.h"

typedef struct { u8 b[4]; } B4_CB578;
typedef struct { u8 b[8]; } B8_CB578;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_CB578;

extern void func_80013F3C(void *a0);
extern void RotMatrixZ(s32 a0, void *a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_800130D0(s32 a0, s32 a1, s32 a2);
extern void func_800CB9F8(u16 *a0, u16 *a1, s32 *a2, s32 *a3, s32 stg);
extern u8 D_800CC114[];
extern u8 D_800CC5B0[];
extern u8 D_800CC638[];


#define gte_rt(p)                                        \
    __asm__ volatile (                                   \
        "lhu $12, 0( %0 );"                              \
        "lhu $13, 6( %0 );"                              \
        "lhu $14, 12( %0 );"                             \
        "mtc2 $12, $9;"                                  \
        "mtc2 $13, $10;"                                 \
        "mtc2 $14, $11;"                                 \
        "nop;"                                           \
        "nop;"                                           \
        "mvmva 1, 0, 3, 3, 0"                            \
        :                                                \
        : "r"( p )                                       \
        : "$12", "$13", "$14", "memory");                \
    __asm__ volatile (                                   \
        "mfc2 $12, $9;"                                  \
        "mfc2 $13, $10;"                                 \
        "mfc2 $14, $11;"                                 \
        "sh $12, 0( %0 );"                               \
        "sh $13, 6( %0 );"                               \
        "sh $14, 12( %0 )"                               \
        :                                                \
        : "r"( p )                                       \
        : "$12", "$13", "$14", "memory")

void func_800CB578(void *arg0) {
    u16 pos[4];
    MTX_CB578 mat;
    u16 sv[4];
    B4_CB578 clr[2];
    s32 obj;
    s32 t;
    s16 sn;
    u8 *p;
    s32 i;

    obj = *(s32 *)((u8 *)arg0 + 0x20);
    func_80013F3C(&mat);
    RotMatrixZ(*(s16 *)((u8 *)arg0 + 0x64), &mat);
    gte_SetRotMatrix(obj + 0x34);
    gte_rt((s32)&mat);
    gte_rt((s32)&mat + 2);
    gte_rt((s32)&mat + 4);
    mat.t[0] = *(s32 *)(obj + 0x48);
    mat.t[1] = *(s32 *)(obj + 0x4C);
    mat.t[2] = *(s32 *)(obj + 0x50);
    *(u16 *)((u8 *)arg0 + 0x64) = (*(u16 *)((u8 *)arg0 + 0x64) + 0x71) & 0xFFF;
    *(B8_CB578 *)pos = *(B8_CB578 *)((u8 *)arg0 + 0x10);

    sn = func_8004787C(*(s16 *)((u8 *)arg0 + 0x62)) / 128;
    t = func_80047948(*(s16 *)((u8 *)arg0 + 0x60));
    pos[0] += (sn * t) / 4096;
    t = func_8004787C(*(s16 *)((u8 *)arg0 + 0x60));
    pos[1] += (sn * t) / 4096;

    *(u16 *)((u8 *)arg0 + 0x60) = (*(u16 *)((u8 *)arg0 + 0x60) + 0xE3) & 0xFFF;
    *(u16 *)((u8 *)arg0 + 0x62) = (*(u16 *)((u8 *)arg0 + 0x62) + 0x38) & 0xFFF;

    p = D_800CC5B0 + *(s32 *)((u8 *)arg0 + 0x50) * 160;
    clr[0] = *(B4_CB578 *)(D_800CC114 + *(s32 *)((u8 *)arg0 + 0x50) * 4);
    clr[1] = *(B4_CB578 *)(D_800CC114 + *(s32 *)((u8 *)arg0 + 0x50) * 4);
    sv[0] = sv[1] = sv[2] = 0x1000;
    func_800CB9F8(pos, (u16 *)p, (s32 *)&mat, (s32 *)clr, (s32)sv);

    p = D_800CC5B0 + *(s32 *)((u8 *)arg0 + 0x50) * 160;
    i = 0;
    do {
        clr[0] = clr[1];
        clr[1].b[0] = func_800130D0(clr[1].b[0], 0, 0xC);
        clr[1].b[1] = func_800130D0(clr[1].b[1], 0, 0xC);
        clr[1].b[2] = func_800130D0(clr[1].b[2], 0, 0xC);
        sv[0] = sv[1] = sv[2] = sv[2] - 0x100;
        func_800CB9F8((u16 *)p, (u16 *)(p + 0x10), (s32 *)&mat, (s32 *)clr, (s32)sv);
        p += 0x10;
        i += 2;
    } while (i < 0x12);

    p = D_800CC638 + *(s32 *)((u8 *)arg0 + 0x50) * 160;
    clr[0] = clr[1];
    clr[1].b[0] = func_800130D0(clr[1].b[0], 0, 0xA);
    clr[1].b[1] = func_800130D0(clr[1].b[1], 0, 0xA);
    clr[1].b[2] = func_800130D0(clr[1].b[2], 0, 0xA);
    sv[0] = sv[1] = sv[2] = sv[2] - 0x100;
    func_800CB9F8((u16 *)p, (u16 *)(p + 0x10), (s32 *)&mat, (s32 *)clr, (s32)sv);

    i = 0;
    p = &D_800CC638[0x10] + *(s32 *)((u8 *)arg0 + 0x50) * 160;
    do {
        *(B8_CB578 *)p = *(B8_CB578 *)(p - 8);
        i += 1;
        p -= 8;
    } while (i < 0x13);
    *(B8_CB578 *)p = *(B8_CB578 *)pos;
}


extern s32 func_80017DC4(void *a0, void *a1);
extern s32 func_80017758(void *a0, void *a1);


void func_800CB9F8(u16 *a0, u16 *a1, s32 *a2, s32 *a3, s32 stg) {
    struct { s16 v[4]; } p[4];
    s32 w[4];
    s32 hdr[2];
    s16 mat[16];
    void *pa;
    s32 t;

    t = *(s32 *)&stg;
    p[0].v[0] = a0[0] - 8;
    p[0].v[1] = a0[1];
    p[0].v[2] = a0[2];
    p[1].v[0] = a0[0] + 8;
    p[1].v[1] = a0[1];
    p[1].v[2] = a0[2];
    p[2].v[0] = a1[0] - 8;
    p[2].v[1] = a1[1];
    p[2].v[2] = a1[2];
    p[3].v[0] = a1[0] + 8;
    p[3].v[1] = a1[1];
    p[3].v[2] = a1[2];
    w[0] = *(s32 *)a3;
    w[1] = *(s32 *)a3;
    w[2] = *(s32 *)(a3 + 1);
    w[3] = *(s32 *)(a3 + 1);
    hdr[0] = 0x50000000;
    func_80017DC4((void *)t, (void *)mat);
    pa = p;
    gte_SetRotMatrix(a2);
    __asm__ volatile (  // !FAKE: gte direct — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
        "lhu $12, 0( %0 );"
        "lhu $13, 6( %0 );"
        "lhu $14, 12( %0 );"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0"
        :
        : "r"((s32)mat)
        : "$12", "$13", "$14", "memory");
    gte_stclmv((s32)mat);
    __asm__ volatile (  // !FAKE: gte direct — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
        "lhu $12, 0( %0 );"
        "lhu $13, 6( %0 );"
        "lhu $14, 12( %0 );"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0"
        :
        : "r"((s32)mat + 2)
        : "$12", "$13", "$14", "memory");
    gte_stclmv((s32)mat + 2);
    __asm__ volatile (  // !FAKE: gte direct — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
        "lhu $12, 0( %0 );"
        "lhu $13, 6( %0 );"
        "lhu $14, 12( %0 );"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0"
        :
        : "r"((s32)mat + 4)
        : "$12", "$13", "$14", "memory");
    gte_stclmv((s32)mat + 4);
    ((s32 *)mat)[5] = a2[5];
    ((s32 *)mat)[6] = a2[6];
    ((s32 *)mat)[7] = a2[7];
    func_80017758(pa, (void *)mat);
}


extern void func_80015978(s32 a0, s32 *a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801202A0[];
extern u8 D_80126720[];

void func_800CBC0C(void *a0) {
    u8 *r04;
    u8 *p;
    s16 buf10[4];
    s16 buf18[4];

    r04 = (u8 *)a0 + 4;
    func_80015978((s32)r04, (s32 *)buf18);
    func_80015954((s32)a0 + 0x10, (s32)r04);
    *(s16 *)((s32)a0 + 0xA) = 0;
    func_80149374((s32)a0, (s32)r04);
    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if (func_8014C308((s32)a0, (s32)p, 0x1E, 0x2000) != 0) {
                if (*(s16 *)(p + 0xAA) == 0) {
                    if (func_8014C278((s32)a0, (s32)p, 0x40) != 0) {
                        func_80015978((s32)(p + 4), (s32 *)buf10);
                        buf10[3] = 0;
                        func_8014C3A4((void *)a0, (s32)p, 0x1E, (s32)buf10);
                    }
                }
            }
            p += 0x10C;
        } while (p < D_80126720);
    }
    func_80015954((s32)buf18, (s32)((u8 *)a0 + 4));
}




extern void func_80162CCC(void);

void func_800CBD0C(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CC130[])(void);
    if (D_80078EC1 == 0xd) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC130[v0]();
    } else {
        func_80162CCC();
    }
}


void func_800CBD68(s32 a0) {
    extern s32 D_800CC830;
    extern s32 D_800CC834;
    extern void func_80146578(void);
    extern void func_8001CD9C(s32 a0, s32 a1);
    extern void func_800233CC(void *a0, u16 a1);
    extern void func_800CBF80(void *a0);
    extern void func_80149374(s32 a0, s32 a1);
    extern void func_800D1FC8(void *a0, s32 a1);
    extern void func_80146CA0(void *a0);
    extern void func_80162CCC_w19(void *a0) __asm__("func_80162CCC");

    s32 iVar1;
    s32 iVar2;
    void *ptr;

    iVar1 = *(s32 *)(a0 + 0x4C);
    iVar2 = ((s32 (*)(void))func_80146578)();
    ptr = &D_800CC830;
    *(s32 *)(a0 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001CD9C(iVar2, (s32)ptr);
        func_800233CC(ptr, 0x60);
        *(u16 *)(iVar2 + 0x1A) = 0x3000;
        *(u16 *)(iVar2 + 0x18) = 0x3000;
        D_800CC834 = 0;
        func_800CBF80((void *)a0);
        *(s32 *)(iVar2 + 4) = *(s32 *)(iVar2 + 4) | 0x50000000;
        func_80149374(iVar1, a0 + 4);
        func_800D1FC8((void *)a0, 6);
        func_80146CA0((void *)a0);
    } else {
        func_80162CCC_w19((void *)a0);
    }
}


extern void func_800CBF80(void *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_800CBE38(u8 *arg0)
{
    s16 w;
    s32 s2;

    s2 = *(s32 *)((u8 *)arg0 + 0x20);
    func_800CBF80(arg0);
    w = *(u16 *)(s2 + 0x18) - 0x600;
    if (w < 0x1000) {
        w = 0x1000;
        func_80146E90((s32 *)arg0, 0x10);
        *(u16 *)(arg0 + 0x60) = w;
        func_80146CA0(arg0);
    }
    *(u16 *)(s2 + 0x1A) = w;
    *(u16 *)(s2 + 0x18) = w;
}


extern s32 func_80146E98(s32 a0);
extern void func_800CBF60();
extern void func_800CBF80(void *a0);
extern u16 D_800B99DA;

void func_800CBEC0(u8 *arg0)
{
    s32 s1;
    s32 w;
    s16 r;

    s1 = *(s32 *)((u8 *)arg0 + 0x20);
    if (func_80146E98((s32)arg0) != 0) {
        func_800CBF60(arg0);
        return;
    }
    func_800CBF80(arg0);
    w = *(u16 *)(arg0 + 0x60) - 0x100;
    *(u16 *)(arg0 + 0x60) = w;
    if (D_800B99DA & 1) {
        r = (s16)w / 2;
    } else {
        r = w;
    }
    *(u16 *)(s1 + 0x1A) = r;
    *(u16 *)(s1 + 0x18) = r;
}


extern void func_80162CCC(void);
void func_800CBF60(void) {
    func_80162CCC();
}


extern u16 D_800B99DA;
extern s32 D_800CC830;

void func_800CBF80(void *a0) {
    s32 v;

    v = 0xFF0000;
    if (!(D_800B99DA & 3)) {
        v = 0xFFFF;
    }
    D_800CC830 = v;
}

