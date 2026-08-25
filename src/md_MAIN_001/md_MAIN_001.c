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


INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CEF04);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CEF54);

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


INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CF180);

INCLUDE_ASM("asm/md_MAIN_001/nonmatchings/md_MAIN_001", func_800CF290);

INCLUDE_RODATA("asm/md_MAIN_001/nonmatchings/md_MAIN_001", D_800CEDF8);
