#include "common.h"

void func_800CCB20(void *a0) {
    extern void func_80154150(s32 a0, s32 a1);
    extern void func_801483E8(u8 *a0);
    extern void func_8014CBF8(void *a0);
    extern void func_801474EC(s32 *a0);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void func_801477E8(s32 *a0, s32 a1);
    extern s32 func_800CCEA0(void *a0);

    func_80154150((s32)a0, 0xF);
    func_801483E8((u8 *)a0);
    func_8014CBF8(a0);
    func_801474EC((s32 *)a0);
    func_80146DE8((s32 *)a0, 0, 0, 0);
    func_801477E8((s32 *)a0, 0xffee0000);
    func_800CCEA0(a0);
}


void func_800CCB8C(void *a0) {

    extern void (*D_800CD6DC[])(void);
    s32 e;

    e = *(u16 *)((s32)a0 + 0x2) - 2;
    D_800CD6DC[e]();
}


void func_800CCBCC(s32 a0)
{
    extern void func_80148038(s32 a0, s32 a1);
    extern void func_80147460(s32 a0);
    extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    extern void func_801473EC(s32 *a0);
    extern void func_8014ED28();
    extern void func_80146D90(s32 a0);
    extern void func_8016151C(void *a0);
    extern s32 func_801725A4(u8 *a0);
    extern void func_801477E8(s32 *a0, s32 a1);
    extern void func_80154274(s32 *a0, s32 a1);
    extern void func_80146CA0(void *a0);
    extern void func_800CCEAC(void *a0);
    extern u8 D_800D53C0[];

    func_80148038(a0, 0x1A000);
    func_80147460(a0);
    func_80147AD4(a0, 0, 0, 0);
    func_801473EC((s32 *)a0);
    {
        register s32 ret __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
        func_8014ED28(a0);
        if (ret != 0) {
            func_80146D90(a0);
        }
    }
    func_8016151C((void *)a0);
    func_801725A4((u8 *)a0);
    if (*(s32 *)(a0 + 0x34) > 0) {
        func_801477E8((s32 *)a0, 0x40000);
        func_80154274((s32 *)a0, (s32)D_800D53C0);
        func_80146CA0((void *)a0);
    } else {
        func_800CCEAC((void *)a0);
    }
}


void func_800CCC88(void *a0) {
    extern void func_8014ED28(s32);
    extern void func_80146D90(s32);
    extern void func_8016151C(void *);
    extern s32 func_801725A4(u8 *);
    extern void func_80154274(s32 *, s32);
    extern void func_80146CA0(void *);
    extern s16 D_800D5404[];

    if (((int (*)(int))func_8014ED28)((s32)a0) != 0) {
        func_80146D90((s32)a0);
    }
    func_8016151C(a0);
    func_801725A4((u8 *)a0);
    if (*(u16 *)((char *)a0 + 0xB8) & 0x8000) {
        func_80154274((s32 *)a0, (s32)&D_800D5404);
        func_80146CA0(a0);
    }
    func_800CCEAC(a0);
}


void func_800CCD04(void *a0) {
    extern void func_80148038(s32 a0, s32 a1);
    extern void func_80147460(s32 a0);
    extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_801473EC(s32 *a0);
    extern void func_8014ED28(s32);
    extern void func_80146D90(s32 a0);
    extern void func_80161450(void *a0);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80146CA0(void *a0);
    extern s32 func_801725A4(u8 *a0);
    s32 s1;

    func_80148038((s32)a0, 0x1A000);
    func_80147460((s32)a0);
    func_80147AD4((s32)a0, 0, 0, 0);
    func_801473EC((s32 *)a0);
    if (((int (*)(int))func_8014ED28)((s32)a0) != 0) {
        func_80146D90((s32)a0);
    }
    s1 = ((int (*)(int))func_80161450)(a0);
    if ((s1 & 5) != 0) {
        func_800CCE24(a0);
        func_80146E90((s32 *)a0, 0x10);
        func_80146CA0(a0);
    }
    if (s1 == 0) {
        func_801725A4((u8 *)a0);
        func_800CCEAC(a0);
    }
}


extern s32 func_80146E98(s32 arg0);
extern void func_801599A4(void *arg0);
extern void func_80159B3C(void *arg0);
extern s32 func_80161208();

void func_800CCDC4(s32 a0)
{
    *(s32 *)(a0 + 0x44) |= 2;
    if (func_80146E98(a0) != 0) {
        func_801599A4((void *)a0);
        func_80159B3C((void *)a0);
    } else {
        func_80161208((void *)a0);
    }
}


extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_8013C9C4(void *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_8014C010(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern s32 D_800D3414;

void func_800CCE24(void *a0) {
    s32 s0;

    s0 = (s32)a0;
    func_8014B5C4((s32 *)s0, 2, 0);
    func_8013C9C4(&D_800D3414);
    func_801466F0(5, s0, 0, 0, 0, 0, 0, 1);
    func_8014C010((s32 *)s0, 1);
    func_80147324(0x47D);
}


s32 func_800CCEA0(void *a0) {
    *(s32 *)((s32)a0 + 0x234) = 150;
    return 150;
}


s32 func_800CCEAC(void *a0)
{
    extern void func_801599A4(void *a0);
    extern void func_80159B3C(void *a0);
    extern s16 currentLocationId;

    if (currentLocationId == 0x306F) {
        if (*(s32 *)((s32)a0 + 0x234) != 0) {
            (*(s32 *)((s32)a0 + 0x234))--;
            return 0;
        }
        func_801599A4(a0);
        func_80159B3C(a0);
        return 1;
    }
    return 0;
}




void func_800CCF14(void *a0) {

    extern void (*D_800CD6EC[])(void);
    D_800CD6EC[*(u16 *)((s32)a0 + 0x2)]();
}


void func_800CCF50(void *a0) {

    extern void func_80146578(void);
    extern void func_8001CD50(s32 a0, s32 a1);
    extern void func_80149374(s32 a0, s32 a1);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_800CD1F4(void *a0, void *a1);
    extern void func_800CD258(void *a0, void *a1);
    extern void func_800CD27C(s32 a0);
    extern void func_80146CA0(void *);
    extern void func_800CD1D4(void);
    extern u8 D_800CD704[];
    extern u8 D_800CD744[];

    s32 s0;
    register s32 s1 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus10)
    s32 s2;
    s32 s3;

    s1 = (s32)a0;
    s2 = *(s32 *)(s1 + 0x4C);
    s0 = (s32)((void *(*)(void))func_80146578)();
    s3 = (s32)&D_800CD704;
    *(s32 *)(s1 + 0x20) = s0;

    if (s0 != 0) {
        func_8001CD50(s0, s3);
        *(s32 *)(s0 + 0x34) = (s32)&D_800CD744;
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(u16 *)(s0 + 0x1C) = 0;
        func_80149374(s2, s1 + 4);
        *(u16 *)(s0 + 0x10) = *(u16 *)(s2 + 0x100);
        *(u16 *)(s0 + 0x14) = *(u16 *)(s2 + 0x104);
        *(u16 *)(s0 + 0x12) = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x12);
        func_80146E90((s32 *)s1, 0x10);
        *(u16 *)(s1 + 0x60) = 0;
        *(u16 *)(s1 + 0x62) = 0;
        func_800CD1F4((void *)s1, (void *)s3);
        func_800CD258((void *)s1, (void *)s3);
        func_800CD27C(s1);
        func_80146CA0((void *)s1);
    } else {
        ((void (*)(void *))func_800CD1D4)((void *)s1);
    }
}


s32 func_800CD258(void *a0, void *a1);
void func_800CD27C(s32 a0);
void func_800CD31C(s32 arg0);

typedef struct { char c[4]; } S4_800CD054;

void func_800CD054(void *a0) {
    extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                              s32 a4, s32 a5, s32 a6, s32 a7);
    extern void func_80147324(s32 a0);
    extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_80146E98(s32 a0);
    extern void func_80146CA0(void *a0);
    extern u8 D_800CD704[];
    u8 *dp;
    s32 s1;
    s32 w;
    s32 v0;
    s32 v1;

    s1 = *(s32 *)((s32)a0 + 0x20);
    dp = D_800CD704;
    func_800CD258(a0, dp);
    func_800CD27C((s32)a0);
    if ((*(u32 *)((s32)a0 + 0x1C) & 7) == 0) {
        func_801466F0(6, (s32)a0, 0, 0, 0, *(s16 *)((s32)a0 + 0x62), 0, 1);
        w = *(u16 *)((s32)a0 + 0x62) + 1;
        *(u16 *)((s32)a0 + 0x62) = w;
        if ((s16)w >= 8) {
            *(u16 *)((s32)a0 + 0x62) = 0;
        }
        func_80147324(0x47E);
    }
    v0 = func_80012FC8(*(s16 *)(s1 + 0x1A), 0x5000, 0xA, 1);
    v1 = *(u16 *)(s1 + 0x1A) + v0;
    *(u16 *)(s1 + 0x1A) = v1;
    *(u16 *)(s1 + 0x18) = v1;
    v1 = *(u16 *)((s32)a0 + 0x60);
    v1 += 0x20;
    *(u16 *)((s32)a0 + 0x60) = v1;
    v0 = *(u16 *)(s1 + 0x1C) + v1;
    *(u16 *)(s1 + 0x1C) = v0;
    if ((s16)v0 >= 0x1000) {
        *(u16 *)(s1 + 0x1C) = 0x1000;
    }
    *(u16 *)(s1 + 0x1E) = *(u16 *)(s1 + 0x1C) | 0x4000;
    if (*(s16 *)(s1 + 0x1C) == 0x1000) {
        *(u16 *)(s1 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 0x60) = 0;
        *(S4_800CD054 *)(dp + 4) = *(S4_800CD054 *)(dp + 0xC);
    }
    v0 = func_80146E98((s32)a0);
    if (v0 != 0) {
        func_80146CA0(a0);
    } else {
        func_800CD31C((s32)a0);
    }
}


