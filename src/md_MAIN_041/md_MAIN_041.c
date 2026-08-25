#include "common.h"

extern s32 func_800183E0(s32 *a0);
void func_800CAE0C(void) {

    extern s32 D_800CB85C;
    func_800183E0(&D_800CB85C);
}




void func_800CAE34(void *a0) {

    extern void (*D_800CB7D4[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB7D4[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAEC0(u8 *a0);
void func_800CAE78(u8 *a0) {
    if (func_80161104()) {
        func_800CAEC0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CAEC0);

INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CAF08);

void func_800CAF88(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


extern u8 D_80078EC1;
extern void (*D_800CB7EC[])(void);
extern void func_80162D28(s32 *a0);
extern void func_800CB338(void);

void func_800CAF9C(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1E) {
        index = *(u16 *)(a0 + 2);
        D_800CB7EC[index]();

        if (*(s32 *)(a0 + 0x20) != 0) {
            func_80162D28((s32 *)a0);
        }

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB338)(a0);
    } else {
        ((void (*)(s32))func_800CB338)(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB028);

extern void func_80162FF4();
extern void func_80162FC0(s32 *a0);
extern s32 func_80146E98(s32 a0);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328();
extern s32 func_801632F0();
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 a0);
extern u8 D_80114EB0[];
extern u8 D_80114EC8[];
extern s16 D_80126B18;
extern s16 D_80126B1A;
extern s16 D_80126B1C;

void func_800CB118(s32 a0) {
    s32 sp20[2];
    s32 sp28;
    register s32 ret __asm__("$3");
    register s32 m __asm__("$2");

    func_80162FF4(a0, 0, 0x4000, 0);
    func_80162FC0((s32 *) a0);
    if (func_80146E98(a0) != 0) {
        func_80146CA0((void *) a0);
        return;
    }
    ret = func_801638A0((u8 *) a0, (s32) sp20);
    if (ret == 0) {
    } else if ((m = ret & 0x8000) != 0) {
        *(s32 *)(a0 + 0x2C) = 0;
        *(s32 *)(a0 + 0x24) = 0;
    } else {
        func_80146E90((s32 *) a0, 0x20);
        func_80146CA0((void *) a0);
        return;
    }
    func_80163408(a0, 0x2C, 0x80, 0x200);
    func_80163328(a0);
    switch ((u32) func_801632F0(a0)) {
    case 1:
        func_80013E94(D_80114EB0, &sp28);
        sp28 |= 0x80000000;
        func_80146A6C(0x1F, (void *) a0, D_80126B18, D_80126B1A, D_80126B1C, sp28, 0);
        func_80147324(0x8E6);
        break;
    case 2:
    case 4:
        func_80013E94(D_80114EC8, &sp28);
        sp28 |= 0x80000000;
        func_80146A6C(7, (void *) a0, D_80126B18, D_80126B1A, D_80126B1C, sp28, 0);
        break;
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB2B4(s32 *a0) {
    s32 *s1;

    s1 = (s32 *)a0[0x20 / 4];
    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
    } else if (a0[0x1C / 4] & 1) {
        s1[1] |= 0x80000000;
    } else {
        s1[1] &= 0x7FFFFFFF;
    }
}


extern void func_80162CCC(void);
void func_800CB338(void) {
    func_80162CCC();
}


#include "common.h"

void func_800CB358(void *param_1) {
    extern void (*D_800CB834[])(void);
    extern void func_80146C3C();

    if (*(u16 *)(*(s32 *)((s32)param_1 + 0x34)) == 0x26) {
        D_800CB834[*(u16 *)((s32)param_1 + 2)]();
    } else {
        func_80146C3C(param_1);
    }
}


INCLUDE_ASM("asm/md_MAIN_041/nonmatchings/md_MAIN_041", func_800CB3BC);

void func_800CB634(s32 a0) {
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(u16 *)(a0 + 0x12) = 0;
    *(u16 *)(a0 + 0x10) = 0x80;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


#include "common.h"

typedef struct { s32 m[8]; } Mat_800CB658;
struct Src_800CB658 {
    u8 pad0[0x34];
    Mat_800CB658 mat;
};
struct Node_800CB658 {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x2];
    s16 unkA;
    u8 padC[0x2];
    s16 unkE;
    u8 pad10[0x10];
    struct Src_800CB658 *unk20;
};
struct Entity_800CB658 {
    u8 pad0[0x6];
    s16 unk6;
    u8 pad8[0x2];
    s16 unkA;
    u8 padC[0x2];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    u8 pad14[0x8];
    s32 unk1C;
    u8 pad20[0x14];
    struct Node_800CB658 *unk34;
    Mat_800CB658 mat;
};

extern s32 rand(void);
extern void func_800CB3BC();
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

s32 func_800CB658(s32 arg0) {
    struct Node_800CB658 *node;
    struct Entity_800CB658 *ent;
    s32 v;

    node = ((struct Entity_800CB658 *)arg0)->unk34;
    if (((struct Entity_800CB658 *)arg0)->unk12 > ((struct Entity_800CB658 *)arg0)->unk10) {
        if (((struct Entity_800CB658 *)arg0)->unk1C > 0) {
            ((struct Entity_800CB658 *)arg0)->unk10 = (s16)(rand() & 0x30);
            v = -0x30;
            goto shared;
        }
    } else if (((struct Entity_800CB658 *)arg0)->unk1C < 0) {
        ((struct Entity_800CB658 *)arg0)->unk10 = (s16)((rand() & 0x30) + 0x40);
        v = 0x30;
    shared:
        ((struct Entity_800CB658 *)arg0)->unk1C = v;
    }
    ((struct Entity_800CB658 *)arg0)->unk12 = (s16)(((struct Entity_800CB658 *)arg0)->unk12 + ((struct Entity_800CB658 *)arg0)->unk1C);
    ((struct Entity_800CB658 *)arg0)->mat = node->unk20->mat;
    func_800CB3BC(arg0, 0, 0, -0x50);
    ent = ((struct Entity_800CB658 *(*)(s32, void *, s16, s16, s32, s32, s32))func_80146A6C)(0xE, (void *)arg0, ((struct Entity_800CB658 *)arg0)->unk6, ((struct Entity_800CB658 *)arg0)->unkA, ((struct Entity_800CB658 *)arg0)->unkE, 0, 0);
    if (ent != 0) {
        ent->mat = node->unk20->mat;
    }
}

