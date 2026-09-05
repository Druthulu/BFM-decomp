#include "common.h"


extern void (*D_800CDD08[])(void);

void func_800CD384(void) {
    register s32 idx __asm__("$2");
    __asm__ __volatile__("" : : "r"(idx));
    D_800CDD08[idx]();
}


INCLUDE_RODATA("asm/md_MAIN_009/nonmatchings/md_MAIN_009", D_800CD348);

extern s32 func_8001B244(s32);
extern void func_8001AD38(const char*);
extern void func_800116A0(void);

extern s32 D_800CDD2C;
extern s32 D_800CDD34;

const char D_800CD34C[] = "C:\\TIMPACK\\OPDEMO0.PAT";

void func_800CD3B8(void) {
    if (func_8001B244(0x8E) == 0) {
        return;
    }

    func_8001AD38(D_800CD34C);
    D_800CDD2C = 0;
    D_800CDD34 = 0;
    func_800116A0();
}


extern s32 D_800CDD2C;
extern s32 D_800CDD34;

extern void func_800CD674(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD408(void) {
    s32 a1 = D_800CDD2C;
    s32 a2 = D_800CDD34;
    func_800CD674(0, a1, a2);

    a2 = D_800CDD34;
    a2 += 8;
    D_800CDD34 = a2;

    if (a2 < 0x80) {
        // skip
    } else {
        func_800116A0();
    }
}


extern s32 D_800CDD2C;
extern s32 D_800CDD34;
extern void func_800CD674(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD464(void) {
    func_800CD674(0, D_800CDD2C, D_800CDD34);
    D_800CDD2C--;
    if (D_800CDD2C >= -0x10F) {
        return;
    }
    D_800CDD2C = -0x110;
    func_800116A0();
}


extern s32 D_800CDD2C;
extern s32 D_800CDD34;

void func_800CD674(s32, s32, s32);
void func_800116A0(void);

void func_800CD4C8(void) {
    func_800CD674(0, D_800CDD2C, D_800CDD34);

    D_800CDD34 -= 8;
    if (D_800CDD34 <= 0) {
        func_800116A0();
    }
}


INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD520);

extern s32 D_800CDD30;
extern s32 D_800CDD34;
extern void func_800CD92C(s32, s32, s32);
extern void func_800116A0(void);

void func_800CD558(void) {
    func_800CD92C(-0x400, 0, D_800CDD34);
    D_800CDD30 = -0x340;
    D_800CDD34 += 8;
    if (D_800CDD34 >= 0x80) {
        func_800116A0();
    }
}


extern s32 D_800CDD30;
extern s32 D_800CDD34;
extern void func_800CD92C(s32 a0, s32 a1, s32 a2);
extern void func_800116A0(void);

void func_800CD5B8(void) {
    func_800CD92C(D_800CDD30, 0, D_800CDD34);
    D_800CDD30++;
    if (D_800CDD30 >= 0x141) {
        func_800116A0();
    }
}


extern s32 D_800CDD30;
extern s32 D_800CDD34;

void func_800CD92C(s32, s32, s32);
void func_800116A0(void);

void func_800CD614(void) {
    s32 v0;
    
    func_800CD92C(D_800CDD30, 0, D_800CDD34);
    v0 = D_800CDD34 - 8;
    D_800CDD34 = v0;
    if (v0 > 0) {
        return;
    }
    func_800116A0();
}


void func_800CD66C(void) {
}

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD674);

INCLUDE_ASM("asm/md_MAIN_009/nonmatchings/md_MAIN_009", func_800CD92C);