extern void func_80162CCC(void);
void func_800CD1D4(void) {
    func_80162CCC();
}


extern void func_800233CC(void *arg0, u16 arg1);

void func_800CD1F4(void *a0, void *a1) {
    void *s0;

    s0 = a1;
    if (*(s32 *)((s32)a0 + 0x50) == 0) {
        func_800233CC(s0, 0x40);
    } else {
        func_800233CC(s0, 0x30);
    }
    *(u8 *)((s32)s0 + 0) = 0;
    *(u8 *)((s32)s0 + 1) = 0;
    *(u8 *)((s32)s0 + 2) = 0;
    *(u8 *)((s32)s0 + 4) = 0;
    *(u8 *)((s32)s0 + 5) = 0;
    *(u8 *)((s32)s0 + 6) = 0;
}


s32 func_800CD258(void *a0, void *a1) {
    s32 v;
    *(u8 *)((s32)a1 + 8) = 0;
    *(u8 *)((s32)a1 + 9) = 0;
    *(u8 *)((s32)a1 + 10) = 0;
    v = (*(u32 *)((s32)a0 + 0x1C)) << 3;
    *(u8 *)((s32)a1 + 14) = 0;
    *(u8 *)((s32)a1 + 12) = v;
    *(u8 *)((s32)a1 + 13) = v;
    return v;
}


typedef struct {
    s16 m[9];
    s16 pad;
    s32 t[3];
} Mtx_800CD27C;

typedef struct {
    Mtx_800CD27C mt; /* 0x00 */
    s32 rest[2];     /* 0x20..0x27 — frame padding, never touched */
} MtxBuf_800CD27C;

extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);

void func_800CD27C(s32 a0) {
    MtxBuf_800CD27C buf;
    s32 obj;

    obj = *(s32 *)(a0 + 0x20);
    func_80013F3C((s32)&buf);
    func_800126C4((s32)&buf, *(s16 *)(obj + 0x10));
    func_800123F0((s32)&buf, *(s16 *)(obj + 0x14));
    func_80012558((s32)&buf, *(s16 *)(obj + 0x12));
    func_800126C4((s32)&buf, 0x400);
    *(Mtx_800CD27C *)(*(s32 *)(obj + 0x34)) = buf.mt;
}


extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801202A0[];

void func_800CD31C(s32 arg0) {
    u8 sp10[8];
    u8 *p = D_801202A0;

    if (p < D_801202A0 + 0x6480) {
        u8 *end = p + 0x6480;
        do {
            if (func_8014C308(arg0, (s32)p, 0x22, 0)) {
                if (func_8014C278(arg0, (s32)p, 0x80)) {
                    func_80015978((s32)(p + 4), (s32 *)sp10);
                    *(u16 *)(sp10 + 6) = 0;
                    func_8014C3A4((void *)arg0, (s32)p, 0x22, (s32 *)sp10);
                }
            }
            p += 0x10C;
        } while (p < end);
    }
}




