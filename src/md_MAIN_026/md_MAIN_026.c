#include "common.h"

extern void func_800183E0(s32 a0);

extern s32 D_800CBBB8;
extern s32 D_800CBB78;

void func_800CAE0C(void)
{
    func_800183E0((s32)&D_800CBBB8);
    func_800183E0((s32)&D_800CBB78);
}




void func_800CAE44(void *a0) {

    extern void (*D_800CBB10[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBB10[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
#include "../shared/slot_800CAE08/func_800CAE88__3eeb9c91.h"


void func_800CAEC0(void *arg0) {
    extern s32 func_80165910(void);
    extern void func_801655E4(s32 arg0);
    extern void func_80147324(s32 arg0);

    if (func_80165910() == 0) {
        func_801655E4((s32)arg0);
        func_80147324(0x7B8);
    }
    *(u8 *)((s32)arg0 + 0x197) += 1;
}


extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);

void func_800CAF10(void *arg0) {
    func_801466F0(0xB, (s32)arg0, 0, 0, 0, 0, 0, 0);
    *(u8 *)((s32)arg0 + 0xBE) = 0;
    *(u8 *)((s32)arg0 + 0x197) += 1;
}


void func_800CAF68(void *arg0) {
    extern u8 D_80078E78[];
    extern s32 func_8014C088(s32 a0, s32 a1);
    extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
    extern void func_80147324(s32 arg0);
    extern void func_800CB098(void *a0);
    u8 *p = D_80078E78;

    if (func_8014C088((s32)arg0, 0xB) == 0 || *(u8 *)((s32)arg0 + 0xBE) != 0) {
        func_800CB098(arg0);
    }
    if (*(s32 *)(p + 0x50) == 0) {
        func_801466F0(0xB, (s32)arg0, 0, 0, 0, 1, 0, 0);
        func_80147324(0x7DE);
        *(u8 *)((s32)arg0 + 0xBE) = 0;
        *(u8 *)((s32)arg0 + 0x197) += 1;
    }
}


extern s32 func_8014C088(s32 a0, s32 a1);
extern s32 func_80165A20(s32 a0);
extern void func_800CB108();

void func_800CB010(void *arg0) {
    if (func_8014C088((s32)arg0, 0xB) == 0) {
        *(u8 *)((s32)arg0 + 0x197) += 1;
        func_80165A20((s32)arg0);
    } else if (*(u8 *)((s32)arg0 + 0xBE) != 0) {
        func_800CB108(arg0);
    }
}


extern void func_800CB108();
void func_800CB078(void) {
    func_800CB108();
}


#include "common.h"

extern s32 func_8014C168(s32 *arg0, s32 arg1);
extern s32 func_8014C088(s32 arg0, s32 arg1);

void func_800CB098(s32 a0) {
    s32 s0;
    s32 v1;

    s0 = func_8014C168((s32 *)a0, 0x15C);
    if (s0 != 0) {
        v1 = func_8014C088(a0, 1);
        if (v1 != 0 && *(u16 *)((s32)v1 + 2) != 0) {
            *(s32 *)((s32)s0 + 0xCC) = v1;
        } else {
            *(s32 *)((s32)s0 + 0xCC) = a0;
        }
    }
}


extern s32 func_8014C168(s32 *arg0, s32 arg1);

void func_800CB108(s32 *arg0) {
    s32 s0;

    s0 = func_8014C168(arg0, 0x15C);
    if (s0 != 0) {
        *(s32 *)(s0 + 0xCC) = 0;
    }
}



extern void func_800CB5D4(void);

void func_800CB134(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB24[])(void);
    if (D_80078EC1 == 0x16) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB24[v0]();
    } else {
        func_800CB5D4();
    }
}


void func_800CB190(void *arg0) {
    extern void func_800CB5F4();
    extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
    extern void func_80146E90(s32 *, s32);
    extern void func_80146CA0(void *);
    extern s32 rand();

    s32 color;
    s32 tmp;

    func_800CB5F4(arg0);
    if (*(s32 *)((u8 *)arg0 + 0x50) == 0) {
        color = (rand() & 0xF) << 8;
        func_801466F0(0xC, arg0, 0, 0, 0, color, 0, 0);
        tmp = color + 0x555;
        func_801466F0(0xC, arg0, 0, 0, 0, tmp, 0, 0);
        tmp = color + 0xAAA;
        func_801466F0(0xC, arg0, 0, 0, 0, tmp, 0, 0);
        func_80146E90((s32 *)arg0, 8);
    } else {
        func_80146E90((s32 *)arg0, 0);
    }
    func_80146CA0(arg0);
}


#include "common.h"

extern s32 func_80146E98();
extern void func_80146578(void);
extern void func_8001CD9C(int a0, void *a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80146CA0(void *a0);
extern void func_80162CCC(void);

extern u8 D_800CBBD8;
extern u8 D_800CBBD9;
extern u8 D_800CBBDA;
extern u8 D_800CBBDB;
extern u8 D_800CBBDC;
extern u8 D_800CBBDD;
extern u8 D_800CBBDE;
extern u8 D_800CBBDF;

void func_800CB278(s32 param_1)
{
    register s32 p1    __asm__("$17");  /* $s1 */  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus10)
    register s32 iVar1 __asm__("$16");  /* $s0 */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus10)
    s32 base;  /* $s2 */
    register s32 ivar3 __asm__("$19");  /* $s3 */  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B tus10)

    p1 = param_1;
    base = (s32)&D_800CBBD8;
    if (((s32 (*)(void))func_80146E98)() == 0) {
        return;
    }
    *(s32 *)(p1 + 0x20) = (iVar1 = ((s32 (*)(void))func_80146578)());
    ivar3 = iVar1;
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, (void *)base);
        func_800233CC((void *)base, 0x80);
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(p1 + 0x60) = 0;
        D_800CBBDB = 0;
        D_800CBBDF = 0;
        if (*(s32 *)(p1 + 0x50) == 0) {
            *(u8 *)base = 0xFF;
            D_800CBBD9 = 0xFF;
            D_800CBBDA = 0xFF;
            D_800CBBDC = 0;
            D_800CBBDD = 0;
            D_800CBBDE = 0xFF;
            *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        } else {
            *(u8 *)base = 0;
            D_800CBBDA = 0xC0;
            D_800CBBD9 = 0;
            D_800CBBDC = 0;
            D_800CBBDD = 0;
            D_800CBBDE = 0x80;
            *(u32 *)(ivar3 + 4) = *(u32 *)(ivar3 + 4) | 0x50000000;
        }
        func_80146CA0((void *)p1);
    } else {
        ((void (*)(s32))func_80162CCC)(p1);
    }
}


