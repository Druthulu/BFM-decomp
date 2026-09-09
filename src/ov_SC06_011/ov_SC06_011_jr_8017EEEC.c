#include "common.h"



extern void func_8001C214(s32 a0, s32 a1);
extern void func_8017F364(void);

void func_8017EEEC(void *a0) {
    extern u8 D_801202A0[];
    extern void *D_80126CC8;
    extern u8 D_8019FDD4[];
    extern s16 D_801A0774;
    u16 state = *(u16 *)((s32)a0 + 0x34);

    switch (state) {
    case 4:
    {
        u8 *p = D_801202A0;
        s32 i;

        for (i = 0; i < 0x60; i++, p += 0x10C) {
            if (*(u16 *)(p + 0) == 0x2E7 && *(u16 *)(p + 2) == 4) {
                func_8001C214(*(s32 *)((s32)a0 + 0x20), (s32)&D_801A0774);
                *(u16 *)((s32)a0 + 0x5C) = 0x8800;
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
                *(s16 *)((s32)a0 + 0x34) = 3;
            }
        }
        /* fall through */
    }
    case 0:
        if (D_80126CC8 == a0) {
            u16 t0 = *(u16 *)((s32)a0 + 0x88);
            u16 t1 = *(u16 *)((s32)a0 + 0x8A);
            u16 t2 = *(u16 *)((s32)a0 + 0x8C);

            *(s16 *)((s32)a0 + 0x34) = 1;
            *(s16 *)((s32)a0 + 0x5C) = 0;
            *(u16 *)((s32)a0 + 0x6) = t0;
            *(u16 *)((s32)a0 + 0xA) = t1;
            *(u16 *)((s32)a0 + 0xE) = t2;
            func_8017F364();
        }
        break;
    case 1:
        break;
    case 2:
    {
        u8 *p = D_801202A0;
        s32 i;

        for (i = 0; i < 0x60; i++, p += 0x10C) {
            if (*(u16 *)(p + 0) == 0x2E7 && *(u16 *)(p + 2) == 4) {
                func_8001C214(*(s32 *)((s32)a0 + 0x20), (s32)D_8019FDD4);
                *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x60000040;
                *(u16 *)((s32)a0 + 0x5C) = 0x9000;
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x400;
                *(s16 *)((s32)a0 + 0x34) = 0;
            }
        }
        break;
    }
    case 3:
        break;
    default:
        break;
    }
}




extern void (*D_8019E268[])(void);

void func_8017F09C(void *a0) {
    D_8019E268[*(u16 *)((s32)a0 + 0x2)]();
}




extern void (*D_8019E2A4[])(void);

void func_8017F0D8(void *a0) {
    D_8019E2A4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_8019E1B8;
extern u8 D_8018077C[];

void func_8017F114(void *a0) {
    if (func_8012C354((s32)a0, (s32)&D_8019E1B8) != 0) {
        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(s16 *)((s32)a0 + 0xAE) = -1;
        func_8012A828((s32 *)a0, (s32)D_8018077C);
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0xE00;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0xE00;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0xE00;
        *(u16 *)((s32)a0 + 0xFC) = 0x300;
        *(u8 *)((s32)a0 + 0x75) = 8;
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern u8 D_8018077C[];
extern u8 D_8019E270[];
extern void func_8012A828(s32 *a0, s32 a1);

void func_8017F1BC(arg0)
s32 arg0;
{

    extern u8 D_8019E270[];
    s32 s0 = arg0;

    if (func_8012C354(s0, (s32)D_8019E270) != 0) {
        *(u8 *)(s0 + 0xC0) = 1;
        func_8012A828((s32 *)s0, (s32)D_8018077C);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) | 0x10;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x18) = 0xAAA;
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x1C) = 0xAAA;
    }
}




extern void func_8017E5D0(void);
    void func_8017F240(s32 *a0) {
        s32 *p = a0;
        func_8017E5D0();
        p[0x1C / 4] += 1;
    }