void func_800CD3C8(void *a0) {

    extern void (*D_800CD6F8[])(void);
    D_800CD6F8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_800CD404(void *a0) {
    extern void func_80146578(void);
    extern void func_8001CD50(s32 a0, s32 a1);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80146CA0(void *);
    extern void func_800CD670(s32 a0, void *a1);
    extern void func_800CD650(void);
    extern void func_800CD6D4(void);
    extern s32 D_800D3428;
    extern u8 D_800CD764[];
    extern u8 D_800CD964[];

    typedef struct {
        s32 w[8];
    } Block32;

    s32 s0;
    register s32 s1 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus10)
    s32 s2;
    s32 s3;

    s32 v;

    s1 = (s32)a0;
    s2 = *(s32 *)(s1 + 0x4C);
    {
        s32 base;
        s32 val;
        base = (s32)&D_800CD764;
        val = *(s32 *)(s1 + 0x50) << 6;
        s3 = val + base;
    }
    func_8013C9C4(&D_800D3428);
    s0 = (s32)((void *(*)(void))func_80146578)();
    *(s32 *)(s1 + 0x20) = s0;

    if (s0 != 0) {
        func_8001CD50(s0, s3);
        *(u16 *)(s0 + 0x1E) = 0xCCC;
        *(s32 *)(s0 + 4) |= 0x50000000;
        *(u16 *)(s0 + 0x18) = 0;
        *(u16 *)(s0 + 0x1A) = 0;
        {
            s32 dstp;
            s32 srcp;
            dstp = (*(s32 *)(s1 + 0x50) << 5) + (s32)&D_800CD964;
            *(s32 *)(s0 + 0x34) = dstp;
            srcp = *(s32 *)(*(s32 *)(s1 + 0x4C) + 0x20);
            srcp = *(s32 *)(srcp + 0x34);
            *(Block32 *)dstp = *(Block32 *)srcp;
        }
        *(u16 *)(s1 + 6) = *(u16 *)(s2 + 6);
        v = *(u16 *)(s2 + 0xA);
        *(u16 *)(s1 + 0xA) = v;
        *(u16 *)(s1 + 0x60) = v;
        *(u16 *)(s1 + 0xE) = *(u16 *)(s2 + 0xE);
        *(u16 *)(s1 + 0x62) = *(s32 *)(s2 + 0x1C);
        func_80146E90((s32 *)s1, 0x20);
        func_800CD670(s1, (void *)s3);
        ((void (*)(void *, void *))func_800CD6D4)((void *)s1, (void *)s3);
        func_80146CA0((void *)s1);
    } else {
        ((void (*)(void *))func_800CD650)((void *)s1);
    }
}


extern void func_800CD6D4(void);
extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8004787C(s32 a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern u8 D_800CD764[];

void func_800CD57C(void *arg0) {
    s32 s0;
    s32 v0;
    s32 t;

    s0 = *(s32 *)((s32)arg0 + 0x20);
    ((void (*)(void *, void *))func_800CD6D4)(
        arg0,
        (void *)(D_800CD764 + (*(s32 *)((s32)arg0 + 0x50) << 6)));
    v0 = func_80012FC8(*(s16 *)(s0 + 0x1A), 0x5000, 0xA, 1);
    t = *(u16 *)(s0 + 0x1A) + v0;
    *(u16 *)(s0 + 0x1A) = t;
    *(u16 *)(s0 + 0x18) = t;
    {
        s32 x;
        x = (s16)t;
        v0 = func_8004787C(x / 10);
    }
    {
        s32 adj;
        s32 v1;
        v1 = *(s16 *)((s32)arg0 + 0x62);
        v0 = v0 * 2;
        v1 = v1 * v0;
        adj = v1 / 0x1000;
        {
            register s32 fld __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
            fld = *(u16 *)((s32)arg0 + 0x60);
            v0 = fld - adj;
        }
    }
    *(u16 *)((s32)arg0 + 0xA) = v0;
    v0 = func_80146E98((s32)arg0);
    if (v0 != 0) {
        func_80146CA0(arg0);
    }
}


extern void func_80162CCC(void);
void func_800CD650(void) {
    func_80162CCC();
}


extern void func_800233CC(void *arg0, u16 arg1);

void func_800CD670(s32 arg0, void *arg1)
{
    s32 t;

    func_800233CC(arg1, 0x40);
    *(u8 *)(arg1 + 0) = 0;
    *(u8 *)(arg1 + 1) = 0;
    *(u8 *)(arg1 + 2) = 0;
    t = *(s16 *)(arg0 + 0x62) * 12;
    *(u8 *)(arg1 + 6) = 0;
    *(u8 *)(arg1 + 5) = t;
    *(u8 *)(arg1 + 4) = t;
}


void func_800CD6D4(void) {
}

INCLUDE_RODATA("asm/md_MAIN_043/nonmatchings/md_MAIN_043", D_800CCB1C);
