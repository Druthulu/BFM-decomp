#include "common.h"



void func_800CEDFC(void) {

    extern u16 D_800B99E4;
    extern void (*D_800CF450[])(void);
    u32 v1;
    v1 = D_800B99E4;
    if (v1 < 8) {
        D_800CF450[v1]();
    }
}


#include "common.h"

extern u8 D_800B9A11;
extern s32 D_800B9A18;
extern u16 D_800B99E8;
extern s32 D_800D3ABC;
extern s32 D_800D3C0C;
extern s32 D_800D3C10;

extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_800146B0(s32 a0);
extern void func_80059658(s32 a0);
extern s32 VSync(s32 a0);
extern void func_800167B8(s32 a0);
extern void func_800183E0(s32 *a0);
extern void func_800116E0(void);
extern s32 func_8001BFE8(void);
extern void func_80011928(s32 a0);
extern void func_8001BFF8(void);
extern void func_800118AC(void);

void func_800CEE40(void) {
    D_800B9A11 = 1;
    func_8001C044();
    func_80015310();
    func_800146B0(7);
    func_80059658(0);
    VSync(0);
    func_80059658(1);
    D_800B9A18 = 0;
    func_800167B8(0);
    func_800183E0(&D_800D3ABC);
    D_800D3C0C = 0;
    D_800D3C10 = 0;
    func_800116E0();
    D_800B99E8 = 0;
    if (func_8001BFE8() != 0) {
        func_80011928(3);
    } else {
        func_8001BFF8();
        func_800118AC();
    }
}


extern s32 D_800D3C10;
extern void func_800118AC(void);
extern void func_800CF290(void);

void func_800CEF04(void) {
    D_800D3C10 += 0x10;
    if (D_800D3C10 >= 0x80) {
        D_800D3C10 = 0x80;
        func_800118AC();
    }
    func_800CF290();
}


void func_800CEF54(void) {
    extern u16 D_800B99EE;
    extern void func_800CF290(void);
    extern void func_800118AC(void);

    func_800CF290();
    D_800B99EE = D_800B99EE + 1;
    if ((s16)D_800B99EE >= 0x105) {
        func_800118AC();
    }
}


extern s32 D_800D3C10;
extern void func_800118AC(void);
extern void func_800CF290(void);

void func_800CEFA8(void) {
    D_800D3C10 -= 4;
    if (D_800D3C10 <= 0) {
        D_800D3C10 = 0;
        func_800118AC();
    }
    func_800CF290();
}


void func_800CEFF4(void) {
    extern void func_800CF180(void);
    extern void func_800CF114(void);
    extern s32 func_800167F0(s32 arg0);
    extern void func_800118AC(void);

    func_800CF180();
    func_800CF114();
    if (func_800167F0(0) & 0xFFFF) {
        func_800118AC();
    }
}


void func_800CF038(void) {
    extern void func_800CF180(void);
    extern void func_800CF114(void);
    extern u16 D_800B99E8;
    extern s32 func_800149E0(s32 a0);
    extern s32 D_800D3C0C;
    extern void func_800167B8(s32 a0);
    extern void func_800118AC(void);
    s32 temp;

    func_800CF180();
    func_800CF114();
    D_800B99E8 = D_800B99E8 + 1;
    temp = func_800149E0(0);
    if (D_800D3C0C != 0) {
        if ((s16)D_800B99E8 >= 0x81 || (temp & 0x840)) {
            func_800167B8(4);
            func_800118AC();
        }
    }
}


void func_800CF0C4(void) {
    extern void func_800CF180(void);
    extern s32 func_800167F0(s32 arg);
    extern void func_800146B0(s32 arg);
    extern u16 D_800B99E6;
    extern s32 D_800B9A18;

    func_800CF180();
    if (func_800167F0(4) & 0xFFFF) {
        D_800B99E6 = 1;
        func_800146B0(1);
        D_800B9A18 = 2;
    }
}


extern s32 func_8001ABBC(s32 arg0, s32 arg1, void *arg2, s32 arg3, s32 *arg4);
extern s32 D_800D3C0C;
extern s32 D_800C7C60;
extern s32 *D_800C7C64;
extern s32 D_800A2E20;
extern u8 D_800AE840[];

void func_800CF114(void) {
    if (D_800D3C0C == 0) {
        s32 *p = &D_800C7C60;
        *p = 0;
        D_800C7C64 = &D_800A2E20;
        if (func_8001ABBC(0, 0, D_800AE840, 0, p) != 0) {
            D_800D3C0C = 1;
        }
    }
}