/* func_8017F278 — exact mirror of the already-MATCHED func_800D33E0
 * (src/resident/resident.c:827), differing only in the global it passes
 * (&D_801A077C here vs &D_800D3AB0 there). func_8016EE40 takes (u8*, s32).
 * asm: lui/addiu a0=&D_801A077C ; jal func_8016EE40 ; lui a1=0x1000000 (delay). */
extern u8 D_801A077C;
extern void func_8016EE40(u8 *arg0, s32 arg1);

void func_8017F278(void) {
    func_8016EE40(&D_801A077C, 0x1000000);
}




extern void (*D_801A0794[])(void);

void func_8017F2A0(void *a0) {
    D_801A0794[*(u8 *)((s32)a0 + 0x216)]();
}




extern s32 func_80171990(u8 *a0);
extern void func_8017F5F0(s32);

void func_8017F2DC(a0)
s32 a0;
{
    s32 t;

    ((void (*)(s32))func_8017F5F0)(a0);
    t = *(s16 *)(a0 + 0x210);
    if (t >= 0) {
        t = 0x30;
    } else {
        t = -0x30;
    }
    *(s16 *)(a0 + 0x210) = t;
    func_80171990((u8 *)a0);
}





extern s32 func_8017F6CC();
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80171928(void *a0);

void func_8017F324(void *param)
{
    void *s0 = param;

    if (func_8017F6CC() != 0) {
        func_8002D4C8(0x8B1, 0);
        func_80171928(s0);
    }
}



/* func_8017F364 — exact mirror of the already-MATCHED func_800D33E0
 * (src/resident/resident.c:827), differing only in the global it passes
 * (&D_801A079C here vs &D_800D3AB0 there). func_8016EE40 takes (u8*, s32).
 * asm: lui/addiu a0=&D_801A079C ; jal func_8016EE40 ; lui a1=0x1000000 (delay). */
extern u8 D_801A079C;
extern void func_8016EE40(u8 *arg0, s32 arg1);

void func_8017F364(void) {
    func_8016EE40(&D_801A079C, 0x1000000);
}



extern void (*D_801A07A8[])(void);

void func_8017F38C(void *a0) {
    D_801A07A8[*(u8 *)((s32)a0 + 0x216)]();
}



extern s32 func_80012A60(s32 a0, s32 a1);
extern s32 func_80171990(u8 *a0);
extern s32 D_801ABBD8;

void func_8017F3C8(void *a0)
{
    void *s3 = a0;
    void *s2;
    void *p;
    s32 v1;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 bits;
    s32 s0;
    s32 s1;

    s2 = *(void **)((s32)s3 + 0x20);
    func_8017F5F0(s3);
    p = (*(void * *)&D_801ABBD8);
    if (p == 0) {
        goto END;
    }
    v0 = *(u16 *)((s32)s2 + 0x12) + 0x800;
    p = *(void **)((s32)p + 0x20);
    bits = *(u16 *)((s32)p + 0x12) & 0x400;
    s0 = v0 & 0xFFF;
    if (bits == 0) {
        goto ELSE;
    }
    s1 = func_80012A60(s0, 0x400);
    v0 = func_80012A60(s0, 0xC00);
    v1 = (s16)s1;
    v0 = (s16)v0;
    v0 = (v0 < v1);
    if (v0 != 0) {
        goto TRUE1;
    }
    v0 = 0x400;
    goto STORE;
TRUE1:
    v0 = 0xC00;
    goto STORE;
ELSE:
    s1 = func_80012A60(s0, 0);
    v0 = func_80012A60(s0, 0x800);
    v1 = (s16)s1;
    v0 = (s16)v0;
    v0 = (v0 < v1);
    if (v0 != 0) {
        goto TRUE2;
    }
    *(u16 *)((s32)s2 + 0x12) = 0;
    goto END;
TRUE2:
    v0 = 0x800;
STORE:
    *(u16 *)((s32)s2 + 0x12) = v0;
END:
    func_80171990((u8 *)s3);
}





