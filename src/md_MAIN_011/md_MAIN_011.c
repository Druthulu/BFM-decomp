#include "common.h"

#include "common.h"

extern u8 D_800AF630[];

typedef struct { void (*fn)(void); } FnEntry;
extern FnEntry D_800D4C54[];

void func_800CEE74(void) {
    register u8 *base = (u8 *)D_800AF630;
    if (*(u16 *)(base + 0xA3B4) < 5u) {
        D_800D4C54[*(u16 *)(base + 0xA3B4)].fn();
    }
}


void func_800CEF00(void) {
    typedef struct { s32 m; } S70;
    extern u8 D_800AF630[];
    extern u8 D_800D31FC[];
    extern u8 D_800D31F8[];
    extern u8 D_800D3248[];
    extern u8 D_800D3208[];
    extern u8 D_800D3214[];
    extern u8 D_800D3220[];
    extern u8 D_800D3228[];
    extern u8 D_800D3230[];
    extern u8 D_800D3238[];
    extern u8 D_800D3250[];
    extern u8 D_800D3258[];
    extern u8 D_800D3264[];
    extern u8 D_800D3278[];
    extern u8 D_800D3284[];
    extern s32 D_800D4C88;
    extern s32 D_800D4C8C;
    extern s32 D_800D4C90;
    extern s32 D_800D4C94;
    extern u8 D_800D4B64[];
    extern S70 D_800D4B70[];
    extern u16 D_800D4C80;
    extern u16 D_800D4C84;
    extern u16 D_800D4CA4;
    extern u16 D_800D4CA0;
    extern u16 D_800D4C9C;
    extern u16 D_800D4C98;
    extern s32 D_800D3344;
    register u8 *v0 = D_800AF630;

    v0[0xA3E1] = 1;
    func_8001C044();
    func_80015310();
    func_80011B7C(0);
    func_8001534C(0, D_800D31FC, 0x40, 0x1E, 0, 0);
    func_8001534C(1, D_800D31F8, 0x34, 0x46, 0, 0);
    func_8001534C(9, D_800D3248, 0x40, 0x46, 0, 0);
    func_8001534C(2, D_800D3208, 0x40, 0x5E, 0, 0);
    func_8001534C(3, D_800D3214, 0x40, 0x6A, 0, 0);
    func_8001534C(4, D_800D3220, 0x40, 0x76, 0, 0);
    func_8001534C(5, D_800D3228, 0x40, 0x82, 0, 0);
    func_8001534C(6, D_800D3230, 0x40, 0x8E, 0, 0);
    func_8001534C(7, D_800D3238, 0x40, 0x9A, 0, 0);
    func_8001534C(0xA, D_800D3250, 0x74, 0x46, 0, 0);
    func_8001534C(0xB, D_800D3258, 0x74, 0x52, 0, 0);
    func_8001534C(0xE, D_800D3264, 0x40, 0xA6, 0, 0);
    func_8001534C(0xF, D_800D3278, 0x40, 0xB2, 0, 0);
    func_8001534C(0x10, D_800D3284, 0x40, 0xBE, 0, 0);
    D_800D4C88 = 0;
    D_800D4C8C = 0;
    D_800D4C90 = 0;
    D_800D4C94 = 0;
    *(u16 *)&v0[0xA3DE] = 0;
    func_8001534C(0xC, &D_800D4B64[D_800D4C88 * 20], 0xA4, 0x46, 0x44, 0);
    func_8001534C(0xD, D_800D4B70[D_800D4C88 * 5].m + D_800D4C8C * 36, 0xA4, 0x52, 0x44, 0);
    D_800D4C80 = 0;
    D_800D4C84 = 0;
    D_800D4CA4 = 0;
    D_800D4CA0 = 0;
    D_800D4C9C = 0;
    D_800D4C98 = 0;
    func_80029514(D_800D3344);
    func_800118AC();
}


INCLUDE_RODATA("asm/md_MAIN_011/nonmatchings/md_MAIN_011", D_800CEDF8);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CF28C);

void func_800CFB88(void) {
    extern s32 D_800D4C90;
    extern void *D_800D32F8[];
    extern void func_8001534C(int, void *, int, int, int, int);
    func_8001534C(0x1C, D_800D32F8[D_800D4C90], 0x78, 0x82, 0, 0);
}


void func_800CFBF0(void) {
    extern s32 D_800D4C94;
    extern s32 D_800D3314[];
    func_8001534C(0x1A, D_800D3314[D_800D4C94], 0x90, 0x9A, 0, 0);
}


INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFC58);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFCBC);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFDB4);

extern u8 D_800AF630[];

void func_800D03F8(void) {
    register u8 *v0 = D_800AF630;

    *(u16 *)(v0 + 0xA3B6) = 1;
}


void func_800D0430(void) {
}




extern s16 D_800D4C80;
extern FnEntry D_800D4C68[];

void func_800D0450(void) {
    if (D_800D4C80 < 5) {
        D_800D4C68[D_800D4C80].fn();
    }
}


extern void func_80136EC4(void);

void func_800D04C4(void) {
    func_80136EC4();
}


INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D04F4);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0828);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0858);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0964);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D0BDC);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D1254);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D1B00);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D235C);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D2BC4);
