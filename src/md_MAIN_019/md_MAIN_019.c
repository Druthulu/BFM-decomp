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
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


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


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB1A0);


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


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB324);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB3FC);

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


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB578);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CB9F8);

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


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBD68);

INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBE38);

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


INCLUDE_ASM("asm/md_MAIN_019/nonmatchings/md_MAIN_019", func_800CBF80);
