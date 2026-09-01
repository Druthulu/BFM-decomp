#include "common.h"

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017EEEC);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F09C);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F0D8);

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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F240);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F278);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F2A0);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F2DC);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F324);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F364);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F38C);


extern s32 func_80012A60(s32 a0, s32 a1);
extern s32 func_80171990(u8 *a0);
extern s32 D_801ABBD8;

void func_8017F3C8(void *a0)
{
    register void *s3 __asm__("$19") = a0;
    void *s2;
    register void *p __asm__("$3");
    register s32 v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    s32 bits;
    register s32 s0 __asm__("$16");
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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F4D0);

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
    __asm__("" ::
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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F6CC);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F760);

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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017F8AC);

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
        register s32 t __asm__("$2") = rand() & 0x3FF;
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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017FA00);

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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017FAB4);

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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017FCC0);

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
    register u8 val __asm__("$3");

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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017FF58);

INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017FF7C);

extern void func_8012CBF4(s32 a0);
extern void func_8017F8F8();

void func_8017FFAC(s32 a0)
{
    func_8012CBF4(a0);
    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        func_8017F8F8(a0);
    }
}


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8017FFF0);

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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_8018015C);


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


INCLUDE_ASM("asm/ov_SC06_011/nonmatchings/ov_SC06_011_jr_8017EEEC", func_80180298);

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

