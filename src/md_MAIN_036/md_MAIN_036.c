#include "common.h"

INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CAE0C);



void func_800CAE54(void *a0) {

    extern void (*D_800CBF94[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBF94[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEE0(u8 *a0);
void func_800CAE98(u8 *a0) {
    if (func_80161104()) {
        func_800CAEE0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


extern s32 func_8014C088(s32 a0, s32 a1);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_801655E4(s32 a0);
extern void func_80165958(void);

void func_800CAEE0(u8* a0)
{
    s32 v0 = func_8014C088((s32)a0, 0x22);

    if (v0 != 0) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        func_801655E4((s32)a0);
        func_80165958();
        *((u8 *)a0 + 0x197) += 1;
    }
}


extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CAF4C(void *a0) {
    func_801466F0(0x22, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x22, (s32)a0, 0, 0, 0, 1, 0, 0);
    func_801599A4(a0);
    func_80159B3C(a0);
}


void func_800CAFCC(void) {
}


extern void func_800CB5A8(void);

void func_800CAFD4(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBFB8[])(void);
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBFB8[v0]();
    } else {
        func_800CB5A8();
    }
}


void func_800CB030(s32 param_1) {
    extern void func_8014659C(void);
    extern void func_8001CA1C(void *a0, void *a1);
    extern void func_80149374(s32 a0, s32 a1);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern s32 func_80146CA0(void *a0);
    extern void func_800CB5A8(void);
    extern u8 D_800CBFA0[];
    extern s32 D_800CC12C;
    extern void (*D_800CC130[])(void);
    s32 obj;
    s32 p;

    obj = *(s32 *)(param_1 + 0x4C);
    p = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = p;

    if (p != 0) {
        func_8001CA1C((void *)p, (void *)((s32)&D_800CBFA0 + *(s32 *)(param_1 + 0x50) * 12));
        *(u32 *)(p + 4) |= 0x08000000;
        func_80149374(obj, param_1 + 4);
        *(u16 *)(param_1 + 0x60) = *(u16 *)(param_1 + 0xA);
        *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x200;
        *(s32 *)(param_1 + 0x58) = 0;
        if (*(s32 *)(param_1 + 0x50) == 0) {
            func_80146E90((s32 *)param_1, 0);
            D_800CC130[0] = 0;
        }
        *(u16 *)(param_1 + 0x62) = 0;
        D_800CC12C = 0x384;
        func_80146CA0((void *)param_1);
    } else {
        ((void (*)(s32))func_800CB5A8)(param_1);
    }
}


extern void func_80147324(s32 a0);
extern s32 func_80146CA0(void *a0);

void func_800CB11C(u8 *arg0) {
    u8 *s1;
    s32 var;
    s16 cur;
    s16 max;
    u16 val;
    s16 temp;

    s1 = *(u8 **)(arg0 + 0x20);
    var = *(s32 *)(arg0 + 0x58) + 0x30000;
    *(s32 *)(arg0 + 0x58) = var;
    *(s32 *)(arg0 + 8) += var;

    cur = *(s16 *)(arg0 + 0x60);
    max = *(s16 *)(arg0 + 0xA);
    if (cur < max) {
        *(s16 *)(arg0 + 0xA) = cur;
        if (*(s16 *)(arg0 + 0x62) == 0) {
            *(s16 *)(arg0 + 0x62) = *(s16 *)(arg0 + 0x62) + 1;
            func_80147324(0x8EC);
        }

        val = *(u16 *)(s1 + 0x1A);
        val -= 0x100;
        *(u16 *)(s1 + 0x1A) = val;

        temp = (s16)val;
        if (temp < 0xC00) {
            func_80146CA0(arg0);
        }
    }
}


extern s32 func_80146CA0(void *a0);

void func_800CB1CC(void *arg0) {
    s32 v1 = *(s32 *)((s32)arg0 + 0x20);
    s16 v = *(u16 *)(v1 + 0x1A) + 0x100;
    *(u16 *)(v1 + 0x1A) = v;
    if (v >= 0x1000) {
        *(u16 *)(v1 + 0x1A) = 0x1000;
        func_80146CA0(arg0);
    }
}


extern s32 D_800CC12C;
extern s32 D_800CC130;
extern s16 D_800CC134;
extern s16 D_800CC136;
extern s16 D_800CC138;
extern u16 D_800B99DA;
extern s32 D_80126B58[];
extern s32 func_8004787C(s32);
extern s32 func_80012DBC(s32, s32, s32, s32);
extern u16 func_80148800(s32 *);
extern s32 func_80146E98(s32);
extern void func_80146E90(s32 *, s32);
extern void func_80147324(s32);
extern s32 func_80146CA0(void *);
extern int rand(void);

void func_800CB218(void *arg0) {
    s32 cnt;
    s32 mode;
    void *s1;
    s16 *evt;

    cnt = D_800CC12C;
    mode = D_800CC130;
    s1 = *(void **)((s32)arg0 + 0x20);
    D_800CC12C = cnt - 1;

    switch (mode) {
    case 0:
        *(s16 *)((s32)arg0 + 0x60) = (func_8004787C((D_800B99DA & 0x3F) << 6)) / 64;
        break;
    case 1:
        *(s16 *)((s32)arg0 + 0x60) = (func_8004787C((D_800B99DA & 0x1F) << 7)) / 32;
        break;
    }

    *(s16 *)((s32)s1 + 0x14) = func_80012DBC(*(s16 *)((s32)s1 + 0x14), *(s16 *)((s32)arg0 + 0x60), 10, 1);

    if (*(s32 *)((s32)arg0 + 0x50) == 0) {
        if (func_80146E98((s32)arg0) != 0) {
            func_80146E90((s32 *)arg0, (rand() & 0x3F) + 0x20);
            D_800CC130 = rand() & 1;
        }
    }

    if (D_800CC12C < 0x80 || (func_80148800(D_80126B58) & 0x20)) {
        evt = &D_800CC134;
        *(s32 *)((s32)s1 + 0x80) = (s32)evt;
        *(u16 *)((s32)s1 + 0x2C) |= 0x80;
        D_800CC138 = 0x80;
        D_800CC136 = 0x80;
        *evt = 0x80;
        func_80146E90((s32 *)arg0, 0);
        func_80147324(0x8ED);
        func_80146CA0(arg0);
    }
}


void func_800CB3B4(void *arg0) {
    extern s32 func_8004787C(s32);
    extern void func_80146E90(s32 *, s32);
    extern void func_80147324(s32);
    extern s32 func_80146CA0(void *);
    extern s16 D_800CC134;
    extern s16 D_800CC136;
    extern s16 D_800CC138;
    extern void func_80147364(u16 a0, s32 a1);
    extern void func_801659B8(void);
    extern void func_801663A4(void *a0);
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern void func_800CB794(s32 arg0);

    void *s3;
    s32 v0;
    s32 i;
    s32 one;

    s3 = *(void **)((s32)arg0 + 0x20);

    v0 = *(s32 *)((s32)arg0 + 0x1C);
    *(s32 *)((s32)arg0 + 0x1C) = v0 + 1;
    *(s16 *)((s32)s3 + 0x18) = func_8004787C((v0 & 7) << 9) / 32 + 0x1000;

    v0 = *(s32 *)((s32)arg0 + 0x1C);
    *(s32 *)((s32)arg0 + 0x1C) = v0 + 1;
    *(s16 *)((s32)s3 + 0x1A) = func_8004787C((v0 & 7) << 9) / 64 + 0x1000;

    {
        s16 *evt;
        s16 tmp;

        evt = &D_800CC134;
        tmp = D_800CC138 + 1;
        D_800CC138 = tmp;
        D_800CC136 = tmp;
        *evt = tmp;
        if (tmp < 0xFF) {
            return;
        }

        D_800CC138 = 0xFF;
        D_800CC136 = 0xFF;
        *evt = 0xFF;
        func_801663A4(arg0);
    }

    i = 0;
    one = 1;
    do {
        func_80146A6C(0x46, arg0, 0, 0, 0, i, 0);
        func_80146A6C(0x46, arg0, 0, 0, 0, i, one);
        func_80146A6C(0x46, arg0, 0, 0, 0, i, one);
        i++;
    } while (i < 6);

    *(u32 *)((s32)s3 + 4) |= 0x80000000;
    func_800CB794((s32)arg0);
    func_80146E90((s32 *)arg0, 0x1E);
    func_80147364(4, 0x8ED);
    func_80147324(0x8EE);
    func_801659B8();
    func_80146CA0(arg0);
}


extern s32 func_80146E98(s32 a0);
extern s32 func_80146CA0(void *a0);
void func_800CB570(int param_1)
{
    if (((int (*)(void))func_80146E98)() != 0) {
        ((void (*)(int))func_80146CA0)(param_1);
    }
}


extern s32 D_80126B58[];
extern void func_80162CCC(void);
extern s32 func_80165A20(s32 a0);

void func_800CB5A8(void) {
    func_80162CCC();
    func_80165A20((s32)&D_80126B58);
}



extern void func_800CB774(void);

void func_800CB5D8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBFD4[])(void);
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBFD4[v0]();
    } else {
        func_800CB774();
    }
}