#include "common.h"

extern void func_800CB5F4();

void func_800CB3C0(void *arg0) {
    void *s0;
    s16 w;
    void *v1;

    s0 = *(void **)((u8 *)arg0 + 0x20);
    func_800CB5F4(arg0);
    if (*(s32 *)((u8 *)arg0 + 0x50) != 0) {
        *(u16 *)((u8 *)s0 + 0x1e) += 0x100;
    }
    *(u16 *)((u8 *)arg0 + 0x60) += 0x40;
    w = *(u16 *)((u8 *)s0 + 0x1a) + *(u16 *)((u8 *)arg0 + 0x60);
    *(u16 *)((u8 *)s0 + 0x1a) = w;
    *(u16 *)((u8 *)s0 + 0x18) = w;
    if ((s16)w >= 0x1001) {
        *(u16 *)((u8 *)s0 + 0x1a) = 0x1000;
        *(u16 *)((u8 *)s0 + 0x18) = 0x1000;
        v1 = *(void **)((u8 *)arg0 + 0x4c);
        *(u8 *)((u8 *)v1 + 0xbe) = 1;
        func_80146CA0(arg0);
    }
}


void func_800CB470(void *arg0) {
    extern void func_800CB5F4();
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146CA0(void *a0);
    extern u8 D_800CBBD8;
    extern u8 D_800CBBD9;
    extern u8 D_800CBBDA;
    extern u8 D_800CBBDC;
    extern u8 D_800CBBDD;
    extern u8 D_800CBBDE;

    s32 base;
    void *s1;
    s16 w;

    s1 = *(void **)((u8 *)arg0 + 0x20);
    func_800CB5F4(arg0);
    base = (s32)&D_800CBBD8;
    *(u8 *)base = func_80012F74(*(u8 *)base, 0, 10, 1);
    D_800CBBD9 = func_80012F74(D_800CBBD9, 0, 10, 1);
    D_800CBBDA = func_80012F74(D_800CBBDA, 0, 10, 1);
    D_800CBBDC = func_80012F74(D_800CBBDC, 0, 10, 1);
    D_800CBBDD = func_80012F74(D_800CBBDD, 0, 10, 1);
    D_800CBBDE = func_80012F74(D_800CBBDE, 0, 10, 1);
    if (*(s32 *)((u8 *)arg0 + 0x50) != 0) {
        w = *(u16 *)((u8 *)s1 + 0x1e) + 0x20;
        *(u16 *)((u8 *)s1 + 0x1e) = w;
        if ((s16)w >= 0x1001) {
            *(u16 *)((u8 *)s1 + 0x1e) = 0x1000;
        }
    }
    if (*(s32 *)base == 0 && *(s32 *)&D_800CBBDC == 0) {
        func_80146CA0(arg0);
    }
}