extern s32 func_8017F6CC();
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80171990(u8*);

void func_8017F4D0(void *param)
{
    void *s0 = param;

    if (func_8017F6CC() != 0) {
        func_8002D4C8(0x8B1, 0);
        ((void (*)(void *))func_80171990)(s0);
    }
}


extern s32 func_80013328(s32 a0, s32 a1);
extern u8 D_801202A0[];
extern void func_800D1724(s32 a0);
extern void func_80171928(void *a0);

void func_8017F510(arg0)
void *arg0;
{
    u8 *p;
    u8 *found;
    s32 i;
    s32 best;
    s16 t;

    found = 0;
    best = 0x7FFFFFFF;
    for (i = 0; i < 0x60; i++) {
        p = &D_801202A0[i * 0x10C];
        if ((*(u16 *)(p + 0) != 0) && ((*(u16 *)(p + 0x5C) & 0x80) != 0)) {
            t = (s16)func_80013328((s32)arg0 + 4, (s32)p + 4);
            if (t < best) {
                best = t;
                found = p;
            }
        }
    }
    if (found != 0) {
        func_800D1724(*(s32 *)(found + 0xDC));
    }
    func_80171928(arg0);
}


extern u8 D_801202A0[];
extern s32 D_801ABBD8;
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80013328(s32 a0, s32 a1);
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);

void func_8017F5F0(s32 arg0)
{
    s16 v;
    s32 i;
    s32 best;
    unsigned short *p;
    s32 buf[2];

    best = 0x7FFFFFFF;
    i = 0;
    p = (unsigned short *)D_801202A0;
    D_801ABBD8 = 0;
loop:
    if (*p == 0x26E) {
        v = (s16)func_80013328(arg0 + 4, (s32)(p + 2));
        if (v < best) {
            best = v;
            D_801ABBD8 = (s32)p;
        }
    }
    __asm__("" ::  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
                "r"(best));
    i++;
    p += 0x86;
    if (i < 0x60) {
        goto loop;
    }
    *(s16 *)(arg0 + 0x208) = 0;
    func_80015978(arg0 + 4, buf);
    func_8012F2E8(D_801ABBD8, (s32)buf, arg0 + 0x20C);
    *(s32 *)(arg0 + 0x204) = D_801ABBD8;
    func_8002D4C8(0x8B0, 0);
}


typedef struct {
    u16 x, y, z, w;
} Pt_8017D87C;


s32 func_8017F6CC(s32 a0) {
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern void func_80015954(s32 a0, s32 a1);
    s32 t;
    s16 out[4];
    u16 w;

    t = *(s32 *)(*(s32 *)(a0 + 0x204) + 0x20);
    if (*(s32 *)(a0 + 0x204) != 0) {
        *(u16 *)(t + 0x12) += 0x80;
        func_8012F14C(t + 0x34, a0 + 0x20C, (s32)out);
        func_80015954((s32)out, a0 + 4);
    }
    t = *(s32 *)(a0 + 0x20);
    *(u16 *)(t + 0x12) += 0x80;
    w = *(u16 *)(a0 + 0x208);
    w = w + 0x80;
    *(u16 *)(a0 + 0x208) = w;
    return (s16)w == 0x800;
}



extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void*);

void func_8017F760(s32 arg0) {
    u8 val;

    /* Check field at +0x100 */
    if (((s16 *)arg0)[0x80] == 0) {
        func_8002A04C(arg0);
    }

    /* Check field at +0xC1 */
    val = ((u8 *)arg0)[0xC1];
    if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
        func_8002AC00(0x7);
    }

    /* Always call func_8012C098 */
    ((void (*)(s32))func_8012C098)(arg0);
}


typedef struct { s16 vx, vy, vz, pad; } SVECTOR;

