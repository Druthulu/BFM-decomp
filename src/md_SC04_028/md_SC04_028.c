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


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7C18);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7CB8);



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


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7D8C);

INCLUDE_RODATA("asm/md_SC04_028/nonmatchings/md_SC04_028", D_801E7B28);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7DB4);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7E1C);

void func_801E7E74(void) {
}



void func_801E7E7C(void *a0) {

    extern void (*D_801E87D8[])(void);
    D_801E87D8[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E7EB8);

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

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8208);

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

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E851C);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E853C);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E855C);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E85E8);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8600);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E8630);

INCLUDE_ASM("asm/md_SC04_028/nonmatchings/md_SC04_028", func_801E868C);