extern void func_80162CCC(void);
void func_800CB5D4(void) {
    func_80162CCC();
}


void func_800CB5F4(s32 a0) {
    extern void func_80146EC0(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void (*D_800CBB38[])(void);
    extern u8 D_800CBB40;
    func_80146EC0(*(s32 *)(a0 + 0x4C), a0 + 4, (s32)&D_800CBB40, (s32)&D_800CBB38);
}



extern void func_800CB8A4(void);

void func_800CB62C(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBB48[])(void);
    if (D_80078EC1 == 0x16) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBB48[v0]();
    } else {
        func_800CB8A4();
    }
}


extern void func_80146CA0(void *arg0);

void func_800CB688(void *a0) {
    s32 v1 = -0x100;
    *(u16 *)((s32)a0 + 0x12) = v1;
    *(u16 *)((s32)a0 + 0x16) = v1;
    v1 = *(s32 *)((s32)a0 + 0x50);
    *(u16 *)((s32)a0 + 0x14) = 8;
    *(u16 *)((s32)a0 + 0x10) = 0;
    *(u8 *)((s32)a0 + 0x58) = 0xFF;
    *(u8 *)((s32)a0 + 0x59) = 0xFF;
    *(u8 *)((s32)a0 + 0x5A) = 0xFF;
    *(u8 *)((s32)a0 + 0x5B) = 0;
    *(u8 *)((s32)a0 + 0x5C) = 0;
    *(u8 *)((s32)a0 + 0x5D) = 0;
    *(u8 *)((s32)a0 + 0x5E) = 0xFF;
    *(u8 *)((s32)a0 + 0x5F) = 0;
    *(u16 *)((s32)a0 + 0x18) = v1;
    func_80146CA0(a0);
}


extern void func_80146CA0(void *a0);
extern void func_800CB8C4(void *a0, void *a1);
extern void func_800CB900();

void func_800CB6E8(void *arg0) {
    s16 w;
    s32 pad[2];

    w = *(u16 *)((u8 *)arg0 + 0x12) + 0x18;
    *(u16 *)((u8 *)arg0 + 0x12) = w;
    if ((s16)w >= -7) {
        *(s16 *)((u8 *)arg0 + 0x12) = -8;
        func_80146CA0(arg0);
    }
    w = *(u16 *)((u8 *)arg0 + 0x18) + 0xB;
    *(u16 *)((u8 *)arg0 + 0x18) = w;
    func_800CB8C4(arg0, pad);
    func_800CB900(arg0, pad, (u8 *)arg0 + 0x10, (u8 *)arg0 + 0x14,
                  (u8 *)arg0 + 0x58, (u8 *)arg0 + 0x5C, (u8 *)arg0 + 0x18);
}


