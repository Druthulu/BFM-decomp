#include "common.h"

extern u16 D_800B99E4;
extern u8 D_800CFABF;
extern u8 D_800CFAC4[];
extern u8 D_800CFAD4[];
extern void (*D_800CFADC[])(void);
extern s32 D_800D1364;
extern u8 D_800AF630[];
extern void func_8001534C(int, void *, int, int, int, int);

void func_800CEE2C(void) {
    u8 *base = D_800AF630;
    u8 *p;
    u8 v1;
    u16 idx;

    p = &D_800CFABF;
    v1 = *(u8 *)&D_800B99E4;
    v1 += 0x30;
    *p = v1;
    func_8001534C(1, p - 0xB, 0x60, 0x64, 0, 0);

    if (D_800D1364) {
        func_8001534C(2, D_800CFAC4, 0x60, 0x70, 0, 0);
    } else {
        func_8001534C(3, D_800CFAD4, 0x60, 0x70, 0, 0);
    }

    idx = *(u16 *)(base + 0xA3B4);
    if (idx < 4) {
        D_800CFADC[idx]();
    }
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CEEFC);



void func_800CEF60(void) {
    extern s32 func_800167F0(s32 a0);
    extern void func_800118AC(void);

    if (func_800167F0(0) & 0xFFFF) {
        func_800118AC();
    }
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CEF94);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CEFF8);


extern u16 D_800B99E4;
extern void (*D_800D133C[])(void);

void func_800CF02C(void) {
    D_800D133C[D_800B99E4]();
}


INCLUDE_RODATA("asm/md_MAIN_007/nonmatchings/md_MAIN_007", D_800CEDF8);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF068);


extern s32 D_800D1374;   /* the target reads it with lw (real-TU diff), not lhu */
extern void (*D_800D1344[])(void);

void func_800CF0B8(void) {
    D_800D1344[D_800D1374]();
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF0F4);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF148);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF1CC);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF220);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF268);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF2BC);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF33C);

extern void func_800CF3B0(void *a0, void *a1, void *a2);

void func_800CF390(void *a0, void *a1, void *a2) {
    func_800CF3B0(a0, a1, a2);
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF3B0);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF408);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF6D0);
