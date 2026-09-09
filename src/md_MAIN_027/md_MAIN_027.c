#include "common.h"

void func_800CAE0C(void) {
    extern void func_800183E0(s32 a0);
    extern s32 D_800CC22C;
    extern s32 D_800CC1EC;
    ((void (*)(void *))func_800183E0)(&D_800CC22C);
    ((void (*)(s32))func_800183E0)((s32)&D_800CC1EC);
}




void func_800CAE44(void *a0) {

    extern void (*D_800CC134[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CC134[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
#include "../shared/slot_800CAE08/func_800CAE88__3eeb9c91.h"


extern void func_801599A4(void *a0);
extern void func_800CAF5C(s32 *a0);
extern s32 func_80165910(s32 a0);
extern void func_801655E4(s32 a0);

void func_800CAEC0(s32 a0) {
    func_801599A4((void *)a0);
    func_800CAF5C((s32 *)a0);
    if (func_80165910(a0) == 0) {
        func_801655E4(a0);
    }
    *(u8 *)(a0 + 0x197) += 1;
}


void func_800CAF18(void) {
}

void func_800CAF20(void) {
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFEC();
void func_800CAF28(s32 *a0) {
    func_80147078(a0, 32);
    ((void (*)(void *))func_800CAFEC)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAF90(void *a0);
void func_800CAF5C(s32 *a0) {
    func_80147078(a0, 32);
    func_800CAF90(a0);
}




void func_800CAF90(void *a0) {

    extern void (*D_800CC140[])(void);
    D_800CC140[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CAFEC();
void func_800CAFCC(void) {
    func_800CAFEC();
}


void func_800CAFEC(s32 *a0) {
    s32 *v1;
    extern s32 func_80161208();
    extern s32 func_80165A20(s32);
    extern void func_801553A8(s32 *a0);
    extern void func_80155440(s32 *a0);
    extern void func_80154150(s32 a0, s32 a1);
    extern void func_80154A74(s32 a0, s32 a1);
    extern void func_80146CA0(void *a0);

    if (func_80161208(a0) != 0) {
        ((void (*)(s32))func_80165A20)((s32)a0);
        return;
    }
    func_801553A8(a0);
    func_80155440(a0);
    func_80154150((s32)a0, 0x26);
    func_80154A74((s32)a0, 0x1E);
    v1 = (s32 *)a0[0x20 / 4];
    *(s16 *)((u8 *)v1 + 0x10) = 0xFE9;
    a0[0x238 / 4] = 0;
    func_80146CA0(a0);
}


extern s32 func_80161208();
extern s32 func_80165A20(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB06C(void *arg0) {
    s32 p;
    s32 q;
    register void *a __asm__("$4");
    if (func_80161208(arg0) != 0) {
        func_80165A20(arg0);
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x238) += 0x1c000;
    p = *(s32 *)((u8 *)arg0 + 0x20);
    *(u16 *)((u8 *)p + 0x10) =
        (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x23a)) & 0xfff;
    q = *(s32 *)((u8 *)arg0 + 0x20);
    if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
        a = arg0;
        __asm__ __volatile__("" : : "r"(a));
        *(u16 *)((u8 *)q + 0x10) = 0xc00;
        *(u16 *)((u8 *)a + 0xb8) = 1;
        func_80146CA0(a);
    }
}


extern s32 func_80161208();
extern s32 func_80165A20(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB108(s32 a0) {
    if (func_80161208()) {
        func_80165A20(a0);
    } else if (*(u16 *)((s32)a0 + 0xB8) == 0x8000) {
        func_80154150(a0, 0x27);
        func_80154A74(a0, 0x1F);
        func_801466F0(0xD, a0, 0, -0x40, 0, 0, 0, 0);
        func_80147324(0x6E2);
        func_80146CA0((void *)a0);
    }
}


#include "common.h"

extern s32 func_80161208();
extern s32 func_80165A20(s32 a0);
extern u16 func_80148800(s32 *a0);
extern void func_8012A62C(s32 a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 D_80078EC8;

void func_800CB1A0(s32 a0) {
    if (func_80161208(a0) != 0) {
        func_80165A20(a0);
        return;
    }
    if ((func_80148800(a0) & 0x20) != 0 || D_80078EC8 == 0) {
        func_8012A62C(0x10);
        func_80165A20(a0);
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        *(u16 *)(a0 + 0x15A) = 1;
    }
}


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_800CB234(void *a0) {
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
    func_801553C0((s32)a0);
    func_80154A74((s32)a0, 0x11);
}


extern u8 D_80078EC1;
extern void (*D_800CC180[])();
extern void func_800CB7FC();

void func_800CB270(int param_1)
{
    if (D_80078EC1 != 24) {
        func_800CB7FC();
    } else {
        D_800CC180[*(u16 *)(param_1 + 2)]();
    }
}


extern s32 func_8014659C(void);
extern void func_8001C2C4(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80146CA0(void *a0);
extern void func_800CB7FC();

extern u8 D_800CC150[];
extern u8 D_800CC298[];

void func_800CB2CC(s32 arg0) {
    s32 s2;
    s32 s0;
    s32 v;
    u16 h;

    s2 = *(s32 *)(arg0 + 0x4C);
    s0 = func_8014659C();
    *(s32 *)(arg0 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C2C4(s0);
        v = *(s32 *)(s2 + 0x20);
        h = *(u16 *)(v + 0x12);
        *(u16 *)(s0 + 0x1A) = 0;
        *(u16 *)(s0 + 0x18) = 0;
        *(u16 *)(s0 + 0x1C) = 0x1000;
        *(u16 *)(s0 + 0x12) = h;
        func_80146E90((s32 *)arg0, 0x20);
        func_80149374(s2, arg0 + 4);
        *(u32 *)(arg0 + 0x58) = (u32)&D_800CC150[0];
        *(u16 *)(arg0 + 0x60) = 0;
        *(u16 *)(arg0 + 0x62) = 0;
        *(u16 *)(arg0 + 0x64) = 0;
        func_801466B4(0x28, arg0, 0, 0, 1);
        func_801466B4(0x28, arg0, 1, 0, 1);
        memcpy(&D_800CC298[0], (void *)(s2 + 0x154), 8);
        func_80146CA0((void *)arg0);
    } else {
        func_800CB7FC(arg0);
    }
}


extern void func_800CB82C(s32 a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80146D90(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB3E0(s32 a0) {
    u8 *s0;
    u16 w;

    s0 = *(u8 **)(a0 + 0x20);
    func_800CB82C(a0, *(s32 *)(a0 + 0x58));

    *(u16 *)(a0 + 0xA) -= 1;

    w = *(u16 *)(s0 + 0x18);
    w += 0x100;
    *(u16 *)(s0 + 0x18) = w;
    if ((s16)w >= 0x1CCD) {
        *(u16 *)(s0 + 0x18) = 0x1CCC;
    }

    w = *(u16 *)(s0 + 0x1A);
    w += 0x100;
    *(u16 *)(s0 + 0x1A) = w;
    if ((s16)w >= 0x1CCD) {
        *(u16 *)(s0 + 0x1A) = 0x1CCC;
    }

    if (func_80146E98(a0) != 0) {
        *(u16 *)(s0 + 0x18) = 0x1CCC;
        *(u16 *)(s0 + 0x1A) = 0x1CCC;
        func_80146D90(a0);
        func_80146CA0((void *)a0);
    }
}


extern s32 D_80078EC8;
extern void func_800CB82C(s32 a0, s32 a1);
extern s32 func_801488A8(s32 a0);
extern void func_80146D90(s32 a0);
extern s32 func_80148D44(s32 a0);
extern void func_80162FF4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_800134FC(s32 a0, void *a1, void *a2);
extern void func_8001599C(void *a0, void *a1);
extern void func_80162FC0(s32 a0);
extern void func_800CBCB4(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern s16 currentLocationId;
extern u8 D_800CC298[];
extern s16 D_800CC29A;
extern s16 D_800CC29C;

typedef struct { s32 w[4]; } CB4A4_V4;

void func_800CB4A4(s32 a0) {
    u8 *ap;
    s32 s1;
    s32 s3;
    s32 *s2;
    s32 v0;
    s32 d;
    s32 flag;
    CB4A4_V4 bak[2];
    s16 *dig;

    s1 = a0;
    s3 = *(s32 *)(s1 + 0x4C);
    ap = *(u8 **)(s1 + 0x20);
    if (D_80078EC8 < 0x28) {
        *(u16 *)(ap + 0x18) = *(u16 *)(ap + 0x18) - 0x40;
        *(u16 *)(ap + 0x1A) = *(u16 *)(ap + 0x1A) - 0x40;
    }
    func_800CB82C(s1, *(s32 *)(s1 + 0x58));
    if (func_801488A8(s3) != 0) {
        bak[1] = *(CB4A4_V4 *)(s1 + 0x10);
        func_80146D90(s1);
        *(s32 *)(s1 + 0x18) = 0;
        *(s32 *)(s1 + 0x14) = 0;
        v0 = func_80148D44((*(s32 *)(s1 + 0x10) = 0, s1));
        *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) = v0;
        func_80162FF4(s1, 0, 0, 0xFFFE4000);
        s2 = (s32 *)(s1 + 0x10);
        if (currentLocationId == 0x3038) {
            bak[0] = *(CB4A4_V4 *)s2;
            func_800134FC(0x400, &bak[0], &bak[0]);
            func_8001599C(&bak[0], s2);
        }
        *(s32 *)(s1 + 0x10) += bak[1].w[0];
        *(s32 *)(s1 + 0x14) += bak[1].w[1];
        *(s32 *)(s1 + 0x18) += bak[1].w[2];
        if (*(s32 *)(s1 + 0x10) > 0xE0000) {
            *(s32 *)(s1 + 0x10) = 0xE0000;
        } else if (*(s32 *)(s1 + 0x10) < -0xE0000) {
            *(s32 *)(s1 + 0x10) = -0xE0000;
        }
        if (*(s32 *)(s1 + 0x14) > 0xE0000) {
            *(s32 *)(s1 + 0x14) = 0xE0000;
        } else if (*(s32 *)(s1 + 0x14) < -0xE0000) {
            *(s32 *)(s1 + 0x14) = -0xE0000;
        }
        if (*(s32 *)(s1 + 0x18) > 0xE0000) {
            *(s32 *)(s1 + 0x18) = 0xE0000;
        } else if (*(s32 *)(s1 + 0x18) < -0xE0000) {
            *(s32 *)(s1 + 0x18) = -0xE0000;
        }
    } else {
        flag = 0;
        if (*(s32 *)(s1 + 0x10) != 0) {
            flag = 1;
            if (*(s32 *)(s1 + 0x10) >= 0) {
                d = *(s32 *)(s1 + 0x10) - 0x8000;
                *(s32 *)(s1 + 0x10) = d;
                if (d < 0) {
                    *(s32 *)(s1 + 0x10) = 0;
                }
            } else {
                d = *(s32 *)(s1 + 0x10) + 0x8000;
                *(s32 *)(s1 + 0x10) = d;
                if (d >= 0) {
                    *(s32 *)(s1 + 0x10) = 0;
                }
            }
        }
        if (*(s32 *)(s1 + 0x14) != 0) {
            flag = 1;
            if (*(s32 *)(s1 + 0x14) >= 0) {
                d = *(s32 *)(s1 + 0x14) - 0x8000;
                *(s32 *)(s1 + 0x14) = d;
                if (d < 0) {
                    *(s32 *)(s1 + 0x14) = 0;
                }
            } else {
                d = *(s32 *)(s1 + 0x14) + 0x8000;
                *(s32 *)(s1 + 0x14) = d;
                if (d >= 0) {
                    *(s32 *)(s1 + 0x14) = 0;
                }
            }
        }
        if (*(s32 *)(s1 + 0x18) != 0) {
            flag = 1;
            if (*(s32 *)(s1 + 0x18) >= 0) {
                d = *(s32 *)(s1 + 0x18) - 0x8000;
                *(s32 *)(s1 + 0x18) = d;
                if (d < 0) {
                    *(s32 *)(s1 + 0x18) = 0;
                }
            } else {
                d = *(s32 *)(s1 + 0x18) + 0x8000;
                *(s32 *)(s1 + 0x18) = d;
                if (d >= 0) {
                    *(s32 *)(s1 + 0x18) = 0;
                }
            }
        }
        if (flag == 0) {
            goto tail;
        }
    }
    func_80162FC0(s1);
tail:
    func_800CBCB4((void *)s1);
    dig = (s16 *)D_800CC298;
    v0 = func_80012F74(dig[0], *(s16 *)(s1 + 6), 0xA, 1);
    dig[0] = v0;
    v0 = func_80012F74(D_800CC29A, *(s16 *)(s1 + 0xA), 0xA, 1);
    D_800CC29A = v0;
    v0 = func_80012F74(D_800CC29C, *(s16 *)(s1 + 0xE), 0xA, 1);
    D_800CC29C = v0;
    memcpy((void *)(s3 + 0x154), &D_800CC298[0], 8);
}


extern void func_801662F4(void);
extern void func_80162CCC(void);
void func_800CB7FC(s32 a0) {
    func_801662F4();
    ((void (*)(s32))func_80162CCC)(a0);
}








extern void func_80015978(s32, s32 *);
extern s32 func_8012EF34(s32, s32);
extern s32 func_80017DC4(void *, void *);
extern void func_800CBA44();
extern void func_800CBBF8();
extern s32 func_80047948(s32);

extern u8 D_800CC290[];
extern u8 D_800CC190[];
extern u8 D_800CC1C0[];
extern u8 D_800CC1B0[];
extern u8 D_800CC1A0[];

typedef struct { u32 a, b; } __attribute__((packed, aligned(1))) Blk8;

struct Mid { u32 gray[4]; u32 code; u8 bmode; };
typedef struct {
    u8 mat[0x14];
    u32 zz[3] __attribute__((aligned(4)));
} __attribute__((packed)) MZ;
typedef struct {
    u16 hB0;
    u16 hB2;
    u32 hpad;
} HB;

#define gte_SetRotMatrix(r0) __asm__ volatile (   \
    "lw $12, 0( %0 );"                            \
    "lw $13, 4( %0 );"                            \
    "ctc2 $12, $0;"                               \
    "ctc2 $13, $1;"                               \
    "lw $12, 8( %0 );"                            \
    "lw $13, 12( %0 );"                           \
    "lw $14, 16( %0 );"                           \
    "ctc2 $12, $2;"                               \
    "ctc2 $13, $3;"                               \
    "ctc2 $14, $4"                                \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "$13", "$14", "memory" )
#define gte_SetTransMatrix(r0) __asm__ volatile ( \
    "lw $12, 20( %0 );"                           \
    "lw $13, 24( %0 );"                           \
    "ctc2 $12, $5;"                               \
    "lw $14, 28( %0 );"                           \
    "ctc2 $13, $6;"                               \
    "ctc2 $14, $7"                                \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "$13", "$14", "memory" )

void func_800CB82C(s32 a0, s32 a1)
{
    u8 lo[0x30];
    volatile struct Mid mid;
    u8 src[8];
    u8 dstc[8];
    u8 out1[0x20];
    MZ mz;
    HB hb;
    volatile u8 fpad[8];
    register s32 g8 __asm__("$8");
    register s32 c1 __asm__("$3");
    s32 *p;
    s32 *plo;
    s32 *p6;
    s32 s5v;
    s32 chk;
    s32 w;
    s32 bm;
    s32 cn;

    plo = (s32 *)lo;
    p = *(s32 **)((s8 *)a0 + 0x20);
    func_80015978((s32)((s8 *)a0 + 4), (s32 *)src);
    chk = func_8012EF34((s32)src, (s32)D_800CC290);
    if ((chk & ~0x1000) == 0) {
        *(Blk8 *)dstc = *(Blk8 *)D_800CC290;
        s5v = *(u16 *)((s8 *)a1 + 0x16) + 3;
        func_80017DC4((void *)((s8 *)p + 0x18), (void *)mz.mat);
        p = (s32 *)dstc;
        mz.zz[2] = 0;
        mz.zz[1] = 0;
        mz.zz[0] = 0;
        gte_SetRotMatrix(mz.mat);
        gte_SetTransMatrix(mz.mat);
        p6 = (s32 *)D_800CC1C0;
        w = *(u16 *)(dstc + 4);
        *(u16 *)(out1 + 0x1C) = w;
        *(u16 *)(out1 + 0x14) = w;
        *(u16 *)(out1 + 0xC) = w;
        *(u16 *)(out1 + 4) = w;
        bm = *(u16 *)((s8 *)a1 + 0x14);
        mid.code = 0x50000000;
        mid.bmode = bm;
        c1 = *(s16 *)((s8 *)a0 + 0x60);
        g8 = 0x808080;
        mid.gray[0] = g8;
        mid.gray[1] = g8;
        mid.gray[2] = g8;
        mid.gray[3] = g8;
        cn = (c1 + 1) & 3;
        c1 <<= 2;
        *(u16 *)((s8 *)a0 + 0x60) = cn;
        cn = (s32)D_800CC1B0;
        c1 += cn;
        if (((s32 (*)(s32, s32, s32, s32, s32 *, s32))func_800CBA44)((s32)out1, (s32)D_800CC190, (s32)a1, (s32)p6,
                          plo, c1) != 0) {
            return;
        }
        *(u16 *)((s8 *)lo + 4) = s5v;
        func_800CBBF8(plo, p);
        a1 = (void *)((s8 *)a1 + 0x18);
        hb.hB0 = func_80047948((*(s16 *)((s8 *)a0 + 0x62)) << 8) / 1024;
        *(u16 *)((s8 *)a0 + 0x62) = (*(u16 *)((s8 *)a0 + 0x62) + 1) & 0xF;
        hb.hB2 = 0;
        if (((s32 (*)(s32, s32, s32, s32, s32 *, s32))func_800CBA44)((s32)out1, (s32)D_800CC1A0, (s32)a1, (s32)&hb.hB0,
                          plo, (s32)p6) != 0) {
            return;
        }
        func_800CBBF8(plo, p);
    }
}


void func_800CBA44()
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "lhu    $2, 0($5)\n"
        "lhu    $3, 16($6)\n"
        "addu   $8, $4, $0\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 0($8)\n"
        "lhu    $2, 2($5)\n"
        "lhu    $3, 18($6)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 2($8)\n"
        "lhu    $2, 4($5)\n"
        "lhu    $3, 16($6)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 8($8)\n"
        "lhu    $2, 6($5)\n"
        "lhu    $3, 18($6)\n"
        "addiu  $29, $29, -8\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 10($8)\n"
        "lhu    $3, 8($5)\n"
        "lhu    $4, 16($6)\n"
        "lhu    $2, 0($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 16($8)\n"
        "lhu    $3, 10($5)\n"
        "lhu    $4, 18($6)\n"
        "lhu    $2, 2($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 18($8)\n"
        "lhu    $3, 12($5)\n"
        "lhu    $4, 16($6)\n"
        "lhu    $2, 0($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 24($8)\n"
        "lhu    $3, 14($5)\n"
        "lhu    $4, 18($6)\n"
        "lhu    $2, 2($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "addiu  $3, $8, 8\n"
        "sh     $2, 26($8)\n"
        "addiu  $2, $8, 16\n"
        "lw     $5, 24($29)\n"
        "lw     $4, 28($29)\n"
        "lwc2   $0, 0($8)\n"
        "lwc2   $1, 4($8)\n"
        "lwc2   $2, 0($3)\n"
        "lwc2   $3, 4($3)\n"
        "lwc2   $4, 0($2)\n"
        "lwc2   $5, 4($2)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "addiu  $2, $5, 16\n"
        "addiu  $3, $5, 8\n"
        "swc2   $12, 0($5)\n"
        "swc2   $13, 0($3)\n"
        "swc2   $14, 0($2)\n"
        "cfc2   $12, $31\n"
        "nop\n"
        "sw     $12, 0($29)\n"
        "lw     $2, 0($29)\n"
        "addiu  $3, $0, -4097\n"
        "and    $2, $2, $3\n"
        "bnez   $2, 99f\n"
        " addiu $2, $0, 1\n"
        "addiu  $2, $8, 24\n"
        "lwc2   $0, 0($2)\n"
        "lwc2   $1, 4($2)\n"
        "nop\n"
        "nop\n"
        "rtps\n"
        "addiu  $2, $5, 24\n"
        "swc2   $14, 0($2)\n"
        "cfc2   $12, $31\n"
        "nop\n"
        "sw     $12, 0($29)\n"
        "lw     $2, 0($29)\n"
        "nop\n"
        "and    $2, $2, $3\n"
        "bnez   $2, 99f\n"
        " addiu $2, $0, 1\n"
        "lw     $2, 0($6)\n"
        "lw     $3, 0($4)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sw     $2, 32($5)\n"
        "lw     $2, 4($6)\n"
        "lw     $3, 0($4)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sw     $2, 36($5)\n"
        "lw     $2, 8($6)\n"
        "lw     $3, 0($4)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sw     $2, 40($5)\n"
        "lw     $3, 12($6)\n"
        "lw     $4, 0($4)\n"
        "addu   $2, $0, $0\n"
        "addu   $3, $3, $4\n"
        "sw     $3, 44($5)\n"
        "99:\n"
        "addiu  $29, $29, 8\n"
        ".set\treorder\n"
    );
}


#include "common.h"

extern void func_800178EC(s32 a0);

void func_800CBBF8(s32 *a0, s32 *a1) {
    *(u16 *)((s8 *)a0 + 0x0) += *(u16 *)((s8 *)a1 + 0x0);
    *(u16 *)((s8 *)a0 + 0x2) += *(u16 *)((s8 *)a1 + 0x2);
    *(u16 *)((s8 *)a0 + 0x8) += *(u16 *)((s8 *)a1 + 0x0);
    *(u16 *)((s8 *)a0 + 0xA) += *(u16 *)((s8 *)a1 + 0x2);
    *(u16 *)((s8 *)a0 + 0x10) += *(u16 *)((s8 *)a1 + 0x0);
    *(u16 *)((s8 *)a0 + 0x12) += *(u16 *)((s8 *)a1 + 0x2);
    *(u16 *)((s8 *)a0 + 0x18) += *(u16 *)((s8 *)a1 + 0x0);
    *(u16 *)((s8 *)a0 + 0x1A) += *(u16 *)((s8 *)a1 + 0x2);
    func_800178EC((s32)a0);
}


extern s16 currentLocationId;

void func_800CBCB4(void *a0) {
    s16 sp[4];

    func_80015978((s32)a0 + 4, sp);
    switch (currentLocationId) {
    case 0x3035:
        if (sp[0] < -0x93E) {
            sp[0] = -0x93E;
        }
        if (sp[0] >= -0x3C1) {
            sp[0] = -0x3C2;
        }
        if (sp[2] < 0x3C2) {
            sp[2] = 0x3C2;
        }
        if (sp[2] >= 0xCBF) {
            sp[2] = 0xCBE;
            goto after;
        }
        break;
    case 0x3037:
        if (sp[0] < 0x4C2) {
            sp[0] = 0x4C2;
        }
        if (sp[0] >= 0xA3F) {
            sp[0] = 0xA3E;
        }
        if (sp[2] < 0xAC2) {
            sp[2] = 0xAC2;
        }
        if (sp[2] >= 0x13BF) {
            sp[2] = 0x13BE;
            goto after;
        }
        break;
    case 0x3038:
        if (sp[0] < -0xF3E) {
            sp[0] = -0xF3E;
        }
        if (sp[0] >= -0x9C1) {
            sp[0] = -0x9C2;
        }
        if (sp[1] < -0xA00) {
            sp[1] = -0xA00;
        }
        if (sp[1] >= -0x201) {
            sp[1] = -0x202;
            goto after;
        }
        break;
    case 0x3039:
        if (sp[0] < -0x153E) {
            sp[0] = -0x153E;
        }
        if (sp[0] >= -0xFC1) {
            sp[0] = -0xFC2;
        }
        if (sp[2] < 0x3C2) {
            sp[2] = 0x3C2;
        }
        if (sp[2] >= 0xFBF) {
            sp[2] = 0xFBE;
        }
        break;
    }
after:
    func_80015954(sp, (s32)a0 + 4);
}


extern u8 D_80078EC1;
extern void (*D_800CC1C4[])();
extern void func_800CC004();

void func_800CBECC(int param_1)
{
    if (D_80078EC1 != 24) {
        func_800CC004();
    } else {
        D_800CC1C4[*(u16 *)(param_1 + 2)]();
    }
}


extern u32 D_800CC250;
extern u32 D_800CC254;
extern s32 func_80146578(void);
extern void func_8001CD04(s32, s32);
extern void func_800233CC(s32, s32);
extern void func_800CC024();

void func_800CBF28(s32 p1)
{
    s32 v0;
    s32 r;
    register s32 base __asm__("$17");  /* $s1 */

    v0 = ((s32 (*)(void))func_80146578)();
    base = (s32)&D_800CC250;
    __asm__("" : "=r"(r) : "0"(v0));
    *(s32 *)(p1 + 0x20) = v0;
    if (v0 != 0) {
        func_8001CD04(v0, base);
        if (*(s32 *)(p1 + 0x50) == 0) {
            func_800233CC(base, 0x20);
            D_800CC254 = 0;
            *(u32 *)base = 0x202000;
        }
        *(s16 *)(p1 + 0x60) = 0;
        *(u32 *)(r + 4) |= 0x50000000;
        func_800CC024(p1);
        func_80146CA0((void *)p1);
    } else {
        func_800CC004(p1);
    }
}


extern void func_800CC024(void);
void func_800CBFE4(void) {
    func_800CC024();
}


extern void func_80162CCC(void);
void func_800CC004(void) {
    func_80162CCC();
}


extern void func_80015954(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_800CC024() {
    extern u8 D_800CC290[];
    s32 s2;
    s32 s3;
    s32 m;
    s32 ang;
    s32 r;
    s16 d[2];
    u16 v;
    u16 t;
    s32 obj;

    {
        register s32 a0p __asm__("$4");
        obj = a0p;
    }

    s2 = *(s32 *)(obj + 0x4C);
    s3 = *(s32 *)(obj + 0x20);
    if (s2 == 0) {
        return;
    }

    func_80015954((s32)D_800CC290, obj + 4);

    v = *(u16 *)(obj + 0x60);
    m = v & 0x1F;
    ang = ((m << 8) & 0x7F00) >> 1;
    t = *(u16 *)(obj + 0xA);
    __asm__("" :: "r"(m), "r"(ang));
    *(u16 *)(obj + 0xA) = t - 0x10;
    *(u16 *)(obj + 0x60) = v + 1;

    if (*(s32 *)(obj + 0x50) == 0) {
        r = func_80047948(m << 7);
    } else {
        r = 0x1000 - func_80047948(m << 7);
    }
    d[0] = r / 1024;
    d[1] = func_8004787C(ang) / 512;

    *(u16 *)(obj + 6) += d[0];
    *(u16 *)(obj + 0xA) += d[1];
    *(s32 *)(s3 + 0x18) = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x18);
}