void func_8017F7D4(s32 a0) {
    SVECTOR in;
    SVECTOR out;
    s32 v0;

    in.vx = *(s16 *)(a0 + 0x6);
    in.vy = *(s16 *)(a0 + 0xA);
    in.vz = *(s16 *)(a0 + 0xE);
    out = in;
    out.vy += 8;

    if ((func_80133784(1, &in, (s32)&out) & 0x6000) != 0) {
        v0 = 1;
    } else {
        func_8012B23C(a0);
        v0 = 0;
    }

    if (v0 == 0) {
        *(s16 *)(a0 + 0x2) = 0x8;
        *(s16 *)(a0 + 0x98) = 0;
        return;
    }

    if (*(s32 *)(a0 + 0xC4) & 4) {
        func_8017F8AC(a0);
    } else {
        func_8017F8F8(a0);
    }
}



extern void func_8012A828(s32*, s32);
extern void func_8012B23C(void*);

void func_8017F8AC(int param_1)
{

    extern unsigned char D_801A8F00[];
    *(short *)(param_1 + 2) = 5;
    *(short *)(param_1 + 0x34) = 0;
    *(unsigned short *)(param_1 + 0x5C) = 0xAA10;
    ((void (*)(s32, void *))func_8012A828)(param_1, &D_801A8F00);
    ((void (*)(s32))func_8012B23C)(param_1);
}


#include "common.h"

extern s32 rand(void);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_8012B23C(void *a0);
extern void Square0(s32 *a0, s32 *a1);
extern u8 D_801A8AE8[];

void func_8017F8F8(void *param_1) {
    s32 d[3];
    void *target;

    *(s16 *)((s32)param_1 + 0x2) = 1;
    *(s16 *)((s32)param_1 + 0x34) = 0;
    *(u16 *)((s32)param_1 + 0x5C) = 0xAA10;
    *(s32 *)((s32)param_1 + 0x1C) = (rand() & 0x1F) + 0x24;

    target = (void *)((s32)param_1 + 0x88);

    d[0] = *(s16 *)((s32)param_1 + 0x6) - *(s16 *)target;
    d[1] = 0;
    d[2] = *(s16 *)((s32)param_1 + 0xE) - *(s16 *)((s32)param_1 + 0x8C);
    Square0(&d[0], &d[0]);

    if (d[0] + d[2] > 0x8FFFF) {
        *(s16 *)((s32)param_1 + 0xFC) = func_8012B744((void *)((s32)param_1 + 4), target);
    } else {
        s32 t = rand() & 0x3FF;
        s32 v1 = t - 0x200;
        if (v1 < 0) {
            v1 = t - 0x500;
        } else {
            v1 = t + 0x100;
        }
        *(s16 *)((s32)param_1 + 0xFC) =
            (*(u16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12) + v1) & 0xFFF;
    }

    func_8012B23C(param_1);
    func_8012A828((s32 *)param_1, (s32)&D_801A8AE8);
}






extern void func_8012A828(s32*, s32);
    extern short D_801A89A0;
    void func_8017FA00(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801A89A0);
    }


extern void func_8012A828(s32 *a0, s32 a1);
extern short D_801A8B90;
extern short D_801A8C18;

void func_8017FA30(s32 a0) {
    *(s16 *)(a0 + 2) = 3;
    if (*(u16 *)(a0 + 0x86) & 2) {
        *(s16 *)(a0 + 0x34) = 1;
        *(s32 *)(a0 + 0x1C) = 0x28;
        func_8012A828((s32 *)a0, (s32)&D_801A8B90);
        *(u16 *)(a0 + 0xFE) = 0;
    } else {
        *(s16 *)(a0 + 0x34) = 0;
        func_8012A828((s32 *)a0, (s32)&D_801A8C18);
        *(s32 *)(a0 + 0x1C) = 0x19;
        *(u16 *)(a0 + 0x86) |= 2;
    }
}


#include "common.h"

extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32);
extern void func_8012ADE4(u8 *a0);
extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern void func_8017F8F8();
extern void func_8017FC7C();

