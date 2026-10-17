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
    ((Unkstruct_800CAE34 *)a0)->unk44 |= 8;
    D_800CC134[((Unkstruct_800CAE34 *)a0)->unk197]();
}


extern void func_800CAEC0(s32 a0);
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
    ((Unkstruct_80126B58 *)a0)->unk197 += 1;
}


void func_800CAF18(void) {
}

void func_800CAF20(void) {
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFEC();  // K&R: 0 of 1 args (P37 rung D t4_D35)
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
    D_800CC140[((Unkstruct_80126B58 *)a0)->unk2]();
}


extern void func_800CAFEC();  // K&R: 0 of 1 args (P37 rung D t4_D35)
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
    void *a;
    if (func_80161208(arg0) != 0) {
        func_80165A20(arg0);
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x238) += 0x1c000;
    p = *(s32 *)((u8 *)arg0 + 0x20);
    ((Unkstruct_800CB06C *)p)->unk10 =
        (((Unkstruct_800CB06C *)p)->unk10 - *(u16 *)((u8 *)arg0 + 0x23a)) & 0xfff;
    q = *(s32 *)((u8 *)arg0 + 0x20);
    if (CAST_SIGN(s16, (u8 *)q, 0x10) < 0xc00) {
        a = arg0;
        ((Unkstruct_800CB06C *)q)->unk10 = 0xc00;
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
    } else if (((Unkstruct_80126B58 *)a0)->unkB8 == 0x8000) {
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
        ((Unkstruct_80126B58 *)a0)->unk15A = 1;
    }
}


extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_800CB234(void *a0) {
    *(u16 *)(((Unkstruct_80126B58 *)a0)->unk20 + 0x10) = 0;
    func_801553C0((s32)a0);
    func_80154A74((s32)a0, 0x11);
}


extern u8 D_80078EC1;
extern void (*D_800CC180[])();
extern void func_800CB7FC();  // K&R: 0/1 of 1 args (P37 rung D t4_D35)

void func_800CB270(int param_1)
{
    if (D_80078EC1 != 24) {
        func_800CB7FC();
    } else {
        D_800CC180[((Unkstruct_800CB270 *)param_1)->unk2]();
    }
}


