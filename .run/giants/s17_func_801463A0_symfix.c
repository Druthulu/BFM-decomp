// @class: struct
// @stuck: none — MATCH (101 ins). Keys: 8-byte BE0->BE8 unaligned copy via char[8] struct (align 1 -> lwl/lwr/swl/swr); three sh to separate BE0/BE2/BE4 globals; D_80126B78 is s32* loaded once into $s0 at top; three short assigns MUST precede the D_80126B9C read-modify-write so the B9C store schedules last.
#include "common.h"

typedef struct { char _b[8]; } M8_801463A0;   /* size 8, align 1 -> unaligned lwl/lwr copy */

extern void func_8014C6F4(void *);
extern void func_80155150(void *);
extern void func_801470C0(s32);
extern void func_80147478(s32);
extern void func_80147118(s32);
extern void func_8014BDE8(s32);
extern short func_801508F8(s32);
extern void func_8014B5B0(s32*);
extern void func_80161D88(void *);

extern s32 D_80126B58;
extern s32 *D_80126B78;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_80126C90;
extern u16 D_80126C92;
extern u16 D_80126C94;
extern s32 D_80126B9C;
extern s32 D_80126BA0;
extern M8_801463A0 D_80126BE0;
extern M8_801463A0 D_80126BE8;
extern u16 D_80126BE2;
extern u16 D_80126BE4;
extern short D_80126C9E;

void func_801463A0(void) {
    int iVar1;
    short sVar2;

    iVar1 = (int)D_80126B78;
    func_8014C6F4(&D_80126B58);
    func_80155150(&D_80126B58);
    ((void (*)(void *))func_801470C0)(&D_80126B58);
    ((void (*)(void *))func_80147478)(&D_80126B58);
    ((void (*)(void *))func_80147118)(&D_80126B58);
    if (iVar1 != 0) {
        sVar2 = D_80126B5E + D_80126C90;
        *(short *)(iVar1 + 8) = sVar2;
        *(int *)(iVar1 + 0x48) = (int)sVar2;
        sVar2 = D_80126B62 + D_80126C92;
        *(short *)(iVar1 + 0xA) = sVar2;
        *(int *)(iVar1 + 0x4C) = (int)sVar2;
        sVar2 = D_80126B66 + D_80126C94;
        *(short *)(iVar1 + 0xC) = sVar2;
        *(unsigned short *)(iVar1 + 0x2C) = *(unsigned short *)(iVar1 + 0x2C) | 0x11;
        *(int *)(iVar1 + 0x50) = (int)sVar2;
    }
    ((void (*)(void *))func_8014BDE8)(&D_80126B58);
    D_80126BE8 = D_80126BE0;
    (*(u16 *)&D_80126BE0) = D_80126B5E;
    D_80126BE2 = D_80126B62;
    D_80126BE4 = D_80126B66;
    D_80126BA0 = D_80126B9C;
    D_80126B9C = D_80126B9C & 0x3fffffff;
    ((void (*)(void *))func_801508F8)(&D_80126B58);
    D_80126C9E = 0;
    ((void (*)(void *))func_8014B5B0)(&D_80126B58);
    func_80161D88(&D_80126B58);
}
