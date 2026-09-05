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


extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_800183E0(void *a0);
extern void func_800167B8(s32 a0);
extern void func_800118AC(void);

extern s8 D_800B9A11;
extern s32 D_800D1364;
extern u16 D_800B99E8;
extern s32 D_800D130C;

void func_800CEEFC(void) {
    D_800B9A11 = 1;
    func_8001C044();
    func_80015310();
    D_800D1364 = 0;
    func_800183E0(&D_800D130C);
    func_800167B8(0);
    D_800B99E8 = 0;
    func_800118AC();
}




void func_800CEF60(void) {
    extern s32 func_800167F0(s32 a0);
    extern void func_800118AC(void);

    if (func_800167F0(0) & 0xFFFF) {
        func_800118AC();
    }
}


void func_800CEF94(void) {
    extern s32 func_80014CAC(s32 a0, s32 a1);
    extern void func_800167B8(s32 a0);
    extern void func_800118AC(void);
    extern u16 D_800B99E8;

    u16 counter = D_800B99E8;
    counter++;
    D_800B99E8 = counter;

    if ((s16)counter < 0x81) {
        s32 result = func_80014CAC(0, 0x800);
        if ((result << 16) == 0) {
            goto end;
        }
    }
    func_800167B8(4);
    func_800118AC();
end:;
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CEFF8);


extern u16 D_800B99E4;
extern void (*D_800D133C[])(void);

void func_800CF02C(void) {
    D_800D133C[D_800B99E4]();
}


INCLUDE_RODATA("asm/md_MAIN_007/nonmatchings/md_MAIN_007", D_800CEDF8);

extern void func_8001AA98(void *a0);
extern s32 D_800D1368;
extern s32 D_800D1370;
extern s32 D_800D1374;
extern void func_800167B8(s32 a0);
extern void func_800118AC(void);
const char D_800CEDFC[] = "C:\\TIMPACK\\OPDEMO0.PAT";  /* §304: the stub .s was the only owner of this rodata block */

void func_800CF068(void) {
    func_8001AA98((void *)D_800CEDFC);
    D_800D1368 = 0;
    D_800D1370 = 0;
    D_800D1374 = 0;
    func_800167B8(0);
    func_800118AC();
}



extern s32 D_800D1374;   /* the target reads it with lw (real-TU diff), not lhu */
extern void (*D_800D1344[])(void);

void func_800CF0B8(void) {
    D_800D1344[D_800D1374]();
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF0F4);

extern s32 D_800D1368;
extern s32 D_800D1374;
extern void func_800CF408(s32 a0, s32 a1);
extern void func_800167B8(s32 a0);

void func_800CF148(void) {
    // Redeclare with correct calling semantics
    extern s32 func_800CF3B0(void);
    
    if (func_800CF3B0()) {
        return;
    }
    
    func_800CF408(0, D_800D1368);
    
    D_800D1368--;
    if (D_800D1368 < -0x10F) {
        func_800167B8(0x4);
        D_800D1368 = -0x110;
        D_800D1374++;
    }
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF1CC);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF220);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF268);

extern void func_800CF6D0(s32 a0, u32 a1);
extern void func_800167B8(s32 a0);
extern s32 D_800D136C;
extern s32 D_800D1374;

void func_800CF2BC(void) {
    if (func_800CF3B0() != 0) {
        return;
    }
    func_800CF6D0(D_800D136C++, 0);
    if (D_800D136C < 0x141) {
        return;
    }
    func_800167B8(4);
    D_800D1374++;
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF33C);

extern s32 func_800CF3B0();

void func_800CF390(void *a0, void *a1, void *a2) {
    func_800CF3B0(a0, a1, a2);
}


extern s32 func_800149E0(s32);
extern u16 D_800B99E6;

s32 func_800CF3B0(void *a0, void *a1, void *a2) {
    s32 result0 = func_800149E0(0);
    s32 result1 = func_800149E0(1);
    s32 combined = result0 | result1;

    if ((combined & 0x800) != 0) {
        D_800B99E6 = 1;
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF408);

INCLUDE_ASM("asm/md_MAIN_007/nonmatchings/md_MAIN_007", func_800CF6D0);