extern s32 func_8014659C(void);
extern void func_8001C2C4(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80146CA0(void *a0);
extern void func_800CB7FC();  // K&R: 0/1 of 1 args (P37 rung D t4_D35)

extern u8 D_800CC150[];
extern u8 D_800CC298[];

void func_800CB2CC(s32 arg0) {
    s32 s2;
    s32 s0;
    s32 v;
    u16 h;

    s2 = *(s32 *)(arg0 + 0x4C);
    s0 = func_8014659C();
    ((Unkstruct_80126B58 *)arg0)->unk20 = s0;
    if (s0 != 0) {
        func_8001C2C4(s0);
        v = ((Unkstruct_80126B58 *)s2)->unk20;
        h = *(u16 *)(v + 0x12);
        *(u16 *)(s0 + 0x1A) = 0;
        *(u16 *)(s0 + 0x18) = 0;
        *(u16 *)(s0 + 0x1C) = 0x1000;
        *(u16 *)(s0 + 0x12) = h;
        func_80146E90((s32 *)arg0, 0x20);
        func_80149374(s2, arg0 + 4);
        ((Unkstruct_80126B58 *)arg0)->unk58 = (u32)&D_800CC150[0];
        ((Unkstruct_80126B58 *)arg0)->unk60 = 0;
        ((Unkstruct_80126B58 *)arg0)->unk62 = 0;
        ((Unkstruct_80126B58 *)arg0)->unk64 = 0;
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

    s0 = CAST_SIGN(u8 *, a0, 0x20);
    func_800CB82C(a0, ((Unkstruct_80126B58 *)a0)->unk58);

    CAST_SIGN(u16, a0, 0xA) -= 1;

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
    s3 = ((Unkstruct_800CB4A4 *)s1)->unk4C;
    ap = *(u8 **)(s1 + 0x20);
    if (D_80078EC8 < 0x28) {
        ((Unkstruct_800CB4A4_2 *)ap)->unk18 = ((Unkstruct_800CB4A4_2 *)ap)->unk18 - 0x40;
        ((Unkstruct_800CB4A4_2 *)ap)->unk1A = ((Unkstruct_800CB4A4_2 *)ap)->unk1A - 0x40;
    }
    func_800CB82C(s1, ((Unkstruct_800CB4A4 *)s1)->unk58);
    if (func_801488A8(s3) != 0) {
        bak[1] = CAST_WIDTH(CB4A4_V4, s1, 0x10);
        func_80146D90(s1);
        ((Unkstruct_800CB4A4 *)s1)->unk18 = 0;
        ((Unkstruct_800CB4A4 *)s1)->unk14 = 0;
        v0 = func_80148D44((((Unkstruct_800CB4A4 *)s1)->unk10 = 0, s1));
        ((Unkstruct_800CB4A4_2 *)*(s32 *)(s1 + 0x20))->unk12 = v0;
        func_80162FF4(s1, 0, 0, 0xFFFE4000);
        s2 = (s32 *)(s1 + 0x10);
        if (currentLocationId == 0x3038) {
            bak[0] = *(CB4A4_V4 *)s2;
            func_800134FC(0x400, &bak[0], &bak[0]);
            func_8001599C(&bak[0], s2);
        }
        ((Unkstruct_800CB4A4 *)s1)->unk10 += bak[1].w[0];
        ((Unkstruct_800CB4A4 *)s1)->unk14 += bak[1].w[1];
        ((Unkstruct_800CB4A4 *)s1)->unk18 += bak[1].w[2];
        if (((Unkstruct_800CB4A4 *)s1)->unk10 > 0xE0000) {
            ((Unkstruct_800CB4A4 *)s1)->unk10 = 0xE0000;
        } else if (((Unkstruct_800CB4A4 *)s1)->unk10 < -0xE0000) {
            ((Unkstruct_800CB4A4 *)s1)->unk10 = -0xE0000;
        }
        if (((Unkstruct_800CB4A4 *)s1)->unk14 > 0xE0000) {
            ((Unkstruct_800CB4A4 *)s1)->unk14 = 0xE0000;
        } else if (((Unkstruct_800CB4A4 *)s1)->unk14 < -0xE0000) {
            ((Unkstruct_800CB4A4 *)s1)->unk14 = -0xE0000;
        }
        if (((Unkstruct_800CB4A4 *)s1)->unk18 > 0xE0000) {
            ((Unkstruct_800CB4A4 *)s1)->unk18 = 0xE0000;
        } else if (((Unkstruct_800CB4A4 *)s1)->unk18 < -0xE0000) {
            ((Unkstruct_800CB4A4 *)s1)->unk18 = -0xE0000;
        }
    } else {
        flag = 0;
        if (((Unkstruct_800CB4A4 *)s1)->unk10 != 0) {
            flag = 1;
            if (((Unkstruct_800CB4A4 *)s1)->unk10 >= 0) {
                d = ((Unkstruct_800CB4A4 *)s1)->unk10 - 0x8000;
                ((Unkstruct_800CB4A4 *)s1)->unk10 = d;
                if (d < 0) {
                    ((Unkstruct_800CB4A4 *)s1)->unk10 = 0;
                }
            } else {
                d = ((Unkstruct_800CB4A4 *)s1)->unk10 + 0x8000;
                ((Unkstruct_800CB4A4 *)s1)->unk10 = d;
                if (d >= 0) {
                    ((Unkstruct_800CB4A4 *)s1)->unk10 = 0;
                }
            }
        }
        if (((Unkstruct_800CB4A4 *)s1)->unk14 != 0) {
            flag = 1;
            if (((Unkstruct_800CB4A4 *)s1)->unk14 >= 0) {
                d = ((Unkstruct_800CB4A4 *)s1)->unk14 - 0x8000;
                ((Unkstruct_800CB4A4 *)s1)->unk14 = d;
                if (d < 0) {
                    ((Unkstruct_800CB4A4 *)s1)->unk14 = 0;
                }
            } else {
                d = ((Unkstruct_800CB4A4 *)s1)->unk14 + 0x8000;
                ((Unkstruct_800CB4A4 *)s1)->unk14 = d;
                if (d >= 0) {
                    ((Unkstruct_800CB4A4 *)s1)->unk14 = 0;
                }
            }
        }
        if (((Unkstruct_800CB4A4 *)s1)->unk18 != 0) {
            flag = 1;
            if (((Unkstruct_800CB4A4 *)s1)->unk18 >= 0) {
                d = ((Unkstruct_800CB4A4 *)s1)->unk18 - 0x8000;
                ((Unkstruct_800CB4A4 *)s1)->unk18 = d;
                if (d < 0) {
                    ((Unkstruct_800CB4A4 *)s1)->unk18 = 0;
                }
            } else {
                d = ((Unkstruct_800CB4A4 *)s1)->unk18 + 0x8000;
                ((Unkstruct_800CB4A4 *)s1)->unk18 = d;
                if (d >= 0) {
                    ((Unkstruct_800CB4A4 *)s1)->unk18 = 0;
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
    v0 = func_80012F74(dig[0], ((Unkstruct_800CB4A4 *)s1)->unk6, 0xA, 1);
    dig[0] = v0;
    v0 = func_80012F74(D_800CC29A, ((Unkstruct_800CB4A4 *)s1)->unkA, 0xA, 1);
    D_800CC29A = v0;
    v0 = func_80012F74(D_800CC29C, CAST_ALIAS(s16, s1, 0xE), 0xA, 1);
    D_800CC29C = v0;
    memcpy((void *)(s3 + 0x154), &D_800CC298[0], 8);
}


extern void func_801662F4();  // K&R: 0 of 1 args (P37 rung D t4_D58)
extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D41)
void func_800CB7FC(s32 a0) {
    func_801662F4();
    ((void (*)(s32))func_80162CCC)(a0);
}








extern void func_80015978(s32, s32 *);
extern s32 func_8012EF34(s32, s32);
extern s32 func_80017DC4(void *, void *);
extern s32 func_800CBA44();
extern void func_800CBBF8(s32 *a0, s32 *a1);
extern s32 func_80047948(s32);

extern u8 D_800CC290[];
extern u8 D_800CC190[];
extern u8 D_800CC1C0[];
extern u8 D_800CC1B0[];
extern u8 D_800CC1A0[];




void func_800CB82C(s32 a0, s32 a1)
{
    u8 lo[0x30];
    struct Mid mid;
    u8 src[8];
    u8 dstc[8];
    u8 out1[0x20];
    MZ mz;
    HB hb;
    u8 fpad[8];
    s32 g8;
    s32 c1;
    s32 *p;
    s32 *plo;
    s32 *p6;
    s32 s5v;
    s32 chk;
    s32 w;
    s32 bm;
    s32 cn;

    plo = (s32 *)lo;
    p = CAST_SIGN(s32 *, (s8 *)a0, 0x20);
    func_80015978((s32)((s8 *)a0 + 4), (s32 *)src);
    chk = func_8012EF34((s32)src, (s32)D_800CC290);
    if ((chk & ~0x1000) == 0) {
        *(Blk8_md_MAIN_027 *)dstc = *(Blk8_md_MAIN_027 *)D_800CC290;
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
        c1 = CAST_SIGN(s16, (s8 *)a0, 0x60);
        g8 = 0x808080;
        mid.gray[0] = g8;
        mid.gray[1] = g8;
        mid.gray[2] = g8;
        mid.gray[3] = g8;
        cn = (c1 + 1) & 3;
        c1 <<= 2;
        ((Unkstruct_80126B58 *)a0)->unk60 = cn;
        cn = (s32)D_800CC1B0;
        c1 += cn;
        if (((s32 (*)(s32, s32, s32, s32, s32 *, s32))func_800CBA44)((s32)out1, (s32)D_800CC190, (s32)a1, (s32)p6,
                          plo, c1) != 0) {
            return;
        }
        *(u16 *)((s8 *)lo + 4) = s5v;
        func_800CBBF8(plo, p);
        a1 = (void *)((s8 *)a1 + 0x18);
        hb.hB0 = func_80047948((CAST_SIGN(s16, (s8 *)a0, 0x62)) << 8) / 1024;
        ((Unkstruct_80126B58 *)a0)->unk62 = (((Unkstruct_80126B58 *)a0)->unk62 + 1) & 0xF;
        hb.hB2 = 0;
        if (((s32 (*)(s32, s32, s32, s32, s32 *, s32))func_800CBA44)((s32)out1, (s32)D_800CC1A0, (s32)a1, (s32)&hb.hB0,
                          plo, (s32)p6) != 0) {
            return;
        }
        func_800CBBF8(plo, p);
    }
}


typedef struct { s16 vx, vy, vz, pad; } SV_CBA44_t;
typedef struct { s16 vx, vy; } P2_CBA44_t;
typedef struct { s32 w[4]; P2_CBA44_t o; } Base_CBA44_t;

s32 func_800CBA44(SV_CBA44_t *out, P2_CBA44_t *in, Base_CBA44_t *b, P2_CBA44_t *off, s32 *res, s32 *d)
{
    long flag;

    out[0].vx = in[0].vx + b->o.vx;
    out[0].vy = in[0].vy + b->o.vy;
    out[1].vx = in[1].vx + b->o.vx;
    out[1].vy = in[1].vy + b->o.vy;
    out[2].vx = off->vx + (in[2].vx + b->o.vx);
    out[2].vy = off->vy + (in[2].vy + b->o.vy);
    out[3].vx = off->vx + (in[3].vx + b->o.vx);
    out[3].vy = off->vy + (in[3].vy + b->o.vy);
    gte_ldv3(&out[0], &out[1], &out[2]);
    gte_rtpt();
    gte_stsxy3(res, res + 2, res + 4);
    gte_stflg(&flag);
    if (flag & ~0x1000)
        return 1;
    gte_ldv0(&out[3]);
    gte_rtps();
    gte_stsxy(res + 6);
    gte_stflg(&flag);
    if (flag & ~0x1000)
        return 1;
    res[8] = b->w[0] + *d;
    res[9] = b->w[1] + *d;
    res[10] = b->w[2] + *d;
    res[11] = b->w[3] + *d;
    return 0;
}


#include "common.h"

extern void func_800178EC(s32 a0);

void func_800CBBF8(s32 *a0, s32 *a1) {
    ((Unkstruct_800CB82C *)a0)->unk0 += ((Unkstruct_800CBBF8 *)a1)->unk0;
    ((Unkstruct_800CB82C *)a0)->unk2 += ((Unkstruct_800CBBF8 *)a1)->unk2;
    ((Unkstruct_800CB82C *)a0)->unk8 += ((Unkstruct_800CBBF8 *)a1)->unk0;
    ((Unkstruct_800CB82C *)a0)->unkA += ((Unkstruct_800CBBF8 *)a1)->unk2;
    ((Unkstruct_800CB82C *)a0)->unk10 += ((Unkstruct_800CBBF8 *)a1)->unk0;
    ((Unkstruct_800CB82C *)a0)->unk12 += ((Unkstruct_800CBBF8 *)a1)->unk2;
    ((Unkstruct_800CB82C *)a0)->unk18 += ((Unkstruct_800CBBF8 *)a1)->unk0;
    ((Unkstruct_800CB82C *)a0)->unk1A += ((Unkstruct_800CBBF8 *)a1)->unk2;
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
        D_800CC1C4[((Unkstruct_800CB270 *)param_1)->unk2]();
    }
}


extern u32 D_800CC250;
extern u32 D_800CC254;
extern s32 func_80146578(void);
extern void func_8001CD04(s32, s32);
extern void func_800233CC(s32, s32);
extern void func_800CC024(s32 a0p);

void func_800CBF28(s32 p1)
{
    s32 v0;
    s32 r;
    s32 base;  /* $s1 */

    base = (s32)&D_800CC250;
    v0 = ((s32 (*)(void))func_80146578)();
    r = v0;
    ((Unkstruct_80126B58 *)p1)->unk20 = v0;
    if (v0 != 0) {
        func_8001CD04(v0, base);
        if (((Unkstruct_80126B58 *)p1)->unk50 == 0) {
            func_800233CC(base, 0x20);
            D_800CC254 = 0;
            *(u32 *)base = 0x202000;
        }
        ((Unkstruct_80126B58 *)p1)->unk60 = 0;
        *(u32 *)(r + 4) |= 0x50000000;
        func_800CC024(p1);
        func_80146CA0((void *)p1);
    } else {
        func_800CC004(p1);
    }
}


extern void func_800CC024(s32 a0p);
void func_800CBFE4(s32 a0) {
    func_800CC024(a0);
}


extern void func_80162CCC();  // K&R: 0 of 1 args (P37 rung D t4_D41)
void func_800CC004(void) {
    func_80162CCC();
}


extern void func_80015954(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_800CC024(s32 a0p) {
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
        obj = a0p;
    }

    s2 = ((Unkstruct_800CC024 *)obj)->unk4C;
    s3 = ((Unkstruct_800CC024 *)obj)->unk20;
    if (s2 == 0) {
        return;
    }

    func_80015954((s32)D_800CC290, obj + 4);

    v = ((Unkstruct_800CC024 *)obj)->unk60;
    m = v & 0x1F;
    ang = ((m << 8) & 0x7F00) >> 1;
    t = ((Unkstruct_800CC024 *)obj)->unkA;
    __asm__("" :: "r"(m), "r"(ang));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)
    ((Unkstruct_800CC024 *)obj)->unkA = t - 0x10;
    ((Unkstruct_800CC024 *)obj)->unk60 = v + 1;

    if (((Unkstruct_800CC024 *)obj)->unk50 == 0) {
        r = func_80047948(m << 7);
    } else {
        r = 0x1000 - func_80047948(m << 7);
    }
    d[0] = r / 1024;
    d[1] = func_8004787C(ang) / 512;

    ((Unkstruct_800CC024 *)obj)->unk6 += d[0];
    ((Unkstruct_800CC024 *)obj)->unkA += d[1];
    *(s32 *)(s3 + 0x18) = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x18);
}

