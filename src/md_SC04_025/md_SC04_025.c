#include "common.h"

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7B3C);


extern s32 func_800167F0(s32 a0);

s32 func_801E7B94(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801E7E68(void *arg0);

s32 func_801E7BB8(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801E7E68, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7C04);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7CA4);



void func_801E7CC4(void *a0) {

    extern void (*D_801E8608[])(void);
    D_801E8608[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D00(void *a0) {

    extern void (*D_801E8610[])(void);
    D_801E8610[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801E7D3C(void *a0) {

    extern void (*D_801E8694[])(void);
    D_801E8694[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7D78);

INCLUDE_RODATA("asm/md_SC04_025/nonmatchings/md_SC04_025", D_801E7B28);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7DA0);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7E08);

void func_801E7E60(void) {
}



void func_801E7E68(void *a0) {

    extern void (*D_801E86A4[])(void);
    D_801E86A4[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7EA4);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7EC4);

void func_801E7F2C(void) {
}

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E7F34);



void func_801E7FF8(void *a0) {

    extern void (*D_801E86B0[])(void);
    D_801E86B0[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E8034);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E805C);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E8254);



void func_801E8284(void *a0) {

    extern void (*D_801E87F0[])(void);
    D_801E87F0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E82C0);



void func_801E830C(void) {

    extern s32 D_801EE5D4;
    D_801EE5D4 = 1;
}




s32 func_801E8320(void) {

    extern s32 D_801EE5D4;
    return D_801EE5D4;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801E8330(void) {
        if ((func_80029178(0x10e) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x10e, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E836C);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E8428);

INCLUDE_ASM("asm/md_SC04_025/nonmatchings/md_SC04_025", func_801E855C);