void func_800CF180(void)
{
    extern u16 D_800B9A02;
    extern u8 D_800CF3F0[];
    extern u8 D_800CF420[];
    extern u8 D_800AA60C[];

    register u32 m24 __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 mFF __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus9)
    u32 *tb;
    register u32 *ab __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus9)
    u32 *pp;

    m24 = 0x00FFFFFF;
    tb = (u32 *)D_800CF3F0;
    {
        register s32 i __asm__("$2") = D_800B9A02;  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
        mFF = 0xFF000000;
        *(u32 *)((s32)tb + i * 24) =
            (*(u32 *)((s32)tb + i * 24) & mFF) |
            (*(u32 *)((s32)D_800AA60C + (i << 14)) & m24);
    }

    {
        s32 i = D_800B9A02;
        ab = (u32 *)D_800AA60C;
        pp = (u32 *)(i << 14);
        pp = (u32 *)((s32)pp + (s32)ab);
        *pp = (*pp & mFF) | ((u32)((s32)tb + i * 24) & m24);
    }

    {
        s32 i = D_800B9A02;
        tb = (u32 *)D_800CF420;
        *(u32 *)((s32)tb + i * 24) =
            (*(u32 *)((s32)tb + i * 24) & mFF) |
            (*(u32 *)((s32)ab + (i << 14)) & m24);
    }

    {
        s32 i = D_800B9A02;
        s32 frame_pad[1];
        (void)&frame_pad;
        pp = (u32 *)(i << 14);
        pp = (u32 *)((s32)pp + (s32)ab);
        *pp = (*pp & mFF) | ((u32)((s32)tb + i * 24) & m24);
    }
}


extern s32 D_800D3C10;

void func_800CF290(void) {
    extern u16 D_800B9A02;
    extern u8 D_800D3AEC[];
    extern u8 D_800D3B1C[];
    extern u8 D_800D3C10_b __asm__("D_800D3C10");
    extern u8 D_800AA60C[];

    s32 n = D_800B9A02;
    u8 *p0;
    register u8 *p1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    u32 c5;
    u32 c64;
    register u32 c7840 __asm__("$14");  // !FAKE: pin $14 — NEEDED DIFFERS (P36 rung B tus9)
    u32 cm28;
    u32 c38;
    u32 c256;
    u32 c60;
    u32 *q0;
    u32 *q1;
    u32 *ot;
    u8 c;
    s32 w;
    u32 t;

    {
        u32 e1a = 0xE100008A;

        w = n * 24;
        p0 = D_800D3AEC + w;
        q0 = (u32 *)(D_800D3AEC + w + 4);
        c5 = 5;
        p0[3] = c5;
        *q0 = e1a;
    }
    c64 = 0x64;
    p0[0xB] = c64;
    *(s16 *)(p0 + 0xC) = -0x100;
    c = D_800D3C10_b;
    n <<= 14;
    c7840 = 0x7840;
    cm28 = -28;
    *(s16 *)(p0 + 0x12) = c7840;
    *(s16 *)(p0 + 0xE) = cm28;
    c38 = 0x38;
    c256 = 0x100;
    p0[0x10] = 0;
    p0[0x11] = c38;
    *(s16 *)(p0 + 0x14) = c256;
    c60 = 0x60;
    *(s16 *)(p0 + 0x16) = c60;
    p0[0xA] = c;
    p0[9] = c;
    p0[8] = c;

    p1 = D_800D3B1C + w;
    q1 = (u32 *)(D_800D3B1C + w + 4);
    {
        register u32 e1b __asm__("$8") = 0xE100008C;  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus9)
        p1[3] = c5;
        *q1 = e1b;
    }
    t = *(u32 *)p1;
    p1[0xB] = c64;
    c = D_800D3C10_b;
    *(s16 *)(p1 + 0x12) = c7840;
    *(s16 *)(p1 + 0xC) = 0;
    *(s16 *)(p1 + 0xE) = cm28;
    p1[0x10] = 0;
    p1[0x11] = c38;
    *(s16 *)(p1 + 0x14) = c256;
    *(s16 *)(p1 + 0x16) = c60;
    p1[0xA] = c;
    p1[9] = c;
    p1[8] = c;

    ot = (u32 *)(D_800AA60C + n);
    {
        register u32 m24 __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus9)
        u32 mFF;

        m24 = 0xFFFFFF;
        mFF = 0xFF000000;
        *(u32 *)p1 = (t & mFF) | (*ot & m24);
        *ot = (*ot & mFF) | ((u32)p1 & m24);
        *(u32 *)p0 = (*(u32 *)p0 & mFF) | (*ot & m24);
        *ot = (*ot & mFF) | ((u32)p0 & m24);
    }
}


INCLUDE_RODATA("asm/md_MAIN_001/nonmatchings/md_MAIN_001", D_800CEDF8);