extern void func_8014659C(void);
extern void func_8001CA1C(void *a0, void *a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146CA0(void *a0);
extern void func_800CB774(void);
extern int rand(void);

typedef struct { s32 vx, vy, vz; } V3_800CB634; /* 12-byte entries: idx*12 addressing */

void func_800CB634(void *a0) {

    extern V3_800CB634 D_800CBFA0[];
    void *s1;
    s32 vx;
    s32 vy;
    s32 vz;

    s1 = (void *)((s32 (*)(void))func_8014659C)();
    *(s32 *)((s32)a0 + 0x20) = (s32)s1;

    if (s1 != NULL) {
        func_8001CA1C(s1, &D_800CBFA0[*(s32 *)((s32)a0 + 0x50)]);

        vx = ((rand() & 0x3f) - 0x20) << 15;
        vy = ((rand() & 0x3f) - 0x20) << 15;
        vz = -(((rand() & 0x1f) + 0x10) << 15);
        func_80146DE8((s32 *)a0, vx, vz, vy);

        func_80146E90((s32 *)a0, 0x40);
        func_80146CA0(a0);
    } else {
        ((void (*)(void *))func_800CB774)(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_036/nonmatchings/md_MAIN_036", func_800CB708);

extern void func_80162CCC(void);
void func_800CB774(void) {
    func_80162CCC();
}


void func_800CB794(s32 arg0) {
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
    extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);

    u8 *p;
    s32 ptr;
    s16 buf[4];

    p = D_801202A0;
    if (p < D_801202A0 + 0x6480) {
        do {
            if (func_8014C308(arg0, (s32)p, 0x33, 0x4000) != 0) {
                if (func_8014C278(arg0, (s32)p, 0xC0) != 0) {
                    func_80015978((s32)(p + 4), (s32 *)buf);
                    buf[3] = 0;
                    if (func_8014C3D0((void *)arg0, (s32)p, 0x33, (s32)buf) != 0) {
                        if (*(u16 *)p == 0x219) {
                            ptr = *(s32 *)(p + 0x78);
                            if (ptr != 0) {
                                *(s16 *)(p + 0x60) = *(s16 *)(p + 0x76) * 0x1000 /
                                                    *(s16 *)(ptr + 0x30) + 1;
                            }
                        }
                    }
                }
            }
            p += 0x10C;
        } while (p < D_80126720);
    }
}


extern u8 D_80078EC1;
extern void (*D_800CC01C[])(void);
extern void func_80146C3C(void);

void func_800CB8B4(void *arg0) {
    if (D_80078EC1 == 0x17) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC01C[v0]();
    } else {
        func_80146C3C();
    }
}


#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } SV_800CB910;   /*  8 bytes, align 2 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_800CB910; /* 0x20 bytes, align 4 */
typedef struct { s32 vx, vy, vz, pad; } V32_800CB910;  /* 16 bytes, align 4 */

extern void func_8001CF00(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_801465C0(void);
extern void func_80146C3C();
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_800CBF24(void);
extern int rand(void);

extern SV_800CB910 D_800CC028[]; /* stride 8, align 2 -> lwl/lwr + swl/swr copy */
extern V32_800CB910 D_800CC058;   /* 16 bytes, align 4 -> plain lw/sw copy      */
extern u16     D_800CC068[]; /* stride 2 scale table                       */

/* func_800CB910 -- SMALL-EDIT sibling of ov_SC02_041:func_8017D7C0 (proven byte
 * match). Diff vs the seed (wave7b_slate.json[16], 5 sites / 13 ins):
 *   1) `buf[1] -= 0x40;` inserted right before func_80015954((s32)buf, param_1+4)
 *      -- the store lands in the jal's delay slot (same idiom already used two
 *      statements earlier in this same function for `*(p+4) |= 0x80000000`).
 *   2) `if (*(s32*)(param_1+0x2c) == 0) func_800CBF24();` inserted right after,
 *      before the sc/D_800CC068 table read. func_800CBF24 takes no args (it just
 *      writes a global constant -- see asm/md_MAIN_036/nonmatchings/md_MAIN_036/
 *      func_800CBF24.s), so `bnez ..; nop; jal func_800CBF24; nop` with no a0
 *      setup matches a void-arg call.
 *   3/4/5) the extra $s0 save/restore + the extra `addu $s0,$v0,$zero` are pure
 *      register-allocator fallout of the two new statements above increasing
 *      live-range pressure on "p" -- not hand-authored, expected to fall out of
 *      the compile once (1) and (2) are in place.
 */
void func_800CB910(s32 param_1) {
    s16 buf[4];
    SV_800CB910 rot;
    MTX_800CB910 m;
    V32_800CB910 vel;
    s32 obj;
    s32 p;
    s32 p2;
    s16 *q;
    s32 i;
    u16 sc;

    obj = *(s32 *)(param_1 + 0x34);
    p = ((s32 (*)(void))func_801465C0)();
    p2 = p;
    *(s32 *)(param_1 + 0x20) = p;

    if (p != 0) {
        func_8001CF00(p);
        *(s32 *)(p + 0x4) |= 0x80000000;
        func_80015978(obj + 4, (s32 *)buf);
        buf[1] -= 0x40;
        func_80015954((s32)buf, param_1 + 4);

        if (*(s32 *)(param_1 + 0x2c) == 0) {
            func_800CBF24();
        }

        sc = D_800CC068[*(s32 *)(param_1 + 0x30)];
        *(u16 *)(p2 + 0x18) = *(u16 *)(p2 + 0x1a) = *(u16 *)(p2 + 0x1c) = sc;

        vel = D_800CC058;
        rot = D_800CC028[*(s32 *)(param_1 + 0x2c)];

        if (*(s32 *)(param_1 + 0x30) != 0) {
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.vx = ((rand() & 0x1f) - 0x10) << 18;
            vel.vy = ((rand() & 0x1f) - 0x10) << 18;
            vel.vz = ((rand() & 0x1f) - 0x10) << 18;
        }

        func_80049CAC((s32)&rot, (s32)&m);
        func_800484EC((s32)&m, (s32)&vel, (s32)&vel);

        *(s32 *)(param_1 + 0x10) = vel.vx;
        *(s32 *)(param_1 + 0x14) = vel.vy;
        *(s32 *)(param_1 + 0x18) = vel.vz;

        q = (s16 *)(param_1 + 0x38);
        i = 0;
        *(s32 *)(param_1 + 0x4c) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x50) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x54) = ((rand() & 0x1f) - 0x10) * 11;

        do {
            i++;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
        } while (i < 3);

        func_80146E90((s32 *)param_1, 2);
        *(s16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


void func_800CBC14(s32 arg0) {
    extern void func_800CBD2C(s32 param_1);
    extern void func_800CBEB0(s32 a0);
    extern s32 func_80146E98(s32 a0);
    extern void func_80146E90(s32 *a0, s32 a1);

    func_800CBD2C(arg0);
    func_800CBEB0(arg0);
    if (func_80146E98(arg0) != 0) {
        *(s32 *)(arg0 + 0x10) >>= 2;
        *(s32 *)(arg0 + 0x14) >>= 2;
        *(s32 *)(arg0 + 0x18) >>= 2;
        func_80146E90((s32 *)arg0, 0x40);
        *(u16 *)(arg0 + 0x2) += 1;
    }
}


extern void func_800CBD2C(s32 param_1);
extern void func_800CBEB0(s32 a0);
extern void func_800CBF3C();
extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();

void func_800CBC90(s32 arg0) {
    u16 *rec = *(u16 **)(arg0 + 0x20);
    rec[8] += 0x2D;
    rec[9] += 0x2D;
    rec[0xA] += 0x2D;
    *(s32 *)(arg0 + 0x14) += 0x4000;
    func_800CBD2C(arg0);
    func_800CBEB0(arg0);
    if (*(s32 *)(arg0 + 0x2C) == 0) {
        func_800CBF3C();
    }
    if (func_80146E98(arg0) != 0) {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}


extern void func_800CBD54(s32 param_1, s32 *param_2);

void func_800CBD2C(s32 param_1) {
    extern s32 D_800CBFE0;
    func_800CBD54(param_1, &D_800CBFE0);
}


typedef struct { s16 m[3][3]; s32 t[3]; } MTX_800CBD54;

extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80017DF8(s16 *a0, void *a1);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_80016EF8(void *a0, void *a1);

void func_800CBD54(s32 param_1, s32 *param_2)
{
    s32 p;
    MTX_800CBD54 mtx;
    s16 buf[4];

    p = *(s32 *)(param_1 + 0x20);
    *(s32 *)((s32)param_2 + 0x34) = 0x50000000;

    func_80017DC4((void *)(p + 0x18), &mtx);
    func_80017DF8((s16 *)(p + 0x10), &mtx);
    func_80015978(param_1 + 4, (s32 *)buf);
    func_80017E68((void *)buf, &mtx);
    func_80016EF8((void *)param_2, &mtx);

    mtx.t[0] += *(s16 *)(param_1 + 0x38);
    mtx.t[1] += *(s16 *)(param_1 + 0x3A);
    mtx.t[2] += *(s16 *)(param_1 + 0x3C);
    func_80016EF8((void *)param_2, &mtx);
    func_80017E68((void *)buf, &mtx);

    mtx.t[0] += *(s16 *)(param_1 + 0x3E);
    mtx.t[1] += *(s16 *)(param_1 + 0x40);
    mtx.t[2] += *(s16 *)(param_1 + 0x42);
    func_80016EF8((void *)param_2, &mtx);
    func_80017E68((void *)buf, &mtx);

    mtx.t[0] += *(s16 *)(param_1 + 0x44);
    mtx.t[1] += *(s16 *)(param_1 + 0x46);
    mtx.t[2] += *(s16 *)(param_1 + 0x48);
    func_80016EF8((void *)param_2, &mtx);
}




void func_800CBEB0(s32 a0) {
    s32 p;
    *(s32 *)(a0 + 0x4) += *(s32 *)(a0 + 0x10);
    *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x14);
    *(s32 *)(a0 + 0xC) += *(s32 *)(a0 + 0x18);
    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x10) += *(s32 *)(a0 + 0x4C);
    *(u16 *)(p + 0x12) += *(s32 *)(a0 + 0x50);
    *(u16 *)(p + 0x14) += *(s32 *)(a0 + 0x54);
}


extern s32 D_800CC010;

void func_800CBF24(void) {
    D_800CC010 = 0x40404040;
}


extern s32 D_800CC010;
extern u8 D_800CC011;
extern u8 D_800CC012;
extern u8 D_800CC013;

void func_800CBF3C(void) {
    u8 c;
    c = D_800CC013 - 2;
    D_800CC013 = c;
    if (c >= 0x81) {
        D_800CC013 = 0;
    }
    c = D_800CC013;
    (*(u8 *)&D_800CC010) = c;
    D_800CC011 = c;
    D_800CC012 = c;
}

