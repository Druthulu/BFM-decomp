#include "common.h"

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801ED9B0);


extern s32 func_800167F0(s32 a0);

s32 func_801EDA08(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EDCF4(void *arg0);

s32 func_801EDA2C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EDCF4, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029504(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_800D0C48(s32);
extern s32 func_800D1E28(void);

s32 func_801EDA78(s32 param_1) {
    u32 s1 = func_80029504();

    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 &&
            (s1 - 0x384) >= 0x6E && (s1 - 0x460) >= 0x32) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801EDB30(void) {
    func_800D1EBC();
}




void func_801EDB50(void *a0) {

    extern void (*D_801EE5C4[])(void);
    D_801EE5C4[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDB8C(void *a0) {

    extern void (*D_801EE5CC[])(void);
    D_801EE5CC[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EDBC8(void *a0) {

    extern void (*D_801EE650[])(void);
    D_801EE650[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801EDC04(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC05_027/nonmatchings/md_SC05_027", D_801ED988);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDC2C);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EDC94(void *arg0) {

    extern u8 D_801EE620[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801EE620));
        func_80171A1C(arg0);
    }
}


void func_801EDCEC(void) {
}



void func_801EDCF4(void *a0) {

    extern void (*D_801EE660[])(void);
    D_801EE660[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801EDD30(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDD50);

void func_801EDDB8(void) {
}

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDDC0);



void func_801EDE84(void *a0) {

    extern void (*D_801EE66C[])(void);
    D_801EE66C[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDEC0);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EDEE8);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE080);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE0C0);



void func_801EE21C(void *a0) {

    extern void (*D_801EE988[])(void);
    D_801EE988[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE258);



void func_801EE268(void) {

    extern s32 D_801F599C;
    D_801F599C = 1;
}




s32 func_801EE27C(void) {

    extern s32 D_801F599C;
    return D_801F599C;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EE28C(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE2C8);

extern void func_80029514(int);
void func_801EE3A4(void) {
    func_80029514(0x181);
}


extern void func_8018CDB0(void);
void func_801EE3C4(void) {
    func_8018CDB0();
}


INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE3E4);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE470);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE488);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE4B8);

INCLUDE_ASM("asm/md_SC05_027/nonmatchings/md_SC05_027", func_801EE514);