extern s16 D_801A8B90;
extern s16 D_801A8C18;
extern s32 D_801A07B8;

void func_8017FAB4(s32 a0)
{
    s32 s0 = a0;
    u16 st;
    s32 v;
    unsigned short *p;
    s16 t;

    st = *(u16 *)(s0 + 0x34);
    switch (st) {
    case 0:
        v = func_8012B8E4(s0, 4);
        p = (unsigned short *)(*(s32 *)(s0 + 0x20) + 0x12);
        *p = *p + v;

        if (*(s32 *)(s0 + 0x1C) == 0xF) {
            func_80142414(s0, -0x78);
            func_8002D4C8(0x6A9, 0);
        }

        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x2) = 3;
            if ((*(u16 *)(s0 + 0x86) & 0x2) != 0) {
                *(u16 *)(s0 + 0x34) = 1;
                *(s32 *)(s0 + 0x1C) = 0x28;
                func_8012A828((s32 *)s0, (s32)&D_801A8B90);
                *(u16 *)(s0 + 0xFE) = 0;
            } else {
                *(u16 *)(s0 + 0x34) = 0;
                func_8012A828((s32 *)s0, (s32)&D_801A8C18);
                *(s32 *)(s0 + 0x1C) = 0x19;
                *(u16 *)(s0 + 0x86) = *(u16 *)(s0 + 0x86) | 0x2;
            }
        }
        break;
    case 1:
        if (*(s32 *)(s0 + 0x1C) >= 0x16) {
            v = func_8012B8E4(s0, 6);
            p = (unsigned short *)(*(s32 *)(s0 + 0x20) + 0x12);
            *p = *p + v;
        }

        func_8012B178(s0, D_801A07B8);

        if (((s32 (*)(s32))func_8012CBA4)(s0) != 0x2000) {
            func_8012ADE4((u8 *)s0);
        }

        t = *(u16 *)(s0 + 0xFE) - 1;
        *(u16 *)(s0 + 0xFE) = t;
        if (t <= 0) {
            func_80143B6C(s0, 0);
            *(u16 *)(s0 + 0xFE) = 8;
        }

        if (func_8012BEE8(s0) != 0) {
            func_8017F8F8(s0);
        }

        if (func_8012BD3C(s0, 0x200, 0x1000) != 0) {
            func_8017FC7C(s0);
        }
        break;
    }
}


extern char D_801A8CE8[];
extern void func_8012A828(s32 *a0, s32 a1);

void func_8017FC7C(param_1)
int param_1;
{
    *(short *)(param_1 + 2) = 4;
    *(short *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, &D_801A8CE8);
    *(int *)(param_1 + 0x1c) = 0x14;
}




void func_8017FCC0(void *a0) {
    extern s32 func_8012BEE8(s32 a0);
    extern s32 func_8012B8E4(s32 a0, s32 a1);
    extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
    extern void func_8012A828(s32*, s32);
    extern u8 D_801A0848[];
    extern u8 D_801A88F8[];
    extern u8 D_801A8DB0[];
    extern short D_801A89A0;
    s32 base = (s32)a0;
    s32 ptr;
    s32 ret;

    switch (*(u16 *)(base + 0x34)) {
    case 0:
        if (*(s32 *)(base + 0x1C) == 7) {
            func_8012D5E4(base, (s32)D_801A0848, (s32)D_801A0848 + 8, 0xB);
        }
        break;
    case 1:
        ret = func_8012B8E4(base, 6);
        ptr = *(s32 *)(base + 0x20);
        *(u16 *)(ptr + 0x12) += ret;
        break;
    case 2:
        if (*(s32 *)(base + 0x1C) == 0xA) {
            func_8012D5E4(base, (s32)D_801A0848, (s32)D_801A0848 + 8, 0xB);
        }
        break;
    }

    if (func_8012BEE8(base) == 0) {
        return;
    }

    switch (*(u16 *)(base + 0x34)) {
    case 0:
        if (func_8012BD3C(base, 0x400, 0x4000) == 0) {
            goto state_off;
        }
        *(u16 *)(base + 0x34) = 1;
        func_8012A828((s32 *)base, (s32)D_801A88F8);
        *(s32 *)(base + 0x1C) = 0xA;
        break;
    case 1:
        *(u16 *)(base + 0x34) = 2;
        *(s32 *)(base + 0x1C) = 0x18;
        func_8012A828((s32 *)base, (s32)D_801A8DB0);
        break;
    case 2:
    state_off:
        *(u16 *)(base + 0x2) = 2;
        *(u16 *)(base + 0x34) = 0;
        func_8012A828((s32 *)base, (s32)&D_801A89A0);
        break;
    }
}