void func_800CB77C(void *arg0) {
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146CA0(void *a0);
    extern void func_800CB8C4(void *a0, void *a1);
    extern void func_800CB900();
    s16 w;
    s32 pad[2];

    w = *(u16 *)((u8 *)arg0 + 0x14) + 8;
    *(u16 *)((u8 *)arg0 + 0x14) = w;
    *(u8 *)((u8 *)arg0 + 0x58) = func_80012F74(*(u8 *)((u8 *)arg0 + 0x58), 0, 10, 1);
    *(u8 *)((u8 *)arg0 + 0x59) = func_80012F74(*(u8 *)((u8 *)arg0 + 0x59), 0, 10, 1);
    *(u8 *)((u8 *)arg0 + 0x5A) = func_80012F74(*(u8 *)((u8 *)arg0 + 0x5A), 0, 10, 1);
    *(u8 *)((u8 *)arg0 + 0x5C) = func_80012F74(*(u8 *)((u8 *)arg0 + 0x5C), 0, 10, 1);
    *(u8 *)((u8 *)arg0 + 0x5D) = func_80012F74(*(u8 *)((u8 *)arg0 + 0x5D), 0, 10, 1);
    *(u8 *)((u8 *)arg0 + 0x5E) = func_80012F74(*(u8 *)((u8 *)arg0 + 0x5E), 0, 10, 1);
    if (*(s32 *)((u8 *)arg0 + 0x58) == 0 && *(s32 *)((u8 *)arg0 + 0x5C) == 0) {
        func_80146CA0(arg0);
    }
    w = *(u16 *)((u8 *)arg0 + 0x18) + 0x2D;
    *(u16 *)((u8 *)arg0 + 0x18) = w;
    func_800CB8C4(arg0, pad);
    func_800CB900(arg0, pad, (u8 *)arg0 + 0x10, (u8 *)arg0 + 0x14,
                  (u8 *)arg0 + 0x58, (u8 *)arg0 + 0x5C, (u8 *)arg0 + 0x18);
}


extern void func_80162CCC(void);
void func_800CB8A4(void) {
    func_80162CCC();
}


extern void func_80015978(s32 a0, s32 *a1);
extern void func_8012EFB8();

void func_800CB8C4(void *a0, void *a1) {
    func_80015978(*(s32 *)((s32)a0 + 0x4C) + 4, (s32 *)a1);
    func_8012EFB8(a1, a1);
}


void func_800CB900(void *arg0, void *trns, void *vsrc, void *dsrc, void *oncep, void *twicep, s16 *angp) {
    extern u16 D_800B99DA;
    struct {
        s16 o1[4];
        s16 o2[4];
        s16 o3[4];
        u16 q28, q2A, q2C, q2E, q30, q32;
        u32 w34, w38, w3C, w40;
        u8 b44;
        char z45[3];
        s16 v48[4];
        s16 v50[4];
        s16 v58[4];
        s32 mat[8];
    } L;
    u32 w3c;
    u16 t;

    func_80013F3C(L.mat);
    RotMatrixZ(*angp, L.mat);

    L.mat[5] = *(s16 *)trns;
    L.mat[6] = *((s16 *)trns + 1);
    L.mat[7] = 0;
    func_8004914C(L.mat);
    func_800491AC(L.mat);


    L.w40 = 0x50000000;
    L.w34 = *(u32 *)oncep;
    L.w38 = *(u32 *)twicep;

    w3c = *(u32 *)twicep;
    L.v48[0] = *(u16 *)vsrc;
    L.v48[1] = *((u16 *)vsrc + 1);
    L.v48[2] = 0;
    L.v50[0] = *(u16 *)vsrc - *(u16 *)dsrc;
    L.v50[1] = *((u16 *)dsrc + 1);
    L.v50[2] = 0;
    L.v58[0] = *(u16 *)vsrc + *(u16 *)dsrc;
    L.v58[1] = *((u16 *)dsrc + 1);
    L.w3C = w3c;
    w3c = (u32)L.o1;
    L.v58[2] = 0;


    gte_ldv0(L.v48);  // !FAKE: gte via LDV — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
    gte_rtv0tr();
    gte_stsv((u16 *)w3c);
    gte_ldv0(L.v50);  // !FAKE: gte via LDV — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
    gte_rtv0tr();
    gte_stsv(L.o2);
    gte_ldv0(L.v58);  // !FAKE: gte via LDV — clobbers beyond Sony's macro (a scheduling steer; P36 T5 t5_remark3)
    gte_rtv0tr();
    gte_stsv(L.o3);

    __asm__ __volatile__("" : : "r"(twicep));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)

    L.q2A = 0x13F;
    L.q2E = 0x100;
    L.q32 = 0x17F;
    L.b44 = 0x19;
    L.o1[2] = 1;
    t = (D_800B99DA << 2) & 0x3F;
    L.q28 = t | 0x680;
    L.q2C = t + 0x6BF;
    L.q30 = L.q2C;
    func_800174DC();
}

