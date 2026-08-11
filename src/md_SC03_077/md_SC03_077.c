#include "common.h"

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF490);


extern s32 func_800167F0(s32 a0);

s32 func_801EF4E8(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801EF7CC(void *arg0);

s32 func_801EF50C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801EF7CC, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 16;
    return 0;
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF558);

extern void func_800D1EBC(void);
void func_801EF608(void) {
    func_800D1EBC();
}




void func_801EF628(void *a0) {

    extern void (*D_801F008C[])(void);
    D_801F008C[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF664(void *a0) {

    extern void (*D_801F0094[])(void);
    D_801F0094[*(u8 *)((s32)a0 + 0x15)]();
}




void func_801EF6A0(void *a0) {

    extern void (*D_801F0118[])(void);
    D_801F0118[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
extern void func_80175414(s32 _arg0);
void func_801EF6DC(void) {
    ((void (*)(void))func_80171A1C)();
    ((void (*)(void))func_80175414)();
}


INCLUDE_RODATA("asm/md_SC03_077/nonmatchings/md_SC03_077", D_801EF468);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF704);


extern s32 func_80014C54(s32, s32, s32);
extern void func_800D1724(void *);
extern void func_80171A1C(void *);

void func_801EF76C(void *arg0) {

    extern u8 D_801F00E8[];
    s32 result;
    result = func_80014C54(0, 0, 0x80);
    if ((result << 16) != 0) {
        func_800D1724(&(*(int *)D_801F00E8));
        func_80171A1C(arg0);
    }
}


void func_801EF7C4(void) {
}



void func_801EF7CC(void *a0) {

    extern void (*D_801F0128[])(void);
    D_801F0128[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171A1C(void*);
void func_801EF808(void) {
    ((void (*)(void))func_80171A1C)();
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF828);

void func_801EF890(void) {
}

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF898);



void func_801EF95C(void *a0) {

    extern void (*D_801F0134[])(void);
    D_801F0134[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF998);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EF9C0);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFB58);



void func_801EFCB4(void *a0) {

    extern void (*D_801F0450[])(void);
    D_801F0450[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFCF0);



void func_801EFD00(void) {

    extern s32 D_801F7464;
    D_801F7464 = 1;
}




s32 func_801EFD14(void) {

    extern s32 D_801F7464;
    return D_801F7464;
}





extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801EFD24(void) {
        if ((func_80029178(0x111) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x111, 1);
            return 1;
        }
        return 0;
    }


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFD60);

extern void func_80029514(int);
void func_801EFE3C(void) {
    func_80029514(0x181);
}


extern void func_8018D0E4(void);
void func_801EFE5C(void) {
    func_8018D0E4();
}


INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFE7C);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFF08);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFF20);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFF50);

INCLUDE_ASM("asm/md_SC03_077/nonmatchings/md_SC03_077", func_801EFFAC);


u8 func_801F005C(u32 a0) {
    if ((u32)(a0 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(a0 - 0x64) < 0x1E) {
        return 0x28;
    }
    return 0xD;
}