extern s32 D_801A085C[];
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_8017FE34(s32 arg0) {
    s32 *tbl = D_801A085C;

    if ((*(u16 *)(arg0 + 0x70) & 0x2000) == 0) {
        tbl += 3;
    }
    *(u16 *)(arg0 + 2) = 7;
    func_8012A828((s32 *)arg0, tbl[0]);
    func_8012B2CC(arg0);
    func_8012B200((u8 *)arg0);
    func_8012B178(arg0, tbl[1]);
    *(s32 *)(arg0 + 0x1C) = tbl[2];
}


#include "common.h"

extern s32 D_801A0874[];
extern s32 func_8012C044(s32 arg0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void *arg0);

void func_8017FEB4(s32 arg0) {
    void (*handler)(s32);
    u8 val;

    handler = (void (*)(s32))D_801A0874[((u16 *)arg0)[1]];
    handler(arg0);

    if (((u16 *)arg0)[0] == 0)
        return;

    if (func_8012C044(arg0) == 0)
        return;

    *(u16 *)(arg0 + 0x100) = 1;

    val = ((u8 *)arg0)[0xC1];
    if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
        func_8002AC00(0x7);
    }

    func_8012C098((void *)arg0);
}




extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_8017FF58(void) {
        func_8002D4C8(0x6AA, 0);
    }




extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_8017FF7C(u8 *a0) {
        if (*(u8 *)(a0 + 0x5E) == 0xC) {
            func_8002D4C8(0x9DA, 0);
        }
    }


extern void func_8012CBF4(s32 a0);
extern void func_8017F8F8();

void func_8017FFAC(s32 a0)
{
    func_8012CBF4(a0);
    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        func_8017F8F8(a0);
    }
}






extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8017FA00();
extern s32 D_801A07B4;

void func_8017FFF0(s32 a0) {
    s32 ret;
    s32 v0;

    if (*(s32 *)(a0 + 0x1C) >= 4) {
        v0 = *(s32 *)(a0 + 0x20);
        ret = func_8012B608(*(s16 *)(v0 + 0x12), *(s16 *)(a0 + 0xFC), 8);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += ret;
    }
    func_8012B178(a0, D_801A07B4);
    if (((s32 (*)(s32))func_8012CBA4)(a0) != 0x2000) {
        func_8012ADE4((u8 *)a0);
    }
    if (func_8012BEE8(a0) != 0) {
        func_8017FA00((short *)a0);
    }
}


extern void Square0(s32 *a0, s32 *a1);
extern s32 func_8012BCCC(s32 a0);
extern void func_8017FA30(s32 a0);
extern void func_8017F8F8();

void func_80180098(s32 a0)
{
    s32 s0 = a0;
    s32 d[3];

    if (*(u16 *)(s0 + 0x34) == 0 && (*(u16 *)(s0 + 0x72) & 0x4000)) {
        d[0] = *(s16 *)(s0 + 0x6) - *(s16 *)(s0 + 0x88);
        d[1] = 0;
        d[2] = *(s16 *)(s0 + 0xE) - *(s16 *)(s0 + 0x8C);
        Square0(d, d);
        if (d[0] + d[2] <= 0x8FFFF && func_8012BCCC(s0) <= 0x10000) {
            func_8017FA30(s0);
        } else {
            func_8017F8F8(s0);
        }
    }
}



