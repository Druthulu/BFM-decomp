#include "common.h"

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7B50);


extern s32 func_800167F0(s32 a0);

s32 func_801E7BA8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E7C(void *arg0);

s32 func_801E7BCC(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E7C, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}




extern s32 func_800D1E28(void);
extern s32 func_8002D4C8(s32, s32);
extern s32 func_8001BFD0(void);
extern s32 func_800291B4(s32);
extern s32 func_80029524(void);
extern s32 func_800D0C48(s32);

s32 func_801E7C18(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0 && func_80029524() == 0) {
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_801E7CB8(void) {
    func_800D1EBC();
}




void func_801E7CD8(void *a0) {

    extern void (*D_801E873C[])(void);
    D_801E873C[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D14(void *a0) {

    extern void (*D_801E8744[])(void);
    D_801E8744[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D50(void *a0) {

    extern void (*D_801E87C8[])(void);
    D_801E87C8[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(void);
void func_801E7D8C(void) {
    ((void (*)(void))func_80171A1C)();
    func_80175414();
}


INCLUDE_RODATA("asm/md_SC04_028/nonmatchings/md_SC04_028", D_801E7B28);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7DB4);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801E7E1C(void *arg0) {

    extern u8 D_801E8798[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801E8798));
        func_80171A1C(arg0);
    }
}


void func_801E7E74(void) {
}



void func_801E7E7C(void *a0) {

    extern void (*D_801E87D8[])(void);
    D_801E87D8[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801E7EB8(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7ED8);

void func_801E7F40(void) {
}

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7F48);



void func_801E800C(void *a0) {

    extern void (*D_801E87E4[])(void);
    D_801E87E4[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8048);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8070);


u8 func_801E8208(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8238);



void func_801E8394(void *a0) {

    extern void (*D_801E8B00[])(void);
    D_801E8B00[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E83D0);



void func_801E83E0(void) {

    extern s32 D_801EFB14;
    D_801EFB14 = 1;
}




s32 func_801E83F4(void) {

    extern s32 D_801EFB14;
    return D_801EFB14;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E8404(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8440);

extern void func_80029514(int);
void func_801E851C(void) {
    func_80029514(0x181);
}


extern void func_8018CDEC(void);
void func_801E853C(void) {
    func_8018CDEC();
}


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E855C);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E85E8);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8600);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8630);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E868C);
