#include "common.h"

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CAE14);



void func_800CAE4C(void *a0) {

    extern void (*D_800CBE34[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBE34[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED8(u8 *a0);
void func_800CAE90(u8 *a0) {
    if (func_80161104()) {
        func_800CAED8(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CAED8);

extern s32 D_80062BE8;
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80019064(void *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80161208();

void func_800CAF80(void *a0) {
    u16 flag;

    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flag & 0x4000) {
            func_801466F0(0x25, (s32)a0, 0, -0x40, 0, 1, 0, 0);
            func_80019064(&D_80062BE8);
        }
        if (func_80161208(a0) == 0) {
            *(s32 *)((u8 *)a0 + 0x44) |= 2;
        }
    }
}


void func_800CB02C(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


extern u8 D_80078EC1;
extern void (*D_800CBE40[])(void);
extern void func_800CB4AC(void);

void func_800CB040(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1C) {
        index = *(u16 *)(a0 + 2);
        D_800CBE40[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB4AC)(a0);
    } else {
        ((void (*)(s32))func_800CB4AC)(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB0B4);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB228);

extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_800CB424(void *a0)
{
    s32 i;

    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
        return;
    }
    for (i = 0; i < 4; i++) {
        func_80146A6C(0x4E, a0, *(s16 *)((s32)a0 + 6), *(s16 *)((s32)a0 + 0xA),
                      *(s16 *)((s32)a0 + 0xE), i, 1);
    }
}


extern void func_80162CCC(void);
void func_800CB4AC(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB4CC);

#include "common.h"

s32 func_800CB4D4(s32 a0) {
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    extern void func_80015978(s32 a0, s32 *a1);
    extern s32 func_8012E778(s32 a0, s32 a1);
    extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_80013328(s32 *a0, s32 *a1);

    u8 *p;
    u8 *q;
    s32 buf[2];
    s32 best;
    u8 *bestp;
    s16 r;

    bestp = 0;
    best = 0x7FFFFFFF;
    p = D_801202A0;
    while (p < D_801202A0 + 0x6480) {
        if (*(u16 *)(p + 0) != 0x282) {
            q = p + 4;
            func_80015978((s32)q, buf);
            if (func_8012E778((s32)p, 0x8C00B4) == 1) {
                if (func_8014C308(a0, (s32)p, 0x2B, 0x40) != 0) {
                    r = func_80013328((s32 *)(a0 + 4), (s32 *)q);
                    if (r < best) {
                        best = r;
                        bestp = p;
                    }
                }
            }
        }
        p += 0x10C;
    }
    return (s32)bestp;
}


void func_800CB5CC(void *a0) {
    if (*(s32 *)((s32)a0 + 0x54) != 0) {
        if (func_8014C308((s32)a0, *(s32 *)((s32)a0 + 0x54), 0x2B, 0x40) != 0) {
            func_800CB61C(a0, *(s32 *)((s32)a0 + 0x54));
        }
    }
}


s32 func_800CB61C(s32 a0, s32 a1)
{
    typedef struct { u8 b[8]; } Blk8;
    extern u8 D_800CAE0C[8];
    extern s32 func_8014C5FC(s32, s32, void *);
    extern s32 func_8014C59C(void *, void *);
    extern s32 func_80012DBC(s32, s32, s32, s32);

    s32 s2 = *(s32 *)(a0 + 0x20);
    Blk8 buf;
    s32 r1, r2, x, y;

    buf = *(Blk8 *)D_800CAE0C;
    if (*(u16 *)a1 == 0x2CE) {
        *(s16 *)&buf.b[2] = -0x1AB;
    }
    r1 = func_8014C59C((void *)a0, (void *)a1);
    x = func_80012DBC(*(s16 *)(s2 + 0x12), (s16)r1, 0x10, 1);
    *(s16 *)(s2 + 0x12) = x;
    r2 = func_8014C5FC(a0, a1, &buf);
    y = func_80012DBC(*(s16 *)(s2 + 0x10), (s16)r2, 0x10, 1);
    *(s16 *)(s2 + 0x10) = y;
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB6F4);


extern void func_80146C3C(void);

void func_800CB804(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBEAC[])(void);
    if (D_80078EC1 == 0x1c) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBEAC[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CB860);

extern void func_800CBBDC(s32 a0);
extern void func_800CBC40(void*, s32);
extern s32 func_80146E98(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);

void func_800CBAAC(s32 param_1)
{
    s32 s0;

    s0 = *(s32 *)(param_1 + 0x20);
    func_80128ED8(s0, (s32 *)(param_1 + 0x24));
    *(s8 *)(s0 + 0x27) = *(u8 *)(param_1 + 0x28) - 0x70;
    func_800CBBDC(param_1);
    ((void (*)(s32, s32))func_800CBC40)(param_1, 0x30);
    if (func_80146E98(param_1) != 0) {
        *(s32 *)(param_1 + 0x10) >>= 2;
        *(s32 *)(param_1 + 0x14) >>= 2;
        *(s32 *)(param_1 + 0x18) >>= 2;
        func_80146E90((s32 *)param_1, 8);
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBB54);

INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBBDC);

void func_800CBC10(void *arg0) {
    u8 *a0 = (u8 *)arg0;
    a0 = *(u8 **)(a0 + 0x20);
    a0[0x24] -= 4;
    a0[0x25] -= 4;
    a0[0x26] -= 4;
}


void func_800CBC40(void *arg0, s32 arg1) {
    void *v1 = *(void **)((s32)arg0 + 0x20);
    u16 v0 = *(u16 *)((s32)v1 + 0x1A) - arg1;
    *(u16 *)((s32)v1 + 0x1A) = v0;
    *(u16 *)((s32)v1 + 0x18) = v0;
}



extern void func_80146C3C(void);

void func_800CBC60(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CBEF8[])(void);
    if (D_80078EC1 == 0x1c) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CBEF8[v0]();
    } else {
        func_80146C3C();
    }
}


extern void func_801465C0(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(void);

void func_800CBCBC(void *a0)
{
    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    void *s1;
    void *s0;
    s32 pad[14];

    s1 = *(void **)((u8 *)a0 + 0x34);
    s0 = ((void *(*)(void))func_801465C0)();
    *(void **)((u8 *)a0 + 0x20) = s0;

    if (s0 != NULL) {
        func_8001CC3C((s32)s0, (s32)&D_800D387C, 0, 0);

        *(u8 *)((u8 *)s0 + 0x27) = 0x9C;
        *(u16 *)((u8 *)s0 + 0x1A) = 0x2000;
        *(u16 *)((u8 *)s0 + 0x18) = 0x2000;
        *(u8 *)((u8 *)s0 + 0x24) = 0xFF;
        *(u8 *)((u8 *)s0 + 0x25) = 0;
        *(u8 *)((u8 *)s0 + 0x26) = 0;
        *(s32 *)((u8 *)s0 + 4) |= 0x50000000;

        func_80149374((s32)s1, (s32)((u8 *)a0 + 4));
        func_80128EA8((s32)s0, (s32)((u8 *)a0 + 0x24), (s32)&D_800D3888);

        *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_039/nonmatchings/md_MAIN_039", func_800CBD90);
