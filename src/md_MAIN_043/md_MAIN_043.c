#include "common.h"

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCB20);

void func_800CCB8C(void *a0) {

    extern void (*D_800CD6DC[])(void);
    s32 e;

    e = *(u16 *)((s32)a0 + 0x2) - 2;
    D_800CD6DC[e]();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCBCC);

void func_800CCC88(void *a0) {
    extern void func_8014ED28(s32);
    extern void func_80146D90(s32);
    extern void func_8016151C(void *);
    extern s32 func_801725A4(u8 *);
    extern void func_80154274(s32 *, s32);
    extern void func_80146CA0(void *);
    extern s16 D_800D5404[];

    if (((int (*)(int))func_8014ED28)((s32)a0) != 0) {
        func_80146D90((s32)a0);
    }
    func_8016151C(a0);
    func_801725A4((u8 *)a0);
    if (*(u16 *)((char *)a0 + 0xB8) & 0x8000) {
        func_80154274((s32 *)a0, (s32)&D_800D5404);
        func_80146CA0(a0);
    }
    func_800CCEAC(a0);
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCD04);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCDC4);

extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_8013C9C4(void *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_8014C010(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern s32 D_800D3414;

void func_800CCE24(void *a0) {
    s32 s0;

    s0 = (s32)a0;
    func_8014B5C4((s32 *)s0, 2, 0);
    func_8013C9C4(&D_800D3414);
    func_801466F0(5, s0, 0, 0, 0, 0, 0, 1);
    func_8014C010((s32 *)s0, 1);
    func_80147324(0x47D);
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCEA0);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCEAC);



void func_800CCF14(void *a0) {

    extern void (*D_800CD6EC[])(void);
    D_800CD6EC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CCF50);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD054);

extern void func_80162CCC(void);
void func_800CD1D4(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD1F4);

s32 func_800CD258(void *a0, void *a1) {
    s32 v;
    *(u8 *)((s32)a1 + 8) = 0;
    *(u8 *)((s32)a1 + 9) = 0;
    *(u8 *)((s32)a1 + 10) = 0;
    v = (*(u32 *)((s32)a0 + 0x1C)) << 3;
    *(u8 *)((s32)a1 + 14) = 0;
    *(u8 *)((s32)a1 + 12) = v;
    *(u8 *)((s32)a1 + 13) = v;
    return v;
}


typedef struct {
    s16 m[9];
    s16 pad;
    s32 t[3];
} Mtx_800CD27C;

typedef struct {
    Mtx_800CD27C mt; /* 0x00 */
    s32 rest[2];     /* 0x20..0x27 — frame padding, never touched */
} MtxBuf_800CD27C;

extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);

void func_800CD27C(s32 a0) {
    MtxBuf_800CD27C buf;
    s32 obj;

    obj = *(s32 *)(a0 + 0x20);
    func_80013F3C((s32)&buf);
    func_800126C4((s32)&buf, *(s16 *)(obj + 0x10));
    func_800123F0((s32)&buf, *(s16 *)(obj + 0x14));
    func_80012558((s32)&buf, *(s16 *)(obj + 0x12));
    func_800126C4((s32)&buf, 0x400);
    *(Mtx_800CD27C *)(*(s32 *)(obj + 0x34)) = buf.mt;
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD31C);



void func_800CD3C8(void *a0) {

    extern void (*D_800CD6F8[])(void);
    D_800CD6F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD404);

INCLUDE_ASM("asm/md_MAIN_043/nonmatchings/md_MAIN_043", func_800CD57C);

extern void func_80162CCC(void);
void func_800CD650(void) {
    func_80162CCC();
}


extern void func_800233CC(void *arg0, u16 arg1);

void func_800CD670(s32 arg0, void *arg1)
{
    s32 t;

    func_800233CC(arg1, 0x40);
    *(u8 *)(arg1 + 0) = 0;
    *(u8 *)(arg1 + 1) = 0;
    *(u8 *)(arg1 + 2) = 0;
    t = *(s16 *)(arg0 + 0x62) * 12;
    *(u8 *)(arg1 + 6) = 0;
    *(u8 *)(arg1 + 5) = t;
    *(u8 *)(arg1 + 4) = t;
}


void func_800CD6D4(void) {
}

INCLUDE_RODATA("asm/md_MAIN_043/nonmatchings/md_MAIN_043", D_800CCB1C);