extern s32 func_8012BCCC(s32 a0);
extern void func_8012E88C(s32 a0);
extern void func_8017FE34(s32 a0);
extern s32 D_801A0858;

void func_8018015C(void *a0) {
    s32 s0 = (s32)a0;
    s32 v0 = func_8012BCCC(s0);
    if (v0 < D_801A0858) {
        func_8012E88C(s0);
        func_8017FE34(s0);
    }
}



extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

extern s16 D_801A8B90;
extern s16 D_801A8C18;

void func_801801AC(s32 a0) {
    s32 v0;

    func_8012AD80(a0);
    if (*(u16 *)(a0 + 0x70) & 0x2000) {
        v0 = *(u16 *)(a0 + 0xFE) - 1;
        *(u16 *)(a0 + 0xFE) = v0;
        if ((s16)v0 <= 0) {
            func_80143B6C(a0, 0);
            *(u16 *)(a0 + 0xFE) = 8;
        }
    }
    if (func_8012BEE8(a0)) {
        *(u16 *)(a0 + 0x86) |= 2;
        *(s16 *)(a0 + 0x2) = 3;
        if (*(u16 *)(a0 + 0x86) & 2) {
            *(s16 *)(a0 + 0x34) = 1;
            *(s32 *)(a0 + 0x1C) = 0x28;
            ((void (*)(s32, void *))func_8012A828)(a0, &D_801A8B90);
            *(u16 *)(a0 + 0xFE) = 0;
        } else {
            *(s16 *)(a0 + 0x34) = 0;
            ((void (*)(s32, void *))func_8012A828)(a0, &D_801A8C18);
            *(s32 *)(a0 + 0x1C) = 0x19;
            *(u16 *)(a0 + 0x86) |= 2;
        }
    }
}




extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_8012C098(void*);
extern void func_8012CBF4(s32 a0);
extern void func_8017F8F8();
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

void func_80180298(s32 a0) {
    u8 val;
    s16 field_a;
    s16 field_100;
    s32 result;

    field_a = *(s16 *)(a0 + 0xA);
    if (field_a >= 0x10) {
        field_100 = *(s16 *)(a0 + 0x100);
        if (field_100 == 0) {
            func_8002A04C(a0);
        }
        val = ((u8 *)a0)[0xC1];
        if (val == 5 || val == 0xD || val == 0xB || val == 0xE) {
            func_8002AC00(0x7);
        }
        ((void (*)(s32))func_8012C098)(a0);
    } else {
        result = ((s32 (*)(s32))func_8012CBF4)(a0);
        if ((result & 0x2000) != 0) {
            if ((result & 0x1000) != 0) {
                func_80131E00((struct S80131E00 *)a0, 0x12);
            } else {
                func_8017F8F8(a0);
            }
        }
    }
}


extern s32 D_801A07CC;
extern u8 D_801A0800[];
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern void func_8012A828(s32 *a0, s32 a1);
extern short D_801A89A0;
extern void func_8012E8A8(u8 *a0);
extern void func_8017F8F8();

void func_80180360(void *a0) {
    if (func_8012C354((s32)a0, (s32)&D_801A07CC) != 0) {
        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(s32 *)((s32)a0 + 0xB4) = -1;
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(s32 *)((s32)a0 + 0xBC) = (s32)D_801A0800;
        func_80143970((s32)a0);
        func_8012B030((u8 *)a0);
        if (*(u16 *)((s32)a0 + 0x70) & 0x6000) {
            *(u16 *)((s32)a0 + 0x2) = 6;
            func_8012A828((s32 *)a0, (s32)&D_801A89A0);
            func_8012E8A8(a0);
        } else {
            func_8017F8F8(a0);
        }
    }
}

