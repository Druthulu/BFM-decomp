#include "common.h"





extern void func_80178CBC(s32, s32);
    extern short D_801F0B24;
    void func_801EF46C(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0xF;   /* constant from the real-TU diff (li v0,0xF) */
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_80178CBC)((s32 *)a0, (s32)&D_801F0B24);
    }


extern s32 func_801789AC(s32 a0);
extern void func_80178CBC(s32 a0, s32 a1);
extern s32 func_80178970(s32 *a0);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80029514(s32 a0);
extern void func_80178D18(u8 *a0);
extern void func_801EF560(void *a0);
extern s32 D_801F0C34;
extern s32 D_801F0D24;

void func_801EF49C(void *a0) {
    s32 v1;

    v1 = *(u16 *)((s32)a0 + 0x34);

    if (v1 != 0) {
        if (v1 == 1) {
            goto L801EF51C;
        }
        return;
    }

    v1 = func_801789AC((s32)a0);
    if (v1 == 0) {
        return;
    }
    if (v1 == 1) {
        func_80178CBC((s32)a0, (s32)&D_801F0C34);
        *(s16 *)((s32)a0 + 0x34) = 1;
    } else {
        func_80178CBC((s32)a0, (s32)&D_801F0D24);
    }
    return;

L801EF51C:
    if (func_80178970((s32 *)a0)) {
        func_80029124(0xEC, 1);
        func_80029514(0x6E);
        func_80178D18((u8 *)a0);
        func_801EF560(a0);
    }
}




void func_801EF560(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x10;   /* NEAR-COUSIN constant from the real-TU diff (li v0,0x10) */
    }


extern s32 func_801858CC(s32);   /* one spelling per TU (§376); the 3-arg call below is fn-ptr cast */

void func_801EF56C(void *a0, void *a1, void *a2) {
    ((void (*)(void *, void *, void *))func_801858CC)(a0, a1, a2);
}






void func_801EF58C(void *a0) {
    extern short D_801F0900;
    extern short D_801F0D84;
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x15;
    func_8012E8E0((s32)a0, (s32)&D_801F0900);
    func_8012E88C((s32)a0);
    func_80187344((s32)a0);
    func_80178CBC((s32 *)a0, (s32)&D_801F0D84);
}


extern s32 func_80178970(s32 *a0);
extern void func_80178D18(u8 *a0);
extern s32 func_801858CC(s32);
void func_801EF5E4(u8 * a0)
{
    if (func_80178970(a0)) {
        func_80178D18((u8 *)a0);
        func_801858CC((s32)a0);
    }
}


INCLUDE_ASM("asm/md_SC03_053/nonmatchings/md_SC03_053", func_801EF624);

INCLUDE_ASM("asm/md_SC03_053/nonmatchings/md_SC03_053", func_801EF6B0);

INCLUDE_ASM("asm/md_SC03_053/nonmatchings/md_SC03_053", func_801EF734);

INCLUDE_ASM("asm/md_SC03_053/nonmatchings/md_SC03_053", func_801EF7E4);





void func_801EF904(void *a0) {
    extern short D_801F0900;
    extern short D_801F0ACC;
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0xA;
    func_8012E8E0((s32)a0, (s32)&D_801F0900);
    func_8012E88C((s32)a0);
    func_80187344((s32)a0);
    func_80178CBC((s32 *)a0, (s32)&D_801F0ACC);
}


INCLUDE_ASM("asm/md_SC03_053/nonmatchings/md_SC03_053", func_801EF95C);



extern s32 func_8012E544(s32 a0);

void func_801EF9AC(void) {
    s32 v0 = func_8012E544(0x157);
    if (v0 != 0) {
        *(s16*)(v0 + 0xfc) = 1;
    }
}




extern s32 func_8012E544(s32 a0);

void func_801EF9DC(void) {
    s32 v0 = func_8012E544(0x157);
    if (v0 != 0) {
        *(s16*)(v0 + 0xFC) = 2;
    }
}




extern s32 func_8012E544(s32 a0);

void func_801EFA0C(void) {
    s32 v0 = func_8012E544(0x157);
    if (v0 != 0) {
        *(s16*)(v0 + 0xfc) = 3;
    }
}


INCLUDE_RODATA("asm/md_SC03_053/nonmatchings/md_SC03_053", D_801EF468);
